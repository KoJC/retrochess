//mittels dieses ASCII-Zeichens kann ein weißer Unterstrich erzeugt werden
#define weiß 0xDF

#include <stdio.h>
#include <iostream>
#include "header.h"
using namespace std;


void schachbrett(char feld[8][8]) {
	//Darstellung des Schachbrettes samt Seitenbezeichungen
	//ein Feld ist 3x3 groß (5x5 mit Rand), der bezeichnende Buchstabe steht in der Mitte
	//Ausgabe der in feld[][] enthaltenen Figurenpositionen

	cout << "             A         B         C         D         E         F         G         H" << endl << endl;

	int z = 1;

	//Durchlaufen jeder Zeile des Schachfeldes
	for (int i = 0; i < 35; i++) {

		//die beiden Ränder oben und unten
		if (i == 0 || i == 34) {
			cout << "       ###################################################################################";
		}

		//die Abgrenzungen zwischen den einzelnen Feldern
		//sprich die erste Zeile von jedem Feld
		else if (i == 1 || i == 5 || i == 9 || i == 13 || i == 17 || i == 21 || i == 25 || i == 29 || i == 33) {
			for (int j = 0; j < 8; j++) {
				if (j == 0) cout << "       ##-----";
				else if (j == 7) cout << "----|---------##";
				else cout << "----|-----";
			}
		}

		//die Leerplätze in diesen Feldern
		else if (i == 2 || i == 6 || i == 10 || i == 14 || i == 18 || i == 22 || i == 26 || i == 30) {
			for (int j = 0; j < 8; j++) {
				if (j == 0) cout << "       ##     ";
				else if (j == 7) cout << "    |         ##";
				else cout << "    |     ";
			}

		}

		//Darstellung der Figuren in den mittleren Feldzeilen
		//weiße Figuren bekommen einen weißen Unterstrich
		//Erkennbar sind sie an der Großschreibung ihrer Bezeichungen im feld[][]-Array
		else if (i == 4 || i == 8 || i == 12 || i == 16 || i == 20 || i == 24 || i == 28 || i == 32) {
			for (int j = 0; j < 8; j++) {
				if (feld[z - 2][j] < 91 && feld[z - 2][j] > 64) {
					if (j == 0) cout << "       ##   " << char(weiß) << char(weiß);
					else if (j == 7) cout << char(weiß) << "   |   " << char(weiß) << char(weiß) << char(weiß) << "   ##";
					else cout << char(weiß) << "   |   " << char(weiß) << char(weiß);
				}

				else {
					if (j == 0) cout << "       ##     ";
					else if (j == 7) cout << "    |         ##";
					else cout << "    |     ";
				}
			}
		}

		//die Zeilen der Felder, in denen die Buchstaben für die Figuren stehen
		//schwarze Bezeichnungen werden ebenfalls als Großbuchtstaben ausgegeben, 
		//indem von ihrem eigentlichen Wert 32 subtrahiert wird (ASCII-Tabelle)
		else {
			for (int j = 0; j < 8; j++) {
				if (j == 0) {
					if (feld[z - 1][j] < 91) cout << "   " << z << "   ##    " << feld[z - 1][j];
					else cout << "   " << z << "   ##    " << char(feld[z - 1][j] - 32);
				}
				else {
					if (feld[z - 1][j] < 91) cout << "    |    " << feld[z - 1][j];
					else cout << "    |    " << char(feld[z - 1][j] - 32);
				}
				if (j == 7) cout << "    ##    " << z;
			}
			z++;
		}
		cout << endl;
	}
	cout << endl;
	cout << "             A         B         C         D         E         F         G         H" << endl << endl;
}