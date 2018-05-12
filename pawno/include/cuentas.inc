#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <detective>
#include <taxis>

//---[INTRO]---
//where the player will spawn
#define player_x (1205.93)
#define player_y (-1742.93)
#define player_z (13.5928)
#define player_angle (34.8035)
//note: for a better effect, let the camera be a few meters away from the player
#define camera_x (1210.4447)
#define camera_y (-1734.0603)
#define camera_z (13.5776)
#define moving_speed 50 //ATTENTION; THESE ARE MILISECONDS
//------------

new Registrado[MAX_PLAYERS];

forward IsValid(playerid, campo[], cadena[]);
public IsValid(playerid, campo[], cadena[])
{
//	if(IsValidNPC(playerid)) return 1;
	new tmp[100];
	new row[60];
	format(tmp, 100, "SELECT %s FROM players WHERE Nombre = '%s' LIMIT 1", campo, pNameEx(playerid));
	mysql_query(tmp);
	mysql_store_result();
	mysql_fetch_row(row);
	
	if(strcmp(row, cadena, true) == 0)
	{
		return 1;
	}
	mysql_free_result();
	return 0;
}

forward ExisteCuenta(playerid);
public ExisteCuenta(playerid)
{
	new query[128];
	new escstr[MAX_PLAYER_NAME];
	mysql_real_escape_string(pNameEx(playerid), escstr);
	format(query, sizeof(query), "SELECT id FROM players WHERE LOWER(Nombre) = LOWER('%s') LIMIT 1", escstr);
	mysql_query(query);
	mysql_store_result();
	if (mysql_num_rows()==0)
	{
		mysql_free_result();
		return 0;
	}
	else
	{
		new strid[32];
		mysql_fetch_row(strid);
		new InTiD = strval(strid);
		mysql_free_result();
		return InTiD;
	}
}

Cuentas_OnPlayerRequestClass(playerid)
{
	if(/*!IsValidNPC(playerid) && */PlayerInfo[playerid][pJugando] == 0)
	{
		if(Registrado[playerid] == 0) { SendClientMessage(playerid, Amarillo, "Debes registrarte en http://oldschool.es/pcu para poder ingresar al servidor."); Kick(playerid); return 1;}
		format(string,sizeof(string),"\n  Bienvenido de vuelta %s!\n\n  Escribe la contraseña de tu cuenta:\n",pName(playerid));
		ShowPlayerDialog(playerid, 1001, DIALOG_STYLE_INPUT, ">> Iniciar sesión!", string, "Log-in", "Cancelar");
		return 0;
	}
	return 1;
}

Cuentas_OnPlayerConnect(playerid)
{
	LimpiarVariables(playerid);
	if(ExisteCuenta(playerid))
	{
		Registrado[playerid] = 1;
	}
	else
	{
		Registrado[playerid] = 0;
		SendClientMessage(playerid, Amarillo, "Debes registrarte en http://oldschool.es/pcu para poder ingresar al servidor."); 
		Kick(playerid);
	}
}

Cuentas_OnPlayerRequestSpawn(playerid)
{
	if(/*!IsValidNPC(playerid) && */PlayerInfo[playerid][pJugando] == 0)
	{
        return 0;
	}
	return 1;
}

LimpiarVariables(playerid)
{
		//Reseteo de variables: Primero reseteamos todo, luego cargamos...
    //---[GENERALES]---
	PlayerInfo[playerid][pLoteria]=-1;
	ResetearVariablesArmas(playerid);
	PlayerInfo[playerid][pMenu]=0;
    PlayerInfo[playerid][pAdminDuty]=0;
    PlayerInfo[playerid][pDuty]=0;
	PlayerInfo[playerid][pAdmin] = 0;
    PlayerInfo[playerid][pRespeto]=0;
	SetPlayerScore(playerid,0);
    PlayerInfo[playerid][pMember]=0;
    PlayerInfo[playerid][pRank]=0;
    PlayerInfo[playerid][pJob]=0;
    PlayerInfo[playerid][pBank]=0;
    PlayerInfo[playerid][pPnumber][0]=0;
    PlayerInfo[playerid][pPnumber][1]=0;
	PlayerInfo[playerid][pPTelEstado]=1;
    PlayerInfo[playerid][pHidePms]=0;
    PlayerInfo[playerid][pBigEars]=0;
	PlayerInfo[playerid][pBigAntena]=0;
    PlayerInfo[playerid][pPmEspera]=0;
    PlayerInfo[playerid][pUsandoTelefono]=0;
    PlayerInfo[playerid][pIncomingCall]=NOEXISTE;
    PlayerInfo[playerid][pTimerCall]=0;
    PlayerInfo[playerid][pFacturaTelefono]=0;
    PlayerInfo[playerid][pNotificaciones]=0;
    PlayerInfo[playerid][pAutoescCP]=0;
    PlayerInfo[playerid][pAutoescVeh]=NOEXISTE;
    PlayerInfo[playerid][pAutoescTimer]=0;
    PlayerInfo[playerid][EnClase]=0;
    PlayerInfo[playerid][PreguntaID]=0;
    PlayerInfo[playerid][pFacturaTelefono]=0;
    PlayerInfo[playerid][pFrecuencia]=0;
    PlayerInfo[playerid][pMiFrecuencia]=0;
    PlayerInfo[playerid][pWalkies]=0;
    PlayerInfo[playerid][pHerido]=0;
	//--[INVENTARIO]--
    PlayerInfo[playerid][pPhonebook]=0;
    PlayerInfo[playerid][pDado]=0;
    PlayerInfo[playerid][pEncendedor]=0;
    PlayerInfo[playerid][pCigarrillos]=0;
	PlayerInfo[playerid][pLataFuel]=0;
    PlayerInfo[playerid][SpecID]= INVALID_PLAYER_ID;
    PlayerInfo[playerid][SpecType]= ADMIN_SPEC_TYPE_NONE;
    PlayerInfo[playerid][pTut]=0;
    PlayerInfo[playerid][pHide]=0;
    PlayerInfo[playerid][pDudaid]=NOEXISTE;
    PlayerInfo[playerid][pReporting]=0;
    PlayerInfo[playerid][pMarcado]=0;
    PlayerInfo[playerid][pJailed]=0;
    PlayerInfo[playerid][pJailTime]=0;
    PlayerInfo[playerid][pMultaMoney]=0;
    PlayerInfo[playerid][pMultaID]=NOEXISTE;
    PlayerInfo[playerid][pFrozen]=0;
    PlayerInfo[playerid][pTempFrozen]=0;
	PlayerInfo[playerid][pFrozenTaser]=0;
    PlayerInfo[playerid][pCheckpoint]=0;
    PlayerInfo[playerid][pRefuerzos]=0;
    PlayerInfo[playerid][pAdvertencias]=0;
    PlayerInfo[playerid][pSonido]=0;
    PlayerInfo[playerid][pMoviendoNeg]=0;
    PlayerInfo[playerid][pEditingNeg]=0;
    PlayerInfo[playerid][pMoviendoCasa]=0;
    PlayerInfo[playerid][pEditingCasa]=0;
    PlayerInfo[playerid][pMoviendoParking]=NOEXISTE;
    PlayerInfo[playerid][pLastCar]=NOEXISTE;
    PlayerInfo[playerid][pOfertaCocheID]=NOEXISTE;
    PlayerInfo[playerid][pOfertaCocheKey]=NOEXISTE;
    PlayerInfo[playerid][pOfertaCocheMoney]=0;
	KillTimer(PlayerInfo[playerid][pConsumoTimer]);
    //---[VARIABLES DE LOS TRABAJOS]---
	// -[GLOBALES]-
    PlayerInfo[playerid][pTrabajando]=0;
    PlayerInfo[playerid][pOferta]=0;
    PlayerInfo[playerid][pRutaDeTrabajo]=0;
    PlayerInfo[playerid][pTrabajandoCP]=0;
    PlayerInfo[playerid][pListoCobro]=0;
    PlayerInfo[playerid][pEquipoParaTrabajar]=0;
    PlayerInfo[playerid][pMaterialTrabajo]=0;
    PlayerInfo[playerid][pTrabajoVeh]=NOEXISTE;
    KillTimer(PlayerInfo[playerid][pTrabajoTimer]);
    // -[DETECTIVE]-	
	OfertaContrato[playerid]=0;
	InvestigandoContrato[playerid]=0;
	EsperandoParaBuscar[playerid]=0;
    // -[BASURERO]-
    PlayerInfo[playerid][pBolsaBasura]=0;
    // -[MECANICOS]-
    PlayerInfo[playerid][pEligiendoColores]=0;
    PlayerInfo[playerid][pRepaintOffer]=NOEXISTE;
    PlayerInfo[playerid][pRepaintPrice]=0;
    PlayerInfo[playerid][pRepaintColor]=0;
    PlayerInfo[playerid][pRepaintColor2]=0;
    PlayerInfo[playerid][pRepairOffer]=NOEXISTE;
    PlayerInfo[playerid][pRepairPrice]=0;
    PlayerInfo[playerid][pRefillOffer]=NOEXISTE;
    PlayerInfo[playerid][pRefillPrice]=0;
	PlayerInfo[playerid][pRefillAmount]=0;
    PlayerInfo[playerid][pEstadoMecanico]=0;
	PlayerInfo[playerid][pClienteMecanico]=NOEXISTE;
    // -[PESCA]-
    PlayerInfo[playerid][pPuedePescar]=0;
    PlayerInfo[playerid][pHaTiradoAnzuelo]=0;
    PlayerInfo[playerid][pHaTiradoRedes]=0;
    PlayerInfo[playerid][pPuntosHabilidadGanados]=0;
    PlayerInfo[playerid][pPuntosHabilidadRestantes]=0;
    PlayerInfo[playerid][pNivelPescador]=0;
    PlayerInfo[playerid][pRedRota]=0;
	// -[AMBULANTE]-
	PlayerInfo[playerid][pOfertaHelado]=NOEXISTE;
	PlayerInfo[playerid][pOfertaPerrito]=NOEXISTE;
    // -[PIZZA]-
    PlayerInfo[playerid][pPizzas]=0;
    PlayerInfo[playerid][pHablandoPizza]=0;
	// -[SEGURO]-
	PlayerInfo[playerid][pOfreciendoS]=NOEXISTE;
	PlayerInfo[playerid][pOfreciendoV]=NOEXISTE;
	PlayerInfo[playerid][pOfreciendoC]=0;
	// -[COMIDAS]-
	PlayerInfo[playerid][pMoviendoCom] = NOEXISTE;
	PlayerInfo[playerid][pEditandoCom] = NOEXISTE;
	// -[TUTORIAL]-
	PlayerInfo[playerid][SpawnAngle] = 0.0;
	PlayerInfo[playerid][SpawnState] = true;
	// -[PAGOS]-
	PlayerInfo[playerid][pPagandole] = NOEXISTE;
	PlayerInfo[playerid][pPagandoDin] = 0;
	// -[TAXIS]-
	PlayerInfo[playerid][pEstadoTaxista]=0;
	PlayerInfo[playerid][pClienteTaxista]=NOEXISTE;
	Taxista[playerid][taestado] = 0;
	Taxista[playerid][tarifa] = 0;
	Taxista[playerid][ganancias] = 0;
	Transporte[playerid][trtime] = 0;
	Transporte[playerid][costo] = 0;
	Transporte[playerid][taxista] = 0;
	KillTimer(Transporte[playerid][timer]);
	// -[CHATS]-
	LocalOOC[playerid] = gettime();
	// -[LICARMAS]-
	PlayerInfo[playerid][pGunLic] = 0;
	PlayerInfo[playerid][pGunLicD] = 0;
	PlayerInfo[playerid][pGunLicM] = 0;
	PlayerInfo[playerid][pHablandoArmas]=0;
	// -[PREMIUM]-
	PlayerInfo[playerid][pPremiumTipo] = 0;
	PlayerInfo[playerid][pPremiumTime] = 0;
	PlayerInfo[playerid][pPTelEstado] = 1;
	// -[LOWRIDER]-
	PlayerInfo[playerid][pInContest] = false;
	PlayerInfo[playerid][pCurrentNote] = -1;
	PlayerInfo[playerid][pPointsEarned] = 0;
	PlayerInfo[playerid][pJustJoined] = false;
	// -[TEXT3D]-
	TextToggle[playerid] = 0;
	AudioTextToggle[playerid] = 0;	
	// -[TAXIS]-
	Transporte[playerid][trtime] = 0;
	Transporte[playerid][costo] = 0;
	Transporte[playerid][taxista] = NOEXISTE;
	KillTimer(Transporte[playerid][timer]);
	// -[SONIDOS]-
	PlayerInfo[playerid][pEfecto] = NOEXISTE;
	// -[GANGZONES]-
	BuildingGangZone[playerid] = false;
	GetPos[playerid] = false;
	// -[PAINTBALL]-
	HaMuertoJugando[playerid] = 0;
	juega_paintball[playerid] = 0;
	participa_paintball[playerid] = 0;
	equipop[playerid] = 0;
	KillTimer(killtimercuentaatras[playerid]);
	KillTimer(partidapaintterminada[playerid]);
}


forward Cuentas_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
public Cuentas_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 1001)
	{
		if(!response) { Kick(playerid); }
		if(IsValid(playerid, "Password", inputtext) && (strlen(inputtext) > 0))
		{
			OnPlayerLogin(playerid);
		}
		else
		{
			ShowPlayerDialog(playerid, 1001, DIALOG_STYLE_INPUT, ">>  Contraseña incorrecta!", "\n  Esa no es la contraseña!\n\n  Escribe la contraseña correcta, porfavor:\n", "Log-in", "Cancelar");
		}
	}
	return 1;
}

forward GetValueFromName(playerid, campo[]);
public GetValueFromName(playerid, campo[])
{
//	if(IsValidNPC(playerid)) return 0;
	new tmp[128];
	new row[60];
	format(tmp, 128, "SELECT %s FROM players WHERE Nombre = '%s' LIMIT 1", campo, pNameEx(playerid));
	mysql_query(tmp);
	mysql_store_result();
	mysql_fetch_row(row);
	new id;
	id = strval(row);
	mysql_free_result();
	return id;
}

forward GetValue(playerid, campo[]);
public GetValue(playerid, campo[])
{
//	if(IsValidNPC(playerid)) return 0;
	new tmp[128];
	new row[60];
	format(tmp, 128, "SELECT %s FROM players WHERE id = %d LIMIT 1", campo, PlayerInfo[playerid][pSQLID]);
	mysql_query(tmp);
	mysql_store_result();
	mysql_fetch_row(row);
	new id;
	id = strval(row);
	mysql_free_result();
	return id;
}

forward CargarCoordenadas(playerid);
public CargarCoordenadas(playerid)
{
//	if(IsValidNPC(playerid)) return 1;
	new tmp[128];
	new row[128];
	format(tmp, 128, "SELECT X, Y, Z, Angulo, Vida, Armor FROM players WHERE id = %d LIMIT 1", PlayerInfo[playerid][pSQLID]);
	mysql_query(tmp);
	mysql_store_result();
	mysql_fetch_row(row);
	
	split(row, arrCoords, '|');
	PlayerInfo[playerid][pPos_x] = floatstr(arrCoords[0]);
	PlayerInfo[playerid][pPos_y] = floatstr(arrCoords[1]);
	PlayerInfo[playerid][pPos_z] = floatstr(arrCoords[2]);
	PlayerInfo[playerid][pAngulo] = floatstr(arrCoords[3]);
	if(floatcmp(floatstr(arrCoords[4]),0.000) == 1)
	{
		SetPlayerHealth(playerid, floatstr(arrCoords[4]));
	}
	SetPlayerArmour(playerid, floatstr(arrCoords[5]));
	mysql_free_result();
	return 1;
}

forward OnPlayerLogout(playerid);
public OnPlayerLogout(playerid)
{
//	if(IsValidNPC(playerid)) return 1;
	if(PlayerInfo[playerid][pJugando] == 0) return 1;
	PlayerInfo[playerid][pJugando] = 0;
	SaveValue(playerid, "Jugando", 0);
	SaveValues(playerid, "Coches");
	SaveValues(playerid, "CochesPrestados");
	SaveValues(playerid,"Inventario");
    if (PlayerInfo[playerid][TiempoEsperaTrabajo] > gettime() )
        SaveValue(playerid, "TiempoEsperaTrabajo", PlayerInfo[playerid][TiempoEsperaTrabajo] - gettime() );
    else SaveValue(playerid, "TiempoEsperaTrabajo", 0 );
    SaveValue(playerid, "Ganancias",PlayerInfo[playerid][pGanancias] );
	SaveValue(playerid, "RutasCompletadas",PlayerInfo[playerid][pRutasCompletadas] );
	SaveValue(playerid, "Respeto",PlayerInfo[playerid][pRespeto]);
	SaveValue(playerid, "Hambre",PlayerInfo[playerid][pHambre]);
	SaveValue(playerid, "Banco",PlayerInfo[playerid][pBank]);
	SaveValues(playerid, "Payday");
	return 1;
}

forward OnPlayerLogin(playerid);
public OnPlayerLogin(playerid)
{
//	if(IsValidNPC(playerid)) return 1;

	//*-----------------------------------------------
	//Carga de variables del jugador, (ya hemos hecho limpieza en onplayerconnect)
	PlayerInfo[playerid][pSQLID] = GetValueFromName(playerid, "id");
	CargarCoordenadas(playerid);
	PlayerInfo[playerid][pRespeto] = GetValue(playerid, "Respeto");
	PlayerInfo[playerid][pAdmin] = GetValue(playerid, "AdminLevel");
	PlayerInfo[playerid][pBank] = GetValue(playerid, "Banco");
	PlayerInfo[playerid][pMember] = GetValue(playerid, "Faccion");
	PlayerInfo[playerid][pRank] = GetValue(playerid, "Rango");
	PlayerInfo[playerid][pJob] = GetValue(playerid, "Trabajo");
	PlayerInfo[playerid][pContrato] = GetValue(playerid, "Contrato");
	PlayerInfo[playerid][pInt] = GetValue(playerid, "Interior");
	PlayerInfo[playerid][pVw] = GetValue(playerid, "VirtualWorld");
	PlayerInfo[playerid][pNegocio] = GetValue(playerid, "PosNeg");
	PlayerInfo[playerid][pPhousekey] = GetValue(playerid, "Casa");
	PlayerInfo[playerid][pPbiskey] = GetValue(playerid, "Negocio");
    PlayerInfo[playerid][pSex] = GetValue(playerid, "sexo");
	PlayerInfo[playerid][pSkin] = GetValue(playerid, "Skin");
	PlayerInfo[playerid][pUniforme] = GetValue(playerid, "Uniforme");
	PlayerInfo[playerid][pDuty] = GetValue(playerid, "EnServicio");
	PlayerInfo[playerid][pHerido] = GetValue(playerid, "Herido");
	PlayerInfo[playerid][pHambre] = GetValue(playerid, "Hambre");
	PlayerInfo[playerid][pJugando] = 1; SaveValue(playerid, "Jugando", 1);
	PlayerInfo[playerid][pProductos] = GetValue(playerid, "Productos");
	PlayerInfo[playerid][pDocumentacion] = GetValue(playerid, "Documentacion");
	PlayerInfo[playerid][pSeguroMedico] = GetValue(playerid, "SeguroMedico");
//	PlayerInfo[playerid][pPnumber][0] = GetValue(playerid, "Telefono");
//	PlayerInfo[playerid][pPnumber][1] = GetValue(playerid, "Telefono2");
	PlayerInfo[playerid][pFrecuencia] = GetValue(playerid, "Frecuencia");
	PlayerInfo[playerid][pMiFrecuencia] = GetValue(playerid, "MiFrecuencia");
	PlayerInfo[playerid][pWalkies] = GetValue(playerid, "Walkies");
    PlayerInfo[playerid][TiempoEsperaTrabajo] = gettime() + GetValue(playerid, "TiempoEsperaTrabajo");
    PlayerInfo[playerid][pGanancias] = GetValue(playerid, "Ganancias");
    PlayerInfo[playerid][pRutasCompletadas] = GetValue(playerid, "RutasCompletadas");
    PlayerInfo[playerid][pAdvertencias] = GetValue(playerid, "Advertencias");
    PlayerInfo[playerid][pTut] = GetValue(playerid, "Tutorial");
    PlayerInfo[playerid][pSex] = GetValue(playerid, "Sexo");
    PlayerInfo[playerid][pAge] = GetValue(playerid, "Edad");
	PlayerInfo[playerid][pAbstinencia] = GetValue(playerid, "Abstinencia");
	PlayerInfo[playerid][pLoteria] = GetValue(playerid, "Loteria");
	PlayerInfo[playerid][pPremiumTipo] = GetValue(playerid, "Premium_Tipo");
	PlayerInfo[playerid][pPremiumTime] = GetValue(playerid, "Premium_Timestamp");
	GetValues(playerid, "Coches");
	GetValues(playerid, "CochesPrestados");
	GetValues(playerid, "Preparada");
	GetValues(playerid, "NoPreparada");
	GetValues(playerid, "Semillas");
	GetValues(playerid, "Parafernalia");
	GetValues(playerid, "Consumos");
	GetValues(playerid, "TmpConsumos");
	GetValues(playerid, "Habilidades");
	GetValues(playerid, "Licencias");
	GetValues(playerid, "Armas");
	GetValues(playerid, "Ammo");
	GetValues(playerid, "Inventario");
	GetValues(playerid, "Encarcelado");
	GetValues(playerid, "Telefonos");
	GetValues(playerid, "LArmas");
	GetValues(playerid, "Muebles");
	
	new Bloqueado = GetValue(playerid, "Bloqueado");
	if(Bloqueado == 1){ SendClientMessage(playerid,Naranja,"Esta cuenta está bloqueada, pasate por el foro para solucionarlo."); return Kick(playerid); }
	
	
	new Certificacion = GetValue(playerid, "Certificacion");
	if(Certificacion == 0){ SendClientMessage(playerid,Naranja,"Aún no has validado el email de tu cuenta, ni pasada la certificacón."); return Kick(playerid);}
	if(Certificacion == 3){ SendClientMessage(playerid,Naranja,"Aún no has terminado el proceso de certificación."); return Kick(playerid);}
	if(Certificacion == 2){ SendClientMessage(playerid,Naranja,"Has sido reeducado y aún no has pasado de nuevo el proceso de certificación."); return Kick(playerid);}
	SetPlayerScore(playerid, GetPlayerLevel(playerid));
	
	if(PlayerInfo[playerid][pPhousekey] == NOEXISTE)
	{
		PlayerInfo[playerid][pPos_x] = 1205.93;
		PlayerInfo[playerid][pPos_y] = -1742.93;
		PlayerInfo[playerid][pPos_z] = 13.5928;
		PlayerInfo[playerid][pVw] = 0;
		PlayerInfo[playerid][pInt] = 0;
		SendClientMessage(playerid,Amarillo, "* Búscate un lugar para dormir, o siempre apareceras aqui.");
	}
	
	if(PlayerInfo[playerid][pDuty] == 0)
	{
		SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], PlayerInfo[playerid][pAngulo], 0,0,0,0,0,0);
		
	}
	else
	{
		SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pUniforme], PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], PlayerInfo[playerid][pAngulo], 0,0,0,0,0,0);
	}
	TogglePlayerControllable(playerid,0);
	SetTimerEx("Descongelar", 2000, 0, "d", playerid);
	if(PlayerInfo[playerid][pHerido] == 1)
	{
		PlayerInfo[playerid][pTmpSpawnx] = PlayerInfo[playerid][pPos_x];
		PlayerInfo[playerid][pTmpSpawny] = PlayerInfo[playerid][pPos_y];
		PlayerInfo[playerid][pTmpSpawnz] = PlayerInfo[playerid][pPos_z];
	}
	SetPlayerInterior(playerid, PlayerInfo[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pVw]);
	SafeResetPlayerMoney(playerid);
	SafeGivePlayerMoney(playerid, GetValue(playerid, "Dinero"));
	if(PlayerInfo[playerid][pTut] == 1){ format(string, sizeof(string), "~w~Bienvenido ~n~~y~   %s", pName(playerid)); GameTextForPlayer(playerid, string, 5000, 1);}
	ComprobarBarrita(playerid);
	SpawnPlayer(playerid);
	
	new ip[16], year, month, day, fecha[16];
	GetPlayerIp(playerid, ip, 16);
	getdate(year, month, day);
	format(fecha, 16, "%d/%d/%d", day, month, year);
	format(string, 128, "INSERT INTO logins (time, ip, userid) VALUES ('%s', '%s', %d)",
		fecha,
		ip,
		PlayerInfo[playerid][pSQLID]);
	mysql_query(string);
	
	if(GetPlayerPremium(playerid) != 0)
	{
		new restante_segundos = PlayerInfo[playerid][pPremiumTime] - gettime();
		new restante_dias = ((restante_segundos /60) /60) /24;
        restante_segundos -= restante_dias*24*60*60;
		new restante_horas = (restante_segundos /60) /60;
        restante_segundos -= restante_horas*60*60;
		new restante_minutos = (restante_segundos /60);
		restante_segundos -= restante_minutos*60;
		format(string, 128, "PREMIUM: %s {FFFFFF} - {77c7ff}TIEMPO RESTANTE:{FFFFFF} %d días %d horas %d minutos %d segundos", Premium[GetPlayerPremium(playerid)], restante_dias, restante_horas, restante_minutos, restante_segundos); 
		SendClientMessage(playerid, AzulClaro, string);
		new restante;
		restante = (((PlayerInfo[playerid][pSeguroMedico] - gettime()) /60) /60) /24;
		if(restante <= 0)
		{
			if(PremiumValido(playerid, 2))
			{
				PlayerInfo[playerid][pSeguroMedico] = gettime() + (7 * 24 * 60 * 60);
				SaveValue(playerid, "SeguroMedico", PlayerInfo[playerid][pSeguroMedico]);
				SendClientMessage(playerid, Blanco, " * Tu seguro médico fue renovado por un semana más.");
			}
		}
		new dia, mes, ano;
		getdate(dia, mes, ano);
		if(mes > PlayerInfo[playerid][pGunLicM])
		{
			if(PremiumValido(playerid, 3))
			{
				if(mes != 12)
				{
					PlayerInfo[playerid][pGunLicM] = mes + 1;
					PlayerInfo[playerid][pGunLicD] = dia;
				}
				else
				{
					PlayerInfo[playerid][pGunLicM] = 1;
					PlayerInfo[playerid][pGunLicD] = dia;
				}
				SendClientMessage(playerid, Blanco, " * Tu licencia de armas fue renovada por un mes más.");
				SaveValues(playerid, "LArmas");
			}
		}
		else if(dia >= PlayerInfo[playerid][pGunLicD] && PlayerInfo[playerid][pGunLicM] == mes)
		{
			if(PremiumValido(playerid, 2))
			{
				if(mes != 12)
				{
					PlayerInfo[playerid][pGunLicM] = mes + 1;
					PlayerInfo[playerid][pGunLicD] = dia;
				}
				else
				{
					PlayerInfo[playerid][pGunLicM] = 1;
					PlayerInfo[playerid][pGunLicD] = dia;
				}
				SendClientMessage(playerid, Blanco, " * Tu licencia de armas fue renovada por un mes más.");
				SaveValues(playerid, "LArmas");
			}
		}
	}
	return 1;
}

forward RefreshPos(playerid);
public RefreshPos(playerid)
{	
//	if(IsValidNPC(playerid)) return 1;
	GetPlayerPos(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
	GetPlayerFacingAngle(playerid, PlayerInfo[playerid][pAngulo]);
	PlayerInfo[playerid][pInt] = GetPlayerInterior(playerid);
	PlayerInfo[playerid][pVw] = GetPlayerVirtualWorld(playerid);
	GetPlayerArmour(playerid, PlayerInfo[playerid][pArmor]);
	return 1;
}

Cuentas_OnPlayerSpawn(playerid)
{
	ActualizarArmas(playerid);
	if(PlayerInfo[playerid][pJailed] == 1)
	{
		SetPlayerInterior(playerid, 1);
		SetPlayerPosEx(playerid,2583.8286,-1325.6830,1047.9634);
	}
	if(PlayerInfo[playerid][pJailed] == 2)
	{
		SetPlayerInterior(playerid, 18);
		SetPlayerPosEx(playerid,-219.5259,1409.8380,27.7734);
	}
	if(PlayerInfo[playerid][pJailed] == 3)
	{
		SetPlayerInterior(playerid, 6);
		SetPlayerPosEx(playerid,264.6727,77.6543,1001.0391);
	}
	return 1;
}

forward SavePos(playerid);
public SavePos(playerid)
{
	new sql[150];
//	if(IsValidNPC(playerid)) return 0;
	if(PlayerInfo[playerid][pJugando] == 1) 
	{
		format(sql, 150, "UPDATE players SET Interior=%d,VirtualWorld=%d,X=%f,Y=%f,Z=%f,Angulo=%f,Armor=%f WHERE id=%d", 
			PlayerInfo[playerid][pInt], 
			PlayerInfo[playerid][pVw], 
			PlayerInfo[playerid][pPos_x], 
			PlayerInfo[playerid][pPos_y], 
			PlayerInfo[playerid][pPos_z], 
			PlayerInfo[playerid][pAngulo], 
			PlayerInfo[playerid][pArmor],
			PlayerInfo[playerid][pSQLID]);
		mysql_query(sql);
		OnPlayerLogout(playerid);
	}
	return 0;
}

forward GetValues(playerid, cadena[]);
public GetValues(playerid, cadena[])
{
//	if(IsValidNPC(playerid)) return 0;
	new row[128];
	format(string, 128, "SELECT %s FROM players WHERE id = %d", cadena, PlayerInfo[playerid][pSQLID]);
	mysql_query(string);
	mysql_store_result();
	mysql_fetch_row(row);
	split(row, arrCoords, ','); 

	if(strcmp(cadena, "Coches", true) == 0)
	{
		for(new i; i < MAX_PROPIOS; i++)
		{
			PlayerInfo[playerid][pPCarKey][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "CochesPrestados", true) == 0)
	{
		for(new i; i < MAX_PRESTADOS; i++)
		{
			PlayerInfo[playerid][pPCochePrestado][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "Preparada", true) == 0)
	{
		for(new i; i < 3; i++)
		{
			PlayerInfo[playerid][pDrogaP][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "NoPreparada", true) == 0)
	{
		for(new i; i < 2; i++)
		{
			PlayerInfo[playerid][pDrogaNP][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "Semillas", true) == 0)
	{
		for(new i; i < 2; i++)
		{
			PlayerInfo[playerid][pSemillas][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "Parafernalia", true) == 0)
	{
		for(new i; i < 2; i++)
		{
			PlayerInfo[playerid][pParafernalia][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "Consumos", true) == 0)
	{
		for(new i; i < 3; i++)
		{
			PlayerInfo[playerid][pConsumos][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "TmpConsumos", true) == 0)
	{
		for(new i; i < 3; i++)
		{
			PlayerInfo[playerid][pTmpConsumos][i] = strval(arrCoords[i]);
		}
	}
	else if(strcmp(cadena, "Habilidades", true) == 0)
	{
		PlayerInfo[playerid][pHabilidadMecanico] = strval(arrCoords[0]);
		PlayerInfo[playerid][pHabilidadPescador] = strval(arrCoords[1]);
		PlayerInfo[playerid][pHabilidadLadron] = strval(arrCoords[2]);
	}
	else if(strcmp(cadena, "Licencias", true) == 0)
	{
		PlayerInfo[playerid][pCarLic] = strval(arrCoords[0]);
		PlayerInfo[playerid][pCarLicPoints] = strval(arrCoords[1]);
		PlayerInfo[playerid][pBoatLic] = strval(arrCoords[2]);
		PlayerInfo[playerid][pFlyLic] = strval(arrCoords[3]);
	}
	else if(strcmp(cadena, "Armas", true) == 0)
	{
		for(new i; i < 13; i++)
		{
			AgregarArma(playerid, strval(arrCoords[i]));
		}
	}
	else if(strcmp(cadena, "Ammo", true) == 0)
	{
		for(new i; i < 13; i++)
		{
			AgregarAmmo(playerid, strval(arrCoords[i]), i);
		}
	}
	else if(strcmp(cadena, "Inventario", true) == 0)
	{
		PlayerInfo[playerid][pEncendedor] = strval(arrCoords[0]);
		PlayerInfo[playerid][pCigarrillos] = strval(arrCoords[1]);
		PlayerInfo[playerid][pDado] = strval(arrCoords[2]);
		PlayerInfo[playerid][pCartas] = strval(arrCoords[3]);
        PlayerInfo[playerid][pPalanca] = strval(arrCoords[4]);
        PlayerInfo[playerid][pGanzua] = strval(arrCoords[5]);
        PlayerInfo[playerid][pAlicates] = strval(arrCoords[6]);
		PlayerInfo[playerid][pGafas] = strval(arrCoords[7]);
		PlayerInfo[playerid][pCascos] = strval(arrCoords[8]);
		PlayerInfo[playerid][pMaterialTrabajo] = strval(arrCoords[9]);
		PlayerInfo[playerid][pBandana] = strval(arrCoords[10]);
	}
	else if(strcmp(cadena, "Encarcelado", true) == 0)
	{
		PlayerInfo[playerid][pJailed] = strval(arrCoords[0]);
		PlayerInfo[playerid][pJailTime] = strval(arrCoords[1]);
	}
	else if(strcmp(cadena, "Payday", true) == 0)
	{
		PlayerInfo[playerid][pHora] = strval(arrCoords[0]);
		PlayerInfo[playerid][pMinuto] = strval(arrCoords[1]);
	}
	else if(strcmp(cadena, "LArmas",true)==0)
	{
		PlayerInfo[playerid][pGunLic] = strval(arrCoords[0]);
		PlayerInfo[playerid][pGunLicD] = strval(arrCoords[1]);
		PlayerInfo[playerid][pGunLicM] = strval (arrCoords[2]);
	}
	else if(strcmp(cadena, "Telefonos",true)==0)
	{
		PlayerInfo[playerid][pPnumber][0] = strval(arrCoords[0]);
		PlayerInfo[playerid][pPnumber][1] = strval(arrCoords[1]);
	}
	else if(strcmp(cadena, "Muebles", true) == 0)
	{
		for(new i; i < MAX_MUEBLES_PER_PLAYER; i++)
		{
			PlayerInfo[playerid][pMuebles][i] = strval(arrCoords[i]);
		}
	}
	mysql_free_result();
	return 0;
}

forward SaveValue(playerid, cadena[], valor);
public SaveValue(playerid, cadena[], valor)
{
//	if(IsValidNPC(playerid)) return 0;
	format(string, 128, "UPDATE players SET %s=%d WHERE id = %d", cadena, valor, PlayerInfo[playerid][pSQLID]);
	mysql_query(string);
	return 0;
}

forward SaveValues(playerid, cadena[]);
public SaveValues(playerid, cadena[])
{
//	if(IsValidNPC(playerid)) return 0;
	new tmp[128];
	if(strcmp(cadena, "Coches", true) == 0)
	{
		format(tmp, 128, "%d", PlayerInfo[playerid][pPCarKey][0]);
		for(new i = 1; i < MAX_PROPIOS; i++)
		{
			format(string, 128, ",%d", PlayerInfo[playerid][pPCarKey][i]);
			strcat(tmp, string, 128);
		}
	}
	else if(strcmp(cadena, "CochesPrestados", true) == 0)
	{
		format(tmp, 128, "%d", PlayerInfo[playerid][pPCochePrestado][0]);
		for(new i = 1; i < MAX_PRESTADOS; i++)
		{
			format(string, 128, ",%d", PlayerInfo[playerid][pPCochePrestado][i]);
			strcat(tmp, string, 128);
		}
	}
	else if(strcmp(cadena, "Preparada", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d", PlayerInfo[playerid][pDrogaP][0], PlayerInfo[playerid][pDrogaP][1], PlayerInfo[playerid][pDrogaP][2]);
	}
	else if(strcmp(cadena, "NoPreparada", true) == 0)
	{
		format(tmp, 128, "%d,%d", PlayerInfo[playerid][pDrogaNP][0], PlayerInfo[playerid][pDrogaNP][1]);
	}
	else if(strcmp(cadena, "Semillas", true) == 0)
	{
		format(tmp, 128, "%d,%d", PlayerInfo[playerid][pSemillas][0], PlayerInfo[playerid][pSemillas][1]);
	}
	else if(strcmp(cadena, "Parafernalia", true) == 0)
	{
		format(tmp, 128, "%d,%d", PlayerInfo[playerid][pParafernalia][0], PlayerInfo[playerid][pParafernalia][1]);
	}
	else if(strcmp(cadena, "Consumos", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d", PlayerInfo[playerid][pConsumos][0], PlayerInfo[playerid][pConsumos][1], PlayerInfo[playerid][pConsumos][2]);
	}
	else if(strcmp(cadena, "TmpConsumos", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d", PlayerInfo[playerid][pTmpConsumos][0], PlayerInfo[playerid][pTmpConsumos][1], PlayerInfo[playerid][pTmpConsumos][2]);
	}
	else if(strcmp(cadena, "Habilidades", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d",PlayerInfo[playerid][pHabilidadMecanico],  PlayerInfo[playerid][pHabilidadPescador], PlayerInfo[playerid][pHabilidadLadron]);
	}
	else if(strcmp(cadena, "Licencias", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d,%d", PlayerInfo[playerid][pCarLic], PlayerInfo[playerid][pCarLicPoints], PlayerInfo[playerid][pBoatLic], PlayerInfo[playerid][pFlyLic]);
	}
	else if(strcmp(cadena, "Armas", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			ScriptWeapons[playerid][0],
			ScriptWeapons[playerid][1],
			ScriptWeapons[playerid][2],
			ScriptWeapons[playerid][3],
			ScriptWeapons[playerid][4],
			ScriptWeapons[playerid][5],
			ScriptWeapons[playerid][6],
			ScriptWeapons[playerid][7],
			ScriptWeapons[playerid][8],
			ScriptWeapons[playerid][9],
			ScriptWeapons[playerid][10],
			ScriptWeapons[playerid][11],
			ScriptWeapons[playerid][12]);
	}
	else if(strcmp(cadena, "Ammo", true) == 0)
	{
		format(tmp, 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			ScriptAmmo[playerid][0],
			ScriptAmmo[playerid][1],
			ScriptAmmo[playerid][2],
			ScriptAmmo[playerid][3],
			ScriptAmmo[playerid][4],
			ScriptAmmo[playerid][5],
			ScriptAmmo[playerid][6],
			ScriptAmmo[playerid][7],
			ScriptAmmo[playerid][8],
			ScriptAmmo[playerid][9],
			ScriptAmmo[playerid][10],
			ScriptAmmo[playerid][11],
			ScriptAmmo[playerid][12]);
	}
	else if(strcmp(cadena, "Inventario", true) == 0)
	{
		if(PlayerInfo[playerid][pJob] == 11 || PlayerInfo[playerid][pJob] == 2 || PlayerInfo[playerid][pJob] == 3)
		{
			format(tmp, 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,0,%d",
				PlayerInfo[playerid][pEncendedor],
				PlayerInfo[playerid][pCigarrillos],
				PlayerInfo[playerid][pDado],
				PlayerInfo[playerid][pCartas],
				PlayerInfo[playerid][pPalanca],
				PlayerInfo[playerid][pGanzua],
				PlayerInfo[playerid][pAlicates],
				PlayerInfo[playerid][pGafas],
				PlayerInfo[playerid][pCascos],
				PlayerInfo[playerid][pBandana]);
		}
		else
		{
			format(tmp, 128, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				PlayerInfo[playerid][pEncendedor],
				PlayerInfo[playerid][pCigarrillos],
				PlayerInfo[playerid][pDado],
				PlayerInfo[playerid][pCartas],
				PlayerInfo[playerid][pPalanca],
				PlayerInfo[playerid][pGanzua],
				PlayerInfo[playerid][pAlicates],
				PlayerInfo[playerid][pGafas],
				PlayerInfo[playerid][pCascos],
				PlayerInfo[playerid][pMaterialTrabajo],
				PlayerInfo[playerid][pBandana]);
		}
	}
	else if(strcmp(cadena, "Encarcelado", true) == 0)
	{
		format(tmp, 128, "%d,%d",	PlayerInfo[playerid][pJailed], PlayerInfo[playerid][pJailTime]);
	}
	else if(strcmp(cadena, "Payday", true) == 0)
	{
		new hora, minuto, segundo;
		gettime(hora, minuto, segundo);
		format(tmp, 128, "%d,%d",hora, PlayerInfo[playerid][pMinuto]); 
	}
	else if(strcmp(cadena, "Telefonos", true) == 0)
	{
		format(tmp, 128, "%d,%d",PlayerInfo[playerid][pPnumber][0],PlayerInfo[playerid][pPnumber][1]); 
	}
	else if(strcmp(cadena, "LArmas", true) ==0 )
	{
		format(tmp, 128, "%d,%d,%d",PlayerInfo[playerid][pGunLic], PlayerInfo[playerid][pGunLicD], PlayerInfo[playerid][pGunLicM]);
	}
	else if(strcmp(cadena, "Muebles", true) == 0)
	{
		format(tmp, 128, "%d", PlayerInfo[playerid][pMuebles][0]);
		for(new i = 1; i < MAX_MUEBLES_PER_PLAYER; i++)
		{
			format(string, 128, ",%d", PlayerInfo[playerid][pMuebles][i]);
			strcat(tmp, string, 128);
		}
	}
	new sql[256];
	format(sql, 256, "UPDATE players SET %s = '%s' WHERE id = %d", cadena, tmp, PlayerInfo[playerid][pSQLID]);
	mysql_query(sql);
	return 0;
}

forward MoverCamera(playerid);
public MoverCamera(playerid)
{
    SetPlayerPos(playerid, player_x,player_y,player_z);
    SetPlayerFacingAngle(playerid, player_angle);
    SetPlayerCameraPos(playerid, camera_x,camera_y,camera_z);
    SetPlayerCameraLookAt(playerid, player_x,player_y,player_z);
    if (PlayerInfo[playerid][SpawnState]) PlayerInfo[playerid][SpawnTimer] = SetTimerEx("MoveCamera", moving_speed, true, "i", playerid);
    PlayerInfo[playerid][SpawnState] = false; //preventing the timer to execute again
	SetTimerEx("ColocarPosJugador",7100,0,"d",playerid);
	return 1;
}

forward ColocarPosJugador(playerid);
public ColocarPosJugador(playerid)
{
	TogglePlayerControllable(playerid,1);
	PlayerInfo[playerid][SpawnAngle] = 0.0; //so when you leave and another player comes, the camera will start from start
	PlayerInfo[playerid][SpawnState] = true; //to not execute to much timers
    KillTimer( PlayerInfo[playerid][SpawnTimer] ); //to kill it, since its useless now
    SetCameraBehindPlayer(playerid); //to prevent some bugs
	format(string,sizeof(string),"Bienvenido a OldSchool RP, %s.", pName(playerid));
	SendClientMessage(playerid,Naranja,string);
	SendClientMessage(playerid,AmarilloClaro,"Acércate al puesto de perritos calientes si necesitas información.");
	return 1;
}

forward MoveCamera(playerid);
public MoveCamera(playerid)
{
    //this is called trigonometry. It makes the camera spin
    //you can experiment with this line. Just change the values 2, 10 and 3 to make different effects
	SetPlayerCameraPos(playerid, player_x + 5 * floatsin(-PlayerInfo[playerid][SpawnAngle], degrees), player_y + 8 * floatcos(-PlayerInfo[playerid][SpawnAngle], degrees), player_z + 3);
	SetPlayerCameraLookAt(playerid, player_x, player_y, player_z + 0.5);
 
    //changing the angle a little
	PlayerInfo[playerid][SpawnAngle] += 1.5;

	if (PlayerInfo[playerid][SpawnAngle] >= 360.0)
    PlayerInfo[playerid][SpawnAngle] = 0.0;
	return 1;
}