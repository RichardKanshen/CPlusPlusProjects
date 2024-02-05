#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;
class Game{
public:
	string playerName, fightstatus, input, tb, decision1, decision1sub1, decision2="";
	string diadec1, diadec2, diadec3, diadec4, diadec5;
	int a=0, b=0, sequence, level, xp, requiredxp, xpgained, initiallvl, hp, currenthp, maxdmg, plvlbonusdmg;
	bool isAlive = true;
  void save() {
    ofstream file("savegame.txt");
    file << sequence << "\n";
    file << playerName << "\n";
    file << level << "\n";
    file << xp << "\n";
    file << hp << "\n"; 
    file << currenthp << "\n";
    file << maxdmg << "\n";
    file.close();
  }

  void load() {
    ifstream file("savegame.txt");
    file >> sequence;
    file >> playerName;
    file >> level;
    file >> xp;
    file >> hp;
    file >> currenthp;
    file >> maxdmg;
    requiredxp=10*pow(1.2, level);
  }
  bool CheckSave(){
  	ifstream file("savegame.txt");
  	return file.good();
	}
	void checkLevelUp(){
		if(xp>=requiredxp){
			initiallvl = level;
			hp = currenthp;
			while(xp>=requiredxp){
				hp += hp/10;
				level += 1;
				xp -= requiredxp;
				requiredxp += requiredxp/5;
			} 
		cout << "\n      Leveled up! Went from lvl " << initiallvl << " to lvl " << level << ". HP: " << currenthp << " -> " << hp << endl;
		cout << "      Current xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << endl;
		}
		save();
	}
	void clearLine(){
		cout<<"\r                                              \r";
	}
void narrator(const string& text, int tickspeed) {
  bool a = false;
  tb="<<    ";
  tb+=text;
  for (char c : text) {
    if (!a) {
      cout << "\033[36m" << "<<    "; 
      a = true;
    }
    if(_kbhit()){
      char key = _getch();
      if(key=='\r' or key==' '){
        clearLine(); 
        cout << "\033[36m" << "<<    " << text;
        break;
      }
    }
    cout << c;
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m";
}
void MCS(const string& text, int tickspeed){
  bool a = false;
  tb=">>    ";
  tb+=text;
  for (char c : text) {
    if (!a) {
      cout << "\033[33m" << ">>    ";  
      a = true;
    }
    if(_kbhit()){
      char key = _getch();
      if(key=='\r' or key==' '){
        clearLine();
        cout << "\033[33m" << ">>    " << text;
        break;  
      }
    }
    cout << c;
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m"; 
}
void narratorclean(string currentColor, const string& text, int tickspeed) {
  bool a = false;
  tb += text;
  for(char c : text) {
    if(currentColor != "") {
      cout << currentColor; 
    }
    cout << c;  
    if(_kbhit()) {
      char key = _getch();
      if(key=='\r' or key==' ') {
        clearLine();
        if(currentColor != "") {
          cout << currentColor;
        }
        cout << tb;
        break;
      }
    }
    
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m"; 
}
	void truenarrator(const string& text, int tickspeed) {
		tb="      ";
		tb+=text; cout << "      ";
	  bool a = false;
	  for (char c : text) {
	      cout << c;
		      if(_kbhit()){
		      	char key = _getch();
		      	if(key=='\r' or key==' '){
		      		clearLine();
		      		cout << tb;
		      		break;
						}
					}
	      this_thread::sleep_for(chrono::milliseconds(tickspeed));
	  }
	}
	void TNC(const string& text, int tickspeed){
		bool a = false;
	  tb+=text;
	  for (char c : text) {
	      cout << c;
		      if(_kbhit()){
		      	char key = _getch();
		      	if(key=='\r' or key==' '){
		      		clearLine();
		      		cout << tb;
		      		break;
						}
					}
	      this_thread::sleep_for(chrono::milliseconds(tickspeed));
	  }
	}
	void skip(int time){
		for(time; time>0; time-=50){
		  if(_kbhit()){
		  	char key = _getch();
		  	if(key=='\r' or key==' '){
		  		break;
				}
			}
			Sleep(50);
		}
	}
	void getInput() {
		cout << ">>    ";
		getline(cin, input);
		skip(1000);
	}
	string GVI(int min, int max) {
		string dinput;
	  while (true) {
      char input = _getch();  
      if (input >= min+'0' && input <= max+'0') {
          dinput = string(1, input);  
          cout << dinput;  
          break;
      }
    }
    return dinput;
	}
	void flushInput() {
			while(_kbhit()) {
		    _getch(); 
		    Sleep(50);
	  }
	}
	int ambush(string attacker, int enemyhp, int enemydmg, int enemyskill, int enemyrage){
		ofstream file("savegame.txt");
    file << sequence << "\n";
    file << playerName << "\n";
    file << level << "\n";
    file << xp << "\n";
    file << hp << "\n"; 
    file << currenthp << "\n";
    file << maxdmg << "\n";
    file << enemyhp << "\n";
    file << enemydmg << "\n";
    file << enemyskill << "\n";
    file << enemyrage << "\n";
    file << attacker << "\n";
    file.close();
	  Sleep(2000);
	  cout << endl << "      "; truenarrator("Prepare to fight...", 50); Sleep(500);
	  const char *programName = "combatmoreeffective.exe";
	  STARTUPINFO si;
	  PROCESS_INFORMATION pi;
	  ZeroMemory(&si, sizeof(si));
	  si.cb = sizeof(si);
	  ZeroMemory(&pi, sizeof(pi));
	  if (CreateProcess(NULL, const_cast<char*>(programName), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
	      WaitForSingleObject(pi.hProcess, INFINITE); 
	  } else {
	      cout << "Error launching program" << endl;
	  }
	  ifstream inputFile("testsave.txt");
	  if (!inputFile.is_open()) {
	    cerr << "Error opening file for reading!" << endl;
	    return 1;
	  }
	  inputFile >> fightstatus;
	  inputFile >> xpgained;
	  if(fightstatus=="1"){
	  	truenarrator("You aborted the fight... You automatically die.", 50); cout << endl; skip(250); truenarrator("[Press F to load the latest save/L to start over]",50);
			while(true){
      	if(_kbhit()){
      		char c = _getch();
      		if(c=='f') sequence1();
					else if(c=='f') introsequence();
				}
			}
		}
		else{
      truenarrator("You finished the fight.", 50); cout << endl;
    }
		Sleep(3000);
		xp+=xpgained;
		checkLevelUp();
		Sleep(2000);
	}
	void d1n(){
		if(a==0) truenarrator("Trees, interesting choice. You come closer to the trees but you don't find anything.", 50);
		if(a==1) truenarrator("For real? You visit the trees again, and... you don't find anything.", 50);
		if(a==2) truenarrator("There is something weird about those trees. They're... trees.", 50);
		if(a>2){
			truenarrator("You visit the trees once more. Once again, you find nothin-", 50); cout << endl;
			truenarrator("w- what's that sound? It seems like... you have awakened something. It's angry.", 75); cout << endl; skip(300);
			truenarrator("Behold Mozz, the tree [BOSS] [10M HP] You stand no chance against this beast as it one hits you", 50); cout << endl;
			truenarrator("before the fight even has a chance to begin.", 50); skip(400); cout << endl; skip(400); system("cls"); cout << "\n\n\n\n";
			truenarrator("\033[1;31mYou get the tree picker ending.\033[0m", 50); cout << endl; skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
			cout << "      [Press F to load the latest save]"; isAlive = false;
			while(true){
				if(_kbhit()){
			  	char key = _getch();
			  	if(key=='f'){
			  		break;
					}
				}
			}
			
		}
	}
	
	// Decisions
	
	void d1(){
		truenarrator("You look around you. You see the following:", 50);
		cout << endl;
		truenarrator("1) Trees",50); cout << endl; truenarrator("2) Trees", 50); cout << endl; truenarrator("3) Trees", 50); cout << endl; truenarrator("4) A path", 50); cout << endl; truenarrator("5) A strange place between the trees, where abandoned stuff can be seen.", 50); skip(500); cout << endl << endl; truenarrator("What do you choose?", 50);
	}
	
	// Sequences
	void savesequence(){
		load();
		truenarrator("Welcome back, "+playerName, 50); skip(250); cout << endl;
		truenarrator("Do you wish to load the latest save or start a new game? [F to Load, L to start over]", 50);
		while(true){
			if(_kbhit()){
				char keypressed = _getch();
				if(keypressed=='f'){
					if(sequence==1) sequence1();
					else if(sequence==2) sequence2();
				} 
				else if(keypressed=='l'){
					introsequence(); sequence1();
				} 
			}
		}
	}
	void introsequence(){
		system("cls");
		level = 0; hp = 20; xp = 0; currenthp = 20; maxdmg = 1;
		cout << "                                          W E L C O M E    T O" << endl;
	 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
		cout << endl << "                                           The C++ Console RPG";
		cout << endl << "                                         Press [ANY KEY] to Begin";
		_getch();
		cout << endl; truenarrator("Hello Player", 100); skip(1000); cout << endl;
		truenarrator("...", 500); skip(1000); cout << endl;
		truenarrator("Your name isn't Player, is it?", 80); skip(1500); cout << endl;
		truenarrator("What's your name?", 80); skip(1000); cout << endl << "      [ENTER YOUR NAME NOW]" << endl;
		flushInput();
		getInput(); playerName = input; save();
		if (!playerName.empty()) {
			truenarrator("Nice to meet you, "+playerName+"!", 100);
		} else {
			truenarrator("You...", 500); TNC(" don't have a name?", 125); skip(500); TNC(" I will give you one more chance to give me your name.", 80); cout << endl; 
			flushInput();
			getInput(); playerName = input; save();
			if (!playerName.empty()) {
			truenarrator("At last, nice to meet you, "+playerName+"!", 80);
		} else {
			truenarrator("You sure?", 125); cout << endl; skip(1000);
			truenarrator("That's", 225); TNC("...", 500); skip(500); TNC(" sad.", 200); cout << endl; skip(750);
			truenarrator("I still need something to call you by, though", 80); cout << endl; skip(500);
			truenarrator("Will Player suffice?", 75); skip(500); TNC(" I think it will be alright.", 75); playerName = "Player"; save();
		}
	} 
		skip(1000);
		cout << endl << "      [PRESS ANY KEY TO START THE GAME]";
		while(true){
			if(_kbhit()){
				system("cls");
				break;
			}
		}
		sequence=0;
		sequence1();
	}
	void sequence1(){
		system("cls");
		if(sequence==0) sequence++;
		save();
		Sleep(500);
		cout << "\n\n\n\n\n\n\t\t{[()]} Sequence 1 {[()]}\n\n\n"; Sleep(500);
		truenarrator("\t\tThe game saves every sequence. Good luck on your journey.", 50);
		Sleep(2000); system("cls");
		Sleep(2500);
		MCS("Where am I?", 80); narratorclean("\033[33m"," How did I get here?",80); skip(1000);
		cout << endl;
		MCS("There is a thick forest all around me.", 80); skip(1000);
		cout << endl;
		MCS("I, ", 100); narratorclean("\033[33m","...", 200); skip(500); narratorclean("\033[33m"," can't remember anything.", 80); skip(1500);
		cout << endl;
		narrator("What's happening! ", 80); skip(600); narratorclean("\033[36m","Why can't I control my body? ", 100); skip(500); narratorclean("\033[36m","This... ", 175); skip(300); narratorclean("\033[36m","This is not my body!", 80);
		cout << endl;
		MCS("Who said that? ", 40); skip(750);
		cout << endl;
		MCS("Where are you? Show yourself!", 75); skip(1000);
		cout << endl;
		narrator("I can't show myself.", 80); skip(1000);
		cout << endl;
		MCS("What do you mean?", 80); skip(1000);
		cout << endl;
		narrator("I myself have no idea.", 80); skip(500); narratorclean("\033[36m"," It seems like...", 120); skip(400); narratorclean("\033[36m"," I am in you.", 100); skip(750);
		cout << endl;
		MCS("Why are you in me?", 80); skip(1000);
		cout << endl;
		narrator("Good question.", 80); skip(500); narratorclean("\033[36m"," All I can remember is my death,", 80); skip(250); narratorclean("\033[36m"," and now,", 125); narratorclean("\033[36m"," I find myself here,", 100); skip(500); narratorclean("\033[36m"," in your body.", 100); skip(1000);
		cout << endl;
		MCS("What do you mean your death?", 80); skip(1500);
		cout << endl;
		narrator("This has to be a nightmare.", 80); skip(1000);
		cout << endl;
		narrator("Well,", 125); skip(400); narratorclean("\033[36m"," we don't really have a choice,",80); skip(300); narratorclean("\033[36m"," stand up and look around.", 80 ); skip(250);
		cout << endl;
		narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
		cout << endl;
		narrator("and why you don't remember anything.", 80); skip(400); narratorclean("\033[36m"," Stand up before someone,", 100);skip(200); narratorclean("\033[36m"," or worse,", 125); skip(200); narratorclean("\033[36m"," something finds us.", 100); skip(1000);
		cout << endl;
		MCS("Why should I listen to you?", 80); skip(1000);
		cout << endl;
		narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
		cout << endl;
		cout << endl;
		d1();
		while(true){
			if(a>0 || b>0) d1();
			cout << endl << endl;
			flushInput();
			cout << "\033[33m>>    ";
			decision1 = GVI(1,5);
			cout << "\033[0m";
    	cout << endl << endl;
			if(decision1=="1"){
				MCS("I want to see the trees.", 80);
				cout << endl << endl;
				d1n();
				if(!isAlive){
					system("cls");
					sequence1();
					break;
				}
				skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="2"){
				MCS("I want to see those trees.", 80);
				cout << endl << endl;
				d1n();
				if(!isAlive){
					system("cls");
					sequence1();
					break;
				}
				skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="3"){
				MCS("I must see these trees.", 80);
				cout << endl << endl;
				d1n();
				if(!isAlive){
					system("cls");
					sequence1();
					break;
				}
				skip(500);
				cout << endl << endl;
				a++;
				continue;		
			}
			else if(decision1=="4"){
				MCS("I would like to see where this path leads.", 80);
				cout << endl << endl;
				truenarrator("Okay, you decide you want to see the destination of this path. Are you sure you don't want to check\n      the abandoned place where your stuff might lay out first?", 50);
				cout << endl << endl;
				skip(250);
				truenarrator("1) Go through with your initial decision\n      2) Abort", 50);
				cout << endl << endl;
				flushInput();
				cout << "\033[33m>>    ";
				decision1sub1 = GVI(1,2);
				cout << "\033[0m" << endl << endl;
				if(decision1sub1=="1"){
					MCS("I really want to know where it leads.", 80);
					cout << endl << endl;
					truenarrator("Very well, you decide to embark on an adventurous journe- nevermind, you die. Reason: UNKN0WN", 50);
					skip(400);
					cout << endl << endl << endl;
					truenarrator("\n      [Press F to pay respects(load the last save)]", 50);
					while(true){
						if(_kbhit()){
					  	char key = _getch();
					  	if(key=='f'){
					  		break;
							}
						}
					}
					system("CLS");
					sequence1();
					break;
				}
				else if(decision1sub1=="2"){
					MCS("I think we should check that strange abandoned place first.", 80);
					cout << endl << endl;
					truenarrator("At last, you decide to check the strange place with abandoned stuff out. You see the following:",50); cout << "\n\n"; truenarrator("- Tea",50); cout << "\n"; truenarrator("- An iron sword",50); cout << "\n"; truenarrator("- Golden armor with a low durability",50); cout << "\n"; truenarrator("- A shield",50); cout << "\n"; truenarrator("- Elixir of Love",50); cout << "\n"; truenarrator("- A stick",50); cout << "\n"; truenarrator("- Bandage x3",50); cout << "\n"; truenarrator("- A small backpack", 50);
					break;
				}
			}
			else if(decision1=="5"){
				MCS("I would like to check the strange abandoned place out first.", 80);
				cout << endl << endl;
					truenarrator("Great choice, better than \"trees\" atleast, you near the abandoned things and find the following:",50); cout << "\n\n"; truenarrator("- Tea",50); cout << "\n"; truenarrator("- An iron sword",50); cout << "\n"; truenarrator("- Golden armor with a low durability",50); cout << "\n"; truenarrator("- A shield",50); cout << "\n"; truenarrator("- Elixir of Love",50); cout << "\n"; truenarrator("- A stick",50); cout << "\n"; truenarrator("- Bandage x3",50); cout << "\n"; truenarrator("- A small backpack", 50); break;
			}
		}
		cout << endl << endl;
		narrator("Great.", 100); skip(250); narratorclean("\033[36m"," These things will come in handy. Grab them and let's get out of here.", 80); skip(1000);
		cout << endl << endl;
		truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); skip(500);
		cout << endl << endl;
		MCS("Good idea, let's follow that path we saw earlier, it looks like it leads to a meadow.", 80); skip(1000);
		cout << endl << endl;
		truenarrator("You are approached by a pack of wolves ready to attack you. You have to defend yourself.", 50); cout << endl; truenarrator("In a quick manner, you have to choose the action you take: ", 50); cout << endl << endl; truenarrator("1) Use a stick to fight them",50); skip(200); cout << endl; truenarrator("2) Use an iron sword to fight them", 50); cout << endl; truenarrator("3) Try to distract them with the stick instead of fighting.", 50); cout << endl << endl;
		cout << "\033[33m>>    ";
		decision2 = GVI(1,3);
		cout << "\033[0m" << endl;
		if(decision2=="1"){
			truenarrator("You decide to take out the stick and use it to fight the wolves off. Commencing combat.", 50); skip(200);
			ambush("Wolves", 20, 3, 1, 1); 
		}
		else if(decision2=="2"){
			truenarrator("You decide to take out the iron sword and use it to fight the wolves off. Commencing combat.", 50); skip(200);
			ambush("Wolves", 20, 3, 1, 1); 
		}
		else if(decision2=="3"){
			int wolfescapechance = rand()%4;
			if(wolfescapechance==1){
				truenarrator("You attempt to distract the wolves using a stick. You throw it and the wolves indeed do get distracted.", 50); // Achievement, 25% chance to work 
			}
			else{
				truenarrator("You try to distract the wolves with the stick, but they fail to notice it and devour you.", 50); skip(400); cout << endl;
				truenarrator("[Press F to pay respects(load last save)]",50);
				while(true){
					if(_kbhit()){
				  	char key = _getch();
				  	if(key=='f'){
				  		break;
						}
					}
				}
				sequence1();
			}
		}
				sequence1();
		}
		if(decision2=="3"){
			cout << endl << endl; narrator("That was really weird,", 80); narratorclean("\033[36m"," I never would have thought of that.", 80); narratorclean("\033[36m"," Great job.", 100); skip(1000);
			cout << endl;
			MCS("I too am surprised that worked.", 80); narratorclean("\033[33m"," Let's maybe get out of here.", 80); skip(1000);
		}
		else{
			narrator("Good job fighting those wolves off.", 80); skip(250); narratorclean("\033[36m"," We should probably get out of here.", 80); skip(400);
			cout << endl;
			MCS("Thank you, yes, we should get out of here.", 80); skip(1000); cout << endl;			
		}
		sequence2();
	}
	void sequence2(){
		if(sequence==1) sequence++; save(); system("cls"); Sleep(1000);
		cout << "\n\n\n\n\n\n        {[()]} Sequence 2 {[()]}\n\n\n"; Sleep(1000); truenarrator("  You're doing great!(not)", 50); Sleep(2000); system("cls"); Sleep(2500);
		cout << endl;
		truenarrator("You walk through a captivating meadow, full of birds, dead bodies and charred weapons.", 50); skip(1000);
		cout << endl << endl;
		MCS("What happened here?", 100); skip(750);
		cout << endl;
		narrator("A minor clash, it seems.", 80); skip(250);
		cout << endl;
		narrator("It reminds me of the field where they got me.", 75); skip(750);
		cout << endl;
		MCS("Got you?", 75); narratorclean("\033[33m"," When will you finally tell me what you meant by your death?", 80); skip(1000); 
		cout << endl;
		narrator("Very well.", 75); narratorclean("\033[36m"," My faction got into a fight with another faction. I was the general, leading an army.", 75); cout << endl;
		narrator("While I was fighting, an arrow hit me. Instead of dying, I saw a bright flash followed by darkness.", 75); cout << endl;
		narrator("I then woke up in a different body,", 75); skip(250); narratorclean("\033[36m"," your body.", 80); skip(400); narratorclean("\033[36m"," And now, we're here.", 75); skip(500);
		cout << endl;
		MCS("I don't remember what happened before we", 80); skip(200); narratorclean("\033[33m","...", 250); skip(250); narratorclean("\033[33m","merged.", 75); skip(1000); 
		cout << endl << endl;
	}
};
int main(){
	Game GameDef;
	srand(time(0));
	if(GameDef.CheckSave()) GameDef.savesequence();
	else GameDef.introsequence();
	return 0;
}
