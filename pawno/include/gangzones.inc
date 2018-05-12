/* 
   Old School v2 "The future is here"
   - - - - - - - - - - - - - - - - - -
		DEATH GOP GORTHOL DESK
   - - - - - - - - - - - - - - - - - -
*/

#include <a_samp>

#undef MAX_GANG_ZONES
#define MAX_GANG_ZONES (50)

// GangZone Colors
#define GBLACK                 	0x000000C7
#define GWHITE                 	0xFFFFFFBE
#define GORANGE                 0xFF8000B8
#define GRED	                0xFF0000C7
#define GBLUE                   0x0000FFC5
#define GVIOLET                 0x8000FFC9
#define GGREEN                  0x00FF00D0
#define GYELLOW                 0xFFFF00CC
#define GPINK                   0xFF80FFC7
#define GSEABLUE                0x5BB9E6CA
#define GBROWN                  0x562C2CD2

enum gInfo
{
	gId,
	gZone,
	gColor,
	gType, // 0 - To GANGS | 1- To COPS
	Float:gMinX,
	Float:gMinY,
	Float:gMaxX,
	Float:gMaxY,
	gEliminado,
}

new GangZone[MAX_GANG_ZONES][gInfo];
new TotalGangs;
new TempGangZone=NOEXISTE, TempGangColor, TempGangType, Float: pMaxX = 0.0, Float: pMaxY = 0.0, Float: pMinX = 0.0, Float: pMinY = 0.0, Float: pZ = 0.0;
new bool:BuildingGangZone[MAX_PLAYERS]=false, bool:GetPos[MAX_PLAYERS];

LoadGangZones()
{
	for(new i; i < MAX_GANG_ZONES; i++)
	{
		GangZone[i][gZone] = NOEXISTE;
	}

	new sql[80], row[512], count, seliminado;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM gangzones");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	count = strval(row);
	
	for (new i; i<=count; i++)
	{
		format(sql, sizeof(sql), "SELECT * FROM gangzones WHERE id=%d LIMIT 1", i);
	    mysql_query(sql);
	    mysql_store_result();
     	mysql_fetch_row(row);
		split(row, arrCoords, '|');
		seliminado = strval(arrCoords[7]);
		if(seliminado == 0)
		{
			GangZone[TotalGangs][gId] = strval(arrCoords[0]);
			GangZone[TotalGangs][gColor] = strval(arrCoords[1]);
			GangZone[TotalGangs][gType] = strval(arrCoords[2]);
			GangZone[TotalGangs][gMinX] = floatstr(arrCoords[3]);
			GangZone[TotalGangs][gMinY] = floatstr(arrCoords[4]);
			GangZone[TotalGangs][gMaxX] = floatstr(arrCoords[5]);
			GangZone[TotalGangs][gMaxY] = floatstr(arrCoords[6]);
			GangZone[TotalGangs][gEliminado] = 0;
			GangZone[TotalGangs][gZone] = GangZoneCreate(GangZone[TotalGangs][gMinX],GangZone[TotalGangs][gMinY],GangZone[TotalGangs][gMaxX],GangZone[TotalGangs][gMaxY]);
			//printf("forid: %d - sqlid:%d - arrayid: %d gang zone cargada",i,GangZone[TotalGangs][gId],TotalGangs);
			TotalGangs++;
		}
	}
	mysql_free_result();
	printf("GangZones cargadas: %d (MAX: %d)", TotalGangs, MAX_GANG_ZONES);
}

SaveGangZone(GangID)
{
	new garrayid = GetGangArrayBySQLID(GangID);
	new sql[512];
	format(sql, sizeof(sql), "UPDATE gangzones SET Color=%d,Type=%d,MinX=%f,MinY=%f,MaxX=%f,MaxY=%f,Eliminado=%d WHERE id=%d",
		GangZone[garrayid][gColor],
		GangZone[garrayid][gType],
		GangZone[garrayid][gMinX],
		GangZone[garrayid][gMinY],
		GangZone[garrayid][gMaxX],
		GangZone[garrayid][gMaxY],
		GangZone[garrayid][gEliminado],
		GangZone[garrayid][gId]);
	mysql_query(sql);
	//print(sql);
	return 1;
}

NewGangZone(color,type,Float:gminx,Float:gminy,Float:gmaxx,Float:gmaxy)
{
	format(string, 128, "INSERT INTO gangzones (Type) VALUES (-1)");
	mysql_query(string);
	//print(string);
	
	new row[64];
	format(string, 128, "SELECT id FROM gangzones WHERE Type = -1");
	mysql_query(string);
	mysql_store_result();
	mysql_fetch_row(row);
	new SQLID = strval(row);
	mysql_free_result();
	GangZone[TotalGangs][gId] = SQLID;
	GangZone[TotalGangs][gColor] = color;
	GangZone[TotalGangs][gType] = type;
	GangZone[TotalGangs][gMinX] = gminx;
	GangZone[TotalGangs][gMinY] = gminy;
	GangZone[TotalGangs][gMaxX] = gmaxx;
	GangZone[TotalGangs][gMaxY] = gmaxy;
	GangZone[TotalGangs][gEliminado] = 0;
	SaveGangZone(GangZone[TotalGangs][gId]);
	GangZone[TotalGangs][gZone] = GangZoneCreate(gminx,gminy,gmaxx,gmaxy);
	ShowGangZoneToPlayers(GangZone[TotalGangs][gZone]);
	TotalGangs++;
	return SQLID;
}

stock GetGangZoneColor(colorid)
{
	switch(colorid)
	{
	   	case 1:
    	{
			return GBLACK;
		}
	   	case 2:
    	{
			return GWHITE;
		}
	   	case 3:
    	{
			return GORANGE;
		}
	   	case 4:
    	{
			return GRED;
		}
	   	case 5:
    	{
			return GBLUE;
		}
	   	case 6:
    	{
			return GVIOLET;
		}
	   	case 7:
    	{
			return GGREEN;
		}
	   	case 8:
    	{
			return GYELLOW;
		}
	   	case 9:
    	{
			return GSEABLUE;
		}
	   	case 10:
    	{
			return GBROWN;
		}
	}
	return GWHITE;
}
stock ShowGangsZonesToPlayers()
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(PlayerInfo[i][pMember] > 10 && PlayerInfo[i][pMember] < 21)
		{
			for(new gi; gi < TotalGangs; gi++)
			{
				if(GangZone[gi][gType] == 0 && GangZone[gi][gZone] != NOEXISTE) GangZoneShowForPlayer(i,GangZone[gi][gZone],GetGangZoneColor(GangZone[gi][gColor]));
			}
		}
		if(PlayerInfo[i][pMember] == 1)
		{
			for(new gi; gi < TotalGangs; gi++)
			{
				if(GangZone[gi][gType] == 1 && GangZone[gi][gZone] != NOEXISTE) GangZoneShowForPlayer(i,GangZone[gi][gZone],GetGangZoneColor(GangZone[gi][gColor]));
			}
		}
	}
	return 1;
}

stock ShowGangZoneToPlayers(GZid)
{
	new gi = GetGangArrayBygZone(GZid);
	if(GangZone[gi][gType] == 0)
	{
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(PlayerInfo[i][pMember] > 10 && PlayerInfo[i][pMember] < 21)
			{
				if(GangZone[gi][gType] == 0 && GangZone[gi][gZone] != NOEXISTE) GangZoneShowForPlayer(i,GZid,GetGangZoneColor(GangZone[gi][gColor]));
			}
		}
	}
	else if(GangZone[gi][gType] == 1)
	{
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(PlayerInfo[i][pMember] == 1)
			{
				if(GangZone[gi][gType] == 1 && GangZone[gi][gZone] != NOEXISTE) GangZoneShowForPlayer(i,GZid,GetGangZoneColor(GangZone[gi][gColor]));
			}
		}	
	}
	return 1;
}

stock ShowGangZonesToPlayer(playerid)
{
	if(PlayerInfo[playerid][pMember] > 10 && PlayerInfo[playerid][pMember] < 21)
	{
		for(new gi; gi < TotalGangs; gi++)
		{
			if(GangZone[gi][gType] == 0 && GangZone[gi][gZone] != NOEXISTE) GangZoneShowForPlayer(playerid,GangZone[gi][gZone],GetGangZoneColor(GangZone[gi][gColor]));
		}
	}
	if(PlayerInfo[playerid][pMember] == 1)
	{
		for(new gi; gi < TotalGangs; gi++)
		{
			if(GangZone[gi][gType] == 1 && GangZone[gi][gZone] != NOEXISTE) GangZoneShowForPlayer(playerid,GangZone[gi][gZone],GetGangZoneColor(GangZone[gi][gColor]));
		}
	}
	return 1;
}

stock FlashGangZoneToPlayers(GZid)
{
	new gi = GetGangArrayBygZone(GZid);
	if(GangZone[gi][gType] == 0)
	{
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(PlayerInfo[i][pMember] > 10 && PlayerInfo[i][pMember] < 21)
			{
				if(GangZone[gi][gType] == 0 && GangZone[gi][gZone] != NOEXISTE) GangZoneFlashForPlayer(i,GZid,GWHITE);
			}
		}
	}
	return 1;
}

stock StopFlashGangZoneToPlayers(GZid)
{
	new gi = GetGangArrayBygZone(GZid);
	if(GangZone[gi][gType] == 0)
	{
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(PlayerInfo[i][pMember] > 10 && PlayerInfo[i][pMember] < 21)
			{
				if(GangZone[gi][gType] == 0 && GangZone[gi][gZone] != NOEXISTE) GangZoneStopFlashForPlayer(i,GZid);
			}
		}
	}
	return 1;
}

stock DestroyGangZones()
{
	for(new gi; gi < TotalGangs; gi++)
	{
		GangZoneHideForAll(GangZone[gi][gZone]);
		GangZoneDestroy(GangZone[gi][gZone]);
	}
	return 1;
}

stock ReloadGangZones()
{
	DestroyGangZones();
	TotalGangs = 0;
	LoadGangZones();
	ShowGangsZonesToPlayers();
	return 1;
}

stock GetGangArrayBygZone(GZid)
{
	for(new i; i < MAX_GANG_ZONES; i++)
	{
		if(GangZone[i][gZone] == GZid)	return i;
	}
	return -1;
}

stock GetGangArrayBySQLID(gsqlid)
{
	for(new i; i < MAX_GANG_ZONES; i++)
	{
		if(GangZone[i][gId] == gsqlid)	return i;
	}
	return -1;
}

Gangs_OnPlayerCommandText(playerid,cmdtext[])
{
	new cmd[128], tmp[128], idx;
	cmd = strtokex(cmdtext, idx);

	if(strcmp(cmd,"/editgz",true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(PlayerInfo[playerid][pAdmin] < 1) return 1;
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /editgz [Crear|Ver(off)|Flash(off)|Color|Tipo|Quitar|Reload]");
			return 1;
		}

		if(strcmp(tmp, "Crear", true) == 0)
		{
			if(PlayerInfo[playerid][pAdmin] < 3) return 1;
			if(TempGangZone != NOEXISTE) { SendClientMessage(playerid, Rojo, "* Ya hay alguien creando una GangZone"); return 1; }
			if(IsPlayerInAnyVehicle(playerid)) RemovePlayerFromVehicle(playerid);
			ShowCreateGangZoneMenu(playerid);
			TempGangZone = MAX_GANG_ZONES+1;
		}
		else if(strcmp(tmp, "Ver", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editgz ver [GangZoneID]");
				return 1;
			}
			new garrayid = strval(tmp);
			if(GangZone[garrayid][gZone] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Esa GangZone no existe."); return 1; }
			if(GangZone[garrayid][gEliminado] == 0)
			{
				new Float:CamX,Float:CamY;
				CamX = floatdiv(floatadd(GangZone[garrayid][gMaxX],GangZone[garrayid][gMinX]),2);
				CamY = floatdiv(floatadd(GangZone[garrayid][gMaxY],GangZone[garrayid][gMinY]),2);
				//SetPlayerPosFindZ(playerid,CamX,CamY,20.0);
				new Float:distance;
				distance = floatsqroot( floatadd ( floatpower( floatsub (GangZone[garrayid][gMaxX] , GangZone[garrayid][gMinX]) , 2) , floatpower( floatsub (GangZone[garrayid][gMaxY] , GangZone[garrayid][gMinY]), 2) ) );
				SetPlayerCameraPos(playerid, CamX,CamY,distance);
				SetPlayerCameraLookAt(playerid, CamX,CamY,0.0);
				TogglePlayerControllable(playerid,0);
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* GangZone ya eliminada");
			}
			return 1;
		}
		else if(strcmp(tmp, "Veroff", true) == 0)
		{
			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid,1);
		}
		else if(strcmp(tmp, "Flash", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editgz flash(off) [GangZoneID]");
				return 1;
			}
			new garrayid = strval(tmp);
			if(GangZone[garrayid][gZone] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Esa GangZone no existe."); return 1; }
			if(GangZone[garrayid][gType] != 0) { SendClientMessage(playerid, Rojo, "* Solo para GangZones de bandas."); return 1; }
			if(GangZone[garrayid][gEliminado] == 0)
			{
				FlashGangZoneToPlayers(GangZone[garrayid][gZone]);
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* GangZone ya eliminada");
			}
			return 1;
		}
		else if(strcmp(tmp, "Flashoff", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editgz flashoff [GangZoneID]");
				return 1;
			}
			new garrayid = strval(tmp);
			if(GangZone[garrayid][gZone] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Esa GangZone no existe."); return 1; }
			if(GangZone[garrayid][gType] != 0) { SendClientMessage(playerid, Rojo, "* Solo para GangZones de bandas."); return 1; }
			if(GangZone[garrayid][gEliminado] == 0)
			{
				StopFlashGangZoneToPlayers(GangZone[garrayid][gZone]);
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* GangZone ya eliminada");
			}
			return 1;
		}
		else if(strcmp(tmp, "Color", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editgz color [GangZoneID]");
				return 1;
			}
			new garrayid = strval(tmp);
			if(GangZone[garrayid][gZone] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Esa GangZone no existe."); return 1; }
			if(GangZone[garrayid][gEliminado] == 0)
			{
				if(TempGangZone != NOEXISTE) { SendClientMessage(playerid, Rojo, "* Ya hay alguien creando una GangZone"); return 1; }
				ShowPlayerDialog(playerid, 3003, DIALOG_STYLE_LIST, "Elige el color de la GangZone", "Negro\nBlanco\nNaranja\nRojo\nBlue\nVioleta\nVerde\nAmarillo\nAzulClaro\nMarron", "Ok", "Salir");
				TempGangZone = garrayid;
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* GangZone ya eliminada");
			}
			return 1;
		}
		else if(strcmp(tmp, "Tipo", true) == 0)
		{
			if(PlayerInfo[playerid][pAdmin] < 3) return 1;
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editgz tipo [GangZoneID]");
				return 1;
			}
			new garrayid = strval(tmp);
			if(GangZone[garrayid][gZone] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Esa GangZone no existe."); return 1; }
			if(GangZone[garrayid][gEliminado] == 0)
			{
				if(TempGangZone != NOEXISTE) { SendClientMessage(playerid, Rojo, "* Ya hay alguien creando una GangZone"); return 1; }
				ShowPlayerDialog(playerid, 3002, DIALOG_STYLE_LIST, "Elige el tipo de GangZones", "Territorios (Para bandas)\nInformacion (Para Policias)", "Ok", "Salir");
				TempGangZone = garrayid;
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* GangZone ya eliminada");
			}
			return 1;
		}
		else if(strcmp(tmp, "Quitar", true) == 0)
		{
			if(PlayerInfo[playerid][pAdmin] < 3) return 1;
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editgz quitar [GangZoneID]");
				return 1;
			}
			new garrayid = strval(tmp);
			if(GangZone[garrayid][gZone] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* Esa GangZone no existe."); return 1; }
			if(GangZone[garrayid][gEliminado] == 0)
			{
				GangZoneHideForAll(GangZone[garrayid][gZone]);
				GangZoneDestroy(GangZone[garrayid][gZone]);
				GangZone[garrayid][gEliminado] = 1;
				SaveGangZone(GangZone[garrayid][gId]);
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* GangZone ya eliminada");
			}
			return 1;
		}
		else if(strcmp(tmp, "Reload", true) == 0)
		{
			if(PlayerInfo[playerid][pAdmin] < 3) return 1;
			ReloadGangZones();
			SendClientMessage(playerid, Verde, "* GangZones recargadas satisfactoriamente");
			return 1;
		}
		else
		{
			SendClientMessage(playerid, Blanco, "USO: /editgz [Crear|Ver(off)|Flash(off)|Color|Tipo|Quitar|Reload]");
			return 1;
		}
		return 1;
	}
	if(strcmp(cmd,"/cleangz",true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 1) return 1;
		TempGangZone = NOEXISTE;
	}
	return 0;
}

ShowCreateGangZoneMenu(playerid)
{
	ShowPlayerDialog(playerid, 3000, DIALOG_STYLE_LIST, "Elige el tipo de GangZones", "Territorios (Para bandas)\nInformacion (Para Policias)", "Ok", "Salir");
}

Gangs_OnDialogResponse(playerid, dialogid, response, listitem)
{
	switch(dialogid)
	{
		case 3000:
		{
     		if(response == 0) return TempGangZone == NOEXISTE;
     		switch(listitem)
       		{
       		    case 0:  TempGangType = 0;
       		    case 1:  TempGangType = 1;
       		}
			ShowPlayerDialog(playerid, 3001, DIALOG_STYLE_LIST, "Elige el color de la nueva GangZone", "Negro\nBlanco\nNaranja\nRojo\nBlue\nVioleta\nVerde\nAmarillo\nAzulClaro\nMarron", "Ok", "Salir");
		}
	   	case 3001:
    	{
     		if(response == 0) return TempGangZone == NOEXISTE;
     		switch(listitem)
       		{
       		    case 0:  TempGangColor = 1; // GBLACK
       		    case 1:  TempGangColor = 2; // GWHITE
       		    case 2:  TempGangColor = 3; // GORANGE
       		    case 3:  TempGangColor = 4; // GRED
       		    case 4:  TempGangColor = 5; // GBLUE
       		    case 5:  TempGangColor = 6; // GVIOLET
       		    case 6:  TempGangColor = 7; // GGREEN
       		    case 7:  TempGangColor = 8; // GYELLOW
       		    case 8:  TempGangColor = 9; // GSEABLUE
       		    case 9:  TempGangColor = 10; // GBROWN
       		}
			SendClientMessage(playerid,Verde,"GangZone creada, usa las flechas del teclado para hacer la zona mas grande o mas pequeña, y Disparo + las flechas para hacerla");
			SendClientMessage(playerid,Verde,"mas ancha o mas estrecha, cuando acabes presiona ENTER, si quieres cancelar pulsa CORRER.");
			BuildingGangZone[playerid] = true;
   			GetPos[playerid] = false;
  		}
		case 3002:
		{
     		if(response == 0) return TempGangZone == NOEXISTE;
     		switch(listitem)
       		{
       		    case 0:  TempGangType = 0;
       		    case 1:  TempGangType = 1;
       		}
			SendClientMessage(playerid,Verde,"* GangZone cambiada de tipo");
			GangZone[TempGangZone][gType] = TempGangType;
			SaveGangZone(GangZone[TempGangZone][gId]);
			ShowGangZoneToPlayers(GangZone[TempGangZone][gZone]);
			TempGangZone = NOEXISTE;
		}
	   	case 3003:
    	{
     		if(response == 0) return TempGangZone == NOEXISTE;
     		switch(listitem)
       		{
       		    case 0:  TempGangColor = 1; // GBLACK
       		    case 1:  TempGangColor = 2; // GWHITE
       		    case 2:  TempGangColor = 3; // GORANGE
       		    case 3:  TempGangColor = 4; // GRED
       		    case 4:  TempGangColor = 5; // GBLUE
       		    case 5:  TempGangColor = 6; // GVIOLET
       		    case 6:  TempGangColor = 7; // GGREEN
       		    case 7:  TempGangColor = 8; // GYELLOW
       		    case 8:  TempGangColor = 9; // GSEABLUE
       		    case 9:  TempGangColor = 10; // GBROWN
       		}
			SendClientMessage(playerid,Verde,"* GangZone cambiada de color");
			GangZone[TempGangZone][gColor] = TempGangColor;
			SaveGangZone(GangZone[TempGangZone][gId]);
			ShowGangZoneToPlayers(GangZone[TempGangZone][gZone]);
			TempGangZone = NOEXISTE;
  		}
	}
	return 1;
}

Gangs_OnPlayerUpdate(playerid)
{
	if(BuildingGangZone[playerid] == true)
	{
	    new Keys, UpDown, LeftRight;
				
		if(GetPos[playerid] == false) GetPlayerPos(playerid, pMaxX, pMaxY, pZ), GetPlayerPos(playerid, pMinX, pMinY, pZ), GetPos[playerid] = true;
	    GetPlayerKeys(playerid, Keys, UpDown, LeftRight);
	    TogglePlayerControllable(playerid, false);
	        
	    if(LeftRight == KEY_LEFT)
	    {
	        pMinX -= 8.0;
	      	GangZoneDestroy(TempGangZone);
	   		TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	      	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
	    }
	    else if(LeftRight & KEY_LEFT && Keys & KEY_FIRE)
	    {
       		pMinX += 8.0;
	      	GangZoneDestroy(TempGangZone);
	   		TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	      	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
	    }
	    else if(LeftRight == KEY_RIGHT)
	    {
	      	pMaxX += 8.0;
	      	GangZoneDestroy(TempGangZone);
	    	TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	      	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
		}
	    else if(LeftRight & KEY_RIGHT && Keys & KEY_FIRE)
	    {
	       	pMaxX -= 8.0;
	       	GangZoneDestroy(TempGangZone);
	    	TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	       	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
		}
		else if(UpDown == KEY_UP)
		{
		    pMaxY += 8.0;
	       	GangZoneDestroy(TempGangZone);
	    	TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	       	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
		}
		else if(UpDown & KEY_UP && Keys & KEY_FIRE)
		{
			pMaxY -= 8.0;
	       	GangZoneDestroy(TempGangZone);
	   		TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	     	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
		}
		else if(UpDown == KEY_DOWN)
		{
			pMinY -= 8.0;
	       	GangZoneDestroy(TempGangZone);
	   		TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	       	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
		}
		else if(UpDown & KEY_DOWN && Keys & KEY_FIRE)
		{
		    pMinY += 8.0;
	       	GangZoneDestroy(TempGangZone);
	  		TempGangZone = GangZoneCreate(pMinX, pMinY, pMaxX, pMaxY);
	       	GangZoneShowForPlayer(playerid, TempGangZone, GetGangZoneColor(TempGangColor));
		}
		else if(Keys & KEY_SECONDARY_ATTACK)
		{
			TogglePlayerControllable(playerid, true);
			BuildingGangZone[playerid] = false;
			GetPos[playerid] = false;
			GangZoneHideForPlayer(playerid,TempGangZone);
			GangZoneDestroy(TempGangZone);
			NewGangZone(TempGangColor,TempGangType, pMinX, pMinY, pMaxX, pMaxY);
			TempGangZone = NOEXISTE;
			SendClientMessage(playerid,Verde,"* GangZone guardada.");
		}
		else if(Keys & KEY_SPRINT)
		{
			TogglePlayerControllable(playerid, true);
			BuildingGangZone[playerid] = false;
			GetPos[playerid] = false;
			GangZoneHideForPlayer(playerid,TempGangZone);
			GangZoneDestroy(TempGangZone);
			TempGangZone = NOEXISTE;
			SendClientMessage(playerid,Amarillo,"* GangZone cancelada.");
		}
	}
}