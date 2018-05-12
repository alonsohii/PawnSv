#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

new cursor[MAX_PLAYERS];
new Seleccionando[MAX_PLAYERS];

enum uInfo
{
	uSkin,
	uId,
	uType,
}
#define UNIFORMES 30
new UniformInfo[UNIFORMES][uInfo] = {
	{71, 1, 0},
	{265, 1, 0},
	{266, 1, 0},
	{267, 1, 0},
	{280, 1, 0},
	{281, 1, 0},
	{284, 1, 0},
	{285, 1, 0},
	{286, 1, 0},
	{295, 1, 0},
	{274, 2, 0},
	{275, 2, 0},
	{276, 2, 0},
	{277, 2, 0},
	{278, 2, 0},
	{279, 2, 0},
	{172, 2, 0},
	{282, 6, 0},
	{283, 6, 0},
	{288, 6, 0},
	{50, 11, 0},
	{50, 1, 1},
	{161, 2, 1},
	{198, 2, 1},
	{34, 2, 1},
	{16, 4, 1},
	{16, 5, 1},
	{155, 6, 1},
	{201, 7, 1},
	{202, 7, 1}
};

forward Uniformes_OnPlayerCommandText(playerid, cmdtext[]);
public Uniformes_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/uniforme", true) == 0)
	{
		if(PlayerInfo[playerid][pMember] != 1 && PlayerInfo[playerid][pMember] != 2 && PlayerInfo[playerid][pMember] != 6 && PlayerInfo[playerid][pJob] != 1 && PlayerInfo[playerid][pJob] != 2 && PlayerInfo[playerid][pJob] != 4 && PlayerInfo[playerid][pJob] != 5 && PlayerInfo[playerid][pJob] != 6 && PlayerInfo[playerid][pJob] != 7) 
		{
			return 1;
		}
		if(PlayerInfo[playerid][pDuty] == 1) { SendClientMessage(playerid, Rojo, "* No tienes que estar de servicio para usar este comando."); return 1; }
		if(Seleccionando[playerid] == 1) { Uniformes_OnPlayerCommandText(playerid, "/quitaruni"); return 1; }
		UniformSelect(playerid, 0);
		Seleccionando[playerid] = 1;
		TogglePlayerControllable(playerid, 0);
		SendClientMessage(playerid, Amarillo, "Utiliza SHIFT y ALT para cambiar el uniforme.");
		SendClientMessage(playerid, Amarillo, "Pulsa ENTER para seleccionar un uniforme y /uniforme para cancelar la acción.");
		return 1;
	}
	
	if(strcmp(cmd, "/quitaruni", true) == 0)
	{
		if(Seleccionando[playerid] == 0) return 1;
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		Seleccionando[playerid] = 0;
		TogglePlayerControllable(playerid, 1);
		return 1;
	}
	
	if(strcmp(cmd, "/incognito", true) == 0)
	{
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_ENTER_VEHICLE || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_EXIT_VEHICLE) return 1;
		if(IsPlayerInAnyVehicle(playerid)) return 1;
		if(PlayerInfo[playerid][pMember] != 1) 
		{
			return 1;
		}
		
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 90, 0,0,0,0,0,0);
		SendClientMessage(playerid, Verde, "* Estas de incognito. Usa /deservicio luego.");
		return 1;
	}
	
	if(strcmp(cmd, "/deservicio", true) == 0)
	{
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_ENTER_VEHICLE || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_EXIT_VEHICLE) return 1;
		if(IsPlayerInAnyVehicle(playerid)) return 1;
		if(PlayerInfo[playerid][pMember] != 1 && PlayerInfo[playerid][pMember] != 2 && PlayerInfo[playerid][pMember] != 6 && PlayerInfo[playerid][pJob] != 1 && PlayerInfo[playerid][pJob] != 2 && PlayerInfo[playerid][pJob] != 4 && PlayerInfo[playerid][pJob] != 5 && PlayerInfo[playerid][pJob] != 6 && PlayerInfo[playerid][pJob] != 7) 
		{
			return 1;
		}
		if(PlayerInfo[playerid][pJob] == 2 || PlayerInfo[playerid][pJob] == 4 || PlayerInfo[playerid][pJob] == 5 || PlayerInfo[playerid][pJob] == 6 || PlayerInfo[playerid][pJob] == 7)
		{
			if(PlayerInfo[playerid][pTrabajando] == 1)
				{ SendClientMessage(playerid, Naranja, "* No puedes quitarte de servicio mientras estes trabajando."); return 1; }
		}
		if(PlayerInfo[playerid][pUniforme] == 0 || PlayerInfo[playerid][pUniforme] == 1)
		{
			SendClientMessage(playerid, Naranja, "* Escribe /uniforme primero!");
			return 1;
		}
		if(PlayerInfo[playerid][pDuty] == 0)
		{
			PlayerInfo[playerid][pDuty] = 1;
			SaveValue(playerid, "EnServicio", PlayerInfo[playerid][pDuty]);
			SetPlayerSkin(playerid, PlayerInfo[playerid][pUniforme]);
			SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pUniforme], PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 90, 0,0,0,0,0,0);
			SendClientMessage(playerid, Verde, "* Te has puesto de servicio.");
			return 1;
		}
		else
		{
			PlayerInfo[playerid][pDuty] = 0;
			SaveValue(playerid, "EnServicio", PlayerInfo[playerid][pDuty]);
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 90, 0,0,0,0,0,0);
			SendClientMessage(playerid, Verde, "* Has dejado de estar de servicio.");
			return 1;
		}
	}
	
	return 0;
}

forward UniformSelect(playerid, operacion);
public UniformSelect(playerid, operacion)
{
	if(operacion == 0)
	{
		for(new i; i < UNIFORMES; i++)
		{
			if((UniformInfo[i][uType] == 0 && PlayerInfo[playerid][pMember] == UniformInfo[i][uId]) || 
				(UniformInfo[i][uType] == 1 && PlayerInfo[playerid][pJob] == UniformInfo[i][uId]))
			{
				cursor[playerid] = i;
				SetPlayerSkin(playerid, UniformInfo[i][uSkin]);
				break;
			}
		}
	}
	else if(operacion == 1)
	{
		if(cursor[playerid] < UNIFORMES)
		{
			cursor[playerid] ++;
		}
		
		new i = cursor[playerid];
		if((UniformInfo[i][uType] == 0 && PlayerInfo[playerid][pMember] == UniformInfo[i][uId]) || 
		(UniformInfo[i][uType] == 1 && PlayerInfo[playerid][pJob] == UniformInfo[i][uId]))
		{
			SetPlayerSkin(playerid, UniformInfo[i][uSkin]);
		}
		else
		{
			cursor[playerid] --;
		}
	}
	else if(operacion == 2)
	{
		if(cursor[playerid] > 0)
		{
			cursor[playerid] --;
		}
		
		new i = cursor[playerid];
		if((UniformInfo[i][uType] == 0 && PlayerInfo[playerid][pMember] == UniformInfo[i][uId]) || 
		(UniformInfo[i][uType] == 1 && PlayerInfo[playerid][pJob] == UniformInfo[i][uId]))
		{
			SetPlayerSkin(playerid, UniformInfo[i][uSkin]);
		}
		else
		{
			cursor[playerid] ++;
		}
	}
	return 1;
}

forward Uniform_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public Uniform_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(Seleccionando[playerid] == 1)
	{
		if (((newkeys & KEY_JUMP) == KEY_JUMP)  && ((oldkeys & KEY_JUMP) != KEY_JUMP))
		{
			UniformSelect(playerid, 1);
			return 1;
		}
		else if (((newkeys & KEY_WALK) == KEY_WALK)  && ((oldkeys & KEY_WALK) != KEY_WALK))
		{
			UniformSelect(playerid, 2);
			return 1;
		}
		else if (((newkeys & KEY_SECONDARY_ATTACK) == KEY_SECONDARY_ATTACK) && ((oldkeys & KEY_SECONDARY_ATTACK) != KEY_SECONDARY_ATTACK))
		{
			SendClientMessage(playerid, Amarillo, "* Uniforme de trabajo seleccionado correctamente. Usa /deservicio para ponertelo.");
			PlayerInfo[playerid][pUniforme] = GetPlayerSkin(playerid);
			SaveValue(playerid, "Uniforme", PlayerInfo[playerid][pUniforme]);
			Uniformes_OnPlayerCommandText(playerid, "/quitaruni");
			return 1;
		}
	}
	return 0;
}
