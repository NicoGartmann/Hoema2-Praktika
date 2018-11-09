#include "C_DGLSolver.h"
#include "CMyVektor.h"
#include <iostream>
using namespace std;

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{

	if (this->DGLSystem)
	{
		return this->f(y,x);
	}
	else
	{
		CMyVektor res(3);
		res.setKomp(y.getKomp(1), 0);
		res.setKomp(y.getKomp(2), 1);
		res.setKomp(this->g(y,x), 2);
		return res;
	}
}

void C_DGLSolver::euler(double start, double end, double steps, CMyVektor y_start)
{
	cout << "h = 0.02\n\n";
	int schritte =0;
	double h = (end-start) / steps;
	double x = start;
	CMyVektor yneu(y_start.getDimension());
	for (int i = 0; i < yneu.getDimension(); i++)
	{
		yneu.setKomp(y_start.getKomp(i), i);
	}
	CMyVektor abl(y_start.getDimension());
	while(schritte<steps)
	{
		//ausgabe

		cout << "Schritt: " << schritte << endl;
		cout << "	x = " << x << endl;
		cout << "	y =  ( ";
		for(int i=0; i<y_start.getDimension(); i++)
		{
			if (i != y_start.getDimension()-1)
				cout << yneu.getKomp(i) << " ; ";
			else
				cout << yneu.getKomp(i);
		}
		cout << " ) \n";
		//ausgabe ende

		//eigentliches Eulerverfahren
		abl=this->ableitungen(yneu, x);
		for(int i=0; i<yneu.getDimension(); i++)
		{
			yneu.setKomp(yneu.getKomp(i)+h*(abl.getKomp(i)),i);
		}

		//ausgabe

		cout << "	y'= ( ";
		for(int i=0; i<yneu.getDimension(); i++)
		{
			if (i != y_start.getDimension()-1)
				cout << abl.getKomp(i) << " ; ";
			else
				cout << abl.getKomp(i);
		}
		cout << " ) \n";
		//ausgabe ende

		//naechster Schritt
		schritte++;
		x+=h;
		//cout << endl;
	}

	//ausgabe

	cout << "Ende bei" << endl;
	cout << "x = " << x << endl;
	cout << "y = ( ";
	for (int h = 0; h < yneu.getDimension(); h++) {
		if (h == yneu.getDimension() - 1) {
			cout << yneu.getKomp(h);
		}
		else
		{
			cout << yneu.getKomp(h) << " ; ";
		}
	}
	cout << " )" << endl;
	//ausgabe ende
}

void C_DGLSolver::heun(double start, double end, double steps, CMyVektor y_start)
{
	cout << "h = 0.02\n\n";
	int schritte = 0;
	double h = (end-start) / steps;
	double x = start;
	CMyVektor ytest(y_start.getDimension());
	CMyVektor y(y_start.getDimension());
	CMyVektor abl(y_start.getDimension());
	CMyVektor abltest(y_start.getDimension());
	y = y_start;

	while (schritte<steps)
	{
		//ausgabe

		cout << "Schritt: " << schritte << endl;
		cout << "	x = " << x << endl;
		cout << "	y =  ( ";
		for (int i = 0; i<y.getDimension(); i++)
		{
			if (i != y.getDimension() - 1)
				cout << y.getKomp(i) << " ; ";
			else
				cout << y.getKomp(i);
		}
		cout << " ) \n";
		//ausgabe ende


		abl = this->ableitungen(y, x);

		//ausgabe

		cout << "	y'_orig = ( ";
		for (int i = 0; i<y.getDimension(); i++)
		{
			if (i != y_start.getDimension() - 1)
				cout << abl.getKomp(i) << " ; ";
			else
				cout << abl.getKomp(i);
		}
		cout << " ) \n";
		cout << endl;
		//ausgabe ende

		//Test Euler schritt
		for (int i = 0; i < y.getDimension(); i++)
		{
			ytest.setKomp(y.getKomp(i) + h*(abl.getKomp(i)), i);
		}

		abltest = this->ableitungen(ytest, x + h);

		//ausgabe
		cout << "	y_Test = ( ";
		for (int i = 0; i < ytest.getDimension(); i++)
		{
			if (i != ytest.getDimension() - 1)
				cout << ytest.getKomp(i) << " ; ";
			else cout << ytest.getKomp(i);
		}
		cout << " ) \n";


		cout << "	y'_Test = ( ";
		for (int i = 0; i < abltest.getDimension(); i++)
		{
			if (i != abl.getDimension() - 1)
				cout << abltest.getKomp(i) << " ; ";
			else cout << abltest.getKomp(i);
		}
		cout << " ) \n" << endl;
		//ausgabe ende

		//ymittel
		abl = (abl + abltest)*0.5;

		//ausgabe

		cout << "	y'_Mittel = ( ";
		for (int i = 0; i < abl.getDimension(); i++)
		{
			if (i != y.getDimension() - 1)
				cout << abl.getKomp(i) << " ; ";
			else cout << abl.getKomp(i);
		}
		cout << " ) \n" << endl;
		//ausgabe ende

		//tatsaechlicher schritt
		for (int i = 0; i < y.getDimension(); i++)
		{
			y.setKomp(y.getKomp(i) + h*(abl.getKomp(i)), i);
		}

		//naechster Schritt
		schritte++;
		x += h;
	}
	//ausgabe
	cout << "Ende bei" << endl;
	cout << "x =  " << x << endl;
	cout << "y = ( ";
	for (int h = 0; h < y.getDimension(); h++) {
		if (h == y.getDimension() - 1) {
			cout << y.getKomp(h);
		}
		else
		{
			cout << y.getKomp(h) << " ; ";
		}
	}
	cout << " )" << endl;
	//ausgabe ende
}

CMyVektor C_DGLSolver::eulerabw(double start, double end, int steps, CMyVektor y_start)
{
	int schritte = 0;
	double h = (end - start) / steps;
	double x = start;
	CMyVektor yneu(y_start.getDimension());
	yneu=y_start;
	CMyVektor abl(y_start.getDimension());
	while (schritte < steps)
	{
		abl = this->ableitungen(yneu, x);
		for (int i = 0; i < yneu.getDimension(); i++)
		{
			yneu.setKomp(yneu.getKomp(i) + h*(abl.getKomp(i)), i);
		}
		schritte++;
		x += h;
	}
	return yneu;
}

CMyVektor C_DGLSolver::heunabw(double start, double end, double steps, CMyVektor y_start)
{
	int schritte = 0;
	double h = (end - start) / steps;
	double x = start;
	CMyVektor ytest(y_start.getDimension());
	CMyVektor y(y_start.getDimension());
	CMyVektor abl(y_start.getDimension());
	CMyVektor abltest(y_start.getDimension());
	y = y_start;

	while (schritte < steps)
	{
		abl = this->ableitungen(y, x);
		for (int i = 0; i < y.getDimension(); i++)
		{
			ytest.setKomp(y.getKomp(i) + h*(abl.getKomp(i)), i);
		}

		abltest = this->ableitungen(ytest, x + h);
		abl = (abl + abltest)*0.5;
		for (int i = 0; i < y.getDimension(); i++)
		{
			y.setKomp(y.getKomp(i) + h*(abl.getKomp(i)), i);
		}
		schritte++;
		x += h;
	}
	return y;
}

void C_DGLSolver::abweichung() {
	C_DGLSolver neuler(false);
	C_DGLSolver nheun(false);


	CMyVektor nstart(3);
	nstart.setKomp(1, 0);
	nstart.setKomp(-1, 1);
	nstart.setKomp(2, 2);
	CMyVektor y(3);

	y = neuler.eulerabw(1, 2, 10, nstart);
	cout << "Abweichung bei Euler bei 10 Schritten: " << y.getKomp(0)-0.5 << endl;

	y = nheun.heunabw(1, 2, 10, nstart);
	cout << "Abweichung bei Heun bei 10 Schritten: " << y.getKomp(0) - 0.5 << endl;
	y = neuler.eulerabw(1, 2, 100, nstart);
	cout << "Abweichung bei Euler bei 100 Schritten: " << y.getKomp(0) - 0.5 << endl;
	y = nheun.heunabw(1, 2, 100, nstart);
	cout << "Abweichung bei Heun bei 100 Schritten: " << y.getKomp(0) - 0.5 << endl;
	y = neuler.eulerabw(1, 2, 1000, nstart);
	cout << "Abweichung bei Euler bei 1000 Schritten: " << y.getKomp(0) - 0.5 << endl;
	y = nheun.heunabw(1, 2, 1000, nstart);
	cout << "Abweichung bei Heun bei 1000 Schritten: " << y.getKomp(0) - 0.5 << endl;
	y = neuler.eulerabw(1, 2, 10000, nstart);
	cout << "Abweichung bei Euler bei 10000 Schritten: " << y.getKomp(0) - 0.5 << endl;
	y = nheun.heunabw(1, 2, 10000, nstart);
	cout << "Abweichung bei Heun bei 10000 Schritten: " << y.getKomp(0) - 0.5 << endl;
	}
