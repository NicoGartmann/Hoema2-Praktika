#include "CLotto.h"
#include "CZufall.h"
#include <iostream>
using namespace std;

int main() {
	/*vector<int> zettel = { 7,20,33,18,40,1 }; 
	CLotto MyLotto(1); 
	MyLotto.setSchein(zettel); 
	cout << "Wahrscheinlichkeit bei 100000 Ziehungen mit einer Ziehung : "; 
	double p1= MyLotto.MC_eineZiehung(zettel,100000); 
	cout << p1 << endl; 
	cout << "Wahrscheinlichkeit bei 100000 Ziehungen mit zwei Ziehungen: ";
	double p2 = MyLotto.MC_zweiZiehungen(zettel, 100000); 
	cout << p2 << endl;  
	cout << "Wahrscheinlichkeit bei 1000000 Ziehungen mit einer Ziehung : ";
	double p3 = MyLotto.MC_eineZiehung(zettel, 1000000);
	cout << p3 << endl;
	cout << "Wahrscheinlichkeit bei 1000000 Ziehungen mit zwei Ziehungen: ";
	double p4 = MyLotto.MC_zweiZiehungen(zettel, 1000000);
	cout << p4 << endl;*/
	cout << "Test mit unterschiedlichem n: \n"; 
	CZufall MyZufall; 
	for (int i = 0; i < 5; i++) {
		int x = 3 + i; 
		srand(i); 
		for (int y = 0; y < 5; y++) {
			vector<int> test;
			test.resize(5);
			test = MyZufall.test(3, 7, 10000);
			cout << x << ": ";
			cout << test[i] << endl; 
		}
		cout << endl; 
	}

	cout << "Test mit gleichem n: \n"; 
	srand(time(NULL)); 
	CZufall gleichesN; 
		for (int i = 0; i < 5; i++) {
			int x = 3 + i;
			cout << x << ": ";
			vector<int> test1;
			test1.resize(5);
			test1 = gleichesN.test(3, 7, 10000);
			cout << test1[i];
			cout << endl;
		}
		cout << endl; 

	cout << "Test falsch: \n"; 
	CZufall falsch;
	for (int i = 0; i < 5; i++) {
		int x = 3 + i; 
		cout << x << ": "; 
		vector<int>  test2; 
		test2.resize(5); 
		test2 = falsch.test_falsch(3, 7, 10000); 
		cout << test2[i]; 
		cout << endl; 
	}

  system("pause");
  return 0;
}