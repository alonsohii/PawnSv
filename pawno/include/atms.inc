#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

#define MAX_ATMS 20

new Transferencia[MAX_PLAYERS];
new TransferenciaID[MAX_PLAYERS];

new Float:ATMInfo[MAX_ATMS][3] = {
{2466.4008789063, -1514.5561523438, 23.902143478394},
{1204.5235595703, -1762.2664794922, 13.489520072937},
{2233.80859375, -1165.9189453125, 25.799325942993},
{599.85131835938, -1245.3594970703, 18.184646606445},
{590.56408691406, -1249.0594482422, 18.013437271118},
{-78.61905670166, -1171.9047851563, 2.0151634216309},
{309.0788269043, -201.73876953125, 1.4718925952911},
{1317.9031982422, -897.26721191406, 39.461376190186},
{1011.5390014648, -928.50537109375, 42.230270385742},
{1108.3698730469, -1369.4790039063, 13.893113136292},
{1206.2705078125, -1468.2092285156, 13.297064781189},
{1349.7719726563, -1759.8059082031, 13.417725563049},
{1833.8083496094, -1849.0778808594, 13.503252029419},
{2808.6423339844, -1587.7308349609, 11.015127182007},
{1837.8933105469, -1691.7854003906, 13.225306510925},
{377.99719238281, -2057.9594726563, 7.7380819320679},
{363.17532348633, -1764.2105712891, 5.3350124359131},
{907.26965332031, -1586.2504882813, 13.467172622681},
{1155.8089599609, -1463.7858886719, 15.699019432068},
{1495.0006103516, -1768.0631103516, 18.697898864746}
};

forward ATMS_OnInit();

public ATMS_OnInit()
{
	ATM = CreateMenu("ATM", 1, 200.0, 100.0, 150.0,0);

	AddMenuItem(ATM, 0, "Retirar");
	AddMenuItem(ATM, 0, "Depositar");
	AddMenuItem(ATM, 0, "Transferir");
	AddMenuItem(ATM, 0, "Consultar");
	AddMenuItem(ATM, 0, "Cancelar");
}

forward ATMS_OnPlayerSelectedMenuRow(playerid, row);
public ATMS_OnPlayerSelectedMenuRow(playerid, row)
{
	new Menu:menuid = GetPlayerMenu(playerid);
	if(menuid == ATM)
	{
		HideMenuForPlayer(ATM, playerid);
		switch(row)
		{
			case 0:
			{
				format(string, 128, "Escribe la cantidad de dinero que retirarás.\nBalance de cuenta:\t$%d", PlayerInfo[playerid][pBank]);
				ShowPlayerDialog(playerid, 1014, DIALOG_STYLE_INPUT, "Retirar dinero", string, "Retirar", "Cancelar");
			}
			case 1:
			{
				format(string, 128, "Escribe la cantidad de dinero que depositarás.\nBalance de cuenta:\t$%d", PlayerInfo[playerid][pBank]);
				ShowPlayerDialog(playerid, 1015, DIALOG_STYLE_INPUT, "Depositar dinero", string, "Depositar", "Cancelar");
			}
			case 2:
			{
				format(string, 128, "Escribe la cantidad de dinero que transferirás.\nBalance de cuenta:\t$%d", PlayerInfo[playerid][pBank]);
				ShowPlayerDialog(playerid, 1016, DIALOG_STYLE_INPUT, "Transferir dinero", string, "Siguiente", "Cancelar");
			}
			case 3:
			{
				format(string, 128, "Balance de tu cuenta a la fecha.\n\t$%d", PlayerInfo[playerid][pBank]);
				ShowPlayerDialog(playerid, 1017, DIALOG_STYLE_MSGBOX, "Consulta de cuenta", string, "Aceptar", "Cancelar");
			}
			case 4:
			{
				HideMenuForPlayer(ATM, playerid);
				format(string, 128, "* %s retira su tarjeta de la ranura.", pName(playerid));
				if(GetPlayerInterior(playerid) > 0) {
				ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				TogglePlayerControllable(playerid, 1);
			}
		}
	}
	return 1;
}

forward ATMS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
public ATMS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 1014)
	{
		if(strlen(inputtext) && response)
		{
			if(IsNumeric(inputtext))
			{
				new cantidad = strval(inputtext);
				
				if(cantidad > PlayerInfo[playerid][pBank] || cantidad < 0)
				{
					format(string, 128, "Escribe la cantidad CORRECTA de dinero que retirarás.\nBalance de cuenta:\t$%d", PlayerInfo[playerid][pBank]);
					ShowPlayerDialog(playerid, 1014, DIALOG_STYLE_INPUT, "Retirar dinero", string, "Retirar", "Cancelar");
					return 1;
				}
				
				PlayerInfo[playerid][pBank] -= cantidad;
				SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
				format(string, 128, "* Has retirado $%d de tu cuenta bancaria.", cantidad);
				SendClientMessage(playerid, Verde, string);
				SafeGivePlayerMoney(playerid, cantidad);
				ShowMenuForPlayer(ATM, playerid);
			}
		}
		else
		{
			ShowMenuForPlayer(ATM, playerid);
		}
	}
	if(dialogid == 1015)
	{
		if(strlen(inputtext) && response)
		{
			if(IsNumeric(inputtext))
			{
				new cantidad = strval(inputtext);
				
				if(SafeGetPlayerMoney(playerid) < cantidad || cantidad < 0)
				{
					format(string, 128, "Escribe la cantidad CORRECTA de dinero que depositarás.\nBalance de cuenta:\t$%d", PlayerInfo[playerid][pBank]);
					ShowPlayerDialog(playerid, 1015, DIALOG_STYLE_INPUT, "Depositar dinero", string, "Depositar", "Cancelar");
					return 1;
				}
				
				PlayerInfo[playerid][pBank] += cantidad;
				SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
				format(string, 128, "* Has depositado $%d en tu cuenta bancaria.", cantidad);
				SendClientMessage(playerid, Verde, string);
				SafeGivePlayerMoney(playerid, -cantidad);
				ShowMenuForPlayer(ATM, playerid);
			}
		}
		else
		{
			ShowMenuForPlayer(ATM, playerid);
		}
	}
	if(dialogid == 1016)
	{
		if(response && strlen(inputtext))
		{
			if(IsNumeric(inputtext))
			{
				Transferencia[playerid] = strval(inputtext);
				
				if(PlayerInfo[playerid][pBank] < Transferencia[playerid])
				{
					format(string, 128, "Escribe la cantidad CORRECTA de dinero que transferirás.\nBalance de cuenta:\t$%d", PlayerInfo[playerid][pBank]);
					ShowPlayerDialog(playerid, 1016, DIALOG_STYLE_INPUT, "Transferir dinero", string, "Siguiente", "Cancelar");
					return 1;
				}
				
				format(string, 128, "Escribe el ID del jugador al que le transferiras:\n\t$%d", Transferencia[playerid]);
				ShowPlayerDialog(playerid, 1018, DIALOG_STYLE_INPUT, "Transferir dinero", string, "Transferir", "Cancelar");
			}
		}
		else
		{
			ShowMenuForPlayer(ATM, playerid);
		}
	}
	if(dialogid == 1017)
	{
		if(response)
		{
			ShowMenuForPlayer(ATM, playerid);
		}
		else
		{
			TogglePlayerControllable(playerid, 1);
		}
	}
	if(dialogid == 1018)
	{
		if(response && strlen(inputtext))
		{
			if(IsNumeric(inputtext))
			{
				TransferenciaID[playerid] = strval(inputtext);
				if(!IsPlayerConnected(playerid))
				{
					format(string, 128, "Escribe el ID CORRECTO del jugador al que le transferiras:\n\t$%d", Transferencia[playerid]);
					ShowPlayerDialog(playerid, 1018, DIALOG_STYLE_INPUT, "Transferir dinero", string, "Transferir", "Cancelar");
					return 1;
				}
				
				PlayerInfo[playerid][pBank] -= Transferencia[playerid];
				SaveValue(playerid, "Banco", PlayerInfo[playerid][pBank]);
				PlayerInfo[TransferenciaID[playerid]][pBank] += Transferencia[playerid];
				SaveValue(TransferenciaID[playerid], "Banco", PlayerInfo[TransferenciaID[playerid]][pBank]);
				format(string, 128, "* %s ha transferido $%d a tu cuenta bancaria.", pName(playerid), Transferencia[playerid]);
				SendClientMessage(TransferenciaID[playerid], Amarillo, string);
				SendClientMessage(playerid, Amarillo, "* Dinero transferido correctamente.");
				ShowMenuForPlayer(ATM, playerid);
			}
		}
		else
		{
			ShowMenuForPlayer(ATM, playerid);
		}
	}
	return 1;
}