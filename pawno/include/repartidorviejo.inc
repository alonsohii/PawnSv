#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <deathac>

new RecogerPedido[MAX_PLAYERS];
new PedidoRecogido[MAX_PLAYERS];
new Pedido[MAX_PLAYERS];

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
            new n=0;
	        SendClientMessage(playerid, Verde, "|____________ PEDIDOS ____________|");
	        for(new i = 1; i < MAX_PEDIDOS && n < 9; i++)
	        {
	            if(Pedidos[i][peState] == 1)
	            {
                    n++;
                    for(new neg; neg < MAX_NEGOCIOS; neg++)
                    {
                        if (NegocioInfo[neg][nId] == Pedidos[i][peNeg])
                        {
                            format(string, sizeof(string), "%d. %s - %d Productos", i, NegocioInfo[neg][nName], Pedidos[i][peCantidad]);
                            SendClientMessage(playerid, Amarillo, string);
                            break;
                        }
                    }
				}
			}
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "* No eres transportista.");
		}
		return 1;
	}
	
	if(strcmp(cmd, "/hacerpedido", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
		    SendClientMessage(playerid, Gris, "USO: /hacerpedido [cantidad]");
		    return 1;
		}
		
		new cant = strval(tmp);
		
		if(PlayerInfo[playerid][pPbiskey] != NOEXISTE)
		{
		    new llave = PlayerInfo[playerid][pPbiskey];
            for(new i=1; i < MAX_NEGOCIOS; i++)
            {
                if (NegocioInfo[i][nId] == llave)
                {
                    if(NegocioInfo[i][nCajaFuerte] >= cant*3)
                    {
                        HacerPedido(llave, cant);
                        SendClientMessage(playerid, Verde, "* Has hecho un pedido, te cobrarán cuando lo dejen en tu Negocio!");
                    }
                    else
                    {
                        SendClientMessage(playerid, Rojo, "* No tienes dinero para pagar!");
                    }
                    break;
                }
            }
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "No eres dueño de ningun negocio!");
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
		if(Pedido[playerid]>0)
		{
		    SendClientMessage(playerid, Rojo, "* No puedes entregar 2 pedidos al mismo tiempo!");
		    return 1;
		}
	    tmp = strtokex(cmdtext, idx);
	    if(!strlen(tmp))
		{
		    SendClientMessage(playerid, Gris, "USO: /atenderpedido [ID]");
		    return 1;
		}
		new pid = strval(tmp);
		new tmpcar = GetPlayerVehicle(playerid);
		if(GetVehicleModel(CarInfo[tmpcar][cId]) == 499)
		{
            if(Pedidos[pid][peState] == 1)
            {
                RecogerPedido[playerid] = Pedidos[pid][peCantidad];
                Pedido[playerid] = pid;
                Pedidos[pid][peState] = 2;
                SetTimerEx("CancelarPedido",900000,0,"i",pid);
                SetPlayerCheckpoint(playerid, 2176.0149,-2266.5845,13.3839, 8.0);
                SendClientMessage(playerid, Rojo, "* La carga esta esperando.");
            }
            else
            {
                SendClientMessage(playerid, Rojo, "Pedido no disponible! (/pedidos)");
            }
		}
		else
		{
		    SendClientMessage(playerid, Rojo, "Tienes que estar en una furgoneta de reparto");
		}
		return 1;
	}
    return 0;
}


HacerPedido(negid, cantidad)
{
	for(new i = 1; i < MAX_PEDIDOS; i++)
	{
	    if(Pedidos[i][peState] == 0)
	    {
	        Pedidos[i][peState] = 1;
	        Pedidos[i][peNeg] = negid;
            for(new neg; neg < MAX_NEGOCIOS; neg++)
            {
                if (NegocioInfo[neg][nId] == negid)
                {
                    Pedidos[i][peX] = NegocioInfo[neg][nEPos_x];
                    Pedidos[i][peY] = NegocioInfo[neg][nEPos_y];
                    Pedidos[i][peZ] = NegocioInfo[neg][nEPos_z];
                    break;
                }
            }
	        Pedidos[i][peCantidad] = cantidad;
	        //printf("Nuevo Pedido de id: %d", Pedidos[i][peNeg]);
	        break;
		}
	}
	return 1;
}

forward CancelarPedido(pid);
public CancelarPedido(pid)
{
    if(Pedidos[pid][peState] == 2)
    {
        for (new playerid; playerid < MAX_PLAYERS;playerid++)
        {
            if (Pedido[playerid] == pid)
            {
                Pedido[playerid] = 0;
                Pedidos[pid][peState] = 0;
                PedidoRecogido[playerid] = 0;
                RecogerPedido[playerid] = 0;
                Pedidos[pid][peState] = 1;
                DisablePlayerCheckpoint(playerid);
            }
        }
    }
}

BorrarPedido(pid)
{
    new maxpedido;
    for (new i=pid; Pedidos[i][peState] > 0 || i+1 < MAX_PEDIDOS; i++)
    {
        Pedidos[i][peNeg]=       Pedidos[i+1][peNeg];
        Pedidos[i][peX]=         Pedidos[i+1][peX];
        Pedidos[i][peY]=         Pedidos[i+1][peY];
        Pedidos[i][peZ]=         Pedidos[i+1][peZ];
        Pedidos[i][peCantidad]=  Pedidos[i+1][peCantidad];
        Pedidos[i][peState]=     Pedidos[i+1][peState];
        Pedidos[i][peTimer]=     Pedidos[i+1][peTimer];
        maxpedido=i+1;
    }
    for (new playerid=0; playerid<MAX_PLAYERS; playerid++)
    {
        if (Pedido[playerid] > pid && Pedido[playerid] < maxpedido)
            Pedido[playerid]--;
    }
}

Reparto_OnPlayerEnterCheckpoint(playerid)
{
	if(RecogerPedido[playerid] > 0)
	{
		PedidoRecogido[playerid] = RecogerPedido[playerid];
		DisablePlayerCheckpoint(playerid);
		new pid = Pedido[playerid];
        SetPlayerCheckpoint(playerid, Pedidos[pid][peX], Pedidos[pid][peY], Pedidos[pid][peZ], 8.0);
        SendClientMessage(playerid, Verde, "Ahora entrega el pedido en el Negocio!");
        RecogerPedido[playerid] = 0;
        return 1;
	}
	if(PedidoRecogido[playerid] > 0)
	{
	    DisablePlayerCheckpoint(playerid);
		new pid = Pedido[playerid];
		new cant = PedidoRecogido[playerid];
		new negocio = Pedidos[pid][peNeg];
        for(new neg; neg < MAX_NEGOCIOS; neg++)
        {
            if (NegocioInfo[neg][nId] == negocio)
            {
                if(NegocioInfo[neg][nOwned] == 1)
                {
                    NegocioInfo[neg][nCajaFuerte] -= cant*3;
                    NegocioInfo[neg][nProd] += cant;
                }
                else
                {
                    NegocioInfo[neg][nProd] += cant;
                }
                SaveNegocio(neg);
            }
        }
		SafeGivePlayerMoney(playerid, 50);
		SendClientMessage(playerid, Verde, "Entregaste el Pedido con Exito!");
        Pedido[playerid] = 0;
		PedidoRecogido[playerid] = 0;
        BorrarPedido(pid);
		return 1;
	}
    return 0;
}