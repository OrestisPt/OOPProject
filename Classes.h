#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include "colors.h"
#include <vector>

using namespace std;

class Werewolf;
class Vampire;

class Competitors {
	int health = 5;		
	int health_potion;
	int attack;
	int defense;
	int x = 0;
	int y = 0;
public:
	int get_x() const {
		return x;
	}
	int get_y() const {
		return y;
	}
	int get_health() const {
		return health;
	}
	int get_attack() const {
		return attack;
	}
	int get_defense() const {
		return defense;
	}
	int get_health_potion() const{
		return health_potion;
	}
	void set_x(int n) {
		x = n;
	}
	void set_y(int n) {
		y = n;
	}
	void set_health(int n) {
		health = n;
	}
	void set_attack(int n) {
		attack = n;
	}
	void set_defense(int n) {
		defense = n;
	}
	void set_health_potion(int n) {
		health_potion = n;
	}
	
	virtual void move(Competitors& c, int* board, int diameter, vector<Werewolf>& w, vector<Vampire>& v) {

	}
	void heal(Competitors& c1, Competitors& c2) {
		int hp = c1.get_health_potion();
		int h = c2.get_health();

		if (hp > 0 && h < 5 && rand() % 3 == 1) {
			h++;
			c2.set_health(h);
			hp--;
			c1.set_health_potion(hp);
		}
	}
};



class Avatar : public Competitors{ 
private:
	int x = 0;
	int y = 0;
	string username;
	int team = 0;
	int magic_potion = 1;
public:
	 void set_x(int n)  {
		x = n;
	};
	 void set_y(int n)  {
		y = n;
	};
	int get_x() const {
		return x;
	};
	int get_y() const {
		return y;
	};
	void set_username(string str) {
		username = str;
	}
	void set_team(int a) {
		team = a;
	}
	void increase_magicpot_num() {
		magic_potion += 1;
	}
	void diminish_magicpot_num() {
		magic_potion -= 1;
	}


	string get_username()const {
		return username;
	}
	int get_team()const {
		return team;
	}
	int get_magic_potion()const {
		return magic_potion;
	}
};

Competitors* locate_w(int, int, vector<Werewolf>&, int);
Competitors* locate_v(int, int, vector<Vampire>&, int);
void attackenemy(Competitors&, Competitors&);

class Werewolf : public Competitors {
public:
	Werewolf() {
		Competitors::set_health(5);
		Competitors::set_attack((rand() % 2) + 2);
		Competitors::set_defense((rand() % 2));
		Competitors::set_health_potion(rand() % 3);
		
	};
	void move(Competitors& c, int* board, int diameter, vector<Werewolf>& w, vector<Vampire>& v) {
		int x, y;
		x = c.get_x();
		y = c.get_y();;
		int rn = rand() % 5;

		if (*(board + (x + 1) * diameter + y) == 6) {  //If friend is below ...
			Competitors* tempw = locate_w(x + 1, y, w, w.size());
			c.heal(c, *tempw);
		}
		if (*(board + x * diameter + y + 1) == 6) {   //If friend is right ...
			Competitors* tempw = locate_w(x, y + 1, w, w.size());
			c.heal(c, *tempw);
		}
		if (*(board + x * diameter + y - 1) == 6) {  //If friend is left ...
			Competitors* tempw = locate_w(x, y - 1, w, w.size());
			c.heal(c, *tempw);
		}
		if (*(board + (x - 1) * diameter + y) == 6) {   //If friend is above ...
			Competitors* tempw = locate_w(x - 1, y, w, w.size());
			c.heal(c, *tempw);
		}
		switch (rn) {
			case 0:   //move down
				if (*(board + (x + 1) * diameter + y) == 3  || *(board + (x + 1) * diameter + y) == 4 || *(board + (x + 1) * diameter + y) == -3 || *(board + (x + 1) * diameter + y) == -2 || *(board + (x + 1) * diameter + y) == 1 || *(board + (x + 1) * diameter + y) == 2) {
					return;
				}
				if (*(board + (x + 1) * diameter + y) == 5) {
					return;
				}
				if (*(board + (x + 1) * diameter + y) == 6) {
					return;
				}
				*(board + x * diameter + y) = 0;
				x += 1;
				c.set_x(x);
				*(board + x * diameter + y) = 6;
				break;
			case 1:   // move up
				if (*(board + (x - 1) * diameter + y) == 3 || *(board + (x - 1) * diameter + y) == 4 || *(board + (x - 1) * diameter + y) == -3 || *(board + (x - 1) * diameter + y) == -2 || *(board + (x - 1) * diameter + y) == 1 || *(board + (x - 1) * diameter + y) == 2) {
					return;
				}
				if (*(board + (x - 1) * diameter + y) == 5) {
					return;;
				}
				if (*(board + (x - 1) * diameter + y) == 6) {
					return;;
				}
				*(board + x * diameter + y) = 0;
				x -= 1;
				c.set_x(x);
				*(board + x * diameter + y) = 6;
				break;
			case 2:  //move right
				if (*(board + x * diameter + y + 1) == 3 || *(board + x * diameter + y + 1) == 4 || *(board + x * diameter + y + 1) == -3 || *(board + x * diameter + y + 1) == -2 || *(board + x * diameter + y + 1) == 1 || *(board + x * diameter + y + 1) == 2) {
					return;
				}
				if (*(board + x * diameter + y + 1) == 5) {
					return;
				}
				if (*(board + x * diameter + y + 1) == 6) {
					return;
				}
				*(board + x * diameter + y) = 0;
				y += 1;
				c.set_y(y);
				*(board + x * diameter + y) = 6;
				break;
			case 3:  // move left
				if (*(board + x * diameter + y - 1) == 3 || *(board + x * diameter + y - 1) == 4 || *(board + x * diameter + y - 1) == -3 || *(board + x * diameter + y - 1) == -2 || *(board + x * diameter + y - 1) == 1 || *(board + x * diameter + y - 1) == 2) {
					return;
				}
				if (*(board + x * diameter + y - 1) == 5) {
					return;
				}
				if (*(board + x * diameter + y - 1) == 6) {
					return;
				}
				*(board + x * diameter + y) = 0;
				y -= 1;
				c.set_y(y);
				*(board + x * diameter + y) = 6;
				break;
			case 4: //no move
				break;
		}
	}
};

class Vampire : public Competitors {
public:
	Vampire() {
		Competitors::set_health(5);
		Competitors::set_attack((rand() % 2) + 2);
		Competitors::set_defense((rand() % 2));
		Competitors::set_health_potion(rand() % 3);

	};
	void move(Competitors& c, int* board, int diameter, vector<Werewolf>& w, vector<Vampire>& v) {
		int x, y;
		x = c.get_x();
		y = c.get_y();
		int rn = rand() % 9;

		if (*(board + (x + 1) * diameter + y) == 6) {  //If enemy is below ...
			Competitors* tempw = locate_w(x + 1, y, w, w.size());
			attackenemy(c, *tempw);
		}
		if (*(board + x * diameter + y + 1) == 6) {   //If enemy is right ...
			Competitors* tempw = locate_w(x, y + 1, w, w.size());
			attackenemy(c, *tempw);
		}
		if (*(board + x * diameter + y - 1) == 6) {  //If enemy is left ...
			Competitors* tempw = locate_w(x, y - 1, w, w.size());
			attackenemy(c, *tempw);
		}
		if (*(board + (x - 1) * diameter + y) == 6) {   //If enemy is above ...
			Competitors* tempw = locate_w(x - 1, y, w, w.size());
			attackenemy(c, *tempw);
		}

		if (*(board + (x + 1) * diameter + y) == 5) {  //If friend is below ...
			Competitors* tempw = locate_v(x + 1, y, v, v.size());
			c.heal(c, *tempw);
		}
		if (*(board + x * diameter + y + 1) == 5) {   //If friend is right ...
			Competitors* tempw = locate_v(x, y + 1, v, v.size());
			c.heal(c, *tempw);
		}
		if (*(board + x * diameter + y - 1) == 5) {  //If friend is left ...
			Competitors* tempw = locate_v(x, y - 1, v, v.size());
			c.heal(c, *tempw);
		}
		if (*(board + (x - 1) * diameter + y) == 5) {   //If friend is above ...
			Competitors* tempw = locate_v(x - 1, y, v, v.size());
			c.heal(c, *tempw);
		}
		switch (rn) {
		case 0:   //move down
			if (*(board + (x + 1) * diameter + y) == 3 || *(board + (x + 1) * diameter + y) == 4 || *(board + (x + 1) * diameter + y) == -3 || *(board + (x + 1) * diameter + y) == -2 || *(board + (x + 1) * diameter + y) == 1 || *(board + (x + 1) * diameter + y) == 2) {
				return;
			}
			if (*(board + (x + 1) * diameter + y) == 5) {
				return;
			}
			if (*(board + (x + 1) * diameter + y) == 6) {
				return;
			}
			*(board + x * diameter + y) = 0;
			x += 1;
			c.set_x(x);
			*(board + x * diameter + y) = 5;
			break;
		case 1:   // move up
			if (*(board + (x - 1) * diameter + y) == 3 || *(board + (x - 1) * diameter + y) == 4 || *(board + (x - 1) * diameter + y) == -3 || *(board + (x - 1) * diameter + y) == -2 || *(board + (x - 1) * diameter + y) == 1 || *(board + (x - 1) * diameter + y) == 2) {
				return;
			}
			if (*(board + (x - 1) * diameter + y) == 5) {
				return;;
			}
			if (*(board + (x - 1) * diameter + y) == 6) {
				return;;
			}
			*(board + x * diameter + y) = 0;
			x -= 1;
			c.set_x(x);
			*(board + x * diameter + y) = 5;
			break;
		case 2:  //move right
			if (*(board + x * diameter + y + 1) == 3 || *(board + x * diameter + y + 1) == 4 || *(board + x * diameter + y + 1) == -3 || *(board + x * diameter + y + 1) == -2 || *(board + x * diameter + y + 1) == 1 || *(board + x * diameter + y + 1) == 2) {
				return;
			}
			if (*(board + x * diameter + y + 1) == 5) {
				return;
			}
			if (*(board + x * diameter + y + 1) == 6) {
				return;
			}
			*(board + x * diameter + y) = 0;
			y += 1;
			c.set_y(y);
			*(board + x * diameter + y) = 5;
			break;
		case 3:  // move left
			if (*(board + x * diameter + y - 1) == 3 || *(board + x * diameter + y - 1) == 4 || *(board + x * diameter + y - 1) == -3 || *(board + x * diameter + y - 1) == -2 || *(board + x * diameter + y - 1) == 1 || *(board + x * diameter + y - 1) == 2) {
				return;
			}
			if (*(board + x * diameter + y - 1) == 5) {
				return;
			}
			if (*(board + x * diameter + y - 1) == 6) {
				return;
			}
			*(board + x * diameter + y) = 0;
			y -= 1;
			c.set_y(y);
			*(board + x * diameter + y) = 5;
			break;
		case 4: //move diagonally up-left
			if (*(board + (x - 1) * diameter + y - 1) == 3 || *(board + (x - 1) * diameter + y - 1) == 4 || *(board + (x - 1) * diameter + y - 1) == -3 || *(board + (x - 1) * diameter + y - 1) == -2 || *(board + (x - 1) * diameter + y - 1) == 1 || *(board + (x - 1) * diameter + y - 1) == 2 || *(board + (x - 1) * diameter + y - 1) == -1 || *(board + (x - 1) * diameter + y - 1) == 5 || *(board + (x - 1) * diameter + y - 1) == 6)
				return;
			*(board + x * diameter + y) = 0;
			x -= 1;
			y -= 1;
			c.set_x(x);
			c.set_y(y);
			*(board + x * diameter + y) = 5;
			break;
		case 5: //move diagonally down-left
			if (*(board + (x + 1) * diameter + y - 1) == 3 || *(board + (x + 1) * diameter + y - 1) == 4 || *(board + (x + 1) * diameter + y - 1) == -3 || *(board + (x + 1) * diameter + y - 1) == -2 || *(board + (x + 1) * diameter + y - 1) == 1 || *(board + (x + 1) * diameter + y - 1) == 2 || *(board + (x + 1) * diameter + y - 1) == -1 || *(board + (x + 1) * diameter + y - 1) == 5 || *(board + (x + 1) * diameter + y - 1) == 6)
				return;
			*(board + x * diameter + y) = 0;
			x += 1;
			y -= 1;
			c.set_x(x);
			c.set_y(y);
			*(board + x * diameter + y) = 5;
			break;
		case 6: //move diagonally up-right
			if (*(board + (x - 1) * diameter + y + 1) == 3 || *(board + (x - 1) * diameter + y + 1) == 4 || *(board + (x - 1) * diameter + y + 1) == -3 || *(board + (x - 1) * diameter + y + 1) == -2 || *(board + (x - 1) * diameter + y + 1) == 1 || *(board + (x - 1) * diameter + y + 1) == 2 || *(board + (x - 1) * diameter + y + 1) == -1 || *(board + (x - 1) * diameter + y + 1) == 5 || *(board + (x - 1) * diameter + y + 1) == 6)
				return;
			*(board + x * diameter + y) = 0;
			x -= 1;
			y += 1;
			c.set_x(x);
			c.set_y(y);
			*(board + x * diameter + y) = 5;
			break;
		case 7: //move diagonally down-right
			if (*(board + (x + 1) * diameter + y + 1) == 3 || *(board + (x + 1) * diameter + y + 1) == 4 || *(board + (x + 1) * diameter + y + 1) == -3 || *(board + (x + 1) * diameter + y + 1) == -2 || *(board + (x + 1) * diameter + y + 1) == 1 || *(board + (x + 1) * diameter + y + 1) == 2 || *(board + (x + 1) * diameter + y + 1) == -1 || *(board + (x + 1) * diameter + y + 1) == 5 || *(board + (x + 1) * diameter + y + 1) == 6)
				return;
			*(board + x * diameter + y) = 0;
			x += 1;
			y += 1;
			c.set_x(x);
			c.set_y(y);
			*(board + x * diameter + y) = 5;
			break;
		case 8: //no move
			break;

		}
	}
};


Competitors* locate_v(int x, int y, vector<Vampire>& v, int a) {
	for (int i = 0; i < a; i++) {
		if ((x == (v[i].get_x())) && (y == (v[i].get_y())))
			return &v[i];
	}
	return NULL;
}

Competitors* locate_w(int x, int y, vector<Werewolf>& w, int a) {
	for (int i = 0; i < a; i++) {
		if ((x == (w[i].get_x())) && (y == (w[i].get_y())))
			return &w[i];
	}
	return NULL;
}
void attackenemy(Competitors& v, Competitors& w) {
	int va, vd, vh, wa, wd, wh;
	va = v.get_attack();
	vd = v.get_defense();
	vh = v.get_health();
	wa = w.get_attack();
	wd = w.get_defense();
	wh = w.get_health();
	if (va > wd) {
		if(wh - (va - wd) < 0)
			w.set_health(0);
		else
			w.set_health(wh - (va - wd));
	}
	if (wa > vd) {
		if (vh - (wa - vd) < 0)
			v.set_health(0);
		else
			v.set_health(vh - (wa - vd));
	}
	return;
}

class Map {
private:
	int diameter;

public:
	Map(int n) : diameter(n) {};
	int get_diameter() const {
		return diameter;
	}

	void createboard(int diameter, int* board) {

		
		int magicpotion_Num = 1;
		int tree_Num = (diameter * diameter) / 40;
		int water_Num = (diameter * diameter) / 40;
		int earth_Num = diameter * diameter - 2 -  tree_Num - water_Num;

		int rn; //randomnumber
		*(board + 0 * diameter + 0) = -1;
		*(board + 0 * diameter + (diameter - 1)) = -1;
		*(board + (diameter - 1) * diameter + 0) = -1;
		*(board + (diameter - 1) * diameter + (diameter - 1)) = -1;

		for (int i = 1; i < diameter - 1; i++) {
			*(board + i * diameter + 0) = -2;

		}

		for (int i = 1; i < diameter - 1; i++) {
			*(board + i * diameter + (diameter - 1)) = -2;

		}

		for (int i = 1; i < diameter - 1; i++) {
			*(board + 0 * diameter + i) = -3;

		}

		for (int i = 1; i < diameter - 1; i++) {
			*(board + (diameter - 1) * diameter + i) = -3;

		}

		for (int i = 1; i < diameter - 1; i++) {
			for (int j = 1; j < diameter - 1; j++) {
					
				do {
					rn = rand() % 100;
				} while (rn >= 0 && rn < 3 && tree_Num == 0 || rn >= 3 && rn < 6 && water_Num == 0 ||
					rn >= 6 && rn < 9 && magicpotion_Num == 0 || rn >= 9 && rn < 100 && earth_Num == 0);

				if (rn >= 0 && rn < 3 && tree_Num != 0) {
					*(board + i * diameter + j) = 2;
					tree_Num = tree_Num - 1;
				}
				if (rn >= 3 && rn < 6 && water_Num != 0){
					*(board + i * diameter + j) = 1;
					water_Num = water_Num - 1;
				}
				if (rn >= 6 && rn < 9 && magicpotion_Num != 0) {
					*(board + i * diameter + j) = 3;
					magicpotion_Num = magicpotion_Num - 1;
				}
				if (rn >= 9 && rn < 100 && earth_Num != 0) {
					*(board + i * diameter + j) = 0;
					earth_Num = earth_Num - 1;
				}
			}
		}
	}

	void changeboard(int diameter, int* board, Avatar avatar, vector<Werewolf> w, vector<Vampire> v) {
		int x, y;
		x = avatar.get_x();
		y = avatar.get_y();
		int ws = w.size() - 1;
		int vs = v.size() - 1;
		if (ws + 1 == 0) {
			return;
		}
		if (vs + 1 == 0) {
			return;
		}
		*(board + x * diameter + y) = 4;

		for (ws; ws >= 0; ws--) {
			x = w[ws].get_x();
			y = w[ws].get_y();
			*(board + x * diameter + y) = 6;
		}
		for (vs; vs >= 0; vs--) {
			x = v[vs].get_x();
			y = v[vs].get_y();
			*(board + x * diameter + y) = 5;
		}
	}

	void printboard(int diameter, int* board, int a) {
		cout << "\n\n\nIt is: ";
		if (a <= 20)
			cout << "Day.\n\n";
		else
			cout << "Night.\n\n";
		for (int i = 0; i < diameter; i++) {
			cout << "\t\t\t";
			for (int j = 0; j < diameter; j++) {
				if (*(board + i * diameter + j) == 6)
					cout << FYEL("W ");
				if (*(board + i * diameter + j) == 5)
					cout << "V ";
				if (*(board + i * diameter + j) == 4)
					cout << BOLD(FRED("A "));
				if (*(board + i * diameter + j) == 3)
					cout << FCYN("P ");
				if (*(board + i * diameter + j) == 2)
					cout << FGRN("Y ");
				if (*(board + i * diameter + j) == 1)
					cout << FBLU("~ ");
				if (*(board + i * diameter + j) == 0)
					cout << FLGR("  ");
				if (*(board + i * diameter + j) == -1)
					cout << FRED("+");
				if (*(board + i * diameter + j) == -2)
					cout << FYEL("|");
				if (*(board + i * diameter + j) == -3)
					cout << FYEL("==");
			}
			cout << endl;
		}
		cout << "\n\t\t\t" << BOLD("YOU MOVE WITH W, A, S, D\n\t\t\tPRESS '0' TO TERMINATE GAME\n\t\t\tPRESS 'P' TO PAUSE GAME\n\t\t\tPRESS 'SPACE' TO USE A MAGIC POTION");
	}
	void move_down(Map nmap,Avatar& avatar,int *board) {
		int x, y;
		x = avatar.get_x();
		y = avatar.get_y();
		int diameter = nmap.get_diameter();
		if (*(board + (x + 1) * diameter + y) == -3 || *(board + (x + 1) * diameter + y) == 1 || *(board + (x + 1) * diameter + y) == 2 || *(board + (x + 1) * diameter + y) == 5|| *(board + (x + 1) * diameter + y) == 6) {
			return;
		}
		if (*(board + (x + 1) * diameter + y) == 3) {
			avatar.increase_magicpot_num();
		}
		*(board + x * diameter + y) = 0;
		x += 1;
		avatar.set_x(x);
		*(board + x * diameter + y) = 4;
	}
	void move_up(Map nmap, Avatar& avatar, int* board) {
		int x, y;
		x = avatar.get_x();
		y = avatar.get_y();
		int diameter = nmap.get_diameter();
		if (*(board + (x - 1) * diameter + y) == -3 || *(board + (x - 1) * diameter + y) == 1 || *(board + (x - 1) * diameter + y) == 2 || *(board + (x - 1) * diameter + y) == 5 || *(board + (x - 1) * diameter + y) == 6) {
			return;
		}
		if (*(board + (x - 1) * diameter + y) == 3) {
			avatar.increase_magicpot_num();
		}
		*(board + x * diameter + y) = 0;
		x -= 1;
		avatar.set_x(x);
		*(board + x * diameter + y) = 4;
	}
	void move_left(Map nmap, Avatar& avatar, int* board) {
		int x, y;
		x = avatar.get_x();
		y = avatar.get_y();
		int diameter = nmap.get_diameter();
		if (*(board + x * diameter + y - 1) == -2  || *(board + x * diameter + y - 1) == 1|| *(board + x * diameter + y - 1) == 2 || *(board + x * diameter + y - 1) == 5 || *(board + x * diameter + y - 1) == 6) {
			return ;
		}
		if (*(board + x * diameter + y - 1) == 3) {
			avatar.increase_magicpot_num();
		}
		*(board + x * diameter + y) = 0;
		y -= 1;
		avatar.set_y(y);
		*(board + x * diameter + y) = 4;
	}
	void move_right(Map nmap, Avatar& avatar, int* board) {
		int x, y;
		x = avatar.get_x();
		y = avatar.get_y();
		int diameter = nmap.get_diameter();
		if (*(board + x * diameter + y + 1) == -2 || *(board + x * diameter + y + 1) == 1 || *(board + x * diameter + y + 1) == 2 || *(board + x * diameter + y + 1) == 5 || *(board + x * diameter + y + 1) == 6) {
			return;
		}
		if (*(board + x * diameter + y + 1) == 3) {
			avatar.increase_magicpot_num();
		}
		*(board + x * diameter + y) = 0;
		y += 1;
		avatar.set_y(y);
		*(board + x * diameter + y) = 4;
	}
};
