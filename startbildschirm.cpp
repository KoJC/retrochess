#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

//Ausgabe der txt Datei banner.txt
int startbildschirm() //lesen von txt
{
  char ch;

  ifstream in("banner.txt", ios::in | ios::binary);
  if (!in)
  {
    cout << "Datei konnte nicht geöffnet werden.\n";
    return 1;
  }

  while (in)
  { // in will be false when eof is reached
    in.get(ch);
    if (in)
      cout << ch;
  }

  in.close();
  
  cout << endl
       << "Willkommen zu dem etwas rustikalerem Schachspiel" << endl
       << "Zu den moeglichen Befehlen und den SPielregeln siehe 'Hilfe'" << endl
       << "Die Befehlszeile und alle Menuepunkte stehen während des gesamten Programmablaufes zur Verfuegung" << endl
       << "Folgende Menuepunkte sind verfuegbar:\n         \n(0) Beenden         \n(1) Neues Spiel\n(2) Laden\n(3) Speichern\n(4) Hilfe " << endl;

  return 0;
}