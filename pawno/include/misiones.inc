#include <colores>
#include <globalvars>
#include <funciones>
#define MAX_LUGARESPINTAR 29
#define MAX_LUGARESQUEMAR 18
#define MAX_CLIENTTAXI 38
new numeromision = 0;
new randmis = 0;
new ApagandoI = 0;
// Misión Spray  //////////////////////////////////////////////////////
new EstaPintando[MAX_PLAYERS];
new EstaEnMision[MAX_PLAYERS];
new checkspray;
new randlugpint = 0;
new pintadotimer;
new MisionFinalizada;
new MisionActiva;
new ganadormis;
new MensajeAPoliciaEnviado;
enum lPintar
{
	Float:chx,
	Float:chy,
	Float:chz,
	Float:rZ,
	ido,
	Text3D:chlabel
}
new LugaresPintar[MAX_LUGARESPINTAR][lPintar] = {
{2229.1572265625, -1696.5451660156, 14.041578292847,353.07604980469,17969},
{2171.7385253906, -1729.7940673828, 13.817392349243,269.39364624023,17969},
{2120.4128417969, -1791.0161132813, 13.830236434937,269.79827880859,17969},
{2171.1977539063, -1786.0766601563, 13.95393371582,89.768402099609,17969},
{2240.0051269531, -1766.4337158203, 13.968311309814,269.7204284668,17969},
{2352.7646484375, -1766.4425048828, 13.905846595764, 269.71984863281,17969},
{2441.0187988281, -1765.1750488281, 13.794003486633,180.71214294434,17969},
{2517.7446289063, -1769.7637939453, 13.822423934937,179.47265625,17969},
{2352.3972167969, -1546.6158447266, 24.284816741943,359.09399414063,17969},
{2151.5070800781, -1475.306640625, 25.89435005188,89.907318115234,17969},
{2118.1750488281, -1374.3723144531, 24.259923934937,89.786682128906,17969},
{2049.1003417969, -1326.7886962891, 24.427711486816,89.785766601563,17969},
{1811.6851806641, -1906.8703613281, 13.77969455719,179.8525390625,17969},
{1950.6447753906, -2034.5939941406, 13.822423934937,179.85168457031,17969},
{1813.0487060547, -2054.0747070313, 13.827587127686,179.8276367187,17969},
{1832.9853515625, -2113.8955078125, 13.792038917542,359.85549926758,17969},
{1804.2266845703, -2150.8681640625, 14.006412506104,89.737182617188,17969},
{1747.3436279297, -2077.8979492188, 13.831970214844,89.880340576172,17969},
{1862.4057617188, -2095.45703125, 13.822423934937,89.880340576172,17969},
{1974.5344238281, -2013.0147705078, 13.816423416138,90.047180175781,17969},
{2724.1708984375, -2007.5286865234, 13.816834449768,0.17227172851563,17969},
{2731.814453125, -2019.2261962891, 14.021203994751,269.71673583984,17969},
{2704.2316894531, -2068.4936523438, 13.334823608398,179.81848144531,17969},
{2657.0634765625, -2016.283203125, 14.18607711792,270.02117919922,17969},
{2736.9716796875, -1962.3135986328, 13.98532295227,359.82827758789,17969},
{2794.4604492188, -1982.1267089844, 13.826892852783,89.800872802734,17969},
{2535.7607421875, -2022.2601318359, 14.147075653076,223.17459106445,17969},
{2403.7890625, -2027.2957763672, 13.822423934937,179.72741699219,17969},
{2451.255859375, -1987.0987548828, 13.965670585632,179.90545654297,17969}
};
// Misión Quemar cosas negras  //////////////////////////////////////////////////////

new EstaQuemando[MAX_PLAYERS];
new timermisiones;
new quemandotimer;
new randlugquem = 0;
new incendio;
enum lQuemar
{
	Float:chx,
	Float:chy,
	Float:chz,
	ido
}
new LugaresQuemar[MAX_LUGARESQUEMAR][lQuemar] = {
{1848.9476318359, -1871.1956787109, 12.578125,18691},
{1787.7706298828, -1719.6165771484, 12.700311660767,18691},
{1835.1181640625, -1442.8173828125, 12.598418235779,18691},
{1862.48828125, -1280.6868896484, 12.559476852417,18691},
{1721.4738769531, -1454.81640625, 12.604610443115,18691},
{1442.2302246094, -1303.3653564453, 12.614899635315,18691},
{1331.4719238281, -1265.8911132813, 12.546875,18691},
{1116.9211425781, -1269.0208740234, 12.546875,18691},
{1042.2781982422, -1285.2227783203, 13.16767024993,18691},
{1001.086730957, -1293.8533935547, 12.546875,18691},
{953.90368652344, -1338.6633300781, 12.621002197266,18691},
{503.14709472656, -1404.9464111328, 15.156709671021,18691},
{363.75009155273, -1554.4553222656, 31.943698883057,18691},
{369.98068237305, -1604.5155029297, 30.589105606079,18691},
{389.08383178711, -1870.9700927734, 6.8359375,18691},
{685.50762939453, -1777.2379150391, 12.6328125,18691},
{1454.5926513672, -1861.5056152344, 12.539081573486,18691},
{1884.7694091797, -1790.646484375, 12.688849449158,18691}
};

// Misiones para taxistas //////////////////////////////////////////////////////
enum lTaxi
{
	Float:tx,
	Float:ty,
	Float:tz,
	Float:rt
}
new LugaresTaxi[MAX_CLIENTTAXI][lTaxi] =
{
{2127.4858,-1116.2338,25.2675,70.4630},
{2222.8479,-1138.6196,25.6389,251.8279},
{2229.3225,-1305.1366,23.9176,90.3100},
{2477.9380,-1506.4569,23.8314,269.9836},
{2415.6841,-1737.2346,13.3919,282.0129},
{2820.9695,-1852.6464,10.9395,356.4754},
{2238.8325,-2208.9287,13.3348,227.1097},
{2289.5884,-2368.6887,13.4073,136.1181},
{1958.2175,-2021.1711,13.3938,180.8345},
{2083.3748,-1816.9615,13.3857,356.4571},
{1825.4084,-1842.7389,13.4162,0.7630},
{1817.0450,-1887.6829,13.4133,179.8432},
{1639.5142,-1875.8335,13.3855,268.7016},
{1533.7384,-1674.0410,13.3851,359.2100},
{1754.4086,-1600.0253,13.3811,76.4018},
{2170.0352,-1797.5029,13.3666,94.2392},
{1517.2095,-1443.4698,13.3846,268.4315},
{1329.4094,-1569.8363,13.3565,77.3406},
{1425.5660,-1647.3005,13.3427,180.6811},
{1346.5642,-1734.9819,13.3957,274.2888},
{1481.4342,-1734.5602,13.3846,269.7408},
{1183.2081,-1725.6776,13.4291,355.9760},
{1198.6096,-1467.6814,13.3869,1.6474},
{1192.9742,-1324.5011,13.4043,181.3130},
{1215.9153,-928.8008,42.7629,98.0689},
{589.3064,-1232.1538,17.7264,108.1566},
{540.4866,-1277.2834,17.2451,92.6775},
{276.2717,-1425.9680,13.6979,295.0875},
{333.8180,-1519.9075,35.8659,142.0510},
{573.4277,-1580.6711,16.0183,89.1882},
{709.0876,-1409.4647,13.3882,271.8878},
{332.7955,-1796.2281,4.7541,269.8796},
{370.9580,-1699.7627,7.0769,90.6283},
{367.0264,-2032.6409,7.6748,179.7998},
{-91.5814,-1123.4928,1.0898,334.5874},
{-530.7665,-555.0803,25.5243,88.4776},
{311.0416,-214.5909,1.3955,270.7313},
{-3.6279,54.0300,3.1213,341.4352}
};
new randclient = 0;
new clientcp[MAX_PLAYERS];
MisBand_OnGameModeInit()
{
	timermisiones = SetTimer("TimerMisiones",3600000,1);
	return 1;
}
MisBand_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd,"/mision",true)==0)
	{
		tmp = strtokex(cmdtext,idx);
		if(!strlen(tmp)){SendClientMessage(playerid,Blanco,"USO: /mision (aceptar/rechazar/info)"); return 1;}
		if(strcmp(tmp,"aceptar",true)==0)
		{
			if(11 <= PlayerInfo[playerid][pMember] <= 20  && EstaEnMision[playerid] != 1 && MisionActiva == 1)
			{
				if(numeromision == 1){MisionSprayAceptada(playerid);}
				if(numeromision == 2){MisionQuemarAceptada(playerid);}
				EstaEnMision[playerid] = 1;
				return 1;
			}
		}
		if(strcmp(tmp,"rechazar",true)==0)
		if(11 <= PlayerInfo[playerid][pMember] <= 20 && EstaEnMision[playerid] != 1 && MisionActiva == 1)
		{
			{
				SendClientMessage(playerid,Amarillo,"* Mision rechazada");
				return 1;
			}
		}
		if(strcmp(tmp,"info",true)==0)
		{
			if(11 <= PlayerInfo[playerid][pMember] <= 20)
			{
				if(MisionFinalizada == 1) return SendClientMessage(playerid,Aguamarina,"* La misión ya fue completada");
				else return SendClientMessage(playerid,Verde,"* Hay una misión activa");
			}
		}
	
		return 1;
	}
	if(strcmp(cmd,"/graf",true)==0)
	{
		if(EstaEnMision[playerid] == 1 && PlayerToPoint(5.0,playerid,LugaresPintar[randlugpint][chx], LugaresPintar[randlugpint][chy], LugaresPintar[randlugpint][chz]))
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(EstaPintando[i] == 1)
				{
					SendClientMessage(playerid,Rojo,"Ya están pintando");
					return 1;
				}
			}
			pintando(playerid);
			return 1;		
		}
		return 1;
	}
	if(strcmp(cmd,"/cgraf",true)==0)
	{
		if(EstaPintando[playerid] == 1)
		{
			KillTimer(pintadotimer);
			EstaPintando[playerid] = 0;
			ClearAnimations(playerid,1);
			return 1;
		}
	}
	if(strcmp(cmd,"/quem",true)==0)
	{
		if(EstaEnMision[playerid] == 1 && PlayerToPoint(5.0,playerid,LugaresQuemar[randlugquem][chx], LugaresQuemar[randlugquem][chy], LugaresQuemar[randlugquem][chz]))
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(EstaQuemando[i] == 1)
				{
					SendClientMessage(playerid,Rojo,"Ya hay otra persona haciéndolo");
					return 1;
				}
			}
			quemando(playerid);
			return 1;		
		}
	}
	if(strcmp(cmd,"/cquem",true)==0)
	{
		if(EstaQuemando[playerid] == 1)
		{
			KillTimer(quemandotimer);
			EstaQuemando[playerid] = 0;
			ClearAnimations(playerid,1);
			return 1;
		}
	}
	if(strcmp(cmd,"/mis",true)==0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 0;
		format(string,sizeof(string),"EstaPintando %d, EstaEnMision %d, randlugpint %d,MisionFinalizada %d,ganadormis %d,nMision %d,MisionActiva %d,EstaQuemando %d,",EstaPintando[playerid], EstaEnMision[playerid], randlugpint,MisionFinalizada,ganadormis,numeromision,MisionActiva,EstaQuemando[playerid]);
		SendClientMessage(playerid,Amarillo,string);
		format(string,sizeof(string),"randlugquem %d,",randlugquem);
		SendClientMessage(playerid,Amarillo,string);
		return 1;
	}
	if(strcmp(cmd,"/lanzarm",true)==0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 0;
		KillTimer(timermisiones);
		TimerMisiones();
		timermisiones = SetTimer("TimerMisiones",3600000,1);
		return 1;
	}
	if(strcmp(cmd,"/mtaxi",true)==0)
	{
		if(PlayerInfo[playerid][pCheckpoint] > 0) { SendClientMessage(playerid,Rojo,"* Ya tienes un Checkpoint activo! Termina de hacer lo que tengas pendiente."); return 1;}
		if(EstaEnMisionTaxi[playerid] == 0)
		{
			MisionTaxi(playerid);
			EstaEnMisionTaxi[playerid] = 1;
		}
		return 1;
	}
	if(strcmp(cmd,"/aincendio",true)==0)
	{
		if(PlayerToPoint(15.0,playerid,LugaresQuemar[randlugquem-1][chx],LugaresQuemar[randlugquem-1][chy],LugaresQuemar[randlugquem-1][chz]))
		{
			if(PlayerInfo[playerid][pMember] == 2 && GetPlayerWeapon(playerid) == 42 && ApagandoI == 0)
			{
				SetTimerEx("AIncendio",10000,0,"i",playerid);
				ApplyAnimation(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,10000,1,1);
				GameTextForPlayer(playerid,"Apagando incendio",5000,1);
			}
			else{SendClientMessage(playerid,Naranja,"* No eres médico o no tienes un extintor");return 1;}
			return 1;
		}
		else{SendClientMessage(playerid,Rojo,"* Acercate más!"); return 1;}
	}
	return 0;	
}
MisBand_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 80)
	{
		if(EstaEnMision[playerid] == 1 || PlayerInfo[playerid][pMember] == 1)
		{
			DisablePlayerCheckpoint(playerid);
			for(new i=0; i < MAX_PLAYERS; i++)
			{
				if(PlayerInfo[i][pMember] == 1){ DisablePlayerCheckpoint(i);}
			}
			PlayerInfo[playerid][pCheckpoint] = 0;
			return 1;
		}
		if(EstaEnMisionTaxi[playerid] == 1)
		{
			numcheck[playerid]++;
			DisablePlayerCheckpoint(playerid);
			SendClientMessage(playerid,Verde,"Cliente: Muchas gracias!.");
			format(string,64,"Llevas %d/20 para conseguir el dinero extra",numcheck[playerid]);
			SendClientMessage(playerid,Blanco,string);
			if(numcheck[playerid] == 20){SendClientMessage(playerid,Verde,"Has ganado 125$ extra");SafeGivePlayerMoney(playerid,150);numcheck[playerid]=0;}
			PlayerInfo[playerid][pCheckpoint] = 0;
			MisionTaxi(playerid);
			return 1;
		}
	}
	return 1;
}
forward TimerMisiones();
public TimerMisiones()
{
	MisionFinalizada = 0;
	MensajeAPoliciaEnviado = 0;
	Delete3DTextLabel(LugaresPintar[randlugpint][chlabel]);
	randmis = random(2);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(11 <= PlayerInfo[i][pMember] <= 20 && EstaEnMision[i] == 0)
		{
			switch(randmis)
			{
				case 0:
				{
					numeromision = 1;
					//new NombreMensajeado[128];
					//GetPlayerName(i,NombreMensajeado,sizeof(NombreMensajeado));
					//format(string,sizeof(string),"%s recibe un mensaje al movil",NombreMensajeado);
					//ProxDetector(10.0,i,string,Morado,Morado,Morado,Morado,Morado);
					SendClientMessage(i,Amarillo,"SMS: Eh, tengo un trabajillo, necesito que marques un territorio con mi firma ¿te encargas?");
					SendClientMessage(i,Verde,"Si quieres aceptar la misión utiliza /mision aceptar. Si la quieres rechazar y que envíen otra más tarde /misión rechazar");
					MisionActiva = 1;
				}
				case 1:
				{
					numeromision = 2;
					//new NombreMensajeado[128];
					//GetPlayerName(i,NombreMensajeado,sizeof(NombreMensajeado));
					//SendClientMessage(i,Amarillo,"");
					//SendClientMessage(i,Amarillo,"");
					//format(string,sizeof(string),"%s recibe un mensaje al movil",NombreMensajeado);
					//ProxDetector(10.0,i,string,Morado,Morado,Morado,Morado,Morado);
					SendClientMessage(i,Amarillo,"SMS: Os necesito para un trabajo algo serio, debeis dejar un regalo a un amigo mio");
					SendClientMessage(i,Verde,"Si quieres aceptar la misión utiliza /mision aceptar. Si la quieres rechazar y que envíen otra más tarde /misión rechazar");
					MisionActiva = 1;
				}
			}
		}
		if(EstaEnMision[i] == 1)
		{
			PlayerInfo[i][pCheckpoint] = 0;
			DisablePlayerCheckpoint(i);
			KillTimer(pintadotimer);
			EstaEnMision[i] = 0;
			EstaPintando[i] = 0;
			EstaQuemando[i] = 0;
			SendClientMessage(i,Amarillo,"SMS: Así no llegaremos a ningún lado, Tienes que ser más rápido!");
			GameTextForPlayer(i,"~r~Has fallado la mision",5000,3);
		}
	}
	return 1;
}
MisBand_OnPlayerDisconnect(playerid)
{
	if(EstaEnMision[playerid] >= 0 || EstaEnMisionTaxi[playerid] >=0)
	{
		EstaEnMision[playerid] = 0;
		EstaEnMisionTaxi[playerid] = 0;
	}
	if(EstaPintando[playerid] == 1 || EstaQuemando[playerid] == 1)
	{
		KillTimer(pintadotimer);
		KillTimer(quemandotimer);
		EstaPintando[playerid] = 0;
		EstaQuemando[playerid] = 0;
	}

}
MisBand_OnPlayerDeath(playerid)
{
	if(EstaPintando[playerid] == 1 || EstaQuemando[playerid] == 1)
	{
		KillTimer(pintadotimer);
		KillTimer(quemandotimer);
		EstaPintando[playerid] = 0;
		EstaQuemando[playerid] = 0;
	}
}	
forward MisionSprayAceptada(playerid);
public MisionSprayAceptada(playerid)
{
	
	if(randlugpint <= MAX_LUGARESPINTAR && randlugpint == 0)
	{
	randlugpint = random(MAX_LUGARESPINTAR);
	LugaresPintar[randlugpint][chlabel] = CreateDynamic3DTextLabel("A pintar!", Amarillo, LugaresPintar[randlugpint][chx], LugaresPintar[randlugpint][chy], LugaresPintar[randlugpint][chz], 15.0);
	SetPlayerCheckpoint(playerid, LugaresPintar[randlugpint][chx], LugaresPintar[randlugpint][chy], LugaresPintar[randlugpint][chz], 8.0);
	SendClientMessage(playerid,Verde,"Misión aceptada, vamos a decorar las calles. Usa /graf para empezar y /cgraf para parar de pintar.");
	PlayerInfo[playerid][pCheckpoint] = 80;
	return 1;
	}
	if(randlugpint <= MAX_LUGARESPINTAR && randlugpint != 0)
	{
	LugaresPintar[randlugpint][chlabel] = CreateDynamic3DTextLabel("A pintar!", Amarillo, LugaresPintar[randlugpint][chx], LugaresPintar[randlugpint][chy], LugaresPintar[randlugpint][chz], 15.0);
	SetPlayerCheckpoint(playerid, LugaresPintar[randlugpint][chx], LugaresPintar[randlugpint][chy], LugaresPintar[randlugpint][chz], 8.0);
	SendClientMessage(playerid,Verde,"Misión aceptada, vamos a decorar las calles. Usa /graf para empezar y /cgraf para parar de pintar");
	PlayerInfo[playerid][pCheckpoint] = 80;
	}
	return 1;
}
forward pintando(playerid);
public pintando(playerid)
{
	new Float:x, Float:y, Float:z;
	EstaPintando[playerid] = 1;
	ApplyAnimation(playerid,"SPRAYCAN","spraycan_fire",4.1,1,1,1,1,22000,1);
	pintadotimer = SetTimerEx("pintado",21000,0,"d",playerid);
	GetPlayerPos(playerid,x,y,z);
	for(new i=0; i < MAX_PLAYERS; i++)
	{
		if((PlayerInfo[i][pMember] == 1 && PlayerInfo[i][pDuty] == 1) && MensajeAPoliciaEnviado == 0 && PlayerInfo[i][pCheckpoint] == 0)
		{
			checkspray = SetPlayerCheckpoint(i,x,y,z,20.0);
			PlayerInfo[i][pCheckpoint] = 80;
			SendClientMessage(i,Aguamarina,"[CENTRAL]: Hemos recibido varios avisos de ciudadanos, parece ser que una banda está decorando las calles");
			SendClientMessage(i,Aguamarina,"comprueba la siguiente posición");
		}
	}
	MensajeAPoliciaEnviado = 1;
	return 1;
}
forward pintado(playerid);
public pintado(playerid)
{
	ClearAnimations(playerid,1);
	DisablePlayerCheckpoint(checkspray);
	GameTextForPlayer(playerid,"~g~Has terminado de pintar, mision completada",5000,3);
	ganadormis = PlayerInfo[playerid][pMember];
	Delete3DTextLabel(LugaresPintar[randlugpint][chlabel]);
	EstaPintando[playerid] = 0;
	MensajeAPoliciaEnviado = 0;
	MisionFinalizada = 1;
	CreateDynamicObject(17969,LugaresPintar[randlugpint][chx],LugaresPintar[randlugpint][chy],LugaresPintar[randlugpint][chz],0,0,LugaresPintar[randlugpint][rZ],-1,-1,-1,200.0);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(11 <= PlayerInfo[i][pMember] && PlayerInfo[i][pMember] <= 20 && ganadormis == PlayerInfo[i][pMember] )
		{
			EstaEnMision[i] = 0;
			SendClientMessage(i,Amarillo,"SMS: Eso es, os vi haciendo el trabajo, sabía que no fallaríais...");
			SafeGivePlayerMoney(i,100);
		}
		else if(11 <= PlayerInfo[i][pMember] && PlayerInfo[i][pMember] <= 20 && ganadormis != PlayerInfo[i][pMember])
		{
			EstaEnMision[i] = 0;
			SendClientMessage(i,Amarillo,"SMS: Así no podeis continuar...");
			GameTextForPlayer(i,"~r~Has fallado la mision",5000,3);
		}
	}
	randlugpint++;
	MisionActiva = 0;
	return 1;
}
forward MisionQuemarAceptada(playerid);
public MisionQuemarAceptada(playerid)
{
	if(randlugquem <= MAX_LUGARESQUEMAR && randlugquem == 0)
	{
	randlugquem = random(MAX_LUGARESQUEMAR);
	SetPlayerCheckpoint(playerid, LugaresQuemar[randlugquem][chx], LugaresQuemar[randlugquem][chy], LugaresQuemar[randlugquem][chz], 8.0);
	SendClientMessage(playerid,Verde,"Misión aceptada, tienes un bidón de gasolina cerca del lugar marcado. Usa /quem para empezar y /cquem para parar el proceso.");
	PlayerInfo[playerid][pCheckpoint] = 80;
	return 1;
	}
	if(randlugquem <= MAX_LUGARESQUEMAR && randlugquem != 0)
	{
	SetPlayerCheckpoint(playerid, LugaresQuemar[randlugquem][chx], LugaresQuemar[randlugquem][chy], LugaresQuemar[randlugquem][chz], 8.0);
	SendClientMessage(playerid,Verde,"Misión aceptada, tienes un bidón de gasolina cerca del lugar marcado. Usa /quem para empezar y /cquem para parar el proceso.");
	PlayerInfo[playerid][pCheckpoint] = 80;
	}	
	return 1;
}
forward quemando(playerid);
public quemando(playerid)
{
	new Float:x, Float:y, Float:z;
	EstaQuemando[playerid] = 1;
	ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop",4.1,1,1,1,1,22000,1);
	quemandotimer = SetTimerEx("quemado",21000,0,"d",playerid);
	GetPlayerPos(playerid,x,y,z);
	for(new i=0; i < MAX_PLAYERS; i++)
	{
		if((PlayerInfo[i][pMember] == 1 || PlayerInfo[i][pMember] == 2) && MensajeAPoliciaEnviado == 0 && PlayerInfo[i][pDuty] == 1 && PlayerInfo[i][pCheckpoint] == 0)
		{
			checkspray = SetPlayerCheckpoint(i,x,y,z,20.0);
			PlayerInfo[i][pCheckpoint] = 80;
			SendClientMessage(i,Aguamarina,"[CENTRAL]: Hemos recibido varios avisos de ciudadanos, hay un indicio de incendio en la siguiente posición");
		}
	}
	MensajeAPoliciaEnviado = 1;
	return 1;
}
forward quemado(playerid);	
public quemado(playerid)
{
	ClearAnimations(playerid,1);
	DisablePlayerCheckpoint(checkspray);
	GameTextForPlayer(playerid,"~g~Has terminado de incendiar, mision completada",5000,3);
	ganadormis = PlayerInfo[playerid][pMember];
	EstaQuemando[playerid] = 0;
	MensajeAPoliciaEnviado = 0;
	MisionFinalizada = 1;
	DestroyDynamicObject(incendio);
	new Float:pxx,Float:pyy,Float:pzz;
	GetPlayerPos(playerid,pxx,pyy,pzz);
	incendio = CreateDynamicObject(LugaresQuemar[randlugquem][ido],pxx,pyy,pzz,0,0,0,-1,-1,-1,200.0);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(11 <= PlayerInfo[i][pMember] && PlayerInfo[i][pMember] <= 20 && ganadormis == PlayerInfo[i][pMember])
		{
			EstaEnMision[i] = 0;
			SendClientMessage(i,Amarillo,"SMS: En la radio estuvieron comentando que hubo un incendio, continuar así");
			SafeGivePlayerMoney(i,125);
		}
		else if(11 <= PlayerInfo[i][pMember] && PlayerInfo[i][pMember] <= 20 && ganadormis != PlayerInfo[i][pMember])
		{
			EstaEnMision[i] = 0;
			SendClientMessage(i,Amarillo,"SMS: No era tan difícil para hacer lo que habeis hecho...");
			GameTextForPlayer(i,"~r~Has fallado la mision",5000,3);
		}
	}
	randlugquem++;
	MisionActiva = 0;
	return 1;
}
forward MisionTaxi(playerid);
public MisionTaxi(playerid)
{
	randclient = random(24);
	clientcp[playerid] = SetPlayerCheckpoint(playerid,LugaresTaxi[randclient][tx],LugaresTaxi[randclient][ty],LugaresTaxi[randclient][tz],3);
	SendClientMessage(playerid,Blanco,"Cliente: Por favor, lléveme a la siguiente dirección.");
	PlayerInfo[playerid][pCheckpoint] = 80;
	return 1;
}
forward AIncendio(playerid);
public AIncendio(playerid)
{
	DestroyDynamicObject(incendio);
	SendClientMessage(playerid,Verde,"* Apagaste el incendio con éxito");
	ApagandoI = 0;
	return 1;
}