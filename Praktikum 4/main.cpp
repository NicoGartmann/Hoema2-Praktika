#include "CKomplex.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

  CKomplex a;
  vector<CKomplex> original(1000);
  vector<CKomplex> test(1000);
  vector<CKomplex> fouriers(1000);
  vector<CKomplex> fourier01(1000);
  vector<CKomplex> fourier10(1000);

  original = a.werte_einlesen("werte.txt");
  test = a.fourier(a.werte_einlesen("werte.txt"), true);
  a.werte_ausgeben("fourier_hin.txt",test);
  test = a.fourier(a.werte_einlesen("werte.txt"), true);
  a.werte_ausgeben("fourier_hin_0.1.txt", test, 0.1);
  test = a.fourier(a.werte_einlesen("werte.txt"), true);
  a.werte_ausgeben("fourier_hin_1.0.txt", test, 1.0);

  fouriers = a.fourier(a.werte_einlesen("fourier_hin.txt"), false);
  a.werte_ausgeben("fourier_rueck.txt", fouriers);
  fourier01 = a.fourier(a.werte_einlesen("fourier_hin_0.1.txt"), false);
  a.werte_ausgeben("fourier_rueck_0.1.txt", fourier01);
  fourier10 = a.fourier(a.werte_einlesen("fourier_hin_1.0.txt"), false);
  a.werte_ausgeben("fourier_rueck_1.0.txt", fourier10);

  a.abweichung(original, fouriers, fourier01, fourier10);

  system("pause");
  return 0;
}
