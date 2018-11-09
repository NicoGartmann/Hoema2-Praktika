#pragma once
#ifndef _CZUFALL_H
#define _CZUFALL_H
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

class CZufall {
public:
  CZufall();
  int wert(int a, int b);
  void initialisiere(int n);
  vector<int> test(int a, int b, int N);
  vector<int> test_falsch(int a, int b, int N);
};
#endif