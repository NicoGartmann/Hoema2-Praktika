#include <iostream>
#include <string>
#include "CMyVektor.h"
#include "CMyMatrix.h"
using namespace std;

double f(CMyVektor x);
double g(CMyVektor x);
CMyVektor h(CMyVektor x);

int main() {

	int hilf;
	double hilf1;
	int eingabe = 0;
	double(*funktiong)(CMyVektor);
	funktiong = g;
	double(*funktionf)(CMyVektor);
	funktionf = f;
	CMyVektor(*funktionh)(CMyVektor);
	funktionh = h;


	CMyVektor test(2);
	test.setKomp(1.0, 0);
	test.setKomp(1.0, 1);

	CMyMatrix jac(2, 2);
	jac.setData(0, 0, 0);
	jac.setData(0, 1, 0);
	jac.setData(0, 0, 1);
	jac.setData(0, 1, 1);
	jac.newton(test, (*funktionh));

	system("pause");



	
	return 0;
}

double f(CMyVektor x) {
	return sin(x.getKomp(0) + pow(x.getKomp(1), 2)) + pow(x.getKomp(1), 3) - 6 * pow(x.getKomp(1), 2) + 9 * x.getKomp(1);

}
double g(CMyVektor x) {
	return -(2 * pow(x.getKomp(0), 2) - 2 * x.getKomp(0) * x.getKomp(1) + pow(x.getKomp(1), 2) + pow(x.getKomp(2), 2) - 2 * x.getKomp(0) - 4 * x.getKomp(2));
}

CMyVektor h(CMyVektor x) {
	CMyVektor tmp(2);
	double x1, y = 0;
	x1 = pow(x.getKomp(0), 3) * pow(x.getKomp(1), 3) - 2 * x.getKomp(1);
	y = x.getKomp(0) - 2;


	tmp.setKomp(x1, 0);
	tmp.setKomp(y, 1);


	return tmp;
}