/*
	---------------------------------------------------------
	|	    GR-TU Tutoriales con TextDraw		|
	|		Script by GROVE4L			|									---------------------------------------------------------
*/


#include <a_samp>

#if defined _TutorialGR_included
  #endinput
#endif
#define _TutorialGR_included
#pragma library TutorialGR

/*
native IniciarTutorialINC(playerid);
native CerrarTutorialINC(playerid);
native ActualizarTituloTuto(playerid,NuevoTitulo[]);
native ActualizarTextoTuto(playerid,NuevoTexto[])
native ActualizarTituloTuto(playerid,NuevoTitulo[],TiempoMilisegundos);
native ActualizarTextoTuto(playerid,NuevoTexto[],TiempoMilisegundos)
*/
new Text:TituloTuto69[MAX_PLAYERS];
new Text:TextoTuto69[MAX_PLAYERS];

forward CerrarTutorialINC(playerid);
public CerrarTutorialINC(playerid)
{
	TextDrawDestroy(TituloTuto69[playerid]);
	TextDrawDestroy(TextoTuto69[playerid]);
	return 1;
}

forward IniciarTutorialINC(playerid);
public IniciarTutorialINC(playerid)
{
	TituloTuto69[playerid] = TextDrawCreate(22.000000,131.000000,"Titulo del Tutorial");
	TextoTuto69[playerid] = TextDrawCreate(22.000000,158.000000,"Texto del Tutorial~n~Lee el Include de ~g~grove4l~w~para mas~n~info");
	TextDrawAlignment(TituloTuto69[playerid],0);
	TextDrawAlignment(TextoTuto69[playerid],0);
	TextDrawBackgroundColor(TituloTuto69[playerid],0x000000ff);
	TextDrawBackgroundColor(TextoTuto69[playerid],0x000000ff);
	TextDrawFont(TituloTuto69[playerid],1);
	TextDrawLetterSize(TituloTuto69[playerid],0.499999,1.700000);
	TextDrawFont(TextoTuto69[playerid],1);
	TextDrawLetterSize(TextoTuto69[playerid],0.499999,1.500000);
	TextDrawColor(TituloTuto69[playerid],0xffffffff);
	TextDrawColor(TextoTuto69[playerid],0xffffffff);
	TextDrawSetOutline(TituloTuto69[playerid],1);
	TextDrawSetOutline(TextoTuto69[playerid],1);
	TextDrawSetProportional(TituloTuto69[playerid],1);
	TextDrawSetProportional(TextoTuto69[playerid],1);
	TextDrawSetShadow(TituloTuto69[playerid],1);
	TextDrawSetShadow(TextoTuto69[playerid],1);
	return 1;
}

stock ActualizarTituloTuto(playerid,NuevoTitulo[])
{
	TextDrawSetString(TituloTuto69[playerid],NuevoTitulo);
	TextDrawShowForPlayer(playerid,TituloTuto69[playerid]);
	return 1;
}

stock ActualizarTextoTuto(playerid,NuevoTexto[])
{
    TextDrawSetString(TextoTuto69[playerid],NuevoTexto);
	TextDrawShowForPlayer(playerid,TextoTuto69[playerid]);
	return 1;
}

stock ActualizarTituloTutoEx(playerid,NuevoTitulo[],Tiempo)
{
	TextDrawSetString(TituloTuto69[playerid],NuevoTitulo);
	TextDrawShowForPlayer(playerid,TituloTuto69[playerid]);
    SetTimerEx("ChauTitle",Tiempo,0,"d",playerid);
	return 1;
}

stock ActualizarTextoTutoEx(playerid,NuevoTexto[],Tiempo)
{
    TextDrawSetString(TextoTuto69[playerid],NuevoTexto);
	TextDrawShowForPlayer(playerid,TextoTuto69[playerid]);
	SetTimerEx("ChauText",Tiempo,0,"d",playerid);
	return 1;
}

forward ChauTitle(playerid);
forward ChauText(playerid);
public ChauTitle(playerid)
{
	TextDrawHideForPlayer(playerid,TituloTuto69[playerid]);
	return 1;
}

public ChauText(playerid)
{
	TextDrawHideForPlayer(playerid,TextoTuto69[playerid]);
	return 1;
}

/*
	-------------------------------------------------------------------------
	|	     BY GROVE4L  || Visita: www.pawnoscripting.com		|
	-------------------------------------------------------------------------
*/