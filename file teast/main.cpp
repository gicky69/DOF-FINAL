#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>

using namespace std;

// DATA STRUCTURE //
struct STATS {
	int ATK; //Increases Damage
	int DEF; //Decreases Damage Taken
	int SPD;
	int HP;
	int LUK;
};

struct WEAPON {
	int dmg; //Damage Modifier
	int acc; //Accuracy Modifier
	int weight; //Lack of ATK means less SPD
	int crit; //Critical Chance Modifier
	int critdmg; //Critical Damage Modifier
};

struct Enemy {

	//--- General ---

	//Enemy Profile
	string enemyname;
	string art[12];

	//Enemy Status
	int HEALTH;
	string pweap;
	STATS stat;

	//Buffs

	//Debuffs

	//--- Enemy Specific ---

	//Flavor text
	int lhdmg; // last hit damage

	//Enemy drops
	int expdrop;
	int wtokendrop;
	int coindrop;

	//Weapon stats
	WEAPON weapon;

	//Enemy Abilities

};

struct Player {

	// --- General ---

	//Player Profile
	string playername;
	int sslot;
	string spweapon;

	//Player Status
	int php;
	int l;
	int dl;
	int expgain;

	// --- Player Specific ---

	//Inventory
	int coins;
	int wtokens;
	string pweapon;

	double weapdmg;

	//Skills
	int sp;
	STATS sk;
    int abpt1;
    int abpt2;
    int abpt3;
    int abpt4;

    int ab1;
    int ab2;
    int ab3;
    int ab4;
	// --- During Fight ---

	//Cooldown
	int wac1;
	int wac2;
	int wac3;
	int wac4;

	//Chance
	float extcritch; //increases crit chance, when crit fails
	float extdodch; //increases dodge chance, when dodge fails
	float exthitch; //increases hit chance, when attack fails

	//Weapon Ability Based
	int aDMG;
	int aACC;
	int aCritch;
	int aCritdmg;

    bool napilinaT;
};

// DATA STRUCTURE //

// Initializing Data to Player
Player initializePlayer() {
	Player MyPlayer;
	// ECONOMY
	MyPlayer.coins = 100;
	MyPlayer.wtokens = 0;

	MyPlayer.dl = 1;
	MyPlayer.sp = 5;
	MyPlayer.l = 1;
	MyPlayer.expgain = 0;

	// Initialize Player Items
	MyPlayer.spweapon = "Short Sword";
	MyPlayer.pweapon = "Short Sword";

	MyPlayer.weapdmg = 0;

	// Initialize Player Skills
	MyPlayer.sk.ATK = 1;
	MyPlayer.sk.DEF = 1;
	MyPlayer.sk.SPD = 1;
	MyPlayer.sk.HP = 1;
	MyPlayer.sk.LUK = 1;

	MyPlayer.php = 100 + (10 * MyPlayer.sk.HP);

	// Special stats
	MyPlayer.abpt1 = 0;
	MyPlayer.abpt2 = 0;
	MyPlayer.abpt3 = 0;
	MyPlayer.abpt4 = 0;

    // Player Abilities
    MyPlayer.ab1 = MyPlayer.abpt1 * 2; // +HP every door
    MyPlayer.ab2 = MyPlayer.abpt2 *2; // +HP every kill
    if (MyPlayer.abpt3 >= 1){
        MyPlayer.ab3 = (MyPlayer.abpt3*10) + 5; // +HP stat
    }
    else {
        MyPlayer.ab3 = 0;
    }
    MyPlayer.ab4 = MyPlayer.abpt4 * 4; // +COINS every door

	// Weapon Cooldown
	MyPlayer.wac1 = 0;
	MyPlayer.wac2 = 0;
	MyPlayer.wac3 = 0;
	MyPlayer.wac4 = 0;

	// Player Chance
	MyPlayer.extcritch = 0; // Extra Crit Chance
	MyPlayer.extdodch = 0;
	MyPlayer.exthitch = 0;

	// Weapon Ability Based
	MyPlayer.aDMG = 0;
	MyPlayer.aACC = 0;
	MyPlayer.aCritch = 0;
	MyPlayer.aCritdmg = 0;

    MyPlayer.napilinaT = false;
	return MyPlayer;
}

// Initializing Data to Enemy
Enemy initializeEnemy(string enemy) {
	Enemy MyEnemy;

	//Specific Enemy Initialization
	if (enemy == "Huge Spider") {
		MyEnemy.stat.ATK = 3;
		MyEnemy.stat.DEF = 1;
		MyEnemy.stat.SPD = 3;
		MyEnemy.stat.HP = 1;
		MyEnemy.stat.LUK = 1;

		MyEnemy.weapon.acc = 60;
		MyEnemy.weapon.critdmg = 200;

		MyEnemy.expdrop = 10;
		MyEnemy.wtokendrop = 20;
		MyEnemy.coindrop = 10;

		//Ascii Art of Huge Spider

		//Art by Max Strandberg
		MyEnemy.art[0] = "";
		MyEnemy.art[1] = "";
		MyEnemy.art[2] = "";
		MyEnemy.art[3] = "";
		MyEnemy.art[4] = "  / _ \\ ";
		MyEnemy.art[5] = "\\_\\(_)/_/";
		MyEnemy.art[6] = " _//o\\\\_";
		MyEnemy.art[7] = "";
		MyEnemy.art[8] = "";
		MyEnemy.art[9] = "";
	}
	if (enemy == "Snek") {
		// Snek Stat
		MyEnemy.stat.ATK = 3;
		MyEnemy.stat.DEF = 2;
		MyEnemy.stat.SPD = 2;
		MyEnemy.stat.HP = 1;
		MyEnemy.stat.LUK = 1;

		MyEnemy.weapon.acc = 60;
		MyEnemy.weapon.critdmg = 150;

		MyEnemy.expdrop = 10;
		MyEnemy.wtokendrop = 15;
		MyEnemy.coindrop = 10;
		//
		//Ascii Art
		MyEnemy.art[0] = "";
		MyEnemy.art[1] = "";
		MyEnemy.art[2] = "";
		MyEnemy.art[3] = "             ____";
		MyEnemy.art[4] = "            / . .\\";
		MyEnemy.art[5] = "            \\  ---<";
		MyEnemy.art[6] = "             \\  /";
		MyEnemy.art[7] = "   __________/ /";
		MyEnemy.art[8] = "-=:___________/";
		MyEnemy.art[9] = "";
		MyEnemy.art[10] = "";
		MyEnemy.art[11] = "";
	}
	if (enemy == "Slime") {
		MyEnemy.stat.ATK = 3;
		MyEnemy.stat.DEF = 1;
		MyEnemy.stat.SPD = -1;
		MyEnemy.stat.HP = 4;
		MyEnemy.stat.LUK = 1;

		MyEnemy.weapon.acc = 55;
		MyEnemy.weapon.critdmg = 200;

		MyEnemy.expdrop = 10;
		MyEnemy.wtokendrop = 13;
		MyEnemy.coindrop = 5;

		MyEnemy.art[0] = "";
		MyEnemy.art[1] = "";
		MyEnemy.art[2] = "";
		MyEnemy.art[3] = "";
		MyEnemy.art[4] = "     ____";
		MyEnemy.art[5] = "    /    \\";
		MyEnemy.art[6] = "  /  .  .  \\";
		MyEnemy.art[7] = " |   \\__/   |";
		MyEnemy.art[8] = "  \\________/";
		MyEnemy.art[9] = "";
		MyEnemy.art[10] = "";
		MyEnemy.art[11] = "";
	}
	if (enemy == "Huge Bat") {
		MyEnemy.stat.ATK = 5;
		MyEnemy.stat.DEF = 2;
		MyEnemy.stat.SPD = 2;
		MyEnemy.stat.HP = 2;
		MyEnemy.stat.LUK = 3;

		MyEnemy.weapon.acc = 90;
		MyEnemy.weapon.critdmg = 200;

		MyEnemy.expdrop = 15;
		MyEnemy.wtokendrop = 25;
		MyEnemy.coindrop = 10;

		MyEnemy.art[0] = "";
		MyEnemy.art[1] = "";
		MyEnemy.art[2] = "";
		MyEnemy.art[3] = "";
		MyEnemy.art[4] = "  (_    ,_,    _)";
		MyEnemy.art[5] = "  / `'--) (--'` \\";
		MyEnemy.art[6] = " /  _,-'\\_/'-,_  \\";
		MyEnemy.art[7] = "/.-'     \"     '-.\\";
		MyEnemy.art[8] = "";
		MyEnemy.art[9] = "";
		MyEnemy.art[10] = "";
		MyEnemy.art[11] = "";
	}

	MyEnemy.HEALTH = 100 + (10 * MyEnemy.stat.HP);
	MyEnemy.enemyname = enemy;
	MyEnemy.lhdmg = 0;

    if (enemy == "Phoenix"){
		MyEnemy.stat.ATK = 15;
		MyEnemy.stat.DEF = 10;
		MyEnemy.stat.SPD = 8;
		MyEnemy.stat.HP = 10;
		MyEnemy.stat.LUK = 5;

		MyEnemy.weapon.acc = 90;
		MyEnemy.weapon.critdmg = 350;

		MyEnemy.expdrop = 100;
		MyEnemy.wtokendrop = 40;
		MyEnemy.coindrop = 200;


		MyEnemy.art[0] = "";
		MyEnemy.art[1] = "      __             __";
		MyEnemy.art[2] = "   .-'.'     .-.     '.'-.";
		MyEnemy.art[3] = " .'.((      ( ^ `>     )).'.";
		MyEnemy.art[4] = "/`'- \\'._____\\ (_____.'/ -'`\\";
		MyEnemy.art[5] = "|-''`.'------' '------'.`''-|";
		MyEnemy.art[6] = "|.-'`.'.'.`/ | | \\`.'.'.`'-.|";
		MyEnemy.art[7] = " \\ .' . /  | | | |  \\ . '. /";
		MyEnemy.art[8] = "  '._. :  _|_| |_|_  : ._.'";
		MyEnemy.art[9] = "     ````` /T\"Y\"T\\ `````";
		MyEnemy.art[10] = "          / | | | \\";
		MyEnemy.art[11] = "         `'`'`'`'`'`";

        MyEnemy.HEALTH = 300 + (10 * MyEnemy.stat.HP);
        MyEnemy.enemyname = enemy;
        MyEnemy.lhdmg = 0;
	}
	if (enemy == "Centaur"){
        MyEnemy.stat.ATK = 25;
		MyEnemy.stat.DEF = 10;
		MyEnemy.stat.SPD = 10;
		MyEnemy.stat.HP = 12;
		MyEnemy.stat.LUK = 4;

		MyEnemy.weapon.acc = 90;
		MyEnemy.weapon.critdmg = 300;

		MyEnemy.expdrop = 1000;
		MyEnemy.wtokendrop = 40;
		MyEnemy.coindrop = 200;

		MyEnemy.art[0] = "";
		MyEnemy.art[1] = "";
		MyEnemy.art[2] = " <=======]}======";
		MyEnemy.art[3] = "    --.   /|";
		MyEnemy.art[4] = "   _\\\"/_.\'/";
		MyEnemy.art[5] = " .\'._._,.\'";
		MyEnemy.art[6] = " :/ \\{}/";
		MyEnemy.art[7] = "(  /--\',----._";
		MyEnemy.art[8] = "    |          \\\\";
		MyEnemy.art[9] = "   : /-\\ .\'-\'\\ / |";
		MyEnemy.art[10]= " \\, ||    \\|";
		MyEnemy.art[11]= "     \\/ ||    ||";

		MyEnemy.HEALTH = 700 + (10 * MyEnemy.stat.HP);
        MyEnemy.enemyname = enemy;
        MyEnemy.lhdmg = 0;
	}

	return MyEnemy;
}

// Functions
// Menus
void Menu();
void About();
void Credits();
void Guide();
void NewGameandLoadGame(Player& p);
bool SaveAndLoad(Player& p, bool save);

// Start
void startmenu(Player& p);
void shop(Player& p);
void weaponshop(Player& p);
void upgradeShop(Player& p);
void vault(Player& p);
void upgrading(Player& p);

// Gameplay
void skilldraw(Player p, char picks);
void skills(Player& p, bool save);
void doors(Player& p);
void showstats(Player& p);
void showinventory(Player& p);

void gameplay(Player& p, bool doorpPicked);

void drawEnemyFight(Player& p, Enemy& enemy, string type);
void BossBehavior(Player& p, Enemy& enemy);

void PlayerAttack(Player& p, Enemy& enemy);


int PlayerWeapon(Player& p, Enemy& enemy, string attr);
string RandomWeapDrop(int RandomWeap);
// Gameplay
void armorshop(Player& p);
void drawarmorselec(Player& p, char s);
void upgradeShop(Player& p);
void enemyFight(Player& p);
void RestPlace(Player& p);
void TreasurePlace(Player& p);

// Boss Encounter
void bossEncounter(Player& p);
void BossFight(Player& p);

int main() {

	cout << "\n\n";
	cout << "\t\t\t           ., ;'..                                                    " << endl;
	cout << "\t\t\t            ., ;'..                                                   " << endl;
	cout << "\t\t\t          .okOk;.''                                                   " << endl;
	cout << "\t\t\t         .:xdxkl.'o:                           __________            " << endl;
	cout << "\t\t\t       .;odocxNx. .;,                         /          \\           " << endl;
	cout << "\t\t\t      ;dxoclo0Wd.  .,;.                      /            \\          " << endl;
	cout << "\t\t\t    .'ckxokXWMMNOkk;,;,'                    |              |          " << endl;
	cout << "\t\t\t  .:occ0NNMMMXkOXXN0dc,''...                |              |          " << endl;
	cout << "\t\t\t  .dOdxKKKWMNkoxOOKXOdc,',,,.               |              |          " << endl;
	cout << "\t\t\t  'occO0:'oK0xxOOO00Ol;;loldl.              |              |          " << endl;
	cout << "\t\t\t  ,l;l0Ol:d0kdO00k:'dk;'..':d;              |              |          " << endl;
	cout << "\t\t\t  .odo:..:KKdxxlol'.k0c,,. .:.              |              |          " << endl;
	cout << "\t\t\t   ;::;. .,,,oddd::d0klccc:.                |              |          " << endl;
	cout << "\t\t\t   ,lll.     c0OdccdOc'',okxo'  ____________|______________|__________" << endl;
	cout << "\t\t\t    ',.     'dxkxk00kc''cooOXx;.                                      " << endl;
	cout << "\t\t\t          .:o;..:dkO: ..;x0kdl;:'                                     " << endl;
	cout << "\t\t\t         'l;... .lxo.    ,oc'...;,.                                   " << endl;
	cout << "\t\t\t       .',. .lOkc:dc      .':lo:;:c;                                  " << endl;
	cout << "\t\t\t      ',.    ,kk;,:.         .';:oodd;                                " << endl;
	cout << "\t\t\t     'l,.   .;ldxl.              ..;:'                                " << endl;
	cout << "\t\t\t     .kKkl:lkd:cl.                                                    " << endl;
	cout << "\t\t\t     .ll:,'c0Odo'                                                     " << endl;
	cout << "\t\t\t    .cc....cOdo,                                                      " << endl;
	cout << "\t\t\t                 Game Made by Carl Andrew Villanueva                  " << endl;
	cout << "\n\n";
	system("pause");
	system("cls");

	cout << "\n\n\n\n\n\t\t     o============================================================================o\n\n";
	cout << "\t\t\t       ____                                __   _____     _\n";
	cout << "\t\t\t      |  _ \\  ___   ___  _ __ ___    ___  / _| |  ___|_ _| |_ ___\n";
	cout << "\t\t\t      | | | |/ _ \\ / _ \\| '__/ __|  / _ \\| |_  | |_ / _` | __/ _ \\ \n";
	cout << "\t\t\t      | |_| | (_) | (_) | |  \\__ \\ | (_) |  _| |  _| (_| | ||  __/\n";
	cout << "\t\t\t      |____/ \\___/ \\___/|_|  |___/  \\___/|_|   |_|  \\__,_|\\__\\___|\n";
	cout << "\n\n\t\t     o============================================================================o\n\n";
	cout << "\n";

	system("pause");
	Menu();
}

void NewGameandLoadGame(Player& p) {
	char saveq[20] = "";
	bool save = false;
	char sslot[20];

	string slot1txt;
	string slot2txt;
	string slot3txt;
	//Slot1
	{
        ifstream infile("slot1.txt");
		if (infile.is_open()) {
            string line;
            char newLine[20];
            char saved_v[1];
            char temp[20];
            getline(infile, line);
            strcpy(newLine, line.c_str());
            strcpy(saved_v, strtok(newLine, ":"));

            if (strcmp(saved_v, "1")==0){
                strcpy(temp, strtok(NULL, ":"));
                slot1txt = temp;
            }
            else {
                slot1txt = "Empty Slot";
            }
		}
		else
		{
			slot1txt = "Empty Slot";
		}
	}

	//Slot2
	{
		ifstream infile("slot2.txt");
		if (infile.is_open()) {
			string line;
            char newLine[20];
            char saved_v[1];
            char temp[20];
            getline(infile, line);
            strcpy(newLine, line.c_str());
            strcpy(saved_v, strtok(newLine, ":"));

            if (strcmp(saved_v, "1")==0){
                strcpy(temp, strtok(NULL, ":"));
                slot2txt = temp;
            }
            else {
                slot2txt = "Empty Slot";
            }
		}
		else
		{
			slot2txt = "Empty Slot";
		}
	}

	//Slot3
	{
		ifstream infile("slot3.txt");
		if (infile.is_open()) {
			string line;
            char newLine[20];
            char saved_v[1];
            char temp[20];
            getline(infile, line);
            strcpy(newLine, line.c_str());
            strcpy(saved_v, strtok(newLine, ":"));

            if (strcmp(saved_v, "1")==0){
                strcpy(temp, strtok(NULL, ":"));
                slot3txt = temp;
            }
            else {
                slot3txt = "Empty Slot";
            }
		}
		else
		{
			slot3txt = "Empty Slot";
		}
	}

	while (true) {
		system("cls");
		cout << "\n\n\n\n\t\t\t\t \t\t\t      New Game or Load Game" << endl;
		cout << "\n\t\t            New Game [N] or Load Game [L]\n" << endl;
		cout << "\n\t >> ";
		cin.getline(saveq, sizeof(saveq));

		switch (saveq[0]) {
		case 'N':
		case 'n':
			do {
				system("cls");
				save = true;
				cout << "\n\n\n\n\n";
				cout << "\t\t     o============================================================================o\n" << endl;
				cout << "\n\n";
				cout << "\t\t                                      New Game" << endl;
				cout << "\n";
				cout << "\t\t                                > [0] " << slot1txt << endl;
				cout << "\t\t                                > [1] " << slot2txt << endl;
				cout << "\t\t                                > [2] " << slot3txt << endl;
				cout << "\n\n";
				cout << "\t\t     o============================================================================o\n" << endl;
				cout << "\t\t Select a save slot: ";
				cin.getline(sslot, sizeof(sslot));

				if (strlen(sslot) != 1 || sslot == "") {
					cout << "\t\tInvalid input, please try again..." << endl;
					cout << "\t\t"; system("pause");
				}

				//Write a playername
				else {
					do {
                        system("cls");
                        cout << "\n\n\t\t Name [20 Characters]: ";
                        cin >> p.playername;
                        if (p.playername.size() > 20){
                            cout << "\t\t Exceeded 20 Characters..." << endl;
                            cout << "\t\t Please try again."<< endl;
                            cout << "\t\t "; system("pause");
                            continue;
                        }
                        else {
                            bool namevalid = true;

                            for (int i=0;i<p.playername.size();i++){
                                if (!isalpha(p.playername[i])){
                                    namevalid = false;
                                    cout << "\t\t Invalid name. Please try again.." << endl;
                                    cout << "\t\t "; system("pause");
                                }
                            }
                            if (namevalid) {
                                cout << "\n\n\t\t Successfully created a character!" << endl;
                                cout << "\t\t "; system("pause");
                                break;
                            }
                            else {
                                continue;
                            }
                        }
					}
					while (true);
					p.sslot = atoi(sslot);
					skills(p, save);
					break;
				}
			} while (true);

		case 'L':
		case 'l':
			do {
				system("cls");
				cout << "\n\n\n\n\n";
				cout << "\t\t     o============================================================================o\n" << endl;
				cout << "\n\n";
				cout << "\t\t                                      Load Game" << endl;
				cout << "\n";
				cout << "\t\t                                > [0] " << slot1txt << endl;
				cout << "\t\t                                > [1] " << slot2txt << endl;
				cout << "\t\t                                > [2] " << slot3txt << endl;
				cout << "\n\n";
				cout << "\t\t     o============================================================================o\n" << endl;

				cout << "\t\t Select a save slot: ";
				cin.getline(sslot, sizeof(sslot));

				if (strlen(sslot) != 1 || sslot == "") {
					cout << "\t\tInvalid input, please try again..." << endl;
					cout << "\t\t"; system("pause");
				}
				else {
					p.sslot = atoi(sslot);
					bool playable = SaveAndLoad(p, save);
					if (playable)
					{
						startmenu(p);
						break;
					}
					else
					{
						cout << endl;
						cout << "Save file does not exist." << endl;
						system("pause");
					}
				}
			} while (true);
		}
		//break;
	}
}

void Menu() {
	Player p = initializePlayer();
	bool valid = false;

	do {
		char query[20] = "";
		system("cls");
		cout << "\n\n\n\t\t     o============================================================================o\n\n";
		cout << "\t\t\t       ____                                __   _____     _\n";
		cout << "\t\t\t      |  _ \\  ___   ___  _ __ ___    ___  / _| |  ___|_ _| |_ ___\n";
		cout << "\t\t\t      | | | |/ _ \\ / _ \\| '__/ __|  / _ \\| |_  | |_ / _` | __/ _ \\ \n";
		cout << "\t\t\t      | |_| | (_) | (_) | |  \\__ \\ | (_) |  _| |  _| (_| | ||  __/\n";
		cout << "\t\t\t      |____/ \\___/ \\___/|_|  |___/  \\___/|_|   |_|  \\__,_|\\__\\___|\n";
		cout << "\n\n\t\t     o============================================================================o\n\n";
		cout << "\t\t\t    __________                  __________                 _________\n";
		cout << "\t\t\t   |          |                |          |               |         |\n";
		cout << "\t\t\t   | [A]ABOUT |                | [S]START |               | [E]EXIT |\n";
		cout << "\t\t\t   |__________|                |__________|               |_________|\n";
		cout << "\t\t\t                 ____________                 __________             \n";
		cout << "\t\t\t                |            |               |          |            \n";
		cout << "\t\t\t                | [C]CREDITS |               | [G]GUIDE |            \n";
		cout << "\t\t\t                |____________|               |__________|            \n";

		cout << "\n\n\t\t >> ";

		cin.getline(query, sizeof(query));

		if (strlen(query) != 1) {
			cout << "\n\t\tInvalid Input. Please try again..." << endl;
			cout << "\t\t";
			system("pause");
		}

		else {
			switch (query[0]) {
			case 'A':
			case 'a':
				About();
				break;
			case 'C':
			case 'c':
				Credits();
				break;
			case 'S':
			case 's':
				NewGameandLoadGame(p);
				valid = true;
				break;
			case 'E':
			case 'e':
				system("cls");
				valid = true;
				cout << "\n\n\tThank you for playing!\n" << "                    - Developed by Carl" << endl;
				break;
			case 'G':
			case 'g':
				Guide();
				break;
			default:
				cout << "Please try again." << endl;
			}
		}
	} while (!valid);
}

bool SaveAndLoad(Player& p, bool save) {

	// SaveAndLoad (Player, cslot, save?)
	// cslot = 0,1,2 saves
	// ex. cslot = 1
	// save = true, will save that slot

	//save file
	string nslot = "";
	char saved_v[20];
	bool saved = true;
	char playername_v[20];

	//character inventory
	char coins_v[100];
	char wtokens_v[100];
	char l_v[20];
	char spweapon_v[30];

	//character stats
	char sp_v[10];
	char exp_v[20];
	char ATK_v[10];
	char DEF_v[10];
	char SPD_v[10];
	char HP_v[10];
	char LUK_v[10];

	switch (p.sslot) {
	case 0:
		nslot = "slot1.txt";
		break;
	case 1:
		nslot = "slot2.txt";
		break;
	case 2:
		nslot = "slot3.txt";
		break;
	}

	// if false, then load game
	if (!save) {

		ifstream infile(nslot.c_str()); //opens the specified file in the input file stream format

		if (infile.is_open()) {
            string line;
            char newLine[20];

            getline(infile, line);
            strcpy(newLine, line.c_str());
            strcpy(saved_v, strtok(newLine, ":"));
            strcpy(playername_v, strtok(NULL, ":"));
            strcpy(coins_v, strtok(NULL, ":"));
            strcpy(wtokens_v , strtok(NULL, ":"));
            strcpy(l_v, strtok(NULL,":"));
            strcpy(spweapon_v,strtok(NULL, ":"));
            strcpy(exp_v, strtok(NULL, ":"));
            strcpy(sp_v, strtok(NULL,":"));
            strcpy(ATK_v, strtok(NULL, ":"));
            strcpy(DEF_v, strtok(NULL, ":"));
            strcpy(SPD_v, strtok(NULL, ":"));
            strcpy(HP_v, strtok(NULL, ":"));
            strcpy(LUK_v, strtok(NULL, ":"));
			//The file will be read according to the comment below
			//saved,playername,coins,wtokens,l,spweapon,expgain,sp,ATK,DEF,SPD,HP,LUK.

			// These Values are now Updated!

			p.playername = playername_v; //copies the value
			p.coins = stoi(coins_v); //turns strings into ints with stoi(<string>), then copies the value
			p.wtokens = stoi(wtokens_v);
			p.l = stoi(l_v);
			p.spweapon = spweapon_v;
			p.expgain = stoi(exp_v);
			p.sp = stoi(sp_v);
			p.sk.ATK = stoi(ATK_v);
			p.sk.DEF = stoi(DEF_v);
			p.sk.SPD = stoi(SPD_v);
			p.sk.HP = stoi(HP_v);
			p.sk.LUK = stoi(LUK_v);

			// to confirm if the save file can be used
			switch (saved_v[0]) {
			case '0':
				saved = false;
			case '1':
				saved = true;
			}

			infile.close();
		}
		else
		{
			saved = false;
		}
	}
	else
	{
		ofstream outfile(nslot.c_str()); //opens the specified file in output file stream format

		// write to outfile

		//The file will be written according to the comment below
		//saved,playername,coins,l,spweapon,sp,ATK,DEF,SPD,HP,LUK.

		outfile << "1";
		outfile << ':';
		outfile << p.playername;
		outfile << ':';
		outfile << p.coins;
		outfile << ':';
		outfile << p.wtokens;
		outfile << ':';
		outfile << p.l;
		outfile << ':';
		outfile << p.spweapon;
		outfile << ':';
		outfile << p.expgain;
		outfile << ':';
		outfile << p.sp;
		outfile << ':';
		outfile << p.sk.ATK;
		outfile << ':';
		outfile << p.sk.DEF;
		outfile << ':';
		outfile << p.sk.SPD;
		outfile << ':';
		outfile << p.sk.HP;
		outfile << ':';
		outfile << p.sk.LUK;
		outfile << ':';

		outfile.close();
	}

	return saved;

}

void About() {
	system("cls");
	cout << "\n\n\tIn this rogue-like game, you will be given a choices of 4 doors. Each door leads to a random\n";
	cout << "\tconsequences such as, fighting enemies, a shop for players to buy and upgrade their skills,\n";
	cout << "\tand/or just a free room that will give you an ability point.\n\n";
	cout << "\tThis is a text-based\n\n";
	cout << "\tThis game is developed by Carl Andrew Villanueva.\n" << endl;
	system("pause");
	Menu();
}

void Credits() {
	system("cls");
	cout << "\n\n";
	cout << "\tLead Programmer:" << endl;
	cout << "\tCarl Andrew Villanueva" << endl;
	cout << endl;
	cout << "\tASCII Art:" << endl;
	cout << "\tMax Strandberg" << endl;
	cout << endl;
	cout << "\tPrograms Used:" << endl;
	cout << "\tG++" << endl;
	cout << "\tVisual Studio" << endl;
	cout << "\tGitHub" << endl;
	cout << "\tNotion" << endl;
	cout << endl;
	cout << "\tWebsites Used:" << endl;
	cout << "\twww.ascii-art-generator.org" << endl;
	cout << endl;
	system("pause");
	Menu();
}

void Guide() {
	bool valid = false;

	do {
		char query[20] = "";

		system("cls");
		cout << "\n\n\n\n\t\t     o======================================GUIDE==================================o\n\n";
		cout << "\t\t            [0]New Game/Load Game" << endl;
		cout << "\t\t            [1]Door Selection" << endl;
		cout << "\t\t            [2]Player Stats" << endl;
		cout << "\t\t            [3]Saving Game" << endl;
		cout << "\t\t            [4]Combat System" << endl;
		cout << "\t\t            [5]Weapon Stats" << endl;
		cout << "\t\t            [6]The Vault" << endl;
		cout << "\t\t            [7]Shop" << endl;
		cout << "\n\n";
		cout << "\t\t            [B]Back" << endl;
		cout << "\t\t     o=============================================================================o";

		cout << "\n\n\t\t >> ";

		cin.getline(query, sizeof(query));

		if (strlen(query) != 1) {
			cout << "\n\t\tInvalid Input. Please try again..." << endl;
			cout << "\t\t";
			system("pause");
		}

		else {
			switch (query[0]) {
			case 'B':
			case 'b':
				valid = true;
				break;
			case '0':
			{
				system("cls");
				cout << "\n\n\n\n\n\t\t     o============================================================================o\n\n";
				cout << "\t\t\t       ____                                __   _____     _\n";
				cout << "\t\t\t      |  _ \\  ___   ___  _ __ ___    ___  / _| |  ___|_ _| |_ ___\n";
				cout << "\t\t\t      | | | |/ _ \\ / _ \\| '__/ __|  / _ \\| |_  | |_ / _` | __/ _ \\ \n";
				cout << "\t\t\t      | |_| | (_) | (_) | |  \\__ \\ | (_) |  _| |  _| (_| | ||  __/\n";
				cout << "\t\t\t      |____/ \\___/ \\___/|_|  |___/  \\___/|_|   |_|  \\__,_|\\__\\___|\n";
				cout << "\n\n\t\t     o============================================================================o\n\n";
				cout << "\t\t\t    __________                  __________                 _________\n";
				cout << "\t\t\t   |          |                |          |               |         |\n";
				cout << "\t\t\t   | [A]ABOUT |                | [S]START | <------       | [E]EXIT |\n";
				cout << "\t\t\t   |__________|                |__________| Start new game|_________|\n";
				cout << "\t\t\t                 ____________                 __________             \n";
				cout << "\t\t\t                |            |               |          |            \n";
				cout << "\t\t\t                | [C]CREDITS |               | [G]GUIDE |            \n";
				cout << "\t\t\t                |____________|               |__________|            \n";
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\n\n\n\n\t\t\t\t \t\t\t      New Game or Load Game" << endl;
				cout << "\n\t\t            New Game [N] or Load Game [L]\n" << endl;
				cout << "\t\t            New Game - Either Creates or Overwrites the save slot\n" << endl;
				cout << "\t\t            Load Game - Loads a save slot, will not load an empty slot\n" << endl;
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\n\t\t     o============================================================================o\n" << endl;
				cout << "\n\n\t\t\t       New Game" << endl;
				cout << "\t\t       > [0] Gicky" << endl;
				cout << "\t\t       > [1] Lednar" << endl;
				cout << "\t\t       > [2] Empty Slot" << endl;
				cout << "\n\n\t\t     o============================================================================o\n" << endl;
				cout << "\t\t Select a save slot: 2 <--- The Slot that will be created/overwritten" << endl;
				cout << "\t\t----------------------------------------------------------------------------------------" << endl;
				cout << "\t\t     o============================================================================o\n" << endl;
				cout << "\n\n\t\t\t       Load Game" << endl;
				cout << "\t\t       > [0] Gicky" << endl;
				cout << "\t\t       > [1] Lednar" << endl;
				cout << "\t\t       > [2] Empty Slot" << endl;
				cout << "\n\n\t\t     o============================================================================o\n" << endl;
				cout << "\t\t Select a save slot: 0 <--- The Slot that will load a save slot";
				cout << "\n\n";
				system("pause");
			}
			break;
			case '1':
			{
				system("cls");
				printf("\n\n\t\t\t\t\t\t\t\t\t\t         Dungeon Level: 1\n");
                printf("\t\t\t\t\t\t\t\t\t\t                 Level: 1\n");
                cout << "\t\t                      ______                ______                ______     " << endl;
                cout << "\t\t                   ,-'      `-.          ,-'      `-.          ,-'      `-.  " << endl;
                cout << "\t\t                  /            \\        /            \\        /            \\" << endl;
                cout << "\t\t                 |              |      |              |      |              |" << endl;
                cout << "\t\t                 )              |      )              |      )              |" << endl;
                cout << "\t\t                 |              |      |              |      |              |" << endl;
                cout << "\t\t                 |          (a) (      |          (b) (      |          (c) (" << endl;
                cout << "\t\t                 |              |      |              |      |              |" << endl;
                cout << "\t\t                 |              |      |              |      |              |" << endl;
                cout << "\t\t                 )              |      )              |      )              |" << endl;
                cout << "\t\t                 |              |      |              |      |              |" << endl;
                cout << "\t\t                 |______________|      |______________|      |______________|\n" << endl;
                cout << "\n\n";
                cout << "\t\t    HEALTH: 110 " << endl;
                cout << "\t\t                                                                 [P] Player Stats" << endl;
                cout << "\n\n";
                cout << "\t\t    Select a door...\n" << endl;
				cout << "\n\t\t >> a <--- the letters written on the door will navigate you through there" << endl;
				cout << "\t\t           you can write letters like S,P,I to go to Shop, Player Stats, or Inventory";
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\n\n\t\t     o==================================DOOR SELECTION=============================o\n\n";
				cout << "\t\t When navigating through the doors, you will receive random events" << endl;
				cout << "\t\t 1. Enemies" << endl;
				cout << "\t\t 2. Treasure" << endl;
				cout << "\t\t 3. Rest Area" << endl;
				cout << "\t\t     o=============================================================================o";
				cout << "\n\n";
				system("pause");
			}
			break;
			case '2':
			{
				system("cls");
				cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
				cout << "\t\t\t\t STATS\t\t\t      Gicky" << "\n\n";
				cout << "\t\t            [A]Attack  (ATK): 1" << "\n";
				cout << "\t\t            [D]Defense (DEF): 1" << "\n";
				cout << "\t\t            [S]Speed   (SPD): 3" << "\n";
				cout << "\t\t            [H]Health   (HP): 1" << "\n";
				cout << "\t\t            [L]Luck    (LUK): 1" << "\n";
				cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: 3" << "\n\n";
				cout << "\t\t     o=============================================================================o\n" << endl;
				cout << "                                                                                           > [B]Back" << endl;
				cout << "\n\t\t >> D <--- First you will select what stats you are willing to add";
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
				cout << "\t\t\t\t STATS\t\t\t      Gicky" << "\n\n";
				cout << "\t\t            [A]Attack  (ATK): 1" << "\n";
				cout << "\t\t         >> [D]Defense (DEF): 1" << "\n";
				cout << "\t\t            [S]Speed   (SPD): 3" << "\n";
				cout << "\t\t            [H]Health   (HP): 1" << "\n";
				cout << "\t\t            [L]Luck    (LUK): 1" << "\n";
				cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: 3" << "\n\n";
				cout << "\t\t     o=============================================================================o\n" << endl;
				cout << "                                                                                           > [B]Back" << endl;
				cout << "\n";
				cout << "\n\t\t >> 3 <--- After selecting the stat, you write the amount to add with skill points";
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
				cout << "\t\t\t\t STATS\t\t\t      Gicky" << "\n\n";
				cout << "\t\t            [A]Attack  (ATK): 1" << "\n";
				cout << "\t\t         >> [D]Defense (DEF): 4" << "\n";
				cout << "\t\t            [S]Speed   (SPD): 3" << "\n";
				cout << "\t\t            [H]Health   (HP): 1" << "\n";
				cout << "\t\t            [L]Luck    (LUK): 1" << "\n";
				cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: 0" << "\n\n";
				cout << "\t\t     o=============================================================================o\n\n";
				cout << "\n\t\tNo more skill points...\n" << endl;
				cout << "\n\t\tSaving game..." << endl;
				cout << "\n";
				system("pause");
			}
			break;
			case '3':
			{
				system("cls");
				cout << "\n\n";
				cout << "\t\t     o===================================SAVING GAME===============================o\n\n";
				cout << "\t\t                           Dying ingame is the only way to save" << endl;
				cout << "\t\t     o=============================================================================o";
				cout << "\n\n";
				system("pause");
				break;
			}
			case '4':
			{
				Enemy enemy = initializeEnemy("Huge Spider");
				string space = "";
				int ensize = 0;
				while (enemy.enemyname[ensize] != '\0') ensize++;
				if (ensize < 7) {
					for (int i = 0;i < 5; i++) {
						space += " ";
					}
				}

				system("cls");
				cout << "\t\t\t                                                 " << endl;
				cout << "\t\t\t     Name of the enemy ---> " << space << enemy.enemyname << "        " << endl;
				cout << "\t\t\t    Current HP/Maximum HP ---> " << enemy.HEALTH << "/" << 100 + (10 * enemy.stat.HP) << endl;
				cout << "\t\t\t                               " << enemy.art[0] << endl;
				cout << "\t\t\t                               " << enemy.art[1] << endl;
				cout << "\t\t\t                               " << enemy.art[2] << endl;
				cout << "\t\t\t          Enemy ASCII Art ---> " << enemy.art[3] << endl;
				cout << "\t\t\t                               " << enemy.art[4] << endl;
				cout << "\t\t\t                               " << enemy.art[5] << endl;
				cout << "\t\t\t                               " << enemy.art[6] << endl;
				cout << "\t\t\t                               " << enemy.art[7] << endl;
				cout << "\t\t     o=============================================================================o" << endl;
				cout << "\t\t\t                                                 " << endl;
				cout << "\t\t\t             [A]ATTACK         [I]INVENTORY        [R]RUN AWAY    " << endl;
				cout << "\n\t\t\t    Health: 100                              Previous Damage: 0" << endl;
				cout << "\t\t\t                                                 " << endl;
				cout << "\n\t\t >> ";
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\t\t\t                                                 " << endl;
				cout << "\t\t\t                            " << space << enemy.enemyname << "        " << endl;
				cout << "\t\t\t                               " << enemy.HEALTH << "/" << 100 + (10 * enemy.stat.HP) << endl;
				cout << "\t\t\t                               " << enemy.art[0] << endl;
				cout << "\t\t\t                               " << enemy.art[1] << endl;
				cout << "\t\t\t                               " << enemy.art[2] << endl;
				cout << "\t\t\t                               " << enemy.art[3] << endl;
				cout << "\t\t\t                               " << enemy.art[4] << endl;
				cout << "\t\t\t                               " << enemy.art[5] << endl;
				cout << "\t\t\t                               " << enemy.art[6] << endl;
				cout << "\t\t\t                               " << enemy.art[7] << endl;
				cout << "\t\t     o=============================================================================o" << endl;
				cout << "\t\t\t                                                 " << endl;
				cout << "\t\t\t             [0]SLASH                                        " << endl;
				cout << "\t\t\t             [1]THRUST                                       " << endl;
				cout << "\t\t\t             [2]NOTHING                                      " << endl;
				cout << "\t\t\t             [3]NOTHING                                      " << endl;
				cout << "\t\t\t             [B]Back                                         " << endl;
				cout << "\n\t\t >> 0 <--- The type of attack you are going to make with your weapon";
				cout << "\n\t\t           Some attacks have cooldown, Some attacks have tradeoff";
				cout << "\n\t\t           You can see the type of attack you are going to make";
				cout << "\n\t\t           in info when in combat.";
				cout << "\n\n";
				system("pause");
				system("cls");
				cout << "\n\n\t\t     o==================================COMBAT SYSTEM==============================o\n\n";
				cout << "\t\t            The chance that the player attacks first or the enemy depends on the SPD." << endl;
				cout << "\t\t            if there's an equal SPD, both have an equal chance of attacking first." << endl;
				cout << "\t\t            The weapon has its own movesets" << endl;
				cout << "\t\t            The enemies has their own movesets" << endl;
				cout << "\t\t            During an attack, both characters can dodge or get missed" << endl;
				cout << "\t\t            depending on SPD, both characters has a chance to attack twice" << endl;
				cout << "\t\t            " << endl;
				cout << "\t\t            The game is built upon strategies in using the weapon in the best way" << endl;
				cout << "\t\t            possible. Knowing both your weapons and enemies and how to counter them" << endl;
				cout << "\t\t            is the best way to win. Adding only one stat will give you disadvantages" << endl;
				cout << "\t\t            against enemies with specific traits. This game is a roguelite so everytime" << endl;
				cout << "\t\t            you die, you get stronger, but you will lose all your loot in the process." << endl;
				cout << "\t\t            You can buy permanent weapons in the shop to get a better early game." << endl;
				cout << "\t\t     o=============================================================================o";
				cout << "\n\n";
				system("pause");
			}
			break;
			case '5':
			    system("cls");
                cout << "\n\n\n";
                cout << "\t\t     o=============================================================================o" << endl;
                cout << "\n";
                cout << "\t\t                                     Mystic Grimoire" << endl;
                cout << "\n";
                cout << "\t\t                     [0] +HP every door open (+2) :  150 Tokens" << endl;
                cout << "\t\t                     [1] +HP every kill      (+2) :  200 Tokens" << endl;
                cout << "\t\t                     [2] +HP stats           (+15):  100 Tokens" << endl;
                cout << "\t\t                     [3] +COINS every door   (+4) :  120 Tokens" << endl;
                cout << "\n\n\n";
                cout << "\n";
                cout << "\t\t                                                                     [C] Check Stats" << endl;
                cout << "\n";
                cout << "\t\t     o=============================================================================o" << endl;
                cout << "\t\t     Witch Tokens: 0                                                        [B] Back" << endl;
                cout << "\n\n";
                cout << "\t\t     Hmmm?....." << endl;
                cout << "\n";
                cout << "\t\t     >> 0 <----- The ability that you would want to get." << endl;
                system("pause");
                break;
            case '6':
                system("cls");
                cout << "\n\n";
                cout << "\t\t        o==============================================================================o";
                cout << "\n\n";
                cout << "\t\t                                  Welcome to The Ohio Goblin Forge";
                cout << "\n\n";
                cout << "\t\t               Welcome, brave traveler! I've got the sharpest steel and the finest" << endl;
                cout << "\t\t                              upgrades this side of the forest!" << endl;
                cout << "\n\n";
                cout << "\t\t        o==============================================================================o";
                cout << "\n\n";
                printf("             Coins: 100 \033[1;33m<--   Player's Coins\033[0m\n");
                cout << "\t\t                            [W]Weapons                  [U]Upgrade" << endl;
                cout << "\n\n";
                cout << "\t\t                                          [L]Leave <" << endl;
                cout << "\n";
                cout << "\t\t        >> W <----- Type which one you would like, Weapons or Upgrades" << endl;
                system("pause");
                system("cls");
                cout << "\n\n";
                cout << "\t\t        o==============================================================================o";
                cout << "\n\n";
                cout << "\t\t                                Welcome to The Ohio Goblin Forge";
                cout << "\n\n";
                cout << "\t\t                         [0] Rusty Sword    (+2  ATK): 150 Coins" << endl;
                cout << "\t\t                         [1] Excalibur      (+10 ATK): 200 Coins" << endl;
                cout << "\t\t                         [2] Stormbringer   (+25 ATK): 500 Coins" << endl;
                cout << "\n\n";
                cout << "\t\t        o==============================================================================o";
                cout << "\t\t        Coins: 100 " << endl;
                cout << "\n\n";
                cout << "\t\t        Which o' these shiny toys ye fancy as yer startin' weapon, eh, adventurer?" << endl;
                cout << "\n";
                cout << "\t\t     >> 0 <--- The weapon you would like to buy" << endl;
                cout << "\t\t        "; system("pause");
                system("cls");
                cout << "\n\n";
                cout << "\t\t        o==============================================================================o" << endl;
                cout << "\n";
                cout << "\t\t                                            Upgrades" << endl;
                cout << "\n";
                cout << "\t\t                                          Your weapons: " << endl;
                cout << "\t\t                                         [0] Short Sword " << endl;
                cout << "\n\n";
                cout << "\t\t        o==============================================================================o";
                cout << "\t\t                                         [L] Leave" << endl;
                cout << "\n\t\t        >> 0 <----- Usually the weapon that could be upgraded here is the starting weapon of the player." << endl;
                cout << "\t\t                      Players won't be able to upgrade weapons that they get from the dungeon." << endl;
                system("pause");
                system("cls");
                break;
			default:
			    system("cls");
				cout << "Please try again." << endl;
				system("pause");
				break;
			}
		}
	} while (!valid);

	Menu();
}

void skilldraw(Player p, char picks) {
	system("cls");
	switch (picks) {
	case 'A':
	case 'a':
		cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
		cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
		printf("\t\t         >> \033[1;33m[A]Attack  (ATK): %d\033[0m\n", p.sk.ATK);
		cout << "\t\t            [D]Defense (DEF): " << p.sk.DEF << "\n";
		cout << "\t\t            [S]Speed   (SPD): " << p.sk.SPD << "\n";
		cout << "\t\t            [H]Health   (HP): " << p.sk.HP << "\n";
		cout << "\t\t            [L]Luck    (LUK): " << p.sk.LUK << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "                                                                                           > [B]Back" << endl;
		cout << "\n";
		break;
	case 'D':
	case 'd':
		cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
		cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
		cout << "\t\t            [A]Attack  (ATK): " << p.sk.ATK << "\n";
		printf("\t\t         >> \033[1;33m[D]Defense (DEF): %d\033[0m\n",p.sk.DEF);
		cout << "\t\t            [S]Speed   (SPD): " << p.sk.SPD << "\n";
		cout << "\t\t            [H]Health   (HP): " << p.sk.HP << "\n";
		cout << "\t\t            [L]Luck    (LUK): " << p.sk.LUK << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "                                                                                           > [B]Back" << endl;
		cout << "\n";
		break;
	case 'S':
	case 's':
		cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
		cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
		cout << "\t\t            [A]Attack  (ATK): " << p.sk.ATK << "\n";
		cout << "\t\t            [D]Defense (DEF): " << p.sk.DEF << "\n";
		printf("\t\t         >> \033[1;33m[S]Speed   (SPD): %d\033[0m\n",p.sk.SPD);
		cout << "\t\t            [H]Health   (HP): " << p.sk.HP << "\n";
		cout << "\t\t            [L]Luck    (LUK): " << p.sk.LUK << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "                                                                                           > [B]Back" << endl;
		cout << "\n";
		break;
	case 'H':
	case 'h':
		cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
		cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
		cout << "\t\t            [A]Attack  (ATK): " << p.sk.ATK << "\n";
		cout << "\t\t            [D]Defense (DEF): " << p.sk.DEF << "\n";
		cout << "\t\t            [S]Speed   (SPD): " << p.sk.SPD << "\n";
		printf("\t\t         >> \033[1;33m[H]Health   (HP): %d\033[0m\n",p.sk.HP);
		cout << "\t\t            [L]Luck    (LUK): " << p.sk.LUK << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "                                                                                           > [B]Back" << endl;
		cout << "\n";
		break;
	case 'L':
	case 'l':
		cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
		cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
		cout << "\t\t            [A]Attack  (ATK): " << p.sk.ATK << "\n";
		cout << "\t\t            [D]Defense (DEF): " << p.sk.DEF << "\n";
		cout << "\t\t            [S]Speed   (SPD): " << p.sk.SPD << "\n";
		cout << "\t\t            [H]Health   (HP): " << p.sk.HP << "\n";
		printf("\t\t         >> \033[1;33m[L]Luck    (LUK): %d\033[0m\n", p.sk.LUK);
		cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "                                                                                           > [B]Back" << endl;
		cout << "\n";
		break;
	}
}

void skills(Player& p, bool save) {
	char q[5];
	int qp;
	bool upskill = true;

	while (upskill) {
		system("cls");
		if (p.sp <= 0) {
			system("cls");
			cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
			cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
			cout << "\t\t            [A]Attack  (ATK): " << p.sk.ATK << "\n";
			cout << "\t\t            [D]Defense (DEF): " << p.sk.DEF << "\n";
			cout << "\t\t            [S]Speed   (SPD): " << p.sk.SPD << "\n";
			cout << "\t\t            [H]Health   (HP): " << p.sk.HP << "\n";
			cout << "\t\t            [L]Luck    (LUK): " << p.sk.LUK << "\n";
			cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
			cout << "\t\t     o=============================================================================o\n\n";
			cin.ignore();
			cout << "\n\t\tNo more skill points...\n" << endl;
			cout << "\n\t\tSaving game..." << endl;
			cout << "\t\t"; system("pause");
			SaveAndLoad(p, save);
			upskill = false;
			startmenu(p);
		}

		cout << "\n\n\n\n\n\t\t     o===================================STATISTICS================================o\n\n";
		cout << "\t\t\t\t STATS\t\t\t      " << p.playername << "\n\n";
		cout << "\t\t            [A]Attack  (ATK): " << p.sk.ATK << "\n";
		cout << "\t\t            [D]Defense (DEF): " << p.sk.DEF << "\n";
		cout << "\t\t            [S]Speed   (SPD): " << p.sk.SPD << "\n";
		cout << "\t\t            [H]Health   (HP): " << p.sk.HP << "\n";
		cout << "\t\t            [L]Luck    (LUK): " << p.sk.LUK << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t     Skill points: " << p.sp << "\n\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "                                                                                           > [B]Back" << endl;
		cin.ignore();
		cout << "\n\t\t >> "; cin.getline(q, sizeof(q));

		if (strlen(q) != 1) {
			cout << "\nInvalid Skill Name. Try again.\n" << endl;
			system("pause");
			continue;
		}
        else {
            skilldraw(p, q[0]);
            cout << "\n\t\tEnter Skill Points.." << endl << "\n\t\t >> ";
            cin >> qp;
			switch (q[0]) {
			case 'A':
			case 'a':

				if (qp <= p.sp) {
					p.sk.ATK += qp;
					p.sp -= qp;
				}
				else {
					cout << "\t\tInvalid skill points. Try again.\n" << endl;
					system("pause");
				}
				break;
			case 'D':
			case 'd':

				if (qp <= p.sp) {
					p.sk.DEF += qp;
					p.sp -= qp;
				}
				else {
					cout << "\t\tInvalid skill points. Try again.\n" << endl;
					system("pause");
				}
				break;
			case 'S':
			case 's':

				if (qp <= p.sp) {
					p.sk.SPD += qp;
					p.sp -= qp;
				}
				else {
					cout << "\t\tInvalid skill points. Try again.\n" << endl;
					system("pause");
				}
				break;
			case 'H':
			case 'h':

				if (qp <= p.sp) {
					p.sk.HP += qp;
					p.sp -= qp;
				}
				else {
					cout << "Invalid skill points. Try again.\n" << endl;
					system("pause");
				}
				break;
			case 'L':
			case 'l':


				if (qp <= p.sp) {
					p.sk.LUK += qp;
					p.sp -= qp;
				}
				else {
					cin.ignore();
					cout << "\t\tInvalid skill points. Try again.\n" << endl;
				}
				break;
			case 'B':
			case 'b':
				Menu();
			default:
				cout << "\nInvalid Skill Name. Try again.\n" << endl;
				system("pause");
				break;
			}

		}
	}
}

void explevel(Player& p, Enemy& enemy){

    double expneedtolevelup = pow(p.l/0.3, 2);
    if (p.expgain >= expneedtolevelup){
        system("cls");
        p.sp++;
        p.l++;
        drawEnemyFight(p, enemy, "Event");
        cout << "\t\t\t Congrats! You leveled up!" << endl;
        cout << "\t\t\t "; system("pause");
    }
    doors(p);
}

void shop(Player& p) {
	char dr[10];
	bool valid = false;
	while (!valid) {
		system("cls");
		cout << "\n\n";
		cout << "\t\t        o==============================================================================o";
		cout << "\n\n";
		cout << "\t\t                                  Welcome to The Ohio Goblin Forge";
		cout << "\n\n";
		cout << "\t\t               Welcome, brave traveler! I've got the sharpest steel and the finest" << endl;
		cout << "\t\t                              upgrades this side of the forest!" << endl;
		cout << "\n\n";
		cout << "\t\t        o==============================================================================o";
		cout << "\n\n";
		cout << "\t\t        Coins: " << p.coins << endl;
		cout << "\t\t                            [W]Weapons                  [U]Upgrade" << endl;
		cout << "\n\n";
		cout << "\t\t                                          [L]Leave <" << endl;
		cout << "\n";
		cout << "\t\t        >> "; cin.getline(dr, sizeof(dr));

		if (strlen(dr) != 1 || dr == "") {
			cout << "\t\t        Ye muck it up! Wrong input, ye do!" << endl;
			cout << "\t\t        "; system("pause");
		}

		else {
			switch (dr[0]) {
			case 'W':
			case 'w':
				weaponshop(p);
				break;
			case 'U':
			case 'u':
				upgradeShop(p);
				break;
			case 'L':
			case 'l':
				startmenu(p);
				break;
			}
		}
	}
}

void vault(Player& p){
    char q[5];
    int ab1 = (p.abpt1 == 0) ? 2 : p.abpt1 * 2;
    int ab2 = (p.abpt2 == 0) ? 2 : p.abpt2 * 2;
    int ab3 = (p.abpt3 == 0) ? 15 : (p.abpt3 * 10) + 5;
    int ab4 = (p.abpt4 == 0) ? 4 : p.abpt4 * 4;
    do {
        system("cls");
        cout << "\n\n\n";
        cout << "\t\t     o=============================================================================o" << endl;
        cout << "\n";
        cout << "\t\t                                     Mystic Grimoire" << endl;
        cout << "\n";
        cout << "\t\t                     [0] +HP every door open (+"<< ab1 <<"): 150 Tokens" << endl;
        cout << "\t\t                     [1] +HP every kill      (+"<< ab2 <<"): 200 Tokens" << endl;
        cout << "\t\t                     [2] +HP stats           (+"<< ab3 <<"): 100 Tokens" << endl;
        cout << "\t\t                     [3] +COINS every door   (+"<< ab4 <<"): 120 Tokens" << endl;
        cout << "\n\n\n";
        cout << "\n";
        cout << "\t\t     o=============================================================================o" << endl;
        cout << "\t\t     Witch Tokens: " << p.wtokens << "                                                             [B] Back" << endl;
        cout << "\n\n";
        cout << "\t\t     Hmmm?....." << endl;
        cout << "\n";
        cout << "\t\t     >> "; cin.getline(q, sizeof(q));

        switch (q[0]){
        case '0':
            if (p.wtokens >= 150){
                cout << "\t\t     Haa, haa... Good luck, traveler..." << endl;
                p.abpt1 += 1;
                p.wtokens -= 150;
                cout << "\t\t     "; system("pause");
                continue;
            }
            else {
                cout << "\t\t     Are ye tryin' to scam me?!!" << endl;
                cout << "\t\t     "; system("pause");
                continue;
            }
            break;
        case '1':
            if (p.wtokens >= 200){
                cout << "\t\t     In each fallen foe, vitality shall flow..." << endl;
                p.abpt2 += 1;
                p.wtokens -= 200;
                cout << "\t\t     "; system("pause");
                continue;
            }
            else {
                cout << "\t\t     Are ye tryin' to scam me?!!" << endl;
                cout << "\t\t     "; system("pause");
                continue;
            }
            break;
        case '2':
            if (p.wtokens >= 100){
                cout << "\t\t     Haa, haa... Good luck, traveler..." << endl;
                p.abpt3 += 1;
                p.wtokens -= 100;
                system("pause");
                continue;
            }
            else {
                cout << "\t\t     Are ye tryin' to scam me?!!" << endl;
                cout << "\t\t     "; system("pause");
                continue;
            }
            break;
        case '3':
            if (p.wtokens >= 120){
                cout << "\t\t     Haa, haa... Good luck, traveler..." << endl;
                p.abpt4 += 1;
                p.wtokens -= 120;
                cout << "\t\t     "; system("pause");
                continue;
            }
            else {
                cout << "\t\t     Are ye tryin' to scam me?!!" << endl;
                cout << "\t\t     "; system("pause");
                continue;
            }
            break;
        case 'B':
        case 'b':
            cout << "\t\t     Pleasure tradin' with ya, traveler!" << endl;
            startmenu(p);
            break;
        default:
            cout << "\t\t     Wrong input, thou fool!" << endl;
            cout << "\t\t     "; system("pause");
            continue;
        }
    }while (true);

}

void weaponshop(Player& p){
    char q[5];
    do {
        system("cls");
        cout << "\n\n";
        cout << "\t\t        o==============================================================================o";
        cout << "\n\n";
        cout << "\t\t                                Welcome to The Ohio Goblin Forge";
        cout << "\n\n";
        cout << "\t\t                         [0] Rusty Sword    (+2  ATK): 150 Coins" << endl;
        cout << "\t\t                         [1] Excalibur      (+10 ATK): 200 Coins" << endl;
        cout << "\t\t                         [2] Stormbringer   (+25 ATK): 500 Coins" << endl;
        cout << "\n\n";
        cout << "\t\t        o==============================================================================o";
        cout << "\t\t                                                                                [B] Back" << endl;
        cout << "\n\n";
        cout << "\t\t        Which o' these shiny toys ye fancy as yer startin' weapon, eh, adventurer?" << endl;
        cout << "\n";
        cout << "\t\t     >> "; cin.getline(q, sizeof(q));

        if (strlen(q) != 1){
            cin.ignore();
            cout << "\t\t        Ye muck it up! Wrong input, ye do!" << endl;
            cout << "\t\t        "; system("pause");

            continue;
        }

        switch (q[0]){
        case '0':
            if (p.coins >= 150){
                p.spweapon = "Rusty Sword";
                cout << "\t\t        Thanks for grabbin' that, hehe! More shinies next time, aye?" << endl;
                system("pause");
                p.coins -= 150;
                continue;
            }
            else {
                cout << "\t\t        Ye be lackin' the shinies for that, traveler!" << endl;
                cout << "\t\t        "; system("pause");
                continue;
            }
            break;
        case '1':
            if (p.coins >= 200){
                p.spweapon = "Excalibur";
                p.coins -= 200;
                cout << "\t\t        Thanks for grabbin' that, hehe! More shinies next time, aye?" << endl;
                continue;
            }
            else {
                cout << "\t\t        Ye be lackin' the shinies for that, traveler!" << endl;
                cout << "\t\t        "; system("pause");
                continue;
            }
            break;
        case '2':
            if (p.coins >= 500){
                p.spweapon = "Stormbringer";
                p.coins -= 500;
                cout << "\t\t        Thanks for grabbin' that, hehe! More shinies next time, aye?" << endl;
                continue;
            }
            else {
                cout << "\t\t        Ye be lackin' the shinies for that, traveler!" << endl;
                cout << "\t\t        "; system("pause");
            }
            break;
        case 'L':
        case 'l':
            cout << "\t\t        Pleasure tradin' with ya, traveler!" << endl;
            cout << "\t\t        "; system("pause");
            shop(p);
            break;
        default:
            cout << "\t\t        Ye muck it up! Wrong input, ye do!" << endl;
            cout << "\t\t        "; system("pause");
            break;
        }
    }while (true);
}

void upgrading(Player& p){
    double dummy = (p.weapdmg == 0) ? 2 : p.weapdmg/10;
    char q[5];
    do {
        system("cls");
        cout << "\t\t     o=============================================================================o" << endl;
        cout << "\n\n";
        cout << "\t\t                                         " << p.pweapon << endl;
        cout << "\n\n";
        cout << "\t\t                                 [0] + ATK (+" << dummy << ") : 30 Coins" << endl;
        cout << "\n\n";
        cout << "\t\t     o=============================================================================o" << endl;
        cout << "\t\t     Coins: " << p.coins << endl;
        cout << "\n\n";
        cout << "\t\t     Which weapon would ye' like to upgrade, eh?" << endl;
        cout << "\n";
        cout << "\t\t     >> "; cin.getline(q, sizeof(q));

        if (strlen(q) != 1){
            cout << "\t\t     Ye muck it up! Wrong input, ye do!" << endl;
            cout << "\t\t     "; system("pause");
            continue;
        }

        switch (q[0]){
        case '0':
            if (p.coins >= 30) {
                cout << "\t\t     Upgrading, up, up, up!" << endl;
                p.weapdmg += 1;
                p.coins -= 30;
                system("pause");
                break;
            }
            else {
                cout << "\t\t        Ye be lackin' the shinies for that, traveler!" << endl;
                system("pause");
                continue;
            }
        case 'B':
        case 'b':
            cout << "\t\t     Pleasure tradin' with ya, traveler!" << endl;
            upgradeShop(p);
            break;
        default:
            cout << "\t\t     Ye muck it up! Wrong input, ye do!" << endl;
            system("pause");
            continue;
        }
    } while (true);
}

void upgradeShop(Player& p) {
	char q2[10];
	do {
		system("cls");
		cout << "\n\n";
		cout << "\t\t        o==============================================================================o" << endl;
		cout << "\n";
		cout << "\t\t                                            Upgrades" << endl;
		cout << "\n";
		cout << "\t\t                                          Your weapons: " << endl;
		cout << "\t\t                                         [0] " << p.pweapon << endl;
		cout << "\n\n";
		cout << "\t\t        o==============================================================================o";
		cout << "\t\t                                         [L] Leave" << endl;
		cout << "\n\t\t        >> "; cin.getline(q2, sizeof(q2));
		for (int i = 0;i < strlen(q2);i++) {
			q2[i] = tolower(q2[i]);
			continue;
		}

		switch (q2[0]){
        case '0':
            upgrading(p);
            break;
        case 'B':
        case 'b':
            cout << "\t\t     Pleasure tradin' with ya, traveler!" << endl;
            shop(p);
            break;
        default:
            cout << "\t\t     Ye muck it up! Wrong input, ye do!" << endl;
            system("pause");
            continue;
		}
	} while (true);
}

void startmenu(Player& p){
    char q[5];
    p.php = 100 + (10 * p.sk.HP);
    p.php = p.php + p.ab3; // + HP Stats

    do {
      system("cls");
        cout << "\n\n\n";
        cout << "\t\t     o=============================================================================o" << endl;
        cout << "\n";
        cout << "\t\t             Prepare to embark on a grand adventure, courageous traveler..." << endl;
        cout << "\n";
        cout << "\t\t             [O]Ohio Shop               [S] Start               [V]The Vault" << endl;
        cout << "\n\n";
        cout << "\t\t     o=============================================================================o" << endl;
        cout << "\n\n";
        cout << "\t\t     >> "; cin.getline(q, sizeof(q));

        switch (q[0]) {
        case 'O':
        case 'o':
            shop(p);
            break;
        case 'S':
        case 's':
            doors(p);
            break;
        case 'V':
        case 'v':
            vault(p);
            break;
        default:
            cout << "\t\t     Please try again..." << endl;
            cout << "\t\t     "; system("pause");
            continue;
        }
    } while (true);
}

void doors(Player& p) {
	char q[5];
	bool doorsval = false;
	bool doorPicked = true;

	// Initializing Player Abilities
	p.ab1 = p.abpt1 * 2;
	p.ab2 = p.abpt2 * 2;
	if (p.abpt3 == 0){
        p.ab3 = 0;
	}
	else {
        p.ab3 = p.abpt3 * (10+5);
	}
	p.ab4 = p.abpt4 * 4;

    p.php += p.ab1; // +HP every door

    if (p.dl % 10 == 0) {
        BossFight(p);
    }

	while (!doorsval) {
		system("cls");
		printf("\n\n\t\t\t\t\t\t\t\t\t\t         Dungeon Level: %d\n", p.dl);
		printf("\t\t\t\t\t\t\t\t\t\t                 Level: %d\n", p.l);
		cout << "\t\t                      ______                ______                ______     " << endl;
		cout << "\t\t                   ,-'      `-.          ,-'      `-.          ,-'      `-.  " << endl;
		cout << "\t\t                  /            \\        /            \\        /            \\" << endl;
		cout << "\t\t                 |              |      |              |      |              |" << endl;
		cout << "\t\t                 )              |      )              |      )              |" << endl;
		cout << "\t\t                 |              |      |              |      |              |" << endl;
		cout << "\t\t                 |          (a) (      |          (b) (      |          (c) (" << endl;
		cout << "\t\t                 |              |      |              |      |              |" << endl;
		cout << "\t\t                 |              |      |              |      |              |" << endl;
		cout << "\t\t                 )              |      )              |      )              |" << endl;
		cout << "\t\t                 |              |      |              |      |              |" << endl;
		cout << "\t\t                 |______________|      |______________|      |______________|\n" << endl;
		cout << "\n\n";
		cout << "\t\t    HEALTH: " << p.php << endl;
		cout << "\t\t                                                                 [P] Player Stats" << endl;
		cout << "\n\n";
		cout << "\t\t    Select a door...\n" << endl;
		cout << "\t\t    >> ";
		cin.getline(q, sizeof(q));

        switch (q[0]) {
        case 'A':
        case 'a':
            gameplay(p, doorPicked);
            break;
        case 'B':
        case 'b':
            gameplay(p, doorPicked);
            break;
        case 'C':
        case 'c':
            gameplay(p, doorPicked);
            break;
        case 'P':
        case 'p':
            showstats(p);
            break;
        case 'I':
        case 'i':
            showinventory(p);
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
	}
}

void showstats(Player& p) {
    int expneedtolevelup = pow(p.l/0.3, 2);
	system("cls");
	cout << "\n\n\n\n\t\t     o==================================PLAYER STATS===============================o\n\n";
	cout << "\t\t            ===PLAYER===                                     ===ABILITIES===" << endl;
	cout << "\t\t            Player Name: " << p.playername << "                                 +HP Door : " << p.abpt1 << endl;
	cout << "\t\t            Starting Weapon: " << p.spweapon << "                     +HP Kill : " << p.abpt2 << endl;
	cout << "\t\t            Player Current Level: " << p.l << "                          +HP Stats: " << p.abpt3 << endl;
	cout << "\t\t            Witch Tokens: " << p.wtokens << "                                  +Coins Door: " << p.abpt4 << endl;
	cout << "\t\t            Player Exp Gained: " << p.expgain << "/" << expneedtolevelup << endl;
	cout << "\n";
	cout << "\t\t            ===DUNGEON===" << endl;
	cout << "\t\t            Current Dungeon Level: " << p.dl << endl;
	cout << "\t\t            Coins: " << p.coins << endl;
	cout << "\t\t            Current Weapon: " << p.pweapon << endl;
	cout << "\n";
	cout << "\t\t            ===STATS===\n";
	cout << "\t\t            ATK: " << p.sk.ATK << endl;
	cout << "\t\t            DEF: " << p.sk.DEF << endl;
	cout << "\t\t            SPD: " << p.sk.SPD << endl;
	cout << "\t\t            HP:  " << p.sk.HP << endl;
	cout << "\t\t            LUK: " << p.sk.LUK << endl;
	cout << "\t\t     o=============================================================================o\n" << endl;
	cout << "\n\n";
	cout << "\t\t"; system("pause");
}

void showinventory(Player& p) {
	Enemy dummy;
	bool inv = true;
	while (inv) {
		system("cls");
		cout << "\n\n\n\n";
		cout << "\t\t     o====================================INVENTORY================================o\n\n";
		cout << "\t\t              [0]Starting Weapon: " << p.pweapon << endl;
		cout << "\n";
		cout << "\t\t              [B]back\n";
		cout << "\t\t     o=============================================================================o\n" << endl;
		cout << "\n\n\t\t     >> ";
		char q[5];
		cin.getline(q, sizeof(q));

		if (sizeof(q) != 1){
            continue;
		}

		switch (q[0]) {
		case '0':
			system("cls");
			cout << "\n\n\n\n\n\t\t     o===================================WEAPON INFO===============================o\n\n";
			PlayerWeapon(p, dummy, "INFO");
			cout << "\t\t     o=============================================================================o\n" << endl;
			cout << "\n\n";
			system("pause");
			break;
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case 'B':
		case 'b':
			inv = false;
			break;
		}
	}
}

// Randomizing chances when door picked
void gameplay(Player& p, bool doorPicked) {
	system("cls");
	cout << "\n\n\n\n\t\t\t\t\tYour fate will be: ";

	// Make random to be only positive integers
	srand((unsigned)time(NULL));

	double chance = 1.0 * p.sk.LUK; // Initial chance factor

	while (doorPicked) {
		// PSEUDO RNG
		int randomNum = rand() % 100;
		randomNum += chance;
		if (p.dl == 1) {
			cout << "Enemies!\n" << endl;
			system("pause");
			doorPicked = false;
			chance += 0.1; // Increase the chance
			p.napilinaT = false;
			enemyFight(p);
		}
		if (randomNum < 65) { //        % chance of enemies
			cout << "Enemies!\n" << endl;
			system("pause");
			doorPicked = false;
			chance += 0.1; // Increase the chance
			p.napilinaT = false;
			enemyFight(p);
		}
		else if (!p.napilinaT && (randomNum >= 66 && randomNum <= 90)){ // 25% and if napilina is false
			cout << "Treasure!\n" << endl;
			system("pause");
			p.dl++;
            doorPicked = false;
			chance = 1.0; // Reset the chance
			p.napilinaT = true;
			TreasurePlace(p);
		}
		else if (!p.napilinaT && (randomNum >= 91 && randomNum <= 100)) { // 10% and if Napilina is false
			cout << "Take some rest, warrior!\n" << endl;
			system("pause");
			p.dl++;
			doorPicked = false;
			chance = 1.0; // Reset the chance
			p.napilinaT = true;
			RestPlace(p);
		}
		else {
            cout << "Enemies!\n" << endl;
			system("pause");
            doorPicked = false;
			chance += 0.1; // Increase the chance
			p.napilinaT = false;
			enemyFight(p);
		}
	}
}

// --- Fighting Functions ---
void fightNarrator(string narrate) {
	if (narrate == "PlayerMiss") {
		int np = (rand() % 8);
		switch (np) {
		case 0:
			cout << "\t\t                            YOU MISSED!" << endl;
			break;
		case 1:
			cout << "\t\t                            YOU MISSED! UNLUCKY!" << endl;
			break;
		case 2:
			cout << "\t\t                            YOU MISSED! BETTER LUCK NEXT TIME!" << endl;
			break;
		case 3:
			cout << "\t\t                            YOU MISSED! YOUR AIM WAS OFF!" << endl;
			break;
		case 4:
			cout << "\t\t                            YOU MISSED! TRY AGAIN!" << endl;
			break;
		case 5:
			cout << "\t\t                            YOU MISSED! PICK A BETTER WEAPON!" << endl;
			break;
		case 6:
			cout << "\t\t                            YOU MISSED! YOU SUCK AT AIMING!" << endl;
			break;
		case 7:
			cout << "\t\t                            YOU MISSED! GOOD JOB!" << endl;
			break;
		case 8:
			cout << "\t\t                            WOOSH! ENEMY DODGED!" << endl;
			break;
		}
	}
	if (narrate == "EnemyDodge") {
		int np = (rand() % 4);
		switch (np) {
		case 0:
			cout << "\t\t                            ENEMY DODGED!" << endl;
			break;
		case 1:
			cout << "\t\t                            ENEMY DODGED! IT MOVES FAST!" << endl;
			break;
		case 2:
			cout << "\t\t                            ENEMY DODGED! HOW NIMBLE!" << endl;
			break;
		case 3:
			cout << "\t\t                            OH NO! ENEMY DODGED!" << endl;
			break;
		case 4:
			cout << "\t\t                            WHAT THE! ENEMY DODGED!" << endl;
			break;
		}
	}
	if (narrate == "PlayerHit") {
		int np = (rand() % 4);
		switch (np) {
		case 4:
			cout << "\t\t                            YOU HIT ENEMY!" << endl;
			break;
		case 0:
			cout << "\t\t                            NICE! YOU HIT ENEMY!" << endl;
			break;
		case 1:
			cout << "\t\t                            GOOD! YOU HIT ENEMY!" << endl;
			break;
		case 2:
			cout << "\t\t                            GREAT! YOU HIT ENEMY!" << endl;
			break;
		case 3:
			cout << "\t\t                            NOT BAD! YOU HIT ENEMY!" << endl;
			break;
		}
	}
	if (narrate == "PlayerCrit") {
		int np = (rand() % 4);
		switch (np) {
		case 0:
			cout << "\t\t                            YOU CRITICAL HIT!" << endl;
			break;
		case 1:
			cout << "\t\t                            YOU HIT IT WHERE IT HURTS! CRITICAL HIT!" << endl;
			break;
		case 2:
			cout << "\t\t                            HIT WITH SURGICAL PRECISION! CRITICAL HIT!" << endl;
			break;
		case 3:
			cout << "\t\t                            THAT WILL LEAVE A SCAR! CRITICAL HIT!" << endl;
			break;
		case 4:
			cout << "\t\t                            FATAL DAMAGE TO THE BODY! CRITICAL HIT!" << endl;
			break;
		}
	}
	if (narrate == "EnemyMiss") {
		int np = (rand() % 4);
		switch (np) {
		case 0:
			cout << "\t\t                            ENEMY MISSED!" << endl;
			break;
		case 1:
			cout << "\t\t                            LUCKY! ENEMY MISSED!" << endl;
			break;
		case 2:
			cout << "\t\t                            THAT WAS CLOSE! ENEMY MISSED!" << endl;
			break;
		case 3:
			cout << "\t\t                            ENEMY MISSED! MAYBE IT WILL HIT NEXT TIME WATCH OUT!" << endl;
			break;
		case 4:
			cout << "\t\t                            ENEMY MISSED! PHEW!" << endl;
			break;
		}
	}
	if (narrate == "PlayerDodge") {
		int np = (rand() % 7);
		switch (np) {
		case 0:
			cout << "\t\t                            YOU DODGED!" << endl;
			break;
		case 1:
			cout << "\t\t                            NICE! YOU DODGED!" << endl;
			break;
		case 2:
			cout << "\t\t                            GOOD! YOU DODGED!" << endl;
			break;
		case 3:
			cout << "\t\t                            THAT ALMOST HIT YOU! YOU DODGED!" << endl;
			break;
		case 4:
			cout << "\t\t                            YOU GOT OUT OF THE WAY! YOU DODGED!" << endl;
			break;
		case 5:
			cout << "\t\t                            YOU DODGED! THAT WAS CLOSE!" << endl;
			break;
		case 6:
			cout << "\t\t                            YOU DODGED! KEEP IT UP!" << endl;
			break;
		case 7:
			cout << "\t\t                            THAT WAS SLOW! YOU DODGED!" << endl;
			break;
		}
	}
	if (narrate == "EnemyHit") {
		int np = (rand() % 6);
		switch (np) {
		case 0:
			cout << "\t\t                            YOU GOT HIT!" << endl;
			break;
		case 1:
			cout << "\t\t                            ENEMY HIT!" << endl;
			break;
		case 2:
			cout << "\t\t                            OUCH! YOU GOT HIT!" << endl;
			break;
		case 3:
			cout << "\t\t                            YOU GOT HIT! THAT ATTACK GRAZED YOU" << endl;
			break;
		case 4:
			cout << "\t\t                            ENEMY HIT!" << endl;
			break;
		case 5:
			cout << "\t\t                            OUCH! YOU GOT HIT!" << endl;
			break;
		case 6:
			cout << "\t\t                            YOU GOT HIT! THAT ATTACK GRAZED YOU" << endl;
			break;
		}
	}
	if (narrate == "EnemyCrit") {
		int np = (rand() % 6);
		switch (np) {
		case 0:
			cout << "\t\t                            ENEMY CRITICAL HIT!" << endl;
			break;
		case 1:
			cout << "\t\t                            OUCH! ENEMY CRITICAL HIT!" << endl;
			break;
		case 2:
			cout << "\t\t                            UH OH! ENEMY CRITICAL HIT!" << endl;
			break;
		case 3:
			cout << "\t\t                            FATAL WOUND! ENEMY CRITICAL HIT!" << endl;
			break;
		case 4:
			cout << "\t\t                            ENEMY CRITICAL HIT! TRY DODGING NEXT TIME!" << endl;
			break;
		case 5:
			cout << "\t\t                            ENEMY CRITICAL HIT! YOUR STILL ALIVE?!" << endl;
			break;
		case 6:
			cout << "\t\t                            WHAT THE! ENEMY CRITICAL HIT!" << endl;
			break;
		}
	}
}

int PlayerWeapon(Player& p, Enemy& enemy, string attr) {

	int val = 0;

	string weap = p.pweapon;

	if (weap == "Short Sword") {
		//Stats
		if (attr == "DMG") { val = 5; }
		if (attr == "ACC") { val = 100; }
		if (attr == "WEIGHT") { val = 2; }
		if (attr == "CRIT") { val = 15; }
		if (attr == "CRITDMG") { val = 250; }

		//Attacks
		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]SLASH                                        " << endl;
			cout << "\t\t\t             [1]THRUST                                       " << endl;
			cout << "\t\t\t             [2]NOTHING                                      " << endl;
			cout << "\t\t\t             [3]NOTHING                                      " << endl;
			cout << "\t\t\t             [B]Back                                         " << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SLASH!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			PlayerAttack(p, enemy);
		}
		if (attr == "A2") {
			//Thrust

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            THRUST!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG = 5;
			p.aCritch = 10;
			p.aACC = -10;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aCritch = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}
		if (attr == "A4") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Short Sword " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Slash] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Thrust]" << "\n";
			cout << "\t\t            DMG +5" << "\n";
			cout << "\t\t            Critical Chance +5" << "\n";
			cout << "\t\t            ACC -10" << "\n";
		}
		//Slash Normal
		//Thrust +5 DMG +5 Critical Chance -10 ACC

	}
	else if (weap == "Rusty Sword"){
      //Stats
		if (attr == "DMG") { val = 7; }
		if (attr == "ACC") { val = 100; }
		if (attr == "WEIGHT") { val = 2; }
		if (attr == "CRIT") { val = 15; }
		if (attr == "CRITDMG") { val = 200; }

		//Attacks
		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]SLASH                                        " << endl;
			cout << "\t\t\t             [1]THRUST                                       " << endl;
			cout << "\t\t\t             [2]NOTHING                                      " << endl;
			cout << "\t\t\t             [3]NOTHING                                      " << endl;
			cout << "\t\t\t             [B]Back                                         " << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SLASH!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			PlayerAttack(p, enemy);
		}
		if (attr == "A2") {
			//Thrust

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            THRUST!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG = 5;
			p.aCritch = 10;
			p.aACC = -10;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aCritch = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}
		if (attr == "A4") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Short Sword " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Slash] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Thrust]" << "\n";
			cout << "\t\t            DMG +5" << "\n";
			cout << "\t\t            Critical Chance +5" << "\n";
			cout << "\t\t            ACC -10" << "\n";
		}
		//Slash Normal
		//Thrust +5 DMG +5 Critical Chance -10 ACC
	}
	else if (weap == "Excalibur"){
        //Stats
		if (attr == "DMG") { val = 15; }
		if (attr == "ACC") { val = 100; }
		if (attr == "WEIGHT") { val = 2; }
		if (attr == "CRIT") { val = 15; }
		if (attr == "CRITDMG") { val = 300; }

		//Attacks
		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]SLASH                                        " << endl;
			cout << "\t\t\t             [1]THRUST                                       " << endl;
			cout << "\t\t\t             [2]NOTHING                                      " << endl;
			cout << "\t\t\t             [3]NOTHING                                      " << endl;
			cout << "\t\t\t             [B]Back                                         " << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SLASH!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			PlayerAttack(p, enemy);
		}
		if (attr == "A2") {
			//Thrust

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            THRUST!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG = 5;
			p.aCritch = 10;
			p.aACC = -10;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aCritch = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}
		if (attr == "A4") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Short Sword " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Slash] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Thrust]" << "\n";
			cout << "\t\t            DMG +5" << "\n";
			cout << "\t\t            Critical Chance +5" << "\n";
			cout << "\t\t            ACC -10" << "\n";
		}
		//Slash Normal
		//Thrust +5 DMG +5 Critical Chance -10 ACC
	}
	else if (weap == "Stormbringer"){
        //Stats
		if (attr == "DMG") { val = 30; }
		if (attr == "ACC") { val = 100; }
		if (attr == "WEIGHT") { val = 2; }
		if (attr == "CRIT") { val = 15; }
		if (attr == "CRITDMG") { val = 250; }

		//Attacks
		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]SLASH                                        " << endl;
			cout << "\t\t\t             [1]THRUST                                       " << endl;
			cout << "\t\t\t             [2]NOTHING                                      " << endl;
			cout << "\t\t\t             [3]NOTHING                                      " << endl;
			cout << "\t\t\t             [B]Back                                         " << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SLASH!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			PlayerAttack(p, enemy);
		}
		if (attr == "A2") {
			//Thrust

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            THRUST!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG = 5;
			p.aCritch = 10;
			p.aACC = -10;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aCritch = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}
		if (attr == "A4") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Short Sword " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Slash] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Thrust]" << "\n";
			cout << "\t\t            DMG +5" << "\n";
			cout << "\t\t            Critical Chance +5" << "\n";
			cout << "\t\t            ACC -10" << "\n";
		}
		//Slash Normal
		//Thrust +5 DMG +5 Critical Chance -10 ACC
	}
	else if (weap == "Long Sword") {
		//Stats
		if (attr == "DMG") { val = 15; }
		if (attr == "ACC") { val = 100; }
		if (attr == "WEIGHT") { val = 5; }
		if (attr == "CRIT") { val = 10; }
		if (attr == "CRITDMG") { val = 150; }

		//Attack Cooldown
		string a1n = "SLASH          ";
		string a2n = "HEAVY STRIKE   ";
		string a3n = "SHEATHE        ";
		string a4n = "NOTHING        ";

		if (p.wac1 > 0) { a1n = "COOLDOWN:"; a1n += to_string(p.wac1); }
		if (p.wac2 > 0) { a2n = "COOLDOWN:"; a2n += to_string(p.wac2); }
		if (p.wac3 > 0) { a3n = "COOLDOWN:"; a3n += to_string(p.wac3); }
		if (p.wac4 > 0) { a4n = "COOLDOWN:"; a4n += to_string(p.wac4); }

		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]" << a1n << endl;
			cout << "\t\t\t             [1]" << a2n << endl;
			cout << "\t\t\t             [2]" << a3n << endl;
			cout << "\t\t\t             [3]" << a4n << endl;
			cout << "\t\t\t             [B]Back" << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Light Attack

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SLASH!" << endl;
			cout << "\t\t\t"; system("pause");
			//Effect
			PlayerAttack(p, enemy);
			p.aDMG = 0;
		}
		if (attr == "A2") {

			//Cooldown Check
			if (p.wac2 > 0) {
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            ITS NOT READY!" << endl;
				cout << "\t\t\t";
				system("pause");
			}
			else
			{
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            HEAVY STRIKE!" << endl;
				cout << "\t\t\t"; system("pause");

				p.wac2 = 5;
				p.aACC = -20;
				p.aCritch = 5;
				p.aCritdmg = 20;
				p.aDMG += 20;
				PlayerAttack(p, enemy);
				p.aACC = 0;
				p.aCritch = 0;
				p.aCritdmg = 0;
				p.aDMG = 0;
			}
		}
		if (attr == "A3") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SHEATHE!" << endl;
			cout << "\t\t\t"; system("pause");

			p.aDMG = 20;
		}
		if (attr == "A4") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Long Sword " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Slash] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Heavy Strike]" << "\n";
			cout << "\t\t            Cooldown 5" << "\n";
			cout << "\t\t            DMG +10" << "\n";
			cout << "\t\t            Critical Chance +5%" << "\n";
			cout << "\t\t            Critical DMG +20%" << "\n";
			cout << "\t\t            ACC -10" << "\n";
			cout << "\t\t            [Sheathe]" << "\n";
			cout << "\t\t            DMG +20 (Next Turn)" << "\n";
		}
		//Slash Normal
		//Heavy Slash +10 DMG, -10 ACC
		//Impale +10 DMG, +50% Critical DMG, -25 ACC
	}
	else if (weap == "Knife") {
		//Stats
		if (attr == "DMG") { val = 3; }
		if (attr == "ACC") { val = 100; }
		if (attr == "WEIGHT") { val = 1; }
		if (attr == "CRIT") { val = 20; }
		if (attr == "CRITDMG") { val = 400; }

		//Attack Cooldown
		string a1n = "SLASH          ";
		string a2n = "STAB           ";
		string a3n = "THROW          ";
		string a4n = "NOTHING        ";

		if (p.wac1 > 0) { a1n = "COOLDOWN:"; a1n += to_string(p.wac1); }
		if (p.wac2 > 0) { a2n = "COOLDOWN:"; a2n += to_string(p.wac2); }
		if (p.wac3 > 0) { a3n = "COOLDOWN:"; a3n += to_string(p.wac3); }
		if (p.wac4 > 0) { a4n = "COOLDOWN:"; a4n += to_string(p.wac4); }

		//Attacks
		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]" << a1n << endl;
			cout << "\t\t\t             [1]" << a2n << endl;
			cout << "\t\t\t             [2]" << a3n << endl;
			cout << "\t\t\t             [3]" << a4n << endl;
			cout << "\t\t\t             [B]Back" << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            SLASH!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			PlayerAttack(p, enemy);
		}
		if (attr == "A2") {
			//Heavy Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            STAB!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG = 8;
			p.aCritch = 10;
			p.aACC = -20;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aCritch = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Throw

			//Cooldown Check
			if (p.wac3 > 0) {
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            ITS NOT READY!" << endl;
				cout << "\t\t\t";
				system("pause");
			}
			else
			{
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            THROW!" << endl;
				cout << "\t\t\t";
				system("pause");
				//Effect
				p.wac3 = 3;
				p.aACC = -20;
				p.extdodch += 0.20;
				p.aCritch = 20;
				PlayerAttack(p, enemy);
				p.aACC = 0;
				p.aCritch = 0;
			}
		}
		if (attr == "A4") {
			//Nothing
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            YOU DID NOTHING!" << endl;
			cout << "\t\t\t";
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Knife" << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Slash] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Stab] " << "\n";
			cout << "\t\t            DMG +8" << "\n";
			cout << "\t\t            CRIT +10%" << "\n";
			cout << "\t\t            ACC -20" << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Throw]" << "\n";
			cout << "\t\t            Cooldown 3" << "\n";
			cout << "\t\t            ACC -20" << "\n";
			cout << "\t\t            DODGE +20" << "\n";
			cout << "\t\t            CRIT +20%" << "\n";
		}
		//Slash Normal
		//Stab +8 DMG, +10% CRIT, -20 ACC
		//Throw (CD 3) -20 ACC, +20 DODGE, +20% CRIT
	}
	else if (weap == "Light Bow") {
		if (attr == "DMG") { val = 8; }
		if (attr == "ACC") { val = 90; }
		if (attr == "WEIGHT") { val = 3; }
		if (attr == "CRIT") { val = 15; }
		if (attr == "CRITDMG") { val = 200; }

		string a1n = "NORMAL SHOT          ";
		string a2n = "QUICKSHOT           ";
		string a3n = "MULTI SHOT          ";
		string a4n = "STRAFE SHOT        ";

		if (p.wac1 > 0) { a1n = "COOLDOWN:"; a1n += to_string(p.wac1); }
		if (p.wac2 > 0) { a2n = "COOLDOWN:"; a2n += to_string(p.wac2); }
		if (p.wac3 > 0) { a3n = "COOLDOWN:"; a3n += to_string(p.wac3); }
		if (p.wac4 > 0) { a4n = "COOLDOWN:"; a4n += to_string(p.wac4); }

		//Attacks
		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]" << a1n << endl;
			cout << "\t\t\t             [1]" << a2n << endl;
			cout << "\t\t\t             [2]" << a3n << endl;
			cout << "\t\t\t             [3]" << a4n << endl;
			cout << "\t\t\t             [B]Back" << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            NORMAL SHOT!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			PlayerAttack(p, enemy);
		}
		if (attr == "A2") {
			//Heavy Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            QUICKSHOT!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG = 4;
			p.aACC = -3;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Throw

			//Cooldown Check
			if (p.wac3 > 0) {
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            ITS NOT READY!" << endl;
				cout << "\t\t\t";
				system("pause");
			}
			else
			{
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            MULTI SHOT!" << endl;
				cout << "\t\t\t";
				system("pause");
				//Effect
				p.wac3 = 3;
				p.aACC = 7;
				p.aDMG = 20;
				p.aCritch = 10;
				PlayerAttack(p, enemy);
				p.aDMG = 0;
				p.aACC = 0;
				p.aCritch = 0;
			}
		}
		if (attr == "A4") {
			if (p.wac3 > 0) {
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            ITS NOT READY!" << endl;
				cout << "\t\t\t";
				system("pause");
			}
			else
			{
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            STRAFE SHOT!" << endl;
				cout << "\t\t\t";
				system("pause");
				//Effect
				p.wac3 = 5;
				p.aACC = -2;
				p.aDMG = 3;
				p.extdodch += 0.40;
				PlayerAttack(p, enemy);
				p.aDMG = 0;
				p.aACC = 0;
			}
		}

		//Info
		if (attr == "INFO") {
			cout << "\t\t            Light Bow" << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Normal Shot] " << "\n";
			cout << "\t\t            Normal " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Quickshot] " << "\n";
			cout << "\t\t            DMG +4" << "\n";
			cout << "\t\t            ACC -3" << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Multi Shot]" << "\n";
			cout << "\t\t            Cooldown 3" << "\n";
			cout << "\t\t            ACC +7" << "\n";
			cout << "\t\t            DMG +20" << "\n";
			cout << "\t\t            CRIT +10%" << "\n";
			cout << "\t\t            [Strafe Shot]" << "\n";
			cout << "\t\t            Cooldown 5" << "\n";
			cout << "\t\t            ACC -7" << "\n";
			cout << "\t\t            DMG +3" << "\n";
			cout << "\t\t            Extra Dodge +0.40%" << "\n";
		}
		//Slash Normal
		//Stab +8 DMG, +10% CRIT, -20 ACC
		//Throw (CD 3) -20 ACC, +20 DODGE, +20% CRIT
	}
	else if (weap == "Heavy Bow") {
		//Stats
		if (attr == "DMG") { val = 15; }
		if (attr == "ACC") { val = 95; }
		if (attr == "WEIGHT") { val = 10; }
		if (attr == "CRIT") { val = 17; }
		if (attr == "CRITDMG") { val = 270; }

		string a1n = "HEAVY SHOT          ";
		string a2n = "POWER SHOT           ";
		string a3n = "DODGE ROLL          ";
		string a4n = "STATIC STRIKE        ";

		if (p.wac1 > 0) { a1n = "COOLDOWN:"; a1n += to_string(p.wac1); }
		if (p.wac2 > 0) { a2n = "COOLDOWN:"; a2n += to_string(p.wac2); }
		if (p.wac3 > 0) { a3n = "COOLDOWN:"; a3n += to_string(p.wac3); }
		if (p.wac4 > 0) { a4n = "COOLDOWN:"; a4n += to_string(p.wac4); }

		if (attr == "ATTACK") {
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t\t             [0]" << a1n << endl;
			cout << "\t\t\t             [1]" << a2n << endl;
			cout << "\t\t\t             [2]" << a3n << endl;
			cout << "\t\t\t             [3]" << a4n << endl;
			cout << "\t\t\t             [B]Back" << endl;
			cout << "\n\t\t >> ";
		}
		if (attr == "A1") {
			//Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            HEAVY SHOT!" << endl;
			cout << "\t\t\t";
			system("pause");
			p.aDMG += 10;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			//Effect
		}
		if (attr == "A2") {
			//Heavy Slash

			//UI
			drawEnemyFight(p, enemy, "Event");
			cout << "\t\t                            POWER SHOT!" << endl;
			cout << "\t\t\t";
			system("pause");
			//Effect
			p.aDMG += 10;
			p.aACC = -2;
			p.exthitch = +0.30;
			PlayerAttack(p, enemy);
			p.aDMG = 0;
			p.aACC = 0;
		}
		if (attr == "A3") {
			//Throw

			//Cooldown Check
			if (p.wac3 > 0) {
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            ITS NOT READY!" << endl;
				cout << "\t\t\t";
				system("pause");
			}
			else
			{
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            DODGE ROLL!" << endl;
				cout << "\t\t\t";
				system("pause");
				//Effect
				p.wac3 = 5;
				p.aACC = -3;
				p.aDMG += 3;
				p.extdodch += 0.103 ;
				PlayerAttack(p, enemy);
				p.aDMG = 0;
				p.aACC = 0;
			}
		}
		if (attr == "A4") {

			if (p.wac4 > 0) {
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            ITS NOT READY!" << endl;
				cout << "\t\t\t";
				system("pause");
			}
			else
			{
				//UI
				drawEnemyFight(p, enemy, "Event");
				cout << "\t\t                            STATIC STRIKE!" << endl;
				cout << "\t\t\t";
				system("pause");
				//Effect
				p.wac4 = 10;
				p.aACC = 20;
				p.aDMG += 15;
				p.exthitch += 0.50;
				p.extcritch += 0.30;
				PlayerAttack(p, enemy);
				p.aDMG = 0;
				p.aACC = 0;
			}
		}

		if (attr == "INFO") {
			cout << "\t\t            Heavy Bow" << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Heavy Shot] " << "\n";
			cout << "\t\t            DMG +15 " << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Power Shot] " << "\n";
			cout << "\t\t            DMG +10" << "\n";
			cout << "\t\t            ACC -5" << "\n";
			cout << "\t\t            " << "\n";
			cout << "\t\t            [Roll & Shot]" << "\n";
			cout << "\t\t            Cooldown 5" << "\n";
			cout << "\t\t            ACC -3" << "\n";
			cout << "\t\t            DMG +3" << "\n";
			cout << "\t\t            Extra Dodge +10%" << "\n";
			cout << "\t\t            [Static Strike]" << "\n";
			cout << "\t\t            Cooldown 10" << "\n";
			cout << "\t\t            ACC +20" << "\n";
			cout << "\t\t            DMG +15" << "\n";
			cout << "\t\t            Extra Hit +0.50%" << "\n";
			cout << "\t\t            Extra Crit +0.30%" << "\n";
		}
	}

	return val;

}

void drawEnemyFight(Player& p, Enemy& enemy, string type) {
    system("cls");
	string space = "";
	int ensize = 0;
	while (enemy.enemyname[ensize] != '\0') ensize++;
	if (ensize < 7) {
		for (int i = 0;i < 3; i++) {
			space += " ";
		}
	}

    if ((enemy.enemyname == "Phoenix" || enemy.enemyname == "Centaur") && type == "Player Turn"){
        system("cls");
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t                               " << space << enemy.enemyname << "        " << endl;
		cout << "\t\t\t                               " << space << enemy.HEALTH << "/" << 500 + (10 * enemy.stat.HP) << endl;
		cout << "\t\t\t                             " << enemy.art[0] << endl;
		cout << "\t\t\t                             " << enemy.art[1] << endl;
		cout << "\t\t\t                             " << enemy.art[2] << endl;
		cout << "\t\t\t                             " << enemy.art[3] << endl;
		cout << "\t\t\t                             " << enemy.art[4] << endl;
		cout << "\t\t\t                             " << enemy.art[5] << endl;
		cout << "\t\t\t                             " << enemy.art[6] << endl;
		cout << "\t\t\t                             " << enemy.art[7] << endl;
		cout << "\t\t\t                             " << enemy.art[8] << endl;
		cout << "\t\t\t                             " << enemy.art[9] << endl;
		cout << "\t\t\t                             " << enemy.art[10] << endl;
		cout << "\t\t\t                             " << enemy.art[11] << endl;
		cout << "\n";
		cout << "\t\t     o=============================================================================o" << endl;
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t             [A]ATTACK         [I]INVENTORY        [R]RUN AWAY    " << endl;
		cout << "\n\t\t\t    Health: " << p.php << "                              Previous Damage: " << enemy.lhdmg << endl;
    }
    else if ((enemy.enemyname == "Phoenix" || enemy.enemyname == "Centaur") && type == "Event"){
        system("cls");
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t                               " << space << enemy.enemyname << "        " << endl;
		cout << "\t\t\t                               " << space << enemy.HEALTH << "/" << 500 + (10 * enemy.stat.HP) << endl;
		cout << "\t\t\t                             " << enemy.art[0] << endl;
		cout << "\t\t\t                             " << enemy.art[1] << endl;
		cout << "\t\t\t                             " << enemy.art[2] << endl;
		cout << "\t\t\t                             " << enemy.art[3] << endl;
		cout << "\t\t\t                             " << enemy.art[4] << endl;
		cout << "\t\t\t                             " << enemy.art[5] << endl;
		cout << "\t\t\t                             " << enemy.art[6] << endl;
		cout << "\t\t\t                             " << enemy.art[7] << endl;
		cout << "\t\t\t                             " << enemy.art[8] << endl;
		cout << "\t\t\t                             " << enemy.art[9] << endl;
		cout << "\t\t\t                             " << enemy.art[10] << endl;
		cout << "\t\t\t                             " << enemy.art[11] << endl;
		cout << "\n";
		cout << "\t\t     o=============================================================================o" << endl;
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t             [A]ATTACK         [I]INVENTORY        [R]RUN AWAY    " << endl;
		cout << "\n\t\t\t    Health: " << p.php << "                              Previous Damage: " << enemy.lhdmg << endl;
		cout << "\t\t\t                                                 " << endl;
    }
	//Player Turn
	else if (type == "Player Turn") {
		system("cls");
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t                               " << space << enemy.enemyname << "        " << endl;
		cout << "\t\t\t                               " << space << enemy.HEALTH << "/" << 100 + (10 * enemy.stat.HP) << endl;
		cout << "\t\t\t                             " << enemy.art[0] << endl;
		cout << "\t\t\t                             " << enemy.art[1] << endl;
		cout << "\t\t\t                             " << enemy.art[2] << endl;
		cout << "\t\t\t                             " << enemy.art[3] << endl;
		cout << "\t\t\t                             " << enemy.art[4] << endl;
		cout << "\t\t\t                             " << enemy.art[5] << endl;
		cout << "\t\t\t                             " << enemy.art[6] << endl;
		cout << "\t\t\t                             " << enemy.art[7] << endl;
		cout << "\t\t\t                             " << enemy.art[8] << endl;
		cout << "\t\t\t                             " << enemy.art[9] << endl;
		cout << "\t\t\t                             " << enemy.art[10] << endl;
		cout << "\t\t\t                             " << enemy.art[11] << endl;
		cout << "\t\t     o=============================================================================o" << endl;
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t             [A]ATTACK         [I]INVENTORY        [R]RUN AWAY    " << endl;
		cout << "\n\t\t\t    Health: " << p.php << "                              Previous Damage: " << enemy.lhdmg << endl;
		cout << "\t\t\t                                                 " << endl;
		cout << "\n\t\t >> ";
	}


	// Enemy Turn
	else if (type == "Event") {
		system("cls");
		cout << "\t\t\t                                                 " << endl;
		cout << "\t\t\t                               " << space << enemy.enemyname << "        " << endl;
		cout << "\t\t\t                               " << space << enemy.HEALTH << "/" << 100 + (10 * enemy.stat.HP) << endl;
		cout << "\t\t\t                             " << enemy.art[0] << endl;
		cout << "\t\t\t                             " << enemy.art[1] << endl;
		cout << "\t\t\t                             " << enemy.art[2] << endl;
		cout << "\t\t\t                             " << enemy.art[3] << endl;
		cout << "\t\t\t                             " << enemy.art[4] << endl;
		cout << "\t\t\t                             " << enemy.art[5] << endl;
		cout << "\t\t\t                             " << enemy.art[6] << endl;
		cout << "\t\t\t                             " << enemy.art[7] << endl;
		cout << "\t\t\t                             " << enemy.art[8] << endl;
		cout << "\t\t\t                             " << enemy.art[9] << endl;
		cout << "\t\t\t                             " << enemy.art[10] << endl;
		cout << "\t\t\t                             " << enemy.art[11] << endl;
		cout << "\t\t     o=============================================================================o" << endl;
		cout << "\t\t\t                                                 " << endl;
	}
}

void PlayerAttack(Player& p, Enemy& enemy) {

	//UI Setup
	drawEnemyFight(p, enemy, "Event");
	system("cls");

	//Attributes (so that they can be changed by weapon)
	p.weapdmg *= 2;
	int ATK = p.sk.ATK;
	int DEF = p.sk.DEF;
	int SPD = p.sk.SPD;
	int HP = p.sk.HP;
	int LUK = p.sk.LUK;
	int eATK = (enemy.stat.ATK) * p.l;
	int eDEF = enemy.stat.DEF;
	int eSPD = enemy.stat.SPD;
	int eHP = (enemy.stat.HP) * p.l;
	int eLUK = enemy.stat.LUK;

	{
		//Attribute Changes
		if (ATK < PlayerWeapon(p, enemy, "WEIGHT")) { SPD -= PlayerWeapon(p, enemy, "WEIGHT") - ATK; }
	}

	//Player Weapon Setup
	int wdmg = PlayerWeapon(p, enemy, "DMG") + p.weapdmg;
	int wacc = PlayerWeapon(p, enemy, "ACC");
	int wweight = PlayerWeapon(p, enemy, "WEIGHT");
	int wcrtch = PlayerWeapon(p, enemy, "CRIT");
	int wcrtdmg = PlayerWeapon(p, enemy, "CRITDMG");

	//Player Reaction
	int dmg = ATK + wdmg + p.aDMG; // Player Damage
	float acc = (wacc / 100.0) + p.exthitch + (p.aACC / 100.0);
	float missChance = 1 - acc;
	float critChance = (LUK / 100.0) + (wcrtch / 100.0) + p.extcritch + (p.aCritch / 100.0); // Player Critical Chance
	float CritDamage = dmg * ((wcrtdmg + p.aCritdmg) / 100.0); // Player Critical Damage

	//Enemy Reaction
	float edodgeChance = 0.20 + (eSPD * 0.01) + (1 - acc); // Enemy Dodge

	//Attack Phase
	int rand1 = (rand() % 5) + 1; // same as dice rolling
	int rand2 = rand() % 100;
	int rand3 = rand() % 100;

	//Miss or Dodge or Hit
	if (rand3 <= missChance * 100) {

		//Miss
		p.exthitch += 0.03;

		//UI
		drawEnemyFight(p, enemy, "Event");
		fightNarrator("PlayerMiss");
		cout << "\t\t\t";
		system("pause");
		system("cls");

	}
	else if (rand3 <= edodgeChance * 100) {

		//Dodged
		p.exthitch += 0.03;

		//UI
		drawEnemyFight(p, enemy, "Event");
		fightNarrator("EnemyDodge");
		cout << "\t\t\t";
		system("pause");
		system("cls");

	}
	else {

		//Hit
		p.exthitch = 0;

		//Critical Hit or Normal Hit
		if (rand2 < critChance * 100) {

			//Damage
			dmg = CritDamage * rand1;
			if (dmg < 1) { dmg = 1; } //Prevents damage from healing enemies with high Defense, Damage is 1 when less than 1
			//Reset Crit Chance
			p.extcritch = 0;

			//UI
			drawEnemyFight(p, enemy, "Event");
			fightNarrator("PlayerCrit");
			cout << "\t\t                            Damage:" << dmg << endl;
			cout << "\t\t\t";
			system("pause");
			system("cls");
		}
		else {

			//Damage
			dmg = (dmg * rand1) - DEF;
			if (dmg < 1) { dmg = 1; } //Prevents damage from healing enemies with high Defense
			//Increase Crit Chance
			p.extcritch += 0.01;

			//UI
			drawEnemyFight(p, enemy, "Event");
			fightNarrator("PlayerHit");
			cout << "\t\t                            Damage:" << dmg << endl;
			cout << "\t\t\t";
			system("pause");
			system("cls");
		}
		enemy.HEALTH = enemy.HEALTH - dmg;

	}
}

void EnemyAttack(Player& p, Enemy& enemy) {

	//UI Setup
	drawEnemyFight(p, enemy, "Event");

	//Attributes (so that they can be changed by debuffs or weapon)
	int ATK = p.sk.ATK;
	int DEF = p.sk.DEF;
	int SPD = p.sk.SPD;
	int HP = p.sk.HP;
	int LUK = p.sk.LUK;
	int eATK = (enemy.stat.ATK) * p.l;
	int eDEF = enemy.stat.DEF;
	int eSPD = enemy.stat.SPD;
	int eHP = (enemy.stat.HP) * p.l;
	int eLUK = enemy.stat.LUK;

	//Enemy Reaction
	int edmg;
	if (enemy.enemyname == "Phoenix"){
        edmg = eATK + 20;
	}
	else {
        edmg = eATK; // Enemy Damag     e
	}
	float acc = (enemy.weapon.acc / 100.0);
	float missChance = 1 - acc;
	float ecritChance = enemy.stat.LUK * 0.10; // Enemy Critical Chance
	float eCritDamage = enemy.stat.ATK * 1.5; // Enemy Critical Damage

	//Player Reaction
	float pdodgeChance = 0.20 + (SPD * 0.01) + (1 - acc) + (p.extdodch); // Enemy Dodge

	//Attack Phase
	cout << "\t\t                            ENEMY ATTACK!" << endl;
	cout << "\t\t\t";
	system("pause");
	system("cls");
	int rand1 = (rand() % 5) + 1; // same as dice rolling
	int rand2 = rand() % 100; // crit or basic dmg
	int rand3 = rand() % 100; // miss or dodge
	int rand4 = rand() % 2;

	//Miss or Dodge or Hit
	if (rand3 <= missChance * 100) {

		//UI
		drawEnemyFight(p, enemy, "Event");
		fightNarrator("EnemyMiss");
		cout << "\t\t\t";
		system("pause");

	}
	else if (rand3 <= pdodgeChance * 100) {

		//UI
		drawEnemyFight(p, enemy, "Event");
		fightNarrator("PlayerDodge");
		cout << "\t\t\t";
		system("pause");

	}
	else {
        int sdmg = 0;
		//Critical Hit or Normal Hit
        if (enemy.enemyname == "Phoenix" && rand4 == 1) {
            int randatk = rand() % 3;
            switch (randatk){
            case 0:
                //Overheat
                sdmg = 48;
                drawEnemyFight(p, enemy, "Event");
                cout << "\t\t                            YOUR ENEMY USED OVERHEAT" << endl;
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
                break;
            case 1:
                // Fire Spin
                sdmg = 15;
                drawEnemyFight(p, enemy, "Event");
                cout << "\t\t                            YOUR ENEMY USED FIRE SPIN" << endl;
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
                break;
            case 2:
                // Fire Blast
                sdmg = 20;
                drawEnemyFight(p, enemy, "Event");
                cout << "\t\t                            YOUR ENEMY USED FIRE BLAST" << endl;
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
                break;
            }
            edmg = (edmg + sdmg) - DEF;
        }
        else if (enemy.enemyname == "Centaur" && rand4 == 1){
            int randatk = rand() % 3;
            switch (randatk){
            case 0:
                //Overheat
                sdmg = 30;
                drawEnemyFight(p, enemy, "Event");
                cout << "\t\t                            YOUR ENEMY USED HOOF STRIKE" << endl;
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
                break;
            case 1:
                // Fire Spin
                sdmg = 25;
                drawEnemyFight(p, enemy, "Event");
                cout << "\t\t                            YOUR ENEMY USED MOUNTED CHARGE" << endl;
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
                break;
            case 2:
                // Fire Blast
                sdmg = 15;
                drawEnemyFight(p, enemy, "Event");
                cout << "\t\t                            YOUR ENEMY USED RAPID GALLOP" << endl;
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
                break;
            }
            edmg = (edmg + sdmg) - DEF;
        }
//        else if (enemy.enemyname == "Shrek" && rand4 = 3){
        else {
            if (rand2 < ecritChance * 100) {

                // Critical Damage
                edmg = eCritDamage + (edmg * rand1);
                if (edmg < 1) { edmg = 1; } //Prevents damage from healing enemies with high Defense, Damage is 1 when less than 1
                p.extdodch += 0.01;
                //UI
                drawEnemyFight(p, enemy, "Event");
                fightNarrator("EnemyCrit");
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
            }
            else {

                // Basic Damage
                edmg = (edmg * rand1) - DEF;
                if (edmg < 1) { edmg = 1; } //Prevents damage from healing enemies with high Defense
                p.extdodch += 0.01;

                //UI
                drawEnemyFight(p, enemy, "Event");
                fightNarrator("EnemyHit");
                cout << "\t\t                            Damage:" << edmg << endl;
                cout << "\t\t\t";
                system("pause");
            }
        }
		p.php = p.php - edmg;

	}

}
// --- Other Events ---
//Death
void PlayerDeath(Player& p, Enemy enemy) {
	drawEnemyFight(p, enemy, "Event");
	cout << "\t\t\t You died!" << endl;
	cout << "\t\t\t ";
	cout << "\t\t\t";
	system("pause");
	p.pweapon = p.spweapon;
	skills(p, true);
}

// --- Door Events ---

// When player meets Enemy
void enemyFight(Player& p) {

	//Randomize Enemy based on dungeon level (Not done yet)
	int randenemy = (rand() % 4) + 1;
	string e;
	switch (randenemy) {
	case 1:
		e = "Huge Spider";
		break;
	case 2:
		e = "Snek";
		break;
	case 3:
		e = "Slime";
		break;
	case 4:
		e = "Huge Bat";
		break;
	}

	Enemy enemy = initializeEnemy(e);
	// Enemy Fighting Query
	bool efightval = true;
	char efq[5];
	//
	srand((unsigned)time(NULL));

	while (efightval) {
		drawEnemyFight(p, enemy, "Player Turn");
		cin.getline(efq, sizeof(efq));

		if (strlen(efq) != 1){
            cout << "\n\nPlease try again..." << endl;
            system("pause");
            continue;
		}
        else {
            switch (efq[0]) {
            case 'A':
            case 'a':
                PlayerWeapon(p, enemy, "ATTACK");
                char q;
                cin >> q;
                cin.ignore();
                switch (q) {
                case '0':
                    PlayerWeapon(p, enemy, "A1");
                    break;
                case '1':
                    PlayerWeapon(p, enemy, "A2");
                    break;
                case '2':
                    PlayerWeapon(p, enemy, "A3");
                    break;
                case '3':
                    PlayerWeapon(p, enemy, "A4");
                    break;
                }

                //Cooldown
                if (p.wac1 > 0) { p.wac1 -= 1; }
                if (p.wac2 > 0) { p.wac2 -= 1; }
                if (p.wac3 > 0) { p.wac3 -= 1; }
                if (p.wac4 > 0) { p.wac4 -= 1; }

                //Enemy Death
                if (enemy.HEALTH <= 0) {

                    //UI
                    drawEnemyFight(p, enemy, "Event");

                    if (enemy.enemyname == "Phoenix" || enemy.enemyname == "Centaur"){
                        p.expgain += enemy.expdrop;
                    }
                    else {
                        enemy.expdrop = enemy.expdrop * p.l;
                        p.expgain += enemy.expdrop;
                    }

                    cout << "\t\t\t You Have Successfully slain the " << enemy.enemyname << "!" << endl;
                    cout << "\t\t\t You Are Rewarded " << enemy.expdrop << " exp and " << enemy.coindrop;
                    if (enemy.coindrop == 1) { cout << " coin" << endl; }
                    else { cout << " coins" << endl; }
                    cout << "\t\t\t The enemy dropped witch tokens: " << enemy.wtokendrop << endl;
                    cout << "\t\t\t";
                    system("pause");

                    //Rewards and exit
                    p.dl++;
                    p.coins += enemy.coindrop;
                    p.wtokens += enemy.wtokendrop;
                    p.php += p.ab2;
                    explevel(p, enemy);

                    efightval = false;
                }
                else {
                    //Enemy Attack Phase
                    EnemyAttack(p, enemy);
                    if (p.php <= 0) {

                        p.l = 1;
                        p.expgain = 0;
                        p.dl = 1;

                        //system("cls");
                        //cout << "\n\n\n\n";
                        efightval = false;
                        PlayerDeath(p, enemy);
                    }
                }
                break;
            default:
                cout << "\n\nPlease try again..." << endl;
                system("pause");
                break;
            }
        }

	}
	doors(p);
}

string RandomWeapDrop(int RandomWeap) {
	string weapos[4] = {
		"Long Sword", "Heavy Bow", "Light Bow",
		"Knife" };
	return weapos[RandomWeap];
}

void TreasurePlace(Player& p) {
    char pickedWeap[5];
	int randweap[3];
	for (int i = 0;i < 3;i++) {
		randweap[i] = rand() % 4;
	}
	string wn1 = RandomWeapDrop(randweap[0]);
	string wn2 = RandomWeapDrop(randweap[1]);
	string wn3 = RandomWeapDrop(randweap[2]);
	do {
        system("cls");
        // spaces
        string space1 = RandomWeapDrop(randweap[0]);
        string space2 = RandomWeapDrop(randweap[1]);
        string space3 = RandomWeapDrop(randweap[2]);
        while (space1.size() < 15) { space1 += " "; }
        while (space2.size() < 15) { space2 += " "; }
        while (space3.size() < 15) { space3 += " "; }

        cout << "\n\n\n\n\n";
        cout << "\t\t\t     o===================================================================o\n\n";
        cout << "\t\t                                         Treasure  Place" << endl;
        cout << "\t\t                                          Pick a Weapon" << endl;
        cout << "\n\n";
        cout << "\t\t                       [0]" << space1 << "[1]" << space2 << "[2]" << space3;
        cout << "\n\n";
        cout << "\t\t\t     o===================================================================o";

        cout << "\n\n\t\t     >> ";
        cin.getline(pickedWeap, sizeof(pickedWeap));

        if (strlen(pickedWeap) != 1){
            cout << "\t\t       Wrong input.." << endl;
            system("pause");
            continue;
        }
        else {
            switch (pickedWeap[0]) {
            case '0':
                p.pweapon = wn1;
                break;
            case '1':
                p.pweapon = wn2;
                break;
            case '2':
                p.pweapon = wn3;
                break;
            default:
                cout << "\n\t\t\tPlease try again.." << endl;
                cout << "\t\t\t"; system("pause");
                break;
            }

            cout << "\n\t\t\tYou have selected: " << p.pweapon << endl;
            cout << "\t\t\t"; system("pause");
            system("cls");
            doors(p);
        }
	} while(true);

}

void RestPlace(Player& p) {
	system("cls");
	int heal;
	cout << "\n\n\n\n\n";
	cout << "\t\t\t     o===================================================================o\n\n";
	cout << "\t\t\t                                    Rest Place" << endl;
	cout << "\n";
	cout << "\t\t\t                              Get some rest warrior!" << endl;
	cout << "\n\n";
	cout << "\t\t\t     o===================================================================o";
	cout << "\n";

	if (p.php >= 100) {
		heal = 10;
	}
	else if (p.php <= 90) {
		heal = 30;
	}
	else {
		heal = 70;
	}
	cout << "\n";
	cout << "\t\t\t     Your Current HP: " << p.php << " + " << heal << endl;
	p.php += heal;
	cout << "\t\t\t     "; system("pause");
	doors(p);
}
// When player meets Boss
void bossEncounter(Player& p, string enemy){
    system("cls");
    if (enemy == "Phoenix"){
        cout << "\t\t  :==================:                                                         :==================:" << endl;
        cout << "\t\t   .~=++++===+++++=~.                                                           .~=++++===+++++=~." << endl;
        cout << "\t\t     ~~-:.    .:-~:                                                              ~~-:.    .:-~:" << endl;
        cout << "\t\t      .~~-:..:-~=                                                                 .~~-:..:-~=" << endl;
        cout << "\t\t      ~-::..::-~                                                                   ~-::..::-~" << endl;
        cout << "\t\t      --.--:-.~~                                                                   --.--:-.~~" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: -- " << endl;
        cout << "\t\t      :: .--: --                                                                   :: :--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: :--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: :--: --" << endl;
        cout << "\t\t      :: :--- --                                                                   :: :--- --" << endl;
        cout << "\t\t      :: :--- --                                                                   :: :--- --" << endl;
        cout << "\t\t      :- :--- --                                                                   :- :--- --" << endl;
        cout << "\t\t      --.----.~~                                                                   --.----.~~" << endl;
        cout << "\t\t     .-::....::-.                                                                 .-::....::-." << endl;
        cout << "\t\t     -=~~----~~=-                                                                 -=~~----~~=-" << endl;
        cout << "\t\t    ---::....::--:                                                               ---::....::--:" << endl;
        cout << "\t\t   -==+========+==-                                                             -==+========+==-" << endl;
        cout << "\t\t  .=++++++++++++++~.                                                           .=++++++++++++++~." << endl;
        cout << "\t\t.=================================================================================================" << endl;
        cout << "\t\t               .====================================================================." << endl;
        cout << "\t\t                                  .===========================." << endl;
        cout << "\t\t                                 You have entered a large Room..." << endl;
        cout << "\n\t\t                                  "; system("pause");
        cout << "\n\n";
        cout << "                                   You have found the PHOENIX!" << endl;
        cout << "                                   "; system("pause");
    }
    else if (enemy == "Centaur") {
        cout << "\t\t  :==================:                                                         :==================:" << endl;
        cout << "\t\t   .~=++++===+++++=~.                                                           .~=++++===+++++=~." << endl;
        cout << "\t\t     ~~-:.    .:-~:                                                              ~~-:.    .:-~:" << endl;
        cout << "\t\t      .~~-:..:-~=                                                                 .~~-:..:-~=" << endl;
        cout << "\t\t      ~-::..::-~                                                                   ~-::..::-~" << endl;
        cout << "\t\t      --.--:-.~~                                                                   --.--:-.~~" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .-:: --                                                                   :: .-:: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: .--: -- " << endl;
        cout << "\t\t      :: .--: --                                                                   :: :--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: :--: --" << endl;
        cout << "\t\t      :: .--: --                                                                   :: :--: --" << endl;
        cout << "\t\t      :: :--- --                                                                   :: :--- --" << endl;
        cout << "\t\t      :: :--- --                                                                   :: :--- --" << endl;
        cout << "\t\t      :- :--- --                                                                   :- :--- --" << endl;
        cout << "\t\t      --.----.~~                                                                   --.----.~~" << endl;
        cout << "\t\t     .-::....::-.                                                                 .-::....::-." << endl;
        cout << "\t\t     -=~~----~~=-                                                                 -=~~----~~=-" << endl;
        cout << "\t\t    ---::....::--:                                                               ---::....::--:" << endl;
        cout << "\t\t   -==+========+==-                                                             -==+========+==-" << endl;
        cout << "\t\t  .=++++++++++++++~.                                                           .=++++++++++++++~." << endl;
        cout << "\t\t.=================================================================================================" << endl;
        cout << "\t\t               .====================================================================." << endl;
        cout << "\t\t                                  .===========================." << endl;
        cout << "\t\t                                 You have entered a large Room..." << endl;
        cout << "\n\n";
        cout << "\t\t"; system("pause");
    }
}
void BossFight(Player& p) {
	system("cls");
	string Bname;

    if (p.dl == 10){
        Bname = "Phoenix";
    }
    else if (p.dl == 20){
        Bname = "Centaur";
    }
    else if (p.dl == 30){
        Bname = "Dragon";
    }


	Enemy bb = initializeEnemy(Bname);

    bossEncounter(p, Bname);
	bool BFightVal = true;
	char bfq[5];

    while (BFightVal) {
        system("cls");
        drawEnemyFight(p, bb, "Player Turn");
        cout << "\n\t\t >> ";
        cin >> bfq;

        switch (bfq[0]) {
		case 'A':
		case 'a':
			PlayerWeapon(p, bb, "ATTACK");
			char q;
			cin >> q;
			switch (q) {
			case '0':
				PlayerWeapon(p, bb, "A1");
				break;
			case '1':
				PlayerWeapon(p, bb, "A2");
				break;
			case '2':
				PlayerWeapon(p, bb, "A3");
				break;
			case '3':
				PlayerWeapon(p, bb, "A4");
				break;
			}

			//Cooldown
			if (p.wac1 > 0) { p.wac1 -= 1; }
			if (p.wac2 > 0) { p.wac2 -= 1; }
			if (p.wac3 > 0) { p.wac3 -= 1; }
			if (p.wac4 > 0) { p.wac4 -= 1; }

			//bb Death
			if (bb.HEALTH <= 0) {

				//UI
				drawEnemyFight(p, bb, "Event");
				cout << "\t\t\t You Have Successfully slain the " << bb.enemyname << "!" << endl;
				cout << "\t\t\t You Are Rewarded " << bb.expdrop << " exp and " << bb.coindrop;
				if (bb.expdrop == 1) { cout << " coin" << endl; }
				else { cout << " coins" << endl; }
				cout << "\t\t\t";
				system("pause");

				//Rewards and exit
				p.dl++;
				p.l++;
				p.sp++;
				p.coins += bb.coindrop;
				p.expgain += bb.expdrop;
				explevel(p, bb);
				BFightVal = false;

			}
			else {
				//Enemy Attack Phase
				EnemyAttack(p, bb);
				if (p.php <= 0) {

					p.l = 1;
					p.expgain = 0;
					p.dl = 1;

					//system("cls");
					//cout << "\n\n\n\n";
					BFightVal = false;
					PlayerDeath(p, bb);
				}
			}
			break;
            default:
                cout << "\n\nPlease try again..." << endl;
		}
    }
}
