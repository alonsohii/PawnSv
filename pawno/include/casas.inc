#include <colores>
#include <a_samp>
#include <streamer>
#include <globalvars>
#include <funciones>
#include <deathac>
#include <cuentas>



Casas_OnGameModeInit()
{
	LoadCasa();

	for(new h = 0; h < TotalCasas; h++)
	{
		CasaInfo[h][hPickup] = CreateDynamic3DTextLabel("",Verde,CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz],5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,CasaInfo[h][hVw]);
		UpdateHouseLabel(h);
	}

	return 1;
}

UpdateHouseLabel(h)
{
	if ( CasaInfo[h][hOwned] == -1) //hotel
	{
		format(string,sizeof(string),"%s\nPrecio de alquiler: %d",CasaInfo[h][hName],CasaInfo[h][hPAlq]);
		if ( CasaInfo[h][hAlquilados] >0 ) strcat(string,"\nOcupada");
		else strcat(string,"\nLibre");
	}
	else if ( CasaInfo[h][hOwned] == 0 ) //casa libre
	{
		format(string,sizeof(string),"%s\nEn venta\n precio de compra: %d\nNivel: %d",CasaInfo[h][hName],CasaInfo[h][hValue],CasaInfo[h][hLevel]);
	}
	else if ( CasaInfo[h][hOwned] == 1 && CasaInfo[h][hAlq] == 0) //casa comprada y no alquilable
	{
		format(string,sizeof(string),"%s\nEstado: Ocupado\nInquilinos: %d",CasaInfo[h][hName],CasaInfo[h][hAlquilados]);
	}
	else if ( CasaInfo[h][hOwned] == 1 && CasaInfo[h][hAlq] == 1) //casa comprada y alquilable
	{
		format(string,sizeof(string),"%s\nEstado: Ocupado\nInquilinos: %d\nPrecio de alquiler: %d",CasaInfo[h][hName],CasaInfo[h][hAlquilados],CasaInfo[h][hPAlq]);
	}
	UpdateDynamic3DTextLabelText(CasaInfo[h][hPickup],Verde,string);
}

LoadCasa()
{
	new sql[80], row[512];
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM casas");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	new hcount = strval(row);
    TotalCasas=0;

    format(sql, sizeof(sql), "SELECT * FROM casas ");
	mysql_query(sql);
    mysql_store_result();
    
	for (new idx=0; idx<hcount; idx++)
	{
        mysql_fetch_row(row);
		split(row, arrCoords, '|');
		CasaInfo[idx][hId] = strval(arrCoords[0]);
		CasaInfo[idx][hEx] = floatstr(arrCoords[1]);
		CasaInfo[idx][hEy] = floatstr(arrCoords[2]);
		CasaInfo[idx][hEz] = floatstr(arrCoords[3]);
		CasaInfo[idx][hSx] = floatstr(arrCoords[4]);
		CasaInfo[idx][hSy] = floatstr(arrCoords[5]);
		CasaInfo[idx][hSz] = floatstr(arrCoords[6]);
		CasaInfo[idx][hInterior] = strval(arrCoords[7]);
		CasaInfo[idx][hInterior2] = strval(arrCoords[8]);
		CasaInfo[idx][hVw] = strval(arrCoords[9]);
		CasaInfo[idx][hOwned] = strval(arrCoords[10]);
		format(CasaInfo[idx][hOwner],24,"%s", arrCoords[11]);
		CasaInfo[idx][hLevel] = strval(arrCoords[12]);
		CasaInfo[idx][hValue] = strval(arrCoords[13]);
		CasaInfo[idx][hLock] = strval(arrCoords[14]);
   		format(CasaInfo[idx][hGuns],128,"%s", arrCoords[15]);
   		format(CasaInfo[idx][hAmmos],128,"%s", arrCoords[16]);
   		format(CasaInfo[idx][hDrogas],128,"%s", arrCoords[17]);
		CasaInfo[idx][hDinero] = strval(arrCoords[18]);
		CasaInfo[idx][hAlq] = strval(arrCoords[19]);
		CasaInfo[idx][hPAlq] = strval(arrCoords[20]);
		CasaInfo[idx][hAlquilados] = strval(arrCoords[21]);
        format(CasaInfo[idx][hName],128,"%s", arrCoords[22]);
        
        new Guns[10][32];
        new Ammos[10][32];
        split(CasaInfo[idx][hGuns],Guns,',');
        split(CasaInfo[idx][hAmmos],Ammos,',');
        for(new i = 0; i < 10; i++)
        {
            CasaInfo[idx][hGun][i] = strval(Guns[i]);
            CasaInfo[idx][hAmmo][i] = strval(Ammos[i]);
        }

        new Drogas[7][10];
        split(CasaInfo[idx][hDrogas],Drogas,',');
        CasaInfo[idx][hSemillas][0] = strval(Drogas[0]);
        CasaInfo[idx][hDrogaNP][0] = strval(Drogas[1]);
        CasaInfo[idx][hDrogaP][0] = strval(Drogas[2]);
        CasaInfo[idx][hSemillas][1] = strval(Drogas[3]);
        CasaInfo[idx][hDrogaNP][1] = strval(Drogas[4]);
        CasaInfo[idx][hDrogaP][1] = strval(Drogas[5]);
        CasaInfo[idx][hDrogaP][2] = strval(Drogas[6]);
        
        TotalCasas++;
	}

	mysql_free_result();
    printf("Casas Totales: %d (MAX: %d)",TotalCasas,MAX_CASAS);
	return 1;
}

SaveCasa(idx)
{
    new sql[1024];
    format(sql, 1024, "UPDATE casas SET EX=%f,EY=%f,EZ=%f,SX=%f,SY=%f,SZ=%f,Interior=%d,Interior2=%d,Vw=%d,Owned=%d,Owner='%s',Nivel= %d,Costo=%d,Locked=%d,Dinero=%d,Alquilable=%d,PrecioAlq=%d,Inquilinos=%d,Nombre='%s' WHERE id=%d",
	CasaInfo[idx][hEx],
	CasaInfo[idx][hEy],
	CasaInfo[idx][hEz],
	CasaInfo[idx][hSx],
	CasaInfo[idx][hSy],
	CasaInfo[idx][hSz],
	CasaInfo[idx][hInterior],
	CasaInfo[idx][hInterior2],
	CasaInfo[idx][hVw],
	CasaInfo[idx][hOwned],
	CasaInfo[idx][hOwner],
	CasaInfo[idx][hLevel],
	CasaInfo[idx][hValue],
	CasaInfo[idx][hLock],
	CasaInfo[idx][hDinero],
	CasaInfo[idx][hAlq],
	CasaInfo[idx][hPAlq],
	CasaInfo[idx][hAlquilados],
	CasaInfo[idx][hName],
	CasaInfo[idx][hId]);
	mysql_query(sql);
    
    new tmp[128];
    
    format(CasaInfo[idx][hGuns], 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		CasaInfo[idx][hGun][0],
		CasaInfo[idx][hGun][1],
		CasaInfo[idx][hGun][2],
		CasaInfo[idx][hGun][3],
		CasaInfo[idx][hGun][4],
		CasaInfo[idx][hGun][5],
		CasaInfo[idx][hGun][6],
		CasaInfo[idx][hGun][7],
		CasaInfo[idx][hGun][8],
		CasaInfo[idx][hGun][9]);
	format(tmp, 128, "UPDATE casas SET Armas='%s' WHERE `id` = %d", CasaInfo[idx][hGuns], CasaInfo[idx][hId]);
    mysql_query(tmp);
    
	format(CasaInfo[idx][hAmmos], 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		CasaInfo[idx][hAmmo][0],
		CasaInfo[idx][hAmmo][1],
		CasaInfo[idx][hAmmo][2],
		CasaInfo[idx][hAmmo][3],
		CasaInfo[idx][hAmmo][4],
		CasaInfo[idx][hAmmo][5],
		CasaInfo[idx][hAmmo][6],
		CasaInfo[idx][hAmmo][7],
		CasaInfo[idx][hAmmo][8],
		CasaInfo[idx][hAmmo][9]);
	format(tmp, 128, "UPDATE casas SET Ammos='%s' WHERE `id` = %d", CasaInfo[idx][hAmmos], CasaInfo[idx][hId]);
    mysql_query(tmp);
    
    	
    format(CasaInfo[idx][hDrogas], 128, "%d,%d,%d,%d,%d,%d,%d",
        CasaInfo[idx][hSemillas][0],
        CasaInfo[idx][hDrogaNP][0],
        CasaInfo[idx][hDrogaP][0],
        CasaInfo[idx][hSemillas][1],
        CasaInfo[idx][hDrogaNP][1],
        CasaInfo[idx][hDrogaP][1],
        CasaInfo[idx][hDrogaP][2]);
	format(tmp, 128, "UPDATE casas SET Drogas='%s' WHERE `id` = %d", CasaInfo[idx][hDrogas], CasaInfo[idx][hId]);
    mysql_query(tmp);
    
	return 1;
}



Casas_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);

	if(strcmp(cmd, "/comprarcasa", true) == 0)
	{
 		if(IsPlayerConnected(playerid))
	    {
			for(new h = 0; h < sizeof(CasaInfo); h++)
			{
                if(PlayerToPoint(2.0, playerid, CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz]) &&
                    CasaInfo[h][hVw] == GetPlayerVirtualWorld(playerid) && CasaInfo[h][hOwned] == 0  )
				{
                    if(GetPlayerLevel(playerid) < CasaInfo[h][hLevel])
					{
						format(string, sizeof(string), "* Necesitas nivel %d para comprarla!", CasaInfo[h][hLevel]);
						SendClientMessage(playerid, Rojo, string);
						return 1;
					}
                    if(PlayerInfo[playerid][pPhousekey] != NOEXISTE)
					{
                        if (strcmp(pNameEx(playerid), CasaInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0)
						{
							SendClientMessage(playerid, Naranja, "* Ya tienes actualmente una casa, escribe /vendercasa para venderla!");
							return 1;
						}else{
							SendClientMessage(playerid, Naranja, "* Ya tienes alquilada una casa, escribe /noalquilar para dejarla!");
							return 1;
						}
					}
                    if(SafeGetPlayerMoney(playerid) > CasaInfo[h][hValue])
					{
						PlayerInfo[playerid][pPhousekey] = CasaInfo[h][hId];
						CasaInfo[h][hOwned] = 1;
						strmid(CasaInfo[h][hOwner], pNameEx(playerid), 0, strlen(pNameEx(playerid)), 255);
						SafeGivePlayerMoney(playerid, -CasaInfo[h][hValue]);
						//PlayerPlayMusic(playerid);
						SetPlayerInterior(playerid,CasaInfo[h][hInterior]);
						SetPlayerPos(playerid,CasaInfo[h][hSx],CasaInfo[h][hSy],CasaInfo[h][hSz]);
						SetPlayerVirtualWorld(playerid,CasaInfo[h][hId]);
						GameTextForPlayer(playerid, "~w~Bienvenido a Casa~n~~y~Puedes salir poniendo /salir al lado de la puerta", 5000, 3);
						PlayerInfo[playerid][pInt] = CasaInfo[h][hInterior];
						PlayerInfo[playerid][pVw] = CasaInfo[h][hId];
						SendClientMessage(playerid, Verde, "* Enhorabuena en tu nueva compra! Escribe /ayuda casas para ver todos los comandos!");
						SaveCasa(h);
						UpdateHouseLabel(h);
						SaveValue(playerid, "Casa", PlayerInfo[playerid][pPhousekey]);
						return 1;
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* No tienes el dinero suficiente!");
						return 1;
					}
				}
			}
		}
        SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
        return 1;
	}

	if(strcmp(cmd, "/vendercasa", true) == 0)
	{
     	if(IsPlayerConnected(playerid))
		{
			if(PlayerInfo[playerid][pPhousekey] == NOEXISTE)
			{
				SendClientMessage(playerid, Rojo, "* No tienes casa.");
				return 1;
			}
            new house = GetPlayerHouse(playerid);
            if (house == NOEXISTE ) { SendClientMessage(playerid, Rojo, "* No tienes casa."); return 1; }
			if(strcmp(pNameEx(playerid), CasaInfo[house][hOwner], true) == 0)
			{
				CasaInfo[house][hLock] = 1;
				CasaInfo[house][hOwned] = 0;
				strmid(CasaInfo[house][hOwner], "El Estado", 0, strlen("El Estado"), 255);
				SafeGivePlayerMoney(playerid,CasaInfo[house][hValue]);
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				format(string, sizeof(string), "~w~Felicidades!~n~~y~Has vendido tu propiedad por ~n~~g~%d$", CasaInfo[house][hValue]);
				GameTextForPlayer(playerid, string, 10000, 3);
				PlayerInfo[playerid][pPhousekey] = NOEXISTE;
				if(PlayerInfo[playerid][pInt] == CasaInfo[house][hInterior] && GetPlayerVirtualWorld(playerid) == CasaInfo[house][hId])
				{
					SetPlayerVirtualWorld(playerid,CasaInfo[house][hVw]);
					SetPlayerInterior(playerid,CasaInfo[house][hInterior2]);
					SetPlayerPos(playerid,CasaInfo[house][hEx],CasaInfo[house][hEy],CasaInfo[house][hEz]);
					PlayerInfo[playerid][pInt] = 0;
					PlayerInfo[playerid][pVw] = 0;
				}
				SaveCasa(house);
				UpdateHouseLabel(house);
				SaveValue(playerid, "Casa", PlayerInfo[playerid][pPhousekey]);
				return 1;
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No tienes casa.");
			}
		}
		return 1;
	}

    if(strcmp(cmd, "/editcasa", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
	        return 1;
	    }

	    tmp = strtokex(cmdtext, idx);
     	if(!strlen(tmp))
      	{
       		SendClientMessage(playerid, Blanco, "USO: /editcasa [Campo]");
			SendClientMessage(playerid, AzulClaro, "Campos Disponibles: Nombre, Posicion, Interior, Costo, Alquiler, Nivel, Eliminar");
			return 1;
		}

		if(strcmp(tmp, "Posicion", true) == 0)
		{
			for(new i = 0; i < sizeof(CasaInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid))
			    {
       				PlayerInfo[playerid][pMoviendoCasa] = CasaInfo[i][hId];
			        SendClientMessage(playerid, Amarillo, "* Estas moviendo la Casa, escribe 'OK' cuando termines.");
                    return 1;
				}
			}
			
		}
        
		else if(strcmp(tmp, "Nombre", true) == 0)
		{
			for(new i = 0; i < sizeof(CasaInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid))
			    {
       				PlayerInfo[playerid][pEditingCasa] = CasaInfo[i][hId];
                    SendClientMessage(playerid, Amarillo, "* Escribe un nuevo nombre para la Casa.");
                    return 1;
				}
			}
            SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
            return 1;
		}
        
		else if(strcmp(tmp, "Eliminar", true) == 0)
		{
			for(new i = 1; i < sizeof(CasaInfo); i++)
			{
			    if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid))
			    {
			        new row[512];
			        format(string, 128, "SELECT COUNT(*) FROM casas");
       				mysql_query(string);
       				mysql_store_result();
					mysql_fetch_row(row);
					new rows;
					rows = strval(row);
					if(rows == 1)
					{
						mysql_query("TRUNCATE TABLE casas");
					}
					else
					{
			        	format(string, 128, "DELETE FROM casas WHERE id = %d LIMIT 1", CasaInfo[i][hId]);
			        	mysql_query(string);
					}
					CasaInfo[i][hEx] = NOEXISTE;
			        CasaInfo[i][hEy] = NOEXISTE;
			        CasaInfo[i][hEz] = NOEXISTE;
			        DestroyDynamic3DTextLabel(CasaInfo[i][hPickup]);
                    TotalCasas--;
                    SendClientMessage(playerid, Rojo, "* Casa eliminada.");
                    return 1;
                }
			}
			mysql_free_result();
            SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
            return 1;
		}

		else if(strcmp(tmp, "Costo", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
     		if(!strlen(tmp))
      		{
      		    SendClientMessage(playerid, Blanco, "USO: /editcasa Costo [$$]");
      		   	return 1;
			}
			new id;
			id = strval(tmp);
			for(new i = 0; i < sizeof(CasaInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid))
			    {
			        CasaInfo[i][hValue] = id;
			        SaveCasa(i);
					UpdateHouseLabel(i);
			        format(string, 128, "* Listo! Cambiaste el costo de la Casa a '%d'e", id);
                    SendClientMessage(playerid, Verde, string);
                    return 1;
				}
			}
            SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
            return 1;
		}
        
		else if(strcmp(tmp, "Alquiler", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
     		if(!strlen(tmp))
      		{
      		    SendClientMessage(playerid, Blanco, "USO: /editcasa alquiler [$$]");
      		   	return 1;
			}
			for(new i = 0; i < sizeof(CasaInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid))
			    {
                    new precio;
                    if (IsNumeric(tmp))
                    {
                        precio = strval(tmp);
                    }
                    else
                    {
                        SendClientMessage(playerid, Blanco, "USO: /editcasa alquiler [$$]");
						return 1;
                    }
                    CasaInfo[i][hPAlq]=precio;
                    format(string,sizeof(string),"* Alquiler ajustado a %d$",precio);
                    SendClientMessage(playerid, Verde,string);
                    SaveCasa(i);
                    UpdateHouseLabel(i);
                    return 1;
                }
            }
            SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
            return 1;
		}

		else if(strcmp(tmp, "Nivel", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
     		if(!strlen(tmp))
      		{
      		    SendClientMessage(playerid, Blanco, "USO: /editcasa Nivel [Lvl]");
      		   	return 1;
			}
			new id;
			id = strval(tmp);
			for(new i = 0; i < sizeof(CasaInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid) )
			    {
			        CasaInfo[i][hLevel] = id;
			        SaveCasa(i);
					UpdateHouseLabel(i);
			        format(string, 128, "* Listo! Cambiaste el nivel de la Casa a '%d'", id);
                    SendClientMessage(playerid, Verde, string);
                    return 1;
				}
			}
            SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
            return 1;
		}

		else if(strcmp(tmp, "Interior", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
		    if(!strlen(tmp))
		    {
		        SendClientMessage(playerid, Blanco, "USO: /editcasa interior [P. 1-6 | M. 7-15 | G. 16-28 | Hab. 29-38 | Caravana. 39]");
				return 1;
			}
			new inter;
			inter = strval(tmp);
			for(new i = 0; i < sizeof(CasaInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid) )
			    {
					switch(inter)
					{
					    //Interiores pequeños
                        case 1: CasaInfo[i][hSx]=-68.8769, CasaInfo[i][hSy]=1351.6051, CasaInfo[i][hSz]=1080.2109, CasaInfo[i][hInterior]= 6;
						case 2: CasaInfo[i][hSx]=-42.5718, CasaInfo[i][hSy]=1405.4707, CasaInfo[i][hSz]=1084.4297, CasaInfo[i][hInterior]= 8;
						case 3: CasaInfo[i][hSx]=223.1618, CasaInfo[i][hSy]=1287.1193, CasaInfo[i][hSz]=1082.1406, CasaInfo[i][hInterior]= 1;
						case 4: CasaInfo[i][hSx]=221.8276, CasaInfo[i][hSy]=1140.5168, CasaInfo[i][hSz]=1082.6094, CasaInfo[i][hInterior]= 4;
						case 5: CasaInfo[i][hSx]=328.1076, CasaInfo[i][hSy]=1477.8431, CasaInfo[i][hSz]=1084.4375, CasaInfo[i][hInterior]= 15;
						case 6: CasaInfo[i][hSx]=22.9175, CasaInfo[i][hSy]=1403.5530, CasaInfo[i][hSz]=1084.4297, CasaInfo[i][hInterior]= 5;
						//Interiores medianos
						case 7: CasaInfo[i][hSx]=2365.0168, CasaInfo[i][hSy]=-1135.3094, CasaInfo[i][hSz]=1050.8750, CasaInfo[i][hInterior]= 8;
						case 8: CasaInfo[i][hSx]=2270.3882, CasaInfo[i][hSy]=-1210.2815, CasaInfo[i][hSz]=1047.5625, CasaInfo[i][hInterior]= 10;
						case 9: CasaInfo[i][hSx]=-260.5417, CasaInfo[i][hSy]=1456.2577, CasaInfo[i][hSz]=1084.3672, CasaInfo[i][hInterior]= 4;
						case 10: CasaInfo[i][hSx]=2333.2151, CasaInfo[i][hSy]=-1077.3209, CasaInfo[i][hSz]=1049.0234, CasaInfo[i][hInterior]= 6;
						case 11: CasaInfo[i][hSx]=260.8665, CasaInfo[i][hSy]=1284.5745, CasaInfo[i][hSz]=1080.2578, CasaInfo[i][hInterior]= 4;
						case 12: CasaInfo[i][hSx]=260.5428, CasaInfo[i][hSy]=1237.2369, CasaInfo[i][hSz]=1084.2578, CasaInfo[i][hInterior]= 9;
						case 13: CasaInfo[i][hSx]=386.9386, CasaInfo[i][hSy]=1471.8782, CasaInfo[i][hSz]=1080.1875, CasaInfo[i][hInterior]= 15;
						case 14: CasaInfo[i][hSx]=226.6141, CasaInfo[i][hSy]=1240.0334, CasaInfo[i][hSz]=1082.1406, CasaInfo[i][hInterior]= 2;
						case 15: CasaInfo[i][hSx]=23.9293, CasaInfo[i][hSy]=1340.2648, CasaInfo[i][hSz]=1084.3750, CasaInfo[i][hInterior]= 10;
						//Interiores grandes
						case 16: CasaInfo[i][hSx]=2324.1143, CasaInfo[i][hSy]=-1149.5406, CasaInfo[i][hSz]=1050.710, CasaInfo[i][hInterior]= 12;
						case 17: CasaInfo[i][hSx]=235.4422, CasaInfo[i][hSy]=1186.7810, CasaInfo[i][hSz]=1080.2578, CasaInfo[i][hInterior]= 3;
						case 18: CasaInfo[i][hSx]=490.9660, CasaInfo[i][hSy]=1398.7607, CasaInfo[i][hSz]=1080.2578, CasaInfo[i][hInterior]= 2;
						case 19: CasaInfo[i][hSx]=234.4409, CasaInfo[i][hSy]=1064.2129, CasaInfo[i][hSz]=1084.2115, CasaInfo[i][hInterior]= 6;
						case 20: CasaInfo[i][hSx]=226.5535, CasaInfo[i][hSy]=1114.1012, CasaInfo[i][hSz]=1080.9943, CasaInfo[i][hInterior]= 5;
						case 21: CasaInfo[i][hSx]=140.2069, CasaInfo[i][hSy]=1366.1321, CasaInfo[i][hSz]=1083.8594, CasaInfo[i][hInterior]= 5;
						case 22: CasaInfo[i][hSx]=225.7627, CasaInfo[i][hSy]=1021.7071, CasaInfo[i][hSz]=1084.0170, CasaInfo[i][hInterior]= 7;
						case 23: CasaInfo[i][hSx]=2317.4592, CasaInfo[i][hSy]=-1026.3820, CasaInfo[i][hSz]=1050.2178, CasaInfo[i][hInterior]= 9;
						case 24: CasaInfo[i][hSx]=446.8984, CasaInfo[i][hSy]=1397.0696, CasaInfo[i][hSz]=1084.3047, CasaInfo[i][hInterior]= 2;
						case 25: CasaInfo[i][hSx]=295.2993, CasaInfo[i][hSy]=1472.5591, CasaInfo[i][hSz]=1080.2578, CasaInfo[i][hInterior]= 15;
						case 26: CasaInfo[i][hSx]=83.3735, CasaInfo[i][hSy]=1322.2920, CasaInfo[i][hSz]=1083.8662, CasaInfo[i][hInterior]= 9;
						case 27: CasaInfo[i][hSx]=376.7856, CasaInfo[i][hSy]=1417.3190, CasaInfo[i][hSz]=1081.328, CasaInfo[i][hInterior]= 15;
						case 28: CasaInfo[i][hSx]=2496.3818,CasaInfo[i][hSy]=-1694.3456,CasaInfo[i][hSz]=1014.7422,CasaInfo[i][hInterior]= 3;
                        //Interiores hoteles
                        case 29: CasaInfo[i][hSx]=2218.2944, CasaInfo[i][hSy]=-1076.0085, CasaInfo[i][hSz]=1050.4844, CasaInfo[i][hInterior]=1;
                        case 30: CasaInfo[i][hSx]=2233.5474, CasaInfo[i][hSy]=-1114.8636, CasaInfo[i][hSz]=1050.8828, CasaInfo[i][hInterior]=5;
                        case 31: CasaInfo[i][hSx]=2365.2593, CasaInfo[i][hSy]=-1135.2416, CasaInfo[i][hSz]=1050.8750, CasaInfo[i][hInterior]=8;
                        case 32: CasaInfo[i][hSx]=2237.2478, CasaInfo[i][hSy]=-1081.6407, CasaInfo[i][hSz]=1049.0234, CasaInfo[i][hInterior]=2;
                        case 33: CasaInfo[i][hSx]=2282.8762, CasaInfo[i][hSy]=-1140.2819, CasaInfo[i][hSz]=1050.8984, CasaInfo[i][hInterior]=11;
                        case 34: CasaInfo[i][hSx]=243.7287, CasaInfo[i][hSy]=305.4619, CasaInfo[i][hSz]=999.1484, CasaInfo[i][hInterior]=1;
                        case 35: CasaInfo[i][hSx]=2317.8538, CasaInfo[i][hSy]=-1026.7557, CasaInfo[i][hSz]=1050.2178, CasaInfo[i][hInterior]=9;
                        case 36: CasaInfo[i][hSx]=2308.6167, CasaInfo[i][hSy]=-1212.9283, CasaInfo[i][hSz]=1049.0234, CasaInfo[i][hInterior]=6;
                        case 37: CasaInfo[i][hSx]=2270.2515, CasaInfo[i][hSy]=-1210.3717, CasaInfo[i][hSz]=1047.5625, CasaInfo[i][hInterior]=10;
                        case 38: CasaInfo[i][hSx]=266.5029, CasaInfo[i][hSy]=304.8156, CasaInfo[i][hSz]=999.1484, CasaInfo[i][hInterior]=2;
						case 39: CasaInfo[i][hSx]=2513.2227, CasaInfo[i][hSy]=-1729.0717, CasaInfo[i][hSz]=778.6371, CasaInfo[i][hInterior]=1;
					}
					SaveCasa(i);
					UpdateHouseLabel(i);
                    SendClientMessage(playerid, Verde, "* Has cambiado el interior de la casa.");
					return 1;
				}
			}
            SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
            return 1;
		}
		return 1;
	}

	if(strcmp(cmd, "/crearcasa", true) == 0)
	{
	    new sql[80], row[256], id;
	    if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
	        return 1;
	    }

		//print("Query 1");
		format(sql, 80, "INSERT INTO casas (Owner) VALUES ('El Estado')");
		mysql_query(sql);

		//print("Query 2");
		format(sql, sizeof(sql), "SELECT MAX(id) FROM casas");
		mysql_query(sql);
		mysql_store_result();
		mysql_fetch_row(row);
		id = strval(row);
		//printf("Query Result: %d",id);

		//print("Seteando Datos");
		CasaInfo[TotalCasas][hId] = id;
		CasaInfo[TotalCasas][hLock] = 1;
		CasaInfo[TotalCasas][hValue] = 30000;
		CasaInfo[TotalCasas][hLevel] = 5;
		CasaInfo[TotalCasas][hDinero] = 0;
		CasaInfo[TotalCasas][hOwned] = 0;
		format(CasaInfo[TotalCasas][hName], 128, "Casa");
        
        //print("Seteando Armas");
        for (new i=0; i < 10; i++)
        {
            CasaInfo[TotalCasas][hGun][i] = NOEXISTE;
            CasaInfo[TotalCasas][hAmmo][i] = NOEXISTE;
        }
        
		//print("Seteando Droga");
        for (new i=0; i < 2; i++)
        {
            CasaInfo[TotalCasas][hDrogaP][i] = 0;
            CasaInfo[TotalCasas][hDrogaNP][i] = 0;
            CasaInfo[TotalCasas][hSemillas][i] = 0;
        }
        CasaInfo[TotalCasas][hDrogaP][2] = 0;
        
		//print("Seteando Owner");
		format(CasaInfo[TotalCasas][hOwner], 24, "El Estado");
		new Float:X[MAX_PLAYERS], Float:Y[MAX_PLAYERS], Float:Z[MAX_PLAYERS];
  		GetPlayerPos(playerid, X[playerid],Y[playerid],Z[playerid]);
		//print("Seteando Coords");
  		CasaInfo[TotalCasas][hEx] = X[playerid];
  		CasaInfo[TotalCasas][hEy] = Y[playerid];
  		CasaInfo[TotalCasas][hEz] = Z[playerid];
        CasaInfo[TotalCasas][hSx] = -68.8769;
        CasaInfo[TotalCasas][hSy] = 1351.6051;
        CasaInfo[TotalCasas][hSz] = 1080.2109;
        CasaInfo[TotalCasas][hInterior] = 6;
        CasaInfo[TotalCasas][hInterior2] = GetPlayerInterior(playerid);
		CasaInfo[TotalCasas][hVw] = GetPlayerVirtualWorld(playerid);

        CasaInfo[TotalCasas][hPAlq] = 100;
        
		//print("Salvando Datos");
		SaveCasa(TotalCasas);

		//print("Creando Pickup");
		CasaInfo[TotalCasas][hPickup] = CasaInfo[TotalCasas][hPickup] = CreateDynamic3DTextLabel("",Verde,CasaInfo[TotalCasas][hEx], CasaInfo[TotalCasas][hEy], CasaInfo[TotalCasas][hEz],5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,CasaInfo[TotalCasas][hVw]);
		UpdateHouseLabel(TotalCasas);
        TotalCasas++;
        format(string,sizeof(string),"* Casa %d creada",TotalCasas);
        SendClientMessage(playerid, Verde,string);
		mysql_free_result();
		return 1;
	}

	if(strcmp(cmd, "/habitacion", true) == 0)
	{
        if(IsPlayerConnected(playerid))
		{
        	if(PlayerInfo[playerid][pAdmin] < 3)
            {
                SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
                return 1;
            }
            for(new h = 0; h < sizeof(CasaInfo); h++)
			{
				if(PlayerToPoint(2.0, playerid, CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz]) && CasaInfo[h][hVw] == GetPlayerVirtualWorld(playerid))
				{
                    if (CasaInfo[h][hOwned] == 0)
                    {
                        CasaInfo[h][hOwned] = -1;
                        CasaInfo[h][hAlq] = 1;
                        UpdateHouseLabel(h);
                        return SendClientMessage(playerid, Verde, "* Habitacion creada");
                    }
                    else if (CasaInfo[h][hOwned] == -1)
                    {
                        CasaInfo[h][hOwned] = 0;
                        CasaInfo[h][hAlq] = 0;
                        UpdateHouseLabel(h);
                        return SendClientMessage(playerid, Verde, "* Casa creada");
                    }
                }
            }
            return SendClientMessage(playerid, Rojo, "* No estas cerca de ninguna casa");
        }
        return 1;
    }
        
	if(strcmp(cmd, "/alquilar", true) == 0)
	{
		if(IsPlayerConnected(playerid))
		{
			for(new h = 0; h < sizeof(CasaInfo); h++)
			{
				if(PlayerToPoint(2.0, playerid, CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz]) 
                    && CasaInfo[h][hVw] == GetPlayerVirtualWorld(playerid) &&
                        CasaInfo[h][hOwned] != 0 &&  CasaInfo[h][hAlq] == 1  )
				{
					if(GetPlayerHouse(playerid) != NOEXISTE)
					{
						if (strcmp(pNameEx(playerid), CasaInfo[GetPlayerHouse(playerid)][hOwner], true) == 0)
						{
							SendClientMessage(playerid, Naranja, "* Ya tienes actualmente una casa, escribe /vendercasa para venderla!");
							return 1;
						}else{
							SendClientMessage(playerid, Naranja, "* Ya tienes alquilada una casa, escribe /noalquilar para dejarla!");
							return 1;
						}
					}
					if ( CasaInfo[h][hOwned] < 0 ) 
					{ 
						if ( CasaInfo[h][hAlquilados] > 0 ) 
						{
							SendClientMessage(playerid, Rojo, "* Esta habitacion ya esta alquilada!");
							return 1;
						}
					}
					else
					{	
						if ( CasaInfo[h][hAlquilados] == 2 || ( CasaInfo[h][hOwned] == -1 && CasaInfo[h][hAlquilados] == 1 ) )
						{
							SendClientMessage(playerid, Rojo, "* Ya hay demasiados inquilinos!");
							return 1;
						}
						if ( CasaInfo[h][hAlq] == 0 )
						{
							SendClientMessage(playerid, Rojo, "* No puedes alquilar esta casa!");
							return 1;
						}
					}
					if(GetPlayerMoney(playerid) > CasaInfo[h][hPAlq])
					{
						PlayerInfo[playerid][pPhousekey] = CasaInfo[h][hId];
						SafeGivePlayerMoney(playerid,-CasaInfo[h][hPAlq]);
						CasaInfo[h][hDinero] += CasaInfo[h][hPAlq];
						CasaInfo[h][hAlquilados] += 1;
						SetPlayerInterior(playerid,CasaInfo[h][hInterior]);
						SetPlayerPos(playerid,CasaInfo[h][hSx],CasaInfo[h][hSy],CasaInfo[h][hSz]);
						SetPlayerVirtualWorld(playerid,CasaInfo[h][hId]);
						GameTextForPlayer(playerid, "~w~Bienvenido a Casa~n~~y~Puedes salir poniendo /salir al lado de la puerta", 5000, 3);
						PlayerInfo[playerid][pInt] = CasaInfo[h][hInterior];
						PlayerInfo[playerid][pVw] = CasaInfo[h][hId];
						SendClientMessage(playerid, Verde, "* Enhorabuena, puedes entrar y salir cuando quieras! Escribe /ayuda casas para ver todos los comandos!");
						SendClientMessage(playerid, Verde, "* Usa /noalquilar para dejar de alquilar.");
						SaveCasa(h);
						UpdateHouseLabel(h);
						SaveValue(playerid, "Casa", PlayerInfo[playerid][pPhousekey]);
						return 1;
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* No tienes suficiente dinero!");
						return 1;
					}
				}
			}
		}
        SendClientMessage(playerid, Rojo, "* No estás cerca de una casa.");
        return 1;
    }

	if(strcmp(cmd, "/noalquilar", true) == 0)
	{
		if(IsPlayerConnected(playerid))
		{
			if(GetPlayerHouse(playerid) == NOEXISTE)
			{
				SendClientMessage(playerid, Rojo, "* No estas alquilando una casa!");
				return 1;
			}
			else if (strcmp(pNameEx(playerid), CasaInfo[GetPlayerHouse(playerid)][hOwner], true) == 0)
			{
				SendClientMessage(playerid, Rojo, "* No estas alquilando una casa!");
				return 1;
			}
			new h = GetPlayerHouse(playerid);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			format(string, sizeof(string), "~w~~n~ Has dejado tu casa");
			GameTextForPlayer(playerid, string, 10000, 3);
			PlayerInfo[playerid][pPhousekey] = NOEXISTE;
			if(PlayerInfo[playerid][pInt] == CasaInfo[h][hInterior] && GetPlayerVirtualWorld(playerid) == CasaInfo[h][hId])
			{
				SetPlayerVirtualWorld(playerid,CasaInfo[h][hVw]);
				SetPlayerInterior(playerid,CasaInfo[h][hInterior2]);
				SetPlayerPos(playerid,CasaInfo[h][hEx],CasaInfo[h][hEy],CasaInfo[h][hEz]);
				PlayerInfo[playerid][pInt] = 0;
				PlayerInfo[playerid][pVw] = 0;
			}
			CasaInfo[h][hAlquilados] -= 1;
			SaveCasa(h);
			UpdateHouseLabel(h);
			SaveValue(playerid, "Casa", PlayerInfo[playerid][pPhousekey]);
		}
		return 1;
	}

	if(strcmp(cmd, "/desalojar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
		{
			new h = GetPlayerHouse(playerid);
			if (h == NOEXISTE ) { SendClientMessage(playerid, Rojo, "* No tienes casa!"); return 1; }
            if (strcmp(pNameEx(playerid), CasaInfo[h][hOwner], true) == 0)
			{
				new name[MAX_PLAYER_NAME];
                name = strtokex(cmdtext, idx);
				if(!strlen(name))
				{
					SendClientMessage(playerid, Blanco, "USO: /desalojar [IdJugador/ParteDelNombre]");
                    return 1;
				}
				new target;
				target = ReturnUser(name,playerid);
				if (target == playerid)
				{
					SendClientMessage(target, Rojo, "* No puedes desalojarte a ti mismo.");
					return 1;
				}
				if(IsPlayerConnected(target))
				{
				    if(target != INVALID_PLAYER_ID)
				    {
						if (PlayerInfo[target][pPhousekey] == PlayerInfo[playerid][pPhousekey] )
						{
							SendClientMessage(target, Naranja, "* Has sido deslojado por el dueño de la casa.");
							format(string,sizeof(string),"* Has desalojado a %s",pName(target));
							SendClientMessage(playerid, Verde, string);
							PlayerInfo[target][pPhousekey] = NOEXISTE;
							CasaInfo[h][hAlquilados]--;
							SaveCasa(h);
							UpdateHouseLabel(h);
							SaveValue(target, "Casa", PlayerInfo[target][pPhousekey]);
							return 1;
						}
						else
						{
						    SendClientMessage(playerid, Rojo, "Ese jugador no está de alquiler en tu casa!");
						    return 1;
						}
					}
				}
				else
				{
                    new sql[128], row[128];
                    new count;
                	format(sql, 128, "SELECT COUNT(*) FROM players WHERE Nombre='%s' AND Casa=%d",
                        name,
                        PlayerInfo[playerid][pPhousekey]);
                    mysql_query(sql);
                    mysql_store_result();
                    mysql_fetch_row(row);
                    count = strval(row);
                    if (count==1) 
                    {
                        format(sql, 128, "UPDATE players SET Casa=-1 WHERE Nombre='%s' AND Casa=%d",
                            name,
                            PlayerInfo[playerid][pPhousekey]);
                        mysql_query(sql);
                        
                        Replace(name, "_", " ");
                        format(string,sizeof(string),"* Has desalojado a %s",name);
                        SendClientMessage(playerid, Verde, string);
						CasaInfo[h][hAlquilados]--;
						SaveCasa(h);
						UpdateHouseLabel(h);
						mysql_free_result();
                    }
                    else
                    {
						mysql_free_result();
                        SendClientMessage(playerid, Naranja, "Jugador no encontrado o no esta de alquiler en tu casa, usa /desalojar Nombre_Apellido");
						return 1;
                    }
                }
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No tienes casa!");
				return 1;
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/desalojartodos", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
		{
			new h = GetPlayerHouse(playerid);
			if (h == NOEXISTE ) { SendClientMessage(playerid, Rojo, "* No tienes casa!"); return 1; }
            if (strcmp(pNameEx(playerid), CasaInfo[h][hOwner], true) == 0)
			{
				for(new i = 0; i < MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i))
					{
						if(i != playerid)
						{
							if (PlayerInfo[i][pPhousekey] == PlayerInfo[playerid][pPhousekey] )
							{
                                SendClientMessage(i, Naranja, "* Has sido desalojado de casa.");
								PlayerInfo[i][pPhousekey] = NOEXISTE;
								CasaInfo[h][hAlquilados]--;
								SaveValue(i, "Casa", PlayerInfo[i][pPhousekey]);
							}
						}
					}
				}
            
                new sql[128], row[128];
                new count;
                format(sql, 128, "SELECT COUNT(*) FROM players WHERE Nombre!='%s' AND Casa=%d",
                    pNameEx(playerid),
                    PlayerInfo[playerid][pPhousekey]);
                mysql_query(sql);
                mysql_store_result();
                mysql_fetch_row(row);
                count = strval(row);
                CasaInfo[h][hAlquilados] -= count;
                if (count>0) 
                {
                    format(sql, 128, "UPDATE players SET Casa=-1 WHERE Nombre!='%s' AND Casa=%d",
                        pNameEx(playerid),
                        PlayerInfo[playerid][pPhousekey]);
                    mysql_query(sql);
                }
                
                SendClientMessage(playerid, Verde, "* Has desalojado a todos tus inquilinos.");

                mysql_free_result();
				SaveCasa(h);
				UpdateHouseLabel(h);
				return 1;
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No tienes casa!");
				return 1;
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/puerta", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
	        for(new i = 0; i < sizeof(CasaInfo); i++)
			{

				if ( (PlayerToPoint(3.0, playerid,CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid) ) ||
                      (PlayerToPoint(3.0, playerid,CasaInfo[i][hSx], CasaInfo[i][hSy], CasaInfo[i][hSz]) && GetPlayerVirtualWorld(playerid)== CasaInfo[i][hId]) )
				{
					if(GetPlayerHouse(playerid) == i)
					{
						if(CasaInfo[i][hLock] == 1)
						{
							CasaInfo[i][hLock] = 0;
							GameTextForPlayer(playerid, "~w~Puerta ~g~Desbloqueada", 5000, 6);
							PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                            SaveCasa(i);
                            UpdateHouseLabel(i);
							return 1;
						}
						if(CasaInfo[i][hLock] == 0)
						{
							CasaInfo[i][hLock] = 1;
							GameTextForPlayer(playerid, "~w~Puerta ~r~Bloqueada", 5000, 6);
							PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                            SaveCasa(i);
                            UpdateHouseLabel(i);
							return 1;
						}
					}
					else
					{
						GameTextForPlayer(playerid, "~w~No tienes la ~g~llave ~w~de este lugar", 5000, 6);
						return 1;
					}
				}
			}
	    }
	    return 1;
	} 
    if(strcmp(cmd, "/alquiler", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
		{
			new h = GetPlayerHouse(playerid); 
			if (h == NOEXISTE) { SendClientMessage(playerid, Rojo, "No eres el dueño de una casa!"); return 1; }
            if (strcmp(pNameEx(playerid), CasaInfo[h][hOwner], true) == 0)
			{
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, Blanco, "USO: /alquiler [precio]");
					return 1; 
				}
                new precio;
                if (IsNumeric(tmp))
                {
                    precio = strval(tmp);
                }
                else
                {
   					SendClientMessage(playerid, Blanco, "USO: /alquiler [precio]");
					return 1; 
				}
				
				if(precio > 500 || precio < 0) { SendClientMessage(playerid, Gris, " * Maximo $500, minimo $0"); return 1; }
				
                CasaInfo[h][hPAlq]=precio;
                format(string,sizeof(string),"* Alquiler ajustado a %d$",precio);
                SendClientMessage(playerid, Verde,string);
                SaveCasa(h);
                UpdateHouseLabel(h);
                return 1;
            }
            else { SendClientMessage(playerid, Rojo, "No eres el dueño de una casa!"); return 1; }
        }
        return 1;
    }
    
    if(strcmp(cmd, "/alquilable", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
		{
			new h = GetPlayerHouse(playerid);
			if (h == NOEXISTE) return SendClientMessage(playerid, Rojo, "* No tienes casa!");
            if (strcmp(pNameEx(playerid), CasaInfo[h][hOwner], true) == 0)
			{

                if ( CasaInfo[h][hAlq] )
                {
                    CasaInfo[h][hAlq] = 0;
                    SendClientMessage(playerid,Naranja,"* Tu casa ya no esta en alquiler");
                }
                else
                {
                    CasaInfo[h][hAlq] = 1;
                    SendClientMessage(playerid,Verde,"* Has puesto tu casa en alquiler");
                }
                format(string,sizeof(string),"* Precio de alquiler: %d$",CasaInfo[h][hPAlq]);
                SendClientMessage(playerid,Amarillo,string);
                SaveCasa(h);
                UpdateHouseLabel(h);
            }
            else SendClientMessage(playerid, Rojo, "* No tienes casa!");
        }
        return 1;
    }

    if(strcmp(cmd, "/armario", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
		{
			if(IsACaravana(playerid)) { SendClientMessage(playerid, Rojo, "* La caravana no tiene armario."); return 1;}
            new house = GetPlayerHouse(playerid);
            if((house != NOEXISTE && strcmp(pNameEx(playerid), CasaInfo[house][hOwner], true) == 0) || IsACop(playerid))
			{
   				if (PlayerToPoint(100.0, playerid,CasaInfo[house][hSx],CasaInfo[house][hSy],CasaInfo[house][hSz]) 
                        && GetPlayerVirtualWorld(playerid)==CasaInfo[house][hId])
				{
                    new buffer[128];
                    SendClientMessage(playerid, Naranja, "Armario:");
                    for(new slot = 0; slot != 10; slot++)
                    {
                        new gunname[100];
                        if(CasaInfo[house][hGun][slot]!= NOEXISTE)
                        {
                            GetWeaponName(CasaInfo[house][hGun][slot], gunname, sizeof(gunname));
                            format(buffer, sizeof(buffer), "Espacio %i: %s (Balas: %i)", slot+1, gunname, CasaInfo[house][hAmmo][slot]);
                            SendClientMessage(playerid, Amarillo, buffer);
                        }
                    }
                    format(buffer, sizeof(buffer),"Marihuana: %d semillas, %d gramos sin preparar, %d preparados",CasaInfo[house][hSemillas][0],
                            CasaInfo[house][hDrogaNP][0],CasaInfo[house][hDrogaP][0]);
                    SendClientMessage(playerid, Verde, buffer);
                    format(buffer, sizeof(buffer),"Coca: %d semillas, %d gramos sin preparar, %d preparados",CasaInfo[house][hSemillas][1],
                            CasaInfo[house][hDrogaNP][1],CasaInfo[house][hDrogaP][1]);
                    SendClientMessage(playerid, Verde, buffer);
                    format(buffer, sizeof(buffer),"Crack: %d gramos preparados",CasaInfo[house][hDrogaP][2]);
                    SendClientMessage(playerid, Verde, buffer);
                    format(buffer, sizeof(buffer),"Dinero: %d$",CasaInfo[house][hDinero]);
                    SendClientMessage(playerid, Verde, buffer);
                    SendClientMessage(playerid,Verde," Comandos: /guardararma, /tomararma, /guardardrogas, /tomardrogas, /guardardinero, /tomardinero");
                }
                else
                {
                    SendClientMessage(playerid, Rojo, "* No estás en tu casa.");
                    return 1;
                }
            }
            else
            {
                SendClientMessage(playerid, Rojo, "* No tienes una casa en propiedad.");
                return 1;
            }
        }
        return 1;
    }
	
	if(strcmp(cmd, "/nevera", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
		{
            new house = GetPlayerHouse(playerid);
            if((house != NOEXISTE && strcmp(pNameEx(playerid), CasaInfo[house][hOwner], true) == 0) || IsACop(playerid))
			{
   				if (PlayerToPoint(100.0, playerid,CasaInfo[house][hSx],CasaInfo[house][hSy],CasaInfo[house][hSz]) 
                        && GetPlayerVirtualWorld(playerid)==CasaInfo[house][hId])
				{
                    if(GetPlayerPremium(playerid) >= 2)
					{
						if(PlayerInfo[playerid][pMenu] == 1) return 1;
						TogglePlayerControllable(playerid,0);
						ShowMenuForPlayer(nevera, playerid);
						PlayerInfo[playerid][pMenu] = 1;
					}
					else
					{
						SendClientMessage(playerid, Rojo, " * Para utilizar esta función debes ser usuario premium plata o superior.");
						return 1;
					}
                }
                else
                {
                    SendClientMessage(playerid, Rojo, "* No estás en tu casa.");
                    return 1;
                }
            }
            else
            {
                SendClientMessage(playerid, Rojo, "* No tienes una casa en propiedad.");
                return 1;
            }
        }
        return 1;
    }

   	if(strcmp(cmd, "/casainfo", true) == 0)
	{
        if(IsPlayerConnected(playerid))
		{
        	if(PlayerInfo[playerid][pAdmin] < 1)
            {
                SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
                return 1;
            }
            tmp = strtokex(cmdtext, idx);
            new i=NOEXISTE;
            if(!strlen(tmp))
            {
                for(new h = 0; h < sizeof(CasaInfo); h++)
                {
                    if (PlayerToPoint(3.0, playerid,CasaInfo[h][hEx],CasaInfo[h][hEy],CasaInfo[h][hEz]))
                    {
                        i=h;
                        break;
                    }
                }
                if (i==NOEXISTE) return 1;
            }
            else
            {
                i=strval(tmp);
            }
            format(string,sizeof(string),"Indice: %d, Llave: %d",i,CasaInfo[i][hId]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Entrada: %f, %f, %f",CasaInfo[i][hEx],CasaInfo[i][hEy],CasaInfo[i][hEz]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Salida: %f, %f, %f",CasaInfo[i][hSx],CasaInfo[i][hSy],CasaInfo[i][hSz]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Interior 1: %d, Interior 2: %d",CasaInfo[i][hInterior],CasaInfo[i][hInterior2]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Comprada: %d, Dueño: %s",CasaInfo[i][hOwned],CasaInfo[i][hOwner]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Nivel: %d, Coste: %d",CasaInfo[i][hLevel],CasaInfo[i][hValue]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Bloqueada: %d",CasaInfo[i][hLock]);
            SendClientMessage(playerid,Blanco,string);
            for(new g=0;g<10;g++)
            {
                format(string,sizeof(string),"Arma %d: %d, Balas: %d",g,CasaInfo[i][hGun][g],CasaInfo[i][hAmmo][g]);
                SendClientMessage(playerid,Blanco,string);
            }
            for(new g=0;g<2;g++)
            {
                format(string,sizeof(string),"Droga %d: Semillas %d, Sin prep: %d, Prep: %d",g,CasaInfo[i][hSemillas][g],CasaInfo[i][hDrogaNP][g],CasaInfo[i][hDrogaP][g]);
                SendClientMessage(playerid,Blanco,string);
            }
            format(string,sizeof(string),"Droga 2: Prep: %d",CasaInfo[i][hDrogaP][2]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Dinero: %d",CasaInfo[i][hDinero]);
            SendClientMessage(playerid,Blanco,string);
            format(string,sizeof(string),"Alquilable: %d, Precio: %d, Inquil.: %d",CasaInfo[i][hAlq],CasaInfo[i][hPAlq],CasaInfo[i][hAlquilados]);
            SendClientMessage(playerid,Blanco,string);


        }
        return 1;
    }
    
    if(strcmp(cmd, "/gotocasa", true) == 0)
	{
        if(IsPlayerConnected(playerid))
		{
        	if(PlayerInfo[playerid][pAdmin] < 2)
            {
                SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
                return 1;
            }
            tmp = strtokex(cmdtext, idx);
 			if(!strlen(tmp) || !IsNumeric(tmp))
			{
				SendClientMessage(playerid, Blanco, "* USO: /gotocasa [Llave]");
				return 1;
			}
			new casa = GetHouseFromId(strval(tmp));
			if (casa == NOEXISTE)
			{
				SendClientMessage(playerid, Rojo, "* Error el código de la llave. Casa no encontrada");
				return 1;
			}
            if (GetPlayerState(playerid) == 2)
            {
                SendClientMessage(playerid, Rojo, "* Bajate antes del coche");
				return 1;            }
            else
            {
                SetPlayerInterior(playerid,CasaInfo[casa][hInterior2]);
                SetPlayerPos(playerid, CasaInfo[casa][hEx], CasaInfo[casa][hEy], CasaInfo[casa][hEz]);
                SetPlayerVirtualWorld(playerid,CasaInfo[casa][hVw]);
            }
            SendClientMessage(playerid, AzulClaro, "* Te has teleportado a la posición de la casa.");
        }
        return 1;
    }
	if(strcmp(cmd, "/timbre", true) == 0)
	{
		for(new h = 0; h < sizeof(CasaInfo); h++)
		{
			if(PlayerToPoint(2.0, playerid, CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz]) && GetPlayerVirtualWorld(playerid)==CasaInfo[h][hVw])
			{
                SendClientMessage(playerid, Verde, "* Has llamado al timbre. ¡Ding, dong!");
                format(string,sizeof(string),"%s ha llamado al timbre de la casa. ¡Ding, dong!",pName(playerid));
                for (new i =0; i< MAX_PLAYERS;i++)
                {
                    if (GetPlayerVirtualWorld(i)==CasaInfo[h][hId] && GetPlayerInterior(i)==CasaInfo[h][hInterior])
                    {
                        SendClientMessage(i, Verde, "Suena el timbre de la casa ¡Ding, dong!");
                    }
                    else if (playerid!= i)
                    {
		            	if (PlayerToPlayer(10.0,playerid,i))
						{
						    SendClientMessage(i, Verde, string);
						}
				    }
				}
				return 1;
			}
		}
		return 1;
	}
    return 0;
    
}

Casas_OnPlayerText(playerid,text[])
{
    if(PlayerInfo[playerid][pMoviendoCasa] > 0)
	{
	    if(strcmp("Ok", text, true) == 0)
	    {
	        new Float:X, Float:Y, Float:Z;
	        GetPlayerPos(playerid, X,Y,Z);
            new h = GetHouseFromId(PlayerInfo[playerid][pMoviendoCasa]);
	        CasaInfo[h][hEx] = X;
	        CasaInfo[h][hEy] = Y;
	        CasaInfo[h][hEz] = Z;
			CasaInfo[h][hInterior2] = GetPlayerInterior(playerid);
			CasaInfo[h][hVw] = GetPlayerVirtualWorld(playerid);
			SaveCasa(h);
            DestroyDynamic3DTextLabel(CasaInfo[h][hPickup]);
            CasaInfo[h][hPickup] = CreateDynamic3DTextLabel("",Verde,CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz],5.0);
            UpdateHouseLabel(h);
			SendClientMessage(playerid, Gris, "Hecho");
			PlayerInfo[playerid][pMoviendoCasa] = 0;
			return 1;
		}
	}
    if(PlayerInfo[playerid][pEditingCasa] > 0)
	{
        new h = GetHouseFromId(PlayerInfo[playerid][pEditingCasa]);
		format(CasaInfo[h][hName], 128, "%s", text);
		format(string, sizeof(string), "* Has cambiado el nombre de la casa a: '%s'", text);
		SendClientMessage(playerid, Verde, string);
		UpdateHouseLabel(h);
		SaveCasa(h);
		PlayerInfo[playerid][pEditingCasa] = 0;
		return 1;
	}
    return 0;
}

IsACaravana(playerid)
{
	if(PlayerToPoint(20.0, playerid, 2513.2227,-1729.0717,778.6371)) return 1;
	return 0;
}