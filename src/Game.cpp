#include "PreHeader.h"
#include "Game.h"

Game::Game()
{
	Daten = std::make_shared<Data>();

	//Gebaude
	BAZ = new Batillion_Ausbildungszentrum(Daten);

	Scoutbueros = new Scoutbuero(Daten);

	Traningzentren = new Traningszentrum(Daten);

	Zentrale = new Hauptquatier(Daten);

	Erholungsresorts = new Erholungsresort(Daten);

	//Auswahl
	AnzahlTage = 0;
	ImEinheitsAuswahlMenu = false;

	View = std::make_unique<View>(Daten);

	ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();
}

Game::~Game()
{
	delete BAZ;
	delete Scoutbueros;
	delete Traningzentren;
	delete Hauptquatier;
	delete Erholungsresorts;
}

void Game::spielLauft()
{
	while (View->getWindow().isOpen())
	{
		update();

		checkSortcuts();

		zeit();

		if (View->getWindow().isOpen())
		{
			//Daten->getAnimationen().Aktualisieren(View->getMousPos());	TODO UI Animation

			mahlen();
		}
	}
}

void Game::update()
{
	vMauspos = View->getMousPos();

	switch (AktuellesMenu)
	{

	case hauptmenu:
	{
		int temp = 1;
		//std::lock_guard<std::mutex> lock(mSicherung);
		for (int i = 0; i < 8; i++)
		{
			if (Daten->getHauptmenu(i).MausSchwebtDrueber(vMauspos))
			{
				if (Daten->getHauptmenu(i).getTextureGroessenSkalierungsFaktor()
						< 1.1)
				{
					Daten->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(
							Daten->getKacheln(i).getTextureGroessenSkalierungsFaktor()
									+ 0.01);
					Daten->getHauptmenu(i).setTexturePosition(
							sf::Vector2f(
									Daten->getKacheln(i).getTexturePosition().x
											- 1,
									Daten->getKacheln(i).getTexturePosition().y
											- 2));
				}

				if (Daten->getHauptmenu(i).wirdGedruedckt())
				{
					Daten->getHauptmenu(i).setKachel_Gedruecktfarbe();
					switch (Daten->getHauptmenu(i).getID())
					{
					case 1:
					{
						AktuellesMenu = zentrale;
					}
						break;
					case 2:
					{
						AktuellesMenu = batillionsausbildungsstate;
					}
						break;
					case 3:
					{
						AktuellesMenu = traningszentrum;
					}
						break;
					case 4:
					{
						AktuellesMenu = scoutbuero;
					}
						break;
					case 5:
					{
						AktuellesMenu = erholungsresort;
					}
						break;
					case 6:
					{
						AktuellesMenu = auftraege;
					}
						break;
					case 7:
					{
						AktuellesMenu = aauftraege;
					}
						break;
					case 8:
					{
						AktuellesMenu = logistikSystem;
					}
						break;
					default:
					{
						AktuellesMenu = hauptmenu;
					}
						break;
					}
				}
				else
					Daten->getHauptmenu(i).setKachel_Schwebefarbe();

			}
			else
			{
				Daten->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(1);
				Daten->getHauptmenu(i).setKachel_Hintergrundfarbe();
				if (i < 4)
					Daten->getHauptmenu(i).setTexturePosition(
							sf::Vector2f(
									i * Daten->getBreite() + (i + 1) * 20 + 15,
									70));

				else
				{
					Daten->getHauptmenu(i).setTexturePosition(
							sf::Vector2f(
									temp * Daten->getBreite() + (temp + 1) * 20
											+ 15, Daten->getHohe() + 90));
				}
			}

			if (i > 3)
				temp++;
		}
	}
		break;

	case zentrale:
	{

	}
		break;

	case batillionsausbildungsstate:
	{
		int temp = 0;
		temp = (Daten->getAnimationen().getKeineBenarichtigung()) ?
				99 : updateButtons(8, 4);
		switch (temp)
		// Bestimmen welcher Butten gedr�ckt wurde
		{
		case 1:
		{
			BAZ->beginneAufgabe();	//starten Gedr�kt
		}
			break;
		case 11:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->erhoheEinheitsGrosse();		//Anzahl Mitglieder wird erh�ht
		}
			break;
		case 12:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->reduziereEinheitsGrosse();	//Anzahl der Mitglieder wird gesengt
		}
			break;
		case 2:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->beschleunigungDerAufgabenDurchfuehrung();//Upgrade Geschwindikeit
		}
			break;
		case 3:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->erhohenDerGrundstarke();	 //Upgrade Grundst�rke
		}
			break;
		case 4:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->reduzierenDerAusfuhrungsKosten();//Upgrade zur kosten Reduzierung
		}
			break;
		case 5:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->vorbereiten_neueAusbildung();
		}
			break;
		default:
		{
			//TODO Fehlermeldung das etwas schiefgelaufen ist.
		}
			break;
		}
	}
		break;

	case scoutbuero:
	{
		int temp = 0;
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			temp = updateButtons(12, 4);
		}
		switch (temp)
		{
		case 1:
		{
			Scoutbueros->beginneAufgabe();				// Suche Starten
		}
			break;
		case 2:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->beschleunigungDerAufgabenDurchfuehrung();// Beschleunigt die Suche
		}
			break;
		case 3:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->erhohenDesMoeglichenRanges();// Erh�ht den mindest Rang
		}
			break;
		case 4:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->reduzierenDerAusfuhrungsKosten();// Reduzierung der Suchkosten
		}
			break;
		case 5:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->annehmenDerEinheit();					// Annehmen
		}
			break;
		case 6:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->ablehnenDerEinheit();					// Ablehnen
		}
			break;
		default:
		{
			//TODO Fehlermeldung das etwas schiefgelaufen ist.
		}
			break;
		}
	}
		break;

	case traningszentrum:
	{
		if (ImEinheitsAuswahlMenu)
		{
			auto temp = Traningzentren->updateAuswahl(vMauspos);
			if (temp.has_value())
			{
				Traningzentren->AuswahlZuOrdnen(temp.value());
				ImEinheitsAuswahlMenu = false;
			}
		}

		else
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			switch (updateButtons(16, 4))
			{
			case 2:
			{
				Traningzentren->beschleunigungDerAufgabenDurchfuehrung();
			}
				break;
			case 3:
			{
				Traningzentren->erhohenDerTraningsWirksamkeit();
			}
				break;
			case 4:
			{
				Traningzentren->reduzierenDerAusfuhrungsKosten();
			}
				break;
			case 5:
			{
				Traningzentren->langeTrainingsDauer();
				ImEinheitsAuswahlMenu = true;
			}
				break;
			case 6:
			{
				Traningzentren->kurzeTraningsDauer();
				ImEinheitsAuswahlMenu = true;
			}
				break;
			case 7:
			{
				Traningzentren->mittlereTrainingsDauer();
				ImEinheitsAuswahlMenu = true;
			}
				break;
			default:
			{
				//TODO Fehlermeldung das etwas schiefgelaufen ist.
			}
				break;
			}
		}
	}
		break;

	case erholungsresort:
	{
		if (ImEinheitsAuswahlMenu)
		{
			auto temp = Erholungsresorts->updateAuswahl();
			if (temp.has_value())
			{
				Erholungsresorts->AuswahlZuOrdnen(temp.value());
				ImEinheitsAuswahlMenu = false;
			}
		}

		else
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			switch (updateButtons(24, 4))
			{
			case 2:
			{
				Erholungsresorts->beschleunigungDerAufgabenDurchfuehrung();
			}
				break;
			case 3:
			{
				Erholungsresorts->erhohenDerTraningsWirksamkeit();
			}
				break;
			case 4:
			{
				Erholungsresorts->reduzierenDerAusfuhrungsKosten();
			}
				break;

			case 5:
			{
				Erholungsresorts->leeren();
				Erholungsresorts->sucheNachEinsetzbarenEinheiten();
				ImEinheitsAuswahlMenu = true;
			}
				break;
			default:
			{
				//TODO Fehlermeldung das etwas schiefgelaufen ist.
			}
				break;
			}
		}
	}
		break;
	default:
	{
		//TODO Fehlermeldung das etwas schiefgelaufen ist.
	}
		break;

	}
}

void Game::zeit()
{
	float delta_time
	{ std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::steady_clock::now() - ZeitpunktDesLetztenTages) };

	if (delta_time >= TagesDauer)
	{
		AnzahlTage++;

		BAZ->aktualisierenTimer();
		Scoutbueros->aktualisierenTimer();
		Traningzentren->aktualisierenTimer();
		Erholungsresorts->aktualisierenTimer();

		if (AnzahlTage % MONATS_DAUER == 0)
		{
			//Sold auszahlen
		}

		ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();
	}
}

void Game::mahlen()
{
	switch (AktuellesMenu)
	{
	case hauptmenu:
	{
		View->DrawHauptmenu(AnzahlTage);
	}
		break;
	case batillionsausbildungsstate:
	{
		View->DrawBAZ(AnzahlTage);
	}
		break;
	case scoutbuero:
	{
		View->DrawScoutbuero(AnzahlTage);
	}
		break;
	case traningszentrum:
	{
		if (!ImEinheitsAuswahlMenu)
			View->DrawTraningszentrum(AnzahlTage);
		else
			View->DrawDiffrent(*Traningzentren);
	}
		break;
	case erholungsresort:
	{
		if (!ImEinheitsAuswahlMenu)
			View->DrawErholungsresort(AnzahlTage);
		else
			View->DrawDiffrent(*Erholungsresorts);
	}
		break;
	default:
	{
		View->DrawNichtVerfuegbar();
	}
		break;
	}
}
