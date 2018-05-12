#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <deathac>
/*
new BasuraRuta[MAX_PLAYERS]; // 1 - ESTE .. 2 - OESTE .. 3 - CENTRAL
new RecogiendoBasuraCP[MAX_PLAYERS]; // CP del que esta recogiendo la basura
new RecogiendoBasura[MAX_PLAYERS]; // 0 - No trabajando ... 1 - Trabajando
new DescargarBasura[MAX_PLAYERS]; // 0 - NO .. 1 - SI
new BolsaBasura[MAX_PLAYERS]; // Bolsa de basura para recoger 
new TimerBasura[MAX_PLAYERS]; // Tiempo que tarda en cargar la basura*/

#define GANADOBS 400 // Dinero ganado por completar la ruta
#define TDEBS 900 // Tiempo de espera al completar la ruta (segundos)

Basura_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
//--------------------------------------------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/recogerbasura", true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 5) { SendClientMessage(playerid, Rojo, "* Debes ser basurero!"); return 1; }

		if(PlayerInfo[playerid][pTrabajando] == 1 && PlayerInfo[playerid][pTrabajoVeh] == NOEXISTE)
			{ SendClientMessage(playerid,Rojo,"* Subete a un vehiculo para empezar a recoger basura!"); return 1; }
		if(PlayerInfo[playerid][pTrabajando] == 1 && PlayerInfo[playerid][pTrabajoVeh] >= 0)
			{ SendClientMessage(playerid,Rojo,"* Ya estás trabajando!"); return 1; }
			
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
		
		if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a recoger basura.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }

		if(!IsPlayerInArea(playerid, 2155.3013,2203.1519,-1993.3302,-1962.7897))
	        { SendClientMessage(playerid,Rojo,"* No estás en el lugar adecuado. Ve al lugar de trabajo primero."); return 1; }

		PlayerInfo[playerid][pTrabajando] = 1;
		SendClientMessage(playerid,Verde,"* Súbete en un camion para empezar a recoger basura.");
		return 1;
	}
//--------------------------------------------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/dejarderecoger", true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 5) { SendClientMessage(playerid, Rojo, "* Debes ser basurero!"); return 1; }
		if(PlayerInfo[playerid][pTrabajando] == 0)
	        { SendClientMessage(playerid,Rojo,"* No estás recogiendo basura!."); return 1; }
		if(PlayerInfo[playerid][pTrabajando] == 1 && PlayerInfo[playerid][pTrabajoVeh] == NOEXISTE)
		{
			PlayerInfo[playerid][pTrabajando] = 0;
			PlayerInfo[playerid][pCheckpoint] = 0;
			PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;
			PlayerInfo[playerid][pTrabajandoCP] = 0;
			PlayerInfo[playerid][pListoCobro] = 0;
			{ SendClientMessage(playerid,Amarillo,"* Has cancelado la ruta!"); return 1; }
		}
		DisablePlayerCheckpoint(playerid);
		SendClientMessage(playerid,Verde,"* No has completado tu ruta!");
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
		PlayerInfo[playerid][pListoCobro] = 0;
		PlayerInfo[playerid][pRutaDeTrabajo]=0;
		CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cBroken] = 0;
		CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cStarted] = 0;
		RepairVehicle(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
		RemovePlayerFromVehicle(playerid);
		TogglePlayerControllable(playerid,1);
		//SetVehicleToRespawn(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
		PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;
	}
//--------------------------------------------------------------------------------------------------------------------------------------------------
/*	if(strcmp(cmd,"/debugba",true) == 0 )
	{
		
		PlayerInfo[playerid][pTrabajandoCP] = 16;
		PlayerInfo[playerid][pRutaDeTrabajo] = 1;
		SetPlayerCheckpoint(playerid,2203.1519,-1962.7897,14.0469,8);
	}*/
	return 0;
}

Basura_OnPlayerEnterCheckpoint(playerid)
{	
	if(PlayerInfo[playerid][pJob] == 5 && PlayerInfo[playerid][pCheckpoint] == 5 && PlayerInfo[playerid][pTrabajando] == 1)
	{
		if(!IsPlayerInAnyVehicle(playerid)) return 1;
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 408) return 1;
		if(PlayerInfo[playerid][pRutaDeTrabajo] >= 1)
		{
			if(PlayerInfo[playerid][pRutaDeTrabajo] == 1){PlayerInfo[playerid][pTrabajoTimer]=SetTimerEx("AvanzarRutaEste",5000,0,"d",playerid);}
			if(PlayerInfo[playerid][pRutaDeTrabajo] == 2){PlayerInfo[playerid][pTrabajoTimer]=SetTimerEx("AvanzarRutaOeste",5000,0,"d",playerid);}
			if(PlayerInfo[playerid][pRutaDeTrabajo] == 3){PlayerInfo[playerid][pTrabajoTimer]=SetTimerEx("AvanzarRutaCentral",5000,0,"d",playerid);}
			if(PlayerToPoint(15.0,playerid,2174.5493,-2015.7906,13.5547)){SendClientMessage(playerid,Verde,"* Espera mientras la basura es descargada del camión...");}
			else{SendClientMessage(playerid,Verde,"* Espera mientras la basura es cargada en el camión...");}
		}
		return 1;
	}
	return 0;
}

AsignarRutaBasurero(playerid)
{
	new rand;
	rand = random(3);
	switch (rand)
	{
	case 0:RutaEste(playerid);
	case 1:RutaOeste(playerid);
	case 2:RutaCentral(playerid);
	}
	return 1;
}

RutaEste(playerid)
{
	GameTextForPlayer(playerid, "~g~Ruta de basura empezada!", 4000, 3);
	SendClientMessage(playerid,Verde,"* Se te ha asignado la Ruta Este para recoger. ((Ve a los checkpoints rojos del mapa)).");
	PlayerInfo[playerid][pRutaDeTrabajo] = 1;
	DisablePlayerCheckpoint(playerid);
	SetPlayerCheckpoint(playerid,1107.8578,-1718.5137,13.6505,5.0);
	PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1107.8578,-1718.5137,12.9505,0.0,0.0,0.0,-1,0,playerid,200.0);
	PlayerInfo[playerid][pTrabajandoCP]=1;
	return 1;
}

RutaOeste(playerid)
{
	GameTextForPlayer(playerid, "~g~Ruta de basura empezada!", 4000, 3);
	SendClientMessage(playerid,Verde,"* Se te ha asignado la Ruta Oeste para recoger. ((Ve a los checkpoints rojos del mapa)).");
	PlayerInfo[playerid][pRutaDeTrabajo] = 2;
	DisablePlayerCheckpoint(playerid);
	SetPlayerCheckpoint(playerid,1475.3682,-1115.0139,23.9834,5.0);
	PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1475.3682,-1115.0139,23.3834,0.0,0.0,0.0,-1,0,playerid,200.0);
	PlayerInfo[playerid][pTrabajandoCP]=1;
	return 1;
}

RutaCentral(playerid)
{
	GameTextForPlayer(playerid, "~g~Ruta de basura empezada!", 4000, 3);
	SendClientMessage(playerid,Verde,"* Se te ha asignado la Ruta Central para recoger. ((Ve a los checkpoints rojos del mapa)).");
	PlayerInfo[playerid][pRutaDeTrabajo] = 3;
	DisablePlayerCheckpoint(playerid);
	SetPlayerCheckpoint(playerid,2243.6052,-1147.4938,26.1136,5.0);
	PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2243.6052,-1147.4938,25.4136,0.0,0.0,0.0,-1,0,playerid,200.0);
	PlayerInfo[playerid][pTrabajandoCP]=1;
	return 1;
}

forward AvanzarRutaEste(playerid);
public AvanzarRutaEste(playerid)
{
	if(IsPlayerInCheckpoint(playerid))
	{
	    switch( PlayerInfo[playerid][pTrabajandoCP] )
		{
			case 1:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1201.7690,-1541.6924,13.5624,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1201.7690,-1541.6924,12.9624,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 2:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1201.7690,-1541.6924,13.5624,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1201.7690,-1541.6924,12.9624,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 3:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1202.1768,-1425.8064,13.5421,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1202.1768,-1425.8064,12.9421,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 4:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1253.6000,-1155.6205,23.9307,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1253.6000,-1155.6205,23.3307,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 5:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1156.6423,-1086.2927,26.4127,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1156.6423,-1086.2927,25.8127,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 6:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1047.6532,-1340.3353,13.6544,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1047.6532,-1340.3353,13.0544,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 7:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,977.3534,-1566.2800,13.7126,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,977.3534,-1566.2800,13.1126,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 8:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,923.4439,-1353.9012,13.4859,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,923.4439,-1353.9012,12.8859,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 9:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,797.7970,-1163.7927,23.5942,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,797.7970,-1163.7927,22.9942,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 10:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,618.0401,-1233.2758,18.3410,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,618.0401,-1233.2758,17.7410,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 11:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,682.7430,-1411.8169,13.6745,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,682.7430,-1411.8169,13.0745,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 12:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,735.2877,-1580.7186,14.5057,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,735.2877,-1580.7186,13.9057,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 13:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,490.1631,-1502.1003,20.6285,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,490.1631,-1502.1003,20.0285,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 14:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,426.3580,-1377.0605,28.8370,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,426.3580,-1377.0605,28.2370,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 15:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,330.1013,-1539.0551,33.3086,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,330.1013,-1539.0551,32.7086,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 16:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);SendClientMessage(playerid,Verde,"* Muy bien! El camión esta lleno, ve a descargarlo!");DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2174.5493,-2015.7906,13.5547,5.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 17:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);
						PlayerInfo[playerid][pTrabajandoCP]=0;
						DisablePlayerCheckpoint(playerid);
						GameTextForPlayer(playerid, "~g~ Completado", 4000, 3);
						format(string,sizeof(string),"* Recibes %d$ por completar tu ruta. Vuelve cuando hayas descansado.",GANADOBS);
						SendClientMessage(playerid,Verde,string);
						SafeGivePlayerMoney(playerid,GANADOBS);
						PlayerInfo[playerid][pTrabajando] = 0;
						PlayerInfo[playerid][pCheckpoint] = 0;
						PlayerInfo[playerid][pTrabajandoCP] = 0;
						PlayerInfo[playerid][pListoCobro] = 0;
                        PlayerInfo[playerid][pRutaDeTrabajo]=0;
                        PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+TDEBS);
						CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cBroken] = 0;
						CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cStarted] = 0;
						RepairVehicle(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
						RemovePlayerFromVehicle(playerid);
						TogglePlayerControllable(playerid,1);
						SetVehicleToRespawn(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
						PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;}
		}
   		KillTimer(PlayerInfo[playerid][pTrabajoTimer]);
	}
	else{SendClientMessage(playerid,Naranja,"* Vuelve, ESPERA y recoge la basura!!");}
}

forward AvanzarRutaOeste(playerid);
public AvanzarRutaOeste(playerid)
{
	if(IsPlayerInCheckpoint(playerid))
	{
		switch( PlayerInfo[playerid][pTrabajandoCP] )
		{
		    case 1:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2243.6052,-1147.4938,26.1136,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2243.6052,-1147.4938,25.5136,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 2:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2263.6301,-1345.8998,24.0852,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2263.6301,-1345.8998,23.4852,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 3:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2335.3213,-1442.7767,23.5647,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2335.3213,-1442.7767,22.9647,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 4:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2335.1199,-1714.1067,13.0991,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2335.1199,-1714.1067,12.4991,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 5:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2209.7971,-1798.2283,12.8616,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2209.7971,-1798.2283,12.2616,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 6:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2262.9758,-2070.3972,13.1116,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2262.9758,-2070.3972,12.5116,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 7:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2207.3191,-2146.6968,13.1098,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2207.3191,-2146.6968,12.5098,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 8:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2258.6111,-2235.7844,13.1118,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2258.6111,-2235.7844,12.5118,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 9:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2502.1184,-2178.3245,13.1200,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2502.1184,-2178.3245,12.5200,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 10:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2722.2664,-2082.6255,11.3488,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2722.2664,-2082.6255,10.7488,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 11:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2661.9250,-1926.0072,13.1131,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2661.9250,-1926.0072,12.5131,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 12:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2523.8115,-1816.8976,13.1109,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2523.8115,-1816.8976,12.5109,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 13:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2649.9092,-1677.7217,10.4100,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2649.9092,-1677.7217,9.8100,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 14:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2876.0928,-1508.4207,10.5977,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2876.0928,-1508.4207,9.9977,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 15:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2684.2466,-1462.3999,30.1160,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2684.2466,-1462.3999,29.5160,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 16:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2650.2578,-1295.2212,44.3187,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2650.2578,-1295.2212,43.7187,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 17:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2545.7908,-1176.6836,59.9817,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2545.7908,-1176.6836,59.3817,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 18:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2444.7761,-1305.6400,23.5663,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2444.7761,-1305.6400,22.9663,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 19:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2406.5007,-1437.9500,23.5662,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2406.5007,-1437.9500,22.9662,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 20:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2378.1741,-1198.5760,26.9882,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2378.1741,-1198.5760,26.3882,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 21:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);SendClientMessage(playerid,Verde,"* Muy bien! El camión esta lleno, ve a descargarlo!");DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2174.5493,-2015.7906,13.5547,5.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 22:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);
						PlayerInfo[playerid][pTrabajandoCP]=0;
						DisablePlayerCheckpoint(playerid);
						GameTextForPlayer(playerid, "~g~ Completado", 4000, 3);
						format(string,sizeof(string),"* Recibes %d$ por completar tu ruta. Vuelve cuando hayas descansado.",GANADOBS);
						SendClientMessage(playerid,Verde,string);
						SafeGivePlayerMoney(playerid,GANADOBS);
						PlayerInfo[playerid][pTrabajando] = 0;
						PlayerInfo[playerid][pCheckpoint] = 0;
						PlayerInfo[playerid][pTrabajandoCP] = 0;
						PlayerInfo[playerid][pListoCobro] = 0;
                        PlayerInfo[playerid][pRutaDeTrabajo]=0;
                        PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+TDEBS);
						CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cBroken] = 0;
						CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cStarted] = 0;
						RepairVehicle(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
						RemovePlayerFromVehicle(playerid);
						TogglePlayerControllable(playerid,1);
						SetVehicleToRespawn(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
						PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;}
		}
   		KillTimer(PlayerInfo[playerid][pTrabajoTimer]);
	}
	else{SendClientMessage(playerid,Naranja,"* Vuelve, ESPERA y recoge la basura!!");}
}

forward AvanzarRutaCentral(playerid);
public AvanzarRutaCentral(playerid)
{
	if(IsPlayerInCheckpoint(playerid))
	{
        switch( PlayerInfo[playerid][pTrabajandoCP] )
        {
			case 1:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1475.3682,-1115.0139,23.9834,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1475.3682,-1115.0139,23.3834,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 2:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1708.3788,-1216.6450,19.5828,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1708.3788,-1216.6450,18.9828,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 3:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1448.1213,-1324.9425,13.6543,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1448.1213,-1324.9425,13.0543,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 4:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1581.0676,-1447.4089,13.6460,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1581.0676,-1447.4089,13.0460,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 5:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1651.7465,-1502.0468,13.6614,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1651.7465,-1502.0468,13.0614,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 6:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1450.7030,-1586.0054,13.6640,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1450.7030,-1586.0054,13.0640,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 7:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1382.9901,-1795.0791,13.6515,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1382.9901,-1795.0791,13.0515,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 8:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1546.4917,-1878.7780,13.6506,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1546.4917,-1878.7780,13.0506,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 9:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1589.9557,-1879.1210,13.6431,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1589.9557,-1879.1210,13.0431,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 10:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1767.8123,-1832.5387,13.6595,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1767.8123,-1832.5387,13.0595,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 11:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1858.7130,-1378.5670,13.6542,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1858.7130,-1378.5670,13.0542,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 12:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1874.9042,-1087.1847,23.9390,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1874.9042,-1087.1847,23.3390,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 13:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2012.8085,-1267.5958,24.0814,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2012.8085,-1267.5958,23.40814,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 14:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2104.8745,-1441.7416,24.1031,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2104.8745,-1441.7416,23.5031,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 15:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2074.9041,-1901.3293,13.6542,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2074.9041,-1901.3293,13.0542,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 16:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2008.9431,-1656.8324,13.6487,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,2008.9431,-1656.8324,13.0487,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 17:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1699.0873,-1473.9713,13.7075,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1699.0873,-1473.9713,13.1075,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 18:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);GameTextForPlayer(playerid, "~g~ Conseguido", 4000, 3);DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,1290.7263,-1387.4669,13.5681,5.0);PlayerInfo[playerid][pBolsaBasura]=CreateDynamicObject(1265,1290.7263,-1387.4669,12.9681,0.0,0.0,0.0,-1,0,playerid,200.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 19:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);SendClientMessage(playerid,Verde,"* Muy bien! El camión esta lleno, ve a descargarlo!");DisablePlayerCheckpoint(playerid);SetPlayerCheckpoint(playerid,2174.5493,-2015.7906,13.5547,5.0);PlayerInfo[playerid][pTrabajandoCP]++;}
			case 20:{DestroyDynamicObject(PlayerInfo[playerid][pBolsaBasura]);
						PlayerInfo[playerid][pTrabajandoCP]=0;
						DisablePlayerCheckpoint(playerid);
						GameTextForPlayer(playerid, "~g~ Completado", 4000, 3);
						format(string,sizeof(string),"* Recibes %d$ por completar tu ruta. Vuelve cuando hayas descansado.",GANADOBS);
						SendClientMessage(playerid,Verde,string);
						SafeGivePlayerMoney(playerid,GANADOBS);
						PlayerInfo[playerid][pTrabajando] = 0;
						PlayerInfo[playerid][pCheckpoint] = 0;
						PlayerInfo[playerid][pTrabajandoCP] = 0;
						PlayerInfo[playerid][pListoCobro] = 0;
                        PlayerInfo[playerid][pRutaDeTrabajo]=0;
                        PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+TDEBS);
						CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cBroken] = 0;
						CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cStarted] = 0;
						RepairVehicle(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
						RemovePlayerFromVehicle(playerid);
						TogglePlayerControllable(playerid,1);
						SetVehicleToRespawn(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
						PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;}
		}
   		KillTimer(PlayerInfo[playerid][pTrabajoTimer]);
	}
	else{SendClientMessage(playerid,Naranja,"* Vuelve, ESPERA y recoge la basura!!");}
}

Basura_OnPlayerStateChange(playerid)
{
	new vehicleid = GetPlayerVehicle(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(PlayerInfo[playerid][pJob] == 5 && PlayerInfo[playerid][pTrabajando] == 0)
		{
			if(CarInfo[vehicleid][cUsos] == 105)
			{
				RemovePlayerFromVehicle(playerid);
				TogglePlayerControllable(playerid,1);
				ClearChatbox(playerid,2);
				return SendClientMessage(playerid,Rojo,"* No estás trabajando! Usa primero /recogerbasura.");
			}
		}
		else if(PlayerInfo[playerid][pJob] == 5 && PlayerInfo[playerid][pTrabajando] == 1)
		{
			if(PlayerInfo[playerid][pTrabajoVeh] == -1 && CarInfo[vehicleid][cUsos] == 105)
			{
				PlayerInfo[playerid][pTrabajoVeh] = vehicleid;
				PlayerInfo[playerid][pTrabajando] = 1;
				PlayerInfo[playerid][pCheckpoint] = 5;
				PlayerInfo[playerid][pTrabajandoCP] = 0;
				PlayerInfo[playerid][pListoCobro] = 0;
				return AsignarRutaBasurero(playerid);
			}
			else if(PlayerInfo[playerid][pTrabajoVeh] >= 0)
			{
				if(PlayerInfo[playerid][pTrabajoVeh] != vehicleid && CarInfo[vehicleid][cUsos] == 105)
				{
					RemovePlayerFromVehicle(playerid);
					TogglePlayerControllable(playerid,1);
					ClearChatbox(playerid,2);
					return SendClientMessage(playerid,Rojo,"* Este no es tu vehiculo!. Si quieres cambiar, abandona la ruta primero. (/dejarderecoger)");
				}
			}
		}
	}
	return 1;
}
