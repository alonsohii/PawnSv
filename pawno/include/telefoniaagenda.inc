#include <a_samp>
#include <globalvars>
#include <colores>

new AgendaE[MAX_PLAYERS];
enum aDatos
{
	aNombre[24],
	aNumero,
}
new AgendaMemoria[MAX_PLAYERS][aDatos];

new MaxRegistros;

new Escribiendo[MAX_PLAYERS];
new ActiveNumber[MAX_PLAYERS]; //Numero de telefono que usa (para llamar o sms)

LoadFrecuencias()
{
	new sql[80], row[512], count,TotalFrecuencias;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM frecuencias");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	count = strval(row);
	
	for (new idx=1; idx<=count; idx++)
	{
		format(sql, sizeof(sql), "SELECT * FROM frecuencias WHERE id=%d LIMIT 1", idx);
	    mysql_query(sql);
	    mysql_store_result();
     	mysql_fetch_row(row);
		split(row, arrCoords, '|');
	
		Frecuencia[idx][fId] = strval(arrCoords[0]);
		format(Frecuencia[idx][fPassword], 128, "%s", arrCoords[1]);
		format(Frecuencia[idx][fDueno], 24, "%s", arrCoords[2]);	
		TotalFrecuencias++;
	}
	printf("Frecuencias cargadas: %d (MAX: %d)",TotalFrecuencias,MAX_FRECUENCIAS);
	return 1;
}

SaveFrecuencias(idx)
{
	format(string, 128, "UPDATE frecuencias SET Password='%s' WHERE id = %d",
		Frecuencia[idx][fPassword],
		Frecuencia[idx][fId]);
	mysql_query(string);
	return 1;
}

LoadAgenda()
{
	new sql[80], row[512], count;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM agenda");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	count = strval(row);
	
	for (new idx=1; idx<=count; idx++)
	{
		format(sql, sizeof(sql), "SELECT * FROM agenda WHERE id=%d LIMIT 1", idx);
	    mysql_query(sql);
	    mysql_store_result();
     	mysql_fetch_row(row);
		split(row, arrCoords, '|');
	
		Registro[idx][rId] = strval(arrCoords[0]);
		format(Registro[idx][rNombre], 24, "%s", arrCoords[1]);
		Registro[idx][rNumero] = strval(arrCoords[2]);
		Registro[idx][rProp] = strval(arrCoords[3]);
	}
	
	MaxRegistros = count;
	return 1;
}

stock SaveAgenda(idx)
{
	format(string, 128, "UPDATE agenda SET nombre='%s', numero=%d, propietario=%d WHERE id=%d",
		Registro[idx][rNombre],
		Registro[idx][rNumero],
		Registro[idx][rProp],
		Registro[idx][rId]);
	mysql_query(string);
	return 1;
}

Frecuencias(playerid, accion, numeros[])
{
	if(PlayerInfo[playerid][pWalkies] == 0) return SendClientMessage(playerid, Rojo, "* No tienes el equipo de radio.");
	switch(accion)
	{
		case 1:
		{
			if(strlen(numeros))
			{
				SendClientMessage(playerid, Gris, "* Conectando...");
				new frecuencia = strval(numeros);
				for(new i = 0; i < MAX_FRECUENCIAS; i++)
				{
					if(Frecuencia[i][fId] == frecuencia)
					{
						if(!strlen(Frecuencia[i][fPassword]))
						{
							PlayerInfo[playerid][pFrecuencia] = frecuencia;
							SendClientMessage(playerid, Verde, "* Conectado a la frecuencia");
							SaveValue(playerid, "Frecuencia", PlayerInfo[playerid][pFrecuencia]);
							break;
						}
						else
						{
							SendClientMessage(playerid, Naranja, "* Esta frecuencia tiene activada una contraseña, escribela.");
							Escribiendo[playerid] = i;
							break;
						}
					}
				}
			}
			else
			{
				SendClientMessage(playerid, Blanco, "USO: /frecuencias conectar [1-25]");
			}
		}
		case 2:
		{
			if(PlayerInfo[playerid][pFrecuencia] != 0)
			{
				PlayerInfo[playerid][pFrecuencia] = 0;
				SendClientMessage(playerid, Naranja, "* Desconectado de la frecuencia");
				SaveValue(playerid, "Frecuencia", PlayerInfo[playerid][pFrecuencia]);
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* Estás desconectado");
			}
		}
		case 3:
		{
			if(SafeGetPlayerMoney(playerid) < 20000) return SendClientMessage(playerid, Rojo, "* No tienes dinero suficiente.");
			if(PlayerInfo[playerid][pMiFrecuencia] == 0)
			{
				new row[256], id, sql[128];
				format(sql, 128, "INSERT INTO frecuencias (dueno) VALUES ('%s')", pNameEx(playerid));
				mysql_query(sql);
				
				format(sql, 128, "SELECT id FROM frecuencias WHERE dueno LIKE '%s'", pNameEx(playerid));
				mysql_query(sql);
				mysql_store_result();
				mysql_fetch_row(row);
				id = strval(row);
				
				for(new i = 0; i < MAX_FRECUENCIAS; i++)
				{
					if(Frecuencia[i][fId] == 0)
					{
						Frecuencia[i][fId] = id;
						format(Frecuencia[i][fDueno], 24, "%s", pName(playerid));
						format(Frecuencia[i][fPassword], 128, "");
						SaveFrecuencias(i);
						PlayerInfo[playerid][pMiFrecuencia] = id;
						SaveValue(playerid, "MiFrecuencia", PlayerInfo[playerid][pMiFrecuencia]);
						format(string, 128, "Has alquilado la frecuencia %d", id);
						SendClientMessage(playerid, Verde, string);
                        SafeGivePlayerMoney(playerid,-20000);
						break;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* Ya tienes una frecuencia");
			}
		}
		case 4:
		{
			if(!strlen(numeros)) return SendClientMessage(playerid, Blanco, "USO: /frecuencias configurar [Password]");
			
			if(PlayerInfo[playerid][pMiFrecuencia] != 0)
			{
				new frecuencia = PlayerInfo[playerid][pMiFrecuencia];
				for(new i = 0; i < MAX_FRECUENCIAS; i++)
				{
					if(Frecuencia[i][fId] == frecuencia)
					{
						format(Frecuencia[i][fPassword], 128, "%s", numeros);
						format(string, 128, "* Has cambiado la password de la frecuencia a: '%s'", Frecuencia[i][fPassword]);
						SaveFrecuencias(i);
						break;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No eres dueño de ninguna frecuencia.");
			}
		}
	}
	return 1;
}

Agenda(playerid, operacion, letras[], id[])
{
	new count;
	switch(operacion)
	{
		case 1:
		{ 	// Agregar a la agenda
			SendClientMessage(playerid, Amarillo, "Nuevo contacto de agenda.");
			SendClientMessage(playerid, AmarilloClaro, "Ingresa un nombre para este contacto.");
			AgendaE[playerid] = 1;
		}
		case 2:
		{
			//Borrar de la agenda
			SendClientMessage(playerid, Amarillo, "Borrar contacto de la agenda.");
			SendClientMessage(playerid, AmarilloClaro, "Ingresa el nombre del contacto (o el número de teléfono).");
			AgendaE[playerid] = 10;
		}
		case 3:
		{
			//Ver agenda
			SendClientMessage(playerid, Amarillo, "Agenda del móvil");
			if(strlen(letras))
			{
				format(string, 128, "Contactos que contienen %s:", letras);
				SendClientMessage(playerid, AmarilloClaro, string);
				
				for(new i= 1; i <= MaxRegistros; i++)
				{
					if(Registro[i][rId] == NOEXISTE) { continue; }
					if(Registro[i][rProp] == PlayerInfo[playerid][pSQLID])
					{
						if(strfind(Registro[i][rNombre], letras, true, 0) != -1)
						{
							format(string, 128, "- %s - %d", Registro[i][rNombre], Registro[i][rNumero]);
							SendClientMessage(playerid, AmarilloClaro, string);
						}
					}
				}
			}
			else
			{
				format(string, 128, "Algunos contactos (Usa /agenda ver [Letra(s)] para buscar un contacto exacto):");
				SendClientMessage(playerid, AmarilloClaro, string);
				
				new p = 0;
				for(new i= 1; i <= MaxRegistros; i++)
				{
					if(Registro[i][rId] == NOEXISTE) continue;
					if(Registro[i][rProp] == PlayerInfo[playerid][pSQLID])
					{
						if(p == 20) break;
						format(string, 128, "- %s - %d", Registro[i][rNombre], Registro[i][rNumero]);
						SendClientMessage(playerid, AmarilloClaro, string);
						p++;
					}
				}
			}
		}
		case 4:
		{
			if(strlen(id) <= 3 && strlen(id) > 0)
			{
				new player;
				player = strval(id);
				if(IsPlayerConnected(player))
				{
					for(new i = 1; i <= MaxRegistros; i++)
					{
						if(Registro[i][rId] == NOEXISTE) continue;
						
						if(Registro[i][rNumero] == PlayerInfo[player][pPnumber][0])
						{
							if(Registro[i][rProp] == PlayerInfo[playerid][pSQLID])
							{
								return PlayerInfo[player][pPnumber][0];
							}
						}
						if(Registro[i][rNumero] == PlayerInfo[player][pPnumber][1])
						{
							if(Registro[i][rProp] == PlayerInfo[playerid][pSQLID])
							{
								return PlayerInfo[player][pPnumber][1];
							}
						}
					}
				}
			}
			else if(strlen(letras))
			{
				for(new i; i < MaxRegistros; i++)
				{
					if(Registro[i][rId] == NOEXISTE) continue;
					
					if(Registro[i][rProp] == PlayerInfo[playerid][pSQLID])
					{
						if(strcmp(Registro[i][rNombre], letras, true) == 0)
						{
							count = Registro[i][rNumero];
						}
					}
				}
				if(count > 0) return count;
				else
				{
					new player;
					player = ReturnUser(letras);
					format(string, 128, "%d", player);
					return Agenda(playerid, 4, "", string);
				}
			}
		}
	}
	return 1;
}

LlamarTelefono(playerid, telefono)
{
	new tlf = 0;
	
	if(PlayerInfo[playerid][pPnumber][0] == 0 && PlayerInfo[playerid][pPnumber][1] == 0) return SendClientMessage(playerid, Rojo, "* No tienes movil!");
	if(PlayerInfo[playerid][pUsandoTelefono] >= 1) return SendClientMessage(playerid, Rojo, "* Estás en una llamada.");
	
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
//		if(IsValidNPC(i)) continue;
		
		if(PlayerInfo[i][pPnumber][0] == telefono || PlayerInfo[i][pPnumber][1] == telefono)
		{
			if(PlayerInfo[i][pUsandoTelefono] == 0 && PlayerInfo[i][pIncomingCall] == NOEXISTE && PlayerInfo[i][pPTelEstado] == 1)
			{
				PlayerInfo[playerid][pUsandoTelefono] = 1;
				tlf = 1;
				PlayerInfo[i][pIncomingCall] = playerid;
				PlayerInfo[playerid][pIncomingCall] = i;
				SetPlayerSpecialAction(playerid, 11);
				format(string, 128, "Está sonando tu teléfono %d.", telefono);
				SendClientMessage(i, AmarilloClaro, string);
				format(string, 128, "Tienes una llamada entrante de %d. ¿/Contestar?", PlayerInfo[playerid][pPnumber][ActiveNumber[playerid]]);
				SendClientMessage(i, Amarillo, string);
				format(string, 128, "* El teléfono de %s está sonando.", pName(i)); 
				if(GetPlayerInterior(i) > 0) {
				ProxDetector(12.0, i, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, i, string,Morado, Morado, Morado, Morado, Morado);}
				format(string, 128, "* %s saca el teléfono y marca un número.", pName(playerid));
				if(GetPlayerInterior(playerid) > 0) {
				ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				SendClientMessage(playerid, Gris, "Llamando...");
				EscucharEfectoEx(i, 4, 5.0);
                PlayerInfo[i][pNotificaciones]=0;
				PlayerInfo[playerid][pTimerCall] = SetTimerEx("Notificar", 4000, 1, "d", i);
				break;
			}
		}
	}
	
	if(tlf == 0)
	{
		SendClientMessage(playerid, Gris, "* Escuchas el tono de ocupado...");
	}
	
	return 1;
}

ColgarTelefono(playerid)
{
	if(PlayerInfo[playerid][pPnumber][0] == 0 && PlayerInfo[playerid][pPnumber][1] == 0 && !IsACop(playerid) && !IsAMedic(playerid)) { SendClientMessage(playerid, Rojo, "* No tienes movil!"); return 1;}
	
	if(PlayerInfo[playerid][pUsandoTelefono] == 1)
	{
		new player = PlayerInfo[playerid][pIncomingCall];
		
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		format(string, 128, "* %s cuelga y guarda su teléfono.", pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		KillTimer(PlayerInfo[playerid][pTimerCall]);
		format(string, 128, "* Tienes una llamada perdida de: %d", PlayerInfo[playerid][pPnumber][ActiveNumber[playerid]]);
		SendClientMessage(player, Gris, string);
		PlayerInfo[playerid][pUsandoTelefono] = 0;
		
		PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pIncomingCall] = NOEXISTE;
		PlayerInfo[playerid][pIncomingCall] = NOEXISTE;
	}
	else if(PlayerInfo[playerid][pUsandoTelefono] == 911 || PlayerInfo[playerid][pUsandoTelefono] == 912 || PlayerInfo[playerid][pUsandoTelefono] == 913)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		format(string, 128, "* %s cuelga y guarda su teléfono.", pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		PlayerInfo[playerid][pUsandoTelefono] = 0;
		PlayerInfo[playerid][pIncomingCall] = NOEXISTE;
	}
	else if(PlayerInfo[playerid][pUsandoTelefono] == 2 || PlayerInfo[playerid][pUsandoTelefono] == 3 || PlayerInfo[playerid][pUsandoTelefono] == 914 || PlayerInfo[playerid][pUsandoTelefono] == 915)
	{
		new player = PlayerInfo[playerid][pIncomingCall];
		SendClientMessage(playerid, Gris, "* Colgaste");
		SendClientMessage(player, Gris, "* Colgaron");
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		SetPlayerSpecialAction(player, SPECIAL_ACTION_STOPUSECELLPHONE);
		PlayerInfo[playerid][pUsandoTelefono] = 0;
		PlayerInfo[player][pUsandoTelefono] = 0;
		format(string, 128, "* %s cuelga y guarda su teléfono.", pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		format(string, 128, "* %s guarda su teléfono.", pName(player));
		if(GetPlayerInterior(player) > 0) {
		ProxDetector(12.0, player, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, player, string,Morado, Morado, Morado, Morado, Morado);}
		PlayerInfo[playerid][pIncomingCall] = NOEXISTE;
		PlayerInfo[player][pIncomingCall] = NOEXISTE;
	}
	else if(PlayerInfo[playerid][pUsandoTelefono] == 4)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		format(string, 128, "* %s cuelga y guarda su teléfono.", pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		PlayerInfo[playerid][pIncomingCall] = NOEXISTE;
		PlayerInfo[playerid][pUsandoTelefono] = 0;
	}
	return 1;
}

forward Notificar(playerid);
public Notificar(playerid)
{
	if(PlayerInfo[playerid][pNotificaciones] == 4)
	{
		KillTimer(PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pTimerCall]);
		SendClientMessage(PlayerInfo[playerid][pIncomingCall], Gris, "* El telefono que marcaste no contesta. Deja un mensaje si lo deseas. (/colgar para cancelar.)");
		format(string, 128, "* Tienes una llamada perdida de: %d", PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pPnumber][0]);
		SendClientMessage(playerid, Gris, string);
		SetPlayerSpecialAction(PlayerInfo[playerid][pIncomingCall], 0);
		PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pUsandoTelefono] = 4;
		PlayerInfo[playerid][pIncomingCall] = NOEXISTE;
	}
	format(string, 128, "* El teléfono de %s está sonando.", pName(playerid)); 
	if(GetPlayerInterior(playerid) > 0) {
	ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
	else {
	ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
	SendClientMessage(PlayerInfo[playerid][pIncomingCall], Gris, "Llamando...");
	EscucharEfectoEx(playerid, 4, 5.0);
	PlayerInfo[playerid][pNotificaciones]++;
}

Tlf_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmdtext, "/contestar", true) == 0)
	{
		if(PlayerInfo[playerid][pIncomingCall] == NOEXISTE)
		{
			if(IsACop(playerid))
			{
				new procede = NOEXISTE;
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(PlayerInfo[i][pUsandoTelefono] == 912)
					{
						procede = i;
						break;
					}
				}
				
				if(procede != NOEXISTE)
				{
					new i;
					i = procede;
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
					SetPlayerSpecialAction(i,SPECIAL_ACTION_USECELLPHONE);
					PlayerInfo[playerid][pIncomingCall] = i; //caller connecting
					PlayerInfo[i][pIncomingCall] = playerid;
					SendClientMessage(i,  Gris, "   Cogieron la llamada.");
					PlayerInfo[playerid][pUsandoTelefono] = 2;
					PlayerInfo[i][pUsandoTelefono] = 914;
					format(string, sizeof(string), "* %s contesta su llamada de emergencia.", pName(playerid));
					ProxDetector(30.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
				}
			}
			if(IsAMedic(playerid))
			{
				new procede = NOEXISTE;
				for(new i; i < MAX_PLAYERS; i++)
				{
					if(PlayerInfo[i][pUsandoTelefono] == 913)
					{
						procede = i;
						break;
					}
				}
				
				if(procede != NOEXISTE)
				{
					new i;
					i = procede;
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
					SetPlayerSpecialAction(i,SPECIAL_ACTION_USECELLPHONE);
					PlayerInfo[playerid][pIncomingCall] = i; //caller connecting
					PlayerInfo[i][pIncomingCall] = playerid;
					SendClientMessage(i,  Gris, "   Cogieron la llamada.");
					PlayerInfo[playerid][pUsandoTelefono] = 2;
					PlayerInfo[i][pUsandoTelefono] = 915;
					format(string, sizeof(string), "* %s contesta su llamada de emergencia.", pName(playerid));
					ProxDetector(30.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
				}
			}
		}
		if(PlayerInfo[playerid][pIncomingCall] > NOEXISTE && PlayerInfo[playerid][pUsandoTelefono] == 0)
		{
			SendClientMessage(playerid, Amarillo, "Contestaste la llamada. Usa T para hablar. Usa (/col)gar cuando termines.");
			SendClientMessage(PlayerInfo[playerid][pIncomingCall], Amarillo, "Te han contestado, se te cobrará $20 por minuto.");
			PlayerInfo[playerid][pUsandoTelefono] = 2;
			PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pUsandoTelefono] = 3;
			SetPlayerSpecialAction(playerid, 11);
			KillTimer(PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pTimerCall]);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/frecuencias", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /frecuencias [Accion]");
			SendClientMessage(playerid, Blanco, "Acciones: Conectar, Desconectar, Alquilar, Configurar");
			return 1;
		}
		else if(strcmp(tmp, "Conectar", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			Frecuencias(playerid, 1, tmp);
		}
		else if(strcmp(tmp, "Desconectar", true) == 0)
		{
			Frecuencias(playerid, 2, "");
		}
		else if(strcmp(tmp, "Alquilar", true) == 0)
		{
			Frecuencias(playerid, 3, "");
		}
		else if(strcmp(tmp, "Configurar", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			Frecuencias(playerid, 4, tmp);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/agenda", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /agenda [Ver|Nuevo|Borrar]");
		}
		else if(strcmp(tmp, "Ver", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			Agenda(playerid, 3, tmp, "");
		}
		else if(strcmp(tmp, "Borrar", true) == 0)
		{
			Agenda(playerid, 2, "", "");
		}
		else if(strcmp(tmp, "Nuevo", true) == 0)
		{
			Agenda(playerid, 1, "", "");
		}
		return 1;
	}

	if(strcmp(cmd, "/sms", true) == 0)
	{
	    tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Gris, "USO: /sms [numero] [mensaje]");
			return 1;
		}
		if(PlayerInfo[playerid][pPnumber][0] == 0 && PlayerInfo[playerid][pPnumber][1] == 0)
		{
			SendClientMessage(playerid, Gris, "  No tienes teléfono móvil...");
			return 1;
		}
			
		format(string, sizeof(string), "* %s saca su teléfono y escribe un mensaje.", pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		
		new phonenumb;
		if(IsNumeric(tmp))
		{
			phonenumb = strval(tmp);
		}
/*		else
		{
			phonenumb = Agenda(playerid, 4, tmp, "");
		}*/
		
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
			SendClientMessage(playerid, Gris, "USO: /sms [numero] [mensaje]");
			return 1;
		}
		
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
				if( (PlayerInfo[i][pPnumber][0] == phonenumb || PlayerInfo[i][pPnumber][1] == phonenumb) && phonenumb != 0)
				{
					format(string, sizeof(string), "SMS: %s, Tlf: %d", result,PlayerInfo[playerid][pPnumber][ActiveNumber[playerid]]);
					SendClientMessage(i, Amarillo, string);
					format(string, sizeof(string), "SMS: %s, Tlf: %d", result,phonenumb);
					SendClientMessage(playerid,  Gris, string);
					SendClientMessage(playerid, Gris, "Mensaje enviado");
					SafeGivePlayerMoney(playerid,-5);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					EscucharEfectoEx(i, 7, 5.0);
					for(new x=0; x<MAX_PLAYERS; x++)
					{
						if(PlayerInfo[x][pBigAntena] == 1)
						{
						format(string,sizeof(string),"[SMS] %s(%d) ha enviado un sms a %s(%d)", pName(playerid), playerid, pName(i), i);
						SendClientMessage(x, Amarillo, string);
						format(string,sizeof(string),"Mensaje: %s",result);
						SendClientMessage(x, AmarilloClaro, string);
						}
					}
					return 1;
				}
			}
		}
	}
    
        
	if(strcmp(cmd, "/tlfactivo", true) == 0)
	{
        if (ActiveNumber[playerid]==0)
        {
            if (PlayerInfo[playerid][pPnumber][1]>0)
            {
                ActiveNumber[playerid]=1;
                format(string,sizeof(string),"Tu número activo ahora es %d", PlayerInfo[playerid][pPnumber][1]);
                SendClientMessage(playerid,Verde,string);
            }
        }
        else
        {
            if (PlayerInfo[playerid][pPnumber][0]>0)
            {
                ActiveNumber[playerid]=0;
                format(string,sizeof(string),"Tu número activo ahora es %d", PlayerInfo[playerid][pPnumber][0]);
                SendClientMessage(playerid,Verde,string);
            }
        }
        return 1;
    }
	
	if(strcmp(cmd, "/tlftoggle", true) == 0)
	{
		if (GetPlayerPremium(playerid) == 0) return 1;
        if (PlayerInfo[playerid][pPTelEstado]==0)
        {
            if (PlayerInfo[playerid][pPnumber][0]>0 || PlayerInfo[playerid][pPnumber][1]>0)
            {
                PlayerInfo[playerid][pPTelEstado] = 1;
                SendClientMessage(playerid,Verde," * Móvil encendido");
            }
        }
        else
        {
            if (PlayerInfo[playerid][pPnumber][0]>0 || PlayerInfo[playerid][pPnumber][1]>0)
            {
                PlayerInfo[playerid][pPTelEstado] = 0;
                SendClientMessage(playerid,Verde," * Móvil apagado");
            }
        }
        return 1;
    }
        

	return 0;
}

Tlf_OnPlayerText(playerid, text[])
{
	if(PlayerInfo[playerid][pUsandoTelefono] == 2 || PlayerInfo[playerid][pUsandoTelefono] == 3 || PlayerInfo[playerid][pUsandoTelefono] == 914 || PlayerInfo[playerid][pUsandoTelefono] == 915)
	{
		format(string, 128, "(Teléfono): %s", text);
		SendClientMessage(PlayerInfo[playerid][pIncomingCall], Amarillo, string);
		ProxDetector(5.0, playerid, string, Gris, Gris, Gris, Gris, Gris);
		return 1;
	}
	else if(PlayerInfo[playerid][pUsandoTelefono] == 4)
	{
		format(string, 128, "Mensaje de Voz: %s, Tlf: %d", text, PlayerInfo[playerid][pPnumber][ActiveNumber[playerid]]);
		SendClientMessage(PlayerInfo[playerid][pIncomingCall], Amarillo, string);
		format(string, 128, "Mensaje de Voz: %s, Tlf: %d", text, PlayerInfo[playerid][pIncomingCall]);
		SendClientMessage(playerid, Gris, string);
		ColgarTelefono(playerid);
		return 1;
	}
	else if(AgendaE[playerid] == 1)
	{
		format(AgendaMemoria[playerid][aNombre], 24, "%s", text);
		SendClientMessage(playerid, Amarillo, "Ahora ingresa el número de este contacto.");
		AgendaE[playerid] = 2;
		return 1;
	}
	else if(AgendaE[playerid] == 2)
	{
		new count;
		AgendaMemoria[playerid][aNumero] = strval(text);
		format(string, 128, "Contacto: %s con número: %d - Creado.", AgendaMemoria[playerid][aNombre], AgendaMemoria[playerid][aNumero]);
		SendClientMessage(playerid, AmarilloClaro, string);
		format(string, 128, "INSERT INTO agenda (nombre, numero, propietario) VALUES ('%s',%d,%d)", AgendaMemoria[playerid][aNombre], AgendaMemoria[playerid][aNumero], PlayerInfo[playerid][pSQLID]);
		mysql_query(string);
		count = MaxRegistros +1;
		
		Registro[count][rId] = count;
		format(Registro[count][rNombre], 24, "%s", AgendaMemoria[playerid][aNombre]);
		Registro[count][rNumero] = AgendaMemoria[playerid][aNumero];
		Registro[count][rProp] = PlayerInfo[playerid][pSQLID];
		
		MaxRegistros++;
		
		AgendaE[playerid] = 0;
		return 1;
	}
	else if(AgendaE[playerid] == 10)
	{	
		new id = 0;
		for(new i = 1; i <= MaxRegistros; i++)
		{
			if(Registro[i][rId] == NOEXISTE) continue;
			
			if(Registro[i][rProp] == PlayerInfo[playerid][pSQLID])
			{
				if(Registro[i][rNumero] == strval(text))
				{
					id = i;
				}
				else if(strcmp(Registro[i][rNombre], text, true) == 0)
				{
					id = i;
				}
			}
		}
		
		if(id == 0)
		{
			SendClientMessage(playerid, Naranja, "* Ningun contacto concuerda con tu busqueda.");
			AgendaE[playerid] = 0;
			return 1;
		}
		
		if(IsNumeric(text))
		{
			format(string, 128, "¿Seguro que quieres eliminar a '%d' de tu agenda? Escribe 'Si' o 'No'.", strval(text));
		}
		else
		{
			format(string, 128, "¿Seguro que quieres eliminar a '%s' de tu agenda? Escribe 'Si' o 'No'.", text);
		}
		SendClientMessage(playerid, Amarillo, string);
		AgendaMemoria[playerid][aNumero] = id;
		AgendaE[playerid] = 11;
		return 1;
	}
	else if(AgendaE[playerid] == 11)
	{
		if(strcmp(text, "Si", true) == 0)
		{
			format(string, 128,"DELETE FROM agenda WHERE id = %d", Registro[AgendaMemoria[playerid][aNumero]][rId]);
			mysql_query(string);
			SendClientMessage(playerid, Verde, "Eliminado de la agenda.");
			AgendaE[playerid] = 0;
			Registro[AgendaMemoria[playerid][aNumero]][rId] = NOEXISTE;
			return 1;
		}
		else if(strcmp(text, "No", true) == 0)
		{
			SendClientMessage(playerid, Rojo, "Operación abortada.");
			AgendaE[playerid] = 0;
			return 1;
		}
	}
	else if(Escribiendo[playerid] > NOEXISTE)
	{
		new frec = Escribiendo[playerid];
		if(strcmp(Frecuencia[frec][fPassword], text, true) == 0)
		{
			PlayerInfo[playerid][pFrecuencia] = Frecuencia[frec][fId];
			SendClientMessage(playerid, Verde, "* Password aceptada. Frecuencia sintonizada correctamente.");
			Escribiendo[playerid] = NOEXISTE;
			SaveValue(playerid, "Frecuencia", PlayerInfo[playerid][pFrecuencia]);
			return 1;
		}
		else 
		{
			SendClientMessage(playerid, Rojo, "* Password incorrecta. Operación abortada.");
			Escribiendo[playerid] = NOEXISTE;
			return 1;
		}
	}

	return 0;
}


Tlf_OnPlayerDisconnect(playerid)
{
	if(PlayerInfo[playerid][pUsandoTelefono] > 0)
	{
		ColgarTelefono(playerid);
		AgendaE[playerid] = 0;
	}
}

Tlf_OnPlayerConnect(playerid)
{
	PlayerInfo[playerid][pUsandoTelefono] = 0;
	PlayerInfo[playerid][pIncomingCall] = NOEXISTE;
	Escribiendo[playerid] = NOEXISTE;
}