#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <deathac>

#define COSTEPIZZA 50
#define MAXPIZZAS 5

new OfertaPizza[MAX_PLAYERS];
enum PedidosPizzaInfo
{
    Activo,
    Float:xpos,
    Float:ypos,
    Float:zpos,
}
new PedidosPizza[100][PedidosPizzaInfo];

new TimerRespawnCar[MAX_VEHICLES];

Pizza_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
//--------------------------------------------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd, "/pizza", true) == 0)
    {
        if(PlayerInfo[playerid][pJob] != 6) {SendClientMessage(playerid, Rojo, "* Debes ser repartidor!"); return 1;}

		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }
        cmd = strtokex(cmdtext, idx);
        
        if (strcmp(cmd, "repartir", true) == 0)
        {
            
            if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
            {
                format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a repartir.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
                SendClientMessage(playerid,Naranja,string);
                return 1;
            }
            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || GetVehicleModel(GetPlayerVehicleID(playerid)) != 448)
            {
                SendClientMessage(playerid,Rojo,"* Súbete en una moto de repartidor de pizza.");
                return 1;
            }

            if(PlayerInfo[playerid][pTrabajando] == 1)
            {
                SendClientMessage(playerid,Rojo,"* Ya estás repartiendo!.");
                return 1;
            }

            if(PlayerInfo[playerid][pPizzas] == 0)
            {
                SendClientMessage(playerid,Rojo,"* No tienes pizzas para repartir. Usa /pizza recoger");
                return 1;
            }

            PlayerInfo[playerid][pTrabajando] = 1;
            CrearPedidoPizza(playerid);
            return 1;
        }

        if (strcmp(cmd, "recoger", true) == 0)
        {
            if(!IsPlayerInArea(playerid, 2101.4729,2123.8374,-1790.2435,-1767.5320)) 
            {
                SendClientMessage(playerid,Rojo,"* No estás en el lugar adecuado. Ve al lugar de trabajo primero.");
                SetPlayerCheckpoint(playerid, 2106.3269,-1789.8027,13.5608, 10); 
                PlayerInfo[playerid][pCheckpoint] = 6;
                PlayerInfo[playerid][pTrabajandoCP] = 1;
                
                return 1;
            }
            format(string,sizeof(string),"* Has recogido %d pizzas, llevas %d en total.",MAXPIZZAS-PlayerInfo[playerid][pPizzas],MAXPIZZAS);
            SendClientMessage(playerid,Verde,string);
            PlayerInfo[playerid][pPizzas]=MAXPIZZAS;
            return 1;
        }

        if (strcmp(cmd, "abandonar", true) == 0)
        {
            if (PlayerInfo[playerid][pTrabajando] == 1)
            {
                SendClientMessage(playerid,Verde,"* Has finalizado el reparto de pizzas");
                SendClientMessage(playerid,Verde,"No te olvides de dejar la moto en la pizzeria!");
                PlayerInfo[playerid][pTrabajando] = 0;
                DisablePlayerCheckpoint(playerid);
            }
            else
            {
                SendClientMessage(playerid,Rojo,"* No estás repartiendo.");
            }
            return 1;
        }
        
        if (strcmp(cmd, "vender", true) == 0)
        {
            new tmp[128];
            tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Gris, "USO: /vender pizza [IdJugador/ParteDelNombre]");
				return 1;
			}
			new giveplayerid;
			giveplayerid = ReturnUser(tmp);
            if(IsPlayerConnected(giveplayerid))
            {
                if(giveplayerid != INVALID_PLAYER_ID)
                {
                    if ( PlayerInfo[playerid][pPizzas]==0 ) {SendClientMessage(playerid,Rojo,"* No te quedan pizzas!"); return 1;}
                    if( GetDistanceBetweenPlayers(playerid, giveplayerid) < 5.0 )
                    {
                        format(string, sizeof(string), "* Ofreciste a %s una pizza por 20$.",pName(giveplayerid));
                        SendClientMessage(playerid, Azul, string);
                        format(string, sizeof(string), "* El pizzero %s te vende una pizza por 20$ (Escribe /aceptar pizza para comprarla).",pName(playerid));                        SendClientMessage(giveplayerid, Azul, string);
                        OfertaPizza[giveplayerid] = playerid;
                    }
                    else
                    {
                        SendClientMessage(playerid, Rojo, "* Jugador no cercano");
                    }
                }
            }
            return 1;
        }
        SendClientMessage(playerid,Blanco,"USO: /pizza (recoger/repartir/abandonar/vender)");
        return 1;
    }
//--------------------------------------------------------------------------------------------------------------------------------------------------
	if(strcmp(cmd,"/debugpizza",true) == 0 )
	{
        if(PlayerInfo[playerid][pAdmin] < 3)
	    {
	        SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
	        return 1;
	    }
		PlayerInfo[playerid][pTrabajando] = 0;
		PlayerInfo[playerid][pJob] = 6;
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pTrabajandoCP] = 0;
		SetPlayerPos(playerid, 2106.3269,-1789.8027,13.5608);
        return 1;
	}
	return 0;
}

Pizza_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pJob] == 6 && PlayerInfo[playerid][pCheckpoint] == 6)
	{
        DisablePlayerCheckpoint(playerid);
		if(PlayerInfo[playerid][pTrabajandoCP] == 0)
		{
			SendClientMessage(playerid,Verde,"* Sacas una pizza de la moto y la entregas");
            format(string,sizeof(string),"* Has ganado %d$", COSTEPIZZA);
            SendClientMessage(playerid,Verde,string);
            SafeGivePlayerMoney(playerid,COSTEPIZZA);
            PlayerInfo[playerid][pGanancias]+=COSTEPIZZA;
            PlayerInfo[playerid][pPizzas]--;
            if (PlayerInfo[playerid][pGanancias]>=400)
            {
                PlayerInfo[playerid][pTrabajando] = 0;
                SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue repartiendo dentro de 20 minutos.");
                PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1200);
                PlayerInfo[playerid][pGanancias]=0;
                SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
                SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
                return 1;
            }
            SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
            if (PlayerInfo[playerid][pPizzas] > 0)  CrearPedidoPizza(playerid); 
            else
            {
                PlayerInfo[playerid][pTrabajando] = 0;
                SendClientMessage(playerid,Naranja,"* No te quedan más pizzas.");
				return 1;
            }            
		}
        else if(PlayerInfo[playerid][pTrabajandoCP] == 1)
        {
            format(string,sizeof(string),"* Has recogido %d pizzas, llevas %d en total.",MAXPIZZAS-PlayerInfo[playerid][pPizzas],MAXPIZZAS);
            SendClientMessage(playerid,Verde,string);
            PlayerInfo[playerid][pPizzas]=MAXPIZZAS;
        }
        
		return 1;
	}
	return 0;
}

Pizza_OnPlayerEnterVehicle(playerid,vehicleid,ispassenger)
{
    if(PlayerInfo[playerid][pJob] == 6)
    { 
        if (GetVehicleModel(vehicleid) == 448 && !ispassenger)
        {
            KillTimer(TimerRespawnCar[vehicleid]);
        }
    }

}

Pizza_OnPlayerExitVehicle(playerid,vehicleid)
{
    if(PlayerInfo[playerid][pJob] == 6 && PlayerInfo[playerid][pTrabajando] == 1)
	{
        if (GetVehicleModel(vehicleid) == 448)
        {
            SendClientMessage(playerid,Naranja,"Si no te vuelves a subir a la moto en 30 segundos dejarás de repartir!");
            TimerRespawnCar[vehicleid] = SetTimerEx("PararRepartoPizza",30000,0,"dd",playerid,GetPlayerVehicle(playerid));
        }
    }
    else if(PlayerInfo[playerid][pJob] == 6 && PlayerInfo[playerid][pTrabajando] == 0)
	{
        if (GetVehicleModel(vehicleid) == 448)
        {
            TimerRespawnCar[vehicleid] = SetTimerEx("RespawnMotoPizza",120000,0,"dd",playerid,GetPlayerVehicle(playerid));
        }
    }
	return 1;
}

forward PararRepartoPizza(playerid,car);
public PararRepartoPizza(playerid,car)
{
    SendClientMessage(playerid,Verde,"* Has finalizado el reparto de pizzas");
    PlayerInfo[playerid][pTrabajando] = 0;
    DisablePlayerCheckpoint(playerid);
    RepairVehicle(CarInfo[car][cId]);
    CarInfo[car][cBroken] = 0;
    CarInfo[car][cStarted] = 0;
	SetVehicleToRespawn(CarInfo[car][cId]);
    SaveCar(car);

}

forward RespawnMotoPizza(playerid,car);
public RespawnMotoPizza(playerid,car)
{
    if (PlayerInfo[playerid][pCheckpoint] == 6) DisablePlayerCheckpoint(playerid);
    RepairVehicle(CarInfo[car][cId]);
    CarInfo[car][cBroken] = 0;
    CarInfo[car][cStarted] = 0;
    SetVehiclePos(CarInfo[car][cId],CarInfo[car][cLocationx], CarInfo[car][cLocationy], CarInfo[car][cLocationz]);
    SetVehicleZAngle(CarInfo[car][cId],CarInfo[car][cAngle]);
    SaveCar(car);
}

CrearPedidoPizza(playerid)
{
    new h;
    do
    {
        h=random(TotalCasas);
    }
    while ((CasaInfo[h][hInterior2]!=0 || !PointToPoint2D(2000.0, CasaInfo[h][hEx],CasaInfo[h][hEy],2115.7017,-1783.7582)) || IsNotValid2DZone(CasaInfo[h][hEx],CasaInfo[h][hEy]));
    
    SetPlayerCheckpoint(playerid, CasaInfo[h][hEx], CasaInfo[h][hEy], CasaInfo[h][hEz], 10);
    PlayerInfo[playerid][pCheckpoint] = 6;
    PlayerInfo[playerid][pTrabajandoCP] = 0;
    SendClientMessage(playerid,Verde,"* Alguien ha pedido una pizza, ve a la posición marcada");
}


LlamadaPizza(playerid,producto[])
{
	if ( strcmp(producto, "margarita", true) == 0 
      || strcmp(producto, "4 quesos", true) == 0 
      || strcmp(producto, "barbacoa", true) == 0  )
	{
        new num=0;
        for (new i=0; i<MAX_PLAYERS; i++)
        {
            if(PlayerInfo[i][pJob] == 6 && PlayerInfo[i][pDuty] > 0)
            {
                num++;
                SendClientMessage(i,Azul,"Alguien ha pedido una pizza, pon /aceptar pedido para realizarlo.");
            }
        }
        if (num>0)
        {
            format(string, sizeof(string),"(Teléfono): De acuerdo, marchando una pizza %s!",producto);
            SendClientMessage(playerid,Amarillo,string);
            SendClientMessage(playerid,Amarillo,"(Teléfono): Ahora mandamos un repartidor");
            SendClientMessage(playerid, Gris, "* Colgaron.");
            PlayerInfo[playerid][pHablandoPizza] = 0;
            for (new i=0;i<20;i++)
            {
                if (PedidosPizza[i][Activo]==0)
                {
                    GetPlayerPos(playerid,PedidosPizza[i][xpos],PedidosPizza[i][ypos],PedidosPizza[i][zpos]);
                    PedidosPizza[i][Activo]=1;
                    break;
                }
            }
        }
        else
        {
            SendClientMessage(playerid,Amarillo,"(Teléfono): Lo sentimos, ahora no tenemos repartidores disponibles, llame mas tarde");
            SendClientMessage(playerid, Gris, "* Colgaron.");
            PlayerInfo[playerid][pHablandoPizza] = 0;
        }
    }
    else if ( strcmp(producto, "nada", true) == 0 )
    {
        SendClientMessage(playerid,Amarillo,"(Teléfono): Pues no me haga perder el tiempo");
        SendClientMessage(playerid, Gris, "* Colgaron.");
        PlayerInfo[playerid][pHablandoPizza] = 0;
    }
    

}