#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <deathac>
#include <streamer>

#define MAX_CPSLC 21 // CPS MAX POR RUTA (TIENEN QUE SER EL MISMO NUMERO EN LAS DIFERENTES RUTAS)
#define XTRALC 30 // DINERO EXTRA GANADO X HACER TODOS LOS CPS
#define DINEROXCPLC 10  // DINERO GANADO X CHECKPOINTS TRABAJADOS

new Float:ChecksLimpiaCallesRuta1[21][3] = {
{1964.38, -1764.67, 13.0885},
{1823.9, -1592.18, 13.0617},
{2029.52, -1343.93, 23.5257},
{2073.47, -1107.66, 24.2636},
{1658.03, -1158.95, 23.4583},
{1217.41, -1140.59, 23.2998},
{1004.9, -955.393, 41.4368},
{940.333, -1186.51, 19.0471},
{1058.04, -1452.01, 13.07},
{856.354, -1591.43, 13.0918},
{639.971, -1502.19, 14.4376},
{486.394, -1350.07, 16.9588},
{322.191, -1566.6, 32.8108},
{552.577, -1671.29, 18.2101},
{816.962, -1644.78, 13.0901},
{1270.54, -1574.12, 13.0882},
{1304.64, -1855.4, 13.0881},
{1432.32, -1669.32, 13.0882},
{1526.74, -1670.45, 13.0875},
{1777.65, -1734.26, 13.0879},
{1732.65, -1852.48, 13.1194}
};

new Float:ChecksLimpiaCallesRuta2[21][3] = {
{1964.43, -1767.62, 13.0877},
{2155.64, -1754.3, 13.0947},
{2215.28, -1834.55, 13.9008},
{2297.19, -2069.65, 13.0798},
{2717.11, -2024.72, 13.0256},
{2518.57, -1829.48, 13.0777},
{2645.51, -1681.29, 10.4814},
{2611.04, -1441.45, 32.2996},
{2373.57, -1279.51, 23.5383},
{2246.77, -1137.94, 25.7358},
{2103.84, -1218.74, 23.5088},
{1823.86, -1258.62, 13.1781},
{1452.58, -1331.79, 13.0882},
{1420.97, -1395.09, 13.088},
{1303.77, -1278.29, 13.0882},
{1195.85, -1367.73, 13.0275},
{1147.5, -1627.83, 13.4866},
{1237.95, -1855.09, 13.0882},
{1391.41, -1797.25, 13.0882},
{1649.77, -1594.83, 13.0967},
{1746.96, -1704.31, 13.0882}
};


new Float:ChecksLimpiaCallesRuta3[21][3] = {
{1964.01, -1766.7, 13.0877},
{1818.84, -1781.28, 13.0882},
{1686.8, -1826.84, 13.0877},
{1447.06, -1870.17, 13.0956},
{1079.21, -1849.85, 13.0949},
{920.402, -1687.3, 13.0886},
{919.322, -1344.71, 12.9831},
{1087.42, -1283.57, 13.1337},
{1245.23, -1150.1, 23.282},
{1263.48, -952.624, 40.97},
{1548.01, -966.395, 36.9975},
{2198.8, -1117.81, 24.9207},
{1966.87, -1186.96, 25.5139},
{1845.4, -1387.62, 13.0962},
{1693.89, -1438.55, 13.0881},
{1680.25, -1544.35, 13.0866},
{1686.6, -1693.36, 13.0866},
{1924.87, -1754.71, 13.0863},
{2037.46, -1615.29, 13.0874},
{2014.07, -1810.13, 13.0882},
{1824.48, -1907.55, 13.0729}
};

LimpiaC_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
//----------------------------------------------------------------------------------------------------------------------------	
	if (strcmp(cmd,"/limpiarcalles",true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 4) { SendClientMessage(playerid, Rojo, "* Debes ser limpiador!"); return 1; }

		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
		
		if(PlayerInfo[playerid][pTrabajando] == 1 && PlayerInfo[playerid][pTrabajoVeh] == NOEXISTE)
			{ SendClientMessage(playerid,Rojo,"* Subete a un vehiculo para empezar a limpiar!"); return 1; }
		if(PlayerInfo[playerid][pTrabajando] == 1 && PlayerInfo[playerid][pTrabajoVeh] >= 0)
			{ SendClientMessage(playerid,Rojo,"* Ya estás trabajando!"); return 1; }
		
		if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a limpiar.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }
		if(!IsPlayerInArea(playerid, 1608.5022,1673.2057,-1904.1826,-1877.8646))
	        { SendClientMessage(playerid,Rojo,"* No estás en el lugar adecuado. Ve al lugar de trabajo primero."); return 1; }


		PlayerInfo[playerid][pTrabajando] = 1;
		SendClientMessage(playerid,Verde,"* Súbete en un limpia calles para empezar a limpiar.");
		return 1;
	}
//----------------------------------------------------------------------------------------------------------------------------	
	if(strcmp(cmd,"/dejardelimpiar",true) == 0 )
	{
		if(PlayerInfo[playerid][pJob] != 4) { SendClientMessage(playerid, Rojo, "* Debes ser limpiador!"); return 1; }
		if(PlayerInfo[playerid][pTrabajando] == 0)
	        { SendClientMessage(playerid,Rojo,"* No estás limpiando las calles!."); return 1; }
		if(PlayerInfo[playerid][pTrabajando] == 1 && PlayerInfo[playerid][pTrabajoVeh] == NOEXISTE)
		{
			PlayerInfo[playerid][pTrabajando] = 0;
			PlayerInfo[playerid][pCheckpoint] = 0;
			PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;
			PlayerInfo[playerid][pTrabajandoCP] = 0;
			PlayerInfo[playerid][pListoCobro] = 0;
			SendClientMessage(playerid,Amarillo,"* Has cancelado la ruta!");
			return 1;
		}
		if(PlayerInfo[playerid][pTrabajandoCP] == MAX_CPSLC)
		{
			format(string,sizeof(string),"* Pero si ya has completado tu ruta! (%d/%d). Ve al lugar de trabajo para cobrar!",PlayerInfo[playerid][pTrabajandoCP],MAX_CPSLC);
			SendClientMessage(playerid,Verde,string);
			return 1;
		}
		DisablePlayerCheckpoint(playerid);
		PlayerInfo[playerid][pTrabajandoCP]--;
		format(string,sizeof(string),"* No has completado tu ruta! (%d/%d). Ve al lugar de trabajo para cobrar!",PlayerInfo[playerid][pTrabajandoCP],MAX_CPSLC);
		SendClientMessage(playerid,Verde,string);
		PlayerInfo[playerid][pListoCobro] = 1;
		SetPlayerCheckpoint(playerid,1644.8088,-1895.0712,13.5534,4);
		return 1;
	}
//----------------------------------------------------------------------------------------------------------------------------

// DEBUG CMDS	
/*	if(strcmp(cmd,"/debuglc",true) == 0 )
	{
		SetPlayerPos(playerid,1644.8088,-1895.0712,13.5534);
		PlayerInfo[playerid][TiempoEsperaTrabajo] = 0;
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pJob] = 4;
		PlayerInfo[playerid][pRutaDeTrabajo] = 0;
		PlayerInfo[playerid][pMaterialTrabajo] = 0;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
	}
	if(strcmp(cmd,"/debugcps",true) == 0 )
	{
		SetPlayerPos(playerid,1920.6045,-1793.0393,13.1080);
		PlayerInfo[playerid][pJob] = 4;
		PlayerInfo[playerid][TiempoEsperaTrabajo] = 0;
		PlayerInfo[playerid][pTrabajando] = 1;
		PlayerInfo[playerid][pMaterialTrabajo] = 1;
		EmpezarRutaLimpieza(playerid);
	}
	if(strcmp(cmd,"/checkrand",true) == 0 )
	{	
		EmpezarRutaLimpieza(playerid);
	}*/
	return 0;
}

LimpiaC_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pJob] == 4 && PlayerInfo[playerid][pCheckpoint] == 4 && PlayerInfo[playerid][pTrabajando] == 1 && (GetPlayerVehicle(playerid) == PlayerInfo[playerid][pTrabajoVeh]))
	{
		if(PlayerInfo[playerid][pListoCobro] == 1)
		{
			DisablePlayerCheckpoint(playerid);
			CobrarPorLimpiar(playerid);
			return 1;
		}
		if(PlayerInfo[playerid][pMaterialTrabajo] == 0)
		{
			GameTextForPlayer(playerid,"CARGANDO AGUA...", 10000, 3);
			PlayerInfo[playerid][pTempFrozen] = 1;
			TogglePlayerControllable(playerid,0);
			SetTimerEx("EmpezarRutaLimpieza",10000,0,"d",playerid);
			DisablePlayerCheckpoint(playerid);
		}
		else if(PlayerInfo[playerid][pMaterialTrabajo] == 1)
		{
			if(PlayerInfo[playerid][pTrabajandoCP] == MAX_CPSLC)
			{
				DisablePlayerCheckpoint(playerid);
				PlayerInfo[playerid][pListoCobro] = 1;
				format(string,sizeof(string),"* Has completado tu ruta! (%d/%d). Ve al lugar de trabajo para cobrar!",PlayerInfo[playerid][pTrabajandoCP],MAX_CPSLC);
				SendClientMessage(playerid,Verde,string);
				SetPlayerCheckpoint(playerid,1644.8088,-1895.0712,13.5534,4);
			}
			else if(PlayerInfo[playerid][pTrabajandoCP] > 0)
			{
				DisablePlayerCheckpoint(playerid);
				SiguienteCPLimpiaCalles(playerid);
			}
		}
		return 1;
	}
	return 0;
}

SiguienteCPLimpiaCalles(playerid)
{
	PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
	new ActualLCCp = PlayerInfo[playerid][pTrabajandoCP];
	PlayerInfo[playerid][pTrabajandoCP]++;
	if(PlayerInfo[playerid][pRutaDeTrabajo] == 1)
	{
		SetPlayerCheckpoint(playerid,ChecksLimpiaCallesRuta1[ActualLCCp][0],ChecksLimpiaCallesRuta1[ActualLCCp][1],ChecksLimpiaCallesRuta1[ActualLCCp][2],3);
	}
	else if(PlayerInfo[playerid][pRutaDeTrabajo] == 2)
	{
		SetPlayerCheckpoint(playerid,ChecksLimpiaCallesRuta2[ActualLCCp][0],ChecksLimpiaCallesRuta2[ActualLCCp][1],ChecksLimpiaCallesRuta2[ActualLCCp][2],3);
	}
	else if(PlayerInfo[playerid][pRutaDeTrabajo] == 3)
	{
		SetPlayerCheckpoint(playerid,ChecksLimpiaCallesRuta3[ActualLCCp][0],ChecksLimpiaCallesRuta3[ActualLCCp][1],ChecksLimpiaCallesRuta3[ActualLCCp][2],3);
	}
	return 1;
}

forward EmpezarRutaLimpieza(playerid);
public EmpezarRutaLimpieza(playerid)
{
	PlayerInfo[playerid][pTempFrozen] = 0;
	PlayerInfo[playerid][pMaterialTrabajo] = 1;
	GameTextForPlayer(playerid,"LISTO!", 1500, 3);
	TogglePlayerControllable(playerid,1);
	new rand;
	rand = random(3);
	switch (rand)
	{
	case 0:EmpezarRutaLimpieza1(playerid);
	case 1:EmpezarRutaLimpieza2(playerid);
	case 2:EmpezarRutaLimpieza3(playerid);
	}
	return 1;
}

EmpezarRutaLimpieza1(playerid)
{
	PlayerInfo[playerid][pRutaDeTrabajo] = 1;
	SetPlayerCheckpoint(playerid,ChecksLimpiaCallesRuta1[0][0],ChecksLimpiaCallesRuta1[0][1],ChecksLimpiaCallesRuta1[0][2],3);
	PlayerInfo[playerid][pTrabajandoCP] = 1;
	SendClientMessage(playerid,Verde,"* Tu ruta ha comenzado. Ve pasando por los checkpoints para ir limpiando las calles.");
//	SendClientMessage(playerid,Rojo,"DEBUG: Ruta 1!.");
	return 1;
}

EmpezarRutaLimpieza2(playerid)
{
	PlayerInfo[playerid][pRutaDeTrabajo] = 2;
	SetPlayerCheckpoint(playerid,ChecksLimpiaCallesRuta2[0][0],ChecksLimpiaCallesRuta2[0][1],ChecksLimpiaCallesRuta2[0][2],3);
	PlayerInfo[playerid][pTrabajandoCP] = 1;
	SendClientMessage(playerid,Verde,"* Tu ruta ha comenzado. Ve pasando por los checkpoints para ir limpiando las calles.");
//	SendClientMessage(playerid,Rojo,"DEBUG: Ruta 2!.");
	return 1;
}

EmpezarRutaLimpieza3(playerid)
{
	PlayerInfo[playerid][pRutaDeTrabajo] = 3;
	SetPlayerCheckpoint(playerid,ChecksLimpiaCallesRuta3[0][0],ChecksLimpiaCallesRuta3[0][1],ChecksLimpiaCallesRuta3[0][2],3);
	PlayerInfo[playerid][pTrabajandoCP] = 1;
	SendClientMessage(playerid,Verde,"* Tu ruta ha comenzado. Ve pasando por los checkpoints para ir limpiando las calles.");
//	SendClientMessage(playerid,Rojo,"DEBUG: Ruta 3!.");
	return 1;
}

CobrarPorLimpiar(playerid)
{
	if(PlayerInfo[playerid][pMaterialTrabajo] == 0)
	{
		TogglePlayerControllable(playerid,0);
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pRutaDeTrabajo] = 0;
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
		PlayerInfo[playerid][pMaterialTrabajo] = 0;
		PlayerInfo[playerid][pListoCobro] = 0;
		SetTimerEx("SalirDelLimpiaCalles",1000,0,"d",playerid);
		return SendClientMessage(playerid,Verde,"* No has ido ni a recargar el limpia calles de agua!. ¿Acaso quieres perder el trabajo?");		
	}
	else
	{
		TogglePlayerControllable(playerid,0);
		new DineroGanado = PlayerInfo[playerid][pTrabajandoCP]*DINEROXCPLC+XTRALC;
		SafeGivePlayerMoney(playerid,DineroGanado);
        PlayerInfo[playerid][pGanancias]+=DineroGanado;
		format(string,sizeof(string),"* Has cobrado %d$ por tu trabajo. (%d/%d)",DineroGanado,PlayerInfo[playerid][pTrabajandoCP],MAX_CPSLC);
		SendClientMessage(playerid,Verde,string);
		if (PlayerInfo[playerid][pGanancias]>=400)
		{
			PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1200);
			SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue limpiando dentro de 20 minutos.");
            PlayerInfo[playerid][pGanancias]=0;
            SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
        }
        SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
		SetTimerEx("SalirDelLimpiaCalles",1000,0,"d",playerid);
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pRutaDeTrabajo] = 0;
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
		PlayerInfo[playerid][pMaterialTrabajo] = 0;
		PlayerInfo[playerid][pListoCobro] = 0;
		return 1;
	}
}

forward SalirDelLimpiaCalles(playerid);
public SalirDelLimpiaCalles(playerid)
{
	CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cBroken] = 0;
	CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cStarted] = 0;
	RepairVehicle(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
	RemovePlayerFromVehicle(playerid);
	TogglePlayerControllable(playerid,1);
	SetVehicleToRespawn(CarInfo[PlayerInfo[playerid][pTrabajoVeh]][cId]);
	return PlayerInfo[playerid][pTrabajoVeh] = NOEXISTE;
}

LimpiaC_OnPlayerStateChange(playerid)
{
	new vehicleid = GetPlayerVehicle(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(PlayerInfo[playerid][pJob] == 4 && PlayerInfo[playerid][pTrabajando] == 0)
		{
			if(CarInfo[vehicleid][cUsos] == 104)
			{
				RemovePlayerFromVehicle(playerid);
				TogglePlayerControllable(playerid,1);
				ClearChatbox(playerid,2);
				return SendClientMessage(playerid,Rojo,"* No estás trabajando! Usa primero /limpiarcalles.");
			}
		}
		else if(PlayerInfo[playerid][pJob] == 4 && PlayerInfo[playerid][pTrabajando] == 1)
		{
			if(PlayerInfo[playerid][pTrabajoVeh] == -1 && CarInfo[vehicleid][cUsos] == 104)
			{
				PlayerInfo[playerid][pTrabajoVeh] = vehicleid;
				SendClientMessage(playerid,Verde,"* Ve a llenar el limpia calles de agua antes de limpiar! ((Checkpoint rojo en el mapa)).");
				PlayerInfo[playerid][pRutaDeTrabajo] = 0;
				PlayerInfo[playerid][pCheckpoint] = 4;
				PlayerInfo[playerid][pTrabajandoCP] = 0;
				PlayerInfo[playerid][pMaterialTrabajo] = 0;
				PlayerInfo[playerid][pListoCobro] = 0;
				return SetPlayerCheckpoint(playerid, 1918.2383,-1791.0295,13.1088, 3.0);
			}
			else if(PlayerInfo[playerid][pTrabajoVeh] >= 0)
			{
				if(PlayerInfo[playerid][pTrabajoVeh] != vehicleid && CarInfo[vehicleid][cUsos] == 104)
				{
					RemovePlayerFromVehicle(playerid);
					TogglePlayerControllable(playerid,1);
					ClearChatbox(playerid,2);
					return SendClientMessage(playerid,Rojo,"* Este no es tu vehiculo!. Si quieres cambiar, abandona la ruta primero. (/dejardelimpiar)");
				}
			}
		}
	}
	return 1;
}