+---------------------------+
¦ How to install JunkBuster ¦
+---------------------------+

>>> To install JunkBuster correctly, you must follow this steps. <<<

Step 1)
	Copy the downloaded folder "JunkBuster" into your folder "scriptfiles".

Step 2)
	Copy "JunkBuster.pwn" into your "filterscripts" folder.
	Add "JunkBuster" to "filterscripts" in your "server.cfg" file, it's probably the best the add it before all other filterscripts.
	Copy all includes in "pawno/includes" into YOUR folder "include" located in
	the folder "pawno".

Step 3)
	Include "JunkBuster.inc" (this is the client script) in ALL your other scripts
	you are running. Just use #include <JunkBuster>. If you do not do this, JunkBuster will not work properly and probably kick/ban innocent players.

Step 4)
	You are using a default admin system with for example levels? Not only RCON?
	You can link this admin system with JunkBuster.
	JunkBuster can't recognize your adminsystem so you must add a function.

	Function (This is only an EXAMPLE!):

		public IsPlayerAdminCall(playerid)
		{
			if(PlayerInfo[playerid][pAdmin] >= 1)
				return 1;
			else
				return 0;
		}

	IMPORTANT:
	This function depends on YOUR admin system. The function above is ONLY FOR GODFATHER so you
	may have to customize this function.
	If you do not add this function admin immunity will only work for RCON-admins!!!
	
	PS:
	JunkBuster is compatible with the default Godfather gamemode! (Tested)
	
Step 5)
	Remove/comment the error lines (#error) at the beginning and the end of the "JunkBuster.pwn" filterscript and compile the script.
	Compile all your other gamemodes/filterscripts and check for errors. If there are any errors or warnings and you
	don't know how to fix it, post them in the JunkBuster topic on forum.sa-mp.com.
	(But there shouldn't be any errors in update 8.)

Step 6)
	Start your gamemode, go ingame and login as RCON-admin. 
	Now type /jbcfg. A dialog will appear.
	Choose the listitem "Set a var". After you have done this
	you will see all JunkBuster variables with the current values. 
	It's the best you choose every variable. Double-click on a variable and a new
	dialog will appear where you can set the variable. There will be a description for every variable, too. 
	Read description for the chosen variable before you change it.
	After you have customized the JunkBuster configuration. Go back to the main dialog (/jbcfg) and 
	choose "Save configuration to file".
	
Step 7)
	Add more bad words and forbidden weapons (or don't). 
	To do this open "BadWords.cfg" in the folder "scriptfiles/JunkBuster".
	Add or remove bad words. Now open "ForbiddenWeapons.cfg" and add or remove weapon IDs. 
	Minigun (38), both rocket launchers (35,36) and flamethrower (37) are forbidden by default.
	Go ingame again, tpye /jbcfg and choose "Load configuration from file" to load the forbidden weapons and bad words.

Step 8) 
	Type ingame /jbcmds for more administration commands.

Step 9)
	JunkBuster is now ready to protect your server from spammers, hackers, cheaters and other noobs.
	If you find a bug, REPORT it in SA-MP forums in the JunkBuster topic.

Step 10)
	Have fun and feel saver.
	