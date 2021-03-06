//damit der Compiler bei fopen() keinen Fehler anzeigt ("function unsafe")
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string.h>

using namespace std;

char zeichen;
FILE *fp;

//Speichern der aktuellen Positionen in einer txt Datei in dem ausgewählten Pfad
//Öffnen und ggf. Erstellen der txt Datei
//der Benutzer gibt noch den Namen der Datei an
//existiert diese bereits, wird abgefragt, ob sie überschrieben werden soll oder eine Datei mit anderem Namen angelegt werden soll
void speichern(char feld[8][8])
{
	char eingabe;
	string name, ort;

	cout << "Dateipfad des Speicherortes: ";
	cin >> ort;
	cout << "Name der Datei: ";
	cin >> name;
	ort += name;

	fp = fopen(ort.c_str(), "r");
	if (fp == NULL)
	{
		fp = fopen(ort.c_str(), "w");
		for (int a = 0; a < 8; a++)
		{
			for (int b = 0; b < 8; b++)
			{
				zeichen = feld[a][b];
				fputc(zeichen, fp);
			}
		}
		fclose(fp);
		cout << "Speichern erfolgreich"<<endl;
	}
	else
	{
		fclose(fp);
		cout << "Die Datei existiert bereits. Soll der Inhalt überschrieben werden?(j/n)";
		cin >> eingabe;

		if (eingabe == 'n')
			cout << "Speichern abgebrochen"<<endl;
		else if (eingabe == 'j')
		{
			fp = fopen(ort.c_str(), "w");
			for (int a = 0; a < 8; a++)
			{
				for (int b = 0; b < 8; b++)
				{
					zeichen = feld[a][b];
					fputc(zeichen, fp);
				}
			}
			fclose(fp);
			cout << "Speichern erfolgreich"<<endl;
		}
	}
}

//Auslesen der Positionen aus der gewählten Datei
//beim Auftreten eines Fehlers Ausgabe der Fehlermeldung
void laden(char feld[8][8])
{
	string eingabe;
	cout << "Bitte Dateipfad eingeben: ";
	cin >> eingabe;

	fp = fopen(eingabe.c_str(), "r");
	if (fp == NULL)
	{
		cout << "ungültiger Dateipfad!" << endl
			 << endl;
	}
	else
	{
		zeichen = fgetc(fp);
		int a = 0;
		int b = 0;
		while (zeichen != EOF)
		{
			feld[a][b] = zeichen;
			b++;
			if (b == 8)
			{
				a++;
				b = 0;
			}

			zeichen = fgetc(fp);
		}
		fclose(fp);
		cout << "Laden erfolgreich" << endl;
	}
}