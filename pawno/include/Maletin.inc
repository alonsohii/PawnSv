// Creado por GROVE4L
// www.pawnoscripting.com

#include <a_samp>

#if defined _Maletin_included
  #endinput
#endif
#define _Maletin_included
#pragma library Maletin

/*
native CrearMaletinTodos();
native BorrarMaletinTodos();
native CrearMaletinEx(playerid);
native BorrarMaletinEx(playerid);
native TieneMaletin(playerid);
*/

#define SetPlayerHoldingObject(%1,%2,%3,%4,%5,%6,%7,%8,%9) SetPlayerAttachedObject(%1,MAX_PLAYER_ATTACHED_OBJECTS-1,%2,%3,%4,%5,%6,%7,%8,%9)
#define StopPlayerHoldingObject(%1) RemovePlayerAttachedObject(%1,MAX_PLAYER_ATTACHED_OBJECTS-1)
#define IsPlayerHoldingObject(%1) IsPlayerAttachedObjectSlotUsed(%1,MAX_PLAYER_ATTACHED_OBJECTS-1)

new ConM[MAX_PLAYERS];

stock CrearMaletinTodos()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        CrearMaletinEx(i);
	}
	return 1;
}

stock BorrarMaletinTodos()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        BorrarMaletinEx(i);
	}
	return 1;
}

stock BorrarMaletinEx(playerid)
{
    ConM[playerid] = 0;
	StopPlayerHoldingObject(playerid);
	return 1;
}

stock CrearMaletinEx(playerid)
{
    ConM[playerid] = 1;
    SetPlayerHoldingObject(playerid, 1210, 6, 0.289999, 0.079999, -0.000000, 0.000000, -100.000000, 1.000000);
	return 1;
}

stock TieneMaletin(playerid)
{
	return ConM[playerid];
}

// Creado por GROVE4L
