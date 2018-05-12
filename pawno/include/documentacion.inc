#include <a_samp>
#include <globalvars>
#include <colores>
#include <funciones>

Docu_OnInit()
{
	CreateDynamic3DTextLabel("Oficina de Inmigración y Registro Civil", Amarillo, 362.3387,173.5419,1008.3828+0.2, 20);
	CreateDynamic3DTextLabel("Pulsa ENTER para más información", Gris, 362.3387,173.5419,1008.3828, 20);
	
	Tramitacion = CreateMenu("Tramitacion", 2, 200.0, 100.0, 150.0, 50);
	
	AddMenuItem(Tramitacion, 0, "Documentacion");
	AddMenuItem(Tramitacion, 0, "Seguro Social");
	AddMenuItem(Tramitacion, 0, "Antecedentes Policiales");
	AddMenuItem(Tramitacion, 0, "Salir");
	AddMenuItem(Tramitacion, 1, "$500");
	AddMenuItem(Tramitacion, 1, "$500");
	AddMenuItem(Tramitacion, 1, "$25");
	SetMenuColumnHeader(Tramitacion, 0, "Tramite");
	SetMenuColumnHeader(Tramitacion, 1, "Precio");
}

Docu_OnPlayerCommandText(playerid, cmdtext[])
{
	new tmp[128];
	new cmd[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	if(strcmp(cmd,"/mostrar",true) == 0)
	{
		tmp = strtokex(cmdtext,idx);
		if(!strlen(tmp)) { SendClientMessage(playerid,Blanco,"Uso: /mostrar [documentacion/carnet/seguro/licencia/placa] [JugadorID/ParteDelNombre]"); return 1; }
		if(strcmp(tmp, "documentacion", true) == 0)
		{	
			if(PlayerInfo[playerid][pDocumentacion] != 1) { SendClientMessage(playerid, Rojo, "No tienes documentacion legal!"); return 1; }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(string,sizeof(string), "* %s saca la documentación de su cartera y la mira.", pName(playerid));
				if(GetPlayerInterior(playerid) > 0) {
				ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				SendClientMessage(playerid, Amarillo, "Los Santos - Estado de San Andreas");
				SendClientMessage(playerid, AmarilloClaro, "Documento de identificación para residentes");
				format(string,sizeof(string), "Nombre: %s", pName(playerid));
				SendClientMessage(playerid, AmarilloClaro, string);
				format(string,sizeof(string), "Edad: %d", PlayerInfo[playerid][pAge]);
				SendClientMessage(playerid, AmarilloClaro, string);
				new Sexo[20];
				if(PlayerInfo[playerid][pSex] == 1) format(Sexo,sizeof(Sexo),"Masculino"); else format(Sexo,sizeof(Sexo),"Femenino");
				format(string,sizeof(string), "Sexo: %s", Sexo);
				SendClientMessage(playerid, AmarilloClaro, string);
			}
			else
			{
				new player;
				if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
				if(IsPlayerConnected(player))
				{
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					format(string,sizeof(string), "* %s saca la documentación de su cartera y se la muestra a %s.", pName(playerid), pName(player));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, player, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, player, string,Morado, Morado, Morado, Morado, Morado);}
					SendClientMessage(player, Amarillo, "Los Santos - Estado de San Andreas");
					SendClientMessage(player, AmarilloClaro, "Documento de identificación para residentes");
					format(string,sizeof(string), "Nombre: %s", pName(playerid));
					SendClientMessage(player, AmarilloClaro, string);
					format(string,sizeof(string), "Edad: %d", PlayerInfo[playerid][pAge]);
					SendClientMessage(player, AmarilloClaro, string);
					new Sexo[20];
					if(PlayerInfo[playerid][pSex] == 1) format(Sexo,sizeof(Sexo),"Masculino"); else format(Sexo,sizeof(Sexo),"Femenino");
					format(string,sizeof(string), "Sexo: %s", Sexo);
					SendClientMessage(player, AmarilloClaro, string);
				}
			}
			return 1;
		}
		
		if(strcmp(tmp, "placa", true) == 0)
		{	
			if(!IsACop(playerid)) { SendClientMessage(playerid, Rojo, "No eres policia!"); return 1; }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(string,sizeof(string), "* %s saca su placa y la mira.", pName(playerid));
				if(GetPlayerInterior(playerid) > 0) {
				ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				SendClientMessage(playerid, Amarillo, "Departamento de Policía de Los Santos");
				SendClientMessage(playerid, AmarilloClaro, "Placa de policía");
				format(string,sizeof(string), "Número de agente: PD-%d", PlayerInfo[playerid][pSQLID]);
				SendClientMessage(playerid, AmarilloClaro, string);
			}
			else
			{
				new player;
				if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
				if(IsPlayerConnected(player))
				{
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					format(string,sizeof(string), "* %s saca la placa y se la muestra a %s.", pName(playerid), pName(player));
					if(GetPlayerInterior(playerid) > 0) {
					ProxDetector(12.0, player, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, player, string,Morado, Morado, Morado, Morado, Morado);}
					SendClientMessage(player, Amarillo, "Departamento de Policía de Los Santos");
					SendClientMessage(player, AmarilloClaro, "Placa de policía");
					format(string,sizeof(string), "Número de agente: PD-%s", PlayerInfo[playerid][pSQLID]);
					SendClientMessage(player, AmarilloClaro, string);
				}
			}
			return 1;
		}
	
		if(strcmp(tmp, "carnet", true) == 0)
		{	
			if(PlayerInfo[playerid][pSeguroMedico] == 0) { SendClientMessage(playerid, Rojo, "No tienes seguro medico!"); return 1; }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(string,sizeof(string), "* %s saca el carnet médico de su cartera y la mira.", pName(playerid));
				if(GetPlayerInterior(playerid) > 0) {
				ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				SendClientMessage(playerid, Amarillo, "Los Santos - Estado de San Andreas");
				SendClientMessage(playerid, AmarilloClaro, "Seguro de salud privado");
				format(string,sizeof(string), "Nombre: %s", pName(playerid));
				SendClientMessage(playerid, AmarilloClaro, string);
				
				new restante_segundos = PlayerInfo[playerid][pSeguroMedico] - gettime();
				if(restante_segundos > 0)
				{ 
					new restante = (((PlayerInfo[playerid][pSeguroMedico] - gettime()) /60) /60) /24;
					format(string,sizeof(string), "Renovación en: %d días", restante);
				}
				else
				{
					format(string,sizeof(string), "Renovación: DOCUMENTO CADUCADO");
				}
				SendClientMessage(playerid, AmarilloClaro, string);
			}
			else
			{
				new player;
				if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
				if(IsPlayerConnected(player))
				{
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					format(string,sizeof(string), "* %s saca el carnet médico de su cartera y se la muestra a %s.", pName(playerid), pName(player));
					if(GetPlayerInterior(player) > 0) {
					ProxDetector(12.0, player, string,Morado, Morado, Morado, Morado, Morado);}
					else {
					ProxDetector(20.0, player, string,Morado, Morado, Morado, Morado, Morado);}
					SendClientMessage(player, Amarillo, "Los Santos - Estado de San Andreas");
					SendClientMessage(player, AmarilloClaro, "Seguro de salud privado");
					format(string,sizeof(string), "Nombre: %s", pName(playerid));
					SendClientMessage(player, AmarilloClaro, string);
					new restante_segundos = PlayerInfo[playerid][pSeguroMedico] - gettime();
					if(restante_segundos > 0)
					{ 
						new restante = (((PlayerInfo[playerid][pSeguroMedico] - gettime()) /60) /60) /24;
						format(string,sizeof(string), "Renovación en: %d días", restante);
					}
					else
					{
						format(string,sizeof(string), "Renovación: DOCUMENTO CADUCADO");
					}
					SendClientMessage(player, AmarilloClaro, string);
				}
			}
			return 1;
		}
		if(strcmp(tmp, "seguro", true) == 0)
		{
			new coche;
			coche = GetPlayerVehicle(playerid);
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && PlayerHaveKeys(playerid,coche)) { SendClientMessage(playerid, Rojo, "* Debes estar en tu coche."); return 1; }
			if(CarInfo[coche][cSeguro] == 0) { SendClientMessage(playerid, Rojo, "* No tienes seguro para coches."); return 1; }
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(string,sizeof(string), "* %s saca el carnet de seguro para coches de su cartera y la mira.", pName(playerid));
				if(GetPlayerInterior(playerid) > 0) {
				ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
				SendClientMessage(playerid, Amarillo, "Los Santos - Estado de San Andreas");
				SendClientMessage(playerid, AmarilloClaro, "Seguro contra todo daño para coches");
				format(string,sizeof(string), "Matrícula: LS-%d", CarInfo[coche][cCarKey]);
				SendClientMessage(playerid, AmarilloClaro, string);
			}
			else
			{
				new player;
				if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
				if(!IsPlayerConnected(player)) return 1;
				if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
				format(string,sizeof(string), "* %s saca el carnet de seguro de su cartera y se la muestra a %s.", pName(playerid), pName(player));
				if(GetPlayerInterior(player) > 0) {
				ProxDetector(12.0, player, string,Morado, Morado, Morado, Morado, Morado);}
				else {
				ProxDetector(20.0, player, string,Morado, Morado, Morado, Morado, Morado);}
				SendClientMessage(player, Amarillo, "Los Santos - Estado de San Andreas");
				SendClientMessage(player, AmarilloClaro, "Seguro contra todo daño para coches");
				format(string,sizeof(string), "Matrícula: LS-%d", CarInfo[coche][cCarKey]);
				SendClientMessage(player, AmarilloClaro, string);
			}
			return 1;
		}
		if(strcmp(tmp, "licencia", true)==0)
		{
			tmp = strtokex(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, Blanco, "USO: /mostrar licencia [Licencia] [JugadorID/ParteDelNombre]");
				SendClientMessage(playerid, Blanco, "Licencias: Conduccion, Navegacion, Aviacion, Armas.");
				return 1;
			}
			if(strcmp(tmp,"Conduccion",true)==0)
			{
				if(PlayerInfo[playerid][pCarLic]!=1) { SendClientMessage(playerid,RojoIntenso,"No tienes carnet de conducir"); return 1; }
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					if(PlayerInfo[playerid][pCarLic]==1)
					{
						format(string,sizeof(string), "* %s saca el carnet de conducir de su cartera y la mira.", pName(playerid));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(playerid,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(playerid,Amarillo,"Carnet de conducir");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(playerid,AmarilloClaro,string);
						format(string,sizeof(string),"Puntos: %d",PlayerInfo[playerid][pCarLicPoints]);
						SendClientMessage(playerid,AmarilloClaro,string);
					}
				}
				else
				{
					new player;
					if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
					if(!IsPlayerConnected(player)) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no está jugando!"); return 1; }
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					if(PlayerInfo[playerid][pCarLic]==1)
					{
						format(string,sizeof(string), "* %s saca el carnet de conducir de su cartera y se lo muestra a %s.", pName(playerid),pName(player));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(player,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(player,Amarillo,"Carnet de conducir");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(player,AmarilloClaro,string);
						format(string,sizeof(string),"Puntos: %d",PlayerInfo[playerid][pCarLicPoints]);
						SendClientMessage(player,AmarilloClaro,string);
					}
				}
				return 1;
			}
			if(strcmp(tmp,"Navegacion",true)==0)
			{
				if(PlayerInfo[playerid][pBoatLic]==0) { SendClientMessage(playerid,RojoIntenso,"No tienes licencia de navegacion."); return 1; }
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					if(PlayerInfo[playerid][pBoatLic]==1)
					{
						format(string,sizeof(string), "* %s saca la licencia de navegación de su cartera y la mira.", pName(playerid));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(playerid,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(playerid,AmarilloClaro,"Licencia de navegación.");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(playerid,AmarilloClaro,string);
					}
				}
				else
				{
					new player;
					if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
					if(!IsPlayerConnected(player)) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no está jugando!"); return 1; }
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					if(PlayerInfo[playerid][pBoatLic]==1)
					{
						format(string,sizeof(string), "* %s saca la licencia de navegación de su cartera y se lo muestra a %s.", pName(playerid),pName(player));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(player,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(playerid,AmarilloClaro,"Licencia de navegación.");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(player,AmarilloClaro,string);
					}
				}
				return 1;
			}
			if(strcmp(tmp,"Aviacion",true)==0)
			{
				if(PlayerInfo[playerid][pFlyLic]==0) { SendClientMessage(playerid,RojoIntenso,"No tienes licencia de aviacion."); return 1; }
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					if(PlayerInfo[playerid][pFlyLic]==1)
					{
						format(string,sizeof(string), "* %s saca la licencia de aviación de su cartera y la mira.", pName(playerid));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(playerid,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(playerid,AmarilloClaro,"Licencia de aviacion.");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(playerid,AmarilloClaro,string);
					}
				}
				else
				{
					new player;
					if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
					if(!IsPlayerConnected(player)) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no está jugando!"); return 1; }
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					if(PlayerInfo[playerid][pFlyLic]==1)
					{
						format(string,sizeof(string), "* %s saca la licencia de aviación de su cartera y se lo muestra a %s.", pName(playerid),pName(player));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(player,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(playerid,AmarilloClaro,"Licencia de aviacion.");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(player,AmarilloClaro,string);
					}
				}
				return 1;
			}
			if(strcmp(tmp,"Armas",true)==0)
			{
				if(PlayerInfo[playerid][pGunLic]==0) { SendClientMessage(playerid,RojoIntenso,"No tienes licencia de armas."); return 1; }
				tmp = strtokex(cmdtext, idx);
				if(!strlen(tmp))
				{
					if(PlayerInfo[playerid][pGunLic]==1)
					{
						format(string,sizeof(string), "* %s saca la licencia de armas de su cartera y la mira.", pName(playerid));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(playerid,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(playerid,AmarilloClaro,"Licencia de armas.");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(playerid,AmarilloClaro,string);
						format(string,sizeof(string),"Registrada a fecha de %d/%d/2011",PlayerInfo[playerid][pGunLicD],PlayerInfo[playerid][pGunLicM]);
						SendClientMessage(playerid,AmarilloClaro,string);
					}
				}
				else
				{
					new player;
					if(!IsNumeric(tmp)) player = ReturnUser(tmp); else player = strval(tmp);
					if(!IsPlayerConnected(player)) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no está jugando!"); return 1; }
					if(GetDistanceBetweenPlayers(playerid,player) > 7.0) { SendClientMessage(playerid,RojoIntenso,"Ese jugador no esta cerca"); return 1; }
					if(PlayerInfo[playerid][pGunLic]==1)
					{
						format(string,sizeof(string), "* %s saca la licencia de armas de su cartera y la muestra a %s.", pName(playerid),pName(player));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(player,Amarillo,"Los Santos - Estado de San Andreas");
						SendClientMessage(player,AmarilloClaro,"Licencia de armas.");
						format(string,sizeof(string),"Registrado a Nombre de: %s", pName(playerid));
						SendClientMessage(player,AmarilloClaro,string);
						format(string,sizeof(string),"Registrada a fecha de %d/%d/2011",PlayerInfo[playerid][pGunLicD],PlayerInfo[playerid][pGunLicM]);
						SendClientMessage(player,AmarilloClaro,string);
					}
				}
				return 1;
			}
		}
		return 1;
	}
	return 0;
}

Docu_OnPlayerSelectedMenuRow(playerid, row)
{
	new Menu:menuid = GetPlayerMenu(playerid);
	if(menuid == Tramitacion)
	{
		switch(row)
		{
			case 0:
			{
				if(PlayerInfo[playerid][pDocumentacion] == 0)
				{
					if(SafeGetPlayerMoney(playerid) >= 500)
					{
						SafeGivePlayerMoney(playerid, -500);
						format(string, 128, "* %s recoge y guarda su documentación.", pName(playerid));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(playerid, Verde, "Has obtenido tu pasaporte y documentación, ahora estás registrado como ciudadano de Los Santos.");
						PlayerInfo[playerid][pDocumentacion] = 1;
						SaveValue(playerid, "Documentacion", PlayerInfo[playerid][pDocumentacion]);
						HideMenuForPlayer(Tramitacion, playerid);
						TogglePlayerControllable(playerid, 1);
					}
					else
					{
						SendClientMessage(playerid, Rojo, "No tienes dinero suficiente.");
						HideMenuForPlayer(Tramitacion, playerid);
						TogglePlayerControllable(playerid, 1);
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "Ya tienes documentación.");
					HideMenuForPlayer(Tramitacion, playerid);
					TogglePlayerControllable(playerid, 1);
				}
			}
			case 1:
			{
				if(PlayerInfo[playerid][pSeguroMedico] == 0 || gettime() > PlayerInfo[playerid][pSeguroMedico])
				{
					if(SafeGetPlayerMoney(playerid) >= 500)
					{
						SafeGivePlayerMoney(playerid, -500);
						format(string, 128, "* %s recoge y guarda su carné del Seguro Médico.", pName(playerid));
						if(GetPlayerInterior(playerid) > 0) {
						ProxDetector(12.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						else {
						ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);}
						SendClientMessage(playerid, Verde, "Has obtenido tu seguro médico, se deberá renovar cada semana.");
						PlayerInfo[playerid][pSeguroMedico] = gettime() + (7 * 24 * 60 * 60);
						SaveValue(playerid, "SeguroMedico", PlayerInfo[playerid][pSeguroMedico]);
						HideMenuForPlayer(Tramitacion, playerid);
						TogglePlayerControllable(playerid, 1);
					}
					else
					{
						SendClientMessage(playerid, Rojo, "No tienes dinero suficiente.");
						HideMenuForPlayer(Tramitacion, playerid);
						TogglePlayerControllable(playerid, 1);
					}
				}
				else
				{
					SendClientMessage(playerid, Rojo, "Ya tienes Seguro Médico.");
					HideMenuForPlayer(Tramitacion, playerid);
					TogglePlayerControllable(playerid, 1);
				}
			}
			case 2:
			{
				SendClientMessage(playerid, Rojo, "No disponible");
				HideMenuForPlayer(Tramitacion, playerid);
				TogglePlayerControllable(playerid, 1);
			}
			case 3:
			{
				HideMenuForPlayer(Tramitacion, playerid);
				TogglePlayerControllable(playerid, 1);
			}
		}
	}
}