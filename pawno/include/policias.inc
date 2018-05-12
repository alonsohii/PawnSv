#include <a_samp>
#include <globalvars>
#include <funciones>

Policia_OnGameModeInit()
{
	CreateDynamic3DTextLabel("Azotea", Amarillo, 277.8429,125.2676,1008.8203, 5);
	CreateDynamic3DTextLabel("Garaje", Amarillo, 214.4302,118.3369,999.5156, 5);
	CreateDynamicPickup(1314, 23, 2580.0894,-1325.8868,1047.9634);
}

Policia_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
   	new idx;
   	cmd = strtokex(cmdtext, idx);
	new giveplayerid;
	new moneys;
	
	if(strcmp(cmd, "/quitar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
	        if(IsACop(playerid) || PlayerInfo[playerid][pAdmin] > 0)
	        {
	            new x_nr[128];
				x_nr = strtokex(cmdtext, idx);
				if(!strlen(x_nr))
				{
					SendClientMessage(playerid, Blanco, "USO: /quitar [objeto] [IdJugador/ParteDelNombre]");
			  		SendClientMessage(playerid, AzulClaro, "Nombres disponibles: Conduccion, Aviacion, Navegacion, Armas, Drogas, Semillas, Objetos");
					return 1;
				}
			    if(strcmp(x_nr,"conduccion",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar conduccion [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
						        format(string, sizeof(string), "* Has retirado a %s su Licencia de Conducción.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El agente %s te ha retirado la licencia de conducir, no podrás sacarla en 3 días.", pName(playerid));
						        SendClientMessage(giveplayerid, Azul, string);
								PlayerInfo[giveplayerid][pCarLic] = 0;
								SaveValues(giveplayerid,"Licencias");
							}
							else
							{
							    SendClientMessage(playerid, Rojo, "* Jugador no cercano!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Gris, "* Jugador no conectado!");
					    return 1;
					}
				}
				else if(strcmp(x_nr,"aviacion",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar aviacion [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
						        format(string, sizeof(string), "* Has retirado a %s su Licencia de Aviacion.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El Agente %s te ha retirado la Licencia de Aviacion.", pName(playerid));
						        SendClientMessage(giveplayerid, Azul, string);
						        PlayerInfo[giveplayerid][pFlyLic] = 0;
								SaveValues(giveplayerid,"Licencias");
							}
							else
							{
							    SendClientMessage(playerid, Rojo, "* El jugador no está cerca tuya!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* Jugador no conectado!");
					    return 1;
					}
				}
				else if(strcmp(x_nr,"navegacion",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar navegacion [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
						        format(string, sizeof(string), "* Has retirado a %s su Licencia de Navegacion.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El agente %s te ha retirado la Licencia de Navegacion.", pName(playerid));
						        SendClientMessage(giveplayerid, Azul, string);
						        PlayerInfo[giveplayerid][pBoatLic] = 0;
								SaveValues(giveplayerid,"Licencias");
					        }
					        else
							{
							    SendClientMessage(playerid, Rojo, "* El jugador no está cerca tuya!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* Jugador no conectado!");
					    return 1;
					}
				}
				else if(strcmp(x_nr,"armas",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar armas [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
						        format(string, sizeof(string), "* Has retirado a %s's sus armas.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El agente %s te ha retirado las armas.", pName(playerid));
						        SendClientMessage(giveplayerid, Azul, string);
						        SafeResetPlayerWeaponsAC(giveplayerid);
					        }
					        else
							{
							    SendClientMessage(playerid, Rojo, "* El jugador no está cerca tuya!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* Jugador no conectado!");
					    return 1;
					}
				}
				else if(strcmp(x_nr,"drogas",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar drogas [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
							    format(string, sizeof(string), "* Has retirado a %s sus Drogas.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El agente %s te ha retirado las Drogas.", pName(playerid));
						        SendClientMessage(giveplayerid, Azul, string);
						        PlayerInfo[giveplayerid][pDrogaP][0]=0;
						        PlayerInfo[giveplayerid][pDrogaP][1]=0;
						        PlayerInfo[giveplayerid][pDrogaP][2]=0;
						        PlayerInfo[giveplayerid][pDrogaNP][0]=0;
						        PlayerInfo[giveplayerid][pDrogaNP][1]=0;
								SaveValues(giveplayerid,"Preparada");
								SaveValues(giveplayerid,"NoPreparada");
							}
					        else
							{
							    SendClientMessage(playerid, Rojo, "* El jugador no está cerca tuya!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* Jugador no conectado!");
					    return 1;
					}
				}
				else if(strcmp(x_nr,"semillas",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar semillas [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
							    format(string, sizeof(string), "* Has retirado a %s sus semillas.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El agente %s te ha retirado las semillas.", pName(playerid));
        						SendClientMessage(giveplayerid, Azul, string);
						        PlayerInfo[giveplayerid][pSemillas][0]=0;
						        PlayerInfo[giveplayerid][pSemillas][1]=0;
								SaveValues(giveplayerid,"Semillas");
							}
					        else
							{
							    SendClientMessage(playerid, Rojo, "* El jugador no está cerca tuya!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* Jugador no conectado!");
					    return 1;
					}
				}
                else if(strcmp(x_nr,"objetos",true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp)) {
						SendClientMessage(playerid, Blanco, "USO: /quitar objetos [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(IsPlayerConnected(giveplayerid))
					{
					    if(giveplayerid != INVALID_PLAYER_ID)
					    {
					        if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
							{
							    format(string, sizeof(string), "* Has retirado a %s el material robado.", pName(giveplayerid));
						        SendClientMessage(playerid, Azul, string);
						        format(string, sizeof(string), "* El agente %s te ha retirado el material robado.", pName(playerid));
        						SendClientMessage(giveplayerid, Azul, string);
						        if (PlayerInfo[giveplayerid][pJob] == 11) {PlayerInfo[giveplayerid][pMaterialTrabajo]=0;}
								SaveValues(giveplayerid,"Inventario");
							}
					        else
							{
							    SendClientMessage(playerid, Rojo, "* El jugador no está cerca tuya!");
							    return 1;
							}
					    }
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* Jugador no conectado!");
					    return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Nombre desconocido!");
					return 1;
				}
	        }
	        else
	        {
	            SendClientMessage(playerid, Rojo, "* No eres Policía!");
	            return 1;
	        }
	    }
	    return 1;
	}
	
	if(strcmp(cmd, "/esposar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
			if(IsACop(playerid))
			{
				giveplayerid = GetClosestPlayer(playerid);
			    if(IsPlayerConnected(giveplayerid))
				{
				    if(giveplayerid != INVALID_PLAYER_ID)
				    {
				        if(IsACop(giveplayerid))
				        {
				            SendClientMessage(playerid, Gris, "* No puedes esposar policias!");
					        return 1;
				        }
					    if(PlayerInfo[giveplayerid][pEsposado] > 1 && GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
					    {
					        SendClientMessage(playerid, Gris, "* Jugador Desesposado!");
					        TogglePlayerControllable(giveplayerid, 1);
					        PlayerInfo[giveplayerid][pEsposado] = 0;
					        return 1;
					    }
						if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
						{
						    if(giveplayerid == playerid) { SendClientMessage(playerid, Gris, "No puedes esposarte a ti mismo!"); return 1; }
						    format(string, sizeof(string), "* Has sido esposado por %s, espera a que te liberen.", pName(playerid));
							SendClientMessage(giveplayerid, AzulClaro, string);
							format(string, sizeof(string), "* Esposaste a %s.", pName(giveplayerid));
							SendClientMessage(playerid, AzulClaro, string);
							format(string, sizeof(string), "* %s esposa a %s .", pName(playerid), pName(giveplayerid));
							ProxDetector(30.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
							GameTextForPlayer(giveplayerid, "~r~Esposado!", 2500, 3);
							TogglePlayerControllable(giveplayerid, 0);
							PlayerInfo[giveplayerid][pEsposado] = 2;
						}
						else
						{
						    SendClientMessage(playerid, Gris, "* Jugador no cercano!");
						    return 1;
						}
					}
				}
				else
				{
				    SendClientMessage(playerid, Gris, "* Jugador no conectado!");
				    return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, Gris, "* No eres Policía!");
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/detener", true) ==0)
	{
		if(IsACop(playerid))
		{
			tmp = strtokex(cmdtext, idx);
	        if (!strlen(tmp))
	        {
	        	SendClientMessage(playerid, Amarillo, "USO: /detener [ID Jugador] [Asiento]");
	        	return 1;
	        }
	        new suspect = strval(tmp);

	        tmp = strtokex(cmdtext, idx);
	        if (!strlen(tmp))
	        {
	        	SendClientMessage(playerid, Amarillo, "USO: /detener [ID Jugador] [Asiento]");
	        	return 1;
	        }
	        new seat = strval(tmp);
	        new car = GetPlayerVehicleID(playerid);
			if(IsPlayerConnected(suspect))
			{
				if(GetDistanceBetweenPlayers(playerid,suspect) < 5)
				{
					if(IsPlayerInAnyVehicle(playerid))
					{
					    if(PlayerInfo[suspect][pEsposado] > 0)
						{
						    if(seat == 2 || seat == 3)
						    {
								format(string, sizeof(string), "* Has sido detenido por %s .", pName(playerid));
								SendClientMessage(suspect, AzulClaro, string);
								format(string, sizeof(string), "* Has detenido a %s .", pName(suspect));
								SendClientMessage(playerid, AzulClaro, string);
								format(string, sizeof(string), "* %s detiene a %s.", pName(playerid), pName(suspect));
								ProxDetector(30.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
								GameTextForPlayer(suspect, "~r~Detenido", 2500, 3);
								TogglePlayerControllable(suspect, 0);
								PutPlayerInVehicle(suspect,car,seat);
							}
							else
							{
							    SendClientMessage(playerid, Gris, "* Solo puedes eligir los asientos traseros. (2 o 3)");
							    return 1;
							}
						}
						else
						{
						    SendClientMessage(playerid, Gris, "* Debe estar esposarlo para poder detenerlo !");
						    return 1;
						}
					}
					else
					{
						SendClientMessage(playerid, Gris, "* Debes estar en el vehículo para detenerlo !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, Gris, "* Estás muy lejos del vehículo o sospechoso!");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, Gris, "  No formas parte de las Fuerzas del Estado !");
		}
		return 1;
	}
	
	if(strcmp(cmd,"/cachear",true)==0)
	{
       	if(IsPlayerConnected(playerid))
    	{
        	if(IsACop(playerid))
	       	{
	       		tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /cachear [Armas/Pertenencias] [IdJugador/ParteDelNombre]");
					return 1;
				}
				if(strcmp(tmp, "armas", true) == 0)
				{
				    tmp = strtokex(cmdtext, idx);
    				if(!strlen(tmp))
					{
						SendClientMessage(playerid, Blanco, "USO: /cachear [Armas/Pertenencias] [IdJugador/ParteDelNombre]");
						return 1;
					}
					if(!IsNumeric(tmp))
					giveplayerid = ReturnUser(tmp,playerid);
					else giveplayerid = strval(tmp);
					if(GetDistanceBetweenPlayers(playerid, giveplayerid) > 5.0 || !IsPlayerConnected(giveplayerid))
					{
					    return 1;
					}
					new Blanca, BlancaAmmo;
					new Pistola, PistolaAmmo;
					new Shotgun, ShotgunAmmo;
					new Metraca, MetracaAmmo;
					new Metraca2, Metraca2Ammo;
					new WeaponName[24];
					GetPlayerWeaponData(giveplayerid, 1, Blanca, BlancaAmmo);
					GetPlayerWeaponData(giveplayerid, 2, Pistola, PistolaAmmo);
					GetPlayerWeaponData(giveplayerid, 3, Shotgun, ShotgunAmmo);
					GetPlayerWeaponData(giveplayerid, 4, Metraca, MetracaAmmo);
					GetPlayerWeaponData(giveplayerid, 5, Metraca2, Metraca2Ammo);
					SendClientMessage(playerid, Verde, "__________| ARMAS ENCONTRADAS |__________");
					if(Blanca > 0) { GetWeaponName(Blanca, WeaponName, 24); format(string, sizeof(string), "ARMAS BLANCAS: %s", WeaponName); } else { format(string, sizeof(string), "ARMAS BLANCAS: Ninguna"); }
					SendClientMessage(playerid, Amarillo, string);
					if(Pistola > 0) { GetWeaponName(Pistola, WeaponName, 24); format(string, sizeof(string), "PISTOLAS: %s", WeaponName); } else { format(string, sizeof(string), "PISTOLAS: Ninguna"); }
					SendClientMessage(playerid, Amarillo, string);
					if(Shotgun > 0) { GetWeaponName(Shotgun, WeaponName, 24); format(string, sizeof(string), "SHOTGUN: %s", WeaponName); } else { format(string, sizeof(string), "SHOTGUN: Ninguna"); }
					SendClientMessage(playerid, Amarillo, string);
					if(Metraca > 0) { GetWeaponName(Metraca, WeaponName, 24); format(string, sizeof(string), "AMETRALLADORAS: %s", WeaponName); } else { format(string, sizeof(string), "AMETRALLADORAS: Ninguna"); }
					SendClientMessage(playerid, Amarillo, string);
					if(Metraca2 > 0) { GetWeaponName(Metraca2, WeaponName, 24); format(string, sizeof(string), "AMETRALLADORAS PESADAS: %s", WeaponName); } else { format(string, sizeof(string), "AMETRALLADORAS PESADAS: Ninguna"); }
					SendClientMessage(playerid, Amarillo, string);
					format(string, sizeof(string), "* %s ha cacheado a %s en busca de armas.", pName(playerid),pName(giveplayerid));
					if(GetPlayerInterior(playerid) > 0){
					ProxDetector(12.0, playerid, string, Morado,Morado,Morado,Morado,Morado);}
					else{
					ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);}
					return 1;
				}
				else if(strcmp(tmp, "Pertenencias", true) == 0)
				{
    				tmp = strtokex(cmdtext, idx);
    				if(!strlen(tmp))
					{
						SendClientMessage(playerid, Blanco, "USO: /cachear [Armas/Pertenencias] [IdJugador/ParteDelNombre]");
						return 1;
					}
					giveplayerid = strval(tmp);
					if(GetDistanceBetweenPlayers(playerid, giveplayerid) > 5.0 || !IsPlayerConnected(giveplayerid))
					{
					    return 1;
					}
					if(giveplayerid == playerid) { SendClientMessage(playerid, Rojo, "* No puedes cachearte a ti mismo!"); return 1; }
					new text1[50], text2[50], text3[50], text4[50], text5[50];
					if(PlayerInfo[giveplayerid][pSemillas][0] > 0 || PlayerInfo[giveplayerid][pSemillas][1] > 0)
					{
						format(text1, 50, "| Tiene semillas ilegales. (Coca: %d | Marihuana: %d)", PlayerInfo[giveplayerid][pSemillas][0], PlayerInfo[giveplayerid][pSemillas][1]);
					}
					else
					{
						text1 = "| No tiene semillas ilegales.";
					}
					if(PlayerInfo[giveplayerid][pDrogaP][0] > 0 || PlayerInfo[giveplayerid][pDrogaP][1] > 0 || PlayerInfo[giveplayerid][pDrogaP][2] > 0)
					{
						format(text2, 50, "| Tiene drogas preparadas. (Marihuana: %d | Cocaina: %d | Crack: %d)",PlayerInfo[giveplayerid][pDrogaP][0],PlayerInfo[giveplayerid][pDrogaP][1],PlayerInfo[giveplayerid][pDrogaP][2]);
					}
					else
					{
						text2 = "| No tiene drogas preparadas.";
					}
					if(PlayerInfo[giveplayerid][pMaterialTrabajo] > 0 && PlayerInfo[giveplayerid][pJob] == 11)
					{
						format(text3, 50, "| Tiene material robado. (Cantidad: %d)", PlayerInfo[giveplayerid][pMaterialTrabajo]);
					}
					else
					{
						text3 = "| No tiene material robado.";
					}
					if(PlayerInfo[giveplayerid][pDrogaNP][0] > 0 || PlayerInfo[giveplayerid][pDrogaNP][1] > 0)
					{
						format(text4, 50, "| Tiene drogas sin preparar. (Coca: %d | Marihuana: %d)", PlayerInfo[giveplayerid][pDrogaNP][0], PlayerInfo[giveplayerid][pDrogaNP][1]);
					}
					else
					{
						text4 = "| No tiene drogas sin preparar.";
					}
					if(PlayerInfo[giveplayerid][pParafernalia][0] > 0 || PlayerInfo[giveplayerid][pParafernalia][1] > 0)
					{
						format(text5, 50, "| Tiene parafernalia. (Cocaina: %d | Crack: %d)", PlayerInfo[giveplayerid][pParafernalia][0], PlayerInfo[giveplayerid][pParafernalia][1]);
					}
					else
					{
						text5 = "| No tiene drogas sin preparar.";
					}
				   	format(string, sizeof(string), "__________| Pertenencias de %s |__________", pName(giveplayerid));
        			SendClientMessage(playerid, Blanco, string);
		   		   	format(string, sizeof(string), "%s.", text1);
					SendClientMessage(playerid, Gris, string);
					format(string, sizeof(string), "%s.", text2);
					SendClientMessage(playerid, Gris, string);
					format(string, sizeof(string), "%s.", text3);
					SendClientMessage(playerid, Gris, string);
					format(string, sizeof(string), "%s.", text4);
					SendClientMessage(playerid, Gris, string);
					format(string, sizeof(string), "%s.", text5);
					SendClientMessage(playerid, Gris, string);
					format(string, sizeof(string), "* %s ha cacheado a %s en busca de algo ilegal.", pName(playerid),pName(giveplayerid));
					if(GetPlayerInterior(playerid) > 0){
					ProxDetector(12.0, playerid, string, Morado,Morado,Morado,Morado,Morado);}
					else{
					ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);}
					return 1;
				}
				else
				{
					SendClientMessage(playerid, Blanco, "USO: /cachear [Armas/Pertenencias] [IdJugador/ParteDelNombre]");
					return 1;
				}
      		}
      	}
      	return 1;
    }
	if(strcmp(cmd, "/arrestar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	   	{
			if(IsACop(playerid))
			{
				if(PlayerInfo[playerid][pDuty] == 0)
				{
				    SendClientMessage(playerid, Rojo, "* No estás en servicio!");
				    return 1;
				}

		        if(!PlayerToPoint(6.0, playerid,2580.0894,-1325.8868,1047.9634) && !PlayerToPoint(6.0, playerid,267.9482,76.9598,1001.0391))
				{
				    SendClientMessage(playerid, Rojo, "* No estás en las cárceles de la LSPD!");
				    return 1;
				}
				new jailtype;
				if(PlayerToPoint(6.0, playerid,2580.0894,-1325.8868,1047.9634)) jailtype = 1;
				else if(PlayerToPoint(6.0, playerid,267.9482,76.9598,1001.0391)) jailtype = 3;
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /arrestar [Minutos] [IdJugador/ParteDelNombre]");
					return 1;
				}
				new time = strval(tmp);
				if(time < 1 || time > 9999) { SendClientMessage(playerid, Rojo, "* El tiempo debe ser entre 1 y 9999!"); return 1; }
				
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USA: /arrestar [Minutos] [IdJugador/ParteDelNombre]");
					return 1;
				}
				new suspect;
				if(!IsNumeric(tmp))
				suspect = ReturnUser(tmp,suspect);
				else suspect = strval(tmp);
				if(IsPlayerConnected(suspect))
				{
					if(GetDistanceBetweenPlayers(playerid,suspect) < 5)
					{
						format(string, sizeof(string), "* Arrestaste a %s!", pName(suspect));
						SendClientMessage(playerid, Azul, string);
						
						GameTextForPlayer(suspect, "~r~Arrestado", 5000, 5);
						SafeResetPlayerWeaponsAC(suspect);
						
						format(string, sizeof(string), "<< El agente %s ha arrestado a %s. >>", pName(playerid),pName(suspect));
						SendFamilyMessage(PlayerInfo[playerid][pMember], Naranja, string);
						
						if(jailtype == 1) SetPlayerPosEx(suspect,2583.8286,-1325.6830,1047.9634);
						else SetPlayerPosEx(suspect,264.6727,77.6543,1001.0391);
						PlayerInfo[suspect][pJailTime] = time;
						PlayerInfo[suspect][pJailed] = jailtype;
						SaveValues(suspect,"Encarcelado"),
						
						format(string, sizeof(string), "* Te han arrestado por %d minutos. Usa /reloj para ver cuanto queda.", time);
						SendClientMessage(suspect, Azul, string);
					}
				}
				else
				{
				    SendClientMessage(playerid, Rojo, "* No está cerca el sospechoso.");
				    return 1;
				}
			}
			else
			{
			    SendClientMessage(playerid, Naranja, "* Arrestar a alguien sin una placa oficial es contra la ley.");
			    return 1;
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/multa", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
	        if(IsACop(playerid) == 1)
			{
				if(PlayerInfo[playerid][pDuty] == 0)
				{
					SendClientMessage(playerid, Rojo, "* No estás en Servicio!");
					return 1;
				}
	    	
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /multa [IdJugador/ParteDelNombre] [Precio] [Razón]");
					return 1;
				}
				
				if(!IsNumeric(tmp))
				giveplayerid = ReturnUser(tmp,playerid);
				else giveplayerid = strval(tmp);
				
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /multa [IdJugador/ParteDelNombre] [Precio] [Razón]");
					return 1;
				}
				moneys = strval(tmp);
				if(moneys < 1 || moneys > 99999) { SendClientMessage(playerid, Rojo, "* La multa tiene que estar entre 1$ y 99999$!"); return 1; }
			
				if(IsPlayerConnected(giveplayerid))
				{
					if(giveplayerid != INVALID_PLAYER_ID)
					{
						if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 7.0)
						{
							new length = strlen(cmdtext);
							while ((idx < length) && (cmdtext[idx] <= ' '))
							{
								idx++;
							}
							new offset = idx;
							new result[128];
							while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
							{
								result[idx - offset] = cmdtext[idx];
								idx++;
							}
							result[idx - offset] = EOS;
							
							if(!strlen(result))
							{
								SendClientMessage(playerid, Blanco, "USO: /multa [IdJugador/ParteDelNombre] [Precio] [Razón]");
								return 1;
							}
							
							format(string, sizeof(string), "* Entregas a %s una multa de %d$. Razón: %s", pName(giveplayerid), moneys, (result));
							SendClientMessage(playerid, Azul, string);
							format(string, sizeof(string), "* Oficial %s te ha entegado una multa de %d$. Razón: %s", pName(playerid), moneys, (result));
							SendClientMessage(giveplayerid, Azul, string);
							PlayerInfo[giveplayerid][pMultaMoney] += moneys;
							PlayerInfo[giveplayerid][pMultaID] = playerid;
							SafeGivePlayerMoney(giveplayerid, -PlayerInfo[giveplayerid][pMultaMoney]);
							format(string, sizeof(string), "* %s ha pagado tu multa de %d$.", pName(giveplayerid), PlayerInfo[giveplayerid][pMultaMoney]);
							SendClientMessage(playerid, AzulClaro, string);
							PlayerInfo[giveplayerid][pMultaMoney] = 0;
							PlayerInfo[giveplayerid][pMultaID] = NOEXISTE;
							SendClientMessage(giveplayerid, Verde, "* Has pagado la multa.");
							return 1;
						}
						else
						{
							SendClientMessage(playerid, Rojo, "* Debes estar cerca del sujeto!");
							return 1;
						}
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Debes estar cerca del sujeto!");
					return 1;
				}
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/megafono", true) == 0 || strcmp(cmd, "/m", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
			new tmpcar = GetPlayerVehicle(playerid);
			new length = strlen(cmdtext);
			while ((idx < length) && (cmdtext[idx] <= ' '))
			{
				idx++;
			}
			new offset = idx;
			new result[128];
			while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
			{
				result[idx - offset] = cmdtext[idx];
				idx++;
			}
			result[idx - offset] = EOS;
			if(!strlen(result))
			{
				SendClientMessage(playerid, Blanco, "USO: (/m)egafono [Chat Megáfono]");
				return 1;
			}
			if(IsAMedic(playerid))
			{
			    if(CarInfo[tmpcar][cUsos] != 2)
			    {
			        SendClientMessage(playerid, Rojo, "* Este coche no tiene un megáfono instalado!");
			        return 1;
			    }
			    format(string, sizeof(string), "[Paramédico %s:o< %s]", pName(playerid), result);
				printf("(Megafono) %s dice: %s", pName(playerid), result);
			    ProxDetector(50.0, playerid, string,Amarillo,Amarillo,Amarillo,Amarillo,Amarillo);
				return 1;
			}
			if(IsACop(playerid))
			{
				if(CarInfo[tmpcar][cUsos] != 1 && CarInfo[tmpcar][cUsos] != 6)
				{
					SendClientMessage(playerid, Rojo, "* Este coche no tiene un megáfono instalado!");
					return 1;
				}
				format(string, sizeof(string), "[Oficial %s:o< %s]", pName(playerid), result);
				printf("(Megafono) %s dice: %s", pName(playerid), result);
				ProxDetector(50.0, playerid, string,Amarillo,Amarillo,Amarillo,Amarillo,Amarillo);
				return 1;
			}
			else
			{
			    SendClientMessage(playerid, Rojo, "* No sabes utilizar el megáfono.");
				return 1;
			}
		}
		return 1;
	}
	if(strcmp(cmd, "/qpl", true) == 0)
	{
		if (PlayerInfo[playerid][pMember] == 1)
		{
			cmd = strtokex(cmdtext, idx);
			if(!strlen(cmd))
			{
				SendClientMessage(playerid, Blanco, "USO: /qpl [IdJugador/ParteDelNombre] [1/2/3]");
				return 1;
			}
			new tmpidplayer;
			if(!IsNumeric(cmd))
			tmpidplayer = ReturnUser(cmd,playerid);
			else tmpidplayer = strval(cmd);
			
			if (!IsPlayerConnected(tmpidplayer))
			{
				SendClientMessage(playerid, Rojo, "* El jugador no está conectado");
				return 1;
			}

			cmd = strtokex(cmdtext, idx);
			if(!strlen(cmd))
			{
				SendClientMessage(playerid, Blanco, "USO: /qpl [IdJugador/ParteDelNombre] [1/2/3]");
				return 1;
			}
			new tmppuntoslic;
			new mensaje[80];
			
			tmppuntoslic = strval(cmd);
			if (tmppuntoslic < 1 || tmppuntoslic > 3)
			{
				SendClientMessage(playerid, Blanco, "USO: /qpl [IdJugador/ParteDelNombre] [1/2/3]");
				return 1;
			}
			if (tmppuntoslic > PlayerInfo[tmpidplayer][pCarLicPoints])
			{
				SendClientMessage(playerid, RojoIntenso, "* Al jugador no le quedan tantos puntos en su licencia");
				return 1;
			}
			PlayerInfo[tmpidplayer][pCarLicPoints] -= tmppuntoslic;
			SaveValues(tmpidplayer,"Licencias");
			format (mensaje, 80, "Quitaste a %s, %d puntos a su licencia", pName(tmpidplayer), tmppuntoslic);
			SendClientMessage (playerid, AzulClaro, mensaje);
			format (mensaje, 80, "Su licencia queda con %d puntos", PlayerInfo[tmpidplayer][pCarLicPoints]);
			SendClientMessage (playerid, AzulClaro, mensaje);
			format (mensaje, 80, "El agente %s te quitó %d puntos a tu licencia", pName(playerid), tmppuntoslic);
			SendClientMessage (tmpidplayer, AzulClaro, mensaje);
			format (mensaje, 80, "Tu licencia queda con %d puntos", PlayerInfo[tmpidplayer][pCarLicPoints]);
			SendClientMessage (tmpidplayer, AzulClaro, mensaje);
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* No eres policía.");
		}
		return 1;
	}
	if(strcmp(cmd,"/dlicarmas",true)==0)
	{
		if(PlayerInfo[playerid][pMember] == 1 && PlayerInfo[playerid][pRank] >= 5)
		{
			cmd = strtokex(cmdtext,idx);
			if(!strlen(cmd))
			{
				SendClientMessage(playerid,Blanco,"USO: /dlicarmas [IdJugador/ParteDelNombre] [Precio]");
				return 1;
			}
			new id;
			if(!IsNumeric(cmd))
			id = ReturnUser(cmd);
			else id = strval(cmd);
			tmp = strtokex(cmdtext,idx);
            if(!strlen(tmp))
            {
				SendClientMessage(playerid,Blanco,"USO: /dlicarmas [IdJugador/ParteDelNombre] [Precio]");
                return 1;
            }
            moneys = strval(tmp);
            if(moneys < 1 || moneys > 99999) { SendClientMessage(playerid, Rojo, "* Precio invalido"); return 1; }

			if(IsPlayerConnected(id))
			{
				new Ano,Mes,Dia;
				getdate(Ano,Mes,Dia);
				format(string,128,"El oficial %s te entregó la licencia de armas con fecha %02d/%02d/%d. Caduca al mes.",pName(playerid),Mes,Dia,Ano);
				SendClientMessage(id,Verde,string);
				SendClientMessage(playerid,Verde,"Entregaste la licencia correctamente");
				PlayerInfo[id][pGunLic] = 1;
				PlayerInfo[id][pGunLicD] = Dia;
				PlayerInfo[id][pGunLicM] = Mes;
				SaveValues(id, "LArmas");
                SafeGivePlayerMoney(id,-moneys);
			}
			else SendClientMessage(playerid,Rojo,"* Jugador no conectado.");
		}
		return 1;
	}
	if(strcmp(cmd,"/qlicarmas",true)==0)
	{
		if(PlayerInfo[playerid][pMember] == 1 && PlayerInfo[playerid][pRank] >= 2)
		{
			cmd = strtokex(cmdtext,idx);
			if(!strlen(cmd))
			{
				SendClientMessage(playerid,Blanco,"USO: /qlicarmas [IdJugador/ParteDelNombre]");
				return 1;
			}
			new id;
			if(!IsNumeric(cmd))
			id = ReturnUser(cmd);
			else id = strval(cmd);
			if(IsPlayerConnected(id))
			{
				if(PlayerInfo[id][pGunLic]==1)
				{
					format(string,128,"El oficial %s te quitó la licencia de armas");
					SendClientMessage(id,Verde,string);
					SendClientMessage(playerid,Verde,"Quitaste la licencia correctamente");
					PlayerInfo[id][pGunLic] = 0;
					PlayerInfo[id][pGunLicD] = 0;
					PlayerInfo[id][pGunLicM] = 0;
					SaveValues(id, "LArmas");
				}
				else SendClientMessage(playerid,Rojo,"* El jugador no tiene licencia de armas.");
			}
			else SendClientMessage(playerid,Rojo,"* Jugador no conectado.");
		}
		return 1;
	}
	return 0;
}

UnjailPlayerIC(playerid)
{
	if(PlayerInfo[playerid][pJailed] == 1)
	{
		SetPlayerInterior(playerid, 2);
		SetPlayerPosEx(playerid,2579.7332,-1346.0867,1047.9634);
		SetPlayerFacingAngle(playerid,80.3944);
	} 
	else if(PlayerInfo[playerid][pJailed] == 3)
	{
		SetPlayerInterior(playerid, 6);
		SetPlayerPosEx(playerid,246.8680,70.1454,1003.6406);
		SetPlayerFacingAngle(playerid,175.3944);
	}
	SetCameraBehindPlayer(playerid);
	PlayerPlaySound(playerid,1057,0.0,0.0,0.0);
	PlayerInfo[playerid][pJailTime] = 0;
	PlayerInfo[playerid][pJailed] = 0;
	SaveValues(playerid,"Encarcelado");
	return SendClientMessage(playerid, AzulClaro, "* Has cumplido tu condena. Vuelves a ser libre!");
}