//damit der Compiler bei fopen() keinen Fehler anzeigt ("function unsafe")
#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<iostream>

//Einbindung aller weiteren Funktionen aus den anderen cpp-Dateien
#include "header.h"

using namespace std;

void startpos(char feld[8][8]);


int main() {
	int eingabe;
	char feld[8][8];

	//Startbildschrim
	cout << "						RETROSCHACH" << endl << endl << endl;
	cout << "Willkommen zu dem etwas rustikalerem Schachspiel" << endl;
	cout << "Folgende Funktionen sind verfügbar:\n(0)Beenden\n(1) Neues Spiel\n(2) Laden\n(3) Speichern\n(4) Hilfe" << endl;
	cout << "Befehlszeile: ";
	cin >> eingabe;

	//Menü des Spiels
	switch (eingabe) {
	case 0: 
		return 0;
		break;
	case 1:
		//Einlesen der Startpostítionen
		startpos(feld);
		//Darstellung des Brettes
		schachbrett(feld);
		break;
	case 2:
        laden(feld);
		break; 
	case 3:
        speichern(feld);
			break;
	case 4:
		break;
	default:
		cout << "Ungültige Eingabe" << endl;
		break;
	}

	return 0;
}


//Übergabe der Figuren beim Neustarten eines Spiels an das feld-array
//schwarze Figuren werden hierbei als Kleinbuchstaben, weiße als Großbuchstaben gekennzeichnet
void startpos(char feld[8][8]) {
	char start[8][8] = { {'T','S','L','D','K','L','S','T'},
						{'B','B','B','B','B','B','B','B'},
						{},{},{},{},
						{'b','b','b','b','b','b','b','b'},
						{'t','s','l','d','k','l','s','t'} };

	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			feld[a][b] = start[a][b];
		}
	}
}