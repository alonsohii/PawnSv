#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <deathac>

/*new RecogerPedido[MAX_PLAYERS];
new PedidoRecogido[MAX_PLAYERS];
new Pedido[MAX_PLAYERS];
*/

#define MAX_PEDIDOS 13
enum peInfo
{
    peNombre[32],
    Float:peX,
	Float:peY,
	Float:peZ,
}
new Pedidos[MAX_PEDIDOS][peInfo] =
{
    {"Tienda de comestibles Jefferson",2148.2593,-1194.4259,23.6155},
    {"Conchita market las flores",2745.0344,-1455.9290,30.2366},
    {"Pig Pen",2412.6997,-1227.5177,24.2311},
    {"El gran burrito",2341.1379,-1315.6505,23.8626},
    {"Tienda de repuestos",2409.6284,-1545.2096,23.7863},
    {"Carniceria el pueblo",2469.9028,-1546.2129,23.7786},
    {"Pizzeria",2121.5994,-1782.6357,13.1715},
    {"24/7 norte",1316.5543,-873.0004,39.3611}, 
    {"Tienda de ropa en richman",483.2520,-1531.6512,19.3304}, 
    {"Tienda de discos",816.2139,-1391.9031,13.1961}, 
    {"Almacen muebles",992.4648,-1375.7102,13.1120}, 
    {"98 Cents Ayuntamiento",1375.7219,-1885.6844,13.2894},
    {"Liquor Store Corona",1986.7334,-2067.1311,13.1581}
};

Reparto_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
    new tmp[128];
    
	if(strcmp(cmd, "/pedidos", true) == 0)
	{
	    if(PlayerInfo[playerid][pJob] == 7)
	    {
	        SendClientMessage(playerid, Verde, "|____________ PEDIDOS ____________|");
	        for(new i = 0; i < MAX_PEDIDOS; i++)
	        {
                if (  ( (PlayerInfo[playerid][pRutasCompletadas] >> i) & 1 ) == 0 )
                {
                    format(string,sizeof(string),"%d - %s", i+1,Pedidos[i][peNombre]);
                    SendClientMessage(playerid,Amarillo,string);
				}
			}
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No eres repartidor.");
		}
		return 1;
	}
    
    if(strcmp(cmd, "/atenderpedido", true) == 0)
	{
	    if(PlayerInfo[playerid][pJob] != 7)
	    {
	        SendClientMessage(playerid, Rojo, "* No eres repartidor!");
	        return 1;
		}
		if(PlayerInfo[playerid][pDuty] == 0) { SendClientMessage(playerid, Rojo, "* No estás de servicio! (/deservicio)"); return 1; }        
        if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a repartir.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }
      
		if(PlayerInfo[playerid][pTrabajando]>0)
		{
		    SendClientMessage(playerid, Rojo, "* No puedes entregar 2 pedidos al mismo tiempo!");
		    return 1;
		}
        
        
        if( GetVehicleModel(GetPlayerVehicleID(playerid)) != 499) { SendClientMessage(playerid,Rojo,"No llevas una furgoneta de reparto!"); return 1; }
        if( GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendClientMessage(playerid,Rojo,"No llevas una furgoneta de reparto!"); return 1; }

	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
		{
		    SendClientMessage(playerid, Gris, "USO: /atenderpedido [ID]");
		    return 1;
		}
		new pid = strval(tmp)-1;
	    if( !(-1 < pid < MAX_PEDIDOS) )
		{
		    SendClientMessage(playerid, Gris, "USO: /atenderpedido [ID]");
		    return 1;
		}
        if ( (PlayerInfo[playerid][pRutasCompletadas] >> pid) & 1 )
		{
		    SendClientMessage(playerid, Gris, "USO: /atenderpedido [ID]");
		    return 1;
		}
        PlayerInfo[playerid][pRutaDeTrabajo]= pid;
        
        SetPlayerCheckpoint(playerid,2206.2412,-2297.2258,14.4695,10.0);
        PlayerInfo[playerid][pCheckpoint]=7;
        PlayerInfo[playerid][pTrabajandoCP] = 0;
        PlayerInfo[playerid][pTrabajando]= 1;
        SendClientMessage(playerid,Verde,"* Ve a recoger la carga al almacén");
        
		return 1;
	}
    
    if(strcmp(cmd, "/pedidodebug", true) == 0)
	{
        if(PlayerInfo[playerid][pAdmin] < 3)
        {
            SendClientMessage(playerid, Rojo, "* No formas parte del Staff!");
            return 1;
        }
        
        if(PlayerInfo[playerid][pTrabajandoCP] == 0 && PlayerInfo[playerid][pCheckpoint] == 7) 
            SetVehiclePos(GetPlayerVehicleID(playerid),2206.2412,-2297.2258,14.4695);
        if(PlayerInfo[playerid][pTrabajandoCP] == 1 && PlayerInfo[playerid][pCheckpoint] == 7) 
        {
            new id=PlayerInfo[playerid][pRutaDeTrabajo];
            SetVehiclePos(GetPlayerVehicleID(playerid),Pedidos[id][peX],Pedidos[id][peY],Pedidos[id][peZ]);
        }
        if(PlayerInfo[playerid][pTrabajandoCP] == 2 && PlayerInfo[playerid][pCheckpoint] == 7) 
            SetVehiclePos(GetPlayerVehicleID(playerid),2206.2412,-2297.2258,14.4695);
        return 1;
    }


    return 0;
}



Reparto_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pJob] == 7 && PlayerInfo[playerid][pCheckpoint] == 7)
	{
        if( GetVehicleModel(GetPlayerVehicleID(playerid)) != 499) { SendClientMessage(playerid,Rojo,"No llevas una furgoneta de reparto!"); return 1; }
        if( GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendClientMessage(playerid,Rojo,"No llevas una furgoneta de reparto!"); return 1; }
        DisablePlayerCheckpoint(playerid);
        if(PlayerInfo[playerid][pTrabajandoCP] == 0)
        {
            SendClientMessage(playerid,Verde,"* Has recogido la carga, llevas 10 productos. Ahora entrégalos en el lugar indicado");
            new id=PlayerInfo[playerid][pRutaDeTrabajo];
            SetPlayerCheckpoint(playerid,Pedidos[id][peX],Pedidos[id][peY],Pedidos[id][peZ],10.0);
            PlayerInfo[playerid][pCheckpoint]=7;
            PlayerInfo[playerid][pTrabajandoCP] = 1;
        }
        
        else if(PlayerInfo[playerid][pTrabajandoCP] == 1)
        {
            SendClientMessage(playerid,Verde,"* Has entregado la carga. Vuelve al almacén para recoger tu paga");
            SetPlayerCheckpoint(playerid,2206.2412,-2297.2258,14.4695,10.0);
            PlayerInfo[playerid][pCheckpoint]=7;
            PlayerInfo[playerid][pTrabajandoCP] = 2;
        }

        else if(PlayerInfo[playerid][pTrabajandoCP] == 2)
        {
            SendClientMessage(playerid,Verde,"* Has ganado 300$");
            SafeGivePlayerMoney(playerid,300);
            PlayerInfo[playerid][pGanancias]+=300;
            if (PlayerInfo[playerid][pGanancias]>=1250) 
            {
                SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue repartiendo dentro de 40 minutos.");
                PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+2400);
                PlayerInfo[playerid][pGanancias]=0;
                SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
            }
            SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
            
            PlayerInfo[playerid][pCheckpoint]=NOEXISTE;
            PlayerInfo[playerid][pTrabajandoCP] = NOEXISTE;
            PlayerInfo[playerid][pTrabajando]=0;

            new i = PlayerInfo[playerid][pRutaDeTrabajo];
            PlayerInfo[playerid][pRutasCompletadas] |= (1 << i);
            PlayerInfo[playerid][pRutaDeTrabajo]=NOEXISTE;

            if ( ( PlayerInfo[playerid][pRutasCompletadas] & ((1 << MAX_PEDIDOS) - 1) ) == ( (1 << MAX_PEDIDOS) - 1) )
            {
                PlayerInfo[playerid][pRutasCompletadas]=0;
            }
        }
		return 1;
    }
    return 0;
}