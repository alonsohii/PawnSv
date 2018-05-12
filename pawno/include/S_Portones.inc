/*
*
*	- Creador de portones en una sola linea. By spell =D
*	- Conserve los creditos...
*
*/

#include <a_samp>
#include <streamer>
#include <YSI\y_hooks>

#define MAX_PORTONES     5//Cambien esto, según la cantidad de portones que creen que vallan a crear
#define DISTANCIA        20//metros a los que se abrirá la puerta
#define TECLA       	KEY_CROUCH//Con qué tecla se podrá abrir las puertas.

/*

native CrearPorton(id_obj,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:x2,Float:y2,Float:z2,Float:Velocidad)

*/

enum pInfo
{
	pID,
	Float:pPosx,
	Float:pPosy,
	Float:pPosz,
	Float:pMovex,
	Float:pMovey,
	Float:pMovez,
	Float:pVelocidad
}

new
		InfoPorton[MAX_PORTONES][pInfo],
		Total_Portones_Creados,
		Porton_Actual;

forward CrearPorton(id_obj,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:x2,Float:y2,Float:z2,Float:Velocidad);

public CrearPorton(id_obj,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:x2,Float:y2,Float:z2,Float:Velocidad)
{
	Total_Portones_Creados++;
	InfoPorton[Total_Portones_Creados][pID] = CreateDynamicObject(id_obj,x,y,z,rx,ry,rz);
	InfoPorton[Total_Portones_Creados][pPosx] = x;
	InfoPorton[Total_Portones_Creados][pPosy] = y;
	InfoPorton[Total_Portones_Creados][pPosz] = z;
	InfoPorton[Total_Portones_Creados][pMovex] = x2;
	InfoPorton[Total_Portones_Creados][pMovey] = y2;
	InfoPorton[Total_Portones_Creados][pMovez] = z2;
	InfoPorton[Total_Portones_Creados][pVelocidad] = Velocidad;
	return 1;
}

Hook:Por_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(Porton_Actual > 0) return 0;
	new i;
	if(newkeys == TECLA)
	{
		while( i++ != Total_Portones_Creados )
		{
		    if(IsPlayerInRangeOfPoint(playerid,DISTANCIA,InfoPorton[i][pPosx],InfoPorton[i][pPosy],InfoPorton[i][pPosz]))
		    {
				MoveDynamicObject(InfoPorton[i][pID],InfoPorton[i][pMovex],InfoPorton[i][pMovey],InfoPorton[i][pMovez],InfoPorton[i][pVelocidad]);
				SetTimer("CerrarPortones",6000,0);
				Porton_Actual = i;
			}
		}
	}
	return 1;
}

forward CerrarPortones();

public CerrarPortones()
{
	new i;
	while( i++ != Total_Portones_Creados )
	{
		if(Porton_Actual == i)
		{
			MoveDynamicObject(InfoPorton[i][pID],InfoPorton[i][pPosx],InfoPorton[i][pPosy],InfoPorton[i][pPosz],InfoPorton[i][pVelocidad]);
			Porton_Actual = 0;
		}
	}
	return 1;
}

