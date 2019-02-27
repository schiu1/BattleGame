#include "charClasses.cpp"
#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

battler battle(battler player1, battler player2) {
	battler attacker;
	battler defender;
	battler winner;
	cout << "______BATTLE START______" << endl;
	if (player1.getSPD() > player2.getSPD()) {
		attacker = player1;
		defender = player2;
		cout << "[" + attacker.getName() + "] goes first." << endl;
		cout << "________________________";
		string trash;
		getline(cin, trash);
		//system("cls");
	}
	else if (player1.getSPD() == player2.getSPD()) {
		attacker = player1;
		defender = player2;
		cout << "[" + attacker.getName() + "] goes first." << endl;
		cout << "________________________";
		string trash;
		getline(cin, trash);
		//system("cls");
	}
	else {
		attacker = player2;
		defender = player1;
		cout << "[" + attacker.getName() + "] goes first." << endl;
		cout << "________________________";
		string trash;
		getline(cin, trash);
		//system("cls");
	}
	while (true) {
		cout << "\n________________________" << endl;
		cout << "[" + defender.getName() + "]:[" + defender.getWep().getWepType() + "]" << endl;
		cout << "HP [" << defender.getCURHP() << "/" << defender.getMAXHP() << ")\n[";
		for (int i = 0; i < defender.getCURHP(); i++) { cout << "|"; }
		int spaces2 = defender.getMAXHP() - defender.getCURHP();
		for (int i = 0; i < spaces2; i++) { cout << "-"; }
		cout << ")\nSTM [" << defender.getCURSTAM() << "/" << defender.getMAXSTAM() << ">\n[";
		for (int i = 0; i < defender.getCURSTAM(); i++) { cout << "#"; }
		int pound2 = defender.getMAXSTAM() - defender.getCURSTAM();
		for (int i = 0; i < pound2; i++) { cout << "-"; }
		cout << ">\n________________________\n\n________________________" << endl;
		cout << "[" + attacker.getName() + "]:[" + attacker.getWep().getWepType() + "]" << endl;
		cout << "HP [" << attacker.getCURHP() << "/" << attacker.getMAXHP() << ")\n[";
		for (int i = 0; i < attacker.getCURHP(); i++) { cout << "|"; }
		int spaces = attacker.getMAXHP() - attacker.getCURHP();
		for (int i = 0; i < spaces; i++) { cout << "-"; }
		cout << ")\nSTM [" << attacker.getCURSTAM() << "/" << attacker.getMAXSTAM() << ">\n[";
		for (int i = 0; i < attacker.getCURSTAM(); i++) { cout << "#"; }
		int pound = attacker.getMAXSTAM() - attacker.getCURSTAM();
		for (int i = 0; i < pound; i++) { cout << "-"; }
		cout << ">\n"<< endl;
		
		cout << attacker.getName() + "'s turn, choose:\n1:[Attack]\n2:[Rest]" << endl;
		cout << "________________________\n-> ";
		string action;
		getline(cin, action);
		if (action == "1") {
			string attack;
			cout << "Choose an attack:\n1:[" + attacker.getWep().getS1Name() + "]" << endl;
			vector<trait> trait1 = attacker.getWep().getS1Traits();
			vector<trait> trait2 = attacker.getWep().getS2Traits();
			for (int i = 0; i < trait1.size(); i++) {
				cout << "   -[" + attacker.getWep().convert1(trait1[i]) + "]" << endl;
			}
			cout << "2:[" + attacker.getWep().getS2Name() + "]" << endl;
			for (int i = 0; i < trait2.size(); i++) {
				cout << "   -[" + attacker.getWep().convert2(trait2[i]) + "]" << endl;
			}
			cout << "\n-> ";
			getline(cin, attack);
			int dmg;
			string name;
			int cost;
			int lifeCost;
			vector<trait> trts;
			if (attack == "1") {
				dmg = attacker.getWep().getS1Att() - (defender.getDEF() / 3);
				name = attacker.getWep().getS1Name();
				cost = attacker.getWep().getS1Cost();
				lifeCost = attacker.getWep().getS1LCost();
				trts = trait1;
			}
			else if (attack == "2") {
				dmg = attacker.getWep().getS2Att() - (defender.getDEF() / 3);
				name = attacker.getWep().getS2Name();
				cost = attacker.getWep().getS2Cost();
				lifeCost = attacker.getWep().getS2LCost();
				trts = trait2;
			}
			else {
				cout << "Not valid option." << endl;
				string trash;
				getline(cin, trash);
				continue;
			}
			if (cost > attacker.getCURSTAM()) {
				cout << "Not enough STAM" << endl;
				string trash;
				getline(cin, trash);
				cout << "\n________________________" << endl;
				continue;
			}

			//hit/miss code goes here. If misses, continue and say that the hit missed.
			random_device rd;     // only used once to initialise (seed) engine
			mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
			uniform_int_distribution<int> attRoll(0, attacker.getACC()); // guaranteed unbiased
			uniform_int_distribution<int> defRoll(0, defender.getSPD());
			auto hitRoll = attRoll(rng);
			auto dodgeRoll = defRoll(rng);
			cout << attacker.getName() + "'s roll: " << hitRoll << endl;
			cout << defender.getName() + "'s roll: " << dodgeRoll << endl;
			if (dodgeRoll > hitRoll) {
				cout << "[" + attacker.getName() + "]'s attack missed!" << endl;
				string trash;
				getline(cin, trash);
				battler temp = attacker;
				attacker = defender;
				defender = temp;
				//system("cls");
				continue;
			}

			//crit system 
			
			for (int i = 0; i < trts.size(); i++) {
				switch (trts[i])
				{
				case Pierce:
					dmg += (defender.getDEF() / 3);
					cout << "[" + attacker.getName() + "] pierced through [" + defender.getName() + "]'s defenses." << endl;
					break;
				case DoubleHit:
					dmg *= 2;
					cout << "[" + attacker.getName() + "] hits twice with [" + name + "]." << endl;
					break;
				default:
					break;
				}
			}
			if (lifeCost != 0) {
				if (dmg / lifeCost >= attacker.getCURHP()) {
					cout << "[" + attacker.getName() + "] died due to recoil." << endl;
					string trash;
					getline(cin, trash);
					defender.absorb(attacker);
					winner = defender;
					break;
				}
				attacker.setCURHP(attacker.getCURHP() - dmg / lifeCost);
				cout << "[" + attacker.getName() + "] lost [" << dmg / lifeCost << "] HP due to recoil." << endl;

			}
			if (dmg <= 0) {
				cout << "[" + defender.getName() + "] took no damage from [" + attacker.getName() + "]'s attack.";
			}
			else {
				defender.setCURHP(defender.getCURHP() - dmg);
				attacker.setCURSTAM(attacker.getCURSTAM() - cost);
				cout << "[" + attacker.getName() + "] attacks [" + defender.getName() + "] with [" + name + "], dealing [" << dmg << "] damage." << endl;
			}
			for (int i = 0; i < trts.size(); i++) {
				switch (trts[i])
				{
				case Leech1:
					if (attacker.getCURHP() == attacker.getMAXHP()) {
						cout << "HP is full." << endl;
					}
					else if (attacker.getCURHP() + (dmg) > attacker.getMAXHP()) {
						cout << "[" + attacker.getName() + "] restored [" << attacker.getMAXHP() - attacker.getCURHP() << "] HP from [" + name + "]." << endl;
						attacker.setCURHP(attacker.getMAXHP());
					}
					else {
						attacker.setCURHP(attacker.getCURHP() + (dmg));
						cout << "[" + attacker.getName() + "] restored [" << (dmg) << "] HP from [" + name + "]." << endl;
					}
					break;
				case Leech2:
					if (attacker.getCURHP() == attacker.getMAXHP()) {
						cout << "HP is full." << endl;
					}
					else if (attacker.getCURHP() + (dmg/2) > attacker.getMAXHP()) {
						cout << "[" + attacker.getName() + "] restored [" << attacker.getMAXHP() - attacker.getCURHP() << "] HP from [" + name + "]." << endl;
						attacker.setCURHP(attacker.getMAXHP());
					}
					else {
						attacker.setCURHP(attacker.getCURHP() + (dmg/2));
						cout << "[" + attacker.getName() + "] restored [" << (dmg/2) << "] HP from [" + name + "]." << endl;
					}
					break;
				case Leech4:
					if (attacker.getCURHP() == attacker.getMAXHP()) {
						cout << "HP is full." << endl;
					}
					else if (attacker.getCURHP() + (dmg / 4) > attacker.getMAXHP()) {
						cout << "[" + attacker.getName() + "] restored [" << attacker.getMAXHP() - attacker.getCURHP() << "] HP from [" + name + "]." << endl;
						attacker.setCURHP(attacker.getMAXHP());
					}
					else {
						attacker.setCURHP(attacker.getCURHP() + (dmg / 4));
						cout << "[" + attacker.getName() + "] restored [" << (dmg / 4) << "] HP from [" + name + "]." << endl;
					}
					break;
				case Energize3:
					if (attacker.getCURSTAM() == attacker.getMAXSTAM()) {
						cout << "Stamina is full." << endl;
					}
					else if (attacker.getCURSTAM() + (dmg * 3) > attacker.getMAXSTAM()) {
						cout << "[" + attacker.getName() + "] restored [" << attacker.getMAXSTAM() - attacker.getCURSTAM() << "] Stamina from [" + name + "]." << endl;
						attacker.setCURSTAM(attacker.getMAXSTAM());
					}
					else {
						attacker.setCURSTAM(attacker.getCURSTAM() + (dmg * 3));
						cout << "[" + attacker.getName() + "] restored [" << dmg * 3 << "] Stamina from [" + name + "]." << endl;
					}
					break;
				default:
					break;
				}
			}
		}
		else if (action == "2") {
			int amt = attacker.getATT();
			if (attacker.getCURSTAM() == attacker.getMAXSTAM()) {
				cout << "[" + attacker.getName() + "] cannot rest anymore" << endl;
			}
			else if ((attacker.getCURSTAM() + amt) > attacker.getMAXSTAM()) { 
				cout << "[" + attacker.getName() + "] rested for [" << (attacker.getMAXSTAM() - attacker.getCURSTAM()) << "] Stamina." << endl;
				attacker.setCURSTAM(attacker.getMAXSTAM()); 
			}
			else { 
				attacker.setCURSTAM(attacker.getCURSTAM() + amt);
				cout << "[" + attacker.getName() + "] rested for [" << amt << "] Stamina." << endl;
			}
		}
		else {
			cout << "Not valid option." << endl;
			string trash;
			getline(cin, trash);
			continue;
		}
		string trash;
		getline(cin, trash);
		if (defender.getCURHP() <= 0) {
			cout << "[" + attacker.getName() + "] killed [" + defender.getName() + "]" << endl;
			string trash;
			getline(cin, trash);
			cout << "\n________________________" << endl;
			attacker.absorb(defender);
			winner = attacker;
			break;
		}
		battler temp = attacker;
		attacker = defender;
		defender = temp;
		//system("cls");
		//cout << "\n________________________" << endl;
	}
	cout << "_______BATTLE END_______" << endl;
	return winner;
}

int main()
{
	battler p1 = battler("Moter", 20, 15, 10, 7, 10, 10, Greatsword);
	battler p2 = battler("Aermia", 20, 15, 7, 10, 10, 10, PyroStaff);
	battler winner = battle(p2, p1);
	while (true) {
		string trash;
		getline(cin, trash);
		//system("cls");
		cout << "Please enter a new Battler to fight or [Done].\nName: ";
		string name;
		getline(cin, name);
		if (name == "done") {
			cout << "Exiting..." << endl;
			break;
		}
		//output = min + (rand() % static_cast<int>(max - min + 1))
		srand(time(0));
		int hp2 = (winner.getMAXHP() - 10) + (rand() % static_cast<int>((winner.getMAXHP() + 10) - (winner.getMAXHP() - 10) + 1));
		int stam2 = (winner.getMAXSTAM() - 10) + (rand() % static_cast<int>((winner.getMAXSTAM() + 10) - (winner.getMAXSTAM() - 10) + 1));
		int att2 = (winner.getATT() - 10) + (rand() % static_cast<int>((winner.getATT() + 10) - (winner.getATT() - 10) + 1));
		int def2 = (winner.getDEF() - 10) + (rand() % static_cast<int>((winner.getDEF() + 10) - (winner.getDEF() - 10) + 1));
		int acc2 = (winner.getACC() - 10) + (rand() % static_cast<int>((winner.getACC() + 10) - (winner.getACC() - 10) + 1));
		int spd2 = (winner.getSPD() - 10) + (rand() % static_cast<int>((winner.getSPD() + 10) - (winner.getSPD() - 10) + 1));
		bool alltrue = false;
		while (alltrue == false) {
			if (hp2 < 0) {
				//cout << "hp" << endl;
				hp2 = (winner.getMAXHP() - 10) + (rand() % static_cast<int>((winner.getMAXHP() + 10) - (winner.getMAXHP() - 10) + 1));
			}
			else if (stam2 < 0) {
				//cout << "stam" << endl;
				stam2 = (winner.getMAXSTAM() - 10) + (rand() % static_cast<int>((winner.getMAXSTAM() + 10) - (winner.getMAXSTAM() - 10) + 1));
			}
			else if (att2 < 0) {
				//cout << "att" << endl;
				att2 = (winner.getATT() - 10) + (rand() % static_cast<int>((winner.getATT() + 10) - (winner.getATT() - 10) + 1));
			}
			else if (def2 < 0) {
				//cout << "def" << endl;
				def2 = (winner.getDEF() - 10) + (rand() % static_cast<int>((winner.getDEF() + 10) - (winner.getDEF() - 10) + 1));
			}
			else if (acc2 < 0) {
				//cout << "int" << endl;
				acc2 = (winner.getACC() - 10) + (rand() % static_cast<int>((winner.getACC() + 10) - (winner.getACC() - 10) + 1));
			}
			else if (spd2 < 0) {
				//cout << "spd" << endl;
				spd2 = (winner.getSPD() - 10) + (rand() % static_cast<int>((winner.getSPD() + 10) - (winner.getSPD() - 10) + 1));
			}
			else {
				//cout << "done" << endl;
				alltrue = true;
			}
		}
		cout << "HP: " << hp2 << endl;
		cout << "STM: " << stam2 << endl;
		cout << "ATT: " << att2 << endl;
		cout << "DEF: " << def2 << endl;
		cout << "ACC: " << acc2 << endl;
		cout << "SPD: " << spd2 << endl;
		int roll = 1 + (rand() % static_cast<int>(3 - 1 + 1));
		weaponType wep;
		if (roll == 1) {
			wep = Sword;
			cout << "Weapon : Sword" << endl;
		}
		else if (roll == 2) {
			wep = PyroStaff;
			cout << "Weapon : Pyro Staff" << endl;
		}
		else {
			wep = Greatsword;
			cout << "Weapon : Greatsword" << endl;
		}
		getline(cin, trash);
		winner.setCURHP(winner.getMAXHP());
		winner.setCURSTAM(winner.getMAXSTAM());
		battler opponent = battler(name, hp2, stam2, att2, def2, acc2, spd2, wep);
		winner = battle(winner, opponent);
	}
	return 0;
}

