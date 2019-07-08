#include <stdio.h>
#include <iostream>
#include <string.h>
#include "bewegen.h"

using namespace std;
bool umwandeln(string befehl, int pos[]);
void bewegen(char feld[8][8], int pos[], int moglichkeiten[64][2]);
void gultigesFeld(char feld[8][8], int moglichkeiten[64][2], bool schwarz);
bool leerer_weg(char feld[8][8], int moglichkeiten[64][2], int i, int offset, bool schwarz);
bool schach(char feld[8][8], int pos[], int spieler);

int ziehen(char feld[8][8], string befehl, int spieler)
{
	bool gemoved;		 //Variable, ob ein gueltiger Zug ausgefuehrt wurde
	bool gultig = false; //Variable, ob die eigene Figur bewegt wurde
	bool schwarz = false;
	int moglichkeiten[64][2]; //zweidimensionales Feld zum Speichern aller möglichen Züge
							  //erste Dimension ist die jeweilige Möglichkeitsnummer, die zweite die Koordinaten davon
							  //ansonsten ist der Zug ungültig
	int pos[befehl.length() - 1];

	if (umwandeln(befehl, pos) == true)
	{
		char aktFigur = feld[pos[1]][pos[0]]; //Entscheidung, ob die Figur auch dem aktuellen Spieler gehört
		if (aktFigur - 97 >= 0)				  //aktuelle Figur = schwarz?
			schwarz = true;

		bewegen(feld, pos, moglichkeiten);

		if (befehl.length() == 4)
		{
			if (spieler % 2 == 0 && aktFigur - 97 < 0 || spieler % 2 != 0 && aktFigur - 97 >= 0)
			{
				for (int i = 0; i < 64; i++)
				{
					if (pos[2] == moglichkeiten[i][0] && pos[3] == moglichkeiten[i][1])
					{
						if (schach(feld, pos, spieler) == false)
						{
							gultig = true;
							spieler++;
						}
						gemoved = true;
					}
				}
				if (gemoved == false)
					cout << "Ungueltiger Zug" << endl;
			}
			else
			{
				cout << "Figuren des Gegenspielers duerfen nicht bewegt werden" << endl;
				gultig = false;
			}
		}

		else if (befehl.length() == 2)
		{
			int j = 1;
			cout << "Erlaubte Zielfelder sind folgende: " << endl;
			for (int i = 0; i < 64; i++)
			{
				if (moglichkeiten[i][0] != 9 && moglichkeiten[i][1] != 9)
					cout << j++ << ". " << (char)(moglichkeiten[i][0] + 65) << moglichkeiten[i][1] + 1 << endl;
			}
		}
	}
	return spieler;
}

//Funktion zum Erkennen einer Schach-Position des Königs
//zuerst auslesen der Position des Königs, dann durchgehen aller gegnerischen Figuren, ob sie ihn bedrohen
//ist der Spieler, dessen König dann bedroht wird, gerade am Zug, so wird dieser rückgängig gemacht und eine Meldung ausgegeben
//ist der Gegner am Zug, wird nur eine Meldung ausgegeben
bool schach(char feld[8][8], int pos[], int spieler)
{
	int figurpos[2];
	bool returnwert = false;
	int moglichkeiten[64][2];
	int w[2], s[2];					   //Positionen des Königs
	char figur = feld[pos[3]][pos[2]]; //alte Figur, die evtl. geschlagen wird
	feld[pos[3]][pos[2]] = feld[pos[1]][pos[0]];
	feld[pos[1]][pos[0]] = '0';

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (feld[i][j] == 'K')
			{
				w[0] = i;
				w[1] = j;
			}
			if (feld[i][j] == 'k')
			{
				s[0] = i;
				s[1] = j;
			}
		}
	}
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			figurpos[0] = j;
			figurpos[1] = i;
			if (feld[i][j] - 97 >= 0) //Überprüfung, ob es eine schwarze Figur ist
			{
				bewegen(feld, figurpos, moglichkeiten);
				gultigesFeld(feld, moglichkeiten, true);
				for (int k = 0; k < 64; k++) //kann sich diese in einem Zug auf das Feld des Königs bewegen?
				{
					if (w[0] == moglichkeiten[k][1] && w[1] == moglichkeiten[k][0] && spieler % 2 == 0) //weißer Spieler am Zug
					{
						feld[pos[1]][pos[0]] = feld[pos[3]][pos[2]];
						feld[pos[3]][pos[2]] = figur;
						cout << "Zug nicht moeglich, der weisse Koenig steht sonst im Schach" << endl;
						returnwert = true;
						break;
					}
					if ((w[0] == moglichkeiten[k][1] && w[1] == moglichkeiten[k][0] && spieler % 2 != 0))
					{
						cout << "Der weisse Koenig steht im Schach" << endl;
						break;
					}
				}
			}
			if (feld[i][j] - 97 < 0) //Überprüfung, ob es eine weiße Figur ist
			{
				bewegen(feld, figurpos, moglichkeiten);
				gultigesFeld(feld, moglichkeiten, false);
				for (int k = 0; k < 64; k++) //kann sich diese in einem Zug auf das Feld des Königs bewegen?
				{
					if (s[0] == moglichkeiten[k][1] && s[1] == moglichkeiten[k][0] && spieler % 2 != 0) //schwarzer Spieler am Zug
					{
						feld[pos[1]][pos[0]] = feld[pos[3]][pos[2]];
						feld[pos[3]][pos[2]] = figur;
						cout << "Zug nicht moeglich, der schwarze Koenig steht sonst im Schach" << endl;
						returnwert = true;
						break;
					}
					if ((s[0] == moglichkeiten[k][1] && s[1] == moglichkeiten[k][0] && spieler % 2 == 0))
					{
						cout << "Der schwarze Koenig steht im Schach" << endl;
						break;
					}
				}
			}
		}
	}
	return returnwert;
}

//der übergebene string wird in ein int-array umgewandelt; char als Zwischensschritt
//die nun im array pos[] stehenden werte sind die tatsächlichen Koordinaten im feld[8][8] array -> B3 ist nun 12
bool umwandeln(string befehl, int pos[])
{
	bool returnwert = true;
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
			returnwert = false;
			break;
		}
	}
	return returnwert;
}

//Aussortieren der Möglichkeiten, die außerhalb des Brettes liegen
//Aussortieren der Möglichkeiten, die von eigenen Figuren belegt sind
//-> Es kommt zu einer Dopplung dieser Überprüfung bei Figuren, bei denen sowohl 'gultigesFeld' als auch 'leererWeg' aufgerufen wird
//-> wird bewusst in Kauf genommen, da Springer, Bauer und König ebenfalls darauf überprüft werden müssen und keine extra Funktion für diese
//-> geschrieben werden soll
//ungültige Möglichkeiten werden mit einer 9 belegt, da 0 eine gültige Feldkoordinate wäre
void gultigesFeld(char feld[8][8], int moglichkeiten[64][2], bool schwarz)
{
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
	}
}

//für jede Figur durchgehen aller möglichen Züge
//zur Überprüfung, ob sich eine Figur zwischen Start und Ziel befindet
//jede Figur muss dabei einzeln behandelt werden, da sich deren Bewegungsmuster unterscheiden
void bewegen(char feld[8][8], int pos[], int moglichkeiten[64][2])
{
	char figur = feld[pos[1]][pos[0]]; //Buchstaben vom Schachbrett lesen --> Figur
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
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i][0] = pos[0] + i; //Linie: +
			moglichkeiten[i][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 0, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 7][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 7, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 15][0] = pos[0] + i; //Reihe: +
			moglichkeiten[i + 15][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 15, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 23][0] = pos[0] - i; //Reihe -
			moglichkeiten[i + 23][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 23, false) == true)
				break;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 'l': //Läufer schwarz
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i][0] = pos[0] + i; //Linie: +
			moglichkeiten[i][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 0, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 7][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 7, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 15][0] = pos[0] + i; //Reihe: +
			moglichkeiten[i + 15][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 15, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 23][0] = pos[0] - i; //Reihe -
			moglichkeiten[i + 23][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 23, true) == true)
				break;
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'T': //Turm weiß
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i][0] = pos[0] + i; //Linie: +
			moglichkeiten[i][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 0, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 7][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 7, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 15][0] = pos[0]; //Reihe: +
			moglichkeiten[i + 15][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 15, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 23][0] = pos[0]; //Reihe -
			moglichkeiten[i + 23][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 23, false) == true)
				break;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 't': //Turm schwarz
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i][0] = pos[0] + i; //Linie: +
			moglichkeiten[i][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 0, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 7][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 7, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 15][0] = pos[0]; //Reihe: +
			moglichkeiten[i + 15][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 15, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 23][0] = pos[0]; //Reihe -
			moglichkeiten[i + 23][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 23, true) == true)
				break;
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	case 'D': //Dame weiß
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i][0] = pos[0] + i; //Linie: +
			moglichkeiten[i][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 0, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 7][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 7, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 15][0] = pos[0] + i; //Reihe: +
			moglichkeiten[i + 15][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 15, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 23][0] = pos[0] - i; //Reihe -
			moglichkeiten[i + 23][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 23, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 31][0] = pos[0] + i; //Linie: +
			moglichkeiten[i + 31][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 31, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 39][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 39][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 39, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 47][0] = pos[0]; //Reihe: +
			moglichkeiten[i + 47][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 47, false) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 55][0] = pos[0]; //Reihe -
			moglichkeiten[i + 55][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 55, false) == true)
				break;
		}
		gultigesFeld(feld, moglichkeiten, false);
		break;
	case 'd': //Dame schwarz
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i][0] = pos[0] + i; //Linie: +
			moglichkeiten[i][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 0, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 7][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 7][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 7, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 15][0] = pos[0] + i; //Reihe: +
			moglichkeiten[i + 15][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 15, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 23][0] = pos[0] - i; //Reihe -
			moglichkeiten[i + 23][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 23, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 31][0] = pos[0] + i; //Linie: +
			moglichkeiten[i + 31][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 31, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 39][0] = pos[0] - i; //Linie -
			moglichkeiten[i + 39][1] = pos[1];
			if (leerer_weg(feld, moglichkeiten, i, 39, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 47][0] = pos[0]; //Reihe: +
			moglichkeiten[i + 47][1] = pos[1] + i;
			if (leerer_weg(feld, moglichkeiten, i, 47, true) == true)
				break;
		}
		for (int i = 1; i <= 7; i++)
		{
			moglichkeiten[i + 55][0] = pos[0]; //Reihe -
			moglichkeiten[i + 55][1] = pos[1] - i;
			if (leerer_weg(feld, moglichkeiten, i, 55, true) == true)
				break;
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
			if (feld[moglichkeiten[0][1]][moglichkeiten[0][0]] != '0')
			{
				moglichkeiten[1][0] = 9; //bei Startreihe zwei Felder
				moglichkeiten[1][1] = 9;
			}
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
			if (feld[moglichkeiten[0][1]][moglichkeiten[0][0]] != '0')
			{
				moglichkeiten[1][0] = 9; //bei Startreihe zwei Felder
				moglichkeiten[1][1] = 9;
			}
		}
		gultigesFeld(feld, moglichkeiten, true);
		break;
	}
}

//Aussortieren der Möglichkeiten für Figuren, bei denen die Felder zwischen Start und Ziel frei sein müssen
//ist das Ziel mit einer eigenen Figur belegt, so ist das zuvor überprüfte Feld das letzte Ziel
//ist das Ziel mit einer gegnerischen Figur belegt, so ist dieses Feld das letzte Ziel -> in diesem Fall schlagen der gegnerischen Figur
//die 'besetzt'-Variable überprüfen, welche Figur auf dem aktuellen Feld steht
bool leerer_weg(char feld[8][8], int moglichkeiten[64][2], int i, int offset, bool schwarz)
{
	char besetzt;
	bool returnwert = false;
	besetzt = feld[moglichkeiten[i + offset][1]][moglichkeiten[i + offset][0]];
	if (schwarz == false)
	{
		if (besetzt == 'b' || besetzt == 'k' || besetzt == 'd' || besetzt == 't' || besetzt == 'l' || besetzt == 's')
			returnwert = true;

		else if (besetzt == 'B' || besetzt == 'K' || besetzt == 'D' || besetzt == 'T' || besetzt == 'L' || besetzt == 'S')
		{
			moglichkeiten[i + offset][0] = 9;
			moglichkeiten[i + offset][1] = 9;
			returnwert = true;
		}
	}
	if (schwarz == true)
	{
		if (besetzt == 'B' || besetzt == 'K' || besetzt == 'D' || besetzt == 'T' || besetzt == 'L' || besetzt == 'S')
			returnwert = true;

		else if (besetzt == 'b' || besetzt == 'k' || besetzt == 'd' || besetzt == 't' || besetzt == 'l' || besetzt == 's')
		{
			moglichkeiten[i + offset][0] = 9;
			moglichkeiten[i + offset][1] = 9;
			returnwert = true;
		}
	}
	return returnwert;
}