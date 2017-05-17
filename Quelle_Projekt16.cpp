#include <iostream>
using namespace std;

class cFahrrad {
private:
	int radzahl;
	double luftdruck;

public:
	cFahrrad(int rad_in = 2, double druck_in = 1.1) {
		radzahl = rad_in;
		luftdruck = druck_in;
	}

	int get_radzahl() {
		cout << "Radzahl: " << radzahl << endl;
		return radzahl;
	}

	double get_luftdruck() {
		cout << "Luftdruck: " << luftdruck << endl;
		return luftdruck;
	}

	double aufpumpen(double druckplus) {
		luftdruck += druckplus;

		if (luftdruck > 3.5) {
			luftdruck = 3.5;
		}

		return luftdruck;
	}

};

class cNutzrad : public cFahrrad{
private:
	double ertrag;

public:
	cNutzrad(int rad_in = 3, double druck_in = 2.2, double ertrag_in = 100.0) : cFahrrad(rad_in, druck_in) {
		ertrag = ertrag_in;
	}

	double kassieren(double einkommen) {
		ertrag += einkommen;
		return ertrag;
	}

	double wartungmachen(double kosten) {
		ertrag -= kosten;
		return ertrag;
	}

};

class cFreizeitrad : public cFahrrad {
private:
	double spass;

public:
	cFreizeitrad(int rad_in = 2, double druck_in = 3.3, double spass_in = 120.0) : cFahrrad(rad_in, druck_in) {
		spass = spass_in;
	}

	void abschliessen(bool disziplin) {
		if (disziplin == 1) {
			spass += 20;
		}

		else {
			spass = 0.0;
		}
	}

	double geniessen(double genuss) {
		spass += genuss;
		return spass;
	}

	double set_spass(double new_spass) {
		spass = new_spass;
		return spass;
	}

};

class cLieferdreirad : public cNutzrad {
private:
	double nutzlast;

public:
	cLieferdreirad(int rad_in = 3, double druck_in = 3.8, double ertrag_in = 380.0, double last_in = 72.50) : cNutzrad(rad_in, druck_in, ertrag_in) {
		nutzlast = last_in;
	}

	double zuladen(double lastplus) {
		nutzlast += lastplus;
		return nutzlast;
	}

	double abladen(double lastminus) {
		nutzlast -= lastminus;
		return nutzlast;
	}

};

class cRikscha : public cNutzrad{
private:
	int fahrgastzahl;

public:
	cRikscha(int rad_in = 4, double druck_in = 2.7, double ertrag_in = 620.0, int gast_in = 1) : cNutzrad(rad_in, druck_in, ertrag_in) {
		fahrgastzahl = gast_in;
	}

	int einsteigen(int rein) {
		fahrgastzahl += rein;

		if (fahrgastzahl > 7) {
			fahrgastzahl = 7;
		}

		return fahrgastzahl;

	}

	int aussteigen(int raus) {
		fahrgastzahl -= raus;

		if (fahrgastzahl < 0) {
			fahrgastzahl = 0;
		}

		return fahrgastzahl;

	}

};

class cMountainbike : public cFreizeitrad {
private:
	void schimpfen() {
		cout << "Schon wieder ein Stein, macht keinen Spass mehr." << endl;
	}

public:
	cMountainbike(int rad_in = 2, double druck_in = 1.3, double spass_in = 100.0) : cFreizeitrad(rad_in, druck_in, spass_in){}

	double downhill(int hoehendifferenz) {
		double help;

		if (hoehendifferenz < 0) {
			hoehendifferenz *= -1;
		}

		help = geniessen(0) + (10 * hoehendifferenz);
		set_spass(help);

		return help;
	}

	void steinschlag() {
		double help;
		help = geniessen(0) - 2000;

		if (help < 0) {
			help = 0;
		}

		set_spass(help);

		if (help == 0) {
			schimpfen();
		}

	}

};

class cEinrad : public cFreizeitrad {
private:


public:
	cEinrad(int rad_in = 1, double druck_in = 2.3, double spass_in = 200.0) : cFreizeitrad(rad_in, druck_in, spass_in){}

	double geniessen(double genuss) {
		double help;

		if (genuss < 0) {
			help = geniessen(0) + (genuss * 5);
		}

		else {
			help = geniessen(0) + (genuss * 20);
		}

		set_spass(help);

	}

};

int main() {
	cLieferdreirad hauruck;
	cRikscha einergehtnochrein;
	cMountainbike downhillstar;
	cEinrad obenbleiben;

	cout << "Radzahl des Lieferdreirads: " << hauruck.get_radzahl() << endl;
	cout << "Radzahl der Rikscha: " << einergehtnochrein.get_radzahl() << endl;
	cout << "Radzahl des Mountainbikes: " << downhillstar.get_radzahl() << endl;
	cout << "Radzahl des Einrads: " << obenbleiben.get_radzahl() << endl;
	cout << "Mountainbike nach 300 meter downhill, spass = "
		<< downhillstar.downhill(-300) << endl;
	cout << "Mountainbike bekommt einen Steinschlag" << endl;
	downhillstar.steinschlag();
	cout << "Mountainbike nach Steinschlag, spass = "
		<< downhillstar.downhill(0) << endl;
	cout << "Mountainbike bekommt einen Steinschlag" << endl;
	downhillstar.steinschlag();
	cout << "Mountainbike nach Steinschlag, spass = "
		<< downhillstar.downhill(0) << endl;
	cout << "Ende" << endl;

	return 0;
}