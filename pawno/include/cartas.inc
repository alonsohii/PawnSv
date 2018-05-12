#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

new carta[128];
enum Cartas
{
	carta1,
	carta2,
	carta3,
	carta4,
	carta5
}
new CartasJugador[MAX_PLAYERS][Cartas];
new tipocarta;

Cartas_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new tmp[128];
    new idx;
    cmd = strtokex(cmdtext,idx);
	if(strcmp(cmd,"/carta",true)==0)
	{
		if(PlayerInfo[playerid][pCartas] == 0)
		{
			SendClientMessage(playerid, Rojo, "* No tienes cartas!");
			return 1;
		}
     	tipocarta = random(13)+1;
		if(tipocarta == 1){ format(string,sizeof(string),"AS"); carta = string;}
		if(tipocarta == 11){ format(string,sizeof(string),"J");carta = string;}
		if(tipocarta == 12){ format(string,sizeof(string),"Q");carta = string;}
		if(tipocarta == 13){ format(string,sizeof(string),"K");carta = string;}
        tmp = strtokex(cmdtext,idx);
	    if(!strlen(tmp))
	    {
	        SendClientMessage(playerid,Blanco,"USO: /carta (Todos/ID/Mostrar/Tirar)");
	        return 1;
		}
		if(IsNumeric(tmp))
		{
			new id;
			id = strval(tmp);
			if(!IsPlayerConnected(id)) { SendClientMessage(playerid,Rojo,"* El jugador no está en línea"); return 1; }
			if(IsPlayerConnected(id))
			{
				tmp = strtokex(cmdtext,idx);
				if(!strlen(tmp)) { SendClientMessage(playerid,Blanco,"USO: /carta ID ind(ividual) /carta ID col(ectiva)"); return 1; }
				if(strcmp(tmp,"ind",true)==0 || strcmp(tmp,"individual",true)==0)
				{
					if(GetDistanceBetweenPlayers(playerid,id) <= 10)
					{
						if(CartasJugador[id][carta1] > 0 && CartasJugador[id][carta2] > 0 && CartasJugador[id][carta3] > 0 && CartasJugador[id][carta4] > 0 && CartasJugador[id][carta5] > 0)
						{
							SendClientMessage(playerid,Naranja,"* Este jugador ya tiene cinco cartas en mano");
							return 1;
						}
						if(CartasJugador[id][carta1] == 0 || CartasJugador[id][carta2] == 0 || CartasJugador[id][carta3] == 0 || CartasJugador[id][carta4] == 0 || CartasJugador[id][carta5] == 0)
						{
							format(string,sizeof(string), "%s saca una carta y se la muestra a %s", pName(playerid),pName(id));
							ProxDetector(10.0,playerid,string,Morado,Morado,Morado,Morado,Morado);
							if(tipocarta == 11 || tipocarta ==12 || tipocarta == 13)
							{
								format(string,sizeof(string),"Te han entregado una %s",carta);
								SendClientMessage(id,Naranja,string);
							}
							if(tipocarta == 1)
							{
								SendClientMessage(id,Naranja,"Te han entregado un As.");
							}
							if(tipocarta != 1 && tipocarta != 11 && tipocarta !=12 && tipocarta != 13)
							{
								format(string,sizeof(string),"Te han entregado un %d",tipocarta);
								SendClientMessage(id,Naranja,string);
							}
							if(CartasJugador[id][carta1] == 0){CartasJugador[id][carta1] = tipocarta;return 1;}
							if(CartasJugador[id][carta2] == 0){CartasJugador[id][carta2] = tipocarta;return 1;}
							if(CartasJugador[id][carta3] == 0){CartasJugador[id][carta3] = tipocarta;return 1;}
							if(CartasJugador[id][carta4] == 0){CartasJugador[id][carta4] = tipocarta;return 1;}
							if(CartasJugador[id][carta5] == 0){CartasJugador[id][carta5] = tipocarta;return 1;}
						}
					}
				}
				if(strcmp(tmp,"col",true)==0 || strcmp(tmp,"colectiva",true)==0)
				{
					if(GetDistanceBetweenPlayers(playerid,id) <= 10)
					{
						if(CartasJugador[id][carta1] > 0 && CartasJugador[id][carta2] > 0 && CartasJugador[id][carta3] > 0 && CartasJugador[id][carta4] > 0 && CartasJugador[id][carta5] > 0)
						{
							SendClientMessage(playerid,Naranja,"* Este jugador ya tiene cinco cartas en mano");
							return 1;
						}
						if(CartasJugador[id][carta1] == 0 || CartasJugador[id][carta2] == 0 || CartasJugador[id][carta3] == 0 || CartasJugador[id][carta4] == 0 || CartasJugador[id][carta5] == 0)
						{
							if(tipocarta == 11 || tipocarta ==12 || tipocarta == 13)
							{
								format(string,sizeof(string), "%s saca una carta para %s, es una: %s", pName(playerid),pName(id),carta);
								ProxDetector(10.0,playerid,string,Morado,Morado,Morado,Morado,Morado);
							}
							if(tipocarta == 1)
							{
								format(string,sizeof(string), "%s saca una carta para %s, es un: %s", pName(playerid),pName(id),carta);
								ProxDetector(10.0,playerid,string,Morado,Morado,Morado,Morado,Morado);
							}
							if(tipocarta != 1 && tipocarta != 11 && tipocarta !=12&& tipocarta != 13)
							{
								format(string,sizeof(string), "%s saca una carta para %s, es un: %d", pName(playerid),pName(id),tipocarta);
								ProxDetector(10.0,playerid,string,Morado,Morado,Morado,Morado,Morado);
							}
							if(CartasJugador[id][carta1] == 0){CartasJugador[id][carta1] = tipocarta;return 1;}
							if(CartasJugador[id][carta2] == 0){CartasJugador[id][carta2] = tipocarta;return 1;}
							if(CartasJugador[id][carta3] == 0){CartasJugador[id][carta3] = tipocarta;return 1;}
							if(CartasJugador[id][carta4] == 0){CartasJugador[id][carta4] = tipocarta;return 1;}
							if(CartasJugador[id][carta5] == 0){CartasJugador[id][carta5] = tipocarta;return 1;}
						}
					}
				}
			}
		}
		else
		{
			if(strcmp(tmp,"todos",true) == 0)
			{
				if(tipocarta == 1 || tipocarta == 11 || tipocarta ==12 || tipocarta == 13)
				{
					format(string, sizeof(string), "%s saca una carta: %s.", pName(playerid),carta);
					ProxDetector(10.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				}
				else
				{
					format(string,sizeof(string),"%s saca una carta: %d.",pName(playerid),tipocarta);
					ProxDetector(10.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				}
				return 1;
			}
			if(strcmp(tmp,"mostrar",true) == 0)
			{
				tmp = strtokex(cmdtext,idx);
				if(!strlen(tmp)) { SendClientMessage(playerid,Blanco,"USO: /carta mostrar (todos/ind)"); return 1; }
				if(strcmp(tmp,"todos",true) == 0)
				{
					if(CartasJugador[playerid][carta1] == 0 && CartasJugador[playerid][carta2] == 0 && CartasJugador[playerid][carta3] == 0 && CartasJugador[playerid][carta4] == 0 && CartasJugador[playerid][carta5] == 0)
					{
						SendClientMessage(playerid,Rojo,"* No tienes cartas");
						return 1;
					}
					format(string, sizeof(string),"%s tiene las siguientes cartas: %d ,%d, %d, %d, %d",pName(playerid),CartasJugador[playerid][carta1],CartasJugador[playerid][carta2],CartasJugador[playerid][carta3],CartasJugador[playerid][carta4],CartasJugador[playerid][carta5]);
					ProxDetector(10.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
					return 1;
				}
				if(strcmp(tmp,"ind",true) == 0 || strcmp(tmp,"individual",true) == 0)
				{
					if(CartasJugador[playerid][carta1] == 0 && CartasJugador[playerid][carta2] == 0 && CartasJugador[playerid][carta3] == 0 && CartasJugador[playerid][carta4] == 0 && CartasJugador[playerid][carta5] == 0)
					{
						SendClientMessage(playerid,Rojo,"* No tienes cartas");
						return 1;
					}
					format(string,sizeof(string),"%d,%d,%d,%d,%d",CartasJugador[playerid][carta1],CartasJugador[playerid][carta2],CartasJugador[playerid][carta3],CartasJugador[playerid][carta4],CartasJugador[playerid][carta5]);
					GameTextForPlayer(playerid,string,5000,1);
					return 1;
				}
			}
			if(strcmp(tmp,"tirar",true)==0)
			{
				if(CartasJugador[playerid][carta1] == 0 && CartasJugador[playerid][carta2] == 0 && CartasJugador[playerid][carta3] == 0 && CartasJugador[playerid][carta4] == 0 && CartasJugador[playerid][carta5] == 0)
				{
					SendClientMessage(playerid,Rojo,"* No tienes cartas");
					return 1;
				}
				format(string,sizeof(string), "%s tira las cartas", pName(playerid));
				ProxDetector(10.0,playerid,string,Morado,Morado,Morado,Morado,Morado);
				CartasJugador[playerid][carta1] = 0; CartasJugador[playerid][carta2] = 0; CartasJugador[playerid][carta3] = 0; CartasJugador[playerid][carta4] = 0; CartasJugador[playerid][carta5] = 0;
				return 1;
			}
		}
    }
	return 0;
}
