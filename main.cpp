#include <iostream>
#include <stdlib.h>
#include <string>
#include "Classes.h"
#include <chrono>
#include <thread>
#include "mingw.thread.h"
#include <windows.h>
#include <time.h>

using namespace std;
using namespace chrono_literals;

int main() {
	srand(time(NULL));
	Avatar player;
	Competitors* c;
	vector<Werewolf> Werewolves;
	vector<Vampire> Vampires;
	string username_input;
	int team_input;
	int diameter;   //diameter of the board
	int entnumber = 0;	//entity number for werewolves and vampires
	int daynightcount = 0;	//counter for day or night 
	bool exit = 0;	//when the game is finished exit value is 1 and the program get terminated
	bool entityslot;	//checks if there is a vampire or werewolf in a slot so that you don't place another one in the same slot

	//			GET BASIC INFORMATION FROM THE USER
	system("ClS");
	cout << "Type your username\n";
	cin >> username_input;

	cout << "Select your team\n";
	cout << "Press 1 if you want to team up with the vampires\n";
	cout << "Press 2 if you want to team up with the werewolves\n";
	cout << "You can select only one time and can't change until the game is over\n";
	cin >> team_input;

	while (team_input != 1 && team_input != 2) {
		cout << "You didn't select any team, please try again\n";
			cin >> team_input;
		if (team_input != 1 && team_input != 2) {
			continue;
		}
		else break;
	}

	player.set_username(username_input);
	player.set_team(team_input);
	cout << "Welcome " << player.get_username() << "!\n";
	cout << "You have selected the ";
	if (team_input == 1) {
		cout << "VAMPIRES!\n";
	}
	if (team_input == 2) {
		cout << "WEREWOLVES!\n";
	}
	cout << "Good Luck!\n\n";

	do {
		cout << "Enter map diameter: (Must be from 10 to 40): ";
		cin >> diameter;
		if (diameter < 10 || diameter > 40) {
			cout << "Diameter entered not in range specified!\nTry again!\n";
		}
	} while (diameter < 10 || diameter > 40);

	if(diameter >= 10 && diameter < 20) {
		entnumber = 3;
	}
	if (diameter >= 20 && diameter < 30) {
		entnumber = 5;
	}
	if (diameter >= 30 && diameter <= 40) {
		entnumber = 7;
	}

	cout << "Generating map...\n";

	this_thread::sleep_for(3s);

	system("CLS");

	//					CREATE AND PRINT MAP

	int* board = new int[diameter * diameter];

	if (board == NULL)
	{
		system("CLS");
		cout << "\n\nThere was a memory problem, please try again!";
		return -1;
	}

	Map nmap(diameter);

	nmap.createboard(diameter, board);

	do {
		player.set_x(rand() % (diameter - 4) + 1);
		player.set_y(rand() % (diameter - 4) + 1);
		int i = player.get_x();
		int j = player.get_y();
		if (*(board + i * diameter + j) == 3)
			entityslot = 1;
		else
			entityslot = 0;
	} while (entityslot);

	nmap.changeboard(diameter, board, player, Werewolves, Vampires);

	for (int a = 0; a <= entnumber; a++) {
		Werewolves.push_back(Werewolf());
		do {
			entityslot = 1;
			Werewolves[a].set_x(rand() % (diameter - 4) + 1);
			Werewolves[a].set_y(rand() % (diameter - 4) + 1);
			int i = Werewolves[a].get_x();
			int j = Werewolves[a].get_y();
			if (*(board + i * diameter + j) == 6 || *(board + i * diameter + j) == 4 || *(board + i * diameter + j) == 3 || *(board + i * diameter + j) == 5)
				entityslot = 1;
			else
				entityslot = 0;
		} while (entityslot);
	}
	for (int a = 0; a <= entnumber; a++) {
		Vampires.push_back(Vampire());
		do {
			Vampires[a].set_x(rand() % (diameter - 4) + 1);
			Vampires[a].set_y(rand() % (diameter - 4) + 1);
			int i = Vampires[a].get_x();
			int j = Vampires[a].get_y();
			if (*(board + i * diameter + j) == 6 || *(board + i * diameter + j) == 4 || *(board + i * diameter + j) == 3 || *(board + i * diameter + j) == 5)
				entityslot = 1;
			else
				entityslot = 0;
		} while (entityslot);
	}

	nmap.changeboard(diameter, board, player, Werewolves, Vampires);

	nmap.printboard(diameter, board, daynightcount);

	//						WHILE LOOP FOR EVERY ROUND OF THE GAME UNTIL IT'S OVER

	while(exit!= 1){
		this_thread::sleep_for(100ms);
		if (Vampires.size() == 0 && Werewolves.size() == 0) {
			cout << "\n\n\nIt's a draw!";
			delete[] board;
			return 0;
		}
		if (Vampires.size() == 0) {
			cout << "\n\n\nWerewolves won!";
			delete[] board;
			return 0;
		}
		else {
			for (int i = 0; i < Vampires.size(); i++) {
				Competitors* cp;
				cp = &(Vampires[i]);
				int h = cp->get_health();
				if (h == 0) {
					int x = cp->get_x();
					int y = cp->get_y();
					*(board + x * diameter + y) = 0;
					Vampires.erase(Vampires.begin() + i);
					system("ClS");
					nmap.changeboard(diameter, board, player, Werewolves, Vampires);
					nmap.printboard(diameter, board, daynightcount);
				}
			}
		}
		if (Werewolves.size() == 0) {
			cout << "\n\n\nVampires won!";
			delete[] board;
			return 0;
		}
		else {
			for (int i = 0; i < Werewolves.size(); i++) {
				Competitors* cp;
				cp = &(Werewolves[i]);
				int h = cp->get_health();
				if (h == 0) {
					int x = cp->get_x();
					int y = cp->get_y();
					*(board + x * diameter + y) = 0;
					Werewolves.erase(Werewolves.begin() + i);
					system("ClS");
					nmap.changeboard(diameter, board, player, Werewolves, Vampires);
					nmap.printboard(diameter, board, daynightcount);
				}
			}
		}
		if (GetKeyState(0x20) & 0x8000)						//if the player presses the 'SPACEBAR' key he uses the magic potion
		{
			if (daynightcount <= 20 && player.get_team() == 1) {
				if (player.get_magic_potion() > 0) {
					player.diminish_magicpot_num();
					for (int i = 0; i < Vampires.size(); i++) {
						Competitors* cp;
						cp = &Vampires[i];
						cp->set_health(5);
					}
					cout << FCYN("\n\n\t\t\t\tUsed a magic potion!");
					this_thread::sleep_for(1200ms);
					system("CLS");
					nmap.printboard(diameter, board, daynightcount);
				}
				else {
					cout << FRED("\n\n\t\t\tYou dont have any magic potions right now!");
					this_thread::sleep_for(1200ms);
					system("CLS");
					nmap.printboard(diameter, board, daynightcount);
				}
			}
			if(daynightcount <= 20 && player.get_team() == 2){
				cout << FYEL("\n\n\t\t\tYou cannot use a magic potion for Werewolves at day!");
				this_thread::sleep_for(1200ms);
				system("CLS");
				nmap.printboard(diameter, board, daynightcount);
			}
			if (daynightcount > 20 && player.get_team() == 2) {
				if (player.get_magic_potion() > 0) {
					player.diminish_magicpot_num();
					for (int i = 0; i < Werewolves.size(); i++) {
						Competitors* cp;
						cp = &Werewolves[i];
						cp->set_health(5);
					}
					cout << FCYN("\n\n\t\t\t\tUsed a magic potion!");
					this_thread::sleep_for(1200ms);
					system("CLS");
					nmap.printboard(diameter, board, daynightcount);
				}
				else {
					cout << FRED("\n\n\t\t\tYou dont have any magic potions right now!");
					this_thread::sleep_for(1200ms);
					system("CLS");
					nmap.printboard(diameter, board, daynightcount);
				}
			}
			if(daynightcount > 20 && player.get_team() == 1){
				cout << FYEL("\n\n\t\t\tYou cannot use a magic potion for Vampires at night!");
				this_thread::sleep_for(1200ms);
				system("CLS");
				nmap.printboard(diameter, board, daynightcount);
			}
		}
		if (GetKeyState(0x41) & 0x8000)						//if the player presses the 'A' key the avatar goes left
		{
			system("CLS");
			daynightcount++;
			nmap.move_left(nmap, player, board);
			for (int a = 0; a <= Vampires.size() - 1; a++) {
				c = &(Vampires[a]);
				c->move((Vampires[a]), board, diameter, Werewolves, Vampires);
			}
				nmap.changeboard(diameter, board, player, Werewolves, Vampires);
			for (int a = 0; a <= Werewolves.size() - 1; a++) {
				c = &(Werewolves[a]);
				c->move((Werewolves[a]), board, diameter, Werewolves, Vampires);
				
			}
			nmap.printboard(diameter, board, daynightcount);
			

		}
		if (GetKeyState(0x44) & 0x8000)					//if the player presses the 'D' key the avatar goes right
		{
			system("CLS");
			nmap.move_right(nmap, player, board);
			daynightcount++;
			for (int a = 0; a <= Vampires.size() - 1; a++) {
				c = &(Vampires[a]);
				c->move((Vampires[a]), board, diameter, Werewolves, Vampires);
			}
			nmap.changeboard(diameter, board, player, Werewolves, Vampires);
			for (int a = 0; a <= Werewolves.size() - 1; a++) {
				c = &(Werewolves[a]);
				c->move((Werewolves[a]), board, diameter, Werewolves, Vampires);

			}
			nmap.printboard(diameter, board, daynightcount);
		}
		if (GetKeyState(0x57) & 0x8000)					//if the player presses the 'W' key the avatar goes up
		{
			system("CLS");
			daynightcount++;
			nmap.move_up(nmap, player, board);
			for (int a = 0; a <= Vampires.size() - 1; a++) {
				c = &(Vampires[a]);
				c->move((Vampires[a]), board, diameter, Werewolves, Vampires);
			}
			nmap.changeboard(diameter, board, player, Werewolves, Vampires);
			for (int a = 0; a <= Werewolves.size() - 1; a++) {
				c = &(Werewolves[a]);
				c->move((Werewolves[a]), board, diameter, Werewolves, Vampires);

			}
			nmap.printboard(diameter, board, daynightcount);
		
		}
		if (GetKeyState(0x50) & 0x8000)			//if the player presses the 'P' key the game pauses		
		{
			system("CLS");
			cout << "\n               GAME PAUSED\n\nYou have " << player.get_magic_potion() << " magic potion(s) left!\nYou are supporting ";
			if (player.get_team() == 1)
				cout << FBLU("Vampires.\n");
			else	
				cout <<FBLU("Werewolves.\n");
			cout << "There are " << Werewolves.size()  << " Werewolves left and " << Vampires.size() << " Vampires left.";
			cout << "\n\n\n";
			system("pause");
			system("CLS");
			nmap.printboard(diameter, board, daynightcount);
		}
		if (GetKeyState(0x53) & 0x8000)					//if the player presses the 'S' key the avatar goes down
		{
			system("CLS");
			daynightcount++;
			nmap.move_down(nmap, player, board);
			for (int a = 0; a <= Vampires.size() - 1; a++) {
				c = &(Vampires[a]);
				c->move((Vampires[a]), board, diameter, Werewolves, Vampires);
			}
			nmap.changeboard(diameter, board, player, Werewolves, Vampires);
			for (int a = 0; a <= Werewolves.size() - 1; a++) {
				c = &(Werewolves[a]);
				c->move((Werewolves[a]), board, diameter, Werewolves, Vampires);

			}
			nmap.printboard(diameter, board, daynightcount);
		}
		if (GetKeyState(0x30) & 0x8000)					//if the player presses the '0' key the game is terminated
		{	
			system("CLS");
			cout << BOLD(FRED("\nTerminated the game, thank you for playing!\n"));	     
			exit = 1;
		}
		if (daynightcount == 40) {				//counter resets after a full cycle of day and night (20 rounds each)
			daynightcount = 0;
		}
	}
	delete[] board;
	return 0;
}
