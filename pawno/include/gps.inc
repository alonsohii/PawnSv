#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

GPS_OnPlayerStream(playerid, forplayerid)
{
	if(PlayerInfo[playerid][pRefuerzos] == 1)
	{
		if(PlayerInfo[forplayerid][pMember] == PlayerInfo[playerid][pMember])
		{
			SetPlayerMarkerForPlayer(forplayerid, playerid, AzulOscuro);
		}
	}
	else if(PlayerInfo[playerid][pRefuerzos] == 2)
	{
		if(PlayerInfo[forplayerid][pMember] == 1)
		{
			SetPlayerMarkerForPlayer(forplayerid, playerid, Amarillo);
		}
	}
	else if(PlayerInfo[playerid][pRefuerzos] == 3)
	{
		if(IsACop(forplayerid) || IsAMedic(forplayerid))
		{
			SetPlayerMarkerForPlayer(forplayerid, playerid, Morado);
		}
	}
	return 1;
}

GPS_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/marcar", true) == 0)
	{
		if(!IsACop(playerid) && !IsAMedic(playerid))
		{
			SendClientMessage(playerid, Rojo, "* No eres policía ni paramédico.");
			return 1;
		}
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid,Rojo,"* No estás de servicio. (/deservicio)"); return 1; }
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !IsNumeric(tmp) || strval(tmp) > 3)
		{
			SendClientMessage(playerid, Blanco, "USO: /marcar [0/1/2/3]");
			if(PlayerInfo[playerid][pMember]==1) SendClientMessage(playerid, Blanco, "0 - Cancelar | 1 - Refuerzos ((/rr)) | 2 - Grua | 3 - LSPD & LSMD");
			else SendClientMessage(playerid, Blanco, "0 - Cancelar | 1 - Refuerzos | 2 - Grua | 3 - LSPD & LSMD");
			return 1;
		}
		new tipo = strval(tmp);
		switch(tipo)
		{
			case 0:
			{
				if(PlayerInfo[playerid][pRefuerzos] == 0) return 1;
				for(new i; i < MAX_PLAYERS; i++)
				{
					switch(PlayerInfo[playerid][pRefuerzos])
					{
						case 1:
						{
							if(PlayerInfo[i][pMember] == PlayerInfo[playerid][pMember] && PlayerInfo[i][pDuty] == 1)
							{
								format(string, 128, "* %s ha cancelado la solicitud de asistencia.", pName(playerid));
								SendClientMessage(i, Verde, string);
								SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
							}
						}
						case 2:
						{
							if(PlayerInfo[i][pMember] == 1 && PlayerInfo[i][pDuty] == 1)
							{
								format(string, 128, "* %s ha cancelado la solicitud de asistencia.", pName(playerid));
								SendClientMessage(i, Verde, string);
								SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
							}
						}
						case 3:
						{
							if((PlayerInfo[i][pMember] == 1 || PlayerInfo[i][pMember] == 2) && PlayerInfo[i][pDuty] == 1)
							{
								format(string, 128, "* %s ha cancelado la solicitud de asistencia.", pName(playerid));
								SendClientMessage(i, Verde, string);
								SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
							}
						}
					}
				}
				PlayerInfo[playerid][pRefuerzos] = 0;
			}
			case 1:
			{
				if(PlayerInfo[playerid][pRefuerzos] > 0) return 1;
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(PlayerInfo[i][pMember] == PlayerInfo[playerid][pMember])
					{
						SetPlayerMarkerForPlayer(i, playerid, AzulOscuro);
					}
				}
				SendClientMessage(playerid, Azul, "* Has marcado la posición para los refuerzos.");
				format(string, 128, "%s solicita refuerzos en la posición marcada en el GPS.", pName(playerid));
				SendFamilyMessageOnDuty(PlayerInfo[playerid][pMember], Azul, string);
				PlayerInfo[playerid][pRefuerzos] = 1;
			}
			case 2:
			{
				if(PlayerInfo[playerid][pRefuerzos] > 0) return 1;
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(PlayerInfo[i][pMember] == 1)
					{
						SetPlayerMarkerForPlayer(i, playerid, Amarillo);
					}
				}
				SendClientMessage(playerid, Azul, "* Has marcado la posición para las gruas.");
				format(string, 128, "%s solicita gruas en la posición marcada en el GPS.", pName(playerid));
				SendFamilyMessageOnDuty(1, Azul, string);
				PlayerInfo[playerid][pRefuerzos] = 2;
			}
			case 3:
			{
				if(PlayerInfo[playerid][pRefuerzos] > 0) return 1;
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(IsACop(i) || IsAMedic(i))
					{
						SetPlayerMarkerForPlayer(i, playerid, Morado);
					}
				}
				SendClientMessage(playerid, Azul, "* Has marcado la posición para todos los departamentos.");
				format(string, 128, "%s solicita la presencia de todos los departamentos estatales en la marca del GPS.", pName(playerid));
				SendFamilyMessageOnDuty(1, Azul, string);
				SendFamilyMessageOnDuty(2, Azul, string);
				SendFamilyMessageOnDuty(6, Azul, string);
				PlayerInfo[playerid][pRefuerzos] = 3;
			}
			
			default:
			{
				SendClientMessage(playerid, Blanco, "USO: /marcar [0/1/2/3]");
			}
		}
		return 1;
	}
	if(strcmp(cmd,"/rr",true)==0)
	{
		GPS_OnPlayerCommandText(playerid, "/marcar 1");
	}
	if(strcmp(cmd,"/norr",true)==0)
	{
		GPS_OnPlayerCommandText(playerid, "/marcar 0");
	}
	
	return 0;
}