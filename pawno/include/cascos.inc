#include <a_samp>
#include <globalvars>

Cascos_OnPlayerCommandText(playerid, cmdtext[])
{
	if(strcmp(cmdtext, "/casco", true) == 0)
	{
		if(PlayerInfo[playerid][pCascos] == 0) {  SendClientMessage(playerid, Rojo, "* No tienes cascos para moto!"); return 1; }
		new casco;
		switch(PlayerInfo[playerid][pCascos])
		{
			case 1: {casco = 18645;}
			case 2: {casco = 18976;}
			case 3: {casco = 18977;}
			case 4: {casco = 18978;}
			case 5: {casco = 18979;}
		}
		switch(GetPlayerSkin(playerid))
		{
			#define SPAO{%0,%1,%2,%3,%4,%5}	SetPlayerAttachedObject(playerid, CASCO_SLOT, casco, 2, (%0), (%1), (%2), (%3), (%4), (%5));
			case 0, 65, 74, 149, 208, 273:  SPAO{0.070000, 0.000000, 0.000000, 88.000000, 75.000000, 0.000000}
			case 1..6, 8, 14, 16, 22, 27, 29, 33, 41..49, 82..84, 86, 87, 119, 289: SPAO{0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000}
			case 7, 10: SPAO{0.090000, 0.019999, 0.000000, 88.000000, 90.000000, 0.000000}
			case 9: SPAO{0.059999, 0.019999, 0.000000, 88.000000, 90.000000, 0.000000}
			case 11..13: SPAO{0.070000, 0.019999, 0.000000, 88.000000, 90.000000, 0.000000}
			case 15: SPAO{0.059999, 0.000000, 0.000000, 88.000000, 82.000000, 0.000000}
			case 17..21: SPAO{0.059999, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 23..26, 28, 30..32, 34..39, 57, 58, 98, 99, 104..118, 120..131: SPAO{0.079999, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 40: SPAO{0.050000, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 50, 100..103, 148, 150..189, 222: SPAO{0.070000, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 51..54: SPAO{0.100000, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 55, 56, 63, 64, 66..73, 75, 76, 78..81, 133..143, 147, 190..207, 209..219, 221, 247..272, 274..288, 290..293: SPAO{0.070000, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 59..62: SPAO{0.079999, 0.029999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 77: SPAO{0.059999, 0.019999, 0.000000, 87.000000, 82.000000, 0.000000}
			case 85, 88, 89: SPAO{0.070000, 0.039999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 90..97: SPAO{0.050000, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 132: SPAO{0.000000, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 144..146: SPAO{0.090000, 0.000000, 0.000000, 88.000000, 82.000000, 0.000000}
			case 220: SPAO{0.029999, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 223, 246: SPAO{0.070000, 0.050000, 0.000000, 88.000000, 82.000000, 0.000000}
			case 224..245: SPAO{0.070000, 0.029999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 294: SPAO{0.070000, 0.019999, 0.000000, 91.000000, 84.000000, 0.000000}
			case 295: SPAO{0.050000, 0.019998, 0.000000, 86.000000, 82.000000, 0.000000}
			case 296..298: SPAO{0.064999, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
			case 299: SPAO{0.064998, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		}
		format(string,sizeof(string),"* %s se pone un casco",pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		SendClientMessage(playerid, Blanco, "* Usa /qcasco para sacartelo.");
		return 1;
	}
	
	if(strcmp(cmdtext, "/quitarcasco", true) == 0 || strcmp(cmdtext, "/qcasco", true) == 0)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid,CASCO_SLOT))
		{
			format(string,sizeof(string),"* %s se quita el casco",pName(playerid));
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			RemovePlayerAttachedObject(playerid,CASCO_SLOT);
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* No te has puesto el casco!");
		}
		return 1;
	}
	return 0;
}
