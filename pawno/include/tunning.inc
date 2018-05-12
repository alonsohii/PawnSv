#include <a_samp>
#include <globalvars>
#include <Seif_Vehicle>
#include <funciones>
#include <negocios>
#include <deathac>
#pragma tabsize 0
//Dialog style
#define DIALOGID 1338
//Variables
static pmodelid[MAX_PLAYERS];
static pvehicleid[MAX_PLAYERS];
//Fowards
forward ModCar(playerid);

new ColorElegido1[MAX_PLAYERS];
new ColorElegido2[MAX_PLAYERS];

#define MAX_TALLERES 9

new Float:Talleres[MAX_TALLERES][3] = {
	{2111.3093,-1934.3367,13.3828},
	{1790.1410,-1903.4978,13.1342},
	{2772.9312,-1623.4125,10.5623},
	{2525.1384,-1525.5135,23.9996},
	{1604.2780,-2154.6558,13.5594},
	{1543.3695,-1708.3140,5.8906},
	{1500.0585,-1483.5030,14.3332}, // GayPalmer
	{612.8947,-607.9156,17.2266}, // Sheriff
    {572.7250,1646.5559,6.9922}
};

////////////////////////////////////////////////////////////////////////////////
Tunning_OnPlayerCommandText(playerid, cmdtext[]) {

	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);

	if(strcmp(cmdtext, "/modificar", true) == 0) {

		if(!IsPlayerInTaller(playerid))
		{
			SendClientMessage(playerid, Rojo, "* Debes estar en algun taller de LS!");
			return 1;
		}
		
		if(PlayerInfo[playerid][pJob] != 1)
		{
		    SendClientMessage(playerid, Rojo, "* No tienes la experiencia necesaria para modificar vehículos.");
		    return 1;
		}
		
		if(PlayerInfo[playerid][pHabilidadMecanico] < 100)
		{
			SendClientMessage(playerid, Rojo, "* No tienes la experiencia necesaria para modificar vehículos.");
			return 1;
		}
	
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
	
		new playerstate = GetPlayerState(playerid);
		if(playerstate == PLAYER_STATE_DRIVER) {
		    { ModCar(playerid); }
		}
		else {
		   { SendClientMessage(playerid, Rojo, "* Tienes que estar dentro de un coche."); }
		}
		return 1;
	}
	
	
	if(strcmp(cmd, "/repintar", true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 1)
		{
     		SendClientMessage(playerid, Rojo, "* No eres mecánico!");
       		return 1;
	    }
		
		if(PlayerInfo[playerid][pHabilidadMecanico] < 50)
		{
			SendClientMessage(playerid, Rojo, "* No tienes suficiente experiencia para pintar vehículos.");
			return 1;
		}
		
		if(!IsPlayerInTaller(playerid))
		{
			SendClientMessage(playerid, Rojo, "* Debes estar en un taller de Los Santos.");
			return 1;
		}
		
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
		
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /repintar [IdJugador/ParteDelNombre] [color] [color2] [precio]");
			SendClientMessage(playerid, Blanco, "Costo por uso: 50 productos.");
			return 1;
		}
		new playa;
		playa = strval(tmp);
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /repintar [IdJugador/ParteDelNombre] [color] [color2] [precio]");
			SendClientMessage(playerid, Blanco, "Costo por uso: 50 productos.");
			return 1;
		}
		new color;
		color = strval(tmp);
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /repintar [IdJugador/ParteDelNombre] [color] [color2] [precio]");
			SendClientMessage(playerid, Blanco, "Costo por uso: 50 productos.");
			return 1;
		}
		new color2;
		color2 = strval(tmp);
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /repintar [IdJugador/ParteDelNombre] [color] [color2] [precio]");
			SendClientMessage(playerid, Blanco, "Costo por uso: 50 productos.");
			return 1;
		}
		new precio;
		precio = strval(tmp);
		if(IsPlayerConnected(playa))
		{
  			if((GetDistanceBetweenPlayers(playerid, playa) < 8.0) && (IsPlayerInAnyVehicle(playa)))
			{
    			format(string, sizeof(string), "* Ofreciste a %s pintar su auto a %d$ .",pName(playa),precio);
				SendClientMessage(playerid, Azul, string);
				format(string, sizeof(string), "* El mecánico %s quiere pintar tu coche por %d$, (Escribe /aceptar pintura) para aceptar.",pName(playerid),precio);
				SendClientMessage(playa, Azul, string);
				PlayerInfo[playa][pRepaintOffer] = playerid;
				PlayerInfo[playa][pRepaintPrice] = precio;
				PlayerInfo[playa][pRepaintColor] = color;
				PlayerInfo[playa][pRepaintColor2] = color2;
			}
			else
			{
			    SendClientMessage(playerid, Rojo, "* El jugador no esta conectado, o no está en un coche.");
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/rellenar", true) == 0)
	{
	
	    if(IsPlayerConnected(playerid))
	    {
			if(PlayerInfo[playerid][pJob] != 1)
			{
		        SendClientMessage(playerid, Rojo, "* No eres mecánico.");
		        return 1;
		    }
			
			if(PlayerInfo[playerid][pHabilidadMecanico] < 10)
			{
				SendClientMessage(playerid, Rojo, "* No tienes suficiente experiencia para rellenar vehículos.");
				return 1;
			}
			
			if(!IsPlayerInTaller(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
			{
				SendClientMessage(playerid, Rojo, "* Debes estar en un taller o en una grúa.");
				return 1;
			}
			
			if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
			
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /rellenar [IdJugador/ParteDelNombre] [Litros] [precio]");
				return 1;
			}
			new playa;
			new money;
			new litros;
			playa = strval(tmp);
			tmp = strtokex(cmdtext, idx);
			litros = strval(tmp);
			if(litros < 1 || litros > 100) { SendClientMessage(playerid, Rojo, "* Máximo 100 litros y mínimo 1."); return 1; }
			tmp = strtokex(cmdtext, idx);
			money = strval(tmp);
			if(money < 1 || money > 1000) { SendClientMessage(playerid, Rojo, "* Precio mínimo 1, y máximo 1000."); return 1; }
			if(IsPlayerConnected(playa))
			{
			    if(playa != INVALID_PLAYER_ID)
			    {
			        if((GetDistanceBetweenPlayers(playerid, playa) < 8.0) && IsPlayerInAnyVehicle(playa) )
					{
						if(HacerConsumo(playerid, litros) != 1)
						{
							SendClientMessage(playerid, Rojo, "* No tienes suficientes piezas y herramientas.");
							return 1;
						}
					    format(string, sizeof(string), "* Ofreciste %s para llenarle %d litros de su depósito por %d$ .",pName(playa), litros, money);
						SendClientMessage(playerid, Azul, string);
						format(string, sizeof(string), "* El mecánico %s quiere llenar %d litros de tu deposito por %d$, (Escribe /aceptar rellenar) para aceptar.",pName(playerid), litros, money);
						SendClientMessage(playa, Azul, string);
						PlayerInfo[playa][pRefillOffer] = playerid;
						//printf("Dinero a cobrar: %d", money);
						PlayerInfo[playa][pRefillPrice] = money;
						PlayerInfo[playa][pRefillAmount] = litros;
					}
					else
					{
					    SendClientMessage(playerid, Rojo, "* El jugador no esta conectado, o no está en un coche.");
					}
				}
			}
			else
			{
			    SendClientMessage(playerid, Rojo, "* Jugador no conectado.");
			}
		}
		return 1;
	}
	
	if(strcmp(cmd, "/reparar", true) == 0)
	{
	    if(IsPlayerConnected(playerid))
	    {
			if(PlayerInfo[playerid][pJob] != 1)
			{
		        SendClientMessage(playerid, Rojo, "* No eres mecánico!");
		        return 1;
		    }
			
			if(PlayerInfo[playerid][pProductos] < 25)
			{
				SendClientMessage(playerid, Rojo, "* No tienes suficientes piezas o herramientas.");
				return 1;
			}
			
			if(!IsPlayerInTaller(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
			{
				SendClientMessage(playerid, Rojo, "* Debes estar en algun taller o en una grua.");
				return 1;
			}
			
			if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
			
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /reparar [IdJugador/ParteDelNombre] [precio]");
				return 1;
			}
			new playa;
			new money;
			playa = strval(tmp);
			if(playa != playerid)
			{
				tmp = strtokex(cmdtext, idx);
				money = strval(tmp);
				if(money < 1 || money > 1000) { SendClientMessage(playerid, Rojo, "* Precio mínimo 1, y máximo 1000!"); return 1; }
				if(IsPlayerConnected(playa))
				{
				    if(playa != INVALID_PLAYER_ID)
				    {
				        if((GetDistanceBetweenPlayers(playerid, playa) < 10.0) && (IsPlayerInAnyVehicle(playa)))
						{
						    format(string, sizeof(string), "* Ofreciste a %s reparar su vehículo por %d$ .",pName(playa),money);
							SendClientMessage(playerid, Azul, string);
							format(string, sizeof(string), "* El mecánico %s quiere reparar tu vehículo por %d$, (Escribe /aceptar reparar) para aceptar.",pName(playerid),money);
							SendClientMessage(playa, Azul, string);
							PlayerInfo[playa][pRepairOffer] = playerid;
							PlayerInfo[playa][pRepairPrice] = money;
						}
						else
						{
						    SendClientMessage(playerid, Rojo, "* El jugador no esta conectado, o no está en un coche.");
						}
					}
				}
				else
				{
				    SendClientMessage(playerid, Rojo, "* Jugador no conectado.");
				}
			}
			else
			{
			    TogglePlayerControllable(playerid,0);
			    GameTextForPlayer(playerid,"~r~Reparando vehiculo",20000,5);
				SetTimerEx("timer_reparar", 20000, 0, "d", playerid);
			}
		}
		return 1;
	}
	
	if(strcmp(cmd,"/grua",true)==0)
	{
	    if(PlayerInfo[playerid][pJob] == 1 || IsACop(playerid))
	    {
			if(IsPlayerInAnyVehicle(playerid))
			{
				new gruaid = GetPlayerVehicle(playerid);
				if(GetVehicleModel(CarInfo[gruaid][cId]) == 525)
				{
					if(GetPlayerState(playerid)==2)
					{
						tmp = strtokex(cmdtext, idx);
						new matricula = strval(tmp);
						if(!strlen(tmp))
						{
							SendClientMessage(playerid, Blanco, "USO: /grua [Matricula del Coche]");
							return 1;
						}
						if(matricula != CarInfo[gruaid][cCarKey])
						{                      
							new remolcado = GetPlayerVehicleByKey(matricula);
							new Float:GX,Float:GY,Float:GZ,Float:RX,Float:RY,Float:RZ;
							GetVehiclePos(CarInfo[gruaid][cId],GX,GY,GZ);
							GetVehiclePos(CarInfo[remolcado][cId],RX,RY,RZ);
							if(PointToPoint3D(7.0, GX, GY, GZ, RX, RY, RZ))
							{
								if(IsTrailerAttachedToVehicle(CarInfo[gruaid][cId]))
								{
									DetachTrailerFromVehicle(CarInfo[gruaid][cId]);
									return 1;
								}
								AttachTrailerToVehicle(CarInfo[remolcado][cId],CarInfo[gruaid][cId]);
								SendClientMessage(playerid, Amarillo, "Has remolcado correctamente el coche.");
							}
							else
							{
								SendClientMessage(playerid, Rojo, "* El vehiculo está demasiado lejos / matricula incorrecta!");
								return 1;
							}
						}
						else
						{
							SendClientMessage(playerid, Rojo, "* No puedes remolcarte a ti mismo!");
							return 1;
						}
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Necesitas ser el conductor!");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, Naranja, "* Necesitas la grúa para hacer esto.");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid,Naranja,"* Necesitas ser Mecánico/Policía para hacer eso!");
			return 1;
		}
		return 1;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
forward Tunning_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
public Tunning_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOGID)
	{
		if(response)
		{
			if(listitem == 0) //Vinilo y pintura
			{
				ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Selecciona el vinilo y la pintura (10000 C/U)", "Vinilo 1\nVinilo 2\nVinilo 3\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 1) //Colors
			{
				ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
			}
			if(listitem == 2) //Exhausts
			{
				ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien\nWheel Arch X-Flow\nLocos Low Chromer\nLocos Low Slamin\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 3) //Front Bumpers
			{
				ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien \nWheel Arch X-Flow \nLocos Low Chromer \nLocos Low Slamin \nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 4) //Rear Bumpers
			{
				ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien\nWheel Arch X-Flow\nLocos Low Chromer \nLocos Low Slamin\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 5) //Roofs
			{
				ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Vent\nWheel Arch X-Flow Vent\nLocos Low Hardtop\nLocos Low Softtop\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 6) //Spoilers
			{
				ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien\nX-Flow\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 7) //SideSkirts
			{
				ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales  (3000 C/U)", "Wheel Arch Alien\nWheel Arch X-Flow\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
			}
            if(listitem == 8) //Bullbars
			{
				ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Selecciona las parrillas  (1500 C/U)", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome \nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 9) //Wheels
			{
				ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 10) //Car stereo
			{
				ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Selecciona el sistema de sonido.", "Estereo normal (1000 C/U)\nEstereo X-Flow (5000 C/U)\nEstereo Alien (10000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 11) //Menu de modificaciones 2
			{
				ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Menu de modificaciones", "Hydraulica (20000 C/U)\nNitro x10 (25000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 12) //Wheels2
			{
				ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
			}
       }
	   else
	   {
			SaveCar(GetPlayerVehicle(playerid));
	   }
   }

   if(dialogid == DIALOGID+1) //Vinilo y pinturas
   {
		if(response)
		{
			if(listitem == 0)
			{
				if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560 ||
				pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 535 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 558)
		        {
		            if(HacerConsumo(playerid, 10000) == 0)
		            {
		            	    SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
		                    return 1;
		            }
					new car = GetPlayerVehicleID(playerid);
					ChangeVehiclePaintjobEx(car,0);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,Amarillo, "* Has puesto el vinilo.");
                    ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Selecciona el vinilo y la pintura (10000 C/U)", "Vinilo 1\nVinilo 2\nVinilo 3\nVolver", "Seleccionar", "Salir");

				}
				else
				{
					SendClientMessage(playerid,Rojo,"* Los vinilos no cuadran en este coche.");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
				}
			}
			if(listitem == 1)
			{
				if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560 ||
				pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 535 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 558)
                {
		            if(HacerConsumo(playerid, 10000) == 0)
		            {
		            	    SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
		                    return 1;
		            }
					new car = GetPlayerVehicleID(playerid);
					ChangeVehiclePaintjobEx(car,1);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,Amarillo, "* Has puesto el vinilo.");
					ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Selecciona el vinilo y la pintura (10000 C/U)", "Vinilo 1\nVinilo 2\nVinilo 3\nVolver", "Seleccionar", "Salir");
				}
				else
				{
					SendClientMessage(playerid,Rojo,"* No se puede poner vinilo en este coche");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
				}
			}
			if(listitem == 2)
			{
				if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560 ||
				pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 535 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 558)
                {
		            if(HacerConsumo(playerid, 10000) == 0)
		            {
		            	    SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
		                    return 1;
		            }
					new car = GetPlayerVehicleID(playerid);
					ChangeVehiclePaintjobEx(car,2);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,Amarillo, "* Has puesto el vinilo.");
					ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Selecciona el vinilo y la pintura (10000 C/U)", "Vinilo 1\nVinilo 2\nVinilo 3\nVolver", "Seleccionar", "Salir");
				}
				else
				{
					SendClientMessage(playerid,Rojo,"* No se puede poner vinilo en este coche");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
				}
			}
			if(listitem == 3)
			{
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
			}
	   }
   }

   if(dialogid == DIALOGID+2) //Colours
   {
		if(response)
		{
			if(listitem == 0)
			{
					new car = GetPlayerVehicleID(playerid);
					ChangeVehicleColor(car,0,0); //Black
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 0;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 0;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de negro.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 1)
			{
		            new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,1,1);//White
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 1;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 1;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de blanco.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 2)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,3,3);//Red
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 3;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 3;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de rojo.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 3)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,79,79); //Blue
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 79;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 79;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de azul.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 4)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,86,86);//Green
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 86;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 86;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de verde.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 5)
			{
					new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,6,6); //Yellow
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 6;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 6;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de amarillo.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 6)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,126,126);//Pink
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 126;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 126;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,Amarillo, "* Has pintado el coche de rosa.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
			if(listitem == 7)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,66,66);//Brown
					CarInfo[GetPlayerVehicle(playerid)][cColorOne] = 66;
					CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = 66;
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	          		SendClientMessage(playerid,Amarillo, "* Has pintado el coche de marron.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Selecciona el color", "Negro\nBlanco\nRojo\nAzul\nVerde\nAmarillo\nRosa\nMarron\nVolver\nOtro", "Seleccionar", "Salir");
					SaveCar(GetPlayerVehicle(playerid));
			}
            if(listitem == 8)
			{
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }
			if(listitem == 9)
			{
					PlayerInfo[playerid][pEligiendoColores] = 1;
					SendClientMessage(playerid,Amarillo, "* Escribe el primer color.");
			}
		}
   }

   if(dialogid == DIALOGID+3) //Exhausts
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Exausts
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
				pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 1000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
		        
		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponentEx(car,1034);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		            	SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch Alien Exhaust en el Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1046);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch Alien Exhaust en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1065);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch Alien Exhaust en el Jetser.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1064);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch Alien Exhaust en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1028);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch Alien Exhaust en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1089);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch Alien Exhaust en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
	    			}
	    			}
	  			 	else
					{
				    SendClientMessage(playerid,Rojo,"* El componente no se puede añadir a este coche");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
                    }
            }
			if(listitem == 1)//Wheel Arch Cars X-Flow Exausts
            {
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
				pmodelid[playerid] == 560)
                {
					if(HacerConsumo(playerid, 1000) == 0)
					{
         	            SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                        return 1;
					}
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponentEx(car,1037);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch X-Flow Exhaust en el Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1045);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch X-Flow Exhaust en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1066);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch X-Flow en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1059);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch X-Flow Exhaust en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1029);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch X-Flow Exhaust en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1092);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Wheel Arch X-Flow Exhaust en el Uranus.");
						format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
						ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
				}
				else
				{
					SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
				}
            }
			if(listitem == 2)//Locos Low Co. Cars Chromer Exausts
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)

			    {
                   if(HacerConsumo(playerid, 1000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponentEx(car,1044);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		             	SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Locos Low Chromer en el Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponentEx(car,1126);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Locos Low Chromer en el Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1129);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	                    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Locos Low Chromer en el Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1104);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Locos Low Chromer en el Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponentEx(car,1113);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Locos Low Chromer en el Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1136);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					   	SendClientMessage(playerid,Amarillo, "* Has añadido el tubo de escape Locos Low Chromer en el Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
			if(listitem == 3)//Locos Low Co. Cars Salmin Exausts
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
			    {
					if(HacerConsumo(playerid, 1000) == 0)
					{
         	            SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                        return 1;
					}
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponentEx(car,1043);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo,"* Has añadido el tubo de escape Locos Low Slamin en el  Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponentEx(car,1127);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo,"* Has añadido el tubo de escape Locos Low Slamin en el  Remingon.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1132);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo,"* Has añadido el tubo de escape Locos Low Slamin en el  Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1105);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo,"* Has añadido el tubo de escape Locos Low Slamin en el  Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}

					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponentEx(car,1114);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo,"* Has añadido el tubo de escape Locos Low Slamin en el  Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}

					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1135);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo,"* Has añadido el tubo de escape Locos Low Slamin en el  Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Selecciona el tubo de escape (1000 C/U)", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nVolver", "Seleccionar", "Salir");
					}
                }
				else
				{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
				}
            }
			if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
           }
	    }
   }

   if(dialogid == DIALOGID+4)//Front Bumpers
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Front Bumper
			{
                if(pmodelid[playerid] == 562 ||
					pmodelid[playerid] == 565 ||
					pmodelid[playerid] == 559 ||
					pmodelid[playerid] == 561 ||
					pmodelid[playerid] == 558 ||
					pmodelid[playerid] == 560)
				{
					if(HacerConsumo(playerid, 3000) == 0)
					{
         	            SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                        return 1;
					}
		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponentEx(car,1171);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch Alien en el  Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1153);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch Alien en el  Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1160);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch Alien en el  Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1155);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch Alien en el  Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1169);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch Alien en el  Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1166);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch Alien en el  Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
				}
				else
				{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
	            }
            }
			if(listitem == 1)//Wheel Arch Cars X-Flow Front Bumper
            {
                   if(pmodelid[playerid] == 562 ||
	               pmodelid[playerid] == 565 ||
	               pmodelid[playerid] == 559 ||
	               pmodelid[playerid] == 561 ||
				   pmodelid[playerid] == 558 ||
                   pmodelid[playerid] == 560)
		           {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }

			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponentEx(car,1172);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch X-Flow en el Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1152);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch X-Flow en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1173);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch X-Flow en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1157);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch X-Flow en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1170);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch X-Flow en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1165);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Wheel Arch X-Flow en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
		    }
			if(listitem == 2)//Locos Low Co. Car Chromer Front Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
				{
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponentEx(car,1174);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Chromer en el Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponentEx(car,1179);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Chromer en el Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1189);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo,"[INFO]:Has añadido el parachoques delantero Locos Low Chromer en el Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1182);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Chromer en el Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponentEx(car,1115);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Chromer en el Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1191);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Chromer en el Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 3)//Locos Low Co. Salmin Front Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
	            pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 576)
			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponentEx(car,1175);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Slamin en el Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponentEx(car,1185);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Slamin en el Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1188);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Slamin en el Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1181);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Slamin en el Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
                    else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponentEx(car,1116);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Slamin en el Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1190);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques delantero Locos Low Slamin en el Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Selecciona el parachoque delantero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
                    }
            }
			if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }
        }
   }

   if(dialogid == DIALOGID+5)//Rear Bumpers
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Rear Bumper
			{
                if(pmodelid[playerid] == 562 ||
	            pmodelid[playerid] == 565 ||
	            pmodelid[playerid] == 559 ||
	            pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
                pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
                    new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponentEx(car,1149);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Wheel Arch Alien en el Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1150);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Wheel Arch Alien en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1159);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Wheel Arch Alien en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1154);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Wheel Arch Alien en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1141);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Wheel Arch Alien en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1168);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Wheel Arch Alien en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
			if(listitem == 1)//Wheel Arch Cars X-Flow Rear Bumper
            {
                if(pmodelid[playerid] == 562 ||
	            pmodelid[playerid] == 565 ||
	            pmodelid[playerid] == 559 ||
	            pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
                pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }

					new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponentEx(car,1148);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el parachote trasero Wheel Arch  X-Flow en el Elegy.");
		                ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1151);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachote trasero Wheel Arch  X-Flow en el Flash.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1161);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachote trasero Wheel Arch  X-Flow en el Jester.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1156);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachote trasero Wheel Arch  X-Flow en el Stratum.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1140);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachote trasero Wheel Arch  X-Flow en el Sultan.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1167);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachote trasero Wheel Arch  X-Flow en el Uranus.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
			if(listitem == 2)//Locos Low Co. Cars Chromer Rear Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponentEx(car,1176);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Chromer en el  Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponentEx(car,1180);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Chromer en el  Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1187);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Chromer en el  Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1184);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Chromer en el  Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponentEx(car,1109);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Chromer en el  Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1192);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Chromer en el  Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
			if(listitem == 3)//Locos Low Co. Cars Salmin Rear Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponentEx(car,1177);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Slamin en el Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponentEx(car,1178);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Slamin en el Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1186);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Slamin en el Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1183);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Slamin en el Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}

					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponentEx(car,1110);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Slamin en el Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}

					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1193);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el parachoques trasero Locos Low Slamin en el Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Selecciona el parachoque trasero (3000 C/U)", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nVolver", "Seleccionar", "Salir");
					}
                    }
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
            if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }
        }
   }

   if(dialogid == DIALOGID+6)//Roofs
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Roof Vent
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
				pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }

		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponentEx(car,1035);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch Alien en el Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1054);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch Alien en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1067);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch Alien en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1055);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch Alien en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1032);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch Alien en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1088);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch Alien en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
	        if(listitem == 1)//Wheel Arch Cars X-Flow Roof Vent
			{
                if(pmodelid[playerid] == 562 ||
	            pmodelid[playerid] == 565 ||
	            pmodelid[playerid] == 559 ||
	            pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
                pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }


			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponentEx(car,1035);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch X-Flow en el Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1053);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch X-Flow en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1068);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch X-Flow en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1061);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch X-Flow en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1033);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch X-Flow en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1091);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Wheel Arch X-Flow en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 2)//Locos Low Co. Cars Hardtop Roof
			{
                if(pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536)
			    {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 567)
			        {
			            AddVehicleComponentEx(car,1130);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el techo Locos Low Hardtop en el  Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
	   				else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1128);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Locos Low Hardtop en el  Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Savanna y Blade]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
		    if(listitem == 3)//Locos Low Co. Cars Softtop Roof
			{
                 if(pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536)
			    {
					if(HacerConsumo(playerid, 1500) == 0)
					{
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
					}
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 567)
			        {
			            AddVehicleComponentEx(car,1131);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el techo Locos Low Softtop en el Savanna.");
			            ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
	   				else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1103);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el techo Locos Low Softtop en el Blade.");
                        ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Selecciona el techo (1500 C/U)", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Savanna y Blade]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
            if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }
	     }
   }

   if(dialogid == DIALOGID+7)//Spoilers
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Spoilers
			{
                if(pmodelid[playerid] == 562 ||
	            pmodelid[playerid] == 565 ||
	            pmodelid[playerid] == 559 ||
	            pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
                pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 4000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }

		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponentEx(car,1147);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch Alien en el Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1049);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch Alien en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1162);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch Alien en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1058);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch Alien en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1138);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch Alien en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1164);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch Alien en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
    	    }
            if(listitem == 1)//Wheel Arch Cars X-Flow Spoilers
			{
                if(pmodelid[playerid] == 562 ||
	            pmodelid[playerid] == 565 ||
	            pmodelid[playerid] == 559 ||
	            pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
                pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 4000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
                    new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponentEx(car,1146);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch X-Flow en el Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1050);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch X-Flow en el Flash.");
			            ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1158);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch X-Flow en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1060);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch X-Flow en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1139);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch X-Flow en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1163);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido el aleron Wheel Arch X-Flow en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Selecciona el aleron (4000 C/U)", "Alien Spoiler\nX-Flow Spoiler\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo X-Flow Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
            }
            if(listitem == 2)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }
	   	 }
   }

   if(dialogid == DIALOGID+8)//Sideskirts
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Sideskirts
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
				pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }

		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponentEx(car,1036);
		            	AddVehicleComponentEx(car,1040);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch Alien en el Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1047);
					    AddVehicleComponentEx(car,1051);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch Alien en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1069);
					    AddVehicleComponentEx(car,1071);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch Alien en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1056);
					    AddVehicleComponentEx(car,1062);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch Alien en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1026);
					    AddVehicleComponentEx(car,1027);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "** Has añadido los faldones laterales Wheel Arch Alien en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1090);
					    AddVehicleComponentEx(car,1094);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch Alien en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
		    }
	   	    if(listitem == 1)//Wheel Arch Cars X-Flow Sideskirts
			{
                if(pmodelid[playerid] == 562 ||
	            pmodelid[playerid] == 565 ||
	            pmodelid[playerid] == 559 ||
	            pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 558 ||
                pmodelid[playerid] == 560)
		        {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
				    new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponentEx(car,1039);
			            AddVehicleComponentEx(car,1041);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch X-Flow en el Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponentEx(car,1048);
					    AddVehicleComponentEx(car,1052);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch X-Flow en el Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponentEx(car,1070);
					    AddVehicleComponentEx(car,1072);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch X-Flow en el Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponentEx(car,1057);
					    AddVehicleComponentEx(car,1063);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch X-Flow en el Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponentEx(car,1031);
					    AddVehicleComponentEx(car,1030);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch X-Flow en el Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponentEx(car,1093);
					    AddVehicleComponentEx(car,1095);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Wheel Arch X-Flow en el Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Wheel Arch Angels!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
		    }
		    if(listitem == 2)//Locos Low Co. Cars Chrome Strip Sideskirts
			{
                 if(pmodelid[playerid] == 575 ||
	               pmodelid[playerid] == 536 ||
	               pmodelid[playerid] == 576 ||
		 	       pmodelid[playerid] == 567)
                   {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
	       		        AddVehicleComponentEx(car,1042);
	       		        AddVehicleComponentEx(car,1099);
	       		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Strip en el Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
	   				else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponentEx(car,1102);
					    AddVehicleComponentEx(car,1133);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Strip en el Savanna.");
	    		        ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
	                }
	                else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponentEx(car,1134);
					    AddVehicleComponentEx(car,1137);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Strip en el Tornado.");
	    		        ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
	                }
	                else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponentEx(car,1108);
					    AddVehicleComponentEx(car,1107);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Strip en el Blade.");
	                    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
	                }
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Brodway, Savanna Tornado y Blade]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
	        }
	  	    if(listitem == 3)//Locos Low Co. Cars Chrome Flames Sideskirts
			{
                if(pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 534)
			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponentEx(car,1122);
			            AddVehicleComponentEx(car,1101);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Flames en el Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Remington]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 4)//Locos Low Co. Cars Chrome Arches Sideskirts
			{
                if(pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 534)
			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponentEx(car,1106);
			            AddVehicleComponentEx(car,1124);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Arches en el Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Remington]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 5)//Locos Low Co. Cars Chrome Trim Sideskirts
			{
                if(pmodelid[playerid] == 535)

			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 535)
			        {
			            AddVehicleComponentEx(car,1118);
			            AddVehicleComponentEx(car,1120);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido los faldones laterales Locos Low Chrome Trim en el Slamvan.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Slamvan]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 6)//Locos Low Co. Cars Chrome Wheelcovers Sideskirts
			{
                if(pmodelid[playerid] == 535)

			    {
                   if(HacerConsumo(playerid, 3000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 535)
			        {
			            AddVehicleComponentEx(car,1119);
			            AddVehicleComponentEx(car,1121);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido las cubieras para las ruedas Locos Low Chrome en el Slamvan.");
						ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Selecciona los faldones laterales (3000 C/U)", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Slamvan]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 7)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }
         }
   }
   if(dialogid == DIALOGID+9)//Bullbars
   {
		if(response)
		{
			if(listitem == 0)//Locos Low Co. Cars Chrome Grill
			{
                if(pmodelid[playerid] == 534)

			    {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponentEx(car,1100);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido la parrilla Locos Low Chrome en el Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Selecciona la parrilla (1500 C/U)", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nVolver", "Seleccionar", "Salir");
			        }
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Remington]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 1)//Locos Low Co. Cars Chrome Bars
			{
                 if(pmodelid[playerid] == 534)

			    {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponentEx(car,1123);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido la parrilla Locos Low Chrome en el Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Selecciona la parrilla (1500 C/U)", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Remington]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 2)//Locos Low Co. Cars Chrome Lights
			{
                if(pmodelid[playerid] == 534)

			    {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponentEx(car,1125);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido la parrilla Locos Low Chrome en el Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Selecciona la parrilla (1500 C/U)", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Remington]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 3)//Locos Low Co. Cars Chrome Bullbar
			{
                if(pmodelid[playerid] == 535)

			    {
                   if(HacerConsumo(playerid, 1500) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 535)
			        {
			            AddVehicleComponentEx(car,1117);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,Amarillo, "* Has añadido la parrilla Locos Low Chrome en el Slamvan.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Selecciona la parrilla (1500 C/U)", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nVolver", "Seleccionar", "Salir");
					}
					}
					else
					{
				    SendClientMessage(playerid,Rojo,"* Solo puedes añadir este componente a los coches de tipo Locos Low [Slamvan]!");
					format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
					}
			}
			if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
          }
       }
   }


   if(dialogid == DIALOGID+10)//Wheels
   {
		if(response)
		{
			if(listitem == 0)//Offroad
			{
                if(HacerConsumo(playerid, 500) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1025);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendClientMessage(playerid,Amarillo,"* Has añadido las ruedas Offroad Wheels.");
	            ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
	        }
            if(listitem == 1)//Mega
			{
                if(HacerConsumo(playerid, 5000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
			    AddVehicleComponentEx(car,1074);
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			    SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Mega Wheels.");
			    ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
            if(listitem == 2)//Wires
			{
                if(HacerConsumo(playerid, 1000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
	            AddVehicleComponentEx(car,1076);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Wires Wheels.");
			    ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
	        if(listitem == 3)//Twist
			{
                if(HacerConsumo(playerid, 7000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
			    AddVehicleComponentEx(car,1078);
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			    SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Twist Wheels.");
			    ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 4)//Groove
			{
                if(HacerConsumo(playerid, 5000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
			    AddVehicleComponentEx(car,1081);
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			    SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Groove Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 5)//Import
			{
                if(HacerConsumo(playerid, 7000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponentEx(car,1082);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
   			    SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Import Wheels.");
			    ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 6)//Atomic
			{
                if(HacerConsumo(playerid, 5000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
			    AddVehicleComponentEx(car,1085);
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			    SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Atomic Wheels.");
				ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 7)//Ahab
			{
                if(HacerConsumo(playerid, 3000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
			    AddVehicleComponentEx(car,1096);
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	          	SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Ahab Wheels.");
			    ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 8)//Virtual
			{
				if(HacerConsumo(playerid, 3000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponentEx(car,1097);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	           	SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Virtual Wheels.");
                ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 9)//Access
			{
                if(HacerConsumo(playerid, 3000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                new car = GetPlayerVehicleID(playerid);
			    AddVehicleComponentEx(car,1098);
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	         	SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Access Wheels.");
			    ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 10)//Next page
			{
                ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 11)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
            }

		}
   }

   if(dialogid == DIALOGID+11)//Car Stereo
   {
		if(response)
		{
			if(listitem == 0)//Bass Boost
			{
                if(HacerConsumo(playerid, 1000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 CarInfo[GetPlayerVehicle(playerid)][cEquipo] = 1;
				 SaveCar(GetPlayerVehicle(playerid));
		         SendClientMessage(playerid,Amarillo, "* Has añadido el sistema de sonido estereo normal.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Selecciona el sistema de sonido.", "Estereo normal (1000 C/U)\nEstereo X-Flow (5000 C/U)\nEstereo Alien (10000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 1)//Super Bass Boost
			{
                if(HacerConsumo(playerid, 5000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 CarInfo[GetPlayerVehicle(playerid)][cEquipo] = 2;
				 SaveCar(GetPlayerVehicle(playerid));
		         SendClientMessage(playerid,Amarillo, "* Has añadido el sistema de sonido estereo X-Flow.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Selecciona el sistema de sonido.", "Estereo normal (1000 C/U)\nEstereo X-Flow (5000 C/U)\nEstereo Alien (10000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 2)//Ultra Bass Boost
			{
                if(HacerConsumo(playerid, 10000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
                 PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 CarInfo[GetPlayerVehicle(playerid)][cEquipo] = 3;
				 SaveCar(GetPlayerVehicle(playerid));
		         SendClientMessage(playerid,Amarillo, "* Has añadido el sistema de sonido estereo Alien.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Selecciona el sistema de sonido.", "Estereo normal (1000 C/U)\nEstereo X-Flow (5000 C/U)\nEstereo Alien (10000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
           }
		}
   }

   if(dialogid == DIALOGID+12)//Menu de modificaciones 2
   {
		if(response)
		{
			if(listitem == 0)//Hydraulics
			{
                   if(HacerConsumo(playerid, 20000) == 0)
                   {
         	                SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                            return 1;
                   }
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponentEx(car,1087);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,Amarillo, "* Has añadido el sistema hidráulico.");
		         ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Menu de modificaciones", "Hydraulica (20000 C/U)\nNitro x10 (25000 C/U)\nVolver", "Seleccionar", "Salir");
			}
			if(listitem == 1)//Nitro x10
			{
                if(HacerConsumo(playerid, 25000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1010);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido el nitro x10.");
		        ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Menu de modificaciones", "Hydraulica (1000 C/U)\nNitro x10 (5000 C/U)\nVolver", "Seleccionar", "Salir");
			}			
			if(listitem == 4)//Volver
            {
				format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
           }
		}
	}

   if(dialogid == DIALOGID+13)//Wheels 2
   {
		if(response)
		{
			if(listitem == 0)//Trance
            {
                if(HacerConsumo(playerid, 1000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1084);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Trance Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 1)//Shadow
            {
                if(HacerConsumo(playerid, 7000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1073);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Shadow Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 2)//Rimshine
            {
                if(HacerConsumo(playerid, 3000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1075);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Rimshine Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 3)//Classic
            {
                if(HacerConsumo(playerid, 5000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1077);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Classic Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 4)//Cutter
            {
                if(HacerConsumo(playerid, 9000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1079);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Cutter Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 5)//Switch
            {
                if(HacerConsumo(playerid, 10000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1080);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Switch Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 6)//Dollar
            {
                if(HacerConsumo(playerid, 1000) == 0)
                {
         	        SendClientMessage(playerid, Amarillo, "* No tienes suficientes productos.");
                    return 1;
                }
		        new car = GetPlayerVehicleID(playerid);
		        AddVehicleComponentEx(car,1083);
		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		        SendClientMessage(playerid,Amarillo, "* Has añadido las ruedas Dollar Wheels.");
		        ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Trance (1000 C/U)\nShadow (7000 C/U)\nRimshine (3000 C/U)\nClassic (5000 C/U)\nCutter (9000 C/U)\nSwitch (10000 C/U)\nDollar (1000 C/U)\nVolver", "Seleccionar", "Salir");
            }
            if(listitem == 7)//Volver
            {
		        ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Selecciona las ruedas", "Offroad (500 C/U)\nMega (5000 C/U)\nWires (1000 C/U)\nTwist (7000 C/U)\nGrove (5000 C/U)\nImport (7000 C/U)\nAtomic (5000 C/U)\nAhab (3000 C/U)\nVirtual (3000 C/U)\nAccess (3000 C/U)\nMás\nVolver", "Seleccionar", "Salir");
            }
         }
    }
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
forward Tunning_OnPlayerStateChange(playerid, newstate, oldstate);
public Tunning_OnPlayerStateChange(playerid, newstate, oldstate) {
	if(newstate == PLAYER_STATE_DRIVER) {
	    pvehicleid[playerid] = GetPlayerVehicleID(playerid);
	    pmodelid[playerid] = GetVehicleModel(pvehicleid[playerid]);
	}
	else {
	    pvehicleid[playerid] = 0;
	}
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
public ModCar(playerid) {
	
	if(pvehicleid[playerid] > 0)
	{
		format(string, 128, "Menu de Modificaciones (Prods disponibles: %d)", PlayerInfo[playerid][pProductos]);
		ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, string,"Vinilos\nColores\nTubos de escape\nParachoques delantero\nParachoques trasero\nTecho\nAlerones\nFaldones laterales\nParrillas\nWheels\nSistema de audio\nMas", "Seleccionar", "Salir");
		return SendClientMessage(playerid, Amarillo, "* Seleciona un componente.");
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
forward Tunning_OnPlayerText(playerid, text[]);
public Tunning_OnPlayerText(playerid, text[])
{
	if(PlayerInfo[playerid][pEligiendoColores] == 1)
	{
		ColorElegido1[playerid] = strval(text);
		if(ColorElegido1[playerid] < -1 || ColorElegido1[playerid] > 255)
		{
			SendClientMessage(playerid, Amarillo, "* El color debe ser entre -1 y 255. Escribelo nuevamente.");
			return 1;
		}
		PlayerInfo[playerid][pEligiendoColores] = 2;
		SendClientMessage(playerid, Amarillo, "* Escribe el segundo color.");
	}
	else if(PlayerInfo[playerid][pEligiendoColores] == 2)
	{
		ColorElegido2[playerid] = strval(text);
		if(ColorElegido2[playerid] < -1 || ColorElegido2[playerid] > 255)
		{
			SendClientMessage(playerid, Amarillo, "* El color debe ser entre -1 y 255. Escribelo nuevamente.");
			return 1;
		}
		PlayerInfo[playerid][pEligiendoColores] = 0;
		SendClientMessage(playerid, Amarillo, "* Has pintado el coche.");
		ChangeVehicleColor(CarInfo[GetPlayerVehicle(playerid)][cId], ColorElegido1[playerid], ColorElegido2[playerid]);
		CarInfo[GetPlayerVehicle(playerid)][cColorOne] = ColorElegido1[playerid];
		CarInfo[GetPlayerVehicle(playerid)][cColorTwo] = ColorElegido2[playerid];
		SaveCar(GetPlayerVehicle(playerid));
	}
	return 0;
}

forward HacerConsumo(playerid, cantidad);
public HacerConsumo(playerid, cantidad)
{
	new resultado = 0;
	if(PlayerInfo[playerid][pProductos] >= cantidad)
	{
		PlayerInfo[playerid][pProductos] -= cantidad;
		resultado = 1;
        SaveValue(playerid, "Productos", PlayerInfo[playerid][pProductos]);
	}
	return resultado;
}

AddVehicleComponentEx(vehicleid, componentid)
{
	AddVehicleComponent(vehicleid, componentid);
	Vehicles_OnVehicleMod(vehicleid, componentid);
	return 1;
}

ChangeVehiclePaintjobEx(vehicleid, paintjobid)
{
	ChangeVehiclePaintjob(vehicleid, paintjobid);
	Vehicles_OnVehiclePaintjob(vehicleid, paintjobid);
	return 1;
}

forward timer_reparar(playerid);
public timer_reparar(playerid)
{
	new tmpcar;
	tmpcar = vehiculomascercano (playerid);
	RepairVehicle(CarInfo[tmpcar][cId]);
	SetVehicleHealth (CarInfo[tmpcar][cId], 1000);
	CarInfo[tmpcar][cBroken] = 0;
	GameTextForPlayer(playerid,"~g~Vehiculo reparado usa /salir",2000,5);
	return 1;
}

forward timer_reparar2(playerid);
public timer_reparar2(playerid)
{
    new tmpcar;
    tmpcar = vehiculomascercano (playerid);
	RepairVehicle(CarInfo[tmpcar][cId]);
	SetVehicleHealth(CarInfo[tmpcar][cId], 1000);
    CarInfo[tmpcar][cBroken] = 0;
    GameTextForPlayer(playerid,"~g~Vehiculo reparado",2000,5);
	PlayerInfo[playerid][pTempFrozen] = 0; // Ya puede usar /salir
	TogglePlayerControllable(playerid,1);
	return 1;
}

IsPlayerInTaller(playerid)
{
	for(new i; i < MAX_TALLERES; i++)
	{
		if(PlayerToPoint(50, playerid, Talleres[i][0], Talleres[i][1], Talleres[i][2]))
		{
			return 1;
		}
	}
	return 0;
}

Tunning_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 1)
	{
		DisablePlayerCheckpoint(playerid);
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pEstadoMecanico] = 0;
		return 1;
	}
	return 0;
}

Tunning_OnPlayerUpdate(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 1 && PlayerInfo[playerid][pEstadoMecanico] == 2)
	{
		if(IsPlayerConnected(PlayerInfo[playerid][pClienteMecanico]))
		{
			new Float:X,Float:Y,Float:Z;
			GetPlayerPos(PlayerInfo[playerid][pClienteMecanico], X,Y,Z);
			SetPlayerCheckpoint(playerid, X,Y,Z, 6.0);
		}
		else
		{
			SendClientMessage(playerid,Naranja, "* El cliente se ha desconectado!");
			DisablePlayerCheckpoint(playerid);
			PlayerInfo[playerid][pCheckpoint] = 0;
			PlayerInfo[playerid][pEstadoMecanico] = 0;
		}
	}
}