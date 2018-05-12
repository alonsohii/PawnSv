/* 
   Old School v2 "The future is here"
   - - - - - - - - - - - - - - - - - -
		DEATH GOP GORTHOL DESK
   - - - - - - - - - - - - - - - - - -
*/

#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>
// JOB ID -> 9
#define MAX_CONTRATOS 50

new OfertaContrato[MAX_PLAYERS], // ID del array de contratos :sherlock:
	InvestigandoContrato[MAX_PLAYERS], // ID del array de contratos una vez aceptado
	EsperandoParaBuscar[MAX_PLAYERS];

enum cDetails
{
	cState, // NOEXISTE - 1(PENDIENTE DE SER ACEPTADO) - 2(INVESTIGANDO)
	cInvestigarName[24],
	cInvestigarNameEx[24],
	cContratadorID,
	cContratadorName[24],
	cInvestigadorID,
}
new Contratos[MAX_CONTRATOS][cDetails];	


Detective_OnGameModeInit()
{
	for(new contratoid = 0; contratoid < MAX_CONTRATOS; contratoid++)
	{
	    Contratos[contratoid][cState] = NOEXISTE;
	}
	return 1;
}


Detective_OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[128], tmp[128], tmp2[128];
    new idx;
    cmd = strtokex(cmdtext, idx);
//-----------------------------------------------------------------------------------------------------------------------------	
	if(strcmp(cmd,"/contratar",true)==0)
	{
    	tmp  = strtokex(cmdtext, idx);
		tmp2 = strtokex(cmdtext, idx);
		if(!strlen(tmp) || !strlen(tmp2) || !IsNumeric(tmp) || !IsNumeric(tmp2)) {
		SendClientMessage(playerid, Blanco, "USO: /contratar [ID del detective (necesario estar cerca)] [ID de la persona a encontrar]");
		return 1; }
		new detectiveid = strval(tmp);
		new buscadoid = strval(tmp2);
		if(IsPlayerConnected(detectiveid) && detectiveid != INVALID_PLAYER_ID)
		{
			if(GetDistanceBetweenPlayers(playerid, detectiveid) < 5.0)
			{
				if(PlayerInfo[detectiveid][pJob] != 9) { SendClientMessage(playerid, Rojo, "* No es un detective!"); return 1; }
				if(playerid == detectiveid) { SendClientMessage(playerid, Rojo, "* No puedes contratarte a ti mismo!"); return 1; }
				if(buscadoid == detectiveid) { SendClientMessage(playerid, Rojo, "* El detective no puede buscarse asi mismo..."); return 1; }
				if(buscadoid == playerid) { SendClientMessage(playerid, Rojo, "* Para que quieres buscarte a ti mismo?..."); return 1; }
				if(InvestigandoContrato[detectiveid] != 0) { SendClientMessage(playerid, Rojo, "* Ese detective ya tiene un contrato!"); return 1; }
				if(OfertaContrato[detectiveid] != 0) { SendClientMessage(playerid, Rojo, "* Ese detective tiene un contrato pendiente!"); return 1; }
				if(IsPlayerConnected(buscadoid) && buscadoid != INVALID_PLAYER_ID)
				{
					format(string,sizeof(string),"* Has ofrecido un contrato a %s",pName(detectiveid));
					SendClientMessage(playerid,AzulClaro,string);
					format(string,sizeof(string),"* %s quiere contratar tus servicios. Usa /contrato (aceptar/rechazar).",pName(playerid));
					SendClientMessage(detectiveid,AzulClaro,string);
					
					for(new contratoid = 0; contratoid < MAX_CONTRATOS; contratoid++)
					{
						if(Contratos[contratoid][cState] == NOEXISTE)
						{
							Contratos[contratoid][cState] = 1;
							Contratos[contratoid][cContratadorID] = playerid;
							format(Contratos[contratoid][cInvestigarName], 24, "%s", pName(buscadoid));
							format(Contratos[contratoid][cInvestigarNameEx], 24, "%s", pNameEx(buscadoid));
							format(Contratos[contratoid][cContratadorName], 24, "%s", pName(playerid));
							OfertaContrato[detectiveid] = contratoid;
							return 1;
						}
					}
				}
				else { SendClientMessage(playerid,Rojo,"* Jugador a investigar no conectado!"); }
			}
			else { SendClientMessage(playerid, Rojo, "* Jugador no cercano!"); }
		}
		else { SendClientMessage(playerid,Rojo,"* Jugador no conectado!"); }
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------------------------	
	if(strcmp(cmd, "/contrato", true) == 0)
    {
        if(PlayerInfo[playerid][pJob] != 9) { SendClientMessage(playerid, Rojo, "* Debes ser detective!"); return 1; }

        cmd = strtokex(cmdtext, idx);
        
        if (strcmp(cmd, "aceptar", true) == 0)
        {
			if(OfertaContrato[playerid] > 0)
			{
				InvestigandoContrato[playerid] = OfertaContrato[playerid];
				Contratos[OfertaContrato[playerid]][cState] = 2;
				Contratos[OfertaContrato[playerid]][cInvestigadorID] = playerid;
				OfertaContrato[playerid] = 0;
				format(string,sizeof(string),"* Has aceptado el contrato de %s. Para más detalles, usa /contrato ver",Contratos[InvestigandoContrato[playerid]][cContratadorName]);
				SendClientMessage(playerid, Verde, string);
			}
			else { SendClientMessage(playerid, Rojo, "* No te han ofrecido un contrato!"); return 1; }
        }

        if (strcmp(cmd, "rechazar", true) == 0)
        {
			if(OfertaContrato[playerid] > 0)
			{
				format(string,sizeof(string),"* Has rechazado el contrato de %s", Contratos[OfertaContrato[playerid]][cContratadorName]);
				SendClientMessage(playerid, Amarillo, string);
				Contratos[OfertaContrato[playerid]][cState] = NOEXISTE;
				OfertaContrato[playerid] = 0;
			}
			else { SendClientMessage(playerid, Rojo, "* No te han ofrecido un contrato!"); return 1; }
        }
		
		if (strcmp(cmd, "dejar", true) == 0)
        {
			if(InvestigandoContrato[playerid] > 0)
			{
				format(string,sizeof(string),"* Has dejado de investigar a %s", Contratos[InvestigandoContrato[playerid]][cInvestigarName]);
				SendClientMessage(playerid, Amarillo, string);
				Contratos[InvestigandoContrato[playerid]][cState] = NOEXISTE;
				InvestigandoContrato[playerid] = 0;
			}
			else { SendClientMessage(playerid, Rojo, "* No tienes un contracto activo!"); return 1; }
        }
		
		if (strcmp(cmd, "ver", true) == 0)
        {
            if(InvestigandoContrato[playerid] > 0)
			{
				SendClientMessage(playerid, AzulClaro, "________| CONTRATO ACTUAL |________");
				format(string,sizeof(string),"Contratista: %s", Contratos[InvestigandoContrato[playerid]][cContratadorName]);
				SendClientMessage(playerid, Blanco, string);
				format(string,sizeof(string),"Investigando a: %s", Contratos[InvestigandoContrato[playerid]][cInvestigarName]);
				SendClientMessage(playerid, Blanco, string);
				SendClientMessage(playerid, AzulClaro, "");
				SendClientMessage(playerid, Blanco, "Usa /buscar para localizarlo. ");
				}
			else { SendClientMessage(playerid, Rojo, "* No tienes un contracto activo!"); return 1; }
        }
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------------------------	
	if(strcmp(cmd,"/buscar",true)==0)
	{
		if(PlayerInfo[playerid][pCheckpoint] > 0) { SendClientMessage(playerid, Rojo, "ERROR: Ya tienes un checkpoint activo."); return 1; }
        if(InvestigandoContrato[playerid] > 0)
		{
			// Falta hacer el check de si la id, sigue correspondiendo al jugador que se estaba investigando
			// Si la id != name, buscar la nueva id si esta conectado, ReturnUser(inside?)
			// Si ReturnUser dice que no, que no esta conectado el contrato pasa a ser cancelado.
			new BuscandoID = ReturnUser(Contratos[InvestigandoContrato[playerid]][cInvestigarNameEx]);
			if(IsPlayerConnected(BuscandoID) && BuscandoID != INVALID_PLAYER_ID)
			{
				if(EsperandoParaBuscar[playerid] == 0)
				{
					if(GetPlayerInterior(BuscandoID) == 0)
					{
						GetPlayerPos(BuscandoID, PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz]);
						format(string,sizeof(string),"* Fuentes de confianza indican que %s está en esta posición, sigue la pista.", Contratos[InvestigandoContrato[playerid]][cInvestigarName]);
						SendClientMessage(playerid, Verde, string);
						
						SetPlayerCheckpoint(playerid,PlayerInfo[playerid][pTmpSpawnx], PlayerInfo[playerid][pTmpSpawny], PlayerInfo[playerid][pTmpSpawnz], 6);
						PlayerInfo[playerid][pCheckpoint] = 9;
						SetTimerEx("QuitarCheckpointDetective",3000,0,"d",playerid);
					
						EsperandoParaBuscar[playerid] = 1;
						SetTimerEx("YaPuedeVolverABuscar",30000,0,"d",playerid);
					}
					else
					{
						format(string,sizeof(string),"* Parece ser que nadie le ha visto, debe estar escondido en algún inmueble.", Contratos[InvestigandoContrato[playerid]][cInvestigarName]);
						SendClientMessage(playerid, Amarillo, string);
					}
				}
				else { SendClientMessage(playerid, Naranja, "* Nadie le ha vuelto a ver, vuelve a intentarlo en 30 segundos"); return 1; }
			}
			else
			{
				SendClientMessage(playerid, Naranja, "* Hemos perdido la pista a ese tio... olvídalo. ((El jugador no está conectado))");
				SendClientMessage(playerid, Naranja, "* Espera a que vuelva a conectar, o deja el contrato. (/contrato dejar)");
				return 1;
			}
		}
		else { SendClientMessage(playerid, Rojo, "* No tienes un contracto activo!"); }
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------------------------	
	return 0;
}

Detective_OnPlayerDisconnect(playerid,reason)
{
	#pragma unused reason
	//Hacer un for en el que todos los contratos ofrecidos por el jugador
	//cuyo estado del contrato sea cState = 1, es decir pendiente, sean borrados, cState = NOEXISTE
	for(new x=0; x<MAX_CONTRATOS; x++){
	    if(Contratos[x][cState] == 1 && Contratos[x][cContratadorID] == playerid)
     	Contratos[x][cState] = NOEXISTE;
	    if(Contratos[x][cState] == 2 && Contratos[x][cInvestigadorID] == playerid)
     	Contratos[x][cState] = NOEXISTE;}
	return 1;
}


forward QuitarCheckpointDetective(playerid);
public QuitarCheckpointDetective(playerid)
{
	DisablePlayerCheckpoint(playerid);
	PlayerInfo[playerid][pCheckpoint] = 0;
	return 1;
}

forward YaPuedeVolverABuscar(playerid);
public YaPuedeVolverABuscar(playerid)
{
	EsperandoParaBuscar[playerid] = 0;
	return 1;
}

