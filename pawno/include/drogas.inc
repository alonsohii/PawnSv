#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>
#include <horas>

#define MAX_PLANTACIONES 900
enum plantaInfo
{
	plSQLID,
	plTipo, 
	Float:plX,
	Float:plY,
	Float:plZ,
	plTiempo,
	plPlantador[24],
	plEstado,
	Text3D:plProgreso,
	plObjeto,
	plVw,
	plInt,
}
new plantadas[MAX_PLAYERS];
new Plantaciones[MAX_PLANTACIONES][plantaInfo];

/*new EntrePlantaciones;

forward ResetTimer();
public ResetTimer()
{
	EntrePlantaciones = 0;
}*/

forward LoadPlantas();
public LoadPlantas()
{
	new sql[80], row[512], count, estado, TotalPlantas;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM plantaciones");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	count = strval(row);
	
	for (new idx=1; idx<=count; idx++)
	{
		format(sql, sizeof(sql), "SELECT * FROM plantaciones WHERE id=%d LIMIT 1", idx);
	    mysql_query(sql);
	    mysql_store_result();
     	mysql_fetch_row(row);
		split(row, arrCoords, '|');
		estado = strval(arrCoords[9]);
		if(estado != 0)
		{
			TotalPlantas++;
			Plantaciones[idx][plSQLID] = strval(arrCoords[0]);
			Plantaciones[idx][plTipo] = strval(arrCoords[1]);
			Plantaciones[idx][plX] = floatstr(arrCoords[2]);
			Plantaciones[idx][plY] = floatstr(arrCoords[3]);
			Plantaciones[idx][plZ] = floatstr(arrCoords[4]);
			Plantaciones[idx][plVw] = strval(arrCoords[5]);
			Plantaciones[idx][plInt] = strval(arrCoords[6]);
			Plantaciones[idx][plTiempo] = strval(arrCoords[7]);
			format(Plantaciones[idx][plPlantador], 24, "%s", arrCoords[8]);
			Plantaciones[idx][plEstado] = strval(arrCoords[9]);
			
			if(Plantaciones[idx][plEstado] == 1)
			{
				new porcentaje;
				porcentaje = (Plantaciones[idx][plTiempo] * 100) / 29;
				format(string, 128, "Plantación [%d%%]", porcentaje);
			}
			else if(Plantaciones[idx][plEstado] == 2)
			{
				if(Plantaciones[idx][plTipo] == 0)
				{
					Plantaciones[idx][plObjeto] = CreateDynamicObject(2244, Plantaciones[idx][plX], Plantaciones[idx][plY], Plantaciones[idx][plZ] - 1, 0, 0, 0, Plantaciones[idx][plVw], Plantaciones[idx][plInt]);
				}
				else
				{
					Plantaciones[idx][plObjeto] = CreateDynamicObject(2001, Plantaciones[idx][plX], Plantaciones[idx][plY], Plantaciones[idx][plZ] - 1, 0, 0, 0, Plantaciones[idx][plVw], Plantaciones[idx][plInt]);
				}
				format(string, 128, "Plantación [100%%]");
			}
			Plantaciones[idx][plProgreso] = CreateDynamic3DTextLabel(string, Verde, Plantaciones[idx][plX], Plantaciones[idx][plY], Plantaciones[idx][plZ], 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Plantaciones[idx][plVw], Plantaciones[idx][plInt]);
		}
	}
	mysql_free_result();
	printf("Plantaciones cargadas: %d (MAX: %d)", TotalPlantas, MAX_PLANTACIONES);
	return 1;
}

forward SavePlanta(idx);
public SavePlanta(idx)
{
	format(string, 128, "UPDATE plantaciones SET tiempo=%d,estado=%d WHERE id=%d",
	Plantaciones[idx][plTiempo],
	Plantaciones[idx][plEstado],
	Plantaciones[idx][plSQLID]);
	mysql_query(string);
	return 1;
}

Drogas_OnPlayerCommandText(playerid, cmdtext[])
{
	new tmp[128], cmd[128], idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/plantaciones", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] == 0 && PlayerInfo[playerid][pRank] != 6) { SendClientMessage(playerid, Rojo, "* No tienes los permisos suficientes."); return 1; }
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /plantaciones [Ver/Eliminar]");
			return 1;
		}
		
		if(strcmp(tmp, "Ver", true) == 0)
		{
			for(new i; i < MAX_PLANTACIONES; i++)
			{
				if(Plantaciones[i][plEstado] == 0) { continue; }
				if(PlayerToPoint(5.0, playerid, Plantaciones[i][plX], Plantaciones[i][plY], Plantaciones[i][plZ]))
				{
					format(string, 128, "* Plantador: %s", Plantaciones[i][plPlantador]);
					SendClientMessage(playerid, Amarillo, string);
					break;
				}
			}
		}
		else if(strcmp(tmp, "Eliminar", true) == 0)
		{
			for(new i; i < MAX_PLANTACIONES; i++)
			{
				if(Plantaciones[i][plEstado] == 0) { continue; }
				if(PlayerToPoint(5.0, playerid, Plantaciones[i][plX], Plantaciones[i][plY], Plantaciones[i][plZ]))
				{
					Plantaciones[i][plEstado] = 0;
					DestroyDynamic3DTextLabel(Plantaciones[i][plProgreso]);
					DestroyDynamicObject(Plantaciones[i][plObjeto]);
					SendClientMessage(playerid, Gris, "* Plantación eliminada.");
					break;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, Blanco, "USO: /plantaciones [Ver/Eliminar]");
		}
		return 1;
	}
	
	if(strcmp(cmd, "/consumir", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /consumir [Crack/Cocaina/Marihuana]");
			return 1;
		}
		
		if(strcmp(tmp, "Crack", true) == 0)
		{
			if(PlayerInfo[playerid][pDrogaP][2] == 0) { SendClientMessage(playerid, Rojo, "* No tienes crack."); return 1; }
			PlayerInfo[playerid][pDrogaP][2] -= 1;
			PlayerInfo[playerid][pConsumos][2] ++;
			PlayerInfo[playerid][pTmpConsumos][2] ++;
			format(string,sizeof(string),"* Has consumido 1 gramo de crack. (%d/15)", PlayerInfo[playerid][pConsumos][2]);
			SendClientMessage(playerid, Amarillo, string);
			SetTimerEx("ResetConsumos", 1200000, 0, "i", playerid);
			ApplyAnimation(playerid,"CRACK","crckidle1",4.1,1,1,1,1,1);
			TogglePlayerControllable(playerid, 0);
			SetTimerEx("Descongelar", 120000 , 0, "i", playerid);
			Consumo(playerid, 1);
			if(PlayerInfo[playerid][pAbstinencia] == 2)
			{
				PlayerInfo[playerid][pAbstinencia] = 1;
				SaveValue(playerid, "Abstinencia", PlayerInfo[playerid][pAbstinencia]);
			}
			if(PlayerInfo[playerid][pConsumos][2] == 15)
			{
				PlayerInfo[playerid][pRespeto] += 1;
				ComprobarNivel(playerid);
				PlayerInfo[playerid][pConsumos][2] = 0;
			}
			else if(PlayerInfo[playerid][pConsumos][2] == 10 && PlayerInfo[playerid][pAbstinencia] == 0)
			{
				PlayerInfo[playerid][pAbstinencia] = 2;
				SendClientMessage(playerid, Naranja, "Ahora estás enganchado al crack, consume un gramo cada hora para no sufrir sus efectos.");
				SaveValue(playerid, "Abstinencia", PlayerInfo[playerid][pAbstinencia]);
			}
			if(PlayerInfo[playerid][pTmpConsumos][2] == 5)
			{
				SendClientMessage(playerid, Rojo, "* Si sigues consumiendo podrás enfermar e incluso morir. Espera 20 minutos para no correr riesgos.");
			}
			else if(PlayerInfo[playerid][pTmpConsumos][2] > 5)
			{
				new probabilidad = random(100);
				if(probabilidad > 49)
				{
					SendClientMessage(playerid, Rojo, "* Si sigues consumiendo podrás desmayarte. Espera 20 minutos para no correr riesgos.");
				}
				else if(probabilidad < 50)
				{
					GM_SetPlayerHealth(playerid, 0);
					SendClientMessage(playerid, Rojo, "* Te has desmayado por sobredosis. (-1Exp)");
					PlayerInfo[playerid][pRespeto] -= 2;
					ComprobarNivel(playerid);
				}
			}
		}
		else if(strcmp(tmp, "Cocaina", true) == 0)
		{
			if(PlayerInfo[playerid][pDrogaP][1] == 0) { SendClientMessage(playerid, Rojo, "* No tienes cocaína."); return 1; }
			PlayerInfo[playerid][pDrogaP][1] -= 1;
			PlayerInfo[playerid][pConsumos][1] ++;
			PlayerInfo[playerid][pTmpConsumos][1] ++;
			format(string,sizeof(string),"* Has consumido 1 gramo de cocaina. (%d/10)", PlayerInfo[playerid][pConsumos][1]);
			SendClientMessage(playerid, Amarillo, string);
			SetTimerEx("ResetConsumos", 1200000, 0, "i", playerid);
			Consumo(playerid, 2);
			if(PlayerInfo[playerid][pConsumos][1] == 10)
			{
				PlayerInfo[playerid][pRespeto] += 1;
				ComprobarNivel(playerid);
				PlayerInfo[playerid][pConsumos][1] = 0;
			}
			if(PlayerInfo[playerid][pTmpConsumos][1] == 5)
			{
				SendClientMessage(playerid, Rojo, "* Si sigues consumiendo podrás enfermar e incluso morir. Espera 20 minutos para no correr riesgos.");
			}
			else if(PlayerInfo[playerid][pTmpConsumos][1] > 5)
			{
				new probabilidad = random(100);
				if(probabilidad > 49)
				{
					SendClientMessage(playerid, Rojo, "* Si sigues consumiendo podrás enfermar e incluso desmayarte. Espera 20 minutos para no correr riesgos.");
				}
				else if(probabilidad < 50)
				{
					GM_SetPlayerHealth(playerid, 0);
					SendClientMessage(playerid, Rojo, "* Te has desmayado por sobredosis. (-1Exp)");
					PlayerInfo[playerid][pRespeto] -= 2;
					ComprobarNivel(playerid);
				}
			}
		}
		else if(strcmp(tmp, "Marihuana", true) == 0)
		{
			if(PlayerInfo[playerid][pDrogaP][0] == 0) { SendClientMessage(playerid, Rojo, "* No tienes marihuana."); return 1; }
			if(PlayerInfo[playerid][pEncendedor] == 0) { SendClientMessage(playerid, Rojo, "* No tienes mechero."); return 1; }
			PlayerInfo[playerid][pEncendedor]--;
			ApplyAnimation(playerid,"SMOKING","M_smk_in",4.0,0,1,1,1,1,1);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
			PlayerInfo[playerid][pDrogaP][0] -= 1;
			PlayerInfo[playerid][pConsumos][0] ++;
			PlayerInfo[playerid][pTmpConsumos][0] ++;
			format(string,sizeof(string),"* Has consumido 1 gramo de marihuana. (%d/30)", PlayerInfo[playerid][pConsumos][0]);
			SendClientMessage(playerid, Amarillo, string);
			SetTimerEx("ResetConsumos", 1200000, 0, "i", playerid);
			Consumo(playerid, 3);
			if(PlayerInfo[playerid][pConsumos][0] == 30)
			{
				ComprobarNivel(playerid);
				PlayerInfo[playerid][pConsumos][0] = 0;
			}
			if(PlayerInfo[playerid][pTmpConsumos][0] == 5)
			{
				SendClientMessage(playerid, Rojo, "* Si sigues consumiendo podrás enfermar e incluso morir. Espera 20 minutos para no correr riesgos.");
			}
			else if(PlayerInfo[playerid][pTmpConsumos][0] > 5)
			{
				new probabilidad = random(100);
				if(probabilidad > 49)
				{
					SendClientMessage(playerid, Rojo, "* Si sigues consumiendo podrás enfermar e incluso desmayarte. Espera 20 minutos para no correr riesgos.");
				}
				else if(probabilidad < 50)
				{
					GM_SetPlayerHealth(playerid, 0);
					SendClientMessage(playerid, Rojo, "* Te has desmayado por sobredosis. (-1Exp)");
					PlayerInfo[playerid][pRespeto] -= 2;
					ComprobarNivel(playerid);
				}
			}
		}
		else
		{
			SendClientMessage(playerid, Blanco, "USO: /consumir [Crack/Cocaina/Marihuana]");
		}
		SaveValues(playerid, "Inventario");
		SaveValues(playerid, "Preparada");
		SaveValues(playerid, "Consumos");
		SaveValues(playerid, "TmpConsumos");
		return 1;
	}
	
	if(strcmp(cmd, "/preparar", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /preparar [Crack/Cocaina/Marihuana]");
			return 1;
		}
		
		if(strcmp(tmp, "Crack", true) == 0)
		{
			if(PlayerInfo[playerid][pParafernalia][1] == 0 || PlayerInfo[playerid][pDrogaNP][1] == 0) { SendClientMessage(playerid, Rojo, "* No tienes suficiente parafernalia o droga sin preparar.");	return 1; }	
			PlayerInfo[playerid][pDrogaP][2] += 4;
			PlayerInfo[playerid][pDrogaNP][1]--;
			SendClientMessage(playerid, Verde, "* Has preparado 4 gramos de crack.");
		}
		else if(strcmp(tmp, "Cocaina", true) == 0)
		{
			if(PlayerInfo[playerid][pParafernalia][0] == 0 || PlayerInfo[playerid][pDrogaNP][1] == 0) { SendClientMessage(playerid, Rojo, "* No tienes suficiente parafernalia o droga sin preparar.");	return 1; }		
			PlayerInfo[playerid][pDrogaP][1] += 2;
			PlayerInfo[playerid][pDrogaNP][1]--;
			SendClientMessage(playerid, Verde, "* Has preparado 2 gramos de cocaína.");
		}
		else if(strcmp(tmp, "Marihuana", true) == 0)
		{
			if(PlayerInfo[playerid][pDrogaNP][0] == 0) { SendClientMessage(playerid, Rojo, "* No tienes suficiente marihuana."); return 1; }			
			PlayerInfo[playerid][pDrogaP][0] += 2;
			PlayerInfo[playerid][pDrogaNP][0]--;
			SendClientMessage(playerid, Verde, "* Has preparado 2 gramos de marihuana.");
		}
		SaveValues(playerid, "Preparada");
		SaveValues(playerid, "NoPreparada");
		return 1;
	}
	
	if(strcmp(cmd, "/inventario", true) == 0)
	{
		MostrarInventario(playerid,playerid);
		return 1;
  	}
	
	if(strcmp(cmd, "/plantar", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /plantar [Coca/Marihuana]");
			return 1;
		}
		
		if(GetPlayerInterior(playerid) > 0)
		{
			SendClientMessage(playerid, Rojo, "* No está permitido plantar en interiores.");
			return 1;
		}
		
		new Float:X, Float:Y, Float:Z; 
		
		if(strcmp(tmp, "Coca", true) == 0)
		{	
			if(PlayerInfo[playerid][pSemillas][1] < 1) { SendClientMessage(playerid, Rojo, "* No tienes lo necesario."); return 1; }
			if(PlayerInfo[playerid][pMember] > 20 && PlayerInfo[playerid][pMember] < 31)
			{
				GetPlayerPos(playerid, X,Y,Z);
				AgregarPlantacion(1, playerid, X,Y,Z, 0);
				PlayerInfo[playerid][pSemillas][1] --;
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No sabes plantar esto.");
			}
		}
		else if(strcmp(tmp, "Marihuana", true) == 0)
		{
			for(new plant = 0; plant < MAX_PLANTACIONES; plant++)
			{
				if(Plantaciones[plant][plEstado] == 0) continue;
				{
					if(strcmp(Plantaciones[plant][plPlantador], pName(playerid),true) == 0)
					{
						plantadas[playerid]++;
					}
				}
			}
			if((plantadas[playerid] < 2 && PlayerInfo[playerid][pMember] < 10) ||10 < PlayerInfo[playerid][pMember] < 31)
			{
				if(PlayerInfo[playerid][pSemillas][0] < 1) { SendClientMessage(playerid, Rojo, "* No tienes lo necesario."); return 1; }
				if(GetPlayerLevel(playerid) >= 3 || 11 < PlayerInfo[playerid][pMember] < 21)
				{
					if(PlayerInfo[playerid][pMember] == 0 || 10 < PlayerInfo[playerid][pMember] < 31)
					{
						GetPlayerPos(playerid, X,Y,Z);
						AgregarPlantacion(0, playerid, X,Y,Z, 0);
						PlayerInfo[playerid][pSemillas][0] --;
						plantadas[playerid] = 0;
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* No tienes suficiente nivel.");
				}
			}
			else
			{
				SendClientMessage(playerid, Blanco, "No puedes plantar más de 2 plantas");
				return 1;
			}
		}
		SaveValues(playerid, "Semillas");
		return 1;
	}
	return 0;
}

forward AgregarPlantacion(tipo, playerid, Float:X, Float:Y, Float:Z, tiempo);
public AgregarPlantacion(tipo, playerid, Float:X, Float:Y, Float:Z, tiempo)
{
	for(new i; i < MAX_PLANTACIONES; i++)
	{
		new Txtmsg[64];
		if(Plantaciones[i][plEstado] == 1) { continue; }
		Plantaciones[i][plEstado] = 1;
		Plantaciones[i][plTipo] = tipo;
		Plantaciones[i][plX] = X;
		Plantaciones[i][plY] = Y;
		Plantaciones[i][plZ] = Z;
		Plantaciones[i][plTiempo] = tiempo;
		format(Plantaciones[i][plPlantador], 24, "%s", pName(playerid));
		format(Txtmsg, 128, "Plantación [0%%]");
		Plantaciones[i][plVw] = GetPlayerVirtualWorld(playerid);
		Plantaciones[i][plInt] = GetPlayerInterior(playerid);
		Plantaciones[i][plProgreso] = CreateDynamic3DTextLabel(Txtmsg, Verde, X, Y, Z, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Plantaciones[i][plVw], Plantaciones[i][plInt]);
	
		new row[10];
		mysql_query("SELECT id FROM plantaciones ORDER BY id DESC LIMIT 1");
		mysql_store_result();
        mysql_fetch_row(row);
        Plantaciones[i][plSQLID] = strval(row) +1;
 
		new tmp[256];
		format(tmp, 256, "INSERT INTO plantaciones (tipo, X, Y, Z, VW, interior, tiempo, plantador, estado) VALUES (%d,%f,%f,%f,%d,%d,%d,'%s',%d)",
		Plantaciones[i][plTipo],Plantaciones[i][plX],Plantaciones[i][plY],Plantaciones[i][plZ],Plantaciones[i][plVw],Plantaciones[i][plInt],Plantaciones[i][plTiempo],
		Plantaciones[i][plPlantador],Plantaciones[i][plEstado]);
		mysql_query(tmp);
		break;
	}
	mysql_free_result();
	return 1;
}

forward IsPlayerPlanting(playerid);
public IsPlayerPlanting(playerid)
{
	for(new i; i < MAX_PLANTACIONES; i++)
	{
		if(strcmp(Plantaciones[i][plPlantador], pName(playerid), true) == 0)
		{
			if(Plantaciones[i][plEstado] == 0) { continue; }
			return 1;
		}
	}
	return 0;
}

forward Plantacion();
public Plantacion()
{
	for(new i; i < MAX_PLANTACIONES; i++)
	{
		if(Plantaciones[i][plEstado] != 1 || Plantaciones[i][plEstado] == 2) {continue;}
		Plantaciones[i][plTiempo] ++;
		if(Plantaciones[i][plTiempo] == 29)
		{
			UpdateDynamic3DTextLabelText(Plantaciones[i][plProgreso], Verde, "Plantación [100\%]");
			if(Plantaciones[i][plTipo] == 0)
			{
				Plantaciones[i][plObjeto] = CreateDynamicObject(2244, Plantaciones[i][plX], Plantaciones[i][plY], Plantaciones[i][plZ] - 0.9, 0, 0, 0, Plantaciones[i][plVw], Plantaciones[i][plInt]);
			}
			else
			{
				Plantaciones[i][plObjeto] = CreateDynamicObject(2001, Plantaciones[i][plX], Plantaciones[i][plY], Plantaciones[i][plZ] - 1.1, 0, 0, 0, Plantaciones[i][plVw], Plantaciones[i][plInt]);
			}
			Plantaciones[i][plEstado] = 2;
		}
		else
		{
			new porcentaje;
			porcentaje = (Plantaciones[i][plTiempo] * 100) / 29;
			format(string, 128, "Plantación [%d%%]", porcentaje);
			UpdateDynamic3DTextLabelText(Plantaciones[i][plProgreso], Verde, string);
		}
		SavePlanta(i);
	}
	return 1;
}

forward Drogas_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public Drogas_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(((newkeys & KEY_SECONDARY_ATTACK) == KEY_SECONDARY_ATTACK) && ((oldkeys & KEY_SECONDARY_ATTACK) != KEY_SECONDARY_ATTACK))
	{
		for(new i; i < MAX_PLANTACIONES; i++)
		{
			if(Plantaciones[i][plEstado] != 2) { continue; }
			if(PlayerToPoint(1.0, playerid, Plantaciones[i][plX], Plantaciones[i][plY], Plantaciones[i][plZ]))
			{
				new vw; 
				vw = GetPlayerVirtualWorld(playerid);
				if(vw == Plantaciones[i][plVw])
				{
					new tipo;
					tipo = Plantaciones[i][plTipo];
					Plantaciones[i][plEstado] = 0;
					PlayerInfo[playerid][pDrogaNP][tipo] += 1;
					SavePlanta(i);
					DestroyDynamic3DTextLabel(Plantaciones[i][plProgreso]);
					DestroyDynamicObject(Plantaciones[i][plObjeto]);
					if(tipo == 0)
					{
						SendClientMessage(playerid, Verde, "* Recogiste hojas de marihuana del suelo.");
					}
					else
					{
						SendClientMessage(playerid, Verde, "* Recogiste hojas de coca del suelo.");
					}
					SaveValues(playerid, "NoPreparada");
					return 1;
				}
			}
		}
	}
	return 0;
}

forward Drogas_OnExit();
public Drogas_OnExit()
{
	for(new i; i < MAX_PLANTACIONES; i++)
	{
		SavePlanta(i);
	}
	return 1;
}

forward Consumo(playerid, tipo);
public Consumo(playerid, tipo)
{
	switch(tipo)
	{
		case 0:
		{
			KillTimer(PlayerInfo[playerid][pConsumoTimer]);
			SetPlayerWeather(playerid, 10);
			new hora, minuto, segundo;
			gettime(hora, minuto, segundo);
			SetPlayerTime(playerid, hora, 0);
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY)
			{
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
			PlayerInfo[playerid][pHambre] = 4;
			SendClientMessage(playerid, Naranja, "* Te ha dado hambre por consummir estupefacientes.");
			ComprobarBarrita(playerid);
		}
		case 1:
		{
			SetPlayerWeather(playerid, -66);
			SetPlayerTime(playerid, 12, 0);
			ApplyAnimation(playerid,"CRACK","crckidle1",4.0,1,0,0,0,10000,1);
			PlayerInfo[playerid][pConsumoTimer] = SetTimerEx("Consumo", 300000, 0, "ii", playerid, 0);
			FlashPlayerScreen(playerid, 0xCC000055, 1, 10);
		}
		case 2:
		{
			PlayerInfo[playerid][pConsumoTimer] = SetTimerEx("Consumo", 300000, 0, "ii", playerid, 0);
			FlashPlayerScreen(playerid, 0xFFFFFF55, 125, 100);
		}
		case 3:
		{
			PlayerInfo[playerid][pConsumoTimer] = SetTimerEx("Consumo", 300000, 0, "ii", playerid, 0);
			SetPlayerDrunkLevel(playerid, 30000);
			FlashPlayerScreen(playerid, 0x1eb03244, 1, 10);
		}
	}
	return 1;
}

forward ResetConsumos(playerid);
public ResetConsumos(playerid)
{
	PlayerInfo[playerid][pTmpConsumos][0] = 0;
	PlayerInfo[playerid][pTmpConsumos][1] = 0;
	PlayerInfo[playerid][pTmpConsumos][2] = 0;
	SaveValues(playerid, "TmpConsumos");
	return 1;
}