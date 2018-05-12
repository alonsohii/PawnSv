#include <globalvars>
#include <a_samp>

new Float:Checkstrigo[4][3] = {
{25.5728,47.9244,2.8795},
{-198.8363,-33.0443,2.8796},
{-146.8839,128.5147,3.3929},
{-3.2884,-48.7394,2.8814}
};

Sis_Cos_OnGameModeInit()
{
	AddStaticPickup(1274,23,-12.4588,47.7954,3.1172);
	CreateDynamic3DTextLabel("Cobertizo de herramientas",Rojo,-12.4588,47.7954,3.6300+0.2,10);
	CreateDynamic3DTextLabel("Utiliza /equipocosecha para comprarlo.",Gris,-12.4588,47.7954,3.6300,10);
	return 1;
}

Sis_Cos_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);

	if (strcmp(cmd,"/cosechar",true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser granjero! ");
			return 1;
		}

		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
		
		if(PlayerInfo[playerid][pEquipoParaTrabajar] == 0)
	    {
			SendClientMessage(playerid,Rojo,"* No tienes las herramientas necesarias, ve al cobertizo de herramientas.");
			return 1;
		}
		
		if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a cosechar.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
		   	SendClientMessage(playerid,Rojo,"* Súbete en un tractor.");
		    return 1;
		}
		if(PlayerInfo[playerid][pListoCobro] == 1)
		{
			SendClientMessage(playerid,Rojo,"* Vende la cosecha primero.");
			return 1;
		}
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 531)
		{
		  	SendClientMessage(playerid,Rojo,"* Súbete en un tractor.");
		  	return 1;
		}
		if(PlayerInfo[playerid][pTrabajando] == 1)
		{
		    SendClientMessage(playerid,Rojo,"((¡Ahora sube en un tractor y usa /recolectar!))");
		    return 1;
		}
		SendClientMessage(playerid,Verde,"* ¡Ya puedes comenzar a cosechar! ((/recolectar)).");
		PlayerInfo[playerid][pTrabajando] = 1;
		PlayerInfo[playerid][pEquipoParaTrabajar] = 0;
		return 1;
	}
	
	if(strcmp(cmd,"/equipocosecha",true)==0)
	{
		if(PlayerInfo[playerid][pJob] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser granjero! ");
			return 1;
		}
	
	    if(!PlayerToPoint(2.0,playerid,-12.4588,47.7954,3.1172))
	    {
	        SendClientMessage(playerid,Rojo,"No estás en el lugar adecuado. Ve al cobertizo de herramientas.");
	        return 1;
		}
	    if(PlayerInfo[playerid][pEquipoParaTrabajar] == 1)
	    {
			SendClientMessage(playerid,Rojo,"* Ya tienes las herramientas necesarias, ve a cosechar.");
			return 1;
		}
		if(SafeGetPlayerMoney(playerid) >= 10)
		{
			SendClientMessage(playerid,Blanco,"Vendedor dice: Aquí tienes tus nuevas herramientas, serán 10$. ¡Suerte con la cosecha!");
			PlayerInfo[playerid][pEquipoParaTrabajar] = 1;
			SafeGivePlayerMoney(playerid, -10);
		}
		else
		{
			SendClientMessage(playerid,Rojo,"* No tienes dinero suficiente.");
		}
		return 1;
	}
	
	if(strcmp(cmd,"/dejarcosechar",true) == 0 )
	{
		if(PlayerInfo[playerid][pJob] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser granjero! ");
			return 1;
		}
	
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
	
	    PlayerInfo[playerid][pListoCobro] = 1;
		SendClientMessage(playerid,Verde,"* Ahora ve a vender la cosecha al mercado (Zona marcada).");
		SetPlayerCheckpoint(playerid,417.9619,-1728.4756,9.1937,10.0);
		PlayerInfo[playerid][pCheckpoint] = 3;
		return 1;
	}
	
	if(strcmp(cmd,"/vendertrigo",true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser granjero! ");
			return 1;
		}
		
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
		
	    if(!PlayerToPoint(10.0,playerid,417.9619,-1728.4756,9.1937))
	    {
	        SendClientMessage(playerid,Rojo,"* ¡No estás en la zona de venta!.");
	        return 1;
		}
		if(PlayerInfo[playerid][pMaterialTrabajo] == 0)
		{
		    SendClientMessage(playerid,Rojo,"* ¡No tienes nada para vender!.");
			return 1;
		}
		new DineroPagado;
		DineroPagado = (PlayerInfo[playerid][pMaterialTrabajo] / 1000 )* 25;
	    PlayerInfo[playerid][pTrabajando] = 0;
		SendClientMessage(playerid,Blanco,"Comprador dice: Gracias por la cosecha, un placer hacer negocios.");
		format(string,sizeof(string),"* Has vendido %d gramos de trigo por %d$",PlayerInfo[playerid][pMaterialTrabajo],DineroPagado);
		SendClientMessage(playerid,Verde,string);
        PlayerInfo[playerid][pGanancias]+=DineroPagado;
        if (PlayerInfo[playerid][pGanancias]>=600) 
        {
            PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1200);
            SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue cosechando dentro de 20 minutos.");
            PlayerInfo[playerid][pGanancias]=0;
            SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
        }
        SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
		PlayerInfo[playerid][pMaterialTrabajo] = 0;
		SaveValues(playerid, "Inventario");
		PlayerInfo[playerid][pEquipoParaTrabajar] = 0;
		PlayerInfo[playerid][pListoCobro] = 0;
		SafeGivePlayerMoney(playerid,DineroPagado);
		return 1;
	}
	
	if(strcmp(cmd,"/trigo",true)==0)
	{
		if(PlayerInfo[playerid][pJob] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser granjero! ");
			return 1;
		}
		
		format(string,sizeof(string),"* Tienes en tu saco %d gramos de trigo",PlayerInfo[playerid][pMaterialTrabajo]);
		SendClientMessage(playerid,Amarillo,string);
		return 1;
	}
	
	if(strcmp(cmd,"/recolectar",true)== 0)
	{
		if(PlayerInfo[playerid][pJob] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser granjero! ");
			return 1;
		}

		if(PlayerInfo[playerid][pTrabajando] != 1)
		{
		    SendClientMessage(playerid,Rojo,"* Utiliza primero /cosechar");
		    return 1;
		}		

		if(PlayerInfo[playerid][pMaterialTrabajo] > 12000)
		{
		    SendClientMessage(playerid,Verde,"* Ve a vender el trigo. (( /dejarcosechar y /vendertrigo ))");
		    return 1;
		}
		
		if(PlayerInfo[playerid][pCheckpoint] == 3)
		{
			SendClientMessage(playerid,Rojo,"* Ya estas recolectando.");
			return 1;
		}

		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
		
		SendClientMessage(playerid,Verde,"* ¡Comienza a recolectar la cosecha!");
		new trigo = random(sizeof(Checkstrigo));
		SetPlayerCheckpoint(playerid,Checkstrigo[trigo][0],Checkstrigo[trigo][1],Checkstrigo[trigo][2],15.0);
		PlayerInfo[playerid][pCheckpoint] = 3;
        PlayerPlaySound(playerid,1137,0.0,0.0,10.0);
		return 1;
	}
	return 0;
}

Sis_Cos_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 3 && PlayerInfo[playerid][pJob] == 2)
	{
		if(PlayerInfo[playerid][pListoCobro] == 1)
		{
			DisablePlayerCheckpoint(playerid);
			PlayerInfo[playerid][pCheckpoint] = 0;
			SendClientMessage(playerid, Amarillo, "* Utiliza /vendertrigo acá para vender el trigo de tu saco.");
			return 1;
		}
		if(PlayerInfo[playerid][pMaterialTrabajo] < 12000)
		{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 531)
			{
				SendClientMessage(playerid,Rojo,"* Súbete en un tractor.");
				return 1;
			}
			PlayerPlaySound(playerid,1137,0.0,0.0,10.0);
			PlayerInfo[playerid][pTrabajandoCP] ++;
			if(PlayerInfo[playerid][pTrabajandoCP] == 4)
			{
				PlayerInfo[playerid][pTrabajandoCP] = 0;
			}
			Granja(playerid);
			DisablePlayerCheckpoint(playerid);
			PlayerInfo[playerid][pCheckpoint] = 0;
			SetPlayerCheckpoint(playerid,Checkstrigo[PlayerInfo[playerid][pTrabajandoCP]][0],Checkstrigo[PlayerInfo[playerid][pTrabajandoCP]][1],Checkstrigo[PlayerInfo[playerid][pTrabajandoCP]][2],15.0);
			PlayerInfo[playerid][pCheckpoint] = 3;
		}
		else
		{
			DisablePlayerCheckpoint(playerid);
			PlayerInfo[playerid][pCheckpoint] = 0;
			SendClientMessage(playerid,Rojo,"* Sacos llenos, no se puede llevar más. ((/dejarcosechar y /vendertrigo en el punto)).");
		}
		return 1;
	}
	return 0;
}

Granja(playerid)
{
 	new pesodetrigo = 500 + random(200);
	if(500 <= pesodetrigo < 565)
	{
		format(string,sizeof(string),"* Has recogido %d gramos de trigo.",pesodetrigo);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += pesodetrigo;
	}
	if(565 <= pesodetrigo < 585)
	{
		format(string,sizeof(string),"* Has recogido trigo en mal estado, será mejor tirarlo.");
		SendClientMessage(playerid,Rojo,string);
	}
	if(585 <= pesodetrigo < 701)
	{
	    format(string,sizeof(string),"* Has recogido %d gramos de trigo.",pesodetrigo);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodetrigo;
	}
	SaveValues(playerid, "Inventario");
	TogglePlayerControllable(playerid,1);
	return 1;
}