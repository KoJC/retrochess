#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

void umwandeln(string befehl, int pos[]);
void bewegen(char feld[8][8], int pos[]);

void ziehen(char feld[8][8], string befehl)
{
    int pos[befehl.length() - 1];
    umwandeln(befehl, pos);
}

//der übergebene string wird in ein int-array umgewandelt; char als Zwischensschritt
//die nun im array pos[] stehenden werte sind die tatsächlichen Koordinaten im feld[8][8] array -> B3 ist nun 12
void umwandeln(string befehl, int pos[])
{
    int laenge = befehl.length() - 1;
    cout << "länge " << laenge << endl;
    char array[laenge];
    strcpy(array, befehl.c_str());
    //seperate Umwandlung der Zahlen und Groß-/Kleinbuchstaben
    for (int i = 0; i <= laenge; i++)
    {
        //if(array[i] >= '8' )
        if (i == 1 || i == 3)
            pos[i] = array[i] - 49;
        else
        {
            if (array[i] >= 'A' && array[i] <= 'Z')
                pos[i] = array[i] - 65;
            else
                pos[i] = array[i] - 97;
        }
    }
}

//für jede Figur durchgehen aller möglichen Züge
//anschließend löschen derer, die außerhalb des Feldes liegen würden

void bewegen(char feld[8][8], int pos[])
{   
    char figur = feld[pos[0]][pos[1]];
    int [64] moglichkeiten;
    switch (figur)
    {
    case 'B':
        break;
    case 'b':
        break;
    case 'K':
        moglichkeiten [0] = pos[0]-1; //ein feld nach oben
        for(int i=0;i<=sizeof(moglichkeiten);i++)
        {
            if(moglichkeiten[i]<0 || moglichkeiten[i]>7)
                moglichkeiten[i] = '\0';
        }
            break;
    }
}