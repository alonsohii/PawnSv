#include <a_samp>

#define MENOROIGUAL <=
#define MAYOROIGUAL >=
#define MAXIMO_DINERO 100000000

new Text:Caja[MAX_PLAYERS];
new Text:Caja2[MAX_PLAYERS];
new Text:Letra[MAX_PLAYERS];
new Text:Dinero[MAX_PLAYERS];
new Text:Dinero2[MAX_PLAYERS];
new DineroV[MAX_PLAYERS] = 0;

forward ActivarGDinero(playerid);
public ActivarGDinero(playerid)
{
	Caja[playerid] = TextDrawCreate(498.000000,79.000000,"_");
	Caja2[playerid] = TextDrawCreate(498.000000,79.000000,"_");
	Letra[playerid] = TextDrawCreate(501.000000,78.000000,"Dinero");
	Dinero[playerid] = TextDrawCreate(500.000000,96.000000,"~g~$");
	Dinero2[playerid] = TextDrawCreate(500.000000,96.000000,"~g~$00000000");
	TextDrawUseBox(Caja[playerid],1);
	TextDrawBoxColor(Caja[playerid],0x000000cc);
	TextDrawTextSize(Caja[playerid],620.000000,1.000000);
	TextDrawUseBox(Caja2[playerid],1);
	TextDrawBoxColor(Caja2[playerid],0x0000ffff);
	TextDrawTextSize(Caja2[playerid],620.000000,0.000000);
	TextDrawAlignment(Caja[playerid],0);
	TextDrawAlignment(Caja2[playerid],0);
	TextDrawAlignment(Letra[playerid],0);
	TextDrawAlignment(Dinero[playerid],0);
	TextDrawAlignment(Dinero2[playerid],0);
	TextDrawBackgroundColor(Caja[playerid],0x000000ff);
	TextDrawBackgroundColor(Caja2[playerid],0x000000ff);
	TextDrawBackgroundColor(Letra[playerid],0x000000ff);
	TextDrawBackgroundColor(Dinero[playerid],0x000000ff);
	TextDrawBackgroundColor(Dinero2[playerid],0x000000ff);
	TextDrawFont(Caja[playerid],3);
	TextDrawLetterSize(Caja[playerid],0.599999,4.599999);
	TextDrawFont(Caja2[playerid],3);
	TextDrawLetterSize(Caja2[playerid],1.000000,1.300000);
	TextDrawFont(Letra[playerid],2);
	TextDrawLetterSize(Letra[playerid],0.699999,1.500000);
	TextDrawFont(Dinero[playerid],3);
	TextDrawLetterSize(Dinero[playerid],0.599999,2.100000);
	TextDrawFont(Dinero2[playerid],3);
	TextDrawLetterSize(Dinero2[playerid],0.599999,2.100000);
	TextDrawColor(Caja[playerid],0xffffffff);
	TextDrawColor(Caja2[playerid],0xffffffff);
	TextDrawColor(Letra[playerid],0xffffffff);
	TextDrawColor(Dinero[playerid],0xffffffff);
	TextDrawColor(Dinero2[playerid],0xffffffff);
	TextDrawSetOutline(Caja[playerid],1);
	TextDrawSetOutline(Caja2[playerid],1);
	TextDrawSetOutline(Letra[playerid],1);
	TextDrawSetOutline(Dinero[playerid],1);
	TextDrawSetOutline(Dinero2[playerid],1);
	TextDrawSetProportional(Caja[playerid],1);
	TextDrawSetProportional(Caja2[playerid],1);
	TextDrawSetProportional(Letra[playerid],1);
	TextDrawSetProportional(Dinero[playerid],1);
	TextDrawSetProportional(Dinero2[playerid],1);
	TextDrawSetShadow(Caja[playerid],1);
	TextDrawSetShadow(Caja2[playerid],1);
	TextDrawSetShadow(Letra[playerid],1);
	TextDrawSetShadow(Dinero[playerid],1);
	TextDrawSetShadow(Dinero2[playerid],1);
	TextDrawShowForPlayer(playerid,Caja[playerid]);
	TextDrawShowForPlayer(playerid,Caja2[playerid]);
	TextDrawShowForPlayer(playerid,Letra[playerid]);
	TextDrawShowForPlayer(playerid,Dinero[playerid]);
	TextDrawShowForPlayer(playerid,Dinero2[playerid]);
	return 1;
}

forward DesactivarGDinero(playerid);
public DesactivarGDinero(playerid)
{
	TextDrawHideForPlayer(playerid,Caja[playerid]);
	TextDrawHideForPlayer(playerid,Caja2[playerid]);
	TextDrawHideForPlayer(playerid,Letra[playerid]);
	TextDrawHideForPlayer(playerid,Dinero[playerid]);
	TextDrawHideForPlayer(playerid,Dinero2[playerid]);
	return 1;
}

stock SumarGDinero(playerid,suma)
{
    new cantidad = DineroV[playerid] + suma;
    if(cantidad == 0)
    {
        new string[256];
		format(string, sizeof(string), "~g~$00000000");
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = 0;
	}
	else if(cantidad MAYOROIGUAL 1 && cantidad MENOROIGUAL 9)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$0000000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 10 && cantidad MENOROIGUAL 99)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$000000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 100 && cantidad MENOROIGUAL 999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$00000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 1000 && cantidad MENOROIGUAL 9999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$0000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 10000 && cantidad MENOROIGUAL 99999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 100000 && cantidad MENOROIGUAL 999999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$00%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 1000000 && cantidad MENOROIGUAL 9999999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$0%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 10000000 && cantidad MENOROIGUAL 99999999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad >= 100000000)
	{
	    new string[256];
	    format(string, sizeof(string), "La cantidad es mayor o igual a $%d. Dato anulado.", MAXIMO_DINERO);
    	SendClientMessage(playerid, 0xD8D8D8FF,string);
		return 1;
	}

	return 1;
}

stock RestarGDinero(playerid,resta)
{
    new cantidad = DineroV[playerid] - resta;
	if(cantidad MAYOROIGUAL -1 && cantidad MENOROIGUAL -9)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-0000000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -10 && cantidad MENOROIGUAL -99)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-000000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -100 && cantidad MENOROIGUAL -999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-00000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -1000 && cantidad MENOROIGUAL -9999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-00000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -10000 && cantidad MENOROIGUAL -99999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-0000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -100000 && cantidad MENOROIGUAL -999999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -1000000 && cantidad MENOROIGUAL -9999999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-00%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -10000000 && cantidad MENOROIGUAL -99999999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-0%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL -10000000 && cantidad MENOROIGUAL -99999999)
	{
	    new string[256];
		format(string, sizeof(string), "~r~$-%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(DineroV[playerid] == cantidad)
	{
	    new string[256];
		format(string, sizeof(string), "~g~$00000000");
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = 0;
	}
	else if(cantidad == 0)
	{
		new string[256];
		format(string, sizeof(string), "~g~$00000000");
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = 0;
	}
	else if(cantidad MAYOROIGUAL 1 && cantidad MENOROIGUAL 9)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$0000000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 10 && cantidad MENOROIGUAL 99)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$000000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 100 && cantidad MENOROIGUAL 999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$00000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 1000 && cantidad MENOROIGUAL 9999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$0000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 10000 && cantidad MENOROIGUAL 99999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$000%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 100000 && cantidad MENOROIGUAL 999999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$00%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 1000000 && cantidad MENOROIGUAL 9999999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$0%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad MAYOROIGUAL 10000000 && cantidad MENOROIGUAL 99999999)
	{
    	new string[256];
		format(string, sizeof(string), "~g~$%d",cantidad);
		TextDrawSetString(Dinero2[playerid],string);
		TextDrawShowForPlayer(playerid,Dinero2[playerid]);
		DineroV[playerid] = cantidad;
	}
	else if(cantidad >= 100000000)
	{
	    new string[256];
	    format(string, sizeof(string), "La cantidad es mayor o igual a $%d. Dato anulado.", MAXIMO_DINERO);
    	SendClientMessage(playerid, 0xD8D8D8FF,string);
		return 1;
	}

	return 1;
}


// By GROVE4L