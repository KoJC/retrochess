#include <stdio.h>
#include <iostream>
#include <string.h>
//#include "startbildschirm.h"

//um den Buffer von cin() zu flushen nach Funktionen, die cin() benutzt haben
//sonst wird Eintrag im Buffer in die Befehlszeile übernommen, was diese mit "ungültiger Eingabe" ausweist
#include <limits>
using namespace std;

#include "header.h"

void startbildschirm()
{
const string rechteck = "\u2580";  
 
    cout << "						RRETROSCHACH" << endl       
         << rechteck << endl
         << rechteck << endl
         << rechteck << endl
         << rechteck << endl
         << rechteck << endl
         << rechteck << endl
         << endl
         << endl
         << "Willkommen zu dem etwas rustikalerem Schachspiel" << endl
         << "Zu den möglichen Befehlen und den SPielregeln siehe 'Hilfe'" << endl
         << "Die Befehlszeile und alle Menüpunkte stehen während des gesamten Programmablaufes zur Verfügung" << endl
         << "Folgende Menüpunkte sind verfügbar:\n         \n(0) Beenden         \n(1) Neues Spiel\n(2) Laden\n(3) Speichern\n(4) Hilfe " << endl;
        return;
}