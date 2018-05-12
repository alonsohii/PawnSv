/*
	@title Low-Rider Mini-Game.
	@author Carlton
	@copyright 2010
	@description Perform a lowriding mini-game similar to singleplayer's one.
	@modified by oldschool developers to OS-RP
*/

#include <a_samp>

#define CameraAngles // Comment this if you would like to disable the camera when you've finished a note.

new	bool:ContestToggled = false, // Desactivado por defecto, activado por STAFF
	Text:ContestText; // TextDraw

Low_OnGMInit()
{
    ContestText = TextDrawCreate(230.000000,309.000000,"_");
	TextDrawAlignment(ContestText,0);
	TextDrawBackgroundColor(ContestText,0x000000ff);
	TextDrawFont(ContestText,2);
	TextDrawLetterSize(ContestText,0.899999,2.599999);
	TextDrawColor(ContestText,0xffff00ff);
	TextDrawSetOutline(ContestText,1);
	TextDrawSetProportional(ContestText,1);
	TextDrawSetShadow(ContestText,1);
	return 1;
}

Low_OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/lowconcurso", cmdtext, true, 10) == 0) {
		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
		    if(ContestToggled == true) 
			{
		        ContestToggled = false;
				SendClientMessage(playerid,Amarillo,"* Has desactivado el concurso de Low Rider");
		    }
		    else 
			{
		        ContestToggled = true;
				SendClientMessage(playerid,Amarillo,"* Has activado el concurso de Low Rider");
		    }
		}
	    return 1;
	}
	if (strcmp("/lowrider", cmdtext, true, 10) == 0)
	{
	    if(ContestToggled == false && PlayerInfo[playerid][pAdmin] == 0) { SendClientMessage(playerid, Naranja, "* El concurso no está habilitado, pideselo a un miembro del Staff."); return 1;}
	    if(PlayerInfo[playerid][pInContest] == false)
		{
	        SetPlayerCheckpoint(playerid, 1792.2076,-1909.4030,13.2685, 9.0);
			PlayerInfo[playerid][pCheckpoint] = 99;
	        PlayerInfo[playerid][pInContest] = true;
	        PlayerInfo[playerid][pJustJoined] = true;
	    }
	    else
		{
	        PlayerInfo[playerid][pInContest] = false;
	        PlayerInfo[playerid][pJustJoined] = false;
	        TextDrawHideForPlayer(playerid, ContestText);
	        DisablePlayerCheckpoint(playerid);
	        SetCameraBehindPlayer(playerid);
	        PlayerInfo[playerid][pCurrentNote] = -1;
	        ClearAnimations(playerid);
	    }
	    return 1;
	}
	if (strcmp("/forcelow", cmdtext, true, 10) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 1;
		if(GetVehicleComponentInSlot(GetPlayerVehicleID(playerid),GetVehicleComponentType(1087)) == 1087)
		{
			PlayerInfo[playerid][pCheckpoint] = 99;
	        PlayerInfo[playerid][pInContest] = true;
	        PlayerInfo[playerid][pJustJoined] = true;
			BeginContestForPlayer(playerid);
		}
		else SendClientMessage(playerid, Naranja, "* Tu vehiculo no tiene sistema hidráulico.");
	    return 1;
	}
	return 0;
}

Low_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pInContest] == true && PlayerInfo[playerid][pCheckpoint] == 99) 
	{
	    if(!IsPlayerInAnyVehicle(playerid)) { SendClientMessage(playerid, Rojo, "* No estás en un coche."); return 1;}
		if(GetVehicleComponentInSlot(GetPlayerVehicleID(playerid),GetVehicleComponentType(1087)) == 1087)
		{
			BeginContestForPlayer(playerid);
		}
		else SendClientMessage(playerid, Naranja, "* Tu vehiculo no tiene sistema hidráulico.");
	}
	return 1;
}

stock BeginContestForPlayer(playerid)
{
	new Float:LPos[4];
	GetPlayerPos(playerid, LPos[0],LPos[1],LPos[2]);
	SetPlayerCameraPos(playerid, LPos[0]+5,LPos[1],LPos[2]+1);
	SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	DisablePlayerCheckpoint(playerid);
    SendClientMessage(playerid, Amarillo, "* The contest is starting, make sure you're in the camera, so you can see!");
    SetTimerEx("SendNoteForPlayer", 5000, 0, "d", playerid);
    GameTextForPlayer(playerid, "~r~Information~n~~n~~>~ Right~n~~<~ Left~n~~up~ Up~n~~down~Down", 4000, 5);
    return 1;
}

forward SendNoteForPlayer(playerid);
public SendNoteForPlayer(playerid) 
{
	new	array[128],
		earned,
		note,
		randanim,
		randomcamera,
		Float:LPos[4];
		
	PlayerPlaySound(playerid, 1130, 0.0, 0.0, 10.0);
	TextDrawHideForPlayer(playerid, ContestText);
	GetPlayerPos(playerid, LPos[0],LPos[1],LPos[2]);
	
	earned = random(20);
	note = random(4);
	randanim = random(3);
	
	#if defined CameraAngles
	randomcamera = random(6);
	#else
	#pragma unused randomcamera
	#endif
	
	if(PlayerInfo[playerid][pJustJoined] == false) 
	{
		PlayerInfo[playerid][pPointsEarned] += earned;
		format(array, 128, "Puntos ganados: ~g~%d Pts", PlayerInfo[playerid][pPointsEarned]);
		GameTextForPlayer(playerid, array, 8000, 4);
	}
	if(PlayerInfo[playerid][pJustJoined] == true)  PlayerInfo[playerid][pJustJoined] = false;
	
	switch(note) {
	    case 0:{
	        TextDrawSetString(ContestText, "New note~n~~n~      ~up~");
	        PlayerInfo[playerid][pCurrentNote] = 0;
	    }
	    case 1:{
	        TextDrawSetString(ContestText, "New note~n~~n~      ~down~");
	        PlayerInfo[playerid][pCurrentNote] = 1;
	    }
	    case 2:{
	       	TextDrawSetString(ContestText, "New note~n~~n~      ~>~");
	        PlayerInfo[playerid][pCurrentNote] = 2;
	    }
	    case 3:{
	        TextDrawSetString(ContestText, "New note~n~~n~      ~<~");
	        PlayerInfo[playerid][pCurrentNote] = 3;
	    }
	}
	switch(randanim) {
	    case 0: {
			ApplyAnimation(playerid, "LOWRIDER", "lrgirl_l3_loop", 4.0, 1, 0, 0, 0, 0);
	    }
	    case 1: {
	        ApplyAnimation(playerid, "LOWRIDER", "lrgirl_l4_loop", 4.0, 1, 0, 0, 0, 0);
	    }
	    case 2: {
	        ApplyAnimation(playerid, "LOWRIDER", "lrgirl_l5_loop", 4.0, 1, 0, 0, 0, 0);
	    }
	}
	#if defined CameraAngles
	switch(randomcamera) {
	    case 0: {
	        SetPlayerCameraPos(playerid, LPos[0]+5,LPos[1],LPos[2]+1);
		    SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	    }
	    case 1: {
	        SetPlayerCameraPos(playerid, LPos[0]+5,LPos[1]+4,LPos[2]+1);
		    SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	    }
	    case 2: {
	        SetPlayerCameraPos(playerid, LPos[0]+3,LPos[1],LPos[2]+1);
		    SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	    }
	    case 3: {
	        SetPlayerCameraPos(playerid, LPos[0]+3,LPos[1],LPos[2]+2);
		    SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	    }
	    case 4: {
	        SetPlayerCameraPos(playerid, LPos[0],LPos[1]+2,LPos[2]+9);
		    SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	    }
	    case 5: {
	        SetPlayerCameraPos(playerid, LPos[0],LPos[1]+2,LPos[2]+2);
		    SetPlayerCameraLookAt(playerid, LPos[0],LPos[1],LPos[2]);
	    }
	}
	#endif
	TextDrawShowForPlayer(playerid, ContestText);
	return 1;
}

Low_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys
	if (newkeys & KEY_ANALOG_UP && PlayerInfo[playerid][pCurrentNote] == 0)
	{
	    SendNoteForPlayer(playerid);
	}
	if (newkeys & KEY_ANALOG_DOWN && PlayerInfo[playerid][pCurrentNote] == 1)
	{
	    SendNoteForPlayer(playerid);
	}
	if (newkeys & KEY_ANALOG_RIGHT && PlayerInfo[playerid][pCurrentNote] == 2)
	{
	    SendNoteForPlayer(playerid);
	}
	if (newkeys & KEY_ANALOG_LEFT && PlayerInfo[playerid][pCurrentNote] == 3)
	{
	    SendNoteForPlayer(playerid);
	}
	return 0;
}
