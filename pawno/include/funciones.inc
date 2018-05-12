#include <globalvars>
#include <a_mysql>
#include <colores>


stock PlayerToPlayer(Float:radi, playerid, playerid2)
{
    new Float:oldposx, Float:oldposy, Float:oldposz;
    GetPlayerPos(playerid2, oldposx, oldposy, oldposz);
    return PlayerToPoint(radi, playerid, oldposx, oldposy, oldposz);
}

stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

stock PointToPoint2D(Float:radi, Float:x, Float:y, Float:x2, Float:y2)
{
	new Float:distance;
    distance= floatsqroot( floatadd ( floatpower( floatsub ( x2 , x) , 2) , floatpower( floatsub ( y2 , y), 2) ) );
	
    if (distance < radi)
    {
        return 1;
    }
	return 0;
}
stock PointToPoint3D(Float:radi, Float:x, Float:y, Float:z, Float:x2, Float:y2, Float:z2)
{
    new Float:distance;
    distance= floatsqroot( floatadd ( floatadd ( floatpower( floatsub ( x2 , x) , 2) , floatpower( floatsub ( y2 , y), 2) ), floatpower( floatsub ( z2 , z), 2) ) );

    if (distance < radi)
    {
        return 1;
    }
	return 0;
}

stock strtokex(const stringe[], &index)
{
	new length = strlen(stringe);
	while ((index < length) && (stringe[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (stringe[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = stringe[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock ProxDetector(Float:radi, playerid, stringe[],col1,col2,col3,col4,col5)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		//radi = 2.0; //Trigger Radius
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
				    if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
				    {
						GetPlayerPos(i, posx, posy, posz);
						tempposx = (oldposx -posx);
						tempposy = (oldposy -posy);
						tempposz = (oldposz -posz);
						//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
						if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
						{
							SendClientMessage(i, col1, stringe);
						}
						else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
						{
							SendClientMessage(i, col2, stringe);
						}
						else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
						{
							SendClientMessage(i, col3, stringe);
						}
						else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
						{
							SendClientMessage(i, col4, stringe);
						}
						else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
						{
							SendClientMessage(i, col5, stringe);
						}
					}
				}
				else
				{
					SendClientMessage(i, col1, stringe);
				}
			}
	}//not connected
	return 1;
}

stock Float:GetDistanceBetweenPlayers(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2))
	{
		return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock Float:GetDistanceBetweenPoints(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1))
	{
		return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetVehiclePos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock split(const strsrc[], strdest[][], delimiter)
{
	new i, li;
	new aNum;
	new len;
	while(i <= strlen(strsrc)){
	    if(strsrc[i]==delimiter || i==strlen(strsrc)){
	        len = strmid(strdest[aNum], strsrc, li, i, 128);
	        strdest[aNum][len] = 0;
	        li = i+1;
	        aNum++;
		}
		i++;
	}
	return 1;
}

stock CheckPlayerDistanceToVehicle(Float:radi, playerid, vehicleid)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:PX,Float:PY,Float:PZ,Float:X,Float:Y,Float:Z;
		GetPlayerPos(playerid,PX,PY,PZ);
		GetVehiclePos(vehicleid, X,Y,Z);
		new Float:Distancia = (X-PX)*(X-PX)+(Y-PY)*(Y-PY)+(Z-PZ)*(Z-PZ);
		if(Distancia <= Float:radi*radi)
		{
			return 1;
		}
	}
	return 0;
}

stock Replace(stringo[24], find[128], replace[128])
{
	new pos;
	while((pos = strfind(stringo, find, true)) != -1)
	{
		strdel(stringo, pos, pos + strlen(find));
		strins(stringo, replace, pos);
	}
	return stringo;
}

stock VehicleToPoint(Float:radi, vehicleid, Float:x, Float:y, Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetVehiclePos(CarInfo[vehicleid][cId], oldposx, oldposy, oldposz);
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
	{
		return 1;
	}
	return 0;
}

stock enfrente(playerid, Float:tmpdist, &Float:tx, &Float:ty, &Float:tz, &Float:tang)
{
	GetPlayerPos(playerid,tx,ty,tz);
	GetPlayerFacingAngle(playerid, tang);
	tx=floatadd(tx,floatmul(floatsin(tang,degrees),-tmpdist));
	ty=floatadd(ty,floatmul(floatcos(tang,degrees),tmpdist));
//	printf("%f %f %f", floatsin(tmpang,degrees), floatcos(tmpang,degrees), tmpang);
	return 1;
}

stock ABroadCast(color,const stringe[],level)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if (PlayerInfo[i][pAdmin] >= level)
			{
				SendClientMessage(i, color, stringe);
			}
		}
	}
	printf("%s", stringe);
	return 1;
}

stock ABroadCastOnDuty(color,const stringe[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if (PlayerInfo[i][pAdminDuty] == 1)
			{
				SendClientMessage(i, color, stringe);
			}
		}
	}
	printf("%s", stringe);
	return 1;
}

stock ReturnUser(text[], playerid = INVALID_PLAYER_ID)
{
	new pos = 0;
	while (text[pos] < 0x21) // Strip out leading spaces
	{
		if (text[pos] == 0) return INVALID_PLAYER_ID; // No passed text
		pos++;
	}
	new userid = INVALID_PLAYER_ID;
	if (IsNumeric(text[pos])) // Check whole passed string
	{
		// If they have a numeric name you have a problem (although names are checked on id failure)
		userid = strval(text[pos]);
		if (userid >=0 && userid < MAX_PLAYERS)
		{
			if(!IsPlayerConnected(userid))
			{
				/*if (playerid != INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, 0xFF0000AA, "User not connected");
				}*/
				userid = INVALID_PLAYER_ID;
			}
			else
			{
				return userid; // A player was found
			}
		}
		/*else
		{
			if (playerid != INVALID_PLAYER_ID)
			{
				SendClientMessage(playerid, 0xFF0000AA, "Invalid user ID");
			}
			userid = INVALID_PLAYER_ID;
		}
		return userid;*/
		// Removed for fallthrough code
	}
	// They entered [part of] a name or the id search failed (check names just incase)
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME];
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i))
		{
			GetPlayerName(i, name, sizeof (name));
			if (strcmp(name, text[pos], true, len) == 0) // Check segment of name
			{
				if (len == strlen(name)) // Exact match
				{
					return i; // Return the exact player on an exact match
					// Otherwise if there are two players:
					// Me and MeYou any time you entered Me it would find both
					// And never be able to return just Me's id
				}
				else // Partial match
				{
					count++;
					userid = i;
				}
			}
		}
	}
	if (count != 1)
	{
		if (playerid != INVALID_PLAYER_ID)
		{
			if (count)
			{
		//		SendClientMessage(playerid, 0xFF0000AA, "Multiple users found, please narrow earch");
			}
			else
			{
		//		SendClientMessage(playerid, 0xFF0000AA, "No matching user found");
			}
		}
		userid = INVALID_PLAYER_ID;
	}
	return userid; // INVALID_USER_ID for bad return
}

stock IsNumeric(stringer[]) { for (new i = 0, j = strlen(stringer); i < j; i++) if (stringer[i] > '9' || stringer[i] < '0') return 0; return 1; }

stock MySQLConnect(sqlhost[], sqluser[], sqlpass[], sqldb[]) // by Luk0r
{
	print("MYSQL: Intentando conexión...");
	mysql_connect(sqlhost, sqluser, sqldb, sqlpass);
	if(mysql_ping()==1)
	{
		print("MYSQL: Conexión establecida.");
		return 1;
	}
	else
	{
		print("MYSQL: Error en la conexión, reintentando...");
		mysql_connect(sqlhost, sqluser, sqldb, sqlpass);
		if(mysql_ping()==1)
		{
			print("MYSQL: Reconexión exitosa. Se puede continuar normalmente.");
			return 1;
		}
		else
		{
			print("MYSQL: No se puede reconectar, cerrando servidor...");
			SendRconCommand("gmx");
			return 0;
		}
	}
}

forward Descongelar(playerid);
public Descongelar(playerid)
{
	TogglePlayerControllable(playerid, 1);
	PlayerInfo[playerid][pTempFrozen] = 0;
	return 1;
}

stock SaveCar(idx)
{
	new tmp[128];
	
	format(CarInfo[idx][cRadios], 40, "%d,%d,%d",
		CarInfo[idx][cEmisora],
		CarInfo[idx][cVolumen],
		CarInfo[idx][cEquipo]);
	format(tmp, 128, "UPDATE cars SET Radios='%s' WHERE `id` = %d", CarInfo[idx][cRadios], CarInfo[idx][cSQLID]);
	mysql_query(tmp);
	
	format(CarInfo[idx][cSlots], 128, "%d,%d,%d,%d,%d,%d,%d,%d",
		CarInfo[idx][cSlot][0],
		CarInfo[idx][cSlot][1],
		CarInfo[idx][cSlot][2],
		CarInfo[idx][cSlot][3],
		CarInfo[idx][cSlot][4],
		CarInfo[idx][cSlot][5],
		CarInfo[idx][cSlot][6],
		CarInfo[idx][cSlot][7]);
	format(tmp, 128, "UPDATE cars SET Slots='%s' WHERE `id` = %d", CarInfo[idx][cSlots], CarInfo[idx][cSQLID]);
    mysql_query(tmp);
    
	format(CarInfo[idx][cAmmos], 128, "%d,%d,%d,%d,%d,%d,%d,%d",
		CarInfo[idx][cAmmo][0],
		CarInfo[idx][cAmmo][1],
		CarInfo[idx][cAmmo][2],
		CarInfo[idx][cAmmo][3],
		CarInfo[idx][cAmmo][4],
		CarInfo[idx][cAmmo][5],
		CarInfo[idx][cAmmo][6],
		CarInfo[idx][cAmmo][7]);
	format(tmp, 128, "UPDATE cars SET Ammos='%s' WHERE `id` = %d", CarInfo[idx][cAmmos], CarInfo[idx][cSQLID]);
    mysql_query(tmp);
	
    format(CarInfo[idx][cDrogas], 128, "%d,%d,%d,%d,%d,%d,%d",
    CarInfo[idx][cSemillas][0],
    CarInfo[idx][cDrogaNP][0],
    CarInfo[idx][cDrogaP][0],
    CarInfo[idx][cSemillas][1],
    CarInfo[idx][cDrogaNP][1],
    CarInfo[idx][cDrogaP][1],
    CarInfo[idx][cDrogaP][2]);
	format(tmp, 128, "UPDATE cars SET Drogas='%s' WHERE `id` = %d", CarInfo[idx][cDrogas], CarInfo[idx][cSQLID]);
    mysql_query(tmp);
	
	GetVehicleDamageStatus(CarInfo[idx][cId], CarInfo[idx][cDano][0], CarInfo[idx][cDano][1], CarInfo[idx][cDano][2], CarInfo[idx][cDano][3]);
	GetVehicleHealth(CarInfo[idx][cId], CarInfo[idx][cDamage]);
	format(CarInfo[idx][cDanos], 40, "%d,%d,%d,%d,%f",
		CarInfo[idx][cDano][0],
		CarInfo[idx][cDano][1],
		CarInfo[idx][cDano][2],
		CarInfo[idx][cDano][3],
		CarInfo[idx][cDamage]);
	format(tmp, 128, "UPDATE cars SET Danos='%s' WHERE id = %d", CarInfo[idx][cDanos], CarInfo[idx][cSQLID]);
	mysql_query(tmp);

    format(CarInfo[idx][cComponentes], 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		CarInfo[idx][cComp][0],
		CarInfo[idx][cComp][1],
		CarInfo[idx][cComp][2],
		CarInfo[idx][cComp][3],
		CarInfo[idx][cComp][4],
		CarInfo[idx][cComp][5],
		CarInfo[idx][cComp][6],
		CarInfo[idx][cComp][7],
		CarInfo[idx][cComp][8],
		CarInfo[idx][cComp][9],
		CarInfo[idx][cComp][10],
		CarInfo[idx][cComp][11],
		CarInfo[idx][cComp][12],
		CarInfo[idx][cComp][13]
	);
    format(tmp, 512, "UPDATE cars SET Comp='%s' WHERE `id` = %d", CarInfo[idx][cComponentes], CarInfo[idx][cSQLID]);
    mysql_query(tmp);
	
    new sql[2048];
	format(sql, sizeof(sql), "UPDATE cars SET `Key`=%d,Model=%d,C1=%d,C2=%d,Owner='%s',Des='%s',Val=%d,Uso=%d,Own=%d,`Lock`=%d,Motor=%d,B=%d,Gas=%d,PJ=%d,Horas=%d,Park=%d,Sirena=%d WHERE `id`=%d",
        CarInfo[idx][cCarKey],
		CarInfo[idx][cModel],
		CarInfo[idx][cColorOne],
		CarInfo[idx][cColorTwo],
		CarInfo[idx][cOwner],
		CarInfo[idx][cDescription],
		CarInfo[idx][cValue],
		CarInfo[idx][cUsos],
		CarInfo[idx][cOwned],
		CarInfo[idx][cLock],
		CarInfo[idx][cStarted],
		CarInfo[idx][cBroken],
		CarInfo[idx][cGas],
		CarInfo[idx][cPaintJob], // PJ -
		CarInfo[idx][horas],
		CarInfo[idx][cParking],
		CarInfo[idx][cSirena],
		CarInfo[idx][cSQLID]
	);
	mysql_query(sql);
	
	if(CarInfo[idx][cUsos] == 0 && !(strcmp(CarInfo[idx][cOwner], "autoescuela", true) == 0))
	{
		format(sql, sizeof(sql), "UPDATE cars SET X=%f,Y=%f,Z=%f,A=%f,Kms=%f,Vw=%d,Interior=%d,Seguro=%d WHERE id = %d",
			CarInfo[idx][cLocationx],
			CarInfo[idx][cLocationy],
			CarInfo[idx][cLocationz],
			CarInfo[idx][cAngle],
			CarInfo[idx][cKms],
			CarInfo[idx][cVw],
			CarInfo[idx][cInt],
			CarInfo[idx][cSeguro],
			CarInfo[idx][cSQLID]);
		mysql_query(sql);
        //printf(sql);
	}
	return 1;
}

stock pName(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	Replace(name, "_", " ");
	return name;
}

stock pNameEx(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

stock IsPlayerInArea(playerid, Float:minx, Float:maxx, Float:miny, Float:maxy)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if (x > minx && x < maxx && y > miny && y < maxy) return 1;
    return 0;
}

stock IsPlayerInParking(playerid)
{
	for(new i; i < TotalParkings; i++)
	{
		if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
		{
			return 1;
		}
		else if(PlayerToPoint(20.0, playerid, 1499.4244384766, 183.61317443848, 1770.9107666016) && ParkInfo[i][paType] == 2)
		{
			return 1;
		}
	}
	return 0;
}

stock GetPlayerParking(playerid)
{
	new parking = -1;
	for(new i = 0; i < TotalParkings; i++)
	{
		if(PlayerToPoint(2.0, playerid, ParkInfo[i][paX], ParkInfo[i][paY], ParkInfo[i][paZ]))
		{
			parking = i;
			break;
		}
		else if(PlayerToPoint(20.0, playerid, 1499.4244384766, 183.61317443848, 1770.9107666016))
		{
			parking = GetPlayerVirtualWorld(playerid);
			break;
		}
	}
	return parking;
}

stock SendFamilyMessage(family, color, stringe[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pMember] == family)
		    {
				SendClientMessage(i, color, stringe);
			}
		}
	}
}

stock SendFamilyMessageOnDuty(family, color, stringe[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pMember] == family && PlayerInfo[i][pDuty] == 1)
		    {
				SendClientMessage(i, color, stringe);
			}
		}
	}
}

stock IsACop(playerid)
{
	if(PlayerInfo[playerid][pMember] == 1 || PlayerInfo[playerid][pMember] == 6)
	{
		return 1;
	}
	return 0;
}

stock IsAMedic(playerid)
{
	if(PlayerInfo[playerid][pMember] == 2)
	{
		return 1;
	}
	return 0;
}


stock GetPlayerHouse(playerid)
{
	for(new h = 0; h < sizeof(CasaInfo); h++)
	{
		if(PlayerInfo[playerid][pPhousekey] == CasaInfo[h][hId])
		{		
			return h;
		}
		else if(IsACop(playerid))
		{
			if( (PlayerToPoint(5.0, playerid, CasaInfo[h][hSx], CasaInfo[h][hSy], CasaInfo[h][hSz])) && GetPlayerVirtualWorld(playerid)==CasaInfo[h][hId])
			{
				return h;
			}
		}
	}
	return -1;
}

stock GetHouseFromId(id)
{
	for(new h = 0; h < sizeof(CasaInfo); h++)
	{
		if(id == CasaInfo[h][hId]) return h;
	}
	return -1;
}

stock GetXYInFrontOfPlayer(playerid, &Float:x2, &Float:y2, Float:distance)
{
	new Float:a;

	GetPlayerPos(playerid, x2, y2, a);
	GetPlayerFacingAngle(playerid, a);

	if(GetPlayerVehicleID(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}

	x2 += (distance * floatsin(-a, degrees));
	y2 += (distance * floatcos(-a, degrees));
}

stock GetPlayerVehicle(playerid)
{
	new car = GetPlayerVehicleID(playerid);
    if (car==0) return NOEXISTE;
	for (new i=0; i < TotalVeh; i++)
 		if (car == CarInfo[i][cId])
			return i;
	return NOEXISTE;
}

stock GetPlayerLevel(playerid)
{
	new Level;
	if(PlayerInfo[playerid][pRespeto] >= 850) Level=20;
	else if(PlayerInfo[playerid][pRespeto] >= 780) Level=19;
	else if(PlayerInfo[playerid][pRespeto] >= 720) Level=18;
	else if(PlayerInfo[playerid][pRespeto] >= 660) Level=17;
	else if(PlayerInfo[playerid][pRespeto] >= 600) Level=16;
	else if(PlayerInfo[playerid][pRespeto] >= 550) Level=15;
	else if(PlayerInfo[playerid][pRespeto] >= 500) Level=14;
	else if(PlayerInfo[playerid][pRespeto] >= 450) Level=13;
	else if(PlayerInfo[playerid][pRespeto] >= 400) Level=12;
	else if(PlayerInfo[playerid][pRespeto] >= 350) Level=11;
	else if(PlayerInfo[playerid][pRespeto] >= 300) Level=10;
	else if(PlayerInfo[playerid][pRespeto] >= 250) Level=9;
	else if(PlayerInfo[playerid][pRespeto] >= 200) Level=8;
	else if(PlayerInfo[playerid][pRespeto] >= 140) Level=7;
	else if(PlayerInfo[playerid][pRespeto] >= 100) Level=6;
	else if(PlayerInfo[playerid][pRespeto] >= 60) Level=5;
	else if(PlayerInfo[playerid][pRespeto] >= 40) Level=4;
	else if(PlayerInfo[playerid][pRespeto] >= 20) Level=3;
	else if(PlayerInfo[playerid][pRespeto] >= 10) Level=2;
	else if(PlayerInfo[playerid][pRespeto] >= 0) Level=1;
	return Level;
}

stock SetPlayerLevel(playerid,level)
{
	new RespetoMinimo;
	if(level == 0 || level == 1) RespetoMinimo = 0;
	else if(level == 2) RespetoMinimo = 10;
	else if(level == 3) RespetoMinimo = 20;
	else if(level == 4) RespetoMinimo = 40;
	else if(level == 5) RespetoMinimo = 60;
	else if(level == 6) RespetoMinimo = 100;
	else if(level == 7) RespetoMinimo = 140;
	else if(level == 8) RespetoMinimo = 200;
	else if(level == 9) RespetoMinimo = 250;
	else if(level == 10) RespetoMinimo = 300;
	else if(level == 11) RespetoMinimo = 350;
	else if(level == 12) RespetoMinimo = 400;
	else if(level == 13) RespetoMinimo = 450;
	else if(level == 14) RespetoMinimo = 500;
	else if(level == 15) RespetoMinimo = 550;
	else if(level == 16) RespetoMinimo = 600;
	else if(level == 17) RespetoMinimo = 660;
	else if(level == 18) RespetoMinimo = 720;
	else if(level == 19) RespetoMinimo = 780;
	else if(level >= 20) RespetoMinimo = 850;
	return PlayerInfo[playerid][pRespeto] = RespetoMinimo;
}

stock GetRespetoMinimo(level)
{
	new RespetoMinimo;
	if(level == 0 || level == 1) RespetoMinimo = 0;
	else if(level == 2) RespetoMinimo = 10;
	else if(level == 3) RespetoMinimo = 20;
	else if(level == 4) RespetoMinimo = 40;
	else if(level == 5) RespetoMinimo = 60;
	else if(level == 6) RespetoMinimo = 100;
	else if(level == 7) RespetoMinimo = 140;
	else if(level == 8) RespetoMinimo = 200;
	else if(level == 9) RespetoMinimo = 250;
	else if(level == 10) RespetoMinimo = 300;
	else if(level == 11) RespetoMinimo = 350;
	else if(level == 12) RespetoMinimo = 400;
	else if(level == 13) RespetoMinimo = 450;
	else if(level == 14) RespetoMinimo = 500;
	else if(level == 15) RespetoMinimo = 550;
	else if(level == 16) RespetoMinimo = 600;
	else if(level == 17) RespetoMinimo = 660;
	else if(level == 18) RespetoMinimo = 720;
	else if(level == 19) RespetoMinimo = 780;
	else if(level >= 20) RespetoMinimo = 850;
	return RespetoMinimo;
}

stock IsATeamCar(vid, team)
{
	if(CarInfo[vid][cUsos] == team)
	{	
		return 1;
	}
	
	return 0;
}

stock ClearChatbox(playerid, lines)
{
	if (IsPlayerConnected(playerid))
	{
		for(new i=0; i<lines; i++)
		{
			SendClientMessage(playerid, Gris, " ");
		}
	}
	return 1;
}

stock GetPlayerStats(targetid,returnid)
{
	new Sex[10];
	if(PlayerInfo[targetid][pSex] == 1) Sex = "Masculino"; else if(PlayerInfo[targetid][pSex] == 2) Sex = "Femenino";
	
	new Faccion[15];
	if(PlayerInfo[targetid][pMember] == 0) Faccion = "Ninguna";
	else if(PlayerInfo[targetid][pMember] == 1) Faccion = "LSPD";
	else if(PlayerInfo[targetid][pMember] == 2) Faccion = "LSMD";
	else if(PlayerInfo[targetid][pMember] == 3) Faccion = "LSTD";
	else if(PlayerInfo[targetid][pMember] == 4) Faccion = "LSNEWS";
	else if(PlayerInfo[targetid][pMember] == 5) Faccion = "Senado";
	else if(PlayerInfo[targetid][pMember] == 6) Faccion = "Sheriff";
	else if(PlayerInfo[targetid][pMember] == 91) Faccion = "RCA";
	else if(101 > PlayerInfo[targetid][pMember] > 4) format(Faccion,sizeof(Faccion),"%d",PlayerInfo[targetid][pMember]);
	
	new Rango[20];
	if(PlayerInfo[targetid][pRank] == 0 && PlayerInfo[targetid][pMember] == 0) Rango = "Ninguno";
	else if(PlayerInfo[targetid][pRank] == 0 && PlayerInfo[targetid][pMember] == 1) format(Rango,sizeof(Rango),"%d",PlayerInfo[targetid][pRank]);
	else if(PlayerInfo[targetid][pRank] == 1 && PlayerInfo[targetid][pMember] == 1) Rango = "Cadete";
	else if(PlayerInfo[targetid][pRank] == 2 && PlayerInfo[targetid][pMember] == 1) Rango = "Oficial";
	else if(PlayerInfo[targetid][pRank] == 3 && PlayerInfo[targetid][pMember] == 1) Rango = "Oficial superior";
	else if(PlayerInfo[targetid][pRank] == 4 && PlayerInfo[targetid][pMember] == 1) Rango = "Sargento";
	else if(PlayerInfo[targetid][pRank] == 5 && PlayerInfo[targetid][pMember] == 1) Rango = "Teniente";
	else if(PlayerInfo[targetid][pRank] == 6 && PlayerInfo[targetid][pMember] == 1) Rango = "Capitán";
	else if(PlayerInfo[targetid][pRank] == 1 && PlayerInfo[targetid][pMember] == 2) Rango = "Practicante";
	else if(PlayerInfo[targetid][pRank] == 2 && PlayerInfo[targetid][pMember] == 2) Rango = "Paramédico";
	else if(PlayerInfo[targetid][pRank] == 3 && PlayerInfo[targetid][pMember] == 2) Rango = "Auxiliar";
	else if(PlayerInfo[targetid][pRank] == 4 && PlayerInfo[targetid][pMember] == 2) Rango = "Enfermero";
	else if(PlayerInfo[targetid][pRank] == 5 && PlayerInfo[targetid][pMember] == 2) Rango = "Médico";
	else if(PlayerInfo[targetid][pRank] == 6 && PlayerInfo[targetid][pMember] == 2) Rango = "Director";
	else if(PlayerInfo[targetid][pRank] > 0 && PlayerInfo[targetid][pRank] < 6 && PlayerInfo[targetid][pMember] == 6) Rango = "Ayudante";
	else if(PlayerInfo[targetid][pRank] == 6 && PlayerInfo[targetid][pMember] == 6) Rango = "Sheriff";
	else if(PlayerInfo[targetid][pMember] > 2) format(Rango,sizeof(Rango),"%d",PlayerInfo[targetid][pRank]);
	
	new Trabajo[20];
	if(PlayerInfo[targetid][pJob] == 0) Trabajo = "Ninguno";
	else if(PlayerInfo[targetid][pJob] == 1) Trabajo = "Mecánico";
	else if(PlayerInfo[targetid][pJob] == 2) Trabajo = "Granjero";
	else if(PlayerInfo[targetid][pJob] == 3) Trabajo = "Pescador";
	else if(PlayerInfo[targetid][pJob] == 4) Trabajo = "Limpia Calles";
	else if(PlayerInfo[targetid][pJob] == 5) Trabajo = "Basurero";
	else if(PlayerInfo[targetid][pJob] == 6) Trabajo = "Pizzero";
	else if(PlayerInfo[targetid][pJob] == 7) Trabajo = "Transportista";
	else if(PlayerInfo[targetid][pJob] == 8) Trabajo = "Vendedor de Comida";
	else if(PlayerInfo[targetid][pJob] == 9) Trabajo = "Detective";
	else if(PlayerInfo[targetid][pJob] == 10) Trabajo = "Vendedor de Seguros";
	else if(PlayerInfo[targetid][pJob] == 11) Trabajo = "Ladrón";
	else if(PlayerInfo[targetid][pJob] > 11) format(Trabajo,sizeof(Trabajo),"%d",PlayerInfo[targetid][pJob]);
	
	new Licencias[35];
	if(PlayerInfo[targetid][pCarLic] == 0 && PlayerInfo[targetid][pFlyLic] == 0 && PlayerInfo[targetid][pBoatLic] == 0) Licencias = "Ninguna";
	else if(PlayerInfo[targetid][pCarLic] == 2 && PlayerInfo[targetid][pFlyLic] == 0 && PlayerInfo[targetid][pBoatLic] == 0) Licencias = "Ninguna";
	else if(PlayerInfo[targetid][pCarLic] == 1 && PlayerInfo[targetid][pFlyLic] == 0 && PlayerInfo[targetid][pBoatLic] == 0) Licencias = "Conducción";
	else if(PlayerInfo[targetid][pCarLic] == 1 && PlayerInfo[targetid][pFlyLic] == 1 && PlayerInfo[targetid][pBoatLic] == 0) Licencias = "Conducción/Aviación";
	else if(PlayerInfo[targetid][pCarLic] == 1 && PlayerInfo[targetid][pFlyLic] == 0 && PlayerInfo[targetid][pBoatLic] == 1) Licencias = "Conducción/Navegación";
	else if(PlayerInfo[targetid][pCarLic] == 0 && PlayerInfo[targetid][pFlyLic] == 1 && PlayerInfo[targetid][pBoatLic] == 0) Licencias = "Aviación";
	else if(PlayerInfo[targetid][pCarLic] == 2 && PlayerInfo[targetid][pFlyLic] == 1 && PlayerInfo[targetid][pBoatLic] == 0) Licencias = "Aviación";
	else if(PlayerInfo[targetid][pCarLic] == 0 && PlayerInfo[targetid][pFlyLic] == 1 && PlayerInfo[targetid][pBoatLic] == 1) Licencias = "Aviación/Navegación";
	else if(PlayerInfo[targetid][pCarLic] == 2 && PlayerInfo[targetid][pFlyLic] == 1 && PlayerInfo[targetid][pBoatLic] == 1) Licencias = "Aviación/Navegación";
	else if(PlayerInfo[targetid][pCarLic] == 0 && PlayerInfo[targetid][pFlyLic] == 0 && PlayerInfo[targetid][pBoatLic] == 1) Licencias = "Navegación";
	else if(PlayerInfo[targetid][pCarLic] == 2 && PlayerInfo[targetid][pFlyLic] == 0 && PlayerInfo[targetid][pBoatLic] == 1) Licencias = "Navegación";
	else if(PlayerInfo[targetid][pCarLic] == 1 && PlayerInfo[targetid][pFlyLic] == 1 && PlayerInfo[targetid][pBoatLic] == 1) Licencias = "Conducción/Aviación/Navegación";

	new Hambre[15];
	if(PlayerInfo[targetid][pHambre] == 0) Hambre = "Ninguno";
	else if(PlayerInfo[targetid][pHambre] == 1) Hambre = "Un Poco";
	else if(PlayerInfo[targetid][pHambre] == 2) Hambre = "Bastante";
	else if(PlayerInfo[targetid][pHambre] == 3) Hambre = "Muy Hambriento";
	else if(PlayerInfo[targetid][pHambre] > 0) format(Hambre,sizeof(Hambre),"%d",PlayerInfo[targetid][pHambre]);
	
	new Telefono[10],Telefono2[10];
	if(PlayerInfo[targetid][pPnumber][0] == 0) Telefono = "Ninguno"; else format(Telefono,sizeof(Telefono),"%d",PlayerInfo[targetid][pPnumber][0]);
	if(PlayerInfo[targetid][pPnumber][1] == 0) Telefono2 = "Ninguno"; else format(Telefono2,sizeof(Telefono2),"%d",PlayerInfo[targetid][pPnumber][1]);
	
	new RespetoNecesario, Respeto[40]; 
	if(GetPlayerLevel(targetid) != 20){	
	RespetoNecesario = (GetRespetoMinimo(GetPlayerLevel(targetid)+1)-PlayerInfo[targetid][pRespeto]);
	format(Respeto,sizeof(Respeto),"Necesitas %d más para subir de nivel.",RespetoNecesario);}
	else{ format(Respeto,sizeof(Respeto),"Has alcanzado el nivel máximo.");}
	
	new vehiculos[128], prestado[128];
	for(new i = 0; i < MAX_PROPIOS; i++)
	{
		if(PlayerInfo[targetid][pPCarKey][i] != NOEXISTE && i > 0)
		{
			format(string, 128, ", %d", PlayerInfo[targetid][pPCarKey][i]);
			strcat(vehiculos, string, 128);
		}
		else if(PlayerInfo[targetid][pPCarKey][i] != NOEXISTE && i == 0)
		{
			format(string, 128, "%d", PlayerInfo[targetid][pPCarKey][i]);
			strcat(vehiculos, string, 128);
		}
	}
	
	for(new i = 0; i < MAX_PRESTADOS; i++)
	{
		if(PlayerInfo[targetid][pPCochePrestado][i] != NOEXISTE && i > 0)
		{
			format(string, 128, ", %d", PlayerInfo[targetid][pPCochePrestado][i]);
			strcat(prestado, string, 128);
		}
		else if(PlayerInfo[targetid][pPCochePrestado][i] != NOEXISTE && i == 0)
		{
			format(string, 128, "%d", PlayerInfo[targetid][pPCochePrestado][i]);
			strcat(prestado, string, 128);
		}
	}
	new rPremium[40];
	new pPremium = GetPlayerPremium(targetid);
	if(pPremium == 0) rPremium = "Nada";if(pPremium == 1) rPremium = "Bronce";if(pPremium == 2) rPremium = "Plata";if(pPremium == 3) rPremium = "Oro";

	//-----------------------
	SendClientMessage(returnid, Amarillo, "|____________________________ Información de personaje: _______________________________|");
	format(string,sizeof(string),"Nombre: %s | Edad: %d | Facción: %s | Rango: %s | Sexo: %s | Tlfs.: %s, %s",pName(targetid), PlayerInfo[targetid][pAge], Faccion, Rango, Sex, Telefono, Telefono2);
	SendClientMessage(returnid, AmarilloClaro, string);
	format(string,sizeof(string),"Trabajo: %s | Cartera: %d$ | Saldo Bancario: %d$ | Licencias: %s | Hambre: %s", Trabajo, SafeGetPlayerMoney(targetid), PlayerInfo[targetid][pBank], Licencias, Hambre);
    SendClientMessage(returnid, AmarilloClaro, string);
    SendClientMessage(returnid, Amarillo, "|________________________________ Estadísiticas:  ____________________________________|");
	format(string,sizeof(string),"Premium: %s | Advertencias: %d | Nivel: %d | Respeto: %d - %s", rPremium, PlayerInfo[targetid][pAdvertencias], GetPlayerLevel(targetid), PlayerInfo[targetid][pRespeto], Respeto);
	SendClientMessage(returnid, AmarilloClaro, string);
	SendClientMessage(returnid, Amarillo, "|________________________________ Propiedades: ____________________________________|");
	format(string,sizeof(string),"Casa: %d | Negocio: %d | Vehículos: %s | Prestados: %s", 
	PlayerInfo[targetid][pPhousekey], PlayerInfo[targetid][pPbiskey], vehiculos, prestado);
	SendClientMessage(returnid, AmarilloClaro, string);
	//-----------------------
	if(PlayerInfo[returnid][pAdmin] > 0)
	{
		new dinerocasa, estadocasa[24];
		if(PlayerInfo[targetid][pPhousekey] == NOEXISTE)
		{
			dinerocasa = 0; format(estadocasa,sizeof(estadocasa),"No tiene"); 
		}
		else 
		{
			dinerocasa = CasaInfo[GetPlayerHouse(targetid)][hDinero];
			if(strcmp(pNameEx(targetid), CasaInfo[GetPlayerHouse(targetid)][hOwner], true) == 0)
			{
				format(estadocasa,sizeof(estadocasa),"Propietario");
			}
			else format(estadocasa,sizeof(estadocasa),"Inquilino");
		}
		SendClientMessage(returnid, Amarillo, "|____________________________ Información para Admins: _______________________________|");
		format(string,sizeof(string),"SQLID: %d | Admin Lvl: %d | Virtual World: %d | Interior: %d | Skin: %d,%d | Checkpoint: %d | ", PlayerInfo[targetid][pSQLID], PlayerInfo[targetid][pAdmin], GetPlayerVirtualWorld(targetid), GetPlayerInterior(targetid),
			PlayerInfo[targetid][pSkin], PlayerInfo[targetid][pUniforme], PlayerInfo[targetid][pCheckpoint]);
		SendClientMessage(returnid, AmarilloClaro, string);
		format(string,sizeof(string),"Trabajando: %d | Ganancias: %d | Tiempo Espera: %d | Jail: %d,%d | Dinero en casa: %d$ (%s)", PlayerInfo[targetid][pTrabajando] , PlayerInfo[targetid][pGanancias],(PlayerInfo[targetid][TiempoEsperaTrabajo]-gettime())/60,  PlayerInfo[targetid][pJailed],
			PlayerInfo[targetid][pJailTime], dinerocasa, estadocasa);
		SendClientMessage(returnid, AmarilloClaro, string);
	}
	return 1;
}

stock MostrarLlaves(playerid,returnid)
{
	if(playerid == returnid)
	{
		SendClientMessage(returnid,Azul, "______|- LLAVES -|______");
	}
	else
	{	
		format(string,sizeof(string),"______| Llaves de %s (%d) |______",pName(playerid),playerid);
		SendClientMessage(returnid,Azul,string);
	}	
	for(new i; i < MAX_PROPIOS; i++)
	{
		if(PlayerInfo[playerid][pPCarKey][i] != NOEXISTE)
		{
			new llave = PlayerInfo[playerid][pPCarKey][i];
			new arrayid = GetPlayerVehicleByKey(llave);
			format(string,sizeof(string),"Slot %d: %s (LS-%d) - Dueño: %s",i+1,CarInfo[arrayid][cDescription],llave,CarInfo[arrayid][cOwner]);
			SendClientMessage(returnid,Blanco,string);
		}
	}
	for(new i; i < MAX_PRESTADOS; i++)
	{
		if(PlayerInfo[playerid][pPCochePrestado][i] != NOEXISTE)
		{
			new llave = PlayerInfo[playerid][pPCochePrestado][i];
			new arrayid = GetPlayerVehicleByKey(llave);
			format(string,sizeof(string),"Slot %d: %s (LS-%d) - Dueño: %s",i+6,CarInfo[arrayid][cDescription],llave,CarInfo[arrayid][cOwner]);
			SendClientMessage(returnid,Blanco,string);
		}
	}
	return 1;
}
stock MostrarInventario(playerid,returnid)
{
	if(playerid == returnid)
	{
		SendClientMessage(returnid,Azul, "______|- INVENTARIO -|______");
	}
	else
	{	
		format(string,sizeof(string),"______| Inventario de %s (%d)",pName(playerid),playerid);
		SendClientMessage(returnid,Azul,string);
	}	
	if(PlayerInfo[playerid][pDrogaP][0] > 0 || PlayerInfo[playerid][pDrogaP][1] > 0 || PlayerInfo[playerid][pDrogaP][2] > 0)
	{
		format(string, 128, "Marihuana Preparada: %d | Cocaina Preparada: %d | Crack: %d", PlayerInfo[playerid][pDrogaP][0], PlayerInfo[playerid][pDrogaP][1], PlayerInfo[playerid][pDrogaP][2]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pDrogaNP][0] > 0 || PlayerInfo[playerid][pDrogaNP][1] > 0)
	{
		format(string, 128, "Marihuana sin preparar: %d | Coca sin preparar: %d", PlayerInfo[playerid][pDrogaNP][0], PlayerInfo[playerid][pDrogaNP][1]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pParafernalia][0] > 0 || PlayerInfo[playerid][pParafernalia][1] > 0)
	{
		format(string, 128, "Parafernalia de Cocaina: %d | Parafernalia de Crack: %d", PlayerInfo[playerid][pParafernalia][0], PlayerInfo[playerid][pParafernalia][1]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pSemillas][0] > 0 || PlayerInfo[playerid][pSemillas][1] > 0)
	{
		format(string, 128, "Semillas de Marihuana: %d | Semillas de Coca: %d", PlayerInfo[playerid][pSemillas][0], PlayerInfo[playerid][pSemillas][1]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pProductos] > 0)
	{
		format(string, 128, "Productos: %d", PlayerInfo[playerid][pProductos]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pEncendedor] > 0 || PlayerInfo[playerid][pCigarrillos] > 0)
	{
		format(string, 128, "Mechero: %d | Cigarrillos: %d", PlayerInfo[playerid][pEncendedor], PlayerInfo[playerid][pCigarrillos]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pDado] > 0 || PlayerInfo[playerid][pCartas] > 0 || PlayerInfo[playerid][pLoteria] > -1)
	{
		format(string, 128, "Dado: %d | Cartas: %d | Lotería: %d", PlayerInfo[playerid][pDado], PlayerInfo[playerid][pCartas], PlayerInfo[playerid][pLoteria]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pPalanca] > 0 || PlayerInfo[playerid][pGanzua] > 0 || PlayerInfo[playerid][pAlicates] > 0)
	{
		format(string, 128, "Palanca: %d | Ganzua: %d | Alicates: %d", PlayerInfo[playerid][pPalanca], PlayerInfo[playerid][pGanzua], PlayerInfo[playerid][pAlicates]);
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pGafas] > 0 || PlayerInfo[playerid][pCascos] > 0 || PlayerInfo[playerid][pBandana] > 0)
	{
		format(string, 128, "Gafas: ");
        if (PlayerInfo[playerid][pGafas] > 0)
            strcat(string, "Sí");
        else
            strcat(string, "No");
		strcat(string," | Casco: ");
		if (PlayerInfo[playerid][pCascos] > 0)
			strcat(string, "Sí");
        else
            strcat(string, "No");
		strcat(string," | Bandana: ");
		if (PlayerInfo[playerid][pBandana] > 0)
			strcat(string, "Sí");
        else
            strcat(string, "No");
		SendClientMessage(returnid, Blanco, string);
	}
	if(PlayerInfo[playerid][pJob] == 11 || PlayerInfo[playerid][pJob] == 2 || PlayerInfo[playerid][pJob] == 3)
	{
		if(PlayerInfo[playerid][pJob] == 11) format(string, 128, "Material robado: %d objetos.",PlayerInfo[playerid][pMaterialTrabajo]);
		if(PlayerInfo[playerid][pJob] == 3) format(string, 128, "Cubo con peces: %d gramos.",PlayerInfo[playerid][pMaterialTrabajo]);
		if(PlayerInfo[playerid][pJob] == 2) format(string, 128, "Saco de trigo: %d gramos.",PlayerInfo[playerid][pMaterialTrabajo]);
		SendClientMessage(returnid, Blanco, string);
	}
	return 1;
}
forward SetCameraPosAtStart(playerid);
public SetCameraPosAtStart(playerid)
{
    SetPlayerCameraPos(playerid, 1439.6588,-763.3558,118.2791);
    SetPlayerCameraLookAt(playerid, 1309.6588,-1283.3558,08.2791);
}


Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ, Float:ObjX, Float:ObjY, Float:ObjZ, Float:FrX, Float:FrY, Float:FrZ) {

	new Float:TGTDistance;

	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));

	new Float:tmpX, Float:tmpY, Float:tmpZ;

	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;

	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}

stock Float:GetPointAngleToPoint(Float:x2, Float:y2, Float:X, Float:Y) {

	new Float:DX, Float:DY;
	new Float:angle;
		
	DX = floatabs(floatsub(x2,X));
	DY = floatabs(floatsub(y2,Y));
	
	if (DY == 0.0 || DX == 0.0) {
		if(DY == 0 && DX > 0) angle = 0.0;
		else if(DY == 0 && DX < 0) angle = 180.0;
		else if(DY > 0 && DX == 0) angle = 90.0;
		else if(DY < 0 && DX == 0) angle = 270.0;
		else if(DY == 0 && DX == 0) angle = 0.0;
	}
	else {
		angle = atan(DX/DY);
	
		if(X > x2 && Y <= y2) angle += 90.0;
		else if(X <= x2 && Y < y2) angle = floatsub(90.0, angle);
		else if(X < x2 && Y >= y2) angle -= 90.0;
		else if(X >= x2 && Y > y2) angle = floatsub(270.0, angle);
	}			

	return floatadd(angle, 90.0);
}

stock GetXYInFrontOfPoint(&Float:x, &Float:y, Float:angle, Float:distance) {
	x += (distance * floatsin(-angle, degrees));
	y += (distance * floatcos(-angle, degrees));
}

stock IsPlayerAimingAt(playerid, Float:x, Float:y, Float:z, Float:radius) {
	new Float:camera_x,Float:camera_y,Float:camera_z,Float:vector_x,Float:vector_y,Float:vector_z;
	GetPlayerCameraPos(playerid, camera_x, camera_y, camera_z);
	GetPlayerCameraFrontVector(playerid, vector_x, vector_y, vector_z);

	new Float:vertical, Float:horizontal;

	switch (GetPlayerWeapon(playerid)) {
		case 34,35,36: {
			if (DistanceCameraTargetToLocation(camera_x, camera_y, camera_z, x, y, z, vector_x, vector_y, vector_z) < radius) return true;
			return false;
		}
		case 30,31: {vertical = 4.0; horizontal = -1.6;}
		case 33: {vertical = 2.7; horizontal = -1.0;}
		default: {vertical = 6.0; horizontal = -2.2;}
	}

	new Float:angle = GetPointAngleToPoint(0, 0, floatsqroot(vector_x*vector_x+vector_y*vector_y), vector_z) - 270.0;
	new Float:resize_x, Float:resize_y, Float:resize_z = floatsin(angle+vertical, degrees);
	GetXYInFrontOfPoint(resize_x, resize_y, GetPointAngleToPoint(0, 0, vector_x, vector_y)+horizontal, floatcos(angle+vertical, degrees));
	
	if (DistanceCameraTargetToLocation(camera_x, camera_y, camera_z, x, y, z, resize_x, resize_y, resize_z) < radius) return true;
	return false;
}

stock IsPlayerAimingAtPlayer(playerid, targetid) {
	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	if (IsPlayerAimingAt(playerid, x, y, z-0.75, 0.25)) return true;
	if (IsPlayerAimingAt(playerid, x, y, z-0.25, 0.25)) return true;
	if (IsPlayerAimingAt(playerid, x, y, z+0.25, 0.25)) return true;
	if (IsPlayerAimingAt(playerid, x, y, z+0.75, 0.25)) return true;
	if (IsPlayerAimingAt(playerid, x, y, z+1.00, 0.25)) return true;
	return false;
}

#define MAX_DISTANCE_UNIT   800.0   // maximum distance a player can shoot from
//**BODY PARTS**//
#define BODY_PART_HEAD  1
#define BODY_PART_TORSO 2
#define BODY_PART_LEGS  3

/*
											---[IsPlayerAimingBodyPart]---
			»playerid: the player
			»bodypart: the body part you want to check
			*Return: 1 if true, 0 if false
		*-------------------------------------------------------------------*
		| Checks if the player is aiming at any player's certain body part.	|
		*-------------------------------------------------------------------*
*/
#if defined SCRIPT_DEBUG
	new shootpick[100];
#endif

stock IsPlayerAimingBodyPart(playerid, bodypart)
{
    #if defined SCRIPT_DEBUG
		new c;
	#endif
	// Get the camera's positions
	new Float:x, Float:y, Float:z, Float:a;
	new Float:vx, Float:vy, Float:vz;
	new Float:cx, Float:cy, Float:cz;
	new Float:offset;
	new Float:radius;
	GetPlayerCameraFrontVector(playerid, vx, vy, vz);
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerFacingAngle(playerid, a);
	// Check if the player is aiming in a certain distance
	for(new Float:d; d < MAX_DISTANCE_UNIT; d += 0.5)
	{
		switch (GetPlayerWeapon(playerid))
		{
		    case 24, 29, 22, 23, 25, 26, 27, 28, 32: offset = 0.11;
		    case 30, 31: offset = 0.07;
		    case 33: offset = 0.045;
		    default: offset = 0.0;
		}
	    switch (GetPlayerWeapon(playerid))
	    {
	        case 22, 26, 28, 32:
	        {
			    // duals, where you don't need to change your angle to change aim direction --  Not very accurate, but considering they spray, it should be good
			    x = vx*d+cx;
			    y = vy*d+cy;
	        }
	        default:
	        {
	    		// this is for weapons where your angle moves when you change your aim(deagle, sdpistol, m4, etc)
	            x = cx + (d * floatsin(-a, degrees));
	    		y = cy + (d * floatcos(-a, degrees));
	        }
	    }

	    z = (vz+offset)*d+cz;
	    switch (bodypart)
	    {
	        case BODY_PART_HEAD: z -= 0.0, radius = 0.3;  // the offsets are made for head shots
	        case BODY_PART_TORSO: z += 0.6, radius = 0.5;
	        case BODY_PART_LEGS: z += 1.2, radius = 0.4;
	    }

		#if defined SCRIPT_DEBUG
	        if (IsValidObject(shootpick[c])) DestroyObject(shootpick[c]);
			shootpick[c] = CreateObject(1274, x, y, z, 0.0, 0.0, 0.0);
			c++;
		#endif
		
	    for(new i, m = GetMaxPlayers(); i < m; i++)
	    {
			if (!IsPlayerConnected(i)) continue;
			if (playerid == i) continue;
			if (GetPlayerSpecialAction(i) == SPECIAL_ACTION_DUCK)
			{
				if (IsPlayerInRangeOfPoint(i, radius+0.2, x, y, z+1.2-1.3-(bodypart==BODY_PART_TORSO?0.42:0.0)))
				{
					return i;
				}
			}
			else if (IsPlayerInRangeOfPoint(i, radius, x, y, z-0.8))
			{
				return i;
			}
		}
	}
	return INVALID_PLAYER_ID;
}

/*
											---[IsPlayerAimingTargetBodyPart]---
			»playerid: the player
			»targetid: the target
			»bodypart: the body part you want to check
			*Return: 1 if true, 0 if false
		*-------------------------------------------------------------------*
		| Checks if the player is aiming at target's specific body part.	|
		*-------------------------------------------------------------------*
*/
stock IsPlayerAimingTargetBodyPart(playerid, targetid, bodypart)
{
    #if defined SCRIPT_DEBUG
		new c;
	#endif
	// Get the camera's positions
	if(!IsPlayerLookingAtPlayer(playerid, targetid)) return 1;
	new Float:x, Float:y, Float:z, Float:a;
	new Float:vx, Float:vy, Float:vz;
	new Float:cx, Float:cy, Float:cz;
	new Float:offset;
	new Float:radius;
	GetPlayerCameraFrontVector(playerid, vx, vy, vz);
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerFacingAngle(playerid, a);
	// Check if the player is aiming in a certain distance
	for(new Float:d; d < MAX_DISTANCE_UNIT; d += 0.5)
	{
		switch (GetPlayerWeapon(playerid))
		{
		    case 24, 29, 22, 23, 25, 26, 27, 28, 32: offset = 0.11;
		    case 30, 31: offset = 0.07;
		    case 33, 34: offset = 0.0;
		}
	    switch (GetPlayerWeapon(playerid))
	    {
	        case 22, 26, 28, 32:
	        {
			    // duals, where you don't need to change your angle to change aim direction --  Not very accurate, but considering they spray, it should be good
			    x = vx*d+cx;
			    y = vy*d+cy;
	        }
	        default:
	        {
	    		// this is for weapons where your angle moves when you change your aim(deagle, sdpistol, m4, etc)
	            x = cx + (d * floatsin(-a, degrees));
	    		y = cy + (d * floatcos(-a, degrees));
	        }
	    }

	    z = (vz+offset)*d+cz;
	    switch (bodypart)
	    {
	        case BODY_PART_HEAD: z -= 0.0, radius = 0.3;  // the offsets are made for head shots
	        case BODY_PART_TORSO: z += 0.6, radius = 0.5;
	        case BODY_PART_LEGS: z += 1.2, radius = 0.4;
	    }

		#if defined SCRIPT_DEBUG
	        if (IsValidObject(shootpick[c])) DestroyObject(shootpick[c]);
			shootpick[c] = CreateObject(1274, x, y, z, 0.0, 0.0, 0.0);
			c++;
		#endif

		if (GetPlayerSpecialAction(targetid) == SPECIAL_ACTION_DUCK)
		{
			if (IsPlayerInRangeOfPoint(targetid, radius+0.2, x, y, z+1.2-1.3-(bodypart==BODY_PART_TORSO?0.42:0.0)))
			{
				return 1;
			}
		}
		else if (IsPlayerInRangeOfPoint(targetid, radius, x, y, z-0.8))
		{
			return 1;
		}
	}
	return 0;
}

stock IsPlayerLookingAtPlayer(player1, player2) { // Simon edited by Carlton
	if (!IsPlayerConnected(player1) || !IsPlayerConnected(player2)) return 0;
 	if(player1 == player2) return 0;
	new
		Float: distance,
		Float: vectorX,
		Float: vectorY,
		Float: vectorZ,
		Float: plyrPos[2][3],
		Float: projPos[3];
	GetPlayerCameraFrontVector(player1, vectorX, vectorY, vectorZ);
	GetPlayerCameraPos(player1, plyrPos[0][0], plyrPos[0][1], plyrPos[0][2]);
	GetPlayerPos(player2, plyrPos[1][0], plyrPos[1][1], plyrPos[1][2]);
	#define SQUARE(%1)  ((%1)*(%1))
	distance = floatsqroot(
	SQUARE(plyrPos[1][0]-plyrPos[0][0]) + SQUARE(plyrPos[1][1]-plyrPos[0][1]) + SQUARE(plyrPos[1][2]-plyrPos[0][2]));
	projPos[0] = plyrPos[0][0] + vectorX * distance;
	projPos[1] = plyrPos[0][1] + vectorY * distance;
	projPos[2] = plyrPos[0][2] + vectorZ * distance;
	return ((SQUARE(plyrPos[1][0]-projPos[0]) + SQUARE(plyrPos[1][1]-projPos[1]) + SQUARE(plyrPos[1][2]-projPos[2])) <= SQUARE(distance / 6));
	#undef SQUARE
}

GM_SetPlayerHealth(playerid, Float:Vida)
{
	SetPlayerHealth(playerid, Vida);
	new Float:Health;
	GetPlayerHealth(playerid, Health);
	if((floatcmp(Health,100.000) == 1) && (PlayerInfo[playerid][pAdminDuty] == 0))
	{
		SetPlayerHealth(playerid, 100);
	}
	
	if(floatcmp(Health,0.000) == 1)
	{
		format(string, 128, "UPDATE players SET Vida=%f WHERE id=%d", Health, PlayerInfo[playerid][pSQLID]);
		mysql_query(string);
	}
	return 1;
}



stock GetPlayer2DZone(playerid, zone[], len)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
 	for(new i = 0; i != sizeof(gSAZones); i++ )
 	{
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
		{
		    return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
		}
	}
	return 0;
}

stock IsNotValid2DZone(Float:x, Float:y)
{
	new zone[128];
 	for(new i = 0; i != sizeof(gSAZones); i++ )
 	{
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
		{
		    format(zone, 128, "%s", gSAZones[i][SAZONE_NAME]);
		}
	}
	
	if(strcmp(zone, "Willowfield", true) == 0 || strcmp(zone, "El Corona", true) == 0) 
	{
		return 1;
	}
	return 0;
}

GetClosestPlayer(p1)
{
	new x,Float:dis,Float:dis2,player;
	player = -1;
	dis = 99999.99;
	for (x=0;x<MAX_PLAYERS;x++)
	{
		if(IsPlayerConnected(x))
		{
			if(x != p1)
			{
				dis2 = GetDistanceBetweenPlayers(x,p1);
				if(dis2 < dis && dis2 != -1.00)
				{
					dis = dis2;
					player = x;
				}
			}
		}
	}
	return player;
}

forward ResetearTimerAnuncios();
public ResetearTimerAnuncios()
{
	return AnuncioTimer = 0;
}

stock PremiumValido(playerid, level)
{
	if(level == 0) return -1;
	new validez;
	if(PlayerInfo[playerid][pPremiumTipo] >= level)
	{
		if(gettime() < PlayerInfo[playerid][pPremiumTime])
		{
			validez = 1;
		}
		else
		{
			SaveValue(playerid, "Premium_Tipo", 0);
			SaveValue(playerid, "Premium_Timestamp", 0);
			validez = 0;
		}
	}
	return validez;
}

stock GetPlayerPremium(playerid)
{
	if(PremiumValido(playerid, 3))
	{
		return 3;
	}
	else if(PremiumValido(playerid, 2))
	{
		return 2;
	}
	else if(PremiumValido(playerid, 1))
	{
		return 1;
	}
	return 0;
}

stock VerPremium(targetid,returnid)
{
	new restante_segundos = PlayerInfo[targetid][pPremiumTime] - gettime();
	new restante_dias = ((restante_segundos /60) /60) /24;
    restante_segundos -= restante_dias*24*60*60;
	new restante_horas = (restante_segundos /60) /60;
    restante_segundos -= restante_horas*60*60;
	new restante_minutos = (restante_segundos /60);
	restante_segundos -= restante_minutos*60;
	if(GetPlayerPremium(targetid) == 0)
	{
		format(string, 128, "PREMIUM: El usuario %s no lo es.", pName(targetid)); 
	}
	else
	{
		format(string, 128, "PREMIUM: %s {FFFFFF} - {77c7ff}TIEMPO RESTANTE:{FFFFFF} %d días %d horas %d minutos %d segundos", Premium[GetPlayerPremium(targetid)], restante_dias, restante_horas, restante_minutos, restante_segundos); 
	}
	SendClientMessage(returnid, AzulClaro, string);
	return 1;
}