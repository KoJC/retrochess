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
    const string bv = "\u2588";  //voller Block
    const string bo = "\u2580";  //Block obere Hälfte
    const string bu = "\u2584";  //Block untere Häfte
    const string dul = "\u2596"; //Punkt unten links
    const string dor = "\u259D"; //Punkt oben rechts

    cout << "						RETROSCHACH" << endl
         << bv << bo << bo << bo << bv << " "    << bv << bv << bv << bv << bv << endl
         << bv << "   " << bv << " "             << bv << bv << bv << bv << bv << endl
         << bv << "   " << bv << " "             << bv << bv << bv << bv << bv << endl
         << bv << "   " << bv << " "             << bv << bv << bv << bv << bv << endl
         << bv << bo << bo << bo << bo << " "    << bv << bv << bv << bv << bv << endl
         << bv << bu << dul << "   "               << bv << bv << bv << bv << bv << endl
         << bv << bo << bv << dul << "  "         << bv << bv << bv << bv << bv << endl
         << bv << " " << dor << bv << dul << " " << bv << bv << bv << bv << bv << endl
         << bv << "  " << dor << bv << " "       << bv << bv << bv << bv << bv << endl
         << endl
         << endl
         << "Willkommen zu dem etwas rustikalerem Schachspiel" << endl
         << "Zu den möglichen Befehlen und den SPielregeln siehe 'Hilfe'" << endl
         << "Die Befehlszeile und alle Menüpunkte stehen während des gesamten Programmablaufes zur Verfügung" << endl
         << "Folgende Menüpunkte sind verfügbar:\n         \n(0) Beenden         \n(1) Neues Spiel\n(2) Laden\n(3) Speichern\n(4) Hilfe " << endl;
    return;
}