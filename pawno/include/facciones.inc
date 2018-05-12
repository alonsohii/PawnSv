#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>

Facciones_OnPlayerCommandText(playerid, cmdtext[])
{
	new tmp[128];
	new cmd[128];
	new idx;
	new jugador;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/darequipo", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] == 0 || PlayerInfo[playerid][pAdmin] == 1)
		{
			SendClientMessage(playerid, Rojo, "* No formas parte del staff.");
			return 1;
		}
		
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /darequipo [IdJugador/ParteDelNombre] [EquipoID]");
			return 1;
		}
		
		if(!IsNumeric(tmp))
		jugador = ReturnUser(tmp,playerid);
	   	else jugador = strval(tmp);
		
		if(!IsPlayerConnected(jugador))
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe estar conectado.");
		    return 1;
		}
		
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !IsNumeric(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /darequipo [IdJugador/ParteDelNombre] [EquipoID]");
			return 1;
		}
		
		new equipo;
		equipo = strval(tmp);
		
		format(string, sizeof(string), "* Un miembro del staff te ha puesto dentro del equipo número %d", equipo);
		SendClientMessage(jugador, Amarillo, string);
		
		format(string, sizeof(string), "* Has puesto correctamente el equipo %d a %s(%d)", equipo, pName(jugador),jugador);
		SendClientMessage(playerid, Amarillo, string);
		
		printf("ADMINLOG: %s ha puesto %s a el equipo '%d'",pName(playerid),pName(jugador),equipo);
		
		PlayerInfo[jugador][pMember] = equipo;
		PlayerInfo[jugador][pRank] = 1;
		
		SaveValue(jugador, "Faccion", PlayerInfo[jugador][pMember]);
		SaveValue(jugador, "Rango", PlayerInfo[jugador][pRank]);
		
		return 1;
	}
	
	if(strcmp(cmd, "/darrango", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 2 && PlayerInfo[playerid][pRank] != 6)
		{
			SendClientMessage(playerid, Rojo, "* No eres miembro del staff o no eres un líder de facción.");
			return 1;
		}

		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /darrango [IdJugador/ParteDelNombre] [Rango]");
			return 1;
		}

		if(!IsNumeric(tmp))
		jugador = ReturnUser(tmp,playerid);
		else jugador = strval(tmp);

		if(!IsPlayerConnected(jugador))
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe estar conectado.");
		    return 1;
		}
		
		if((PlayerInfo[playerid][pMember] != PlayerInfo[jugador][pMember]) && PlayerInfo[playerid][pAdmin] < 2)
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe ser de tu mismo equipo.");
		    return 1;
		}

		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !IsNumeric(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /darrango [IdJugador/ParteDelNombre] [Rango]");
			return 1;
		}

		new rango;
		rango = strval(tmp);

		if(rango == 0 || rango > 6) { SendClientMessage(playerid, Rojo, "* Rango entre 1 y 6 inclusives."); return 1; }
		
		format(string, sizeof(string), "* Un miembro del staff o un líder te ha promovido a rango %d", rango);
		SendClientMessage(jugador, Amarillo, string);

		format(string, sizeof(string), "* Has promovido correctamente a rango %d a %s(%d)", rango, pName(jugador) ,jugador);
		SendClientMessage(playerid, Amarillo, string);

		printf("USERLOG: %s ha dado a %s el rango '%d'",pName(playerid),pName(jugador),rango);

		
		PlayerInfo[jugador][pRank] = rango;
		SaveValue(jugador, "Rango", PlayerInfo[jugador][pRank]);

		return 1;
	}
	
	if(strcmp(cmd, "/reclutar", true) == 0)
	{
	    if(PlayerInfo[playerid][pRank] != 6)
		{
			SendClientMessage(playerid, Rojo, "* No eres un líder de facción.");
			return 1;
		}
	
	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
	    {
	        SendClientMessage(playerid, Blanco, "USO: /reclutar [IdJugador/ParteDelNombre]");
			return 1;
	    }
	    
		if(!IsNumeric(tmp))
		jugador = ReturnUser(tmp,playerid);
		else jugador = strval(tmp);

		if(!IsPlayerConnected(jugador))
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe estar conectado.");
		    return 1;
		}
		
		if(PlayerInfo[jugador][pMember] != 0)
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe ser civil.");
		    return 1;
		}
		
		if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] < 11)
		{
			if(PlayerInfo[jugador][pJob] > 0)
			{
				format(string, sizeof(string), "* No puedes reclutar a %s(%d). Tiene que dejar su trabajo para ingresar en una facción publica.", pName(jugador), jugador);
				SendClientMessage(playerid, Naranja, string);
				
				format(string, sizeof(string), "* %s(%d) quiere reclutarte para una facción publica, pero antes deberas dejar tu trabajo actual. (/dejartrabajo)", pName(playerid),playerid);
				SendClientMessage(playerid, Naranja, string);
				return 1;
			}
		}
		
		PlayerInfo[jugador][pMember] = PlayerInfo[playerid][pMember];
		PlayerInfo[jugador][pRank] = 1;
		SaveValue(jugador, "Faccion", PlayerInfo[jugador][pMember]);
		SaveValue(jugador, "Rango", PlayerInfo[jugador][pRank]);
	    
		format(string, sizeof(string), "* Has reclutado correctamente a %s(%d).", pName(jugador), jugador);
		SendClientMessage(playerid, Amarillo, string);
		format(string, sizeof(string), "* Has sido reclutado a la faccion número %d", PlayerInfo[jugador][pMember]);
		SendClientMessage(jugador, Amarillo, string);
		printf("USERLOG: %s ha reclutado a %s a la faccion '%d'",pName(playerid),pName(jugador),PlayerInfo[jugador][pMember]);
	    return 1;
	}
	
	if(strcmp(cmd, "/expulsar", true) == 0)
	{
	    if(PlayerInfo[playerid][pRank] != 6)
		{
			SendClientMessage(playerid, Rojo, "* No eres un líder de facción.");
			return 1;
		}

	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
	    {
	        SendClientMessage(playerid, Blanco, "USO: /expulsar [IdJugador/ParteDelNombre]");
			return 1;
	    }

		if(!IsNumeric(tmp))
		jugador = ReturnUser(tmp,playerid);
		else jugador = strval(tmp);

		if(!IsPlayerConnected(jugador))
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe estar conectado.");
		    return 1;
		}

		if(PlayerInfo[jugador][pMember] != PlayerInfo[playerid][pMember])
		{
		    SendClientMessage(playerid, Rojo, "* El jugador debe estar en tu facción.");
		    return 1;
		}
	
		if(PlayerInfo[jugador][pDuty] == 1)
		{
			PlayerInfo[jugador][pDuty] = 0;
			SaveValue(jugador, "EnServicio", PlayerInfo[jugador][pDuty]);
			SetPlayerSkin(jugador, PlayerInfo[jugador][pSkin]);
		}
		PlayerInfo[jugador][pUniforme] = 0;
		SaveValue(jugador, "Uniforme", 0);
		PlayerInfo[jugador][pMember] = 0;
		PlayerInfo[jugador][pRank] = 0;
		SaveValue(jugador, "Faccion", PlayerInfo[jugador][pMember]);
		SaveValue(jugador, "Rango", PlayerInfo[jugador][pRank]);

		format(string, sizeof(string), "* Has expulsado correctamente a %s(%d).", pName(jugador), jugador);
		SendClientMessage(playerid, Amarillo, string);
		format(string, sizeof(string), "* Has sido expulsado de la faccion número %d", PlayerInfo[playerid][pMember]);
		SendClientMessage(jugador, Amarillo, string);
		printf("USERLOG: %s ha expulsado a %s de la faccion '%d'",pName(playerid),pName(jugador),PlayerInfo[playerid][pMember]);
		SetPlayerSkin(jugador, PlayerInfo[jugador][pSkin]);
		
	    return 1;
	}
	
	if(strcmp(cmd, "/miembros", true) == 0)
	{
	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
	    {
			if(PlayerInfo[playerid][pMember] == 0)
			{
				SendClientMessage(playerid, Rojo, "* Debes ser miembro de una faccion.");
				return 1;
			}
			new Faccion[15];
			if(PlayerInfo[playerid][pMember] == 1) Faccion = "LSPD";
			else if(PlayerInfo[playerid][pMember] == 2) Faccion = "LSMD";
			else if(PlayerInfo[playerid][pMember] == 3) Faccion = "LSTD";
			else if(PlayerInfo[playerid][pMember] == 4) Faccion = "LSNEWS";
			else if(PlayerInfo[playerid][pMember] == 5) Faccion = "Senado";
			else if(PlayerInfo[playerid][pMember] == 6) Faccion = "Sheriff";
			else if(PlayerInfo[playerid][pMember] == 91) Faccion = "RCA";
			else if(101 > PlayerInfo[playerid][pMember] > 4) format(Faccion,sizeof(Faccion),"%d",PlayerInfo[playerid][pMember]);
						
	        format(string, sizeof(string), "Miembros Online (%s):",Faccion);
			SendClientMessage(playerid, Verde, string);
			if(PlayerInfo[playerid][pMember] < 3 || PlayerInfo[playerid][pMember] == 6)
			{
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(PlayerInfo[i][pMember] == PlayerInfo[playerid][pMember] && IsPlayerConnected(i))
					{
						format(string, sizeof(string), "%s - Rango: %d - De Servicio: ", pName(i), PlayerInfo[i][pRank]);
						if(PlayerInfo[i][pDuty] > 0)
							strcat(string, "Sí");
						else
							strcat(string, "No");
						SendClientMessage(playerid, Amarillo, string);
					}
				}
			}
			else
			{
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(PlayerInfo[i][pMember] == PlayerInfo[playerid][pMember] && IsPlayerConnected(i))
					{
						format(string, sizeof(string), "%s - Rango: %d", pName(i), PlayerInfo[i][pRank]);
						SendClientMessage(playerid, Amarillo, string);
					}
				}
			}
	    }
	    else
	    {
			if(PlayerInfo[playerid][pAdmin] >= 1)
			{
				new id;
				id = strval(tmp);
				if(id <= 0)
				{
					SendClientMessage(playerid, Rojo, "* Solo numeros mayores a 0.");
					return 1;
				}
				
				new Faccion[15];
				if(id == 1) Faccion = "LSPD";
				else if(id == 2) Faccion = "LSMD";
				else if(id == 3) Faccion = "LSTD";
				else if(id == 4) Faccion = "LSNEWS";
				else if(id == 5) Faccion = "Senado";
				else if(id == 6) Faccion = "Sheriff";
				else if(id > 4) format(Faccion,sizeof(Faccion),"%d",id);
						
				format(string, sizeof(string), "Miembros Online (%s):",Faccion);
				SendClientMessage(playerid, Verde, string);
				if(id < 3 || id == 6)
				{
					for(new i; i < MAX_PLAYERS; i++)
					{
						if(PlayerInfo[i][pMember] == id && IsPlayerConnected(i))
						{
							format(string, sizeof(string), "%s - Rango: %d - De Servicio: ", pName(i), PlayerInfo[i][pRank]);
							if(PlayerInfo[i][pDuty] > 0)
								strcat(string, "Sí");
							else
								strcat(string, "No");
							SendClientMessage(playerid, Amarillo, string);
						}
					}
				}
				else
				{
					for(new i; i < MAX_PLAYERS; i++)
					{
						if(PlayerInfo[i][pMember] == id && IsPlayerConnected(i))
						{
							format(string, sizeof(string), "%s - Rango: %d", pName(i), PlayerInfo[i][pRank]);
							SendClientMessage(playerid, Amarillo, string);
						}
					}
				}
			} 
			else { SendClientMessage(playerid, Rojo, "* No formas parte del Staff!"); return 1; }
		}
		return 1;
	}
	return 0;
}