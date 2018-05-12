#include <colores>
#include <globalvars>
#include <funciones>
#include <gafas>

new TotalNegs;

Negocios_OnGameModeInit()
{
	LoadNegocio();
	
	for(new h = 0; h < sizeof(NegocioInfo); h++)
	{
	    NegocioInfo[h][nPickup] = CreateDynamic3DTextLabel(NegocioInfo[h][nName], AzulOscuro, NegocioInfo[h][nEPos_x], NegocioInfo[h][nEPos_y], NegocioInfo[h][nEPos_z], 20);
	}
	
	venticuatroseven = CreateMenu("24/7", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(venticuatroseven, 0, "Telefono");
	AddMenuItem(venticuatroseven, 1, "$400");
	AddMenuItem(venticuatroseven, 0, "Equipo de Radio");
	AddMenuItem(venticuatroseven, 1, "$2000");
	AddMenuItem(venticuatroseven, 0, "Mechero");
	AddMenuItem(venticuatroseven, 1, "$10");
	AddMenuItem(venticuatroseven, 0, "Cigarrillos");
	AddMenuItem(venticuatroseven, 1, "$10");
	AddMenuItem(venticuatroseven, 0, "Flores");
	AddMenuItem(venticuatroseven, 1, "$5");
	AddMenuItem(venticuatroseven, 0, "Camara");
	AddMenuItem(venticuatroseven, 1, "$25");
	AddMenuItem(venticuatroseven, 0, "Juegos de azar");
	AddMenuItem(venticuatroseven, 1, "$5");
	AddMenuItem(venticuatroseven, 0, "Palanca");
	AddMenuItem(venticuatroseven, 1, "$250");
	AddMenuItem(venticuatroseven, 0, "Alicates");
	AddMenuItem(venticuatroseven, 1, "$150");
	AddMenuItem(venticuatroseven, 0, "Ganzua");
	AddMenuItem(venticuatroseven, 1, "$200");
	AddMenuItem(venticuatroseven, 0, "Bate");
	AddMenuItem(venticuatroseven, 1, "$50");
	AddMenuItem(venticuatroseven, 0, "Salir");
	amu = CreateMenu("Ammu Nation", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(amu,0,"Colt 45");
	AddMenuItem(amu,1,"7500$");
	AddMenuItem(amu,0,"Cuchillo");
	AddMenuItem(amu,1,"200$");
	AddMenuItem(amu,0,"Salir");
	azar = CreateMenu("Azar", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(azar,0,"Dado");
	AddMenuItem(azar, 1, "$5");
	AddMenuItem(azar,0,"Cartas");
	AddMenuItem(azar, 1, "$5");
	AddMenuItem(azar, 0, "Num de loteria");
	AddMenuItem(azar, 1, "$50");
	AddMenuItem(azar,0,"Atras");
	Ropa = CreateMenu("Tienda de Ropa", 1, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(Ropa, 0, "Gafas");
	AddMenuItem(Ropa, 0, "Cascos");
	AddMenuItem(Ropa, 0, "Bandana");
	AddMenuItem(Ropa, 0, "Salir");
	gafas = CreateMenu("Gafas", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(gafas, 0, "Normales");
	AddMenuItem(gafas, 1, "$40");
	AddMenuItem(gafas, 0, "Cuadradas");
	AddMenuItem(gafas, 1, "$50");
	AddMenuItem(gafas, 0, "Circulares");
	AddMenuItem(gafas, 1, "$50");
	AddMenuItem(gafas, 0, "Rayban");
	AddMenuItem(gafas, 1, "$80");
	AddMenuItem(gafas, 0, "Atras");
	AddMenuItem(gafas, 0, "Salir");
	gafasnorm = CreateMenu("Gafas Normales", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(gafasnorm, 0, "Rojas");
	AddMenuItem(gafasnorm, 0, "Naranjas");
	AddMenuItem(gafasnorm, 0, "Verdes");
	AddMenuItem(gafasnorm, 0, "Azules");
	AddMenuItem(gafasnorm, 0, "Negras");
	AddMenuItem(gafasnorm, 0, "Transparentes");
	AddMenuItem(gafasnorm, 0, "Atras");
	gafascuad = CreateMenu("Gafas Cuadradas", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(gafascuad, 0, "Amarillas");
	AddMenuItem(gafascuad, 0, "Naranjas");
	AddMenuItem(gafascuad, 0, "Rojas");
	AddMenuItem(gafascuad, 0, "Azules");
	AddMenuItem(gafascuad, 0, "Verdes");
	AddMenuItem(gafascuad, 0, "Atras");
	gafascirc = CreateMenu("Gafas Circulares",2,50.0,180.0,200.0,200.0);
	AddMenuItem(gafascirc, 0, "Normal");
	AddMenuItem(gafascirc, 0, "Amarillas");
	AddMenuItem(gafascirc, 0, "Rojas");
	AddMenuItem(gafascirc, 0, "Negras");
	AddMenuItem(gafascirc, 0, "Atras");
	gafasrayban = CreateMenu("RayBan", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(gafasrayban, 0, "Grises");
	AddMenuItem(gafasrayban, 0, "Azules");
	AddMenuItem(gafasrayban, 0, "Moradas");
	AddMenuItem(gafasrayban, 0, "Rosas");
	AddMenuItem(gafasrayban, 0, "Rojas");
	AddMenuItem(gafasrayban, 0, "Naranjas");
	AddMenuItem(gafasrayban, 0, "Amarillas");
	AddMenuItem(gafasrayban, 0, "Verdes");
	AddMenuItem(gafasrayban, 0, "Atras");
	Casco = CreateMenu("Cascos", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(Casco, 0, "Blanco y rojo");
	AddMenuItem(Casco, 1, "$75");
	AddMenuItem(Casco, 0, "Verde");
	AddMenuItem(Casco, 1, "$100");
	AddMenuItem(Casco, 0, "Negro y rojo");
	AddMenuItem(Casco, 1, "$100");
	AddMenuItem(Casco, 0, "Azul");
	AddMenuItem(Casco, 1, "$100");
	AddMenuItem(Casco, 0, "Motocross");
	AddMenuItem(Casco, 1, "$300");
	AddMenuItem(Casco, 0, "Atras");
	Bandanas = CreateMenu("Bandanas", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(Bandanas, 0, "Negra Tipo 1");
	AddMenuItem(Bandanas, 1, "$30");
	AddMenuItem(Bandanas, 0, "Negra Tipo 2");
	AddMenuItem(Bandanas, 1, "$30");
	AddMenuItem(Bandanas, 0, "Verde");
	AddMenuItem(Bandanas, 1, "$30");
	AddMenuItem(Bandanas, 0, "Camuflaje");
	AddMenuItem(Bandanas, 1, "$30");
	AddMenuItem(Bandanas, 0, "Rosa");
	AddMenuItem(Bandanas, 1, "$30");
	AddMenuItem(Bandanas, 0, "Mas");
	AddMenuItem(Bandanas, 0, "Atras");
	Bandanas2 = CreateMenu("Bandanas", 2, 50.0, 180.0, 200.0, 200.0);
	AddMenuItem(Bandanas2, 0, "Naranja y blanco");
	AddMenuItem(Bandanas2, 1, "$30");
	AddMenuItem(Bandanas2, 0, "Azul");
	AddMenuItem(Bandanas2, 1, "$30");
	AddMenuItem(Bandanas2, 0, "Amarilla");
	AddMenuItem(Bandanas2, 1, "$30");
	AddMenuItem(Bandanas2, 0, "Marron y amarillo");
	AddMenuItem(Bandanas2, 1, "$30");
	AddMenuItem(Bandanas2, 0, "Atras");
	return 1;
}

LoadNegocio()
{
	new sql[80], row[512], negcount, neliminado;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM negocios");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	negcount = strval(row);
	
	for (new idx=1; idx<=negcount; idx++)
	{
		format(sql, sizeof(sql), "SELECT * FROM negocios WHERE id=%d LIMIT 1", idx);
	    mysql_query(sql);
	    mysql_store_result();
     	mysql_fetch_row(row);
		split(row, arrCoords, '|');
		neliminado = strval(arrCoords[16]);
		if(neliminado == 0)
		{
			NegocioInfo[idx][nId] = strval(arrCoords[0]);
			format(NegocioInfo[idx][nName], 128, "%s", arrCoords[1]);
			NegocioInfo[idx][nType] = strval(arrCoords[2]);
			NegocioInfo[idx][nEPos_x] = floatstr(arrCoords[3]);
			NegocioInfo[idx][nEPos_y] = floatstr(arrCoords[4]);
			NegocioInfo[idx][nEPos_z] = floatstr(arrCoords[5]);
			NegocioInfo[idx][nSPos_x] = floatstr(arrCoords[6]);
			NegocioInfo[idx][nSPos_y] = floatstr(arrCoords[7]);
			NegocioInfo[idx][nSPos_z] = floatstr(arrCoords[8]);
			NegocioInfo[idx][nProd] = strval(arrCoords[9]);
			NegocioInfo[idx][nCajaFuerte] = strval(arrCoords[10]);
			NegocioInfo[idx][nLocked] = strval(arrCoords[11]);
			format(NegocioInfo[idx][nOwner], 128, "%s", arrCoords[12]);
			NegocioInfo[idx][nOwned] = strval(arrCoords[13]);
			NegocioInfo[idx][nInterior] = strval(arrCoords[14]);
			NegocioInfo[idx][nCosto] = strval(arrCoords[15]);
			TotalNegs++;
		}
	}
	
	printf("Negocios Totales: %d (MAX: %d)",TotalNegs,MAX_NEGOCIOS);
	mysql_free_result();
	return 1;
}

SaveNegocio(i)
{
	new sql[1024];
	format(sql, sizeof(sql), "UPDATE negocios SET Nombre='%s',Tipo=%d,EPos_X=%f,EPos_Y=%f,EPos_Z=%f,SPos_X=%f,SPos_Y=%f,SPos_Z=%f,Productos=%d,CajaFuerte=%d,Locked=%d,Owner='%s',Owned=%d,Interior=%d,Costo=%d WHERE id=%d LIMIT 1",
    NegocioInfo[i][nName],
	NegocioInfo[i][nType],
	NegocioInfo[i][nEPos_x],
	NegocioInfo[i][nEPos_y],
	NegocioInfo[i][nEPos_z],
	NegocioInfo[i][nSPos_x],
	NegocioInfo[i][nSPos_y],
	NegocioInfo[i][nSPos_z],
	NegocioInfo[i][nProd],
	NegocioInfo[i][nCajaFuerte],
	NegocioInfo[i][nLocked],
	NegocioInfo[i][nOwner],
	NegocioInfo[i][nOwned],
	NegocioInfo[i][nInterior],
 	NegocioInfo[i][nCosto],
	NegocioInfo[i][nId]);
	mysql_query(sql);
	return 1;
}

Negocios_OnPlayerCommandText(playerid, cmdtext[])
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/comprar", true) == 0)
	{
		new Negocio;
		Negocio = PlayerInfo[playerid][pNegocio];
			
		for(new i; i < MAX_NEGOCIOS; i++)
		{
			if(PlayerToPoint(5.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			{
				Negocio = i;
				break; 
			}
		}
		if(PlayerInfo[playerid][pNegocio] > 0 || Negocio != NOEXISTE)
		{
			
			if(NegocioInfo[Negocio][nType] == 7)
			{
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
				    SendClientMessage(playerid, Blanco, "USO: /comprar [ID]");
					SendClientMessage(playerid, AzulClaro, "|_______ TALLER _______|");
					SendClientMessage(playerid, AzulClaro, "| 1: Pack de Productosx100 100$");
					SendClientMessage(playerid, AzulClaro, "| 2: Pack de Productosx1000 1000$");
					SendClientMessage(playerid, AzulClaro, "| 3: Pack de Productosx10000 10000$");
					return 1;
				}
				new id;
				id = strval(tmp);
				if(id == 1 && SafeGetPlayerMoney(playerid) >= 100 )
				{
					if(NegocioInfo[Negocio][nProd] < 100)
					{
						SendClientMessage(playerid, Rojo, "* Sin existencias.");
						return 1;
					}
					SendClientMessage(playerid, Gris, "* Has comprado un pack de productos x 100.");
					SafeGivePlayerMoney(playerid, -100);
					PlayerInfo[playerid][pProductos]+=100;
					SaveValue(playerid, "Productos", PlayerInfo[playerid][pProductos]);
					SaveNegocio(Negocio);
					return 1;
				}
				if(id == 2 && SafeGetPlayerMoney(playerid) >= 1000 )
				{
					if(NegocioInfo[Negocio][nProd] < 1000)
					{
						SendClientMessage(playerid, Rojo, "* Sin existencias.");
						return 1;
					}
					SendClientMessage(playerid, Gris, "* Has comprado un pack de productos x 1000.");
					SafeGivePlayerMoney(playerid, -1000);
					PlayerInfo[playerid][pProductos]+=1000;
					SaveValue(playerid, "Productos", PlayerInfo[playerid][pProductos]);
					SaveNegocio(Negocio);
					return 1;
				}
				if(id == 3 && SafeGetPlayerMoney(playerid) >= 10000 )
				{
					if(NegocioInfo[Negocio][nProd] < 10000)
					{
						SendClientMessage(playerid, Rojo, "* Sin existencias.");
						return 1;
					}
					SendClientMessage(playerid, Gris, "* Has comprado un pack de productos x 10000.");
					SafeGivePlayerMoney(playerid, -10000);
					PlayerInfo[playerid][pProductos]+=10000;
					SaveValue(playerid, "Productos", PlayerInfo[playerid][pProductos]);
					SaveNegocio(Negocio);
					return 1;
				}
				else
				{
				    SendClientMessage(playerid, Blanco, "USO: /comprar [ID]");
					SendClientMessage(playerid, AzulClaro, "|_______ TALLER _______|");
					SendClientMessage(playerid, AzulClaro, "| 1: Pack de Productosx100 100$");
					SendClientMessage(playerid, AzulClaro, "| 2: Pack de Productosx1000 1000$");
					SendClientMessage(playerid, AzulClaro, "| 3: Pack de Productosx10000 10000$");
					return 1;
				}
			}
			else if(NegocioInfo[Negocio][nType] == 3 && GetPlayerInterior(playerid) != 0) //Es 24/7
		    {
				ShowMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 0);
			}
			else if(NegocioInfo[Negocio][nType] == 9 && GetPlayerInterior(playerid) != 0)
			{
				ShowMenuForPlayer(amu,playerid);
				TogglePlayerControllable(playerid,0);
			}
			else if(NegocioInfo[Negocio][nType] == 10 && GetPlayerInterior(playerid) != 0)
		    {
				ShowMenuForPlayer(Ropa, playerid);
				TogglePlayerControllable(playerid, 0);
			}
			else if(NegocioInfo[Negocio][nType] == 11 && GetPlayerInterior(playerid) != 0)
		    {
				if(PlayerInfo[playerid][pAdmin] < 1) return 1;
//				MostrarCatalogoMuebles(playerid);
				TogglePlayerControllable(playerid, 0);
			}
			else if(NegocioInfo[Negocio][nType] == 8) // Hierbas Ilegales
			{
				if(PlayerInfo[playerid][pMember] > 10)
				{
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
				    SendClientMessage(playerid, Blanco, "USO: /comprar [ID]");
					SendClientMessage(playerid, AzulClaro, "|_______ HIERBAS ILEGALES _______|");
					SendClientMessage(playerid, AzulClaro, "| 1: Semillas de Marihuana 20$");
					SendClientMessage(playerid, AzulClaro, "| 2: Semillas de Coca 50$");
					SendClientMessage(playerid, AzulClaro, "| 3: Parafernalia para preparación de Cocaína 2000$");
                    SendClientMessage(playerid, AzulClaro, "| 4: Parafernalia para preparación de Crack 1000$");
					return 1;
				}
				new id;
				id = strval(tmp);
				if(id == 1 && SafeGetPlayerMoney(playerid) >= 20 )
				{
					if((PlayerInfo[playerid][pMember] > 10 && PlayerInfo[playerid][pMember] < 30))
					{
						SendClientMessage(playerid, Gris, "* Has comprado semillas de marihuana.");
						SafeGivePlayerMoney(playerid, -20);
						PlayerInfo[playerid][pSemillas][0] ++;
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Hay muchas otras cosas que comprar además de marihuana.");
					}
				}
				else if(id == 2 && SafeGetPlayerMoney(playerid) >= 50 )
				{
					if(PlayerInfo[playerid][pMember] > 20 && PlayerInfo[playerid][pMember] < 31)
					{
						SendClientMessage(playerid, Gris, "* Has comprado semillas de coca.");
						SafeGivePlayerMoney(playerid, -50);
						PlayerInfo[playerid][pSemillas][1] ++;
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Hay muchas otras cosas que comprar además de Coca.");
					}
				}
				else if(id == 3 && SafeGetPlayerMoney(playerid) >= 2000 )
				{
					if(PlayerInfo[playerid][pMember] > 20 && PlayerInfo[playerid][pMember] < 31)
					{
						SendClientMessage(playerid, Gris, "* Has comprado parafernalia para la preparación de Cocaína.");
						SafeGivePlayerMoney(playerid, -2000);
						PlayerInfo[playerid][pParafernalia][0] ++;
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Qué pretendes hacer con eso?");
					}
				}
				else if(id == 4 && SafeGetPlayerMoney(playerid) >= 1000 )
				{
					if(PlayerInfo[playerid][pMember] > 10 && PlayerInfo[playerid][pMember] < 21)
					{
						SendClientMessage(playerid, Gris, "* Has comprado parafernalia para la preparación de Crack.");
						SafeGivePlayerMoney(playerid, -1000);
						PlayerInfo[playerid][pParafernalia][1] ++;
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Qué pretendes hacer con eso?");
					}
				}
				else
				{
					SendClientMessage(playerid, Blanco, "USO: /comprar [ID]");
					SendClientMessage(playerid, AzulClaro, "|_______ HIERBAS ILEGALES _______|");
					SendClientMessage(playerid, AzulClaro, "| 1: Semillas de Marihuana 20$");
					SendClientMessage(playerid, AzulClaro, "| 2: Semillas de Coca 50$");
					SendClientMessage(playerid, AzulClaro, "| 3: Parafernalia para preparación de Cocaína 4000$");
                    SendClientMessage(playerid, AzulClaro, "| 4: Parafernalia para preparación de Crack 2000$");
				}
				SaveValues(playerid, "Semillas");
				SaveValues(playerid, "Parafernalia");
				SaveNegocio(Negocio);
			}
			}
			return 1;
		}
		SendClientMessage(playerid, Rojo, "* No estas en ningun Negocio!");
		return 1;
	}
	
	if(strcmp(cmd, "/editneg", true) == 0)
	{
	    if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
	        return 1;
	    }
	
	    tmp = strtokex(cmdtext, idx);
     	if(!strlen(tmp))
      	{
       		SendClientMessage(playerid, Blanco, "USO: /editneg [Campo]");
			SendClientMessage(playerid, AzulClaro, "Campos Disponibles: Posicion, Nombre, Tipo, Interior, Costo, Nivel, Eliminar");
			return 1;
		}
		
		if(strcmp(tmp, "Posicion", true) == 0)
		{
			for(new i = 0; i < sizeof(NegocioInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			    {
       				PlayerInfo[playerid][pMoviendoNeg] = i;
			        break;
				}
			}
			SendClientMessage(playerid, Amarillo, "* Estas moviendo el Negocio, escribe 'OK' cuando termines.");
			return 1;
		}
		
		else if(strcmp(tmp, "Nombre", true) == 0)
		{
			for(new i = 0; i < sizeof(NegocioInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			    {
       				PlayerInfo[playerid][pEditingNeg] = i;
       				break;
				}
			}
			SendClientMessage(playerid, Amarillo, "* Escribe un nuevo nombre para el Negocio.");
			return 1;
		}
		
		else if(strcmp(tmp, "eliminar", true) == 0)
		{
			for(new i = 1; i < sizeof(NegocioInfo); i++)
			{
			    if(PlayerToPoint(2.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			    {
			        format(string, 128, "UPDATE negocios SET eliminado=1 WHERE id=%d LIMIT 1", i);
			        mysql_query(string);
			        EliminarNegocio(i);
					break;
				}
			}
		}
		
		else if(strcmp(tmp, "Tipo", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
     		if(!strlen(tmp))
      		{
      		    SendClientMessage(playerid, Blanco, "USO: /editneg Tipo [ID]");
      		    SendClientMessage(playerid, AzulClaro, "IDs Disponibles: 1- Restaurantes 2- Bares/NightClubs 3-24/7 4-Comidas Rápidas");
				SendClientMessage(playerid, AzulClaro, "6-Corrupto 7-Mecanico Faccion 8-Hierbas 9-AmmuNation 10-Tiendas de ropa 11-Muebles");
				return 1;
			}
			new id;
			id = strval(tmp);
			for(new i = 0; i < sizeof(NegocioInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			    {
			        NegocioInfo[i][nType] = id;
					if(id > 5 && id < 9)
					{
						NegocioInfo[i][nLocked] = 1;
					}
					else { NegocioInfo[i][nLocked] = 0; } 
			        SaveNegocio(i);
			        format(string, 128, "* Listo! Cambiaste el tipo del Negocio a '%d'", id);
					break;
				}
			}
			SendClientMessage(playerid, Amarillo, string);
			return 1;
		}
		
		else if(strcmp(tmp, "Costo", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
     		if(!strlen(tmp))
      		{
      		    SendClientMessage(playerid, Blanco, "USO: /editneg Costo [$$]");
      		   	return 1;
			}
			new id;
			id = strval(tmp);
			for(new i = 0; i < sizeof(NegocioInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			    {
			        NegocioInfo[i][nCosto] = id;
			        SaveNegocio(i);
					format(string, 128, "* Listo! Cambiaste el costo del Negocio a '%d'e", id);
					break;
				}
			}
			SendClientMessage(playerid, Amarillo, string);
			return 1;
		}
		
		else if(strcmp(tmp, "Interior", true) == 0)
		{
		    tmp = strtokex(cmdtext, idx);
		    if(!strlen(tmp))
		    {
		        SendClientMessage(playerid, Blanco, "USO: /editneg Interior [ID]");
				SendClientMessage(playerid, Amarillo, "[TIPO 1] 1 Restaurante Italiano | 2 Restaurante Normal | 3 Chino | 4 R. Casino | 5 Bar de Carretera");
				SendClientMessage(playerid, Amarillo, "[TIPO 2] 1 Alhambra | 2 10Botellas | 3 Bar Area51 | 4 PigPen | 5 Pleasure Domes | 6 Club del puente");
				SendClientMessage(playerid, Amarillo, "[TIPO 3] 1 - 7 24/7s");
				SendClientMessage(playerid, Amarillo, "[TIPO 4] 1 Burger Shot | 2 Cluckin Bell | 3 Well Staked Pizza | 4 Donuts | 5 Cafeteria Americana");
				SendClientMessage(playerid, Amarillo, "[TIPO 9] 1 AmmuNation");
				SendClientMessage(playerid, Amarillo, "[TIPO 10] 1 Binco | 2 Zip | 3 DS | 4 Victim | 5 Suburban | 6 Prolaps");
				SendClientMessage(playerid, Amarillo, "[TIPO 11] 1 Tienda de muebles");
				return 1;
			}
			new inter;
			inter = strval(tmp);
			for(new i = 0; i < sizeof(NegocioInfo); i++)
			{
   				if(PlayerToPoint(2.0, playerid, NegocioInfo[i][nEPos_x], NegocioInfo[i][nEPos_y], NegocioInfo[i][nEPos_z]))
			    {
			        if(NegocioInfo[i][nType] == 1)
			        {
			            if(inter == 1)
			            {
			                NegocioInfo[i][nSPos_x] = -800.0458;
							NegocioInfo[i][nSPos_y] = 512.1575;
							NegocioInfo[i][nSPos_z] = 1751.3335;
							NegocioInfo[i][nInterior] = 1;
			            }
			            else if(inter == 2)
			            {
			                NegocioInfo[i][nSPos_x] = 460.4592;
			                NegocioInfo[i][nSPos_y] = -88.7668;
			                NegocioInfo[i][nSPos_z] = 999.5547;
			                NegocioInfo[i][nInterior] = 4;
			            }
						else if(inter == 3)
						{
							NegocioInfo[i][nSPos_x] = 2264.8356933594;
							NegocioInfo[i][nSPos_y] = 1615.4234619141;
							NegocioInfo[i][nSPos_z] = 1637.5969238281;
							NegocioInfo[i][nInterior] = 1; 
						}
						else if(inter == 4)
						{
							NegocioInfo[i][nSPos_x] = 2945.9106445313;
							NegocioInfo[i][nSPos_y] = -605.34265136719;
							NegocioInfo[i][nSPos_z] = 3110.0737304688;
							NegocioInfo[i][nInterior] = 1;
						}
						else if(inter == 5)
						{
							NegocioInfo[i][nSPos_x] = 1445.2429199219;
							NegocioInfo[i][nSPos_y] = 245.3904876709;
							NegocioInfo[i][nSPos_z] = 2293.8967285156;
							NegocioInfo[i][nInterior] = 1;
						}
			        }
			        else if(NegocioInfo[i][nType] == 2)
			        {
						switch(inter)
						{
						    case 1:
						    {
          						NegocioInfo[i][nSPos_x] = 488.2629;
			                	NegocioInfo[i][nSPos_y] = -14.4430;
			                	NegocioInfo[i][nSPos_z] = 1094.8901;
			                	NegocioInfo[i][nInterior] = 17;
			                }
			                case 2:
			                {
                  				NegocioInfo[i][nSPos_x] = 501.9810;
			                	NegocioInfo[i][nSPos_y] = -69.1502;
			                	NegocioInfo[i][nSPos_z] = 998.757812;
			                	NegocioInfo[i][nInterior] = 11;
			                }
			                case 3:
			                {
                  				NegocioInfo[i][nSPos_x] = 2538.6535644531;
			                	NegocioInfo[i][nSPos_y] = -1407.0051269531;
			                	NegocioInfo[i][nSPos_z] = 2634.7524414063;
			                	NegocioInfo[i][nInterior] = 1;
			                }
			                case 4:
			                {
			                	NegocioInfo[i][nSPos_x] = 2519.1640625;
			                	NegocioInfo[i][nSPos_y] = -1410.09765625;
			                	NegocioInfo[i][nSPos_z] = 3244.349609375;
			                	NegocioInfo[i][nInterior] = 1;
			                }
			                case 5:
			                {
			                    NegocioInfo[i][nSPos_x] = -2648.8720703125;
								NegocioInfo[i][nSPos_y] = 1407.3342285156;
								NegocioInfo[i][nSPos_z] = 1114.9744873047;
								NegocioInfo[i][nInterior] = 1;
							}
							case 6:
							{
								NegocioInfo[i][nSPos_x] = 370.5724;
								NegocioInfo[i][nSPos_y] = -1691.9987;
								NegocioInfo[i][nSPos_z] = 18.4710;
								NegocioInfo[i][nInterior] = -1;
							}
						}
					}
					else if(NegocioInfo[i][nType] == 3)
					{
					    switch(inter)
					    {
					        case 1:
					        {
					            NegocioInfo[i][nSPos_x] = 6.0092;
			                	NegocioInfo[i][nSPos_y] = -31.6645;
			                	NegocioInfo[i][nSPos_z] = 1003.55;
			                	NegocioInfo[i][nInterior] = 10;
			                }
			                case 2:
			                {
			                    NegocioInfo[i][nSPos_x] = -25.884498;
			                	NegocioInfo[i][nSPos_y] = -185.868988;
			                	NegocioInfo[i][nSPos_z] = 1003.546875;
			                	NegocioInfo[i][nInterior] = 17;
			                }
			                case 3:
			                {
			                    NegocioInfo[i][nSPos_x] = -30.946699;
			                	NegocioInfo[i][nSPos_y] = -89.609596;
			                	NegocioInfo[i][nSPos_z] = 1003.546875;
			                	NegocioInfo[i][nInterior] = 18;
			                }
			                case 4:
							{
							    NegocioInfo[i][nSPos_x] = 663.3172;
								NegocioInfo[i][nSPos_y] = -573.3005;
								NegocioInfo[i][nSPos_z] = 16.3359;
								NegocioInfo[i][nInterior] = 0;
							}
							case 5:
							{
							    NegocioInfo[i][nSPos_x] = -25.132598;
								NegocioInfo[i][nSPos_y] = -139.066986;
								NegocioInfo[i][nSPos_z] = 1003.546875;
								NegocioInfo[i][nInterior] = 16;
							}
							case 6:
							{
							    NegocioInfo[i][nSPos_x] = -27.312299;
							    NegocioInfo[i][nSPos_y] = -29.277599;
							    NegocioInfo[i][nSPos_z] = 1003.557250;
							    NegocioInfo[i][nInterior] = 4;
							}
							case 7:
							{
							    NegocioInfo[i][nSPos_x] = -26.691598;
								NegocioInfo[i][nSPos_y] = -55.714897;
								NegocioInfo[i][nSPos_z] = 1003.546875;
							}
						}
					}
     				else if(NegocioInfo[i][nType] == 4)
			        {
			            switch(inter)
			            {
			                case 1:
			                {
			                	NegocioInfo[i][nSPos_x] = 362.8855;
			                	NegocioInfo[i][nSPos_y] = -75.1039;
			                	NegocioInfo[i][nSPos_z] = 1001.5078;
			                	NegocioInfo[i][nInterior] = 10;
			                }
			                case 2:
			                {
			                    NegocioInfo[i][nSPos_x] = 364.8881;
			                	NegocioInfo[i][nSPos_y] = -11.6040;
			                	NegocioInfo[i][nSPos_z] = 1001.8516;
			                	NegocioInfo[i][nInterior] = 9;
			                }
			                case 3:
			                {
			                    NegocioInfo[i][nSPos_x] = 372.4163;
			                	NegocioInfo[i][nSPos_y] = -133.3985;
			                	NegocioInfo[i][nSPos_z] = 1001.4922;
			                	NegocioInfo[i][nInterior] = 5;
			                }
			                case 4:
			                {
			                    NegocioInfo[i][nSPos_x] = 377.2815;
			                	NegocioInfo[i][nSPos_y] = -192.9495;
			                	NegocioInfo[i][nSPos_z] = 1000.6401;
			                	NegocioInfo[i][nInterior] = 17;
			                }
							case 5:
							{
								NegocioInfo[i][nSPos_x] = 1454.2191162109;
			                	NegocioInfo[i][nSPos_y] = 218.90119934082;
			                	NegocioInfo[i][nSPos_z] = 2884.2409667969;
			                	NegocioInfo[i][nInterior] = 1;
							}
						}
					}
					else if(NegocioInfo[i][nType] == 9)
					{
						 switch(inter)
						{
							case 1:
							{
								NegocioInfo[i][nSPos_x] = 286.148986;
			                	NegocioInfo[i][nSPos_y] = -40.644397;
			                	NegocioInfo[i][nSPos_z] = 1001.515625;
			                	NegocioInfo[i][nInterior] = 1;
							}
						}
					}
					else if(NegocioInfo[i][nType] == 10)
					{
						 switch(inter)
						{
							case 1: // Binco
							{
								NegocioInfo[i][nSPos_x] = 207.737991;
			                	NegocioInfo[i][nSPos_y] = -109.019996;
			                	NegocioInfo[i][nSPos_z] = 1005.132812;
			                	NegocioInfo[i][nInterior] = 15;
							}
							case 2: // Zip
							{
								NegocioInfo[i][nSPos_x] = 161.6299;
			                	NegocioInfo[i][nSPos_y] = -96.1142;
			                	NegocioInfo[i][nSPos_z] = 1001.8047;
			                	NegocioInfo[i][nInterior] = 18;
							}
							case 3: // Didier sachs
							{
								NegocioInfo[i][nSPos_x] = 	204.332992;
			                	NegocioInfo[i][nSPos_y] = -166.694992;
			                	NegocioInfo[i][nSPos_z] = 1000.523437;
			                	NegocioInfo[i][nInterior] = 14;
							}
							case 4: // Victim
							{
								NegocioInfo[i][nSPos_x] = 226.293991;
			                	NegocioInfo[i][nSPos_y] = -7.431529;
			                	NegocioInfo[i][nSPos_z] = 1002.210937;
			                	NegocioInfo[i][nInterior] = 5;
							}
							case 5: // Suburban
							{
								NegocioInfo[i][nSPos_x] = 203.777999;
			                	NegocioInfo[i][nSPos_y] = -48.492397;
			                	NegocioInfo[i][nSPos_z] = 1001.804687;
			                	NegocioInfo[i][nInterior] = 1;
							}
							case 6: // Prolaps
							{
								NegocioInfo[i][nSPos_x] = 207.054992;
			                	NegocioInfo[i][nSPos_y] = -138.80499;
			                	NegocioInfo[i][nSPos_z] = 1003.507812;
			                	NegocioInfo[i][nInterior] = 3;
							}
						}
					}
					else if(NegocioInfo[i][nType] == 11)
					{
						 switch(inter)
						{
							case 1:
							{
								NegocioInfo[i][nSPos_x] = 298.8442;
			                	NegocioInfo[i][nSPos_y] = -141.6956;
			                	NegocioInfo[i][nSPos_z] = 1004.0547;
			                	NegocioInfo[i][nInterior] = 7;
							}
						}
					}
					SaveNegocio(i);
					break;
				}
			}
			SendClientMessage(playerid, Verde, "* Listo Cambiaste el Interior del Negocio");
		}
		return 1;
	}
	
	if(strcmp(cmd, "/crearnegocio", true) == 0)
	{
	    new sql[80], row[256], id;
	    if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
	        return 1;
	    }
	    
	    
		format(sql, 80, "INSERT INTO negocios (Nombre) VALUES ('Negocio')");
		mysql_query(sql);
	    
		format(sql, sizeof(sql), "SELECT COUNT(*) FROM negocios");
		mysql_query(sql);
		mysql_store_result();
		mysql_fetch_row(row);
		id = strval(row);
	    
	    NegocioInfo[id][nId] = id;
		NegocioInfo[id][nType] = 1;
		NegocioInfo[id][nLocked] = 0;
		NegocioInfo[id][nCosto] = 30000;
		NegocioInfo[id][nCajaFuerte] = 0;
		NegocioInfo[id][nProd] = 250;
		format(NegocioInfo[id][nOwner], 128, "El Estado");
		format(NegocioInfo[id][nName], 128, "Negocio Numero %d", id);
		new Float:X[MAX_PLAYERS], Float:Y[MAX_PLAYERS], Float:Z[MAX_PLAYERS];
  		GetPlayerPos(playerid, X[playerid],Y[playerid],Z[playerid]);
  		NegocioInfo[id][nEPos_x] = X[playerid];
  		NegocioInfo[id][nEPos_y] = Y[playerid];
  		NegocioInfo[id][nEPos_z] = Z[playerid];
		NegocioInfo[id][nSPos_x] = -800.25134277344;
		NegocioInfo[id][nSPos_y] = 512.41198730469;
		NegocioInfo[id][nSPos_z] = 1751.0947265625;
		NegocioInfo[id][nInterior] = 1;
     	
		SaveNegocio(id);

		NegocioInfo[id][nPickup] = CreateDynamic3DTextLabel(NegocioInfo[id][nName], Azul, X[playerid], Y[playerid], Z[playerid], 10);
		mysql_free_result();
		return 1;
	}

	return 0;
}

EliminarNegocio(idx)
{
	DestroyDynamic3DTextLabel(NegocioInfo[idx][nPickup]);
	for( ; idx < TotalNegs; idx++)
	{
		NegocioInfo[idx][nId] = NegocioInfo[idx+1][nId];
		format(NegocioInfo[idx][nName], 128, "%s", NegocioInfo[idx+1][nName]);
		NegocioInfo[idx][nType] = NegocioInfo[idx+1][nType];
		NegocioInfo[idx][nEPos_x] = NegocioInfo[idx+1][nEPos_x];
		NegocioInfo[idx][nEPos_y] = NegocioInfo[idx+1][nEPos_y];
		NegocioInfo[idx][nEPos_z] = NegocioInfo[idx+1][nEPos_z];
		NegocioInfo[idx][nSPos_x] = NegocioInfo[idx+1][nSPos_x];
		NegocioInfo[idx][nSPos_y] = NegocioInfo[idx+1][nSPos_y];
		NegocioInfo[idx][nSPos_z] = NegocioInfo[idx+1][nSPos_z];
		NegocioInfo[idx][nProd] = NegocioInfo[idx+1][nProd];
		NegocioInfo[idx][nCajaFuerte] = NegocioInfo[idx+1][nCajaFuerte];
		NegocioInfo[idx][nLocked] = NegocioInfo[idx+1][nLocked];
		format(NegocioInfo[idx][nOwner], 128, "%s", NegocioInfo[idx+1][nOwner]);
		NegocioInfo[idx][nOwned] = NegocioInfo[idx+1][nOwned];
		NegocioInfo[idx][nInterior] = NegocioInfo[idx+1][nInterior];
        NegocioInfo[idx][nCosto] = NegocioInfo[idx+1][nCosto];
		NegocioInfo[idx][nPickup] = NegocioInfo[idx+1][nPickup];
	}
	return 1;
}

Negocios_OnPlayerText(playerid, text[])
{
	if(PlayerInfo[playerid][pEditingNeg] > 0)
	{
		format(NegocioInfo[PlayerInfo[playerid][pEditingNeg]][nName], 128, "%s", text);
		format(string, sizeof(string), "* Has cambiado el nombre del Negocio a: '%s'", text);
		SendClientMessage(playerid, Verde, string);
		DestroyDynamic3DTextLabel(NegocioInfo[PlayerInfo[playerid][pEditingNeg]][nPickup]);
		NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nPickup] = CreateDynamic3DTextLabel(NegocioInfo[PlayerInfo[playerid][pEditingNeg]][nName], Azul, NegocioInfo[PlayerInfo[playerid][pEditingNeg]][nEPos_x], NegocioInfo[PlayerInfo[playerid][pEditingNeg]][nEPos_y], NegocioInfo[PlayerInfo[playerid][pEditingNeg]][nEPos_z], 20);
		SaveNegocio(PlayerInfo[playerid][pEditingNeg]);
		PlayerInfo[playerid][pEditingNeg] = 0;
		return 1;
	}
	if(PlayerInfo[playerid][pMoviendoNeg] > 0)
	{
		new Float:X[MAX_PLAYERS], Float:Y[MAX_PLAYERS], Float:Z[MAX_PLAYERS];
		GetPlayerPos(playerid, X[playerid],Y[playerid],Z[playerid]);
  		NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nEPos_x] = X[playerid];
    	NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nEPos_y] = Y[playerid];
     	NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nEPos_z] = Z[playerid];
		SaveNegocio(PlayerInfo[playerid][pMoviendoNeg]);
		DestroyDynamic3DTextLabel(NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nPickup]);
		NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nPickup] = CreateDynamic3DTextLabel(NegocioInfo[PlayerInfo[playerid][pMoviendoNeg]][nName], Azul, X[playerid], Y[playerid], Z[playerid], 10);
		SendClientMessage(playerid, Gris, "Hecho");
		PlayerInfo[playerid][pMoviendoNeg] = 0;
		return 1;
	}
	return 0;
}

Neg_OnPlayerSelectedMenuRow(playerid, row)
{
    new Menu:current;
    current = GetPlayerMenu(playerid);
	if(current == azar)
	{
        switch(row)
        {
			case 0:
			{
				if(PlayerInfo[playerid][pDado] != 1)
				{
					if(SafeGetPlayerMoney(playerid) >= 5)
					{
						SafeGivePlayerMoney(playerid, - 5);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						PlayerInfo[playerid][pDado] = 1;
						SendClientMessage(playerid, Verde, "* Has comprado un dado! Para utilizarlo usa /dado");
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Ya tienes un dado");
				}
				HideMenuForPlayer(azar, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(PlayerInfo[playerid][pCartas] != 1)
				{
					if(SafeGetPlayerMoney(playerid) >= 5)
					{
						SafeGivePlayerMoney(playerid, - 5);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						PlayerInfo[playerid][pCartas] = 1;
						SendClientMessage(playerid, Verde, "* Has comprado unas cartas! Para utilizarlas usa /carta");
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Ya tienes cartas");
				}
				HideMenuForPlayer(azar, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(PlayerInfo[playerid][pLoteria] == NOEXISTE)
				{
					if(SafeGetPlayerMoney(playerid) >= 50)
					{
						SafeGivePlayerMoney(playerid, - 50);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						ShowPlayerDialog(playerid, 10000, DIALOG_STYLE_INPUT, "Lotería", "Escriba un número (Máx. 100),\n puede elegir la opción 'Aletorio'\n para asignarle cualquier número.", "Elegir", "Aletorio");
					}
					else
					{
						SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Ya tienes un número");
				}
				HideMenuForPlayer(azar, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				HideMenuForPlayer(azar, playerid);
				ShowMenuForPlayer(venticuatroseven, playerid);
			}
		}
		SaveValues(playerid, "Inventario");	
	}
    else if(current == venticuatroseven)
    {
        switch(row)
        {
            case 0:
			{
                if(SafeGetPlayerMoney(playerid) >= 400)
				{
      				new randphone = 100000 + random(899999);//minimum 100000  max 999999
                    new id=-1;
					for (new i;i<2;i++)
                    {
                        if (PlayerInfo[playerid][pPnumber][i] != 0) continue;
                        id=i;
                        format(string, sizeof(string), "* Ahora tienes un nuevo número de teléfono: %d", randphone);
                        break;
                    }
                    if (id==-1)
                    {
                        SendClientMessage(playerid, Rojo, "Ya tienes dos números de teléfono");
                    }
                    else
                    {
                        PlayerInfo[playerid][pPnumber][id] = randphone;
                        SafeGivePlayerMoney(playerid, - 400);
                        SaveValues(playerid, "Telefonos");
                        SendClientMessage(playerid, Amarillo, "PISTA: Escribe /ayuda para ver los comandos de tu teléfono.");
                    }
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
            case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 2000)
				{
					if(PlayerInfo[playerid][pWalkies] != 0) return SendClientMessage(playerid, Rojo, "* Ya tienes el equipo de radio.");
					
					SafeGivePlayerMoney(playerid, -2000);
					PlayerInfo[playerid][pWalkies] = 1;
					SaveValue(playerid, "Walkies", PlayerInfo[playerid][pWalkies]);
					SendClientMessage(playerid, Verde, "* Ahora tienes un equipo de radio!");
					SendClientMessage(playerid, Amarillo, "PISTA: Escribe /ayuda para ver los comandos del equipo de radio y frecuencias.");
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
            case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 10)
				{
      				SafeGivePlayerMoney(playerid, - 10);
					PlayerInfo[playerid][pEncendedor] += 30;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					format(string, sizeof(string), "* Has comprado un mechero.");
					SendClientMessage(playerid, Verde, string);
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
            case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 10)
				{
      				SafeGivePlayerMoney(playerid, - 10);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					format(string, sizeof(string), "* Caja de cigarrillos comprada.");
					SendClientMessage(playerid, Verde, string);
					PlayerInfo[playerid][pCigarrillos] += 10;
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
            case 4:
			{
				if(SafeGetPlayerMoney(playerid) >= 25)
				{
      				SafeGivePlayerMoney(playerid, - 25);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					format(string, sizeof(string), "* Has Comprado un Ramo de Flores.");
					SafeGivePlayerWeapon(playerid, 14, 1);
					SendClientMessage(playerid, Verde, string);
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
            case 5:
			{
				if(SafeGetPlayerMoney(playerid) > 25)
				{
      				SafeGivePlayerMoney(playerid, - 25);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					format(string, sizeof(string), "Cámara comprada.");
					SafeGivePlayerWeapon(playerid,43,25);
					SendClientMessage(playerid, Gris, string);
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 6:
			{
				HideMenuForPlayer(venticuatroseven,playerid);
				ShowMenuForPlayer(azar,playerid);
			}
			case 7:
			{
				if(SafeGetPlayerMoney(playerid) >= 250)
				{
      				SafeGivePlayerMoney(playerid, - 250);
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					PlayerInfo[playerid][pPalanca] = 10;
					format(string, sizeof(string), "* Palanca comprada.");
					SendClientMessage(playerid, Verde, string);
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 8:
			{
				if(SafeGetPlayerMoney(playerid) >= 150)
				{
      				SafeGivePlayerMoney(playerid, - 150);
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					PlayerInfo[playerid][pAlicates] = 10;
					format(string, sizeof(string), "* Alicates comprados.");
					SendClientMessage(playerid, Verde, string);
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 9:
			{
				if(SafeGetPlayerMoney(playerid) >= 200)
				{
      				SafeGivePlayerMoney(playerid, - 200);
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					PlayerInfo[playerid][pGanzua] = 10;
					format(string, sizeof(string), "* Ganzua compradada.");
					SendClientMessage(playerid, Verde, string);
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 10: //baseball bat
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
					SafeGivePlayerMoney(playerid, - 50);
					SafeGivePlayerWeapon(playerid,5,1);
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado un bate de beisbol");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(venticuatroseven, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 11:
			{
				HideMenuForPlayer(venticuatroseven,playerid);
				TogglePlayerControllable(playerid, 1);
			}

        }
		SaveValues(playerid, "Inventario");	
    }
	if(current == amu)
	{
		switch(row)
		{
			case 0:
			{
				if(SafeGetPlayerMoney(playerid) >= 7500 && PlayerInfo[playerid][pGunLic] == 1)
				{
					SafeGivePlayerMoney(playerid, -7500);
					SendClientMessage(playerid,Verde,"Has comprado una Colt 45");
					SafeGivePlayerWeapon(playerid,22,30);
					new query[1024],WeapName[40],hour,minute,second,day,month,year;
					GetWeaponName(22,WeapName,sizeof(WeapName));
					format(query, sizeof(query), "INSERT INTO `logarmas` (`Emisor`, `Receptor`, `Desc`, `Fecha`) VALUES ('Ammunation', '%s', '/comprar | %s | %d','%d:%d:%d | %d-%d-%d')", pNameEx(playerid), WeapName, 30,hour,minute,second,day,month,year);
					mysql_query(query);
				}
				HideMenuForPlayer(amu, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 200 && PlayerInfo[playerid][pGunLic] == 1)
				{
					SafeGivePlayerMoney(playerid, - 200);
					SendClientMessage(playerid,Verde,"Has comprado una navaja");
					SafeGivePlayerWeapon(playerid,4,1);
					new query[1024],WeapName[40],hour,minute,second,day,month,year;
					GetWeaponName(22,WeapName,sizeof(WeapName));
					format(query, sizeof(query), "INSERT INTO `logarmas` (`Emisor`, `Receptor`, `Desc`, `Fecha`) VALUES ('Ammunation', '%s', '/comprar | %s | %d','%d:%d:%d | %d-%d-%d')", pNameEx(playerid), WeapName, 1,hour,minute,second,day,month,year);
					mysql_query(query);
				}
				HideMenuForPlayer(amu, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				HideMenuForPlayer(amu, playerid);
				TogglePlayerControllable(playerid, 1);
			}
		}
	}
	if(current == Ropa)
	{
		switch(row)
		{
			case 0: // Gafas
			{
				HideMenuForPlayer(Ropa, playerid);
				ShowMenuForPlayer(gafas,playerid);
			}
			case 1: // Casco
			{
				HideMenuForPlayer(Ropa, playerid);
				ShowMenuForPlayer(Casco,playerid);
			}
			case 2: // Bandana
			{
				HideMenuForPlayer(Ropa, playerid);
				//if(IsBandanaSkinValid(playerid))
				//{
				ShowMenuForPlayer(Bandanas,playerid);
				//}
				//else SendClientMessage(playerid, Rojo, "* A ese skin aun no se le pueden poner bandanas");
			}
			case 3: // Salir
			{
				HideMenuForPlayer(Ropa,playerid);
				TogglePlayerControllable(playerid, 1);
			}
		}
	}
	if(current == Casco)
	{
		switch(row)
		{
			case 0: //cascos
			{
				if(SafeGetPlayerMoney(playerid) >= 75)
				{
					SafeGivePlayerMoney(playerid, - 75);
					PlayerInfo[playerid][pCascos] = 1;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado un casco, usa /casco para usarlo");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Casco, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1: //cascos
			{
				if(SafeGetPlayerMoney(playerid) >= 100)
				{
					SafeGivePlayerMoney(playerid, - 100);
					PlayerInfo[playerid][pCascos] = 5;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado un casco, usa /casco para usarlo");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Casco, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2: //cascos
			{
				if(SafeGetPlayerMoney(playerid) >= 100)
				{
					SafeGivePlayerMoney(playerid, - 100);
					PlayerInfo[playerid][pCascos] = 3;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado un casco, usa /casco para usarlo");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Casco, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3: //cascos
			{
				if(SafeGetPlayerMoney(playerid) >= 100)
				{
					SafeGivePlayerMoney(playerid, - 100);
					PlayerInfo[playerid][pCascos] = 4;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado un casco, usa /casco para usarlo");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Casco, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4: //cascos
			{
				if(SafeGetPlayerMoney(playerid) >= 300)
				{
					SafeGivePlayerMoney(playerid, - 300);
					PlayerInfo[playerid][pCascos] = 2;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado un casco, usa /casco para usarlo");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Casco, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 5: // Atras
			{
				HideMenuForPlayer(Casco,playerid);
				ShowMenuForPlayer(Ropa,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}
	if(current == Bandanas)
	{
		switch(row)
		{
			case 0: 
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 1;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 2;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 3;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 4;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 5;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 5:
			{
				HideMenuForPlayer(Bandanas,playerid);
				ShowMenuForPlayer(Bandanas2,playerid);
			}
			case 6:
			{
				HideMenuForPlayer(Bandanas,playerid);
				ShowMenuForPlayer(Ropa,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}	
	if(current == Bandanas2)
	{
		switch(row)
		{
			case 0: 
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 6;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 7;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 8;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 30)
				{
					SafeGivePlayerMoney(playerid, - 30);
					PlayerInfo[playerid][pBandana] = 9;
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado una bandana, usa /bandana para usarla");	
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(Bandanas, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4:
			{
				HideMenuForPlayer(Bandanas2,playerid);
				ShowMenuForPlayer(Bandanas,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}
	if(current == gafas)
	{
		switch(row)
		{
			case 0: // Normales
			{
				HideMenuForPlayer(Ropa, playerid);
				ShowMenuForPlayer(gafasnorm,playerid);
			}
			case 1: // Cuadradas
			{
				HideMenuForPlayer(Ropa, playerid);
				ShowMenuForPlayer(gafascuad,playerid);
			}
			case 2: // Circulares
			{
				HideMenuForPlayer(Ropa, playerid);
				ShowMenuForPlayer(gafascirc,playerid);
			}
			case 3: // Rayban
			{
				HideMenuForPlayer(Ropa, playerid);
				ShowMenuForPlayer(gafasrayban,playerid);
			}
			case 4: // Atras
			{
				HideMenuForPlayer(gafas,playerid);
				ShowMenuForPlayer(Ropa,playerid);
			}
			case 5: // Salir
			{
				HideMenuForPlayer(gafas,playerid);
				TogglePlayerControllable(playerid, 1);
			}
		}
	}
	if(current == gafasnorm)
	{
		switch(row)
		{
			case 0:
			{
				if(SafeGetPlayerMoney(playerid) >= 40)
				{
      				SafeGivePlayerMoney(playerid, - 40);
					PlayerInfo[playerid][pGafas] = Gafas[0];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasnorm, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 40)
				{
      				SafeGivePlayerMoney(playerid, - 40);
					PlayerInfo[playerid][pGafas] = Gafas[1];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasnorm, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 40)
				{
      				SafeGivePlayerMoney(playerid, - 40);
					PlayerInfo[playerid][pGafas] = Gafas[2];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasnorm, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 40)
				{
      				SafeGivePlayerMoney(playerid, - 40);
					PlayerInfo[playerid][pGafas] = Gafas[3];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasnorm, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4:
			{
				if(SafeGetPlayerMoney(playerid) >= 40)
				{
      				SafeGivePlayerMoney(playerid, - 40);
					PlayerInfo[playerid][pGafas] = Gafas[4];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasnorm, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 5:
			{
				if(SafeGetPlayerMoney(playerid) >= 40)
				{
      				SafeGivePlayerMoney(playerid, - 40);
					PlayerInfo[playerid][pGafas] = Gafas[5];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasnorm, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 6: // Atras
			{
				HideMenuForPlayer(gafasnorm,playerid);
				ShowMenuForPlayer(gafas,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}
	if(current == gafascuad)
	{
		switch(row)
		{
			case 0:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[6];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascuad, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[7];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascuad, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[8];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascuad, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[9];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascuad, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[10];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascuad, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 5: // Atras
			{
				HideMenuForPlayer(gafascuad,playerid);
				ShowMenuForPlayer(gafas,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}
	if(current == gafasrayban)
	{
		switch(row)
		{
			case 0:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[11];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[12];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[13];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[14];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[15];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 5:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[16];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 6:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[17];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 7:
			{
				if(SafeGetPlayerMoney(playerid) >= 80)
				{
      				SafeGivePlayerMoney(playerid, - 80);
					PlayerInfo[playerid][pGafas] = Gafas[18];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafasrayban, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 8:
			{
				HideMenuForPlayer(gafasrayban,playerid);
				ShowMenuForPlayer(gafas,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}
	if(current == gafascirc)
	{
		switch(row)
		{
			case 0:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[19];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascirc, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 1:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[20];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascirc, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 2:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[21];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascirc, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				if(SafeGetPlayerMoney(playerid) >= 50)
				{
      				SafeGivePlayerMoney(playerid, - 50);
					PlayerInfo[playerid][pGafas] = Gafas[22];
      				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					SendClientMessage(playerid, Verde, "* Has comprado unas gafas, usa /gafas para usarlas");				
				}
				else
				{
					SendClientMessage(playerid, Rojo, "* Dinero insuficiente");
				}
				HideMenuForPlayer(gafascirc, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 4: // Atras
			{
				HideMenuForPlayer(gafascirc,playerid);
				ShowMenuForPlayer(gafas,playerid);
			}
		}
		SaveValues(playerid,"Inventario");
	}
    return 1;
}

stock GetTypeOfClothesShop(negocioid)
{
	new type = 0; // 0 - Tienda chunga (binco,suburban,victim,prolaps) 1 - Tienda pija (ds,zip)
	if((NegocioInfo[negocioid][nSPos_x] == 460.4592 && NegocioInfo[negocioid][nSPos_y] = -88.7668 && NegocioInfo[negocioid][nSPos_z] = 999.5547) ||
		(NegocioInfo[negocioid][nSPos_x] = 2264.8356933594 && NegocioInfo[negocioid][nSPos_y] = 1615.4234619141 && NegocioInfo[negocioid][nSPos_z] = 1637.5969238281))
		type = 1;
	return type;
}