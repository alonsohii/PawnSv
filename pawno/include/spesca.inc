#include <globalvars>
#include <a_samp>

new MarPicado;
new TipoDeMarea;

new Float:ChecksBancosPeces[10][3] = {
{799.6782,-2113.1348,-0.2681},
{687.6782,-2267.1348,-0.2864},
{417.4556,-2388.0286,-0.2127},
{156.7392,-2127.8455,-0.5812},
{1.0752,-1904.5907,-0.6603},
{227.4763,-2040.6285,-0.6742},
{394.2636,-2177.6577,-0.2585},
{442.9732,-1992.7094,-0.6310},
{634.6270,-2060.0115,-0.3702},
{565.3250,-2392.5818,-0.2007}
};
Sis_Pes_OnGameModeInit()
{
	CreateDynamicPickup(1274,23,359.8036,-2031.8665,7.8359);
	CreateDynamic3DTextLabel("Tienda de pesca",Rojo,359.8036,-2031.8665,8.500+0.2,10);
	CreateDynamic3DTextLabel("Utiliza /equipopesca para comprarlo.",Gris,359.8036,-2031.8665,8.500,10);
	return 1;
}
Sis_Pes_OnPlayerSpawn(playerid)
{
	if(PlayerInfo[playerid][pJob] == 3)
	{
		if(PlayerInfo[playerid][pHabilidadPescador] >= 0)
		{
			PlayerInfo[playerid][pNivelPescador] = 1;
		}	
		if( PlayerInfo[playerid][pHabilidadPescador] >= 100)
		{
			PlayerInfo[playerid][pNivelPescador] = 2;
		}
		if(PlayerInfo[playerid][pHabilidadPescador] >= 300)
		{
	    PlayerInfo[playerid][pNivelPescador] = 3;
		}
	}
	return 1;
}
Sis_Pes_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
	if (strcmp(cmd,"/pescar",true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}
	
		cmd = strtokex(cmdtext,idx);
		if(!strlen(cmd) || !IsNumeric(cmd) || strval(cmd) > 2)
		{
			SendClientMessage(playerid,Blanco,"USO: /pescar 1(Muelle) / 2(Barco)");
			return 1;
		}
		if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a pescar.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }
		PlayerInfo[playerid][pRutaDeTrabajo] = strval(cmd);
		if(PlayerInfo[playerid][pRutaDeTrabajo] == 1)
		{
			if(PlayerInfo[playerid][pEquipoParaTrabajar] != 1)
			{
			    SendClientMessage(playerid,Naranja,"* ¡No tienes el equipo para pescar! Alquilalo en la tienda de pesca ((/equipopesca)).");
			    return 1;
			}
			if(PlayerInfo[playerid][pTrabajando] == 1)
			{
			    SendClientMessage(playerid,Verde,"((¡Ahora usa /tirarcaña en la zona marcada!)).");
			    return 1;
			}
			if(PlayerInfo[playerid][pListoCobro] == 1)
			{
			    SendClientMessage(playerid,Rojo,"* Vende los peces primero.");
			    return 1;
			}
			if(PlayerInfo[playerid][pHabilidadPescador] >= 0)
			{
				PlayerInfo[playerid][pNivelPescador] = 1;
			}	
			if( PlayerInfo[playerid][pHabilidadPescador] >= 100)
			{
				PlayerInfo[playerid][pNivelPescador] = 2;
			}
			if(PlayerInfo[playerid][pHabilidadPescador] >= 300)
			{
				PlayerInfo[playerid][pNivelPescador] = 3;
			}
			SetPlayerCheckpoint(playerid,377.6505,-2087.6382,7.8359,30.0);
			SendClientMessage(playerid,VerdeOscuro,"* Puedes comenzar a pescar en la zona marcada, recuerda que puedes ver el estado de la mar con /infomarea.");
			SendClientMessage(playerid,VerdeOscuro,"* ¡Y no olvides usar /tirarcaña para que empiecen a picar! ¡Mucha suerte!.");
			PlayerInfo[playerid][pPuedePescar] = 1;
			PlayerInfo[playerid][pCheckpoint] = 2;
			PlayerInfo[playerid][pTrabajando] = 1;
			return 1;
		}
		if(PlayerInfo[playerid][pRutaDeTrabajo] == 2)
		{
		    if(PlayerInfo[playerid][pHabilidadPescador] == 3)
		    {
		        SendClientMessage(playerid,Rojo,"* ¡No tienes suficiente experiencia para pescar en un barco!");
		        return 1;
			}
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			{
		   	 	SendClientMessage(playerid,Rojo,"* Súbete en un barco.");
		    	return 1;
			}
			if(PlayerInfo[playerid][pListoCobro] == 1)
			{
			    SendClientMessage(playerid,Rojo,"* Vende los peces primero.");
			    return 1;
			}
			if(PlayerInfo[playerid][pTrabajando] == 1)
			{
			    SendClientMessage(playerid,Rojo,"((¡Ahora sube en un barco y usa /tirarredes!))");
			    return 1;
			}
			SendClientMessage(playerid,Verde,"* ¡Ya puedes comenzar a pescar! ((/tirarredes)).");
			PlayerInfo[playerid][pTrabajando] = 1;
			return 1;
		}
	}
	if(strcmp(cmd,"/equipopesca",true)==0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}
	
	    if(!PlayerToPoint(2.0,playerid,359.8036,-2031.8665,7.8359))
	    {
	        SendClientMessage(playerid,Rojo,"* No estás en el lugar adecuado. Ve a la tienda de pesca.");
	        return 1;
		}
	    if(PlayerInfo[playerid][pEquipoParaTrabajar] == 1)
	    {
		 SendClientMessage(playerid,Rojo,"* ¡Ya tienes un equio de pesca, ve a por los peces!.");
		 return 1;
		}
		if(PlayerInfo[playerid][pEquipoParaTrabajar] == 2)
		{
			if(SafeGetPlayerMoney(playerid) >= 5)
			{
	 		SendClientMessage(playerid,Blanco,"Vendedor dice: Vaya, hay un fuerte oleaje... toma otro anzuelo, serán 5$.");
		 	PlayerInfo[playerid][pEquipoParaTrabajar] = 1;
		 	SafeGivePlayerMoney(playerid, -5);
		 	}
		 	else
			{
		 	SendClientMessage(playerid,Rojo,"* No tienes dinero suficiente.");
		 	}
		 	return 1;
		}
		if(SafeGetPlayerMoney(playerid) >= 10)
		{
		SendClientMessage(playerid,Blanco,"Vendedor dice: Aqui tienes el equipo de pesca, serán 10$. Buena pesca! ((usa /pescar 1)).");
		PlayerInfo[playerid][pEquipoParaTrabajar] = 1;
		SafeGivePlayerMoney(playerid, -10);
		}
		else
		{
		SendClientMessage(playerid,Rojo,"* No tienes dinero suficiente.");
		}
		return 1;
	}
	if(strcmp(cmd,"/tirarcaña",true)==0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}
	
	    if(PlayerInfo[playerid][pPuedePescar] != 1)
	    {
	        SendClientMessage(playerid,Rojo,"* No has comenzado a pescar, usa /pescar.");
	        return 1;
		}
		if(PlayerInfo[playerid][pEquipoParaTrabajar] == 2)
		{
		    SendClientMessage(playerid,Rojo,"* ¡Ve a comprar otro anzuelo!.");
		    return 1;
		}
		if(PlayerInfo[playerid][pHaTiradoAnzuelo] !=0)
		{
		    SendClientMessage(playerid,Amarillo,"* Espera a que piquen.");
		    return 1;
		}
	    if(!PlayerToPoint(30.0,playerid,377.6505,-2087.6382,7.8359))
	    {
	        SendClientMessage(playerid,Rojo,"* No estás en la zona de pesca.");
	        return 1;
		}
        if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para volver a pescar.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }
		if(PlayerInfo[playerid][pNivelPescador] == 1 && PlayerInfo[playerid][pMaterialTrabajo] > 8000)
		{
		    SendClientMessage(playerid,Rojo,"* No puedes pescar más, vende los peces primero ((/dejarpescar y después /venderpeces)).");
		    return 1;
		}
		if(PlayerInfo[playerid][pNivelPescador] >= 2 && PlayerInfo[playerid][pMaterialTrabajo] > 10000)
		{
		    SendClientMessage(playerid,Rojo,"* No puedes pescar más, vende los peces primero ((/dejarpescar y después /venderpeces)).");
		    return 1;
		}
        format(string,sizeof(string),"* %s ha tirado el anzuelo al mar",pName(playerid));
		ProxDetector(20.0,playerid,string,Morado,Morado,Morado,Morado,Morado);
		TogglePlayerControllable(playerid,0);
        SetPlayerAttachedObject( playerid, TOOLS_SLOT, 18632, 6, 0.076712, 0.000000, 0.000000, 0.000000, 180.000000, 180.000000, 1.000000, 1.000000, 1.000000 );
        ApplyAnimation(playerid,"SWORD","sword_3",50.0,0,1,1,1,1,1);
		SetTimerEx("TiroCanaZona1",10000,0,"d",playerid);
		PlayerInfo[playerid][pHaTiradoAnzuelo] = 1;
		return 1;
	}
	if(strcmp(cmd,"/dejarpescar",true) == 0 )
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}
	
		if(PlayerInfo[playerid][pMaterialTrabajo] == 0)
		{
		    SendClientMessage(playerid,Rojo,"* No tienes nada para vender. Pesca primero!.");
		    return 1;
		}
	
	    PlayerInfo[playerid][pListoCobro] = 1;
		SendClientMessage(playerid,Verde,"* Ahora ve a vender los peces al mercado (Zona marcada).");
		if(PlayerInfo[playerid][pRutaDeTrabajo] == 1)
		{
			SetPlayerCheckpoint(playerid,2416.1550,-2468.6348,13.6250,10.0);
			PlayerInfo[playerid][pCheckpoint] = 2;
		}
		else if(PlayerInfo[playerid][pRutaDeTrabajo] == 2)
		{
			SetPlayerCheckpoint(playerid,2675.3132,-2260.4341,-0.7959,15.0);
			PlayerInfo[playerid][pCheckpoint] = 2;
		}
		return 1;
	}
	if(strcmp(cmd,"/venderpeces",true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}

	    if( (!PlayerToPoint(10.0,playerid,2416.1550,-2468.6348,13.6250) && PlayerInfo[playerid][pRutaDeTrabajo] == 1) || (!PlayerToPoint(25.0,playerid,2675.3132,-2260.4341,-0.7959) && PlayerInfo[playerid][pRutaDeTrabajo] == 2) )
	    {
	        SendClientMessage(playerid,Rojo,"* ¡No estás en la zona de venta!.");
	        return 1;
		}
		if(PlayerInfo[playerid][pMaterialTrabajo] == 0)
		{
		    SendClientMessage(playerid,Rojo,"* ¡No tienes nada para vender!.");
			return 1;
		}
		new DineroPagado;
		DineroPagado = ((PlayerInfo[playerid][pMaterialTrabajo] / 1000 )* 40);
	    PlayerInfo[playerid][pTrabajando] = 0;
		SendClientMessage(playerid,Blanco,"Comprador dice: Arr, gracias por la mercancía marinero!");
		format(string,sizeof(string),"* Has vendido %d gramos de pescado por %d$",PlayerInfo[playerid][pMaterialTrabajo],DineroPagado);
		SendClientMessage(playerid,VerdeOscuro,string);
        PlayerInfo[playerid][pGanancias]+=DineroPagado;
        if (PlayerInfo[playerid][pGanancias]>=600)
        {
            PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1800);
   			SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue pescando dentro de 30 minutos.");
            PlayerInfo[playerid][pGanancias] = 0;
            SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
        }
        SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
		PlayerInfo[playerid][pCheckpoint] = 0;
		DisablePlayerCheckpoint(playerid);
		PlayerInfo[playerid][pMaterialTrabajo] = 0;
		SaveValues(playerid, "Inventario");
		PlayerInfo[playerid][pEquipoParaTrabajar] = 0;
		PlayerInfo[playerid][pHaTiradoRedes] = 0;
		PlayerInfo[playerid][pRutaDeTrabajo] = 0;
		PlayerInfo[playerid][pListoCobro] = 0;
		SafeGivePlayerMoney(playerid,DineroPagado);
		PlayerInfo[playerid][pPuntosHabilidadGanados] = (DineroPagado/100);
		PlayerInfo[playerid][pHabilidadPescador] += PlayerInfo[playerid][pPuntosHabilidadGanados];
		if(PlayerInfo[playerid][pHabilidadPescador] >= 100 && PlayerInfo[playerid][pNivelPescador] == 1)
		{
		    SendClientMessage(playerid,Verde,"* Felicidades, ahora tienes más experiencia en el arte de la pesca");
		    PlayerInfo[playerid][pNivelPescador]++;
		}
		if(PlayerInfo[playerid][pHabilidadPescador] >= 300 && PlayerInfo[playerid][pNivelPescador] == 2)
		{
		    SendClientMessage(playerid,Verde,"* Felicidades, ¡ahora puedes usar barcos para pescar en alta mar!");
			PlayerInfo[playerid][pNivelPescador]++;
		}
		if(PlayerInfo[playerid][pNivelPescador] == 1)
		{
		PlayerInfo[playerid][pPuntosHabilidadRestantes] = 100 - PlayerInfo[playerid][pHabilidadPescador];
		format(string,sizeof(string),"* Tu habilidad como pescador aumentó %d ptos. Puntos totales %d. Puntos para el siguiente nivel %d. Nivel actual %d",PlayerInfo[playerid][pPuntosHabilidadGanados],PlayerInfo[playerid][pHabilidadPescador],PlayerInfo[playerid][pPuntosHabilidadRestantes],PlayerInfo[playerid][pNivelPescador]);
		SendClientMessage(playerid,Amarillo,string);
		}
		if(PlayerInfo[playerid][pNivelPescador] == 2)
		{
		PlayerInfo[playerid][pPuntosHabilidadRestantes] = 300 - PlayerInfo[playerid][pHabilidadPescador];
		format(string,sizeof(string),"* Tu habilidad como pescador aumentó %d ptos. Puntos totales %d. Puntos para el siguiente nivel %d. Nivel actual %d",PlayerInfo[playerid][pPuntosHabilidadGanados],PlayerInfo[playerid][pHabilidadPescador],PlayerInfo[playerid][pPuntosHabilidadRestantes],PlayerInfo[playerid][pNivelPescador]);
		SendClientMessage(playerid,Amarillo,string);
		}
		SaveValues(playerid,"Habilidades");
		return 1;
	}
	if(strcmp(cmd,"/mispeces",true)==0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador!");
			return 1;
		}
	
		if(PlayerInfo[playerid][pEquipoParaTrabajar] == 0 && PlayerInfo[playerid][pRutaDeTrabajo] == 1)
		{
		    SendClientMessage(playerid,Rojo,"* No alquilaste ningún equipo para pescar");
		    return 1;
		}
	    if(PlayerInfo[playerid][pEquipoParaTrabajar] > 0 && PlayerInfo[playerid][pRutaDeTrabajo] == 1)
	    {
			format(string,sizeof(string),"* Tienes en tu cubo %d gramos de peces",PlayerInfo[playerid][pMaterialTrabajo]);
			SendClientMessage(playerid,Amarillo,string);
			return 1;
		}
		if(PlayerInfo[playerid][pRutaDeTrabajo] == 2)
		{
			format(string,sizeof(string),"* Tienes en tu cubo %d gramos de peces",PlayerInfo[playerid][pMaterialTrabajo]);
			SendClientMessage(playerid,Amarillo,string);
			return 1;
		}
		return 1;
	}
	if(strcmp(cmd,"/picar",true)==0) // DEBUG INSIDE, ESTO DEBERIA IR CON EL SISTEMA DE TIEMPO
	{
		if(PlayerInfo[playerid][pAdmin] < 2)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser Administrador! ");
			return 1;
		}
		if(MarPicado == 0)
		{
			MarPicado = 1;
			SendClientMessage(playerid,Amarillo,"MarPicado 1");
		}
		else
		{
			MarPicado = 0;
			SendClientMessage(playerid,Amarillo,"MarPicado 0");
		}
		return 1;
	}
	if(strcmp(cmd,"/infomarea",true)==0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}
		if(!PlayerToPoint(2.0,playerid,359.8036,-2031.8665,7.8359) && PlayerInfo[playerid][pRutaDeTrabajo] != 2)
	    {
	        SendClientMessage(playerid,Rojo,"* No estás en el lugar adecuado,ve a la tienda de pesca");
	        return 1;
		}
		new Marea[128];
		new Picado[128];
		new hora, minuto, segundo;
		gettime(hora, minuto, segundo);
 		if(hora <= 6 || hora >= 22)
		{
		    TipoDeMarea = 1;
		}
		else
		{
		    TipoDeMarea = 0;
		}
		if(TipoDeMarea == 0)
		{
		    
			format(string,sizeof(string)," 'Marea Normal' ");
			Marea = string;
		}
		if(TipoDeMarea == 1)
		{
		    format(string,sizeof(string)," 'Marea Alta' ");
		    Marea = string;
		}
		if(MarPicado == 0)
		{
		    format(string,sizeof(string)," en calma ");
			Picado = string;
		}
		if(MarPicado == 1)
		{
		    format(string,sizeof(string)," con fuerte oleaje ");
		    Picado = string;
		}
		SendClientMessage(playerid,Morado,"* Observas atentamente el cartel que informa del estado de las mareas");
		SendClientMessage(playerid,AzulOscuro,"________________________________");
		format(string,sizeof(string),"El estado de las mareas en estos momentos es %s y está %s",Marea,Picado);
		SendClientMessage(playerid,Naranja,string);
		if(MarPicado == 1)
		{
		    SendClientMessage(playerid,Rojo,"Se recomienda extremar la precaución");
		}
		else
		{
		    SendClientMessage(playerid,Verde,"Puede pescar con normalidad");
		}
		SendClientMessage(playerid,AzulOscuro,"________________________________");
		//printf("Jugador en posición correcta");
		return 1;
 	}
	if(strcmp(cmd,"/tirarredes",true)== 0)
	{
		if(PlayerInfo[playerid][pJob] != 3)
		{
			SendClientMessage(playerid, Rojo, "* Debes ser pescador! ");
			return 1;
		}
	    if(PlayerInfo[playerid][pRutaDeTrabajo] != 2)
	    {
			SendClientMessage(playerid,Rojo,"* No estas pescando en alta mar");
			return 1;
		}
		if(PlayerInfo[playerid][pHaTiradoRedes] == 1)
		{
		    SendClientMessage(playerid,Rojo,"* Ya tiraste las redes a la mar, ¡ve a pescar!");
		    return 1;
		}
		if(PlayerInfo[playerid][pMaterialTrabajo] > 20000)
		{
		    SendClientMessage(playerid,Verde,"* ¡Vende los peces! ((/dejarpescar y /venderpeces))");
		    return 1;
		}
		if(PlayerInfo[playerid][pTrabajando] != 1)
		{
		    SendClientMessage(playerid,Rojo,"* Utiliza primero /pescar 2");
		    return 1;
		}
		if(PlayerInfo[playerid][pRedRota] == 1)
		{
		    SendClientMessage(playerid,Verde,"* Colocas satisfactoriamente otra red y puedes volver a pescar");
		    PlayerInfo[playerid][pRedRota] = 0;
		}
		PlayerInfo[playerid][pHaTiradoRedes] = 1;
		SendClientMessage(playerid,Verde,"* El radar ha localizado varios bancos de peces, la ruta está programada, puedes empezar");
		new bancopeces = random(sizeof(ChecksBancosPeces));
		SetPlayerCheckpoint(playerid,ChecksBancosPeces[bancopeces][0],ChecksBancosPeces[bancopeces][1],ChecksBancosPeces[bancopeces][2],15.0);
		PlayerInfo[playerid][pCheckpoint] = 2;
        PlayerPlaySound(playerid,1137,0.0,0.0,10.0);
		return 1;
	}
	return 0;
}
Sis_Pes_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 2 && PlayerInfo[playerid][pJob] == 3)
	{
		DisablePlayerCheckpoint(playerid);
		PlayerInfo[playerid][pCheckpoint] = 0;
		if(PlayerInfo[playerid][pHaTiradoRedes] == 1)
		{
			if(PlayerInfo[playerid][pRedRota] == 1)
			{
				SendClientMessage(playerid,Rojo,"* No tienes red ¿Qué quieres pescar?");
				return 1;
			}
			if(PlayerInfo[playerid][pListoCobro] == 1)
			{
				return 1;
			}
			if(PlayerInfo[playerid][pMaterialTrabajo] < 20000)
			{
				PlayerPlaySound(playerid,1137,0.0,0.0,10.0);
				TiroCanaZona2(playerid);
				new bancopeces = random(sizeof(ChecksBancosPeces));
				SetPlayerCheckpoint(playerid,ChecksBancosPeces[bancopeces][0],ChecksBancosPeces[bancopeces][1],ChecksBancosPeces[bancopeces][2],15.0);
				PlayerInfo[playerid][pCheckpoint] = 2;
			}
			else
			{
				SendClientMessage(playerid,Amarillo,"* El barco esta cargado, vende los peces ((/dejarpescar y /venderpeces en el punto)).");
			}
		}
		return 1;
	}
	return 0;
}
forward TiroCanaZona1(playerid);
public TiroCanaZona1(playerid)
{
	new hora, minuto, segundo;
	gettime(hora, minuto, segundo);
 	if(hora <= 6 || hora >= 22)
	{
	    TipoDeMarea = 1;
	}
	else
	{
	    TipoDeMarea = 0;
	}
    
	new pesodepescado = random(1000);
	if(TipoDeMarea == 0 && MarPicado == 0) // normal y mar sin picar
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos",pesodepescado);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado;
		}
		if(250 < pesodepescado < 400)
		{
		format(string,sizeof(string),"* No hay peces a la vista, vuelve a intentarlo");
		SendClientMessage(playerid,Rojo,string);
		}
		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una lubina de %d gramos",pesodepescado);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado;
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos",pesodepescado);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado;
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado un atún de %d gramos",pesodepescado);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado;
		}
		TogglePlayerControllable(playerid,1);
		PlayerInfo[playerid][pHaTiradoAnzuelo] = 0;
	}
	if(TipoDeMarea == 1 && MarPicado == 1) // Marea alta y mar picado
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos",pesodepescado+100);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+100;
		}
		if(250 < pesodepescado < 400)
		{
		SendClientMessage(playerid,Rojo,"* ¡Se ha roto el anzuelo! ((compra otro con /equipopesca en la tienda))");
		PlayerInfo[playerid][pEquipoParaTrabajar] = 2;
		}
		if(400 < pesodepescado < 600)
		{
		format(string,sizeof(string),"* Has pescado una lubina de %d gramos",pesodepescado+100);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+100;
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos",pesodepescado+100);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+100;
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado un atún de %d gramos",pesodepescado+100);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+100;
		}
	}
	if(TipoDeMarea == 1 && MarPicado == 0) // Marea alta y sin picar
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos",pesodepescado+50);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+50;
		}
		if(250 < pesodepescado < 400)
		{
		format(string,sizeof(string),"* Has pescado una anchoa de %d gramos",pesodepescado+50);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+50;
		}
		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una lubina de %d gramos",pesodepescado+50);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+50;
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos",pesodepescado+50);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+50;
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado un atún de %d gramos",pesodepescado+50);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+50;
		}
	}
	if(TipoDeMarea == 0 && MarPicado == 1) // Marea normal y mar picado
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos",pesodepescado+75);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+75;
		}
		if(250 < pesodepescado < 400)
		{
		SendClientMessage(playerid,Rojo,"* ¡Se ha roto el anzuelo! ((compra otro con /equipopesca en la tienda))");
		PlayerInfo[playerid][pEquipoParaTrabajar] = 2;
		}
		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos",pesodepescado+75);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+75;
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos",pesodepescado+75);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+75;
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado un atún de %d gramos",pesodepescado+75);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += pesodepescado+75;
		}
	}
	TogglePlayerControllable(playerid,1);
    ClearAnimations(playerid);
    RemovePlayerAttachedObject(playerid,TOOLS_SLOT);
	PlayerInfo[playerid][pHaTiradoAnzuelo] = 0;
	SaveValues(playerid, "Inventario");
	return 1;
}
forward TiroCanaZona2(playerid);
public TiroCanaZona2(playerid)
{
	new hora, minuto, segundo;
	gettime(hora, minuto, segundo);
 	if(hora <= 6 || hora >= 22)
	{
	    TipoDeMarea = 1;
	}
	else
	{
	    TipoDeMarea = 0;
	}
	new pesodepescado = random(1000);
	if(TipoDeMarea == 0 && MarPicado == 0) // normal y mar sin picar
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos.",pesodepescado+100);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+100);
		}
		if(250 < pesodepescado < 400)
		{
		format(string,sizeof(string),"* Has pescado una anchoa de %d gramos.",pesodepescado+100);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+100);
		}
		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una lubina de %d gramos.",pesodepescado+100);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+100);
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos.",pesodepescado+100);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+100);
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado una ñocla de %d gramos.",pesodepescado+100);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+100);
		}
	}
	if(TipoDeMarea == 1 && MarPicado == 1) // Marea alta y mar picado
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos.",pesodepescado+200);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+200);
		}
		if(250 < pesodepescado < 300)
		{
		format(string,sizeof(string),"* Has pescado una anchoa de %d gramos.",pesodepescado+200);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+200);
		}
 		if(300 < pesodepescado < 400)
		{
		format(string,sizeof(string),"* Se han roto las redes, pon unas nuevas ((/tirarredes)).");
		SendClientMessage(playerid,Rojo,string);
		PlayerInfo[playerid][pRedRota] = 1;
		}

		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una lubina de %d gramos.",pesodepescado+200);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+200);
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos.",pesodepescado+200);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+200);
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado una ñocla de %d gramos.",pesodepescado+200);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+200);
		}
	}
	if(TipoDeMarea == 1 && MarPicado == 0) // Marea alta y sin picar
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos.",pesodepescado+150);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+150);
		}
		if(250 < pesodepescado < 400)
		{
		format(string,sizeof(string),"* Has pescado una anchoa de %d gramos.",pesodepescado+150);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+150);
		}
		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una lubina de %d gramos.",pesodepescado+150);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+150);
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos.",pesodepescado+150);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+150);
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado una ñocla de %d gramos.",pesodepescado+150);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+150);
		}
	}
	if(TipoDeMarea == 0 && MarPicado == 1) // Marea normal y mar picado
	{
		if(0 < pesodepescado < 250)
		{
		format(string,sizeof(string),"* Has pescado una sardina de %d gramos.",pesodepescado+225);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+225);
		}
		if(250 < pesodepescado < 300)
		{
		format(string,sizeof(string),"* Has pescado una anchoa de %d gramos.",pesodepescado+225);
		SendClientMessage(playerid,AzulClaro,string);
		PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+225);
		}
		if(300 < pesodepescado < 400)
		{
		format(string,sizeof(string),"* Se han roto las redes, pon unas nuevas ((/tirarredes)).");
		SendClientMessage(playerid,Rojo,string);
		PlayerInfo[playerid][pRedRota] = 1;
		}
		if(400 < pesodepescado < 600)
		{
	    format(string,sizeof(string),"* Has pescado una lubina de %d gramos.",pesodepescado+225);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+225);
		}
		if(600 < pesodepescado < 900)
		{
	    format(string,sizeof(string),"* Has pescado una raya de %d gramos.",pesodepescado+225);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+225);
		}
		if(900 < pesodepescado < 1000)
		{
	    format(string,sizeof(string),"* Has pescado una ñocla de %d gramos.",pesodepescado+225);
	    SendClientMessage(playerid,AzulClaro,string);
	    PlayerInfo[playerid][pMaterialTrabajo] += (pesodepescado+225);
		}
	}
	SaveValues(playerid, "Inventario");
	return 1;
}