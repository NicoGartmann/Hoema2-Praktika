#include "CMyMatrix.h"
#include <cmath>
#include <iostream>
#include "CMyVektor.h"
using namespace std;

void CMyMatrix::setData(double pData, int pSpalte, int pZeile) {
	this->matrix[pSpalte][pZeile] = pData;
}

double CMyMatrix::getData(int pSpalte, int pZeile) {
	return this->matrix[pSpalte][pZeile];
}

double CMyMatrix::det() {
	if (this->zeilen == 2 && this->spalten == 2) {
		double result;
		result = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
		return result;
	}
	else {
		cout << "Matrix ist nicht 2x2 groß." << '\n';
	}
}

CMyMatrix CMyMatrix::inverse() {
	if (this->zeilen == 2 && this->spalten == 2) {
		CMyMatrix result(2, 2);
		double bruch;
		bruch = 1 / this->det();
		result.matrix[0][0] = this->matrix[1][1];
		result.matrix[1][0] = -this->matrix[1][0];
		result.matrix[0][1] = -this->matrix[0][1];
		result.matrix[1][1] = this->matrix[0][0];

		result = result * bruch;
		return result;
	}
	else {
		cout << "Matrix ist nicht 2x2 groß." << '\n';
	}
}

CMyMatrix CMyMatrix::operator*(double a) {
	CMyMatrix neu(this->zeilen, this->spalten);
	for (int i = 0; i < this->zeilen; i++) {
		for (int j = 0; j < this->spalten; j++) {
			neu.matrix[j][i] = this->matrix[j][i] * a;
		}
	}
	return neu;
}

CMyVektor CMyMatrix::operator*(CMyVektor a) {
	CMyVektor neu(this->zeilen);
	if (this->spalten == a.getDimension()) {

		double tmp;
		for (int i = 0; i < this->zeilen; i++) {
			tmp = 0.0;
			for (int j = 0; j < this->spalten; j++) {
				tmp += this->matrix[j][i] * a.getKomp(j);
			}
			neu.setKomp(tmp, i);
		}
		return neu;
	}
	else {
		cout << "Matrix Spalten und Vektor Dimension sind nicht gleich." << '\n';
	}
}

CMyMatrix CMyMatrix::jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x)) {
	CMyVektor xh = x;
	CMyMatrix jacobi(2, 2);
	CMyVektor speicher(2);
	double h = 0.0001;
	for (int zei = 0; zei < 2; zei++) {
		xh = x;
		xh.setKomp(x.getKomp(zei) + h, zei);
		speicher = ((*funktion)(xh) - (*funktion)(x)) / h;
		for (int i = 0; i < 2; i++) {
			jacobi.setData(speicher.getKomp(i), zei, i);
		}
	}
	return jacobi;
}


void CMyMatrix::newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x)) {
	CMyVektor xalt = x;
	CMyVektor xneu(x.getDimension());
	CMyVektor fx(x.getDimension());
	CMyVektor dx(x.getDimension());
	int schritte = 0;
	CMyMatrix jac(x.getDimension(), x.getDimension());
	CMyMatrix jacinv(x.getDimension(), x.getDimension());
	double laenge = (*funktion)(x).getLength();
	while (schritte < 50 && laenge > 1e-5) {
		cout << "Schritt: " << schritte << endl;
		cout << "x = (" << xalt.getKomp(0) << " ; " << xalt.getKomp(1) << ")" << endl;
		fx = (*funktion)(xalt);
		cout << "f(x) = (" << fx.getKomp(0) << " ; " << fx.getKomp(1) << ")" << endl;
		jac = jac.jacobi(xalt, (*funktion));
		cout << "f'(x) = (" << jac.getData(0, 0) << " ; " << jac.getData(1, 0) << " ; " << jac.getData(0, 1) << " ; " << jac.getData(1, 1) << " )" << endl;
		jacinv = jac.inverse();
		cout << "f'(x)^-1 = (" << jacinv.getData(0, 0) << " ; " << jacinv.getData(1, 0) << " ; " << jacinv.getData(0, 1) << " ; " << jacinv.getData(1, 1) << " )" << endl;
		dx = jacinv * fx;
		cout << "d(x) = (" << dx.getKomp(0) << " ; " << dx.getKomp(1) << ")" << endl;
		xneu = xalt - dx;
		laenge = fx.getLength();
		cout << "||f(x)|| = " << laenge << endl;
		xalt = xneu;
		schritte++;

	}
	if (schritte >= 50) {
		cout << "Ende wegen Schritte = " << schritte << endl;
	}
	else {
		cout << "Ende wegen ||f(x)||<1e-5 bei" << endl;
	}
	cout << "x = (" << xalt.getKomp(0) << " ; " << xalt.getKomp(1) << ")" << endl;
	cout << "f(x) = (" << fx.getKomp(0) << " ; " << fx.getKomp(1) << ")" << endl;
	cout << "||f(x)|| = " << laenge << endl;
}