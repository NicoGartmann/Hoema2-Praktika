#include <iostream>
#include <string>
#include <cmath>
#include "CMyVektor.h"
using namespace std;

double f(CMyVektor x);
double g(CMyVektor x);

int main() {

	int hilf;
	double hilf1;
	int eingabe = 0;
	double(*funktiong)(CMyVektor);
	funktiong = g;
	double(*funktionf)(CMyVektor);
	funktionf = f;

	cout << "Welche Dimension soll Vektor 1 haben?: ";
	cin >> hilf;

	CMyVektor vec1(hilf);

	cout << "Welche Dimension soll Vektor 2 haben?: ";
	cin >> hilf;

	CMyVektor vec2(hilf);

	do {
		cout << "1) Vektoren fuellen." << endl;
		cout << "2) Vektoren ausgeben" << endl;
		cout << "3) L�nge der Vektoren" << endl;
		cout << "4) Vektoren addieren" << endl;
		cout << "5) Vektor multiplizieren" << endl;
		cout << "6) Maximierung" << endl;
		cin >> eingabe;
		if (eingabe == 1) {
			cout << "Vektor 1:" << endl;
			for (int i = 0; i < vec1.getDimension(); i++)
			{
				cout << i + 1 << ". Komponente:";
				cin >> hilf1;
				vec1.setKomp(hilf1, i);
			}
			cout << "Vektor 2:" << endl;
			for (int i = 0; i < vec2.getDimension(); i++)
			{
				cout << i + 1 << ". Komponente:";
				cin >> hilf1;
				vec2.setKomp(hilf1, i);
			}
		}
		else if (eingabe == 2) {
			cout << "Vektor 1:" << endl;
			for (int i = 0; i < vec1.getDimension(); i++)
			{
				cout << vec1.getKomp(i) << endl;
			}
			cout << endl;
			cout << endl;
			cout << "Vektor 2:" << endl;
			for (int i = 0; i < vec2.getDimension(); i++)
			{
				cout << vec2.getKomp(i) << endl;
			}
		}
		else if (eingabe == 3) {
			cout << "Laenge Vektor 1:" << vec1.getLength() << endl;
			cout << "Laenge Vektor 2:" << vec2.getLength() << endl;
			cout << endl;
			cout << endl;
		}
		else if (eingabe == 4) {
			if (vec1.getDimension() == vec2.getDimension()) {
				CMyVektor tmp(vec1.getDimension());
				tmp = vec1 + vec2;
				cout << "Addition:" << endl;
				for (int i = 0; i < tmp.getDimension(); i++)
				{
					cout << tmp.getKomp(i) << endl;
				}
			}
			else {
				cout << "Dimensionen der Vektoren nicht gleich." << endl;
			}
		}
		else if (eingabe == 5) {
			int auswahl = 0;
			double tmp1;

			cout << "Multiplikation von:" << endl;
			cout << "1) Vektor 1" << endl;
			cout << "2) Vektor 2" << endl;
			cin >> auswahl;
			if (auswahl == 1) {
				CMyVektor tmp(vec1.getDimension());
				cout << "Vektor 1 * ?";
				cin >> tmp1;
				tmp = vec1 * tmp1;
				cout << "Multiplikation:" << endl;
				for (int i = 0; i < tmp.getDimension(); i++)
				{
					cout << tmp.getKomp(i) << endl;
				}
			}
			else {
				CMyVektor tmp(vec2.getDimension());
				cout << "Vektor 2 * ?";
				cin >> tmp1;
				tmp = vec1 * tmp1;
				cout << "Multiplikation:" << endl;
				for (int i = 0; i < tmp.getDimension(); i++)
				{
					cout << tmp.getKomp(i) << endl;
				}
			}
		}
		else if (eingabe == 6) {
			string func;
			cout << "Welche Funktion soll benutzt werden?: " << endl;
			cout << " f = sin(x + y^2) + y^3 - 6y^2 + 9y" << endl;
			cout << " g = -(2x^2 - 2xy + y^2 + z^2 - 2x - 4z" << endl;
			cin >> func;
			if (func == "f") {
				CMyVektor test(2);
				test.setKomp(3, 0);
				test.setKomp(2, 1);


				test.maximieren((*funktionf), test, 1.0);
			}
			else {
				CMyVektor test2(3);
				test2.setKomp(0, 0);
				test2.setKomp(0, 1);
				test2.setKomp(0, 2);


				test2.maximieren((*funktiong), test2, 0.1);
			}
		}

	} while (eingabe != 99);
	return 0;
}

double f(CMyVektor x) {
	return sin(x.getKomp(0) + pow(x.getKomp(1), 2)) + pow(x.getKomp(1), 3) - 6 * pow(x.getKomp(1), 2) + 9 * x.getKomp(1);

}
double g(CMyVektor x) {
	return -(2 * pow(x.getKomp(0), 2) - 2 * x.getKomp(0) * x.getKomp(1) + pow(x.getKomp(1), 2) + pow(x.getKomp(2), 2) - 2 * x.getKomp(0) - 4 * x.getKomp(2));
}
