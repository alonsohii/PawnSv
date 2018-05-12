#include <a_samp>
#include <globalvars>
#include <funciones>
#include <streamer>

#define MAX_COPOBJS 200

enum cpInfo
{
	cpType,
	cpCreated,
    Float:cpX,
    Float:cpY,
    Float:cpZ,
    cpObject,
	cpDepartament,
};
new ObjectsInfo[MAX_COPOBJS][cpInfo];

Accesorios_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	new tmp[128];
	
	if (strcmp(cmd,"/poner",true) == 0)
	{
		if(!IsACop(playerid) && !IsAMedic(playerid)) { SendClientMessage(playerid, Rojo, "* No eres policia o médico!"); return 1; }
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /poner [objeto]");
			SendClientMessage(playerid, AzulClaro, "Objetos disponible: Clavos, Cono, Barrera, Valla");
			return 1;
		}
		
		if(strcmp(tmp, "Clavos", true) == 0)
		{
			new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
			GetPlayerPos(playerid, plocx, plocy, plocz);
			GetPlayerFacingAngle(playerid,ploca);
			CreateCopObject(1,plocx,plocy,plocz,ploca,PlayerInfo[playerid][pMember]);
	    }
		else if(strcmp(tmp, "Cono", true) == 0)
		{
			new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
			GetPlayerPos(playerid, plocx, plocy, plocz);
			GetPlayerFacingAngle(playerid,ploca);
			CreateCopObject(2,plocx,plocy,plocz-0.2,ploca,PlayerInfo[playerid][pMember]);
	    }
		else if(strcmp(tmp, "Barrera", true) == 0)
		{
			new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
			GetPlayerPos(playerid, plocx, plocy, plocz);
			GetPlayerFacingAngle(playerid,ploca);
			CreateCopObject(3,plocx,plocy,plocz,ploca,PlayerInfo[playerid][pMember]);
	    }
		else if(strcmp(tmp, "Valla", true) == 0)
		{
			new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
			GetPlayerPos(playerid, plocx, plocy, plocz);
			GetPlayerFacingAngle(playerid,ploca);
			CreateCopObject(4,plocx,plocy,plocz,ploca,PlayerInfo[playerid][pMember]);
	    }
		else
		{
			SendClientMessage(playerid, Blanco, "USO: /poner [objeto]");
			SendClientMessage(playerid, AzulClaro, "Objetos disponible: Clavos, Cono, Barrera, Valla");	
		}
		return 1;
	}
	if (strcmp(cmd,"/sacar",true) == 0)
	{
		if(!IsACop(playerid) && !IsAMedic(playerid)) return SendClientMessage(playerid, Rojo, "* No eres policia o médico!");
        DeleteClosestObject(playerid);
	    return 1;
	}
	if (strcmp(cmd,"/limpiar",true) == 0)
	{
		if(!IsACop(playerid) && !IsAMedic(playerid)) return SendClientMessage(playerid, Rojo, "* No eres policia o médico!");
        DeleteAllObjects(playerid);
	    return 1;
	}
	if (strcmp(cmd,"/equipo", true) == 0)
	{
		if (!IsACop(playerid) && !IsAMedic(playerid)) { SendClientMessage(playerid, Rojo, "* No eres médico ni policía!"); return 1; }
		else if(PlayerInfo[playerid][pMember] == 1 && !PlayerToPoint(8,playerid,267.1019,119.0340,1004.6172)) { SendClientMessage(playerid, Rojo, "* No estás en los vestuarios!"); return 1; }
		else if(IsAMedic(playerid) && !PlayerToPoint(8,playerid,-345.1156,166.4304,1035.1298)) { SendClientMessage(playerid, Rojo, "* No estás en los vestuarios!"); return 1; }
		else if(PlayerInfo[playerid][pMember] == 6 && !PlayerToPoint(8,playerid,255.3840,76.6392,1003.6406)) { SendClientMessage(playerid, Rojo, "* No estás en los vestuarios!"); return 1; }
        
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !IsNumeric(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /equipo [ID]");
			if(IsACop(playerid))
				SendClientMessage(playerid, Blanco, "1. Taser, 2. Desert Eagle, 3. Escopeta, 4. M4A1, 5. MP5, 6. Rifle, 7. Equipo especial, 8. SprayCan, 9. Porra");
			else
				SendClientMessage(playerid, Blanco, "1. Extintor");
			return 1;
		}
		
		new id,gun,ammo;
		id = strval(tmp);
		switch(id)
		{
			case 1:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 23, 50);
					gun = 23;
					ammo = 50;
				}
				else
				{
					SafeGivePlayerWeapon(playerid, 42, 500);
					gun = 0;
					ammo = 0;
				}
			}
			case 2:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 24, 50);
					gun = 24;
					ammo = 50;
				}
			}
			case 3:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 25, 40);
					gun = 25;
					ammo = 40;
				}
			}
			case 4:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 31, 300);	
					gun = 31;
					ammo = 300;
				}
			}
			case 5:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 29, 300);
					gun = 29;
					ammo = 300;
				}
			}
			case 6:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 34, 100);
					gun = 34;
					ammo = 100;
				}
			}
			case 7:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 16, 10);
					gun = 16;
					ammo = 10;
				}
			}
			case 8:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 41, 500);
					gun = 41;
					ammo = 500;
				}
			}
			case 9:
			{
				if(IsACop(playerid))
				{
					SafeGivePlayerWeapon(playerid, 3, 1);
					gun = 3;
					ammo = 1;
				}
			}
		}
		format(string, sizeof(string), "* Sacaste el equipaje especial de la taquilla.");
		SendClientMessage(playerid, Verde, string);
		GM_SetPlayerHealth(playerid, 100.0);
		SetPlayerArmour(playerid, 100.0);
		if( gun != 0 && ammo != 0)
		{
			new hour,minute,second,year,month,day,gunname[30];
			GetWeaponName(gun,gunname,sizeof(gunname));
			gettime(hour,minute,second);
			getdate(year, month, day);
			new query[128];
			format(query, sizeof(query), "INSERT INTO `logarmas` (`Emisor`, `Receptor`, `Desc`, `Fecha`) VALUES ('Taquilla', '%s', '/equipo | %s | %d','%d:%d:%d | %d-%d-%d')", pNameEx(playerid), gunname, ammo,hour,minute,second,day,month,year);
			mysql_query(query);
		}
		return 1;
	}
	
	return 0;
}

forward Accesorios_OnPlayerUpdate(playerid);
public Accesorios_OnPlayerUpdate(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        for(new i = 0; i < sizeof(ObjectsInfo); i++)
  	    {
  	        if(IsPlayerInRangeOfPoint(playerid, 3.0, ObjectsInfo[i][cpX], ObjectsInfo[i][cpY], ObjectsInfo[i][cpZ]))
            {
  	            if(ObjectsInfo[i][cpCreated] == 1 && ObjectsInfo[i][cpType] == 1)
  	            {
  	                new panels, doors, lights, tires;
  	                new carid = GetPlayerVehicleID(playerid);
		            GetVehicleDamageStatus(carid, panels, doors, lights, tires);
		            tires = encode_tires(1, 1, 1, 1);
		            UpdateVehicleDamageStatus(carid, panels, doors, lights, tires);
  	                return 0;
  	            }
  	        }
  	    }
  	}

	return 1;
}

stock CreateCopObject(tipo, Float:x,Float:y,Float:z,Float:Angle, departament)
{
	switch(tipo)
	{
		case 1:
		{
			for(new i = 0; i < sizeof(ObjectsInfo); i++)
			{
				if(ObjectsInfo[i][cpCreated] == 0)
				{
					ObjectsInfo[i][cpType]=tipo;
					ObjectsInfo[i][cpCreated]=1;
					ObjectsInfo[i][cpX]=x;
					ObjectsInfo[i][cpY]=y;
					ObjectsInfo[i][cpZ]=z-0.7;
					ObjectsInfo[i][cpObject] = CreateDynamicObject(2899, x, y, z-0.9, 0, 0, Angle-90);
					ObjectsInfo[i][cpDepartament]=departament;
					return 1;
				}
			}
		}
		case 2:
		{
			for(new i = 0; i < sizeof(ObjectsInfo); i++)
			{
				if(ObjectsInfo[i][cpCreated] == 0)
				{
					ObjectsInfo[i][cpType]=tipo;
					ObjectsInfo[i][cpCreated]=1;
					ObjectsInfo[i][cpX]=x;
					ObjectsInfo[i][cpY]=y;
					ObjectsInfo[i][cpZ]=z-0.5;
					ObjectsInfo[i][cpObject] = CreateDynamicObject(1238, x, y, z-0.5, 0, 0, Angle-90);
					ObjectsInfo[i][cpDepartament]=departament;
					return 1;
				}
			}
		}
		case 3:
		{
			for(new i = 0; i < sizeof(ObjectsInfo); i++)
			{
				if(ObjectsInfo[i][cpCreated] == 0)
				{
					ObjectsInfo[i][cpType]=tipo;
					ObjectsInfo[i][cpCreated]=1;
					ObjectsInfo[i][cpX]=x;
					ObjectsInfo[i][cpY]=y;
					ObjectsInfo[i][cpZ]=z-0.3;
					ObjectsInfo[i][cpObject] = CreateDynamicObject(1423, x, y, z-0.3, 0, 0, Angle);
					ObjectsInfo[i][cpDepartament]=departament;
					return 1;
				}
			}
		}
		case 4:
		{
			for(new i = 0; i < sizeof(ObjectsInfo); i++)
			{
				if(ObjectsInfo[i][cpCreated] == 0)
				{
					ObjectsInfo[i][cpType]=tipo;
					ObjectsInfo[i][cpCreated]=1;
					ObjectsInfo[i][cpX]=x;
					ObjectsInfo[i][cpY]=y;
					ObjectsInfo[i][cpZ]=z-0.5;
					ObjectsInfo[i][cpObject] = CreateDynamicObject(1422, x, y, z-0.5, 0, 0, Angle);
					ObjectsInfo[i][cpDepartament]=departament;
					return 1;
				}
			}
		}
	}
  	return 0;
}

stock DeleteAllObjects(playerid)
{
    for(new i = 0; i < sizeof(ObjectsInfo); i++)
  	{
  	    if(ObjectsInfo[i][cpCreated] == 1 && ObjectsInfo[i][cpDepartament] == PlayerInfo[playerid][pMember])
  	    {
			ObjectsInfo[i][cpType]=0;
  	        ObjectsInfo[i][cpCreated]=0;
            ObjectsInfo[i][cpX]=0.0;
            ObjectsInfo[i][cpY]=0.0;
            ObjectsInfo[i][cpZ]=0.0;
            DestroyDynamicObject(ObjectsInfo[i][cpObject]);
			ObjectsInfo[i][cpDepartament]=0;
  	    }
	}
    return 0;
}

stock DeleteClosestObject(playerid)
{
    for(new i = 0; i < sizeof(ObjectsInfo); i++)
  	{
  	    if(IsPlayerInRangeOfPoint(playerid, 2.0, ObjectsInfo[i][cpX], ObjectsInfo[i][cpY], ObjectsInfo[i][cpZ]) && ObjectsInfo[i][cpDepartament] == PlayerInfo[playerid][pMember])
        {
  	        if(ObjectsInfo[i][cpCreated] == 1)
            {
				ObjectsInfo[i][cpType]=0;
                ObjectsInfo[i][cpCreated]=0;
                ObjectsInfo[i][cpX]=0.0;
                ObjectsInfo[i][cpY]=0.0;
                ObjectsInfo[i][cpZ]=0.0;
                DestroyDynamicObject(ObjectsInfo[i][cpObject]);
				ObjectsInfo[i][cpDepartament]=0;
                return 1;
  	        }
  	    }
  	}
    return 0;
}

encode_tires(tires1, tires2, tires3, tires4)
{
	return tires1 | (tires2 << 1) | (tires3 << 2) | (tires4 << 3);
}

stock IsAtVestuarios(playerid)
{
	if(IsACop(playerid))
	{
		if(PlayerToPoint(8.0,playerid,267.1019,119.0340,1004.6172)) return 1;
	}
	if(IsAMedic(playerid))
	{
		if(PlayerToPoint(8.0,playerid,-345.1156,166.4304,1035.1298)) return 1;
	}
	return 0;
}
