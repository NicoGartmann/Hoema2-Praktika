#pragma once
#ifndef _CMYMATRIX_H
#define _CMYMATRIX_H
#include <string>
#include <vector>
#include "CMyVektor.h"
using namespace std;
class CMyMatrix {

private:

	int zeilen = 0;
	int spalten = 0;
	vector< vector<double> > matrix;


public:

	CMyMatrix();
	CMyMatrix(int pZeilen, int pSpalten) {
		this->matrix.resize(pSpalten);
		zeilen = pZeilen;
		spalten = pSpalten;
		for (int i = 0; i < pSpalten; i++) {
			this->matrix[i].resize(pZeilen);
		}
	};

	void setData(double pData, int pSpalte, int pZeile);
	double getData(int pSpalte, int pZeile);
	CMyMatrix inverse();
	double det();
	CMyVektor operator*(CMyVektor a);
	CMyMatrix operator*(double a);
	CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
	void newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));

};
#endif