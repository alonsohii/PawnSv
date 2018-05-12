#include <a_samp>
#define MAX_SPRUNK 100
#define SPRUNK_PRICE 5
forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z, Float:RotX, Float:RotY, Float:RotZ);
forward Sprunkend(playerid);

new sprunk[MAX_SPRUNK], Float:Rot[7][MAX_SPRUNK];

stock AddStaticSprunk(id,Float:X,Float:Y,Float:Z,Float:RotX,Float:RotY,Float:RotZ)
{
	sprunk[id] = CreateObject(955,X,Y,Z,RotX,RotY,RotZ);
	GetObjectPos(sprunk[id],Rot[1][id],Rot[2][id],Rot[3][id]);
	GetObjectRot(sprunk[id],Rot[4][id],Rot[5][id],Rot[6][id]);
	return id;
}

public Sprunkend(playerid)
{
	ApplyAnimation(playerid,"VENDING","VEND_Drink_P",3.0,0,0,0,0,0);
	TogglePlayerControllable(playerid,1);
	new Float:health;
	GetPlayerHealth(playerid,health);
	SetPlayerHealth(playerid,health+10);
}


public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z, Float:RotX, Float:RotY, Float:RotZ)
{
	new Float:oldposx, Float:oldposy, Float:oldposz, Float:oldposrotx, Float:oldposroty, Float:oldposrotz;
	new Float:tempposx, Float:tempposy, Float:tempposz, Float:tempposrotx, Float:tempposroty, Float:tempposrotz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	GetObjectRot(playerid, oldposrotx, oldposroty, oldposrotz);
	tempposx    = (oldposx -x);
	tempposy    = (oldposy -y);
	tempposz    = (oldposz -z);
	tempposrotx = (oldposrotx -RotX);
	tempposroty = (oldposroty -RotY);
	tempposrotz = (oldposrotz -RotZ);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi) && (tempposrotx < radi) && (tempposrotx > -radi)) && ((tempposroty < radi) && (tempposroty > -radi)) && ((tempposrotz < radi) && (tempposrotz > -radi)))
	{
		return 1;
	}
	return 0;
}

IsPlayerInSphere(playerid,Float:x,Float:y,Float:z,radius)
{
	if(GetPlayerDistanceToPointEx(playerid,x,y,z) < radius)
	{
   		return 1;
	}
   	return 0;
}

GetPlayerDistanceToPointEx(playerid,Float:x,Float:y,Float:z)
{
	new Float:x1,Float:y1,Float:z1;
	new Float:tmpdis;
	GetPlayerPos(playerid,x1,y1,z1);
	tmpdis = floatsqroot(floatpower(floatabs(floatsub(x,x1)),2)+floatpower(floatabs(floatsub(y,y1)),2)+floatpower(floatabs(floatsub(z,z1)),2));
	return floatround(tmpdis);
}