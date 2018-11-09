#include "CKomplex.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

double CKomplex::re() {
  return this->real;
}

double CKomplex::im() {
  return this->imagi;
}

CKomplex CKomplex::umwandeln() {
	CKomplex res;
	res.real = cos(this->phi);
	res.imagi = sin(this->phi);
  
	res.polar = false;
	return res;
}

CKomplex CKomplex::operator+(CKomplex a) {
  CKomplex res;
  CKomplex hilf;
  hilf.real = this->real;
  hilf.imagi = this->imagi;
  if(this->polar == true) {
    hilf = this->umwandeln();
  }
  if(a.polar == true) {
    a = a.umwandeln();
  }
  res.real = hilf.real + a.real;
  res.imagi = hilf.imagi + a.imagi;
  res.polar = false;
  return res;
}

CKomplex CKomplex::operator*(CKomplex a) {
  CKomplex res;
  CKomplex hilf;
  hilf.real = this->real;
  hilf.imagi = this->imagi;
  if (this->polar) {
	  hilf = this->umwandeln();
  }
  if(a.polar) {
    a = a.umwandeln();
  }

  res.real = (hilf.real * a.real) - (hilf.imagi * a.imagi);
  res.imagi = (hilf.real * a.imagi) + (hilf.imagi * a.real);
  res.polar = false;
  return res;
}

CKomplex CKomplex::operator+(double a) {
  CKomplex res;
  CKomplex hilf;
  hilf.real = this->real;
  hilf.imagi = this->imagi;
  if (this->polar) {
	  hilf = this->umwandeln();
  }
  res.real = hilf.real + a;
  res.imagi = hilf.imagi;
  res.polar = false;
  return res;
}

CKomplex CKomplex::operator*(double a) {
  CKomplex res;
  CKomplex hilf;
  hilf.real = this->real;
  hilf.imagi = this->imagi;
  if (this->polar) {
	  hilf = this->umwandeln();
  }
  res.real = hilf.real * a;
  res.imagi = hilf.imagi * a;
  res.polar = false;
  return res;
}

double CKomplex::abs() {
	CKomplex hilf;
	hilf.real = this->real;
	hilf.imagi = this->imagi;
	if (this->polar) {
		hilf = this->umwandeln();
	}
  return sqrt(pow(hilf.real,2)+pow(hilf.imagi,2));
}



vector<CKomplex> CKomplex::werte_einlesen(string dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
		// File oeffnen
	ifstream fp;
	fp.open(dateiname);
		// Dimension einlesen
	fp >> N;
		// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0.0,0.0);
	for (i = 0; i<N; i++)
		werte[i] = null;
		// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re,im);
		werte[idx] = a;
	}
		// File schliessen
	fp.close();

	return werte;
}

void CKomplex::werte_ausgeben(string dateiname, vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
		// File oeffnen
	ofstream fp;
	fp.open(dateiname);
		// Dimension in das File schreiben
	fp << N << endl;
		// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
		// File schliessen
	fp.close();
}


vector<CKomplex> CKomplex::fourier(vector<CKomplex> werte, bool hin) {

  int N = werte.size();
  const double PI = 3.141592653589793238463;
  
  vector<CKomplex> result;
  result.resize(N);
  
  if (hin == true) {

	  for (int n = 0; n < N; n++) {
		  CKomplex summe, zwischen;
		  for (int k = 0; k < N; k++) {
			 CKomplex e(-(2 * PI *k*n)/N);
			 zwischen =  e * werte[k].re();
			 summe = summe + zwischen;
			}
		  result[n] = summe * (1.0 / sqrt((double)N));
		}
  }else{

	  for (int k = 0; k < N; k++) {
		  CKomplex summe, zwischen;
		  for (int n = 0; n < N; n++) {
			  CKomplex e((2 * PI*k*n) / N);
			  zwischen = werte[n] * e;
			  summe = summe + zwischen;
		  }
		  result[k] = summe * (1.0 / sqrt((double)N));
	  }
  }
  
  return result;
}

void CKomplex::abweichung(vector<CKomplex> orig, vector<CKomplex> stand, vector<CKomplex> e01, vector<CKomplex> e10) {

	double tmp,record;
	tmp = 0;
	record = 0;
	for (int i = 0; i < orig.size(); i++)
	{
		tmp = orig[i].re() - stand[i].re();
		if (tmp < 0)
			tmp = tmp * (-1);
		if (tmp > record)
			record = tmp;

	}
	cout << "Maximale Abweichung bei Standard-Epsilon: " << record << endl;

	tmp = 0;
	record = 0;
	for (int i = 0; i < orig.size(); i++)
	{
		tmp = orig[i].re() - e01[i].re();
		if (tmp < 0)
			tmp = tmp * (-1);
		if (tmp > record)
			record = tmp;

	}
	cout << "Maximale Abweichung bei epsilon=0.1: " << record << endl;

	tmp = 0;
	record = 0;
	for (int i = 0; i < orig.size(); i++)
	{
		tmp = orig[i].re() - e10[i].re();
		if (tmp < 0)
			tmp = tmp * (-1);
		if (tmp > record)
			record = tmp;

	}
	cout << "Maximale Abweichung bei epsilon=1.0: " << record << endl;
}