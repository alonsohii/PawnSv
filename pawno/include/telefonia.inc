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
new Escribiendo[MAX_PLAYERS];

LoadFrecuencias()
{
	new sql[80], row[512], count;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM frecuencias");
	samp_mysql_query(sql);
	samp_mysql_store_result();
	samp_mysql_fetch_row(row);
	count = strval(row);
	
	for (new idx=1; idx<=count; idx++)
	{
		format(sql, sizeof(sql), "SELECT * FROM frecuencias WHERE id=%d LIMIT 1", idx);
	    samp_mysql_query(sql);
	    samp_mysql_store_result();
     	samp_mysql_fetch_row(row);
		split(row, arrCoords, '|');
	
		Frecuencia[idx][fId] = strval(arrCoords[0]);
		format(Frecuencia[idx][fPassword], 128, "%s", arrCoords[1]);
		format(Frecuencia[idx][fDueno], 24, "%s", arrCoords[2]);		
	}
	samp_mysql_free_result();
	return 1;
}

SaveFrecuencias(idx)
{
	format(string, 128, "UPDATE frecuencias SET Password='%s' WHERE id = %d",
		Frecuencia[idx][fPassword],
		Frecuencia[idx][fId]);
	samp_mysql_query(string);
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
				SendClientMessage(playerid, Blanco, "USO: /frecuencias conectar [1-100]");
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
				samp_mysql_query(sql);
				
				format(sql, 128, "SELECT id FROM frecuencias WHERE dueno LIKE '%s'", pNameEx(playerid));
				samp_mysql_query(sql);
				samp_mysql_store_result();
				samp_mysql_fetch_row(row);
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
						break;
					}
				}
				samp_mysql_free_result();
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
/*
Agenda(playerid, operacion, letras[], id[])
{
	new row[64], sql[128], count;
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
				format(string, 128, "Contactos que comienzan con %s:", letras);
			}
			else
			{
				format(string, 128, "Algunos contactos (Usa /agenda ver [Letra(s)] para buscar un contacto exacto):");
			}
			SendClientMessage(playerid, AmarilloClaro, string);
			format(sql, 128, "SELECT COUNT(*) FROM agenda");
			samp_mysql_query(sql);
			samp_mysql_store_result();
			samp_mysql_fetch_row(row);
			count = strval(row);
			
			new count2 = 0, countsql = 0;
			
			for(new i=1; i <= count; i++)
			{
				format(sql, 128, "SELECT id FROM agenda WHERE idplayer = %d AND nombre LIKE '%s%%' AND id = %d LIMIT 1", PlayerInfo[playerid][pSQLID], letras, i);
				samp_mysql_query(sql);
				samp_mysql_store_result();
				samp_mysql_fetch_row(row);
				count2 = strval(row); 
				countsql = samp_mysql_num_rows();				
				if(countsql == 0) continue;
				
				new row2[50];
				format(sql, 128, "SELECT * FROM agenda WHERE id = %d ", count2);
				samp_mysql_query(sql);
				samp_mysql_store_result();
				samp_mysql_fetch_row(row2);
				split(row2, arrCoords, '|');
				
				format(string, 128, "- %s - %d", arrCoords[2], strval(arrCoords[1]));
				SendClientMessage(playerid, AmarilloClaro, string);
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
					format(sql, 128, "SELECT COUNT(*) FROM agenda WHERE telefono = %d AND idplayer = %d LIMIT 1", PlayerInfo[player][pPnumber], PlayerInfo[playerid][pSQLID]);
					samp_mysql_query(sql);
					samp_mysql_store_result();
					samp_mysql_fetch_row(row);
					count = strval(row);
					if(count > 0) return PlayerInfo[player][pPnumber];
				}
			}
			else if(strlen(letras))
			{
				format(sql, 128, "SELECT telefono FROM agenda WHERE nombre = '%s' AND idplayer = %d LIMIT 1", letras, PlayerInfo[playerid][pSQLID]);
				samp_mysql_query(sql);
				samp_mysql_store_result();
				samp_mysql_fetch_row(row);
				count = strval(row);
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
*/
LlamarTelefono(playerid, telefono)
{
	new tlf = 0;
	
	if(PlayerInfo[playerid][pPnumber] == 0) return SendClientMessage(playerid, Rojo, "* No tienes movil!");
	if(PlayerInfo[playerid][pUsandoTelefono] >= 1) return SendClientMessage(playerid, Rojo, "* Estás en una llamada.");
	
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
//		if(IsValidNPC(i)) continue;
		
		if(PlayerInfo[i][pPnumber] == telefono)
		{
			if(PlayerInfo[i][pUsandoTelefono] == 0 && PlayerInfo[i][pIncomingCall] == NOEXISTE)
			{
				PlayerInfo[playerid][pUsandoTelefono] = 1;
				tlf = 1;
				PlayerInfo[i][pIncomingCall] = playerid;
				PlayerInfo[playerid][pIncomingCall] = i;
				SetPlayerSpecialAction(playerid, 11);
				SendClientMessage(i, AmarilloClaro, "Está sonando tu teléfono, escribe /contestar para atender la llamada.");
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
				EscucharEfecto(i, 4, 20.0);
				PlayerInfo[playerid][pTimerCall] = SetTimerEx("Notificar", 4000, 1, "d", i);
				break;
			}
		}
	}
	
	if(tlf == 0)
		return SendClientMessage(playerid, Gris, "* Escuchas el tono de ocupado...");
		
	return 1;
}

ColgarTelefono(playerid)
{
	if(PlayerInfo[playerid][pPnumber] == 0 && !IsACop(playerid) && !IsAMedic(playerid)) return SendClientMessage(playerid, Rojo, "* No tienes movil!");
	
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
		format(string, 128, "* Tienes una llamada perdida de: %d", PlayerInfo[playerid][pPnumber]);
		SendClientMessage(player, Gris, string);
		PlayerInfo[playerid][pUsandoTelefono] = 0;
		
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
		format(string, 128, "* Tienes una llamada perdida de: %d", PlayerInfo[PlayerInfo[playerid][pIncomingCall]][pPnumber]);
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
	EscucharEfecto(playerid, 4, 20.0);
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
	
/*	if(strcmp(cmd, "/agenda", true) == 0)
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
*/	
	if(strcmp(cmd, "/sms", true) == 0)
	{
	    tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Gris, "USO: /sms [numero] [mensaje]");
			return 1;
		}
		if(PlayerInfo[playerid][pPnumber] == 0)
		{
			SendClientMessage(playerid, Gris, "  No tienes teléfono móvil...");
			return 1;
		}
			
		format(string, sizeof(string), "* %s saca su teléfono.", pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		new phonenumb = strval(tmp);
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
				if(PlayerInfo[i][pPnumber] == phonenumb && phonenumb != 0)
				{
					format(string, sizeof(string), "SMS: %s, Tlf: %d", result,PlayerInfo[playerid][pPnumber]);
					SendClientMessage(playerid, Gris, "Mensaje enviado");
					SendClientMessage(i, Amarillo, string);
					SendClientMessage(playerid,  Gris, string);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					return 1;
				}
			}
		}
	}
	return 0;
}

Tlf_OnPlayerText(playerid, text[])
{
	if(PlayerInfo[playerid][pUsandoTelefono] == 2 || PlayerInfo[playerid][pUsandoTelefono] == 3 || PlayerInfo[playerid][pUsandoTelefono] == 914 || PlayerInfo[playerid][pUsandoTelefono] == 915)
	{
		format(string, 128, "[ID:%d] (Teléfono): %s", playerid, text);
		SendClientMessage(PlayerInfo[playerid][pIncomingCall], Amarillo, string);
		ProxDetector(5.0, playerid, string, Gris, Gris, Gris, Gris, Gris);
		return 1;
	}
	else if(PlayerInfo[playerid][pUsandoTelefono] == 4)
	{
		format(string, 128, "Mensaje de Voz: %s, Tlf: %d", text, PlayerInfo[playerid][pPnumber]);
		SendClientMessage(PlayerInfo[playerid][pIncomingCall], Amarillo, string);
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
		AgendaMemoria[playerid][aNumero] = strval(text);
		format(string, 128, "Contacto: %s con número: %d - Creado.", AgendaMemoria[playerid][aNombre], AgendaMemoria[playerid][aNumero]);
		SendClientMessage(playerid, AmarilloClaro, string);
		format(string, 128, "INSERT INTO agenda (idplayer, telefono, nombre) VALUES (%d,%d,'%s')", PlayerInfo[playerid][pSQLID], AgendaMemoria[playerid][aNumero], AgendaMemoria[playerid][aNombre]);
		samp_mysql_query(string);
		AgendaE[playerid] = 0;
		return 1;
	}
	else if(AgendaE[playerid] == 10)
	{
		new row[64], sql[128];
		if(IsNumeric(text))
		{
			format(sql, 128, "SELECT * FROM agenda WHERE telefono = %d AND idplayer = %d LIMIT 1", strval(text), PlayerInfo[playerid][pSQLID]);
		}
		else
		{
			format(sql, 128, "SELECT * FROM agenda WHERE nombre = '%s' AND idplayer = %d LIMIT 1", text, PlayerInfo[playerid][pSQLID]);
		}
		samp_mysql_query(sql);
		samp_mysql_store_result();
		samp_mysql_fetch_row(row);
		split(row, arrCoords, '|');
		
		new id;
		id = strval(arrCoords[4]);
		if(id == 0)
		{
			SendClientMessage(playerid, Naranja, "* Ningun contacto concuerda con tu busqueda.");
			return 1;
		}
		
		format(string, 128, "¿Seguro que quieres eliminar a '%s' de tu agenda? Escribe 'Si' o 'No'.", arrCoords[2]);
		SendClientMessage(playerid, Amarillo, string);
		AgendaMemoria[playerid][aNumero] = id;
		AgendaE[playerid] = 11;
		return 1;
	}
	else if(AgendaE[playerid] == 11)
	{
		if(strcmp(text, "Si", true) == 0)
		{
			new sql[128];
			format(sql, 128,"DELETE FROM agenda WHERE id = %d", AgendaMemoria[playerid][aNumero]);
			samp_mysql_query(sql);
			SendClientMessage(playerid, Verde, "Eliminado de la agenda.");
			AgendaE[playerid] = 0;
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