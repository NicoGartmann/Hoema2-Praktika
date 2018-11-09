#pragma once
#ifndef _CKOMPLEX_H
#define _CKOMPLEX_H
#include <vector>
using namespace std;
class CKomplex
{

public:
	double real = 0;
	double imagi = 0;
	double phi = 0;
	bool polar = false;

public:
	CKomplex(double real, double im) {
		this->real = real;
		this->imagi = im;
		this->polar = false;
	}

	CKomplex(double phi) {
		this->phi = phi;
		this->polar = true;
	}

	CKomplex() {}

	double re();
	double im();
	CKomplex umwandeln();
	CKomplex operator+(CKomplex a);
	CKomplex operator*(CKomplex a);
	CKomplex operator+(double a);
	CKomplex operator*(double a);
	double abs();
	vector<CKomplex> werte_einlesen(string dateiname);
	void werte_ausgeben(string dateiname, vector<CKomplex> werte, double epsilon=-1);
	vector<CKomplex> fourier(vector<CKomplex> werte, bool hin);
	void abweichung(vector<CKomplex> orig, vector<CKomplex> stand, vector<CKomplex> e01, vector<CKomplex> e10);
};
#endif
