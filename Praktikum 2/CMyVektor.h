#pragma once
#ifndef _CMYVEKTOR_H
#define _CMYVEKTOR_H
#include <string>
#include <vector>
using namespace std;
class CMyVektor {

private:

	int dimension;
	vector<double> vec;

public:

	CMyVektor() {
		this->dimension = 0;
	}
	CMyVektor(int pDim) {
		this->dimension = pDim;
		this->vec.resize(pDim);
	}
	int getDimension();
	void setKomp(double wert, int pos);
	double getKomp(int pos);
	double getLength();
	CMyVektor operator+(CMyVektor a);
	CMyVektor operator-(CMyVektor a);
	CMyVektor operator+(double a);
	CMyVektor operator*(double lambda);
	CMyVektor operator/(double lambda);
	CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));
	void maximieren(double(*funktion)(CMyVektor x), CMyVektor x, double lambda = 1.0);
};
#endif