/* 
   Old School v2 "The future is here"
   - - - - - - - - - - - - - - - - - -
		DEATH GOP GORTHOL DESK
   - - - - - - - - - - - - - - - - - -
*/

#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>

//--[RECON SYSTEM -> DEFINES Y NEWS <-]--
new Float:RecPos[MAX_PLAYERS][4], IntRec[MAX_PLAYERS], VwRec[MAX_PLAYERS];
new Float:GosX[MAX_PLAYERS], Float:GosY[MAX_PLAYERS], Float:GosZ[MAX_PLAYERS], Float:GosA[MAX_PLAYERS], GosI[MAX_PLAYERS];
new Text:ReconTD[MAX_PLAYERS];
#define ADMIN_SPEC_TYPE_NONE	0
#define ADMIN_SPEC_TYPE_PLAYER 	1
#define ADMIN_SPEC_TYPE_VEHICLE 2
//----------------------------------------
//--[-> DUDAS SYSTEM <-]--
#define MAX_DUDAS 50
enum dInfo
{
	dState,
	dQuestioner,
	dQuestionerName[24],
	dQuestion[128],
}
new Dudas[MAX_DUDAS][dInfo];
//----------------------------------------
//--[-> REPORT SYSTEM <-]--
#define MAX_REPORTS 50
enum rInfo
{
	rState,
	rReporter,
	rReporterName[24],
	rReported,
	rReportedName[24],
	rDescription[128],
	rTime[24],
}
new Report[MAX_REPORTS][rInfo];
//----------------------------------------
Admin_OnGameModeInit()
{
	//RECON System
	for(new l=0; l<MAX_PLAYERS; l++)
	{
	ReconTD[l] = TextDrawCreate(326.000000, 362.000000, " ");
	TextDrawAlignment(ReconTD[l], 2);
	TextDrawBackgroundColor(ReconTD[l], 255);
	TextDrawFont(ReconTD[l], 1);
	TextDrawLetterSize(ReconTD[l], 0.300000, 1.100000);
	TextDrawColor(ReconTD[l], -1587871574);
	TextDrawSetOutline(ReconTD[l], 0);
	TextDrawSetProportional(ReconTD[l], 1);
	TextDrawSetShadow(ReconTD[l], 1);
	}
	//DUDAS System
	for (new dudaid = 1; dudaid < MAX_DUDAS; dudaid++)
	{
	    Dudas[dudaid][dState] = NOEXISTE;
	}
	//REPORT System
	for (new reportid = 1; reportid < MAX_REPORTS; reportid++)
	{
	    Report[reportid][rState] = NOEXISTE;
	}
	return 1;
}

Admin_OnPlayerDisconnect(playerid)
{
	// RECON System
	for(new x=0; x<MAX_PLAYERS; x++)
	{
    if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] == playerid)
	AdvanceSpectate(x);
	}
	//DUDAS System
	if(PlayerInfo[playerid][pDudaid] != NOEXISTE)
	{
	new id = PlayerInfo[playerid][pDudaid];
	Dudas[id][dState] = NOEXISTE;
	}
	return 1;
}

Admin_OnPlayerDeath(playerid)
{
	// RECON System
	for(new x=0; x<MAX_PLAYERS; x++)
	    if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] == playerid)
     	AdvanceSpectate(x);
	return 1;
}

Admin_OnPlayerInteriorChange(playerid, newinteriorid)
{
	// RECON System
	new x = 0;
	while(x!=MAX_PLAYERS)
	{
    if( IsPlayerConnected(x) &&	GetPlayerState(x) == PLAYER_STATE_SPECTATING &&
	PlayerInfo[x][SpecID] == playerid && PlayerInfo[x][SpecType] == ADMIN_SPEC_TYPE_PLAYER)
	{
		SetPlayerVirtualWorld(x,GetPlayerVirtualWorld(playerid));
		SetPlayerInterior(x,newinteriorid);
	}
	x++;
	}
}


Admin_OnPlayerKeyStateChange(playerid, newkeys)
{
	// RECON System
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && PlayerInfo[playerid][SpecID] != INVALID_PLAYER_ID)
	{
		if(newkeys == KEY_JUMP) AdvanceSpectate(playerid);
		else if(newkeys == KEY_SPRINT) ReverseSpectate(playerid);
		else if(newkeys == 4) StartSpectate(playerid, PlayerInfo[playerid][SpecID]);
		return 1;
	}
	return 0;
}

Admin_OnPlayerUpdate(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING  && (PlayerInfo[playerid][SpecType] == ADMIN_SPEC_TYPE_PLAYER || PlayerInfo[playerid][SpecType] == ADMIN_SPEC_TYPE_VEHICLE))
	{
		new specplayerid = PlayerInfo[playerid][SpecID];
		
		SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(specplayerid));
		SetPlayerInterior(playerid,GetPlayerInterior(specplayerid));

		new Float:hp, Float:ar;
		GetPlayerHealth(specplayerid, hp);
		GetPlayerArmour(specplayerid, ar);
		
		format(string,sizeof(string),"~w~- %s(%d) -~n~~n~~y~Vida: ~w~%0.1f ~l~- ~y~Armadura: ~w~%0.1f ~l~- ~y~Dinero: ~w~$%d~n~~n~~r~< Correr - Saltar >", pName(specplayerid),specplayerid,hp,ar,SafeGetPlayerMoney(specplayerid));
		TextDrawSetString(ReconTD[playerid], string);
	}
}

Admin_OnPlayerStateChange(playerid,newstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		for(new x=0; x<MAX_PLAYERS; x++)
		{
			if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] == playerid)
			{
				TogglePlayerSpectating(x, 1);
				PlayerSpectateVehicle(x, GetPlayerVehicleID(playerid));
				PlayerInfo[x][SpecType] = ADMIN_SPEC_TYPE_VEHICLE;
			}
		}
	}
	if(newstate == PLAYER_STATE_ONFOOT)
	{
		for(new x=0; x<MAX_PLAYERS; x++)
		{
			if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] == playerid && PlayerInfo[x][SpecType] == ADMIN_SPEC_TYPE_VEHICLE)
			{
				TogglePlayerSpectating(x, 1);
				PlayerSpectatePlayer(x, playerid);
				PlayerInfo[x][SpecType] = ADMIN_SPEC_TYPE_PLAYER;
			}
		}
	}
}


Admin_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128],idx,tmp[128],tmp2[128];
	cmd = strtokex(cmdtext, idx);
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/adminhelp", true) == 0 || strcmp(cmd, "/ah", true) == 0 || strcmp(cmd, "/ahelp", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
	    {		
			new pagina;
			if(PlayerInfo[playerid][pAdmin] == 4) pagina = 3; 
			else pagina = PlayerInfo[playerid][pAdmin];
			
			switch(pagina)
			{
				case 1:
				{
					SendClientMessage(playerid, Rosa, "Comandos de moderador");
					SendClientMessage(playerid, Blanco, "/adminservicio - /slap - /ajail - /kick - /ban - /banip - /reeducar - /advertir - /mark - /gotomark - /ir - /vermaletero");
					SendClientMessage(playerid, Blanco, "/(borrar)dudas - /rduda - /borrarduda - /(borrar)reportes - /verreporte - /borrarreporte - /goto - /teleplayer - /hide - /editgz");
					SendClientMessage(playerid, Blanco, "/setint - /setvw - /mover - /recon - /verarmas - /con(gelar) - /carinfo - /privados - /pms - /versms - /asay - /check - /verinventario");
					SendClientMessage(playerid, Blanco, "/afindcar - /afixpos - /resitecar - /findadmincar - /findteamcar - /adminbloqueo - /healcar - /oldcar - /verllaves - /premiums");
				}
				case 2:
				{
					SendClientMessage(playerid, Rosa, "Comandos de coordinador");
					SendClientMessage(playerid, Blanco, "/adminservicio - /slap - /ajail - /kick - /ban - /banip - /reeducar - /advertir - /mark - /gotomark - /ir - /vermaletero - /editgz");
					SendClientMessage(playerid, Blanco, "/(borrar)dudas - /rduda - /borrarduda - /(borrar)reportes - /verreporte - /borrarreporte - /goto - /teleplayer - /hide - /premiums");
					SendClientMessage(playerid, Blanco, "/setint - /setvw - /mover - /recon - /verarmas - /con(gelar) - /carinfo - /privados - /pms - /versms - /asay - /check - /verinventario");
					SendClientMessage(playerid, Blanco, "/repair - /sethp - /setarmor - /setdinero - /dardinero - /ad - /xgoto - /darequipo - /getcar - /gotocar - /asetcar - /desconectartodos");
					SendClientMessage(playerid, Blanco, "/resetllavescoches - /afindcar - /afixpos - /resitecar - /findadmincar - /findteamcar - /adminbloqueo - /healcar - /oldcar - /verllaves");
				}
				case 3:
				{
					SendClientMessage(playerid, Rosa, "Comandos de administrador");
					SendClientMessage(playerid, Blanco, "/adminservicio - /slap - /ajail - /kick - /ban - /banip - /reeducar - /advertir - /mark - /gotomark - /ir - /vermaletero");
					SendClientMessage(playerid, Blanco, "/(borrar)dudas - /rduda - /borrarduda - /(borrar)reportes - /verreporte - /borrarreporte - /goto - /teleplayer - /editgz");
					SendClientMessage(playerid, Blanco, "/setint - /setvw - /mover - /recon - /verarmas - /con(gelar) - /carinfo - /privados - /pms - /versms - /asay - /check - /verinventario");
					SendClientMessage(playerid, Blanco, "/repair - /sethp - /setarmor - /setdinero - /dardinero - /ad - /xgoto - /darequipo - /getp - /getcar - /gotocar - /verllaves");
					SendClientMessage(playerid, Blanco, "/crearcoche - /asetcar - /crearcasa - /editcasa - /creanergocio - /editneg - /resetllavescoches - /adminbloqueo - /desconectartodos");
					SendClientMessage(playerid, Blanco, "/setstat - /sethabilidad - /haceradmin - /afindcar - /afixpos - /resitecar - /findadmincar - /findteamcar - /healcar - /oldcar");
					SendClientMessage(playerid, Blanco, "/editaraudio - /crearparking - /editparking - /hacerpremium - /verpremium - /premiums - /atach - /qatach - /rcmd");
				}
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/goto", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /goto [IdJugador/ParteDelNombre]"); return 1;}
	    	new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
			{
				new Float:x, Float:y, Float:z;	GetPlayerPos(player1,x,y,z);
				SetPlayerInterior(playerid,GetPlayerInterior(player1));
				SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(player1));
				if(GetPlayerState(playerid) == 2)
				{
				SetVehiclePos(GetPlayerVehicleID(playerid),x+3,y,z);
				LinkVehicleToInterior(GetPlayerVehicleID(playerid),GetPlayerInterior(player1));
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),GetPlayerVirtualWorld(player1));
				}
				else SetPlayerPos(playerid,x+2,y,z);
				//printf("ADMINLOG: %s se ha teleportado a la posicion de %s",pName(playerid), pName(player1));
				format(string,sizeof(string),"* Te has teleportado a la posicion de \"%s\"", pName(player1));
				SendClientMessage(playerid,AzulClaro,string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/xgoto", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 2)
		{
			new Float:x, Float:y, Float:z;
			new tmp3[256];
    	    tmp  = strtokex(cmdtext,idx);
			tmp2 = strtokex(cmdtext,idx);
			tmp3 = strtokex(cmdtext,idx);
    		if(!strlen(tmp) || !strlen(tmp2) || !strlen(tmp3)) { SendClientMessage(playerid, Blanco, "USO: /xgoto [PosX] [PosY] [PosZ]"); return 1; }
		    x = floatstr(tmp);
			y = floatstr(tmp2);
			z = floatstr(tmp3);
			if(GetPlayerState(playerid) == 2)
			SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
			else SetPlayerPos(playerid,x,y,z);
			//printf("ADMINLOG: %s se ha teleportado a las coordenadas %f %f %f",pName(playerid), x,y,z);
			format(string,sizeof(string),"* Te has teleportado a las coordenadas - X: %f, Y: %f, Z: %f", x,y,z);
			SendClientMessage(playerid,AzulClaro,string);
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/getthere", true) == 0 || strcmp(cmd, "/get", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /gethere [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1;
  			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
		 	{
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid,x,y,z);
				SetPlayerInterior(player1,GetPlayerInterior(playerid));
				SetPlayerVirtualWorld(player1,GetPlayerVirtualWorld(playerid));
				if(GetPlayerState(player1) == 2)
				{
   				new VehicleID = GetPlayerVehicleID(player1);
				SetVehiclePos(VehicleID,x+3,y,z);
				LinkVehicleToInterior(VehicleID,GetPlayerInterior(playerid));
				SetVehicleVirtualWorld(GetPlayerVehicleID(player1),GetPlayerVirtualWorld(playerid));
				}
				else SetPlayerPos(player1,x+2,y,z);
				format(string,sizeof(string),"* Has sido teleportado a la posicion del Administrador \"%s\"",pName(playerid));
				SendClientMessage(player1,AzulClaro,string);
				//printf("ADMINLOG: %s ha traido a su posicion a %s",pName(playerid), pName(player1));
				format(string,sizeof(string),"* Has teleportado a \"%s\" a tu posicion.", pName(player1));
				SendClientMessage(playerid,AzulClaro,string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
    if(strcmp(cmd, "/kick", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /kick [IdJugador/ParteDelNombre] [Razon]"); return 1;}
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /kick [IdJugador/ParteDelNombre] [Razon]"); return 1; }
				new hour,minute,second,year,month,day;
				gettime(hour,minute,second);
				getdate(year, month, day);
				new query[128];
				format(query, sizeof(query), "INSERT INTO `kicks` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', '%s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
				mysql_query(query);
				printf("ADMINLOG: %s ha kickeado %s - Razon: %s",pName(playerid), pName(player1), (result));
				format(string, sizeof(string), "\"%s\" ha sido expulsado por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
				SendClientMessageToAll(Rojo, string);
				TogglePlayerControllable(player1,0);
				Kick(player1);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
    if(strcmp(cmd, "/reeducar", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /reeducar [IdJugador/ParteDelNombre]"); return 1; }
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
		    {
				new hour,minute,second,year,month,day;
				gettime(hour,minute,second);
				getdate(year, month, day);
				new query[128];
				format(query, sizeof(query), "INSERT INTO `kicks` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', 'Reeducar','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid),hour,minute,second,day,month,year);
				mysql_query(query);
				format(string, sizeof(string), "\"%s\" ha sido expulsado por \"%s\" y forzado a aprender el tutorial", pName(player1), pName(playerid));
				SendClientMessageToAll(Rojo, string);
				SaveValue(player1, "Certificacion", 2);
				printf("ADMINLOG: %s ha reeducado a %s",pName(playerid), pName(player1));
				format(string, sizeof(string), "Has sido expulsado del juego. Necesitas reaprender las normas.");
				SendClientMessage(player1,Amarillo,string);
				TogglePlayerControllable(player1,0);
				Kick(player1);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo.");  }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
    if(strcmp(cmd, "/ban", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, Blanco, "USO: /ban [IdJugador/ParteDelNombre] [razon]");
				SendClientMessage(playerid, AzulClaro, "Aviso: Para banear a cheats o bans permanentes usar /banip"); 
				return 1;
			}
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /ban [IdJugador/ParteDelNombre] [razon]"); return 1; }
				new hour,minute,second,year,month,day;
				gettime(hour,minute,second);
				getdate(year, month, day);
				new query[128];
				format(query, sizeof(query), "INSERT INTO `bans` (`banneado`, `banner`, `razon`, `fecha`) VALUES ('%s', '%s', '%s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
				mysql_query(query);
				printf("ADMINLOG: %s ha baneado a %s - Razon: %s",pName(playerid), pName(player1), (result));
				format(string, sizeof(string), "\"%s\" ha sido baneado por \"%s\". Razón: %s", pNameEx(player1), pNameEx(playerid), (result));
				SendClientMessageToAll(Rojo, string);
				TogglePlayerControllable(player1,0);
				SaveValue(player1,"Bloqueado",1);
				Kick(player1);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
    if(strcmp(cmd, "/banip", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /banip [IdJugador/ParteDelNombre] [razon]"); return 1; }
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /banip [IdJugador/ParteDelNombre] [razon]"); return 1; }
				new hour,minute,second,year,month,day;
				gettime(hour,minute,second);
				getdate(year, month, day);
				new query[128];
				format(query, sizeof(query), "INSERT INTO `bans` (`banneado`, `banner`, `razon`, `fecha`) VALUES ('%s', '%s', '%s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
				mysql_query(query);
				printf("ADMINLOG: %s ha baneado permanentemente %s - Razon: %s",pNameEx(playerid), pNameEx(player1), (result));
				format(string, sizeof(string), "\"%s\" ha sido baneado permanentemente por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
				SendClientMessageToAll(Rojo, string);
				TogglePlayerControllable(player1,0);
				SaveValue(player1,"Bloqueado",1);
				Ban(player1);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); } 
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
    if(strcmp(cmd, "/move", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
		    if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /move [Up/Down/+X/-X/+Y/-Y/off]");
				return 1;
			}
			new Float:X, Float:Y, Float:Z;
			if(strcmp(tmp,"Up",true) == 0){
				TogglePlayerControllable(playerid,false);
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerPos(playerid,X,Y,Z+5);
				SetCameraBehindPlayer(playerid);
			}
			else if(strcmp(tmp,"Down",true) == 0){
				TogglePlayerControllable(playerid,false);
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerPos(playerid,X,Y,Z-5);
				SetCameraBehindPlayer(playerid);
			}
			else if(strcmp(tmp,"+X",true) == 0){
				TogglePlayerControllable(playerid,false);
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerPos(playerid,X+5,Y,Z);
			}
			else if(strcmp(tmp,"-X",true) == 0){
				TogglePlayerControllable(playerid,false);
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerPos(playerid,X-5,Y,Z);
			}
			else if(strcmp(tmp,"+Y",true) == 0){
				TogglePlayerControllable(playerid,false);
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerPos(playerid,X,Y+5,Z);
			}
			else if(strcmp(tmp,"-Y",true) == 0){
				TogglePlayerControllable(playerid,false);
				GetPlayerPos(playerid,X,Y,Z);
				SetPlayerPos(playerid,X,Y-5,Z);
			}
		    else if(strcmp(tmp,"off",true) == 0){
				TogglePlayerControllable(playerid,true);
			}
			else { SendClientMessage(playerid, Blanco, "USO: /move [Up/Down/+X/-X/+Y/-Y/off]"); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/sethp", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 2)
		{
		    tmp  = strtokex(cmdtext, idx);
			tmp2 = strtokex(cmdtext, idx);
		    if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp) || !IsNumeric(tmp2))
			{
				SendClientMessage(playerid, Blanco, "USO: /sethp [IdJugador] [Health]");
				return 1;
			}
			new player1 = strval(tmp);
			new hp = strval(tmp2);
        	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				format(string, sizeof(string), "* Has puesto a \"%s\" su vida a '%d'", pName(player1), hp);
				SendClientMessage(playerid,AzulClaro,string);
				if(player1 != playerid)
				{
				format(string,sizeof(string),"* Administrador \"%s\" ha puesto tu vida a '%d'", pName(playerid), hp);
				SendClientMessage(playerid,AzulClaro,string);
				}
				printf("ADMINLOG: %s ha setado la vida de %s a '%d'",pName(playerid), pName(player1), hp);
				PlayerPlaySound(player1,1057,0.0,0.0,0.0);
   				GM_SetPlayerHealth(player1, hp);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/setarmor", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 2)
		{
		    tmp  = strtokex(cmdtext, idx);
			tmp2 = strtokex(cmdtext, idx);
		    if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp) || !IsNumeric(tmp2))
			{
				SendClientMessage(playerid, Blanco, "USO: /setarmor [IdJugador] [Armadura]");
				return 1;
			}
			new player1 = strval(tmp);
			new armour = strval(tmp2);
        	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				format(string, sizeof(string), "* Has puesto a \"%s\" su armadura a '%d'", pName(player1), armour);
				SendClientMessage(playerid,AzulClaro,string);
				if(player1 != playerid)
				{
				format(string,sizeof(string),"* Administrador \"%s\" ha puesto tu armadura a '%d'", pName(playerid), armour);
				SendClientMessage(playerid,AzulClaro,string);
				}
				printf("ADMINLOG: %s ha setado la armadura de %s a '%d'",pName(playerid), pName(player1), armour);
				PlayerPlaySound(player1,1057,0.0,0.0,0.0);
   				SetPlayerArmour(player1, armour);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/setvw", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp  = strtokex(cmdtext, idx);
			tmp2 = strtokex(cmdtext, idx);
		    if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp) || !IsNumeric(tmp2))
			{
				SendClientMessage(playerid, Blanco, "USO: /setvw [IdJugador] [VirtualWorldID]");
				return 1;
			}
			new player1 = strval(tmp);
			new vw = strval(tmp2);
        	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				format(string, sizeof(string), "* Has puesto a \"%s\" el Virtual World '%d'", pName(player1), vw);
				SendClientMessage(playerid,AzulClaro,string);
				if(player1 != playerid)
				{
				format(string,sizeof(string),"* Administrador \"%s\" ha cambiado tu Virtual World a '%d'", pName(playerid), vw);
				SendClientMessage(player1,AzulClaro,string);
				}
				//printf("ADMINLOG: %s ha setado el vw de %s a '%d'",pName(playerid), pName(player1), vw);
				PlayerPlaySound(player1,1057,0.0,0.0,0.0);
   				SetPlayerVirtualWorld(player1, vw);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/setint", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp  = strtokex(cmdtext, idx);
		    tmp2 = strtokex(cmdtext, idx);
		    if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp) || !IsNumeric(tmp2))
			{
				SendClientMessage(playerid, Blanco, "USO: /setint [IdJugador] [InteriorID]");
				return 1;
			}
			new player1 = strval(tmp);
			new interior = strval(tmp2);
        	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				format(string, sizeof(string), "* Has puesto a \"%s\" el Interior '%d'", pName(player1), interior);
				SendClientMessage(playerid,AzulClaro,string);
				if(player1 != playerid)
				{
				format(string,sizeof(string),"* Administrador \"%s\" ha cambiado tu Interior a '%d'", pName(playerid), interior);
				SendClientMessage(player1,AzulClaro,string);
				}
				//printf("ADMINLOG: %s ha setado el interior de %s a '%d'",pName(playerid), pName(player1), interior);
				PlayerPlaySound(player1,1057,0.0,0.0,0.0);
   				SetPlayerInterior(player1, interior);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/clima", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] > 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /clima [ID]");
				return 1;
			}
			
			new id;
			id = strval(tmp);
			SetWeather(id);
		}
		return 1;
	}	
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/teleplayer", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp  = strtokex(cmdtext,idx);
			tmp2 = strtokex(cmdtext,idx);
		    if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp) || !IsNumeric(tmp2))
			{
				SendClientMessage(playerid, Blanco, "USO: /teleplayer [IDJugador] a [IDJugador]");
				return 1;
			}
			new player1 = strval(tmp), player2 = strval(tmp2);
			new Float:plocx,Float:plocy,Float:plocz;

		 	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			 {
	 		 	if(IsPlayerConnected(player2) && player2 != INVALID_PLAYER_ID)
				  {
					GetPlayerPos(player2, plocx, plocy, plocz);
					new intid = GetPlayerInterior(player2);
					SetPlayerInterior(player1,intid);
					SetPlayerVirtualWorld(player1,GetPlayerVirtualWorld(player2));
					if (GetPlayerState(player1) == PLAYER_STATE_DRIVER)
					{
					new VehicleID = GetPlayerVehicleID(player1);
					SetVehiclePos(VehicleID, plocx, plocy+4, plocz); LinkVehicleToInterior(VehicleID,intid);
					SetVehicleVirtualWorld(VehicleID, GetPlayerVirtualWorld(player2));
					}
					else SetPlayerPos(player1,plocx,plocy+2, plocz);
					printf("ADMINLOG: %s ha enviado a %s la posicion de %s",pName(playerid), pName(player1), pName(player2));
					format(string,sizeof(string),"* Administrador \"%s\" ha teleportado a \"%s\" a la posicion de \"%s\"!", pName(playerid), pName(player1), pName(player2));
					SendClientMessage(player1,AzulClaro,string); SendClientMessage(player2,AzulClaro,string);
					format(string,sizeof(string),"* Has teleportado a \"%s\" a la posicion de \"%s\"!", pName(player1), pName(player2));
	 		 	    SendClientMessage(playerid,AzulClaro,string);
	 		 	}
				else { SendClientMessage(playerid, Rojo, "ERROR: Jugador 2 no conectado."); }
			}
			else { SendClientMessage(playerid, Rojo, "ERROR: Jugador 1 no conectado."); } 
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if (strcmp(cmd, "/desconectartodos", true) ==0 )
	{
	    if(IsPlayerConnected(playerid))
	    {
			if (PlayerInfo[playerid][pAdmin] >= 1)
			{
				for(new i = 0; i < MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i))
					{
						if(PlayerInfo[i][pAdmin] < 1){SendClientMessage(i, Amarillo,"Un Administrador ha cerrado el servidor, por favor vuelve entrar en unos minutos.");Kick(i);}
					}
				}
				SendClientMessage(playerid, Gris, "  Todos los jugadores desconectados.");
				
				SendRconCommand("exit");
			}
			else
			{
				SendClientMessage(playerid, Gris, "   No puedes usar ese comando!");
			}
		}
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd,"/am",true)==0)
	{
		if (PlayerInfo[playerid][pAdmin] > 0)
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
				SendClientMessage(playerid, Blanco, "USO: /am [mensaje]");
				return 1;
			}
			format(string, sizeof(string), "ADMIN: %s", result);
			SendClientMessageToAll(Aguamarina,string);
		}
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/slap", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /slap [IdJugador/ParteDelNombre] [Razon]"); return 1; }
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /slap [IdJugador/ParteDelNombre] [Razon]"); return 1; }
		        new Float:Health;
				new Float:x, Float:y, Float:z;
				GetPlayerHealth(player1,Health);
				GM_SetPlayerHealth(player1,Health-25);
				GetPlayerPos(player1,x,y,z);
				SetPlayerPos(player1,x,y,z+5);
				PlayerPlaySound(playerid,1190,0.0,0.0,0.0);
				PlayerPlaySound(player1,1190,0.0,0.0,0.0);
				printf("ADMINLOG: %s ha bofeteado a %s - Razon: %s",pName(playerid), pName(player1), (result));
				format(string,sizeof(string),"* Has sido abofeteado por el administrador \"%s\" | Razon: %s",pName(playerid),(result));
				SendClientMessage(player1,AzulClaro,string);
				format(string,sizeof(string),"* Has bofetado a \"%s\" | Razon: %s",pName(player1),(result));
				SendClientMessage(playerid,AzulClaro,string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/haceradmin", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 3 || IsPlayerAdmin(playerid))
		{
			tmp = strtokex(cmdtext, idx);
			new Level, player1, rLevel[64];
  			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
			tmp2 = strtokex(cmdtext, idx);
			Level = strval(tmp2);
			if(!strlen(tmp) || !strlen(tmp2) || Level > 4) { SendClientMessage(playerid, Blanco, "USO: /haceradmin [IdJugador/ParteDelNombre] [Nivel(1-3)]"); return 1; }
			if(Level == 0) rLevel = "Usuario Normal";if(Level == 1) rLevel = "Moderador";if(Level == 2) rLevel = "Coordinador";if(Level == 3) rLevel = "Administrador";if(Level == 4) rLevel = "Programador";
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
		    {
				PlayerInfo[player1][pAdmin] = Level;
				printf("ADMINLOG: %s ha promocionado a %s a '%s'.", pName(playerid),pName(player1), rLevel);
				format(string, sizeof(string), "* Has sido promocionado a '%s' por \"%s\"", rLevel, pName(playerid));
				SendClientMessage(player1, AzulClaro, string);
				SaveValue(player1, "AdminLevel", PlayerInfo[player1][pAdmin]);
				format(string, sizeof(string), "* Has promocionado a \"%s\" a '%s'.", pName(player1),rLevel);
				SendClientMessage(playerid, AzulClaro, string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/hacerpremium", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 3)
		{
			tmp = strtokex(cmdtext, idx);
			new Level, player1, rLevel[40];
  			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
			tmp2 = strtokex(cmdtext, idx);
			Level = strval(tmp2);
			if(!strlen(tmp) || !strlen(tmp2) || Level > 3) { SendClientMessage(playerid, Blanco, "USO: /hacerpremium [IdJugador/ParteDelNombre] [0-Nada|1-Bronce|2-Plata|3-Oro]"); return 1; }
			if(Level == 0) rLevel = "Normal";if(Level == 1) rLevel = "Bronce";if(Level == 2) rLevel = "Plata";if(Level == 3) rLevel = "Oro";
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
		    {
				PlayerInfo[player1][pPremiumTipo] = Level;
				if(Level == 0) PlayerInfo[player1][pPremiumTime] = 0; else PlayerInfo[player1][pPremiumTime] = gettime()+2592000; // 1 mes
				SaveValue(player1, "Premium_Tipo", Level);
				SaveValue(player1, "Premium_Timestamp", PlayerInfo[player1][pPremiumTime]);
				printf("ADMINLOG: %s ha hecho premium %s a '%s'.", pName(playerid),Premium[GetPlayerPremium(player1)],pName(player1));
				if(Level != 0)
				{
					format(string, sizeof(string), "* Has sido hecho usuario premium '%s' por \"%s\"", rLevel, pName(playerid));
					SendClientMessage(player1, AzulClaro, string);
				}
				format(string, sizeof(string), "* Has hecho usuario premium '%s' a \"%s\".", rLevel, pName(player1));
				SendClientMessage(playerid, AzulClaro, string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/setdinero", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 2)
		{
			tmp = strtokex(cmdtext, idx);
			new player1, money;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
			tmp2 = strtokex(cmdtext, idx);
			money = strval(tmp2);
			if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp2)) { SendClientMessage(playerid, Blanco, "USO: /setdinero [IdJugador/ParteDelNombre] [Cantidad]"); return 1; }
	    	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
	    	{
 				new actualmoney = SafeGetPlayerMoney(player1);
				SafeGivePlayerMoney(player1, money-actualmoney);
				SaveValue(playerid, "Dinero", SafeGetPlayerMoney(player1));
				printf("ADMINLOG: %s seteo a %s '%d$' en su dinero de mano.", pName(playerid),pName(player1),money);
				format(string, sizeof(string), "* Has seteado a \"%s\" '%d$' en su dinero de mano.", pName(player1),money);
				SendClientMessage(playerid, AzulClaro, string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/dardinero", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 2)
		{
			tmp = strtokex(cmdtext, idx);
			new player1, money;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
			tmp2 = strtokex(cmdtext, idx);
			money = strval(tmp2);
			if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp2)) { SendClientMessage(playerid, Blanco, "USO: /dardinero [IdJugador/ParteDelNombre] [Cantidad]"); return 1; }
	    	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
	    	{
				SafeGivePlayerMoney(player1, money);
				SaveValue(playerid, "Dinero", SafeGetPlayerMoney(player1));
				printf("ADMINLOG: %s ha dado a %s '%d$' de dinero de mano.", pName(playerid),pName(player1),money);
				format(string, sizeof(string), "* Has dado a \"%s\" '%d$' de dinero de mano.", pName(player1),money);
				SendClientMessage(playerid, AzulClaro, string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/ad", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 2)
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
				SendClientMessage(playerid, Blanco, "USO: /ad [Texto]");
				SendClientMessage(playerid, AzulClaro, "NOTA: ~n~=NLinea ~r~=Rojo ~g~=Verde ~b~=Azul ~w~=Blanco ~y~=Amarillo");
				return 1;
			}
			format(string, sizeof(string), "~b~%s: ~w~%s",pName(playerid),result);
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i)) GameTextForPlayer(i, string, 5000, 6);
			}
			return 1;
	    }
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); return 1; }
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/recon", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1 || IsPlayerAdmin(playerid))
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) return
			SendClientMessage(playerid, Blanco, "USO: /recon [IdJugador/ParteDelNombre]");
	    	new specplayerid;
  			if(!IsNumeric(tmp))
			specplayerid = ReturnUser(tmp,playerid);
	   		else specplayerid = strval(tmp);
	        if(IsPlayerConnected(specplayerid) && specplayerid != INVALID_PLAYER_ID)
			{
				if(specplayerid == playerid)
				{ SendClientMessage(playerid, Rojo, "ERROR: No puedes hacer recon a ti mismo!"); return 1; }

				if(GetPlayerState(specplayerid) == PLAYER_STATE_SPECTATING && PlayerInfo[playerid][SpecID] != INVALID_PLAYER_ID)
				{ SendClientMessage(playerid, Rojo, "ERROR: Ese jugador ya esta haciendo recon a alguien!"); return 1; }

				if(GetPlayerState(specplayerid) != 1 && GetPlayerState(specplayerid) != 2 && GetPlayerState(specplayerid) != 3)
				{ SendClientMessage(playerid, Rojo, "ERROR: El jugador aun no esta logeado."); return 1; }

				if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && PlayerInfo[playerid][SpecID] == INVALID_PLAYER_ID)
				{
					GetPlayerPos(playerid,RecPos[playerid][0],RecPos[playerid][1],RecPos[playerid][2]);
					GetPlayerFacingAngle(playerid,RecPos[playerid][3]);
					IntRec[playerid] = (GetPlayerInterior(playerid));
					VwRec[playerid] = (GetPlayerVirtualWorld(playerid));
				}
                StartSpectate(playerid, specplayerid);
				//printf("ADMINLOG: %s esta reconeando a %s.", pName(playerid), pName(specplayerid));
				format(string,sizeof(string),"* Estas reconeando a \"%s\", para parar usa /reconoff.",pName(specplayerid));
			 	SendClientMessage(playerid,AzulClaro,string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/reconoff", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1 || IsPlayerAdmin(playerid))
		{
	   		if(PlayerInfo[playerid][SpecType] != ADMIN_SPEC_TYPE_NONE)
			{
				StopSpectate(playerid);
	  			TogglePlayerControllable(playerid, 0);
				SetTimerEx("ReturnPosition",1000,0,"d",playerid);
			 	//printf("ADMINLOG: %s ha dejado de reconear.", pName(playerid));
				SendClientMessage(playerid,AzulClaro,"* Has dejado de hacer recon.");
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: No estas reconeando a nadie."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/hide", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1 || IsPlayerAdmin(playerid))
		{
		    if (PlayerInfo[playerid][pHide] == 1)
 			{ SendClientMessage(playerid,Rojo,"ERROR: Ya estas oculto en la lista de admins!"); return 1; }

	 		PlayerInfo[playerid][pHide] = 1;
	   		SendClientMessage(playerid,AzulClaro,"* Ahora estas oculto en la lista de admins");
			//printf("ADMINLOG: %s se ha ocultado de la lista de admins.", pName(playerid));
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); } 
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/unhide", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1 || IsPlayerAdmin(playerid))
		{
 			if (PlayerInfo[playerid][pHide] != 1)
 			{ SendClientMessage(playerid,Rojo,"ERROR: No estas oculto en la lista de admins!"); return 1; }

 	 		PlayerInfo[playerid][pHide] = 0;
 	  		SendClientMessage(playerid,AzulClaro,"* Ahora estas visible en la lista de admins");
			//printf("ADMINLOG: %s ahora esta visible en la lista de admins.", pName(playerid));
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/amarcar", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /amarcar [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
		   		if(PlayerInfo[player1][pMarcado] == 0)
		   		{
 					PlayerInfo[player1][pMarcado] = 1;
 					SetPlayerColor(player1,0xD900D3C8);
 					//printf("ADMINLOG: %s ha marcado a %s en el mapa.", pName(playerid),pName(player1));
					format(string,sizeof(string),"* Has marcado a \"%s\" en el mapa.", pName(player1));
					SendClientMessage(playerid,AzulClaro,string);
				}
				else
				{
					PlayerInfo[player1][pMarcado] = 0;
    	    		SetPlayerColor(player1,0xFFFFFF00);
					//printf("ADMINLOG: %s ha quitado la marca a %s del mapa.", pName(playerid),pName(player1));
					format(string,sizeof(string),"* Has quitado la marca del mapa a \"%s\"", pName(player1));
					SendClientMessage(playerid,AzulClaro,string);
				}
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado"); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/adminservicio", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1 || IsPlayerAdmin(playerid))
		{
		    if(PlayerInfo[playerid][pAdminDuty] == 0)
		    {
 				PlayerInfo[playerid][pAdminDuty] = 1;
 				GM_SetPlayerHealth(playerid,100000);
 //				SetPlayerColor(playerid,0xD900D3C8);
				//printf("ADMINLOG: %s se ha puesto en admin servicio.", pName(playerid));
 				SendClientMessage(playerid,AzulClaro,"* Ahora estas en 'Admin Servicio'");
			}
			else
			{
				PlayerInfo[playerid][pAdminDuty] = 0;
    	    	GM_SetPlayerHealth(playerid,100);
//    	    	SetPlayerColor(playerid,0xFFFFFF00);
				//printf("ADMINLOG: %s se ha quitado de admin servicio.", pName(playerid));
 				SendClientMessage(playerid,AzulClaro,"* Ya no estas en 'Admin Servicio'");
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/premiums", true) == 0)
	{
	    new count = 0;
        new PremiumRank[64];
        SendClientMessage(playerid, AzulClaro, "___________ |- Premiums Online -| ___________");
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if (IsPlayerConnected(i))
				{
					if(GetPlayerPremium(i) >= 1)
					{
						switch(GetPlayerPremium(i))
						{
							case 1: {
							PremiumRank = "Bronce";
							}
							case 2: {
							PremiumRank = "Plata";
							}
							case 3: {
							PremiumRank = "Oro";
							}
 						}
						format(string, 128, "(ID:%i) %s - %s",i,pName(i),PremiumRank);
						SendClientMessage(playerid, Blanco, string);
						count++;
					}
				}
			}
		}
		if (count == 0)
		SendClientMessage(playerid,Blanco, "No hay ningún premium conectado.");
		
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/admins", true) == 0)
	{
	    new count = 0;
        new AdmRank[64],AdmDuty[64], AdmHide[64];
        SendClientMessage(playerid, AzulClaro, "___________ |- Staff Online -| ___________");
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if (IsPlayerConnected(i))
				{
					if(PlayerInfo[i][pAdmin] >= 1)
					{
						if(PlayerInfo[i][pAdmin] > 4)
						{
							AdmRank = "{a80707}Administrador";
						}
						else
						{
							switch(PlayerInfo[i][pAdmin])
							{
								case 1: {
								AdmRank = "{1eb032}Moderador";
								}
								case 2: {
								AdmRank = "{fce80c}Coordinador";
								}
								case 3: {
								AdmRank = "{a80707}Administrador";
								}
								case 4: {
								AdmRank = "{694cab}Programador";
								}
							}
						}
						switch(PlayerInfo[i][pAdminDuty])
						{
							case 0: AdmDuty = "{1eb032}Jugando!";
							case 1: AdmDuty = "{fce80c}De Servicio!";
						}
						switch(PlayerInfo[i][pHide])
						{
							case 0: AdmHide = " ";
							case 1: AdmHide = "{FFFFFF} - OCULTO";
						}
						format(string, 128, "(ID:%i) %s - %s {FFFFFF}- %s%s",i,pName(i),AdmRank,AdmDuty,AdmHide);
						SendClientMessage(playerid, Blanco, string);
						count++;
					}
				}
			}
		}
		else
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if (IsPlayerConnected(i))
				{
					if(PlayerInfo[i][pAdmin] >= 1 && PlayerInfo[i][pHide] == 0)
					{
						if(PlayerInfo[i][pAdmin] > 4)
						{
							AdmRank = "{a80707}Administrador";
						}
						else
						{
							switch(PlayerInfo[i][pAdmin])
							{
								case 1: {
								AdmRank = "{1eb032}Moderador";
								}
								case 2: {
								AdmRank = "{fce80c}Coordinador";
								}
								case 3: {
								AdmRank = "{a80707}Administrador";
								}
								case 4: {
								AdmRank = "{694cab}Programador";
								}
							}
						}
						switch(PlayerInfo[i][pAdminDuty])
						{
							case 0: AdmDuty = "{1eb032}Jugando!";
							case 1: AdmDuty = "{fce80c}De Servicio!";
						}
						format(string, 128, "(ID:%i) %s - %s {FFFFFF}- %s",i,pName(i),AdmRank,AdmDuty);
						SendClientMessage(playerid, Blanco, string);
						count++;
					}
				}
			}
		}
		if (count == 0)
		SendClientMessage(playerid,Blanco, "No hay nadie del Staff conectado en este momento.");
		
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/verarmas", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1 || IsPlayerAdmin(playerid))
		{
  			tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /verarmas [IdJugador/ParteDelNombre]");
				return 1;
			}
			new player1;
  			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
			new Count,x;
			new WeapName[24], slot, weap, ammo, string2[128];
		 	if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
		 	{
				//printf("ADMINLOG: %s ha consultado las armas de %s.", pName(playerid),pName(player1));
				format(string2,sizeof(string2),"_______|- Armas de \"%s\" (%d) -|_______",pName(player1), player1);
				SendClientMessage(playerid,Amarillo,string2);
				for(slot = 0; slot < 14; slot++)
				{
				GetPlayerWeaponData(player1, slot, weap, ammo);
				if(weap != 0)
				Count++;
				}
				if(Count < 1)
				{ SendClientMessage(playerid,Rojo,"* El jugador no tiene ningun arma!"); return 1; }

				if(Count >= 1)
				{
                    format(string, sizeof(string), "");
					for (slot = 0; slot < 14; slot++)
					{
						GetPlayerWeaponData(player1, slot, weap, ammo);

						if(weap != 0)
						{
							GetWeaponName(weap, WeapName, sizeof(WeapName));
							format(string,sizeof(string),"%s%s (%d)",string, WeapName, ammo);
							x++;
							if(x >= 5)
							{
								SendClientMessage(playerid, Amarillo, string);
								x = 0;
								format(string, sizeof(string), "");
							}
							else format(string, sizeof(string), "%s,  ", string);
						}
					}
					if(x <= 4 && x > 0)
					{
					string[strlen(string)-3] = '.';
    				SendClientMessage(playerid, Amarillo, string);
					}
		    	}
		    	return 1;
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/congelar", true) == 0 || strcmp(cmd, "/con", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /con(gelar) [IdJugador/ParteDelNombre]"); return 1; }
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
		    {
	    		if(PlayerInfo[player1][pFrozen] == 0)
	    		{
	    		    PlayerInfo[player1][pFrozen] = 1;
	    		    TogglePlayerControllable(player1, 0);
					//printf("ADMINLOG: %s ha congelado a %s.", pName(playerid),pName(player1));
					format(string,sizeof(string),"* Has sido congelado por el administrador \"%s\"",pName(playerid));
					SendClientMessage(player1,AzulClaro,string);
					format(string,sizeof(string),"* Has congelado a \"%s\"",pName(player1));
					SendClientMessage(playerid,AzulClaro,string);
				}
				else if(PlayerInfo[player1][pFrozen] == 1)
				{
	    		    PlayerInfo[player1][pFrozen] = 0;
	    		    TogglePlayerControllable(player1, 1);
					//printf("ADMINLOG: %s ha descongelado a %s.", pName(playerid),pName(player1));
					format(string,sizeof(string),"* Has sido descongelado por el administrador \"%s\"",pName(playerid));
					SendClientMessage(player1,AzulClaro,string);
					format(string,sizeof(string),"* Has descongelado a \"%s\"",pName(player1));
					SendClientMessage(playerid,AzulClaro,string);
				}
				
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/asay", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
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
				SendClientMessage(playerid, Blanco, "USO: /asay [Texto] ");
				return 1;
			}
			new Rango[24];
			if(PlayerInfo[playerid][pAdmin] == 1) Rango = "Moderador";
			if(PlayerInfo[playerid][pAdmin] == 2) Rango = "Coordinador";
			if(PlayerInfo[playerid][pAdmin] == 3) Rango = "Admin";
			if(PlayerInfo[playerid][pAdmin] == 4) Rango = "Programador";
			if(PlayerInfo[playerid][pAdmin] > 4) Rango = "Admin";
			printf("ADMINLOG: (%s) %s dice: %s", Rango, pName(playerid), (result));
			format(string, sizeof(string), "* (%s) %s: %s", Rango, pName(playerid), (result));
			SendClientMessageToAll(AzulClaro,string);
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if (strcmp(cmd, "/kickall", true) ==0 )
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
					if(PlayerInfo[i][pAdmin] == 0)
					{
						TogglePlayerControllable(i,0);
						Kick(i);
						printf("ADMINLOG: %s ha expulsado a todos los jugadores.", pName(playerid));
						format(string,sizeof(string),"Administrador \"%s\" ha cerrado el servidor, por favor vuelve entrar en unos minutos.",pName(playerid));
						SendClientMessage(i,Amarillo,string);
					}
				}
			}
			SendClientMessage(playerid, AzulClaro, "* Todos los jugadores han sido desconectados.");
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	/*if (strcmp(cmd, "/saveall", true) ==0 )
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
            printf("Guardando posiciones...");
            for(new i; i < MAX_PLAYERS; i++)
            {
                if(IsPlayerConnected(i))
                {
                    SavePos(i);
                }
            }
            printf("Posiciones guardadas");
            printf("Guardando coches...");
            for(new i; i < TotalVeh; i++)
            {
                if (CarInfo[i][eliminado]==0) SaveCar(i);
            }
            printf("Posiciones guardadas");
			SendClientMessage(playerid, AzulClaro, "* Todos los jugadores han sido guardados.");
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}*/
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/getip", true) == 0)
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			new playersip[128];
	    	tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /getip [IdJugador/ParteDelNombre]"); return 1; }
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
			GetPlayerIp(player1,playersip,sizeof(playersip));
			//printf("ADMINLOG: %s ha mirado la ip de %s.", pName(playerid), pName(player1));
	 		format(string,sizeof(string),"* Jugador: \"%s\" - IP: \"%s\"",pName(player1),playersip);
			SendClientMessage(playerid,AzulClaro,string);
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/reportar", true) == 0)
	{
		new reported;
		tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /reportar [IdJugador/ParteDelNombre] [Razon]") &&
			SendClientMessage(playerid, Naranja, "Atencion: Para reportes largos usar el foro!");
			return 1;
		}
		if(!IsNumeric(tmp))
		reported = ReturnUser(tmp,reported);
	   	else reported = strval(tmp);

 		if(IsPlayerConnected(reported) && reported != INVALID_PLAYER_ID)
	 	{
			if(PlayerInfo[reported][pAdmin] >= 1)
			{ SendClientMessage(playerid,Rojo,"ERROR: No puedes reportar a un administrador!"); return 1; }
			if(playerid == reported)
			{ SendClientMessage(playerid,Rojo,"ERROR: No puedes reportarte ati mismo!"); return 1; }

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
				SendClientMessage(playerid, Blanco, "USO: /reportar [IdJugador/ParteDelNombre] [Razon]");
				SendClientMessage(playerid, Naranja, "Atencion: Para reportes largos usar el foro!"); 
				return 1; 
			}

			if(PlayerInfo[playerid][pReporting]==1)
			{
			    SendClientMessage(playerid,AzulClaro,"* Parece que ya reportaste algo, inténtalo dentro de 30 segundos.");
				return 1;
			}

			for(new reportid = 1; reportid < MAX_REPORTS; reportid++)
			{
			    if(Report[reportid][rState] == NOEXISTE)
			    {
					new hour,minute,second,year,month,day;
					gettime(hour,minute,second);
					getdate(year, month, day);
					new query[128];
					format(query, sizeof(query), "INSERT INTO `reportes` (`reportado`, `reportador`, `razon`, `fecha`) VALUES ('%s', '%s', '%s','%d:%d:%d | %d-%d-%d')", pNameEx(reported), pNameEx(playerid), (result),hour,minute,second,day,month,year);
					mysql_query(query);
					PlayerInfo[playerid][pReporting]=1;
					SetTimerEx("Reporting",30000,0,"i",playerid);
					Report[reportid][rState] = 1;
           			Report[reportid][rReporter] = playerid;
           			format(Report[reportid][rReporterName], 24, "%s", pName(playerid));
           			Report[reportid][rReported] = reported;
           			format(Report[reportid][rReportedName], 24, "%s", pName(reported));
           			format(Report[reportid][rDescription], 128, "%s", result);
           			format(Report[reportid][rTime], 24, "%d:%d:%d", hour,minute,second);
					SendClientMessage(playerid,Amarillo, "* Tu reporte ha sido enviado a los administradores!");
					format(string, sizeof(string), "REPORTE: %s(%d) ha reportado a %s(%d) - Hora: %d:%d:%d", pName(playerid),playerid, pName(reported), reported,hour,minute,second);
					ABroadCastOnDuty(Amarillo, string);
					format(string, sizeof(string), "Razon: %s", (result));
					ABroadCastOnDuty(Amarillo, string);
					return 1;
			   	}
			}
		}
		else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/reportes", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
 		{
			SendClientMessage(playerid, AzulClaro, "_______|- Reportes Actuales -|_______");
   		  	for(new reportid = 1; reportid < MAX_REPORTS; reportid++)
		    {
				if(Report[reportid][rState] > NOEXISTE)
				{
				    format(string, 128, "ID(%d) |- Reportador \"%s\" - Reportado \"%s\" - Hora: %s",reportid,Report[reportid][rReporterName], Report[reportid][rReportedName], Report[reportid][rTime]);
				    SendClientMessage(playerid, Blanco, string);
				}
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/verreporte", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			new id;
			id = strval(tmp);

	   		if(!strlen(tmp)) return
			SendClientMessage(playerid, Blanco, "USO: /verreporte [Reporte ID]");

			if(Report[id][rState] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Reporte inexistente! Usa /reportes"); return 1; }
		
		    format(string, 128, "REPORTE(%d): Reportador \"%s\" - Reportado \"%s\" - Hora: %s ",id, Report[id][rReporterName], Report[id][rReportedName], Report[id][rTime]);
			SendClientMessage(playerid, AzulClaro, string);
		    format(string, 128, "Razon: %s ",Report[id][rDescription]);
			SendClientMessage(playerid, AzulClaro, string);
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/borrarreporte", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			new id;
			id = strval(tmp);

	   		if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, Blanco, "USO: /borrarreporte [Reporte ID]");
				return 1;
			}
				
			if(Report[id][rState] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Reporte inexistente! Usa /reportes"); return 1; }

			Report[id][rState] = NOEXISTE;
		    format(string, 128, "* Has borrado el reporte numero '%d'",id);
			SendClientMessage(playerid, AzulClaro, string);
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
	//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/borrarreportes", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
 		{
			SendClientMessage(playerid, AzulClaro, "* Has borrado todos los reportes.");
   		  	for(new reportid = 1; reportid < MAX_REPORTS; reportid++)
		    {
				if(Report[reportid][rState] > NOEXISTE)
				{
					Report[reportid][rState] = NOEXISTE;
				}
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/duda", true) == 0 || strcmp(cmd, "/du", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
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
				SendClientMessage(playerid, Blanco, "USO: /duda [texto]");
				return 1;
			}
			if(PlayerInfo[playerid][pDudaid] == NOEXISTE)
			{
				for(new dudaid = 1; dudaid < MAX_DUDAS; dudaid++)
				{
				    if(Dudas[dudaid][dState] == NOEXISTE)
				    {
						PlayerInfo[playerid][pDudaid] = dudaid;
						Dudas[dudaid][dState] = 1;
				        Dudas[dudaid][dQuestioner] = playerid;
						format(Dudas[dudaid][dQuestionerName], 24, "%s", pName(playerid));
				        format(Dudas[dudaid][dQuestion], 128, "%s", result);
						format(string, sizeof(string), "Duda de %s(%d): %s. Para responderle: /rduda %d.", pName(playerid), playerid, (result), dudaid);
						ABroadCastOnDuty(Amarillo,string);
						SendClientMessage(playerid, Amarillo, "* Espera que algun Admin responda tu duda.");
						return 1;
					}
				}
			}
			else { SendClientMessage(playerid, Rojo, "ERROR: Ya tienes una duda enviada, espera a que te respondan."); }
		}
		return 1;
 	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/rduda", true) == 0)
 	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			new dudaid;
			dudaid = strval(tmp);

			if(!strlen(tmp) || dudaid == 0)
			{
			    SendClientMessage(playerid, Blanco, "USO: /rduda [ID Duda] [Respuesta]");
			    return 1;
			}

			if(Dudas[dudaid][dState] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Duda inexistente! Usa /dudas"); return 1; }

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
			if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /rduda [ID Duda] [Respuesta]"); return 1; }

	  		format(string, 128, "* Has respondido la Duda(%d) de \"%s\".", dudaid, pName(Dudas[dudaid][dQuestioner]));
			SendClientMessage(playerid, AzulClaro, string);
			format(string, 128, "Respuesta a tu Duda: %s", (result));
			SendClientMessage(Dudas[dudaid][dQuestioner], AzulClaro, string);

			new id = Dudas[dudaid][dQuestioner];
			
			Dudas[dudaid][dState] = NOEXISTE;
			PlayerInfo[id][pDudaid] = NOEXISTE;
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/dudas", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
 		{
			SendClientMessage(playerid, AzulClaro, "_______|- Dudas Actuales -|_______");
   		  	for(new dudaid = 1; dudaid < MAX_DUDAS; dudaid++)
		    {
				if(Dudas[dudaid][dState] > NOEXISTE)
			{
				    format(string, 128, "DUDA(%d) - %s(%d) - Pregunta: %s", dudaid, Dudas[dudaid][dQuestionerName], Dudas[dudaid][dQuestioner], Dudas[dudaid][dQuestion]);
				    SendClientMessage(playerid, Blanco, string);
				}
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
	if(strcmp(cmd, "/borrarduda", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			new id;
			id = strval(tmp);

	   		if(!strlen(tmp)) return
			SendClientMessage(playerid, Blanco, "USO: /borrarduda [Duda ID]");

			if(Dudas[id][dState] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Duda inexistente! Usa /dudas"); return 1; }

			Dudas[id][dState] = NOEXISTE;
		    format(string, 128, "* Has borrado la duda numero '%d'",id);
			SendClientMessage(playerid, AzulClaro, string);
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/borrardudas", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
 		{
			SendClientMessage(playerid, AzulClaro, "* Has borrado todas las dudas.");
   		  	for(new dudaid = 1; dudaid < MAX_DUDAS; dudaid++)
		    {
				if(Dudas[dudaid][dState] > NOEXISTE)
				{
					Dudas[dudaid][dState] = NOEXISTE;
				}
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/eject", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /eject [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1, Float:xxx, Float:yyy, Float:zzz;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				if(IsPlayerInAnyVehicle(player1))
				{
					if(player1 != playerid)
					{
					format(string,sizeof(string),"* Administrador \"%s\" te ha sacado de tu vehiculo", pName(playerid));
					SendClientMessage(player1,AzulClaro,string);
					}
					format(string,sizeof(string),"* Has sacado a \"%s\" de su vehiculo", pName(player1));
					SendClientMessage(playerid,AzulClaro,string);
					//printf("ADMINLOG: %s ha sacado a %s de su coche.", pName(playerid),pName(player1));
    			   	GetPlayerPos(player1,xxx,yyy,zzz);
					SetPlayerPos(player1,xxx,yyy,zzz+3);
				}
				else { SendClientMessage(playerid,Rojo,"ERROR: El jugador no esta en un vehiculo."); }
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/repair", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 2)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /repair [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				if(IsPlayerInAnyVehicle(player1))
				{
					if(player1 != playerid)
					{
					format(string,sizeof(string),"* Administrador \"%s\" te ha reparado tu vehiculo", pName(playerid));
					SendClientMessage(player1,AzulClaro,string);
					}
					format(string,sizeof(string),"* Has reparado a \"%s\" su vehiculo", pName(player1));
					SendClientMessage(playerid,AzulClaro,string);
					printf("ADMINLOG: %s ha reparado el coche de %s.", pName(playerid),pName(player1));
					RepairVehicle(GetPlayerVehicleID(player1));
					CarInfo[GetPlayerVehicle(player1)][cBroken] = 0;
					SaveCar(GetPlayerVehicle(player1));
				}
				else { SendClientMessage(playerid,Rojo,"ERROR: El jugador no esta en un vehiculo."); }
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if (strcmp(cmdtext, "/mark", true)==0)
	{
	    if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			GetPlayerPos(playerid, GosX[playerid], GosY[playerid], GosZ[playerid]);
			GetPlayerFacingAngle(playerid, GosA[playerid]);
			GosI[playerid] = (GetPlayerInterior(playerid));
			SendClientMessage(playerid, Amarillo, "* Posicion guardada! Usa /gotomark para volver!");
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if (strcmp(cmdtext, "/gotomark", true)==0)
	{
    	if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			if (!floatsqroot(GosX[playerid]+GosY[playerid]+GosZ[playerid]))
			{
				SendClientMessage(playerid, Rojo, "ERROR: Guarda una posicion primero! /mark!");
				return 1;
			}
			else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				SetVehiclePos(GetPlayerVehicleID(playerid), GosX[playerid], GosY[playerid], GosZ[playerid]);
				SetVehicleZAngle(GetPlayerVehicleID(playerid), GosA[playerid]);
   				SetCameraBehindPlayer(playerid);
				LinkVehicleToInterior(GetPlayerVehicleID(playerid), GosI[playerid]);
			}
			else
			{
			    SetPlayerPos(playerid, GosX[playerid], GosY[playerid], GosZ[playerid]);
			    SetPlayerFacingAngle(playerid, GosA[playerid]);
				SetCameraBehindPlayer(playerid);
			}
			SetPlayerInterior(playerid, GosI[playerid]);
			SendClientMessage(playerid, Amarillo, "* Has vuelto a tu posicion guardada!");
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/ajail", true) == 0)
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /ajail [IdJugador/ParteDelNombre] [tiempo] [razon]"); return 1; }
			
			new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
		   	else player1 = strval(tmp);
	   	
			new time;
			tmp = strtokex(cmdtext, idx);
			time = strval(tmp);
			if(!IsNumeric(tmp)) { SendClientMessage(playerid, Blanco, "USO: /ajail [IdJugador/ParteDelNombre] [tiempo] [razon]"); return 1; }

	        if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /ajail [IdJugador/ParteDelNombre] [tiempo] [razon]"); return 1; }
				format(string, sizeof(string), "\"%s\" ha sido encarcelado/a %d Minuto(s) por \"%s\"! Razon: %s", pName(player1), time, pName(playerid), (result));
				SendClientMessageToAll(Rojo, string);
				format(string, sizeof(string), "* Has encarcelado a \"%s\"(%d)", pName(player1),player1);
				SendClientMessage(playerid, AzulClaro, string);
				format(string, sizeof(string), "* Has sido encarcelado por \"%s\"", pName(playerid));
				SendClientMessage(player1, AzulClaro, string);
				new hour,minute,second,year,month,day;
				gettime(hour,minute,second);
				getdate(year, month, day);
				new query[1024];
				format(query, 1024, "INSERT INTO `ajails` (`ajaileado`, `ajailer`, `razon`, `tiempo`, `fecha`) VALUES ('%s','%s','%s',%d,'%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result), time, hour,minute,second,day,month,year);
				mysql_query(query);
				printf("ADMINLOG: %s ha jaileado a %s - Razon: %s.", pName(playerid),pName(player1),(result));
				PlayerInfo[player1][pJailed] = 2;
				PlayerInfo[player1][pJailTime] = time;
				SaveValues(playerid,"Encarcelado");
				SetTimerEx("JailPlayerOOC",100,0,"d",player1);
  			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/nobug", true) == 0)
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
	    	tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /nobug [IdJugador/ParteDelNombre]"); return 1; }

			new player1;
			player1 = strval(tmp);

	        if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
		    {
				format(string, sizeof(string), "* Has desbugueado a \"%s\".", pName(player1));
				SendClientMessage(playerid, AzulClaro, string);
				format(string, sizeof(string), "* Has sido desbugeado y enviado al ayuntamiento por \"%s\"", pName(playerid));
				SendClientMessage(player1, AzulClaro, string);
				printf("ADMINLOG: %s ha desbugeado a %s.", pName(playerid),pName(player1));
				SetPlayerInterior(player1, 0);
				SetPlayerVirtualWorld(player1, 0);
				GM_SetPlayerHealth(player1, 100);
				SetPlayerArmour(player1, 0);
				SetPlayerPos(player1, 1479.1301,-1742.1343,13.5469);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador inválido."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/ir", true) == 0)
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /ir [Nombre]");
				SendClientMessage(playerid, AzulClaro, "Teleports: LS, LV, SF, Autoescuela, TallerUnity, TallerCommerce, TallerSeville, TallerCorona");
				SendClientMessage(playerid, AzulClaro, "Inicio, Hospital, Barrendero, Basurero, Reporteros, Banco, Desguace, Noria, Ladron, Taxis");
				SendClientMessage(playerid, AzulClaro, "Ambulante, Peces, Granja, Camionero, Comisaria, Carcel, Cafeteria, Deposito");
				SendClientMessage(playerid, AzulClaro, "ConceBarato, ConceGentleman, ConceImportados, ConceDeportivos, ConceCamiones, ConceBarcos");
                SendClientMessage(playerid, AzulClaro, "ConceAviones, AngelPine, BlueBerry, MontGommery, PalominoCreek, Dillimore, Chilliad, ChilliadMedio");
				return 1;
			}
			if(strcmp(tmp,"LS",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1479.1301,-1742.1343,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1479.1301,-1742.1343,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'LS'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"SF",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), -2025.3699,170.4128,28.8359);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, -2025.3699,170.4128,28.8359);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'SF'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Inicio",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1216.1790,-1705.3472,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1216.1790,-1705.3472,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Inicio'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"TallerUnity",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1826.9290,-1888.5348,13.5331);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1826.9290,-1888.5348,13.5331);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Taller Unity'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"TallerCommerce",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1435.7506,-1648.9535,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1435.7506,-1648.9535,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Taller Commerce'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"TallerSeville",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2854.8625,-1575.5536,11.0938);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2854.8625,-1575.5536,11.0938);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Taller Seville'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"TallerCorona",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1636.4855,-2200.6226,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1636.4855,-2200.6226,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Taller Corona'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"ConceBarato",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2127.2224,-1105.6681,25.3363);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2127.2224,-1105.6681,25.3363);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario barato'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"ConceGentleman",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1320.8348,-1578.3765,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1320.8348,-1578.3765,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario Gentleman'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"ConceImportados",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2298.9897,-2375.3010,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2298.9897,-2375.3010,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario importados'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"ConceDeportivos",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 556.0988,-1269.8090,17.2422);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 556.0988,-1269.8090,17.2422);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario Deportivo'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"ConceCamiones",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 317.9112,-206.3972,1.4939);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 317.9112,-206.3972,1.4939);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario Camiones'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"ConceBarcos",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 702.5894,-1478.6523,5.4688);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 702.5894,-1478.6523,5.4688);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario Barcos'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"ConceAviones",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1954.0319,-2148.8406,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1954.0319,-2148.8406,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Concesionario Aviones'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Comisaria",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1523.6063,-1676.5245,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1523.6063,-1676.5245,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Comisaria'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Hospital",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1212.0164,-1323.9034,13.5591);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1212.0164,-1323.9034,13.5591);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Hospital'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Taxis",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2534.6797,-1499.0673,23.9980);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2534.6797,-1499.0673,23.9980);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Taxis'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Reporteros",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1841.0175,-1325.3533,13.5547);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1841.0175,-1325.3533,13.5547);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Reporteros'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Carcel",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1818.1708,-1572.6617,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1818.1708,-1572.6617,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Carcel'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Deposito",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), -490.4905,-561.9511,25.5234);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, -490.4905,-561.9511,25.5234);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Deposito'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Banco",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 589.3929,-1236.3790,17.8717);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 589.3929,-1236.3790,17.8717);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Banco'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Autoescuela",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1190.1178,-1464.6293,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1190.1178,-1464.6293,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Autoescuela'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Desguace",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), -100.1847,-1118.3927,1.4297);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, -100.1847,-1118.3927,1.4297);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Desguace'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Ambulante",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2487.4216,-1521.6116,23.9922);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2487.4216,-1521.6116,23.9922);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Ambulante'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Barrendero",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1629.6147,-1879.8452,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1629.6147,-1879.8452,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Barrendero'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Basurero",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2208.0381,-1981.8241,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2208.0381,-1981.8241,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Basurero'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Ladron",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2455.3308,-1975.2047,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2455.3308,-1975.2047,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Ladron'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"Granja",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 3.0274,75.3254,3.1172);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 3.0274,75.3254,3.1172);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Granja'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Camionero",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2205.9761,-2252.7847,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2205.9761,-2252.7847,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Camionero'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Noria",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 376.1023,-2032.9734,7.8301);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 376.1023,-2032.9734,7.8301);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Noria'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Peces",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2431.0349,-2453.3442,13.6250);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2431.0349,-2453.3442,13.6250);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Peces'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Muelles",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2911.6521,-787.5832,11.1995);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2911.6521,-787.5832,11.1995);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Peces'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Cafeteria",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1155.5519,-960.9357,42.7807);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1155.5519,-960.9357,42.7807);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Cafeteria'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Chicanos",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1884.8436,-2058.3650,13.5469);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1884.8436,-2058.3650,13.5469);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Chicanos'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Negros",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2707.8538,-2017.1968,13.5531);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2707.8538,-2017.1968,13.5531);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Negros'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"AngelPine",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), -2172.6885,-2398.4661,30.6250);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, -2172.6885,-2398.4661,30.6250);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Angel Pine'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"BlueBerry",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 227.1843,-179.4954,1.5781);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 227.1843,-179.4954,1.5781);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Blueberry'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"MontGommery",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 1310.3944,282.1730,19.5547);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 1310.3944,282.1730,19.5547);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'MontGommery'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"PalominoCreek",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2349.0889,62.0061,26.4844);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2349.0889,62.0061,26.4844);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Palomino Creek'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Dillmore",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 701.9221,-535.5767,16.3359);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 701.9221,-535.5767,16.3359);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Dillmore'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"Chilliad",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), -2316.7563,-1635.5719,483.7031);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, -2316.7563,-1635.5719,483.7031);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Chilliad'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}

			if(strcmp(tmp,"ChilliadMedio",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), -2796.6897,-1519.1058,139.2013);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, -2796.6897,-1519.1058,139.2013);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'Chilliad'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
			
			if(strcmp(tmp,"LV",true) == 0)
	    	{
	    		if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), 2035.6755,1344.6552,10.8203);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				}
				else
				{
					SetPlayerPos(playerid, 2035.6755,1344.6552,10.8203);
				}
				//printf("ADMINLOG: %s ha teletransportado a 'LV'", pName(playerid));
				SetPlayerInterior(playerid,0);
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
			}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
	
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/sethabilidad", true) == 0)
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /sethabilidad [IdJugador/ParteDelNombre] [codigo] [cantidad]");
				SendClientMessage(playerid, AzulClaro, "|1 Mecanico |2 Pescador |3 Ladron");
				return 1;
			}
			new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	   		
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
	    	{
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /sethabilidad [IdJugador/ParteDelNombre] [codigo] [cantidad]");
					SendClientMessage(playerid, AzulClaro, "|1 Mecanico |2 Pescador |3 Ladron");
					return 1;
				}
				new stat;
				stat = strval(tmp);
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /sethabilidad [IdJugador/ParteDelNombre] [codigo] [cantidad]");
					SendClientMessage(playerid, AzulClaro, "|1 Mecanico |2 Pescador |3 Ladron");
					return 1;
				}
				new amount;
				amount = strval(tmp);

				switch (stat)
				{
					case 1:
					{
						PlayerInfo[player1][pHabilidadMecanico] = amount;
						format(string, sizeof(string), "* Has ajustado a '%d' la habilidad de mecanico de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						SaveValues(player1, "Habilidades");
						printf("ADMINLOG: \"%s\" ha establecido la habilidad de mecanico de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 2:
					{
						PlayerInfo[player1][pHabilidadPescador] = amount;
						format(string, sizeof(string), "* Has ajustado a '%d' la habilidad de pescador de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						SaveValues(player1, "Habilidades");
						printf("ADMINLOG: \"%s\" ha establecido la habilidad de pescador de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 3:
					{
						PlayerInfo[player1][pHabilidadLadron] = amount;
						format(string, sizeof(string), "* Has ajustado a '%d' la habilidad de ladron de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						SaveValues(player1, "Habilidades");
						printf("ADMINLOG: \"%s\" ha establecido la habilidad de ladron de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					default:
					{
						SendClientMessage(playerid,Rojo,"* Codigo invalido!");
					}
				}
  			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/setstat", true) == 0)
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /setstat [IdJugador/ParteDelNombre] [codigo] [cantidad]");
				SendClientMessage(playerid, AzulClaro, "|1 Nivel |2 Respeto |3 Trabajo |4 Faccion |5 Dinero Banco");
				SendClientMessage(playerid, AzulClaro, "|6 Llave casa |7 Skin |8 Hambre |9 Advertencias");			
				return 1;
			}
			
    		new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	   		
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
	    	{
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /setstat [IdJugador/ParteDelNombre] [codigo] [cantidad]");
					SendClientMessage(playerid, AzulClaro, "|1 Nivel |2 Respeto |3 Trabajo |4 Faccion |5 Dinero Banco");
					SendClientMessage(playerid, AzulClaro, "|6 Llave casa |7 Skin |8 Hambre |9 Advertencias");						
					return 1;
				}
				new stat;
				stat = strval(tmp);
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /setstat [IdJugador/ParteDelNombre] [codigo] [cantidad]");
					SendClientMessage(playerid, AzulClaro, "|1 Nivel |2 Respeto |3 Trabajo |4 Faccion |5 Dinero Banco");
					SendClientMessage(playerid, AzulClaro, "|6 Llave casa |7 Skin |8 Hambre |9 Advertencias");			
					return 1;
				}
				new amount;
				amount = strval(tmp);

				switch (stat)
				{
					case 1:
					{
						SetPlayerLevel(player1,amount);
						format(string, sizeof(string), "* Has ajustado a '%d' el nivel de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						SaveValue(player1, "Respeto", PlayerInfo[player1][pRespeto]);
						SetPlayerScore(player1, GetPlayerLevel(player1)); 
						printf("ADMINLOG: \"%s\" ha establecido el nivel de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 2:
					{
						PlayerInfo[player1][pRespeto] = amount;
						format(string, sizeof(string), "* Has ajustado a '%d' el respeto de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						SaveValue(player1, "Respeto", PlayerInfo[player1][pRespeto]);
						SetPlayerScore(player1, GetPlayerLevel(player1)); 
						printf("ADMINLOG: \"%s\" ha establecido el respeto de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 3:
					{
						PlayerInfo[player1][pJob] = amount;
						SaveValue(player1, "Trabajo", PlayerInfo[player1][pJob]);
						format(string, sizeof(string), "* Has ajustado a '%d' el trabajo de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido el trabajo de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 4:
					{
						PlayerInfo[player1][pMember] = amount;
						SaveValue(player1, "Faccion", PlayerInfo[player1][pMember]);
						format(string, sizeof(string), "* Has ajustado a '%d' la faccion de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido la faccion de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 5:
					{
						PlayerInfo[player1][pBank] = amount;
						SaveValue(player1, "Banco", PlayerInfo[player1][pBank]);
						format(string, sizeof(string), "* Has ajustado a '%d' el dinero del banco de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido el dinero del banco de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 6:
					{
						PlayerInfo[player1][pPhousekey] = amount;
						SaveValue(player1, "Casa", PlayerInfo[player1][pPhousekey]);
						format(string, sizeof(string), "* Has ajustado a '%d' la llave de casa de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido la llave de casa de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 7:
					{
						if(amount > 300) return 1;
						PlayerInfo[player1][pSkin] = amount;
						SaveValue(player1, "Skin", PlayerInfo[player1][pSkin]);
						SetPlayerSkin(player1, PlayerInfo[player1][pSkin]);
						format(string, sizeof(string), "* Has ajustado a '%d' el skin de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido el skin de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 8:
					{
						PlayerInfo[player1][pHambre] = amount;
						SaveValue(player1, "Hambre", PlayerInfo[player1][pHambre]);
						ComprobarBarrita(player1);
						format(string, sizeof(string), "* Has ajustado a '%d' el hambre de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido el hambre de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					case 9:
					{
						PlayerInfo[player1][pAdvertencias] = amount;
						SaveValue(player1, "Advertencias", PlayerInfo[player1][pAdvertencias]);
						format(string, sizeof(string), "* Has ajustado a '%d' las advertencias de \"%s\"", amount,pName(player1));
						SendClientMessage(playerid,AzulClaro,string);
						printf("ADMINLOG: \"%s\" ha establecido las advertencias de \"%s\" a '%d'.", pName(playerid),pName(player1),amount);
					}
					default:
					{
						SendClientMessage(playerid,Rojo,"* Codigo invalido!");
					}
				}
  			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/advertir", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /advertir [IdJugador/ParteDelNombre] [Razon]"); return 1; }
			new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
			else player1 = strval(tmp);
			if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID && player1 != playerid)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /advertir [IdJugador/ParteDelNombre] [Razon]"); return 1; }
				if(PlayerInfo[player1][pAdmin] >= 1) { SendClientMessage(playerid, Rojo, "* No puedes advertir a un administrador."); return 1; }
				new hour,minute,second,year,month,day;
				gettime(hour,minute,second);
				getdate(year, month, day);
				new query[128];
				if(PlayerInfo[player1][pAdvertencias] == 0)
				{
					format(query, sizeof(query), "INSERT INTO `advertirs` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', '(1/5) %s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
					mysql_query(query);
					printf("ADMINLOG: %s advierte a %s (1/5) - Razon: %s",pName(playerid), pName(player1), (result));
					format(string, sizeof(string), "\"%s\" ha sido advertido por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
					SendClientMessageToAll(Rojo,string);
					format(string, sizeof(string), "* Has advertido a \"%s\". (1/5).", pName(player1));
					SendClientMessage(playerid,AzulClaro, string);
					ClearChatbox(player1,20);
					format(string, sizeof(string), "* Has sido advertido por \"%s\". (1/5) La próxima vez que seas advertido, serás kickeado.", pName(playerid));
					SendClientMessage(player1,Rojo, string);
					format(string, sizeof(string), "* Castigo: Aviso - Razón: %s", (result));
					SendClientMessage(player1,Rojo, string);
					PlayerInfo[player1][pAdvertencias] = 1;
					SaveValue(player1, "Advertencias", PlayerInfo[player1][pAdvertencias]);
				}
				if(PlayerInfo[player1][pAdvertencias] == 1)
				{
					format(query, sizeof(query), "INSERT INTO `advertirs` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', '(2/5) %s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
					mysql_query(query);
					printf("ADMINLOG: %s advierte a %s (2/5) - Razon: %s",pName(playerid), pName(player1), (result));
					format(string, sizeof(string), "\"%s\" ha sido advertido por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
					SendClientMessageToAll(Rojo,string);
					format(string, sizeof(string), "* Has advertido a \"%s\". (2/5) El jugador ha sido kickeado.", pName(player1));
					SendClientMessage(playerid,AzulClaro, string);
					ClearChatbox(player1,20);
					format(string, sizeof(string), "* Has sido advertido por \"%s\". (2/5) La próxima vez que seas advertido, serás encarcelado.", pName(playerid));
					SendClientMessage(player1,Rojo, string);
					format(string, sizeof(string), "* Castigo: Kick - Razón: %s", (result));
					SendClientMessage(player1,Rojo, string);
					PlayerInfo[player1][pAdvertencias] = 2;
					SaveValue(player1, "Advertencias", PlayerInfo[player1][pAdvertencias]);
					TogglePlayerControllable(player1,0);
					Kick(player1);
				}
				else if(PlayerInfo[player1][pAdvertencias] == 2)
				{
					format(query, sizeof(query), "INSERT INTO `advertirs` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', '(3/5) %s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
					mysql_query(query);
					printf("ADMINLOG: %s advierte a %s (3/5) - Razon: %s",pName(playerid), pName(player1), (result));
					format(string, sizeof(string), "\"%s\" ha sido advertido por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
					SendClientMessageToAll(Rojo,string);
					format(string, sizeof(string), "* Has advertido a \"%s\". (3/5) El jugador ha sido kickeado.", pName(player1));
					SendClientMessage(playerid,AzulClaro, string);
					ClearChatbox(player1,20);
					format(string, sizeof(string), "* Has sido advertido por \"%s\". (3/5) La próxima vez que seas advertido, serás reeducado.", pName(playerid));
					SendClientMessage(player1,Rojo, string);
					format(string, sizeof(string), "* Castigo: Encarcelamiento por 10 minutos - Razón: %s", (result));
					SendClientMessage(player1,Rojo, string);
					PlayerInfo[player1][pAdvertencias] = 3;
					SaveValue(player1, "Advertencias", PlayerInfo[player1][pAdvertencias]);
					format(string, sizeof(string), "/ajail %d 10 <Sanción automática por 3era advertencia>", player1);
					Admin_OnPlayerCommandText(playerid, string);
				}
				else if(PlayerInfo[player1][pAdvertencias] == 3)
				{
					format(query, sizeof(query), "INSERT INTO `advertirs` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', '(4/5) %s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
					mysql_query(query);
					printf("ADMINLOG: %s advierte a %s (4/5) - Razon: %s",pName(playerid), pName(player1), (result));
					format(string, sizeof(string), "\"%s\" ha sido advertido por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
					SendClientMessageToAll(Rojo,string);
					format(string, sizeof(string), "* Has advertido a \"%s\". (4/5) El jugador ha sido reeducado.", pName(player1));
					SendClientMessage(playerid,AzulClaro, string);
					ClearChatbox(player1,20);
					format(string, sizeof(string), "* Has sido advertido por \"%s\". (4/5) La próxima vez que seas advertido, tu cuenta será bloqueada.", pName(playerid));
					SendClientMessage(player1,Rojo, string);
					format(string, sizeof(string), "* Castigo: Reeducar - Razón: %s", (result));
					SendClientMessage(player1,Rojo, string);
					PlayerInfo[player1][pAdvertencias] = 4;
					SaveValue(player1, "Advertencias", PlayerInfo[player1][pAdvertencias]);
					SaveValue(player1, "Certificacion", 2);
					TogglePlayerControllable(player1,0);
					Kick(player1);
				}
				else if(PlayerInfo[player1][pAdvertencias] >= 4)
				{
					format(query, sizeof(query), "INSERT INTO `advertirs` (`kickeado`, `kicker`, `razon`, `fecha`) VALUES ('%s', '%s', '(5/5) %s','%d:%d:%d | %d-%d-%d')", pNameEx(player1), pNameEx(playerid), (result),hour,minute,second,day,month,year);
					mysql_query(query);
					printf("ADMINLOG: %s advierte a %s (5/5) - Razon: %s",pName(playerid), pName(player1), (result));
					format(string, sizeof(string), "\"%s\" ha sido advertido por \"%s\". Razón: %s", pName(player1), pName(playerid), (result));
					SendClientMessageToAll(Rojo,string);
					format(string, sizeof(string), "* Has advertido a \"%s\". (5/5) La cuenta del jugador ha sido bloqueada.", pName(player1));
					SendClientMessage(playerid,AzulClaro, string);
					ClearChatbox(player1,20);
					format(string, sizeof(string), "* Has sido advertido por \"%s\". (5/5) Tus oportunidades se han agotado.", pName(playerid));
					SendClientMessage(player1,Rojo, string);
					format(string, sizeof(string), "* Castigo: Bloqueo de cuenta - Razón: %s", (result));
					SendClientMessage(player1,Rojo, string);
					SaveValue(player1, "Bloqueado", 1);
					TogglePlayerControllable(player1,0);
					Kick(player1);
				}
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado o eres tu mismo."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/privados", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			if(PlayerInfo[playerid][pHidePms] == 0){ PlayerInfo[playerid][pHidePms] = 1; SendClientMessage(playerid,AzulClaro,"* Has desactivado los privados!");} 
			else if(PlayerInfo[playerid][pHidePms] == 1){ PlayerInfo[playerid][pHidePms] = 0; SendClientMessage(playerid,AzulClaro,"* Has activado los privados!");} 
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/pms", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			if(PlayerInfo[playerid][pBigEars] == 0){ PlayerInfo[playerid][pBigEars] = 1; SendClientMessage(playerid,AzulClaro,"* Ahora lees todos los privados!");}
			else if(PlayerInfo[playerid][pBigEars] == 1){ PlayerInfo[playerid][pBigEars] = 0; SendClientMessage(playerid,AzulClaro,"* Has dejado de leer todos los privados!");}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/versms", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			if(PlayerInfo[playerid][pBigAntena] == 0){ PlayerInfo[playerid][pBigAntena] = 1; SendClientMessage(playerid,AzulClaro,"* Ahora lees todos los sms!");}
			else if(PlayerInfo[playerid][pBigAntena] == 1){ PlayerInfo[playerid][pBigAntena] = 0; SendClientMessage(playerid,AzulClaro,"* Has dejado de leer todos los sms!");}
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/check", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /check [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				//printf("ADMINLOG: %s ha mirado las estadisticas de %s",pName(playerid), pName(player1));
				GetPlayerStats(player1,playerid);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/verpremium", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /verpremium [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				VerPremium(player1,playerid);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/verinventario", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    tmp = strtokex(cmdtext, idx);
	    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /verinventario [IdJugador/ParteDelNombre]"); return 1; }
	    	new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
	   		else player1 = strval(tmp);
	 		if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				//printf("ADMINLOG: %s ha mirado el inventario de %s",pName(playerid), pName(player1));
				MostrarInventario(player1,playerid);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/verllaves", true) == 0)
	{
	    tmp = strtokex(cmdtext, idx);
    	if(!strlen(tmp)) {	MostrarLlaves(playerid,playerid); return 1; }
    	new player1;
		if(!IsNumeric(tmp))
		player1 = ReturnUser(tmp,playerid);
   		else player1 = strval(tmp);
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				//printf("ADMINLOG: %s ha mirado las llaves de %s",pName(playerid), pName(player1));
				MostrarLlaves(player1,playerid);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado."); }
		}
		else { SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!"); }
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
/*	if(strcmp(cmd, "/debugpinfo", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] == 4)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /debugpinfo [IdJugador/ParteDelNombre] [pValue]");
			new player1;
			if(!IsNumeric(tmp))
			player1 = ReturnUser(tmp,playerid);
			else player1 = strval(tmp);
			tmp = strtokex(cmdtext, idx);
			new pValue[24];
			pValue = strval(tmp); // error 033: array must be indexed (variable "pValue")
			if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
			{
				new pValueRes[128];
				pValueRes = PlayerInfo[player1][pValue]; //  error 033: array must be indexed (variable "pValue") &&  (variable "pValueRes")
				format(string,sizeof(string),"Player: '%s'  -  [%s] = %s",pName(player1),pValue,pValueRes);
				{ SendClientMessage(playerid, Naranja, string);
			}
			else { SendClientMessage(playerid,Rojo,"ERROR: Jugador no conectado.");
		}
		else { SendClientMessage(playerid,Rojo,"* No eres programador!");
	}*/
	
	if(strcmp(cmd, "/givegun", true) == 0)//Testing porpouses
	{
	    if(IsPlayerConnected(playerid))
	    {
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /givegun [IdJugador/ParteDelNombre] [weaponid] [ammo]");
				SendClientMessage(playerid, AzulClaro, "3(Club) 4(knife) 5(bat) 6(Shovel) 7(Cue) 8(Katana) 10-13(Dildo) 14(Flowers) 16(Grenades) 18(Molotovs) 22(Pistol) 23(SPistol)");
				SendClientMessage(playerid, AzulClaro, "24(Eagle) 25(shotstring) 29(MP5) 30(AK47) 31(M4) 33(Rifle) 34(Sniper) 37(Flamethrower) 41(spray) 42(exting) 43(Camera) 46(Parachute)");
				return 1;
			}
			new playa;
			new gun;
			new ammo;
			playa = ReturnUser(tmp);
			if(!IsPlayerConnected(playa)){ SendClientMessage(playerid, Rojo, "* Jugador no conectado"); return 1; }
			tmp = strtokex(cmdtext, idx);
			gun = strval(tmp);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /givegun [IdJugador/ParteDelNombre] [weaponid] [ammo]");
				SendClientMessage(playerid, AzulClaro, "3(Club) 4(knife) 5(bat) 6(Shovel) 7(Cue) 8(Katana) 10-13(Dildo) 14(Flowers) 16(Grenades) 18(Molotovs) 22(Pistol) 23(SPistol)");
				SendClientMessage(playerid, AzulClaro, "24(Eagle) 25(shotstring) 29(MP5) 30(AK47) 31(M4) 33(Rifle) 34(Sniper) 37(Flamethrower) 41(spray) 42(exting) 43(Camera) 46(Parachute)");
				return 1;
			}
			if(gun < 1||gun > 46)
			{ SendClientMessage(playerid, Rojo, "ERROR: WeaponID invalida!"); return 1; }
			tmp = strtokex(cmdtext, idx);
			ammo = strval(tmp);
			if(ammo <1||ammo > 999)
			{ SendClientMessage(playerid, Rojo, "ERROR: La municion debe estar entre 1 y 999 balas!"); return 1; }
			if (PlayerInfo[playerid][pAdmin] >= 3)
			{
			    if(IsPlayerConnected(playa))
			    {
			        if(playa != INVALID_PLAYER_ID)
			        {
						SafeGivePlayerWeapon(playa, gun, ammo);
						new hour,minute,second,year,month,day,gunname[30];
						GetWeaponName(gun,gunname,sizeof(gunname));
						gettime(hour,minute,second);
						getdate(year, month, day);
						new query[128];
						format(query, sizeof(query), "INSERT INTO `logarmas` (`Emisor`, `Receptor`, `Desc`, `Fecha`) VALUES ('Admin', '%s', '/givegun | %s | %d','%d:%d:%d | %d-%d-%d')", pNameEx(playerid), gunname, ammo,hour,minute,second,day,month,year);
						mysql_query(query);
					}
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
			}
		}
		return 1;
	}
	if(strcmp(cmd, "/atach", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 1;
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new t11 = strval(tmp); //slot
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new t0 = strval(tmp); //modelid
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new t1 = strval(tmp); //bone
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new Float:t2 = floatstr(tmp); //fX
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new Float:t3 = floatstr(tmp); //fY
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new Float:t4 = floatstr(tmp); //fZ
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new Float:t5 = floatstr(tmp); //fRotX
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new Float:t6 = floatstr(tmp); //fRotY
        tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /(q)atach [slot] [modelid] [bone] [fX] [fY] [fZ] [fRotX] [fRotY] [fRotZ] [(fScaleX)] [(fScaleY)] [(fScaleZ)] [(PlayerID)]");
			return 1;
		}
		new Float:t7 = floatstr(tmp); //fRotZ
        tmp = strtokex(cmdtext, idx);
		new Float:t8; //fScaleX
		if(!strlen(tmp)) t8 = 1.0; 
		else t8 = floatstr(tmp);
        tmp = strtokex(cmdtext, idx);
		new Float:t9; //fScaleY
		if(!strlen(tmp)) t9 = 1.0; 
		else t9 = floatstr(tmp);
        tmp = strtokex(cmdtext, idx);
		new Float:t10; //fScaleZ
		if(!strlen(tmp)) t10 = 1.0; 
		else t10 = floatstr(tmp);
		new t12; //PlayerID
		if(!strlen(tmp)) t12 = playerid; 
		else t12 = strval(tmp);
        SetPlayerAttachedObject(t12,t11,t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10);
        return 1;
	}
	if(strcmp(cmd, "/qatach", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 1;
		tmp = strtokex(cmdtext, idx);
		new slot = strval(tmp);
		if(!strlen(tmp) || slot < 0 || slot > 4)
		{
			SendClientMessage(playerid, Blanco, "USO: /qatach [slot] [(PlayerID)]");
			return 1;
		}
		new t12;
		if(!strlen(tmp)) t12 = playerid; 
		else t12 = strval(tmp);	
		RemovePlayerAttachedObject(t12,slot);
        return 1;
	}	
	if(strcmp(cmd, "/rcmd", true) == 0)
	{
	    tmp = strtokex(cmdtext, idx);
    	if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /rcmd [IdJugador/ParteDelNombre] [Command]");
			SendClientMessage(playerid, Blanco, "Utilizar como ultimo recurso ante problemas.");
			return 1;
		}
    	new player1;
		if(!IsNumeric(tmp))
		player1 = ReturnUser(tmp,playerid);
   		else player1 = strval(tmp);
		
		if(PlayerInfo[playerid][pAdmin] >= 3)
		{
		    if(IsPlayerConnected(player1) && player1 != INVALID_PLAYER_ID)
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
				if(!strlen(result)) { SendClientMessage(playerid, Blanco, "USO: /rcmd [IdJugador/ParteDelNombre] [Command]"); return 1; }

				printf("ADMINLOG: %s rcmd sobre %s - \"%s\"",pName(playerid), pName(player1), (result));
				OnPlayerCommandText(player1, result);
			}
		}
		else 
		{
			SendClientMessage(playerid,Rojo,"* No eres miembro del Staff!");
		}
		return 1;
	}
	return 0;
}

//----------------------------------[RECON SYSTEM  -  INICIO]----------------------------------------------------
stock StartSpectate(playerid, specplayerid)
{
	for(new x=0; x<MAX_PLAYERS; x++)
	{
	    if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] == playerid)
		{
  	     AdvanceSpectate(x);
		}
	}
	TogglePlayerSpectating(playerid, 1);

	if(IsPlayerInAnyVehicle(specplayerid))
	{
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(specplayerid));
		PlayerInfo[playerid][SpecID] = specplayerid;
		PlayerInfo[playerid][SpecType] = ADMIN_SPEC_TYPE_VEHICLE;
	}
	else
	{
		PlayerSpectatePlayer(playerid, specplayerid);
		PlayerInfo[playerid][SpecID] = specplayerid;
		PlayerInfo[playerid][SpecType] = ADMIN_SPEC_TYPE_PLAYER;
	}
	SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(specplayerid));
	SetPlayerInterior(playerid,GetPlayerInterior(specplayerid));

	new Float:hp, Float:ar;
	GetPlayerHealth(specplayerid, hp);
	GetPlayerArmour(specplayerid, ar);
	
	format(string,sizeof(string),"~w~- %s(%d) -~n~~n~~y~Vida: ~w~%0.1f ~l~- ~y~Armadura: ~w~%0.1f ~l~- ~y~Dinero: ~w~$%d~n~~n~~r~< Correr - Saltar >", pName(specplayerid),specplayerid,hp,ar,SafeGetPlayerMoney(specplayerid));
	TextDrawSetString(ReconTD[playerid], string);
	TextDrawShowForPlayer(playerid,ReconTD[playerid]);
}

stock StopSpectate(playerid)
{
	TogglePlayerSpectating(playerid, 0);
	PlayerInfo[playerid][SpecID] = INVALID_PLAYER_ID;
	PlayerInfo[playerid][SpecType] = ADMIN_SPEC_TYPE_NONE;
	for(new x=0; x<MAX_PLAYERS; x++) TextDrawHideForPlayer(playerid,ReconTD[x]);
	return 1;
}

stock AdvanceSpectate(playerid)
{
    if(ConnectedPlayers() == 2) { StopSpectate(playerid); return 1; }
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && PlayerInfo[playerid][SpecID] != INVALID_PLAYER_ID)
	{
	    for(new x=PlayerInfo[playerid][SpecID]+1; x<=MAX_PLAYERS; x++)
		{
	    	if(x == MAX_PLAYERS) x = 0;
	        if(IsPlayerConnected(x) && x != playerid)
			{
				if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] != INVALID_PLAYER_ID || (GetPlayerState(x) != 1 && GetPlayerState(x) != 2 && GetPlayerState(x) != 3))
				{
					continue;
				}
				else
				{
					StartSpectate(playerid, x);
					break;
				}
			}
		}
	}
	return 1;
}

stock ReverseSpectate(playerid)
{
    if(ConnectedPlayers() == 2) { StopSpectate(playerid); return 1; }
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && PlayerInfo[playerid][SpecID] != INVALID_PLAYER_ID)
	{
	    for(new x=PlayerInfo[playerid][SpecID]-1; x>=0; x--)
		{
	    	if(x == 0) x = MAX_PLAYERS;
	        if(IsPlayerConnected(x) && x != playerid)
			{
				if(GetPlayerState(x) == PLAYER_STATE_SPECTATING && PlayerInfo[x][SpecID] != INVALID_PLAYER_ID || (GetPlayerState(x) != 1 && GetPlayerState(x) != 2 && GetPlayerState(x) != 3))
				{
					continue;
				}
				else
				{
					StartSpectate(playerid, x);
					break;
				}
			}
		}
	}
	return 1;
}

stock ReconTextDraws()
{
	for(new l=0; l<130; l++)
	{
	GpsTD[l] = TextDrawCreate(326.000000, 362.000000, " ");
	TextDrawAlignment(GpsTD[l], 2);
	TextDrawBackgroundColor(GpsTD[l], 255);
	TextDrawFont(GpsTD[l], 1);
	TextDrawLetterSize(GpsTD[l], 0.300000, 1.100000);
	TextDrawColor(GpsTD[l], -1587871574);
	TextDrawSetOutline(GpsTD[l], 0);
	TextDrawSetProportional(GpsTD[l], 1);
	TextDrawSetShadow(GpsTD[l], 1);
	}
	return 1;
}

forward ReturnPosition(playerid);
public ReturnPosition(playerid)
{
	TogglePlayerControllable(playerid, 1);
	SetPlayerPos(playerid,RecPos[playerid][0],RecPos[playerid][1],RecPos[playerid][2]);
	SetPlayerFacingAngle(playerid,RecPos[playerid][3]);
	SetPlayerInterior(playerid,IntRec[playerid]);
	SetPlayerVirtualWorld(playerid,VwRec[playerid]);
	PlayerPlaySound(playerid,1137,0.0,0.0,0.0);
}

stock ConnectedPlayers()
{
	new Connected;
	for(new i = 0; i < MAX_PLAYERS; i++)
	if(IsPlayerConnected(i))
	Connected++;
	return Connected;
}
//----------------------------------[RECON SYSTEM  -  FIN]----------------------------------------------------

//REPORT SYSTEM
forward Reporting(playerid);
public Reporting(playerid)
{
//	SendClientMessage(playerid,COLOR_LIGHTBLUE,"Ya puedes volver a reportar!");
	PlayerInfo[playerid][pReporting]=0;
	return 1;
}

//JAIL SYSTEM
forward JailPlayerOOC(player1);
public JailPlayerOOC(player1)
{
	SafeResetPlayerWeaponsAC(player1);
	SetPlayerInterior(player1, 18); // antiguo interior 3
	SetPlayerPos(player1,-219.5259,1409.8380,27.7734); // antiguas coords 198.4886,162.1866,1003.0300
	SetCameraBehindPlayer(player1);
	format(string, sizeof(string), "* Estas encarcelado por %d minuto(s). Usa /reloj para ver el tiempo restante.", PlayerInfo[player1][pJailTime]);
	SendClientMessage(player1, Amarillo, string);
}
UnjailPlayerOOC(player1)
{
	PlayerInfo[player1][pJailTime] = 0;
	PlayerInfo[player1][pJailed] = 0;
	SetPlayerInterior(player1,0);
	SetPlayerPosEx(player1, 1479.1301,-1742.1343,13.5469);
	SetCameraBehindPlayer(player1);
	PlayerPlaySound(player1,1057,0.0,0.0,0.0);
	SaveValues(player1,"Encarcelado");
	SendClientMessage(player1, AzulClaro, "* Tu Jail OOC ha acabado, esperemos que te haya servido de algo. Vuelves a ser libre!");
}
