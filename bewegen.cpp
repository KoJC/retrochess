#include <stdio.h>
#include <iostream>
#include <string.h>
#include "bewegen.h"

using namespace std;
void umwandeln(string befehl, int pos[]);
void bewegen(char feld[8][8], int pos[]);
void gultigesFeld(char feld[8][8], int moglichkeiten[64][2], bool schwarz);

void ziehen(char feld[8][8], string befehl)
{
	int pos[befehl.length() - 1];
	umwandeln(befehl, pos);
	bewegen(feld, pos);
}

//der übergebene string wird in ein int-array umgewandelt; char als Zwischensschritt
//die nun im array pos[] stehenden werte sind die tatsächlichen Koordinaten im feld[8][8] array -> B3 ist nun 12
void umwandeln(string befehl, int pos[])
{
	bool falsch;
	int laenge = befehl.length() - 1;
	char array[laenge];
	strcpy(array, befehl.c_str());
	//seperate Umwandlung der Zahlen und Groß-/Kleinbuchstaben
	for (int i = 0; i <= laenge; i++)
	{
		if (i == 1 || i == 3)
			pos[i] = array[i] - 49;
		else
		{
			if (array[i] >= 'A' && array[i] <= 'Z')
				pos[i] = array[i] - 65;
			else
				pos[i] = array[i] - 97;
		}
		if (pos[i] >= 8)
		{
			cout << "Koordinaten liegen außerhalb des Feldes" << endl;
			falsch = true;
			break;
		}
	}
}

//für jede Figur durchgehen aller möglichen Züge
//anschließend löschen derer, die außerhalb des Feldes liegen würden

void bewegen(char feld[8][8], int pos[])
{
	char figur = feld[pos[1]][pos[0]]; //Buchstaben vom Schachbrett lesen --> Figur
	int moglichkeiten[64][2];		   //zweidimensionales Feld zum Speichern aller möglichen Züge
									   //erste Dimension ist die jeweilige Möglichkeitsnummer, die zweite die Koordinaten davon
	for (int i = 0; i < 64; i++)
	{
		moglichkeiten[i][0] = 9;
		moglichkeiten[i][1] = 9;
	}
	switch (figur)
	{
	case 'K':							  //König weiß
		moglichkeiten[0][0] = pos[0] - 1; //ein feld nach oben
		moglichkeiten[0][1] = pos[1];
		moglichkeiten[1][0] = pos[0] + 1; //ein feld nach unten
		moglichkeiten[1][1] = pos[1];
		moglichkeiten[2][0] = pos[0]; //ein feld nach links
		moglichkeiten[2][1] = pos[1] - 1;
		moglichkeiten[3][0] = pos[0]; //ein feld nach rechts
		moglichkeiten[3][1] = pos[1] + 1;
		moglichkeiten[4][0] = pos[0] - 1; //diagonal hoch links
		moglichkeiten[4][1] = pos[1] - 1;
		moglichkeiten[5][0] = pos[0] - 1; //diagonal hoch rechts
		moglichkeiten[5][1] = pos[1] + 1;
		moglichkeiten[6][0] = pos[0] + 1; //diagonal runter links
		moglichkeiten[6][1] = pos[1] - 1;
		moglichkeiten[7][0] = pos[0] + 1; //diagonal runter rechts
		moglichkeiten[7][1] = pos[1] + 1;
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 'k':							  //König schwarz
		moglichkeiten[0][0] = pos[0] - 1; //ein feld nach oben
		moglichkeiten[0][1] = pos[1];
		moglichkeiten[1][0] = pos[0] + 1; //ein feld nach unten
		moglichkeiten[1][1] = pos[1];
		moglichkeiten[2][0] = pos[0]; //ein feld nach links
		moglichkeiten[2][1] = pos[1] - 1;
		moglichkeiten[3][0] = pos[0]; //ein feld nach rechts
		moglichkeiten[3][1] = pos[1] + 1;
		moglichkeiten[4][0] = pos[0] - 1; //diagonal hoch links
		moglichkeiten[4][1] = pos[1] - 1;
		moglichkeiten[5][0] = pos[0] - 1; //diagonal hoch rechts
		moglichkeiten[5][1] = pos[1] + 1;
		moglichkeiten[6][0] = pos[0] + 1; //diagonal runter links
		moglichkeiten[6][1] = pos[1] - 1;
		moglichkeiten[7][0] = pos[0] + 1; //diagonal runter rechts
		moglichkeiten[7][1] = pos[1] + 1;
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'S':							  //Springer weiß
		moglichkeiten[0][0] = pos[0] + 2; // Linie +2 Reihe +1
		moglichkeiten[0][1] = pos[1] + 1;
		moglichkeiten[1][0] = pos[0] + 1; // Linie +1 Reihe +2
		moglichkeiten[1][1] = pos[1] + 2;
		moglichkeiten[2][0] = pos[0] - 1; // Linie -1 Reihe +2
		moglichkeiten[2][1] = pos[1] + 2;
		moglichkeiten[3][0] = pos[0] - 2; // Linie -2 Reihe +1
		moglichkeiten[3][1] = pos[1] + 1;
		moglichkeiten[4][0] = pos[0] - 2; // Linie -2 Reihe -1
		moglichkeiten[4][1] = pos[1] - 1;
		moglichkeiten[5][0] = pos[0] - 1; // Linie -1 Reihe -2
		moglichkeiten[5][1] = pos[1] - 2;
		moglichkeiten[6][0] = pos[0] + 1; // Linie +1 Reihe -2
		moglichkeiten[6][1] = pos[1] - 2;
		moglichkeiten[7][0] = pos[0] + 2; // Linie +2 Reihe -1
		moglichkeiten[7][1] = pos[1] - 1;
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 's':							  //Springer schwarz
		moglichkeiten[0][0] = pos[0] + 2; // Linie +2 Reihe +1
		moglichkeiten[0][1] = pos[1] + 1;
		moglichkeiten[1][0] = pos[0] + 1; // Linie +1 Reihe +2
		moglichkeiten[1][1] = pos[1] + 2;
		moglichkeiten[2][0] = pos[0] - 1; // Linie -1 Reihe +2
		moglichkeiten[2][1] = pos[1] + 2;
		moglichkeiten[3][0] = pos[0] - 2; // Linie -2 Reihe +1
		moglichkeiten[3][1] = pos[1] + 1;
		moglichkeiten[4][0] = pos[0] - 2; // Linie -2 Reihe -1
		moglichkeiten[4][1] = pos[1] - 1;
		moglichkeiten[5][0] = pos[0] - 1; // Linie -1 Reihe -2
		moglichkeiten[5][1] = pos[1] - 2;
		moglichkeiten[6][0] = pos[0] + 1; // Linie +1 Reihe -2
		moglichkeiten[6][1] = pos[1] - 2;
		moglichkeiten[7][0] = pos[0] + 2; // Linie +2 Reihe -1
		moglichkeiten[7][1] = pos[1] - 1;
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'L': //Läufer weiß
		for (int i = -7; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] + i; //Diagonale: links oben <--> rechts unten
			moglichkeiten[i + 7][1] = pos[1] + i;
			moglichkeiten[i + 7 + 15][0] = pos[0] + i; //Diagonale: links unten <--> rechts oben
			moglichkeiten[i + 7 + 15][1] = pos[1] - i;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 'l': //Läufer schwarz
		for (int i = -7; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] + i; //Diagonale: links oben <--> rechts unten
			moglichkeiten[i + 7][1] = pos[1] + i;
			moglichkeiten[i + 7 + 15][0] = pos[0] + i; //Diagonale: links unten <--> rechts oben
			moglichkeiten[i + 7 + 15][1] = pos[1] - i;
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'T': //Turm weiß
		for (int i = -7; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] + i; //Linie: + und -
			moglichkeiten[i + 7][1] = pos[1];
			moglichkeiten[i + 7 + 15][0] = pos[0]; //Reihe: + und -
			moglichkeiten[i + 7 + 15][1] = pos[1] + i;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 't': //Turm schwarz
		for (int i = -7; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] + i; //Linie: + und -
			moglichkeiten[i + 7][1] = pos[1];
			moglichkeiten[i + 7 + 15][0] = pos[0]; //Reihe: + und -
			moglichkeiten[i + 7 + 15][1] = pos[1] + i;
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'D': //Dame weiß
		for (int i = -7; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] + i; //Diagonale: links oben <--> rechts unten
			moglichkeiten[i + 7][1] = pos[1] + i;
			moglichkeiten[i + 7 + 15][0] = pos[0] + i; //Diagonale: links unten <--> rechts oben
			moglichkeiten[i + 7 + 15][1] = pos[1] - i;
			moglichkeiten[i + 7 + 30][0] = pos[0] + i; //Linie: + und -
			moglichkeiten[i + 7 + 30][1] = pos[1];
			moglichkeiten[i + 7 + 45][0] = pos[0]; //Reihe: + und -
			moglichkeiten[i + 7 + 45][1] = pos[1] + i;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 'd': //Dame schwarz
		for (int i = -7; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] + i; //Diagonale: links oben <--> rechts unten
			moglichkeiten[i + 7][1] = pos[1] + i;
			moglichkeiten[i + 7 + 15][0] = pos[0] + i; //Diagonale: links unten <--> rechts oben
			moglichkeiten[i + 7 + 15][1] = pos[1] - i;
			moglichkeiten[i + 7 + 30][0] = pos[0] + i; //Linie: + und -
			moglichkeiten[i + 7 + 30][1] = pos[1];
			moglichkeiten[i + 7 + 45][0] = pos[0]; //Reihe: + und -
			moglichkeiten[i + 7 + 45][1] = pos[1] + i;
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'B':						  //Bauer weiß
		moglichkeiten[0][0] = pos[0]; //ein feld nach unten
		moglichkeiten[0][1] = pos[1] + 1;
		if (pos[1] == 1)
		{
			moglichkeiten[1][0] = pos[0]; //bei Startreihe zwei Felder
			moglichkeiten[1][1] = pos[1] + 2;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 'b':						  //Bauer schwarz
		moglichkeiten[0][0] = pos[0]; //ein feld nach oben
		moglichkeiten[0][1] = pos[1] - 1;
		if (pos[1] == 6)
		{
			moglichkeiten[1][0] = pos[0]; //bei Startreihe zwei Felder
			moglichkeiten[1][1] = pos[1] - 2;
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	}
}

//Aussortieren der Möglichkeiten, die außerhalb des Brettes liegen
//Aussortieren der Möglichkeiten, die von eigenen Figuren belegt sind
//ungültige Möglichkeiten werden mit einer 9 belegt, da 0 eine gültige Feldkoordinate wäre
void gultigesFeld(char feld[8][8], int moglichkeiten[64][2], bool schwarz)
{
	//PUSHED
	char belegt;
	for (int i = 0; i < 64; i++)
	{
		if (moglichkeiten[i][0] < 0 || moglichkeiten[i][0] > 7 || moglichkeiten[i][1] < 0 || moglichkeiten[i][1] > 7)
		{
			moglichkeiten[i][0] = 9;
			moglichkeiten[i][1] = 9;
		}

		if (moglichkeiten[i][0] != 9 && moglichkeiten[i][1] != 9)
			belegt = feld[moglichkeiten[i][1]][moglichkeiten[i][0]];

		if (schwarz == true)
		{
			if (belegt == 'd' || belegt == 't' || belegt == 'b' || belegt == 's' || belegt == 'l' || belegt == 'k')
			{
				moglichkeiten[i][0] = 9;
				moglichkeiten[i][1] = 9;
			}
		}
		else if (schwarz == false)
		{
			if (belegt == 'D' || belegt == 'T' || belegt == 'B' || belegt == 'S' || belegt == 'L' || belegt == 'K')
			{
				moglichkeiten[i][0] = 9;
				moglichkeiten[i][1] = 9;
			}
		}

		if (moglichkeiten[i][0] != 9 && moglichkeiten[i][1] != 9)
			cout << moglichkeiten[i][0] << moglichkeiten[i][1] << "  ";
	}
}