#pragma once
#ifndef _CLOTTO_H
#define _CLOTTO_H
#include <vector>
#include <time.h>
#include "CZufall.h"
using namespace std;

class CLotto {
	friend class CZufall;
private:
	vector<int> schein;
	vector<int> ziehung();
public:
	CLotto();
	CLotto(int n);
	void setSchein(vector<int> pSchein);
	int pruefe_doppel(vector<int> y);
	int eine_ziehung(vector<int> tippzettel); 
	int zwei_ziehungen(vector<int> tippzettel); 
	double MC_eineZiehung(vector<int> tippzettel, int N); 
	double MC_zweiZiehungen(vector<int> tippzettel, int N); 
};
#endif