#include <a_samp>
#include <globalvars>
#include <colores>

#define MAX_TRABAJOS 11

new Float:Trabajos[MAX_TRABAJOS][3] = 
{
	{1771.7593,-1898.0857,13.5542},
	{1616.0564,-1896.6565,13.5490},
	{2195.7747,-1973.2986,13.5589},
	{2106.3269,-1789.8027,13.5608},
	{2182.8015,-2253.5034,14.7755},
	{376.5908,-2069.6064,7.8359},
	{-5.0203,67.6059,3.1172},
	{358.6638,163.1266,1008.3828},
	{358.7370,186.1769,1008.3828},
	{2481.3455,-1536.6989,24.1266},
	{2442.5952,-1981.2106,13.5469}
};

#define MAX_JOB_NPCS 14

enum npcEnum
{
	npcID,
	npcNombre[24],
	npcSkin,
	Float:npcX,
	Float:npcY,
	Float:npcZ,
	Float:npcA,
};

/*new NPCS[MAX_JOB_NPCS][npcEnum] = 
{
	{499, "Pizzero", 155,2106.2314,-1790.5963,13.5608,357.1692},
	{498, "Basurero", 160,2195.8167,-1971.3378,13.7841,180.5366},
	{497, "LimpiaCalles", 153,1614.7932,-1897.5802,13.5489,3.0778},
	{496, "Mecanico", 50,1770.2878,-1898.0068,13.5649,271.3742},
	{495, "Repartidor", 16,2181.8650,-2252.4397,14.7734,226.1167},
	{494, "Granja", 161,-5.8006,66.4755,3.1172,248.3381},
	{493, "Ayunta1", 150,356.3014,163.2031,1008.3762,272.0776},
	{492, "Ayunta2", 216,356.2979,186.1871,1008.3762,270.8242},
	{491, "Ayunta3", 219,359.7139,173.6342,1008.3893,271.1376},
	{490, "Pescador", 168,375.2784,-2069.6086,7.8359,271.7828},
	{489, "Vendedor", 220,2481.2000,-1535.1279,24.1241,271.3365},
	{488, "Ladron", 33,2440.7009,-1981.6567,13.5469,302.3100},
	{487, "Escuela", 17,1488.7009,1305.4723,1093.2964,272.5827},
	{486, "Salchichas", 209,1195.7719,-1729.1204,13.5689,229.5068}
};*/

Trabajos_OnInit()
{
	for(new i; i < MAX_TRABAJOS; i++)
	{
		CreateDynamic3DTextLabel("Puesto de Trabajo", Verde, Trabajos[i][0], Trabajos[i][1], Trabajos[i][2] + 0.2, 35);
		CreateDynamic3DTextLabel("Usa /trabajo para más información", Gris, Trabajos[i][0], Trabajos[i][1], Trabajos[i][2], 35);
		CreateDynamicPickup(1274, 23, Trabajos[i][0], Trabajos[i][1], Trabajos[i][2]);
	}
	
/*	for(new i; i < MAX_JOB_NPCS; i++)
	{
		CreateNPC(NPCS[i][npcID], NPCS[i][npcNombre]);
		SetSpawnInfo(NPCS[i][npcID], 0, NPCS[i][npcSkin], NPCS[i][npcX], NPCS[i][npcY], NPCS[i][npcZ], NPCS[i][npcA], 0,0,0,0,0,0);
		SpawnNPC(NPCS[i][npcID]);
		SetPlayerColor(NPCS[i][npcID], 0xFFFFFF00);
		SetNPCFacingAngle(NPCS[i][npcID], NPCS[i][npcA]);
	}*/
}

Trabajos_OnPlayerCommandText(playerid, cmdtext[])
{
	if(strcmp(cmdtext, "/trabajo", true) == 0)
	{
		new trabajo = -1;
		for(new i; i < MAX_TRABAJOS; i++)
		{
			if(PlayerToPoint(5.0, playerid, Trabajos[i][0], Trabajos[i][1], Trabajos[i][2]))
			{
				trabajo = i;
				break;
			}
		}
		
		switch(trabajo)
		{
			case -1:
			{
				return 1;
			}
			case 0:
			{
				if(GetPlayerLevel(playerid) < 3){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 3))"); return 1;}
				SendClientMessage(playerid, Amarillo, "Bienvenido a los antiguos talleres industriales de Los Santos. Ahora que hemos tenido que cerrar, estamos");
				SendClientMessage(playerid, Amarillo, "buscando mecánicos profesionales que puedan reparar vehículos a domicilio, con el tiempo ofrecemos");
				SendClientMessage(playerid, Amarillo, "cursillos para repostar, repintar e incluso customizar vehículos. El sueldo base es de 250$ por hora más lo");
				SendClientMessage(playerid, Amarillo, "que ganes por tu cuenta, y el horario mínimo del contrato son 6 horas. ¿Te interesa?");
				PlayerInfo[playerid][pOferta] = 1;
			}
			case 1:
			{
				SendClientMessage(playerid, Amarillo, "Hola, bienvenido al servicio municipal de limpieza. Estamos buscando profesionales que matengan la");
				SendClientMessage(playerid, Amarillo, "suciedad lejos de nuestras calles. El sueldo base es de 100$ por hora más lo que ganes por tu cuenta en cada");
				SendClientMessage(playerid, Amarillo, "ruta, y el horario mínimo del contrato son 6 horas. ¿Qué me dices, te interesa?");
				PlayerInfo[playerid][pOferta] = 4;
			}
			case 2:
			{
				if(GetPlayerLevel(playerid) < 4){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 4))"); return 1;}
				SendClientMessage(playerid, Amarillo, "Hey, bienvenido al vertedero municipal. Necesitamos a gente como tú que recoja la basura y mantenga");
				SendClientMessage(playerid, Amarillo, "limpia la ciudad para que no huela a rayos. El sueldo base es de 100$ por hora más lo que ganes por tu");
				SendClientMessage(playerid, Amarillo, "cuenta en cada ruta, y el horario mínimo del contrato son 6 horas. ¿Aceptas o no? Vamos, que hay prisa.");
				PlayerInfo[playerid][pOferta] = 5;
			}
			case 3:
			{
				SendClientMessage(playerid, Amarillo, "Bienvenido a Pizza Stack. Disponemos de scooters, pero los pedidos no dan abasto, ahora mismo estamos");
				SendClientMessage(playerid, Amarillo, "buscando nuevos empleados. El sueldo base es de 100$ por hora más lo que ganes por tu cuenta, y el horario");
				SendClientMessage(playerid, Amarillo, "mínimo del contrato son 6 horas. ¿Estás interesado?");
				PlayerInfo[playerid][pOferta] = 6;
			}
			case 4:
			{
				if(GetPlayerLevel(playerid) < 6){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 6))"); return 1;}
				SendClientMessage(playerid, Amarillo, "Hola, bienvenido a la central de repartos. Nosotros distribuímos productos de todo tipo a todos los negocios");
				SendClientMessage(playerid, Amarillo, "de Los Santos, pero ahora mismo estamos escasos de personal. El sueldo base es de 100$ por hora más lo que"); 
				SendClientMessage(playerid, Amarillo, "ganes por tu cuenta, y el horario mínimo del contrato son 6 horas. ¿Quieres empezar ya? Tenemos algo de");
				SendClientMessage(playerid, Amarillo, "prisa...");
				PlayerInfo[playerid][pOferta] = 7;
			}
			case 5:
			{
				if(GetPlayerLevel(playerid) < 4){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 4))"); return 1;}
				SendClientMessage(playerid, Amarillo, "Bievenido al muelle de pesca, grumete. Si te interesa, estamos buscando pescadores que lleven sus capturas");
				SendClientMessage(playerid, Amarillo, "al puerto, la cantidad no importa, pagamos al peso. El sueldo base es de...bueno, no hay sueldo base, solo");
				SendClientMessage(playerid, Amarillo, "ganarás lo que obtengas trabajando, y el horario mínimo del contrato son 6 horas. ¿Qué me dices, te");
				SendClientMessage(playerid, Amarillo, "interesa?");
				PlayerInfo[playerid][pOferta] = 3;
			}
			case 6:
			{
				if(GetPlayerLevel(playerid) < 4){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 4))"); return 1;}
				SendClientMessage(playerid, Amarillo, "¡Yépale! ¿Eres de por aquí? Bueno, igualmente necesitamos gente con tractor propio y ganas de trabajar. No");
				SendClientMessage(playerid, Amarillo, "pagamos extras, solo ganarás lo que obtengas trabajando, y el horario mínimo del contrato son 6 horas.");
				SendClientMessage(playerid, Amarillo, "¿Tienes lo que hay que tener para este trabajo?");
				PlayerInfo[playerid][pOferta] = 2;
			}
			case 7:
			{
				if(GetPlayerLevel(playerid) < 4){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 4))"); return 1;}
				SendClientMessage(playerid, Amarillo, "Bievenido al ayuntamiento de Los Santos. Si lo desea, ofrecemos licencias oficiales de investigador privado.");
				SendClientMessage(playerid, Amarillo, "El sueldo base es de 500$ la hora, sin contar sus propias tarifas. El horario mínimo del contrato son 6 horas.");
				SendClientMessage(playerid, Amarillo, "¿Comenzamos con el papeleo?");
				PlayerInfo[playerid][pOferta] = 9;
			}
			case 8:
			{
				if(GetPlayerLevel(playerid) < 3){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 3))"); return 1;}
				SendClientMessage(playerid, Amarillo, "Bievenido al ayuntamiento de Los Santos. Si lo desea, puede trabajar para el estado ofreciendo seguros");
				SendClientMessage(playerid, Amarillo, "gubernamentales para vehículos de cualquier clase. El sueldo base es de 300$ la hora, sin contar sus propias");
				SendClientMessage(playerid, Amarillo, "tarifas. El horario mínimo del contrato son 6 horas. ¿Comenzamos con el papeleo?");
				PlayerInfo[playerid][pOferta] = 10;
			}
			case 9:
			{
				SendClientMessage(playerid, Amarillo, "Eh, ¿quieres trabajo? Tengo algunos camiones, pero no tengo conductores, solo tienes que ir a los puntos de");
				SendClientMessage(playerid, Amarillo, "venta y esperar a que vengan clientes. Te pago 100 la hora más lo que saques con las ventas y el horario");
				SendClientMessage(playerid, Amarillo, "mínimo del contrato son 6 horas. ¿Te hace?");
				PlayerInfo[playerid][pOferta] = 8;
			}
			case 10:
			{
				if(GetPlayerLevel(playerid) < 4){SendClientMessage(playerid,Amarillo,"No cumples los requisitos para el puesto de trabajo ((nivel 4))"); return 1;}
				SendClientMessage(playerid, Amarillo, "¡Ey, tú! ¿Quieres sacarte unos pavos? No es del todo legal pero... Bueno, se trata de conseguir mercancía y");
				SendClientMessage(playerid, Amarillo, "entregársela a mi colega de la tienda de empeños, con el tiempo si consigues algún cacharro decente... tengo");
				SendClientMessage(playerid, Amarillo, "contactos en talleres ilegales. Yo no voy a darte un centavo, pero mi colega te pagará bien por la mercancía");
				SendClientMessage(playerid, Amarillo, "que le lleves. Eso sí, mantente al menos 6 horas en el ajo o no hay trato. ¿Te interesa o que? No tengo todo el");
				SendClientMessage(playerid, Amarillo, "día.");
				PlayerInfo[playerid][pOferta] = 11;
			}
		}
		SendClientMessage(playerid, Gris, "Utiliza /aceptar trabajo para continuar con el contrato de 6 horas.");
		return 1;
	}
	
	if(strcmp(cmdtext, "/dejartrabajo", true) == 0)
	{
		if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pContrato] == 0)
		{
			if(PlayerInfo[playerid][pTrabajando] > 0) { SendClientMessage(playerid, Rojo, "* No puedes abandonar el trabajo mientras estás trabajando."); return 1;}
			PlayerInfo[playerid][pJob] = 0;
			PlayerInfo[playerid][pContrato] = 0;
			PlayerInfo[playerid][pUniforme] = 0;
			SendClientMessage(playerid, Amarillo, "Has abandonado el trabajo anterior.");
			SaveValue(playerid, "Uniforme", 0);
			SaveValue(playerid, "Trabajo", 0);
			SaveValue(playerid, "Contrato", 0);
			if(PlayerInfo[playerid][pDuty] == 1)
			{
				PlayerInfo[playerid][pDuty] = 0;
				SaveValue(playerid, "EnServicio", PlayerInfo[playerid][pDuty]);
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			}
		}
		else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pContrato] != 0)
		{
			format(string, 128, "No puedes abandonar el trabajo ahora. Tu contrato termina en %d horas.", PlayerInfo[playerid][pContrato]);
			SendClientMessage(playerid, AzulClaro, string);
		}
		return 1;
	}
	return 0;
}
