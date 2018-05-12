#include <a_samp>
#include <funciones>
#define MAX_NIEVE 120


nieve_OnPlayerSpawn(playerid)
{
	if(nevando == 1)
	{
		SetPlayerAttachedObject( playerid, INDEX_NIEVE, 18863, 1, 36.512592, 3.075343, 6.010456, 359.854156, 351.700927, 7.929049, 1.000000, 1.000000, 1.000000 );
	}
    return 1;
}
nieve_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[256];
    new idx;
    cmd = strtokex(cmdtext, idx);
    if (strcmp(cmd,"/nieve",true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 2 && nevando == 0)
		{
			for(new i=0; i < MAX_NIEVE; i++)
			{
				RemovePlayerAttachedObject(i,INDEX_NIEVE);
				SetPlayerAttachedObject( i, INDEX_NIEVE, 18863, 1, 36.512592, 3.075343, 6.010456, 359.854156, 351.700927, 7.929049, 1.000000, 1.000000, 1.000000 );
			}
			SetWeather(9);
		}
		nevando = 1;
		return 1;
	}
    if (strcmp(cmd,"/qnieve",true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] >= 2 && nevando == 1)
		{
			for(new i = 0; i <MAX_PLAYERS; i++)
			{
				RemovePlayerAttachedObject(i,INDEX_NIEVE);
			}
			SetWeather(1);
			nevando = 0;
			return 1;
		}
	}
	if(strcmp(cmd,"/quitarnieve",true)==0)
	{
			RemovePlayerAttachedObject(playerid,INDEX_NIEVE);
	}
	return 0;
}