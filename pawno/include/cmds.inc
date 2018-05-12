#include <a_samp>
#include <colores>
#include <globalvars>

Cmds_OnPlayerCommandText(playerid, cmdtext)
{
	new cmd[128];
	new tmp[128];
	new idx;
	cmd = strtokex(cmdtext, idx);
	
	if(strcmp(cmd, "/ayuda", true) == 0)
	{
		tmp = strtokex(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, Blanco, "USO: /ayuda [Tema]");
			SendClientMessage(playerid, Blanco, "Casas, Negocios, Coches, Facciones, Trabajos");
			return 1;
		}
		
		if(strcmp(tmp, "Negocios", true) == 0)
		{
			SendClientMessage(playerid, Amarillo, "Los negocios en este servidor no se compran normalmente.");
			SendClientMessage(playerid, Amarillo, "Para adquirir un negocio deberas estar atento a al foro,");
			SendClientMessage(playerid, Amarillo, "solo los miembros del Staff podrán dar negocios.");
			SendClientMessage(playerid, Gris, "Comandos:");
			SendClientMessage(playerid, Gris, "ENTER - Entrar/Salir del negocio.");
			SendClientMessage(playerid, Gris, "/comprar - Ver la lista de productos que vende el negocio.");
		}
		else if(strcmp(tmp, "Casas", true) == 0)
		{
			SendClientMessage(playerid, Amarillo, "Las casas en este servidor se adquieren segun tu dinero y");
			SendClientMessage(playerid, Amarillo, "nivel. Puedes ponerla en alquiler. El alquiler se cobra de");
			SendClientMessage(playerid, Amarillo, "tu cuenta bancaria a cada hora en punto.");
			SendClientMessage(playerid, Gris, "Comandos:");
			SendClientMessage(playerid, Gris, "ENTER - Entrar/Salir de la casa.");
			SendClientMessage(playerid, Gris, "/alquilar - Alquilar una habitación de una casa.");
		}
	}
}