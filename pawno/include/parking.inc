#include <a_samp>
#include <globalvars>
#include <coches>
#include <funciones>
#include <colores>


CargarParkings()
{
	new pcount;
	new sql[80], row[512];
	format(sql, sizeof(sql), "SELECT id FROM parkings ORDER BY id DESC");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	pcount = strval(row);
	
    new idx=-1;
	for (new id = 0; id<pcount; id++)
	{	
		format(sql, sizeof(sql), "SELECT * FROM parkings WHERE id=%d LIMIT 1", id+1);
		mysql_query(sql);
		mysql_store_result();
		if (mysql_num_rows() == 0)  continue; // No existe parking con esa id: volvemos arriba del bucle
		mysql_fetch_row(row);
		split(row, arrCoords, '|');
        
        idx++;
		ParkInfo[idx][paSQLID] = strval(arrCoords[0]);
		ParkInfo[idx][paType] = strval(arrCoords[1]);
		ParkInfo[idx][paCap] = strval(arrCoords[2]);
		ParkInfo[idx][paTotal] = strval(arrCoords[3]);
		ParkInfo[idx][paX] = floatstr(arrCoords[4]);
		ParkInfo[idx][paY] = floatstr(arrCoords[5]);
		ParkInfo[idx][paZ] = floatstr(arrCoords[6]);
		ParkInfo[idx][paOwner] = strval(arrCoords[7]);
		if(ParkInfo[idx][paType] == 0)
		{
			ParkInfo[idx][paPickup]=CreateDynamic3DTextLabel("Aparcamiento", Amarillo, ParkInfo[idx][paX], ParkInfo[idx][paY], ParkInfo[idx][paZ], 20);
		}
		else if(ParkInfo[idx][paType] == 1)
		{
			ParkInfo[idx][paPickup]=CreateDynamic3DTextLabel("Garaje", Amarillo, ParkInfo[idx][paX], ParkInfo[idx][paY], ParkInfo[idx][paZ], 5);
		}
		else if(ParkInfo[idx][paType] == 2)
		{
			ParkInfo[idx][paPickup]=CreateDynamic3DTextLabel("Aparcamiento Privado", Amarillo, ParkInfo[idx][paX], ParkInfo[idx][paY], ParkInfo[idx][paZ], 10);
		}
		else if(ParkInfo[idx][paType] == 3 || ParkInfo[idx][paType] == 4)
		{
			ParkInfo[idx][paPickup]=CreateDynamic3DTextLabel("Deposito", Amarillo, ParkInfo[idx][paX], ParkInfo[idx][paY], ParkInfo[idx][paZ], 20);
		}		
	}
    TotalParkings= idx+1;
	mysql_free_result();
	printf("Parkings cargados: %d (MAX: %d)",TotalParkings,MAX_PARKINGS);
	return 1;
}


SaveParking(idx)
{
	format(string, sizeof(string), "UPDATE parkings SET X = %f, Y = %f, Z = %f, Total = %d, Capacidad = %d, Owner = %d WHERE id = %d", 
		ParkInfo[idx][paX],
		ParkInfo[idx][paY],
		ParkInfo[idx][paZ],
		ParkInfo[idx][paTotal],
		ParkInfo[idx][paCap],
		ParkInfo[idx][paOwner],
		ParkInfo[idx][paSQLID]);
	mysql_query(string);
	return 1;
}

Parking_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);

	if(strcmp(cmd, "/aparcar", true) == 0)
	{
		new coche = GetPlayerVehicle(playerid);
		
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid,Rojo,"* No estás conduciendo un vehiculo!");
			return 1;
		}
		
		if(IsPlayerInParking(playerid) == 0)
		{
			SendClientMessage(playerid, Rojo, "* Debes estar en un aparcamiento para poder utilizar este comando.");
			return 1;
		}
				
		if(strcmp(CarInfo[coche][cOwner], "autoescuela", true) == 0)
		{
			SendClientMessage(playerid, Rojo, "* No puedes aparcar el coche de la autoescuela.");
			return 1;
		}
		
		new parking = GetPlayerParking(playerid);
		if(ParkInfo[parking][paCap] == ParkInfo[parking][paTotal])
		{
			if(ParkInfo[parking][paType] == 1 && PremiumValido(playerid, 3))
			{
				if(PlayerInfo[playerid][pPhousekey] != ParkInfo[parking][paOwner])
				{
					SendClientMessage(playerid, Rojo, "* Este es un garage, necesitas tener la llave.");
					return 1;
				}
				if(ParkInfo[parking][paTotal] >= 4)
				{
					SendClientMessage(playerid, Rojo, "* Este aparcamiento está ocupado!");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* Este aparcamiento está ocupado!");
				return 1;
			}
		}
		
		if(ParkInfo[parking][paType] == 1 && PlayerInfo[playerid][pPhousekey] != ParkInfo[parking][paOwner])
		{
			SendClientMessage(playerid, Rojo, "* Este es un garage, necesitas tener la llave.");
			return 1;
		}
		
		if(ParkInfo[parking][paType] == 2 && PlayerInfo[playerid][pMember] != ParkInfo[parking][paOwner])
		{
			SendClientMessage(playerid, Rojo, "* Este es un aparcamiento privado, necesitas ser parte de la organización.");
			return 1;
		}
		
		if(ParkInfo[parking][paType] == 4 && PlayerInfo[playerid][pMember] != 1)
		{
			SendClientMessage(playerid, Rojo, "* Este es un deposito, necesitas ser parte del LSPD.");
			return 1;
		}
		
		if(!PlayerHaveKeys(playerid, coche) && (ParkInfo[parking][paType] != 4 && ParkInfo[parking][paType] != 3 && ParkInfo[parking][paType] != 2))
		{
			SendClientMessage(playerid, Rojo, "* No tienes las llaves de este coche.");
			return 1;
		}
		
		if(CarInfo[coche][cSubWoofer] == 1)
		{
			SendClientMessage(playerid, Rojo, "* Desactiva el subwoofer primero!");
			return 1;
		}
		CarInfo[coche][horas] = 1;
		CarInfo[coche][cParking] = ParkInfo[parking][paSQLID];
		ParkInfo[parking][paTotal]++;
		SaveParking(parking);
		GetVehicleZAngle(CarInfo[coche][cId], CarInfo[coche][cAngle]);
		if(ParkInfo[parking][paType] == 0)
		{
			SendClientMessage(playerid, Verde, "* Has aparcado el coche en este parking, la tarifa es de 30$ por hora. Si no recuerdas donde has aparcado, usa /verparking");
			SaveCar(coche);
			HideLLLCar(coche);
			TogglePlayerControllable(playerid,1);
		}
		else if(ParkInfo[parking][paType] == 1)
		{
			SendClientMessage(playerid, Verde, "* Has aparcado el coche correctamente, vuelve por el cuando quieras!");
			SaveCar(coche);
			HideLLLCar(coche);
			TogglePlayerControllable(playerid,1);
		}		
		else if(ParkInfo[parking][paType] == 3 || ParkInfo[parking][paType] == 4)
		{
			SendClientMessage(playerid, Verde, "* Has aparcado el coche en el deposito.");
			SaveCar(coche);
			HideLLLCar(coche);
			TogglePlayerControllable(playerid,1);
		}
		else
		{
			SendClientMessage(playerid, Verde, "* Has aparcado el coche correctamente, vuelve por el cuando quieras!");
			LinkVehicleToInterior(GetPlayerVehicleID(playerid),1);
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), parking);
			CarInfo[coche][cVw] = parking;
			CarInfo[coche][cInt] = 1;
			for(new i; i < MAX_PLAYERS; i++)
			{
				if(!IsPlayerConnected(i)) { continue; }
				if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
				{
					SetPlayerInterior(i, 1);
					SetPlayerVirtualWorld(i, parking);
				}
			}
			SetVehiclePosiEx(GetPlayerVehicleID(playerid), playerid, 1499.4244384766, 183.61317443848, 1773.9107666016);
			SaveCar(coche);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/desaparcar", true) == 0)
	{
		
		if(!IsPlayerInParking(playerid))
		{
			SendClientMessage(playerid, Rojo, "* No estas en un aparcamiento.");
			return 1;
		}
		
		new parking = GetPlayerParking(playerid);
		
        if(ParkInfo[parking][paType] == 2 && PlayerInfo[playerid][pMember] != ParkInfo[parking][paOwner])
		{
			SendClientMessage(playerid, Rojo, "* Este es un aparcamiento privado, necesitas ser parte de la organización.");
			return 1;
		}

        
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) && ParkInfo[parking][paType] != 2)
		{
			SendClientMessage(playerid, Blanco, "USO: /desaparcar [Matricula del Coche]");
			return 1;
		}
		
		new llave;
		new coche;
		if(ParkInfo[parking][paType] != 2)
		{
			llave = strval(tmp);
			coche = GetVehicleByKey(llave);
		}
		else
		{
			llave = CarInfo[GetPlayerVehicle(playerid)][cCarKey];
			coche = GetPlayerVehicle(playerid);
		}
		
		if(coche == -1)
		{
			SendClientMessage(playerid, Rojo, "* Coche inválido!");
			return 1;
		}
		
		new total;
		switch(ParkInfo[parking][paType])
		{
			case 0:
			{
				total = CarInfo[coche][horas] * 30;
			}
			case 3, 4:
			{
				if(CarInfo[coche][horas] != 69)
				{
					if(CarInfo[coche][cSeguro] == 0)
					{
						total = 500;
					}
					else
					{
						total = 0;
					}
				}
				else
				{
					if(CarInfo[coche][cSeguro] == 0)
					{
						total = CarInfo[coche][cValue] / 2;
					}
					else
					{
						total = 0;
					}
				}
			}
			default:
			{
				total = 0;
			}
		}
		
		if(!PlayerHaveKeys(playerid, coche) && ParkInfo[parking][paType] != 2)
		{
			SendClientMessage(playerid, Rojo, "* No tienes las llaves de este coche.");
			return 1;
		}
		
		if(CarInfo[coche][eliminado] != -1 && ParkInfo[parking][paType] != 2)
		{
			SendClientMessage(playerid, Rojo, "* Ese coche no esta aparcado!");
			return 1;
		}
		
		if(CarInfo[coche][cParking] != ParkInfo[parking][paSQLID] && ParkInfo[parking][paType] != 2)
		{
			HideLLLCar(coche);
			SendClientMessage(playerid, Rojo, "* No estas en el aparcamiento donde dejaste el coche. Usa /verparking si no lo recuerdas.");
			return 1;
		}
		
		if(SafeGetPlayerMoney(playerid) < total)
		{
			SendClientMessage(playerid, Rojo, "* No tienes el dinero suficiente, no puedes retirar el coche!");
			format(string, 128, "* Necesitas $%d para poder desaparcarlo de acá.", total);
			SendClientMessage(playerid, Rojo, string);
			return 1;
		}
		else if(SafeGetPlayerMoney(playerid) >= total && ParkInfo[parking][paType] != 2 && ParkInfo[parking][paType] != 1 && ParkInfo[parking][paType] != 0)
		{
			SafeGivePlayerMoney(playerid, -total);
			CarInfo[coche][cSeguro] = 0;
			if(total > 0) format(string, 128, "* Te hemos cobrado $%d por desaparcar el coche del deposito.", total);
			else format(string, 128, "* Tu seguro ha cubierto los gastos del coche, pero tendrás que buscarte otro seguro nuevo...");
			SendClientMessage(playerid, Naranja, string);
		}
		
		if(ParkInfo[parking][paType] == 0)
		{
			LoadLLLCar(coche);
			ParkInfo[parking][paTotal]--;
			SafeGivePlayerMoney(playerid, -total);
			format(string, sizeof(string), "* Has desaparcado el coche, te hemos cobrado %d$", total);
			SendClientMessage(playerid, Verde, string);
//			PutPlayerInVehicle(playerid, CarInfo[coche][cId], 0);
		}
		else if(ParkInfo[parking][paType] == 1)
		{
			LoadLLLCar(coche);
			ParkInfo[parking][paTotal]--;
			SendClientMessage(playerid, Verde, "* Has desaparcado el coche.");
		}
		else if(ParkInfo[parking][paType] == 3 || ParkInfo[parking][paType] == 4)
		{
			LoadLLLCar(coche);
			ParkInfo[parking][paTotal]--;
			SendClientMessage(playerid, Verde, "* Has desaparcado el coche del deposito.");
		}
		else if(ParkInfo[parking][paType] == 2)
		{
			ParkInfo[parking][paTotal]--;
			SetVehiclePos(CarInfo[coche][cId], ParkInfo[parking][paX], ParkInfo[parking][paY], ParkInfo[parking][paZ]);
			LinkVehicleToInterior(CarInfo[coche][cId], 0);
			SetVehicleVirtualWorld(CarInfo[coche][cId], 0);
			for(new i; i < MAX_PLAYERS; i++)
			{
				if(!IsPlayerConnected(i)) { continue; }
				if(IsPlayerInVehicle(i, CarInfo[coche][cId]))
				{
					SetPlayerInterior(i, 0);
					SetPlayerVirtualWorld(i, 0);
				}
			}
			CarInfo[coche][cVw] = 0;
			CarInfo[coche][cInt] = 0;
		}
		SaveParking(parking);
		CarInfo[coche][cParking] = -1;
		SaveCar(coche);
		
		return 1;
	}
	
	if(strcmp(cmd, "/crearparking", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
	        return 1;
	    }
	
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /crearparking [Tipo de Parking 0-3, 0-Publico 1-Garage 2-Privado 3 y 4-Deposito] [0-Capacidad|1-Llave|2-Faccion]");
			return 1;
		}
		
		new tipo = strval(tmp);
		
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /crearparking [Tipo de Parking 0-3, 0-Publico 1-Garage 2-Privado 3 y 4-Deposito] [0-Capacidad|1-Llave|2-Faccion]");
			return 1;
		}
		
		new param2 = strval(tmp);
		
		new sql[128], row[256], id;
		new Float:X, Float:Y, Float:Z;
		
		GetPlayerPos(playerid, X, Y, Z);
		
		if(tipo == 0)
		{
			format(sql, 128, "INSERT INTO parkings (Tipo, Capacidad, X, Y, Z) VALUES (%d, %d, %f, %f, %f)", tipo, param2, X, Y, Z);
			mysql_query(sql);
		}
		else if(tipo == 1)
		{
			format(sql, 128, "INSERT INTO parkings (Tipo, Capacidad, X, Y, Z, Owner) VALUES (%d, 2, %f, %f, %f, %d)", tipo, X, Y, Z, param2);
			mysql_query(sql);
		}
		else if(tipo == 2)
		{
			format(sql, 128, "INSERT INTO parkings (Tipo, Capacidad, X, Y, Z, Owner) VALUES (%d, 1000, %f, %f, %f, %d)", tipo, X, Y, Z, param2);
			mysql_query(sql);
		}
		else if(tipo == 3 || tipo == 4)
		{
			format(sql, 128, "INSERT INTO parkings (Tipo, Capacidad, X, Y, Z) VALUES (%d, 9999, %f, %f, %f)", tipo, X, Y, Z);
			mysql_query(sql);
		}
	    
		format(sql, sizeof(sql), "SELECT MAX(id) FROM parkings");
		mysql_query(sql);
		mysql_store_result();
		mysql_fetch_row(row);
		id = strval(row);
		
		ParkInfo[TotalParkings][paSQLID] = id;
		ParkInfo[TotalParkings][paType] = tipo;
		if(tipo == 0)
		{
			ParkInfo[TotalParkings][paCap] = param2;
			ParkInfo[TotalParkings][paOwner] = -1;
		}
		else if(tipo == 1)
		{
			ParkInfo[TotalParkings][paCap] = 2;
			ParkInfo[TotalParkings][paOwner] = param2;
		}
		else if(tipo == 2)
		{
			ParkInfo[TotalParkings][paCap] = 1000;
			ParkInfo[TotalParkings][paOwner] = param2;
		}
		else if(tipo == 3 || tipo == 4)
		{
			ParkInfo[TotalParkings][paCap] = 9999;
		}
		ParkInfo[TotalParkings][paTotal] = 0;
		ParkInfo[TotalParkings][paX] = X;
		ParkInfo[TotalParkings][paY] = Y;
		ParkInfo[TotalParkings][paZ] = Z;
		
		if(ParkInfo[TotalParkings][paType] == 0)
		{
			CreateDynamic3DTextLabel("Aparcamiento", Amarillo, ParkInfo[TotalParkings][paX], ParkInfo[TotalParkings][paY], ParkInfo[TotalParkings][paZ], 20);
		}
		else if(ParkInfo[TotalParkings][paType] == 1)
		{
			CreateDynamic3DTextLabel("Garaje", Amarillo, ParkInfo[TotalParkings][paX], ParkInfo[TotalParkings][paY], ParkInfo[TotalParkings][paZ], 5);
		}
		else if(ParkInfo[TotalParkings][paType] == 2)
		{
			CreateDynamic3DTextLabel("Aparcamiento Privado", Amarillo, ParkInfo[TotalParkings][paX], ParkInfo[TotalParkings][paY], ParkInfo[TotalParkings][paZ], 10);
		}
		else if(ParkInfo[TotalParkings][paType] == 3 || ParkInfo[TotalParkings][paType] == 4)
		{
			CreateDynamic3DTextLabel("Deposito", Amarillo, ParkInfo[TotalParkings][paX], ParkInfo[TotalParkings][paY], ParkInfo[TotalParkings][paZ], 20);
		}	
		TotalParkings++;
        mysql_free_result();
		return 1;
	}
	

	if(strcmp(cmd, "/editparking", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(PlayerInfo[playerid][pAdmin] < 3) return 1;
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /editparking [Info|Owner|Plazas|Mover]");
			return 1;
		}

		if(strcmp(tmp, "Info", true) == 0)
		{
			for(new i = 0; i < TotalParkings; i++)
			{
				if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
				{
					format(string,sizeof(string),"[SQLID]: %d - [paType]: %d - [paOwner]: %d - [paCap]: %d - [paTotal]: %d",ParkInfo[i][paSQLID],ParkInfo[i][paType],ParkInfo[i][paOwner],ParkInfo[i][paCap],ParkInfo[i][paTotal]);
					SendClientMessage(playerid, Amarillo, string);
					return 1;
				}
			}
		}
		else if(strcmp(tmp, "Owner", true) == 0)
		{
			new owner;
			tmp = strtokex(cmdtext, idx);
			owner = strval(tmp);
			
			for(new i = 0; i < TotalParkings; i++)
			{
				if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
				{
					ParkInfo[i][paOwner] = owner;
					SaveParking(i);
					SendClientMessage(playerid, Amarillo, "* Has cambiado el número de dueño de este aparcamiento.");
					return 1;
				}
			}
		}
		else if(strcmp(tmp, "Plazas", true) == 0)
		{
			new plazas;
			tmp = strtokex(cmdtext, idx);
			plazas = strval(tmp);
			
			for(new i = 0; i < TotalParkings; i++)
			{
				if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
				{
					ParkInfo[i][paCap] = plazas;
					SaveParking(i);
					SendClientMessage(playerid, Amarillo, "* Has cambiado el número de plazas maximas de este aparcamiento.");
					return 1;
				}
			}
		}
		else if(strcmp(tmp, "Mover", true) == 0)
		{
			for(new i = 0; i < TotalParkings; i++)
			{
				if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
				{
					PlayerInfo[playerid][pMoviendoParking] = i;
					SendClientMessage(playerid, Amarillo, "* Estas moviendo el parking, escribe 'OK' cuando termines.");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, Blanco, "USO: /editarparking [Info|Owner|Plazas|Mover]");
			return 1;
		}
		return 1;
	}

	if(strcmp(cmd, "/parking", true) == 0)
	{
		new parking = NOEXISTE;
		for(new i = 0; i < TotalParkings; i++)
		{
			if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
			{
				parking = i;
				break;
			}
		}
		if(parking == NOEXISTE) return 1;
		if(PlayerInfo[playerid][pAdmin] < 1)
		{
			if(ParkInfo[parking][paType] != 1) return 1;
			if(PlayerInfo[playerid][pPhousekey] == ParkInfo[parking][paOwner])
			{
				SendClientMessage(playerid,AzulClaro,"Coches aparcados en el garaje:");
				for(new i; i < MAX_VEHICLES; i++)
				{
					if(CarInfo[i][cParking] == ParkInfo[parking][paSQLID])
					{
						format(string,sizeof(string),"%s (LS-%d) - Dueño: %s",CarInfo[i][cDescription],CarInfo[i][cCarKey],CarInfo[i][cOwner]);
						SendClientMessage(playerid,Blanco,string);						
					}
				}
			}
			else
			{
				SendClientMessage(playerid,AzulClaro,"* No tienes las llaves de este parking");
			}
		}
		else
		{
			SendClientMessage(playerid,AzulClaro,"Coches aparcados en el aparcamiento:");
			for(new i; i < MAX_VEHICLES; i++)
			{
				if(CarInfo[i][cParking] == ParkInfo[parking][paSQLID])
				{
					format(string,sizeof(string),"%s (LS-%d) - Dueño: %s",CarInfo[i][cDescription],CarInfo[i][cCarKey],CarInfo[i][cOwner]);
					SendClientMessage(playerid,Blanco,string);						
				}
			}
		}
		return 1;
	}
    
	if(strcmp(cmd, "/verparking", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /verparking [1/2/3/4/5 - 6/7/8/9/10]");
			return 1;
		}
		
		new llave = strval(tmp);
		
		switch(llave)
		{
			case 1..5: 
			{
				if(PlayerInfo[playerid][pPCarKey][llave-1] == NOEXISTE)
				{
					SendClientMessage(playerid, Rojo, "* Llave inválida!");
					return 1;
				}
				new coche = GetVehicleByKey(PlayerInfo[playerid][pPCarKey][llave-1]);
				new parking = CarInfo[coche][cParking];
				if(parking == -1 || parking == 0)
				{
					SendClientMessage(playerid, Rojo, "* El coche no se encuentra aparcado en ningun aparcamiento publico o privado.");
					return 1;
				}
				new park;
				for(new i; i < MAX_PARKINGS; i++)
				{
					if(ParkInfo[i][paSQLID] == parking)
					{
						park = i;
						break;
					}
				}
				SetPlayerCheckpoint(playerid, ParkInfo[park][paX], ParkInfo[park][paY], ParkInfo[park][paZ], 8.0);
				PlayerInfo[playerid][pCheckpoint] = 32;
			}
			case 6..10: 
			{
				if(PlayerInfo[playerid][pPCochePrestado][llave-6] == NOEXISTE)
				{
					SendClientMessage(playerid, Rojo, "* Llave inválida!");
					return 1;
				}
				new coche = GetVehicleByKey(PlayerInfo[playerid][pPCochePrestado][llave-6]);
				new parking = CarInfo[coche][cParking];
				if(parking == -1 || parking == 0)
				{
					SendClientMessage(playerid, Rojo, "* El coche no se encuentra aparcado en ningun aparcamiento publico o privado.");
					return 1;
				}
				new park;
				for(new i; i < MAX_PARKINGS; i++)
				{
					if(ParkInfo[i][paSQLID] == parking)
					{
						park = i;
						break;
					}
				}
				SetPlayerCheckpoint(playerid, ParkInfo[park][paX], ParkInfo[park][paY], ParkInfo[park][paZ], 8.0);
				PlayerInfo[playerid][pCheckpoint] = 32;
			}
			default:
			{
				SendClientMessage(playerid, Blanco, "USO: /verparking [1/2/3/4/5 - 6/7/8/9/10]");
				return 1;
			}
		}
		SendClientMessage(playerid, Verde, "* Hemos localizado correctamente tu coche.");
		return 1;
	}
	
	return 0;
}

Parking_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 32)
	{
		SendClientMessage(playerid, Blanco, "PISTA: Utiliza /desaparcar, para sacar el coche del deposito.");
		DisablePlayerCheckpoint(playerid);
		PlayerInfo[playerid][pCheckpoint] = 0;
		return 1;
	}
	return 0;
}


Park_OnPlayerText(playerid,text[])
{
    if(PlayerInfo[playerid][pMoviendoParking] > NOEXISTE)
	{
	    if(strcmp("Ok", text, true) == 0)
	    {
	        new Float:X, Float:Y, Float:Z;
	        GetPlayerPos(playerid, X,Y,Z);
            new i=PlayerInfo[playerid][pMoviendoParking];
	        ParkInfo[i][paX] = X;
	        ParkInfo[i][paY] = Y;
	        ParkInfo[i][paZ] = Z;
			SaveParking(i);
            DestroyDynamic3DTextLabel(ParkInfo[i][paPickup]);
            if(ParkInfo[i][paType] == 0)
            {
                ParkInfo[i][paPickup]=CreateDynamic3DTextLabel("Aparcamiento", Amarillo, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ], 20);
            }
            else if(ParkInfo[i][paType] == 1)
            {
                ParkInfo[i][paPickup]=CreateDynamic3DTextLabel("Garaje", Amarillo, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ], 5);
            }
            else if(ParkInfo[i][paType] == 2)
            {
                ParkInfo[i][paPickup]=CreateDynamic3DTextLabel("Aparcamiento Privado", Amarillo, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ], 10);
            }
            else if(ParkInfo[i][paType] == 3 || ParkInfo[i][paType] == 4)
            {
                ParkInfo[i][paPickup]=CreateDynamic3DTextLabel("Deposito", Amarillo, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ], 20);
            }		
			SendClientMessage(playerid, Gris, "Hecho");
			PlayerInfo[playerid][pMoviendoParking] = NOEXISTE;
			return 1;
		}
	}
    return 0;
}