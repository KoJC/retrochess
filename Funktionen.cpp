//damit der Compiler bei fopen() keinen Fehler anzeigt ("function unsafe")
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <iostream>
#include "header.h"
using namespace std;


char zeichen;
FILE* fp;

void speichern(char feld[8][8]) {
	//Speichern der aktuellen Positionen in einer txt Datei
	//Öffnen und ggf. Erstellen der txt Datei
	fp = fopen("C:/Users/paulo/Desktop/positionen", "w+");

	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			zeichen = feld[a][b];
			fputc(zeichen, fp);
		}
	}
	fclose(fp);
}

void laden(char feld[8][8]) {
	//Auslesen der Positionen aus der gewählten Datei
	//beim Auftreten eines Fehlers Ausgabe der Fehlermeldung
	fp = fopen("C:/Users/paulo/Desktop/positionen", "r");
	if (fp == NULL) {
		cout << "Fehler; keine Datei vorhanden" << endl;
	}
	else {
		zeichen = fgetc(fp);
		int a = 0;
		int b = 0;
		while (zeichen != EOF) {
			feld[a][b] = zeichen;
			b++;
			if (b == 8) {
				a++;
				b = 0;
			}

			zeichen = fgetc(fp);
		}
		fclose(fp);
	}


}