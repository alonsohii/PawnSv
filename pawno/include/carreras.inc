#include <a_samp>
#include <globalvars>
#include <funciones>
#include <colores>

//==============================================================================
// Track System
//==============================================================================

// DEFINES
#define MAX_RACECHECKPOINTS 64 // Change if you want more room for checkpoints than this
#define MAX_BUILDERS 4 // Change if you want more builderslots than this
#define RACEFILE_VERSION 2 // !!! DO NOT CHANGE !!!

//==============================================================================
// Key State
//==============================================================================
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define PRESSED(%0) \
(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))




// FORWARDS
forward LockRacers();
forward UnlockRacers();
forward LockRacer(i);
forward UnlockRacer(i);
//forward SaveScores(playerid);   				// After race, if new best times have been made, saves them.
forward GetRaceTick(playerid);			// Gets amount of ticks the player was racing
forward ReadyRefresh(playerid);    		// Check the /ready status of players and start the race when ready
forward RaceSound(playerid,sound);      // Plays <sound> for <playerid>
forward BActiveCP(playerid,sele);       // Gives the player selected checkpoint
forward endrace(playerid);                      // Ends the race, whether it ended normally or by /endrace. Cleans the variables.
forward countdown(i);                    // Handles the countdown
//forward strtokex(const string[],&index);
forward SetNextCheckpoint(playerid);    // Gives the next checkpoint for the player during race
forward CheckBestRace(playerid,racetime);   // Check if <racetime> is better than any of the ones in highscore list, and update.
forward SetRaceCheckpoint(playerid,target,next);    // Race-mode checkpoint setter
forward SetBRaceCheckpoint(playerid,target,next);   // Builder-mode checkpoint  setter
forward LoadTimes(playerid,timemode,tmp[]);     // bestlap and bestrace-parameter race loader
forward IsNotAdmin(playerid);          // Is the player admin, if no, return 1 with an error message.
forward GetBuilderSlot(playerid);   // Get next free builderslot, return 0 if none available
forward b(playerid); 		       // Quick and dirty fix for the BuilderSlots
forward Float:Distance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);
forward clearrace(playerid);
forward startrace(playerid);
forward LoadRace(tmp[],playerid);
forward CreateRaceMenus();

forward CountDown(playerid);
//==============================================================================
// Includes
//==============================================================================

#include <streamer>
#include <a_mysql>

native WP_Hash(buffer[], len, const str[]);
#pragma dynamic 145000

// NEWS
new desactivado; //si falla el mysql, los comandos estaran desactivados
new Motos[14] = {522,468,523,461,462,521,581,509,481,463,510,448,471,586};
// General variables
new trackid[MAX_PLAYERS];
new CBuilder[MAX_PLAYERS][MAX_PLAYER_NAME], CRaceName[MAX_PLAYERS][128];        //Creator of the race and the filename, for score changing purposes.
// Racing-related variables
new Ranking;            //Finishing order for prizes
new Countdown[MAX_PLAYERS];          //Countdown timer
new cd[MAX_PLAYERS];                 //Countdown time
new RaceActive[MAX_PLAYERS];         //Is a race active?
new RaceStart[MAX_PLAYERS];          //Has race started?
new Float:RaceCheckpoints[MAX_PLAYERS][MAX_RACECHECKPOINTS][3];  //Current race CP array
new LCurrentCheckpoint[MAX_PLAYERS];                             //Current race array pointer
new CurrentCheckpoint[MAX_PLAYERS];                 //Current race array pointer array :V
new CurrentLap[MAX_PLAYERS];                        //Current lap array
new RaceParticipant[MAX_PLAYERS];                   //Has the player /joined the race
// \_values: 0 - not in race, 1 - joined, 2 - arrived to start CP, 3 - /ready, 4 - racing, 5 - Last CP
new Participants;                                   //Amount of participants
new PlayerVehicles[MAX_PLAYERS];                    //For slapping the player back in their vehicle.
new ORacelaps[MAX_PLAYERS], ORacemode[MAX_PLAYERS];   						//Saves the laps/mode from file in case they aren't changed
new OAirrace[MAX_PLAYERS], Float:OCPsize[MAX_PLAYERS];
new Racelaps[MAX_PLAYERS], Racemode[MAX_PLAYERS];								//If mode/laps has been changed, the new scores won't be saved.
//new ScoreChange;            						//Flag for new best times, so they are saved.
new RaceTick[MAX_PLAYERS];            						    //Startime of the race
//new RaceHealth[MAX_PLAYERS];                                     //Health at race start
new LastLapTick[MAX_PLAYERS];       				//Array that stores the times when players started the lap
new TopRacers[MAX_PLAYERS][11][MAX_PLAYER_NAME]; 					// Stores 5 top scores, 6th isn't
new TopRacerCars[MAX_PLAYERS][11];
new TopRacerTimes[MAX_PLAYERS][11];              					// saved to file, used to simplify
new Float:CPsize[MAX_PLAYERS];                        			// Checkpoint size for the race
new Airrace[MAX_PLAYERS];                       					// Is the race airrace?
new Float:RLenght[MAX_PLAYERS], Float:LLenght[MAX_PLAYERS]; 					//Lap lenght and race lenght
// Building-related variables
new Btrackid[MAX_BUILDERS];
new BCurrentCheckpoints[MAX_BUILDERS];              //Buildrace array pointers
new BSelectedCheckpoint[MAX_BUILDERS];              //Selected checkpoint during building
new RaceBuilders[MAX_PLAYERS];                      //Who is building a race?
new BuilderSlots[MAX_BUILDERS];                     //Stores the racebuilder pids
new Float:BRaceCheckpoints[MAX_BUILDERS][MAX_RACECHECKPOINTS][3]; //Buildrace CP array
new Bracemode[MAX_BUILDERS];
new Blaps[MAX_BUILDERS];
new Float:BCPsize[MAX_BUILDERS];
new BAirrace[MAX_BUILDERS];

new CircuitoActivo[128];
new ModoCircuitoActivo; // 0 entrenar, 1 correr
new TesteandoCircuito[MAX_PLAYERS];


new VehicleNames[212][] = {
{"Landstalker"},{"Bravura"},{"Buffalo"},{"Linerunner"},{"Perrenial"},{"Sentinel"},{"Dumper"},
{"Firetruck"},{"Trashmaster"},{"Stretch"},{"Manana"},{"Infernus"},{"Voodoo"},{"Pony"},{"Mule"},
{"Cheetah"},{"Ambulance"},{"Leviathan"},{"Moonbeam"},{"Esperanto"},{"Taxi"},{"Washington"},
{"Bobcat"},{"Mr Whoopee"},{"BF Injection"},{"Hunter"},{"Premier"},{"Enforcer"},{"Securicar"},
{"Banshee"},{"Predator"},{"Bus"},{"Rhino"},{"Barracks"},{"Hotknife"},{"Trailer 1"},{"Previon"},
{"Coach"},{"Cabbie"},{"Stallion"},{"Rumpo"},{"RC Bandit"},{"Romero"},{"Packer"},{"Monster"},
{"Admiral"},{"Squalo"},{"Seasparrow"},{"Pizzaboy"},{"Tram"},{"Trailer 2"},{"Turismo"},
{"Speeder"},{"Reefer"},{"Tropic"},{"Flatbed"},{"Yankee"},{"Caddy"},{"Solair"},{"Berkley's RC Van"},
{"Skimmer"},{"PCJ-600"},{"Faggio"},{"Freeway"},{"RC Baron"},{"RC Raider"},{"Glendale"},{"Oceanic"},
{"Sanchez"},{"Sparrow"},{"Patriot"},{"Quad"},{"Coastguard"},{"Dinghy"},{"Hermes"},{"Sabre"},
{"Rustler"},{"ZR-350"},{"Walton"},{"Regina"},{"Comet"},{"BMX"},{"Burrito"},{"Camper"},{"Marquis"},
{"Baggage"},{"Dozer"},{"Maverick"},{"News Chopper"},{"Rancher"},{"FBI Rancher"},{"Virgo"},{"Greenwood"},
{"Jetmax"},{"Hotring"},{"Sandking"},{"Blista Compact"},{"Police Maverick"},{"Boxville"},{"Benson"},
{"Mesa"},{"RC Goblin"},{"Hotring Racer A"},{"Hotring Racer B"},{"Bloodring Banger"},{"Rancher"},
{"Super GT"},{"Elegant"},{"Journey"},{"Bike"},{"Mountain Bike"},{"Beagle"},{"Cropdust"},{"Stunt"},
{"Tanker"}, {"Roadtrain"},{"Nebula"},{"Majestic"},{"Buccaneer"},{"Shamal"},{"Hydra"},{"FCR-900"},
{"NRG-500"},{"HPV1000"},{"Cement Truck"},{"Tow Truck"},{"Fortune"},{"Cadrona"},{"FBI Truck"},
{"Willard"},{"Forklift"},{"Tractor"},{"Combine"},{"Feltzer"},{"Remington"},{"Slamvan"},
{"Blade"},{"Freight"},{"Streak"},{"Vortex"},{"Vincent"},{"Bullet"},{"Clover"},{"Sadler"},
{"Firetruck LA"},{"Hustler"},{"Intruder"},{"Primo"},{"Cargobob"},{"Tampa"},{"Sunrise"},{"Merit"},
{"Utility"},{"Nevada"},{"Yosemite"},{"Windsor"},{"Monster A"},{"Monster B"},{"Uranus"},{"Jester"},
{"Sultan"},{"Stratum"},{"Elegy"},{"Raindance"},{"RC Tiger"},{"Flash"},{"Tahoma"},{"Savanna"},
{"Bandito"},{"Freight Flat"},{"Streak Carriage"},{"Kart"},{"Mower"},{"Duneride"},{"Sweeper"},
{"Broadway"},{"Tornado"},{"AT-400"},{"DFT-30"},{"Huntley"},{"Stafford"},{"BF-400"},{"Newsvan"},
{"Tug"},{"Trailer 3"},{"Emperor"},{"Wayfarer"},{"Euros"},{"Hotdog"},{"Club"},{"Freight Carriage"},
{"Trailer 3"},{"Andromada"},{"Dodo"},{"RC Cam"},{"Launch"},{"Police Car (LSPD)"},{"Police Car (SFPD)"},
{"Police Car (LVPD)"},{"Police Ranger"},{"Picador"},{"S.W.A.T. Van"},{"Alpha"},{"Phoenix"},{"Glendale"},
{"Sadler"},{"Luggage Trailer A"},{"Luggage Trailer B"},{"Stair Trailer"},{"Boxville"},{"Farm Plow"},
{"Utility Trailer"}
};
//------------------------------------------------


Carreras_OnGameModeInit()
{
	// INICIO - TRACK SYSTEM
	Ranking=1;
	Participants=0;
	for(new i=0;i<MAX_PLAYERS;i++)
	{
		RaceActive[i]=0;
		LCurrentCheckpoint[i]=0;
	}
	for(new i=0;i<MAX_BUILDERS;i++)
	{
	    BuilderSlots[i]=MAX_PLAYERS+1;
	}
 	// FIN - TRACK SYSTEM


	return 1;
}


//==============================================================================
//-------------------------------------------------
// Player Disconnect
//-------------------------------------------------
//==============================================================================
Carreras_OnPlayerDisconnect(playerid)
{

// TRACK SYSTEM
	if(RaceParticipant[playerid]>=1)
	{
		if(Participants==1) //Last participant leaving, ending race.
		{
			endrace(playerid);
		}
		if(RaceParticipant[playerid] < 3 && RaceStart[playerid] == 0 && !(RaceParticipant[playerid]==3 && RaceStart[playerid] == 1))
		{ //Doing readycheck since someone left, but not if they disconnected during countdown.
		    ReadyRefresh(playerid);
		}
	    Participants--;
	    RaceParticipant[playerid]=0;
	    DisablePlayerRaceCheckpoint(playerid);
	}
	if(RaceBuilders[playerid] != 0)
	{
   	    DisablePlayerRaceCheckpoint(playerid);
	    for(new i;i<BCurrentCheckpoints[b(playerid)];i++)
	    {
	        BRaceCheckpoints[b(playerid)][i][0]=0.0;
   	        BRaceCheckpoints[b(playerid)][i][1]=0.0;
	        BRaceCheckpoints[b(playerid)][i][2]=0.0;
		}
		BuilderSlots[b(playerid)] = MAX_PLAYERS+1;
		RaceBuilders[playerid] = 0;
	}
 	return 1;
}


//==============================================================================
//-------------------------------------------------
// OnPlayerCommandText
//-------------------------------------------------
//==============================================================================
Carreras_OnPlayerCommandText(playerid, cmdtext[])
{

	new cmd[128];
	new tmp[128];
	new idx;

	cmd = strtokex(cmdtext, idx);


//============================
// Track System
//============================
    if (desactivado) SendClientMessage(playerid,Rojo,"Connection error");
    // INICIO COMANDOS PARA CREAR CARRERAS
    if(strcmp(cmd, "/buildhelp", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >= 1)
        {
            SendClientMessage(playerid, Amarillo, "____________________________|- BUILD HELP -|____________________________");
            SendClientMessage(playerid, Amarillo, "/buildrace para crear una nueva  ||  /clearrace para terminar de editar");
            SendClientMessage(playerid, Amarillo, "/editrace para editar una carrera  ||  /saverace [name] para guardar las carreras");
            SendClientMessage(playerid, Amarillo, "/cp para hacer un checkpoint nuevo  ||  /scp para selecionar un checkpoint");
            SendClientMessage(playerid, Amarillo, "/dcp para borrarlo  ||  /mcp para moverlo  ||  /icp para insertar uno");
            SendClientMessage(playerid, Amarillo, "/rcp para remplazarlo por otro nuevo  ||  /cpsize para cambiar el tamaño del checkpoint");
            SendClientMessage(playerid, Amarillo, "/revcps para invertir el orden de los cps  || /renamerace para cambiar el nombre");
            return SendClientMessage(playerid, Amarillo, "/clearcps para borrarlos todos");
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}
    }

    if(strcmp(cmd, "/buildrace", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >= 3)
        {
            if(RaceBuilders[playerid] != 0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are already building a race.");
            }
            else if(RaceParticipant[playerid]>0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are participating in a race, can't build a race.");
            }
            else
            {
                new slot;
                slot=GetBuilderSlot(playerid);
                if(slot == 0)
                {
                    SendClientMessage(playerid, Rojo, "ERROR: No builderslots available!");
                    return 1;
                }
                format(string,sizeof(string),"You are now building a race (Slot: %d)",slot);
                SendClientMessage(playerid, Verde, string);
                RaceBuilders[playerid]=slot;
                BCurrentCheckpoints[b(playerid)]=0;
                Bracemode[b(playerid)]=0;
                Blaps[b(playerid)]=0;
                BAirrace[b(playerid)] = 0;
                BCPsize[b(playerid)] = 8.0;
            }
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/cp", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] != 0 && BCurrentCheckpoints[b(playerid)] < MAX_RACECHECKPOINTS)
            {
                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid,x,y,z);
                format(string,sizeof(string),"Checkpoint %d created: %f,%f,%f.",BCurrentCheckpoints[b(playerid)],x,y,z);
                SendClientMessage(playerid, Verde, string);
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][0]=x;
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][1]=y;
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][2]=z;
                BSelectedCheckpoint[b(playerid)]=BCurrentCheckpoints[b(playerid)];
                SetBRaceCheckpoint(playerid,BCurrentCheckpoints[b(playerid)],-1);
                BCurrentCheckpoints[b(playerid)]++;
            }
            else if(RaceBuilders[playerid] != 0 && BCurrentCheckpoints[b(playerid)] == MAX_RACECHECKPOINTS)
            {
                format(string,sizeof(string),"ERROR: Maximum amount of checkpoints reached (%d).",MAX_RACECHECKPOINTS);
                SendClientMessage(playerid, Rojo, string);
            }
            else
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
            }
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/scp", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            new sele;
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp)) {
                SendClientMessage(playerid, Blanco, "USAGE: /scp [checkpoint]");
                return 1;
            }
            sele = strval(tmp);
            if(RaceBuilders[playerid] != 0)
            {
                if(sele>BCurrentCheckpoints[b(playerid)]-1 || BCurrentCheckpoints[b(playerid)] < 1 || sele < 0)
                {
                    SendClientMessage(playerid, Rojo, "ERROR: Invalid checkpoint!");
                    return 1;
                }
                format(string,sizeof(string),"Selected checkpoint %d.",sele);
                SendClientMessage(playerid, Verde, string);
                BActiveCP(playerid,sele);
                BSelectedCheckpoint[b(playerid)]=sele;
            }
            else
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
            }
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/icp", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            new sele;
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp)) {
                SendClientMessage(playerid, Blanco, "USAGE: /icp [checkpoint]");
                return 1;
            }
            sele = strval(tmp);
            if(RaceBuilders[playerid] != 0)
            {
                if(sele>BCurrentCheckpoints[b(playerid)]-1 || BCurrentCheckpoints[b(playerid)] < 1 || sele < 0)
                {
                    SendClientMessage(playerid, Rojo, "ERROR: Invalid checkpoint!");
                    return 1;
                }
                for(new i=BCurrentCheckpoints[b(playerid)];i>sele;i--)
                {
                    BRaceCheckpoints[b(playerid)][i][0]=BRaceCheckpoints[b(playerid)][i-1][0];
                    BRaceCheckpoints[b(playerid)][i][1]=BRaceCheckpoints[b(playerid)][i-1][1];
                    BRaceCheckpoints[b(playerid)][i][2]=BRaceCheckpoints[b(playerid)][i-1][2];
                }
                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid,x,y,z);
                format(string,sizeof(string),"Checkpoint %d inserted: %f,%f,%f.",sele,x,y,z);
                SendClientMessage(playerid, Verde, string);
                BRaceCheckpoints[b(playerid)][sele][0]=x;
                BRaceCheckpoints[b(playerid)][sele][1]=y;
                BRaceCheckpoints[b(playerid)][sele][2]=z;
                BSelectedCheckpoint[b(playerid)]=sele;
                SetBRaceCheckpoint(playerid,sele,-1);
                BCurrentCheckpoints[b(playerid)]++;
            }
            else
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
            }
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/rcp", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] == 0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
                return 1;
            }
            else if(BCurrentCheckpoints[b(playerid)] < 1)
            {
                SendClientMessage(playerid, Rojo, "ERROR: No checkpoint to replace!");
                return 1;
            }
            new Float:x,Float:y,Float:z;
            GetPlayerPos(playerid,x,y,z);
            format(string,sizeof(string),"Checkpoint %d replaced: %f,%f,%f.",BSelectedCheckpoint[b(playerid)],x,y,z);
            SendClientMessage(playerid, Verde, string);
            BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][0]=x;
            BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][1]=y;
            BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][2]=z;
            BActiveCP(playerid,BSelectedCheckpoint[b(playerid)]);
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/mcp", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] == 0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
                return 1;
            }
            else if(BCurrentCheckpoints[b(playerid)] < 1)
            {
                SendClientMessage(playerid, Rojo, "ERROR: No checkpoint to move!");
                return 1;
            }
            new direction, dir[256];
            dir=strtokex(cmdtext, idx);
            new Float:amount=floatstr(strtokex(cmdtext,idx));
            if(amount == 0.0 || (dir[0] != 'x' && dir[0]!='y' && dir[0]!='z'))
            {
                SendClientMessage(playerid, Blanco, "USAGE: /mcp [x,y or z] [amount]");
                return 1;
            }
            if(dir[0] == 'x') direction=0;
            else if (dir[0] == 'y') direction=1;
            else if (dir[0] == 'z') direction=2;
            BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][direction]=BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][direction]+amount;
            BActiveCP(playerid,BSelectedCheckpoint[b(playerid)]);
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/dcp", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] == 0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
                return 1;
            }
            else if(BCurrentCheckpoints[b(playerid)] < 1)
            {
                SendClientMessage(playerid, Rojo, "ERROR: No checkpoint to delete!");
                return 1;
            }
            for(new i=BSelectedCheckpoint[b(playerid)];i<BCurrentCheckpoints[b(playerid)];i++)
            {
                BRaceCheckpoints[b(playerid)][i][0]=BRaceCheckpoints[b(playerid)][i+1][0];
                BRaceCheckpoints[b(playerid)][i][1]=BRaceCheckpoints[b(playerid)][i+1][1];
                BRaceCheckpoints[b(playerid)][i][2]=BRaceCheckpoints[b(playerid)][i+1][2];
            }
            BCurrentCheckpoints[b(playerid)]--;
            BSelectedCheckpoint[b(playerid)]--;
            if(BCurrentCheckpoints[b(playerid)] < 1)
            {
                DisablePlayerRaceCheckpoint(playerid);
                BSelectedCheckpoint[b(playerid)]=0;
                return 1;
            }
            else if(BSelectedCheckpoint[b(playerid)] < 0)
            {
                BSelectedCheckpoint[b(playerid)]=0;
            }
            BActiveCP(playerid,BSelectedCheckpoint[b(playerid)]);
            SendClientMessage(playerid,Verde,"Checkpoint deleted!");
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }
    if(strcmp(cmd, "/revcps", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] == 0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
                return 1;
            }
            else if(BCurrentCheckpoints[b(playerid)] < 2)
            {
                SendClientMessage(playerid, Rojo, "ERROR: No checkpoints to invert!");
                return 1;
            }
            new Float:temp1,Float:temp2,Float:temp3;
            for(new i=0;i<BCurrentCheckpoints[b(playerid)]/2;i++)
            {
                temp1=BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]-i-1][0];
                temp2=BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]-i-1][1];
                temp3=BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]-i-1][2];
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]-i-1][0]=BRaceCheckpoints[b(playerid)][i][0];
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]-i-1][1]=BRaceCheckpoints[b(playerid)][i][1];
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]-i-1][2]=BRaceCheckpoints[b(playerid)][i][2];
                BRaceCheckpoints[b(playerid)][i][0]=temp1;
                BRaceCheckpoints[b(playerid)][i][1]=temp2;
                BRaceCheckpoints[b(playerid)][i][2]=temp3;
            }
            SendClientMessage(playerid,Verde,"Checkpoints inverted!");
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/clearrace", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] != 0) clearrace(playerid);
            else SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/clearcps", true) == 0 )
    {
         
        if(PlayerInfo[playerid][pAdmin] >=1)
        {
            if(RaceBuilders[playerid] != 0)
            {
                if(BCurrentCheckpoints[b(playerid)]>0) //Clear the old race if there is such.
                {
                    for(new i=0;i<BCurrentCheckpoints[b(playerid)];i++)
                    {
                        BRaceCheckpoints[b(playerid)][i][0]=0.0;
                        BRaceCheckpoints[b(playerid)][i][1]=0.0;
                        BRaceCheckpoints[b(playerid)][i][2]=0.0;
                    }
                    BCurrentCheckpoints[b(playerid)]=0;
                }
            }
            else SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/renamerace", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp))
            {
                SendClientMessage(playerid, Blanco, "USAGE: /renamerace [old name] [new name]");
                return 1;
            }

            new old_name[24],new_name[24];
            new query[128];
            new data[1024];
            new id;
            format(old_name,sizeof(old_name), "%s",tmp);
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp))
            {
                SendClientMessage(playerid, Blanco, "USAGE: /renamerace [old name] [new name]");
                return 1;
            }
            format(new_name,sizeof(new_name), "%s",tmp);
            format(query,sizeof(query),"SELECT id FROM tracks WHERE Name = '%s'",old_name);
            mysql_query(query);
            mysql_store_result();
            if( mysql_num_rows() != 1)
            {
                format(string,sizeof(string), "ERROR: The race \"%s\" doesn't exist.",old_name);
                SendClientMessage(playerid, Rojo, string);
                mysql_free_result();
                return 1;
            }
            mysql_fetch_row(data);
            mysql_free_result();
            id=strval(data);
            for (new i=0;i<MAX_PLAYERS;i++)
            {
                if (trackid[i]==id) endrace(i);
            }
            format(query,sizeof(query),"UPDATE tracks SET Name = '%s' WHERE id = %d",new_name,id);
            mysql_query(query);
            format(string,sizeof(string), "The race \"%s\" now is \"%s\".",old_name,new_name);
            SendClientMessage(playerid, Verde, string);
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/editrace", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] == 0)
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
                return 1;
            }
            if(BCurrentCheckpoints[b(playerid)]>0) //Clear the old race if there is such.
            {
                for(new i=0;i<BCurrentCheckpoints[b(playerid)];i++)
                {
                    BRaceCheckpoints[b(playerid)][i][0]=0.0;
                    BRaceCheckpoints[b(playerid)][i][1]=0.0;
                    BRaceCheckpoints[b(playerid)][i][2]=0.0;
                }
                BCurrentCheckpoints[b(playerid)]=0;
            }
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp))
            {
                SendClientMessage(playerid, Blanco, "USAGE: /editrace [name]");
                return 1;
            }

            new race_name[24];
            new query[128];
            new data[1024];

            format(race_name,sizeof(race_name), "%s",tmp);
            format(query,sizeof(query),"SELECT * FROM tracks WHERE Name = '%s'",race_name);
            mysql_query(query);
            mysql_store_result();
            if( mysql_num_rows() != 1)
            {
                format(string,sizeof(string), "The race \"%s\" doesn't exist.",race_name);
                SendClientMessage(playerid, Rojo, string);
                mysql_free_result();
                return 1;
            }

            mysql_fetch_row(data);
            split(data, arrCoords, '|');
            Btrackid[b(playerid)]=strval(arrCoords[0]);
            Bracemode[b(playerid)]=strval(arrCoords[3]);
            Blaps[b(playerid)]=strval(arrCoords[4]);
            BAirrace[b(playerid)]=strval(arrCoords[5]);
            BCPsize[b(playerid)]=floatstr(arrCoords[6]);
            mysql_free_result();
            new id;
            id=Btrackid[b(playerid)];
            format(query,sizeof(query),"SELECT * FROM `checks` WHERE `trackid` = '%d'",id);
            mysql_query(query);
            mysql_store_result();
            BCurrentCheckpoints[b(playerid)]=-1;
            while(mysql_fetch_row(data))
            {
                BCurrentCheckpoints[b(playerid)]++;
                split(data, arrCoords, '|');
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][0]=floatstr(arrCoords[2]);
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][1]=floatstr(arrCoords[3]);
                BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][2]=floatstr(arrCoords[4]);
            }
            mysql_free_result();
            BCurrentCheckpoints[b(playerid)]++;
            format(string,sizeof(string),"Race \"%s\" has been loaded for editing. (%d checkpoints)",race_name,BCurrentCheckpoints[b(playerid)]);
            SendClientMessage(playerid, Verde,string);
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/saverace", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            if(RaceBuilders[playerid] != 0)
            {
                tmp = strtokex(cmdtext, idx);
                if(!strlen(tmp))
                {
                    SendClientMessage(playerid, Blanco, "USAGE: /saverace [name]");
                    return 1;
                }
                if(BCurrentCheckpoints[b(playerid)] < 2)
                {
                    SendClientMessage(playerid, Rojo, "ERROR: You need atleast 2 checkpoints to save!");
                    return 1;
                }
                new race_name[24];
                new query[256];
                new data[1024];
                new Bcreator[MAX_PLAYER_NAME];
                new id;

                format(race_name,sizeof(race_name), "%s",tmp);
                format(query,sizeof(query),"SELECT id FROM tracks WHERE Name = '%s'",race_name);
                mysql_query(query);
                mysql_store_result();
                if( mysql_num_rows() > 0)
                {
                    mysql_fetch_row(data);
                    id=strval(data);
                    if (id != Btrackid[b(playerid)])
                    {
                        format(string,sizeof(string), "ERROR: Race \"%s\" already exists.",tmp);
                        SendClientMessage(playerid, Rojo, string);
                        mysql_free_result();
                        return 1;
                    }else{
                        format(query,sizeof(query),"UPDATE tracks SET CPSize = %f WHERE id = %d",BCPsize[b(playerid)],Btrackid[b(playerid)]);
                        mysql_query(query);
                        format(query,sizeof(query),"DELETE FROM checks WHERE trackid = %d",Btrackid[b(playerid)]);
                        mysql_query(query);
                        new Float:x,Float:y,Float:z;
                        for(new i = 0; i < BCurrentCheckpoints[b(playerid)];i++)
                        {
                            x=BRaceCheckpoints[b(playerid)][i][0];
                            y=BRaceCheckpoints[b(playerid)][i][1];
                            z=BRaceCheckpoints[b(playerid)][i][2];
                            format(query,sizeof(query),"INSERT INTO checks (trackid, numero, posx, posy, posz) VALUES (%d,%d,%f,%f,%f)",id,i,x,y,z);
                            mysql_query(query);
                        }
                        format(query,sizeof(query),"DELETE FROM records WHERE id = %d",Btrackid[b(playerid)]);
                        mysql_query(query);
                        format(string,sizeof(string),"Your race \"%s\" has been updated.",tmp);
                        SendClientMessage(playerid, Verde, string);
                        mysql_free_result();
                        return 1;
                    }
                }
                mysql_free_result();
                GetPlayerName(playerid, Bcreator, MAX_PLAYER_NAME);
                format(query,sizeof(query),"INSERT INTO tracks (Name, Builder) VALUES('%s','%s')",race_name,Bcreator);
                mysql_query(query);
                format(query,sizeof(query),"SELECT id FROM tracks WHERE Name = '%s'",race_name);
                mysql_query(query);
                mysql_store_result();
                mysql_fetch_row(data);
                id=strval(data);
                mysql_free_result();
                new Float:x,Float:y,Float:z;
                for(new i = 0; i < BCurrentCheckpoints[b(playerid)];i++)
                {
                    x=BRaceCheckpoints[b(playerid)][i][0];
                    y=BRaceCheckpoints[b(playerid)][i][1];
                    z=BRaceCheckpoints[b(playerid)][i][2];
                    format(query,sizeof(query),"INSERT INTO checks (trackid, numero, posx, posy, posz) VALUES (%d,%d,%f,%f,%f)",id,i,x,y,z);
                    mysql_query(query);
                }
                
                format(string,sizeof(string),"Your race \"%s\" has been saved.",tmp);
                SendClientMessage(playerid, Verde, string);

            }
            else
            {
                SendClientMessage(playerid, Rojo, "You are not building a race!");
            }
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }

    if(strcmp(cmd, "/cpsize", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >=3)
        {
            tmp = strtokex(cmdtext,idx);
            if(!(strlen(tmp)) || floatstr(tmp) <= 0.0)
            {
                SendClientMessage(playerid,Blanco,"USAGE: /cpsize [size]");
                return 1;
            }
            if(RaceBuilders[playerid] != 0)
            {
                BCPsize[b(playerid)] = floatstr(tmp);
                format(string,sizeof(string),"Checkpoint size set to %f",floatstr(tmp));
                SendClientMessage(playerid,Verde,string);
                return 1;
            }
            else
            {
                SendClientMessage(playerid, Rojo, "ERROR: You are not building a race!");
            }
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}    }
    // FIN COMANDOS PARA CREAR CARRERAS

    // INICIO DE COMANDOS PARA CORRER
    if(strcmp(cmd, "/top", true) == 0 )
    {
        new modo;
        tmp = strtokex(cmdtext, idx);
        if(!strlen(tmp))
        {
            if(trackid[playerid]==0)
            {
                SendClientMessage(playerid,Rojo,"USO: /top <tramo> [0/1] (0 - entreno / 1 - carrera]");
                return 1;
            }
            else
            {
                modo=ModoCircuitoActivo;
                LeerTiempos(playerid,trackid[playerid],modo);
            }
        }
        else
        {
			if(IsNumeric(tmp))
            {
                if(strval(tmp)<0 || strval(tmp)>2)
                {
                    SendClientMessage(playerid,Rojo,"USO: /top <tramo> [0/1] (0 - entreno / 1 - carrera]");
                    return 1;
                }
                modo = strval(tmp);
                if (trackid[playerid]==0)
                {
                    SendClientMessage(playerid,Rojo,"USO: /top <tramo> [0/1] (0 - entreno / 1 - carrera]");
                    return 1;
                }
                else
                {
                    LeerTiempos(playerid,trackid[playerid],modo);
                }
            }
            else
            {
                new query[128];
                new data[1024];
                new id;

                format(query,sizeof(query),"SELECT id, Name FROM tracks WHERE Name = '%s'",tmp);
                mysql_query(query);
                mysql_store_result();
                if( mysql_num_rows() < 1)
                {
                    SendClientMessage(playerid,Rojo,"ERROR: Ese circuito no existe");
                    mysql_free_result();
                    return 1;
                }
                mysql_fetch_row(data);
                split(data, arrCoords, '|');
                id=strval(arrCoords[0]);
                mysql_free_result();
                format(CRaceName[playerid],128,"%s",arrCoords[1]);
                tmp = strtokex(cmdtext, idx);
                if(IsNumeric(tmp))
                {
                    if(strval(tmp)<0 || strval(tmp)>2)
                    {
                        SendClientMessage(playerid,Rojo,"USO: /top <tramo> [0/1] (0 - entreno / 1 - carrera]");
                        return 1;
                    }
                    modo = strval(tmp);
                    LeerTiempos(playerid,id,modo);
                }
                else 
                {
                    SendClientMessage(playerid,Rojo,"USO: /top <tramo> [0/1] (0 - entreno / 1 - carrera]");
                    return 1;
                }
            }
        }

        if (modo==0) format(string,sizeof(string),"___|- \"%s\" - Entrenamientos -|___",CRaceName[playerid]);
        else if (modo==1) format(string,sizeof(string),"___|- \"%s\" - Carrera -|___",CRaceName[playerid]);
        else if (modo==2) format(string,sizeof(string),"___|- \"%s\" - Testing -|___",CRaceName[playerid]);
        SendClientMessage(playerid,Verde,string);
        for(new i=1;i<9;i++)
        {
            if(TopRacerTimes[playerid][i] == 0)
            {
                format(string,sizeof(string),"%d. Todavia nadie.",i);
                i=11;
            }
            else
            {
               format(string,sizeof(string),"%d. %s - %s - %s",i,BeHuman(TopRacerTimes[playerid][i]),TopRacers[playerid][i],VehicleNames[TopRacerCars[playerid][i]-400]);
            }
            SendClientMessage(playerid,Naranja,string);
        }
        return 1;
    }

    if(strcmp(cmd, "/listatramos", true) == 0 )
    {
         
        new zstring[512];
        new data[512];
        mysql_query("SELECT Name FROM tracks ORDER BY Name ASC");
        mysql_store_result();
        zstring="";
        mysql_fetch_row(data);
        strcat(zstring,data);
        while (mysql_fetch_row(data))
        {
            strcat(zstring,"\n");
            strcat(zstring,data);
        }
        ShowPlayerDialog(playerid, 6767, DIALOG_STYLE_LIST, ">> Lista de tramos disponibles:",zstring,"Aceptar","Cancelar");
        mysql_free_result();
        return 1;
    }

    if(strcmp(cmd, "/tramo", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >= 1)
        {
            Racemode[playerid] = 0; Racelaps[playerid] = 1;
            new fback;
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp))
            {
                SendClientMessage(playerid, Rojo, "USO: /tramo <nombre>");
                return 1;
            }
            if(RaceActive[playerid] == 1)
            {
                endrace(playerid);
        //		SendClientMessage(playerid, Rojo, "ERROR: Ya has iniciado un tramo! Usa /terminar para anularlo.","ERROR: You have already started a track! Type /endtrack to finish it");
            }
            fback=LoadRace(tmp,playerid);
            if(fback == -1) format(string,sizeof(string),"ERROR: No existe ningun tramo con el nombre \"%s\"",tmp);
            else if (fback == -2) format(string,sizeof(string),"ERROR: 003 PLEASE CONTACT WITH ADMIN"); // Race \'%s\' is created with a newer version of YRACE, cannot load.
            if(fback < 0)
            {
                SendClientMessage(playerid,Rojo,string);
                return 1;
            }
            startrace(playerid);
            CurrentCheckpoint[playerid]=0;
            SetRaceCheckpoint(playerid,0,1);
            RaceParticipant[playerid]=1;
            CurrentLap[playerid]=0;
            Participants++;
            TesteandoCircuito[playerid]=1;
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}
    }



    if(strcmp(cmd, "/listo", true) == 0 )
    {
         
        new PState=GetPlayerState(playerid);
        if(RaceParticipant[playerid]==2 && PState == PLAYER_STATE_DRIVER && IsPlayerInRaceCheckpoint(playerid))
        {

            RaceParticipant[playerid]=3;
            ReadyRefresh(playerid);
        }
        else if (PState == PLAYER_STATE_PASSENGER ) SendClientMessage(playerid,Rojo,"ERROR: Tienes que estar conduciendo tu mismo el coche!");
        else if(RaceParticipant[playerid] == 1 || !IsPlayerInRaceCheckpoint(playerid)) SendClientMessage(playerid,Rojo,"ERROR: Tienes que estar en el checkpoint de inicio!.");
        //else SendClientMessage(playerid,Rojo,"ERROR: No has selecionado ningun tramo! Usa /tramo para iniciar uno.");
        return 1;
    }

    if(strcmp(cmd, "/terminar", true) == 0 )
    {
         
        if(RaceActive[playerid]==0)
        {
            SendClientMessage(playerid,Rojo,"No estas corriendo ninguna carrera");
            return 1;
        }
        endrace(playerid);
        return 1;
    }

    if(strcmp(cmd, "/abrircircuito", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >= 1)
        {
            tmp = strtokex(cmdtext, idx);
            if(!strlen(tmp))
            {
                SendClientMessage(playerid, Rojo, "USO: /abrircircuito <nombre> <0/1>  (0 - entrenar / 1- carrera)");
                return 1;
            }
            new tmp2[128];
            tmp2 = strtokex(cmdtext, idx);
            if(!strlen(tmp2))
            {
                SendClientMessage(playerid, Rojo, "USO: /abrircircuito <nombre> <0/1>  (0 - entrenar / 1- carrera)");
                return 1;
            }
            if(strval(tmp2)!=0 && strval(tmp2)!=1 )
            {
                SendClientMessage(playerid, Rojo, "USO: /abrircircuito <nombre> <0/1>  (0 - entrenar / 1- carrera)");
                return 1;
            }
       
            CircuitoActivo=tmp;
            ModoCircuitoActivo=strval(tmp2);
            if (ModoCircuitoActivo==0) format(string,sizeof(string),"Has habilitado el ciruito %s para entrenar",CircuitoActivo);
            else if (ModoCircuitoActivo==1) format(string,sizeof(string),"Has habilitado el ciruito %s para carreras",CircuitoActivo);
            SendClientMessage(playerid,Verde,string);
            return 1;
            
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}
    }
    
    if(strcmp(cmd, "/cerrarcircuito", true) == 0 )
    {
        if(PlayerInfo[playerid][pAdmin] >= 1)
        {
            if(!strlen(CircuitoActivo))
            {
                SendClientMessage(playerid, Rojo, "Ningún circuito abierto)");
                return 1;
            }
            CircuitoActivo="";
            ModoCircuitoActivo=0;
            SendClientMessage(playerid,Verde,"Has cerrado el circuito");
            return 1;
        }
        else {SendClientMessage(playerid,Rojo,"ERROR: Necesitas ser administrador para poder usar este comando"); return 1;}
    }
    
    if( strcmp(cmd, "/entrenar", true) == 0 || strcmp(cmd, "/carrera", true) == 0 )
    {
        if (!strlen(CircuitoActivo))
        {
            if( strcmp(cmd, "/entrenar", true) == 0)
            {
                SendClientMessage(playerid,Rojo,"No hay circuito disponible para entrenar");
                return 1;
            }
            if( strcmp(cmd, "/carrera", true) == 0)
            {
                SendClientMessage(playerid,Rojo,"No hay circuito disponible para correr");
                return 1;
            }
            return 1;
        }
        if( strcmp(cmd, "/entrenar", true) == 0 && ModoCircuitoActivo!=0)
        {
            SendClientMessage(playerid,Rojo,"No hay circuito disponible para entrenar");
            return 1;
        }
        if( strcmp(cmd, "/carrera", true) == 0 && ModoCircuitoActivo!=1)
        {
            SendClientMessage(playerid,Rojo,"No hay circuito disponible para correr");
            return 1;
        }
        Racemode[playerid] = 0; Racelaps[playerid] = 1;
        new fback;
        if(RaceActive[playerid] == 1)
        {
            endrace(playerid);
        }
        fback=LoadRace(CircuitoActivo,playerid);
        if(fback == -1) format(string,sizeof(string),"ERROR: No existe ningun tramo con el nombre \"%s\"",CircuitoActivo);
        //else if (fback == -2) format(string,sizeof(string),"ERROR: 003 PLEASE CONTACT WITH ADMIN"); // Race \'%s\' is created with a newer version of YRACE, cannot load.
        if(fback < 0)
        {
            SendClientMessage(playerid,Rojo,string);
            return 1;
        }
        startrace(playerid);
        CurrentCheckpoint[playerid]=0;
        SetRaceCheckpoint(playerid,0,1);
        RaceParticipant[playerid]=1;
        CurrentLap[playerid]=0;
        Participants++;
        return 1;
    }
    
    
    
    return 0;
}


//==============================================================================
Carreras_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new PState=GetPlayerState(playerid);
    if(RaceActive[playerid] == 1)
    {
        if (PRESSED( KEY_CROUCH ) && IsPlayerInRaceCheckpoint(playerid))
        {
			if(RaceParticipant[playerid]==2 && PState == PLAYER_STATE_DRIVER)
			{
				RaceParticipant[playerid]=3;
				ReadyRefresh(playerid);
                return 1;                
			}
			else if (PState != PLAYER_STATE_DRIVER) SendClientMessage(playerid,Rojo,"ERROR: Tienes que estar conduciendo tu mismo el coche!");
			/*else if(RaceParticipant[playerid] == 1) SendClientMessage(playerid,Rojo,"ERROR: Tienes que estar en el checkpoint de inicio!.","ERROR: You need to be at the start checkpoint!");
        	return 1;*/
    	}
	}
	return 0;
}



//===============================
// TRACK SYSTEM
//===============================
public LockRacers()
{
	for(new i;i<MAX_PLAYERS;i++)
	{
		if(RaceParticipant[i] != 0)
		{
			TogglePlayerControllable(i,0);
			if(IsPlayerInAnyVehicle(i)) PlayerVehicles[i]=GetPlayerVehicleID(i);
			else PlayerVehicles[i]=0;
		}
	}
}
public LockRacer(i)
{
	if(RaceParticipant[i] != 0)
	{
		TogglePlayerControllable(i,0);
		if(IsPlayerInAnyVehicle(i)) PlayerVehicles[i]=GetPlayerVehicleID(i);
		else PlayerVehicles[i]=0;
	}
}

public UnlockRacers()
{
	for(new i;i<MAX_PLAYERS;i++)
	{
		if(RaceParticipant[i]>0)
		{
			TogglePlayerControllable(i,1);
			if(PlayerVehicles[i] != 0)
			{
				PutPlayerInVehicle(i,PlayerVehicles[i],0);
				PlayerVehicles[i]=0;
			}
		}
	}
}

public UnlockRacer(i)
{
	if(RaceParticipant[i]>0)
	{
		TogglePlayerControllable(i,1);
		if(PlayerVehicles[i] != 0)
		{
			PutPlayerInVehicle(i,PlayerVehicles[i],0);
			PlayerVehicles[i]=0;
		}
	}
}

public countdown(i) {
	if(RaceStart[i] == 0)  // Locking players, setting the reward and
	{
		RaceStart[i]=1;
//		LockRacer(i);
	}

	if(cd[i]>0)
	{
		format(string, sizeof(string), "~y~%d",cd[i]);

		if(RaceParticipant[i]>1)
		{
			RaceSound(i,1056);
		    GameTextForPlayer(i,string,1000,3);
	    }

	}
	else if(cd[i]== 0)
	{
		format(string, sizeof(string), "~g~GO ~g~GO ~g~GO!",cd[i]);
	    KillTimer(Countdown[i]);

		if(RaceParticipant[i]>1)
		{
			RaceSound(i,1057);
		    GameTextForPlayer(i,string,3000,3);
			RaceParticipant[i]=4;
			CurrentLap[i]=1;
			if(Racemode[i] == 3) SetRaceCheckpoint(i,LCurrentCheckpoint[i],LCurrentCheckpoint[i]-1);
			else SetRaceCheckpoint(i,0,1);
	    }

		UnlockRacer(i);
		RaceTick[i]=GetTickCount();
		//RepairVehicle(GetPlayerVehicleID(i));
		//SetVehicleHealth( GetPlayerVehicleID(i), 1000.0);
	}
	cd[i]--;
}

public SetNextCheckpoint(playerid)
{
	CurrentCheckpoint[playerid]++;
	if(CurrentCheckpoint[playerid] == LCurrentCheckpoint[playerid])
	{
		SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],-1);
		RaceParticipant[playerid]=6;
	}
	else SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]+1);
}

public SetRaceCheckpoint(playerid,target,next)
{
	if(next == -1 && Airrace[playerid] == 0) SetPlayerRaceCheckpoint(playerid,1,RaceCheckpoints[playerid][target][0],RaceCheckpoints[playerid][target][1],RaceCheckpoints[playerid][target][2],0.0,0.0,0.0,CPsize[playerid]);
	else if(next == -1 && Airrace[playerid] == 1) SetPlayerRaceCheckpoint(playerid,4,RaceCheckpoints[playerid][target][0],RaceCheckpoints[playerid][target][1],RaceCheckpoints[playerid][target][2],0.0,0.0,0.0,CPsize[playerid]);
	else if(Airrace[playerid] == 1) SetPlayerRaceCheckpoint(playerid,3,RaceCheckpoints[playerid][target][0],RaceCheckpoints[playerid][target][1],RaceCheckpoints[playerid][target][2],RaceCheckpoints[playerid][next][0],
							RaceCheckpoints[playerid][next][1],RaceCheckpoints[playerid][next][2],CPsize[playerid]);
	else SetPlayerRaceCheckpoint(playerid,0,RaceCheckpoints[playerid][target][0],RaceCheckpoints[playerid][target][1],RaceCheckpoints[playerid][target][2],RaceCheckpoints[playerid][next][0],RaceCheckpoints[playerid][next][1],
							RaceCheckpoints[playerid][next][2],CPsize[playerid]);
}

public SetBRaceCheckpoint(playerid,target,next)
{
	new ar = BAirrace[b(playerid)];
	if(next == -1 && ar == 0) SetPlayerRaceCheckpoint(playerid,1,BRaceCheckpoints[b(playerid)][target][0],BRaceCheckpoints[b(playerid)][target][1],
								BRaceCheckpoints[b(playerid)][target][2],0.0,0.0,0.0,BCPsize[b(playerid)]);
	else if(next == -1 && ar == 1) SetPlayerRaceCheckpoint(playerid,4,BRaceCheckpoints[b(playerid)][target][0],
				BRaceCheckpoints[b(playerid)][target][1],BRaceCheckpoints[b(playerid)][target][2],0.0,0.0,0.0,
				BCPsize[b(playerid)]);
	else if(ar == 1) SetPlayerRaceCheckpoint(playerid,3,BRaceCheckpoints[b(playerid)][target][0],BRaceCheckpoints[b(playerid)][target][1],BRaceCheckpoints[b(playerid)][target][2],
						BRaceCheckpoints[b(playerid)][next][0],BRaceCheckpoints[b(playerid)][next][1],BRaceCheckpoints[b(playerid)][next][2],BCPsize[b(playerid)]);
	else SetPlayerRaceCheckpoint(playerid,0,BRaceCheckpoints[b(playerid)][target][0],BRaceCheckpoints[b(playerid)][target][1],BRaceCheckpoints[b(playerid)][target][2],
			BRaceCheckpoints[b(playerid)][next][0],BRaceCheckpoints[b(playerid)][next][1],BRaceCheckpoints[b(playerid)][next][2],BCPsize[b(playerid)]);
}

public GetRaceTick(playerid)
{
	new tick, race;
	tick=GetTickCount();
	race=tick-RaceTick[playerid];
	return race;
}

Carreras_OnPlayerEnterRaceCheck(playerid)
{
	if(RaceParticipant[playerid]>=1) // See if the player is participating in a race, allows race builders to do their stuff in peace.
	{
		if(RaceParticipant[playerid] == 6) // Player reaches the checkered flag.
	    {
			new name[MAX_PLAYER_NAME], RaceTime;
			RaceTime=GetRaceTick(playerid);
			new Float:h, penalty;
			GetVehicleHealth ( GetPlayerVehicleID(playerid), h);
            if (h<1000.0)
                penalty = floatround(floatsub(1000.0, h),floatround_round) * 20;
			GetPlayerName(playerid, name, MAX_PLAYER_NAME);
			RaceParticipant[playerid]=0;
			RaceSound(playerid,1139);
			if(Racemode[playerid] == ORacemode[playerid] && ORacelaps[playerid] == Racelaps[playerid])
			{
				new	RaceString[10], racerank;
				RaceString=BeHuman(RaceTime+penalty);
				racerank=CheckBestRace(playerid,RaceTime+penalty);
                if (racerank == 0)
                {
                    format(string,sizeof(string),"~y~META!~n~~n~~w~penalizacion: ~r~%0.3f segundos",floatdiv(penalty,1000));
                    GameTextForPlayer(playerid,string,3000,3);
                    format(string,sizeof(string),">> %s ha completado el tramo \"%s\", tiempo: %s",pName(playerid),CRaceName[playerid],RaceString);
                }
				if(racerank == 1)
				{
				   	format(string,sizeof(string),"~y~NUEVO RECORD!!~n~~n~~w~penalizacion: ~r~%0.3f segundos",floatdiv(penalty,1000));
				    GameTextForPlayer(playerid,string,3000,3);
                    format(string,sizeof(string),">> %s ha completado el tramo \"%s\", con tiempo record: %s",pName(playerid),CRaceName[playerid],RaceString);
				}
                else if (racerank == 2)
				{
					format(string,sizeof(string),"~y~NUEVO RECORD PERSONAL!!~n~~n~~w~penalizacion: ~r~%0.3f segundos",floatdiv(penalty,1000));
				    GameTextForPlayer(playerid,string,3000,3);
                    format(string,sizeof(string),">> %s ha completado el tramo \"%s\", con mejor tiempo personal: %s",pName(playerid),CRaceName[playerid],RaceString);
				}
                ProxDetector(20.0, playerid, string,Morado, Morado, Morado, Morado, Morado);
				GuardarTiempo(playerid,RaceTime+penalty, GetVehicleModel(GetPlayerVehicleID(playerid)));
		    }
			Ranking++;
			Participants--;
	        DisablePlayerRaceCheckpoint(playerid);
	        endrace(playerid);
	    }
	    else if (RaceStart[playerid] == 0 && RaceParticipant[playerid]==1) // Player arrives to the start CP for 1st time
	    {
			SendClientMessage(playerid,Amarillo,"Escribe /listo o presiona el claxon, cuando estes preparado para empezar el tramo!.");
			SendClientMessage(playerid,Amarillo,"NOTA: Tus controles seran bloquados hasta que se de la salida.");
			RaceParticipant[playerid]=2;
	    }
	    else if (RaceStart[playerid]==1) // Otherwise switch to the next race CP.
	    {
			RaceSound(playerid,1138);
			SetNextCheckpoint(playerid);
	    }
	}
	return 1;
}

public endrace(playerid)
{
 	for(new i=0;i<LCurrentCheckpoint[playerid];i++)
	{
	    RaceCheckpoints[playerid][i][0]=0.0;
	    RaceCheckpoints[playerid][i][1]=0.0;
	    RaceCheckpoints[playerid][i][2]=0.0;
	}
	LCurrentCheckpoint[playerid]=0;

	LastLapTick[playerid]=0;
    DisablePlayerRaceCheckpoint(playerid);
	if(RaceParticipant[playerid]==3) //Player was still /ready-locked, unlocking.
	{
			TogglePlayerControllable(playerid,1);
	        if(PlayerVehicles[playerid] != 0)
	        {
	            PutPlayerInVehicle(playerid,PlayerVehicles[playerid],0);
	            PlayerVehicles[playerid]=0;
	        }
	}
    RaceParticipant[playerid]=0;

	RaceActive[playerid]=0;
	RaceStart[playerid]=0;
	Participants=0;
	trackid[playerid]=0;
    TesteandoCircuito[playerid]=0;
}

public BActiveCP(playerid,sele)
{
	if(BCurrentCheckpoints[b(playerid)]-1 == sele) SetBRaceCheckpoint(playerid,sele,-1);
	else SetBRaceCheckpoint(playerid,sele,sele+1);
}

public RaceSound(playerid,sound)
{
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	PlayerPlaySound(playerid,sound,x,y,z);
}

public ReadyRefresh(playerid)
{
	if(RaceActive[playerid]==1) //No countdown if no race is active (could occur with /leave)
	{
		LockRacer(playerid);
		SendClientMessage(playerid,Naranja,"Iniciando la cuenta atras!");
		cd[playerid]=5;
		Countdown[playerid] = SetTimerEx("countdown",1000,1,"%d",playerid);
		RemoveVehicleComponent(GetPlayerVehicleID(playerid), 1010);
	}
}


LeerTiempos(playerid,id,modo)
{
	new query[128];
    new data[1024];


    format(query,sizeof(query),"SELECT Time, Name, Coche FROM records WHERE id = %d AND Modo = %d ORDER BY Time ASC",id,modo);
    mysql_query(query);
	mysql_store_result();
	new c=1;
    while(mysql_fetch_row(data) && c<9)
	{
        split(data, arrCoords, '|');           
        TopRacerTimes[playerid][c]=strval(arrCoords[0]);
        format(TopRacers[playerid][c],24,"%s",arrCoords[1]);
        TopRacerCars[playerid][c]=strval(arrCoords[2]);
        for (new i=1;i<c;i++)
        {
            if (strcmp(TopRacers[playerid][i],TopRacers[playerid][c],true)==0)
            c--;
        }
        c++;
	}
    mysql_free_result();
    while (c<9)
    {
    	TopRacerTimes[playerid][c]=0;
		TopRacers[playerid][c]="";
		c++;
	}
}


GuardarTiempo(playerid,tiempo,coche)
{
	new query[256];
	new name[MAX_PLAYER_NAME];
	new data[128];
	new	oldtime;
    new modo;
	
    GetPlayerName(playerid, name, MAX_PLAYER_NAME);
    if (TesteandoCircuito[playerid]) {modo=2;}
    else {modo=ModoCircuitoActivo;}

    format(query,sizeof(query),"SELECT Time FROM records WHERE id = %d AND Name = '%s' AND Coche = %d AND Modo = %d ORDER BY Time ASC LIMIT 1",trackid[playerid],name,coche,modo);
    mysql_query(query);
	mysql_store_result();
	if( mysql_num_rows() > 0)
	{
	    mysql_fetch_row(data);
		oldtime=strval(data);
        mysql_free_result();
		if (oldtime<tiempo) return 1;
        format(query,sizeof(query),"UPDATE records SET Time = %d WHERE id = %d AND Name = '%s' AND coche = %d AND Modo = %d",tiempo,trackid[playerid],name,coche,modo);
	}
    else
    {
        mysql_free_result();
    	format(query,sizeof(query),"INSERT INTO records (id,Time,Name,Coche,Modo) VALUES(%d,%d,'%s',%d,%d)",trackid[playerid],tiempo,name,coche,modo);
	}
    mysql_query(query);
    return 1;
}


public CheckBestRace(playerid,racetime)
{
  	new query[128];
    new data[1024];
	new time;
    new modo;
	
    if (TesteandoCircuito[playerid]) {modo=2;}
    else {modo=ModoCircuitoActivo;}
	
    format(query,sizeof(query),"SELECT Time FROM records WHERE id = %d AND Modo = %d ORDER BY Time ASC LIMIT 1",trackid[playerid],modo);
	mysql_query(query);
	mysql_store_result();
	if( mysql_num_rows() < 1)
	{
        mysql_free_result();
		return 1;
	}
	mysql_fetch_row(data);
	time=strval(data);
    mysql_free_result();
	if (time>racetime)
	{
		return 1;
	}
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,sizeof(name));
	format(query,sizeof(query),"SELECT Time FROM records WHERE id = %d AND Name = '%s' AND Modo = %d ORDER BY Time ASC LIMIT 1",trackid[playerid],name,modo);
	mysql_query(query);
	mysql_store_result();
	if( mysql_num_rows() < 1)
	{
        mysql_free_result();
		return 2;
	}
	mysql_fetch_row(data);
	time=strval(data);
	if (time>racetime)
	{
        mysql_free_result();
		return 2;
	}
    mysql_free_result();
	return 0;
}

BeHuman(ticks)
{
	new HumanTime[10], minutes, seconds;
	minutes=ticks/60000;
	ticks=ticks-(minutes*60000);
	seconds=ticks/1000;
	ticks=ticks-(seconds*1000);
	format(HumanTime,sizeof(HumanTime),"%d:%02d:%03d",minutes,seconds,ticks);
	return HumanTime;
}

public GetBuilderSlot(playerid)
{
	for(new i;i < MAX_BUILDERS; i++)
	{
	    if(!(BuilderSlots[i] < MAX_PLAYERS+1))
	    {
	        BuilderSlots[i] = playerid;
	        RaceBuilders[playerid] = i+1;
			return i+1;
	    }
	}
	return 0;
}

public b(playerid) return RaceBuilders[playerid]-1;

public Float:Distance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	new Float:temp=floatsqroot((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) + (z1-z2) * (z1-z2));
	if(temp < 0) temp=temp*(-1);
	return temp;
}

public clearrace(playerid)
{
	for(new i=0;i<BCurrentCheckpoints[b(playerid)];i++)
	{
		BRaceCheckpoints[b(playerid)][i][0]=0.0;
		BRaceCheckpoints[b(playerid)][i][1]=0.0;
		BRaceCheckpoints[b(playerid)][i][2]=0.0;
	}
	BCurrentCheckpoints[b(playerid)]=0;
	DisablePlayerRaceCheckpoint(playerid);
	SendClientMessage(playerid, Verde, "Your race has been cleared! Use /buildrace to start a new one.");
	BuilderSlots[b(playerid)] = MAX_PLAYERS+1;
	Btrackid[b(playerid)]=0;
	RaceBuilders[playerid]=0;
}

public startrace(playerid)
{
	format(string,sizeof(string),">> Has elegido el tramo \"%s\". Longitud: %0.2fkm", CRaceName[playerid], RLenght[playerid]/1000);
	SendClientMessage(playerid,Naranja,string);
	RaceStart[playerid]=0;
	RaceActive[playerid]=1;
//	ScoreChange=0;
	Ranking=1;
}

public LoadRace(tmp[],playerid)
{
	new race_name[24];
    new query[128];
    new data[1024];

    format(race_name,sizeof(race_name), "%s",tmp);
    format(query,sizeof(query),"SELECT * FROM tracks WHERE Name = '%s'",race_name);
    mysql_query(query);
	mysql_store_result();
	if( mysql_num_rows() != 1)
	{
        mysql_free_result();
		return -1;
	}

    mysql_fetch_row(data);
    split(data, arrCoords, '|');
	trackid[playerid]=strval(arrCoords[0]);
	format(CRaceName[playerid],128,"%s",arrCoords[1]);
	format(CBuilder[playerid],24,"%s",arrCoords[2]);
	Racemode[playerid]=strval(arrCoords[3]); ORacemode[playerid]=Racemode[playerid];
	Racelaps[playerid]=strval(arrCoords[4]); ORacelaps[playerid]=Racelaps[playerid];
	Airrace[playerid]=strval(arrCoords[5]); OAirrace[playerid]= Airrace[playerid];
    CPsize[playerid]=floatstr(arrCoords[6]); OCPsize[playerid]=CPsize[playerid];
    mysql_free_result();
    
	new id;
	id=trackid[playerid];
    format(query,sizeof(query),"SELECT * FROM `checks` WHERE `trackid` = '%d'",id);
    mysql_query(query);
    mysql_store_result();
	new lines = mysql_num_rows();
    if( lines == 0)
	{
        mysql_free_result();
		return -2;
	}
	new i;
	LCurrentCheckpoint[playerid]=-1; RLenght[playerid]=0; LLenght[playerid]=0;
    while(mysql_fetch_row(data))
	{
        split(data, arrCoords, '|');
		LCurrentCheckpoint[playerid]++;
		i=strval(arrCoords[1]);
	    RaceCheckpoints[playerid][i][0]=floatstr(arrCoords[2]);
		RaceCheckpoints[playerid][i][1]=floatstr(arrCoords[3]);
		RaceCheckpoints[playerid][i][2]=floatstr(arrCoords[4]);
		if(LCurrentCheckpoint[playerid] >= 1)
		{
			RLenght[playerid]+=Distance(RaceCheckpoints[playerid][LCurrentCheckpoint[playerid]][0],RaceCheckpoints[playerid][LCurrentCheckpoint[playerid]][1],
							RaceCheckpoints[playerid][LCurrentCheckpoint[playerid]][2],RaceCheckpoints[playerid][LCurrentCheckpoint[playerid]-1][0],
							RaceCheckpoints[playerid][LCurrentCheckpoint[playerid]-1][1],RaceCheckpoints[playerid][LCurrentCheckpoint[playerid]-1][2]);
		}

	}
    mysql_free_result();
    return 1;

}


stock IsMoto(id)
{
	for(new i = 0; i < 14; i++)
	{
		if (Motos[i]==id) return 1;
	}
	return 0;
}

stock GetVehicleModelIDFromName(vname[])
{
	for(new i = 0; i < 211; i++)
	{
	if ( strfind(VehicleNames[i], vname, true) != -1 )
	return i + 400;
	}
	return -1;
}
