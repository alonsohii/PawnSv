#include <a_samp>
#include <G_Zonas>

main()
{
	print("\n----------------------------------");
	print(" Blank Gamemode by your name here");
	print("----------------------------------\n");
}

new TestZona;

public OnGameModeInit()
{
	OnGZonasInit();
	SetGameModeText("G_Zonas GM Test");
	AddPlayerClass(0, -2035.1187,185.3362,28.8359, 269.1425, 0, 0, 0, 0, 0, 0);
	TestZona = CrearZona("G_Zonas",-2139.745,-1992.963,132.5009,231.1251,-1,-1);
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/borrarzona", cmdtext, true, 10) == 0)
	{
		BorrarZona(TestZona);
		return 1;
	}
	return 0;
}
public OnPlayerEnterZona(playerid,ZonaID)
{
	if(ZonaID == TestZona) GameTextForPlayer(playerid,"~b~~h~~h~G_Zonas",5000,3);
	return 1;
}