#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

//new PDe;// palo exterior, garaje policía (rota)
new lspdgate; // puerta garaje policía
//new barrera;
new jgate; //Jin Azugay's gate
new ggate;//Gay Palmer's gate
new ggate_state = 0;//Cerrada por defecto
//new tgate; // Taxistas' gate
new puertacomi1,puertacomi2,puertacomi3,puertacomi4,puertacomi5,puertacomi6,puertacomi7;
new puertasheriff1,puertasheriff2;

Puertas_OnGameModeInit()
{
	lspdgate = CreateDynamicObject(10558, 1588.6029, -1638.3813, 14.4201, 0.0000, 0.0000, 269.6265); //LSPDt 1
	//PDe = CreateDynamicObject(968, 1544.670532, -1630.744873, 13.182366, 1.7189, 90.2408, 89.3814); //LSPD 2
	puertacomi1 = CreateDynamicObject(977, 239.58805847168, 118.58154296875, 1003.8226318359, 0, 0, 281.07531738281);
	puertacomi2 = CreateDynamicObject(977, 239.60734558105, 126.0859375, 1003.8226318359, 0, 0, 281.07421875);
	puertacomi3 = CreateDynamicObject(977, 253.23394775391, 126.2578125, 1003.8226318359, 0, 0, 281.07421875);
	puertacomi4 = CreateDynamicObject(977, 253.2008972168, 110.0859375, 1003.8226318359, 0, 0, 281.07421875);
	puertacomi5 = CreateDynamicObject(977,230.13186646,119.53012848,1010.12194824,0.00000000,0.00000000,11.25000000);
	puertacomi6 = CreateDynamicObject(977,232.92861938,108.07891846,1010.12194824,0.00000000,0.00000000,101.25000000);
	puertacomi7 = CreateDynamicObject(977,229.40443420,108.06378174,1010.12194824,0.00000000,0.00000000,101.49996948);
	puertasheriff1 = CreateDynamicObject(977,250.62304688,62.25606537,1003.46875000,0.00000000,0.00000000,102.00000000); 
	puertasheriff2 = CreateDynamicObject(977,247.46295166,72.61702728,1003.96923828,0.00000000,0.00000000,190.25001526); 
	jgate = CreateDynamicObject(10558,1643.30000000,-1715.00000000,16.00000000,0.00000000,0.00000000,0.00000000);
	ggate = CreateDynamicObject(975,1469.51904297,-1494.60839844,14.22451973,0.00000000,0.00000000,87.80010986);
	//tgate = CreateDynamicObject(975, 2534.1584472656, -1515.5895996094, 24.67022895813, 0, 0, 0);
	return 1;
}

Puertas_OnPlayerCommandText(playerid,cmdtext[])
{
	new cmd[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd, "/ap", true) == 0)
	{
        if(PlayerToPoint(25.0,playerid,1588.5617, -1638.0871, 5.7200))
		{
			if(PlayerInfo[playerid][pMember] == 1)
			{
				MoveDynamicObject(lspdgate, 1588.6631, -1638.3735, 18.4032, 1);
				format(string,sizeof(string), "* %s usa su control remoto para abrir la puerta.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				SendClientMessage(playerid,Azul,"La puerta se cerrará automáticamente en 10 segundos");
				SetTimerEx("CloseGate",10000,0,"p",lspdgate);
			}
		}
		/*else if(PlayerToPoint(25.0,playerid,1544.683593,-1630.765991,12.952643))
		{
			if(PlayerInfo[playerid][pMember] == 1)
			{
				SetDynamicObjectRot(PDe,0.0000, 0.0000, 89.3814); //LSPD2 :)
				format(string,sizeof(string), "* %s le avisa al oficial en la cabina que levante la barrera.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				SendClientMessage(playerid,Azul,"La barrera se cerrará automáticamente en 5 segundos");
				SetTimerEx("CloseGate",8000,0,"p",barrera);
			}
		}*/
		else if(PlayerToPoint(50.0,playerid,1643, -1715, 16.299999237061))
		{
			if(PlayerInfo[playerid][pMember] == 91)
			{
				MoveDynamicObject(jgate,1643.30000000,-1707.00000000,16.00000000, 1);
				format(string,sizeof(string), "* %s usa su control remoto para abrir la puerta.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				SendClientMessage(playerid,Azul,"La barrera se cerrará automáticamente en 10 segundos");
				SetTimerEx("CloseGate",10000,0,"p",jgate);
			}
		}
		/*else if(PlayerToPoint(25.0,playerid,2525.828125, -1515.7279052734, 24.670562744141))
		{
			if(PlayerInfo[playerid][pMember] == 3)
			{
				MoveDynamicObject(tgate,2525.828125, -1515.7279052734, 24.670562744141, 1);
				format(string,sizeof(string), "* %s usa su control remoto para abrir la puerta.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				SendClientMessage(playerid,Azul,"La barrera se cerrará automáticamente en 5 segundos");
				SetTimerEx("CloseGate",8000,0,"p",tgate);
			}
		}*/
		else if(PlayerToPoint(25.0,playerid,1469.51904297,-1486.60839844,14.22451973))
		{
			if(PlayerInfo[playerid][pMember] == 92 && ggate_state == 0)
			{
				MoveDynamicObject(ggate,1469.51904297,-1486.60839844,14.22451973, 1);
				ggate_state = 1;
				format(string,sizeof(string), "* %s usa su control remoto para abrir la puerta.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
				SendClientMessage(playerid,Azul,"Para cerrar la barrera usa /ap.");
			}
			else if(PlayerInfo[playerid][pMember] == 92 && ggate_state == 1)
			{
				CloseGate(ggate);
				ggate_state = 0;
				format(string,sizeof(string), "* %s usa su control remoto para cerrar la puerta.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado,Morado,Morado,Morado,Morado);
			}
		}
		return 1;
	}
	return 0;
}

Puertas_OnPlayerKeyStateChange(playerid, newkeys)
{
	new keyso, updown, leftright;
	GetPlayerKeys(playerid, keyso, updown, leftright);
	if((newkeys & KEY_SECONDARY_ATTACK))
	{
		if(PlayerToPoint(4.0,playerid,239.58805847168, 118.58154296875, 1003.8226318359) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi1,239.60903930664, 116.58627319336, 1003.8226318359,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi1);
			return 1;
		}
		if(PlayerToPoint(4.0,playerid,239.60734558105, 126.0859375, 1003.8226318359) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi2,239.61297607422, 124.08457183838, 1003.8226318359,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi2);
			return 1;
		}
		if(PlayerToPoint(4.0,playerid,253.23394775391, 126.2578125, 1003.8226318359) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi3,253.16390991211, 124.24350738525, 1003.8226318359,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi3);
			return 1;
		}
		if(PlayerToPoint(4.0,playerid,253.2008972168, 110.0859375, 1003.8226318359) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi4,253.1690826416, 108.0838470459, 1003.8226318359,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi4);
			return 1;
		}
		if(PlayerToPoint(1.5,playerid,230.13186646,119.53012848,1010.12194824) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi5,228.15505981,119.52091980,1010.12194824,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi5);
			return 1;
		}	
		if(PlayerToPoint(1.5,playerid,232.92861938,108.07891846,1010.1219482) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi6,232.88725281,106.10101318,1010.12194824,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi6);
			return 1;
		}			
		if(PlayerToPoint(1.5,playerid,229.40443420,108.06378174,1010.12194824) && PlayerInfo[playerid][pMember] == 1)
		{
			MoveDynamicObject(puertacomi7,229.41319275,106.11409760,1010.12194824,4);
			SetTimerEx("CloseGate",4000,0,"p",puertacomi7);
			return 1;
		}
		if(PlayerToPoint(1.5,playerid,250.62304688,62.25606537,1003.46875000) && PlayerInfo[playerid][pMember] == 6)
		{
			MoveDynamicObject(puertasheriff1,250.63641357,60.44984436,1003.46875000,4);
			SetTimerEx("CloseGate",4000,0,"p",puertasheriff1);
			return 1;
		}
		if(PlayerToPoint(2.0,playerid,247.46295166,72.61702728,1003.96923828) && PlayerInfo[playerid][pMember] == 6)
		{
			MoveDynamicObject(puertasheriff2,249.28527832,72.52067566,1003.96923828,4);
			SetTimerEx("CloseGate",4000,0,"p",puertasheriff2);
			return 1;
		}
	}
	return 0;
}

forward CloseGate(gate);
public CloseGate(gate)
{
	//if(gate == barrera)  {SetDynamicObjectRot(PDe,1.7189, 90.2408, 89.3814);}
	if(gate == lspdgate)   {MoveDynamicObject(lspdgate, 1588.6029, -1638.3813, 14.4201, 1);}
	if(gate == puertacomi1) {MoveDynamicObject(puertacomi1,239.58805847168, 118.58154296875, 1003.8226318359,4);}
	if(gate == puertacomi2) {MoveDynamicObject(puertacomi2, 239.60734558105, 126.0859375, 1003.8226318359,4);}
	if(gate == puertacomi3) {MoveDynamicObject(puertacomi3,253.23394775391, 126.2578125, 1003.8226318359,4);}
	if(gate == puertacomi4) {MoveDynamicObject(puertacomi4,253.2008972168, 110.0859375, 1003.8226318359,4);}
	if(gate == puertacomi5) {MoveDynamicObject(puertacomi5,230.13186646,119.53012848,1010.12194824,4);}
	if(gate == puertacomi6) {MoveDynamicObject(puertacomi6,232.92861938,108.07891846,1010.1219482,4);}
	if(gate == puertacomi7) {MoveDynamicObject(puertacomi7,229.40443420,108.06378174,1010.12194824,4);}
	if(gate == puertasheriff1) {MoveDynamicObject(puertasheriff1,250.62304688,62.25606537,1003.46875000,4);}
	if(gate == puertasheriff2) {MoveDynamicObject(puertasheriff2,247.46295166,72.61702728,1003.96923828,4);}
	if(gate == jgate) {MoveDynamicObject(jgate,1643.30000000,-1715.00000000,16.00000000,1);}
	if(gate == ggate) {MoveDynamicObject(ggate,1469.51904297,-1494.60839844,14.22451973,1);}
	//if(gate == tgate) {MoveDynamicObject(tgate,2534.1584472656, -1515.5895996094, 24.67022895813,1);}
	return 1;
}