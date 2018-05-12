/*
	1 = Alarma.mp3
	2 = Arranque.mp3 - 
	3 = Dados.mp3
	4 = Llamada.mp3
	5 = Pedo.mp3
	6 = Puertas.mp3 -
	7 = Sms.mp3
	8 = taser.mp3
*/

#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>
#include <audio>

#define MAX_RADIOS 41

new Sintonizando[MAX_PLAYERS][20];
new Escuchando[MAX_PLAYERS][MAX_SONIDOS];

new PlayerText3D:AudioText[MAX_PLAYERS][MAX_SONIDOS];
new AudioTextToggle[MAX_PLAYERS];

enum raInfo
{
	rGenero,
	rNombre[60],
	rUrl[1024],
}
new Radios[MAX_RADIOS][raInfo] =
{
	// Hip Hop
	{1, "Hot 108 Jamz", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1281016"},
	{1, "Musik Jam", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1269742"},
	{1, "Powerhitz", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1283516"},
	{1, "Yakata West Coast Radio", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1462312"},
	{1, "True Hip Hop", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=612542"},
	{1, "ORS Radio - Classics", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1446246"},
	{1, "Classic Hip Hop Radio", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=212924"},
	{1, "Hot 97.7", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=421871"},
	{1, "Def Jay", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=616366"},
	
	// Electronica
	{2, "182.FM Energy 98", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1274106"},
	{2, "Techno Base", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1377200"},
	{2, "Raute Musik", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1275319"},
	{2, "French Kiss FM", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=52923"},
	{2, "Drum and Bass Radio", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1272005"},
    {2, "Musik Harder", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1275377"},
	
	// Latin
	{3, "Pocos Pero Locos FM", "http://link.live.net/?l=http%3a%2f%2fwww.live365.com%2fcgi-bin%2fplay.pls%3fstation%3dlatinhiphop%26site%3dwebtag%3dweb%26auth%3d19167e17b7e7e53dde04bbea1a8f8846-1292896638-latinhiphop%26membername%3dmember_10254524787%26session%3dlatinhiphop%253A0&h=2OMr32ketGqveEg65DJV1esMgy7l%2fovPmTtfqqDrRGI%3d&p=1"},
	{3, "Radio Reggaeton", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1267431"},
	{3, "Latino HD", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=312118"},
	{3, "Impacto Latino", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1270163"},
	{3, "La X Estereo", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=846149"},
    {3, "Baladas", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=334397"},

    // Clasica
    {4, "Abacus FM", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=144782"},
    {4, "Venice Classic Radio", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1280215"},
    {4, "Crazy Opera", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1269951"},

    // Rock & Metal
    {5, "Chronix Agression", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1377260"},
    {5, "Musik Extreme", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1275071"},
    {5, "Rock Radio One", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1275071"},
    {5, "Big R Radio", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=134938"},
    {5, "Amped FM Rock", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=541275"},
    {5, "Oldies", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1270522"},
    {5, "4U Classics", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1290072"},
    {5, "181 FM Classic Hits", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1271907"},

    // Reggae & Dancelhall
    {6, "Reggae 141", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1280855"},
    {6, "Dancehall Vibes", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=579793"},
    {6, "Big Up Radio", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1269793"},
    {6, "Ragga Kings", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1269672"},

    // Otros
    {7, "181.FM Kickin' Country", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1283687"},
    {7, "181.FM Classic Country", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1267926"},
    {7, "Smooth Jazz", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1339789"},
    {7, "977 Pop Hitz", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1280356"},
	{7, "Radio Japonesa", "http://yp.shoutcast.com/sbin/tunein-station.pls?id=520899"}
};

LoadSonidos()
{
	new sql[80], row[512], count, seliminado, TotalRadios;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM sonidos");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	count = strval(row);
	
	for (new i=1; i<=count; i++)
	{
		format(sql, sizeof(sql), "SELECT * FROM sonidos WHERE id=%d LIMIT 1", i);
	    mysql_query(sql);
	    mysql_store_result();
     	mysql_fetch_row(row);
		split(row, arrCoords, '|');
		seliminado = strval(arrCoords[6]);
		if(seliminado == 0)
		{
			Sonidos[i][sId] = strval(arrCoords[0]);
			Sonidos[i][sRadio] = strval(arrCoords[1]);
			Sonidos[i][sX] = floatstr(arrCoords[2]);
			Sonidos[i][sY] = floatstr(arrCoords[3]);
			Sonidos[i][sZ] = floatstr(arrCoords[4]);
			Sonidos[i][sRatio] = floatstr(arrCoords[5]);
			Sonidos[i][sEliminado] = 0;
			TotalRadios++;
		}
	}
	mysql_free_result();
	printf("Radios cargadas: %d (MAX: %d)", TotalRadios, MAX_SONIDOS);
}

SaveSonidos(idx)
{
	format(string, sizeof(string), "UPDATE sonidos SET radio=%d,X=%f,Y=%f,Z=%f,ratio=%f,eliminado=%d WHERE id=%d",
		Sonidos[idx][sRadio],
		Sonidos[idx][sX],
		Sonidos[idx][sY],
		Sonidos[idx][sZ],
		Sonidos[idx][sRatio],
		Sonidos[idx][sEliminado],
		Sonidos[idx][sId]);
	mysql_query(string);
}

Radio_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128], tmp[128], idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/editaraudio", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(PlayerInfo[playerid][pAdmin] < 3) return 1;
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /editaraudio [Crear|Emisora|Ratio|Ver|Goto|Eliminar]");
			return 1;
		}

		if(strcmp(tmp, "Crear", true) == 0)
		{
			format(string, 128, "INSERT INTO sonidos (radio) VALUES (-1)");
			mysql_query(string);
			
			new row[64];
			format(string, 128, "SELECT id FROM sonidos WHERE radio = -1");
			mysql_query(string);
			mysql_store_result();
			mysql_fetch_row(row);
			new id, Float:X, Float:Y, Float:Z;
			id = strval(row);
			GetPlayerPos(playerid, X,Y,Z);
			
			Sonidos[id][sId] = id;
			Sonidos[id][sRadio] = 1;
			Sonidos[id][sX] = X;
			Sonidos[id][sY] = Y;
			Sonidos[id][sZ] = Z;
			Sonidos[id][sRatio] = 30.0;
			mysql_free_result();
			SaveSonidos(id);		
			for(new i; i < MAX_PLAYERS; i++)
			{
				if(AudioTextToggle[i] == 1)
				{
					new ratio = floatround(Sonidos[id][sRatio],floatround_round);
					format(string,sizeof(string),"DEBUG: Radio %d (%d/%d)", Sonidos[id][sId], Sonidos[id][sRadio], ratio);
					AudioText[i][id] = CreatePlayer3DTextLabel(i, string, Azul, Sonidos[id][sX], Sonidos[id][sY], Sonidos[id][sZ], 10.0);
				}
			}
		}
		else if(strcmp(tmp, "Emisora", true) == 0)
		{
			for(new i; i < MAX_SONIDOS; i++)
			{
				if(PlayerToPoint(5.0, playerid, Sonidos[i][sX], Sonidos[i][sY], Sonidos[i][sZ]) && Sonidos[i][sEliminado] == 0)
				{
					tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp))
					{
						format(string,sizeof(string),"USO: /editcaraudio emisora 0 - %d", MAX_RADIOS);
						SendClientMessage(playerid, Blanco, string);
						return 1;
					}
					new id;
					id = strval(tmp);

					if(id < 0 || id > MAX_RADIOS) { format(string,sizeof(string),"* Radios solo de 0 a %d", MAX_RADIOS); SendClientMessage(playerid, Rojo, string); return 1;} 
					Sonidos[i][sRadio] = id;
					SaveSonidos(i);
					for(new ix; ix < MAX_PLAYERS; ix++)
					{
						Audio_Stop(ix, Escuchando[ix][i]);
						Escuchando[ix][i] = 0;
						if(AudioTextToggle[ix] == 1)
						{
							new ratio = floatround(Sonidos[i][sRatio],floatround_round);
							format(string,sizeof(string),"DEBUG: Radio %d (%d/%d)", Sonidos[i][sId], Sonidos[i][sRadio], ratio);
							UpdatePlayer3DTextLabelText(ix, AudioText[ix][i], Azul, string);
						}	
					}
					break;
				}
			}
		}
		else if(strcmp(tmp, "Ratio", true) == 0)
		{
			for(new i; i < MAX_SONIDOS; i++)
			{
				if(PlayerToPoint(5.0, playerid, Sonidos[i][sX], Sonidos[i][sY], Sonidos[i][sZ]) && Sonidos[i][sEliminado] == 0)
				{
					tmp = strtokex(cmdtext, idx);
					if(!strlen(tmp))
					{
						SendClientMessage(playerid, Blanco, "USO: /editaraudio ratio [X]");
						SendClientMessage(playerid, Naranja, "Para borrarlas usar /editaraudio eliminar");
						return 1;
					}
					new Float:id;
					id = floatstr(tmp);
					Sonidos[i][sRatio] = id;
					SaveSonidos(i);
					for(new ix; ix < MAX_PLAYERS; ix++)
					{
						Audio_Stop(ix, Escuchando[ix][i]);
						Escuchando[ix][i] = 0;
						if(AudioTextToggle[ix] == 1)
						{
							new ratio = floatround(Sonidos[i][sRatio],floatround_round);
							format(string,sizeof(string),"DEBUG: Radio %d (%d/%d)", Sonidos[i][sId], Sonidos[i][sRadio], ratio);
							UpdatePlayer3DTextLabelText(ix, AudioText[ix][i], Azul, string);
						}	
					}
					break;
				}
			}
		}
		else if(strcmp(tmp, "Ver", true) == 0)
		{
			if(AudioTextToggle[playerid] == 0)
			{
				for(new i = 1; i < MAX_SONIDOS; i++)
				{
					new ratio = floatround(Sonidos[i][sRatio],floatround_round);
					format(string,sizeof(string),"DEBUG: Radio %d (%d/%d)", Sonidos[i][sId], Sonidos[i][sRadio], ratio);
					AudioText[playerid][i] = CreatePlayer3DTextLabel(playerid, string, Azul, Sonidos[i][sX], Sonidos[i][sY], Sonidos[i][sZ], 10.0);
				}
				AudioTextToggle[playerid] = 1;
				SendClientMessage(playerid, Amarillo, "* Debug audio activado!");
			}
			else
			{
				for(new i = 1; i < MAX_SONIDOS; i++)
				{
					DeletePlayer3DTextLabel(playerid, AudioText[playerid][i]);
				}
				AudioTextToggle[playerid] = 0;
				SendClientMessage(playerid, Amarillo, "* Debug audio desactivado!");
			}
		}
		else if(strcmp(tmp, "Goto", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editaraudio goto [ID Radio]");
				return 1;
			}
			new id;
			id = strval(tmp);
			new arrayid = NOEXISTE;
			
			for(new i = 0; i < MAX_SONIDOS; i++)
			{
				if(Sonidos[i][sId] == id)
				{
					arrayid = i;
					break;
				}
			}
			if(arrayid == NOEXISTE || Sonidos[arrayid][sEliminado] == 1)
			{
				SendClientMessage(playerid, Rojo, "* ID invalida, no existe.");
				return 1;
			}

			SetPlayerPosEx(playerid,Sonidos[arrayid][sX],Sonidos[arrayid][sY],Sonidos[arrayid][sZ]);
			SendClientMessage(playerid, AzulClaro, "* Te has teleportado.");
		}
		else if(strcmp(tmp, "Eliminar", true) == 0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /editaraudio eliminar [ID Radio]");
				return 1;
			}
			new id;
			id = strval(tmp);
			new arrayid = NOEXISTE;
			
			for(new i = 0; i < MAX_SONIDOS; i++)
			{
				if(Sonidos[i][sId] == id)
				{
					arrayid = i;
					break;
				}
			}
			if(arrayid == NOEXISTE)
			{
				SendClientMessage(playerid, Rojo, "* ID invalida, no existe.");
				return 1;
			}
			
			if(Sonidos[arrayid][sEliminado] == 1)
			{
				SendClientMessage(playerid, Rojo, "* Radio ya eliminada, si da algun problema, en el reset cargará bien.");
				return 1;
			}
			
			Sonidos[arrayid][sRatio] = 0;
			Sonidos[arrayid][sEliminado] = 1;
			SaveSonidos(arrayid);
			for(new ix; ix < MAX_PLAYERS; ix++)
			{
				Audio_Stop(ix, Escuchando[ix][arrayid]);
				Escuchando[ix][arrayid] = 0;
				if(AudioTextToggle[ix] == 1)
				{
					DeletePlayer3DTextLabel(ix, AudioText[ix][arrayid]);
				}	
			}
		}
		else
		{
			SendClientMessage(playerid, Blanco, "USO: /editaraudio [Crear|Emisora|Ratio|Ver|Goto|Eliminar]");
			return 1;
		}
		return 1;
	}
	
	if(strcmp(cmd, "/volumen", true) == 0 || strcmp(cmd, "/vol", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /volumen [0-100]");
			return 1;
		}
		
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
		{
			SendClientMessage(playerid, Rojo, "* Tienes que estar de conductor para usar este comando");
			return 1;
		}
		
		if(CarInfo[GetPlayerVehicle(playerid)][cEquipo] == 0)
		{
			SendClientMessage(playerid, Rojo, "* No tienes instalado un equipo car-audio en el vehículo.");
			return 1;
		}
		
		new car, volumen;
		volumen = strval(tmp);
		if(volumen < 0 || volumen > 100)
		{
			SendClientMessage(playerid, Blanco, "USO: /volumen [0-100]");
			return 1;
		}
		
		car = GetPlayerVehicle(playerid);
		if(IsABike(car))
		{
			SendClientMessage(playerid, Rojo, "* No puedes hacer eso en una bici!");
			return 1;
		}
		if(CarInfo[car][cSubWoofer] == 1) { return 1; }
		
		CarInfo[car][cVolumen] = volumen;
		format(string, 128, "[RADIO]: %s ha cambiado el volumen a '%d'", pName(playerid), volumen);
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerInVehicle(i, CarInfo[car][cId]))
			{
				SendClientMessage(i, Naranja, string);
			}
		}
		SaveCar(car);
		ActualizarVolumenEmisora(car);
		return 1;
	}
	
	if(strcmp(cmd, "/efecto", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 1) return 1;
		
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp)) 
		{
			SendClientMessage(playerid, Blanco, "USO: /efecto [0-8] [Ratio]");
			return 1;
		}
		new efecto = strval(tmp);
		if(efecto < 0 || efecto > 8)
		{
			SendClientMessage(playerid, Blanco, "USO: /efecto [0-8] [Radio]");
			return 1;
		}
		
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /efecto [0-8] [Radio]");
			return 1;
		}
		new Float:radio = floatstr(tmp);
		if(radio > 200 || radio < 0)
		{
			SendClientMessage(playerid, Blanco, "USO: /efecto [0-8] [Radio]");
			return 1;
		}
		if(IsPlayerInAnyVehicle(playerid))
		{
			EscucharEfecto(GetPlayerVehicle(playerid), efecto, radio);
		}
		else
		{
			EscucharEfectoEx(playerid, efecto, radio);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/sintonizar", true) == 0 || strcmp(cmd, "/sin", true) == 0)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, Rojo, "* Tienes que estar de conductor para usar este comando");
			return 1;
		}
		if(CarInfo[GetPlayerVehicle(playerid)][cEquipo] == 0)
		{
			SendClientMessage(playerid, Rojo, "* No tienes instalado un equipo car-audio en el vehículo.");
			return 1;
		}
		new car = GetPlayerVehicle(playerid);
		if(IsABike(car)) return SendClientMessage(playerid, Rojo, "* No puedes hacer eso en una bici!");
		if(CarInfo[car][cSubWoofer] == 1) { return 1; }
		ShowPlayerDialog(playerid,1003,DIALOG_STYLE_LIST,"Seleccione un género","1. Hip Hop\r\n2. Electronica\r\n3. Latin\r\n4. Clásica\r\n5. Rock & Metal\r\n6. Reggae & Dancelhall\r\n7. Otros","Seleccionar", "Salir");
		return 1;
	}
	
	if(strcmp(cmd, "/subwoofer", true) == 0 || strcmp(cmd, "/sub", true) == 0)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid, Rojo, "* Tienes que estar de conductor para usar este comando");
			return 1;
		}
		new car = GetPlayerVehicle(playerid);
		if(IsABike(car))
		{
			SendClientMessage(playerid, Rojo, "* No puedes hacer eso en una bici!");
			return 1;
		}
		if(CarInfo[car][cStarted] == 1)
		{
			SendClientMessage(playerid, Rojo, "* Primero debes apagar el motor para activar el subwoofer.");
			return 1;
		}
		if(CarInfo[GetPlayerVehicle(playerid)][cEquipo] < 2)
		{
			SendClientMessage(playerid, Rojo, "* Necesitas un equipo estereo X-Flow o Alien para cambiar el volumen.");
			return 1;
		}
		if(CarInfo[car][cUsos] == 0)
		{
			GetVehiclePos(CarInfo[car][cId], CarInfo[car][cLocationx], CarInfo[car][cLocationy], CarInfo[car][cLocationz]);
		}
		if(CarInfo[car][cSubWoofer] == 0)
		{
			SendClientMessage(playerid, Verde, "* Subwoofer activado!");
			Sintonizar(car);
			CarInfo[car][cSubWoofer] = 1;
			ActualizarEmisora(car);
		}
		else
		{
			SendClientMessage(playerid, Verde, "* Subwoofer desactivado!");
			ApagarWoofer(car);
			CarInfo[car][cSubWoofer] = 0;
		}
		return 1;
	}
	
	if(strcmp(cmd, "/apagarradio", true) == 0 || strcmp(cmd, "/ar", true) == 0)
	{
		Audio_Stop(playerid, PlayerInfo[playerid][pSonido]);
		PlayerInfo[playerid][pSonido] = 0;
		for(new i; i < MAX_VEHICLES; i++)
		{
			Audio_Stop(playerid, Sintonizando[playerid][CarInfo[i][cId]]);
			Sintonizando[playerid][CarInfo[i][cId]] = 0;
		}
		for(new i; i < MAX_SONIDOS; i++)
		{
			Audio_Stop(playerid, Escuchando[playerid][i]);
			Escuchando[playerid][Sonidos[i][sId]] = 0;
		}
		return 1;
	}
	return 0;
}

Radio_OnDialogResponse(playerid, dialogid, response, listitem)
{
	if(dialogid == 1003 && response)
	{
		new nuevalista[256];
		if(listitem >= 0 && listitem < 7)
		{
			for(new i; i < MAX_RADIOS; i++)
			{
				if(Radios[i][rGenero] == (listitem+1))
				{
					if(strlen(nuevalista) > 0)
					{
						format(string, 128, "\r\n%s", Radios[i][rNombre]);
						strcat(nuevalista, string, 256);					
					}
					else
					{	
						strcat(nuevalista, Radios[i][rNombre], 256);
					}
				}
			}
			
			new newid;
			newid = listitem + 1004;
			ShowPlayerDialog(playerid, newid, DIALOG_STYLE_LIST, "Seleccione una emisora", nuevalista, "Seleccionar", "Salir"); 
		}
		return 1;
	}
	if(dialogid > 1003 && dialogid < 1011)
	{
		if(!response)
		{
			ShowPlayerDialog(playerid,1003,DIALOG_STYLE_LIST,"Seleccione un género","1. Hip Hop\r\n2. Electronica\r\n3. Latin\r\n4. Clásica\r\n5. Rock & Metal\r\n6. Reggae & Dancelhall\r\n7. Otros","Seleccionar", "Salir");
		}
		
		new genero, emisora, car;
		genero = dialogid - 1003;
		for(new i; i < MAX_RADIOS; i++)
		{
			if(Radios[i][rGenero] == genero)
			{
				emisora = i;
				break;
			}
		}
		
		emisora += listitem;
		car = GetPlayerVehicle(playerid);
		CarInfo[car][cEmisora] = emisora;
		format(string, 128, "[RADIO]: %s ha sintonizado a la emisora '%s'", pName(playerid), Radios[emisora][rNombre]);
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerInVehicle(i, CarInfo[car][cId]))
			{
				SendClientMessage(i, Naranja, string);
			}
		}
		ActualizarEmisora(car);
		SaveCar(car);
		return 1;
	}
	return 0;
}

Radio_OnPlayerDisconnect(playerid)
{
	for(new i; i < MAX_VEHICLES; i++)
	{
		Audio_Stop(playerid, i);
		Sintonizando[playerid][i] = 0;
	}
	return 1;
}

Radio_OnPlayerUpdate(playerid)
{
	if(PlayerInfo[playerid][pEfecto] != NOEXISTE)
	{
		GetPlayerPos(playerid,PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z]);
		for(new i; i < MAX_PLAYERS; i++)
		{
			if(PlayerToPoint(PlayerInfo[playerid][pEfectoRatio], i, PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z]))
			{
				Audio_Set3DPosition(i, PlayerInfo[playerid][pEfecto], PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z], PlayerInfo[playerid][pEfectoRatio]);
			}
		}
	}
	return 1;
}

Radio_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		new idx = GetPlayerVehicle(playerid);
		if(CarInfo[idx][cSubWoofer] == 1) { ApagarWoofer(idx); CarInfo[idx][cSubWoofer] = 0; SendClientMessage(playerid, Verde, "* SubWoofer desactivado!"); return 1;}
		if(CarInfo[idx][cStarted] == 1 && CarInfo[idx][cEquipo] > 0)
		{
			new radio = CarInfo[idx][cEmisora];
			PlayerInfo[playerid][pSonido] = Audio_PlayStreamed(playerid, Radios[radio][rUrl], false, false, false);
			Audio_SetVolume(playerid, PlayerInfo[playerid][pSonido], CarInfo[idx][cVolumen]);
			return 1;
		}
	}
	if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) && newstate == PLAYER_STATE_ONFOOT)
	{
		new idx = vehiculomascercano(playerid);
		if(CarInfo[idx][cUsos] == 0 && !(strcmp(CarInfo[idx][cOwner], "autoescuela", true) == 0))
		{
			GetVehiclePos(CarInfo[idx][cId], CarInfo[idx][cLocationx], CarInfo[idx][cLocationy], CarInfo[idx][cLocationz]);
		}
		if(CarInfo[idx][cSubWoofer] == 0)
		{
			Audio_Stop(playerid, PlayerInfo[playerid][pSonido]);
			return 1;
		}
		else
		{
			Audio_Set3DPosition(playerid, PlayerInfo[playerid][pSonido], CarInfo[idx][cLocationx], CarInfo[idx][cLocationy], CarInfo[idx][cLocationz], 15.0);
			Sintonizando[playerid][GetEmptySintonizarID(playerid, idx)] = PlayerInfo[playerid][pSonido];
			return 1;
		}
	}
	return 0;
}

ActualizarEmisora(vehicleid)
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerInVehicle(i, CarInfo[vehicleid][cId]))
		{
			if(CarInfo[vehicleid][cEquipo] > 0)
			{
				Audio_Stop(i, PlayerInfo[i][pSonido]);
				new radio = CarInfo[vehicleid][cEmisora];
				PlayerInfo[i][pSonido] = Audio_PlayStreamed(i, Radios[radio][rUrl], false, false, false);
				SetTimerEx("ActualizarVolumenEmisora", 3000, 0, "d", vehicleid);
			}
		}
	}
	return 1;
}

forward ActualizarVolumenEmisora(vehicleid);
public ActualizarVolumenEmisora(vehicleid)
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerInVehicle(i, CarInfo[vehicleid][cId]))
		{
			if(CarInfo[vehicleid][cStarted] == 1 || CarInfo[vehicleid][cSubWoofer] == 1)
			{
				Audio_SetVolume(i, PlayerInfo[i][pSonido], CarInfo[vehicleid][cVolumen]);
			}
			else
			{
				Audio_SetVolume(i, PlayerInfo[i][pSonido], 0);
			}
		}
	}
	return 1;
}

Sintonizar(vehicleid)
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		new Float:Ratio;
		if(CarInfo[vehicleid][cEquipo] == 2)
		{
			Ratio = 10.0;
		}
		else if(CarInfo[vehicleid][cEquipo] == 3)
		{
			Ratio = 20.0;
		}
		else
		{
			return 1;
		}
		
		new sintonizarid = GetSintonizarID(i, vehicleid);
		if(Sintonizando[i][sintonizarid] > 0)
		{
			if(!PlayerToPoint(Ratio, i, CarInfo[vehicleid][cLocationx], CarInfo[vehicleid][cLocationy], CarInfo[vehicleid][cLocationz]))
			{
				Audio_Stop(i, Sintonizando[i][sintonizarid]);
				Sintonizando[i][sintonizarid] = 0;
			}
		}
		else
		{
			if(PlayerToPoint(Ratio, i, CarInfo[vehicleid][cLocationx], CarInfo[vehicleid][cLocationy], CarInfo[vehicleid][cLocationz]))
			{
				if(IsPlayerInAnyVehicle(i)) { continue; }				
				if(Sintonizando[i][sintonizarid] > 0) { continue; }
				new emisora = CarInfo[vehicleid][cEmisora];
				sintonizarid = GetEmptySintonizarID(i, vehicleid);
				Sintonizando[i][sintonizarid] = Audio_PlayStreamed(i, Radios[emisora][rUrl], false, false, false);
				Audio_Set3DPosition(i, Sintonizando[i][sintonizarid], CarInfo[vehicleid][cLocationx], CarInfo[vehicleid][cLocationy], CarInfo[vehicleid][cLocationz], 10.0);
			}
		}
	}
	return 1;
}

forward SintonizarEx();
public SintonizarEx()
{
	for(new i = 0; i < MAX_VEHICLES; i++)
	{
		if(CarInfo[i][cSubWoofer] == 1)
		{
			Sintonizar(i);
		}
	}
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) || i < 200)
		{
			Escuchar3D(i);
		}
	}
	return 1;
}

stock Escuchar3D(i)
{
	for(new id = 0; id < MAX_SONIDOS; id++)
	{
		if(Sonidos[id][sId] == 0) { continue; }
		if(PlayerToPoint(Sonidos[id][sRatio], i, Sonidos[id][sX], Sonidos[id][sY], Sonidos[id][sZ]))
		{
			if(IsPlayerInAnyVehicle(i)) { continue; }
			if(Escuchando[i][Sonidos[id][sId]] > 0) { continue; }
			new emisora = Sonidos[id][sRadio];
			Escuchando[i][Sonidos[id][sId]] = Audio_PlayStreamed(i, Radios[emisora][rUrl], false, false, false);
			Audio_Set3DPosition(i, Escuchando[i][Sonidos[id][sId]], Sonidos[id][sX], Sonidos[id][sY], Sonidos[id][sZ], Sonidos[id][sRatio]);
		}
	}
}

ApagarWoofer(vehicleid)
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		new sintonizarid = GetSintonizarID(i, vehicleid);
		if(Sintonizando[i][sintonizarid] > 0)
		{
			Audio_Stop(i, Sintonizando[i][sintonizarid]);
			Sintonizando[i][sintonizarid] = 0;
		}
	}
	return 1;
}

GetSintonizarID(i, vehicleid)
{
	new sintonizarid = 0;
	for(new h; h < 20; h++)
	{
		if(Sintonizando[i][h] == 0) continue;
				
		if(Sintonizando[i][h] == CarInfo[vehicleid][cId])
		{
			sintonizarid = h;
			break;
		}
	}
	return sintonizarid;
}

GetEmptySintonizarID(i, vehicleid)
{
	new sintonizarid = 0;
	for(new h; h < 20; h++)
	{
		if(Sintonizando[i][h] > 0) continue;
				
		if(Sintonizando[i][h] == 0)
		{
			Sintonizando[i][h] = CarInfo[vehicleid][cId];
			sintonizarid = h;
			break;
		}
	}
	return sintonizarid;
}

EscucharEfecto(vehicleid, efectoid, Float:ratio)
{
	if(CarInfo[vehicleid][cUsos] == 0)
	{
		GetVehiclePos(CarInfo[vehicleid][cId], CarInfo[vehicleid][cLocationx], CarInfo[vehicleid][cLocationy], CarInfo[vehicleid][cLocationz]);
	}
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(PlayerToPoint(ratio, i, CarInfo[vehicleid][cLocationx], CarInfo[vehicleid][cLocationy], CarInfo[vehicleid][cLocationz]))
		{
			ApagarWoofer(vehicleid);
			new sintonizarid = GetEmptySintonizarID(i, vehicleid);
			Sintonizando[i][sintonizarid] = Audio_Play(i, efectoid, false, false, false);
			Audio_Set3DPosition(i, Sintonizando[i][sintonizarid], CarInfo[vehicleid][cLocationx], CarInfo[vehicleid][cLocationy], CarInfo[vehicleid][cLocationz], ratio);
		}
	}
}

EscucharEfectoEx(playerid, efectoid, Float:ratio)
{
	GetPlayerPos(playerid,PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z]);
	PlayerInfo[playerid][pEfectoRatio] = ratio;
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(PlayerToPoint(ratio, i, PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z]))
		{
			PlayerInfo[playerid][pEfecto] = Audio_Play(i, efectoid, false, false, false);
			Audio_Set3DPosition(i, PlayerInfo[playerid][pEfecto], PlayerInfo[playerid][pPos_x],PlayerInfo[playerid][pPos_y],PlayerInfo[playerid][pPos_z], ratio);
		}
	}
}

Radio_OnPlayerDeath(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		Radio_OnPlayerCommandText(playerid, "/apagarradio");
	}
}
