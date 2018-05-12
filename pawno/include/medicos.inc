#include <a_samp>
#include <globalvars>
#include <funciones>
#include <cuentas>

#define MAX_INFORMES 50
enum iInfo
{
	iPaciente,
	iEstado,
	Float:iX,
	Float:iY,
	Float:iZ,
	
	iTimer,
	iMedico,
}

new Informes[MAX_INFORMES][iInfo];

Medicos_OnGameModeInit()
{
	CreateDynamic3DTextLabel("Azotea", Amarillo, -368.6265,140.1281,1035.6298, 5);
	for(new i; i < MAX_INFORMES; i++)
	{
		Informes[i][iPaciente] = -1;
		Informes[i][iMedico] = -1;
	}
}

Medicos_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/informes", true) == 0)
	{
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estas en servicio!"); return 1; }
		if(!IsAMedic(playerid)) { SendClientMessage(playerid, Rojo, "* No eres médico!"); return 1; }
		SendClientMessage(playerid, Amarillo, "Informes disponibles:");
		for(new i = 0; i < MAX_INFORMES; i++)
		{
			if(Informes[i][iEstado] > 0)
			{
				if(Informes[i][iEstado] == 1)
				{
					format(string, 128, "%d. En espera...", i);
					SendClientMessage(playerid, Rojo, string);
				}
				else if(Informes[i][iEstado] == 2)
				{
					format(string, 128, "%d. En Camino...", i);
					SendClientMessage(playerid, Verde, string);
				}
			}
		}
		SendClientMessage(playerid, Blanco, "USO: /informe [ID]");
		return 1;
	}
	
	if(strcmp(cmd, "/informe", true) == 0)
	{
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estas en servicio!"); return 1; }
		if(!IsAMedic(playerid)) { SendClientMessage(playerid, Rojo, "* No eres médico!"); return 1; }
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !IsNumeric(tmp)) { SendClientMessage(playerid, Blanco, "USO: /informe [ID]"); return 1; }
		new id = strval(tmp);
		if(Informes[id][iEstado] != 1) { SendClientMessage(playerid, Rojo, "* Informe inválido. Usa /informes para mayor información."); return 1; }
		SendClientMessage(playerid, Naranja, "[INFORMES]: Te hemos marcado la posición de la emergencia en el GPS.");
		SetPlayerCheckpoint(playerid, Informes[id][iX], Informes[id][iY], Informes[id][iZ], 8.0);
		PlayerInfo[playerid][pCheckpoint] = 16;
		Informes[id][iEstado] = 2;
		Informes[id][iMedico] = playerid;
		return 1;
	}
	
	if(strcmp(cmd, "/subiram", true) == 0)
	{
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estas en servicio!"); return 1; }
	    if(!IsAMedic(playerid))
	    {
	        SendClientMessage(playerid, Rojo, "* Debes ser médico!");
	        return 1;
	    }
	    if(!IsPlayerInAnyVehicle(playerid))
	    {
	        SendClientMessage(playerid, Rojo, "* Debes estar en una Ambulancia!");
	        return 1;
	    }
	    if((CarInfo[GetPlayerVehicle(playerid)][cUsos]!=PlayerInfo[playerid][pMember]) || GetVehicleModel(GetPlayerVehicleID(playerid)) != 416)
	    {
	        SendClientMessage(playerid, Rojo, "Debes estar en una Ambulancia!");
	        return 1;
	    }
	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
	    {
	        SendClientMessage(playerid, Blanco, "USO: /subiram [IdJugador/ParteDelNombre]");
	        return 1;
	    }
		new id;
		if(!IsNumeric(tmp))
		id = ReturnUser(tmp,playerid);
		else id = strval(tmp);
	    if(GetDistanceBetweenPlayers(playerid, id) >= 10)
	    {
	        SendClientMessage(playerid, Rojo, "* Debes estar más cerca!");
	        return 1;
	    }

		new vid = GetPlayerVehicleID(playerid);
		PutPlayerInVehicle(id, vid, 3);
		format(string,sizeof(string), "* %s ha subido al herido %s a la ambulancia.",pName(playerid),pName(id));
		ProxDetector(20.0, playerid, string, Verde,Verde,Verde,Verde,Verde);
		TogglePlayerControllable(id, 0);
		return 1;
	}
	
	if(strcmp(cmd, "/bajaram", true) == 0)
	{
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estas en servicio!"); return 1; }
	    if(IsAMedic(playerid))
	    {
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp) || !IsNumeric(tmp))
			{
			    SendClientMessage(playerid, Blanco, "USO: /bajaram [IdJugador/ParteDelNombre]");
			    return 1;
			}
			new id;
			if(!IsNumeric(tmp))
			id = ReturnUser(tmp,playerid);
			else id = strval(tmp);
			if(GetDistanceBetweenPlayers(playerid, id) > 10)
			{
			    SendClientMessage(playerid, Rojo, "* Debes estar más cerca!");
			    return 1;
			}
			if(IsPlayerInAnyVehicle(id))
			{
			    TogglePlayerControllable(id, 1);
				new Float:X, Float:Y, Float:Z;
				GetPlayerPos(playerid, X,Y,Z);
				SetPlayerPos(id, X,Y,Z+1.5);
				TogglePlayerControllable(id, 1);
				format(string,sizeof(string), "* %s baja la camilla de la ambulancia y la empuja hacia emergencias.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				format(string, sizeof(string), "* %s te ha bajado de la ambulancia. (( Sigue al Paramédico ))", pName(playerid));
				SendClientMessage(id, Azul, string);
				
			}
			else
			{
			    SendClientMessage(playerid, Rojo, "* Esa persona no está en la ambulancia!");
			    return 1;
			}
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No eres Médico!");
		    return 1;
		}
		return 1;
	}

	if(strcmp(cmd, "/curar", true) == 0)
	{
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estas en servicio!"); return 1; }
	    if(!IsAMedic(playerid))
	    {
	        SendClientMessage(playerid, Rojo, "* Debes ser médico!");
	        return 1;
	    }
	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
	    {
	        SendClientMessage(playerid, Blanco, "USO: /curar [IdJugador/ParteDelNombre]");
	        return 1;
	    }
		new id;
		if(!IsNumeric(tmp))
		id = ReturnUser(tmp,playerid);
		else id = strval(tmp);
	    if(GetDistanceBetweenPlayers(playerid, id) >= 10)
	    {
	        SendClientMessage(playerid, Rojo, "* Debes estar más cerca de la persona que deseas curar!");
	        return 1;
	    }
		new Float:health;
		GetPlayerHealth(id,health);
		if(health != 100.0)
		{
			format(string,sizeof(string), "¡Enhorabuena! El Paramédico %s ha logrado curar las heridas de %s.",pName(playerid),pName(id));
			if(GetPlayerInterior(playerid) > 0){
			ProxDetector(12.0, playerid, string, Verde,Verde,Verde,Verde,Verde);}
			else {
			ProxDetector(20.0, playerid, string, Verde,Verde,Verde,Verde,Verde);}
			GM_SetPlayerHealth(id, 100.0);
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* Esa persona no está herida.");
		}
		return 1;
	}
	
	if(strcmp(cmd, "/rehabilitar", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /rehabilitar [PlayerID]");
			return 1;
		}
		
		new player;
		player = ReturnUser(tmp);
		
		if(PlayerInfo[player][pAbstinencia] > 0)
		{
			PlayerInfo[player][pAbstinencia] = 0;
			SaveValue(player, "Abstinencia", PlayerInfo[player][pAbstinencia]);
			format(string, 128, "* El paramédico %s curó tu sindrome de abstienencia producido por consumo excesivo de crack.", pName(playerid));
			SendClientMessage(player, Amarillo, string);
			format(string, 128, "* Curaste de abstinencia a %s.", pName(player));
			SendClientMessage(playerid, Amarillo, string);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/reanimar", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 1)
		{
			if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estas en servicio!"); return 1; }
			if(!IsAMedic(playerid))
			{
				SendClientMessage(playerid, Rojo, "* Debes ser médico!");
				return 1;
			}
		}
	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
	    {
	        SendClientMessage(playerid, Blanco, "USO: /reanimar [IdJugador/ParteDelNombre]");
	        return 1;
	    }
		new id;
		id = ReturnUser(tmp);

	    if(GetDistanceBetweenPlayers(playerid, id) >= 10)
	    {
	        SendClientMessage(playerid, Rojo, "* Debes estar más cerca de la persona que deseas reanimar!");
	        return 1;
	    }
		
		if(PlayerInfo[playerid][pAdmin] < 1)
		{
			if(id == playerid)
			{
				SendClientMessage(playerid, Rojo, "* No te puedes reanimar a ti mismo!");
				return 1;
			}
		}
		
		if(PlayerInfo[id][pHerido] == 1)
		{
			format(string,sizeof(string), "¡Enhorabuena! El Paramédico %s ha logrado reanimar al herido %s.",pName(playerid),pName(id));
			if(GetPlayerInterior(playerid) > 0){
			ProxDetector(12.0, playerid, string, Verde,Verde,Verde,Verde,Verde);}
			else {
			ProxDetector(20.0, playerid, string, Verde,Verde,Verde,Verde,Verde);}
			GM_SetPlayerHealth(id, 20.0);
			TogglePlayerControllable(id, 1);
			PlayerInfo[id][pHerido] = 0;
			if(PlayerInfo[id][pSeguroMedico] == 0){ SafeGivePlayerMoney(id,-500); }
			SaveValue(id, "Herido", 0);
			
			for(new i; i < MAX_INFORMES; i++)
			{
				if(Informes[i][iPaciente] == id)
				{
					Informes[i][iEstado] = 0;
					KillTimer(Informes[i][iTimer]);
					DisablePlayerCheckpoint(Informes[i][iMedico]);
					break;
				}
			}
			
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* Esa persona no está herida.");
		}
		return 1;
	}
	
	return 0;
}

Medicos_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	if(juega_paintball[playerid] == 0 || PlayerInfo[playerid][pJailed] == 1 || PlayerInfo[playerid][pFixDeathCar] == 1)
	{
		GetPlayerPos(playerid, PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz]);
		PlayerInfo[playerid][pTmpInt] = GetPlayerInterior(playerid);
		PlayerInfo[playerid][pTmpVw] = GetPlayerVirtualWorld(playerid);
		PlayerInfo[playerid][pHerido] = 1;
		SaveValue(playerid, "Herido", PlayerInfo[playerid][pHerido]);
		SetTimerEx("DetectarClassSelection",5000,0,"i",playerid);
	}
	return 1;
}

forward DetectarClassSelection(playerid);
public DetectarClassSelection(playerid)
{
    if (GetPlayerState(playerid) == PLAYER_STATE_WASTED )
    {
        //SendClientMessage(playerid,Rojo,"Seleccion de clase");
		SetPlayerPos(playerid, PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz]);
        SpawnPlayer(playerid);
    }
    return 1;
}
Medicos_OnPlayerSpawn(playerid)
{
	if(PlayerInfo[playerid][pHerido] == 1)
	{
		if(PlayerInfo[playerid][pDuty] == 0)
		{
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		}
		else
		{
			SetPlayerSkin(playerid, PlayerInfo[playerid][pUniforme]);
		}
		SetPlayerPosEx(playerid, PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz]);
		SetPlayerInterior(playerid, PlayerInfo[playerid][pTmpInt]);
		SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pTmpVw]);
		TogglePlayerControllable(playerid, 0);
		Ambulancia(playerid);
		SetTimerEx("Animacion", 2000, 0, "d", playerid);
	}
	return 1;
}

Medicos_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 16)
	{
		SendClientMessage(playerid, Verde, "* Has llegado a tiempo al lugar de la emergencia.");
		for(new i; i < MAX_INFORMES; i++)
		{
			if(Informes[i][iMedico] == playerid)
			{
				KillTimer(Informes[i][iTimer]);
				Informes[i][iEstado] = 0;
				Informes[i][iPaciente] = -1;
				Informes[i][iMedico] = -1;
				break;
			}
		}
		DisablePlayerCheckpoint(playerid);
		return 1;
	}
	return 0;
}

Ambulancia(playerid)
{
	for(new i; i < MAX_INFORMES; i++)
	{
		if(Informes[i][iEstado] == 0)
		{
			Informes[i][iPaciente] = playerid;
			Informes[i][iX] = PlayerInfo[playerid][pTmpSpawnx];
			Informes[i][iY] = PlayerInfo[playerid][pTmpSpawny];
			Informes[i][iZ] = PlayerInfo[playerid][pTmpSpawnz];
			Informes[i][iEstado] = 1;
			Informes[i][iTimer] = SetTimerEx("PlayerDeath", 180000, 0, "i", playerid);
			format(string, 128, "[INFORMES]: Se ha reportado un caso de emergencias nuevo. Para atenderlo: /informe %d", i);
			break;
		}
	}
	SendFamilyMessage(2, Naranja, string);
	if(PremiumValido(playerid, 2))
	{
		SendClientMessage(playerid, Amarillo, "* Los paramedicos están en camino. ((Si no llegan en 3 minutos serás teleportado))");
	}
	else
	{
		SendClientMessage(playerid, Amarillo, "* Los paramedicos están en camino. Pierdes 1 punto de respeto. ((Si no llegan en 3 minutos serás teleportado))");
		if(PlayerInfo[playerid][pRespeto] > 0) { PlayerInfo[playerid][pRespeto] -= 2; ComprobarNivel(playerid); }
	}
	return 1;
}

forward PlayerDeath(playerid);
public PlayerDeath(playerid)
{
	PlayerInfo[playerid][pHerido] = 0;
	SaveValue(playerid, "Herido", 0);
	TogglePlayerControllable(playerid, 1);
	for(new i; i < MAX_INFORMES; i++)
	{
		if(Informes[i][iPaciente] == playerid && Informes[i][iEstado] == 1)
		{
			Informes[i][iEstado] = 0;
			break;
		}
		else if(Informes[i][iPaciente] == playerid && Informes[i][iEstado] == 2)
		{
			DisablePlayerCheckpoint(Informes[i][iMedico]);
			SendClientMessage(Informes[i][iMedico], Rojo, "* Te has demorado mucho. Misión abortada.");
			Informes[i][iEstado] = 0;
			Informes[i][iMedico] = NOEXISTE;
			break;
		}
	}
	new medicos;
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(IsAMedic(i))
		{
			medicos=1;
			break;
		}
	}
	if(PlayerInfo[playerid][pJailed] == 1)
	{
		SendClientMessage(playerid, Naranja, "* Has quedado inconsciente. No recuerdas nada... Un patrulla te trajo de vuelta a prisión.");
		SetPlayerPos(playerid, 2583.8286,-1325.6830,1047.9634);
		SetPlayerInterior(playerid, 2);
		SetPlayerVirtualWorld(playerid, 0);		
	}
	else if(medicos == 1 && GetPlayerInterior(playerid) == 0)
	{
		if(PremiumValido(playerid, 3))
		{
			SendClientMessage(playerid, Naranja, "* Has quedado inconsciente y te han llevado al hospital.");
		}
		else if(PremiumValido(playerid, 2))
		{
			if(PlayerInfo[playerid][pRespeto] > 1) { PlayerInfo[playerid][pRespeto] -= 3; ComprobarNivel(playerid); }
			SendClientMessage(playerid, Naranja, "* Has quedado inconsciente y te han llevado al hospital. Desafortunadamente has perdido $2000.");
		}
		else
		{
			if(SafeGetPlayerMoney(playerid) > 0) SafeGivePlayerMoney(playerid, -2000);
			if(PlayerInfo[playerid][pRespeto] > 1) { PlayerInfo[playerid][pRespeto] -= 3; ComprobarNivel(playerid); }
			SendClientMessage(playerid, Naranja, "* Has quedado inconsciente y te han llevado al hospital. Desafortunadamente has perdido $2000 y 2Exp.");
		}
		SetPlayerPos(playerid, 1184.0231,-1323.8063,13.3217);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else
	{
		SendClientMessage(playerid, Naranja, "* Has quedado inconsciente y una ambulancia te trajo hasta el hospital. No recuerdas nada.");
		SetPlayerPos(playerid, 1184.0231,-1323.8063,13.3217);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	return 1;
}

Medicos_PlayerDisconnect(playerid)
{	
	for(new i; i < MAX_INFORMES; i++)
	{
		if(Informes[i][iPaciente] == playerid && Informes[i][iEstado] == 1)
		{
			KillTimer(Informes[i][iTimer]);
			Informes[i][iEstado] = 0;
			break;
		}
		else if(Informes[i][iPaciente] == playerid && Informes[i][iEstado] == 2)
		{
			KillTimer(Informes[i][iTimer]);
			DisablePlayerCheckpoint(Informes[i][iMedico]);
			SendClientMessage(Informes[i][iMedico], Naranja, "(( El jugador se desconectó. Misión abortada. ))");
			Informes[i][iEstado] = 0;
			Informes[i][iMedico] = NOEXISTE;
			break;
		}
	}
	return 1;
}

forward Animacion(playerid);
public Animacion(playerid)
{
	ApplyAnimation(playerid,"CRACK","crckdeth1",4.1,0,1,1,1,1,1);
	TogglePlayerControllable(playerid, 0);
}