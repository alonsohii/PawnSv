/*
	Release:
	    	» Automatic Transmission Info Filterscript

	Functions:
			» IsVehicleDrivingBackwards(vehicleid);

	Credits:
	        » Credits go to Joker for IsVehicleDrivingBackwards(vehicleid) function
*/

#include <a_samp>
#include <globalvars>

/*#define ForEach(%0,%1) \
	for(new %0; %0 != %1; %0++) if(IsPlayerConnected(%0) && !IsPlayerNPC(%0))*/ //Paul: Innecesario

/*#define Loop(%0,%1) \
	for(new %0; %0 != %1; %0++)*/  // Paul: esta causando demasiados problemas, lo deshecho.


// Colores del velocimetro	
#define VC1 0xFFFFF5FF // BLANCO
	
#define VC2 0xF5F4C0FF // AMARILLO - CLARO
	
#define VC3	0xF8F20EFF // AMARILLO
	
#define VC4 0xF4A44CFF // NARANJA - CLARO
	
#define VC5 0xEC6537FF // NARANJA - OSCURO

#define VC6 0xE52C25FF // ROJO
	
new
	Text: GearInfo[MAX_PLAYERS],
	Text: Speedo[MAX_PLAYERS],
	Text: Fuel[MAX_PLAYERS],
	Text: General[5],
	Text: Gear[6],
	bool: ShiftInfo[MAX_PLAYERS] = true,
	ShiftTimer[MAX_PLAYERS];


Velocimetro_OnGameModeInit()
{
	General[0] = TextDrawCreate(554.000000, 414.000000, "_");
	TextDrawBackgroundColor(General[0], 255);
	TextDrawFont(General[0], 1);
	TextDrawLetterSize(General[0], 0.500000, 2.599999);
	TextDrawColor(General[0], -1);
	TextDrawSetOutline(General[0], 0);
	TextDrawSetProportional(General[0], 1);
	TextDrawSetShadow(General[0], 1);
	TextDrawUseBox(General[0], 1);
	TextDrawBoxColor(General[0], 70);
	TextDrawTextSize(General[0], 628.000000, 0.000000);

	General[1] = TextDrawCreate(554.000000, 440.000000, "_");
	TextDrawBackgroundColor(General[1], 255);
	TextDrawFont(General[1], 1);
	TextDrawLetterSize(General[1], 0.500000, -0.300000);
	TextDrawColor(General[1], -1);
	TextDrawSetOutline(General[1], 0);
	TextDrawSetProportional(General[1], 1);
	TextDrawSetShadow(General[1], 1);
	TextDrawUseBox(General[1], 1);
	TextDrawBoxColor(General[1], 120);
	TextDrawTextSize(General[1], 628.000000, 0.000000);

	General[2] = TextDrawCreate(554.000000, 414.000000, "_");
	TextDrawBackgroundColor(General[2], 255);
	TextDrawFont(General[2], 1);
	TextDrawLetterSize(General[2], 0.500000, -0.300000);
	TextDrawColor(General[2], -1);
	TextDrawSetOutline(General[2], 0);
	TextDrawSetProportional(General[2], 1);
	TextDrawSetShadow(General[2], 1);
	TextDrawUseBox(General[2], 1);
	TextDrawBoxColor(General[2], 120);
	TextDrawTextSize(General[2], 628.000000, 0.000000);

	General[3] = TextDrawCreate(631.000000, 414.000000, "_");
	TextDrawBackgroundColor(General[3], 255);
	TextDrawFont(General[3], 1);
	TextDrawLetterSize(General[3], 0.500000, 2.599999);
	TextDrawColor(General[3], -1);
	TextDrawSetOutline(General[3], 0);
	TextDrawSetProportional(General[3], 1);
	TextDrawSetShadow(General[3], 1);
	TextDrawUseBox(General[3], 1);
	TextDrawBoxColor(General[3], 120);
	TextDrawTextSize(General[3], 629.000000, 0.000000);

	General[4] = TextDrawCreate(554.000000, 414.000000, "_");
	TextDrawBackgroundColor(General[4], 255);
	TextDrawFont(General[4], 1);
	TextDrawLetterSize(General[4], 0.500000, 2.599999);
	TextDrawColor(General[4], -1);
	TextDrawSetOutline(General[4], 0);
	TextDrawSetProportional(General[4], 1);
	TextDrawSetShadow(General[4], 1);
	TextDrawUseBox(General[4], 1);
	TextDrawBoxColor(General[4], 120);
	TextDrawTextSize(General[4], 550.000000, 0.000000);

	Gear[0] = TextDrawCreate(558.000000, 430.000000, "_");
	TextDrawBackgroundColor(Gear[0], 255);
	TextDrawFont(Gear[0], 1);
	TextDrawLetterSize(Gear[0], 0.500000, 0.399999);
	TextDrawColor(Gear[0], -1);
	TextDrawSetOutline(Gear[0], 0);
	TextDrawSetProportional(Gear[0], 1);
	TextDrawSetShadow(Gear[0], 1);
	TextDrawUseBox(Gear[0], 1);
	TextDrawBoxColor(Gear[0], VC1);
	TextDrawTextSize(Gear[0], 553.000000, 0.000000);

	Gear[1] = TextDrawCreate(562.000000, 427.399993, "_");
	TextDrawBackgroundColor(Gear[1], 255);
	TextDrawFont(Gear[1], 1);
	TextDrawLetterSize(Gear[1], 0.549999, 0.699999);
	TextDrawColor(Gear[1], -1);
	TextDrawSetOutline(Gear[1], 0);
	TextDrawSetProportional(Gear[1], 1);
	TextDrawSetShadow(Gear[1], 1);
	TextDrawUseBox(Gear[1], 1);
	TextDrawBoxColor(Gear[1], VC2);
	TextDrawTextSize(Gear[1], 557.000000, 0.000000);

	Gear[2] = TextDrawCreate(566.000000, 424.600006, "_");
	TextDrawBackgroundColor(Gear[2], 255);
	TextDrawFont(Gear[2], 1);
	TextDrawLetterSize(Gear[2], 0.549999, 1.000000);
	TextDrawColor(Gear[2], -1);
	TextDrawSetOutline(Gear[2], 0);
	TextDrawSetProportional(Gear[2], 1);
	TextDrawSetShadow(Gear[2], 1);
	TextDrawUseBox(Gear[2], 1);
	TextDrawBoxColor(Gear[2], VC3);
	TextDrawTextSize(Gear[2], 561.000000, 0.000000);

	Gear[3] = TextDrawCreate(570.000000, 422.000000, "_");
	TextDrawBackgroundColor(Gear[3], 255);
	TextDrawFont(Gear[3], 1);
	TextDrawLetterSize(Gear[3], 0.549999, 1.300000);
	TextDrawColor(Gear[3], -1);
	TextDrawSetOutline(Gear[3], 0);
	TextDrawSetProportional(Gear[3], 1);
	TextDrawSetShadow(Gear[3], 1);
	TextDrawUseBox(Gear[3], 1);
	TextDrawBoxColor(Gear[3], VC4);
	TextDrawTextSize(Gear[3], 565.000000, 0.000000);

	Gear[4] = TextDrawCreate(574.000000, 419.299987, "_");
	TextDrawBackgroundColor(Gear[4], 255);
	TextDrawFont(Gear[4], 1);
	TextDrawLetterSize(Gear[4], 0.549999, 1.600000);
	TextDrawColor(Gear[4], -1);
	TextDrawSetOutline(Gear[4], 0);
	TextDrawSetProportional(Gear[4], 1);
	TextDrawSetShadow(Gear[4], 1);
	TextDrawUseBox(Gear[4], 1);
	TextDrawBoxColor(Gear[4], VC5);
	TextDrawTextSize(Gear[4], 569.000000, 0.000000);

	Gear[5] = TextDrawCreate(578.000000, 417.299987, "_");
	TextDrawBackgroundColor(Gear[5], 255);
	TextDrawFont(Gear[5], 1);
	TextDrawLetterSize(Gear[5], 0.549999, 1.800000);
	TextDrawColor(Gear[5], -1);
	TextDrawSetOutline(Gear[5], 0);
	TextDrawSetProportional(Gear[5], 1);
	TextDrawSetShadow(Gear[5], 1);
	TextDrawUseBox(Gear[5], 1);
	TextDrawBoxColor(Gear[5], VC6);
	TextDrawTextSize(Gear[5], 573.000000, 0.000000);
	return 1;
}


Velocimetro_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd,"/velocimetro", true) == 0)
	{
	    ShiftInfo[playerid] = (ShiftInfo[playerid] == true) ? (false) : (true);
	    return 1;
	}
	return 0;
}
Velocimetro_OnPlayerConnect(playerid)
{
	GearInfo[playerid] = TextDrawCreate(588.000000, 425.000000, "~w~R ~g~~h~N ~w~D"); // 596, 425
	TextDrawBackgroundColor(GearInfo[playerid], 255);
	TextDrawFont(GearInfo[playerid], 1);
	TextDrawLetterSize(GearInfo[playerid], 0.320000, 1.299999);
	TextDrawColor(GearInfo[playerid], -1);
	TextDrawSetOutline(GearInfo[playerid], 0);
	TextDrawSetProportional(GearInfo[playerid], 1);
	TextDrawSetShadow(GearInfo[playerid], 1);
	
	Speedo[playerid] = TextDrawCreate(588.000000, 413.000000, "255 ~w~km/h"); //579,414
	TextDrawBackgroundColor(Speedo[playerid], 0x000000FF);
	TextDrawFont(Speedo[playerid], 1);
	TextDrawLetterSize(Speedo[playerid], 0.170000, 0.799999);
	TextDrawColor(Speedo[playerid], 0xA803D0FF);
	TextDrawSetOutline(Speedo[playerid], 0);
	TextDrawSetProportional(Speedo[playerid], 1);
	TextDrawSetShadow(Speedo[playerid], 1);
	
	Fuel[playerid] = TextDrawCreate(588.000000, 419.000000, "100% ~w~Fuel"); //579,414
	TextDrawBackgroundColor(Fuel[playerid], 0x000000FF);
	TextDrawFont(Fuel[playerid], 1);
	TextDrawLetterSize(Fuel[playerid], 0.170000, 0.799999);
	TextDrawColor(Fuel[playerid], 0xA803D0FF);
	TextDrawSetOutline(Fuel[playerid], 0);
	TextDrawSetProportional(Fuel[playerid], 1);
	TextDrawSetShadow(Fuel[playerid], 1);
	
    //ShiftInfo[playerid] = (ShiftInfo[playerid] == false) ? (true) : (true);
    ShiftTimer[playerid] = SetTimerEx("ShiftFunction", 200, true, "e", playerid);
	return 1;
}

Velocimetro_OnPlayerDisconnect(playerid)
{
	TextDrawDestroy(GearInfo[playerid]);
	TextDrawDestroy(Speedo[playerid]);
	HideGeneral(playerid);
    TextDrawHideForPlayer(playerid, Gear[0]);
	TextDrawHideForPlayer(playerid, Gear[1]);
	TextDrawHideForPlayer(playerid, Gear[2]);
	TextDrawHideForPlayer(playerid, Gear[3]);
	TextDrawHideForPlayer(playerid, Gear[4]);
	TextDrawHideForPlayer(playerid, Gear[5]);
	
    ShiftInfo[playerid] = (ShiftInfo[playerid] == false) ? (true) : (true);
    KillTimer(ShiftTimer[playerid]);
	return 1;
}

forward ShiftFunction(playerid);
public ShiftFunction(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsABike(GetPlayerVehicle(playerid)))
	{
		new
			Float: vPos[3],
			Float: Speed
		;
		if(ShiftInfo[playerid] == true)
		{
			ShowGeneral(playerid);
			new porciento[5] = "~w~%";
			format(string, sizeof(string), "%d%s ~w~Fuel", CarInfo[GetPlayerVehicle(playerid)][cGas], porciento), TextDrawSetString(Fuel[playerid], string), TextDrawShowForPlayer(playerid, Fuel[playerid]);
			if(!IsVehicleDrivingBackwards(GetPlayerVehicleID(playerid)))
			{
				GetVehicleVelocity(GetPlayerVehicleID(playerid), vPos[0], vPos[1], vPos[2]);
				Speed = floatdiv(floatpower(floatmul(floatsqroot(floatadd(floatpower(vPos[0], 2), floatadd(floatpower(vPos[1], 2), floatpower(vPos[2], 2)))), 200), 1.5 ),15);
				format(string, sizeof(string), "%0.0f ~w~km/h", Speed), TextDrawSetString(Speedo[playerid], string), TextDrawShowForPlayer(playerid, Speedo[playerid]);
				if(Speed < 1)
				{
					TextDrawHideForPlayer(playerid, Gear[0]);
					TextDrawHideForPlayer(playerid, Gear[1]);
					TextDrawHideForPlayer(playerid, Gear[2]);
					TextDrawHideForPlayer(playerid, Gear[3]);
					TextDrawHideForPlayer(playerid, Gear[4]);
					TextDrawHideForPlayer(playerid, Gear[5]);
					TextDrawSetString(GearInfo[playerid], "~w~R ~g~~h~N ~w~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
				}
				else if(Speed > 160)
				{
					TextDrawSetString(GearInfo[playerid], "~w~R N ~g~~h~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
					TextDrawShowForPlayer(playerid, Gear[0]);
					TextDrawShowForPlayer(playerid, Gear[1]);
					TextDrawShowForPlayer(playerid, Gear[2]);
					TextDrawShowForPlayer(playerid, Gear[3]);
					TextDrawShowForPlayer(playerid, Gear[4]);
					TextDrawShowForPlayer(playerid, Gear[5]);
				}
				else if(Speed > 120)
				{
					TextDrawSetString(GearInfo[playerid], "~w~R N ~g~~h~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
					TextDrawHideForPlayer(playerid, Gear[0]);
					TextDrawHideForPlayer(playerid, Gear[1]);
					TextDrawHideForPlayer(playerid, Gear[2]);
					TextDrawHideForPlayer(playerid, Gear[3]);
					TextDrawHideForPlayer(playerid, Gear[4]);
					TextDrawHideForPlayer(playerid, Gear[5]);
					TextDrawShowForPlayer(playerid, Gear[0]);
					TextDrawShowForPlayer(playerid, Gear[1]);
					TextDrawShowForPlayer(playerid, Gear[2]);
					TextDrawShowForPlayer(playerid, Gear[3]);
					TextDrawShowForPlayer(playerid, Gear[4]);
				}
				else if(Speed > 90)
				{
					TextDrawSetString(GearInfo[playerid], "~w~R N ~g~~h~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
					TextDrawHideForPlayer(playerid, Gear[0]);
					TextDrawHideForPlayer(playerid, Gear[1]);
					TextDrawHideForPlayer(playerid, Gear[2]);
					TextDrawHideForPlayer(playerid, Gear[3]);
					TextDrawHideForPlayer(playerid, Gear[4]);
					TextDrawHideForPlayer(playerid, Gear[5]);
					TextDrawShowForPlayer(playerid, Gear[0]);
					TextDrawShowForPlayer(playerid, Gear[1]);
					TextDrawShowForPlayer(playerid, Gear[2]);
					TextDrawShowForPlayer(playerid, Gear[3]);
				}
				else if(Speed > 60)
				{
					TextDrawSetString(GearInfo[playerid], "~w~R N ~g~~h~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
					TextDrawHideForPlayer(playerid, Gear[0]);
					TextDrawHideForPlayer(playerid, Gear[1]);
					TextDrawHideForPlayer(playerid, Gear[2]);
					TextDrawHideForPlayer(playerid, Gear[3]);
					TextDrawHideForPlayer(playerid, Gear[4]);
					TextDrawHideForPlayer(playerid, Gear[5]);
					TextDrawShowForPlayer(playerid, Gear[0]);
					TextDrawShowForPlayer(playerid, Gear[1]);
					TextDrawShowForPlayer(playerid, Gear[2]);
				}
				else if(Speed > 30)
				{
					TextDrawSetString(GearInfo[playerid], "~w~R N ~g~~h~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
					TextDrawHideForPlayer(playerid, Gear[0]);
					TextDrawHideForPlayer(playerid, Gear[1]);
					TextDrawHideForPlayer(playerid, Gear[2]);
					TextDrawHideForPlayer(playerid, Gear[3]);
					TextDrawHideForPlayer(playerid, Gear[4]);
					TextDrawHideForPlayer(playerid, Gear[5]);
					TextDrawShowForPlayer(playerid, Gear[0]);
					TextDrawShowForPlayer(playerid, Gear[1]);
				}
				else if(Speed > 1)
				{
					TextDrawSetString(GearInfo[playerid], "~w~R N ~g~~h~D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
					TextDrawHideForPlayer(playerid, Gear[0]);
					TextDrawHideForPlayer(playerid, Gear[1]);
					TextDrawHideForPlayer(playerid, Gear[2]);
					TextDrawHideForPlayer(playerid, Gear[3]);
					TextDrawHideForPlayer(playerid, Gear[4]);
					TextDrawHideForPlayer(playerid, Gear[5]);
					TextDrawShowForPlayer(playerid, Gear[0]);
				}
				if(CarInfo[GetPlayerVehicle(playerid)][cUsos] == 0) CarInfo[GetPlayerVehicle(playerid)][cKms] = floatadd(CarInfo[GetPlayerVehicle(playerid)][cKms],floatdiv(Speed,18000));
				return 1;
			}
			else if(IsVehicleDrivingBackwards(GetPlayerVehicleID(playerid)))
			{
				TextDrawHideForPlayer(playerid, Gear[0]);
				TextDrawHideForPlayer(playerid, Gear[1]);
				TextDrawHideForPlayer(playerid, Gear[2]);
				TextDrawHideForPlayer(playerid, Gear[3]);
				TextDrawHideForPlayer(playerid, Gear[4]);
				TextDrawHideForPlayer(playerid, Gear[5]);
				TextDrawShowForPlayer(playerid, Gear[0]);
				TextDrawSetString(GearInfo[playerid], "~g~~h~R ~w~N D"), TextDrawShowForPlayer(playerid, GearInfo[playerid]);
				TextDrawSetString(Speedo[playerid], "- ~w~km/h"), TextDrawShowForPlayer(playerid, Speedo[playerid]);
				return 1;
			}
		}
		else
		{
			if(CarInfo[GetPlayerVehicle(playerid)][cUsos] == 0 && !IsVehicleDrivingBackwards(GetPlayerVehicleID(playerid)))
			{
				GetVehicleVelocity(GetPlayerVehicleID(playerid), vPos[0], vPos[1], vPos[2]);
				Speed = floatdiv(floatpower(floatmul(floatsqroot(floatadd(floatpower(vPos[0], 2), floatadd(floatpower(vPos[1], 2), floatpower(vPos[2], 2)))), 200), 1.5 ),15);
				CarInfo[GetPlayerVehicle(playerid)][cKms] = floatadd(CarInfo[GetPlayerVehicle(playerid)][cKms],floatdiv(Speed,18000));
			}
			HideGeneral(playerid);
			TextDrawHideForPlayer(playerid, Speedo[playerid]);
			TextDrawHideForPlayer(playerid, Fuel[playerid]);
			TextDrawHideForPlayer(playerid, GearInfo[playerid]);
			TextDrawHideForPlayer(playerid, Gear[0]);
			TextDrawHideForPlayer(playerid, Gear[1]);
			TextDrawHideForPlayer(playerid, Gear[2]);
			TextDrawHideForPlayer(playerid, Gear[3]);
			TextDrawHideForPlayer(playerid, Gear[4]);
			TextDrawHideForPlayer(playerid, Gear[5]);
			return 1;
		}
	}
	else
	{
	    HideGeneral(playerid);
	    TextDrawHideForPlayer(playerid, Speedo[playerid]);
		TextDrawHideForPlayer(playerid, Fuel[playerid]);
	    TextDrawHideForPlayer(playerid, GearInfo[playerid]);
	    TextDrawHideForPlayer(playerid, Gear[0]);
		TextDrawHideForPlayer(playerid, Gear[1]);
		TextDrawHideForPlayer(playerid, Gear[2]);
		TextDrawHideForPlayer(playerid, Gear[3]);
		TextDrawHideForPlayer(playerid, Gear[4]);
		TextDrawHideForPlayer(playerid, Gear[5]);
	}
	return 1;
}

ShowGeneral(playerid)
{
	TextDrawShowForPlayer(playerid, General[0]);
	TextDrawShowForPlayer(playerid, General[1]);
	TextDrawShowForPlayer(playerid, General[2]);
	TextDrawShowForPlayer(playerid, General[3]);
	TextDrawShowForPlayer(playerid, General[4]);
	return 1;
}

HideGeneral(playerid)
{
	TextDrawHideForPlayer(playerid, General[0]);
	TextDrawHideForPlayer(playerid, General[1]);
	TextDrawHideForPlayer(playerid, General[2]);
	TextDrawHideForPlayer(playerid, General[3]);
	TextDrawHideForPlayer(playerid, General[4]);
	return 1;
}

stock IsVehicleDrivingBackwards(vehicleid) // By Joker
{
	new
		Float:Float[3]
	;
	if(GetVehicleVelocity(vehicleid, Float[1], Float[2], Float[0]))
	{
		GetVehicleZAngle(vehicleid, Float[0]);
		if(Float[0] < 90)
		{
			if(Float[1] > 0 && Float[2] < 0) return true;
		}
		else if(Float[0] < 180)
		{
			if(Float[1] > 0 && Float[2] > 0) return true;
		}
		else if(Float[0] < 270)
		{
			if(Float[1] < 0 && Float[2] > 0) return true;
		}
		else if(Float[1] < 0 && Float[2] < 0) return true;
	}
	return false;
}
