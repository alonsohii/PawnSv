#include <a_samp>
#include <colores>
#include <globalvars>
#include <funciones>

#define MAX_PAINTBALL_B 10
#define MIN_PAINTBALL_B 1
#define MAX_PAINTBALL_R 10
#define MIN_PAINTBALL_R 1

new paint_players_r = 0;
new paint_players_b = 0;
new HaMuertoJugando[MAX_PLAYERS];
new tiempo_paintball = 1;
new juega_paintball[MAX_PLAYERS];
new paintball_comenzado;
new participa_paintball[MAX_PLAYERS] = 0;
new equipop[MAX_PLAYERS];
new muertes_rojo = 0;
new muertes_azul = 0;
new killtimercuentaatras[MAX_PLAYERS];
new ganador;
new tmpcampeon[64];
new partidapaintterminada[MAX_PLAYERS];
new UltimoEnMorir = NOEXISTE;


new Float:EquipoA[4][3] = {
{-1485.0409,1581.5350,1425.6323},
{-1488.6858,1617.3190,1425.6323},
{-1475.4310,1649.8346,1425.6323},
{-1435.2688,1623.1118,1425.6323}
};

new Float:EquipoB[4][3] = {
{-1377.4054,1639.4357,1425.6323},
{-1379.0948,1620.5918,1425.6323},
{-1389.1249,1587.0569,1432.5366},
{-1406.6505,1582.0790,1425.6323}
};

Paintball_OnGameModeInit()
{
	CreateDynamicPickup(1242,1,2780.9104,-1814.2130,11.8438,0);
	CreateDynamic3DTextLabel("Paintball",Rojo,2780.9104,-1814.2130,11.8438+0.2,10.0);
	CreateDynamic3DTextLabel("Para inscribirte usa /participar",Gris,2780.9104,-1814.2130,11.8438,10.0);
	return 1;
}

/*Paintball_OnPlayerSpawn(playerid)
{
/if(paintball_comenzado == 1 && juega_paintball[playerid] == 1)
	{
		if(equipop[playerid] == 1)
		{
			new id;
			id = random(4);
		    SetPlayerPosEx(playerid,EquipoA[id][0],EquipoA[id][1],EquipoA[id][2]);
		    SafeGivePlayerWeapon(playerid,33,750);
		    SetPlayerInterior(playerid,18);
		}
		else if(equipop[playerid] == 2)
		{
			new id;
			id = random(4);
		    SetPlayerPosEx(playerid,EquipoB[id][0],EquipoB[id][1],EquipoB[id][2]);
		    SafeGivePlayerWeapon(playerid,33,750);
		    SetPlayerInterior(playerid,18);
		}

	}

	return 1;
}*/

Paintball_OnPlayerDeath(playerid)
{
	if(paintball_comenzado == 1 && juega_paintball[playerid] == 1)
	{
		HaMuertoJugando[playerid]  = 1;
	    if(equipop[playerid] == 1)
	    {
	        muertes_rojo++;
		}
		if(equipop[playerid] == 2)
		{
		    muertes_azul++;
		}
		UltimoEnMorir = playerid;
	}
	        
	return 1;
}
Paintball_OnPlayerSpawn(playerid)
{
	if(juega_paintball[playerid] == 1 && HaMuertoJugando[playerid] != 1)
	{
		    SetPlayerPosEx(playerid,2779.4575,-1812.9095,11.8438);
			SafeResetPlayerWeaponsAC(playerid);
			juega_paintball[playerid] = 0;
			GM_SetPlayerHealth(playerid,100);
		    SetPlayerVirtualWorld(playerid,0);
		    SetPlayerInterior(playerid,0);
			participa_paintball[playerid] = 0;
			KillTimer(killtimercuentaatras[playerid]);
			KillTimer(partidapaintterminada[playerid]);
	}
	HaMuertoJugando[playerid] = 0;
	return 1;
}
Paintball_OnPlayerCommandText(playerid, cmdtext[])
{
	// Agregados mensajes de advertencia temporalmente, hasta scriptear algo decente.


    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd,"/participar", true)== 0)
	{
     	if(PlayerToPoint(5.0,playerid,2779.4575,-1812.9095,11.8438))
     	{
	    	if(participa_paintball[playerid] == 1)
       		{
	    		SendClientMessage(playerid,Rojo,"Ya estas inscrito");
				SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
	    	    return 1;
			}
	    	if(paintball_comenzado == 1)
	    	{
	    	    SendClientMessage(playerid,Rojo,"Hay una partida en curso, espera a que finalice");
				SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
	    		return 1;
			}
	    	new equipo;
        	cmd = strtokex(cmdtext, idx);
        	if(!strlen(cmd))
        	{
				SendClientMessage(playerid,Blanco,"USO: /participar rojo(1)/azul(2)/aletorio(3) Ej. /participar 3");
				SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
				return 1;
			}
			equipo = strval(cmd);
	    	if(equipo == 1)
	    	{
				paint_players_r++;
				equipop[playerid] = 1;
				juega_paintball[playerid] = 1;
				participa_paintball[playerid] = 1;
				
				if(paint_players_b == 0)
				{
		    		SendClientMessage(playerid,Rojo,"Te has apuntado a una partida de paintball en el equipo rojo, deberás esperar a que se apunte 1 persona más para comenzar");
					SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
					return 1;
				}
				
				if(paint_players_r >= MIN_PAINTBALL_R && paint_players_b >= MIN_PAINTBALL_B )
				{
		    		format(string,sizeof(string),"Te has apuntado a una partida de paintball en el equipo rojo, el número de jugadores es de %d . La partida empezará en %d minutos.",paint_players_r,tiempo_paintball);
		    		SendClientMessage(playerid,Verde,string);
					SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
					return 1;
				}
			}
			else if(equipo == 2)
			{
				paint_players_b++;
				equipop[playerid] = 2;
				juega_paintball[playerid] = 1;
				participa_paintball[playerid] = 1;
			
				if(paint_players_r == 0)
				{
				    SendClientMessage(playerid,Rojo,"Te has apuntado a una partida de paintball en el equipo azul, deberás esperar a que se apunte una persona más");
					SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
					return 1;
				}
				else if(paint_players_r >= MIN_PAINTBALL_R && paint_players_b >= MIN_PAINTBALL_B )
				{
		    		format(string,sizeof(string),"Te has apuntado a una partida de paintball en el equipo azul, el número de jugadores es de %d . La partida empezará en %d minutos. Mantente en la entrada de la actividad.",paint_players_b,tiempo_paintball);
		    		SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
					SendClientMessage(playerid,Verde,string);
					return 1;
				}
			}
			else if(equipo == 3)
			{
				if((paint_players_b > paint_players_r) || paint_players_r == 0) return Paintball_OnPlayerCommandText(playerid, "/participar 1");
				else if(paint_players_r > paint_players_b) return Paintball_OnPlayerCommandText(playerid, "/participar 2");
				return 1;
			}
		
			SendClientMessage(playerid,Amarillo,"Jugadores Inscritos:");
			for(new i=0; i < MAX_PLAYERS; i++)
			{
			    if(juega_paintball[i] == 1)
			    {
					if(equipop[i] == 1)
					{
						SendClientMessage(playerid,Rojo,pName(i));
					}
					else if(equipop[i] == 2)
					{
						SendClientMessage(playerid,AzulOscuro,pName(i));
					}
				}
			}
			SendClientMessage(playerid,Blanco,"¡Recuerda permanecer cerca de las instalaciones para poder jugar!");
			SendClientMessage(playerid,Rojo,"(( ATENCIÓN: GUARDA TUS ARMAS EN UN MALETERO / ARMARIO ANTES DE COMENZAR, NO SE HARÁN MÁS DEVOLUCIONES. ))");
		}
		return 1;
	}
	
	if(strcmp(cmd,"/retirarse", true) == 0)
	{
		if(juega_paintball[playerid] == 1)
		{
			if(equipop[playerid] == 1)
			{
				ganador = 2;
			}
			else
			{
				ganador = 1;
			}
		}
	}
	if(strcmp(cmd,"/salirpaintball",true) == 0)
	{
		if(juega_paintball[playerid] != 1)
		{
		    SetPlayerPosEx(playerid,2779.4575,-1812.9095,11.8438);
			SafeResetPlayerWeaponsAC(playerid);
			juega_paintball[playerid] = 0;
			GM_SetPlayerHealth(playerid,100);
		    SetPlayerVirtualWorld(playerid,0);
		    SetPlayerInterior(playerid,0);
			participa_paintball[playerid] = 0;
			KillTimer(killtimercuentaatras[playerid]);
			KillTimer(partidapaintterminada[playerid]);
		}
		return 1;
	}
	return 0;
}

TiempoEventos() //TimerDeUnMinuto
{
	if(paintball_comenzado == 1)return 1;
	if(paint_players_r >= MIN_PAINTBALL_R && paint_players_b >= MIN_PAINTBALL_B && tiempo_paintball != 0  && (paint_players_r < (paint_players_b+2) || paint_players_b < (paint_players_r+2)))
	{
	    tiempo_paintball--;
	}
	if(tiempo_paintball == 0)
	{
	    paintball_comenzado = 1;
		for(new i=0; i < MAX_PLAYERS; i++)
		{
			if(juega_paintball[i] == 1)
			{
			    if(PlayerToPoint(50.0,i,2779.4575,-1812.9095,11.8438))
	  			{
					if(equipop[i] == 1)
					{
						new id;
						id = random(4);
						SetPlayerInterior(i,18);
						SetPlayerPosEx(i,EquipoA[id][0],EquipoA[id][1],EquipoA[id][2]);
						SetPlayerColor(i, 0xa8070700);
						SafeGivePlayerWeapon(i,33,750);
					}
					else if(equipop[i] == 2)
					{
						new id;
						id = random(4);
						SetPlayerInterior(i,18);
						SetPlayerPosEx(i,EquipoB[id][0],EquipoB[id][1],EquipoB[id][2]);
						SetPlayerColor(i, 0x004d9b00);
						SafeGivePlayerWeapon(i,33,750);
					}
					SetPlayerVirtualWorld(i,1);
					GameTextForPlayer(i,"~g~Comienza la partida",5000,1);
					ganador = 0;
					killtimercuentaatras[i] = SetTimerEx("MarcadorPaintball",1000,1,"d",i);
					partidapaintterminada[i] = SetTimerEx("TiempoPartidaPaintball",6000,1,"d",i);
			    }
			}
		}
	}
	return 1;
}

forward TiempoPartidaPaintball(i);
public TiempoPartidaPaintball(i)
{
	if(juega_paintball[i] == 1)
	{
		if(ganador > 0)
		{
		    SetPlayerPosEx(i,2779.4575,-1812.9095,11.8438);
			SafeResetPlayerWeaponsAC(i);
			juega_paintball[i] = 0;
			SetPlayerColor(i,0xFFFFFF00);
			GM_SetPlayerHealth(i,100);
			format(string,sizeof(string),"~r~Partida Terminada, equipo ganador %s",tmpcampeon);
		    GameTextForPlayer(i,string,5000,1);
		    SetPlayerVirtualWorld(i,0);
		    SetPlayerInterior(i,0);
			tiempo_paintball= 1;
			participa_paintball[i] = 0;
			paint_players_r = 0;
			paint_players_b = 0;
			paintball_comenzado = 0;
			KillTimer(killtimercuentaatras[i]);
			KillTimer(partidapaintterminada[i]);
	    	muertes_azul = 0;
			muertes_rojo = 0;
		}
	}
	return 1;
}

forward MarcadorPaintball(i);
public MarcadorPaintball(i)
{
	new marcador[128];
	format(marcador,sizeof(marcador),"~r~%d ~w~- ~b~%d",muertes_azul,muertes_rojo);
	GameTextForPlayer(i,marcador,1000,1);
	if(muertes_azul == 8) {ganador = 1;}
	if(muertes_rojo == 8) {ganador = 2;}
	if(ganador == 1){format(tmpcampeon,sizeof(tmpcampeon),"Rojo");}
	if(ganador == 2){format(tmpcampeon,sizeof(tmpcampeon),"Azul");}
	return 1;
}
