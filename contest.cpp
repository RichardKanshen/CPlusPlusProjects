#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <clocale>
#include <cmath>
#include "CONFunctions.h"

using namespace std;
class Game {
public:

	Functions FunctionDef;
	string lang, playerName="", mode, fightstatus, input, tb, decision1, decision1sub1, b1pathdec, decision2="";
	string diadec1, diadec2, diadec3, diadec4, diadec5;
	string b0, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
	const string mc = "\033[33m", vc = "\033[36m";
	int saveload, relwvoid, a=0, b=0, sequence, level, xp, requiredxp, xpgained, initiallvl, plvlbonusdmg, lives;
	double perlevel, hp, currenthp, maxdmg;
	bool isAlive = true, earlyexplanation = false, ExistujeSave;

	bool CheckSave() {
		const wstring folderPath = L"save";
		DWORD folderAttributes = GetFileAttributesW(folderPath.c_str());

		if (folderAttributes == INVALID_FILE_ATTRIBUTES || !(folderAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (CreateDirectoryW(folderPath.c_str(), nullptr) == 0 && GetLastError() != ERROR_ALREADY_EXISTS) {
				cerr << "[!] Save File Cannot be created!" << "\n";
				return false;
			}

			return false;
		}
		
		return true;
	}

	void UlozitInfo(const string& data, const string& fileName) {
		const string folderPath = "save";
		const string filePath = folderPath + "\\" + fileName;

		ofstream file(filePath);

		if (file.is_open()) {
			file << data;

			file.close();
		}
		else {
			cout << "[!] An error occurred";
		}
	}
	string PrecitatInfo(const string& fileName) {
		const string folderPath = "save";
		const string filePath = folderPath + "\\" + fileName;

		ifstream file(filePath);

		if (file.is_open()) {
			string data;
			getline(file, data);

			file.close();

			return data;
		}
		else {
			cout << "[!] An error occurred" << "\n";
			return "";
		}
	}
	void save() {
		UlozitInfo(to_string(sequence), "sequence.txt");
		UlozitInfo(to_string(level), "PlayerLevel.txt");
		UlozitInfo(to_string(xp), "PlayerXp.txt");
		UlozitInfo(to_string(hp), "PlayerHp.txt");
		UlozitInfo(to_string(currenthp), "PlayerCurrentHp.txt");
		UlozitInfo(to_string(maxdmg), "PlayerMaxDmg.txt");
		UlozitInfo(playerName, "PlayerName.txt");
		UlozitInfo(mode, "Mode.txt");
	}
	void load() {
		string strSequence = PrecitatInfo("sequence.txt");
		string strLevel = PrecitatInfo("PlayerLevel.txt");
		string strXp = PrecitatInfo("PlayerXp.txt");
		string strHp = PrecitatInfo("PlayerHp.txt");
		string strCurrenthp = PrecitatInfo("PlayerCurrentHp.txt");
		string strMaxdmg = PrecitatInfo("PlayerMaxDmg.txt");
		playerName = PrecitatInfo("PlayerName.txt");
		mode = PrecitatInfo("Mode.txt");
		lang = PrecitatInfo("Language.txt");

		sequence = stoi(strSequence);
		level = stoi(strLevel);
		xp = stoi(strXp);
		hp = stoi(strHp);
		currenthp = stoi(strCurrenthp);
		maxdmg = stoi(strMaxdmg);
		requiredxp=10*pow(1.2, level);
	}
	void checkLevelUp(string language){
		if(xp>=requiredxp){
			initiallvl = level;
			hp = currenthp;
			while(xp>=requiredxp){
				hp += hp/10;
				level += 1;
				xp -= requiredxp;
				requiredxp += requiredxp/5;
			} 
		if(language=="en"){
			cout << "\n      Leveled up! Went from lvl " << initiallvl << " to lvl " << level << ". HP: " << currenthp << " -> " << hp << "\n";
			cout << "      Current xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << "\n";
		}
		else{
			cout << "\n      Zvýšila sa it úroveň " << initiallvl << " na úroveň " << level << ". HP: " << currenthp << " -> " << hp << "\n";
			cout << "      Momentálne xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << "\n";
		}
	}
	save();
	}
	void statreset(){
		playerName="", mode="", fightstatus="", input="", tb="", decision1="", decision1sub1="", b1pathdec="", decision2="", diadec1="", diadec2="", diadec3="", diadec4="", diadec5="", hp=20, level=0, xp=0, currenthp=20;
	}
	void deathsequence(string language){
		if(language=="en"){
			system("cls");
			cout << "\n\n"; FunctionDef.truenarrator("\tWhoops...", 50); FunctionDef.skip(200); FunctionDef.TNC(" it lowkey seems like someone has lost a life.", 50); FunctionDef.skip(200); cout << "\n";
			if(lives!=0){
				FunctionDef.truenarrator("\tDon't worry though, brave traveller.", 50); FunctionDef.skip(200); FunctionDef.TNC(" Death is experience, and experience is life.", 50); FunctionDef.skip(200); 
				if(lives!=1) FunctionDef.TNC("You have " + to_string(lives) + " lives remaining.", 50);
				else FunctionDef.TNC("You have 1 life remaining...", 50);
				cout << "\n"; FunctionDef.skip(250);
				FunctionDef.truenarrator("\t[Press F to respawn, L to start new game]", 50);
				while(true){
					if(_kbhit()){
				  	char key = _getch();
				  	if(key=='f'){
				  		if(sequence==1) sequence1();
				  		else if(sequence==2) sequence2();
						}
						else{
							statreset();
							picklanguage();
						}
					}
				}
			}
			else{
				FunctionDef.truenarrator("\tAnd it was your last one...", 50); FunctionDef.skip(250); FunctionDef.TNC("I'm sorry this happened to you.", 50); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.truenarrator("\t[Press L to start new game.]", 50); 
				while(true){
					if(_kbhit()){
				  	char key = _getch();
						if(key=='l'){
							statreset();
							picklanguage();
						}
					}
				}
			}
		}
		else{
			system("cls");
			cout << "\n\n"; FunctionDef.truenarrator("\Ups...", 50); FunctionDef.skip(200); FunctionDef.TNC(" Vypadá to trochu tak, že niekto prišiel o jeden život.", 50); FunctionDef.skip(200); cout << "\n";
			if(lives!=0){
				FunctionDef.truenarrator("\tNemusíš sa ale báť, odvážny cestovateľ!", 50); FunctionDef.skip(200); FunctionDef.TNC(" Smrť je skúsenosť a skúsenosť je život.", 50); FunctionDef.skip(200); 
				if(lives==2) FunctionDef.TNC("Ostávaju ti " + to_string(lives) + " životy", 50);
				else if(lives==1) FunctionDef.TNC("Ostáva ti 1 život.", 50);
				else{
					FunctionDef.TNC("Máš nekonečno životov.", 50);
				}
				cout << "\n"; FunctionDef.skip(250);
				FunctionDef.truenarrator("\t[Stlač F na oživenie, L na začatie novej hry.]", 50);
				while(true){
					if(_kbhit()){
				  	char key = _getch();
				  	if(key=='f'){
				  		if(sequence==1) sequence1();
				  		else if(sequence==2) sequence2();
						}
						else{
							statreset();
							picklanguage();
						}
					}
				}
			}
			else{
				FunctionDef.truenarrator("\tA bol to tvoj posledný život...", 50); FunctionDef.skip(250); FunctionDef.TNC(" Je mi ľúto že sa ti toto stalo.", 50); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.truenarrator("\t[Stlač L na začatie novej hry.]", 50); 
				while(true){
					if(_kbhit()){
				  	char key = _getch();
						if(key=='l'){
							statreset();
							picklanguage();
						}
					}
				}
			}
		}
	}
	int ambush(string attacker, string language) {

		UlozitInfo(to_string(sequence), "sequence.txt");
		UlozitInfo(to_string(level), "PlayerLevel.txt");
		UlozitInfo(to_string(xp), "PlayerXp.txt");
		UlozitInfo(to_string(hp), "PlayerHp.txt");
		UlozitInfo(to_string(currenthp), "PlayerCurrentHp.txt");
		UlozitInfo(to_string(maxdmg), "PlayerMaxDmg.txt");
		UlozitInfo(playerName, "PlayerName.txt");

		UlozitInfo(attacker, "attacker.txt");

		Sleep(2000);
		if(language=="en") cout << endl << "      "; FunctionDef.truenarrator("Prepare to fight...", 50); Sleep(500);
		else cout << endl << "      "; FunctionDef.truenarrator("Priprav sa na boj...", 50); Sleep(500);
		const char* programName = "combatmoreeffective.exe";
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		WCHAR wProgramName[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, programName, -1, wProgramName, MAX_PATH); 
		char commandLine[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, wProgramName, -1, commandLine, MAX_PATH, NULL, NULL);
		if(language=="en"){
			if (CreateProcess(NULL, commandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				WaitForSingleObject(pi.hProcess, INFINITE);
			}
			else {
				cout << "Error launching program" << "\n";
			}
			ifstream inputFile("testsave.txt");
		  if (!inputFile.is_open()) {
		    cerr << "Error opening file for reading!" << "\n";
		    return 1;
		  }
		  inputFile >> fightstatus;
		  inputFile >> xpgained;
		  if(fightstatus=="1"){
		  	FunctionDef.truenarrator("You aborted the fight... You automatically die.", 50); cout << "\n"; FunctionDef.skip(250); FunctionDef.truenarrator("[Press F to load the latest save/L to start over]",50);
				string strlives = PrecitatInfo("Lives.txt");
		    lives = stoi(strlives);
		    deathsequence();
			}
			else{
	      FunctionDef.truenarrator("You finished the fight.", 50); cout << "\n";
	    }
		}
		else{
	if (CreateProcess(NULL, commandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			WaitForSingleObject(pi.hProcess, INFINITE);
		}
		else {
			cout << "Chyba pri spustení programu." << endl;
		}
		ifstream inputFile("testsave.txt");
	  if (!inputFile.is_open()) {
	    cerr << "Chyba pri otvorení súboru na načítanie údajov." << endl;
	    return 1;
	  }
	  inputFile >> fightstatus;
	  inputFile >> xpgained;
	  if(fightstatus=="1"){
	  	FunctionDef.truenarrator("Prerušil si súboj... Automaticky umieraš.", 50); cout << endl; FunctionDef.skip(250); FunctionDef.truenarrator("[Stlač F pre načítanie poslednej uloženej pozície alebo stlač L pre načítanie novej hry.]",50);
			while(true){
      	if(_kbhit()){
      		char c = _getch();
      		if(c=='f') sequence1();
					else if(c=='f') introsequence();
				}
			}
		}
		else{
      			FunctionDef.truenarrator("Dokončil si súboj.", 50); cout << endl;
		}
		Sleep(3000);
		xp+=xpgained;
		checkLevelUp(lang);
		Sleep(2000);
	}
	void endingplaceholder1(string language){
		if(language=="en"){
			cout << "\n\n";
			FunctionDef.truenarrator("You went your own way. You will never know what happened next.", 50); FunctionDef.skip(250); cout << "\n\n";
			FunctionDef.truenarrator("\tEnding: You went your own path", 50);
		}
		else{
			cout << "\n\n";
			FunctionDef.truenarrator("Išiel si vlastnout cestou. Nikdy sa nedozvieš čo sa stalo.", 50); FunctionDef.skip(250); cout << "\n\n";
			FunctionDef.truenarrator("Koniec: Vlastná cesta", 50);
		}
	}
	void d1n(string language) {
		if(language=="en"){
			if (a == 0) FunctionDef.truenarrator("\t  Trees, interesting choice. You come closer to the trees but you don't find anything.", 50);
			if (a == 1) FunctionDef.truenarrator("\t  For real? You visit the trees again, and... you don't find anything.", 50);
			if (a == 2) FunctionDef.truenarrator("\t  There is something weird about those trees. They're... trees.", 50);
			if (a > 2) {
				FunctionDef.truenarrator("\t  You visit the trees once more. Once again, you find nothin-", 50); cout << "\n";
				FunctionDef.truenarrator("\t  w- what's that sound? It seems like... you have awakened something. It's angry.", 75); cout << "\n"; FunctionDef.skip(300);
				FunctionDef.truenarrator("\t  Behold Mozz, the tree [BOSS] [10M HP] You stand no chance against this beast as it one hits you", 50); cout << "\n";
				FunctionDef.truenarrator("\t  before the fight even has a chance to begin.", 50); FunctionDef.skip(400); cout << "\n"; FunctionDef.skip(400); system("cls"); cout << "\n\n\n\n";
				FunctionDef.truenarrator("\t  \033[1;31mYou get the tree picker ending.\033[0m", 50); cout << "\n"; FunctionDef.skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
				lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence(lang);
			}
		}
		else{
			if (a == 0) FunctionDef.truenarrator("\t  Stromy, zaujímavá voľba. Išiel si bližšie ku stromom, ale nič si nenašiel.", 50);
			if (a == 1) FunctionDef.truenarrator("\t  Vážne? Prišiel si znova ku stromom, a... znova si nič nenašiel.", 50);
			if (a == 2) FunctionDef.truenarrator("\t  Niečo je divné na tých stromoch. Sú ako... stromy.", 50);
			if (a > 2) {
				FunctionDef.truenarrator("\t  Išiel si k stromom ešteb raz.A opäť si nič nenašie-", 50); cout << endl;
				FunctionDef.truenarrator("\t  Č- čo to je za zvuk? Vyzerá to tak... že si niečo zobudil. A je to naštvané.", 75); cout << endl; FunctionDef.skip(300);
				FunctionDef.truenarrator("\t  Axir, The Lord of the Forbidden Forest [BOSS] [10M HP] Nemáš šancu proti tomuto monštru zvíťaziť, keďže ťa zabije", 50); cout << endl;
				FunctionDef.truenarrator("\t  ešte predtým, než má súboj vôbec šancu začať.", 50); FunctionDef.skip(400); cout << endl; FunctionDef.skip(400); system("cls"); cout << "\n\n\n\n";
				FunctionDef.truenarrator("\t  \033[1;31mZískal si koniec Zberač Stromov.\033[0m", 50); cout << endl; FunctionDef.skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
				lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence(lang);
			}
		}
	}

	// Decisions

	void d1(string language) {
		if(language=="en"){
			FunctionDef.truenarrator("\t  You look around you. You see the following:", 50);
			cout << "\n";
			FunctionDef.truenarrator("\t  1) Trees", 50); cout << "\n"; FunctionDef.truenarrator("\t  2) Trees", 50); cout << "\n"; FunctionDef.truenarrator("\t  3) Trees", 50); cout << "\n"; FunctionDef.truenarrator("\t  4) A path", 50); cout << "\n"; FunctionDef.truenarrator("\t  5) A strange place between the trees, where abandoned stuff can be seen.", 50); FunctionDef.skip(500); cout << endl << "\n"; FunctionDef.truenarrator("\t  What do you choose?", 50);
			cout << "\n";
		}
		else{
			FunctionDef.truenarrator("\t  Poobzeráš sa okolo seba a vidíš:", 50);
			cout << endl;
			FunctionDef.truenarrator("\t  1) Stromy", 50); cout << endl; FunctionDef.truenarrator("\t  2) Stromy", 50); cout << endl; FunctionDef.truenarrator("\t  3) Stromy", 50); cout << endl; FunctionDef.truenarrator("\t  4) Cestu", 50); cout << endl; FunctionDef.truenarrator("\t  5) Divné miesto medzi stromami, kde môžeš vidieť pohodené veci.", 50); FunctionDef.skip(500); cout << endl << endl; FunctionDef.truenarrator("\t  What do you choose?", 50);
			cout << endl;
		}
	}

	// Sequences
	void savesequence(string language) {
		if(language=="en"){
			FunctionDef.truenarrator("\tWelcome back, " + playerName, 50); FunctionDef.skip(250); cout << "\n";
			FunctionDef.truenarrator("\tDo you wish to load the latest save or start a new game? [F to Load, L to start over]", 50);
		}
		else{
			FunctionDef.truenarrator("\tVitaj späť, " + playerName, 50); FunctionDef.skip(250); cout << endl;
			FunctionDef.truenarrator("\tChceš načítať poslednú uloženú pozíciu alebo začať novú hru? [F pre načítanie pozície, L pre novú hru]", 50);
		}
		while (true) {
			if (_kbhit()) {
				char keypressed = _getch();
				if (keypressed == 'f') {
					saveload = 1;
					if (sequence == 1) sequence1(lang);
					else if (sequence == 2) sequence2(lang);
				}
				else if (keypressed == 'l') {
					picklanguage();
				}
			}
		}
	}
	void picklanguage(){
		system("cls");
		FunctionDef.truenarrator("\tPick a language.", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("1 < English-EN >", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("2 < Slovak-SK >", 50);
		lang = FunctionDef.GVIclean(1,2);
		if(lang=="1") lang = "en";
		else lang = "sk";
		UlozitInfo(lang, "Language.txt");
		introsequence(lang);
	}
	void introsequence(string language){
		if(language=="en"){
			system("cls");
			if(mode=="speedrun"){
				mode = ""; UlozitInfo(mode, "Mode.txt");
				cout << "\n\n\n"; FunctionDef.truenarrator("\tYeahhhh, uhhh, you kind of abandoned your last speedrun session sooo, yeah, you know what that means...", 50); Sleep(2000);
				system("cls");
			}
			
			level = 0; hp = 20; xp = 0; currenthp = 20; maxdmg = 1;
			cout << "                                          W E L C O M E    T O" << "\n";
		 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
			cout << endl << "                                           The C++ Console RPG";
			cout << endl << "                                         Press [ANY KEY] to Begin";
			_getch();
			cout << "\n";FunctionDef.truenarrator("Hello Player", 100); FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("...", 500); FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("Your name isn't Player, is it?", 80); FunctionDef.skip(1500); cout << "\n";
			FunctionDef.truenarrator("What's your name?", 80); FunctionDef.skip(1000); cout << endl << "      [ENTER YOUR NAME NOW]" << "\n";
			FunctionDef.flushInput();
			cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
			if (!playerName.empty()) {
				FunctionDef.truenarrator("Nice to meet you, "+playerName+"!", 100);
			} 
			else {
				FunctionDef.truenarrator("You...", 500); FunctionDef.TNC(" don't have a name?", 125); FunctionDef.skip(500); FunctionDef.TNC(" I will give you one more chance to give me your name.", 80); cout << "\n"; 
				FunctionDef.flushInput();
				cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
				if (!playerName.empty()) {
					FunctionDef.truenarrator("At last, nice to meet you, "+playerName+"!", 80);
				} 
				else {
					FunctionDef.truenarrator("You sure?", 125); cout << "\n"; FunctionDef.skip(1000);
					FunctionDef.truenarrator("That's", 225); FunctionDef.TNC("...", 500); FunctionDef.skip(500); FunctionDef.TNC(" sad.", 200); cout << "\n"; FunctionDef.skip(750);
					FunctionDef.truenarrator("I still need something to call you by, though", 80); cout << "\n"; FunctionDef.skip(500);
					FunctionDef.truenarrator("Will Player suffice?", 75); FunctionDef.skip(500); FunctionDef.TNC(" I think it will be alright.", 75); playerName = "Player"; save();
				}
			} 
			FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("What mode would you like to explore today, fellow adventurer?", 80); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<1> EASY", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<2> NORMAL", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<3> HARD", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<4> SPEEDRUN", 50);
			mode = FunctionDef.GVIclean(1,4);
			if(mode=="1") mode = "easy";
			else if(mode=="2") mode = "normal";
			else if(mode=="3") mode = "hard";
			else if(mode=="4") mode = "speedrun";
			UlozitInfo(mode, "Mode.txt");
			system("cls");
			if(mode=="easy"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tEasy mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have an unlimited amount of respawns.", 50); 
				Sleep(2000); lives = -1;
			}
			else if(mode=="normal"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tNormal mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have 3 respawns.", 50); 
				Sleep(2000); lives = 3;
			}
			else if(mode=="hard"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tHard mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have 1 respawn.", 50); 
				Sleep(2000); lives = 1;
			}
			else{
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tSpeedrun mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have 1 respawn and the game does not save. Godspeed on your adventure.", 50); 
				Sleep(2000); lives = 1;
			}
			UlozitInfo(to_string(lives), "Lives.txt");
			sequence=0;
			sequence1(language);
		}
		else{
				system("cls");
		level = 0; hp = 20; xp = 0; currenthp = 20; maxdmg = 1;
		cout << "                                            V I T A J    V" << endl;
	 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
		cout << endl << "                                           The C++ Console RPG";
		cout << endl << "                                         Stlač [čokoľvek] a začni hru"; 
		_getch();
		cout << endl;FunctionDef.truenarrator("Zdravím ťa cestovateľ!", 100); FunctionDef.skip(1000); cout << endl;
		FunctionDef.truenarrator("...", 500); FunctionDef.skip(1000); cout << endl;
		FunctionDef.truenarrator("Asi sa nevoláš cestovateľ, že", 80); FunctionDef.skip(1500); cout << endl;
		FunctionDef.truenarrator("Ako sa voláš?", 80); FunctionDef.skip(1000); cout << endl << "      [NAPÍŠ SVOJE MENO]" << endl;
		FunctionDef.flushInput();
		cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
		if (!playerName.empty()) {
			FunctionDef.truenarrator("Rád ťa spoznávam, "+playerName+"!", 100);
		} else {
			FunctionDef.truenarrator("Ty...", 500); FunctionDef.TNC(" ty nemáš meno?", 125); FunctionDef.skip(500); FunctionDef.TNC(" Isto máš nejaké meno. Dám ti šancu ho ešte zadať..", 80); cout << endl; 
			FunctionDef.flushInput();
			cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
			if (!playerName.empty()) {
			FunctionDef.truenarrator("Výborne, rád ťa spoznávam, "+playerName+"!", 80);
		} else {
			FunctionDef.truenarrator("Vážne nemáš meno?", 125); cout << endl; FunctionDef.skip(1000);
			FunctionDef.truenarrator("To je", 225); FunctionDef.TNC("...", 500); FunctionDef.skip(500); FunctionDef.TNC(" smutné. Je mi ťa ľúto.", 200); cout << endl; FunctionDef.skip(750);
			FunctionDef.truenarrator("Ale aj tak ťa nejako potrebujem volať.", 80); cout << endl; FunctionDef.skip(500);
			FunctionDef.truenarrator("Môžem ťa volať Cestovateľ?", 75); FunctionDef.skip(500); FunctionDef.TNC(" Myslím, že to budem fajn.", 75); playerName = "Cestovateľ"; save();
		}
	} 
				FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("Na akej obtiažnosti si praješ hrať hru, drahý cestovateľ?", 80); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<1> ĽAHKÁ", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<2> NORMÁLNA", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<3> ŤAŽKÁ", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<4> TURBO", 50);
			mode = FunctionDef.GVIclean(1,4);
			if(mode=="1") mode = "easy";
			else if(mode=="2") mode = "normal";
			else if(mode=="3") mode = "hard";
			else if(mode=="4") mode = "speedrun";
			UlozitInfo(mode, "Mode.txt");
			system("cls");
			if(mode=="easy"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tJednoduchá obtiažnosť...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tMáš neobmedzený počet oživení.", 50); 
				Sleep(2000); lives = -1;
			}
			else if(mode=="normal"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tNormálna obtiažnosť...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tMáš k dispozícii 3 oživenia.", 50); 
				Sleep(2000); lives = 3;
			}
			else if(mode=="hard"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tŤážká obtiažnosť...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tMáš k dispozícii jedno oživenie.", 50); 
				Sleep(2000); lives = 1;
			}
			else{
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tSpeedrun mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tMáš jedno oživenie a hra sa neukladá. Tvoja cesta bude mať tú správnu rýchlosť.", 50); 
				Sleep(2000); lives = 1;
			}
			UlozitInfo(to_string(lives), "Lives.txt");
			sequence=0;
			sequence1(language);
		}
	}
	void sequence1(string language){
		if(language=="en"){
			system("cls");
			if(saveload==1){
				cout << "\n\n\n"; FunctionDef.truenarrator("\tWelcome back traveller. We missed you. You may now continue on your "+mode+ " mode journey.", 50); Sleep(2500);
				system("cls");
			}
			if(sequence==0) sequence++;
			save();
			Sleep(500);
			cout << "\n\n\n\n\n\n\t\t{[()]} Sequence 1 {[()]}\n\n\n"; Sleep(500);
			if(mode!="speedrun") FunctionDef.truenarrator("\t\tThe game saves every sequence. Good luck on your journey.", 50);
			else FunctionDef.truenarrator("\t\tThe game savesn't every sequence. Good luck on your journey.", 50);
			Sleep(2000); system("cls");
			Sleep(2500);
			FunctionDef.MCS("Where am I?", 80);FunctionDef.narratorclean(mc," How did I get here?",80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("There is a thick forest all around me.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("I, ", 100);FunctionDef.narratorclean(mc,"...", 200); FunctionDef.skip(500);FunctionDef.narratorclean(mc," can't remember anything.", 80); FunctionDef.skip(1500);
			cout << "\n";
			FunctionDef.narrator("What's happening! ", 80); FunctionDef.skip(600);FunctionDef.narratorclean(vc,"Why can't I control my body? ", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc,"This... ", 175); FunctionDef.skip(300);FunctionDef.narratorclean(vc,"This is not my body!", 80);
			cout << "\n";
			FunctionDef.MCS("Who said that? ", 40); FunctionDef.skip(750);
			cout << "\n";
			FunctionDef.MCS("Where are you? Show yourself!", 75); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("I can't show myself.", 80); FunctionDef.skip(1000); cout << "\n";
			FunctionDef.MCS("What do you mean?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("I myself have no idea.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," It seems like...", 120); FunctionDef.skip(400);FunctionDef.narratorclean(vc," I am in you.", 100); FunctionDef.skip(750);
			cout << endl << "\n";FunctionDef.truenarrator("1) Why are you in me?", 50); cout << "\n";FunctionDef.truenarrator("2) How is that possible?",50); cout << "\n";FunctionDef.truenarrator("3) What happened to my memories?",50); cout << "\n";FunctionDef.truenarrator("4) You're lying. You're hiding behind those trees aren't you?",50); 
			cout << "\n\n\033[33m>>    ";
			diadec2 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec2=="1"){
				FunctionDef.MCSC(mc, "Why are you in me?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Good question.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," All I can remember is my death,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," and now,", 125);FunctionDef.narratorclean(vc," I find myself here,", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc," in your body.", 100); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) What do you mean your death?", 50); cout << "\n";FunctionDef.truenarrator("2) Hold on, you're dead?",50); cout << "\n";FunctionDef.truenarrator("3) Is this a dream?",50); cout << "\n";FunctionDef.truenarrator("4) Huh?",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc,"What do you mean your death?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("This has to be a nightmare.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Well,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," we don't really have a choice,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," stand up and look around.", 80 ); FunctionDef.skip(250);
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Stand up before someone,", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," or worse,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," something finds us.", 100); FunctionDef.skip(1000);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"Is this a nigthmare?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
						FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000);
						FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
				else if(diadec3=="2"){
					FunctionDef.MCSC(mc,"Hold on, you're dead?", 70); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Affirmative, it does seem that way.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Well,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," we don't really have time and a choice,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," stand up and look around.", 80 ); FunctionDef.skip(250);
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Stand up before someone,", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," or worse,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," something finds us.", 100); FunctionDef.skip(1000);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"Is this a nightmare?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
						FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000);
						FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
				else if(diadec3=="3"){
					FunctionDef.MCSC(mc,"That's not possible!", 70);FunctionDef.narratorclean(mc," Am I dreaming?", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I understand the difficulty of comprehending a situation like this,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," however,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," dream or not,", 100); FunctionDef.skip(250);
					cout << "\n";
					FunctionDef.narrator("we have to move. So, I would advise you to get up before someone,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," or worse,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," something,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," finds us.", 80 );
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) This is insane.",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"This is insane.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," I don't understand.", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But I'll comply.", 80 ); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("I'll explain what I know once we get out of here.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
				else if(diadec3=="4"){
					FunctionDef.MCSC(mc,"Huh?", 70); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I understand if comprehending it is beyond your current capabilities,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," however,", 100); FunctionDef.skip(250); 
					cout << "\n";
					FunctionDef.narrator("we have to move. So, I would advise you to get up before someone,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," or worse,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," something,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," finds us.", 80 );
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"Is this a nightmare?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
						FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000); cout << "\n";
						FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
			}
			else if(diadec2=="2"){
				FunctionDef.MCSC(mc, "How is that possible?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("I don't know.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," But what I do know,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," is,", 125);FunctionDef.narratorclean(vc," that we should get out of here,", 100); FunctionDef.skip(500); cout << "\n";FunctionDef.narrator("we don't want anyone or anything to find us, do we now?", 80); FunctionDef.skip(1000);FunctionDef.narratorclean(vc," I'll tell you the answers on the way out of here,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("just get up and move,", 80); FunctionDef.skip(200);FunctionDef.narratorclean(vc, " please.", 100); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="2"){
					FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="3"){
					FunctionDef.MCSC(mc,"Is this a nigthmare?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
					FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000); cout << "\n";
					FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec3=="4"){
					FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			if(diadec2=="3"){
				FunctionDef.MCSC(mc, "But where are my memories?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," You just came here into my mind, and all of them are gone.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " What have you done to them?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("I haven't done anything to your memories.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," I know nothing,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," same as you.", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Do you think I want to be here?", 100); FunctionDef.skip(500); cout << "\n";FunctionDef.narrator("I somehow died and now I am here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " in your body,", 100);FunctionDef.narratorclean(vc, " which I can't control.", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("But,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," here we are,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," so move your ass and get up.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) This has to be a nightmare.",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 	
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="2"){
					FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="3"){
					FunctionDef.MCSC(mc,"This has to be a nightmare!...", 80);FunctionDef.narratorclean(mc, "URGHHHH!", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("We have no choice,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," we must cooperate,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," unless you want to die.", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Okay, let's go.", 50); cout << "\n";FunctionDef.truenarrator("2) Wait, why would I die?",50); cout << "\n";FunctionDef.truenarrator("3) No! I want to go my own way.",50); cout << "\n";FunctionDef.truenarrator("4) I'm not moving unless you tell me who you are.",50); 	
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4); 
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Okay, let's go.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great.", 75);FunctionDef.narratorclean(vc," Time to move this way.", 75); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"Wait, why would I die?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Because you will be alone in this world,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " without memories,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " forgotten to everyone,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and an easy target for enemies.", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("We're not alone in this forest.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I can help you get out of here safely.", 75); FunctionDef.skip(1000); 
						cout << "\n";
						FunctionDef.MCS("Why is this happening to me?", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("I know you're scared and frustrated.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But trust me,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," the only way for both of us to survive is to get up and move.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("I guess I have no choice...", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," Fine,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," I'll cooperate.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Okay, great. Let's go that way.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"No! I want to go my own way.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 75); FunctionDef.skip(1500);
						endingplaceholder1(lang);
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"I'm not moving unless you tell me who you are.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Fine, fine.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," I'll tell you...", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," My name is Void.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," I was the general of a faction", 75); cout << "\n";FunctionDef.narrator("called Terragnis.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," We were in a war against another faction called Slofridi.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," When I was in a battle,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("an arrow hit me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," somehow,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," I didn't die.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Suddenly,", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator(" a bright light flashed before it was followed by darkness.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," When I came to my senses, I found myself in someone else's body...", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("in your body.", 75); FunctionDef.skip(400);FunctionDef.narratorclean(vc," And now,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," we're here.", 100); FunctionDef.skip(1500);
						cout << "\n";
						FunctionDef.MCS("So, you died and woke up in my head.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("To put it shortly, yes.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("But, how is that possible?", 80); FunctionDef.skip(1000); 
						cout << "\n";
						FunctionDef.narrator("I told you everything I know.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," I would like to know more too,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " but we will find out nothing if we just sit here.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("You have a point,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," let's get out of here.", 75); FunctionDef.skip(1500);	relwvoid = 3;
						earlyexplanation = true;	
					}
				}
			}
			else if(diadec2=="4"){
				FunctionDef.MCSC(mc, "You're lying.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " You're hiding behind those trees, aren't you?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("I am not one lie to lie.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Only when it is an utter necessity.", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("You should get up and move your ass before you get us both killed by someone or something.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Alright, let's get going.", 50); cout << "\n";FunctionDef.truenarrator("2) I will need a further explanation in order to comply.",50); cout << "\n";FunctionDef.truenarrator("3) I don't understand, how is this possible?",50); cout << "\n";FunctionDef.truenarrator("4) I'm not buying that. You are trying to lure me out.",50);
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc, "Alright,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " let's get going.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Okay, great.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Let's go that way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it seems like there might be something there.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				else if(diadec3=="2"){
					FunctionDef.MCSC(mc, "I will need a further explanation in order to comply.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I told you,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " I don't know.", 80);FunctionDef.narratorclean(vc, " All I know is that I am stuck here in your mind and that you're gonna get us", 80); cout << "\n";FunctionDef.narrator("killed if you don't move,",80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " so please,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " move,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and I'll tell you more when we're on the move.", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) Nope, still don't trust you. I refuse to believe this.", 50); cout << "\n";FunctionDef.truenarrator("3) Alright, I'll move", 50);
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,3);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc, "Why should I listen to you?", 80); FunctionDef.skip(1000);
						FunctionDef.narrator("You don't have a choice.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Or maybe you do,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " do whatever you want,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " you want to die?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Fine, then.", 80); FunctionDef.skip(1000);
						cout << endl << "\n";FunctionDef.truenarrator("1) I'll go my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) Okay, I'm sorry. I'll do what you want now.", 50);
						cout << "\n\n\033[33m>>    ";
						diadec5 = FunctionDef.GVIclean(1,4);
						cout << "\033[0m";
						if(diadec5=="1"){
							FunctionDef.MCSC(mc, "I'll go my own way.", 50); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80);
							endingplaceholder1(lang);
						}
						else{
							FunctionDef.MCSC(mc, "Okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'm sorry.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " I'll do what you want now.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("At last.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Well,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " no time to lose,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " get up and go that way.", 80); FunctionDef.skip(1500); relwvoid = 3;
						}
					}
					else if(diadec4=="2"){
						FunctionDef.MCSC(mc, "Nope,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " still don't trust you.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " I refuse to believe this.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("So,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " you want to die here then?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Alright,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " go your own way then.", 80); FunctionDef.skip(1000);
						cout << endl << "\n";FunctionDef.truenarrator("1) I'll be on my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) You know what, fine, I'll listen to you for now.", 50);
						cout << "\n\n\033[33m>>    ";
						diadec5 = FunctionDef.GVIclean(1,2);
						cout << "\033[0m";
						if(diadec5=="1"){
							FunctionDef.MCSC(mc, "I'll be on my own way.", 50); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80);
							endingplaceholder1(lang);
						}
						else{
							FunctionDef.MCSC(mc, "You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " fine,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll listen to you for now.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("Finally...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We can move.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Stand up,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and let's go this way.", 80); FunctionDef.skip(1500); relwvoid = 1;
						}
					}
					else{
						FunctionDef.MCSC(mc, "Alright,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll move.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Good,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " alright,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we should 	go that way.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
				}
				else if(diadec3=="3"){
					FunctionDef.MCSC(mc, "I don't understand, how is this possible?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I don't understand either.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We can figure it out together,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " just,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " please,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " move.", 100); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Okay, I'm sorry, I'll move.", 50); cout << "\n";FunctionDef.truenarrator("2) How about, no?", 50);
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,2);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc, "Okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'm sorry,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll move.", 90); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("It's okay", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " let's go that way.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I can see something sticking out, there might be something there.", 80); FunctionDef.skip(1000); relwvoid = 3;
					}
					else{
						FunctionDef.MCSC(mc, "How about,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " no?", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Are you sure you want me as your enemy?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Remember,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I am inside your mind,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and I can make this", 80); cout << "\n";FunctionDef.narrator("a living hell for you.", 80); FunctionDef.skip(1000);
						cout << endl << "\n";FunctionDef.truenarrator("1) Yes, I want to go my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) I changed my mind, I'm sorry, I'll listen to you.", 50); 
						cout << "\n\n\033[33m>>    ";
						diadec5 = FunctionDef.GVIclean(1,2);
						cout << "\033[0m";
						if(diadec5=="1"){
							FunctionDef.MCSC(mc, "Yes, I want to go my own way.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80); FunctionDef.skip(1500);
							endingplaceholder1(lang);
						}
						else{
							FunctionDef.MCSC(mc, "I changed my mind,",80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'm sorry,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll listen to you.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("At last,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "let's go that way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I'll try to explain what I know.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " If we want to live together", 80); cout << "\n";FunctionDef.narrator("in peace,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we have to cooperate.", 80); FunctionDef.skip(1500); relwvoid = 2;
						}
					}
				}
				else{
					FunctionDef.MCSC(mc, "I'm not buying that.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " You are trying to lure me out.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Okay, seriously?", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Listen,", 80);FunctionDef.narratorclean(vc," you don't have a choice,", 80);FunctionDef.narratorclean(vc," move,",100);FunctionDef.narratorclean(vc," you have nothing to lose.", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Stop talking to me, I want to go my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) Fine.", 50); cout << "\n";FunctionDef.truenarrator("3) I'm sorry, I was just  making sure. We can move now.", 50); 
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,3);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc, "Stop talking to me,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I want to go my own way.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80); FunctionDef.skip(1500);
						endingplaceholder1(lang);
					}
					else if(diadec4=="2"){
						FunctionDef.MCSC(mc, "Fine.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("This attitude is insane,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " show some respect to the inhabitant of your mind.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Look around a little,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("there looks to be something that way.", 80); FunctionDef.skip(1500); relwvoid = 1;
					}
					else{
						FunctionDef.MCSC(mc, "I'm sorry,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I was just making sure.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " We can move now.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("It is alright,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I understand.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Let's go now.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " That way seems to lead somewhere.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
				}
			}
			cout << "\n";
			cout << "\n";
			d1();
			while(true){
				if(a>0 || b>0) d1(lang);
				cout << endl << "\n";
				FunctionDef.flushInput();
				cout << "\033[33m>>    ";
				decision1 = FunctionDef.GVIclean(1,5);
				cout << "\033[0m";
				if(decision1=="1"){
					FunctionDef.MCSC(mc, "I want to see the trees.", 80);
					cout << endl << "\n";
					d1n(lang);
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;
				}
				else if(decision1=="2"){
					FunctionDef.MCSC(mc, "I want to see those trees.", 80);
					cout << endl << "\n";
					d1n(lang);
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;
				}
				else if(decision1=="3"){
					FunctionDef.MCSC(mc, "I must see these trees.", 80);
					cout << endl << "\n";
					d1n();
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;		
				}
				else if(decision1=="4"){
					FunctionDef.MCSC(mc, "I would like to see where this path leads.", 80);
					cout << endl << "\n";
					FunctionDef.truenarrator("Okay, you decide you want to see the destination of this path. Are you sure you don't want to check\n      the abandoned place where your stuff might lay out first?", 50);
					cout << endl << "\n";
					FunctionDef.skip(250);
					FunctionDef.truenarrator("1) Go through with your initial decision\n      2) Abort", 50);
					cout << endl << "\n";
					FunctionDef.flushInput();
					cout << "\033[33m>>    ";
					decision1sub1 = FunctionDef.GVI(1,2);
					cout << "\033[0m";
					if(decision1sub1=="1"){
						FunctionDef.MCSC(mc, "I really want to know where it leads.", 80);
						cout << endl << "\n";
						FunctionDef.truenarrator("Very well, you decide to embark on an adventurous journe- nevermind, you die. Reason: UNKN0WN", 50);
						FunctionDef.skip(400);
						cout << endl << endl << "\n";
						lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence(lang);
					}
					else if(decision1sub1=="2"){
						FunctionDef.MCSC(mc, "I think we should check that strange abandoned place first.", 80);
						cout << endl << "\n";
						FunctionDef.truenarrator("At last, you decide to check the strange place with abandoned stuff out. You see the following:",50); cout << "\n\n";FunctionDef.truenarrator("- Tea",50); cout << "\n";FunctionDef.truenarrator("- An iron sword",50); cout << "\n";FunctionDef.truenarrator("- Golden armor with a low durability",50); cout << "\n";FunctionDef.truenarrator("- A shield",50); cout << "\n";FunctionDef.truenarrator("- Elixir of Love",50); cout << "\n";FunctionDef.truenarrator("- A stick",50); cout << "\n";FunctionDef.truenarrator("- Bandage x3",50); cout << "\n";FunctionDef.truenarrator("- A small backpack", 50);
						break;
					}
				}
				else if(decision1=="5"){
					FunctionDef.MCSC(mc, "I would like to check the strange abandoned place out first.", 80);
					cout << endl << "\n";
					FunctionDef.truenarrator("Great choice, better than \"trees\" atleast, you near the abandoned things and find the following:",50); cout << "\n\n";FunctionDef.truenarrator("- Tea",50); cout << "\n";FunctionDef.truenarrator("- An iron sword",50); cout << "\n";FunctionDef.truenarrator("- Golden armor with a low durability",50); cout << "\n";FunctionDef.truenarrator("- A shield",50); cout << "\n";FunctionDef.truenarrator("- Elixir of Love",50); cout << "\n";FunctionDef.truenarrator("- A stick",50); cout << "\n";FunctionDef.truenarrator("- Bandage x3",50); cout << "\n";FunctionDef.truenarrator("- A small backpack", 50); break;
				}
			}
			cout << endl << "\n"; diadec1 = ""; diadec2 = ""; diadec3 = ""; diadec4 = ""; diadec5 = "";
			if(a==3&&(relwvoid==1||relwvoid==2)) b0 = "1";
			else if(a==3&&(relwvoid==3||relwvoid==4)) b0 = "2";
			else if(a<2&&(relwvoid==1||relwvoid==2)) b0 = "3";
			else if(a<2&&(relwvoid==3)) b0 = "4";
			else if(a<2&&relwvoid==4) b0 = "5";
			else if(a==2&&(relwvoid==1||relwvoid==2)) b0 = "6";
			else if(a==2&&(relwvoid==3||relwvoid==4)) b0 = "7";
			else if(earlyexplanation==true&&a<2) b0 = "8";
			else if(earlyexplanation==true&&a>1) b0 = "9";
			if(b0=="1"){
				FunctionDef.narrator("Not only are you an asshole right away,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," you're also dumb.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Why would you choose the trees three times?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I don't want to hear it,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " stop wasting our time and grab the things and get the hell out of here.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Sorry, I really wanted to see the trees.", 50); cout << "\n";FunctionDef.truenarrator("2) I'm an asshole? You're an asshole!", 50); cout << endl << "\n"; 
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Sorry, I really wanted to see the trees.", 80); FunctionDef.skip(500);
					cout << "\n";
					FunctionDef.narrator("Save it,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " grab the things and GO!", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500); cout << "\n";
				}
				else{
					FunctionDef.MCSC(mc, "I'm an asshole?!", 75); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " You're an asshole!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " You're the one who invaded my mind.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Me?!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " go to hell,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I told you I don't know whath appened and how I got here.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Stop it and get the things before we die here.", 80); FunctionDef.skip(1000);
					cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500); cout << endl << "\n";
				}
				FunctionDef.narrator("I'm really trying to be nice here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " but you're not letting me.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " What do you suggest we do now?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Do we take the path this way?", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Take the path in Void's desired direction.", 80); cout << "\n";FunctionDef.truenarrator("2) Go the opposite way.", 50); cout << endl << "\n";
				cout << "\033[33m>>    ";
				b1pathdec = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";
				if(b1pathdec=="1"){
					FunctionDef.MCSC(mc, "Fine, let's go your way.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Atleast you listen.", 80); FunctionDef.skip(1000); relwvoid = 2;
				}
				else{
					FunctionDef.MCSC(mc, "You know what?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "I don't like listening to you.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "I prefer if we went this way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " we can't lose anything.", 80); 
					cout << "\n";
					FunctionDef.narrator("You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " fine,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " go wherever the hell you want.", 80); FunctionDef.skip(1000); relwvoid = 1; d="7";
				}
			}
			else if(b0=="2"){
				FunctionDef.narrator("Why would you choose trees three times?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Are you", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "-", 200);FunctionDef.narratorclean(vc, " I'm sorry.", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " You choosing trees 3 times frustrated me.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("There was clearly nothing there,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we wasted our time.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We should probably get going,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " grab the things and go.", 80); FunctionDef.skip(1000);
				cout << "\n"; 
				FunctionDef.MCS("I'm sorry.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Let's take the path we saw before.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n"; 
				FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " that path should lead us someplace we can find answers.", 80); FunctionDef.skip(1000);
			}
			else if(b0=="3"){
				FunctionDef.narrator("Grab that and go.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Also,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " what's up with you?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Quit acting this way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it's better if we get along.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n";FunctionDef.truenarrator("1) I'm sorry about that...", 50); cout << "\n";FunctionDef.truenarrator("2) ...", 50); cout << endl << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";			 
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "I'm sorry about that...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " I didn't mean what I said before,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I was just being careful.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.MCS("But I see that you're not a bad guy and that you are actually in my mind now.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("It's okay,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I understand.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Thank you for the apology.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We should move,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " let's take the path we saw earlier.", 80); FunctionDef.skip(1000);
					relwvoid = 3;
				}
				else{
					FunctionDef.MCSC(mc, "...", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I-", 150); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I know it must be hard from your perspective.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Looking at it from your shoes,", 80);FunctionDef.narratorclean(vc, " I wouldn't trust myself either.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("I understand,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I'm sorry.", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Thank you,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I should be the one sorry.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " But you're right,", 80);FunctionDef.narratorclean(mc, " we should move and talk about this later.", 80); FunctionDef.skip(1000); 
					relwvoid = 3;
				}
			}
			else if(b0=="4"){
				FunctionDef.narrator("Great.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," These things will come in handy.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Grab them and let's go.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n";
				FunctionDef.MCS("Good idea,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " let's follow that path we saw earlier,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " perhaps it leads into a town.",80); FunctionDef.skip(400); FunctionDef.narratorclean("\033[33m", " Can't be a path from nowhere to nowhere,", 80);FunctionDef.narratorclean("\033[33m", " right?", 100); FunctionDef.skip(1000);
			}
			else if(b0=="5"){
				FunctionDef.narrator("Amazing,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we got really lucky.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We should continue moving and get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " right after you grab these things.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n";FunctionDef.MCS("Okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " we should get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " you're right,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " perhaps we should take that path we saw earlier,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.MCS("it could lead somewhere.", 80); FunctionDef.skip(1000);			
				cout << "\n";
				FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it will lead somewhere,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it has to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " don't worry.", 80); FunctionDef.skip(1000);
			}
			else if(b0=="6"){
				FunctionDef.narrator("Can you stop choosing the trees and grab the things and get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " asshole?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Fine,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll grab the things.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.MCS("Now what?", 80); FunctionDef.skip(1000);
				FunctionDef.narrator("We get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " using that path.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Go and don't talk.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " I'm becoming allergic to you speaking and we only", 80); cout << "\n";FunctionDef.narrator("met 3 minutes ago.", 80); FunctionDef.skip(1000);			
			}
			else if(b0=="7"){
				FunctionDef.narrator("Good,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we're getting somewhere.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " But why did you choose the trees twice?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " It is kind of confusing,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " but whatever,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("we should continue moving,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we could take that path we saw earlier.", 80); FunctionDef.skip(1000);
				cout << "\n";
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.MCS("Got them.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " We should take the path we saw earlier.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " It might lead somewhere.", 80); FunctionDef.skip(1000);					
				cout << "\n";
				FunctionDef.narrator("It should lead somewhere,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I assume a village.", 80); FunctionDef.skip(1000);		
			}	
			else if(b0=="8"){
				FunctionDef.narrator("Great,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " grab those,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " they will be very useful.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we should continue moving,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("we could take that path we saw earlier.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Okay.", 100); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.narrator("Good,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " you can walk now,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " try to be stealthy,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we don't know what might be here with us.", 80); FunctionDef.skip(1000);			
			}
			else if(b0=="9"){
				FunctionDef.narrator("Why would you pick the trees frist?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Such a waste of time.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Let's just grab these and let's keep moving.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Sorry about that,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " yes.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " let's keep moving after I grab those.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " We should take that path we saw earlier.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";FunctionDef.narrator("I suppose that is the only path and choice we have.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " It must lead to a village,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I'm pretty positive.", 80); FunctionDef.skip(1000);			 
			}
			if(b0!="1"&&relwvoid!=1){
				cout << endl << "\n";FunctionDef.truenarrator("You are approached by a pack of wolves ready to attack you. You have to defend yourself.", 50); cout << "\n";FunctionDef.truenarrator("In a quick manner, you have to choose the action you take: ", 50); cout << endl << "\n";FunctionDef.truenarrator("1) Use a stick to fight them",50); FunctionDef.skip(200); cout << "\n";FunctionDef.truenarrator("2) Use an iron sword to fight them", 50); cout << "\n";FunctionDef.truenarrator("3) Try to distract them with the stick instead of fighting.", 50); cout << endl << "\n";
				cout << "\033[33m>>    ";
				decision2 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
				if(decision2=="1"){
					FunctionDef.truenarrator("You decide to take out the stick and use it to fight the wolves off. Commencing combat.", 50); FunctionDef.skip(200);
					UlozitInfo("Stick", "CurrentWeapon.txt"); ambush("Wolves"); 
				}
				else if(decision2=="2"){
					FunctionDef.truenarrator("You decide to take out the iron sword and use it to fight the wolves off. Commencing combat.", 50); FunctionDef.skip(200);
					UlozitInfo("IronSword", "CurrentWeapon.txt"); ambush("Wolves"); 
				}
				else if(decision2=="3"){
					int wolfescapechance = rand()%4;
					if(wolfescapechance==1){
						FunctionDef.truenarrator("You attempt to distract the wolves using a stick. You throw it and the wolves indeed do get distracted.", 50); // Achievement, 25% chance to work 
					}
					else{
						FunctionDef.truenarrator("You try to distract the wolves with the stick, but they fail to notice it and devour you.", 50); FunctionDef.skip(400); cout << "\n";
						deathsequence();
					}
				}
			}
			if((b0=="1"||b0=="6")&&decision2=="3") c="1";
			else if((b0!="1"&&b0!="6")&&decision2=="3") c="2";
			else if((b0=="1"||b0=="6")&&decision2=="1") c="3";
			else if((b0!="1"&&b0!="6")&&decision2=="1") c="4";
			else if((b0=="1"||b0=="6")&&decision2=="2") c="5";
			else if((b0!="1"&&b0!="6")&&decision2=="2") c="6";
			if(c=="1"){
				FunctionDef.narrator("Are you crazy?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You could have gotten us killed.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You are lucky that worked.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("You should continue walking on this path.", 80); FunctionDef.skip(1000);
				cout << "\n"; 
				FunctionDef.MCS("It was a good idea,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " we could have died fighting.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " It distracted them and we are safe now.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("I'll continue walking now.", 80); FunctionDef.skip(1000);
			}
			else if(c=="2"){
				FunctionDef.narrator("Woah.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Good idea with that stick,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I didn't expect it would work.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("I didn't think it would work either,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " but I am glad it did.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's keep on going.", 80); FunctionDef.skip(1000);
			}
			else if(c=="3"){
				FunctionDef.narrator("Why would you use the stick on the wolves?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We're lucky that we're still alive.", 80); FunctionDef.skip(1000);
				cout << "\n"; 
				FunctionDef.MCS("It was a decision I had to make on the spot.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " It might have been rash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " but we won the fight.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's continue moving.", 80); FunctionDef.skip(1000); 
			}
			else if(c=="4"){
				FunctionDef.narrator("Okay...?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Good job,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you've got some skill with that stick.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Why didn't you use the sword though?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("I don't know.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " The stick was the first thing I got a hold of,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " so I used it.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " But it doesn't matter.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We won,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " so let's move.", 80); FunctionDef.skip(1000);
			}
			else if(c=="5"){
				FunctionDef.narrator("Atleast you're decent at fighting with a sword.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Continue moving forward.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Thanks for the appreciation I guess...", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " You haven't been very useful to me,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " you know?", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("But that's probably not your fault.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's keep moving.", 80); FunctionDef.skip(400);
			}
			else if(c=="6"){
				FunctionDef.narrator("Amazing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you did great!", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should continue before we are met by another pack of wolves.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("I'm sure there is a lot of them around here.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Thank you,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " and I agree.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's continue on our way.", 80); FunctionDef.skip(1000);		
			}
			sequence2(language);
		}
		else{
		if(saveload==1){
				cout << "\n\n\n"; FunctionDef.truenarrator("\tVitaj späť cestovateľ. Chýbal si nám. Môžeš pokračovať "+mode+ " na svojej ceste.", 50); Sleep(2500);
				system("cls");
			}
			if(sequence==0) sequence++;
			save();
			Sleep(500);
		cout << "\n\n\n\n\n\n\t\t{[()]} Akt 1 {[()]}\n\n\n"; Sleep(500);
		FunctionDef.truenarrator("\t\tHra automaticky ukladá každý akt. Veľa šťastia na cestách.", 50);
		Sleep(2000); system("cls");
		Sleep(2500);
		FunctionDef.MCS("Kde to som?", 80);FunctionDef.narratorclean(mc," Ako som sa sem dostal?",80); FunctionDef.skip(1000);
		cout << endl;
		FunctionDef.MCS("Všade okolo mňa je len hustý les.", 80); FunctionDef.skip(1000);
		cout << endl;
		FunctionDef.MCS("Ja, ", 100);FunctionDef.narratorclean(mc,"...", 200); FunctionDef.skip(500);FunctionDef.narratorclean(mc," nič si nepamätám.", 80); FunctionDef.skip(1500);
		cout << endl;
		FunctionDef.narrator("Čo sa deje?! ", 80); FunctionDef.skip(600);FunctionDef.narratorclean(vc,"Prečo nemôžem ovládať svoje telo? ", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Počkať, toto... ", 175); FunctionDef.skip(300);FunctionDef.narratorclean(vc,"Toto nie je moje telo!", 80);
		cout << endl;
		FunctionDef.MCS("Kto to povedal? ", 40); FunctionDef.skip(750);
		cout << endl;
		FunctionDef.MCS("Kde si? Ukáž sa!", 75); FunctionDef.skip(1000);
		cout << endl;
		FunctionDef.narrator("Nemôžem sa ukázať.", 80); FunctionDef.skip(1000); cout << endl;
		FunctionDef.MCS("Ako to myslíš že nemôžeš?", 80); FunctionDef.skip(1000);
		cout << endl;
		FunctionDef.narrator("Sám netuším.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Vyzerá to tak...", 120); FunctionDef.skip(400);FunctionDef.narratorclean(vc," že som v tebe.", 100); FunctionDef.skip(750);
		cout << endl << endl;FunctionDef.truenarrator("1) Prečo si vo mne?", 50); cout << "\n";FunctionDef.truenarrator("2) Ako je to možné?",50); cout << "\n";FunctionDef.truenarrator("3) Čo sa stalo s mojimi spomienkami?",50); cout << "\n";FunctionDef.truenarrator("4) Klameš!. Isto sa schovávaš niekde za tými stromami.",50); 
		cout << "\n\n\033[33m>>    ";
		diadec2 = FunctionDef.GVIclean(1,4);
		cout << "\033[0m";
		if(diadec2=="1"){
			FunctionDef.MCSC(mc, "Prečo si vo mne?", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.narrator("Dobrá otázka.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Všetko čo si pamätám, je moja smrť.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," a zrazu,", 125);FunctionDef.narratorclean(vc," som sa ocitol tu,", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc," v tvojom tele.", 100); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Čo myslíš pod tvojou smrťou?", 50); cout << "\n";FunctionDef.truenarrator("2) Počkaj, ty si mŕtvy?",50); cout << "\n";FunctionDef.truenarrator("3) Toto je sen, že?",50); cout << "\n";FunctionDef.truenarrator("4) Čo?",50); 		
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc,"Čo myslíš pod tvojou smrťou?", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Toto musí byť nočná mora.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Nuž,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," nemáme moc na výber,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," postav sa a poobzeraj sa tu trochu.", 80 ); FunctionDef.skip(250);
				cout << endl;
				FunctionDef.narrator("Medzitým ti skúsim vysvetliť čo som myslel pod \"smrťou\" a taktiež skúsime zistiť, prečo som v tvojej hlave ", 80);
				cout << endl;
				FunctionDef.narrator("a prečo si nič nepamätáš.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Postav sa a poďme inde, skôr než nás niekto", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," alebo horšie,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," niečo nájde.", 100); FunctionDef.skip(1000);
				cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mmal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Neverím ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nočná mora,že?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohnúť.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Myslíš, že máš na výber? Čo iné chceš robiť?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Neverím ti.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Nemusíš mi veriť.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stačí, keď sa postavíš a pohneš tým svojim zadkom predtým než nás niečo nájde a obidvoch nás zabije.", 75); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Toto je nočná mora,že?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Ale no tak, vschop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasné, že toto nie je nočná mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj keď možno aj je, ale na tom nezáleží.", 80); FunctionDef.skip(200); cout << endl;
					FunctionDef.narrator("Umierať vo sne tiež stojí za nič.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa prosím ťa postav a spolu na to prídeme.", 80); FunctionDef.skip(1000);
					FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Oukej, mali by sme sa pohnúť.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Výborne, poďme tadiaľto.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Vyzerá to tam sľubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			else if(diadec3=="2"){
				FunctionDef.MCSC(mc,"Počkať, ty si mŕtvy?", 70); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Potvrdzujem. Teda aspoň to tak vyzerá.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("No,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," nemáme zrovna čas na zbytočné premýšľania,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," postav sa a poobzeraj sa.", 80 ); FunctionDef.skip(250);
				cout << endl;
				FunctionDef.narrator("Medzitým, ti skúsim vysvetliť čo som myslel pod \"smrťou\" a taktiež skúsime zistiť, prečo som v tvojej hlave", 80);
				cout << endl;
				FunctionDef.narrator("a prečo si nič nepamätáš.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Postav sa skôr než nás niekto", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," alebo horšie,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," niečo nájde.", 100); FunctionDef.skip(1000);
				cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Neverím ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nočná mora, že?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohnúť.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Myslíš, že máš na výber? čo iné chceš robiť?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Neverím ti.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Nemusíš mi veriť.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stačí, keď sa pohneš s tým svojím zadkom predtým, než nás niečo zabije.", 75); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Toto je nočná mora, že?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Ale no tak, vzchop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasné, že toto nie je nočná mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj keď, možno aj je, ale na tom nezáleží.", 80); FunctionDef.skip(200); cout << endl;
					FunctionDef.narrator("Umieranie v sne tiež stojí za nič.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa prosím ťa postav a spolu na to prídeme.", 80); FunctionDef.skip(1000);
					FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohnúť.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Výborne, poďme tadiaľto.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Vyzerá to tam sľubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			else if(diadec3=="3"){
				FunctionDef.MCSC(mc,"To nie je možné!", 70);FunctionDef.narratorclean(mc," Snívam?", 100); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Chápem, že je ťažké pochopiť takúto situáciu,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," ale každopádne,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," či už sen alebo realita,", 100); FunctionDef.skip(250);
				cout << endl;
				FunctionDef.narrator("musíme sa pohnúť. Takže by som ti navrhoval vsať skôr než nás niekto", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," alebo horšie,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," niečo,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," nájde.", 80 );
				cout << endl;
				FunctionDef.narrator("Medzitým, ti skúsim vysvetliť, čo som myslel pod \"smrťou\" a taktiež skúsime zistiť, prečo som v tvojej hlave", 80);
				cout << endl;
				FunctionDef.narrator("a prečo si nič nepamätáš.", 80);
				cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Neverím ti.",50); cout << "\n";FunctionDef.truenarrator("3) To je šialenstvo.",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohnúť.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Myslíš, že máš na výber? Čo iné chceš robiť?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Neverím ti.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Nemusíš mi veriť.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stačí, keď sa pohneš s tým svojím zadkom predtým, než nás niečo zabije.", 75); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"To je šialenstvo.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," Nerozumiem.", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ale nemám moc na výber. Takže ti vyhoviem.", 80 ); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Vysvetlím ti všetko, čo viem, akonáhle sa odtiaľto dostaneme.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohnúť.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Výborne, poďme tadiaľto.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Vyzerá to tam sľubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			else if(diadec3=="4"){
				FunctionDef.MCSC(mc,"Čo??", 70); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Chápem, že to teraz asi nedokážeš pochopiť,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," ale každopádne,", 100); FunctionDef.skip(250); 
				cout << endl;
				FunctionDef.narrator("musíme sa pohnúť. Takže by som ti radil vstať a odísť odtiaľto skôr než nás niekto", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," alebo horšie,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," niečo,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," nájde.", 80 );
				cout << endl;
				FunctionDef.narrator("Medzitým, ti skúsim vysvetliť, čo som myslel pod \"death\" a taktiež skúsime prísť na to, prečo som v tvojej hlave", 80);
				cout << endl;
				FunctionDef.narrator("a prečo si nič nepamätáš.", 80);
				cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Neverím ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nočná mora, že?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohnúť.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Myslíš, že máš na výber? Čo iné chceš robiť?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Neverím ti.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Nemusíš mi veriť.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stačí, keď pohneš s tým svojím zadkom skôr, než nás niečo zabije.", 75); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Toto je nočná mora, že?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Ale no tak, vzchop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasné, že toto nie je nočná mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj keď možno je, ale na tom nezáleží.", 80); FunctionDef.skip(200); cout << endl;
					FunctionDef.narrator("Umierať v sne tiež stojí za dve veci.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa už prosím ťa postav a spolu to nejako rozlúskneme.", 80); FunctionDef.skip(1000); cout << endl;
					FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohnúť.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Výborne, poďme tadiaľto.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Vyzerá to tam sľubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
		}
		else if(diadec2=="2"){
			FunctionDef.MCSC(mc, "Ako je to možné?", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.narrator("Netuším.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Ale čo viem,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," je to,", 125);FunctionDef.narratorclean(vc," že by sme mali odtiaľto vypadnúť,", 100); FunctionDef.skip(500); cout << endl;FunctionDef.narrator("nechceme, aby nás tu čokoľvek našlo, že?", 80); FunctionDef.skip(1000);FunctionDef.narratorclean(vc," Odpovede ti dám po ceste,", 80); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("proste sa postav a daj do pohybu,", 80); FunctionDef.skip(200);FunctionDef.narratorclean(vc, " prosím.", 100); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Neverím ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nočná mora, že?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohnúť.",50); 		
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc,"Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Myslíš, že máš na výber? Čo iné chceš robiť?", 75); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="2"){
				FunctionDef.MCSC(mc,"Neverím ti.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Nemusíš mi veriť.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stačí, keď pohneš s tým svojím zadkom skôr, než nás niečo zabije.", 75); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="3"){
				FunctionDef.MCSC(mc,"Toto je nočná mora, že?", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Ale no tak, vzchop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasné, že toto nie je nočná mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj keď, možno je, ale na tom nezáleží.", 80); FunctionDef.skip(200); cout << endl;
				FunctionDef.narrator("Umierať v sne tiež za moc nestojí.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa už prosím ťa postav a spolu to nejako rozlúskneme.", 80); FunctionDef.skip(1000); cout << endl;
				FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
			}
			if(diadec3=="4"){
				FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohnúť.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Výborne, poďme tadiaľto.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Vyzerá to tam sľubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
			}
		}
		if(diadec2=="3"){
			FunctionDef.MCSC(mc, "Ale kde sú moje spomienky?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," Len tak si sem prišiel, a všetky sú preč.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Čo si snimi urobil?", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.narrator("Ja som tvojim spomienkam nič neurobil.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Nič o tom neviem,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," rovnako ako ty.", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," myslíš, že tu chcem byť?", 100); FunctionDef.skip(500); cout << endl;FunctionDef.narrator("Umrel som ani neviem ako a zrazu som v cudzom tele,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " v tvojom tele,", 100);FunctionDef.narratorclean(vc, " ktoré nemôžem kontrolovať.", 100); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("Ale,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," sme tam, kde sme,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," tak pohni s tým svojím zadkom a postav sa.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Neverím ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto musí byť nočná mora.",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohnúť.",50); 	
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc,"Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Myslíš, že máš na výber? Čo iné chceš robiť?", 75); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="2"){
				FunctionDef.MCSC(mc,"Neverím ti.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Nemusíš mi veriť.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stačí, keď pohneš s tým svojím zadkom skôr, než nás niečo zabije.", 75); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="3"){
				FunctionDef.MCSC(mc,"Toto musí byť nočná mora!...", 80);FunctionDef.narratorclean(mc, "ARGHHHH!", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Nemáme na výber,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," musíme spolupracovať,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," jedine, že by si chcel umrieť.", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Dobre, tak poďme.", 50); cout << "\n";FunctionDef.truenarrator("2) Moment, prečo by som mal umrieť?",50); cout << "\n";FunctionDef.truenarrator("3) Nie! Chcem ísť vlastnou cestou.",50); cout << "\n";FunctionDef.truenarrator("4) Nepohnem sa odtiaľto, kým mi nepovieš, kto si.",50); 	
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4); 
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Dobre, tak poďme.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Výborne.", 75);FunctionDef.narratorclean(vc," Vydajme sa týmto smerom.", 75); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Počkaj, prečo by som mal umrieť?", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Pretože budeš na tomto svete sám,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " bez spomienok,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ukradtnutý každému,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a ľahký cieľ pre nepriateľov.", 75); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("V tomto lese nie sme sami.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " A ja som ten, ktorý ti pomôže sa odtiaľto bezpečne dostať.", 75); FunctionDef.skip(1000); 
					cout << endl;
					FunctionDef.MCS("Prečo sa mi toto deje?", 75); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Viem, že si vystrašený a frustrovaný.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ale ver mi,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," naša jediná šanca, ako prežiť, je postaviť sa pohnúť sa odtiaľto.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Vyzerá to tak, že nemám na výber...", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," Dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," budem spolupracovať.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Super. Tak sa vydajme na cestu.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Nie! Chcem ísť vlastnou cestou.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Vieš čo, fajn, choď si svojou cestou, uvidíme, kam nás to zavedie.", 75); FunctionDef.skip(1500);
					// endingplaceholder1();
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Nepohnem sa odtiaľto, kým mi nepovieš, kto si.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Dobre, dobre.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Všetko ti poviem...", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Volám sa Void.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Bol som generálom frakcie", 75); cout << endl;FunctionDef.narrator("ktorej meno bolo Terragnis.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Boli sme vo vojne s inou frakciou, volali sa Slofridi.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Bol som uprostred boja,", 80); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("keď ma zasiahol šíp.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ale,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," nejakým zázrakom,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," som neumrel.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Zrazu,", 100); FunctionDef.skip(250); cout << endl;FunctionDef.narrator(" som videl ostré svetlo, po ktorom nasledovala tma.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Keď som prišiel k vedomiu, našiel som sa v cudzom tele...", 75); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("v tvojom tele.", 75); FunctionDef.skip(400);FunctionDef.narratorclean(vc," A teraz,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," sme tu.", 100); FunctionDef.skip(1500);
					cout << endl;
					FunctionDef.MCS("Takže si umriel a zobudil sa v mojom tele.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Áno, v skratke.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Ale ako je to možné?", 80); FunctionDef.skip(1000); 
					cout << endl;
					FunctionDef.narrator("Povedal som ti všetko, čo viem.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Tiež by som rád vedel viac,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ale nič nezistíme, pokiaľ tu budeme len tak sedieť.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.MCS("Máš pravdu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," poďme odtiaľto preč.", 75); FunctionDef.skip(1500);	relwvoid = 3;
					earlyexplanation = true;	
				}
			}
		}
		else if(diadec2=="4"){
			FunctionDef.MCSC(mc, "Klameš!", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Schovávaš sa za tými stromami, že??", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.narrator("Nie som klamár.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Iba vtedy, keď je to fakt nevyhnutné.", 80); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("Ale zato ty by si sa mal pohnúť s tým zadkom, inak kvôli tebe obidvaja umrieme.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Fajn, pohnime sa.", 50); cout << "\n";FunctionDef.truenarrator("2) Vyhoviem ti, keď mi podáš lepšie vysvetlenie.",50); cout << "\n";FunctionDef.truenarrator("3) Nechápem, ako je to možné?",50); cout << "\n";FunctionDef.truenarrator("4) Tak toto ti neverím. Iba sa ma snažíš vylákať von.",50);
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc, "Dobre,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, "tak sa dajme do pohybu.", 75); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Super.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Vydajme sa tadiaľto,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " vyzerá to tam sľubne.", 80); FunctionDef.skip(1500); relwvoid = 3;
			}
			else if(diadec3=="2"){
				FunctionDef.MCSC(mc, "Vyhoviem ti, keď mi podáš lepšie vysvetlenie.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Povedal som ti,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " fakt neviem.", 80);FunctionDef.narratorclean(vc, " Jediné čo viem je, že som uväznený v tvojej hlave a že nás dostaneš ", 80); cout << endl;FunctionDef.narrator("do hrobu pokiaľ sa odtiaľto nepohneš,",80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tak ťa prosím,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " pohni sa,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a poviem ti viac po ceste.", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Prečo by som ťa mal počúvať?", 50); cout << "\n";FunctionDef.truenarrator("2) Nie, stále ti neverím. Odmietam tomuto všetkému veriť.", 50); cout << "\n";FunctionDef.truenarrator("3) Fajn, tak sa teda dám do pohybu", 50);
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,3);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc, "Prečo by som ťa mal počúvať?", 80); FunctionDef.skip(1000);
					FunctionDef.narrator("Nemáš na výber.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Aj keď, možno máš,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " rob si čo chceš,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " chceš tak veľmi umrieť?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Prosím, v kľude si choď.", 80); FunctionDef.skip(1000);
					cout << endl << endl;FunctionDef.truenarrator("1) Pôjdem svojou vlastnou cestou.", 50); cout << "\n";FunctionDef.truenarrator("2) Dobre, počkaj, ospravedlňujem sa. Urobím, čo chceš.", 50);
					cout << "\n\n\033[33m>>    ";
					diadec5 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec5=="1"){
						FunctionDef.MCSC(mc, "Pôjdem svojou vlastnou cestou.", 50); FunctionDef.skip(1000);
						cout << endl;
						FunctionDef.narrator("Vieš čo, fajn, choď kam chceš, uvidíme, kam sa dostaneš.", 80);
						// endingplaceholder1();
					}
					else{
						FunctionDef.MCSC(mc, "Dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " prepáč.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Urobím, čo chceš.", 80); FunctionDef.skip(1000);
						cout << endl;
						FunctionDef.narrator("Tak predsa len.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Nuž,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " nemáme času nazvyš,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " povstaň a vydaj sa tamtou cestou.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
				}
				else if(diadec4=="2"){
					FunctionDef.MCSC(mc, "Nie,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " stále ti neverím.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Odmietam tomuto všetkému veriť.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Aha,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " takže tu chceš umrieť?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Prosím,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " choď kam chceš.", 80); FunctionDef.skip(1000);
					cout << endl << endl;FunctionDef.truenarrator("1) Pôjdem tam, kde chcem.", 50); cout << "\n";FunctionDef.truenarrator("2) Vieš čo, fajn, počúvnem ťa.", 50);
					cout << "\n\n\033[33m>>    ";
					diadec5 = FunctionDef.GVIclean(1,2);
					cout << "\033[0m";
					if(diadec5=="1"){
						FunctionDef.MCSC(mc, "Pôjdem tam, kde chcem.", 50); FunctionDef.skip(1000);
						cout << endl;
						FunctionDef.narrator("Vieš čo, ako chceš, choď svojou cestou. Aspoň uvidíme, kam to vedie.", 80);
						// endingplaceholder1();
					}
					else{
						FunctionDef.MCSC(mc, "Vieš čo,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " fajn,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " počúvnem ťa.", 80); FunctionDef.skip(1000);
						cout << endl;
						FunctionDef.narrator("Konečne...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Môžeme sa pohnúť.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Postav sa,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a poďme touto cestou.", 80); FunctionDef.skip(1500); relwvoid = 1;
					}
				}
				else{
					FunctionDef.MCSC(mc, "Fajn,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " dám sa do pohybu.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " v poriadku,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mali by sme ísť tadiaľto.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
			}
			else if(diadec3=="3"){
				FunctionDef.MCSC(mc, "Nerozumiem, ako je to možné?", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Tiež tomu nerozumiem.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Môžeme to spolu zistiť,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " len sa už,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " prosím ťa,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " pohni.", 100); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Jasné, prepáč, dám sa do pohybu.", 50); cout << "\n";FunctionDef.truenarrator("2) Čo ak nie?", 50);
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc, "Jasné,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " prepáč,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " dám sa do pohybu.", 90); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("V pohode", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " poďme tadiaľto.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Zdá sa mi, že tam niečo vidím.", 80); FunctionDef.skip(1000); relwvoid = 3;
				}
				else{
					FunctionDef.MCSC(mc, "Čo ak,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " nie?", 100); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Fakt si chceš zo mňa urobiť nepriateľa?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Pamätaj,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " som v tvojej hlave,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a kedykoľvek môžem pre teba z tohto urobiť ", 80); cout << endl;FunctionDef.narrator("peklo na Zemi.", 80); FunctionDef.skip(1000);
					cout << endl << endl;FunctionDef.truenarrator("1) Áno. A chcem ísť svojou cestou.", 50); cout << "\n";FunctionDef.truenarrator("2) Zmenil som názor, prepáč, už ťa budem počúvať.", 50); 
					cout << "\n\n\033[33m>>    ";
					diadec5 = FunctionDef.GVIclean(1,2);
					cout << "\033[0m";
					if(diadec5=="1"){
						FunctionDef.MCSC(mc, "Áno. A chcem ísť svojou cestou.", 80); FunctionDef.skip(1000);
						cout << endl;
						FunctionDef.narrator("Vieš čo, rob si ako chceš, uvidíme, kam sa dostaneme.", 80); FunctionDef.skip(1500);
						// endingplaceholder1();
					}
					else{
						FunctionDef.MCSC(mc, "Zmenil som názor,",80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " prepáč,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " už ťa budem počúvať.", 80); FunctionDef.skip(1000);
						cout << endl;
						FunctionDef.narrator("Tak nakoniec predsa len,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " fajn,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "poďme tadiaľto,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Skúsim ti vysvetliť všetko, čo viem.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Pokiaľ chceme spolu nažívať", 80); cout << endl;FunctionDef.narrator("v mieri,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tak musíme spolupracovať.", 80); FunctionDef.skip(1500); relwvoid = 2;
					}
				}
			}
			else{
				FunctionDef.MCSC(mc, "Na to ti neskočím.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Snažíš sa ma dostať von.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Vážne?", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Počúvaj,", 80);FunctionDef.narratorclean(vc," nemáš na výber,", 80);FunctionDef.narratorclean(vc," pohni sa,",100);FunctionDef.narratorclean(vc," nemáš čo stratiť.", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Prestaň na mňa hovoriť, chcem ísť vlastnou cestou.", 50); cout << "\n";FunctionDef.truenarrator("2) Fajn.", 50); cout << "\n";FunctionDef.truenarrator("3) Prepáč, chcel som sa iba uistiť. Môžeme ísť.", 50); 
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,3);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc, "Prestaň na mňa hovoriť,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " chcem ísť vlastnou cestou.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Vieš čo, fajn, choď, kadiaľ chceš, uvidíme, čo z tohto vznikne.", 80); FunctionDef.skip(1500);
					// endingplaceholder1();
				}
				else if(diadec4=="2"){
					FunctionDef.MCSC(mc, "Fajn.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("Tvoj postoj je otrasný,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mohol by si prejaviť aspoň trochu úcty tomu hlasu, čo máš v hlave.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Poobzeraj sa trochu,", 80); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("vyzerá to, že tamtým smerom niečo je.", 80); FunctionDef.skip(1500); relwvoid = 1;
				}
				else{
					FunctionDef.MCSC(mc, "Prepáč,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " chcel som sa len uistiť.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Môžeme sa dať do pohybu.", 80); FunctionDef.skip(1000);
					cout << endl;
					FunctionDef.narrator("To je v pohode,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Chápem ťa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " tak sa teda vydajme na cestu.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Vyzerá, že táto cesta niekam vedie.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
			}
		}
		cout << endl;
		cout << endl;
		d1();
		while(true){
			if(a>0 || b>0) d1(lang);
			cout << endl << endl;
			FunctionDef.flushInput();
			cout << "\033[33m>>    ";
			decision1 = FunctionDef.GVIclean(1,5);
			cout << "\033[0m";
			if(decision1=="1"){
				FunctionDef.MCSC(mc, "Chcem sa pozrieť na tie stromy.", 80);
				cout << endl << endl;
				d1n(lang);
				FunctionDef.skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="2"){
				FunctionDef.MCSC(mc, "Chcem sa pozrieť na tie stromy.", 80);
				cout << endl << endl;
				d1n(lang);
				FunctionDef.skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="3"){
				FunctionDef.MCSC(mc, "Musím vidieť tie stromy.", 80);
				cout << endl << endl;
				d1n(lang);
				FunctionDef.skip(500);
				cout << endl << endl;
				a++;
				continue;		
			}
			else if(decision1=="4"){
				FunctionDef.MCSC(mc, "Chcel by som vedieť, kam vedie táto cesta.", 80);
				cout << endl << endl;
				FunctionDef.truenarrator("Okej, rozhodol si sa zistiť, aký je cieľ tej cesty. Si si istý, že nechceš naskôr skontrolovať\n      to opustené miesto medzi stromami, kde môžu ležať užitočné veci?", 50);
				cout << endl << endl;
				FunctionDef.skip(250);
				FunctionDef.truenarrator("1) Pokračovať v pôvodnom rozhodnutí a ísť preskúmať cestu\n      2) Upustiť od pôvodného rozhodnutia a ísť preskúmať opustené miesto medzi stromami", 50);
				cout << endl << endl;
				FunctionDef.flushInput();
				cout << "\033[33m>>    ";
				decision1sub1 = FunctionDef.GVI(1,2);
				cout << "\033[0m";
				if(decision1sub1=="1"){
					FunctionDef.MCSC(mc, "Veľmi chcem vedieť, kam to vedie.", 80);
					cout << endl << endl;
					FunctionDef.truenarrator("Nuž dobre, rozhodol si sa vydať na dobrodrúžnu cest- hups, tak nič, umrel si. Dôvod: NEZNÁMY", 50);
					FunctionDef.skip(400);
					lives--; deathsequence(lang);
				}
				else if(decision1sub1=="2"){
					FunctionDef.MCSC(mc, "Myslím, že by sme mali najskôr skontrolovať to opustené miesto.", 80);
					cout << endl << endl;
					FunctionDef.truenarrator("Nakoniec si sa rozhodol skontrolovať to divné miesto s opustenými vecami na zemi. A pred sebou máš:",50); cout << "\n\n";FunctionDef.truenarrator("- Čaj",50); cout << "\n";FunctionDef.truenarrator("- Železný meč",50); cout << "\n";FunctionDef.truenarrator("- ľahko-zničiteľné zlaté brnenie",50); cout << "\n";FunctionDef.truenarrator("- Štít",50); cout << "\n";FunctionDef.truenarrator("- Elixír lásky",50); cout << "\n";FunctionDef.truenarrator("- Palicu",50); cout << "\n";FunctionDef.truenarrator("- Obväzy x3",50); cout << "\n";FunctionDef.truenarrator("- Malý batoh", 50);
					break;
				}
			}
			else if(decision1=="5"){
				FunctionDef.MCSC(mc, "Rád by som najskôr skontroloval to opustené miesto medzi stromami.", 80);
				cout << endl << endl;
				FunctionDef.truenarrator("Skvelá voľba, teda minimálne lepšia ako \"stromy\", priblížil si sa k opusteným veciam a vidíš nasledovné:",50); cout << "\n\n";FunctionDef.truenarrator("- Čaj",50); cout << "\n";FunctionDef.truenarrator("- Železný meč",50); cout << "\n";FunctionDef.truenarrator("- Ľahko-zničiteľné zlaté brnenie",50); cout << "\n";FunctionDef.truenarrator("- Štít",50); cout << "\n";FunctionDef.truenarrator("- Elixír lásky",50); cout << "\n";FunctionDef.truenarrator("- Palicu",50); cout << "\n";FunctionDef.truenarrator("- Obväzy x3",50); cout << "\n";FunctionDef.truenarrator("- Malý batoh", 50); break;
			}
		}
		cout << endl << endl; diadec1 = ""; diadec2 = ""; diadec3 = ""; diadec4 = ""; diadec5 = "";
		if(a==3&&(relwvoid==1||relwvoid==2)) b0 = "1";
		else if(a==3&&(relwvoid==3||relwvoid==4)) b0 = "2";
		else if(a<2&&(relwvoid==1||relwvoid==2)) b0 = "3";
		else if(a<2&&(relwvoid==3)) b0 = "4";
		else if(a<2&&relwvoid==4) b0 = "5";
		else if(a==2&&(relwvoid==1||relwvoid==2)) b0 = "6";
		else if(a==2&&(relwvoid==3||relwvoid==4)) b0 = "7";
		else if(earlyexplanation==true&&a<2) b0 = "8";
		else if(earlyexplanation==true&&a>1) b0 = "9";
		if(b0=="1"){
			FunctionDef.narrator("Nielen, že si úplný kretén,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," ale ešte aj úplne hlúpy.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Prečo by si si vybral stromy 3-krát po sebe?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Vieš čo,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Radšej to ani nechcem počuť,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " prestaň strácať náš čas, zober veci and vypadni odtiaľto.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Prepáč, fakt som chcel tie stromy.", 50); cout << "\n";FunctionDef.truenarrator("2) Ja som kretén?! Ty si kretén!", 50); cout << endl << endl; 
			cout << "\033[33m>>    ";
			diadec1 = FunctionDef.GVIclean(1,2);
			cout << "\033[0m";
			if(diadec1=="1"){
				FunctionDef.MCSC(mc, "Prepáč, fakt som chcel tie stromy.", 80); FunctionDef.skip(500);
				cout << endl;
				FunctionDef.narrator("Ulož to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " zober veci a CHOĎ!", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500); cout << endl;
			}
			else{
				FunctionDef.MCSC(mc, "Ja som kretén?!", 75); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Ty si kretén!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Ty si ten, ktorým sa mi vtrel do hlavy.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Ja?!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Vieš čo,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " choď do čerta,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " povedal som ti, čo sa stalo a prečo som tu.", 80); FunctionDef.skip(400); cout << endl;FunctionDef.narrator("Tak láskavo prestaň, zober veci a padaj preč odtiaľto skôr, než umrieme.", 80); FunctionDef.skip(1000);
				cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500); cout << endl << endl;
			}
			FunctionDef.narrator("Fakt sa snažím byť milý,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ale ty ma proste nenecháš.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Čo navrhuješ teraz?", 80); FunctionDef.skip(400); cout << endl;FunctionDef.narrator("Pôjdeme touto cestou?", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Ísť cestou, ktorú navrhol Void.", 80); cout << "\n";FunctionDef.truenarrator("2) Ísť opačným smerom.", 50); cout << endl << endl;
			cout << "\033[33m>>    ";
			b1pathdec = FunctionDef.GVIclean(1,2);
			cout << "\033[0m";
			if(b1pathdec=="1"){
				FunctionDef.MCSC(mc, "Fajn, poďme teda tvojou cestou.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Aspoň že počúvaš.", 80); FunctionDef.skip(1000); relwvoid = 2;
			}
			else{
				FunctionDef.MCSC(mc, "Vieš čo?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "nechce sa mi ťa počúvať.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "Radšej by som šiel tdiaľto,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " nemáme čo stratiť.", 80); 
				cout << endl;
				FunctionDef.narrator("Vieš čo,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " fajn,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " choď do ktorejkoľvek riti chceš.", 80); FunctionDef.skip(1000); relwvoid = 1; d="7";
			}
		}
		else if(b0=="2"){
			FunctionDef.narrator("Prečo by si si vybral stromy 3-krát po sebe?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Nie si náhodou", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "-", 200);FunctionDef.narratorclean(vc, " Ospravedlňujem sa.", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Tvoj výber ma frustroval.", 80); FunctionDef.skip(400); cout << endl;FunctionDef.narrator("Je úplne jasné, že tam nič nie je,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " strácame náš čas.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mali by sme ísť ďalej,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " zobver veci a poď.", 80); FunctionDef.skip(1000);
			cout << endl; 
			FunctionDef.MCS("Prepáč.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Poďme tú cestu, čo sme videli predtým.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl; 
			FunctionDef.narrator("Pravda,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tá cesta by nás mohla zaviesť niekde, kde môžeme nájsť odpovede.", 80); FunctionDef.skip(1000);
		}
		else if(b0=="3"){
			FunctionDef.narrator("Zober to a poďme.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " A inak,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " čo je to s tebou?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Upusti od takýchto rozhodnutí,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " bude lepšie, keď sa dohodneme.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl;FunctionDef.truenarrator("1) Ospravedlňujem sa za to...", 50); cout << "\n";FunctionDef.truenarrator("2) ...", 50); cout << endl << endl;
			cout << "\033[33m>>    ";
			diadec1 = FunctionDef.GVIclean(1,2);
			cout << "\033[0m";			 
			if(diadec1=="1"){
				FunctionDef.MCSC(mc, "Ospravedlňujem sa za to...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Nemyslel som to tak,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " bol som iba opatrný.", 80); FunctionDef.skip(400); cout << endl;FunctionDef.MCS("But Ale aspoň už vidím, že nie si zlý a že si naozaj v mojej hlave.", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("V poriadku,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " rozumiem.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Cením si tvoje ospravedlnenie.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mali by sme sa dať do pohybu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " poďme tou cestou, ktorú sme videli predtým.", 80); FunctionDef.skip(1000);
				relwvoid = 3;
			}
			else{
				FunctionDef.MCSC(mc, "...", 80); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.narrator("Ja-", 150); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " chápem, že to musí byť z tvojho pohľadu ťažké.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Keď sa na to pozerám z tvojej perspektívy,", 80);FunctionDef.narratorclean(vc, " tiež by som sebe neveril.", 80); FunctionDef.skip(400); cout << endl;FunctionDef.narrator("Chápem ťa,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " prepáč.", 100); FunctionDef.skip(1000);
				cout << endl;
				FunctionDef.MCS("Ďakujem,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " ale ja som ten, ktorý by sa tu mal ospravedlňovať.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Ale máš pravdu,", 80);FunctionDef.narratorclean(mc, " mali by sme sa dať do pohybu a o tomto sa porozprávame neskôr.", 80); FunctionDef.skip(1000); 
				relwvoid = 3;
			}
		}
		else if(b0=="4"){
			FunctionDef.narrator("Výborne.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Tie veci môžu byť pre nás užitočné.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Zober ich a poďme ďalej.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl;
			FunctionDef.MCS("Dobrý nápad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " nasledujme tú cestu, ktorú sme videli predtým,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " hádam, že vedie do mesta.",80); FunctionDef.skip(400); FunctionDef.narratorclean("\033[33m", " Nemôže predsa viesť odnikiaľ nikam,", 80);FunctionDef.narratorclean("\033[33m", " že?", 100); FunctionDef.skip(1000);
		}
		else if(b0=="5"){
			FunctionDef.narrator("Užasné,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mali sme riadne šťastie.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mali by sme pokračovať v pohybe a dostať sa odtiaľto,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " hneď ako zoberieš tie veci.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl;FunctionDef.MCS("Súhlasím,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " mali by sme sa odtiaľto spakovať,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " máš pravdu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " asi by sme mohli ísť tou cestou, ktorú sme videli predtým,", 80); FunctionDef.skip(250); cout << endl;FunctionDef.MCS("isto niekam vedie.", 80); FunctionDef.skip(1000);			
			cout << endl;
			FunctionDef.narrator("Presne,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " niekam vedie,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " musí,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " neboj sa.", 80); FunctionDef.skip(1000);
		}
		else if(b0=="6"){
			FunctionDef.narrator("Môžeš sa prestať tak extrémne zaujímať o stromy, zobrať tie veci a vypadnúť odtiaľto,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " trkvas?", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Dobre, dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " zoberiem tie veci.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl;
			FunctionDef.MCS("A čo teraz?", 80); FunctionDef.skip(1000);
			FunctionDef.narrator("Vypadneme odtiaľto,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tamtou cestou.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Choď a nič nehovor.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Tvoja reč ma začína iritovať", 80); cout << endl;FunctionDef.narrator("a to sme sa spoznali len 3 minúty dozadu.", 80); FunctionDef.skip(1000);			
		}
		else if(b0=="7"){
			FunctionDef.narrator("Super,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " niekam sa dostávame.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Ale prečo si si 2-krát vybral stromy?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Príde mi to dosť mätúce,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ale čo už,", 80); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("mali by sme pojračovať ďalej,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " môžeme ísť tou cestou, ktorú sme videli predtým.", 80); FunctionDef.skip(1000);
			cout << endl;
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl;
			FunctionDef.MCS("Mám ich.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Vydajme sa teda tamtou cestou.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Možno niekam vedie.", 80); FunctionDef.skip(1000);					
			cout << endl;
			FunctionDef.narrator("Mala by niekam viesť,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " predpokladám, že do dediny.", 80); FunctionDef.skip(1000);		
		}	
		else if(b0=="8"){
			FunctionDef.narrator("Výborne,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " zober ich,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " môžu byť užitočné.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " A hneď potom,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " by sme sa mali dať do pohybu,", 80); FunctionDef.skip(250); cout << endl;FunctionDef.narrator("môžeme ísť tou cestou, ktorú sme videli predtým.", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Dobre.", 100); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl;
			FunctionDef.narrator("Super,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " môžeš sa dať do pohybu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " skús byť nenápadný,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " nikdy nevieme, kto tu s nami môže byť.", 80); FunctionDef.skip(1000);			
		}
		else if(b0=="9"){
			FunctionDef.narrator("Prečo by si išiel 2-krát k stromom?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Absolútna strata času.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Proste iba zober tie veci a daj sa do pohybu.", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Ospravedlňujem sa za to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " ale súhlasím.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Pohnem sa, hneď ako to zoberiem.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Mali by sme ísť tou cestou, ktorú sme videli predtým.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho môžeš nájsť vo svojom inventári, ktorým je batoh.", 50); FunctionDef.skip(500);
			cout << endl;FunctionDef.narrator("Myslím, že je to naša jediná možnosť.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Musí viesť do dediny,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " na sto percent.", 80); FunctionDef.skip(1000);			 
		}
		if(b0!="1"&&relwvoid!=1){
			cout << endl << endl;FunctionDef.truenarrator("Si obkľúčený svorkou vlkov, ktorá je prepravená na teba zaútočiť. Musíš sa brániť.", 50); cout << endl;FunctionDef.truenarrator("Musíš sa rýchlo rozhodnúť, čo urobíš: ", 50); cout << endl << endl;FunctionDef.truenarrator("1) POužiť palicu a bojovať s nimi",50); FunctionDef.skip(200); cout << endl;FunctionDef.truenarrator("2) Použiť meč a bojovať s nimi", 50); cout << endl;FunctionDef.truenarrator("3) Skúsiť ich odlákať palicou namiesto bojovania.", 50); cout << endl << endl;
			cout << "\033[33m>>    ";
			decision2 = FunctionDef.GVI(1,3);
			cout << "\033[0m" << endl;
			if(decision2=="1"){
				FunctionDef.truenarrator("Rozhodol si sa zobrať palicu a s ňou sa vrhnúť do boja. Zahájujem súboj.", 50); FunctionDef.skip(200);
				ambush("Wolves", lang); 
			}
			else if(decision2=="2"){
				FunctionDef.truenarrator("Rozhodol si sa zobrať meč a s ním sa vrhnúť do boja. Zahájujem súboj.", 50); FunctionDef.skip(200);
				ambush("Wolves", lang); 
			}
			else if(decision2=="3"){
				int wolfescapechance = rand()%4;
				if(wolfescapechance==1){
					FunctionDef.truenarrator("Skúsil si vlkov odlákať palicou. Hodil  si ho a podarilo sa ti ich odlákať.", 50); // Achievement, 25% chance to work 
				}
				else{
					FunctionDef.truenarrator("Skúsil si vlkov odlákať palicou, ale vôbec nezareagovali a roztrhali ťa ka kúsky.", 50); FunctionDef.skip(400); cout << endl;
					lives--; deathsequence();
				}
			}
		}
		if((b0=="1"||b0=="6")&&decision2=="3") c="1";
		else if((b0!="1"&&b0!="6")&&decision2=="3") c="2";
		else if((b0=="1"||b0=="6")&&decision2=="1") c="3";
		else if((b0!="1"&&b0!="6")&&decision2=="1") c="4";
		else if((b0=="1"||b0=="6")&&decision2=="2") c="5";
		else if((b0!="1"&&b0!="6")&&decision2=="2") c="6";
		if(c=="1"){
			FunctionDef.narrator("Zbláznil si sa?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Mohol si nás zabiť.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Máš šťastie, že to vyšlo.", 80); FunctionDef.skip(400); cout << endl; FunctionDef.narrator("No nič, pokračujme ďalej po ceste.", 80); FunctionDef.skip(1000);
			cout << endl; 
			FunctionDef.MCS("Bol to dobrý nápad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " v boji by sme mohli umrieť.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Odlákal som ich a teraz sme v bezpečí.", 80); FunctionDef.skip(400); cout << endl; FunctionDef.MCS("Idem teda ďalej.", 80); FunctionDef.skip(1000);
		}
		else if(c=="2"){
			FunctionDef.narrator("Wau!", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " To s tou palicou bol dobrý nápad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " nečakal som, že to bude fungovať.", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Tiež som si nemyslel, že to môže fungovať,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " ale som rád, že to vyšlo.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Nezastavujme a poďme ďalej.", 80); FunctionDef.skip(1000);
		}
		else if(c=="3"){
			FunctionDef.narrator("Prečo by si používal na vlkov palicu?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Máme šťastie, že sme stále nažive.", 80); FunctionDef.skip(1000);
			cout << endl; 
			FunctionDef.MCS("Bolo to veľmi spontánne rozhodnutie.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Možno to bolo ubáhlené,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " ale každopádne sme vyhrali.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Pokračujme ďalej.", 80); FunctionDef.skip(1000); 
		}
		else if(c=="4"){
			FunctionDef.narrator("Zaujímavé...?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Dobrá práca,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " očividne vieš, ako používať palicu.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Ale prečo si namiesto toho nepoužil meč?", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Netuším.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Zobral som prvú vec, čo mi prišla do rany a náhodou to bola zrovna palica,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " tak som ju použil.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Ale na to nezáleží.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Vyhrali sme,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " tak sa dajme to pohybu.", 80); FunctionDef.skip(1000);
		}
		else if(c=="5"){
			FunctionDef.narrator("Aspoň že vieš bojovať s mečom.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Pokračuj smerom vpred.", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Ďakujem za uznanie, asi...", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Zatiaľ si mi nebol veľmi nápomocný,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " vieš o tom?", 80); FunctionDef.skip(400); cout << endl; FunctionDef.MCS("Ale to asi nie je tvoja chyba.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Pokračujme ďalej.", 80); FunctionDef.skip(400);
		}
		else if(c=="6"){
			FunctionDef.narrator("Úžasné,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " bol si super!", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Mali by sme sa pohnúť ďalej skôr, než sem príde ďalšia svorka.", 80); FunctionDef.skip(400); cout << endl; FunctionDef.narrator("Som si istý, že je ich tu veľa.", 80); FunctionDef.skip(1000);
			cout << endl;
			FunctionDef.MCS("Ďakujem,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " a súhlasím.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Poďme teda ďalej.", 80); FunctionDef.skip(1000);		
		}
		sequence2(language);
		}
	}
	void sequence2(string language){
		if(lang=="en"){
			if(sequence==1) sequence++; save(); system("cls"); Sleep(1000);
			diadec1 = ""; diadec2 = ""; diadec3 = "";
			cout << "\n\n\n\n\n\n        {[()]} Sequence 2 {[()]}\n\n\n"; Sleep(1000);FunctionDef.truenarrator("  You're doing great!(not)", 50); Sleep(2000); system("cls"); Sleep(2500);
			cout << "\n";
			FunctionDef.truenarrator("You walk through a captivating meadow, full of birds, dead bodies and charred weapons.", 50); FunctionDef.skip(1000);
			cout << "\n\n";
			if(earlyexplanation==true) d = "5";
			else if(relwvoid==1) d = "1";
			else if(relwvoid==2) d = "2";
			else if(relwvoid==3) d = "3";
			else if(relwvoid==4) d = "4"; 
			else if(relwvoid==5) d = "5";
			if(d=="1"){
				FunctionDef.MCS("What the hell happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Seems like more people couldn't take your mere existence.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " A clash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " from the looks of it.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) Shut up already.", 50); cout << "\n"; FunctionDef.truenarrator("2) I'm sorry about before.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,2);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Oh, why don't you shut up already and tell me what is going on and who you are now?", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Why don't you shut up,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " huh?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Can we not get a moment of peace here between us,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " huh?", 100); FunctionDef.skip(400); cout <<"\n"; FunctionDef.narrator("I want to tell you shit,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " but you are being a complete,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " utter,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " asshole.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You want to know shit?", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("Then you better give me one hell of an apology for this behavior.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am not willing to be stuck in the body of a bastard who can't trust me.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("I,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I'm sorry.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I want to be nice,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " but you,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you're not letting me.", 80); FunctionDef.skip(1000);
					cout << "\n\n"; FunctionDef.truenarrator("1) No. Get the hell out of my mind.", 50); cout << "\n"; FunctionDef.truenarrator("2) ...", 50); cout << "\n"; FunctionDef.truenarrator("3) I'm sorry. I am really sorry about before.", 80); cout << "\n";
					cout << "\033[33m>>    ";
					diadec2 = FunctionDef.GVI(1,3);
					cout << "\033[0m" << "\n";
					if(diadec2=="1"){
						FunctionDef.MCSC(mc, "No.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Get the hell out of my mind.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You want me,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " me to get out of your mind?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You realize who I am?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We're not gonna get along,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " are we?", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("You're gonna get us killed.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " go to hell.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " If you won't listen to me,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("I will make the little time you have hellish.", 80); FunctionDef.skip(1000); 
					}
					if(diadec2=="2"){
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator(" You're not gonna say anything?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "Fine.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I'm not saying anything either.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Are we gonna stay here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " do nothing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, "say nothing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " forever?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "We're gonna die here.", 80); FunctionDef.skip(1000);
						cout << "\n\n"; FunctionDef.truenarrator("1) ...", 50); cout << "\n"; FunctionDef.truenarrator("2) You are right. We need to get out of here.", 50); cout << "\n";
						cout << "\033[33m>>    ";
						diadec3 = FunctionDef.GVI(1,2);
						cout << "\033[0m" << "\n";
						if(diadec3=="1"){
							FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
							FunctionDef.truenarrator("You don't say anything and you stay there until midnight.", 50); FunctionDef.skip(200); FunctionDef.TNC(" The unnamed inhabitant of your mind remains quiet as well.", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("After a while, you fall asleep on the field.", 50); FunctionDef.skip(200); FunctionDef.TNC("You never wake up... Reason of death: Unavailable.", 50); FunctionDef.skip(1000);
							cout << "\n"; 
							FunctionDef.truenarrator("ENDING: Asleep on the field.", 50); Sleep(2000);
							lives--;
							deathsequence();
						}
						else{
							FunctionDef.MCSC(mc, "You are right.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We need to get out of here.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("Then go,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " get the hell out of here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " asshole.", 80); FunctionDef.skip(1000);
						}
					}
					else{
						FunctionDef.MCSC(mc, "I'm sorry.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I am really sorry about before.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I didn't want to be an asshole but at first I was so confused and scared,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I didn't trust you,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator(" but I suppose that doesn't excuse the behavior.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I am really sorry,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I want to survive and you are right,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " it's better if we get along.", 80); FunctionDef.skip(1000);
						cout << "\n"; 
						FunctionDef.narrator("Thank you for the heartfelt apology.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am glad that we can finally get along a little.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I'll tell you what I know now.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was the general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " my army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We were confronted by an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " In that battle,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I got hit by an arrow and...", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("died,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I suppose.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I saw a bright flash of light after the arrow hit me and then it was followed by darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("I woke up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I do not recall anything else.", 80); FunctionDef.skip(1000);
						cout << "\n\n"; FunctionDef.truenarrator("1) We should get out of here first and then have a talk about it.", 50); cout << "\n"; FunctionDef.truenarrator("2) Wow, I am so sorry that happened to you.", 50); cout << "\n";
						cout << "\033[33m>>    ";
						diadec3 = FunctionDef.GVI(1,2);
						cout << "\033[0m" << "\n";
						if(diadec3=="1"){
							FunctionDef.MCSC(mc, " I think we should get out of here first and then talk about it.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " It seems dangerous here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " we can figure it out,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " together,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("when we get to safety,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " okay?", 100); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You are right.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's go.", 80); FunctionDef.skip(1000);
						}
						else{
							FunctionDef.MCSC(mc, "Wow,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I am so sorry that happened to you.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("It's okay.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Thank you for finally coming to your senses and apologizing.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " It's better now that we get along.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We should continue moving and get into safety and then try to figure things out.", 80); FunctionDef.skip(1000);
						}
						relwvoid = 3;
					}
				}
				else{
					FunctionDef.MCSC(mc, "Okay.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I'm sorry about before.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("I didn't mean to act like that,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I'm sorry.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I'm sorry I didn't trust you.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Can you please at least tell me who you are now?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("It's... okay.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I understand.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Yes,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I will tell you now,", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " thank you for the apology.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am the general,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("well,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I was the general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " my army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We were confronted by an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " In that battle,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I got hit by an arrow and...", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("died,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I suppose.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I saw a bright flash of light after the arrow hit me and then it was followed by darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " And then,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("I woke up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(1000);
					relwvoid = 3;
					cout << "\n\n"; FunctionDef.truenarrator("1) Okay, I see. We should keep moving and talk about this later.", 50); cout << "\n"; FunctionDef.truenarrator("2) Is that everything?", 50); cout << "\n"; FunctionDef.truenarrator("3) I am sorry about that. About you dying and about what happened.", 50); cout << "\n";
					cout << "\033[33m>>    ";
					diadec2 = FunctionDef.GVI(1,3);
					cout << "\033[0m" << "\n";
					if(diadec2=="1"){
						FunctionDef.MCSC(mc, " Okay,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I see.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Interesting and sad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " but I think we should keep on moving and talk about all this later,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narratorclean(mc, " once we're safer.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You are right,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we have to keep moving and then we can try and figure it out,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " once we are safe.", 80); FunctionDef.skip(1000);
					}
					else if(diadec2=="2"){
						FunctionDef.MCSC(mc, "Is that everything?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " that is everything I know,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I'm afraid.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "We should keep moving until we find a safe spot,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " a village or a settlement perhaps.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We will have to figure the rest out there.", 80); FunctionDef.skip(1000);
					}
					else{
						FunctionDef.MCSC(mc, "I am sorry about that.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " About you dying and about what happened.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("It's okay.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We need to keep moving if we want to survive.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We need to find a village or a settlement or something safe,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("we can talk more there,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and figure things out.", 80); FunctionDef.skip(1000);
					}
				}
			}	
			else if(d=="2"){
				FunctionDef.MCS("What in the name of everything holy happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("It appears to have been a minor clash.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " It does remind me a little of the field where they got me.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) Got you? Will you tell me what is happening already?", 50); cout << "\n"; FunctionDef.truenarrator("2) I'm sorry I didn't trust you before.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,2);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Got you?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Will you tell me what is happening already?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Fine.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " The general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " my army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We were confronted by an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " That's where I got hit by an arrow. ", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that happened,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator(" I saw a bright flash followed by darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Then I somehow wound up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(1000);
					cout << "\n\n"; FunctionDef.truenarrator("1) I see, we should keep moving though and talk later.", 50); cout << "\n"; FunctionDef.truenarrator("2) Is that everything you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) I am sorry, really sorry about how I was before.", 50); cout << "\n";
					cout << "\033[33m>>    ";
					diadec2 = FunctionDef.GVI(1,3);
					cout << "\033[0m" << "\n";
					if(diadec2=="1"){
						FunctionDef.MCSC(mc, "I see,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we should keep moving though and talk about this later,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we don't really have much time, ", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("we don't want to meet the people who did this,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " do we?", 80); FunctionDef.skip(1000);
						cout << "\n"; 
						FunctionDef.narrator("Yes,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we should keep on moving.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We will figure the rest out later.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " And can we please get along and not be", 80); cout << "\n"; FunctionDef.narrator("asses to each other?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I understand your situation,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and why you didn't trust me before,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("but we have to get along if we want to work together.", 80); FunctionDef.skip(1000);  
					}
					else if(diadec2=="2"){
						FunctionDef.MCSC(mc, "Is that everything you know?", 80); FunctionDef.skip(400); 
						cout << "\n";
						FunctionDef.narrator("It seems like it.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should get out of here and figure the rest out once we are someplace safer.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " And when we get along more.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("You know,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you were kind of an asshole,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, "  but I understand.", 80); FunctionDef.skip(1000);
					}
					else{
						FunctionDef.MCSC(mc, "I am sorry,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " really sorry about how I was before and about what happened to you.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I was trying to be careful.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("Thank you for telling me this.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Thank you,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " for the apology", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I understand,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " it's okay", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should probably move quick though,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("and find find a shelter or somewhere to hole up and then we can talk in peace.", 80); FunctionDef.skip(1000);
					}
				}
				else{
					FunctionDef.MCSC("I'm sorry I didn't trust you before.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I was being careful.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, "Also,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " what did you mean by \"got you?\"", 80); FunctionDef.skip(1000);
				}
			}
			else if(d=="3"){
				FunctionDef.MCS("What the glyph happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("It seems like there was a minor clash here.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Can't be too long since it happened.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("It reminds me of the battle field where they got me.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Got you?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Will you tell me what happened already?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Very well, then.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " The name's Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was a general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We found ourselves in a confrontation with an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We were fighting,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("and then I got hit by an arrow.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " It was followed by a bright flash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all I saw was darkness.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("And,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I guess then I just woke up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "That's all I know.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) That's sad. We should probably move though and talk about it later.", 50); cout << "\n"; FunctionDef.truenarrator("2) That's all you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) Wow, I'm sorry that happened to you.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Okay,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " that's...", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " sad.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We should probably move now though,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " and perhaps talk about it later", 80); cout << "\n"; FunctionDef.narrator("when we are holed up somewhere safe,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " okay?", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Yes,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you are right.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should continue moving until we get to safety.", 80); FunctionDef.skip(1000);
				}
				else if(diadec1=="2"){
					FunctionDef.MCSC(mc, "Is that everything?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I'm afraid it is.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I don't know anything else,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all this is new to me as well.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should probably keep moving if we want to survive", 80); cout << "\n"; FunctionDef.narrator("this stupid day.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's try finding a shelter or a settlement before the sun sets.", 80); FunctionDef.skip(1000);
				}
				else{
					FunctionDef.MCSC(mc, "Oh, wow,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I am really sorry about that.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Yeah,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " dying sucks,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " but it's not your fault.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's make sure the same thing doesn't happen to you too,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " okay?", 100); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We have to get out of here as soon as possible if we wish to accomplish that.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's move,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we can talk more when we get to safety.", 80); FunctionDef.skip(1000);
					relwvoid = 4;
				}
			}
			else if(d=="4"){
				FunctionDef.MCS("What happened here?", 100); FunctionDef.skip(750);
				cout << "\n";
				FunctionDef.narrator("A minor clash, it seems.", 80); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.narrator("It reminds me of the field where they got me.", 75); FunctionDef.skip(750);
				cout << "\n";
				FunctionDef.MCS("Woah,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " that's crazy.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Wait,", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " got you?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " What do you meanb by that?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " When will you finally tell me who you are?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Okay then.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was a general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We found ourselves in a confrontation with an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We were figthing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then I got hit by an arrow.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("It was followed by a bright flash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all I saw was darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I woke up in your body.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("That's all I know.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) What?? So you really are dead.", 50); cout << "\n"; FunctionDef.truenarrator("2) That's all you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) Wow, I'm sorry that happened to you.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "What??", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " So you really are dead.", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Positive,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I really am dead.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Well,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I think we should not waste more time looking at charred bodies and perhaps move,", 80); FunctionDef.skip(250); cout <<"\n"; FunctionDef.narrator("unless you want whoever did this to return and find us.", 80); FunctionDef.skip(1000); 
				}
				else if(diadec1=="2"){
					FunctionDef.MCSC(mc, "That's all you know?", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("I'm afraid so.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should probably keep moving unless we want to wait for those who did this.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I don't think they would be very welcoming.", 80); FunctionDef.skip(1000); 
				}
				else{
					FunctionDef.MCSC(mc, "Wow,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I'm sorry that happened to you.", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Yeah,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " well,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " dying sucks.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's make sure that doesn't happen to you too,", 80); FunctionDef.skip(250); cout <<"\n"; FunctionDef.narrator("okay?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We have to get out of here as soon as possible if we want to accomplish that.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's move,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("we can talk when we get to safety.", 80); FunctionDef.skip(1000);
				}
			}
			else if(d=="5"){
				FunctionDef.MCS("Woah,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " what the hell happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("From the looks of it,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I'd guess an unfriendly clash.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " This reminds me of the field where they got me,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("with the arrow I mentioned earlier.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("I see,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " it's unfortune what happened.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I think we should just keep on moving until we get to safety.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we should.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We need to find a settlement.", 80); FunctionDef.skip(1000);
			}
		}
		else{
			// sem to iste xd
		}
	}
};
int main() {
    setlocale(LC_ALL, "");
	Functions FunctionsDef;
	Game GameDef;
	srand(time(0));

	GameDef.ExistujeSave = GameDef.CheckSave();
	if (GameDef.ExistujeSave) {
		GameDef.load();
		if(GameDef.playerName!=""&&(GameDef.mode!="speedrun"&&GameDef.mode!=""))	GameDef.savesequence(lang);
		else GameDef.introsequence(GameDef.lang);
	}
	else {
		GameDef.save();
		GameDef.picklanguage();
	}

	return 0;
}