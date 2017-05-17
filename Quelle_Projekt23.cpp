#include <iostream>
using namespace std;

class cTransport {
private:
	double distanz;

public:
	cTransport(double d_in = 100.0) {
		distanz = d_in;
	}

	virtual double preis() = 0;
};

class cTransGew : public cTransport{
private:
	double gewicht;

public:
	cTransGew(double gew_in = 0.0, double d_in = 100.0) : cTransport(d_in) {
		gewicht = gew_in;
	}

	double preis() {
		cout << "Gewicht eingeben: ";
		cin >> gewicht;
		cout << endl;

		return gewicht * 1.65;
	}

};

class cTransVol : public cTransport {
private:
	double volumen;

public:
	cTransVol(double vol_in = 0.0, double d_in = 100.0) : cTransport(d_in) {
		volumen = vol_in;
	}

	double preis() {
		cout << "Volumen eingeben: ";
		cin >> volumen;
		cout << endl;

		return volumen * 1.09;
	}

};

class cTransLang : public cTransport {
private:
	double gewicht;
	double laenge;

public:
	cTransLang(double gew_in = 0.0, double laenge_in = 0.0, double d_in = 100.0) : cTransport(d_in) {
		gewicht = gew_in;
		laenge = laenge_in;
	}

	double preis() {
		cout << "Gewicht eingeben: ";
		cin >> gewicht;
		cout << endl << "Lange eingeben: ";
		cin >> laenge;
		cout << endl;

		if (laenge >= 14) {
			return gewicht * 1.28 * 1.4;
		}

		if (laenge >= 9) {
			return gewicht * 1.28 * 1.2;
		}

		if (laenge >= 5) {
			return gewicht * 1.28 * 1.1;
		}

		else {
			return gewicht * 1.28;
		}

	}

};

class cTransEil : public cTransport {
private:
	double gewicht;
	int tag;

public:
	cTransEil(double gew_in = 0.0, int tag_in = 1, double d_in = 100.0) : cTransport(d_in) {
		gewicht = gew_in;
		tag = tag_in;
	}

	double preis() {
		double eiligkeit;

		cout << "Gewicht eingeben: ";
		cin >> gewicht;
		cout << endl << "Eiligkeit eingeben (1 - 3): ";
		cin >> eiligkeit;
		cout << endl << "Wochentag eingeben (1: Montag - Donnerstag, 2: Freitag/Samstag, 3: Sonntag): ";
		cin >> tag;
		cout << endl;

		if (tag == 2) {
			return gewicht * 2.75 * eiligkeit * 1.7;
		}

		if (tag == 3) {
			return gewicht * 2.75 * eiligkeit * 2.2;
		}

		else {
			return gewicht * 2.75 * eiligkeit;
		}

	}

};

class cTransSchwer : public cTransGew {
private:


public:
	cTransSchwer(double gew_in = 0.0, double d_in = 100.0) : cTransGew(gew_in, d_in) {}

	double preis() {
		double gewicht;
		double breite;
		int aufwand;

		cout << "Gewicht eingeben: ";
		cin >> gewicht;
		cout << endl << "Breite eingeben (cm): ";
		cin >> breite;
		cout << endl << "Aufwand eingeben (1 - 4): ";
		cin >> aufwand;
		cout << endl;

		if (breite > 350) {
			breite -= 350;
			breite = (breite / 100) + 1;
		}

		else {
			breite = 1;
		}

		if (aufwand == 2) {
			return gewicht * 5.4 * 1.6 * breite;
		}

		else if (aufwand == 3) {
			return gewicht * 5.4 * 2.1 * breite;
		}

		else if (aufwand == 4) {
			return gewicht * 5.4 * 4.3 * breite;
		}

		else {
			return gewicht * 5.4 * breite;
		}

	}

};

int main() {
	double einnahmen = 0;
	cTransport * array[10];

	array[0] = new cTransGew;
	array[1] = new cTransVol;
	array[2] = new cTransLang;
	array[3] = new cTransEil;
	array[4] = new cTransSchwer;
	array[5] = new cTransGew;
	array[6] = new cTransVol;
	array[7] = new cTransLang;
	array[8] = new cTransEil;
	array[9] = new cTransSchwer;

	for (int i = 0; i < 10; i++) {
		einnahmen += 100 * (array[i]->preis());
	}

	cout << "Einnahmen gesamt: " << einnahmen << endl;

	for (int i = 0; i < 10; i++) {
		delete array[i];
	}

	return 0;
}