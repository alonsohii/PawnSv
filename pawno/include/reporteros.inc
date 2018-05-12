#include <a_samp>
#include <colores>
#include <globalvars>
#include <funciones>

new gNews[MAX_PLAYERS];
new NewsOn=0;
new TalkingLive[MAX_PLAYERS];
new LiveOffer[MAX_PLAYERS];
new CallNews=1;
new Programa[MAX_PLAYERS];

Reporteros_OnPlayerSpawn(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(PlayerInfo[playerid][pJailed] < 1)
	    {
			if(PlayerInfo[playerid][pMember] == 9)
			{
				SafeGivePlayerWeapon(playerid,43,100);
			}
		}
	}
}

Reporteros_OnPlayerConnect(playerid)
{
	TalkingLive[playerid] = NOEXISTE;
	LiveOffer[playerid] = NOEXISTE;
}

Reporteros_OnPlayerCommandText(playerid,cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	new giveplayerid;
	cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd, "/noticias", true) == 0||strcmp(cmd, "/n", true) == 0||strcmp(cmd, "//", true) == 0)
	{
			if(PlayerInfo[playerid][pMember] == 4)
			{
			    new newcar = GetPlayerVehicleID(playerid);
				if(IsANewsVan(newcar) || GetPlayerInterior(playerid)>0 || GetPlayerVirtualWorld(playerid) > 0)
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
						SendClientMessage(playerid, Blanco, "USO: /n [noticias]");
						return 1;
					}
					format(string, sizeof(string), "[NOTICIAS] %s: %s", pName(playerid), result);
					OOCNews(VerdeClaro,string);
				}
				else
				{
				    SendClientMessage(playerid, Naranja, "* No estás en un vehículo de San News, o en algún local habilitado.");
				    return 1;
				}
			}
			else
			{
			    SendClientMessage(playerid, Rojo, "* No eres reportero!");
			}
		return 1;
	}
	if(strcmp(cmd, "/directo", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
			if(PlayerInfo[playerid][pMember] == 4)
			{
			    if(TalkingLive[playerid] != NOEXISTE)
			    {
			        SendClientMessage(playerid, AzulClaro, "* Conversación en directo finalizada.");
			        SendClientMessage(TalkingLive[playerid], AzulClaro, "* Conversación en directo finalizada.");
			        TogglePlayerControllable(playerid, 1);
			        TogglePlayerControllable(TalkingLive[playerid], 1);
		            TalkingLive[TalkingLive[playerid]] = NOEXISTE;
			        TalkingLive[playerid] = NOEXISTE;
			        return 1;
			    }
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /directo [IdJugador/ParteDelNombre]");
					return 1;
				}
		        giveplayerid = ReturnUser(tmp);
				if (IsPlayerConnected(giveplayerid))
				{
				    if(giveplayerid != INVALID_PLAYER_ID)
				    {
						if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 10.0)
						{
						    if(giveplayerid == playerid) { SendClientMessage(playerid, Gris, "No puedes hacer eso a ti mismo!"); return 1; }
							format(string, sizeof(string), "* Ofreciste a %s para tener una conversación en directo.", pName(giveplayerid));
							SendClientMessage(playerid, AzulClaro, string);
							format(string, sizeof(string), "* %s te ofrecio una conversación en directo, escribe (/aceptar directo) para aceptar.", pName(playerid));
							SendClientMessage(giveplayerid, AzulClaro, string);
							LiveOffer[giveplayerid] = playerid;
						}
						else
						{
						    SendClientMessage(playerid, Rojo, "* Demasiado lejos del jugador!");
						    return 1;
						}
					}
				}
				else
				{
				    SendClientMessage(playerid, Rojo, "* Nombre /Id Invalida!");
				    return 1;
				}
			}
			else
			{
			    SendClientMessage(playerid, Rojo, "* No eres reportero!");
			}
		}
		return 1;
	}
	return 0;
}

OOCNews(color,const stringe[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(!gNews[i])
		    {
				SendClientMessage(i, color, stringe);
			}
		}
	}
}

Reporteros_OnPlayerText(playerid,text[])
{
	if(TalkingLive[playerid] != NOEXISTE)
	{
		if(PlayerInfo[playerid][pMember] == 4)
		{
		    format(string, sizeof(string), "Locutor %s: %s", pName(playerid), text);
			OOCNews(VerdeClaro, string);
		}
		else
		{
		    format(string, sizeof(string), "Invitado %s: %s", pName(playerid), text);
			OOCNews(Ocre, string);
		}
		return 1;
	}
	return 0;
}	