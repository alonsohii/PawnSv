#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

new armaid = NOEXISTE;
new cuenta[MAX_PLAYERS];
new prods[MAX_PLAYERS];
new ultimacuenta;
new timerocupado[MAX_PLAYERS];

new Float:UbicacionesPosibles[7][4] = {
	{158.6217,-22.3992,1.6458,88.5529},
	{1391.2380,381.9784,19.8246,247.3490},
	{2320.0481,63.1006,26.5502,358.3146},
	{657.7421,-499.4246,16.4072,0.5283},
	{-2180.0024,-2425.3511,30.6925,231.6867},
	{1402.1122,360.5889,19.1839,247.6865},
	{90.0245,-303.2902,1.3502,178.3179}	
};

Armas_OnGameModeInit()
{
	ReconocerCoche();
	return 1;
}

ReconocerCoche()
{
	for(new i; i < TotalVeh; i++)
	{
		if(strcmp(CarInfo[i][cDescription], "Corrupto", true) == 0)
		{
			cocheselect = i;
			break;
		}
	}
	if(cocheselect == NOEXISTE)
	{
		CreateLLLCar(0, 498, 158.6217,-22.3992,1.6458,88.5529,-1,-1);
		format(CarInfo[TotalVeh-1][cDescription], 32, "Corrupto");
		cocheselect = TotalVeh-1;
		SaveCar(cocheselect);
	}
}

IncomingCall(playerid, producto[])
{
	if(strcmp(producto, "9mm", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 600) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una 9mm.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 22;
						CarInfo[cocheselect][cAmmo][armaid] = 50;
						armaid++;
						cuenta[playerid] += 600;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Katana", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 5000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una katana.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 8;
						CarInfo[cocheselect][cAmmo][armaid] = 1;
						armaid++;
						cuenta[playerid] += 5000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Molotov", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 1000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito molotovs.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 18;
						CarInfo[cocheselect][cAmmo][armaid] = 5;
						armaid++;
						cuenta[playerid] += 1000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Eagle", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 700) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una Eagle.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 24;
						CarInfo[cocheselect][cAmmo][armaid] = 50;
						armaid++;
						cuenta[playerid] += 700;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Recortada", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 1000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una recortada.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 26;
						CarInfo[cocheselect][cAmmo][armaid] = 30;
						armaid++;
						cuenta[playerid] += 1000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Spas12", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 10000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una Spas 12.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 27;
						CarInfo[cocheselect][cAmmo][armaid] = 60;
						armaid++;
						cuenta[playerid] += 10000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "MP5", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 3000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una MP5.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 29;
						CarInfo[cocheselect][cAmmo][armaid] = 300;
						armaid++;
						cuenta[playerid] += 3000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "AK47", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 8000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una AK47.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 30;
						CarInfo[cocheselect][cAmmo][armaid] = 200;
						armaid++;
						cuenta[playerid] += 8000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
	        }
	    }
	}
	else if(strcmp(producto, "M4", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 12000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una M4.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 31;
						CarInfo[cocheselect][cAmmo][armaid] = 200;
						armaid++;
						cuenta[playerid] += 12000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
	        }
	    }
	}
	else if(strcmp(producto, "Sniper", true) == 0)
	{
	    for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 25000) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una sniper.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 34;
						CarInfo[cocheselect][cAmmo][armaid] = 30;
						armaid++;
						cuenta[playerid] += 25000;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
	        }
	    }
	}
	else if(strcmp(producto, "mac10", true) == 0)
	{
		for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 1200) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una Mac10.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 28;
						CarInfo[cocheselect][cAmmo][armaid] = 300;
						armaid++;
						cuenta[playerid] += 1200;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Nos vemos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "escopeta", true) == 0)
	{
		for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 800) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{	
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una escopeta.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 25;
						CarInfo[cocheselect][cAmmo][armaid] = 30;
						armaid++;
						cuenta[playerid] += 800;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Nos vemos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "navaja", true) == 0)
	{
		for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 50) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito una navaja.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 4;
						CarInfo[cocheselect][cAmmo][armaid] = 1;
						armaid++;
						cuenta[playerid] += 50;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							ultimacuenta = cuenta[playerid];
							armaid = 0;
							cuenta[playerid] = 0;
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Nos vemos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Nudillos", true) == 0)
	{
		for(new i; i < MAX_NEGOCIOS; i++)
	    {
	        if(NegocioInfo[i][nType] == 6)
	        {
	            if(NegocioInfo[i][nProd] >= (1000 + prods[playerid]))
	            {
					if((cuenta[playerid] + 50) > PlayerInfo[playerid][pBank])
					{
						SendClientMessage(playerid, Amarillo, "(Teléfono): No creo que puedas pagar eso... elige otra cosa.");
					}
					else
					{
						SendClientMessage(playerid, Gris, "(Teléfono): Necesito unos nudillos.");
						SendClientMessage(playerid, Amarillo, "(Teléfono): Bien.");
						CarInfo[cocheselect][cSlot][armaid] = 1;
						CarInfo[cocheselect][cAmmo][armaid] = 1;
						armaid++;
						cuenta[playerid] += 50;
						prods[playerid] += 1000;
						if(armaid == 8)
						{
							new ubicacion = random(sizeof(UbicacionesPosibles));
							format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
							SendClientMessage(playerid, Amarillo, string);
							SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
							SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
							SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
							PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
							PlayerInfo[playerid][pCheckpoint] = 30;
							PlayerInfo[playerid][pBank] -= cuenta[playerid];
							SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
							Hacer_Consumo(playerid, prods[playerid]);
							armaid = 0;
							cuenta[playerid] = 0;
							ultimacuenta = cuenta[playerid];
							SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Nos vemos.");
							SendClientMessage(playerid, Gris, " Colgaron.");
							SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
							PlayerInfo[playerid][pHablandoArmas] = 0;
							SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
						}
						else
						{
							format(string, 128, "(Teléfono): ¿Algo más? Puedes pedirme %d cosas más.", (8-armaid));
							SendClientMessage(playerid, Amarillo, string);
							SendClientMessage(playerid, Amarillo, "(Teléfono): Tengo 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
							SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
							SendClientMessage(playerid, Gris, "PISTA: Escribe 'Nada mas' para terminar la compra.");
						}
					}
	            }
				else
				{
					SendClientMessage(playerid, Amarillo, "(Teléfono): No tengo más de esas.");
				}
				break;
	        }
	    }
	}
	else if(strcmp(producto, "Nada mas", true) == 0 || strcmp(producto, "Nada", true) == 0)
	{
		if(armaid == 0)
		{
			format(string, 128, "(Teléfono): %s", producto);
			SendClientMessage(playerid, Gris, string);
			SendClientMessage(playerid, Amarillo, "(Teléfono): Qué manera de perder tiempo y dinero, macho.");
			SendClientMessage(playerid, Gris, " Colgaron.");
			PlayerInfo[playerid][pHablandoArmas] = 0;
			CocheOcupado = 0;
		}
		else
		{
			new ubicacion = random(sizeof(UbicacionesPosibles));
			format(string, 128, "(Teléfono): Todo saldrá $%d, me los cobraré de tu cuenta bancaria.", cuenta[playerid]);
			SendClientMessage(playerid, Amarillo, string);
			SetVehiclePos(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2]);
			SetVehicleZAngle(CarInfo[cocheselect][cId], UbicacionesPosibles[ubicacion][3]);
			SetPlayerCheckpoint(playerid, UbicacionesPosibles[ubicacion][0], UbicacionesPosibles[ubicacion][1], UbicacionesPosibles[ubicacion][2], 8.0);
			PlayerInfo[playerid][pPCocheTemporal] = CarInfo[cocheselect][cCarKey];
			PlayerInfo[playerid][pCheckpoint] = 30;
			PlayerInfo[playerid][pBank] -= cuenta[playerid];
			SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
			Hacer_Consumo(playerid, prods[playerid]);
			ultimacuenta = cuenta[playerid];
			armaid = 0;
			cuenta[playerid] = 0;
			SendClientMessage(playerid, Amarillo, "(Teléfono): La ubicación del coche abandonado está marcada en tu GPS. Tienes 5 minutos.");
			SendClientMessage(playerid, Gris, " Colgaron.");
			SendFamilyMessageOnDuty(1, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
			SendFamilyMessageOnDuty(6, Naranja, "* Camara de vigilancia: Se han visto movimientos sospechosos de coches a las afueras de la ciudad.");
			PlayerInfo[playerid][pHablandoArmas] = 0;
			timerocupado[playerid] = SetTimerEx("DesocuparCoche", 300000, 0, "d", playerid);
		}
	}
	else
	{
		SendClientMessage(playerid, Amarillo, "(Teléfono): No te entiendo, solo tengo: 9mm ($300), Mac10 ($1200), Escopeta ($800), Navaja ($50), Katana ($5000),");
		SendClientMessage(playerid, Amarillo, "(Teléfono): Molotov ($1000), Eagle ($700), Recortada ($1000), Spas10 ($10000), MP5 ($3000),");
		SendClientMessage(playerid, Amarillo, "(Teléfono): AK47 ($8000), M4 ($12000), Sniper ($25000)");
	}
}

Armas_OnPlayerConnect(playerid)
{
	armaid = 0;
	cuenta[playerid] = 0;
	PlayerInfo[playerid][pPCocheTemporal] = NOEXISTE; //temporal - Solucion a /maletero
	return 1;
}

Armas_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 30)
	{
		if(PlayerInfo[playerid][pPCocheTemporal] != NOEXISTE)
		{
			DisablePlayerCheckpoint(playerid);
			CocheOcupado = 0;
			KillTimer(timerocupado[playerid]);
			PlayerInfo[playerid][pCheckpoint] = 0;
		}
		return 1;
	}
	return 0;
}

forward DesocuparCoche(playerid);
public DesocuparCoche(playerid)
{
	CocheOcupado = 0;
	SendClientMessage(playerid, Amarillo, "SMS: Te has demorado mucho, he tenido que mover el coche a otro sitio. Te devuelvo la mitad de tu dinero.");
	PlayerInfo[playerid][pBank] += ultimacuenta/2;
	SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
	return 1;
}

forward Hacer_Consumo(playerid, cantidad);
public Hacer_Consumo(playerid, cantidad)
{
	for(new i; i < MAX_NEGOCIOS; i++)
	{
		if(NegocioInfo[i][nType] == 6)
		{
			NegocioInfo[i][nProd] -= cantidad;
			SaveNegocio(i);
		}
	}
	prods[playerid] = 0;
	return 1;
}
