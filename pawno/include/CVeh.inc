#include <a_samp>
//By irinel1996. || Keep the credits.
//Contact: irinel.iovu@yahoo.com | irinel.iovu@hotmail.com
#define MAX_PCambio 100
#define ID_PC_INVALID 999

enum PicksCmb { IDPC, Float:PX, Float:PY, Float:PZ, IDNewCar };
new PickCam[MAX_PCambio][PicksCmb], PickupC, TUpdate;

forward UpdatePos(); forward ChangeVeh(IDPCmb); forward ReactivarT();

stock start_sveh() { TUpdate = SetTimer("UpdatePos",40,1); return 1; }

stock CreateChangeVeh(Model, NewCar, Float:X, Float:Y, Float:Z, Texto[])
{
    new IDPCmb = PickupC;
    if(PickupC > MAX_PCambio-1)
	{
		print(">> ERROR: Sobrepasado el límite de pickups de cambio!!");
		IDPCmb = ID_PC_INVALID;
		return IDPCmb;
	}
	PickupC++;
	PickCam[IDPCmb][IDPC] = IDPCmb; PickCam[IDPCmb][IDNewCar] = NewCar;
	PickCam[IDPCmb][PX] = X; PickCam[IDPCmb][PY] = Y; PickCam[IDPCmb][PZ] = Z;
	AddStaticPickup(Model,23,X,Y,Z,-1); Create3DTextLabel(Texto,0xFF00EBFF,X,Y,Z,30,0);
	return 0;
}

stock ScarMaxPC() { return PickupC; }

public UpdatePos() { for(new pcsc = 0; pcsc < ScarMaxPC(); pcsc++) { if(pcsc != ID_PC_INVALID) { ChangeVeh(pcsc); } } }

public ChangeVeh(IDPCmb)
{
	for(new i = 0; i <MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(IsPlayerInAnyVehicle(i))
       		{
       		    new vehicleid = GetPlayerVehicleID(i);
         		if(IsVehicleInRangeOfPoint(vehicleid,0.8,PickCam[IDPCmb][PX],PickCam[IDPCmb][PY],PickCam[IDPCmb][PZ]))
       			{
       			    PlayerPlaySound(i, 1054, 0.0, 0.0, 0.0);
	        		new Float:Velocidad[3], Float:X, Float:Y, Float:Z, Float:Angulo;
				 	GetVehiclePos(vehicleid, X,Y,Z); GetVehicleZAngle(vehicleid,Angulo);
				  	GetVehicleVelocity(vehicleid, Velocidad[0], Velocidad[1], Velocidad[2]);
					DestroyVehicle(vehicleid);
					new NewVeh = CreateVehicle(PickCam[IDPCmb][IDNewCar],X,Y,Z,Angulo,129,129,180);
					PutPlayerInVehicle(i,NewVeh,0);
					SetVehicleVelocity(NewVeh, Velocidad[0], Velocidad[1], Velocidad[2]);
					KillTimer(TUpdate); SetTimer("ReactivarT",1000,0);
				}
			}
		}
	}
	return 1;
}

public ReactivarT() { TUpdate = SetTimer("UpdatePos",40,1); return 1; }

IsVehicleInRangeOfPoint(vehicleid, Float:vrange, Float:x, Float:y, Float:z) //By ¿Unknown?
{
	new Float:oldpos[3], Float:temppos[3];
	GetVehiclePos(vehicleid, oldpos[0], oldpos[1], oldpos[2]);
	temppos[0] = (oldpos[0] -x); temppos[1] = (oldpos[1] -y); temppos[2] = (oldpos[2] -z);
	if(((temppos[0] < vrange) && (temppos[0] > -vrange)) && ((temppos[1] < vrange) && (temppos[1] > -vrange)) && ((temppos[2] < vrange) && (temppos[2] > -vrange)))
	{ return true; }
	return false;
}
