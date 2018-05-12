/* 
   Old School v2 "The future is here"
   - - - - - - - - - - - - - - - - - -
		DEATH GOP GORTHOL DESK
   - - - - - - - - - - - - - - - - - -
*/
//JOB ID -> 8
//Heladero -> 423 // Perritos -> 588

#define AMB_$xCP 100 // Cantidad de dinero que recibe por checkpoint pasados los 3 minutos

new Float:ChecksVendedorAmbulante[6][3] = {
{1208.6206,-1699.8248,13.3426},
{310.5056,-1799.5725,4.2942},
{1219.3057,-1417.2056,13.0930},
{1834.2611,-1884.3628,13.2045},
{1791.8082,-1623.2368,13.3594},
{1519.1069,-1434.1648,13.3342}
};

Ambulan_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd,"/debugamb",true)==0)
	{
		format(string,sizeof(string),"pTrabajando: %d - pCheckpoint: %d - pTrabajoVeh: %d - pTrabajandoCP: %d - pListoCobro: %d",
			PlayerInfo[playerid][pTrabajando], PlayerInfo[playerid][pCheckpoint], PlayerInfo[playerid][pTrabajoVeh], PlayerInfo[playerid][pTrabajandoCP], PlayerInfo[playerid][pListoCobro]);
		SendClientMessage(playerid,Amarillo,string);
		return 1;
	}
	if(strcmp(cmd,"/cleanamb",true)==0)
	{
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
		PlayerInfo[playerid][pListoCobro] = 0;
		DisablePlayerCheckpoint(playerid);
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------------------------	
	if(strcmp(cmd,"/ambulante",true)==0)
	{
	    if(PlayerInfo[playerid][pJob] != 8) { SendClientMessage(playerid, Rojo, "* Debes ser Vendedor Ambulante!"); return 1; }
		
		cmd = strtokex(cmdtext, idx);
        
        if (strcmp(cmd, "comenzar", true) == 0)
        {
			if(PlayerInfo[playerid][pTrabajando] == 1)
			{
				SendClientMessage(playerid,Rojo,"* Ya estás trabajando!");
				return 1;
			}
			if(PlayerInfo[playerid][pCheckpoint] > 0) { SendClientMessage(playerid,Rojo,"* Ya tienes un Checkpoint activo! Termina de hacer lo que tengas pendiente."); return 1;}
			
			if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
            {
                format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a vender.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
                SendClientMessage(playerid,Naranja,string);
                return 1;
            }
			
			if(!IsPlayerInAnyVehicle(playerid)) { SendClientMessage(playerid,Rojo,"* Tienes que estar montado en el vehiculo de los helados o los perritos!"); return 1; }
			else if (CarInfo[GetPlayerVehicle(playerid)][cUsos] != 108) { SendClientMessage(playerid,Rojo,"* Tienes que estar montado en el vehiculo de los helados o los perritos!"); return 1; }
			
			PlayerInfo[playerid][pTrabajando] = 1;
			Ambulan_RandomCP(playerid);
			return 1;
        }
		if (strcmp(cmd, "abandonar", true) == 0)
        {
			if(PlayerInfo[playerid][pTrabajando] == 0) { SendClientMessage(playerid, Rojo, "* No estás trabajando! Usa /ambulante comenzar."); return 1; }
			if(PlayerInfo[playerid][pTrabajando] == 1)
			{
				PlayerInfo[playerid][pTrabajando] = 0;
				PlayerInfo[playerid][pCheckpoint] = 0;
				PlayerInfo[playerid][pTrabajandoCP] = 0;
				DisablePlayerCheckpoint(playerid);
				SendClientMessage(playerid,Amarillo,"* Has cancelado la ruta!");
				return 1;
			}
			return 1;
        }
		if (strcmp(cmd, "vender", true) == 0)
        {
			if(!IsPlayerInAnyVehicle(playerid)) { SendClientMessage(playerid,Rojo,"* Tienes que estar montado en el vehiculo de los helados o los perritos!"); return 1; }
			else if (CarInfo[GetPlayerVehicle(playerid)][cUsos] != 108) { SendClientMessage(playerid,Rojo,"* Tienes que estar montado en el vehiculo de los helados o los perritos!"); return 1; }
			
			new tmp[128];
            tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /ambulante vender [IdJugador/ParteDelNombre]");
				return 1;
			}
			new giveplayerid;
			giveplayerid = ReturnUser(tmp);
			
            if(IsPlayerConnected(giveplayerid) && giveplayerid != INVALID_PLAYER_ID)
            {
				if( GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0 )
                {
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 423) //Helados
					{
						format(string, sizeof(string), "* Ofreciste a %s un helado por 15$.",pName(giveplayerid));
						SendClientMessage(playerid, Azul, string);
						format(string, sizeof(string), "* El vendedor %s te vende un helado por 15$ (Escribe /aceptar helado para comprarlo).",pName(playerid));
						SendClientMessage(giveplayerid, Azul, string);
						PlayerInfo[giveplayerid][pOfertaHelado] = playerid;
						return 1;
					}
					else //if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 588) // Perritos
					{
						format(string, sizeof(string), "* Ofreciste a %s un perrito por 20$.",pName(giveplayerid));
						SendClientMessage(playerid, Azul, string);
						format(string, sizeof(string), "* El vendedor %s te vende un perrito por 20$ (Escribe /aceptar perrito para comprarlo).",pName(playerid));
						SendClientMessage(giveplayerid, Azul, string);
						PlayerInfo[giveplayerid][pOfertaPerrito] = playerid;
						return 1;
					}
				}
                else {	SendClientMessage(playerid, Rojo, "* Jugador no cercano"); return 1; }
            }
			else { SendClientMessage(giveplayerid, Azul, "* Jugador no conectado!"); return 1; }
        }
		SendClientMessage(playerid, Blanco, "USO: /ambulante (comenzar/abandonar/vender)");
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------------------------	
	return 0;
}

Ambulan_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 8)
	{
		if(IsPlayerInAnyVehicle(playerid) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
		{
			if(PlayerInfo[playerid][pTrabajandoCP] >= 0 && (CarInfo[GetPlayerVehicle(playerid)][cModel] == 423 || CarInfo[GetPlayerVehicle(playerid)][cModel] == 588))
			{
				KillTimer(PlayerInfo[playerid][pTrabajoTimer]);
				PlayerInfo[playerid][pTrabajoTimer]=SetTimerEx("Ambulan_AvanzarCP",180000,0,"d",playerid); //3min->180s->180000ms
				SendClientMessage(playerid,Verde,"* Espera 3 minutos en esta localización y atiende a los clientes que se presenten.");
			}
		}
		return 1;
	}
	return 0;
}

Ambulan_RandomCP(playerid)
{
	new AmbulanCP = random(6);
	return Ambulan_NoRepetirCP(playerid, AmbulanCP);
}

Ambulan_NoRepetirCP(playerid, AmbulanCP)
{
	if(PlayerInfo[playerid][pTrabajandoCP] == AmbulanCP) return Ambulan_RandomCP(playerid);
	else PlayerInfo[playerid][pTrabajandoCP] = AmbulanCP; return Ambulan_MostrarCheckpoint(playerid,AmbulanCP);
}

Ambulan_MostrarCheckpoint(playerid,AmbulanCP)
{
	SetPlayerCheckpoint(playerid,ChecksVendedorAmbulante[AmbulanCP][0],ChecksVendedorAmbulante[AmbulanCP][1],ChecksVendedorAmbulante[AmbulanCP][2],10);
	PlayerInfo[playerid][pCheckpoint] = 8;
	return SendClientMessage(playerid,Verde,"* Ve a la posición marcada en el mapa y espera a los clientes.");
}

forward	Ambulan_AvanzarCP(playerid);
public Ambulan_AvanzarCP(playerid)
{
	if(!IsPlayerInCheckpoint(playerid)) return SendClientMessage(playerid,Naranja,"* Vuelve y ESPERA 3 minutos en esa localización!");
	
	SafeGivePlayerMoney(playerid,AMB_$xCP);
	PlayerInfo[playerid][pGanancias]+=AMB_$xCP;
	format(string,sizeof(string),"~g~Has ganado %d$",AMB_$xCP);
	GameTextForPlayer(playerid, string, 4000, 3);
    if (PlayerInfo[playerid][pGanancias]>=400)
    {
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
		DisablePlayerCheckpoint(playerid);
        SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue vendiendo dentro de 20 minutos.");
        PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1200);
        PlayerInfo[playerid][pGanancias]=0;
        SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
        SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
        return 1;
    }
	else
	{
        SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
		return Ambulan_RandomCP(playerid);
	}
}