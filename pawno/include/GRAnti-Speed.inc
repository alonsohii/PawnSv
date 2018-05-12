/*
	---------------------------------------------------------
	|		  GR_Anti-Speed				|
	|		Script by GROVE4L			|									---------------------------------------------------------
*/

#include <a_samp>
#define SetPlayerPos SetPlayerPosAntiC
new VACheat[MAX_PLAYERS];
new AAActivado[MAX_PLAYERS];
new Float:POSAntiCheat[3][MAX_PLAYERS];
new StringAntiCheat[256];


forward OnAntiDisconnect(playerid);
public OnAntiDisconnect(playerid)
{
    KillTimer(VACheat[playerid]);
	AAActivado[playerid] = 0;
}

forward OnAntiSpawn(playerid);
public OnAntiSpawn(playerid)
{
    if(AAActivado[playerid] == 0)
	{
		SetTimerEx("Activated",3000,0,"i",playerid);
		AAActivado[playerid] = 1;
		printf("Anticheat activado para el id %d",playerid);
	}
}

forward Activated(playerid);
public Activated(playerid)
{
    GetPlayerPos(playerid,POSAntiCheat[0][playerid],POSAntiCheat[1][playerid],POSAntiCheat[2][playerid]);
    SendClientMessage(playerid,0xFF2E11FF,"Este Server tiene un Anticheat de AirBreak WARNING!");
	VACheat[playerid] = SetTimerEx("ACheat",1000,1,"d",playerid);
}

forward OnAntiDeath(playerid);
public OnAntiDeath(playerid)
{
    KillTimer(VACheat[playerid]);
	AAActivado[playerid] = 0;
}

forward ACheat(playerid);
public ACheat(playerid)
{
	if(AAActivado[playerid] == 1)
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			if(IsPlayerInRangeOfPoint(playerid,15,POSAntiCheat[0][playerid],POSAntiCheat[1][playerid],POSAntiCheat[2][playerid]))
			{
		        GetPlayerPos(playerid,POSAntiCheat[0][playerid],POSAntiCheat[1][playerid],POSAntiCheat[2][playerid]);
		        return 1;
			}
			else
			{
			    new NombreAC[24];
			    GetPlayerName(playerid,NombreAC,24);
		        format(StringAntiCheat, sizeof(StringAntiCheat), "AdmCmd: %s fue kickeado del servidor. Razon: SpeedHack A Pie.", NombreAC);
	            SendClientMessageToAll(0xFF6347AA, StringAntiCheat);
				Kick(playerid);
		        return 1;
			}
		}
		else if(IsPlayerInAnyVehicle(playerid))
		{
			new Float:VAX, Float:VAY, Float:VAZ, Float:Velo;
			GetVehicleVelocity(GetPlayerVehicleID(playerid), VAX, VAY, VAZ);
			Velo = floatmul(floatsqroot(floatadd(floatadd(floatpower(VAX, 2), floatpower(VAY, 2)), floatpower(VAZ, 2))), 100.0);
			if(floatround(Velo / 0.5125, floatround_floor) > 310.0)
			{
				new NombreAC[24];
				GetPlayerName(playerid,NombreAC,24);
				format(StringAntiCheat, sizeof(StringAntiCheat), "AdmCmd: %s fue kickeado por el AntiCheat. Razon: SpeedHack En Vehiculo.", NombreAC);
				SendClientMessageToAll(0xFF6347AA, StringAntiCheat);
				Kick(playerid);
				return 1;
			}
		}
	}
	return 1;
}

stock SetPlayerPosAntiC(playerid,Float:Xanti,Float:Yanti,Float:Zanti)
{
    KillTimer(VACheat[playerid]);
	SetPlayerPos(playerid,Xanti,Yanti,Zanti);
	POSAntiCheat[0][playerid] = Xanti;
	POSAntiCheat[1][playerid] = Yanti;
	POSAntiCheat[2][playerid] = Zanti;
	VACheat[playerid] = SetTimerEx("ACheat",1000,1,"d",playerid);
}

/*
	-------------------------------------------------------------------------
	|	     BY GROVE4L  || Visita: www.pawnoscripting.com		|
	-------------------------------------------------------------------------
*/