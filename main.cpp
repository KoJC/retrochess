//damit der Compiler bei fopen() keinen Fehler anzeigt ("function unsafe")
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "startbildschirm.h"
#include "Brett.h"
#include "Funktionen.h"
#include "bewegen.h"
#include "Brett.cpp"
#include "Funktionen.cpp"
#include "startbildschirm.cpp"
#include "bewegen.cpp"

//um den Buffer von cin() zu flushen nach Funktionen, die cin() benutzt haben
//sonst wird Eintrag im Buffer in die Befehlszeile übernommen, was diese mit "ungültiger Eingabe" ausweist
#include <limits>
using namespace std;

void startpos(char feld[8][8]);
void hilfe();
void eingabe();

//globale Variable für das Beenden des Spieles
bool ende = 1;

int main()
{
	//Startbildschrim
	startbildschirm();

	while (ende)
	{
		eingabe();
	}
}
//###################################################################################################################################

//Funktion für die Eingaben in der Befehlszeile
void eingabe()
{
	//Bei jedem Schleifendurchlauf wird die Variable wieder auf 5 gesetzt. Wenn der Wert nicht durch "menu"
	//geändert wird, soll auch nichts passiereren. Dafür sorgt dann die leere case-Anweisung für den Wert 5
	int menupunkt = 5;
	char feld[8][8];
	string zug;	   //string für den "move" und "help"-Befehl
	string help;   //string für den "help"-befehl
	string befehl; //Die Eingabe in die Befehlszeile

	//Definition der verschiedenen Befehlstrings
	string menu1 = "menu";
	string menu2 = "MENU";
	string move1 = "move";
	string move2 = "MOVE";
	string help1 = "help";
	string help2 = "HELP";
	string remis1 = "remis";
	string remis2 = "REMIS";
	string aufgeben1 = "aufgeben";
	string aufgeben2 = "AUFGEBEN";

	cout << endl
		 << endl
		 << endl
		 << "Befehlszeile: ";
	getline(cin, befehl);

	//Überprüfung, ob dieser Teilstring in der Eingabe enthalten ist und damit, welcher Befehl eingegeben wurde
	//dabei ist die syntaxgerechte Eingabe laut den Vorgaben notwendig

	if (((befehl.find(menu1) != string::npos && befehl[0] == 'm') || (befehl.find(menu2) != string::npos && befehl[0] == 'M')) && befehl[4] == ' ' && befehl[6] == '\0')
		 menupunkt = befehl[5]-48;
	
	else if (((befehl.find(move1) != string::npos && befehl[0] == 'm') || (befehl.find(move2) != string::npos && befehl[0] == 'M')) && befehl[4] == ' ' && befehl[7] == ' ' && befehl[10] == '\0')
		{zug = befehl.replace(0, 5, "");
		 zug = befehl.replace(2, 1, "");
		}

	else if (((befehl.find(help1) != string::npos && befehl[0] == 'h') || (befehl.find(help2) != string::npos && befehl[0] == 'H')) && befehl[4] == ' ' && befehl[7] == '\0')
		help = befehl.replace(0, 5, "");

	else if (((befehl.find(remis1) != string::npos && befehl[0] == 'r') || (befehl.find(remis2) != string::npos && befehl[0] == 'R')) && befehl[5] == '\0')
		zug = "remis";

	else if (((befehl.find(aufgeben1) != string::npos && befehl[0] == 'a') || (befehl.find(aufgeben2) != string::npos && befehl[0] == 'A')) && befehl[8] == '\0')
		zug = "aufgeben";

	else
	{
		cout << "Ungültige Eingabe";
	}

	//Menüpunkte des Spiels
	switch (menupunkt)
	{
	case 0:
		ende = 0;
		break;
	case 1:
		//Einlesen der Startpostítionen
		startpos(feld);
		//Darstellung des Brettes
		cout << endl;
		schachbrett(feld);
		//#########ACHTUNG############
		void bewegen(char feld[8][8], int pos[]);
		//void ziehen(char feld[8][8], string befehl);
		//#########ACHTUNG############
		break;
	case 2:
		laden(feld);
		schachbrett(feld);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		break;
	case 3:
		speichern(feld);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		break;
	case 4:
		hilfe();
		break;
	case 5:
		break;
	default:
		cout << "Ungültiger Menüpunkt" << endl;
		break;
	}

	//Aufruf der bewegen_Funktion
	if(help != "")
		ziehen(feld, help);
	else if(zug != "")
		ziehen(feld, zug);

}

//###################################################################################################################################

//Übergabe der Figuren beim Neustarten eines Spiels an das feld-array
//schwarze Figuren werden hierbei als Kleinbuchstaben, weiße als Großbuchstaben gekennzeichnet
//leere Felder haben '0' als Wert
void startpos(char feld[8][8])
{
	char start[8][8] = {{'T', 'S', 'L', 'D', 'K', 'L', 'S', 'T'},
						{'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
						{'0', '0', '0', '0', '0', '0', '0', '0'},
						{'0', '0', '0', '0', '0', '0', '0', '0'},
						{'0', '0', '0', '0', '0', '0', '0', '0'},
						{'0', '0', '0', '0', '0', '0', '0', '0'},
						{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
						{'t', 's', 'l', 'd', 'k', 'l', 's', 't'}};

	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			feld[a][b] = start[a][b];
		}
	}
}

//###################################################################################################################################

//Ausgabe aller möglichen Befehle
//Ausgabe der Regeln des Schachspiels
void hilfe()
{
	cout << endl
		 << endl
		 << endl
		 << "############################################################################################################################" << endl
		 << endl
		 << "Die folgenden Befehle sind im Programm zulässig.\nDabei sind sowohl Groß- als auch Kleinschreibung erlaubt." << endl
		 << "Vor Befehlseingaben sind keine weiteren Zeichen zulässig." << endl
		 << "Zwischen Befehl und dazugehöriger Eingabe muss ein Leerzeichen stehen." << endl
		 << endl

		 << "MENU X                   -> Ausführung des X-ten Menüpunktes" << endl
		 << "MOVE Position1 Position2 -> Bewegen der Figur auf Position1 zu Position2\n"
			"                            Die Leerzeichen sind dabei zwingend erforderlich"
		 << endl
		 << "HELP Position1           -> Zeigt die möglichen Zielpositionen der auf Position1 befindlichen Figur" << endl
		 << "REMIS                    -> Ein Spieler kann damit ein Remis anbieten. Der gleiche Befehl muss vom zweiten Spieler eingegeben werden,\n"
			"                            Um dies zu bestätigen"
		 << endl
		 << "AUFGEBEN                 -> Der Spieler gibt auf und verliert dadurch das Spiel" << endl
		 << endl
		 << "Hinweis: Bei Positionsangaben wird zuerst der Buchstabe und anschließend die Zahl eingegeben\n"
		 << "Beipiel: MOVE A1 B3" << endl
		 << endl
		 << "############################################################################################################################" << endl;
}