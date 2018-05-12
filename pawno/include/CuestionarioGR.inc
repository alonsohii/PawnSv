#include <a_samp>

#if defined _CuestionarioGR_included
  #endinput
#endif
#define _CuestionarioGR_included
#pragma library CuestionarioGR

#define DIALOGOCUESTIONAIO 69 //Id del Dialogo
new PCorrecta[MAX_PLAYERS];

forward Cuestionarios(playerid,respondio);

//native Cuestionario(playerid,Correcta,Pregunta[],Opciones[])

stock Cuestionario(playerid,Correcta,Pregunta[],Opciones[])
{
	ShowPlayerDialog(playerid,DIALOGOCUESTIONAIO,DIALOG_STYLE_LIST,Pregunta,Opciones,"Aceptar","");
	PCorrecta[playerid] = Correcta;
}

