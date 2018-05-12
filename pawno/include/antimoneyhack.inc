/* -+-+-+-+-+-+ Anti - Money hack creado por Spell -+-+-+-+-+-+

Para agregarlo a su GameMode o Filterscript , colocar en OnPlayerSpawn:

SetTimerEx("Empiezachequear,2000,false,"d",playerid);

Y Luego, debajo de #include <a_samp> agregar #include <Anti_Money>. Quedaria asi:

#include <a_samp>
#include <Anti_Money>

*/

#include <a_samp>
#define SegCheck 1


new dinero[MAX_PLAYERS];

forward Empiezachequear(playerid);
forward CheckPlata(playerid);

public Empiezachequear(playerid){
dinero[playerid] = GetPlayerMoney(playerid);
SetTimerEx("CheckPlata", 1000,true,"d",playerid);
return 1;}


public CheckPlata(playerid){
if(GetPlayerMoney(playerid) > dinero[playerid]) { SetPlayerMoneyS(playerid,dinero[playerid]);}
else if(GetPlayerMoney(playerid) == dinero[playerid]) return 0;
dinero[playerid] = GetPlayerMoney(playerid);
return 1;}

stock DarDinero(playerid,cantidad){
GivePlayerMoney(playerid,cantidad);
dinero[playerid] = GetPlayerMoney(playerid);
return 1;}

SetPlayerMoneyS(playerid,cantidad){
ResetPlayerMoney(playerid);
GivePlayerMoney(playerid,cantidad);
return 1; }

/*

Opcional: Pueden agregar la callback JugadorChitea si quieren que kickee, banee o alguna otra función. Este callback es llamado cada vez que el jugador chitea dinero.

*/
