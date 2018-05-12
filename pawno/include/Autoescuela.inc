/* 
   Old School v2 "The future is here"
   - - - - - - - - - - - - - - - - - -
		DEATH GOP GORTHOL DESK
   - - - - - - - - - - - - - - - - - -
*/

#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>
#include <coches>

#define COSTEFALLARTEORICOCOCHE 25 // -> DINERO QUE PIERDES AL FALLAR EL TEST TEORICO DE COCHE
#define COSTETEORICOCOCHE 300 // -> DINERO QUE CUESTA EL CARNET DE COCHE (PARTE TEORICA)
#define COSTEPRACTICOCOCHE 600  // -> DINERO QUE CUESTA EL CARNET DE COCHE (PARTE PRACTICA)
#define COSTENAVEGACION 6000  // -> DINERO QUE CUESTA LA LICENCIA DE NAVEGACION

#define AUTOESC 5000
/*
AUTOESC - MENU DE LICENCIAS
AUTOESC+1 - INTRODUCION CLASE TEORICA
AUTOESC+2 - TEMA 1
AUTOESC+3 - TEMA 2
AUTOESC+4 - TEMA 3
AUTOESC+5 - TEMA 4
AUTOESC+6 - TEMA 5
AUTOESC+7 - TEMA 6
AUTOESC+8 - TEMA 7
AUTOESC+9 - TEMA 8
AUTOESC+10 - FIN CLASE TEORICA
AUTOESC-1 - SALIR DEL EXAMEN
AUTOESC+11 - Pregunta 1a
AUTOESC+12 - Pregunta 1b
AUTOESC+13 - Pregunta 1c
AUTOESC+14 - Pregunta 2a
AUTOESC+15 - Pregunta 2b
AUTOESC+16 - Pregunta 2c
AUTOESC+17 - Pregunta 3a
AUTOESC+18 - Pregunta 3b
AUTOESC+19 - Pregunta 3c
AUTOESC+20 - Pregunta 4a
AUTOESC+21 - Pregunta 4b
AUTOESC+22 - Pregunta 4c
AUTOESC+23 - Pregunta 5a
AUTOESC+24 - Pregunta 5b
AUTOESC+25 - Pregunta 5c
*/

// Checkpoints Practico Coche
#define CPCOCHEAUTOESC 21 // Nº de cps del practico
new Float:ChecksPracticoCoche[21][3] = {
{1207.8629,-1487.7981,13.1977},
{1198.5718,-1439.8506,12.9993},
{1271.5221,-1408.0732,12.6763},
{1385.6802,-1408.9950,13.0392},
{1479.4430,-1443.4308,13.0371},
{1607.9470,-1399.7391,13.5847},
{1642.5599,-1304.9666,15.3140},
{1717.1388,-1233.6349,15.8960},
{1654.6605,-1158.0519,23.4509},
{1570.2112,-1086.3628,23.1484},
{1435.9391,-1031.2838,23.3105},
{1312.3289,-1035.9690,29.5683},
{1134.3394,-1036.5645,31.3580},
{1080.4027,-1096.3289,24.7314},
{1055.8900,-1165.7200,23.4708},
{1055.9668,-1273.6129,13.3750},
{1059.4119,-1428.6680,13.0219},
{1040.0933,-1523.4482,13.0266},
{1080.0498,-1574.7627,13.0343},
{1198.5524,-1557.3030,13.0383},
{1207.8629,-1487.7981,13.1977}
};

// Checkpoints Navegacion
#define CPNAVEGAUTOESC 17 // Nº de cps del practico
new Float:ChecksNavegacion[17][3] = {
{-343.5116,-339.7494,-0.2608},
{-940.7413,-302.2996,-0.2926},
{-885.0145,159.3876,-0.2558},
{-638.4843,330.9884,-0.4381},
{-18.2408,248.7810,-0.1871},
{546.4388,413.3510,-0.1769},
{1128.2461,619.5447,-0.3620},
{1562.5573,534.4667,-0.4088},
{2043.2057,467.3105,-0.1897},
{2052.2834,-65.0676,-0.2132},
{1641.9211,-12.7984,-0.2427},
{1231.3518,-157.1078,-0.2199},
{879.7170,-127.4195,-0.2708},
{590.2217,-235.2143,-0.1740},
{154.4320,-423.2866,-0.1876},
{-116.6476,-609.2410,-0.2414},
{-306.7156,-481.6946,-0.2450}
};

Autoesc_OnGameModeInit()
{
	CreateDynamic3DTextLabel("Profesor Jaden Rezabal", Verde, 1488.6595,1305.4219,1093.42, 8);
	CreateDynamic3DTextLabel("/autoescuela", Gris, 1488.6595,1305.4219,1093.32, 8);
	return 1;
}

Autoesc_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	if(PlayerInfo[playerid][pAutoescVeh] >= 0)
	{
		if(PlayerInfo[playerid][EnClase] == 2) ResetearCochePractico(PlayerInfo[playerid][pAutoescVeh]);
		if(PlayerInfo[playerid][EnClase] == 3) ResetearBarcoPractico(PlayerInfo[playerid][pAutoescVeh]);
	}
	if(PlayerInfo[playerid][EnClase] > 1)
 	{
		KillTimer(PlayerInfo[playerid][pAutoescTimer]);
	}
	return 1;
}

Autoesc_OnPlayerCommandText(playerid, cmdtext[])
{
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmdtext, "/debugpractico", true) == 0) // DEBUG
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return 0;
		SetPlayerPos(playerid,1206.8440,-1459.6036,13.3828);
		PlayerInfo[playerid][pCheckpoint] = 0;
		PlayerInfo[playerid][pAutoescCP] = 0;
		PlayerInfo[playerid][EnClase] = 0;
		PlayerInfo[playerid][pAutoescVeh] = -1;
		PlayerInfo[playerid][pPCocheTemporal] = -1;
		PlayerInfo[playerid][pCarLic] = 2;
		SaveValues(playerid,"Licencias");
		return 1;
	}
//---------------------------------------------------------------------------------------------------------------
	if(strcmp(cmdtext, "/autoescuela", true) == 0)
	{
		if(PlayerToPoint(8.0,playerid,1488.6595,1305.4219,1093.2964))
		{
			if(PlayerInfo[playerid][EnClase] < 1)
			{
				SendClientMessage(playerid,Blanco,"Jaden Rezabal dice: Bienvenido a la autoescuela! ¿En que puedo ayudarte?");
				MostrarDialogLicencias(playerid);
			}
			else { TogglePlayerControllable(playerid, 1), SendClientMessage(playerid, Rojo, "* Ya estás sacandote un carnet!"); }
		}
		else {  SendClientMessage(playerid, Rojo, "* No estas en la Autoescuela!"); }
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------
	if(strcmp(cmdtext, "/reintentar", true) == 0)
	{
		if(PlayerToPoint(8.0,playerid,-337.8818,-452.5030,3.2221) && PlayerInfo[playerid][EnClase] == 0 && PlayerInfo[playerid][pBoatLic] == 0)
		{
			if((SafeGetPlayerMoney(playerid) >= COSTENAVEGACION) && GetPlayerLevel(playerid) >= 3)
			{
				PlayerInfo[playerid][pCheckpoint] = 33;
				PlayerInfo[playerid][EnClase] = 3;
				ClearChatbox(playerid,2);
				SendClientMessage(playerid,Verde,"* Sube a un barco para reintentar el exámen!");
			}
			else 
			{
				TogglePlayerControllable(playerid, 1);
				format(string,sizeof(string),"* Necesitas %d y nivel 3 para sacarte la licencia de navegación!",COSTENAVEGACION);
				SendClientMessage(playerid, Naranja, string);
			}
		}
		return 1;
	}
//-----------------------------------------------------------------------------------------------------------
	return 0;
}

Autoesc_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
//---------------------------------[MENU LICENCIAS]----------------------------------------------------------
	if(dialogid == AUTOESC)
	{
        if(response == 0)
        {
            TogglePlayerControllable(playerid, 1);
            SendClientMessage(playerid,Blanco,"Jaden Rezabal dice: Vuelve cuando quieras sacarte algun carnet!");
        }
		if(response)
		{
			if(listitem == 0)
			{
			EmpezarTeoricoCoche(playerid);
			}
			if(listitem == 1)
			{
			EmpezarExamenBarco(playerid);
			}
			if(listitem == 2)
			{
			EmpezarTeoricoAvion(playerid);
			}
		}
		return 1;
	}
//---------------------------------[TEORICO COCHE]-------------------------------------------------------
	if(dialogid == AUTOESC+1) // INTRODUCCION
	{
        if(response == 0)
        {
            MostrarDialogLicencias(playerid);
            PlayerInfo[playerid][EnClase] = 0;
            PlayerInfo[playerid][PreguntaID] = 0;
        }
		if(response)
		{
			CursoTeoricoCoche1(playerid);
		}
		return 1;
	}

	if(dialogid == AUTOESC+2) // TEMA 1
	{
        if(response == 0)
        {
            CursoTeoricoIntroduccion(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche2(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+3) // TEMA 2
	{
        if(response == 0)
        {
            CursoTeoricoCoche1(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche3(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+4) // TEMA 3
	{
        if(response == 0)
        {
            CursoTeoricoCoche2(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche4(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+5) // TEMA 4
	{
        if(response == 0)
        {
            CursoTeoricoCoche3(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche5(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+6) // TEMA 5
	{
        if(response == 0)
        {
            CursoTeoricoCoche4(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche6(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+7) // TEMA 6
	{
        if(response == 0)
        {
            CursoTeoricoCoche5(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche7(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+8) // TEMA 7
	{
        if(response == 0)
        {
            CursoTeoricoCoche6(playerid);
        }
		if(response)
		{
			CursoTeoricoCoche8(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+9) // TEMA 8
	{
        if(response == 0)
        {
            CursoTeoricoCoche7(playerid);
        }
		if(response)
		{
			EmpezarTestTeoricoCoche(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+10) // FIN CLASE TEORICA
	{
        if(response == 0)
        {
            CursoTeoricoCoche8(playerid);
        }
		if(response)
		{
			TeoricoCochePregunta1(playerid);
		}
		return 1;
	}
	
	if(dialogid == AUTOESC-1) // SALIR DEL EXAMEN
	{
        if(response == 0)
        {
        	VolverAlExamen(playerid);
        }
		if(response)
		{
        	PlayerInfo[playerid][EnClase] = 0;
            PlayerInfo[playerid][PreguntaID] = 0;
            TogglePlayerControllable(playerid, 1);
            SendClientMessage(playerid,Blanco,"Jaden Rezabal dice: Vuelve cuando tengas los conocimientos mas claros!");
		}
		return 1;
	}

	if(dialogid == AUTOESC+11) // PREGUNTA 1a
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 2)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}

	if(dialogid == AUTOESC+12) // PREGUNTA 1b
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 1)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}

	if(dialogid == AUTOESC+13) // PREGUNTA 1c
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 2)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+14) // PREGUNTA 2a
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 2)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+15) // PREGUNTA 2b
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 3)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+16) // PREGUNTA 2c
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 3)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+17) // PREGUNTA 3a
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 2)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+18) // PREGUNTA 3b
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 2)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+19) // PREGUNTA 3c
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			if(strlen(inputtext) == 0 || !IsNumeric(inputtext)) return VolverAlExamen(playerid);
			if(strval(inputtext) == 4)
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}

	if(dialogid == AUTOESC+20) // PREGUNTA 4a
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			new tmp[128], idx;
			tmp = strtokex(inputtext,idx);
			if(!strlen(tmp)) return VolverAlExamen(playerid);
			if((strcmp("2/3", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("2/3")) || (strcmp("3/2", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("3/2")))
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+21) // PREGUNTA 4b
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			new tmp[128], idx;
			tmp = strtokex(inputtext,idx);
			if(!strlen(tmp)) return VolverAlExamen(playerid);
			if((strcmp("1/2", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("1/2")) || (strcmp("2/1", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("2/1")))
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+22) // PREGUNTA 4c
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			new tmp[128], idx;
			tmp = strtokex(inputtext,idx);
			if(!strlen(tmp)) return VolverAlExamen(playerid);
			if((strcmp("2/3", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("2/3")) || (strcmp("3/2", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("3/2")))
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+23) // PREGUNTA 5a
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			new tmp[128], idx;
			tmp = strtokex(inputtext,idx);
			if(!strlen(tmp)) return VolverAlExamen(playerid);
			if((strcmp("3/4", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("3/4")) || (strcmp("4/3", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("4/3")))
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+24) // PREGUNTA 5b
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			new tmp[128], idx;
			tmp = strtokex(inputtext,idx);
			if(!strlen(tmp)) return VolverAlExamen(playerid);
			if((strcmp("1/4", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("1/4")) || (strcmp("4/1", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("4/1")))
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
	
	if(dialogid == AUTOESC+25) // PREGUNTA 5c
	{
        if(response == 0)
        {
            SalirDelExamen(playerid);
        }
		if(response)
		{
			new tmp[128], idx;
			tmp = strtokex(inputtext,idx);
			if(!strlen(tmp)) return VolverAlExamen(playerid);
			if((strcmp("3/4", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("3/4")) || (strcmp("4/3", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("4/3")))
			{
				return RespuestaCorrecta(playerid);
			}
			else
			{
				return RespuestaIncorrecta(playerid);
			}
		}
		return 1;
	}
//------------------------------------------------------------------------------------------------------------
	return 0;
}
//-----------------------------------[INICIO - LICENCIA DE COCHE]----------------------------------
EmpezarTeoricoCoche(playerid)
{
	if(PlayerInfo[playerid][EnClase] > 0) return SendClientMessage(playerid, Naranja, "* Ya estás sacandote una licencia!");
   	if(PlayerInfo[playerid][pCarLic] != 1 || (PlayerInfo[playerid][pCarLic] == 1 && PlayerInfo[playerid][pCarLicPoints] == 0))
	{
		if(PlayerInfo[playerid][pCarLic] == 2)
		{
			if(SafeGetPlayerMoney(playerid) >= COSTEPRACTICOCOCHE)
			{
				TogglePlayerControllable(playerid, 1);
				PlayerInfo[playerid][EnClase] = 2;
				PlayerInfo[playerid][pAutoescTimer] = SetTimerEx("SuspenderPorNoMontarse", 120000, 0, "d", playerid);
				SendClientMessage(playerid, Blanco, "Jaden Rezabal dice: Veo que ya estas preparado para sacarte el práctico, vamos allá!");
				return SendClientMessage(playerid, AzulClaro,"(( Sal fuera, y montate en un coche de la Autoescuela para empezar el exámen ))");
			}
			else 
			{
				TogglePlayerControllable(playerid, 1);
				format(string,sizeof(string),"* Necesitas %d para sacarte la parte práctica!",COSTEPRACTICOCOCHE);
				return SendClientMessage(playerid, Naranja, string);
			}
		}
		else
		{
			if(SafeGetPlayerMoney(playerid) >= COSTETEORICOCOCHE)
			{
				PlayerInfo[playerid][EnClase] = 1;
				TogglePlayerControllable(playerid, 0);
				SetTimerEx("CursoTeoricoIntroduccion", 2300, 0, "d", playerid);
				return GameTextForPlayer(playerid, "~y~Presta atencion",2000,3);
			}
			else 
			{
				TogglePlayerControllable(playerid, 1);
				format(string,sizeof(string),"* Necesitas %d para sacarte la parte teórica!",COSTETEORICOCOCHE);
				return SendClientMessage(playerid, Naranja, string);
			}
		}
	}
	else return TogglePlayerControllable(playerid, 1), SendClientMessage(playerid, Rojo, "* Ya tienes el carnet de coche!");
}

RespuestaCorrecta(playerid)
{
    GameTextForPlayer(playerid, "~g~CORRECTO",1500,3);
    if(PlayerInfo[playerid][PreguntaID] == 1 || PlayerInfo[playerid][PreguntaID] == 2 || PlayerInfo[playerid][PreguntaID] == 3) return SetTimerEx("TeoricoCochePregunta2", 1700, 0, "d", playerid);
    if(PlayerInfo[playerid][PreguntaID] == 4 || PlayerInfo[playerid][PreguntaID] == 5 || PlayerInfo[playerid][PreguntaID] == 6) return SetTimerEx("TeoricoCochePregunta3", 1700, 0, "d", playerid);
    if(PlayerInfo[playerid][PreguntaID] == 7 || PlayerInfo[playerid][PreguntaID] == 8 || PlayerInfo[playerid][PreguntaID] == 9) return SetTimerEx("TeoricoCochePregunta4", 1700, 0, "d", playerid);
    if(PlayerInfo[playerid][PreguntaID] == 10 || PlayerInfo[playerid][PreguntaID] == 11 || PlayerInfo[playerid][PreguntaID] == 12) return SetTimerEx("TeoricoCochePregunta5", 1700, 0, "d", playerid);
    if(PlayerInfo[playerid][PreguntaID] == 13 || PlayerInfo[playerid][PreguntaID] == 14 || PlayerInfo[playerid][PreguntaID] == 15)return ExamenTeoricoCocheAprobado(playerid);
	return 1;
}

RespuestaIncorrecta(playerid)
{
    GameTextForPlayer(playerid, "~r~INCORRECTO",1500,3);
	SafeGivePlayerMoney(playerid, -COSTEFALLARTEORICOCOCHE);
    PlayerInfo[playerid][EnClase] = 0;
    PlayerInfo[playerid][PreguntaID] = 0;
   	TogglePlayerControllable(playerid, 1);
    SendClientMessage(playerid,Blanco,"Jaden Rezabal dice: Lo siento, has suspendido el examen. Estare por aqui, si quieres volver a intentarlo.");
	return 1;
}

ExamenTeoricoCocheAprobado(playerid)
{
	SafeGivePlayerMoney(playerid, -COSTETEORICOCOCHE);
    PlayerInfo[playerid][EnClase] = 0;
    PlayerInfo[playerid][PreguntaID] = 0;
	PlayerInfo[playerid][pCarLic] = 2;
	SaveValues(playerid, "Licencias");
    SendClientMessage(playerid,Blanco,"Jaden Rezabal dice: Enhorabuena has aprobado el examen teorico del carnet de conducir. Vuelve cuando quieras empezar el práctico.");
    TogglePlayerControllable(playerid, 1);
	return 1;
}

SalirDelExamen(playerid)
{
	ShowPlayerDialog(playerid, AUTOESC-1, DIALOG_STYLE_MSGBOX, ">> Salir del examen:", "¿Estas seguro de que quieres salir del examen?\n", "Si", "No");
}

VolverAlExamen(playerid)
{
	if(PlayerInfo[playerid][PreguntaID] == 1) return TeoricoCochePregunta1a(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 2) return TeoricoCochePregunta1b(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 3) return TeoricoCochePregunta1c(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 4) return TeoricoCochePregunta2a(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 5) return TeoricoCochePregunta2b(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 6) return TeoricoCochePregunta2c(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 7) return TeoricoCochePregunta3a(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 8) return TeoricoCochePregunta3b(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 9) return TeoricoCochePregunta3c(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 10) return TeoricoCochePregunta4a(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 11) return TeoricoCochePregunta4b(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 12) return TeoricoCochePregunta4c(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 13) return TeoricoCochePregunta5a(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 14) return TeoricoCochePregunta5b(playerid);
	else if(PlayerInfo[playerid][PreguntaID] == 15) return TeoricoCochePregunta5c(playerid);
	return 1;
}

MostrarDialogLicencias(playerid)
{
	TogglePlayerControllable(playerid, 0);
	ShowPlayerDialog(playerid, AUTOESC, DIALOG_STYLE_LIST, ">> Licencias disponibles:","Coche / Moto\nBarcos\nAviones", "Selecionar", "Salir");
}
forward CursoTeoricoIntroduccion(playerid);
public CursoTeoricoIntroduccion(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"Bienvenido a la autoescuela de Los Santos.\n\nSoy el profesor Jaden Rezabal y os voy a explicar resumidamente\nel temario necesario ");
	format(text2,sizeof(text2),"para aprobar el examen teórico de conducir.\nPrestar mucha atención ya que para algunos es vuestra primera vez,\ny tenemos muchos conceptos nuevos ");
	format(text3,sizeof(text3),"que aprender, bien vamos:\n\nOs deseo suerte chicos tras la explicación realizaremos el examen teórico.\n\nPagina web: www.Autoescuelaonline.info\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+1, DIALOG_STYLE_MSGBOX, ">> Introduccion:", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche1(playerid)
{
	new text1[165],text2[165],text3[165],textTotal[485];
	format(text1,sizeof(text1),"Alumnos, no me gustaría que cuando tengáis vuestro carnet y coche aparcarais\nmal, porque aparte de molestar podéis causar accidentes, asique tened en\ncuenta que");
	format(text2,sizeof(text2)," un estacionamiento correcto será aquel en el que nuestro\nvehículo este estacionado en lugares acondicionados para ese fin como\ngarajes, parking públicos etc.\n\n");
	format(text3,sizeof(text3),"Si estáis en necesidad de aparcar en una vía dejad el vehículo paralelo a la acera\nsin subirnos a esta ya que la acera es para las personas y no para los coches.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+2, DIALOG_STYLE_MSGBOX, ">> TEMA 1 - \"Comportamiento general\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche2(playerid)
{
	new text1[165],text2[165],text3[165],textTotal[485];
	format(text1,sizeof(text1),"Este tema es triste porque los accidentes de tráfico en la mayoría de los casos\npodrían haberse evitado. La clave para evitarlos es conocer los fac");
	format(text2,sizeof(text2),"tores de riesgo,\nespecialmente los que dependen del propio conductor, que aumentan la probabilidad\nde que un accidente llegue a producirse o de que res");
	format(text3,sizeof(text3),"ulte mas grave.\n\nIndependientemente de otros factores, en la mayoría de los casos el conductor\npodría haber actuado de otra manera que evitara el accidente.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+3, DIALOG_STYLE_MSGBOX, ">> TEMA 2 - \"Los accidentes de tráfico\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche3(playerid)
{
	new text1[165],text2[165],text3[165],textTotal[485];
	format(text1,sizeof(text1),"Cuando conduces debes adaptar tu velocidad a las condiciones cambiantes del trafico,\nde la vía, del vehículo o de tu estado (por ejemplo, si te encuentras");
	format(text2,sizeof(text2)," fatigado).\nLa velocidad adecuada está siempre por debajo de la velocidad máxima y por encima de la\nmínima, pero no es igual a ninguna de estas dos.\n\n");
	format(text3,sizeof(text3),"Circulando de esta manera podrás controlar tu vehículo ante cualquier obstáculo\no imprevisto que pueda surgir.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+4, DIALOG_STYLE_MSGBOX, ">> TEMA 3 - \"La velocidad adecuada en cada momento\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche4(playerid)
{
	new text1[165],text2[165],text3[165],textTotal[485];
	format(text1,sizeof(text1),"Los efectos del alcohol son mayores en los conductores con poca experiencia al volante,\nya que todavía no han automatizado los movimientos necesarios para ");
	format(text2,sizeof(text2),"conducir y que\nse aprenden con la practica.\n\nEsta es una de las razones por la que los conductores noveles tienen una tasa de\nalcoholemia menor ");
	format(text3,sizeof(text3),"circular con seguridad. Si aun conociendo sus efectos decides\nbeber utiliza formas alternativas para desplazarte ya que la única tasa de\nalcohol segura es 0,0.");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+5, DIALOG_STYLE_MSGBOX, ">> TEMA 4 - \"El alcohol\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche5(playerid)
{
	new text1[170],text2[170],text3[170],textTotal[510];
	format(text1,sizeof(text1),"Una de las drogas mas consumidas en esta ciudad es la cocaína con la que nuestro\ncomportamiento puede volverse mas agresivo con los demás conductores, pero\n");
	format(text2,sizeof(text2),"se sobrevaloran las propias capacidades al volante y aumenta el riesgo de accidentes.\nSe cometen mas infracciones de trafico y la conducción se vuelve mas peligrosa.\n\n");
	format(text3,sizeof(text3),"Bueno estos son algunos de sus efectos mas conocidos, yo como vuestro profesor que\nsoy no os recomiendo tomar cuando vas a conducir y mucho menos mezclar con alcohol.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+6, DIALOG_STYLE_MSGBOX, ">> TEMA 5 - \"Las drogas\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche6(playerid)
{
	new text1[125],text2[125],text3[125],textTotal[375];
	format(text1,sizeof(text1),"Es muy importante tener siempre presente al conducir que las conductas interferentes,\n");
	format(text2,sizeof(text2),"como fumar o hablar por el teléfono móvil pueden hacer más probable que aparezca una\n");
	format(text3,sizeof(text3),"distracción, suficiente como para no reaccionar a tiempo ante algún acontecimiento\nimportante en el trafico.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+7, DIALOG_STYLE_MSGBOX, ">> TEMA 6 - \"Distracciones al volante\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche7(playerid)
{
	new text1[165],text2[165],text3[165],textTotal[485];
	format(text1,sizeof(text1),"Como norma general ante un accidente de trafico aunque no dispongamos de\nconocimientos sobre primeros auxilios, podemos ser de gran ayuda siguiendo\n");
	format(text2,sizeof(text2),"una regla de actuación tan básica como la regla PAS (Proteger, Avisar, Socorrer)\ncon esta regla protegemos la zona, avisamos a emergencias y socorremos a las\n");
	format(text3,sizeof(text3),"victimas.\n\nSi cuando pasamos junto a un accidente ya están las autoridades ateniendo el\naccidente lo correcto es continuar la marcha para no molestar.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+8, DIALOG_STYLE_MSGBOX, ">> TEMA 7 - \"Accidentes y heridos\"", textTotal, "Siguiente", "Atras");
}
CursoTeoricoCoche8(playerid)
{
	new text1[165],text2[165],text3[165],text4[165],text5[165],textTotal[805];
	format(text1,sizeof(text1),"Como ya sabemos todos, los agentes de policía son los que mandan en la\ncarretera, estamos obligados a detenernos cuando un agente nos lo ordene\n");
	format(text2,sizeof(text2),"al igual que si estamos implicados en un accidente de circulación, no parar\nes un delito, al igual que si cometemos una infracción con nuestro vehículo\n");
	format(text3,sizeof(text3),"podremos ser sancionados económicamente y también perder puntos de\nnuestro carnet de conducir.\n\nLa perdida total de puntos supondrá que volváis a verme ");
	format(text4,sizeof(text4),"y volver a sacar\nde nuevo el carnet.\n\nRecordad que los vehículos prioritarios (Policía, ambulancias, etc.) tienen\nprioridad de paso sobre nosotros cuando ");
	format(text5,sizeof(text5),"circulen en servicio urgente,\ncuando tengan las luces o sirena encendidas o ambas al mismo tiempo\ntendremos que dejarles pasar.\n");
	format(textTotal,sizeof(textTotal),"%s%s%s%s%s",text1,text2,text3,text4,text5);
	ShowPlayerDialog(playerid, AUTOESC+9, DIALOG_STYLE_MSGBOX, ">> TEMA 8 - \"Agentes y vehículos prioritarios\"", textTotal, "Siguiente", "Atras");
}
EmpezarTestTeoricoCoche(playerid)
{
	new text1[170],text2[190],textTotal[360];
	format(text1,sizeof(text1),"El examen es tipo test y consta de 5 preguntas aleatorias. Cada vez que suspendas\nel examen perderas %d$. Asi que piensa bien las preguntas antes de contestarlas.\n\n", COSTEFALLARTEORICOCOCHE);
	format(text2,sizeof(text2),"* Para contestar las preguntas pon el numero de la respuesta.\n ** Ejemplo: 1\n\n* Para contestar las preguntas con doble respuesta se hace separandolas con una /\n** Ejemplo: 1/3\n\nSuerte!");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+10, DIALOG_STYLE_MSGBOX, ">> Fin de la clase teorica.", textTotal, "Siguiente", "Atras");
}
TeoricoCochePregunta1a(playerid)
{
	new text1[120];
	format(text1,sizeof(text1),"Cuando hablamos de accidentes de tráfico...\ntenemos claro que se debe al destino.\n\n1) Verdadero.\n2) Falso.\n");
	ShowPlayerDialog(playerid, AUTOESC+11, DIALOG_STYLE_INPUT, ">> Primera pregunta:", text1, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta1b(playerid)
{
	new text1[120];
	format(text1,sizeof(text1),"Gran parte de los accidentes de tráfico se\ndeben principalmente al factor humano.\n\n1) Verdadero.\n2) Falso.\n");
	ShowPlayerDialog(playerid, AUTOESC+12, DIALOG_STYLE_INPUT, ">> Primera pregunta:", text1, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta1c(playerid)
{
	new text1[120];
	format(text1,sizeof(text1),"La velocidad adecuada está siempre por encima\nde la velocidad máxima y de la mínima.\n\n1) Verdadero.\n2) Falso.\n");
	ShowPlayerDialog(playerid, AUTOESC+13, DIALOG_STYLE_INPUT, ">> Primera pregunta:", text1, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta2a(playerid)
{
	new text1[120],text2[120],textTotal[240];
	format(text1,sizeof(text1),"Los efectos del alcohol son mayores...\n\n1) en conductores veteranos.\n2) en los conductores con poca experiencia al");
	format(text2,sizeof(text2)," volante.\n3) en los conductores profesionales.\n4) en conductores experimentados.\n");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+14, DIALOG_STYLE_INPUT, ">> Segunda pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta2b(playerid)
{
	new text1[120],text2[120],textTotal[240];
	format(text1,sizeof(text1),"Un conductor bajo los efectos de la cocaína... \n\n1) aumenta su capacidad para mantener la concentracion.\n2) tiene");
	format(text2,sizeof(text2)," mayores reflejos.\n3) se vuelve más agresivo, cometiendo graves errores.\n4) aumenta su capacidad locomotora.\n");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+15, DIALOG_STYLE_INPUT, ">> Segunda pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta2c(playerid)
{
	new text1[150],text2[150],textTotal[300];
	format(text1,sizeof(text1),"Si tienes que conducir y no has evitado las bebidas alcoholicas... \n\n1) conduce, por una vez no va a pasar nada.\n2) toma");
	format(text2,sizeof(text2)," refrescos y comida esto reducira los efectos del alcohol.\n3) utiliza formas alternativas para desplazarte.\n4) no hay riesgo de accidente.\n");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+16, DIALOG_STYLE_INPUT, ">> Segunda pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta3a(playerid)
{
	new text1[150],text2[150],textTotal[300];
	format(text1,sizeof(text1),"Entre las conductas que más distraen en la conducción destacaríamos... \n\n1) conducir por una vía en buen estado.\n2) buscar el ");
	format(text2,sizeof(text2),"móvil cuando suena.\n3) atender las diferentes señáles de la vía.\n4) mirar el velocimetro.\n");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+17, DIALOG_STYLE_INPUT, ">> Tercera pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta3b(playerid)
{
	new text1[150],text2[150],textTotal[300];
	format(text1,sizeof(text1),"Durante la conducción, hablando por teléfono movil... \n\n1) resulta fácil mantener la velocidad adecuada.\n2) se cometen más infracciones.");
	format(text2,sizeof(text2),"\n3) no existen problemas en la percepción de las señales.\n4) la conducción es mas segura.\n");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+18, DIALOG_STYLE_INPUT, ">> Tercera pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta3c(playerid)
{
	new text1[150],text2[150],textTotal[300];
	format(text1,sizeof(text1),"Fumar conduciendo implica... \n\n1) una mayor atención del conductor al entorno.\n2) una mayor eficacia en los movimientos realizados.");
	format(text2,sizeof(text2),"\n3) asumir menos riesgos.\n4) una posible distracción al depositar la ceniza en el cenicero.\n");
	format(textTotal,sizeof(textTotal),"%s%s",text1,text2);
	ShowPlayerDialog(playerid, AUTOESC+19, DIALOG_STYLE_INPUT, ">> Tercera pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta4a(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"Se considera estacionamiento correcto... \n\n1) Estacionar sobre la acera completamente.\n2) En lugares acondicionados para este fin.");
	format(text2,sizeof(text2),"\n3) Dejando el vehículo paralelo a la acera sin invadirla.\n4) Colocando medio vehículo sobre la acera y medio en la calzada.\n\n");
	format(text3,sizeof(text3),"* Esta pregunta tiene doble respuesta! Usa: x/x pra responder\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+20, DIALOG_STYLE_INPUT, ">> Cuarta pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta4b(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"Usted esta obligado a detenerse... \n\n1) Cuando un agente de policía lo ordene.\n2) Cuando este envuelto en un accidente de circulación.");
	format(text2,sizeof(text2),"\n3) Si algún civil me hace el alto.\n4) Cuando vea algun letrero gracioso.\n\n");
	format(text3,sizeof(text3),"* Esta pregunta tiene doble respuesta! Usa: x/x pra responder\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+21, DIALOG_STYLE_INPUT, ">> Cuarta pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta4c(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"¿Como actuara usted ante un accidente de circulación? \n\n1) Continuare la marcha normalmente.\n2) Si las autoridades ya están en el lugar, ");
	format(text2,sizeof(text2),"continuare la marcha.\n3) Protegiendo la zona, avisando al número de emergencias y socorriendo a los heridos.\n4) Dar bebidas alcohólicas");
	format(text3,sizeof(text3)," para estimular a los heridos.\n\n* Esta pregunta tiene doble respuesta! Usa: x/x pra responder\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+22, DIALOG_STYLE_INPUT, ">> Cuarta pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta5a(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"Si circulando con su turismo se aproxima una ambulancia,\n¿Debería facilitarle el paso apartandose o deteniéndose si es preciso? \n\n1) ");
	format(text2,sizeof(text2),"Sí, siempre.\n2) Normalmente no, salvo que use el claxon.\n3) Sí, si va circulando en servicio urgente.\n4) Siempre que circule ");
	format(text3,sizeof(text3),"con la señal luminosa, acustica o ambas a la vez.\n\n* Esta pregunta tiene doble respuesta! Usa: x/x pra responder\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+23, DIALOG_STYLE_INPUT, ">> Quinta pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta5b(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"En una calzada de 4 carriles,\n¿Cuando esta permitido circular por el carril izquierdo? \n\n1) Con causa justificada.\n2) ");
	format(text2,sizeof(text2),"Siempre que uno quiera.\n3) No existen reglas sobre esto.\n4) Al rebasar a otro vehículo.");
	format(text3,sizeof(text3),"\n\n* Esta pregunta tiene doble respuesta! Usa: x/x pra responder\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+24, DIALOG_STYLE_INPUT, ">> Quinta pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta5c(playerid)
{
	new text1[150],text2[150],text3[150],textTotal[450];
	format(text1,sizeof(text1),"Si circulando con su turismo se aproxima una ambulancia,\n¿Debería facilitarle el paso apartandose o deteniéndose si es preciso? \n\n1) ");
	format(text2,sizeof(text2),"Sí, siempre.\n2) Normalmente no, salvo que use el claxon.\n3) Sí, si va circulando en servicio urgente.\n4) Siempre que circule ");
	format(text3,sizeof(text3),"con la señal luminosa, acustica o ambas a la vez.\n\n* Esta pregunta tiene doble respuesta! Usa: x/x pra responder\n");
	format(textTotal,sizeof(textTotal),"%s%s%s",text1,text2,text3);
	ShowPlayerDialog(playerid, AUTOESC+25, DIALOG_STYLE_INPUT, ">> Quinta pregunta:", textTotal, "Siguiente", "Salir");
	return 1;
}
TeoricoCochePregunta1(playerid)
{
	new posibilidad = random(75);
	if(posibilidad >= 50)
	{
	TeoricoCochePregunta1a(playerid);
	return PlayerInfo[playerid][PreguntaID] = 1;
	}
	if(posibilidad >= 25)
	{
	TeoricoCochePregunta1b(playerid);
	return PlayerInfo[playerid][PreguntaID] = 2;
	}
	if(posibilidad >= 0)
	{
	TeoricoCochePregunta1c(playerid);
	return PlayerInfo[playerid][PreguntaID] = 3;
	}
	return 1;
}
forward TeoricoCochePregunta2(playerid);
public TeoricoCochePregunta2(playerid)
{
	new posibilidad = random(75);
	if(posibilidad >= 50)
	{
	TeoricoCochePregunta2a(playerid);
	return PlayerInfo[playerid][PreguntaID] = 4;
	}
	if(posibilidad >= 25)
	{
	TeoricoCochePregunta2b(playerid);
	return PlayerInfo[playerid][PreguntaID] = 5;
	}
	if(posibilidad >= 0)
	{
	TeoricoCochePregunta2c(playerid);
	return PlayerInfo[playerid][PreguntaID] = 6;
	}
	return 1;
}
forward TeoricoCochePregunta3(playerid);
public TeoricoCochePregunta3(playerid)
{
	new posibilidad = random(75);
	if(posibilidad >= 50)
	{
	TeoricoCochePregunta3a(playerid);
	return PlayerInfo[playerid][PreguntaID] = 7;
	}
	if(posibilidad >= 25)
	{
	TeoricoCochePregunta3b(playerid);
	return PlayerInfo[playerid][PreguntaID] = 8;
	}
	if(posibilidad >= 0)
	{
	TeoricoCochePregunta3c(playerid);
	return PlayerInfo[playerid][PreguntaID] = 9;
	}
	return 1;
}
forward TeoricoCochePregunta4(playerid);
public TeoricoCochePregunta4(playerid)
{
	new posibilidad = random(75);
	if(posibilidad >= 50)
	{
	TeoricoCochePregunta4a(playerid);
	return PlayerInfo[playerid][PreguntaID] = 10;
	}
	if(posibilidad >= 25)
	{
	TeoricoCochePregunta4b(playerid);
	return PlayerInfo[playerid][PreguntaID] = 11;
	}
	if(posibilidad >= 0)
	{
	TeoricoCochePregunta4c(playerid);
	return PlayerInfo[playerid][PreguntaID] = 12;
	}
	return 1;
}
forward TeoricoCochePregunta5(playerid);
public TeoricoCochePregunta5(playerid)
{
	new posibilidad = random(75);
	if(posibilidad >= 50)
	{
	TeoricoCochePregunta5a(playerid);
	return PlayerInfo[playerid][PreguntaID] = 13;
	}
	if(posibilidad >= 25)
	{
	TeoricoCochePregunta5b(playerid);
	return PlayerInfo[playerid][PreguntaID] = 14;
	}
	if(posibilidad >= 0)
	{
	TeoricoCochePregunta5c(playerid);
	return PlayerInfo[playerid][PreguntaID] = 15;
	}
	return 1;
}
//-----------------------------------[FIN - LICENCIA DE COCHE]----------------------------------

//-----------------------------------[INICIO - PRACTICO COCHE]----------------------------------
forward EmpezarPracticoCoche(playerid);
public EmpezarPracticoCoche(playerid)
{
	KillTimer(PlayerInfo[playerid][pAutoescTimer]);
	SetPlayerCheckpoint(playerid,ChecksPracticoCoche[0][0],ChecksPracticoCoche[0][1],ChecksPracticoCoche[0][2],5);
	PlayerInfo[playerid][pCheckpoint] = 33;
	PlayerInfo[playerid][pAutoescCP] = 1;
	ClearChatbox(playerid,20);
    SendClientMessage(playerid,Verde,"* Arranca el coche (/encendermotor) y recorre la ruta por los checkpoints marcados. (Puntos rojos en el mapa)");
	ClearChatbox(playerid,1);
	SendClientMessage(playerid,Verde,"* Controla la velocidad, no superes los 80 km/h, y trae de vuelta el coche en perfectas condiciones. Suerte!");
	ClearChatbox(playerid,2);
	return 1;
}

ExamenPracticoCocheAprobado(playerid)
{
	DestroyDynamic3DTextLabel(PlayerInfo[playerid][pAutoescText3d]);
	GameTextForPlayer(playerid, "~g~APROBADO",3000,3);
	KillTimer(PlayerInfo[playerid][pAutoescTimer]);
	ResetearCochePractico(PlayerInfo[playerid][pAutoescVeh]);
	SafeGivePlayerMoney(playerid, -COSTEPRACTICOCOCHE);
	PlayerInfo[playerid][pCheckpoint] = 0;
	PlayerInfo[playerid][pAutoescCP] = 0;
	PlayerInfo[playerid][EnClase] = 0;
	PlayerInfo[playerid][pAutoescVeh] = -1;
	PlayerInfo[playerid][pPCocheTemporal] = -1;
	PlayerInfo[playerid][pCarLic] = 1;
	PlayerInfo[playerid][pCarLicPoints] = 10;
	SaveValues(playerid, "Licencias");
	PlayerInfo[playerid][pRespeto] = PlayerInfo[playerid][pRespeto]+3;
	SaveValue(playerid, "Respeto", PlayerInfo[playerid][pRespeto]);
	ClearChatbox(playerid,3);
    SendClientMessage(playerid,Verde,"* Enhorabuena! Has aprobado el exámen práctico del carnet de conducir!");
	SendClientMessage(playerid,Verde,"* Recibes 3 puntos de respeto, y 10 puntos en el carnet.");
	return 1;
}

 // 1 - No montarse en un coche despues de 2 minutos | 2 - Abandonar el coche
ExamenPracticoCocheSuspenso(playerid,reason) // 3 - Superar la velocidad maxima | 4 - Dañar el coche | 5 - Tardar mas de 2 minutos entre checkpoint y checkpoint
{
	DestroyDynamic3DTextLabel(PlayerInfo[playerid][pAutoescText3d]);
	KillTimer(PlayerInfo[playerid][pAutoescTimer]);
	if(PlayerInfo[playerid][pAutoescVeh] > 0) ResetearCochePractico(PlayerInfo[playerid][pAutoescVeh]);
	if(PlayerInfo[playerid][pCheckpoint] == 33) PlayerInfo[playerid][pCheckpoint] = 0,DisablePlayerCheckpoint(playerid);
	PlayerInfo[playerid][pAutoescCP] = 0;
	PlayerInfo[playerid][EnClase] = 0;
	PlayerInfo[playerid][pAutoescVeh] = -1;
	PlayerInfo[playerid][pPCocheTemporal] = -1;
	if(reason >= 3)
	{
		SetPlayerPos(playerid,1209.6854,-1478.7896,13.5469);
		SetPlayerFacingAngle(playerid,318.0978);
		SetCameraBehindPlayer(playerid);
		SetPlayerInterior(playerid,0);
		SetPlayerVirtualWorld(playerid,0);
	}
	if(reason == 1)	format(string,sizeof(string),"* Has suspendido el exámen, no has ido a montarte en el vehiculo.");
	if(reason == 2)	format(string,sizeof(string),"* Has suspendido el exámen, has abandonado el vehiculo.");
	if(reason == 3)	format(string,sizeof(string),"* Has suspendido el exámen, has superado la velocidad máxima.");
	if(reason == 4)	format(string,sizeof(string),"* Has suspendido el exámen, has dañado el vehiculo.");
	if(reason == 5)	format(string,sizeof(string),"* Has suspendido el exámen, has tardado demasiado tiempo en ir al siguiente punto.");
	ClearChatbox(playerid,2);
    return SendClientMessage(playerid,Rojo,string);
}

ResetearCochePractico(vehicleid)
{
	RepairVehicle(CarInfo[vehicleid][cId]);
	SetVehicleToRespawn(CarInfo[vehicleid][cId]);
	ChangeVehicleColor(CarInfo[vehicleid][cId],99,99);
	CarInfo[vehicleid][cColorOne] = 99;
	CarInfo[vehicleid][cLock] = 0;
	CarInfo[vehicleid][cBroken] = 0;
	CarInfo[vehicleid][cStarted] = 0;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[vehicleid][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(CarInfo[vehicleid][cId], CarInfo[vehicleid][cStarted], lights, alarm, doors, bonnet, boot, objective);
	CarInfo[vehicleid][cGas] = 100;
	// Falta resetear maleteros
	SaveCar(vehicleid);
	return 1;
}

forward SuspenderPorNoMontarse(playerid);
public SuspenderPorNoMontarse(playerid)
{
	return GameTextForPlayer(playerid, "~r~SUSPENSO",3000,3), ExamenPracticoCocheSuspenso(playerid,1);
}

forward SuspenderPorNoVolver(playerid);
public SuspenderPorNoVolver(playerid)
{
	return GameTextForPlayer(playerid, "~r~SUSPENSO",3000,3), ExamenPracticoCocheSuspenso(playerid,2);
}

forward SuspenderPorCorrer(playerid);
public SuspenderPorCorrer(playerid)
{
	return TogglePlayerControllable(playerid,1), ExamenPracticoCocheSuspenso(playerid,3);
}

forward SuspenderPorRomper(playerid);
public SuspenderPorRomper(playerid)
{
	TogglePlayerControllable(playerid,1), ExamenPracticoCocheSuspenso(playerid,4);
	return 1;
}

forward SuspenderPorTardar(playerid);
public SuspenderPorTardar(playerid)
{
	GameTextForPlayer(playerid, "~r~SUSPENSO",3000,3), ExamenPracticoCocheSuspenso(playerid,5);
	return 1;
}

forward SeguimosAutoescSCM(playerid);
public SeguimosAutoescSCM(playerid)
{
	return ClearChatbox(playerid,1),SendClientMessage(playerid,Verde,"* Continuemos con el exámen!");
}

forward EsteNoEsAutoescSCM(playerid);
public EsteNoEsAutoescSCM(playerid)
{
	return ClearChatbox(playerid,1),SendClientMessage(playerid,Rojo,"* Este no es el vehiculo con el que estabas haciendo el examen!");
}
//-----------------------------------[FIN - PRACTICO COCHE]-----------------------------------
//-----------------------------------[INICIO - LICENCIA NAVEGACION]----------------------------------
EmpezarExamenBarco(playerid)
{
	if(PlayerInfo[playerid][EnClase] > 0) return SendClientMessage(playerid, Naranja, "* Ya estás sacandote una licencia!");
   	if(PlayerInfo[playerid][pBoatLic] != 1)
	{
		if((SafeGetPlayerMoney(playerid) >= COSTENAVEGACION) && GetPlayerLevel(playerid) >= 3)
		{
			TogglePlayerControllable(playerid, 1);
			PlayerInfo[playerid][EnClase] = 3;
			PlayerInfo[playerid][pAutoescCP] = 0;
			PlayerInfo[playerid][pCheckpoint] = 33;
			SetPlayerCheckpoint(playerid,-338.0516,-456.1885,2.8698,3);
			SendClientMessage(playerid, Blanco,"Jaden Rezabal: Lo siento, aqui solo tramitamos el carnet de coche. Dirigete al embarcadero.");
			return SendClientMessage(playerid, AzulClaro,"(( Ve a la posición marcada en el mapa. ))");
		}
		else 
		{
			TogglePlayerControllable(playerid, 1);
			format(string,sizeof(string),"* Necesitas %d y nivel 3 para sacarte la licencia de navegación!",COSTENAVEGACION);
			return SendClientMessage(playerid, Naranja, string);
		}
	}
	else
	{
		TogglePlayerControllable(playerid, 1);
		SendClientMessage(playerid, Rojo, "* Ya tienes la licencia de navegación!");
	}
	return 1;
}

forward EmpezarPracticoNavegacion(playerid);
public EmpezarPracticoNavegacion(playerid)
{
	SetPlayerCheckpoint(playerid,ChecksNavegacion[0][0],ChecksNavegacion[0][1],ChecksNavegacion[0][2],8);
	PlayerInfo[playerid][pCheckpoint] = 33;
	PlayerInfo[playerid][pAutoescCP] = 1;
	ClearChatbox(playerid,2);
    SendClientMessage(playerid,Verde,"* Recorre la ruta por los checkpoints marcados y trae de vuelta el barco en perfectas condiciones.");
	return 1;
}

ResetearBarcoPractico(vehicleid)
{
	RepairVehicle(CarInfo[vehicleid][cId]);
	SetVehicleToRespawn(CarInfo[vehicleid][cId]);
	ChangeVehicleColor(CarInfo[vehicleid][cId],61,61);
	CarInfo[vehicleid][cColorOne] = 61;
	CarInfo[vehicleid][cLock] = 0;
	CarInfo[vehicleid][cBroken] = 0;
	CarInfo[vehicleid][cStarted] = 0;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(CarInfo[vehicleid][cId], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(CarInfo[vehicleid][cId], CarInfo[vehicleid][cStarted], lights, alarm, doors, bonnet, boot, objective);
	CarInfo[vehicleid][cGas] = 100;
	SaveCar(vehicleid);
	return 1;
}

ExamenBarcoAprobado(playerid)
{
	GameTextForPlayer(playerid, "~g~APROBADO",3000,3);
	KillTimer(PlayerInfo[playerid][pAutoescTimer]);
	ResetearBarcoPractico(PlayerInfo[playerid][pAutoescVeh]);
	SafeGivePlayerMoney(playerid, -COSTENAVEGACION);
	PlayerInfo[playerid][pCheckpoint] = 0;
	PlayerInfo[playerid][pAutoescCP] = 0;
	PlayerInfo[playerid][EnClase] = 0;
	PlayerInfo[playerid][pAutoescVeh] = -1;
	PlayerInfo[playerid][pPCocheTemporal] = -1;
	PlayerInfo[playerid][pBoatLic] = 1;
	SaveValues(playerid, "Licencias");
	ClearChatbox(playerid,3);
    SendClientMessage(playerid,Verde,"* Enhorabuena! Has obtenido la licencia de navegación!");
	return 1;
}

forward ExamenBarcoSuspenso(playerid,reason);
public ExamenBarcoSuspenso(playerid,reason) // 1 - Dañar el barco | 2 - Tardar mas de 2 minutos entre checkpoint y checkpoint
{
	KillTimer(PlayerInfo[playerid][pAutoescTimer]);
	if(PlayerInfo[playerid][pAutoescVeh] > 0) ResetearBarcoPractico(PlayerInfo[playerid][pAutoescVeh]);
	if(PlayerInfo[playerid][pCheckpoint] == 33) PlayerInfo[playerid][pCheckpoint] = 0,DisablePlayerCheckpoint(playerid);
	PlayerInfo[playerid][pAutoescCP] = 0;
	PlayerInfo[playerid][EnClase] = 0;
	PlayerInfo[playerid][pAutoescVeh] = -1;
	PlayerInfo[playerid][pPCocheTemporal] = -1;
	SetPlayerPos(playerid,-337.8818,-452.5030,3.2221);
	SetPlayerFacingAngle(playerid,226.9108);
	SetCameraBehindPlayer(playerid);
	SetPlayerInterior(playerid,0);
	SetPlayerVirtualWorld(playerid,0);
	TogglePlayerControllable(playerid,1);
	ClearChatbox(playerid,2);
	if(reason == 1)	format(string,sizeof(string),"* Has suspendido el exámen, has tardado demasiado tiempo en ir al siguiente punto.");
	if(reason == 2)	format(string,sizeof(string),"* Has suspendido el exámen, has dañado el barco.");
	SendClientMessage(playerid,Amarillo,string);
	ClearChatbox(playerid,1);
    return SendClientMessage(playerid,AmarilloClaro,"* Usa /reintentar si quieres volver a hacerlo");
}

EmpezarTeoricoAvion(playerid)
{
    TogglePlayerControllable(playerid, 1);
    SendClientMessage(playerid,Gris,"Jaden Rezabal dice: Mi compañero esta de vacaciones, vuelve otro día!");
	return 1;
}

SiguienteCPAutoescuela(playerid)
{
	if(PlayerInfo[playerid][EnClase] == 2)
	{
		new SiguienteCpAutoesc = PlayerInfo[playerid][pAutoescCP];
		PlayerInfo[playerid][pAutoescCP]++;
		PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
		SetPlayerCheckpoint(playerid,ChecksPracticoCoche[SiguienteCpAutoesc][0],ChecksPracticoCoche[SiguienteCpAutoesc][1],ChecksPracticoCoche[SiguienteCpAutoesc][2],5);
	}
	else if(PlayerInfo[playerid][EnClase] == 3)
	{
		new SiguienteCpAutoesc = PlayerInfo[playerid][pAutoescCP];
		PlayerInfo[playerid][pAutoescCP]++;
		PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
		SetPlayerCheckpoint(playerid,ChecksNavegacion[SiguienteCpAutoesc][0],ChecksNavegacion[SiguienteCpAutoesc][1],ChecksNavegacion[SiguienteCpAutoesc][2],8);
	}
	return 1;
}

Autoesc_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused newstate
	#pragma unused oldstate
	new vehicleid = GetPlayerVehicle(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(PlayerInfo[playerid][EnClase] == 2)
		{
			if(PlayerInfo[playerid][pAutoescVeh] == -1 && strcmp(CarInfo[vehicleid][cOwner], "autoescuela", true) == 0)
			{
				//Si el coche es de la autoescuela, y esta haciendo el examen practico, le seteamos la llave temporal
				PlayerInfo[playerid][pPCocheTemporal] = GetCarKey(vehicleid);
				PlayerInfo[playerid][pAutoescVeh] = vehicleid;
				RepairVehicle(CarInfo[vehicleid][cId]);
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x, y, z);
				PlayerInfo[playerid][pAutoescText3d] = CreateDynamic3DTextLabel("Haciendo exámen práctico", Verde, x, y, z, 8, playerid);
				SetTimerEx("EmpezarPracticoCoche", 100, 0, "d", playerid);
			}
			else if(PlayerInfo[playerid][pAutoescVeh] >= 0)
			{
				if(PlayerInfo[playerid][pAutoescVeh] == vehicleid)
				{
					KillTimer(PlayerInfo[playerid][pAutoescTimer]);
					PlayerInfo[playerid][pAutoescTimer] = SetTimerEx("SuspenderPorTardar", 120000, 0, "d", playerid);
					SetTimerEx("SeguimosAutoescSCM", 100, 0, "d", playerid);
				}
				else
				{
					SetTimerEx("EsteNoEsAutoescSCM", 100, 0, "d", playerid);
				}
			}
		}
		else if(PlayerInfo[playerid][EnClase] == 3)
		{
			if(PlayerInfo[playerid][pAutoescVeh] == -1 && strcmp(CarInfo[vehicleid][cOwner], "autoescuela", true) == 0)
			{
				PlayerInfo[playerid][pPCocheTemporal] = GetCarKey(vehicleid);
				PlayerInfo[playerid][pAutoescVeh] = vehicleid;
				RepairVehicle(CarInfo[vehicleid][cId]);
				SetTimerEx("EmpezarPracticoNavegacion", 100, 0, "d", playerid);
			}
			else if(PlayerInfo[playerid][pAutoescVeh] >= 0)
			{
				if(PlayerInfo[playerid][pAutoescVeh] == vehicleid)
				{
					KillTimer(PlayerInfo[playerid][pAutoescTimer]);
					PlayerInfo[playerid][pAutoescTimer] = SetTimerEx("ExamenBarcoSuspenso", 120000, 0, "dd", playerid,1);
					SetTimerEx("SeguimosAutoescSCM", 100, 0, "d", playerid);
				}
				else
				{
					SetTimerEx("EsteNoEsAutoescSCM", 100, 0, "d", playerid);
				}
			}
		}
	}
	return 1;
}

Autoesc_OnPlayerExitVehicle(playerid,vehicleid)
{
	if(PlayerInfo[playerid][EnClase] == 2 && CarInfo[PlayerInfo[playerid][pAutoescVeh]][cId] == vehicleid)
	{
		KillTimer(PlayerInfo[playerid][pAutoescTimer]);
		PlayerInfo[playerid][pAutoescTimer] = SetTimerEx("SuspenderPorNoVolver", 30000, 0, "d", playerid);
		return SendClientMessage(playerid,Naranja,"* Sí no vuelves al coche en 30 segundos suspenderás el exámen!");
	}
	return 1;
}
Autoesc_OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerInfo[playerid][pCheckpoint] == 33)
	{
		new vehicleid = GetPlayerVehicle(playerid);
		if(PlayerInfo[playerid][EnClase] == 2 && PlayerInfo[playerid][pAutoescVeh] == vehicleid)
		{
			if(PlayerInfo[playerid][pAutoescCP] == CPCOCHEAUTOESC)
			{
				KillTimer(PlayerInfo[playerid][pAutoescTimer]);
				DisablePlayerCheckpoint(playerid);
				PlayerPlaySound(playerid,1058,0.0,0.0,0.0);
				ExamenPracticoCocheAprobado(playerid);
			}
			else if(PlayerInfo[playerid][pAutoescCP] > 0)
			{
				KillTimer(PlayerInfo[playerid][pAutoescTimer]);
				PlayerInfo[playerid][pAutoescTimer] = SetTimerEx("SuspenderPorTardar", 120000, 0, "d", playerid);
				DisablePlayerCheckpoint(playerid);
				PlayerPlaySound(playerid,1139,0.0,0.0,0.0);	  
				SiguienteCPAutoescuela(playerid);
			}
		}
		else if(PlayerInfo[playerid][EnClase] == 3)
		{
			if(PlayerInfo[playerid][pAutoescCP] == CPNAVEGAUTOESC && PlayerInfo[playerid][pAutoescVeh] == vehicleid)
			{
				KillTimer(PlayerInfo[playerid][pAutoescTimer]);
				DisablePlayerCheckpoint(playerid);
				PlayerPlaySound(playerid,1058,0.0,0.0,0.0);
				ExamenBarcoAprobado(playerid);
			}
			else if(PlayerInfo[playerid][pAutoescCP] > 0 && PlayerInfo[playerid][pAutoescVeh] == vehicleid)
			{
				KillTimer(PlayerInfo[playerid][pAutoescTimer]);
				PlayerInfo[playerid][pAutoescTimer] = SetTimerEx("ExamenBarcoSuspenso", 120000, 0, "dd", playerid,1);
				DisablePlayerCheckpoint(playerid);
				PlayerPlaySound(playerid,1139,0.0,0.0,0.0);	  
				SiguienteCPAutoescuela(playerid);
			}
			else if(PlayerInfo[playerid][pAutoescCP] == 0 && !IsPlayerInAnyVehicle(playerid))
			{
				DisablePlayerCheckpoint(playerid);
				SendClientMessage(playerid,Verde,"* Sube a un barco para empezar el exámen!");
			}
		}
		return 1;
	}
	return 0;
}

Autoesc_OnPlayerUpdate(playerid)
{
	if(PlayerInfo[playerid][EnClase] == 2)
	{
		if(IsPlayerInVehicle(playerid,CarInfo[PlayerInfo[playerid][pAutoescVeh]][cId]))
		{
			new Float:health;
			GetVehicleHealth(CarInfo[PlayerInfo[playerid][pAutoescVeh]][cId], health);
			if(health < 900) return PlayerInfo[playerid][EnClase] = 0, TogglePlayerControllable(playerid,0), GameTextForPlayer(playerid, "~r~SUSPENSO",3000,3), SetTimerEx("SuspenderPorRomper", 3000, 0, "d", playerid);
			
			new Float:Speed, Float: vPos[3];
			GetVehicleVelocity(CarInfo[PlayerInfo[playerid][pAutoescVeh]][cId], vPos[0], vPos[1], vPos[2]);
			Speed = floatdiv(floatpower(floatmul(floatsqroot(floatadd(floatpower(vPos[0], 2), floatadd(floatpower(vPos[1], 2), floatpower(vPos[2], 2)))), 200), 1.5 ),15);
			if(Speed > 85) return PlayerInfo[playerid][EnClase] = 0, TogglePlayerControllable(playerid,0), GameTextForPlayer(playerid, "~r~SUSPENSO",3000,3), SetTimerEx("SuspenderPorCorrer", 3000, 0, "d", playerid);
		}
	}
	if(PlayerInfo[playerid][EnClase] == 3)
	{
		new Float:health;
		GetVehicleHealth(CarInfo[PlayerInfo[playerid][pAutoescVeh]][cId], health);
		if(health < 950) return PlayerInfo[playerid][EnClase] = 0, TogglePlayerControllable(playerid,0), GameTextForPlayer(playerid, "~r~SUSPENSO",3000,3), SetTimerEx("ExamenBarcoSuspenso", 3000, 0, "dd", playerid, 2);
	}	
	return 1;
}