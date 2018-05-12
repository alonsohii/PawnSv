#include <a_samp>
#include <globalvars>
#include <paintball>

new ScriptMoney[MAX_PLAYERS];
new ScriptWeapons[MAX_PLAYERS][13];
new ScriptAmmo[MAX_PLAYERS][13];
new Alerta[MAX_PLAYERS];

forward AC_OnInit();
public AC_OnInit()
{
	//SetTimer("CheatsDetection", 1000, 1);
	return 1;
}

stock SetPlayerPosEx(playerid, Float:X, Float:Y, Float:Z)
{
	PlayerInfo[playerid][pPos_x] = X;
	PlayerInfo[playerid][pPos_y] = Y;
	PlayerInfo[playerid][pPos_z] = Z;
	SetPlayerPos(playerid, X,Y,Z);
	TogglePlayerControllable(playerid, 0);
	PlayerInfo[playerid][pTempFrozen] = 1;
	SetTimerEx("Descongelar", 2000, 0, "d", playerid);
	return 1;
}

forward CheatsDetection();
public CheatsDetection()
{
	//ArmourDetection
	for(new playerid; playerid < MAX_PLAYERS; playerid++)
	{
		if(!IsPlayerConnected(playerid)) continue;
		
		new Float:armor;
		GetPlayerArmour(playerid, armor);
		if(armor > 0 && (IsACop(playerid) == 0 && PlayerInfo[playerid][pAdmin] < 1))
		{
		    SetPlayerArmour(playerid, 0.0);
		    //format(string, 128, "* %s (ID:%d) ha usado trampas para ponerse Armadura.", pName(playerid), playerid);
		    //SendAdminMessage(COLOR_RED, string);
		}

 	   	if(GetPlayerMoney(playerid) > SafeGetPlayerMoney(playerid))
   		{
			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, SafeGetPlayerMoney(playerid));
			printf(" %s (ID:%d) ha usado trampas para spawnear dinero.",pName(playerid), playerid);
			//format(string, 128, "* %s (ID:%d) ha usado trampas para spawnear dinero.",pName(playerid), playerid);
  			//SendAdminMessage(COLOR_RED, string);
		}
        else
        {
            SaveValue(playerid, "Dinero", ScriptMoney[playerid]);
        }
	}
	
	//WeaponsDetection
	new w[MAX_PLAYERS],a[MAX_PLAYERS];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
	    if (IsPlayerConnected(i))
	    {
			if (GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK)
			{
				printf("%s (ID:%d) ha usado trampas para spawnear un JetPack. (Kickeado)",pName(i), i);
				format(string, 128, "* %s (ID:%d) ha usado trampas para spawnear un JetPack. (Kickeado)",pName(i), i);
  				ABroadCast(RojoIntenso, string, 1);
  				Kick(i);
				break;
			}
			w[i] = 0;
			a[i] = 0;
	        for(new s = 0; s < 13; s++)
	        {
         		GetPlayerWeaponData(i, s, w[i], a[i]);
           		if (ScriptWeapons[i][s] != w[i] && w[i] != 33 && w[i] != 41 && w[i] != 46 && EnActividad[i] == 0)
             	{
              		if (a[i] > ScriptAmmo[i][s])
           			{
              			//if ((a[i] - ScriptAmmo[i][GetWeaponSlot(w[i])]) >= 20)
              			//{
							if(UltimoEnMorir != i)
							{
								SafeResetPlayerWeaponsAC(i);
								printf("%s (ID:%d) ha usado trampas para spawnear Armas/Ammo.",pName(i), i);
								format(string, 128, "* %s (ID:%d) ha usado trampas para spawnear Armas/Ammo.",pName(i), i);
								ABroadCast(RojoIntenso, string, 1);
							}
							else
							{
								if(juega_paintball[i] == 0)
								{
									Alerta[i]++;
									SetTimerEx("Alertas", 10000, 0, "d", i);
								}
							}
                    	//}
                   	}
					return 1;
             	}
	        }
	    }
		ActualizarAmmo(i);
	}
	return 1;
}

forward Alertas(playerid);
public Alertas(playerid)
{
	Alerta[playerid] = 0;
}

forward SafeGivePlayerMoney(plyid, amounttogive);
public SafeGivePlayerMoney(plyid, amounttogive)
{
	if (amounttogive < 0)
	{
		ScriptMoney[plyid] = (ScriptMoney[plyid] + amounttogive);
		GivePlayerMoney(plyid, amounttogive);
	}
	else
	{
		ScriptMoney[plyid] = (ScriptMoney[plyid] + amounttogive);
		GivePlayerMoney(plyid, amounttogive);
	}
	
	return 1;
}

forward SafeGivePlayerMoneyEx(plyid, plyid2, amounttogive);
public SafeGivePlayerMoneyEx(plyid, plyid2, amounttogive)
{
	if (amounttogive < 0)
	{
		ScriptMoney[plyid] = (ScriptMoney[plyid] + amounttogive);
		GivePlayerMoney(plyid, amounttogive);
		ScriptMoney[plyid2] = (ScriptMoney[plyid2] - amounttogive);
		GivePlayerMoney(plyid2, -amounttogive);
	}
	else
	{
		ScriptMoney[plyid] = (ScriptMoney[plyid] + amounttogive);
		GivePlayerMoney(plyid, amounttogive);
		ScriptMoney[plyid2] = (ScriptMoney[plyid2] - amounttogive);
		GivePlayerMoney(plyid2, -amounttogive);
	}
	return 1;
}

AgregarArma(playerid, gun)
{
	new slot = GetWeaponSlot(gun);
	ScriptWeapons[playerid][slot] = gun;
	return 1;
}

AgregarAmmo(playerid, ammo, slot)
{
	ScriptAmmo[playerid][slot] = ammo;
	return 1;
}

ResetearVariablesArmas(playerid)
{
	for(new i; i < 13; i++)
	{
		ScriptWeapons[playerid][i] = 0;
		ScriptAmmo[playerid][i] = 0;
	}
}

ActualizarArmas(playerid)
{
	ResetPlayerWeapons(playerid);
	for(new slot; slot < 13; slot++)
	{
	    GivePlayerWeapon(playerid, ScriptWeapons[playerid][slot],ScriptAmmo[playerid][slot]);
	}
	return 1;
}

ActualizarArmasEx(playerid, exception)
{
	ResetPlayerWeapons(playerid);
	for(new slot; slot < 13; slot++)
	{
		if(slot == exception)
		{
			ScriptWeapons[playerid][slot] = 0;
			ScriptAmmo[playerid][slot] = 0;
			//EnActividad[playerid] = 0;
		}
		else
		{
			GivePlayerWeapon(playerid, ScriptWeapons[playerid][slot],ScriptAmmo[playerid][slot]);
			//EnActividad[playerid] = 0;
		}
	}
	return 1;
}

PlayerHaveWeapon(playerid, weaponid)
{
	new have = 0;
	for(new slot; slot < 13; slot++)
	{
		if(ScriptWeapons[playerid][slot] == weaponid)
		{
			have = 1;
			break;
		}
	}
	return have;
}

forward SafeResetPlayerMoney(plyid);
public SafeResetPlayerMoney(plyid)
{
   	ScriptMoney[plyid] = 0;
	ResetPlayerMoney(plyid);
	return 1;
}

forward SafeGivePlayerWeapon(plyid, weaponid, ammo);
public SafeGivePlayerWeapon(plyid, weaponid, ammo)
{
	EnActividad[plyid] = 1;
	new slot = GetWeaponSlot(weaponid);
	ScriptWeapons[plyid][slot] = weaponid;
	ScriptAmmo[plyid][slot] = ammo;
	GivePlayerWeapon(plyid, weaponid, ammo);
	SaveValues(plyid, "Armas");
	SaveValues(plyid, "Ammo");
	//EnActividad[plyid] = 0;	
	return 1;
}

forward SafeResetPlayerWeaponsAC(plyid);
public SafeResetPlayerWeaponsAC(plyid)
{
	
	for(new slot; slot < 13; slot++)
	{
	    ScriptWeapons[plyid][slot] = 0;
   	 	ScriptAmmo[plyid][slot] = 0;
	}
	ResetPlayerWeapons(plyid);
	SaveValues(plyid, "Armas");
	SaveValues(plyid, "Ammo");
	return 1;
}

forward SafeGetPlayerMoney(plyid);
public SafeGetPlayerMoney(plyid)
{
	return ScriptMoney[plyid];
}

forward GetWeaponSlot(weaponid);
public GetWeaponSlot(weaponid)
{
	new slot;
	switch(weaponid)
	{
		case 0, 1: slot = 0;
		case 2 .. 9: slot = 1;
		case 22 .. 24: slot = 2;
		case 25 .. 27: slot = 3;
		case 28, 29, 32: slot = 4;
		case 30, 31: slot = 5;
		case 33, 34: slot = 6;
		case 35 .. 38: slot = 7;
		case 16, 18, 39: slot = 8;
		case 42, 43: slot = 9;
		case 14: slot = 10;
		case 44 .. 46: slot = 11;
		case 40: slot = 12;
		default: slot = -1;
	}
	return slot;
}
ActualizarAmmo(playerid)
{
	new Weapon[13], Ammo[13];
	for(new i; i < 13; i++)
	{
		GetPlayerWeaponData(playerid, i, Weapon[i], Ammo[i]);
		ScriptAmmo[playerid][i] = Ammo[i];
	}
}
forward ResetEnActividad(playerid);
public ResetEnActividad(playerid)
{
	for(new i=0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
		if(EnActividad[i] == 1){EnActividad[i] = 0;}
	}
}

stock EstaEnGrua(vid)
{
	new resultado = 0;
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(vid == i) continue;
		if(GetVehicleTrailer(i) == vid)
		{
			resultado = 1;
			break;
		}
	}
	return resultado;
}