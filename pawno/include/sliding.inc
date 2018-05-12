#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

new Sliding[MAX_PLAYERS];
new SlidingP[MAX_PLAYERS] = -1;
new Piloto[MAX_PLAYERS] = 0;
new PilotoTimer[MAX_PLAYERS];
new Float:PilotPos[MAX_PLAYERS][4];

forward Slide_OnPlayerConnect(playerid);
public Slide_OnPlayerConnect(playerid)
{
	Sliding[playerid] = 0;
	return 1;
}

forward Slide_OnPlayerDisconnect(playerid, reason);
public Slide_OnPlayerDisconnect(playerid, reason)
{
	if(Sliding[playerid] == 1)
	{
	    Piloto[SlidingP[playerid]]--;
	    SlidingP[playerid] = -1;
	    Sliding[playerid] = 0;
	}
	return 1;
}

Slide_OnPlayerCommandText(playerid, cmdtext[])
{
   	new cmd[128];
   	new idx;
   	cmd = strtokex(cmdtext, idx);

   	if(strcmp(cmd, "/cuerda", true) == 0)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
		    SendClientMessage(playerid, Rojo, "* El piloto no puede usar las cuerdas.");
		    return 1;
		}
   		if(IsPlayerInAnyVehicle(playerid) && IsAChopper(GetPlayerVehicleID(playerid)) && Sliding[playerid] == 0 && PlayerInfo[playerid][pMember] == 1)
   		{
			new car = GetPlayerVehicleID(playerid);
   		    for(new i; i < MAX_PLAYERS; i++)
   		    {
   		        if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == car)
   		        {
   		            TogglePlayerControllable(i, 0);
   		            GetVehiclePos(GetPlayerVehicleID(i), PilotPos[i][0], PilotPos[i][1], PilotPos[i][2]);
   		            GetVehicleZAngle(GetPlayerVehicleID(i), PilotPos[i][3]);
   		            Piloto[i] ++;
   		            SlidingP[playerid] = i;
   		            if(Piloto[i] == 1)
   		            {
   		                PilotoTimer[i] = SetTimerEx("PilotoFunc", 100, 1, "i", i);
   		            }
					break;
   		        }
   		    }
   			Sliding[playerid] = 1;
   			RemovePlayerFromVehicle(playerid);
   			TogglePlayerControllable(playerid, 0);
   			SetTimerEx("Slide", 500, 0, "i", playerid);
   			SendClientMessage(playerid, Amarillo, "* Estás bajando, usa /soltar cuando lleges al suelo.");
   		}
   		return 1;
	}
   	if(strcmp(cmd, "/soltar", true) == 0)
   	{
   		if(Sliding[playerid] == 1)
   		{
   			Sliding[playerid] = 0;
   			Piloto[SlidingP[playerid]] --;
   			TogglePlayerControllable(playerid, 1);
   			SendClientMessage(playerid, Amarillo, "* Has soltado la cuerda.");
			format(string, sizeof(string), "* %s suelta la cuerda.", pName(playerid));
			ProxDetector(20.0, playerid, string,Morado,Morado,Morado,Morado,Morado);
   			ClearAnimations(playerid, 1);
   		}
   		return 1;
   	}
   	return 0;
}

forward Slide(playerid);
public Slide(playerid)
{
    if(Sliding[playerid] == 1)
    {
    	new Float:X;
    	new Float:Y;
    	new Float:Z;
    	ApplyAnimation(playerid,"ped","abseil",4.0,0,0,0,1,0);
    	GetPlayerPos(playerid, X, Y, Z);
    	SetPlayerPos(playerid, X, Y, Z - 3.00);
    	SetTimerEx("Slide", 500, 0, "i", playerid);
    }
	return 1;
}

forward PilotoFunc(playerid);
public PilotoFunc(playerid)
{
	if(Piloto[playerid] == 0)
	{
	    TogglePlayerControllable(playerid, 1);
	    KillTimer(PilotoTimer[playerid]);
	}
	else
	{
		SetVehiclePos(GetPlayerVehicleID(playerid), PilotPos[playerid][0], PilotPos[playerid][1], PilotPos[playerid][2]);
  		SetVehicleZAngle(GetPlayerVehicleID(playerid), PilotPos[playerid][3]);
	}
	return 1;
}

