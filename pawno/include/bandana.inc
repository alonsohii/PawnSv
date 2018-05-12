/* 
   Old School v2 "The future is here"
   - - - - - - - - - - - - - - - - - -
		DEATH GOP GORTHOL DESK
   - - - - - - - - - - - - - - - - - -
*/

#include <a_samp>

Bandana_OnPlayerCommandText(playerid,cmdtext[])
{
	new cmd[128], tmp[128], idx;
	cmd = strtokex(cmdtext, idx);

	if(strcmp(cmd,"/bandana",true) == 0)
	{
		if(PlayerInfo[playerid][pBandana] == 0) { SendClientMessage(playerid, Rojo, "* No tienes una bandana!"); return 1; }
		//if(!IsBandanaSkinValid(playerid)) { SendClientMessage(playerid, Rojo, "* No te puedes poner una bandana con este skin!"); return 1; }
		format(string,sizeof(string),"* %s se pone una bandana",pName(playerid));
		if(GetPlayerInterior(playerid) > 0) {
		ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		else {
		ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
		SendClientMessage(playerid,Blanco,"Usa /qbandana para quitartela");
		new bandana;
		switch(PlayerInfo[playerid][pBandana])
		{
			case 1: {bandana = 18911;}
			case 2: {bandana = 18912;}
			case 3: {bandana = 18913;}
			case 4: {bandana = 18914;}
			case 5: {bandana = 18915;}
			case 6: {bandana = 18916;}
			case 7: {bandana = 18917;}
			case 8: {bandana = 18918;}
			case 9: {bandana = 18919;}
		}
		new Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ, Float:ScaleX, Float:ScaleY, Float:ScaleZ;
		new SkinA = GetPlayerSkin(playerid);	
		if(SkinA == 114){ OffsetX = 0.075032; OffsetY = 0.033350; OffsetZ = -0.00230; RotX = 270.0; RotY = 354.129486; RotZ = 270.0; ScaleX = 1.140555; ScaleY = 1.0; ScaleZ = 1.169999; }
		else if(SkinA == 116){ OffsetX = 0.088407; OffsetY = 0.012163; OffsetZ = 0.002391; RotX = 266.934539; RotY = 0.607962; RotZ = 266.221496; ScaleX = 1.0; ScaleY = 1.3; ScaleZ = 1.172806; }
		else if(SkinA == 115){ OffsetX = 0.1; OffsetY = 0.02; OffsetZ = 0.0; RotX = 270.0; RotY = 3.0; RotZ = 267.0; ScaleX = 1.25; ScaleY = 1.15; ScaleZ = 1.15; }
		else if(SkinA == 173){ OffsetX = 0.088407; OffsetY = 0.030055; OffsetZ = 0.002897; RotX = 266.934539; RotY = 0.917962; RotZ = 266.021496; ScaleX = 1.110016; ScaleY = 1.1; ScaleZ = 1.09; }
		else if(SkinA == 174){ OffsetX = 0.088407; OffsetY = 0.030055; OffsetZ = -0.005007; RotX = 266.934539; RotY = 0.607962; RotZ = 266.021496; ScaleX = 1.072806; ScaleY = 1.2; ScaleZ = 1.0; }
		else if(SkinA == 175){ OffsetX = 0.088407; OffsetY = 0.030055; OffsetZ = -0.002897; RotX = 266.934539; RotY = 0.607962; RotZ = 266.021496; ScaleX = 1.110016; ScaleY = 1.1; ScaleZ = 1.09; }
		//groves
		else if(SkinA == 271){ OffsetX = 0.073522; OffsetY = 0.015061; OffsetZ = -0.005912; RotX = 277.060668; RotY = 9.697027; RotZ = 264.330200; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 270){ OffsetX = 0.083064; OffsetY = 0.015061; OffsetZ = 0.003734; RotX = 270.357788; RotY = 2.187248; RotZ = 264.330200; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 269){ OffsetX = 0.083064; OffsetY = 0.017489; OffsetZ = 0.002312; RotX = 270.357788; RotY = 2.187248; RotZ = 266.944274; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 105){ OffsetX = 0.078534; OffsetY = 0.041857; OffsetZ = -0.001727; RotX = 268.970458; RotY = 1.533374; RotZ = 269.223754; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 106){ OffsetX = 0.084321; OffsetY = 0.032509; OffsetZ = -0.006748; RotX = 268.970458; RotY = 1.533374; RotZ = 269.223754; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 107){ OffsetX = 0.084321; OffsetY = 0.035590; OffsetZ = -0.004405; RotX = 268.970458; RotY = 1.533374; RotZ = 269.223754; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		//Latinos
		else if(SkinA == 108){ OffsetX = 0.084809; OffsetY = 0.026987; OffsetZ = 0.000924; RotX = 273.545745; RotY = 0.572601; RotZ = 264.837554; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 109){ OffsetX = 0.081629; OffsetY = 0.035036; OffsetZ = -0.006385; RotX = 273.545745; RotY = 0.572601; RotZ = 264.837554; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 110){ OffsetX = 0.073774; OffsetY = 0.042118; OffsetZ = -0.003368; RotX = 273.422515; RotY = 0.243100; RotZ = 267.547058; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		//Ballas
		else if(SkinA == 102){ OffsetX = 0.117283; OffsetY = 0.023948; OffsetZ = 0.007144; RotX = 266.934539; RotY = 0.607962; RotZ = 267.715026; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 0.953347; }
		else if(SkinA == 103){ OffsetX = 0.098212; OffsetY = 0.002083; OffsetZ = 0.004703; RotX = 267.582092; RotY = 0.607962; RotZ = 267.715026; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.103653; }
		else if(SkinA == 104){ OffsetX = 0.098212; OffsetY = 0.002083; OffsetZ = 0.003503; RotX = 267.582092; RotY = 0.607962; RotZ = 267.715026; ScaleX = 1.17; ScaleY = 1.0; ScaleZ = 0.103652; }
		else if(SkinA == 293){ OffsetX = 0.104230; OffsetY = 0.019460; OffsetZ = -0.002173; RotX = 268.196228; RotY = 359.229461; RotZ = 269.282684; ScaleX = 1.09; ScaleY = 1.0; ScaleZ = 1.224868; }
		//Blood
		else if(SkinA == 7){ OffsetX = 0.086248; OffsetY = 0.036498; OffsetZ = -0.004328; RotX = 270.304412; RotY = 359.126678; RotZ = 266.091674; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 67){ OffsetX = 0.086248; OffsetY = 0.020672; OffsetZ = 0.001285; RotX = 270.304412; RotY = 359.126678; RotZ = 266.091674; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 180){ OffsetX = 0.084799; OffsetY = 0.039217; OffsetZ = -0.007458; RotX = 270.304412; RotY = 359.126678; RotZ = 271.452209; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 19){ OffsetX = 0.081000; OffsetY = 0.026039; OffsetZ = -0.004144; RotX = 270.304412; RotY = 359.126678; RotZ = 271.452209; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 144){ OffsetX = 0.110470; OffsetY = 0.043788; OffsetZ = -0.002435; RotX = 266.909606; RotY = 358.832275; RotZ = 267.704956; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 143){ OffsetX = 0.0844551; OffsetY = -0.018; OffsetZ = 0.007644; RotX = 266.934539; RotY = 0.607962; RotZ = 267.715026; ScaleX = 1.09; ScaleY = 1.0; ScaleZ = 1.106930; }
		else if(SkinA == 176){ OffsetX = 0.109974; OffsetY = 0.005303; OffsetZ = 0.005296; RotX = 270.835723; RotY = 1.246085; RotZ = 266.144866; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.064156; }
		else if(SkinA == 297){ OffsetX = 0.104230; OffsetY = 0.007563; OffsetZ = -0.001793; RotX = 268.196228; RotY = 353.889251; RotZ = 269.282684; ScaleX = 1.2; ScaleY = 1.0; ScaleZ = 1.134868; }

		//Moteros
		else if(SkinA == 23){ OffsetX = 0.082504; OffsetY = 0.038338; OffsetZ = -0.005320; RotX = 271.407196; RotY = 356.295104; RotZ = 267.907989; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 247){ OffsetX = 0.088066; OffsetY = 0.038264; OffsetZ = 0.000398; RotX = 271.407196; RotY = 356.295104; RotZ = 267.907989; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 248){ OffsetX = 0.088066; OffsetY = 0.038264; OffsetZ = 0.000398; RotX = 271.407196; RotY = 356.295104; RotZ = 267.907989; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 100){ OffsetX = 0.088066; OffsetY = 0.038264; OffsetZ = 0.000398; RotX = 271.407196; RotY = 356.295104; RotZ = 267.907989; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else if(SkinA == 33){ OffsetX = 0.041866; OffsetY = 0.015547; OffsetZ = -0.001428; RotX = 271.371276; RotY = 356.919921; RotZ = 269.937591; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; }
		else { OffsetX = 0.073774; OffsetY = 0.042118; OffsetZ = -0.003368; RotX = 273.422515; RotY = 0.243100; RotZ = 267.547058; ScaleX = 1.0; ScaleY = 1.0; ScaleZ = 1.0; } // Default
		SetPlayerAttachedObject(playerid, BANDANAS_SLOT,bandana, 2, OffsetX, OffsetY, OffsetZ, RotX, RotY, RotZ, ScaleX, ScaleY, ScaleZ);
		return 1;
	}
	if(strcmp(cmd,"/qbandana",true) == 0)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid,BANDANAS_SLOT))
		{
			format(string,sizeof(string),"* %s se quita la bandana",pName(playerid));
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			RemovePlayerAttachedObject(playerid,BANDANAS_SLOT);
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* No te has puesto la bandana!");
		}
		return 1;
	}
	if(strcmp(cmd,"/debugbandana",true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 1) return 0;
	    tmp = strtokex(cmdtext, idx);
    	if(!strlen(tmp)) { SendClientMessage(playerid, Blanco, "USO: /debugbandana id"); return 1; }
    	new bandana = strval(tmp);
		format(string,sizeof(string),"DEBUG: Bandana id cambiada a %d",bandana);
		SendClientMessage(playerid,AmarilloClaro,string);
		PlayerInfo[playerid][pBandana] = bandana;
		SaveValues(playerid,"Inventario");
		return 1;
	}
	return 0;
}

stock IsBandanaSkinValid(playerid)
{
	new SkinA = GetPlayerSkin(playerid);
	if(SkinA == 115 || SkinA == 114 || SkinA == 116 || SkinA == 173 || SkinA == 174 || SkinA == 175 || SkinA == 271
		|| SkinA == 270 || SkinA == 269 || SkinA == 105 || SkinA == 106 || SkinA == 107 || SkinA == 108 || SkinA == 109 
		|| SkinA == 110 || SkinA == 102 || SkinA == 103 || SkinA == 104 || SkinA == 293 || SkinA == 7 || SkinA == 67 
		|| SkinA == 180 || SkinA == 19 || SkinA == 144 || SkinA == 23 || SkinA == 247 || SkinA == 248 || SkinA == 100 
		|| SkinA == 33){ return 1;}
	return 0;
}
