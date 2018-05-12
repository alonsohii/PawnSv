#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>

//------------------------------------------------------------------------------------------------------

Guns_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_FIRE))
	{
		new weapon = GetPlayerWeapon(playerid);
		new target = NOEXISTE;
		switch(weapon)
		{
			case 23:
			{
				if(IsACop(playerid) || IsAMedic(playerid))
				{
					if(PlayerInfo[playerid][pFrozenTaser] == 1){ GameTextForPlayer(playerid, "~r~ESPERA - RECARGA", 2000, 3); return 1;}
					for(new i; i < MAX_PLAYERS; i++)
					{
						if(i == playerid) continue;
						
						if(!IsPlayerConnected(i)) continue;
						
						if(IsPlayerAimingAtPlayer(playerid, i))
						{
							target = i;
							break;
						}
					}
					
					if(target != NOEXISTE)
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 15)
						{
							TogglePlayerControllable(target, 0);
							ApplyAnimation(target,"CRACK","crckdeth1",4.1,0,1,1,1,1,1);
							GameTextForPlayer(target, "~r~Paralizado", 1000, 3);
							format(string, sizeof(string), "* Has sido paralizado por %s por 40 segundos.", pName(playerid));
							SendClientMessage(target, AzulClaro, string);
							format(string, sizeof(string), "* Has paralizado a %s por 40 segundos.", pName(target));
							SendClientMessage(playerid, AzulClaro, string);
							format(string, sizeof(string), "* %s dispara su Tazer a %s, y lo paraliza.", pName(playerid), pName(target));
							ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
							PlayerInfo[target][pTempFrozen] = 1;
							SetTimerEx("DescongelarTazer", 40000, 0, "i", target);
						}
					}
					PlayerInfo[playerid][pFrozenTaser] = 1;
					SetTimerEx("DelayTaser", 3000, 0, "i", playerid);
				}
				else
				{
					SafeResetPlayerWeaponsAC(playerid);
					SendClientMessage(playerid, Rojo, "* Detectada arma inválida.");
				}
				return 1;
			}
			case 8:
			{
				if(IsPlayerAimingBodyPart(playerid, 1) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 1);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 800)
						{
							GM_SetPlayerHealth(target, 0);
						}
					}
				}
				return 1;
			}
			case 34:
			{
				if(IsPlayerAimingBodyPart(playerid, 1) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 1);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 800)
						{
							GM_SetPlayerHealth(target, 0);
							GameTextForPlayer(playerid, "~r~HeadShot!", 3000, 5);
						}
					}
				}
				else if(IsPlayerAimingBodyPart(playerid, 2) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 2);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 800)
						{
							new Float:Vida, dano, Float:Armor;
							GetPlayerArmour(target, Armor);
							if(Armor > 0)
							{
								dano = random (5) + 5;
								SetPlayerArmour(target, Armor - dano);
							}
							else
							{
								GetPlayerHealth(target, Vida);
								dano = random (25) + 50;
								GM_SetPlayerHealth(target, Vida - dano);
							}
						}
					}
				}
				return 1;
			}
			case 22, 24:
			{
				if(IsPlayerAimingBodyPart(playerid, 1) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 1);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 30)
						{
							GM_SetPlayerHealth(target, 0);
							GameTextForPlayer(playerid, "~r~HeadShot!", 3000, 5);
						}
					}
				}
				else if(IsPlayerAimingBodyPart(playerid, 2) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 2);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 30)
						{
							new Float:Vida, dano, Float:Armor;
							GetPlayerArmour(target, Armor);
							if(Armor > 0)
							{
								dano = random (5) + 5;
								SetPlayerArmour(target, Armor - dano);
							}
							else
							{
								GetPlayerHealth(target, Vida);
								dano = random (15) + 10;
								GM_SetPlayerHealth(target, Vida - dano);
							}
						}
					}
				}
				return 1;
			}
			case 28, 29:
			{
				if(IsPlayerAimingBodyPart(playerid, 1) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 1);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 20)
						{
							GM_SetPlayerHealth(target, 0);
							GameTextForPlayer(playerid, "~r~HeadShot!", 3000, 5);
						}
					}
				}
				else if(IsPlayerAimingBodyPart(playerid, 2) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 2);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 30)
						{
							new Float:Vida, dano, Float:Armor;
							GetPlayerArmour(target, Armor);
							if(Armor > 0)
							{
								dano = random (5) + 5;
								SetPlayerArmour(target, Armor - dano);
							}
							else
							{
								GetPlayerHealth(target, Vida);
								dano = random (10) + 30;
								GM_SetPlayerHealth(target, Vida - dano);
							}
						}
					}
				}
				return 1;
			}
			case 31, 30:
			{
				if(IsPlayerAimingBodyPart(playerid, 1) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 1);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 50)
						{
							GM_SetPlayerHealth(target, 0);
							GameTextForPlayer(playerid, "~r~HeadShot!", 3000, 5);
						}
					}
				}
				else if(IsPlayerAimingBodyPart(playerid, 2) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 2);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 30)
						{
							new Float:Vida, dano, Float:Armor;
							GetPlayerArmour(target, Armor);
							if(Armor > 0)
							{
								dano = random (5) + 5;
								SetPlayerArmour(target, Armor - dano);
							}
							else
							{
								GetPlayerHealth(target, Vida);
								dano = random (5) + 15;
								GM_SetPlayerHealth(target, Vida - dano);
							}
						}
					}
				}
				return 1;
			}
			case 25, 26, 27:
			{
				if(IsPlayerAimingBodyPart(playerid, 1) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 1);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 15)
						{
							GM_SetPlayerHealth(target, 0);
							GameTextForPlayer(playerid, "~r~HeadShot!", 3000, 5);
						}
					}
				}
				else if(IsPlayerAimingBodyPart(playerid, 2) != INVALID_PLAYER_ID)
				{
					target = IsPlayerAimingBodyPart(playerid, 2);
					if(PlayerInfo[target][pHerido] == 0 && IsPlayerLookingAtPlayer(playerid, target))
					{
						if(GetDistanceBetweenPlayers(playerid, target) < 30)
						{
							new Float:Vida, dano, Float:Armor;
							GetPlayerArmour(target, Armor);
							if(Armor > 0)
							{
								dano = random (5) + 5;
								SetPlayerArmour(target, Armor - dano);
							}
							else
							{
								GetPlayerHealth(target, Vida);
								dano = random (10) + 30;
								GM_SetPlayerHealth(target, Vida - dano);
							}
						}
					}
				}
				return 1;				
			}
		}
	}
	return 0;
}

forward DescongelarTazer(playerid);
public DescongelarTazer(playerid)
{
	PlayerInfo[playerid][pTempFrozen] = 0;
	TogglePlayerControllable(playerid,1);
}

forward DelayTaser(playerid);
public DelayTaser(playerid)
{
	PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
	PlayerInfo[playerid][pFrozenTaser] = 0;
	format(string, sizeof(string), "* %s recarga su Tazer.", pName(playerid));
	ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
	format(string, sizeof(string), "[ID:%d] Tazer listo para ser utilizado.", playerid);
	ProxDetector(20.0, playerid, string, Verde, Verde, Verde, Verde, Verde);
}

AntiDesertEagleDriveBy(playerid,newstate)
{
	if(newstate==PLAYER_STATE_PASSENGER)
	{
		if(GetPlayerWeapon(playerid) == 24 )
		{
			SetPlayerArmedWeapon(playerid, 0);
		}
	}
}