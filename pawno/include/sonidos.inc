#include <a_samp>
#include <globalvars>
#include <funciones>
#include <audio>

#define MAX_SOUNDS 250

enum aInfo
{
	aState,
	aVehicle,
	aUrl[256],
	Float:aX,
	Float:aY,
	Float:aZ,
}
new AudioInfo[MAX_SOUNDS][aInfo];
enum eInfo
{
	eState[50],
	eRadios[50],
	eId[50],
}
new EscucharInfo[MAX_PLAYERS][eInfo];
new VehicleTimer[MAX_VEHICLES];

forward Audio_OnPlayerStateChange(playerid, newstate);
public Audio_OnPlayerStateChange(playerid, newstate)
{
	if((newstate == PLAYER_STATE_DRIVER && !IsABike(GetPlayerVehicle(playerid))) || (newstate == PLAYER_STATE_PASSENGER && !IsABike(GetPlayerVehicle(playerid))))
	{
		//print("OnPlayerStateChange");
		// Acá entra el jugador al coche, silenciamos cualquier sonido anterior.
		for(new h; h < 50; h++)
		{
			if(EscucharInfo[playerid][eState][h] == 0) { continue; }
			Audio_Stop(playerid, EscucharInfo[playerid][eRadios][h]);
		}
		
		//Hacemos escuchar la radio del coche al jugador
		PlayerInfo[playerid][pSonido] = Audio_PlayStreamed(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1271543", false, false, false);
		//printf("Sonido: %d", PlayerInfo[playerid][pSonido]);
		
		//Nos fijamos si alguien puso la radio en 3D antes que nosotros
		new result = 0;
		new vid = GetPlayerVehicle(playerid);
		for(new i; i < MAX_SOUNDS; i++)
		{
			if(AudioInfo[i][aVehicle] == vid && AudioInfo[i][aState] != 0)
			{
				result++;
			}
		}
		
		if(result == 0)
		{
		//Si somos el primer pasajero, creamos la "Radio"
			for(new i; i < MAX_SOUNDS; i++)
			{
				if(AudioInfo[i][aState] == 0)
				{
					AudioInfo[i][aState] = 1;
					AudioInfo[i][aVehicle] = vid;
					format(AudioInfo[i][aUrl], 256, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1271543");
					VehicleTimer[vid] = SetTimerEx("ActualizarCoords", 1000, 1, "i", i);
				}
			}
		}
	}
	return 1;
}

forward ActualizarCoords(sonido);
public ActualizarCoords(sonido)
{
	GetVehiclePos(AudioInfo[sonido][aVehicle], AudioInfo[sonido][aX], AudioInfo[sonido][aY], AudioInfo[sonido][aZ]);
	return 1;
}

forward Audio_OnPlayerUpdate(playerid);
public Audio_OnPlayerUpdate(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		//print("OnPlayerUpdate");
		for(new i; i < 50; i++)
		{
			// Si ya no se esta escuchando una radio, se la elimina del array del jugador.
			if(EscucharInfo[playerid][eState][i] == 0) { continue; }
			
			if(EscucharInfo[playerid][eState][i] == 1)
			{
				new id = EscucharInfo[playerid][eId][i];
				if(AudioInfo[id][aState] == 1) { continue; }
				
				Audio_Stop(playerid, EscucharInfo[playerid][eRadios][i]);
				EscucharInfo[playerid][eState][i] = 0;
			}
			
			//Si no estamos escuchando una radio, la añadimos
			for(new h; h < MAX_SOUNDS; h++)
			{
				if(AudioInfo[h][aState] == 0) { continue; }
				if(EscucharInfo[playerid][eId][i] == h && EscucharInfo[playerid][eState][i] == 1)
				{
					Audio_Set3DPosition(playerid, EscucharInfo[playerid][eRadios][i], AudioInfo[h][aX], AudioInfo[h][aY], AudioInfo[h][aZ], 30.0);
					continue;
				}
				else
				{
					//No la tenemos, la agregamos
					EscucharInfo[playerid][eState][i] = 1;
					EscucharInfo[playerid][eRadios][i] = Audio_PlayStreamed(playerid, AudioInfo[h][aUrl], false, false, false);
					Audio_Set3DPosition(playerid, EscucharInfo[playerid][eRadios][i], AudioInfo[h][aX], AudioInfo[h][aY], AudioInfo[h][aZ], 30.0);
					EscucharInfo[playerid][eId][i] = h;
				}
			}	
		}
	}
	return 1;
}


forward Audio_OnPlayerExitVehicle(playerid, vehicleid);
public Audio_OnPlayerExitVehicle(playerid, vehicleid)
{
	Audio_Stop(playerid, PlayerInfo[playerid][pSonido]);
	
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) { continue; }
		if(IsPlayerInVehicle(i, vehicleid) && i != playerid) { break; } 

		for(new h; h < MAX_SOUNDS; h++)
		{
			if(AudioInfo[h][aVehicle] != vehicleid || AudioInfo[h][aState] == 0) { continue; }		
			
			AudioInfo[h][aState] = 0;
			KillTimer(VehicleTimer[vehicleid]);	
		}
	}
}