#include <a_samp>
#include <globalvars>

#define COLOR_GREEN 0x33AA33AA
#define COLOR_RED 0xAA3333AA

new IsSpu[MAX_VEHICLES] = 0;
new Lamp[MAX_VEHICLES] = 0;
new light[MAX_VEHICLES];

Sirena_OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/sirena", cmdtext, true) == 0)
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			if(CarInfo[GetPlayerVehicle(playerid)][cUsos] == 1 || CarInfo[GetPlayerVehicle(playerid)][cUsos] == 2 || CarInfo[GetPlayerVehicle(playerid)][cUsos] == 6)
			{
				if(IsACop(playerid) || IsAMedic(playerid))
				{
					ShowPlayerDialog(playerid, 112, DIALOG_STYLE_LIST, "Quieres una sirena? Cual necesitas?", "Sultan [tablero]\nSultan [techo]\nCheetah [tablero]\nCheetah [techo]\nWashington [tablero]\nWashington [techo]\nPremier [tablero]\nPremier [techo]\nHuntley [tablero]\nHuntley [techo]\nMas", "Tomarlo", "Salir" );
				}
			}
		}
		return 1;
	}
	return 0;
}

Sirena_OnDialogResponse(playerid, dialogid, response, listitem)
{
	if(dialogid != 112 && dialogid != 113) return 1;
	
	if(response == 1 && dialogid == 112)
	{
		if(IsSpu[GetPlayerVehicleID(playerid)] > 0)
		{
			DestroyObject(light[GetPlayerVehicleID(playerid)]);
			Lamp[GetPlayerVehicleID(playerid)] = 0;
		}
		switch(listitem)
		{
           case 0:
            {//sultan lamp inside
     			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 1;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.398071289, 0.75390625, 0.43879509, 0.0, 0.0, 0.0);
			}
            case 1:
            {//sultan lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 2;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.35644531250, 0.0388183593, 0.863788605, 0.0, 0.0, 0.0);
			}
            case 2:
            {//cheetah lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 3;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.409729004, 0.526367188, 0.206963539, 0.0, 0.0, 0.0);
			}
            case 3:
            {//cheetah lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 4;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.290039062, -0.284179688, 0.631957054, 0.0, 0.0, 0.0);
			}
			case 4:
            {//wash lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 5;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.421691895, 0.804931641, 0.256482124, 0.0, 0.0, 0.0);
			}
            case 5:
            {//wash lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 6;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.323303223, 0.0207519532, 0.731482506, 0.0, 0.0, 0.0);
			}//done
			case 6:
            {//premier lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 7;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.575378418, 0.786132812, 0.361483574, 0.0, 0.0, 0.0);
			}
			case 7:
            {//premier lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 8;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.455505371, -0.143066406, 0.861475945, 0.0, 0.0, 0.0);
			}
			case 8:
            {//huntley lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 9;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.454345703, 0.575683594, 0.645122528, 0.0, 0.0, 0.0);
			}
			case 9:
            {//huntley lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 10;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.442626953, -0.269042969, 1.27014542, 0.0, 0.0, 0.0);
			}
			case 10:
            {//new dialog
	            ShowPlayerDialog(playerid, 113, DIALOG_STYLE_LIST, "Quieres una sirena? Cual necesitas?", "Buffalo [tablero]\nBuffalo [techo]\nLSPD Cruiser[tablero]\nLSPD Cruiser[techo]\nSFPD Cruiser[tablero]\nSFPD Cruiser[techo]\nLVPD Cruiser[tablero]\nLVPD Cruiser[techo]", "Tomarlo", "Salir" );
				return 1;
			}
		}
	}
	if(response == 1 && dialogid == 113)
	{
		switch(listitem)
		{
            case 0:
            {//buffalo lamp inside
     			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 11;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.53515625, 0.562988281, 0.278743744, 0.0, 0.0, 0.0);

			}
            case 1:
            {//buffalo lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 12;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.412841797, -0.474365234, 0.778804779, 0.0, 0.0, 0.0);
			}
			case 2:
            {//lspd lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 13;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.53515625, 0.771728516, 0.373809814, 0.0, 0.0, 0.0);
			}
            case 3:
            {//lspd lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 14;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.0048828125, -0.860107422, 0.848770142, 0.0, 0.0, 0.0);
			}
			case 4:
            {//sfpd lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 15;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.53515625, 0.771728516, 0.373809814, 0.0, 0.0, 0.0);
			}
            case 5:
            {//sfpd lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 16;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.0048828125, -0.860107422, 0.848770142, 0.0, 0.0, 0.0);
			}
            case 6:
            {//lvpd lamp inside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 17;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, 0.406738281, 0.696777344, 0.398208618, 0.0, 0.0, 0.0);
			}
            case 7:
            {//lvpd lamp outside
    			new Float:x, Float:y, Float:z, Float:angle;
	 			GetPlayerPos(playerid, x, y, z);
	 			GetPlayerFacingAngle(playerid, angle);
	    		new vehicleid=CarInfo[GetPlayerVehicle(playerid)][cId];
				IsSpu[vehicleid] = 18;
				Lamp[vehicleid] = 1;
				light[vehicleid] = CreateObject(18646,x, y, z, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(light[vehicleid], vehicleid, -0.0048828125, -0.860107422, 0.848770142, 0.0, 0.0, 0.0);
			}
		}
	}
	CarInfo[GetPlayerVehicle(playerid)][cSirena] = IsSpu[CarInfo[GetPlayerVehicle(playerid)][cId]];
	SaveCar(GetPlayerVehicle(playerid));
	return 1;
}

Sirena_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH))
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(CarInfo[GetPlayerVehicle(playerid)][cUsos] == 1 || CarInfo[GetPlayerVehicle(playerid)][cUsos] == 2 || CarInfo[GetPlayerVehicle(playerid)][cUsos] == 6)
			{
				VehicleLightSwitch(playerid);
				return 1;
			}
		}
	}
	return 0;
}

VehicleLightSwitch(playerid)
{
		new vid = GetPlayerVehicleID(playerid);
		if(vid == INVALID_VEHICLE_ID) return 1;
		if(IsSpu[vid] == 1)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.398071289, 0.75390625, 0.43879509, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
   		if(IsSpu[vid] == 2)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.35644531250, 0.0388183593, 0.863788605, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
   		if(IsSpu[vid] == 3)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.409729004, 0.526367188, 0.206963539, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
   		if(IsSpu[vid] == 4)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.290039062, -0.284179688, 0.631957054, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
   		if(IsSpu[vid] == 5)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.421691895, 0.804931641, 0.256482124, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
   		if(IsSpu[vid] == 6)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.323303223, 0.0207519532, 0.731482506, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
   		if(IsSpu[vid] == 7)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.575378418, 0.786132812, 0.361483574, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 8)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.455505371, -0.143066406, 0.861475945, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 9)
		{
		    if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.454345703, 0.575683594, 0.645122528, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 10)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.442626953, -0.269042969, 1.27014542, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 11)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.53515625, 0.562988281, 0.278743744, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 12)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.412841797, -0.474365234, 0.778804779, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
	    if(IsSpu[vid] == 13)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.53515625, 0.771728516, 0.373809814, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 14)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.0048828125, -0.860107422, 0.848770142, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 15)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.53515625, 0.771728516, 0.373809814, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 16)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.0048828125, -0.860107422, 0.848770142, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 17)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, 0.406738281, 0.696777344, 0.398208618, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
    	if(IsSpu[vid] == 18)
		{
 			if(Lamp[vid] == 1)
 			{
				 DestroyObject(light[vid]);
				 Lamp[vid] = 0;
				 return 1;
			}
			if(Lamp[vid] == 0)
 			{
				 light[vid] = CreateObject(18646,0, 0, 0, 0.0, 0.0, 96.0);
				 AttachObjectToVehicle(light[vid], vid, -0.0048828125, -0.860107422, 0.848770142, 0.0, 0.0, 0.0);
				 Lamp[vid] = 1;
				 return 1;
			}
	    }
	    return 1;
}