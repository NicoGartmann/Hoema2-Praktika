#include "C_DGLSolver.h"
#include "CMyVektor.h"
#include <iostream>
using namespace std;

int main()
{
	int bef;
	
	cout << "Bitte treffen Sie Ihre Auswahl:\n";
	cout << "1 - DGLSystem \n";
	cout << "2 - DGL-hoeherer Ordnung\n";
	cout << "3 - Abweichungen\n"; 
	cout << "> ? "; cin >> bef;
	cout << endl; 

	if (bef == 1)
	{
		int bef2; 
		C_DGLSolver dgl(true);
		cout << "Welches Verfahren wollen Sie anwenden?\n";
		cout << "1- Euler\n";
		cout << "2- Heun\n";
		cout << "> ? "; cin >> bef2;
		cout << endl; 
		CMyVektor start(2);
		start.setKomp(0,0);
		start.setKomp(1,1);
		if(bef2==1)
		{
			dgl.euler(0,2,100,start);
		}
		else if(bef2==2)
		{
			dgl.heun(0,2,100,start);
		}
	}
	else if (bef == 2)
	{
		int bef2; 
		C_DGLSolver dgl(false);
		cout << "Welches Verfahren wollen Sie anwenden?\n";
		cout << "1- Euler\n";
		cout << "2- Heun\n";
		cout << "> ? "; cin >> bef2;
		cout << endl; 
		CMyVektor start(3);
		start.setKomp(1,0);
		start.setKomp(-1,1);
		start.setKomp(2,2);
		if(bef2==1)
		{
			dgl.euler(1,2,100,start);
		}
		else if(bef2==2)
		{
			dgl.heun(1,2,100,start);
		}
	}
	else if (bef == 3)
	{
		C_DGLSolver abw(true); 
		cout << "\nAbweichungen:\n"; 
		abw.abweichung(); 
	}

	system("pause"); 
	return 0;
}
