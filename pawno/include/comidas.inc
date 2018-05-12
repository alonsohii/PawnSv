#include <a_samp>
#include <globalvars>
#include <colores>

#define MAX_BEBIDAS 7
#define MAX_SNACKS 6
#define MAX_CAFES 6
#define MAX_RESTAURANTE 9
#define MAX_BURGER 7
#define MAX_PIZZERIA 8
#define MAX_POLLOFRITO 7
#define MAX_BARCAFETERIA 7
#define MAX_ALCOHOL 7
#define MAX_DONUTS 7
#define MAX_PERRITOS 3
#define MAX_HELADOS 3
#define MAX_CHINO 7
#define MAX_JAPO 6
#define MAX_CARCEL 1
#define MAX_MEX 7
#define MAX_NEVERA 4

enum foodInfo
{	
	foodName[50],
	Float:foodHealth,
	foodPrecio,
}

new Bebidas[MAX_BEBIDAS][foodInfo] = {
{"CocaCola", 0.0, 5},
{"Sprite", 0.0, 5},
{"Fanta", 0.0, 5},
{"Te helado", 0.0, 5},
{"Coca Light", 0.0, 5},
{"Aquarius", 0.0, 5},
{"Agua", 0.0, 5}
};

new Snacks[MAX_SNACKS][foodInfo] = {
{"Doritos", 0.0, 5},
{"Pipas", 0.0, 5},
{"Gominolas", 0.0, 5},
{"Chocolatina", 0.0, 5},
{"Chicles", 0.0, 5},
{"Barrita energetica", 0.0, 5}
};

new Cafes[MAX_CAFES][foodInfo] = {
{"Cafe solo", 0.0, 20},
{"Descafeinado", 0.0, 20},
{"Capuccino", 0.0, 20},
{"Americano", 0.0, 20},
{"Espresso", 0.0, 20},
{"Cafe late", 0.0, 20}
};

new Restaurante[MAX_RESTAURANTE][foodInfo] = {
{"Ensalada Mixta", 70.0, 100},
{"Sopa de marisco", 75.0, 150},
{"Sopa vegetal", 60.0, 80},
{"Pizza especial", 80.0, 150},
{"Pasta de la casa", 75.0, 150},
{"Rape con menestra", 90.0, 200},
{"Pollo en salsa de ciruelas", 90.0, 200},
{"Chuleta de cerdo agridulce", 100.0, 250},
{"Pata de cordero con setas", 100.0, 270}
};

new Burger[MAX_BURGER][foodInfo] = {
{"Refresco mediano", 20.0, 10},
{"Refresco grande", 30.0, 20},
{"Hamburguesa vegetal", 35.0, 30},
{"Hamburguesa y patatas", 60.0, 40},
{"Hamburguesa especial", 75.0, 50},
{"Hamburguesa doble con queso", 80.0, 60},
{"Helado", 30.0, 20}
};

new Pizzeria[MAX_PIZZERIA][foodInfo] = {
{"Refresco mediano", 20.0, 10},
{"Refresco grande", 30.0, 20},
{"Bruschetta marinara", 40.0, 30},
{"Pizza margarita", 60.0, 80},
{"Pizza a los 4 quesos", 60.0, 90},
{"Pizza barbacoa", 70.0, 100},
{"Pizza vegetal", 90.0, 100},
{"Pizza caprichosa", 40.0, 150}
};

new Pollofrito[MAX_POLLOFRITO][foodInfo] = {
{"Refresco mediano", 20.0, 10},
{"Refresco grande", 30.0, 20},
{"Nuggets mediano", 35.0, 30},
{"Nuggets con patatas", 60.0, 40},
{"Alitas de pollo", 75.0, 50},
{"Muslos de pollo", 80.0, 60},
{"Helado", 30.0, 20}
};

new Barcafeteria[MAX_BARCAFETERIA][foodInfo] = {
{"Cafe", 30.0, 20},
{"Refresco", 20.0, 10},
{"Cerveza", 35.0, 30},
{"Sandwich", 60.0, 40},
{"Tortitas", 75.0, 50},
{"Huevos con bacon", 80.0, 60},
{"Filete y patatas", 90.0, 80}
};

new Alcohol[MAX_ALCOHOL][foodInfo] = {
{"Cerveza", 30.0, 20},
{"Litro de cerveza", 50.0, 50},
{"Chupito de ron con miel", 60.0, 80},
{"Whisky", 80.0, 100},
{"Combinado", 100.0, 200},
{"Hennessy del 87", 100.0, 500},
{"Absenta", 100.0, 600}
};

new Donuts[MAX_DONUTS][foodInfo] = {
{"Refresco mediano", 20.0, 10},
{"Refresco grande", 30.0, 20},
{"Cafe con leche", 30.0, 25},
{"Donut y cafe", 35.0, 30},
{"Paquete de donuts pequeño", 60.0, 40},
{"Paquete de donuts mediano", 75.0, 50},
{"Caja de donuts", 80.0, 60}
};

new Chino[MAX_CHINO][foodInfo] = {
{"Arroz tres delicias", 50.0, 50},
{"Ensalada china", 60.0, 60},
{"Tallarines con gambas", 60.0, 65},
{"Fideos con ternera", 65.0, 70},
{"Pollo frito con almendras", 65.0, 80},
{"Ternera con salsa de judías", 75.0, 80},
{"Gambas agridulces", 80.0, 100}
};

new Japo[MAX_JAPO][foodInfo] = {
{"Sushi", 50.0, 50},
{"Yakisoba", 60.0, 60},
{"Teriyaki", 60.0, 65},
{"Onigiri", 65.0, 70},
{"Sake", 65.0, 80},
{"Cerveza japonesa", 75.0, 80}
};

new Perritos[MAX_PERRITOS][foodInfo] = {
{"Perrito normal", 60.0, 40},
{"Perrito especial", 75.0, 50},
{"Perrito doble", 80.0, 60}
};

new Helados[MAX_HELADOS][foodInfo] = {
{"Cucurucho de helado", 60.0, 40},
{"Cucurucho doble de helado", 75.0, 50},
{"Tarrina de helado con especias", 80.0, 60}
};

new Carcel[MAX_CARCEL][foodInfo] = {
{"Bandeja de comida", 60.0, 0}
};

new Mexicano[MAX_MEX][foodInfo] = {
{"Cerveza", 10.0, 10},
{"Nachos", 20.0, 20},
{"Tacos", 35.0, 30},
{"Burrito", 60.0, 40},
{"Enchilada", 75.0, 50},
{"Chimichanga", 80.0, 60},
{"Fajitas de pollo", 90.0, 80}
};

new Nevera[MAX_NEVERA][foodInfo] = {
{"Cerveza", 10.0, 0},
{"Nugets de pollo", 20.0, 0},
{"Pizza", 20.0, 0},
{"Hamburguesas", 20.0, 0}
};



CrearMenus()
{
	bebidas = CreateMenu("Bebidas", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_BEBIDAS; i++)
	{
		format(string, 128, "$%d", Bebidas[i][foodPrecio]);
		AddMenuItem(bebidas, 0, Bebidas[i][foodName]);
		AddMenuItem(bebidas, 1, string);
	}
	AddMenuItem(bebidas, 0, "Salir");
	
	snacks = CreateMenu("Snacks", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_SNACKS; i++)
	{
		format(string, 128, "$%d", Snacks[i][foodPrecio]);
		AddMenuItem(snacks, 0, Snacks[i][foodName]);
		AddMenuItem(snacks, 1, string);
	}
	AddMenuItem(snacks, 0, "Salir");

	cafes = CreateMenu("Cafes", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_CAFES; i++)
	{
		format(string, 128, "$%d", Cafes[i][foodPrecio]);
		AddMenuItem(cafes, 0, Cafes[i][foodName]);
		AddMenuItem(cafes, 1, string);
	}
	AddMenuItem(cafes, 0, "Salir");
	
	restaurante = CreateMenu("Restaurante", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_RESTAURANTE; i++)
	{
		format(string, 128, "$%d", Restaurante[i][foodPrecio]);
		AddMenuItem(restaurante, 0, Restaurante[i][foodName]);
		AddMenuItem(restaurante, 1, string);
	}
	AddMenuItem(restaurante, 0, "Salir");
	
	burger = CreateMenu("Burger", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_BURGER; i++)
	{
		format(string, 128, "$%d", Burger[i][foodPrecio]);
		AddMenuItem(burger, 0, Burger[i][foodName]);
		AddMenuItem(burger, 1, string);
	}
	AddMenuItem(burger, 0, "Salir");
	
	pizzeria = CreateMenu("Pizzeria", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_PIZZERIA; i++)
	{
		format(string, 128, "$%d", Pizzeria[i][foodPrecio]);
		AddMenuItem(pizzeria, 0, Pizzeria[i][foodName]);
		AddMenuItem(pizzeria, 1, string);
	}
	AddMenuItem(pizzeria, 0, "Salir");
	
	pollofrito = CreateMenu("Pollo frito", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_POLLOFRITO; i++)
	{
		format(string, 128, "$%d", Pollofrito[i][foodPrecio]);
		AddMenuItem(pollofrito, 0, Pollofrito[i][foodName]);
		AddMenuItem(pollofrito, 1, string);
	}
	AddMenuItem(pollofrito, 0, "Salir");
	
	barcafeteria = CreateMenu("Bar Cafeteria", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_BARCAFETERIA; i++)
	{
		format(string, 128, "$%d", Barcafeteria[i][foodPrecio]);
		AddMenuItem(barcafeteria, 0, Barcafeteria[i][foodName]);
		AddMenuItem(barcafeteria, 1, string);
	}
	AddMenuItem(barcafeteria, 0, "Salir");
	
	alcohol = CreateMenu("Alcohol", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_ALCOHOL; i++)
	{
		format(string, 128, "$%d", Alcohol[i][foodPrecio]);
		AddMenuItem(alcohol, 0, Alcohol[i][foodName]);
		AddMenuItem(alcohol, 1, string);
	}
	AddMenuItem(alcohol, 0, "Salir");
	
	donuts = CreateMenu("Donuts", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_DONUTS; i++)
	{
		format(string, 128, "$%d", Donuts[i][foodPrecio]);
		AddMenuItem(donuts, 0, Donuts[i][foodName]);
		AddMenuItem(donuts, 1, string);
	}
	AddMenuItem(donuts, 0, "Salir");
	
	chino = CreateMenu("Chino", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_CHINO; i++)
	{
		format(string, 128, "$%d", Chino[i][foodPrecio]);
		AddMenuItem(chino, 0, Chino[i][foodName]);
		AddMenuItem(chino, 1, string);
	}
	AddMenuItem(chino, 0, "Salir");
	
	helados = CreateMenu("Helados", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_HELADOS; i++)
	{
		format(string, 128, "$%d", Helados[i][foodPrecio]);
		AddMenuItem(helados, 0, Helados[i][foodName]);
		AddMenuItem(helados, 1, string);
	}
	AddMenuItem(helados, 0, "Salir");
	
	perritos = CreateMenu("Perritos", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_PERRITOS; i++)
	{
		format(string, 128, "$%d", Perritos[i][foodPrecio]);
		AddMenuItem(perritos, 0, Perritos[i][foodName]);
		AddMenuItem(perritos, 1, string);
	}
	AddMenuItem(perritos, 0, "Salir");
	
	japo = CreateMenu("Comida Japonesa", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_JAPO; i++)
	{
		format(string, 128, "$%d", Japo[i][foodPrecio]);
		AddMenuItem(japo, 0, Japo[i][foodName]);
		AddMenuItem(japo, 1, string);
	}
	AddMenuItem(japo, 0, "Salir");

	carcel = CreateMenu("Carcel", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_CARCEL; i++)
	{
		format(string, 128, "$%d", Carcel[i][foodPrecio]);
		AddMenuItem(carcel, 0, Carcel[i][foodName]);
		AddMenuItem(carcel, 1, string);
	}
	AddMenuItem(carcel, 0, "Salir");
	
	mexicano = CreateMenu("Menu Mexicano", 2, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_MEX; i++)
	{
		format(string, 128, "$%d", Mexicano[i][foodPrecio]);
		AddMenuItem(mexicano, 0, Mexicano[i][foodName]);
		AddMenuItem(mexicano, 1, string);
	}
	AddMenuItem(mexicano, 0, "Salir");
	
	nevera = CreateMenu("Nevera", 1, 200.0, 200.0, 200.0, 200.0);
	for(new i; i < MAX_NEVERA; i++)
	{
		AddMenuItem(nevera, 0, Nevera[i][foodName]);
	}
	AddMenuItem(nevera, 0, "Salir");
}

Comidas_OnPlayerSelectedMenuRow(playerid, row)
{
	new Menu:current = GetPlayerMenu(playerid);
	new Float:Health;
	GetPlayerHealth(playerid, Health);
	if(current == bebidas)
	{
		if(row != MAX_BEBIDAS)
		{
			if(SafeGetPlayerMoney(playerid) < Bebidas[row][foodPrecio])
			{
				HideMenuForPlayer(bebidas, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Bebidas[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Bebidas[row][foodPrecio]);
			format(string, 128, "* %s mete una moneda y obtiene una botella de %s", pName(playerid), Bebidas[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(bebidas, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(bebidas, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
	}
	else if(current == snacks)
	{
		if(row != MAX_SNACKS)
		{
			if(SafeGetPlayerMoney(playerid) < Snacks[row][foodPrecio])
			{
				HideMenuForPlayer(snacks, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Snacks[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Snacks[row][foodPrecio]);
			format(string, 128, "* %s mete una moneda y obtiene un paquete de %s", pName(playerid), Snacks[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(snacks, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(snacks, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == cafes)
	{
		if(row != MAX_CAFES)
		{
			if(SafeGetPlayerMoney(playerid) < Cafes[row][foodPrecio])
			{
				HideMenuForPlayer(cafes, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Cafes[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Cafes[row][foodPrecio]);
			format(string, 128, "* %s ha pedido un %s", pName(playerid), Cafes[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(cafes, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(cafes, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == restaurante)
	{
		if(row != MAX_RESTAURANTE)
		{
			if(SafeGetPlayerMoney(playerid) < Restaurante[row][foodPrecio])
			{
				HideMenuForPlayer(restaurante, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Restaurante[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Restaurante[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Restaurante[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(restaurante, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(restaurante, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == burger)
	{
		if(row != MAX_BURGER)
		{
			if(SafeGetPlayerMoney(playerid) < Burger[row][foodPrecio])
			{
				HideMenuForPlayer(burger, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Burger[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Burger[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Burger[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(burger, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(burger, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == pizzeria)
	{
		if(row != MAX_PIZZERIA)
		{
			if(SafeGetPlayerMoney(playerid) < Pizzeria[row][foodPrecio])
			{
				HideMenuForPlayer(pizzeria, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Pizzeria[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Pizzeria[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Pizzeria[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(pizzeria, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(pizzeria, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == pollofrito)
	{
		if(row != MAX_POLLOFRITO)
		{
			if(SafeGetPlayerMoney(playerid) < Pollofrito[row][foodPrecio])
			{
				HideMenuForPlayer(pollofrito, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Pollofrito[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Pollofrito[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Pollofrito[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(pollofrito, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(pollofrito, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == barcafeteria)
	{
		if(row != MAX_BARCAFETERIA)
		{
			if(SafeGetPlayerMoney(playerid) < Barcafeteria[row][foodPrecio])
			{
				HideMenuForPlayer(barcafeteria, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Barcafeteria[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Barcafeteria[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Barcafeteria[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(barcafeteria, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(barcafeteria, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == alcohol)
	{
		if(row != MAX_ALCOHOL)
		{
			if(SafeGetPlayerMoney(playerid) < Alcohol[row][foodPrecio])
			{
				HideMenuForPlayer(alcohol, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Alcohol[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Alcohol[row][foodPrecio]);
			PlayerInfo[playerid][pAlcohol] += 1;
			SaveValue(playerid, "Alcohol", PlayerInfo[playerid][pAlcohol]);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
			if(PlayerInfo[playerid][pAlcohol] == 3)
			{
				SetPlayerDrunkLevel(playerid, 5000);
			}
			switch(row)
			{
				case 0:
				{
					format(string, 128, "* %s pide una jarra de cerveza en la barra.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				}
				case 1:
				{
					format(string, 128, "* %s pide una botella de cerveza de 40 onzas.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}

				}
				case 2:
				{
					format(string, 128, "* %s pide un chupito de ron con miel en la barra.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}

				}
				case 3:
				{
					format(string, 128, "* %s pide un vaso de whisky escocés en la barra.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}

				}
				case 4:
				{
					format(string, 128, "* %s pide un cocktail especial de la casa en la barra.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}

				}
				case 5:
				{
					format(string, 128, "* %s pide una copa de coñac Hennessy del año 87.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}

				}
				case 6:
				{
					format(string, 128, "* %s pide una copa de absenta añejo Pernod Fils.", pName(playerid));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}

				}
			}
			HideMenuForPlayer(alcohol, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(alcohol, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
	}
	else if(current == donuts)
	{
		if(row != MAX_DONUTS)
		{
			if(SafeGetPlayerMoney(playerid) < Donuts[row][foodPrecio])
			{
				HideMenuForPlayer(donuts, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Donuts[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Donuts[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Donuts[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(donuts, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(donuts, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == chino)
	{
		if(row != MAX_CHINO)
		{
			if(SafeGetPlayerMoney(playerid) < Chino[row][foodPrecio])
			{
				HideMenuForPlayer(chino, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Chino[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Chino[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Chino[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(chino, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(chino, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == perritos)
	{
		if(row != MAX_PERRITOS)
		{
			if(SafeGetPlayerMoney(playerid) < Perritos[row][foodPrecio])
			{
				HideMenuForPlayer(perritos, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Perritos[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Perritos[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Perritos[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(perritos, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(perritos, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == helados)
	{
		if(row != MAX_HELADOS)
		{
			if(SafeGetPlayerMoney(playerid) < Helados[row][foodPrecio])
			{
				HideMenuForPlayer(helados, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Helados[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Helados[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Helados[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(helados, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(helados, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == japo)
	{
		if(row != MAX_JAPO)
		{
			if(SafeGetPlayerMoney(playerid) < Japo[row][foodPrecio])
			{
				HideMenuForPlayer(japo, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Japo[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Japo[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Japo[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(japo, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(japo, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == carcel)
	{
		if(row != MAX_CARCEL)
		{
			GM_SetPlayerHealth(playerid, Health + Carcel[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Carcel[row][foodPrecio]);
			format(string, 128, "* %s coge su %s", pName(playerid), Carcel[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(carcel, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(carcel, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] = 0;
		ComprobarBarrita(playerid);
	}
	else if(current == mexicano)
	{
		if(row != MAX_MEX)
		{
			if(SafeGetPlayerMoney(playerid) < Mexicano[row][foodPrecio])
			{
				HideMenuForPlayer(mexicano, playerid);
				TogglePlayerControllable(playerid, 1);
				SendClientMessage(playerid, Rojo, "* Dinero insuficiente!");
				return 1;
			}
			GM_SetPlayerHealth(playerid, Health + Mexicano[row][foodHealth]);
			SafeGivePlayerMoney(playerid, -Mexicano[row][foodPrecio]);
			format(string, 128, "* %s ha hecho su pedido: %s", pName(playerid), Mexicano[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(mexicano, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(mexicano, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	else if(current == nevera)
	{
		if(row == 0)
		{
			PlayerInfo[playerid][pAlcohol] += 1;
			SaveValue(playerid, "Alcohol", PlayerInfo[playerid][pAlcohol]);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
			if(PlayerInfo[playerid][pAlcohol] == 3)
			{
				SetPlayerDrunkLevel(playerid, 5000);
			}
			format(string, 128, "* %s coge de la nevera: %s", pName(playerid), Nevera[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(nevera, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		if(row != MAX_NEVERA && row > 0)
		{
			GM_SetPlayerHealth(playerid, Health + Nevera[row][foodHealth]);
			format(string, 128, "* %s coge de la nevera: %s", pName(playerid), Nevera[row][foodName]);
			if(GetPlayerInterior(playerid) > 0) {
			ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			else {
			ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
			HideMenuForPlayer(nevera, playerid);
			TogglePlayerControllable(playerid, 1);
		}
		else
		{
			HideMenuForPlayer(nevera, playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		PlayerInfo[playerid][pHambre] --;
		ComprobarBarrita(playerid);
	}
	SaveValue(playerid, "Hambre", PlayerInfo[playerid][pHambre]);
	return 1;
}

LoadComidas()
{
	new sql[80], row[512], count, celiminado, TotalComidas;
	format(sql, sizeof(sql), "SELECT COUNT(*) FROM comidas");
	mysql_query(sql);
	mysql_store_result();
	mysql_fetch_row(row);
	count = strval(row);
	
	for(new i = 1; i <= count; i++)
	{
		format(sql, sizeof(sql), "SELECT * FROM comidas WHERE id = %d", i);
		mysql_query(sql);
		mysql_store_result();
		mysql_fetch_row(row);
		split(row, arrCoords, '|');
		celiminado = strval(arrCoords[8]);
		
		if(celiminado == 0)
		{
			Comidas[i][coId] = strval(arrCoords[0]);
			format(Comidas[i][coName], 24, "%s", arrCoords[1]);
			Comidas[i][coX] = floatstr(arrCoords[2]);
			Comidas[i][coY] = floatstr(arrCoords[3]);
			Comidas[i][coZ] = floatstr(arrCoords[4]);
			Comidas[i][coInt] = strval(arrCoords[5]);
			Comidas[i][coVw] = strval(arrCoords[6]);
			Comidas[i][coType] = strval(arrCoords[7]);
			Comidas[i][coEliminado] = 0;
			
			Comidas[i][coText] = CreateDynamic3DTextLabel(Comidas[i][coName], Naranja, Comidas[i][coX], Comidas[i][coY], Comidas[i][coZ], 20, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, Comidas[i][coVw], Comidas[i][coInt]);
			TotalComidas++;
		}
	}
	printf("Comidas cargadas: %d (MAX: %d)",TotalComidas, MAX_COMIDAS);
}

SaveComidas(id)
{
	format(string, 128, "UPDATE comidas SET Nombre='%s',X=%f,Y=%f,Z=%f,`Int`=%d,Vw=%d,Tipo=%d WHERE id = %d",
		Comidas[id][coName],
		Comidas[id][coX],
		Comidas[id][coY],
		Comidas[id][coZ],
		Comidas[id][coInt],
		Comidas[id][coVw],
		Comidas[id][coType],
		Comidas[id][coId]);
	mysql_query(string);
}

Comidas_OnPlayerCommandText(playerid, cmdtext[])
{	
	new cmd[128], idx, tmp[128], Float:X, Float:Y, Float:Z;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/crearcomida", true) == 0)
	{
		GetPlayerPos(playerid, X,Y,Z);
		new row[64], id;
		format(string, 128, "INSERT INTO comidas (Nombre) VALUES ('Nueva Comida')");
		mysql_query(string);
		
		format(string, 128, "SELECT id FROM comidas WHERE Nombre = 'Nueva Comida'");
		mysql_query(string);
		mysql_store_result();
		mysql_fetch_row(row);
		
		id = strval(row);
		format(Comidas[id][coName], 24, "Nueva Comida");
		Comidas[id][coId] = id;
		Comidas[id][coX] = X;
		Comidas[id][coY] = Y;
		Comidas[id][coZ] = Z;
		Comidas[id][coInt] = GetPlayerInterior(playerid);
		Comidas[id][coVw] = GetPlayerVirtualWorld(playerid);
		Comidas[id][coType] = 1;
		Comidas[id][coEliminado] = 0;
		
		Comidas[id][coText] = CreateDynamic3DTextLabel(Comidas[id][coName], Naranja, Comidas[id][coX], Comidas[id][coY], Comidas[id][coZ], 20, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, Comidas[id][coVw], Comidas[id][coInt]);
		SaveComidas(id);
	}
	
	if(strcmp(cmd, "/editcomida", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /editcomida [Accion]");
			SendClientMessage(playerid, Blanco, "Acciones disponibles: Mover, Nombre, Tipo, Eliminar");
			return 1;
		}
		else
		{
			for(new i; i < MAX_COMIDAS; i++)
			{
				if(PlayerToPoint(2.0, playerid, Comidas[i][coX], Comidas[i][coY], Comidas[i][coZ]) && Comidas[i][coEliminado] == 0 && GetPlayerVirtualWorld(playerid) == Comidas[i][coVw])
				{
					if(strcmp(tmp, "Mover", true) == 0)
					{
						PlayerInfo[playerid][pMoviendoCom] = i;
						SendClientMessage(playerid, Amarillo, "Escribe 'OK' donde quieras poner la comida.");
					}
					else if(strcmp(tmp, "Nombre", true) == 0)
					{
						PlayerInfo[playerid][pEditandoCom] = i;
						SendClientMessage(playerid, Amarillo, "Escribe el nombre para esta comida.");
					}
					else if(strcmp(tmp, "Tipo", true) == 0)
					{
						tmp = strtokex(cmdtext, idx);
						if(!strlen(tmp))
						{
							SendClientMessage(playerid, Blanco, "USO: /editcomida Tipo [1-16]");
							return 1;
						}
						new tipo;
						tipo = strval(tmp);
						if(tipo == 0 || tipo > 16) { SendClientMessage(playerid, Blanco, "USO: /editcomida Tipo [1-16]"); return 1; }
						
						Comidas[i][coType] = tipo;
						SaveComidas(i);
					}
					else if(strcmp(tmp, "Eliminar", true) == 0)
					{
						format(string, 128, "UPDATE comidas SET eliminado = 1 WHERE id = %d", Comidas[i][coId]);
						mysql_query(string);
						DestroyDynamic3DTextLabel(Comidas[i][coText]);
						Comidas[i][coEliminado] = 1;
					}
				}
			}
		}
		return 1;
	}
	return 0;
}

Comidas_OnPlayerText(playerid, text[])
{
	if(PlayerInfo[playerid][pMoviendoCom] != NOEXISTE)
	{
		new com = PlayerInfo[playerid][pMoviendoCom];
		GetPlayerPos(playerid, Comidas[com][coX], Comidas[com][coY], Comidas[com][coZ]);
		SaveComidas(com);
		DestroyDynamic3DTextLabel(Comidas[com][coText]);
		Comidas[com][coText] = CreateDynamic3DTextLabel(Comidas[com][coName], Naranja, Comidas[com][coX], Comidas[com][coY], Comidas[com][coZ], 20, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, Comidas[com][coVw], Comidas[com][coInt]);
		SendClientMessage(playerid, Verde, "Operación completada.");
		PlayerInfo[playerid][pMoviendoCom] = NOEXISTE;
		return 1;
	}
	else if(PlayerInfo[playerid][pEditandoCom] != NOEXISTE)
	{
		new com = PlayerInfo[playerid][pEditandoCom];
		format(Comidas[com][coName], 24, "%s", text);
		SaveComidas(com);
		SendClientMessage(playerid, Verde, "Operación completada.");
		UpdateDynamic3DTextLabelText(Comidas[com][coText], Naranja, Comidas[com][coName]);
		PlayerInfo[playerid][pEditandoCom] = NOEXISTE;
		return 1;
	}
	return 0;
}
