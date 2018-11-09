#include "CMyVektor.h"
#include <cmath>
#include <iostream>
using namespace std;

int CMyVektor::getDimension() {
	return this->dimension;
}

void CMyVektor::setKomp(double wert, int pos) {
	this->vec.at(pos) = wert;
}

double CMyVektor::getKomp(int pos) {
	return this->vec.at(pos);
}

double CMyVektor::getLength() {
	double speicher = 0;
	for (int i = 0; i < this->dimension; i++) {
		speicher += this->vec.at(i) * this->vec.at(i);
	}
	return sqrt(speicher);
}

CMyVektor CMyVektor::operator+(CMyVektor a) {

	CMyVektor neu(this->dimension);

	for (int i = 0; i < this->dimension; i++)
	{
		neu.vec.at(i) = this->vec.at(i) + a.vec.at(i);
	}
	return neu;

}

CMyVektor CMyVektor::operator-(CMyVektor a) {

	CMyVektor neu(this->dimension);

	for (int i = 0; i < this->dimension; i++)
	{
		neu.vec.at(i) = this->vec.at(i) - a.vec.at(i);
	}
	return neu;

}

CMyVektor CMyVektor::operator+(double a) {

	CMyVektor neu(this->dimension);

	for (int i = 0; i < this->dimension; i++)
	{
		neu.vec.at(i) = this->vec.at(i) + a;
	}
	return neu;

}

CMyVektor CMyVektor::operator*(double lambda) {
	CMyVektor neu(this->dimension);

	for (int i = 0; i < this->dimension; i++)
	{
		neu.vec.at(i) = this->vec.at(i) * lambda;
	}
	return neu;
}

CMyVektor CMyVektor::operator/(double lambda) {
	CMyVektor neu(this->dimension);

	for (int i = 0; i < this->dimension; i++)
	{
		neu.vec.at(i) = this->vec.at(i) / lambda;
	}
	return neu;
}

CMyVektor CMyVektor::gradient(CMyVektor x, double(*funktion)(CMyVektor x)) {
	CMyVektor gradient(x.getDimension());
	double h = 1.0e-8;

	for (int i = 0; i < x.getDimension(); i++) {
		double speicher = 0;
		CMyVektor tmp = x;
		tmp.setKomp(x.getKomp(i) + h, i);

		speicher = ((*funktion) (tmp) - (*funktion) (x)) / h;
		gradient.setKomp(speicher, i);
	}
	return gradient;
}

void CMyVektor::maximieren(double(*funktion)(CMyVektor x), CMyVektor x, double lambda) {

	CMyVektor xneu(x.getDimension());
	CMyVektor xtest(x.getDimension());
	CMyVektor tmp(x.getDimension());

	int schritte = 0;

	while (schritte < 50 && gradient(x, (*funktion)).getLength() > 0.00001) {
		tmp = gradient(x, (*funktion));
		xneu = x + tmp * lambda;
		cout << endl;
		cout << endl;
		cout << "Schritt:" << schritte << endl;
		cout << "x = (";
		for (int i = 0; i < x.getDimension(); i++) {
			if (i != x.getDimension() - 1) {
				cout << x.getKomp(i) << ";";
			}
			else {
				cout << x.getKomp(i) << ")" << endl;
			}
		}
		cout << "lambda = " << lambda << endl;
		cout << "f(x) = " << (*funktion)(x) << endl;
		cout << "grad f(x) = (";

		for (int i = 0; i < tmp.getDimension(); i++) {
			if (i != tmp.getDimension() - 1) {
				cout << tmp.getKomp(i) << ";";
			}
			else {
				cout << tmp.getKomp(i) << ")" << endl;
			}
		}
		cout << "||grad f(x)|| = " << gradient(x, (*funktion)).getLength() << endl;
		cout << endl;
		cout << endl;
		cout << "x_neu = (";
		for (int i = 0; i < xneu.getDimension(); i++) {
			if (i != xneu.getDimension() - 1) {
				cout << xneu.getKomp(i) << ";";
			}
			else {
				cout << xneu.getKomp(i) << ")" << endl;
			}
		}
		cout << "f(x_neu) = " << (*funktion)(xneu) << endl;


		if ((*funktion) (xneu) > (*funktion) (x)) {

			xtest = x + tmp * (2 * lambda);
			cout << endl;
			cout << endl;
			cout << "Test mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl;
			cout << "x_test = (";
			for (int i = 0; i < xtest.getDimension(); i++) {
				if (i != xtest.getDimension() - 1) {
					cout << xtest.getKomp(i) << ";";
				}
				else {
					cout << xtest.getKomp(i) << ")" << endl;
				}
			}
			cout << "f(x_test) = " << (*funktion)(xtest) << endl;

			if ((*funktion) (xtest) >(*funktion) (xneu)) {
				x = xtest;
				lambda = 2 * lambda;
				cout << "Verdoppele Schrittweite!" << endl;
			}
			else {
				x = xneu;
			}
		}
		else if ((*funktion) (xneu) <= (*funktion) (x)) {
			cout << endl;
			cout << endl;


			while ((*funktion) (xneu) <= (*funktion) (x)) {
				lambda = lambda / 2;
				xneu = x + tmp * lambda;
			}
			x = xneu;
			cout << "x_neu = (";

			for (int i = 0; i < xneu.getDimension(); i++) {
				if (i != xneu.getDimension() - 1) {
					cout << xneu.getKomp(i) << ";";
				}
				else {
					cout << xneu.getKomp(i) << ")" << endl;
				}
			}
			cout << "f(x_neu) = " << (*funktion)(xneu) << endl;
		}
		schritte++;

	}
}
