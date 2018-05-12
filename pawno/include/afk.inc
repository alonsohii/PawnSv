#include <a_samp>
#include <globalvars>
#define COLOR_ROJO 0xAA3333AA
#define TIEMPO 1200000 // 20 Minutos en Milisegundos
forward AFK(playerid);
forward Fuera(playerid);

new Float:Posiciones[MAX_PLAYERS][6];
new TAFK[MAX_PLAYERS];
new TFuera[MAX_PLAYERS];
new EstaAFK[MAX_PLAYERS] = 0;

AFK_OnPlayerDisconnect(playerid)
{
    KillTimer(TAFK[playerid]);
	KillTimer(TFuera[playerid]);
	return 1;
}

AFK_OnPlayerSpawn(playerid)
{
	KillTimer(TAFK[playerid]);
	KillTimer(TFuera[playerid]);
	if(PlayerInfo[playerid][pAdmin] == 0)
	{
    	TAFK[playerid] = SetTimerEx("AFK", TIEMPO, 1, "i", playerid);
	}
	return 1;
}

public AFK(playerid)
{
    GetPlayerPos(playerid, Posiciones[playerid][0], Posiciones[playerid][1], Posiciones[playerid][2]);
	if((Posiciones[playerid][0] == Posiciones[playerid][3] && Posiciones[playerid][1] == Posiciones[playerid][4] && Posiciones[playerid][2] == Posiciones[playerid][5]))
    {
        if(EstaAFK[playerid] == 0)
        {
	        Kick(playerid);
	        return 1;
		}
		else
		{
		    Posiciones[playerid][3] = Posiciones[playerid][0];
			Posiciones[playerid][4] = Posiciones[playerid][1];
			Posiciones[playerid][5] = Posiciones[playerid][2];
		    KillTimer(TAFK[playerid]);
		    TAFK[playerid] = SetTimerEx("AFK", TIEMPO, 1, "i", playerid);
	    	return 1;
		}
	}
	else
	{
	    Posiciones[playerid][3] = Posiciones[playerid][0];
		Posiciones[playerid][4] = Posiciones[playerid][1];
		Posiciones[playerid][5] = Posiciones[playerid][2];
	    KillTimer(TAFK[playerid]);
	    TAFK[playerid] = SetTimerEx("AFK", TIEMPO, 1, "i", playerid);
	    return 1;
	}
}

public Fuera(playerid)
{
    EstaAFK[playerid] = 0;
	return 1;
}

AFK_OnPlayerText(playerid)
{
	if(EstaAFK[playerid] == 0)
	{
    	TFuera[playerid] = SetTimerEx("Fuera", 60000, 1, "i", playerid);
    	EstaAFK[playerid] = 1;
    	return 1;
	}
	else if(EstaAFK[playerid] == 1)
	{
	    KillTimer(TFuera[playerid]);
	    TFuera[playerid] = SetTimerEx("Fuera", 60000, 1, "i", playerid);
	    EstaAFK[playerid] = 1;
	    return 1;
	}
	return 0;
}
