#include <iostream>
using namespace std;

class cBruch {
private:
	int zaehler;
	int nenner;

public:
	cBruch(int z_in = 0, int n_in = 1) {
		zaehler = z_in;
		nenner = n_in;

		if (nenner == 0) {
			nenner = 1;
		}

		else if (nenner < 0) {
			zaehler *= -1;
			nenner *= -1;
		}

	}

	void ausgabe() {
		cout << "Bruch: " << zaehler << "/" << nenner << endl;
		cout << "Gleitkommazahl: " << (double)zaehler / (double)nenner << endl;
	}

	void kuerzen() {

		if (nenner == 0) {
			nenner = 1;
		}

		else if (nenner < 0) {
			zaehler *= -1;
			nenner *= -1;
		}

		for (int i = 2; i < nenner; i++) {
			if (zaehler % i == nenner % i) {
				zaehler /= i;
				nenner /= i;
			}
		}
	}

	friend cBruch operator + (cBruch b1, cBruch b2);
	friend cBruch operator - (cBruch b1, cBruch b2);
	friend cBruch operator * (cBruch b1, cBruch b2);
	friend cBruch operator / (cBruch b1, cBruch b2);
	friend bool operator < (cBruch b1, cBruch b2);
	friend bool operator > (cBruch b1, cBruch b2);
	friend bool operator == (cBruch b1, cBruch b2);
	friend void tausch(cBruch &b1, cBruch &b2);

};

int main() {
	cBruch helpme;	
	cBruch cBArr[8] = {
		cBruch(3, 4),
		cBruch(24, -6),
		cBruch(5, 3),
		cBruch(-8, 13),
		cBruch(21, 57),
		cBruch(7, -11),
		cBruch(2, 3)
	};

	for (int i = 0; i < 8; i++) {
		cBArr[i].ausgabe();
	}

	helpme = cBArr[0] + cBArr[1];
	helpme.ausgabe();

	helpme = cBArr[2] - cBArr[3];
	helpme.ausgabe();

	helpme = cBArr[4] * cBArr[5];
	helpme.ausgabe();

	helpme = cBArr[6] / cBArr[7];
	helpme.ausgabe();

	for (int n = 8; n > 1; n--) {
		for (int i = 0; i < n - 1; i++) {
			if (cBArr[i] > cBArr[i + 1]) {
				tausch(cBArr[i], cBArr[i + 1]);
			}
		}
	}	for (int i = 0; i < 8; i++) {
		cBArr[i].ausgabe();
	}
	return 0;
}

cBruch operator + (cBruch b1, cBruch b2) {
	cBruch summe;

	summe.zaehler = (b1.zaehler * b2.nenner) + (b2.zaehler * b1.nenner);
	summe.nenner = b1.nenner * b2.nenner;

	summe.kuerzen();

	return summe;
}

cBruch operator - (cBruch b1, cBruch b2) {
	cBruch differenz;

	differenz.zaehler = (b1.zaehler * b2.nenner) - (b2.zaehler * b1.nenner);
	differenz.nenner = b1.nenner * b2.nenner;

	differenz.kuerzen();
	return differenz;
}

cBruch operator * (cBruch b1, cBruch b2) {
	cBruch produkt;

	produkt.zaehler = b1.zaehler * b2.zaehler;
	produkt.nenner = b1.nenner * b2.nenner;

	produkt.kuerzen();
	return produkt;
}

cBruch operator / (cBruch b1, cBruch b2) {
	cBruch quotient;

	quotient.zaehler = b1.zaehler * b2.nenner;
	quotient.nenner = b1.nenner * b2.zaehler;

	quotient.kuerzen();
	return quotient;
}

bool operator < (cBruch b1, cBruch b2) {
	if ((b1.zaehler / b1.nenner) < (b2.zaehler / b2.nenner)) {
		return true;
	}

	else {
		return false;
	}
}

bool operator > (cBruch b1, cBruch b2) {
	if ((b1.zaehler / b1.nenner) > (b2.zaehler / b2.nenner)) {
		return true;
	}

	else {
		return false;
	}
}

bool operator == (cBruch b1, cBruch b2) {
	if ((b1.zaehler / b1.nenner) == (b2.zaehler / b2.nenner)) {
		return true;
	}

	else {
		return false;
	}
}

void tausch(cBruch &b1, cBruch &b2) {
	cBruch help;

	help = b1;
	b1 = b2;
	b2 = help;
}