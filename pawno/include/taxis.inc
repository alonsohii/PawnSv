#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>

enum tInfo
{
	trtime, 
	costo,
	taxista,
	timer,
};
new Transporte[MAX_PLAYERS][tInfo];

enum taInfo
{
	taestado,
	tarifa,
	ganancias,
};
new Taxista[MAX_PLAYERS][taInfo];

new Taxistas;

Taxis_OnGameModeInit()
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		Transporte[i][taxista] = NOEXISTE;
	}
	return 1;
}

forward Taximetro(playerid);
public Taximetro(playerid)
{
 	if(Transporte[playerid][trtime] == 20)
	{
		Transporte[playerid][trtime] = 1;
		if(Transporte[playerid][taxista] != NOEXISTE)
		{
			if(IsPlayerConnected(Transporte[playerid][taxista]))
			{
				Transporte[playerid][costo] += Taxista[Transporte[playerid][taxista]][tarifa];
				Taxista[Transporte[playerid][taxista]][ganancias] += Taxista[Transporte[playerid][taxista]][tarifa];
			}
		}
	}
  	Transporte[playerid][trtime] += 1;
    format(string, sizeof(string), "~r~%d ~w~: ~g~%d $",Transporte[playerid][trtime],Transporte[playerid][costo]);
	GameTextForPlayer(playerid, string, 1000, 6);
	GameTextForPlayer(Transporte[playerid][taxista], string, 1000, 6);
}

Taxis_OnPlayerCommandText(playerid, cmdtext[])
{
	new tmp[128];
	new cmd[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd,"/tarifa",true)==0)
    {
        if(PlayerInfo[playerid][pMember] == 3)
		{
			if(Taxista[playerid][taestado] > 0)
			{
				Taxistas -= 1;
				Taxista[playerid][taestado] = 0;
				format(string, sizeof(string), "* Ya no estás de servicio y has ganado %d$.", Taxista[playerid][ganancias]);
				SendClientMessage(playerid, Azul, string);
				SafeGivePlayerMoney(playerid, Taxista[playerid][ganancias]);
				Taxista[playerid][ganancias] = 0;
				return 1;
			}
			if(!IsPlayerInAnyVehicle(playerid)) { SendClientMessage(playerid,RojoIntenso,"Necesitas estar en el taxi");	 return 1; }		
			new Veh = GetPlayerVehicle(playerid);
			if(IsATeamCar(Veh, 3))
			{
				if(GetPlayerState(playerid) == 2)
				{
					tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp))
					{
						SendClientMessage(playerid, Blanco, "USO: /tarifa [precio]");
						return 1;
					}
					new moneys = strval(tmp);
					if(moneys < 1 || moneys > 15) { SendClientMessage(playerid, Gris, "La tarifa debe ser entre 1$ y 15$!"); return 1; }
					Taxistas += 1; Taxista[playerid][taestado] = 1; Taxista[playerid][tarifa] = moneys; Taxista[playerid][ganancias] = 0;
					format(string, sizeof(string), "Taxista %s está de Servicio, tarifa: %d$.", pName(playerid), Taxista[playerid][tarifa]);
	    			SendClientMessageToAll(Verde,string);
			        format(string, sizeof(string), "* %s enciende la luz de Taxi y el taxímetro.", pName(playerid));
			        ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
				}
			}
		}
	    return 1;
 	}
	return 0;
}

forward Taxis_OnPlayerStateChange(playerid, newstate, oldstate);
public Taxis_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_PASSENGER)
	{
	    for(new i = 0; i < MAX_PLAYERS; i++)
	    {
	        if(IsPlayerConnected(i))
	        {
	            if(IsPlayerInVehicle(i, CarInfo[GetPlayerVehicle(playerid)][cId]) && GetPlayerState(i) == 2 && Taxista[i][taestado] > 0)
	            {
	                if(SafeGetPlayerMoney(playerid) < Taxista[i][tarifa])
	                {
	                    format(string, sizeof(string), "* Necesitas $%d para entrar.", Taxista[i][tarifa]);
						SendClientMessage(playerid, Azul, string);
						RemovePlayerFromVehicle(playerid);
	                }
	                else
	                {
	                    format(string, sizeof(string), "* Has entrado en el taxi, pagarás %d$ cada 20 segundos de recorrido.", Taxista[i][tarifa]);
						SendClientMessage(playerid, Azul, string);
						format(string, sizeof(string), "* El pasajero %s ha entrado al taxi.", pName(playerid));
						SendClientMessage(i, Azul, string);
						Transporte[playerid][trtime] = 1;
	                    Transporte[playerid][costo] = Taxista[i][tarifa];
	                    Taxista[i][ganancias] += Taxista[i][tarifa];
	                    Transporte[playerid][taxista] = i;
	                    Transporte[playerid][timer] = SetTimerEx("Taximetro",1000,1,"i",playerid);
	                }
	            }
	        }
	    }
	}
	if(newstate == PLAYER_STATE_ONFOOT)
	{
		if(Transporte[playerid][costo] > 0)
		{
			SafeGivePlayerMoney(playerid, -Transporte[playerid][costo]);
			format(string, 128, "* Has pagado $%d por todo el recorrido.", Transporte[playerid][costo]);
			SendClientMessage(playerid, Azul, string);
			KillTimer(Transporte[playerid][timer]);
			Transporte[playerid][taxista] = NOEXISTE;
			Transporte[playerid][costo] = 0;
		}
		if(Taxista[playerid][taestado] > 0)
		{
			Taxistas -= 1;
			Taxista[playerid][taestado] = 0;
			format(string, sizeof(string), "* Ya no estás de servicio y has ganado %d$.", Taxista[playerid][ganancias]);
			SendClientMessage(playerid, Azul, string);
			SafeGivePlayerMoney(playerid, Taxista[playerid][ganancias]);
			Taxista[playerid][ganancias] = 0;
		}
	}
	return 1;
}

Taxis_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 17)
	{
		DisablePlayerCheckpoint(playerid);
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pEstadoTaxista] = 0;
		return 1;
	}
	return 0;
}

Taxis_OnPlayerUpdate(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 17 && PlayerInfo[playerid][pEstadoTaxista] == 2)
	{
		if(IsPlayerConnected(PlayerInfo[playerid][pClienteTaxista]))
		{
			new Float:X,Float:Y,Float:Z;
			GetPlayerPos(PlayerInfo[playerid][pClienteTaxista], X,Y,Z);
			SetPlayerCheckpoint(playerid, X,Y,Z, 6.0);
		}
		else
		{
			SendClientMessage(playerid,Naranja, "* El cliente se ha desconectado!");
			DisablePlayerCheckpoint(playerid);
			PlayerInfo[playerid][pCheckpoint] = 0;
			PlayerInfo[playerid][pEstadoTaxista] = 0;
		}
	}
}