#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

enum weaponType{Sword, PyroStaff, Greatsword};
enum trait {Pierce, Leech1, Leech2, Leech4, Energize3, DoubleHit};

class weapon {
protected:
	weaponType type;
	string s1Name;
	string s2Name;
	int s1Dmg;
	int s2Dmg;
	int s1Cost;
	int s2Cost;
	int s1LCost;
	int s2LCost;
	vector<trait> s1traits;
	vector<trait> s2traits;
	map<trait, string> traitToString1;
	map<trait, string> traitToString2;
public:
	weapon(int x, weaponType y) {
		switch (y)
		{
		case Sword:
			type = Sword;
			s1Name = "Soul Slash";
			s2Name = "Soul Drain";
			s1Dmg = x + 2;
			s2Dmg = x + 2;
			s1Cost = 2;
			s2Cost = 4;
			s1LCost = 0;
			s2LCost = 0;
			s1traits.push_back(Pierce);
			s2traits.push_back(Leech1);
			traitToString1.insert({ Pierce, "Pierce" });
			traitToString2.insert({ Leech1, "Leech 1" });
			break;
		case PyroStaff:
			type = PyroStaff;
			s1Name = "Power Drain";
			s2Name = "Meteorquake";
			s1Dmg = x;
			s2Dmg = x + 8;
			s1Cost = 0;
			s2Cost = 10;
			s1LCost = 0;
			s2LCost = 0;
			s1traits.push_back(Leech4);
			s1traits.push_back(Energize3);
			traitToString1.insert({ Leech4, "Leech 4" });
			traitToString1.insert({ Energize3, "Energize 3" });
			break;
		case Greatsword:
			type = Greatsword;
			s1Name = "Invigorating Strike";
			s2Name = "Reckless Swing";
			s1Dmg = x;
			s2Dmg = x;
			s1Cost = 2;
			s2Cost = 5;
			s1LCost = 0;
			s2LCost = 3;
			s1traits.push_back(Leech2);
			s1traits.push_back(Pierce);
			s2traits.push_back(DoubleHit);
			traitToString1.insert({ Leech2, "Leech 2" });
			traitToString1.insert({ Pierce, "Pierce" });
			traitToString2.insert({ DoubleHit, "Double Hit" });
			break;
		}
	}

	weapon() {

	}

	string getWepType() {
		if (type == Sword) {
			return "Sword";
		}
		else if (type == PyroStaff) {
			return "Pyro Staff";
		}
		else {
			return "Greatsword";
		}
	}

	string getS1Name() { return s1Name; }
	string getS2Name() { return s2Name; }
	int getS1Att() { return s1Dmg; }
	int getS2Att() { return s2Dmg; }
	int getS1Cost() { return s1Cost; }
	int getS2Cost() { return s2Cost; }
	int getS1LCost() { return s1LCost; }
	int getS2LCost() { return s2LCost; }
	vector<trait> getS1Traits() { return s1traits; }
	vector<trait> getS2Traits() { return s2traits; }
	void setS1Cost(int n) { s1Cost = n; }
	void setS2Cost(int n) { s2Cost = n; }
	string convert1(trait m) { return traitToString1[m]; }
	string convert2(trait m) { return traitToString2[m]; }
};


class battler {
protected:
	string name;
	int maxHP;
	int curHP;
	int maxStam;
	int curStam;
	int att;
	int def;
	int acc;
	int spd;
	weapon wep;
	weaponType wepType;


public:
	battler(string n, int h, int s, int a, int d, int i, int sp, weaponType w) {
		name = n;
		maxHP = h;
		curHP = h;
		maxStam = s;
		curStam = s;
		att = a;
		def = d;
		acc = i;
		spd = sp;
		if (w == Sword) {
			wep = weapon(a, Sword);
			wepType = Sword;
		}
		else if (w == PyroStaff) {
			wep = weapon(a, PyroStaff);
			wepType = PyroStaff;
		}
		else {
			wep = weapon(a, Greatsword);
			wepType = Greatsword;
		}
	}

	battler() {

	}

	string getName() { return name; }
	string setName(string n) { name = n; }

	int getMAXHP() { return maxHP; }
	void setMAXHP(int n) { maxHP = n; }

	int getCURHP() { return curHP; }
	void setCURHP(int n) { curHP = n; }

	int getMAXSTAM() { return maxStam; }
	void setMAXSTAM(int n) { maxStam = n; }

	int getCURSTAM() { return curStam; }
	void setCURSTAM(int n) { curStam = n; }

	int getATT() { return att; }
	void setATT(int n) { att = n; }

	int getDEF() { return def; }
	void setDEF(int n) { def = n; }

	int getACC() { return acc; }
	void setACC(int n) { acc = n; }

	int getSPD() { return spd; }
	void setSPD(int n) { spd = n; }

	weapon getWep() { return wep; }


	void absorb(battler loser) {
		int newMaxHp = maxHP + (loser.getMAXHP() / 3);
		int newMaxStm = maxStam + (loser.getMAXSTAM() / 4);
		int newAtt = att + (loser.getATT() / 4);
		int newDef = def + (loser.getDEF() / 4);
		int newAcc = acc + (loser.getACC() / 4);
		int newSpd = spd + (loser.getSPD() / 4);
		cout << "[" + name + "] has grown stronger!" << endl;
		cout << "HP: [" << maxHP << "]+[" << (loser.getMAXHP() / 3) << "] -> [" << newMaxHp << "]" << endl;
		cout << "STM: [" << maxStam << "]+[" << (loser.getMAXSTAM() / 4) << "] -> [" << newMaxStm << "]" << endl;
		cout << "ATT: [" << att << "]+[" << (loser.getATT() / 4) << "] -> [" << newAtt << "]" << endl;
		cout << "DEF: [" << def << "]+[" << (loser.getDEF() / 4) << "] -> [" << newDef << "]" << endl;
		cout << "ACC: [" << acc << "]+[" << (loser.getACC() / 4) << "] -> [" << newAcc << "]" << endl;
		cout << "SPD: [" << spd << "]+[" << (loser.getSPD() / 4) << "] -> [" << newSpd << "]" << endl;
		maxHP = newMaxHp;
		maxStam = newMaxStm;
		att = newAtt;
		def = newDef;
		acc = newAcc;
		spd = newSpd;
		wep = weapon(att, wepType); 
	}

};


