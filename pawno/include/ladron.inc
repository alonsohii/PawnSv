#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <deathac>

#define TIEMPO_ESPERA_ROBO 600 // 10 minutos 
enum t_informe
{
    infTipo,  //1: negocio, 2: casa;
    infId,
    infH,
    infM,    //hora, minutos, segundos
    infS,
    infExiste,
}
new InformesRobos[8][t_informe];
new BuscandoObjetos[MAX_PLAYERS];

new Float:PuntosEntrega[][3]=
{
    {2351.5833,-653.9247,127.7818},
    {797.5244,-617.7917,16.0630},
    {-83.7538,-1557.9482,2.3378}
};

new Float:CasasEmpeno[4][3]=
{
    {2422.5208,-1954.8135,13.5469},
    {2722.9695,-2033.5568,13.5472},
    {2507.0825,-1725.4403,13.5469},
    {2151.6157,-1903.5575,13.5524}
};


Ladron_OnGameModeInit()
{
    for (new i; i<sizeof(CasasEmpeno);i++)
    {
        CreateDynamic3DTextLabel("Casa de empeño",AzulOscuro,CasasEmpeno[i][0],CasasEmpeno[i][1],CasasEmpeno[i][2],15.0);
    }
    return 1;
}
Ladron_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128];
    new tmp[128];
    new idx;
    cmd = strtokex(cmdtext, idx);


	if(strcmp(cmd, "/robar", true) == 0)
    {
		if(PlayerInfo[playerid][pTempFrozen] == 1) return 1;
	
		if(BuscandoObjetos[playerid] == 1) { SendClientMessage(playerid, Rojo, "* Ya estas robando!"); return 1; }
        if(PlayerInfo[playerid][pJob] != 11) { SendClientMessage(playerid, Rojo, "* Debes ser ladrón!"); return 1; }
        if (PlayerInfo[playerid][pMaterialTrabajo]  >= 20) { SendClientMessage(playerid, Rojo, "* Ya llevas demasiados objetos, véndelos antes!"); return 1; }
        
        if(gettime() < PlayerInfo[playerid][TiempoEsperaTrabajo])
        {
            format(string,sizeof(string),"* Tienes que esperar %d minutos para seguir trabajando.",(PlayerInfo[playerid][TiempoEsperaTrabajo]-gettime())/60);
            SendClientMessage(playerid,Naranja,string);
            return 1;
        }
        
        if (PlayerInfo[playerid][pTrabajando] == 1) { SendClientMessage(playerid, Rojo, "* Ya estás robando!"); return 1; }
        
        cmd = strtokex(cmdtext, idx);
        if (!strlen(cmd)) return 1;
        
        if (strcmp(cmd, "objetos", true) == 0)
        {
            new tipo, id;
            id = GetPlayerVehicle(playerid);
            if (id!=NOEXISTE)
            {
                tipo = 1; //robando coche
                if (PlayerHaveKeys(playerid, id)) { SendClientMessage(playerid, Rojo, "* No puedes robar de tu coche!"); return 1; }
                if (CarInfo[id][cOwned]!=1) { SendClientMessage(playerid, Rojo, "* No puedes robar de ese coche!"); return 1; }
                if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendClientMessage(playerid, Rojo, "* Tienes que ser el conductor"); return 1; }
                if (CarInfo[id][cRobado]>gettime()) { SendClientMessage(playerid, Rojo, "* Este coche acaba de sufrir un robo, busca otro"); return 1; }
                CarInfo[id][cRobado]=gettime()+TIEMPO_ESPERA_ROBO;

            }
            else if (PlayerInfo[playerid][pNegocio] > 0)
            {
                tipo=2; //robando negocio
                id=PlayerInfo[playerid][pNegocio];
                if (NegocioInfo[id][nRobado]>gettime()) { SendClientMessage(playerid, Rojo, "* Este negocio acaba de sufrir un robo, busca otro"); return 1; }
                NegocioInfo[id][nRobado]=gettime()+TIEMPO_ESPERA_ROBO;

            }
            else if (PlayerInfo[playerid][pHot] > 0)
            {
                new id2=NOEXISTE;
                tipo=3; //robando casa dentro de hotel
                id=PlayerInfo[playerid][pHot];
                for(new h;h<TotalCasas;h++)
                {
                    if (PlayerToPoint(100.0, playerid,CasaInfo[h][hSx],CasaInfo[h][hSy],CasaInfo[h][hSz]) 
                        && GetPlayerVirtualWorld(playerid)==CasaInfo[h][hId])
                        {
                            if (GetPlayerHouse(playerid)==h) { SendClientMessage(playerid, Rojo, "* No puedes robar de tu casa!"); return 1; }
                            id2=h;
                            if (CasaInfo[id2][hRobado]>gettime()) { SendClientMessage(playerid, Rojo, "* Esta casa acaba de sufrir un robo, busca otra"); return 1; }
                            CasaInfo[id2][hRobado]=gettime()+TIEMPO_ESPERA_ROBO;
                            break;
                        }
                }
                if (id2==NOEXISTE) { SendClientMessage(playerid, Rojo, "* Tienes que estar dentro de una habitacion!"); return 1; }
            }
            else
            {
                for(new h;h<TotalCasas;h++)
                {
                    if (PlayerToPoint(100.0, playerid,CasaInfo[h][hSx],CasaInfo[h][hSy],CasaInfo[h][hSz]) 
                        && GetPlayerVirtualWorld(playerid)==CasaInfo[h][hId])
                        {
                            if (GetPlayerHouse(playerid)==h) { SendClientMessage(playerid, Rojo, "* No puedes robar de tu casa!"); return 1; }
                            id=h;
                            tipo=4; //robando casa
                            if (CasaInfo[id][hRobado]>gettime()) { SendClientMessage(playerid, Rojo, "* Esta casa acaba de sufrir un robo, busca otra"); return 1; }
                            CasaInfo[id][hRobado]=gettime()+TIEMPO_ESPERA_ROBO;
                            break;
                        }
                }
            }
            if (id==NOEXISTE || tipo==0) { SendClientMessage(playerid,Rojo,"* Tienes que estar dentro de un coche, un negocio o una casa."); return 1; }
            PlayerInfo[playerid][pTempFrozen]=1;
			TogglePlayerControllable(playerid, 0);
            if (tipo>1)
            {           
                ClearAnimations(playerid);
                ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,0,0,1);
            }
            PlayerInfo[playerid][pTrabajando] = 1;
            GameTextForPlayer(playerid,"~r~Buscando objetos de valor",15000,5);
			BuscandoObjetos[playerid] = 1;
            
            new ZoneName[128];
            GetPlayer2DZone(playerid, ZoneName, 128);
            if (tipo==1)
            {
                format(string,sizeof(string),"[AVISO]: Un coche esta siendo robado en %s",ZoneName);
            }
            else if (tipo==2)
            {
                format(string,sizeof(string),"[AVISO]: Se está cometiendo un atraco en %s. Usa /avisos", NegocioInfo[id][nName]);
            }
            else if (tipo==3)
            {
                format(string,sizeof(string),"[AVISO]: Se esta cometiendo un robo en un hotel en %s. Usa /avisos", ZoneName);
            }
            else if (tipo==4)
            {
                format(string,sizeof(string),"[AVISO]: Se esta cometiendo un robo en una casa en %s. Usa /avisos", ZoneName);
            }
            else return 1;
            SendFamilyMessageOnDuty(1, Naranja, string);
			SendFamilyMessageOnDuty(6, Naranja, string);
			
			SetTimerEx("Timer_Robar", 25000, 0, "d", playerid);
			
            if (tipo>1)
            {
                for ( new i= (sizeof(InformesRobos)-1) ; i>0 ; i-- )
                {
                    InformesRobos[i][infTipo]=InformesRobos[i-1][infTipo];
                    InformesRobos[i][infId]=InformesRobos[i-1][infId];
                    InformesRobos[i][infH]=InformesRobos[i-1][infH];
                    InformesRobos[i][infM]=InformesRobos[i-1][infM];
                    InformesRobos[i][infS]=InformesRobos[i-1][infS];
                    InformesRobos[i][infExiste]=InformesRobos[i-1][infExiste];
                }
                InformesRobos[0][infTipo]=tipo;
                InformesRobos[0][infId]=id;
                gettime(InformesRobos[0][infH],InformesRobos[0][infM],InformesRobos[0][infS]);
                InformesRobos[0][infExiste]=1;
            }
            return 1;
        }
        
        if(strcmp(cmd, "radio", true) == 0)
        {
            if(PlayerInfo[playerid][pJob] != 11) { SendClientMessage(playerid, Rojo, "* Debes ser ladrón!"); return 1; }
            if(PlayerInfo[playerid][pHabilidadLadron] < 30) { SendClientMessage(playerid, Rojo, "* No tienes la habilidad suficiente para hacer eso."); return 1; }
            new id=GetPlayerVehicle(playerid);
            if (id!=NOEXISTE)
            {
                if (PlayerHaveKeys(playerid, id)) { SendClientMessage(playerid, Rojo, "* No puedes robar de tu coche!"); return 1; }
                if(CarInfo[id][cEquipo]==0) { SendClientMessage(playerid, Rojo, "* Este coche no tiene radio!"); return 1; }
                if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendClientMessage(playerid, Rojo, "* Tienes que ser el conductor"); return 1; }
                if (CarInfo[id][cRobado]>gettime()) { SendClientMessage(playerid, Rojo, "* Este coche acaba de sufrir un robo, busca otro"); return 1; }
                CarInfo[id][cRobado]=gettime()+TIEMPO_ESPERA_ROBO;

                TogglePlayerControllable(playerid, 0);
                PlayerInfo[playerid][pTempFrozen]=1;
                PlayerInfo[playerid][pTrabajando] = 1;
                GameTextForPlayer(playerid,"~r~Robando el equipo de música",25000,5);
                SetTimerEx("Timer_Robar_Radio", 25000, 0, "dd", playerid,id);
                new ZoneName[128];
                GetPlayer2DZone(playerid, ZoneName, 128);
                format(string,sizeof(string),"[AVISO]: Un coche esta siendo robado en %s", ZoneName);
                SendFamilyMessageOnDuty(1, Naranja, string);
				SendFamilyMessageOnDuty(6, Naranja, string);
                return 1;
            }
            SendClientMessage(playerid, Rojo, "* Tienes que estar en un coche!");
			return 1;
        }    

        return 1;
    }    

    if(strcmp(cmd, "/avisos", true) == 0)
    {
        if(PlayerInfo[playerid][pMember] != 1) { SendClientMessage(playerid, Rojo, "* No eres policía!"); return 1; }
        SendClientMessage(playerid, Amarillo, "|___________AVISOS DE ROBO____________|");
        for (new i=0 ; i<sizeof(InformesRobos) ; i++)
        {
            if (!InformesRobos[i][infExiste]) break;
            if (InformesRobos[i][infTipo]==2)
            {
                format(string,sizeof(string),"%d. (%02d:%02d:%02d)  Atraco en %s",i+1,InformesRobos[i][infH],InformesRobos[i][infM],InformesRobos[i][infS],NegocioInfo[InformesRobos[i][infId]][nName]);
            }
            else if (InformesRobos[i][infTipo]==3)
            {
                format(string,sizeof(string),"%d. (%02d:%02d:%02d)  Robo en hotel",i+1,InformesRobos[i][infH],InformesRobos[i][infM],InformesRobos[i][infS]);
            }
            else if (InformesRobos[i][infTipo]==4)
            {
                format(string,sizeof(string),"%d. (%02d:%02d:%02d)  Robo en vivienda",i+1,InformesRobos[i][infH],InformesRobos[i][infM],InformesRobos[i][infS]);
            }
            SendClientMessage(playerid, Verde, string);
        }
        SendClientMessage(playerid, Amarillo, "Usa /atenderaviso [id]");
        return 1;
    }    
               
    else if(strcmp(cmd,"/atenderaviso", true) == 0 || strcmp(cmd,"/aa", true) == 0)
    {
        if(PlayerInfo[playerid][pMember] != 1) { SendClientMessage(playerid, Rojo, "* No eres policía!"); return 1; }
        tmp = strtokex(cmdtext, idx);
        if(!strlen(tmp))
        {
            return SendClientMessage(playerid, Blanco, "USO: /atenderaviso [id]");
        }
        new i=strval(tmp)-1;
        if(i<0 || i>=sizeof(InformesRobos))
        {
            SendClientMessage(playerid, Blanco, "USO: /atenderaviso [id]"); return 1;
        }
        if (!InformesRobos[i][infExiste])
        {
            SendClientMessage(playerid, Blanco, "USO: /atenderaviso [id]"); return 1;
        }
        
        new id = InformesRobos[i][infId];
        if (InformesRobos[i][infTipo]==2)
        {
            SendClientMessage(playerid,Verde,"* La posicion del negocio ha sido marcada");
            SetPlayerCheckpoint(playerid,NegocioInfo[id][nEPos_x],NegocioInfo[id][nEPos_y],NegocioInfo[id][nEPos_z],8.0);
        }
        if (InformesRobos[i][infTipo]==3)
        {
            SendClientMessage(playerid,Verde,"* La posicion del hotel ha sido marcada");
            SetPlayerCheckpoint(playerid,InteriorInfo[id][itX], InteriorInfo[id][itY], InteriorInfo[id][itZ],8.0);
        }
        else if (InformesRobos[i][infTipo]==4)
        {
            if (CasaInfo[id][hInterior2]==0)
            {
                SendClientMessage(playerid,Verde,"* La posicion de la vivienda ha sido marcada");
                SetPlayerCheckpoint(playerid,CasaInfo[id][hEx],CasaInfo[id][hEy],CasaInfo[id][hEz],8.0);
            }
        }
        PlayerInfo[playerid][pCheckpoint]=11;
        PlayerInfo[playerid][pTrabajandoCP]=0;
        return 1;
    }
    
    if(strcmp(cmd, "/puente", true) == 0)
    {
        if(PlayerInfo[playerid][pJob] != 11) { SendClientMessage(playerid, Rojo, "* Debes ser ladrón!"); return 1; }
        if(PlayerInfo[playerid][pHabilidadLadron] < 50) { SendClientMessage(playerid, Rojo, "* No tienes la habilidad suficiente para hacer eso."); return 1; }
        new id=GetPlayerVehicle(playerid);
        if (id!=NOEXISTE)
        {
            if (PlayerHaveKeys(playerid, id)) { SendClientMessage(playerid, Rojo, "* No puedes robar tu coche!"); return 1; }
            if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendClientMessage(playerid, Rojo, "* Tienes que ser el conductor"); return 1; }
            if(CarInfo[id][cStarted]==1) { SendClientMessage(playerid, Rojo, "* Este coche ya está arrancado!"); return 1; }
			if(CarInfo[id][cBroken] == 1) { SendClientMessage(playerid, Rojo, "* El vehiculo está destrozado!"); return 1; }
			if(CarInfo[id][cGas] == 0) { SendClientMessage(playerid, Rojo, "* El vehiculo no tiene gasolina!"); return 1; }
			if(CarInfo[id][cSubWoofer] == 1) { SendClientMessage(playerid, Rojo, "* Desactiva el subwoofer primero!"); return 1; }
            if (PlayerInfo[playerid][pAlicates]==0) { SendClientMessage(playerid, Rojo, "* Necesitas unos alicates."); return 1; }
            if (CarInfo[id][cRobado]>gettime()) { SendClientMessage(playerid, Rojo, "* Este coche acaba de sufrir un robo, busca otro"); return 1; }
            CarInfo[id][cRobado]=gettime()+TIEMPO_ESPERA_ROBO;

            TogglePlayerControllable(playerid, 0);
            PlayerInfo[playerid][pTempFrozen]=1;
            GameTextForPlayer(playerid,"~r~Haciendo el puente",25000,5);
			
			new engine,lights,alarm,doors,bonnet,boot,objective;
			GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
			SetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,1,doors,bonnet,boot,objective);
			
            SetTimerEx("Timer_Puente", 25000, 0, "dd", playerid,id);
            new ZoneName[128];
            GetPlayer2DZone(playerid, ZoneName, 128);
            format(string,sizeof(string),"[AVISO]: Un coche esta siendo robado en %s", ZoneName);
            SendFamilyMessageOnDuty(1, Naranja, string);
			SendFamilyMessageOnDuty(6, Naranja, string);
            return 1;
        }
        SendClientMessage(playerid, Rojo, "* Tienes que estar en un coche!");
		return 1;
    }    

    
    if(strcmp(cmd, "/forzar", true) == 0)
	{
	    if(PlayerInfo[playerid][pJob] != 11 && PlayerInfo[playerid][pMember] != 1) { SendClientMessage(playerid, Rojo, "* Debes ser ladrón o policía!"); return 1; }
	    if(PlayerInfo[playerid][pHabilidadLadron] < 30 && PlayerInfo[playerid][pMember] != 1) { SendClientMessage(playerid, Rojo, "* No tienes la habilidad suficiente para hacer eso."); return 1; }
        
        new id = vehiculomascercano(playerid);
        if (CheckPlayerDistanceToVehicle(3.0, playerid, CarInfo[id][cId]))
        {
            //robando coche
            if (PlayerHaveKeys(playerid, id)) { SendClientMessage(playerid, Rojo, "* No puedes forzar tu coche!"); return 1; }
            if(CarInfo[id][cLock] == 1)
            {
                if (PlayerInfo[playerid][pPalanca]==0 && PlayerInfo[playerid][pMember] != 1) { SendClientMessage(playerid, Rojo, "* Necesitas una palanca."); return 1; }
                ClearAnimations(playerid);
                TogglePlayerControllable(playerid, 0);
                PlayerInfo[playerid][pTempFrozen]=1;
                ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",2.0,1,0,0,0,0,1);
                SetPlayerAttachedObject( playerid, TOOLS_SLOT, 18634, 6, 0.076347, 0.016477, 0.029525, 88.697738, 275.000000, 355.814025, 1.000000, 1.000000, 1.000000 );
                GameTextForPlayer(playerid,"~r~Forzando la cerradura",15000,5);
                SetTimerEx("Timer_Forzar_Coche", 15000, 0, "dd", playerid,id);
                return 1;
            }
            if(CarInfo[id][cLock] == 0)
            {
                SendClientMessage(playerid, Rojo, "* Este coche ya está abierto.");
                return 1;
            }
            
        }
        
        for(new i = 0; i < sizeof(CasaInfo); i++)
        {
            if (PlayerToPoint(3.0, playerid,CasaInfo[i][hEx], CasaInfo[i][hEy], CasaInfo[i][hEz]) && CasaInfo[i][hVw] == GetPlayerVirtualWorld(playerid) )
            {
                if(GetPlayerHouse(playerid) != i)
                {
                    if(CasaInfo[i][hLock] == 1)
                    {
                        if (PlayerInfo[playerid][pGanzua]==0 && PlayerInfo[playerid][pMember] != 1) { SendClientMessage(playerid, Rojo, "* Necesitas una ganzua."); return 1; }
                        ClearAnimations(playerid);
                        TogglePlayerControllable(playerid, 0);
                        PlayerInfo[playerid][pTempFrozen]=1;
                        ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",2.0,1,0,0,0,0,1);
                        SetPlayerAttachedObject( playerid, TOOLS_SLOT, 18644, 6, 0.079923, 0.016667, 0.000000, 0.000000, 180.000000, 0.000000, 1.000000, 1.000000, 1.000000 );                        GameTextForPlayer(playerid,"~r~Forzando la cerradura",15000,5);
                        SetTimerEx("Timer_Forzar", 15000, 0, "dd", playerid,CasaInfo[i][hId]);
                        return 1;
                    }
                    if(CasaInfo[i][hLock] == 0)
                    {
                        SendClientMessage(playerid, Rojo, "* Esta puerta ya estaba desbloqueada.");
                        return 1;
                    }
                }
                else
                {
                    SendClientMessage(playerid, Rojo, "* Ya tienes la llave de este lugar!");
                    return 1;
                }
            }
        }
	    return 1;
	} 

    
    
    if(strcmp(cmd, "/empeñar", true) == 0)
	{
		if(IsPlayerInAnyVehicle(playerid)) return 1;
	    if(PlayerInfo[playerid][pJob] != 11) { SendClientMessage(playerid, Rojo, "* Debes ser ladrón!"); return 1; }
		new id = 0;
        for (new i; i<sizeof(CasasEmpeno);i++)
        {
            if (PlayerToPoint(5.0,playerid,CasasEmpeno[i][0],CasasEmpeno[i][1],CasasEmpeno[i][2]) ) { id = i; break;}
        }
		
		if(id == 0)
		{
			SendClientMessage(playerid, Rojo, "* No estas en ninguna casa de empeño.");
			return 1;
		}
		
        new objetos = PlayerInfo[playerid][pMaterialTrabajo];
        if ( objetos == 0)
            { SendClientMessage(playerid, Rojo, "* No tienes objetos para vender."); return 1; }
        PlayerInfo[playerid][pHabilidadLadron] += 1;
        SafeGivePlayerMoney(playerid, objetos * 30 );
        PlayerInfo[playerid][pGanancias]+= (objetos * 30);
        format(string,sizeof(string),"* Has vendido %d objetos a %d$", objetos, objetos * 30); 
        SendClientMessage(playerid, Verde, string);
        if (PlayerInfo[playerid][pGanancias]>=500) 
        {
            SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue trabajando dentro de 30 minutos.");
            PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1800);
            PlayerInfo[playerid][pGanancias]=0;
            SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
        }
        PlayerInfo[playerid][pMaterialTrabajo]=0;
        SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
		SaveValues(playerid,"Habilidades");
		SaveValues(playerid, "Inventario");
	    return 1;
	} 
    
    return 0;
}


forward Timer_Robar(playerid);
public Timer_Robar(playerid)
{
    PlayerInfo[playerid][pTrabajando] = 0;
    TogglePlayerControllable(playerid, 1);
    if (!IsPlayerInAnyVehicle(playerid)) ClearAnimations(playerid);
    PlayerInfo[playerid][pTempFrozen]=0;
    new objetos= random(10)+5;
    if ( (PlayerInfo[playerid][pMaterialTrabajo] + objetos) > 20)
        objetos = 20 - PlayerInfo[playerid][pMaterialTrabajo];
    PlayerInfo[playerid][pMaterialTrabajo] += objetos;
    format(string,sizeof(string),"* Has encontrado %d objetos, llevas %d en total.",objetos,PlayerInfo[playerid][pMaterialTrabajo]);
    SendClientMessage(playerid, Verde, string);
	BuscandoObjetos[playerid] = 0;
	SaveValues(playerid, "Inventario");
    return 1;
}

forward Timer_Robar_Radio(playerid,id);
public Timer_Robar_Radio(playerid,id)
{
    PlayerInfo[playerid][pTrabajando] = 0;
    TogglePlayerControllable(playerid, 1);
    PlayerInfo[playerid][pTempFrozen]=0;
    new objetos= 10;
    if ( (PlayerInfo[playerid][pMaterialTrabajo] + objetos) > 20)
        objetos = 20 - PlayerInfo[playerid][pMaterialTrabajo];
    PlayerInfo[playerid][pMaterialTrabajo] += objetos;
    CarInfo[id][cEquipo]=0;
    format(string,sizeof(string),"* Has robado la radio del coche.");
    SendClientMessage(playerid, Verde, string);
	SaveValues(playerid, "Inventario");
    return 1;
}

forward Timer_Puente(playerid,id);
public Timer_Puente(playerid,id)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,0,doors,bonnet,boot,objective);
    TogglePlayerControllable(playerid, 1);
    format(string,sizeof(string),"* Has conseguido arrancar el coche. Usa /llamar desguace para vender el coche");
    SendClientMessage(playerid, Verde, string);
    Start(playerid,id);
    PlayerInfo[playerid][pAlicates]--;
    if (PlayerInfo[playerid][pAlicates]==0) SendClientMessage(playerid, Rojo, "* Has roto los alicates en el proceso.");
    SaveValues(playerid, "Inventario");
    return 1;
}


forward Timer_Forzar(playerid,h);
public Timer_Forzar(playerid,h)
{
    ClearAnimations(playerid);
    RemovePlayerAttachedObject(playerid,TOOLS_SLOT);
    TogglePlayerControllable(playerid, 1);
    PlayerInfo[playerid][pTempFrozen]=0;
    new i=GetHouseFromId(h);
    CasaInfo[i][hLock] = 0;
    GameTextForPlayer(playerid, "~w~Puerta ~g~Desbloqueada", 5000, 6);
    PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
    PlayerInfo[playerid][pGanzua]--;
    if (PlayerInfo[playerid][pGanzua]==0) SendClientMessage(playerid, Rojo, "* Has roto la ganzua en el proceso.");
    SaveCasa(i);
    UpdateHouseLabel(i);
    SaveValues(playerid, "Inventario");
    return 1;
}

forward Timer_Forzar_Coche(playerid,id);
public Timer_Forzar_Coche(playerid,id)
{
    new engine, lights, alarm, doors, bonnet, boot, objective;
	ClearAnimations(playerid);
    RemovePlayerAttachedObject(playerid,TOOLS_SLOT);
    TogglePlayerControllable(playerid, 1);
    PlayerInfo[playerid][pTempFrozen]=0;
    CarInfo[id][cLock] = 0;
    GetVehicleParamsEx(CarInfo[id][cId], engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(CarInfo[id][cId], engine, lights, alarm , 0 , bonnet, boot, objective);
    SendClientMessage(playerid, Amarillo, "* Coche desbloqueado");
    PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
    PlayerInfo[playerid][pPalanca]--;
    if (PlayerInfo[playerid][pPalanca]==0) SendClientMessage(playerid, Rojo, "* Has roto la palanca en el proceso.");
    SaveValues(playerid, "Inventario");
    SaveCar(id);
    return 1;
}





Ladron_OnPlayerEnterCheckpoint(playerid)
{
    if (PlayerInfo[playerid][pCheckpoint] == 11)
	{
        DisablePlayerCheckpoint(playerid);
        if (PlayerInfo[playerid][pTrabajandoCP] == 1 && GetPlayerVehicle(playerid)!=-1)
        {
            new id=GetPlayerVehicle(playerid);
            new tipo;
            for (new i=0;i<sizeof(datacar);i++)
            {
                if (strcmp(CarInfo[id][cDescription],datacar[i][dcNombre],true)==0)
                {
                    tipo=datacar[i][dcConcesionario];
                    break;
                }
            }
            if (tipo==0) return 1;
            /* for(new parking; parking < MAX_PARKINGS; parking++)
            {
                if(ParkInfo[parking][paType] == 3)
                {
                    CarInfo[id][cParking] = ParkInfo[parking][paSQLID];
                    CarInfo[id][horas] = 1;
                    ParkInfo[parking][paTotal]++;
                    SaveParking(parking);
                    RepairVehicle(CarInfo[id][cId]);
                    SaveCar(id);
                    HideLLLCar(id);
                    break;
                }
            } */
			SetTimerEx("RespawnearCocheRobado", 3000, 0, "d", id);
			RemovePlayerFromVehicle(playerid);
            TogglePlayerControllable(playerid,1);
			
            new ganado=200+tipo*(random(40)+40);
            PlayerInfo[playerid][pHabilidadLadron] += 1;
            SafeGivePlayerMoney(playerid, ganado );
			SaveValues(playerid,"Habilidades");
            PlayerInfo[playerid][pGanancias]+= ganado;
            format(string,sizeof(string),"* Has vendido el coche por %d$", ganado); 
            SendClientMessage(playerid, Verde, string);
            if (PlayerInfo[playerid][pGanancias]>=500) 
            {
                SendClientMessage(playerid,Naranja,"* Estás cansado. Sigue trabajando dentro de 30 minutos.");
                PlayerInfo[playerid][TiempoEsperaTrabajo] = (gettime()+1800);
                PlayerInfo[playerid][pGanancias]=0;
                SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
            }
            SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
        }
		return 1;
    }
    return 0;
}

forward RespawnearCocheRobado(id);
public RespawnearCocheRobado(id)
{
	SetVehiclePos(CarInfo[id][cId], CarInfo[id][cLocationx], CarInfo[id][cLocationy], CarInfo[id][cLocationz]);
    SetVehicleZAngle(CarInfo[id][cId], CarInfo[id][cAngle]);
    CarInfo[id][cStarted]=0;
    CarInfo[id][cLock]=1;
    new engine,lights,alarm,doors,bonnet,boot,objective;
    GetVehicleParamsEx(CarInfo[id][cId],engine,lights,alarm,doors,bonnet,boot,objective);
    SetVehicleParamsEx(CarInfo[id][cId],CarInfo[id][cStarted],lights,alarm,CarInfo[id][cLock],bonnet,boot,objective);
	return 1;
}