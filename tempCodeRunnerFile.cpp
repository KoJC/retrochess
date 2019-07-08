
	int spieleralt = spieler;
	if (begonnen == true)
	{
		//Aufruf der bewegen_Funktion
		if (help != "")
		{
			ziehen(feld, help, spieleralt);
		}
		else if (zug != "")
		{
			spieler = ziehen(feld, zug, spieleralt);
			schachbrett(feld);
		}
	}
}
