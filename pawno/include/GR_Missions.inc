#include <a_samp>

new Text:TMisiones[MAX_PLAYERS];
new Text:TPeli[2][MAX_PLAYERS];
new Text:TCrono[MAX_PLAYERS];
new TTimer[MAX_PLAYERS];
new TTPeli[MAX_PLAYERS];
new TCamara[MAX_PLAYERS];
new TReloj[MAX_PLAYERS];
new P1[MAX_PLAYERS];
new Float:POS[3];
new EstaEnMision[MAX_PLAYERS];
new Pasos[MAX_PLAYERS] = -1;
new string[256];
new sr[256];
new Reloj[2][MAX_PLAYERS];



