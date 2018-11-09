#pragma once
#ifndef _C_DGLSOLVER_H
#define _C_DGLSOLVER_H
#include "CMyVektor.h"
#include <vector>
#include <string>
using namespace std;

typedef CMyVektor(*dglfunc) (CMyVektor, double);
typedef double(*dglhfunc) (CMyVektor, double);

class C_DGLSolver
{
private:
	static CMyVektor DGL_System(CMyVektor y, double x)
	{
		CMyVektor res(2);
		res.setKomp(2 * y.getKomp(1) - x*(y.getKomp(0)), 0);
		res.setKomp(y.getKomp(0)*y.getKomp(1) - 2 * (x*x*x), 1);
		return res;
	}

	static double DGL_nterOrdnung(CMyVektor y, double x)
	{
		double res = 0;
		res = 2 * x*y.getKomp(1) * y.getKomp(2) + 2 * (y.getKomp(0)*y.getKomp(0))*y.getKomp(1);
		return res;
	}

	dglfunc f = DGL_System;
	dglhfunc g = DGL_nterOrdnung;
	bool DGLSystem;
	CMyVektor ableitungen(CMyVektor y, double x);
public:
	C_DGLSolver(bool pDGLSystem)
	{
		this->DGLSystem=pDGLSystem;
	}
	void euler(double start, double end, double steps, CMyVektor y_start);
	void heun(double start, double end, double steps, CMyVektor y_start);
	CMyVektor C_DGLSolver::eulerabw(double start, double end, int steps, CMyVektor y);
	CMyVektor C_DGLSolver::heunabw(double start, double end, double steps, CMyVektor y); 
	void abweichung();
};
#endif
