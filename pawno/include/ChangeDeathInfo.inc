#if defined _cdi_included
	#endinput
#endif
#define _cdi_included

#include <a_samp>

/*
native ChangeDeathInfo(playerid, killerid, reason, delay=30000);
native ResetDeathInfo(playerid);
*/

stock ChangeDeathInfo(playerid, killerid, reason, delay=30000)
{
	if(IsPlayerConnected(playerid))
	{
	    SetPVarInt(playerid, "CDI_DeathReason", reason);
	    SetPVarInt(playerid, "CDI_Killer", killerid);
	    SetPVarInt(playerid, "CDI_Changed", GetTickCount());
	    SetPVarInt(playerid, "CDI_ChangeDelay", delay);
		return 1;
	}
	return 0;
}

stock ResetDeathInfo(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    SetPVarInt(playerid, "CDI_DeathReason", 255);
	    SetPVarInt(playerid, "CDI_Killer", INVALID_PLAYER_ID);
	    SetPVarInt(playerid, "CDI_Changed", GetTickCount());
	    SetPVarInt(playerid, "CDI_ChangeDelay", 0);
	    return 1;
	}
	return 0;
}

public OnPlayerSpawn(playerid)
{
	ResetDeathInfo(playerid);
	return CallLocalFunction("CDI_OnPlayerSpawn", "i", playerid);
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn CDI_OnPlayerSpawn
forward CDI_OnPlayerSpawn(playerid);

public OnPlayerDeath(playerid, killerid, reason)
{
    if((GetPVarInt(playerid, "CDI_DeathReason") == 255 && !IsPlayerConnected(GetPVarInt(playerid, "CDI_Killer"))) || (GetTickCount() - GetPVarInt(playerid, "CDI_Changed")) > GetPVarInt(playerid, "CDI_ChangeDelay"))
  		return CallLocalFunction("CDI_OnPlayerDeath", "iii", playerid, killerid, reason);
	return CallLocalFunction("CDI_OnPlayerDeath", "iii", playerid, GetPVarInt(playerid, "CDI_Killer"), GetPVarInt(playerid, "CDI_DeathReason"));
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath CDI_OnPlayerDeath
forward CDI_OnPlayerDeath(playerid);
