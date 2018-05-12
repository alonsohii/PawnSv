#include <a_mysql>
#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>
#include <deathac>
#include <radios>
#include <sirenas>

enum ConceInfo
{
	Float:cX,
	Float:cY,
	Float:cZ,
	Float:ctX,
	Float:ctY,
	Float:ctZ,
	cNombre[128],
}

new Concesionarios[7][ConceInfo] = {
	{2131.4873,-1148.9374,24.3184, 2126.2341,-1132.8004,25.2141, "Rusty Rides"},
	{303.6850,-226.6397,1.5781, 315.0065,-236.6873,1.2767, "Heavy Weight Trucks"},
	{1328.4136,-1558.3014,13.5469, 1340.1494,-1567.3983,13.2519, "Gentlemen Cars"},
	{2281.5684,-2364.5156,13.5469, 2271.9656,-2349.9148,13.2524, "Import Street Angels"},
	{521.2985,-1293.2179,17.2422, 528.4189,-1288.0062,17.0149, "Luxury Vehicles & Co."},
	{1952.8345,-2179.1643,13.5469, 1979.9656,-2316.4849,13.3186, "Flying Stars Planes"},
	{732.8066,-1476.6700,5.4688, 728.8990,-1503.9154,0.0934, "Seaside Boats"}
};
new PConcesionario[MAX_PLAYERS];


enum datos_del_coche
{
	dcCategoria,
	dcNombre[30],
	dcIDModel,
	dcPrecio,
	dcMember, // código de facción para uso
	dcComprador, // código del comprador
	dcConcesionario, // Concesionario
	dcNivel,
}

#define MAX_CAR_DATA 100
#define FACCION_CIUDADANO 0
#define FACCION_POLICIA 1

new datacar[MAX_CAR_DATA][datos_del_coche] = {
      /* TARTANAS GAMA CHUNGA */

      {0, "Glendale", 466, 5000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Oceanic", 467, 5000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Clover", 542, 4000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Tampa", 549, 4000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Walton", 478, 4000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Sadler", 543, 5000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Esperanto", 419, 7000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Buccaneer", 518, 9000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Blista", 496, 6000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Perennial", 404, 5000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},
      {0, "Regina", 479, 5000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,1},

      /* LOWRIDERS / OTROS */

      {0, "Voodoo", 412, 35000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Remington", 534, 39000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Tahoma", 566, 45000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,2},
      {0, "Majestic", 517, 37000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,2},
      {0, "Tornado", 576, 35000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Broadway", 575, 45000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Savanna", 567, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Slamvan", 535, 45000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Blade", 536, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},
      {0, "Stallion", 439, 60000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,2},
      {0, "Phoenix", 603, 70000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,4},
      {0, "Hermes", 474, 80000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,4},
      {0, "Sabre", 475, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 1,3},

      /* FRAGONETAS Y CURROS */

      {0, "Tractor", 531, 3000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,1},
      {0, "Benson", 499, 12000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,1},
      {0, "Moonbeam", 418, 15000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,1},
      {0, "Bobcat", 422, 20000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,1},
      {0, "Pony", 413, 17000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,2},
      {0, "Rumpo", 440, 25000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,2},
      {0, "Picador", 600, 35000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,3},
      {0, "Burrito", 482, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,3},
      {0, "Yosemite", 554, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,3},
      {0, "Camper", 483, 60000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,4},
	  {0, "Quad", 471, 55000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,12},

      /* 4x4 */

      {0, "Rancher", 489, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,2},
      {0, "Landstalker", 400, 180000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,3},
      {0, "Huntley", 579, 200000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,5},
      {0, "Towtruck", 525, 25000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,2},
      {0, "Mesa", 500, 80000, FACCION_CIUDADANO, FACCION_CIUDADANO, 2,3},


      /* BERLINAS */

      {0, "Greenwood", 492, 40000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,1},
      {0, "Virgo", 491, 35000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,1},
      {0, "Willard", 529, 10000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,1},
      {0, "Manana", 410, 13000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,1},
      {0, "Bravura", 401, 25000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,1},
      {0, "Previon", 436, 26000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,1},
      {0, "Primo", 547, 38000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Emperor", 585, 41000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Nebula", 516, 39500, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Sunrise", 550, 43000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Intruder", 546, 48000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Vincent", 540, 45000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Fortune", 526, 43000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Cadrona", 527, 46000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,2},
      {0, "Premier", 426, 80000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,3},
      {0, "Merit", 551, 70000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,3},
      {0, "Sentinel", 405, 120000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,5},
      {0, "Washington", 421, 130000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,5},
      {0, "Admiral", 445, 140000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,5},
      {0, "Elegant", 507, 150000, FACCION_CIUDADANO, FACCION_CIUDADANO, 3,5},

      /* STREET RACERS */

      {0, "Flash", 565, 40000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,3},
      {0, "Club", 589, 30000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,3},
      {0, "Stratum", 561, 80000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,3},
      {0, "Alpha", 602, 80000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,3},
      {0, "Uranus", 558, 90000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,3},
      {0, "Euros", 587, 90000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,4},
      {0, "Jester", 559, 110000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,5},
      {0, "ZR-350", 477, 110000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,5},
      {0, "Buffalo", 402, 120000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,6},
      {0, "Elegy", 562, 160000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,6},
      {0, "Sultan", 560, 200000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,6},
      {0, "SuperGT", 506, 250000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,8},
      {0, "Infernus", 411, 300000, FACCION_CIUDADANO, FACCION_CIUDADANO, 4,8},

      /* COSTE ELEVADO */

      {0, "Journey", 508, 100000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,5},
      {0, "Hustler", 545, 120000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,5},
      {0, "Windsor", 555, 200000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,5},
      {0, "Feltzer", 533, 250000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,5},
      {0, "Stafford", 580, 400000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,8},
      {0, "Stretch", 409, 800000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,8},

      /* MOTOS */

      {1, "Freeway", 463, 25000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,4},
      {1, "Wayfarer", 586, 27000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,4},
      {1, "Sanchez", 468, 50000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,5},
      {1, "BF-400", 581, 60000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,6},
      {1, "FCR-900", 521, 150000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,8},

      /* SUPERCARS */

      {0, "Comet", 480, 800000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,8},
      {0, "Banshee", 429, 900000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,8},
      {0, "Bullet", 541, 900000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,8},
      {0, "Cheetah", 415, 1200000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,10},
      {0, "Turismo", 451, 1500000, FACCION_CIUDADANO, FACCION_CIUDADANO, 5,10},

      /* AERONAVES */

      {2, "Maverick", 487, 1000000, FACCION_CIUDADANO, FACCION_CIUDADANO, 6,10},
      {2, "Dodo", 593, 700000, FACCION_CIUDADANO, FACCION_CIUDADANO, 6,10},
      {2, "Shamal", 519, 2000000, FACCION_CIUDADANO, FACCION_CIUDADANO, 6,10},
      {2, "Skimmer", 460, 750000, FACCION_CIUDADANO, FACCION_CIUDADANO, 6,10},
      {2, "Beagle", 511, 1000000, FACCION_CIUDADANO, FACCION_CIUDADANO, 6,10},

      /* BARCOS */

      {3, "Reefer", 453, 60000, FACCION_CIUDADANO, FACCION_CIUDADANO, 7,1},
      {3, "Tropic", 454, 800000, FACCION_CIUDADANO, FACCION_CIUDADANO, 7,8},
      {3, "Squalo", 446, 500000, FACCION_CIUDADANO, FACCION_CIUDADANO, 7,5},
      {3, "Speeder", 452, 200000, FACCION_CIUDADANO, FACCION_CIUDADANO, 7,5},
      {3, "Jetmax", 493, 280000, FACCION_CIUDADANO, FACCION_CIUDADANO, 7,8},
      {3, "Marquis", 484, 600000, FACCION_CIUDADANO, FACCION_CIUDADANO, 7,8}

};

new TimerConce = 0; // Timer para no comprar vehiculo muy seguido o a la vez
new Refueling[MAX_PLAYERS];
new trunkTimer[MAX_PLAYERS];
new Maletero[MAX_VEHICLES];
new EnCatalogoVeh[MAX_PLAYERS]; // modelo consultado por jugador en catálogo de coches
new VehCatalogo[MAX_PLAYERS]; // vehicle id generado por samp
new PlayerTmr[MAX_PLAYERS]; // Timer para hacer recon sobre los vehículos de un jugador
new Text:Nombre[MAX_CAR_DATA];
new Text:Costo[MAX_CAR_DATA];
new Text:Id[MAX_CAR_DATA];
new Recolocarcoches[MAX_VEHICLES]; // indica qué coches están ocupados cuando se ejecuta la orden de recolocar coches (corregir sincronización)
new PlayerText3D:CarText[MAX_PLAYERS][MAX_VEHICLES];
new TextToggle[MAX_PLAYERS];
new LocalizandoVehiculo[MAX_PLAYERS];

stock IsAPlane(carid)
{
	new M =GetVehicleModel(carid);
	if(M == 592 || M == 577 || M == 511 || M == 548 || M == 512 || M == 593 || M == 425 || M == 417 || M == 487 || M == 553){return 1;}
	if(M == 488 || M == 497 || M == 563 || M == 476 || M == 447 || M == 519 || M == 460 || M == 469 || M == 513 || M == 520){return 1;}
	return 0;
}

stock IsABoat(tmpcar)
{
	new M = GetVehicleModel(tmpcar);
	if(M == 472 || M == 473 || M == 493 || M == 595 || M == 484 || M == 430 || M == 453 || M == 452 || M == 446 || M == 454){return 1;}
	return 0;
}

stock IsAHarvestor(carid)
{
	new M = GetVehicleModel(carid);
	if(M == 532){return 1;}
    return 0;
}

stock IsATaxi(carid)
{
	if(GetVehicleModel(carid) == 438 || GetVehicleModel(carid) == 420) { return 1; }
	return 0;
}

stock IsACopCar(carid)
{
	if(CarInfo[carid][cUsos] == 1) return 1;
	return 0;
}

stock IsADeliveryCar(carid)
{
	if(GetVehicleModel(carid) == 562){return 1;}
    return 0;
}

stock IsANewsVan(carid)
{
	if(GetVehicleModel(carid) == 582)
	{
	    return 1;
	}
	return 0;
}

stock IsATowTruck(carid)
{
	if(GetVehicleModel(carid) == 525)
	{
	    return 1;
	}
	return 0;
}

stock IsAnAmbulance(carid)
{
	if(CarInfo[carid][cUsos] == 4) return 1;
	return 0;
}


stock IsAMotorcycle (tmpcar)
{
	new M;
	M = GetVehicleModel(CarInfo[tmpcar][cId]);
	if (M == 462 || M == 463)
	    return 1;
	return 0;
}

stock IsABike (tmpcar)
{
	new M;
	M = GetVehicleModel(CarInfo[tmpcar][cId]);
	if (M == 510 || M == 481 || M == 509)
	    return 1;
	return 0;
}

stock IsATrashTruck(carid)
{
	new model = GetVehicleModel(carid);
 	if(model == 408)
	{
		return 1;
	}
	return 0;
}

stock IsABus(carid)
{
	new M = GetVehicleModel(carid);
	if(M == 431 || M == 437){return 1;}
	return 0;
}

stock IsASweeper(carid)
{
	new M = GetVehicleModel(carid);
	if(M == 574) return 1;
	return 0;
}

stock IsAChopper(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	if(model == 497) // < Define your Chopper ID's Here
	{
		return 1;
	}
	return 0;
}

LoadCar()
{
	new VehStatus, VehPark;
    new ccount;
	new sql[80], row[512];
	format(sql, sizeof(sql), "SELECT id FROM cars ORDER BY id DESC");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	ccount = strval(row);

    TotalVeh = 0;
    CodigoLlave = 0;

    new idx=-1;
    for (new id = 0; id<ccount; id++)
	{
		format(sql, sizeof(sql), "SELECT * FROM cars WHERE id=%d LIMIT 1", id+1);
		mysql_query(sql);
		mysql_store_result();
		if (mysql_num_rows() == 0)  continue; // No existe coche con esa id: volvemos arriba del bucle
		mysql_fetch_row(row);
		split(row, arrCoords, '|');
        
        
		VehStatus = strval(arrCoords[23]);
		VehPark = strval(arrCoords[25]);
		
		if(VehStatus == -1 && VehPark == -1)
		{
			VehStatus = 0;
			format(sql, 200, "UPDATE cars SET eliminado=0 WHERE id = %d LIMIT 1", id+1);
			mysql_query(sql);
		}
		else if(VehStatus == -1 && VehPark == 0)
		{
			VehStatus = 0;
			format(sql, 200, "UPDATE cars SET eliminado=0 WHERE id = %d LIMIT 1", id+1);
			mysql_query(sql);
		}
		
	    if(VehStatus < 1)  //No eliminado
		{
            TotalVeh ++;
            idx++;
			CarInfo[idx][cSQLID] = strval(arrCoords[0]);
			CarInfo[idx][cCarKey] = strval(arrCoords[1]);
			CarInfo[idx][cModel] = strval(arrCoords[2]);
			CarInfo[idx][cLocationx] = floatstr(arrCoords[3]);
			CarInfo[idx][cLocationy] = floatstr(arrCoords[4]);
			CarInfo[idx][cLocationz] = floatstr(arrCoords[5]);
			CarInfo[idx][cAngle] = floatstr(arrCoords[6]);
			CarInfo[idx][cColorOne] = strval(arrCoords[7]);
			CarInfo[idx][cColorTwo] = strval(arrCoords[8]);
			format(CarInfo[idx][cOwner], 24, "%s", arrCoords[9]);
			format(CarInfo[idx][cDescription], 24, "%s", arrCoords[10]);
			CarInfo[idx][cValue] = strval(arrCoords[11]);
			CarInfo[idx][cUsos] = strval(arrCoords[12]);
			CarInfo[idx][cOwned] = strval(arrCoords[13]);
			CarInfo[idx][cLock] = strval(arrCoords[14]);
			CarInfo[idx][cStarted] = strval(arrCoords[15]);
			CarInfo[idx][cBroken] = strval(arrCoords[16]);
			CarInfo[idx][cGas] = strval(arrCoords[17]);
			format(CarInfo[idx][cDrogas],128,"%s",arrCoords[18]);
			format(CarInfo[idx][cSlots],128,"%s",arrCoords[19]);
			format(CarInfo[idx][cAmmos],128,"%s",arrCoords[20]);
			format(CarInfo[idx][cComponentes], 256, "%s", arrCoords[21]);
			CarInfo[idx][cPaintJob] = strval(arrCoords[22]); // PJ -
			CarInfo[idx][eliminado] = VehStatus;
			CarInfo[idx][horas] = strval(arrCoords[24]);
			CarInfo[idx][cParking] = strval(arrCoords[25]);
			format(CarInfo[idx][cDanos],40,"%s",arrCoords[26]);
			format(CarInfo[idx][cRadios],40,"%s",arrCoords[27]);
			CarInfo[idx][cVw] = strval(arrCoords[28]);
			CarInfo[idx][cInt] = strval(arrCoords[29]);
			CarInfo[idx][cSeguro] = strval(arrCoords[30]);
			CarInfo[idx][cSirena] = strval(arrCoords[31]);
			CarInfo[idx][cKms] = floatstr(arrCoords[32]);
			CarInfo[idx][cIntermitentesTmr] = NOEXISTE;
            
			// Creación del coche por samp y asignación de configuración (color, matrícula y tuning)
			if(CarInfo[idx][eliminado] != -1)
			{
				CarInfo[idx][cId] = CreateVehicle (CarInfo[idx][cModel], CarInfo[idx][cLocationx], CarInfo[idx][cLocationy], CarInfo[idx][cLocationz], CarInfo[idx][cAngle], CarInfo[idx][cColorOne], CarInfo[idx][cColorTwo], 3000000);
				if(CarInfo[idx][cInt] > 0)
				{
					LinkVehicleToInterior(CarInfo[idx][cId], CarInfo[idx][cInt]);
				}
				if(CarInfo[idx][cVw] > 0)
				{
					SetVehicleVirtualWorld(CarInfo[idx][cId], CarInfo[idx][cVw]);
				}
			}
		

			if(CarInfo[idx][cUsos] > 0)
			{
				CarInfo[idx][cTmpx] = CarInfo[idx][cLocationx];
				CarInfo[idx][cTmpy] = CarInfo[idx][cLocationy];
				CarInfo[idx][cTmpz] = CarInfo[idx][cLocationz];
				CarInfo[idx][cTmpa] = CarInfo[idx][cAngle];
			}
			ChangeVehiclePaintjob(CarInfo[idx][cId], CarInfo[idx][cPaintJob]);
		
			new Armas[MAX_TRUNK_SLOTS][10];
			new Ammos[MAX_TRUNK_SLOTS][10];
			split(CarInfo[idx][cSlots],Armas,',');
			split(CarInfo[idx][cAmmos],Ammos,',');
			for(new i = 0; i < MAX_TRUNK_SLOTS; i++)
			{
				CarInfo[idx][cSlot][i] = strval(Armas[i]);
				CarInfo[idx][cAmmo][i] = strval(Ammos[i]);
			}

            new Drogas[7][10];
			split(CarInfo[idx][cDrogas],Drogas,',');
            CarInfo[idx][cSemillas][0] = strval(Drogas[0]);
            CarInfo[idx][cDrogaNP][0] = strval(Drogas[1]);
            CarInfo[idx][cDrogaP][0] = strval(Drogas[2]);
            CarInfo[idx][cSemillas][1] = strval(Drogas[3]);
            CarInfo[idx][cDrogaNP][1] = strval(Drogas[4]);
            CarInfo[idx][cDrogaP][1] = strval(Drogas[5]);
            CarInfo[idx][cDrogaP][2] = strval(Drogas[6]);
            

			new Comp[14][10];
			split(CarInfo[idx][cComponentes],Comp,',');
			for(new i = 0; i < 14; i++)
			{
				CarInfo[idx][cComp][i] = strval(Comp[i]);
				if(CarInfo[idx][cComp][i] > 0)	AddVehicleComponent(CarInfo[idx][cId], CarInfo[idx][cComp][i]);
			}
			new Partes[5][10];
			split(CarInfo[idx][cDanos],Partes,',');
			for(new i = 0; i < 5; i++)
			{
				if(i == 4)
				{
					if(floatstr(Partes[i]) > 300.0)
					{
						CarInfo[idx][cDamage] = floatstr(Partes[i]);
					}
					else
					{
						CarInfo[idx][cDamage] = 301;
					}
				}
				else
				{
					CarInfo[idx][cDano][i] = strval(Partes[i]);
				}
			}
			UpdateVehicleDamageStatus(CarInfo[idx][cId],CarInfo[idx][cDano][0],CarInfo[idx][cDano][1],CarInfo[idx][cDano][2],CarInfo[idx][cDano][3]);
			SetVehicleHealth(CarInfo[idx][cId], CarInfo[idx][cDamage]);
			
			new RadiosP[3][10];
			split(CarInfo[idx][cRadios],RadiosP,',');
			for(new i = 0; i < 3; i++)
			{
				if(i == 0)
					CarInfo[idx][cEmisora] = strval(RadiosP[0]);
				
				else if(i == 1)
					CarInfo[idx][cVolumen] = strval(RadiosP[1]);
				
				else if(i == 2)
					CarInfo[idx][cEquipo] = strval(RadiosP[2]);
			}

            CarInfo[idx][cGPS]=-1;
            
			new Matricula[32];
			format(Matricula,sizeof(Matricula),"LS-%d",CarInfo[idx][cCarKey]);
			SetVehicleNumberPlate(CarInfo[idx][cId],Matricula);
			
			if (CarInfo[idx][cCarKey] >= CodigoLlave)
				CodigoLlave = CarInfo[idx][cCarKey] + 1;
				
			IsSpu[idx] = CarInfo[idx][cSirena];
			Lamp[idx] = 0;
				
			
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(CarInfo[idx][cId], engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(CarInfo[idx][cId], CarInfo[idx][cStarted], false, false, CarInfo[idx][cLock], false, false, false);
		}
	}
	mysql_free_result();
	printf("Coches cargados: %d (MAX: %d)", TotalVeh, MAX_VEHICLES);
	return 1;
}

LoadLLLCar(idx)
{
	// Creación del coche por samp y asignación de configuración (color, matrícula y tuning)
	new park;
	for(new i; i < MAX_PARKINGS; i++)
	{
		if(CarInfo[idx][cParking] == ParkInfo[i][paSQLID])
		{
			park = i;
			break;
		}
	}
	CarInfo[idx][cId] = CreateVehicle (CarInfo[idx][cModel], ParkInfo[park][paX], ParkInfo[park][paY], ParkInfo[park][paZ], CarInfo[idx][cAngle], CarInfo[idx][cColorOne], CarInfo[idx][cColorTwo], 3000000);
	
	ChangeVehiclePaintjob(CarInfo[idx][cId], CarInfo[idx][cPaintJob]);
	new Comp[14][10];
	split(CarInfo[idx][cComponentes],Comp,',');
	for(new i = 0; i < 14; i++)
	{
		CarInfo[idx][cComp][i] = strval(Comp[i]);
		if(CarInfo[idx][cComp][i] > 0)	AddVehicleComponent(CarInfo[idx][cId], CarInfo[idx][cComp][i]);
	}
	
	new Partes[5][10];
	split(CarInfo[idx][cDanos],Partes,',');
	for(new i = 0; i < 5; i++)
	{
		if(i == 4)
		{
			CarInfo[idx][cDamage] = floatstr(Partes[i]);
		}
		else
		{
			CarInfo[idx][cDano][i] = strval(Partes[i]);
		}
	}
	
	if (CarInfo[idx][cCarKey] >= CodigoLlave)
	{
		CodigoLlave = CarInfo[idx][cCarKey] + 1;
	}
	
	CarInfo[idx][eliminado] = 0;
	CarInfo[idx][horas] = 1;
	CarInfo[idx][cIntermitentesTmr] = NOEXISTE;
	
	new sql[200];
	format(sql, 200, "UPDATE cars SET eliminado=0 WHERE id = %d LIMIT 1", CarInfo[idx][cSQLID]);
	mysql_query(sql);
	
	UpdateVehicleDamageStatus(CarInfo[idx][cId],CarInfo[idx][cDano][0],CarInfo[idx][cDano][1],CarInfo[idx][cDano][2],CarInfo[idx][cDano][3]);
	SetVehicleHealth(CarInfo[idx][cId], CarInfo[idx][cDamage]);
	
	new Matricula[32];
	format(Matricula,sizeof(Matricula),"LS-%d",CarInfo[idx][cCarKey]);
	SetVehicleNumberPlate(CarInfo[idx][cId],Matricula);
	
	
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[idx][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(CarInfo[idx][cId], CarInfo[idx][cStarted], false, false, CarInfo[idx][cLock], false, false, false);

	SaveCar(idx);
	
	return 1;
}

Vehicles_OnVehicleDeath(vehicleid, killerid)
{
	#pragma unused killerid
	for (new contador = 0; contador < TotalVeh; contador++)
	if (CarInfo[contador][cId] == vehicleid)
	{
		if(CarInfo[contador][cUsos] != 0) continue;
		if(CarInfo[contador][cIntermitentesTmr] != NOEXISTE)
		{
			KillTimer(CarInfo[contador][cIntermitentesTmr]);
			CarInfo[contador][cIntermitentesTmr] = NOEXISTE;
		}
		for(new parking; parking < MAX_PARKINGS; parking++)
		{
			if(ParkInfo[parking][paType] == 3)
			{
				CarInfo[contador][cParking] = ParkInfo[parking][paSQLID];
				CarInfo[contador][horas] = 69;
				CarInfo[contador][cStarted] = 0;
				ParkInfo[parking][paTotal]++;
				SaveParking(parking);
				RepairVehicle(CarInfo[contador][cId]);
				SaveCar(contador);
				HideLLLCar(contador);
			}
		}
	}
	return 1;
}
/*
forward Vehicles_OnVehicleDeath(vehicleid, killerid); // Antiguo, con este se quitaba el tunning, podria ser util en un futuro
public Vehicles_OnVehicleDeath(vehicleid, killerid)
{
	if(CarInfo[vehicleid][cUsos] != 0) return 1;
	for (new contador = 0; contador < TotalVeh; contador++)
	if (CarInfo[contador][cId] == vehicleid)
	{
	    for(new slot = 0; slot < 10; slot++)
		{
	        if(CarInfo[contador][cComponentes][slot] != NOEXISTE)
	        {
	            RemoveVehicleComponent(CarInfo[contador][cId], CarInfo[contador][cComponentes][slot]);
	            CarInfo[contador][cComponentes][slot] = NOEXISTE;
	            CarInfo[contador][cPaintJob] = NOEXISTE;
				CarInfo[contador][cBroken] = 1;
				for(new parking; parking < MAX_PARKINGS; parking++)
				{
					if(ParkInfo[parking][paType] == 3)
					{
						CarInfo[contador][cParking] = ParkInfo[parking][paSQLID];
						CarInfo[contador][horas] = 1;
						ParkInfo[parking][paTotal]++;
						SaveParking(parking);
						RepairVehicle(CarInfo[contador][cId]);
						SaveCar(contador);
						HideLLLCar(contador);
					}
				}
	        }
		}
	}
	return 1;
}*/

Vehicles_OnVehiclePaintjob(vehicleid, paintjobid)
{
	new tmpcar;
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(CarInfo[i][cId] == vehicleid)
		{
			tmpcar = i;
			break;
		}
	}
	CarInfo[tmpcar][cPaintJob] = paintjobid;
	SaveCar(tmpcar);
	return 1;
}

Vehicles_OnVehicleMod(vehicleid, componentid)
{
	new tmpcar;
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(CarInfo[i][cId] == vehicleid)
		{
			tmpcar = i;
			break;
		}
	}

	new slot = GetVehicleComponentType(componentid);
    CarInfo[tmpcar][cComp][slot] = componentid;
	SaveCar(tmpcar);
	return 1;
}

Vehicles_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	#pragma unused vehicleid
	#pragma unused ispassenger
	new tmpcar;  // Float:X,Float:Y,Float:Z,

	tmpcar = vehiculomascercano (playerid);
	
    if (CarInfo[tmpcar][cGPS]>-1 && GetPlayerVehicleSeat(playerid)==0)
    {
        DisablePlayerCheckpoint(CarInfo[tmpcar][cGPS]);
        PlayerInfo[CarInfo[tmpcar][cGPS]][pCheckpoint] = 0;
        SetPlayerMarkerForPlayer(CarInfo[tmpcar][cGPS],playerid,Rojo);
    }
    
	if (IsABike (tmpcar)) // es bici o moto
	{
	    return 1;
	}

	if (IsAMotorcycle (tmpcar))
	{
	    return 1;
	}
	    
	if (IsABoat (CarInfo[tmpcar][cId]))
	{
	    return 1;
	}

	if (CarInfo[tmpcar][cLock] == 1)
	{
		GameTextForPlayer(playerid, "El vehiculo esta cerrado.", 3000, 5);
		return 1;
	}

	return 1;
}

Veh_OnPlayerEnterCheckpoint(playerid)
{
    if (PlayerInfo[playerid][pCheckpoint] == 31)
	{
        DisablePlayerCheckpoint(playerid);
        for (new i;i<TotalVeh;i++)
        {
            if (LocalizandoVehiculo[playerid] == CarInfo[i][cId])
            {
                CarInfo[i][cGPS]=NOEXISTE;
                LocalizandoVehiculo[playerid]= NOEXISTE;
                break;
            }
        }
        PlayerInfo[playerid][pCheckpoint] = 0;
		return 1;
    }
    return 0;
}

catalogovehiculos(playerid, concesionario)
{
	// Si en el ciclo de elegir vehículo se sobrepasan el valor máximo o mínimo de ID de vehiculo, evitar error de ID
	if (EnCatalogoVeh[playerid] < MenorPosArray(concesionario))
    	EnCatalogoVeh[playerid] = MayorPosArray(concesionario);
	if (EnCatalogoVeh[playerid] > MayorPosArray(concesionario))
	    EnCatalogoVeh[playerid] = MenorPosArray(concesionario);

	if (VehCatalogo[playerid] != NOEXISTE)
	{
	    DestroyVehicle(EnCatalogoVeh[playerid]);
	}
	if(concesionario == 7)
	{
		VehCatalogo[playerid] = CreateVehicle(datacar[EnCatalogoVeh[playerid]][dcIDModel], 733.2559,-1506.8319,-0.0312,0.3772,-1,-1,3600000);
	}
	else if(concesionario == 6)
	{
		VehCatalogo[playerid] = CreateVehicle(datacar[EnCatalogoVeh[playerid]][dcIDModel], -2229.1060,2326.0977,8.2523,359.4237,-1,-1,3600000);
	}
	else
	{
		VehCatalogo[playerid] = CreateVehicle(datacar[EnCatalogoVeh[playerid]][dcIDModel], -1951.1927,264.8029,40.7625,40.3529,-1,-1,3600000);
	}
	SetVehicleVirtualWorld(VehCatalogo[playerid], playerid + 1);
 	TextDrawShowForPlayer(playerid, Nombre[EnCatalogoVeh[playerid]]);
  	TextDrawShowForPlayer(playerid, Costo[EnCatalogoVeh[playerid]]);
   	TextDrawShowForPlayer(playerid, Id[EnCatalogoVeh[playerid]]);
	return 1;
}

MayorPosArray(concesionario)
{
	new mayorpos;
	for(new i = 0; i < MAX_CAR_DATA; i++)
	{
		if(datacar[i][dcConcesionario] == concesionario)
		{
			mayorpos = i;
		}
	}
	return mayorpos;
}

MenorPosArray(concesionario)
{
	new menorpos;
	for(new i = 0; i < MAX_CAR_DATA; i++)
	{
		if(datacar[i][dcConcesionario] == concesionario)
		{
			menorpos = i;
			break;
		}
	}
	return menorpos;
}

GetPlayerConcesionario(playerid)
{
	new Concesionario;
	for(new i = 0; i < 7; i ++)
	{
		if(PlayerToPoint(10, playerid, Concesionarios[i][cX], Concesionarios[i][cY], Concesionarios[i][cZ]))
		{
			Concesionario = i+1;
		}
	}
	return Concesionario;
}

GetPlayerConcesionarioEx(playerid)
{
	new Concesionario;
	for(new i = 0; i < 7; i ++)
	{
		if(PlayerToPoint(10, playerid, Concesionarios[i][cX], Concesionarios[i][cY], Concesionarios[i][cZ]))
		{
			Concesionario = i;
		}
	}
	return Concesionario;
}

stock vehiculomascercano (playerid)
{
	new Float:tmpdistancia;
	new Float:tmpmascercano=10000.0;
	new tmpid;
	new Float:ptmpx, Float:ptmpy, Float:ptmpz;
	new Float:vtmpx, Float:vtmpy, Float:vtmpz;

	GetPlayerPos(playerid, ptmpx, ptmpy, ptmpz);
	for (new contador=0; contador < TotalVeh; contador++)
	{
//	        printf ("Contador: %d", contador);
		GetVehiclePos(CarInfo[contador][cId], vtmpx, vtmpy, vtmpz);
		tmpdistancia=floatsqroot(floatadd(floatpower(floatsub(vtmpx,ptmpx),2.0), floatpower(floatsub(vtmpy, ptmpy),2.0)));
	    if (tmpdistancia < tmpmascercano)
    	{
        	tmpmascercano = tmpdistancia;
	        tmpid=contador;
		}
	}
//	GetVehiclePos(CarInfo[tmpid][cID], vtmpx, vtmpy, vtmpz);
//	SetPlayerCheckpoint (playerid, vtmpx, vtmpy, vtmpz, 5.0);
	return tmpid;
}


stock PlayerHaveKeys(playerid, vehiculo)
{
	for(new i; i < MAX_PROPIOS; i++)
	{
		if(PlayerInfo[playerid][pPCarKey][i] == CarInfo[vehiculo][cCarKey])
		{
			return 1;
		}
	}
	for(new i; i < MAX_PRESTADOS; i++)
	{
		if(PlayerInfo[playerid][pPCochePrestado][i] == CarInfo[vehiculo][cCarKey])
		{
			return 1;
		}
	}
	if(PlayerInfo[playerid][pPCocheTemporal] == CarInfo[vehiculo][cCarKey]) return 1;
	return 0;
}

forward cancelarespectador (playerid, tmpidplayer, tmpcoche);
public cancelarespectador (playerid, tmpidplayer, tmpcoche)
{
	new tmpnombrejugador[30], tmpcar, mensaje[80], tmpposicionllave, tmpllave;

	tmpposicionllave = tmpcoche;
	// CASO ESPECIAL: para un único recon de vehiculo. Usado por lideres para buscar un vehiculo concreto en /findteamcar
	if (tmpposicionllave == 1)
	{
        // no hay más coches que mirar
        tmpposicionllave = 7;
	}

	if (tmpposicionllave == 2)
	{
	    if (PlayerInfo[tmpidplayer][pPCarKey][1] != NOEXISTE)
	    {
	        tmpllave = PlayerInfo[tmpidplayer][pPCarKey][1];
	        tmpcar = GetPlayerVehicleByKey(tmpllave);
		}
		else
	        tmpposicionllave = 4;
	}

	if (tmpposicionllave == 3)
	{
	    if (PlayerInfo[tmpidplayer][pPCarKey][2] != NOEXISTE)
	    {
	        tmpllave = PlayerInfo[tmpidplayer][pPCarKey][2];
	        tmpcar = GetPlayerVehicleByKey(tmpllave);
		}
		else
	        tmpposicionllave = 4;
	}
	
	if (tmpposicionllave == 4)
	{
	    if (PlayerInfo[tmpidplayer][pPCochePrestado][0] != NOEXISTE)
	    {
	        tmpllave = PlayerInfo[tmpidplayer][pPCochePrestado][0];
	        tmpcar = GetPlayerVehicleByKey(tmpllave);
		}
		else
		    tmpposicionllave = 7;
	}

	if (tmpposicionllave == 5)
	{
	    if (PlayerInfo[tmpidplayer][pPCochePrestado][1] != NOEXISTE)
	    {
	        tmpllave = PlayerInfo[tmpidplayer][pPCochePrestado][1];
	        tmpcar = GetPlayerVehicleByKey(tmpllave);
		}
		else
		    tmpposicionllave = 7;
	}
	if (tmpposicionllave == 6)
	{
	    if (PlayerInfo[tmpidplayer][pPCochePrestado][2] != NOEXISTE)
	    {
	        tmpllave = PlayerInfo[tmpidplayer][pPCochePrestado][2];
	        tmpcar = GetPlayerVehicleByKey(tmpllave);
		}
		else
		    tmpposicionllave = 7;
	}

	if (tmpposicionllave == 7) // no hay más coches que mirar
	{
		TogglePlayerSpectating (playerid, 0);
//		SetPlayerPos(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
	}
	else
	{
		// si el jugador tiene la llave de más de un coche
		// tomar nombre del jugador
		GetPlayerName(tmpidplayer, tmpnombrejugador, 30);
		// es nombre de jugador el dueño del coche de la llave? sí -> recon de vehiculo
		if (tmpcar == NOEXISTE)
		{
			format (mensaje, 80, "El coche de la llave %d no existe. ¿Qué pasó? Hablar con jugador.");
		    SendClientMessage(playerid, Rojo, mensaje);
			TogglePlayerSpectating (playerid, 0);
			return 1;
		}
//		if (strcmp (tmpnombrejugador, CarInfo[tmpcar][cOwner], true) == 0)
//		{
		PlayerSpectateVehicle(playerid, CarInfo[tmpcar][cId], SPECTATE_MODE_NORMAL);
		format (mensaje, 80, "Prop: %s~n~Llave: %d", CarInfo[tmpcar][cOwner], tmpllave);
		GameTextForPlayer(playerid, mensaje, 5000, 5);
		PlayerTmr[playerid] = SetTimerEx("cancelarespectador", 8000, false, "iii", playerid, tmpidplayer, tmpposicionllave + 1);
//		}
	}
	return 1;
}

stock GetCarOwner(tmpcar)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(PlayerHaveKeys(i, tmpcar))
	    {
	        for(new c = 0; c < MAX_PROPIOS; c++)
			{
				if(PlayerInfo[i][pPCarKey][c] != NOEXISTE)
				{
					if(PlayerInfo[i][pPCarKey][c] == tmpcar)
					{
						return i;
					}
				}
			}
		}
	}
	return NOEXISTE;
}

stock GetPlayerVehicleByKey (tmpllave)
{
	for (new i = 0; i < TotalVeh; i++)
	{
	    if (CarInfo[i][cCarKey] == tmpllave)
	        return i;
	}
	// no se encontró, coche destruido?
	return NOEXISTE;
}

stock GetVehicleByKey (tmpllave)
{
	new coche = -1;
	new sqlid = 0;
	new sql[80];
	new row[256];
	format(sql, 80, "SELECT * FROM `cars` WHERE `Key` =%d AND `eliminado` = -1", tmpllave);
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	split(row, arrCoords, ',');
	sqlid = strval(arrCoords[0]);
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(CarInfo[i][cSQLID] == sqlid)
		{
			coche = i;
			break;
		}
	}
	mysql_free_result();
	return coche;
}

forward RecolocarJobVeh(playerid, param);
public RecolocarJobVeh(playerid, param)
{
	for(new i = 0;i < TotalVeh; i++)
	{
	    if(param == 0)
	    {
	    	if(((CarInfo[i][cUsos] > 0) && (CarInfo[i][cUsos] < 100)) && (Recolocarcoches[i] == 0))
	    	{
				SetVehiclePos(CarInfo[i][cId], CarInfo[i][cLocationx], CarInfo[i][cLocationy], CarInfo[i][cLocationz]);
        	    SetVehicleZAngle(CarInfo[i][cId], CarInfo[i][cAngle]);
				RepairVehicle(CarInfo[i][cId]);
				CarInfo[i][cBroken] = 0;
        	    //Recolocarcoches[i] = NOEXISTE;
  			}
		}
		else if(param == 100)
		{
			if(CarInfo[i][cUsos] > 100 && Recolocarcoches[i] == 0)
	    	{
				SetVehiclePos(CarInfo[i][cId], CarInfo[i][cLocationx], CarInfo[i][cLocationy], CarInfo[i][cLocationz]);
        	    SetVehicleZAngle(CarInfo[i][cId], CarInfo[i][cAngle]);
				RepairVehicle(CarInfo[i][cId]);
				CarInfo[i][cBroken] = 0;
        	    //Recolocarcoches[i] = NOEXISTE;
  			}
		}
		else
		{
			if(CarInfo[i][cUsos] == param && Recolocarcoches[i] == 0)
	    	{
				SetVehiclePos(CarInfo[i][cId], CarInfo[i][cLocationx], CarInfo[i][cLocationy], CarInfo[i][cLocationz]);
        	    SetVehicleZAngle(CarInfo[i][cId], CarInfo[i][cAngle]);
				if(param >= 100)
				{
					RepairVehicle(CarInfo[i][cId]);
					CarInfo[i][cBroken] = 0;					
				}
        	    //Recolocarcoches[i] = NOEXISTE;
  			}
		}
		if(Recolocarcoches[i] == 1)
		{
		Recolocarcoches[i] = 0;
		}
  	}
  	return 1;
}

// Luca: cambio en resitecar 22-04-09
forward Recolocarveh (playerid, Float:radio);
public Recolocarveh(playerid, Float:radio)
{
	new tmpcar;
	tmpcar = 0;
	// Respawnear todos los coches vacíos de 1 en 1 (espacio de tiempo entre coches: 2 seg)
	while (tmpcar < TotalVeh)
	{
	    if (Recolocarcoches[tmpcar] == 0)
	    {
	        if (CheckPlayerDistanceToVehicle(radio, playerid, CarInfo[tmpcar][cId]))
	        {
	            if(CarInfo[tmpcar][cUsos] == 0)
	            {
					SetVehiclePos(CarInfo[tmpcar][cId], CarInfo[tmpcar][cLocationx], CarInfo[tmpcar][cLocationy], CarInfo[tmpcar][cLocationz]);
					SetVehicleZAngle(CarInfo[tmpcar][cId], CarInfo[tmpcar][cAngle]);
				}
				else
				{
					SetVehiclePos(CarInfo[tmpcar][cId], CarInfo[tmpcar][cTmpx], CarInfo[tmpcar][cTmpy], CarInfo[tmpcar][cTmpz]);
					SetVehicleZAngle(CarInfo[tmpcar][cId], CarInfo[tmpcar][cTmpa]);
				}
			}
		}
		else
		{
			Recolocarcoches[tmpcar] = 0;
		}
		tmpcar++;
	}
	return 1;
}

stock CreateLLLCar (playerid, tmpcarinlist, Float:X, Float:Y, Float:Z, Float:Angle, color1, color2)
{

	// coche de Admin o normal?
	if (tmpcarinlist >= 400) // de Admin. Se ha enviado el Modelo
	{
	    new tmpcarencatalogo;
	    tmpcarencatalogo = 0;
		CarInfo[TotalVeh][cId] = CreateVehicle(tmpcarinlist, X,Y,Z, Angle, color1, color2, 3000000);
		format(CarInfo[TotalVeh][cOwner], MAX_PLAYER_NAME, "Admin");
		for (new contador = 0; contador < MAX_CAR_DATA; contador++)
		{
		    if (datacar[contador][dcIDModel] == tmpcarinlist) // el modelo añadido está en el catálogo
		    {
			    format(CarInfo[TotalVeh][cDescription], MAX_PLAYER_NAME, "%s", datacar[contador][dcNombre]);
			   	CarInfo[TotalVeh][cValue] = datacar[contador][dcPrecio];
			    tmpcarencatalogo = 1;
				break;
			}
		}
		if (tmpcarencatalogo == 0)
		{
		    format(CarInfo[TotalVeh][cDescription], MAX_PLAYER_NAME, "Admin");
		   	CarInfo[TotalVeh][cValue] = 100000;
		}
    	CarInfo[TotalVeh][cModel] = GetVehicleModel(CarInfo[TotalVeh][cId]);
	    GetVehiclePos(CarInfo[TotalVeh][cId], CarInfo[TotalVeh][cLocationx], CarInfo[TotalVeh][cLocationy], CarInfo[TotalVeh][cLocationz]);
	   	GetVehicleZAngle(CarInfo[TotalVeh][cId], CarInfo[TotalVeh][cAngle]);
		CarInfo[TotalVeh][cUsos] = 200; // 
		CarInfo[TotalVeh][cStarted] = 0; // 
	    CarInfo[TotalVeh][cLock] = 0; // Abierto por defecto
		CarInfo[TotalVeh][cOwned] = 0;
		CarInfo[TotalVeh][cGas] = 100;
	}
	else // normal, se ha enviado el coche en la lista de datacar
	{
    	CarInfo[TotalVeh][cModel] = datacar[tmpcarinlist][dcIDModel];
		CarInfo[TotalVeh][cId] = CreateVehicle(CarInfo[TotalVeh][cModel], X,Y,Z, Angle, color1, color2, 3600000);
		GetPlayerName(playerid, CarInfo[TotalVeh][cOwner], MAX_PLAYER_NAME);
	    format(CarInfo[TotalVeh][cDescription], MAX_PLAYER_NAME, "%s", datacar[tmpcarinlist][dcNombre]);
	    GetVehiclePos(CarInfo[TotalVeh][cId], CarInfo[TotalVeh][cLocationx], CarInfo[TotalVeh][cLocationy], CarInfo[TotalVeh][cLocationz]);
	   	GetVehicleZAngle(CarInfo[TotalVeh][cId], CarInfo[TotalVeh][cAngle]);
	   	CarInfo[TotalVeh][cValue] = datacar[tmpcarinlist][dcPrecio];
//	   	if(CodigoLlave > 10000) { CodigoLlave-=10000; }
//		CarInfo[TotalVeh][cCarKey] = CodigoLlave;
		CarInfo[TotalVeh][cUsos] = datacar[tmpcarinlist][dcMember]; // asignado el código de facción
		CarInfo[TotalVeh][cStarted] = 0;
	    CarInfo[TotalVeh][cLock] = 0; // cerrado por defecto
		CarInfo[TotalVeh][cOwned] = 1;
		CarInfo[TotalVeh][cGas] = 30;
	}
    CarInfo[TotalVeh][cCarKey] = CodigoLlave;
    CarInfo[TotalVeh][cColorOne] = color1;
	CarInfo[TotalVeh][cColorTwo] = color2;
	CarInfo[TotalVeh][cBroken] = 0;
	CarInfo[TotalVeh][cDamage] = 1000;
	CarInfo[TotalVeh][cEmisora] = 1;
	CarInfo[TotalVeh][cVolumen] = 100;
	CarInfo[TotalVeh][cSubWoofer] = 0;
	CarInfo[TotalVeh][cGPS] = -1;
	CarInfo[TotalVeh][cIntermitentesTmr] = -1;
	for(new i = 0; i < MAX_TRUNK_SLOTS; i++)
	{
	    CarInfo[TotalVeh][cSlot][i] = NOEXISTE;
	    CarInfo[TotalVeh][cAmmo][i] = NOEXISTE;
	}
    for (new i = 0; i < 3; i++)
    {
        CarInfo[TotalVeh][cDrogaP][i] = 0;
    }
    for (new i = 0; i < 2; i++)
    {
        CarInfo[TotalVeh][cDrogaNP][i] = 0;
        CarInfo[TotalVeh][cSemillas][i] = 0;
    }
	CarInfo[TotalVeh][cPaintJob] = NOEXISTE;// PJ -
	for(new slot = 0; slot < 10; slot++)
	{
	    CarInfo[TotalVeh][cComponentes][slot] = NOEXISTE;
	}
	
	new Matricula[32];
	format(Matricula,sizeof(Matricula),"LS-%d",CarInfo[TotalVeh][cCarKey]);
	SetVehicleNumberPlate(CarInfo[TotalVeh][cId],Matricula);

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[TotalVeh][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(CarInfo[TotalVeh][cId], CarInfo[TotalVeh][cStarted], lights, alarm, CarInfo[TotalVeh][cLock], bonnet, boot, objective);

	
	new sql[128];
	format(sql, 128, "INSERT INTO `cars` (`Key`, `Des`) VALUES (%d, 'Nuevo Coche');", CarInfo[TotalVeh][cCarKey]);
	mysql_query(sql);

	
	new row[64];
	mysql_query("SELECT id FROM cars ORDER BY id DESC LIMIT 1");
    mysql_store_result();
   	mysql_fetch_row(row);
	CarInfo[TotalVeh][cSQLID] = strval(row);
	mysql_free_result();
	SaveCar(TotalVeh);
 	TotalVeh++;
    CodigoLlave++;

	return 1;
}

stock DestroyLLLCar (tmpidcar)
{
	CarInfo[tmpidcar][eliminado] = 1;
	new sql[200];
	format(sql, 200, "UPDATE cars SET eliminado=1 WHERE id = %d LIMIT 1", CarInfo[tmpidcar][cSQLID]);
	mysql_query(sql);
	DestroyVehicle(CarInfo[tmpidcar][cId]);
	TotalVeh--;
	for ( ; tmpidcar < TotalVeh; tmpidcar++)
	{
 		CarInfo[tmpidcar][cId] = CarInfo[tmpidcar+1][cId];
  		CarInfo[tmpidcar][cCarKey] = CarInfo[tmpidcar+1][cCarKey];
 		CarInfo[tmpidcar][cModel] = CarInfo[tmpidcar+1][cModel];
  		CarInfo[tmpidcar][cLocationx] = CarInfo[tmpidcar+1][cLocationx];
		CarInfo[tmpidcar][cLocationy] = CarInfo[tmpidcar+1][cLocationy];
		CarInfo[tmpidcar][cLocationz] = CarInfo[tmpidcar+1][cLocationz];
		CarInfo[tmpidcar][cColorOne] = CarInfo[tmpidcar+1][cColorOne];
		CarInfo[tmpidcar][cColorTwo] = CarInfo[tmpidcar+1][cColorTwo];
		format (CarInfo[tmpidcar][cOwner], MAX_PLAYER_NAME, "%s", CarInfo[tmpidcar+1][cOwner]);
 		format (CarInfo[tmpidcar][cDescription], MAX_PLAYER_NAME, "%s", CarInfo[tmpidcar+1][cDescription]);
 		CarInfo[tmpidcar][cValue] = CarInfo[tmpidcar+1][cValue];
 		CarInfo[tmpidcar][cAngle] = CarInfo[tmpidcar+1][cAngle];
		CarInfo[tmpidcar][cUsos] = CarInfo[tmpidcar+1][cUsos];
		CarInfo[tmpidcar][cOwned] = CarInfo[tmpidcar+1][cOwned];
  		CarInfo[tmpidcar][cLock] = CarInfo[tmpidcar+1][cLock];
		CarInfo[tmpidcar][cBroken] = CarInfo[tmpidcar+1][cBroken];
		CarInfo[tmpidcar][cStarted] = CarInfo[tmpidcar+1][cStarted];
		CarInfo[tmpidcar][cGas] = CarInfo[tmpidcar+1][cGas];
		for(new i; i < MAX_TRUNK_SLOTS; i++)
		{
		    CarInfo[tmpidcar][cSlot][i] = CarInfo[tmpidcar+1][cSlot][i];
		    CarInfo[tmpidcar][cAmmo][i] = CarInfo[tmpidcar+1][cAmmo][i];
		}
        for (new i = 0; i < 2; i++)
        {
            CarInfo[tmpidcar][cDrogaP][i] = CarInfo[tmpidcar+1][cDrogaP][i];
            CarInfo[tmpidcar][cDrogaNP][i] = CarInfo[tmpidcar+1][cDrogaNP][i];
            CarInfo[tmpidcar][cSemillas][i] = CarInfo[tmpidcar+1][cSemillas][i];
        }
        CarInfo[tmpidcar][cDrogaP][2] = CarInfo[tmpidcar+1][cDrogaP][2];
        for (new i = 0; i < 14; i++)
        {
            CarInfo[tmpidcar][cComp][i] = CarInfo[tmpidcar+1][cComp][i];
        }
		CarInfo[tmpidcar][cPaintJob] = CarInfo[tmpidcar+1][cPaintJob];
  		CarInfo[tmpidcar][cTmpx] = CarInfo[tmpidcar+1][cTmpx];
		CarInfo[tmpidcar][cTmpy] = CarInfo[tmpidcar+1][cTmpy];
		CarInfo[tmpidcar][cTmpz] = CarInfo[tmpidcar+1][cTmpz];
		CarInfo[tmpidcar][cTmpa] = CarInfo[tmpidcar+1][cTmpa];
		CarInfo[tmpidcar][cSQLID] = CarInfo[tmpidcar+1][cSQLID];
		CarInfo[tmpidcar][eliminado] = CarInfo[tmpidcar+1][eliminado];
		CarInfo[tmpidcar][horas] = CarInfo[tmpidcar+1][horas];
		CarInfo[tmpidcar][cParking] = CarInfo[tmpidcar+1][cParking];
        for (new i = 0; i < 4; i++)
        {
            CarInfo[tmpidcar][cDano][i] = CarInfo[tmpidcar+1][cDano][i];
        }
		CarInfo[tmpidcar][cDamage] = CarInfo[tmpidcar+1][cDamage];
		CarInfo[tmpidcar][cEmisora] = CarInfo[tmpidcar+1][cEmisora];
		CarInfo[tmpidcar][cVolumen] = CarInfo[tmpidcar+1][cVolumen];
		CarInfo[tmpidcar][cSubWoofer] = CarInfo[tmpidcar+1][cSubWoofer];
		CarInfo[tmpidcar][cEquipo] = CarInfo[tmpidcar+1][cEquipo];
		format (CarInfo[tmpidcar][cRadios], 40, "%s", CarInfo[tmpidcar+1][cRadios]);
		CarInfo[tmpidcar][cVw] = CarInfo[tmpidcar+1][cVw];
		CarInfo[tmpidcar][cInt] = CarInfo[tmpidcar+1][cInt];
		CarInfo[tmpidcar][cSeguro] = CarInfo[tmpidcar+1][cSeguro];
		CarInfo[tmpidcar][cGPS] = CarInfo[tmpidcar+1][cGPS];
		CarInfo[tmpidcar][cSirena] = CarInfo[tmpidcar+1][cSirena];
		CarInfo[tmpidcar][cRobado] = CarInfo[tmpidcar+1][cRobado];
		CarInfo[tmpidcar][cKms] = CarInfo[tmpidcar+1][cKms];
    }
	return 1;
}

stock HideLLLCar (tmpidcar)
{
	if(CarInfo[tmpidcar][cIntermitentesTmr] != NOEXISTE) // HideLLLCar
	{
		KillTimer(CarInfo[tmpidcar][cIntermitentesTmr]);
		CarInfo[tmpidcar][cIntermitentesTmr] = NOEXISTE;
	}
	CarInfo[tmpidcar][eliminado] = -1;
	new sql[200];
	format(sql, 200, "UPDATE cars SET eliminado=-1 WHERE id = %d LIMIT 1", CarInfo[tmpidcar][cSQLID]);
	mysql_query(sql);
	DestroyVehicle(CarInfo[tmpidcar][cId]);
	CarInfo[tmpidcar][cId] = -1;
	return 1;
}
stock ResetLlavesCoche (playerid)
{
	if (IsPlayerConnected(playerid))
	{
	    for(new i; i < MAX_PROPIOS; i++)
		{
			PlayerInfo[playerid][pPCarKey][i] = NOEXISTE;
		}
		for(new i; i < MAX_PRESTADOS; i++)
		{
			PlayerInfo[playerid][pPCochePrestado][i] = NOEXISTE;
		}
		return 1;
	}
	else
	    return 0;
}

stock ReorganizarLlavesCoches (playerid)
{
	new i = 0;
	while(i < MAX_PROPIOS)
	{
		if (PlayerInfo[playerid][pPCarKey][i] == NOEXISTE)
		{
			PlayerInfo[playerid][pPCarKey][i] = PlayerInfo[playerid][pPCarKey][i+1];
			PlayerInfo[playerid][pPCarKey][i+1] = NOEXISTE;
		}
		i++;
	}
	i = 0;
	while(i < MAX_PRESTADOS)
	{
		if (PlayerInfo[playerid][pPCochePrestado][i] == NOEXISTE)
		{
			PlayerInfo[playerid][pPCochePrestado][i] = PlayerInfo[playerid][pPCochePrestado][i+1];
			PlayerInfo[playerid][pPCochePrestado][i+1] = NOEXISTE;
		}
		i++;
	}
	SaveValues(playerid, "Coches");
	SaveValues(playerid, "CochesPrestados");
	return 1;
}

stock IsFakeCar(tmpidvehicle)
{
    for (new j = 0; j < TotalVeh; j++)
    {
        if (CarInfo[j][cId] == tmpidvehicle)
        {
            return NOEXISTE; // el coche no es fake
		}
	}
	return tmpidvehicle; // el coche es fake, devolver su idvehicle
}

stock EsNumero (cmd[])
{
	new valido, longitud;
	
	valido = 0;
	longitud = strlen(cmd);
	for (new contador = 0; contador < longitud; contador++)
	{
	    switch (cmd[contador])
		{
			case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-': valido = 1;
			default: return 0;
		}
	}
	return valido;
}

forward CerrarMaletero(vehicleid, playerid);
public CerrarMaletero(vehicleid, playerid)
{
	Maletero[vehicleid] = 0;
	CocheOcupado = 0;
	trunkTimer[playerid] = NOEXISTE;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[vehicleid][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(CarInfo[vehicleid][cId], engine, lights, alarm, doors, bonnet, false, objective);
	return 1;
}

CheckCarsHealth()
{
	new Float:HealthV, engine, lights, alarm, doors, bonnet, boot, objective;
	for(new i=0; i < MAX_PLAYERS; i++)
	{
	    if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
	    {
	        new arrayid = GetPlayerVehicle(i);
	        GetVehicleHealth(CarInfo[arrayid][cId], HealthV);
	        if(HealthV <= 380 && !IsABike(arrayid) && CarInfo[arrayid][cBroken] == 0)
	        {
				CarInfo[arrayid][cBroken] = 1;
				CarInfo[arrayid][cStarted] = 0;
				GetVehicleParamsEx(CarInfo[arrayid][cId], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(CarInfo[arrayid][cId], CarInfo[arrayid][cStarted], lights, alarm, doors, bonnet, boot, objective);
				SaveCar(arrayid);
				SendClientMessage(i, Naranja, "* El vehículo ha dejado de funcionar, llama a un mecánico para poder repararlo.");
				return 1;
			}
		}
	}
	return 1;
}

Vehicles_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new keyso, updown, leftright;
	GetPlayerKeys(playerid, keyso, updown, leftright);
	if (EnCatalogoVeh[playerid] != NOEXISTE)
	{
	    if (((newkeys & KEY_JUMP) == KEY_JUMP)  && ((oldkeys & KEY_JUMP) != KEY_JUMP))
	    {
			TextDrawHideForPlayer(playerid, Nombre[EnCatalogoVeh[playerid]]);
			TextDrawHideForPlayer(playerid, Costo[EnCatalogoVeh[playerid]]);
			TextDrawHideForPlayer(playerid, Id[EnCatalogoVeh[playerid]]);
	        EnCatalogoVeh[playerid]--;
			DestroyVehicle(VehCatalogo[playerid]);
			VehCatalogo[playerid] = NOEXISTE;
			catalogovehiculos(playerid, PConcesionario[playerid]);
			return 1;
		}
	    if (((newkeys & KEY_WALK) == KEY_WALK) && ((oldkeys & KEY_WALK) != KEY_WALK))
	    {
			TextDrawHideForPlayer(playerid, Nombre[EnCatalogoVeh[playerid]]);
			TextDrawHideForPlayer(playerid, Costo[EnCatalogoVeh[playerid]]);
			TextDrawHideForPlayer(playerid, Id[EnCatalogoVeh[playerid]]);
	        EnCatalogoVeh[playerid]++;
			DestroyVehicle(VehCatalogo[playerid]);
			VehCatalogo[playerid] = NOEXISTE;
			catalogovehiculos(playerid, PConcesionario[playerid]);
			return 1;
		}
	    if (((newkeys & KEY_SECONDARY_ATTACK) == KEY_SECONDARY_ATTACK) && ((oldkeys & KEY_SECONDARY_ATTACK) != KEY_SECONDARY_ATTACK))
	    {
			TextDrawHideForPlayer(playerid, Nombre[EnCatalogoVeh[playerid]]);
			TextDrawHideForPlayer(playerid, Costo[EnCatalogoVeh[playerid]]);
			TextDrawHideForPlayer(playerid, Id[EnCatalogoVeh[playerid]]);
	        TogglePlayerControllable(playerid,1);
	        DestroyVehicle(VehCatalogo[playerid]);
	        VehCatalogo[playerid] = NOEXISTE;
	        SetPlayerPos(playerid, PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz]);
			SetCameraBehindPlayer(playerid);
			SetPlayerVirtualWorld(playerid, 0);
	    	EnCatalogoVeh[playerid] = NOEXISTE;
	    	SendClientMessage(playerid, Verde, "Saliendo del catálogo.");
			return 1;
		}
	}
	//ARRANCAR CON ALT
	new newcar = GetPlayerVehicle(playerid);
//	if (keyso == KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && CarInfo[newcar][cStarted]==0)
	if ((oldkeys == 4 ) && (newkeys == 0) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && CarInfo[newcar][cStarted]==0)
	{
		EncenderMotor(playerid,newcar);
		return 1;
   	}
	if ((oldkeys == 4 ) && (newkeys == 0) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && CarInfo[newcar][cStarted]==1)
	{
		ApagarMotor(playerid,newcar);
		return 1;
	}
	//Luces con +
	if ((oldkeys == KEY_SUBMISSION ) && (newkeys == 0) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
		if(lights == 1)
		{
			SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, false, alarm, doors, bonnet, boot, objective);
		}
		else
		{
			SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, true, alarm, doors, bonnet, boot, objective);
		}
		return 1;
	}
	return 0;
}

Vehicles_OnGameModeInit()
{
	ManualVehicleEngineAndLights();

	for(new i=0; i < MAX_CAR_DATA; i++)
	{
		format(string, sizeof(string), "Vehiculo: %s", datacar[i][dcNombre]);
		Nombre[i] = TextDrawCreate(151.000000,342.000000,string);
    	format(string, sizeof(string), "Precio: $%d", datacar[i][dcPrecio]);
		Costo[i] = TextDrawCreate(152.000000,356.000000,string);
		format(string, sizeof(string), "Id: %d Nivel: %d", i, datacar[i][dcNivel]);
		Id[i] = TextDrawCreate(151.000000,369.000000,string);
		TextDrawAlignment(Nombre[i],0);
		TextDrawAlignment(Costo[i],0);
		TextDrawAlignment(Id[i],0);
		TextDrawBackgroundColor(Nombre[i],0x000000ff);
		TextDrawBackgroundColor(Costo[i],0x000000ff);
		TextDrawBackgroundColor(Id[i],0x000000ff);
		TextDrawFont(Nombre[i],2);
		TextDrawLetterSize(Nombre[i],0.499999,1.100000);
		TextDrawFont(Costo[i],2);
		TextDrawLetterSize(Costo[i],0.499999,1.100000);
		TextDrawFont(Id[i],2);
		TextDrawLetterSize(Id[i],0.499999,1.300000);
		TextDrawColor(Nombre[i],0xffffffff);
		TextDrawColor(Costo[i],0x00ff0066);
		TextDrawColor(Id[i],0xffffffff);
		TextDrawSetOutline(Nombre[i],1);
		TextDrawSetOutline(Costo[i],1);
		TextDrawSetOutline(Id[i],1);
		TextDrawSetProportional(Nombre[i],1);
		TextDrawSetProportional(Costo[i],1);
		TextDrawSetProportional(Id[i],1);
		TextDrawSetShadow(Nombre[i],1);
		TextDrawSetShadow(Costo[i],1);
		TextDrawSetShadow(Id[i],1);
	}
	
	for(new i; i < 7; i++)
	{
		CreateDynamicPickup(1239, 23, Concesionarios[i][cX], Concesionarios[i][cY], Concesionarios[i][cZ]);
		format(string, 128, "Concesionario %s", Concesionarios[i][cNombre]);
		CreateDynamic3DTextLabel(string, Amarillo, Concesionarios[i][cX], Concesionarios[i][cY], Concesionarios[i][cZ] + 0.8, 30);
		CreateDynamic3DTextLabel("/comprarveh - /catalogo", Gris, Concesionarios[i][cX], Concesionarios[i][cY], Concesionarios[i][cZ] + 0.6, 30);
	}
		
	LoadCar();
	
}

Vehicles_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);


	if(strcmp(cmd, "/getp", true) == 0)
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 1;
		new vehicleid, engine, lights, alarm, doors, bonnet, boot, objective;
		if(!IsPlayerInAnyVehicle(playerid)) vehicleid = vehiculomascercano(playerid); else vehicleid = GetPlayerVehicle(playerid);
		GetVehicleParamsEx(CarInfo[vehicleid][cId], engine, lights, alarm, doors, bonnet, boot, objective);
		format(string,sizeof(string),"Engine: %d - Lights: %d - Alarm: %d - Doors: %d - Bonnet: %d - Boot: %d - Objective: %d",engine, lights, alarm, doors, bonnet, boot, objective);
		SendClientMessage(playerid, Amarillo, string);
		return 1;
	}
	
	if(strcmp(cmd, "/kms", true) == 0)
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(CarInfo[GetPlayerVehicle(playerid)][cUsos] == 0)
			{
				new kms = floatround(CarInfo[GetPlayerVehicle(playerid)][cKms],floatround_round);
				format(string,sizeof(string),"* El contador de kilometros del vehiculo marca: %d Kms",kms);
				SendClientMessage(playerid, AmarilloClaro, string);
			}
			else SendClientMessage(playerid, Naranja, "* (( Los kilometros solo se guardan en vehiculos comprados )).");
		}
		else SendClientMessage(playerid, Rojo, "* Necesitas estar en un vehiculo y ser el conductor.");
		return 1;
	}
	if(strcmp(cmd, "/gas", true) == 0 || strcmp(cmd, "/gasolina", true) == 0)
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			format(string,sizeof(string),"* El deposito del vehiculo marca: %d%\%",CarInfo[GetPlayerVehicle(playerid)][cGas]);
			SendClientMessage(playerid, AmarilloClaro, string);
		}
		else SendClientMessage(playerid, Rojo, "* Necesitas estar en un vehiculo y ser el conductor.");
		return 1;
	}	
	if(strcmp(cmd, "/luces", true) == 0)
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
			if(lights == 1)
			{
				SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, false, alarm, doors, bonnet, boot, objective);
			}
			else
			{
				SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, true, alarm, doors, bonnet, boot, objective);
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/intermitentes", true) == 0)
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new coche = GetPlayerVehicle(playerid);
			if(CarInfo[coche][cIntermitentesTmr] == NOEXISTE)
			{
				SendClientMessage(playerid, Verde, "* Luces intermitentes activadas");
				CarInfo[coche][cIntermitentesTmr] = SetTimerEx("Intermitentes", 500, 1, "d", coche);
			}
			else
			{
				SendClientMessage(playerid, Verde, "* Luces intermitentes desactivadas");
				KillTimer(CarInfo[coche][cIntermitentesTmr]);
				CarInfo[coche][cIntermitentesTmr] = NOEXISTE;
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/capo", true) == 0)
	{
		new car, engine, lights, alarm, doors, bonnet, boot, objective;
		if(!IsPlayerInAnyVehicle(playerid)) car = vehiculomascercano(playerid); else car = GetPlayerVehicle(playerid);
		if(IsABike(car) || IsAPlane(car) || IsAMotorcycle(car)) return 0;
		if(PlayerInfo[playerid][pJob] == 1 || PlayerHaveKeys(playerid,car)
			|| PlayerInfo[playerid][pAdminDuty] > 0 || PlayerInfo[playerid][pMember] == CarInfo[GetPlayerVehicle(playerid)][cUsos])
		{
			GetVehicleParamsEx(CarInfo[car][cId], engine, lights, alarm, doors, bonnet, boot, objective);
			if(doors == 1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && PlayerInfo[playerid][pAdminDuty] == 0) { SendClientMessage(playerid, Rojo, "* El coche está cerrado!"); return 1;}
			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendClientMessage(playerid, Rojo, "* Tienes que ser el conductor del coche!"); return 1;}
			if(bonnet == 1)
			{
				SetVehicleParamsEx(CarInfo[car][cId], engine, lights, alarm, doors, 0, boot, objective);
				format(string, sizeof(string),"* %s cierra el capó del coche.",pName(playerid));
			}
			else
			{
				SetVehicleParamsEx(CarInfo[car][cId], engine, lights, alarm, doors, 1, boot, objective);
				format(string, sizeof(string),"* %s abre el capó del coche.",pName(playerid));
			}
			ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
			return 1;
		}
		else { SendClientMessage(playerid, Rojo, "* No eres mecánico o no tienes las llaves!"); return 1; }
	}
	
	if(strcmp(cmd, "/vermatriculas", true) == 0 || strcmp(cmd, "/vm", true) == 0)
	{
		if(TextToggle[playerid] == 0)
		{
			for(new i; i < MAX_VEHICLES; i++)
			{
				if(CarInfo[i][cId] == 0)
				{
					continue;
				}
				format(string, 128, "Matricula: LS-%d", CarInfo[i][cCarKey]);
				CarText[playerid][i] = CreatePlayer3DTextLabel(playerid, string, Azul, 0.0, 0.0, 0.0, 5.0, -1, CarInfo[i][cId]);
			}
			TextToggle[playerid] = 1;
			SendClientMessage(playerid, Amarillo, "* Matriculas activadas!");
		}
		else
		{
			for(new i; i < MAX_VEHICLES; i++)
			{
				DeletePlayer3DTextLabel(playerid, CarText[playerid][i]);
			}
			TextToggle[playerid] = 0;
			SendClientMessage(playerid, Amarillo, "* Matriculas desactivadas!");
		}
		return 1;
	}
	
	if(strcmp(cmd, "/venderseguro", true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 10) { SendClientMessage(playerid, Rojo, "* No eres vendedor de seguros!"); return 1; }
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /venderseguro [IdJugador/ParteDelNombre] [Precio]");
			return 1;
		}
		new player;
		if(!IsNumeric(tmp))
		player = ReturnUser(tmp,playerid);
		else player = strval(tmp);
		if(!IsPlayerConnected(player) || player == playerid) { SendClientMessage(playerid, Rojo, "* Jugador Inválido!"); return 1; }
		if(GetDistanceBetweenPlayers(playerid, player) > 8.0) { SendClientMessage(playerid, Rojo, "* Debes acercarte más a él!"); return 1; }	
		if(PlayerInfo[player][pOfreciendoS] > 0) { SendClientMessage(playerid, Naranja, "* El jugador ya tiene una oferta de seguro pendiente!"); return 1; }
		if(PlayerInfo[playerid][pOfreciendoS] > 0) { SendClientMessage(playerid, Naranja, "* Ya estas ofreciendo un seguro a alguien! Usa /cancelar seguro."); return 1; }
		if(!IsPlayerInAnyVehicle(player)) { SendClientMessage(playerid, Rojo, "* El jugador tiene que estar montado en un vehiculo!");	return 1; }
		new arrayid = GetPlayerVehicle(player);
		new precio = (CarInfo[arrayid][cValue]*5)/100;
		if(precio > 5000) precio = 5000;
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !IsNumeric(tmp))
		{
			format(string,sizeof(string),"El precio mínimo para asegurar el %s son %d$", CarInfo[arrayid][cDescription],precio);
			SendClientMessage(playerid, AmarilloClaro, string);
			return 1;
		}
		new dinero;
		dinero = strval(tmp);

		if(dinero < precio) { SendClientMessage(playerid, Naranja, "* No puedes ofrecer un seguro por menos del minimo."); return 1; }
				
		new estaono = 0;
		
		if(PlayerHaveKeys(player,arrayid)) estaono = 1;

		if(estaono == 0) { SendClientMessage(playerid, Rojo, "* El jugador debe ser el propietario del coche."); return 1; }
		PlayerInfo[player][pOfreciendoS] = playerid;
		PlayerInfo[player][pOfreciendoC] = dinero;
		PlayerInfo[player][pOfreciendoV] = arrayid;
		PlayerInfo[playerid][pOfreciendoS] = player;
		format(string, 128, "* %s te ha ofrecido un seguro contra todo daño de coche por $%d.", pName(playerid), dinero);
		SendClientMessage(player, AzulClaro, string);
		SendClientMessage(player, AmarilloClaro, "Utiliza /aceptar seguro o /cancelar seguro");
		format(string, 128, "* Haz ofrecido a %s un seguro contra todo daño de coche por $%d.", pName(player), dinero);
		SendClientMessage(playerid, AzulClaro, string);
		SendClientMessage(playerid, AmarilloClaro, "Usa /cancelar seguro para retirar la oferta.");
		return 1;
	}
	
	if(strcmp(cmd, "/gotocar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp) || !IsNumeric(tmp))
			{
				SendClientMessage(playerid, Blanco, "* USO: /gotocar [CocheID]");
				return 1;
			}
			new testcar = GetPlayerVehicleByKey(strval(tmp));
			if (testcar == NOEXISTE)
			{
				SendClientMessage(playerid, Rojo, "* Error el código de la llave. Vehículo no encontrado");
				return 1;
			}

			if (PlayerInfo[playerid][pAdmin] >= 1)
			{
				new Float:cwx2,Float:cwy2,Float:cwz2;
                if(CarInfo[testcar][eliminado] == -1)
                {
                    new park=NOEXISTE;
                    for(new i; i < MAX_PARKINGS; i++)
                    {
                        if(ParkInfo[i][paSQLID] == CarInfo[testcar][cParking])
                        {
                            park = i;
                            break;
                        }
                    }
                    if (park==NOEXISTE) { SendClientMessage(playerid, Rojo, "* Parking no encontrado"); return 1; }

                    cwx2=ParkInfo[park][paX];
                    cwy2=ParkInfo[park][paY];
                    cwz2=ParkInfo[park][paZ];
                }
                else GetVehiclePos(CarInfo[testcar][cId], cwx2, cwy2, cwz2);
				if (GetPlayerState(playerid) == 2)
				{
					SetVehiclePos(GetPlayerVehicleID(playerid), cwx2, cwy2, cwz2);
				}
				else
				{
					SetPlayerPos(playerid, cwx2, cwy2, (cwz2 + 4.0));
				}
				SendClientMessage(playerid, AzulClaro, "* Te has teleportado a la posición del coche.");
				SetPlayerInterior(playerid,0);
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/getcar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp) || !IsNumeric(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /getcar [CodigoLlave]");
				return 1;
			}
			new Float:plocx,Float:plocy,Float:plocz, Float:pangle;
			new plo, tmpllave;
			plo = strval(tmp);
			if (PlayerInfo[playerid][pAdmin] >= 1)
			{
				tmpllave = GetPlayerVehicleByKey(plo);
				if (tmpllave != NOEXISTE)
				{
					GetPlayerPos(playerid, plocx, plocy, plocz);
					GetPlayerFacingAngle(playerid, pangle);
					enfrente (playerid, 5.0, plocx, plocy, plocz, pangle);
					SetVehiclePos(CarInfo[tmpllave][cId],plocx, plocy, plocz);
					SetVehicleZAngle(CarInfo[tmpllave][cId], pangle);
				}
				else
				    SendClientMessage(playerid, Rojo, "* Código de llave no válido");
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
			}
		}
		return 1;
	}
	
	if (strcmp(cmd, "/setck", true) == 0)
	{
	    if (PlayerInfo[playerid][pAdmin] < 1)
	        return 1;

	    new tmpplayer, tmpllave, tmpidcar;
	    tmp = strtokex (cmdtext, idx);
	    if (!strlen(tmp))
	    {
	        SendClientMessage (playerid, Blanco, "USO: /setck [IdJugador] [Posicionllave] [IDVehiculo]");
	        SendClientMessage (playerid, AzulClaro, "Para eliminar llave, idvehiculo es -1");
	        return 1;
	    }
		tmpplayer = strval(tmp);
	    tmp = strtokex (cmdtext, idx);
	    if (!strlen(tmp))
	    {
	        SendClientMessage (playerid, Blanco, "USO: /setck [IdJugador] [Posicionllave] [IDVehiculo]");
	        SendClientMessage (playerid, AzulClaro, "Para eliminar llave, idvehiculo es -1");
	        return 1;
	    }
	    tmpllave = strval(tmp);
		
		if(tmpllave > (MAX_PROPIOS+MAX_PRESTADOS) || tmpllave < 1)
		{
			SendClientMessage (playerid, Rojo, "* Slot no valido");
			return 1;
		}	
		
	    tmp = strtokex (cmdtext, idx);
	    if (!strlen(tmp))
	    {
	        SendClientMessage (playerid, Blanco, "USO: /setck [IdJugador] [Posicionllave] [IDVehiculo]");
	        SendClientMessage (playerid, AzulClaro, "Para eliminar llave, idvehiculo es -1");
	        return 1;
	    }
	    tmpidcar = strval(tmp);
		if(tmpllave > MAX_PROPIOS)
		{
			PlayerInfo[tmpplayer][pPCochePrestado][tmpllave-6] = tmpidcar;
		}
		else
		{
			PlayerInfo[tmpplayer][pPCarKey][tmpllave-1] = tmpidcar;
		}
		printf("ADMINLOG: %s ha seteado la llave %d en el hueco %d a %s",pName(playerid),tmpidcar,tmpllave,pName(tmpplayer));
		SendClientMessage(playerid, Verde, "* Llave seteada correctamente.");
		SaveValues(tmpplayer, "Coches");
		SaveValues(tmpplayer, "CochesPrestados");
	    return 1;
	}
	
	if (strcmp("/resetllavescoche", cmd, true) == 0)
	{
	    if (PlayerInfo[playerid][pAdmin] < 2)
	        return 1;
	        
	    tmp = strtokex (cmdtext, idx);
	    if (!strlen(cmd))
	    {
	        SendClientMessage(playerid,Blanco, "USO: /resetllavescoche [IdJugador/ParteDelNombre]");
	        return 1;
		}

		if (!ResetLlavesCoche (strval(cmd)))
		    SendClientMessage (playerid, Rojo, "* Ese jugador no está conectado.");

		return 1;
	}
	
	if (strcmp("/asetcar", cmd, true) == 0)
	{
	    new tmpidcar, engine, lights, alarm, doors, bonnet, boot, objective;

	    if (PlayerInfo[playerid][pAdmin] < 1)
	        return 1;

	    tmpidcar = vehiculomascercano(playerid);
	    cmd = strtokex (cmdtext, idx);
	    if (!strlen(cmd))
	    {
			SendClientMessage(playerid,Blanco,"USO: /asetcar [Model/Owned/Owner/Team/Job/Spawn/Color/Gas/Start/Lock/Broken/Vw/Int]");
			SendClientMessage(playerid,AzulClaro,"Actua sobre el coche mas cercano");
	        return 1;
		}

		if (strcmp("model", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar model [NombreVehiculo]");
		        return 1;
			}
			format(CarInfo[tmpidcar][cDescription], MAX_PLAYER_NAME, "%s", cmd);
			SaveCar(tmpidcar);
			return 1;
		}

		if (strcmp("owner", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar owner [NombrePropietario]");
		        return 1;
			}
			format(CarInfo[tmpidcar][cOwner], MAX_PLAYER_NAME, "%s", cmd);
			SaveCar(tmpidcar);
			return 1;
		}

		if (strcmp("team", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar team [FacciónID]");
		        return 1;
			}
			CarInfo[tmpidcar][cUsos] = strval(cmd);
			SaveCar(tmpidcar);
			return 1;
		}
		
		if (strcmp("job", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar job [JobID]");
		        return 1;
			}
			CarInfo[tmpidcar][cUsos] = 100+strval(cmd);
			SaveCar(tmpidcar);
			return 1;
		}
		
		if (strcmp("Vw", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar VW [VWID]");
		        return 1;
			}
			CarInfo[tmpidcar][cVw] = strval(cmd);
			SetVehicleVirtualWorld(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cVw]);
			SaveCar(tmpidcar);
			return 1;
		}
		
		if (strcmp("Int", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar Int [IntID]");
		        return 1;
			}
			CarInfo[tmpidcar][cInt] = strval(cmd);
			LinkVehicleToInterior(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cInt]);
			SaveCar(tmpidcar);
			return 1;
		}
		
		if (strcmp("spawn", cmd, true) == 0)
		{
			new sql[256];
		    if(!IsPlayerInAnyVehicle(playerid)) return 1;
		    tmpidcar = GetPlayerVehicle(playerid);
		    GetVehiclePos(CarInfo[tmpidcar][cId],CarInfo[tmpidcar][cLocationx],CarInfo[tmpidcar][cLocationy],CarInfo[tmpidcar][cLocationz]);
		    GetVehicleZAngle(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cAngle]);
			SendClientMessage(playerid, Amarillo, "* Spawn del vehiculo ajustado.");
			format(sql, sizeof(sql), "UPDATE cars SET X=%f,Y=%f,Z=%f,A=%f,Vw=%d,Interior=%d WHERE id = %d",
				CarInfo[tmpidcar][cLocationx],
				CarInfo[tmpidcar][cLocationy],
				CarInfo[tmpidcar][cLocationz],
				CarInfo[tmpidcar][cAngle],
				CarInfo[tmpidcar][cVw],
				CarInfo[tmpidcar][cInt],
				CarInfo[tmpidcar][cSQLID]);
			mysql_query(sql);
			return 1;
		}

		if (strcmp("color", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar color [0-126] [0-126]");
		        return 1;
			}
			new idcolor1, idcolor2;
			idcolor1 = strval (cmd);
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar color [0-126] [0-126]");
		        return 1;
			}
		
			idcolor2 = strval (cmd);
			
			CarInfo[tmpidcar][cColorOne] = idcolor1;
			CarInfo[tmpidcar][cColorTwo] = idcolor2;
			
			ChangeVehicleColor(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cColorOne], CarInfo[tmpidcar][cColorTwo]);

            SaveCar(tmpidcar);
			return 1;
		}

		if (strcmp("gas", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar gas [0-100]");
		        return 1;
			}
			if (strval(cmd) < 0 || strval(cmd) > 100)
		    {
		        SendClientMessage(playerid,Rojo,"* Valor invalido de gasolina. USO: /asetcar gas [0-100]");
		        return 1;
			}
			CarInfo[tmpidcar][cGas] = strval(cmd);
			SaveCar(tmpidcar);
			return 1;
		}

		if (strcmp("lock", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
				SendClientMessage(playerid,Blanco,"USO: /asetcar lock [0 - Abierto  /  1 - Cerrado]");
		        return 1;
			}
			if (strval(cmd) != 0 && strval(cmd) != 1)
		    {
		        SendClientMessage(playerid,Rojo,"* Valor invalido. USO: /asetcar lock [0 - Abierto  /  1 - Cerrado]");
		        return 1;
			}
			CarInfo[tmpidcar][cLock] = strval(cmd);
			GetVehicleParamsEx(CarInfo[tmpidcar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(CarInfo[tmpidcar][cId], engine, lights, alarm, CarInfo[tmpidcar][cLock], bonnet, boot, objective);
			SaveCar(tmpidcar);
			return 1;
		}

		if (strcmp("start", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
		        SendClientMessage(playerid,Blanco,"USO: /asetcar start [0 - Parado  /  1 - Arrancado]");
		        return 1;
			}
			if (strval(cmd) != 0 && strval(cmd) != 1)
		    {
		        SendClientMessage(playerid,Rojo,"Valor invalido. Uso: /asetcar start [0 - Parado  /  1 - Arrancado]");
		        return 1;
			}
			CarInfo[tmpidcar][cStarted] = strval(cmd);
			GetVehicleParamsEx(CarInfo[tmpidcar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cStarted], lights, alarm, doors, bonnet, boot, objective);
			SaveCar(tmpidcar);
			return 1;
		}
			
		if (strcmp("broken", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
		        SendClientMessage(playerid,Blanco,"USO: /asetcar broken [0 - Funcional  /  1 - Estropeado]");
		        return 1;
			}
			if (strval(cmd) != 0 && strval(cmd) != 1)
		    {
		        SendClientMessage(playerid,Rojo,"Valor invalido. Uso: /asetcar broken [0 - Funcional  /  1 - Estropeado]");
		        return 1;
			}
			CarInfo[tmpidcar][cBroken] = strval(cmd);
			SaveCar(tmpidcar);
			return 1;
		}
		
		if (strcmp("owned", cmd, true) == 0)
		{
		    cmd = strtokex (cmdtext, idx);
		    if (!strlen(cmd))
		    {
		        SendClientMessage(playerid,Blanco,"USO: /asetcar owned [0 - No tiene Dueño  /  1 - Si tiene]");
		        return 1;
			}
			if (strval(cmd) != 0 && strval(cmd) != 1)
		    {
		        SendClientMessage(playerid,Rojo,"USO: /asetcar owned [0 - No tiene Dueño  /  1 - Si tiene]");
		        return 1;
			}
			CarInfo[tmpidcar][cOwned] = strval(cmd);
			SaveCar(tmpidcar);
			return 1;
		}
		

	    return 1;
	}

	if (strcmp("/carinfo", cmd, true) == 0 || strcmp("/comprobar", cmd, true) == 0)
	{
		new tmpidcar;
		if (PlayerInfo[playerid][pAdmin] > 0)
		{
			tmpidcar = vehiculomascercano(playerid);
			if(CarInfo[tmpidcar][cUsos] < 100)
			{
				format (string, sizeof(string), "[Modelo]: %s - [ID Samp]: %d - [ID Array]: %d - [ID SQL]: %d - [Llave]: %d - [Dueño]: %d - [Propietario]: %s - [Int]: %d", 
					CarInfo[tmpidcar][cDescription], CarInfo[tmpidcar][cId], tmpidcar, CarInfo[tmpidcar][cSQLID], CarInfo[tmpidcar][cCarKey], CarInfo[tmpidcar][cOwned], CarInfo[tmpidcar][cOwner], CarInfo[tmpidcar][cInt]);
				SendClientMessage(playerid,Amarillo,string);
				format (string, sizeof(string), "[Faccion]: %d - [Precio]: %d - [Gas]: %d - [Arrancado]: %d - [Cerrado]: %d - [Averiado]: %d - [Colores]: %d,%d - [VW]: %d",
					CarInfo[tmpidcar][cUsos], CarInfo[tmpidcar][cValue], CarInfo[tmpidcar][cGas], CarInfo[tmpidcar][cStarted], CarInfo[tmpidcar][cLock], CarInfo[tmpidcar][cBroken], CarInfo[tmpidcar][cColorOne], CarInfo[tmpidcar][cColorTwo], CarInfo[tmpidcar][cVw]);
				SendClientMessage(playerid,Amarillo,string);
			}
			else
			{
				format (string, sizeof(string), "[Modelo]: %s - [ID Samp]: %d - [ID Array]: %d - [ID SQL]: %d - [Llave]: %d - [Dueño]: %d - [Propietario]: %s", 
					CarInfo[tmpidcar][cDescription], CarInfo[tmpidcar][cId], tmpidcar, CarInfo[tmpidcar][cSQLID], CarInfo[tmpidcar][cCarKey], CarInfo[tmpidcar][cOwned], CarInfo[tmpidcar][cOwner], CarInfo[tmpidcar][cInt]);
				SendClientMessage(playerid,Amarillo,string);
				format (string, sizeof(string), "[Trabajo]: %d - [Precio]: %d - [Gas]: %d - [Arrancado]: %d - [Cerrado]: %d - [Averiado]: %d - [Colores]: %d,%d - [VW]: %d",
					CarInfo[tmpidcar][cUsos]-100, CarInfo[tmpidcar][cValue], CarInfo[tmpidcar][cGas], CarInfo[tmpidcar][cStarted], CarInfo[tmpidcar][cLock], CarInfo[tmpidcar][cBroken], CarInfo[tmpidcar][cColorOne], CarInfo[tmpidcar][cColorTwo], CarInfo[tmpidcar][cVw]);
				SendClientMessage(playerid,Amarillo,string);
			}
		}
		else if(IsACop(playerid))
		{
			tmp = strtokex(cmdtext, idx);
			if(!strval(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /comprobar [Matricula]");
				return 1;
			}
			
			new id;
			id = strval(tmp);
			tmpidcar = vehiculomascercano(playerid);
			
			if(id == CarInfo[tmpidcar][cCarKey])
			{
				format(string, sizeof(string), "[Propietario]: %s", CarInfo[tmpidcar][cOwner]);
				SendClientMessage(playerid, Amarillo, string);
			}
		}

	    return 1;
	}

	if (strcmp("/afindcar", cmd, true) == 0)
	{
	    if (PlayerInfo[playerid][pAdmin] < 1)
	        return 1;

		cmd = strtokex (cmdtext, idx);
		if (!strlen(cmd))
		{
			SendClientMessage(playerid,Blanco,"USO: /afindcar [IdJugador/ParteDelNombre]");
		    return 1;
		}

		new tmpidplayer, mensaje[80];
		if(!IsNumeric(tmp))
		tmpidplayer = ReturnUser(tmp,playerid);
		else tmpidplayer = strval(tmp);
		if (IsPlayerConnected(tmpidplayer))
		{
		    for (new contador = 0; contador < TotalVeh; contador++)
		    {
		        if (strcmp(CarInfo[contador][cOwner], pNameEx(tmpidplayer), true) == 0)
		        {
		            GetPlayerPos(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
		            TogglePlayerSpectating (playerid, 1);
		            PlayerSpectateVehicle(playerid, CarInfo[contador][cId], SPECTATE_MODE_NORMAL);
		            format (mensaje, 80, "Prop: %s~n~Llave: %d", CarInfo[contador][cOwner], CarInfo[contador][cCarKey]);
		            GameTextForPlayer(playerid, mensaje, 5000, 5);
		            PlayerTmr[playerid] = SetTimerEx("cancelarespectador", 8000, false, "iii", playerid, tmpidplayer, 2);
		            return 1;
				}
			}
			SendClientMessage(playerid, Rojo, "* No se ha encontrado un vehiculo para ese jugador");
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* Jugador no conectado.");
		}
	    return 1;
	}

	if (strcmp("/afixpos", cmd, true) == 0)
	{
	
		if(PlayerInfo[playerid][pAdmin] < 1) { SendClientMessage(playerid,Rojo,"* No formas parte del Staff"); return 1; }
	    new tmpidcar;
	    tmpidcar = vehiculomascercano (playerid);
	    SetVehiclePos(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cLocationx], CarInfo[tmpidcar][cLocationy], CarInfo[tmpidcar][cLocationz]);
		SetVehicleZAngle(CarInfo[tmpidcar][cId], CarInfo[tmpidcar][cAngle]);

	    return 1;
	}
	if (strcmp("/resitecar", cmd, true) == 0)
	{
	    if (PlayerInfo[playerid][pAdmin] < 1)
	        return 1;

	    new tmpcar;
	    
		cmd = strtokex(cmdtext, idx);

		for (new contador = 0; contador < MAX_PLAYERS; contador++)
	    	if (IsPlayerInAnyVehicle(contador))
		    {
		        tmpcar = GetPlayerVehicle(contador);
	    	    Recolocarcoches[tmpcar] = 1;
			}
			
		if (!strlen(cmd))
		{
			SetTimerEx("Recolocarveh", 100, false, "ii", playerid, 30.0);
		}
		else
		{
			if (strcmp(cmd, "autoescuela", true) == 0)
			{
				for(new i = 0;i < TotalVeh; i++)
				{
					if((strcmp(CarInfo[i][cOwner], "autoescuela", true) == 0) && (Recolocarcoches[i] == 0))
					{
						SetVehiclePos(CarInfo[i][cId], CarInfo[i][cLocationx], CarInfo[i][cLocationy], CarInfo[i][cLocationz]);
						SetVehicleZAngle(CarInfo[i][cId], CarInfo[i][cAngle]);
						//Recolocarcoches[i] = NOEXISTE;
					}
					if(Recolocarcoches[i] == 1)
					{
					Recolocarcoches[i] = 0;
					}
				}
				return 1;
			}
			if (strcmp(cmd, "job", true) == 0)
			{
				cmd = strtokex(cmdtext, idx);
				if(!strlen(cmd))
				{
			    	SetTimerEx("RecolocarJobVeh", 100, false, "ii", playerid, 100);
				}
				else
				{
				    new id = strval(cmd);
				    SetTimerEx("RecolocarJobVeh", 100, false, "ii", playerid, id+100);
				}
				return 1;
			}
			if (strcmp(cmd, "team", true) == 0)
			{
				cmd = strtokex(cmdtext, idx);
				if(!strlen(cmd))
				{
			    	SetTimerEx("RecolocarJobVeh", 100, false, "ii", playerid, 0);
				}
				else
				{
				    new id = strval(cmd);
				    SetTimerEx("RecolocarJobVeh", 100, false, "ii", playerid, id);
				}
				return 1;
			}
		}
		return 1;
	}

	if (strcmp("/findadmincar", cmd, true) == 0)
	{
	    if (PlayerInfo[playerid][pAdmin] < 1)
	        return 1;

		for (new contador = 0; contador < TotalVeh; contador++)
		{
		    if (strcmp (CarInfo[contador][cOwner], "Admin", true) == 0 && CarInfo[contador][cCarKey] != 0)
		    {
		        new mensaje[80];
		        format(mensaje, 80, "**   Vehiculo Admin. Llave: %d", CarInfo[contador][cCarKey]);
		        SendClientMessage(playerid, Amarillo, mensaje);
			}
		}
        SendClientMessage(playerid, AzulClaro, "***   Búsqueda finalizada");
		return 1;
	}
	
	if (strcmp("/findteamcar", cmd, true) == 0)
	{
		new tmpteam, tmpcar;
        new mensaje[80];
	    if (PlayerInfo[playerid][pAdmin] < 1)
	    {
	        if (PlayerInfo[playerid][pRank] != 6)
		        return 1;
			else
			    tmpteam = PlayerInfo[playerid][pMember];
		}
		else
		{
			cmd = strtokex (cmdtext, idx);
			if (!strlen(cmd))
			{
				SendClientMessage(playerid,Blanco,"USO: /findteamcar [FacciónID] [LlaveID (Opcional)");
			    return 1;
			}
			tmpteam = strval(cmd);
		}
		
		cmd = strtokex (cmdtext, idx);
		if (!strlen(cmd))
		{
			for (new contador = 0; contador < TotalVeh; contador++)
			{
	    		if (CarInfo[contador][cUsos] == tmpteam)
			    {
			        format(mensaje, 80, "** Vehiculo %s. Llave: %d", CarInfo[contador][cDescription], CarInfo[contador][cCarKey]);
			        SendClientMessage(playerid, Amarillo, mensaje);
				}
			}
	   	    SendClientMessage(playerid, AzulClaro, "***  Finalizada búsqueda de vehículos de facción.");
		}
		else
		{
		    tmpcar = GetPlayerVehicleByKey(strval(cmd));
		    if (tmpcar != NOEXISTE)
		    {
	    		if (CarInfo[tmpcar][cUsos] == tmpteam)
			    {
		            GetPlayerPos(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
		            TogglePlayerSpectating (playerid, 1);
		            PlayerSpectateVehicle(playerid, CarInfo[tmpcar][cId], SPECTATE_MODE_NORMAL);
					format (mensaje, 80, "Prop: %s~n~Llave: %d", CarInfo[tmpcar][cOwner], strval(cmd));
					GameTextForPlayer(playerid, mensaje, 5000, 5);
		            PlayerTmr[playerid] = SetTimerEx("cancelarespectador", 8000, false, "iii", playerid, tmpcar, 1);
				}
		    }
		    else
		    {
		   	    SendClientMessage(playerid, Rojo, "* Llave inválida");
		   	    return 1;
			}
		}

		return 1;
	}

	if (strcmp("/findautoescuela", cmd, true) == 0)
	{
        new mensaje[80];
	    if (PlayerInfo[playerid][pAdmin] < 1) return 1;

		for (new contador = 0; contador < TotalVeh; contador++)
		{
    		if ((strcmp(CarInfo[contador][cOwner], "autoescuela", true) == 0))
			{
			    format(mensaje, 80, "** Vehiculo %s. Llave: %d", CarInfo[contador][cDescription], CarInfo[contador][cCarKey]);
				SendClientMessage(playerid, Amarillo, mensaje);
			}
		}
	   	SendClientMessage(playerid, AzulClaro, "***  Finalizada búsqueda de vehículos de autoescuela.");
		return 1;
	}
	
	if (strcmp("/encendermotor", cmd, true) == 0)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
		//ARRANCAR /ENCENDERMOTOR
		new newcar = GetPlayerVehicle(playerid);
  		return EncenderMotor(playerid,newcar);
   	}
	
	if (strcmp("/apagarmotor", cmd, true) == 0)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
		//APAGAR /APAGARMOTOR
		new newcar = GetPlayerVehicle(playerid);
		return ApagarMotor(playerid,newcar);
	}
	
	if (strcmp("/desguazarveh", cmd, true) == 0)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpidcar;
			tmpidcar = GetPlayerVehicle(playerid);
		    if (!PlayerHaveKeys(playerid, GetPlayerVehicle(playerid)))
		    {
		        return 1;
		    }
			new Conce;
			for(new i; i < MAX_CAR_DATA; i++)
			{
				if(strcmp(CarInfo[tmpidcar][cDescription], datacar[i][dcNombre], true) == 0)
				{
					Conce = datacar[i][dcConcesionario] -1;
					break;
				}
			}
			if (PlayerToPoint(15.0, playerid, Concesionarios[Conce][cX], Concesionarios[Conce][cY], Concesionarios[Conce][cZ]))
			{	
				new result;
			    for(new i; i < MAX_PROPIOS; i++)
				{
					if(PlayerInfo[playerid][pPCarKey][i] == CarInfo[tmpidcar][cCarKey])
					{
						result = 1;
						PlayerInfo[playerid][pPCarKey][i] = NOEXISTE;
						break;
					}
				}
				if(result == 0){SendClientMessage(playerid, Rojo, "* No puedes desguazar coches prestados!");return 1;}
				GameTextForPlayer(playerid,"~g~Vehiculo desguazado",3000,5);
				TogglePlayerControllable(playerid,1);
				DestroyLLLCar(tmpidcar);
				SaveValues(playerid,"Coches");
				return 1;
			}
			else { SendClientMessage(playerid, Rojo, "* No estas en el concesionario donde compraste este coche."); }
		}
		else { SendClientMessage(playerid, Rojo, "Debes estar en el puesto de conductor."); }
		return 1;
	}
	
	if (strcmp("/catalogo", cmd, true) == 0)
	{
		GetPlayerPos(playerid, PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz]);
		if (GetPlayerConcesionario(playerid) > 0)
		{
			format(string, 128, "Bienvenido al 	Concesionario %s, puede observar toda la gama de modelos.", Concesionarios[GetPlayerConcesionarioEx(playerid)][cNombre]);
			GameTextForPlayer(playerid, string, 5000, 5);
			SendClientMessage(playerid, Naranja, "Pulsa SHIFT y ALT en el teclado para cambiar los modelos.");
			SendClientMessage(playerid, Amarillo, "Pulsa ENTER para salir del catálogo");
			if(GetPlayerConcesionario(playerid) == 6)
			{//Aviones
				SetPlayerFacingAngle(playerid, 230.7040);
				SetPlayerCameraPos(playerid, -2236.1682,2334.3647,7.5469);
				SetPlayerCameraLookAt(playerid, -2229.1060,2326.0977,8.2523);
				SetPlayerVirtualWorld(playerid, playerid+1);
				SetPlayerPos(playerid, -2237.7878,2335.6909,7.5469);
			}
			else if(GetPlayerConcesionario(playerid) == 7)
			{//Barcos
				SetPlayerCameraPos(playerid, 723.3899,-1495.9838,1.9343);
				SetPlayerCameraLookAt(playerid, 733.2559,-1506.8319,-0.0312);
				SetPlayerVirtualWorld(playerid, playerid+1);
				SetPlayerPos(playerid, 723.3899,-1495.9838,1.9343);
				SetPlayerFacingAngle(playerid, 217.5417);
			}
			else
			{//Coches
				SetPlayerCameraPos(playerid, -1952.2235,272.1783,41.0471);
				SetPlayerCameraLookAt(playerid, -1951.1927,264.8029,40.7625);
				SetPlayerVirtualWorld(playerid, playerid+1);
				SetPlayerPos(playerid, -1952.2235,272.1783,41.0471);
				SetPlayerFacingAngle(playerid, 189.8909);
			}
			
			if (EnCatalogoVeh[playerid] == NOEXISTE)
			{
				TogglePlayerControllable(playerid,0);
				EnCatalogoVeh[playerid] = 1;
			}
			PConcesionario[playerid] = GetPlayerConcesionario(playerid);
			//printf("Concesionario = %d", PConcesionario[playerid]);
			catalogovehiculos(playerid, PConcesionario[playerid]);
		}
		else
			GameTextForPlayer(playerid, "No estas en el concesionario, debes salir del catalogo.", 3000, 5);
		return 1;
	}

	if (strcmp("/comprarveh", cmd, true) == 0)
	{
	    cmd = strtokex(cmdtext,idx);
	    if (!strlen(cmd))
	    {
	        SendClientMessage(playerid, Blanco, "USO: /comprarveh [VehiculoID] [Color1] [Color2]");
	        return 1;
		}
		
		if(TimerConce == 1) { SendClientMessage(playerid, Rojo, "* Acaban de comprar un coche, espera mientras se guardan los datos..."); return 1; }
				
		if (EnCatalogoVeh[playerid] != NOEXISTE) { SendClientMessage(playerid, Rojo, "* Sal del catálogo para comprar el vehiculo. (ENTER)"); return 1; }
		
		GetPlayerPos(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
		SetPlayerFacingAngle(playerid, 212.2497);
		SetCameraBehindPlayer(playerid);

		new tmpcar;
		tmpcar = strval(cmd);

		if ((PlayerInfo[playerid][pMember] == datacar[tmpcar][dcComprador])
				|| (datacar[tmpcar][dcMember] == 0))
		{
			if(datacar[tmpcar][dcIDModel] == 525)
			{
				if(PlayerInfo[playerid][pHabilidadMecanico] < 20)
				{
					SendClientMessage(playerid, Rojo, "* No tienes suficiente experiencia para conducir este tipo de vehiculos.");
					return 1;
				}
			}
			
			if(datacar[tmpcar][dcNivel] > GetPlayerLevel(playerid))
			{
				SendClientMessage(playerid, Rojo, "* Nivel insuficiente!");
                return 1;
			}
			
			if(PlayerInfo[playerid][pPCarKey][0] != NOEXISTE && PlayerInfo[playerid][pPCarKey][1] != NOEXISTE && PlayerInfo[playerid][pPCarKey][2] != NOEXISTE 
				&& PlayerInfo[playerid][pPCarKey][3] != NOEXISTE && PlayerInfo[playerid][pPCarKey][4] != NOEXISTE)
			{
				SendClientMessage(playerid, Naranja, "* Ya tienes todos los slots de llaves propias ocupados!");	
				return 1;
			}
				
			if(datacar[tmpcar][dcConcesionario] == GetPlayerConcesionario(playerid))
			{
				new Conce = GetPlayerConcesionarioEx(playerid);
				for(new i=0; i < TotalVeh; i++)
				{
					if(VehicleToPoint(10.0, i, Concesionarios[Conce][ctX], Concesionarios[Conce][ctY], Concesionarios[Conce][ctZ]))
					{
						SendClientMessage(playerid, Rojo, "* Hay un vehículo en el punto de entrega, imposible entregar.");
	        			return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No disponemos de ese modelo, deberás buscar en otro concesionario.");
	        	return 1;
			}
				
			if (SafeGetPlayerMoney(playerid) < datacar[tmpcar][dcPrecio])
			{
				SendClientMessage(playerid, Rojo, "* No llevas dinero suficiente. Vuelve en otro momento");
				return 1;
			}
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
			    SendClientMessage(playerid, Blanco, "USO: /comprarveh [VehiculoID] [Color1] [Color2]");
			    return 1;
			}
			new color1;
			color1 = strval(tmp);
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
			    SendClientMessage(playerid, Blanco, "USO: /comprarveh [VehiculoID] [Color1] [Color2]");
			    return 1;
			}

			new color2;
			color2 = strval(tmp);
			for(new i; i < MAX_PROPIOS; i++)
			{
				if(PlayerInfo[playerid][pPCarKey][i] == NOEXISTE)
				{
					PlayerInfo[playerid][pPCarKey][i] = CodigoLlave;
					break;
				}
			}

			SendClientMessage(playerid, Verde, "* Has comprado un nuevo vehículo.");
			SendClientMessage(playerid, Amarillo, "* El vendedor te ha entregado las llaves (mira en /stats)");
			new Conce = datacar[tmpcar][dcConcesionario]-1;
			CreateLLLCar (playerid, tmpcar, Concesionarios[Conce][ctX], Concesionarios[Conce][ctY], Concesionarios[Conce][ctZ], 90.0, color1,color2); //autos
			SafeGivePlayerMoney(playerid, - datacar[tmpcar][dcPrecio]);
			TimerConce = 1;

			SetTimerEx("ResetearTimerConce",10000,0,"");
			SaveValues(playerid, "Coches");
			SaveValues(playerid, "CochesPrestados");
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No puedes comprar este tipo de vehiculo");
		}
		return 1;
	}
	

	if(strcmp(cmd,"/localizarveh", true) == 0)
	{
	    if(SafeGetPlayerMoney(playerid) < 50)
	    {
	        SendClientMessage(playerid, Rojo, "* No tienes dinero suficiente!");
	        return 1;
	    }
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
		    SendClientMessage(playerid, Blanco, "Precio: 50$ | USO: /localizarveh [1/2/3/4/5|6/7/8/9/10]");
		    return 1;
		}
		new coche, car;
		coche = strval(tmp);
		switch(coche)
		{
			case 1..5:
			{
				car = GetPlayerVehicleByKey(PlayerInfo[playerid][pPCarKey][coche-1]);
			}
			case 6..10:
			{
				car = GetPlayerVehicleByKey(PlayerInfo[playerid][pPCochePrestado][coche-6]);
			}
			default:
			{
				SendClientMessage(playerid, Blanco, "Precio: 50$ | USO: /localizarveh [1/2/3/4/5|6/7/8/9/10]");
				return 1;
			}
		}
				
		if(car != -1)
		{
			if((CarInfo[car][cParking] != 0 && CarInfo[car][cParking] != NOEXISTE) && CarInfo[car][eliminado] == -1) { SendClientMessage(playerid, Naranja, "* Tu coche está en un aparcamiento. Usa /verparking para más información."); return 1; }
		    SendClientMessage(playerid, Verde, "[SAT]: Hemos localizado y señalizado el vehículo en tu GPS. (-50$).");
			//SetVehicleParamsForPlayer(CarInfo[car][cId], playerid, 1, 0);
            CarInfo[car][cGPS]=playerid;
            new conductor=-1;
            for (new i;i<MAX_PLAYERS;i++)
            {
                if (GetPlayerVehicle(i) == car && GetPlayerVehicleSeat(i)==0)
                {
                    conductor=i;
                    break;
                }
            }
            if (conductor > -1)
            {
                SetPlayerMarkerForPlayer(playerid, conductor ,Rojo);
            }
            else
            {
                new Float:X,Float:Y,Float:Z;
                GetVehiclePos(CarInfo[car][cId],X,Y,Z);
                SetPlayerCheckpoint(playerid,X,Y,Z,8.0);
                PlayerInfo[playerid][pCheckpoint]=31;

            }
			LocalizandoVehiculo[playerid] = CarInfo[car][cId];
			SafeGivePlayerMoney(playerid, - 50);
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No tienes un vehículo!");
		    return 1;
		}
		return 1;
	}
	
	if(strcmp(cmd,"/maletero", true) == 0)
	{
		new counter = 0;
		new result;

		for(new i=0; i != TotalVeh; i++)
		{
			new dist = CheckPlayerDistanceToVehicle(5.0, playerid, CarInfo[i][cId]);
			if(dist)
			{
				result = i;
				counter++;
			}
		}

		switch(counter)
		{
			case 0:
			{
				SendClientMessage(playerid, Rojo, "* No hay vehículos cerca de ti.");
			}

			case 1:
			{
				if(strcmp(CarInfo[result][cOwner], "autoescuela", true) == 0) return 0;
				if(IsABike(result)) return 0;
  				if (trunkTimer[playerid] != NOEXISTE)
				KillTimer(trunkTimer[playerid]);
				trunkTimer[playerid] = SetTimerEx("CerrarMaletero",60000,0,"dd",result, playerid);
				new engine, lights, alarm, doors, bonnet, boot, objective;
	    		if(CarInfo[result][cOwned] >= 0)
	    		{
					if(PlayerInfo[playerid][pPCocheTemporal] == CarInfo[cocheselect][cCarKey])
					{
						format(string, sizeof(string),"* %s fuerza la puerta trasera de la furgoneta.",pName(playerid));
	    		        ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
						SendClientMessage(playerid, Amarillo, "* Tienes 2 minutos para sacar todas las armas del coche!");
						PlayerInfo[playerid][pPCocheTemporal] = NOEXISTE;
                        Maletero[result]=1;
						GetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, 1, objective);				
                        SetTimerEx("CerrarMaletero",120000,0,"dd",result, playerid);	
					}
	    		    else if(PlayerHaveKeys(playerid, result) == 1 || (PlayerInfo[playerid][pMember] == CarInfo[result][cUsos] && PlayerInfo[playerid][pMember] != 0))
	    		    {
	    		        format(string, sizeof(string),"* %s usa sus llaves y abre el maletero.",pName(playerid));
	    		        ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
                        Maletero[result]=1;
						GetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, 1, objective);	
                        SetTimerEx("CerrarMaletero",60000,0,"dd",result, playerid);
					}
					else if(IsACop(playerid))
					{
     					format(string, sizeof(string),"* %s fuerza el maletero del vehículo con una palanca.",pName(playerid));
	    		        ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
                        Maletero[result]=1;
						GetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, 1, objective);	
                        SetTimerEx("CerrarMaletero",60000,0,"dd",result, playerid);
					}
	    		    else
	    		    {
	    		        SendClientMessage(playerid, Rojo, "* Este no es tu vehículo.");
	    		        return 1;
	    		    }
	    		}
	    		else
	    		{
					format(string, sizeof(string),"* %s abre el maletero del vehículo.",pName(playerid));
     				ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
					Maletero[result]=1;
					GetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(CarInfo[result][cId], engine, lights, alarm, doors, bonnet, 1, objective);	
					SetTimerEx("CerrarMaletero",60000,0,"dd",result, playerid);
				}
		
		    	new buffer[128];
				SendClientMessage(playerid, Naranja, "Maletero del vehículo:");
				for(new slot = 0; slot != MAX_TRUNK_SLOTS; slot++)
				{
					new gunname[100];
					if(CarInfo[result][cSlot][slot]!= NOEXISTE)
					{
						GetWeaponName(CarInfo[result][cSlot][slot], gunname, sizeof(gunname));
						format(buffer, sizeof(buffer), "Espacio %i: %s (Balas: %i)", slot+1, gunname, CarInfo[result][cAmmo][slot]);
						SendClientMessage(playerid, Amarillo, buffer);

					}
				}
				format(buffer, sizeof(buffer),"Marihuana: %d semillas, %d gramos sin preparar, %d preparados",CarInfo[result][cSemillas][0],
                        CarInfo[result][cDrogaNP][0],CarInfo[result][cDrogaP][0]);
                SendClientMessage(playerid, Verde, buffer);
                format(buffer, sizeof(buffer),"Coca: %d semillas, %d gramos sin preparar, %d preparados",CarInfo[result][cSemillas][1],
                        CarInfo[result][cDrogaNP][1],CarInfo[result][cDrogaP][1]);
                SendClientMessage(playerid, Verde, buffer);
                format(buffer, sizeof(buffer),"Crack: %d gramos preparados",CarInfo[result][cDrogaP][2]);
                SendClientMessage(playerid, Verde, buffer);
				SendClientMessage(playerid,Amarillo," Comandos: /guardararma, /tomararma, /guardardrogas, /tomardrogas");
			}
			default:
			{
				SendClientMessage(playerid, Rojo, "* Más de un vehículo detectado cerca, por favor acérquese más a su vehículo.");
			}
		}
		return 1;
	}
	if(strcmp(cmd, "/cerrarmaletero", true) == 0)
	{	
		new counter = 0;
		new result;

		for(new i=0; i != TotalVeh; i++)
		{
			new dist = CheckPlayerDistanceToVehicle(5.0, playerid, CarInfo[i][cId]);
			if(dist)
			{
				result = i;
				counter++;
			}
		}

		switch(counter)
		{
			case 0:
			{
				SendClientMessage(playerid, Rojo, "* No hay vehículos cerca de ti.");
			}

			case 1:
			{
				if(IsABike(result)) return SendClientMessage(playerid, Rojo, "* La bici no tiene maletero!");
				
				KillTimer(trunkTimer[playerid]);
				format(string, sizeof(string),"* %s cierra el maletero del vehículo.",pName(playerid));
     			ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
				CerrarMaletero(result,playerid);
			}
			default:
			{
				SendClientMessage(playerid, Rojo, "* Más de un vehículo detectado cerca, por favor acérquese más a su vehículo.");
			}
		}
		return 1;
	}
	if(strcmp(cmd, "/vermaletero", true) == 0)
	{	
		if(PlayerInfo[playerid][pAdmin] < 1) return 1;
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
		    SendClientMessage(playerid, Blanco, "USO: /vermaletero [LLaveID]");
		    return 1;
		}
		new llaveid;
		llaveid = strval(tmp);	
		new result = GetPlayerVehicleByKey(llaveid);
	   	new buffer[128];
		SendClientMessage(playerid, Naranja, "Maletero del vehículo:");
		for(new slot = 0; slot != MAX_TRUNK_SLOTS; slot++)
		{
			new gunname[100];
			if(CarInfo[result][cSlot][slot]!= NOEXISTE)
			{
				GetWeaponName(CarInfo[result][cSlot][slot], gunname, sizeof(gunname));
				format(buffer, sizeof(buffer), "Espacio %i: %s (Balas: %i)", slot+1, gunname, CarInfo[result][cAmmo][slot]);
				SendClientMessage(playerid, Amarillo, buffer);
			}
		}
		format(buffer, sizeof(buffer),"Marihuana: %d semillas, %d gramos sin preparar, %d preparados",CarInfo[result][cSemillas][0],
        CarInfo[result][cDrogaNP][0],CarInfo[result][cDrogaP][0]);
        SendClientMessage(playerid, Verde, buffer);
        format(buffer, sizeof(buffer),"Coca: %d semillas, %d gramos sin preparar, %d preparados",CarInfo[result][cSemillas][1],
        CarInfo[result][cDrogaNP][1],CarInfo[result][cDrogaP][1]);
        SendClientMessage(playerid, Verde, buffer);
        format(buffer, sizeof(buffer),"Crack: %d gramos preparados",CarInfo[result][cDrogaP][2]);
		SendClientMessage(playerid, Verde, buffer);
		return 1;
	}
	if(strcmp(cmd, "/bloqueo", true) == 0)
	{
	    new carkey, tmpcar, engine, lights, alarm, doors, bonnet, boot, objective;
	    new Float: vX, Float: vY, Float: vZ;
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
		    SendClientMessage(playerid, Blanco, "USO: /bloqueo [1/2/3/4/5|6/7/8/9/10]");
		    return 1;
		}
		new slot;
		slot = strval(tmp);
		if(slot <= MAX_PROPIOS)
		{
			carkey = PlayerInfo[playerid][pPCarKey][slot-1];
		}
		else
		{
			carkey = PlayerInfo[playerid][pPCochePrestado][slot-6];
		}
		
		if (carkey == NOEXISTE)
		{
			SendClientMessage(playerid, Rojo, "* Llave Inválida");
			return 1;
		}

		tmpcar = GetPlayerVehicleByKey(carkey);
		GetVehiclePos(CarInfo[tmpcar][cId], vX, vY, vZ);
		if(PlayerToPoint(5.0, playerid, vX, vY, vZ))
		{
			if (IsABoat (CarInfo[tmpcar][cId]) || IsABike (tmpcar) || IsAMotorcycle (tmpcar))
			{
			    SendClientMessage (playerid, Rojo, "* Este vehiculo no tiene puertas que bloquear");
			    return 1;
			}
			if(CarInfo[tmpcar][cLock] == 0)
			{
				CarInfo[tmpcar][cLock] = 1; 
				GetVehicleParamsEx(CarInfo[tmpcar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(CarInfo[tmpcar][cId], engine, lights, alarm ,CarInfo[tmpcar][cLock], bonnet, boot, objective);
			}
			else
			{
				CarInfo[tmpcar][cLock] = 0;
				GetVehicleParamsEx(CarInfo[tmpcar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(CarInfo[tmpcar][cId], engine, lights, alarm ,CarInfo[tmpcar][cLock], bonnet, boot, objective);
			}
			if(CarInfo[tmpcar][cLock] == 1) {
			    format(string, 128, "[Coche nº%d] Cerrado.",carkey); }
			else {
			    format(string, 128, "[Coche nº%d] Abierto.",carkey); }
			SendClientMessage(playerid, Verde, string);
			if(CarInfo[tmpcar][cSubWoofer] == 0)
			{
				EscucharEfecto(tmpcar, 6, 20.0);
			}
			SaveCar(tmpcar);
		}
		else
		{
			SendClientMessage(playerid, Rojo, "* Estás muy Lejos!");
		}
		return 1;
	}
	
	if(strcmp(cmd, "/adminbloqueo", true) == 0)
	{
	    new contador;
		new keycar, engine, lights, alarm, doors, bonnet, boot, objective;
		for(new i=0; i < TotalVeh; i++)
		{
		    if(CheckPlayerDistanceToVehicle(5.0, playerid, CarInfo[i][cId]))
		    {
		        keycar = i;
		        contador++;
		    }
		}
		if(contador > 1)
		{
		    SendClientMessage(playerid, Rojo, "* Muchos coches alrededor tuyo!");
		    return 1;
		}
		new Float:CarX,Float:CarY,Float:CarZ;
		GetVehiclePos(CarInfo[keycar][cId],CarX,CarY,CarZ);
	    if(IsPlayerConnected(playerid))
	    {
	        if(PlayerInfo[playerid][pAdmin] >= 1)
			{
				if(IsPlayerInVehicle(playerid, CarInfo[keycar][cId]) || PlayerToPoint(5.0, playerid,CarX,CarY,CarZ))
				{
				    if(CarInfo[keycar][cLock] == 1)
				    {
						CarInfo[keycar][cLock] = 0;
						GetVehicleParamsEx(CarInfo[keycar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(CarInfo[keycar][cId], engine, lights, alarm ,CarInfo[keycar][cLock], bonnet, boot, objective);
						SaveCar(keycar);
						for(new i = 0; i < MAX_PLAYERS; i++){SetVehicleParamsForPlayer(CarInfo[keycar][cId],i,0,0);}
					}
					else
					{
					    CarInfo[keycar][cLock] = 1;
						GetVehicleParamsEx(CarInfo[keycar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(CarInfo[keycar][cId], engine, lights, alarm ,CarInfo[keycar][cLock], bonnet, boot, objective);
						SaveCar(keycar);
					}
				}
				else{SendClientMessage(playerid,Rojo,"* No estás cerca de ningún coche!");}
			}
			else{SendClientMessage(playerid,Rojo,"* No formas parte del Staff!");}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/tirarllave", true) == 0)
	{
		cmd = strtokex(cmdtext, idx);
		if(!strlen(cmd))
		{
			SendClientMessage(playerid, Blanco, "USO: /tirarllave [1/2/3/4/5]");
			SendClientMessage(playerid, AzulClaro, "Solo llaves de coches prestadas.");
			return 1;
		}
		
		new tmpllave = strval(cmd);
		if ((tmpllave < 1) && (tmpllave > 5))
		{
			SendClientMessage(playerid, Rojo, "* Llaves entre 1 y 5. USO: /tirarllave [1/2/3/4/5]");
			return 1;
		}
		
		PlayerInfo[playerid][pPCochePrestado][tmpllave-1] = NOEXISTE;

		SendClientMessage(playerid, Rojo, "* Te has deshecho de la llave");
		SaveValues(playerid, "Coches");
		SaveValues(playerid, "CochesPrestados");
		return 1;
	}

/*	if(strcmp(cmd, "/coche", true) == 0) // Coindice con una anim, ademas de que hay que retocarlo. Att Paul
	{
	    new mensaje[128], tmpcar, tmpnombre[MAX_PLAYER_NAME];
	    new texto1[40], texto2[40], texto3[40], texto4[40];
	    new Float:tmpdamage;

		tmpcar = vehiculomascercano(playerid);
		GetPlayerName (playerid, tmpnombre, MAX_PLAYER_NAME);
		GetVehicleHealth(CarInfo[tmpcar][cId], tmpdamage);
		if (strcmp (tmpnombre, CarInfo[tmpcar][cOwner], true) == 0)
		{
		    if (CarInfo[tmpcar][cLock] == 0)
				format (texto1, 40, "~g~Este coche es tuyo~n~Esta abierto");
			else
				format (texto1, 40, "~g~Este coche es tuyo~n~Esta cerrado");

			if (tmpdamage == 1000)
			{
			    format (texto4, 40, "~g~El vehiculo esta nuevo");
			}
			else
			{
				if (tmpdamage > 800)
				    format (texto4, 40, "~g~Tiene algunos roces en la pintura");
				else
				{
					if (tmpdamage > 500)
					    format (texto4, 40, "Tiene abollones en la chapa");
					else
					{
						if (tmpdamage > 250)
						    format (texto4, 40, "Da pena, un milagro que aun ande");
						else
						    format (texto4, 40, " ");
					}
				}
			}
		    format (texto3, 40, "~y~Combustible: %d", CarInfo[tmpcar][cGas]);
		}
		else
		{
		    if (CarInfo[tmpcar][cLock] == 0)
				format (texto1, 40, "~r~Este coche no es tuyo~n~Esta abierto");
			else
				format (texto1, 40, "~r~Este coche no es tuyo~n~Esta cerrado");

			if (tmpdamage == 1000)
			{
			    format (texto4, 40, "~g~El coche esta nuevo");
			}
			else
			{
				if (tmpdamage > 600)
				    format (texto4, 40, "~y~No esta bien cuidado");
				else
				{
					if (tmpdamage > 250)
					    format (texto4, 40, "~r~El propietario lo tiene hecho un asco");
					else
					    format (texto4, 40, " ");
				}
			}
		    format (texto3, 40, " ");
		}

	    if (CarInfo[tmpcar][cStarted] == 0)
			format (texto2, 40, "~r~El motor esta apagado");
		else
			format (texto2, 40, "~g~El motor esta encendido");

		format (mensaje, 128, "~n~~n~~n~%s~n~%s~n~%s~n~%s", texto1, texto2, texto4, texto3);
		GameTextForPlayer(playerid, mensaje, 5000, 4);
		return 1;
	}*/
	
	if(strcmp(cmd, "/crearcoche", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
	        if (PlayerInfo[playerid][pAdmin] < 3)
			{
			    SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
			    return 1;
			}
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /crearcoche [ModelID] [Color1] [Color2]");
				return 1;
			}
			new car;
			car = strval(tmp);
			if(car < 400 || car > 611) { SendClientMessage(playerid, Rojo, "* Número de vehículo entre 400 y 611!"); return 1; }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /crearcoche [ModelID] [Color1] [Color2]");
				return 1;
			}
			new color1;
			color1 = strval(tmp);
			if(color1 < 0 || color1 > 126) { SendClientMessage(playerid, Rojo, "* Número de color no puede ser menor de 0 y mayor de 126!"); return 1; }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /crearcoche [ModelID] [Color1] [Color2]");
				return 1;
			}
			new color2;
			color2 = strval(tmp);
			if(color2 < 0 || color2 > 126) { SendClientMessage(playerid, Rojo, "* Número de color no puede ser menor de 0 y mayor de 126!"); return 1; }
			new Float:X, Float:Y, Float:Z, Float:Angle;
			enfrente (playerid, 5.0, X, Y, Z, Angle);
			CreateLLLCar(playerid, car, X, Y, Z, Angle, color1, color2); // parámetro NOEXISTE para indicar que es de admin
			format(string, sizeof(string), "* Vehículo %d creado.", TotalVeh);
			SendClientMessage(playerid, Amarillo, string);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/healcar", true) == 0)
	{
 		if(PlayerInfo[playerid][pAdmin] >= 1)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /healcar [Vida]");
				return 1;
			}
			new health;
			health = strval(tmp);

			SetVehicleHealth(GetPlayerVehicleID(playerid), health);
       		//format(string, sizeof(string), "AvisoAdmin: %s ha curado su coche por %d", pName(playerid),health);
			//ABroadCast(Amarillo,string,1);
			printf("ADMINLOG: %s ha curado su coche por %d", pName(playerid),health);
		}
		return 1;
	}
	
	if(strcmp(cmd, "/oldcar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
		    format(string, sizeof(string), "* Antiguo vehículo: %d",PlayerInfo[playerid][pLastCar]);
		    SendClientMessage(playerid, Amarillo, string);
	    }
	    return 1;
	}
	
	if(strcmp(cmd, "/quitarcoche", true) == 0)
	{
	 	new car = GetPlayerVehicle(playerid);
	 	if(PlayerInfo[playerid][pAdmin] >= 1)
	 	{
			if (IsPlayerInAnyVehicle(playerid))
			{
		 	    if (strcmp (CarInfo[car][cOwner], "Admin", true) == 0)
		 	    {
					DestroyLLLCar(car);
					SendClientMessage(playerid, Rojo, "* Vehículo eliminado!");
					return 1;
			 	}
			 	else
			 	    SendClientMessage(playerid, Naranja, "* Este coche no lo ha añadido un administrador. No se puede eliminar.");
			}
			else
			{
				cmd = strtokex (cmdtext, idx);
				if (!strlen(cmd))
				{
					SendClientMessage(playerid, Amarillo, "Se aconseja eliminar un vehículo estando dentro, siempre que sea posible");
					SendClientMessage(playerid, Amarillo, "Si no lo es, para eliminarlo a distancia: /quitarcoche [CódigoLlave]");
					return 1;
				}
				new tmpcar;
				tmpcar = GetPlayerVehicleByKey(strval(cmd));
				if (tmpcar == NOEXISTE)
				{
					SendClientMessage(playerid, Rojo, "* Llave inexistente.");
					return 1;
				}

		    	DestroyLLLCar(tmpcar);
				SendClientMessage(playerid, Rojo, "* Vehículo destruido!");
			}
		}
		return 1;
    }
	
	if(strcmp(cmd, "/llenar", true) == 0)
	{
		if(IsAtGasStation(playerid))
		{
			new vehid;
		    if (!IsPlayerInAnyVehicle(playerid))
            vehid = vehiculomascercano(playerid); // jugador fuera del coche, junto a él
			else
			vehid = GetPlayerVehicle(playerid); // jugador dentro del coche

			if(IsABike(vehid)) { SendClientMessage(playerid, Rojo, "* No puedes repostar una bici!"); return 1; }
		
		    new pago;
			cmd = strtokex(cmdtext, idx);
			if(!strlen(cmd))
			    pago = NOEXISTE; // el jugador no establece una cantidad a pagar, lo quiere lleno
			else
			{
			    if (IsNumeric(cmd))
				    pago = strval (cmd);
				else { SendClientMessage(playerid, Rojo, "* Valor de pago incorrecto"); return 1; }
			}
			if(PlayerHaveKeys(playerid,vehid))
			{
				GameTextForPlayer(playerid,"~w~~n~~n~~n~~n~~n~~n~~n~~n~~n~Llenando deposito, espera por favor!",4800,3);
				Refueling[playerid] = 1;
				TogglePlayerControllable(playerid,0);
				PlayerInfo[playerid][pTempFrozen] = 1;
				SetTimerEx("Fillup",5000,0, "ddd", playerid, vehid, pago);
				return 1;
			}
			else { SendClientMessage(playerid,Rojo,"No tienes las llaves"); return 1; }
		}
		else { SendClientMessage(playerid,Rojo,"* No estás en ninguna Gasolinera!"); return 1; }
	}
	
	if(strcmp(cmd,"/llenarlata",true)==0)
    {
		if(IsAtGasStation(playerid))
		{
			if(PlayerInfo[playerid][pLataFuel] > 0) { SendClientMessage(playerid,Rojo,"* Ya tienes la lata llena!"); return 1; }
			new price = 50;
	    	format(string, sizeof(string), "* Llenaste la lata de combustible con 20 litros por %d$",price);
		    SendClientMessage(playerid, Verde, string);
		    PlayerInfo[playerid][pLataFuel] = 20;
			SafeGivePlayerMoney(playerid, -  price);
			return 1;
		}
		else
		{
			SendClientMessage(playerid,Rojo,"* No estás en la gasolinera!");
			return 1;
		}
	}
	if(strcmp(cmd, "/usarlata", true) == 0)
	{
	    if(PlayerInfo[playerid][pLataFuel] > 0)
	    {
			new vehicle = GetPlayerVehicle(playerid);
			if(!IsPlayerInAnyVehicle(playerid)) { SendClientMessage(playerid,Rojo,"* No estás montado en ningún vehículo!"); return 1; }
	        if(CarInfo[vehicle][cGas] < 100)
	        {
		        SendClientMessage(playerid, Verde, "* Llenaste tu vehículo con 20 litros de la lata de combustible.");
		        CarInfo[vehicle][cGas] += 20;
		        PlayerInfo[playerid][pLataFuel] = 0;
			}
			else
			{
			    SendClientMessage(playerid, Naranja, "* El depósito de combustible del vehículo ya está lleno!");
			}
	    }
	    else
	    {
	        SendClientMessage(playerid, Rojo, "* No tienes combustible en la lata!");
	    }
		return 1;
	}
	if(strcmp(cmd, "/quitarllave", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /quitarllave [1/2/3/4/5] [IdJugador/ParteDelNombre]");
			return 1;
		}
		new SlotAQuitar = strval(tmp);
		if ((SlotAQuitar < 1) && (SlotAQuitar > 5))
		{
			SendClientMessage(playerid, Blanco, "USO: /quitarllave [1/2/3/4/5] [IdJugador/ParteDelNombre]");
			return 1;
		}
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /quitarllave [1/2/3/4/5] [IdJugador/ParteDelNombre]");
			return 1;
		}
		new giveplayerid;
		if(!IsNumeric(tmp))
		giveplayerid = ReturnUser(tmp);
		else giveplayerid = strval(tmp);
		
		if (IsPlayerConnected(giveplayerid) && giveplayerid != INVALID_PLAYER_ID)
		{
			new LlaveAQuitar = PlayerInfo[playerid][pPCarKey][SlotAQuitar-1];
			if(PlayerInfo[playerid][pPCarKey][SlotAQuitar-1] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* No tienes ninguna llave en ese slot!"); return 1; }
			
			if(PlayerInfo[giveplayerid][pPCochePrestado][0] != LlaveAQuitar && PlayerInfo[giveplayerid][pPCochePrestado][1] != LlaveAQuitar && 
				PlayerInfo[giveplayerid][pPCochePrestado][2] != LlaveAQuitar && PlayerInfo[giveplayerid][pPCochePrestado][3] != LlaveAQuitar && PlayerInfo[giveplayerid][pPCochePrestado][4] != LlaveAQuitar)
				{ SendClientMessage(playerid, Rojo, "* El jugador no tiene una copia de estas llaves!"); return 1; }
						
			if(PlayerInfo[giveplayerid][pPCochePrestado][0] == LlaveAQuitar) PlayerInfo[giveplayerid][pPCochePrestado][0] = NOEXISTE;
			if(PlayerInfo[giveplayerid][pPCochePrestado][1] == LlaveAQuitar) PlayerInfo[giveplayerid][pPCochePrestado][1] = NOEXISTE;
			if(PlayerInfo[giveplayerid][pPCochePrestado][2] == LlaveAQuitar) PlayerInfo[giveplayerid][pPCochePrestado][2] = NOEXISTE;
			if(PlayerInfo[giveplayerid][pPCochePrestado][3] == LlaveAQuitar) PlayerInfo[giveplayerid][pPCochePrestado][3] = NOEXISTE;
			if(PlayerInfo[giveplayerid][pPCochePrestado][4] == LlaveAQuitar) PlayerInfo[giveplayerid][pPCochePrestado][4] = NOEXISTE;
			
			format(string,sizeof(string),"* Has retirado una copia de las llaves '%d' a %s", LlaveAQuitar, pName(giveplayerid));
			SendClientMessage(playerid,Amarillo,string);
		
			format(string,sizeof(string),"(( %s ha cambiado la cerradura de su coche, la llave '%d' ya no te sirve ))", pName(playerid), LlaveAQuitar);
			SendClientMessage(giveplayerid,Amarillo,string);
	    }
		else { SendClientMessage(playerid, Rojo, "* Jugador no conectado/invalido!"); }
		return 1;		
	}
	if(strcmp(cmd,"/vendercoche",true)==0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /vendercoche [1/2/3/4/5] [IdJugador/ParteDelNombre] [Precio]");
			return 1;
		}
		new SlotAVender = strval(tmp);
		if ((SlotAVender < 1) && (SlotAVender > 5))
		{
			SendClientMessage(playerid, Rojo, "* Llaves entre 1 y 5. USO: /vendercoche [1/2/3/4/5] [IdJugador/ParteDelNombre] [Precio]");
			return 1;
		}
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /vendercoche [1/2/3/4/5] [IdJugador/ParteDelNombre] [Precio]");
			return 1;
		}
		new giveplayerid = ReturnUser(tmp);
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /vendercoche [1/2/3/4/5] [IdJugador/ParteDelNombre] [Precio]");
			return 1;
		}
		new money = strval(tmp);
		if(PlayerInfo[playerid][pPCarKey][SlotAVender-1] == NOEXISTE) { SendClientMessage(playerid, Rojo, "* No tienes ninguna llave en ese slot!"); return 1; }
		if(PlayerInfo[playerid][pOfertaCocheID] != NOEXISTE) { SendClientMessage(playerid, Rojo, "* Ya tienes una oferta de coche pendiente! Usa /cancelar venta."); return 1; }
		if(PlayerInfo[giveplayerid][pOfertaCocheID] != NOEXISTE) { SendClientMessage(playerid, Rojo, "* Ese jugador ya tiene una oferta de coche pendiente!"); return 1; }
		if(money < 1) { SendClientMessage(playerid, Naranja, "* No puedes vender por 0$. Venta cancelada."); return 1; }
		if (IsPlayerConnected(giveplayerid) && giveplayerid != INVALID_PLAYER_ID)
		{
		    if(GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0)
			{
			    if(giveplayerid == playerid)
			    {
			        SendClientMessage(playerid, Rojo, "* No puedes hacer eso a ti mismo!");
			        return 1;
			    }
				if(PlayerInfo[giveplayerid][pPCarKey][0] != NOEXISTE && PlayerInfo[giveplayerid][pPCarKey][1] != NOEXISTE && PlayerInfo[giveplayerid][pPCarKey][2] != NOEXISTE 
					&& PlayerInfo[giveplayerid][pPCarKey][3] != NOEXISTE && PlayerInfo[giveplayerid][pPCarKey][4] != NOEXISTE)
					{ SendClientMessage(playerid, Naranja, "* Ese jugador ya tiene todos los slots de llaves propias ocupados!"); return 1; }
					
				if (SafeGetPlayerMoney(giveplayerid) < money) { SendClientMessage(playerid, Naranja, "* El otro jugador no tiene dinero suficiente para comprarlo."); return 1; }
				
				new LLaveAVender = PlayerInfo[playerid][pPCarKey][SlotAVender-1];
					
				PlayerInfo[playerid][pOfertaCocheID] = giveplayerid;
				PlayerInfo[giveplayerid][pOfertaCocheID] = playerid;
				PlayerInfo[giveplayerid][pOfertaCocheKey] = LLaveAVender;
				PlayerInfo[giveplayerid][pOfertaCocheMoney] = money;
				
				format(string,sizeof(string), "* %s te ofrece su %s por %d$", pName(playerid), CarInfo[GetPlayerVehicleByKey(LLaveAVender)][cDescription], money);
				SendClientMessage(giveplayerid, AzulClaro, string);
				SendClientMessage(giveplayerid, AmarilloClaro, "Usa /aceptar venta para comprar, o /cancelar venta para no comprar.");
					
				format(string,sizeof(string), "* Ofreces tu %s por %d$ a %s", CarInfo[GetPlayerVehicleByKey(LLaveAVender)][cDescription], money, pName(giveplayerid));
				SendClientMessage(playerid, AzulClaro, string);
				SendClientMessage(playerid, AmarilloClaro, "Usa /cancelar venta para cancelar la venta.");
			}
			else { SendClientMessage(playerid, Rojo, "* Jugador no cercano!"); return 1; }
	    }
		else {	SendClientMessage(playerid, Rojo, "* Jugador no conectado/invalido!"); return 1; }
		return 1;
	}
	if(strcmp(cmd, "/echar", true) == 0)
	{
        if(IsPlayerInAnyVehicle(playerid))
        {
	        if(GetPlayerState(playerid)!= PLAYER_STATE_DRIVER)
	        {
	        	SendClientMessage(playerid,Naranja,"* Solo puedes echar gente como conductor!");
	            return 1;
	        }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /echar [IdJugador/ParteDelNombre]");
				return 1;
			}
			new playa = ReturnUser(tmp);
			if(IsPlayerConnected(playa) && playa != INVALID_PLAYER_ID)
			{
		        if(playa == playerid) { SendClientMessage(playerid, Amarillo, "¡Sal del coche sin más, hombre!"); return 1; }
		        if(IsPlayerInVehicle(playa,GetPlayerVehicleID(playerid)))
		        {
					format(string, sizeof(string), "* Has echado a %s del vehículo!", pName(playa));
					SendClientMessage(playerid, AzulClaro, string);
					format(string, sizeof(string), "* %s te echó a golpes del vehículo.", pName(playerid));
					SendClientMessage(playa, AzulClaro, string);
					RemovePlayerFromVehicle(playa);
					return 1;
				}
				else
				{
				    SendClientMessage(playerid, Rojo, "* Ese jugador no está en tu vehículo!");
				    return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* Nombre /Id Invalida!");
			}
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No estás en un vehículo!");
		}
		return 1;
	}
	if(strcmp(cmd, "/capota", true) == 0)
	{
        if(IsPlayerInAnyVehicle(playerid))
        {
			new arrayid = GetPlayerVehicle(playerid);
	        if(GetPlayerState(playerid)!= PLAYER_STATE_DRIVER)
	        {
	        	SendClientMessage(playerid,Naranja,"* Solo puedes hacer eso como conductor!");
	            return 1;
	        }
			if(GetVehicleModel(CarInfo[arrayid][cId]) == 567 || GetVehicleModel(CarInfo[arrayid][cId]) == 536)
			{
				if(CarInfo[arrayid][cComp][2] == 1131 || CarInfo[arrayid][cComp][2] == 1103)
				{
					if(CarInfo[arrayid][cStarted] != 0) { SendClientMessage(playerid, Naranja, "* Apaga el vehiculo primero!"); return 1; }
					if(GetVehicleComponentInSlot(CarInfo[arrayid][cId],2) == 1131 || GetVehicleComponentInSlot(CarInfo[arrayid][cId],2) == 1031)
					{
						if(GetVehicleModel(CarInfo[arrayid][cId]) == 567) RemoveVehicleComponent(CarInfo[arrayid][cId],1131);
						else if(GetVehicleModel(CarInfo[arrayid][cId]) == 536) RemoveVehicleComponent(CarInfo[arrayid][cId],1103);
						format(string, sizeof(string), "* %s pliega la capota del coche.",pName(playerid));
						ProxDetector(15.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
					}
					else
					{
						if(GetVehicleModel(CarInfo[arrayid][cId]) == 567) AddVehicleComponent(CarInfo[arrayid][cId],1131);
						else if(GetVehicleModel(CarInfo[arrayid][cId]) == 536) AddVehicleComponent(CarInfo[arrayid][cId],1103);
						format(string, sizeof(string), "* %s pone la capota del coche.",pName(playerid));
						ProxDetector(15.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* No tienes una capota instalada en tu coche, instalala primero!");
				}
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* Solo funcional en Blade o Savanna!");
			}
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No estás en un vehículo!");
		}
		return 1;
	}
	return 0;
}	

Vehicles_OnPlayerStateChange(playerid, oldstate, newstate)
{
	#pragma unused newstate
	#pragma unused oldstate
	new newcar;
	newcar = GetPlayerVehicle(playerid);
	new estado;
	estado = GetPlayerState(playerid);
	if(estado == PLAYER_STATE_DRIVER)
	{
		PlayerInfo[playerid][pLastCar] = CarInfo[GetPlayerVehicle(playerid)][cCarKey];
		
		if(CarInfo[newcar][cModel] == 531 && PlayerInfo[playerid][pJob] != 2)
		{
			RemovePlayerFromVehicle(playerid);
			TogglePlayerControllable(playerid,1);
			SendClientMessage(playerid, Rojo, "* No tienes el empleo necesario para acceder a éste vehículo.");
			return 1;
		}
		/*else if(CarInfo[newcar][cModel] == 499 && PlayerInfo[playerid][pJob] != 7)
		{
			RemovePlayerFromVehicle(playerid);TogglePlayerControllable(playerid,1);
			return SendClientMessage(playerid, Rojo, "* No tienes el empleo necesario para acceder a éste vehículo.");
		}*/
		else if(PlayerInfo[playerid][pAdminDuty] == 0 && strcmp(CarInfo[newcar][cOwner], "autoescuela", true) == 0 && PlayerInfo[playerid][EnClase] < 2)
		{
			RemovePlayerFromVehicle(playerid);TogglePlayerControllable(playerid,1);
			SendClientMessage(playerid, Rojo, "* No estás haciendo ningún exámen de la autoescuela.");
			return 1;
		}
		
		/*if(LocalizandoVehiculo[playerid] == CarInfo[newcar][cId]) 
		{
			SetVehicleParamsForPlayer(LocalizandoVehiculo[playerid], playerid, 0, 0);
			RemovePlayerFromVehicle(playerid);
			OnPlayerExitVehicle(playerid, LocalizandoVehiculo[playerid]);
			RespawnVehicle(LocalizandoVehiculo[playerid]);
			PutPlayerInVehicle(playerid, LocalizandoVehiculo[playerid], 0);
			LocalizandoVehiculo[playerid] = NOEXISTE;
			return 1;
		}*/
		
		if(IsABike(newcar))
		{
			if(PlayerHaveKeys(playerid,newcar) || PlayerInfo[playerid][pMember] == CarInfo[newcar][cUsos] || PlayerInfo[playerid][pJob] == (CarInfo[newcar][cUsos] - 100))
			{
				SetVehicleParamsEx(CarInfo[newcar][cId],1,0,0,0,0,0,0);
				return 1;
			}
			else
			{
				SendClientMessage(playerid, Rojo, "* No puedes conducir esta bici.");
				new Float:x,Float:y,Float:z;
				GetPlayerPos(playerid,x,y,z);
				SetPlayerPos(playerid,x,y,z+2);
				return 1;
			}
		}
		
		if(CarInfo[newcar][cGas] == 0)
		{
			GameTextForPlayer(playerid,"~w~~n~~n~~n~~n~~n~~n~~n~~n~No hay combustible~n~Usa /salir para abandonar el vehiculo",1500,3);
			return 1;
		}
		
		if (IsABoat(CarInfo[newcar][cId]))
		{
		    SendClientMessage(playerid, Rojo, "* Navegar sin licencia es ilegal, además de peligroso.");
		}
		else if (IsAPlane(CarInfo[newcar][cId]))
		{
		    SendClientMessage(playerid, Rojo, "* Pilotar sin licencia es ilegal, además de peligroso.");
		}
		else
		{
			if(PlayerInfo[playerid][pCarLic] == 0 || PlayerInfo[playerid][pCarLic] == 2)
	    	{
				if(PlayerInfo[playerid][EnClase] != 2) SendClientMessage(playerid, Rojo, "* Conducir sin licencia es ilegal, además de peligroso.");
			}
		}


		if(CarInfo[newcar][cUsos] < 100)
		{
			if ((PlayerInfo[playerid][pMember] == CarInfo[newcar][cUsos]) && (CarInfo[newcar][cUsos] != FACCION_CIUDADANO))
			{
			    if (CarInfo[newcar][cStarted] == 0)
			    {
				    SendClientMessage(playerid, Verde, "* Coges las llaves y las pones en el contacto.");
				    SendClientMessage(playerid, Verde, "* Para encender el motor del vehículo pulsa 'ALT' (o /encendermotor)");
				}
				else
				{
				    SendClientMessage(playerid, Verde, "* Este vehículo ya tiene el motor en marcha.");
				}
			    return 1;
			}
		}
		else
		{
		    if (PlayerInfo[playerid][pJob] == (CarInfo[newcar][cUsos] - 100))
			{
			    if (CarInfo[newcar][cStarted] == 0)
			    {
				    SendClientMessage(playerid, Verde, "* Coges las llaves y las pones en el contacto.");
				    SendClientMessage(playerid, Verde, "* Para encender el motor del vehículo pulsa 'ALT' (o /encendermotor)");
				}
				else
				{
				    SendClientMessage(playerid, Verde, "* Este vehículo ya tiene el motor en marcha.");
				}
			    return 1;
			}
		}

		
		if(PlayerHaveKeys(playerid, newcar))
		{
			if(CarInfo[newcar][cStarted] == 0)
			{
			    SendClientMessage(playerid, Verde, "* Para encender el motor del vehículo pulsa 'ALT' (o /encendermotor)");
				return 1;
			}
			else
			{
			    SendClientMessage(playerid, Amarillo, "* ¡Te has dejado el vehículo encendido!");
			    return 1;
			}
		}
		else
		{
		    if ((PlayerInfo[playerid][pAdmin] > 0) && (strcmp (CarInfo[newcar][cOwner], "Admin", true) == 0))
		    {
			    SendClientMessage(playerid, Azul, "* Usas este vehiculo con poder de Mod / Admin.");
			    SendClientMessage(playerid, Azul, "* Para eliminarlo del juego, usa /quitarcoche dentro del vehiculo.");
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(CarInfo[newcar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(CarInfo[newcar][cId], 1, lights, alarm, doors, bonnet, boot, objective);
			    return 1;
			}
			
	    	switch (CarInfo[newcar][cUsos])
		    {
		        case FACCION_CIUDADANO:
		        {
					if(CarInfo[newcar][cStarted] == 1)
					{
					    SendClientMessage(playerid, Amarillo, "* Algún tonto se ha dejado el vehículo encendido.");
					    SendClientMessage(playerid, Amarillo, "* Si conduces este vehículo estarás cometiendo un robo.");
						return 1;
					}
					else
					{
						if (PlayerInfo[playerid][pJob] == 11)
						{
						    SendClientMessage(playerid, Verde, "* Para encender el motor del vehículo escribe /puente");
							return 1;
						}
				    	SendClientMessage(playerid, Rojo, "* No puedes conducir este vehículo. Usa /salir para abandonarlo");
						return 1;
					}
		        }
		        case FACCION_POLICIA: { SendClientMessage(playerid, Rojo, "* No eres policía o no tienes las llaves.");SafeResetPlayerWeaponsAC(playerid);}
				default: { SendClientMessage(playerid, Rojo, "* No perteneces a la organización o no tienes las llaves.");}
			}
			RemovePlayerFromVehicle(playerid);
		}
		return 1;
	}
	return 1;
}

stock LockCar(carid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SetVehicleParamsForPlayer(carid,i,0,1);
		}
	}
}

stock UnLockCar(carid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(!IsAPlane(carid))
			{
				SetVehicleParamsForPlayer(carid,i,0,0);
			}
		}
	}
}

Vehicle_OnPlayerExitVehicle(playerid, vehicleid)
{
	#pragma unused vehicleid
	new tmpcar;
	tmpcar = GetPlayerVehicle(playerid);
	CarInfo[tmpcar][cFixPos] = 1;
    
	TogglePlayerControllable (playerid, 1);
    
    if (CarInfo[tmpcar][cGPS] > -1  && GetPlayerVehicleSeat(playerid)==0)
    {
        new Float:X,Float:Y,Float:Z;
        GetVehiclePos(CarInfo[tmpcar][cId],X,Y,Z);
        SetPlayerMarkerForPlayer(CarInfo[tmpcar][cGPS], playerid, 0xFFFFFF00);
        SetPlayerCheckpoint(CarInfo[tmpcar][cGPS],X,Y,Z,8.0);
        PlayerInfo[CarInfo[tmpcar][cGPS]][pCheckpoint]=31;
    }
	SetTimerEx("FixVPos", 10000, 0, "d", tmpcar);
	return 1;
}

EncenderMotor(playerid,newcar)
{
	if(IsABike(CarInfo[newcar][cId])) return 0;
	//else if(IsABoat(CarInfo[newcar][cId])) return 0;
	else if(PlayerHaveKeys(playerid, newcar))
	{
		if(PlayerInfo[playerid][pTempFrozen] == 1) return 0;
		if(CarInfo[newcar][cBroken] == 1) return SendClientMessage(playerid, Rojo, "* El vehiculo está destrozado!");
		if(CarInfo[newcar][cGas] == 0) return SendClientMessage(playerid, Rojo, "* El vehiculo no tiene gasolina!");
		if(CarInfo[newcar][cSubWoofer] == 1) return SendClientMessage(playerid, Rojo, "* Desactiva el subwoofer primero!");
		format(string, sizeof(string), "* %s pone la llave en el contacto y enciende el motor.",pName(playerid));
		ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
		GameTextForPlayer(playerid,"~r~Encendiendo motor...",3000,1);
		EscucharEfecto(newcar, 2, 20.0);
		PlayerInfo[playerid][pTempFrozen] = 1;
		SetTimerEx("Start",3500,0,"ic",playerid,newcar);
		return 1;
  	}
   	else if(CarInfo[newcar][cUsos] > 0)
	{
		if(CarInfo[newcar][cUsos] < 100)
		{
			if ((PlayerInfo[playerid][pMember] == CarInfo[newcar][cUsos]) && (CarInfo[newcar][cUsos] != FACCION_CIUDADANO))
			{
				if(PlayerInfo[playerid][pTempFrozen] == 1) return 0;
				if(CarInfo[newcar][cBroken] == 1) return SendClientMessage(playerid, Rojo, "* El vehiculo está destrozado!");
				if(CarInfo[newcar][cGas] == 0) return SendClientMessage(playerid, Rojo, "* El vehiculo no tiene gasolina!");
				if(CarInfo[newcar][cSubWoofer] == 1) return SendClientMessage(playerid, Rojo, "* Desactiva el subwoofer primero!");
				format(string, sizeof(string), "* %s pone la llave en el contacto y enciende el motor.",pName(playerid));
				ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
				GameTextForPlayer(playerid,"~r~Encendiendo motor...",3000,1);
				EscucharEfecto(newcar, 2, 20.0);
				PlayerInfo[playerid][pTempFrozen] = 1;
				SetTimerEx("Start",3500,0,"ic",playerid,newcar);
				return 1;
			}
		}
		else if (PlayerInfo[playerid][pJob] == (CarInfo[newcar][cUsos] - 100))
		{
			if(PlayerInfo[playerid][pTempFrozen] == 1) return 0;
			if(CarInfo[newcar][cBroken] == 1) return SendClientMessage(playerid, Rojo, "* El vehiculo está destrozado!");
			if(CarInfo[newcar][cGas] == 0) return SendClientMessage(playerid, Rojo, "* El vehiculo no tiene gasolina!");
			if(CarInfo[newcar][cSubWoofer] == 1) return SendClientMessage(playerid, Rojo, "* Desactiva el subwoofer primero!");
			format(string, sizeof(string), "* %s pone la llave en el contacto y enciende el motor.",pName(playerid));
			ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
			GameTextForPlayer(playerid,"~r~Encendiendo motor...",3000,1);
			EscucharEfecto(newcar, 2, 20.0);
			PlayerInfo[playerid][pTempFrozen] = 1;
			SetTimerEx("Start",3500,0,"ic",playerid,newcar);
			return 1;
		}
	}
   	else return SendClientMessage(playerid, Rojo, "* No tienes las llaves de este vehículo.");
	return 1;
}

ApagarMotor(playerid,newcar)
{
	if(IsABike(newcar)) return 0;
	format(string, sizeof(string), "* %s saca las llaves del contacto y apaga el motor.",pName(playerid));
	ProxDetector(20.0, playerid, string, Morado, Morado, Morado, Morado, Morado);
	SendClientMessage(playerid, Verde, "* Usa /salir para abandonar el vehículo.");
	GameTextForPlayer(playerid,"~r~Apagando motor...",2800,1);
	CarInfo[newcar][cStarted] = 0;
	ActualizarVolumenEmisora(newcar);
	SaveCar(newcar);
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[newcar][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(CarInfo[newcar][cId],CarInfo[newcar][cStarted], lights, alarm, doors, bonnet, boot, objective);
	return 1;
}

forward Start(playerid,carid);
public Start(playerid,carid)
{
	new rand = random(200);
 	if(rand > 1)
  	{
		PlayerInfo[playerid][pTempFrozen] = 0;
		GameTextForPlayer(playerid,"~g~Vehiculo encendido.",3000,1);
		CarInfo[carid][cStarted] = 1;
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(CarInfo[carid][cId], engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(CarInfo[carid][cId], CarInfo[carid][cStarted], lights, alarm, doors, bonnet, boot, objective);
		CarInfo[carid][cVolumen] = 100;
		ActualizarEmisora(carid);
		SaveCar(carid);
	}
	else
	{
		PlayerInfo[playerid][pTempFrozen] = 0;
	    CarInfo[carid][cBroken] = 1;
		SetVehicleHealth(CarInfo[carid][cId], 400);
		SaveCar(carid);
	    GameTextForPlayer(playerid,"~r~Vehiculo averiado.",3000,1);
	    SendClientMessage(playerid, Naranja, "* El vehículo se ha averiado al intentar arrancar.");
	}
	return 1;
}

Vehicles_OnPlayerConnect(playerid)
{
	EnCatalogoVeh[playerid] = NOEXISTE;
	VehCatalogo[playerid] = NOEXISTE;
	LocalizandoVehiculo[playerid] = NOEXISTE;
	return 1;
}

Vehicles_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	if(LocalizandoVehiculo[playerid] > NOEXISTE)
	{
		//SetVehicleParamsForPlayer(LocalizandoVehiculo[playerid], playerid, 0, 0);
		LocalizandoVehiculo[playerid] = NOEXISTE;
	}
	EnCatalogoVeh[playerid] = NOEXISTE;
	if (VehCatalogo[playerid] != NOEXISTE)
	{
		DestroyVehicle(VehCatalogo[playerid]);
		VehCatalogo[playerid] = NOEXISTE;
	}
	
	if(TextToggle[playerid] == 1)
	{
		TextToggle[playerid] = 0;
		for(new i; i < MAX_VEHICLES; i++)
		{
			DeletePlayer3DTextLabel(playerid, CarText[playerid][i]);
		}
	}
	
	if(PlayerInfo[playerid][pOfertaCocheID] >= 0 && PlayerInfo[playerid][pOfertaCocheKey] == NOEXISTE)
	{
		new giveplayerid = PlayerInfo[playerid][pOfertaCocheID];
		if(PlayerInfo[giveplayerid][pOfertaCocheID] == playerid)
		{
			format(string,sizeof(string),"* %s se ha desconectado. Venta de coche cancelada!",pName(playerid));
			SendClientMessage(giveplayerid, Amarillo, string);
			PlayerInfo[giveplayerid][pOfertaCocheID] = NOEXISTE;
			PlayerInfo[giveplayerid][pOfertaCocheKey] = NOEXISTE;
			PlayerInfo[giveplayerid][pOfertaCocheMoney] = 0;
			return PlayerInfo[playerid][pOfertaCocheID] = NOEXISTE;	
		}
	}
	if(PlayerInfo[playerid][pOfertaCocheID] >= 0 && PlayerInfo[playerid][pOfertaCocheKey] >= 0 && PlayerInfo[playerid][pOfertaCocheMoney] > 0)
	{
		new giveplayerid = PlayerInfo[playerid][pOfertaCocheID];
		if(PlayerInfo[giveplayerid][pOfertaCocheID] == playerid)
		{
			format(string,sizeof(string),"* %s se ha desconectado. Venta de coche cancelada!",pName(playerid));
			SendClientMessage(giveplayerid, Amarillo, string);
			PlayerInfo[playerid][pOfertaCocheID] = NOEXISTE;
			PlayerInfo[playerid][pOfertaCocheKey] = NOEXISTE;
			PlayerInfo[playerid][pOfertaCocheMoney] = 0;
			return PlayerInfo[giveplayerid][pOfertaCocheID] = NOEXISTE;	
		}
	}
	if(PlayerInfo[playerid][pOfreciendoS] >= 0 && PlayerInfo[playerid][pOfreciendoC] == 0)
	{
		new giveplayerid = PlayerInfo[playerid][pOfreciendoS];
		if(PlayerInfo[giveplayerid][pOfreciendoS] == playerid)
		{
			format(string,sizeof(string),"* %s se ha desconectado. Venta de seguro cancelada!",pName(playerid));
			SendClientMessage(giveplayerid, Amarillo, string);
			PlayerInfo[giveplayerid][pOfreciendoS] = NOEXISTE;
			PlayerInfo[giveplayerid][pOfreciendoC] = 0;
			return PlayerInfo[playerid][pOfreciendoS] = NOEXISTE;	
		}
	}
	if(PlayerInfo[playerid][pOfreciendoS] >= 0 && PlayerInfo[playerid][pOfreciendoC] > 0)
	{
		new giveplayerid = PlayerInfo[playerid][pOfreciendoS];
		if(PlayerInfo[giveplayerid][pOfreciendoS] == playerid)
		{
			format(string,sizeof(string),"* %s se ha desconectado. Venta de coche cancelada!",pName(playerid));
			SendClientMessage(giveplayerid, Amarillo, string);
			PlayerInfo[playerid][pOfreciendoS] = NOEXISTE;
			PlayerInfo[playerid][pOfreciendoC] = 0;
			return PlayerInfo[giveplayerid][pOfreciendoS] = NOEXISTE;	
		}
	}
	return 1;
}

stock RespawnVehicle(vehicleid)
{
	new idx;
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(vehicleid == CarInfo[i][cId])
		{
			idx = i;
			break;
		}
	}
	if(CarInfo[idx][cUsos] == 0 && !(strcmp(CarInfo[vehicleid][cOwner], "autoescuela", true) == 0))
	{
		GetVehiclePos(vehicleid, CarInfo[idx][cLocationx], CarInfo[idx][cLocationy], CarInfo[idx][cLocationz]);
		SaveCar(idx);
		SetVehicleToRespawn(vehicleid);
		SetVehiclePos(vehicleid, CarInfo[idx][cLocationx], CarInfo[idx][cLocationy], CarInfo[idx][cLocationz]);
	}
	else
	{
		GetVehiclePos(vehicleid, CarInfo[idx][cTmpx], CarInfo[idx][cTmpy], CarInfo[idx][cTmpz]);
		SetVehicleToRespawn(vehicleid);
		SetVehiclePos(vehicleid, CarInfo[idx][cTmpx], CarInfo[idx][cTmpy], CarInfo[idx][cTmpz]);
	}
	
	ChangeVehiclePaintjob(CarInfo[idx][cId], CarInfo[idx][cPaintJob]);
		
	new Comp[14][10];
	split(CarInfo[idx][cComponentes],Comp,',');
	for(new i = 0; i < 14; i++)
	{
		CarInfo[idx][cComp][i] = strval(Comp[i]);
		if(CarInfo[idx][cComp][i] > 0)	AddVehicleComponent(CarInfo[idx][cId], CarInfo[idx][cComp][i]);
	}
	
	new Partes[5][10];
	split(CarInfo[idx][cDanos],Partes,',');
	for(new i = 0; i < 5; i++)
	{
		if(i == 4)
		{
			CarInfo[idx][cDamage] = floatstr(Partes[i]);
		}
		else
		{
			CarInfo[idx][cDano][i] = strval(Partes[i]);
		}
	}
	UpdateVehicleDamageStatus(CarInfo[idx][cId],CarInfo[idx][cDano][0],CarInfo[idx][cDano][1],CarInfo[idx][cDano][2],CarInfo[idx][cDano][3]);
	SetVehicleHealth(CarInfo[idx][cId], CarInfo[idx][cDamage]);
	return 1;
}

stock GetCarKey(vehicleid)
{
	return CarInfo[vehicleid][cCarKey];
}

ConsumirGasolina()
{
	// Consumo de combustible si el motor está encendido
	for (new i = 0; i < TotalVeh; i++)
	{
		if(IsAPlane(CarInfo[i][cId])) { continue; }
		if(IsABoat(CarInfo[i][cId])) { continue; }
		if (CarInfo[i][cStarted] == 1)
		{
			{
				if (CarInfo[i][cGas] == 0)
				{
					CarInfo[i][cStarted] = 0;
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(CarInfo[i][cId], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(CarInfo[i][cId], CarInfo[i][cStarted], lights, alarm, doors, bonnet, boot, objective);
				}
				else if(CarInfo[i][cUsos] < 100 && CarInfo[i][cUsos] != 1 && CarInfo[i][cUsos] != 2 && CarInfo[i][cUsos] != 3 && CarInfo[i][cUsos] != 4 && CarInfo[i][cUsos] != 6 && !IsABike(i) && !(strcmp(CarInfo[i][cOwner], "autoescuela", true) == 0))
				{
					if(CarInfo[i][cGas] > 100) CarInfo[i][cGas] = 99;
					else CarInfo[i][cGas]--;
				}
			}
		}
	}
	return 1;
}

stock IsAtGasStation(playerid)
{
	if(PlayerToPoint(15.0,playerid,1004.0070,-939.3102,42.1797) || PlayerToPoint(15.0,playerid,1944.3260,-1772.9254,13.3906)) return 1; // LS
	else if(PlayerToPoint(15.0,playerid,-90.5515,-1169.4578,2.4079) || PlayerToPoint(15.0,playerid,-1609.7958,-2718.2048,48.5391)) return 1; // LS
	else if(PlayerToPoint(15.0,playerid,-2029.4968,156.4366,28.9498) || PlayerToPoint(15.0,playerid,-2408.7590,976.0934,45.4175)) return 1; // SF
	else if(PlayerToPoint(15.0,playerid,-2243.9629,-2560.6477,31.8841) || PlayerToPoint(15.0,playerid,-1676.6323,414.0262,6.9484)) return 1; //Between LS and SF
	else if(PlayerToPoint(15.0,playerid,2202.2349,2474.3494,10.5258) || PlayerToPoint(15.0,playerid,614.9333,1689.7418,6.6968)) return 1; // LV
	else if(PlayerToPoint(15.0,playerid,-1328.8250,2677.2173,49.7665) || PlayerToPoint(15.0,playerid,70.3882,1218.6783,18.5165)) return 1; // LV
	else if(PlayerToPoint(15.0,playerid,655.4630,-565.0519,15.8758)) return 1; // LV
	else if(PlayerToPoint(15.0,playerid,2113.7390,920.1079,10.5255) || PlayerToPoint(15.0,playerid,-1327.7218,2678.8723,50.0625)) return 1; // LV
	else if(PlayerToPoint(15.0,playerid,1262.9064,-1661.1958,17.9884)) return 1; // SEC
	else if(PlayerToPoint(15.0,playerid,1381.9622,456.7426,19.86)) return 1; 
	else if(PlayerToPoint(15.0,playerid,1596.0240,2198.8435,10.75)) return 1; 
	else if(PlayerToPoint(15.0,playerid,2637.5271,1106.4844,10.7488)) return 1; 
	else if(PlayerToPoint(15.0,playerid,2148.2817,2748.7183,10.759)) return 1; 
	else if(PlayerToPoint(15.0,playerid,1477.0997,1863.0142,32.404)) return 1; 
	else if(PlayerToPoint(15.0,playerid,2527.2910,-1529.5762,24.0012)) return 1; // Taller taxistas
	else if(PlayerToPoint(15.0,playerid,1622.1447,-2169.8442,13.1751)) return 1; 
	else if(PlayerToPoint(15.0,playerid,611.9585,1695.1058,6.7358)) return 1; 
	else if(PlayerToPoint(15.0,playerid,605.5297,1704.5707,6.7390)) return 1; 
	else if(PlayerToPoint(15.0,playerid,622.2368,1680.2150,6.7357)) return 1; 
	else if(PlayerToPoint(15.0,playerid,-1470.5610,1864.3929,32.3763)) return 1; 
//	else if(PlayerToPoint(8.0,playerid,2976.4685,-1489.5551,-0.2474)) return 1; // Barcos
	return 0;
}

forward Fillup(playerid, vehid, pago);
public Fillup(playerid, vehid, pago)
{
    new fillup, total;

	if(Refueling[playerid] == 1)
    {
		if (pago == NOEXISTE) 		// cálculo de gasolina a llenar
		    fillup = 100 - CarInfo[vehid][cGas]; // lleno
		else
		{
  				fillup = (pago / 2); // pago fijo indicado por el jugador
		}
		if (fillup > (100 - CarInfo[vehid][cGas]))
		{
		    fillup = 100 - CarInfo[vehid][cGas]; // lleno
			return 1;
		}

	    total = fillup*2;

		if(SafeGetPlayerMoney(playerid) >= total)
		{
			CarInfo[vehid][cGas] += fillup;
			SendClientMessage(playerid, Amarillo, "____________[Gasolinera]_____________");
			SendClientMessage(playerid, Blanco, "Precio/Litro: 2$");
			format(string, sizeof(string), "Litros pagados: %d L",fillup);
			SendClientMessage(playerid, Blanco, string);
			new descuento;
			if(PremiumValido(playerid,1))
			{
				descuento = (total / 100) * 5;
			}
			else if(PremiumValido(playerid,2))
			{
				descuento = (total / 100) * 10;
			}
			else if(PremiumValido(playerid,3))
			{
				descuento = (total / 100) * 15;
			}
			if(descuento > 0)
			{
				total -= descuento;
				format(string,sizeof(string),"Descuento: $%d",descuento);
				SendClientMessage(playerid, Blanco,string);
			}
			format(string, sizeof(string), "Total: %d$",total);
			SendClientMessage(playerid, AmarilloClaro, string);
			SafeGivePlayerMoney(playerid, - total);
			TogglePlayerControllable(playerid,1);
		    PlayerInfo[playerid][pTempFrozen] = 0;
			return Refueling[playerid] = 0;
		}
	   	else
	   	{
			TogglePlayerControllable(playerid,1);
	   	    format(string,sizeof(string),"* No tienes suficiente dinero, cuesta %d$ llenar el depósito.",total);
		    PlayerInfo[playerid][pTempFrozen] = 0;
			return SendClientMessage(playerid,Naranja,string);
	   	}
 	}
	return 1;
}

SetVehiclePosiEx(vehicleid, playerid, Float:X, Float:Y, Float:Z)
{
	SetVehiclePos(vehicleid, X,Y,Z);
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("Descongelar", 2000, 0, "d", playerid);
	return 1;
} 

forward ResetearTimerConce();
public ResetearTimerConce()
{
	return TimerConce = 0;
}

forward FixVPos(tmpcar);
public FixVPos(tmpcar)
{
	if(CarInfo[tmpcar][cUsos] == 0 && !(strcmp(CarInfo[tmpcar][cOwner], "autoescuela", true) == 0))
	{
		//print("Es un coche de civil, saquemos las coordenadas");
		GetVehiclePos(CarInfo[tmpcar][cId], CarInfo[tmpcar][cLocationx], CarInfo[tmpcar][cLocationy], CarInfo[tmpcar][cLocationz]);
		GetVehicleZAngle(CarInfo[tmpcar][cId], CarInfo[tmpcar][cAngle]);
		SaveCar(tmpcar);
	}
	else
	{
		//print("No es un coche de civil, saquemos las coordenadas temporales");
	    GetVehiclePos(CarInfo[tmpcar][cId], CarInfo[tmpcar][cTmpx], CarInfo[tmpcar][cTmpy], CarInfo[tmpcar][cTmpz]);
	    GetVehicleZAngle(CarInfo[tmpcar][cId], CarInfo[tmpcar][cTmpa]);
	}
	CarInfo[tmpcar][cFixPos] = 0;
	return 1;
}

forward Intermitentes(coche);
public Intermitentes(coche)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[coche][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	if(lights == 1)
	{
		SetVehicleParamsEx(CarInfo[coche][cId], engine, false, alarm, doors, bonnet, boot, objective);
	}
	else
	{
		SetVehicleParamsEx(CarInfo[coche][cId], engine, true, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}