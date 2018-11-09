#include "CLotto.h"
using namespace std;

CLotto::CLotto() {

}

CLotto::CLotto(int n) {
	if (n < 0) {
			srand(time(NULL));
	}
	else {
		srand(n);
	}
}

void CLotto::setSchein(vector<int> pSchein) {
	this->schein = pSchein;
}

int CLotto::pruefe_doppel(vector<int> y) {
	CZufall a;
	int x = a.wert(1, 49);
	for (int i = 0; i < y.size(); i++) {
		if (x == y.at(i)) {
			x = this->pruefe_doppel(y);

		}
	}
	return x;
}

vector<int> CLotto::ziehung() {
	vector<int> res = { 0,0,0,0,0,0 };
	int aktuell;
	for (int i = 0; i < res.size(); i++) {
		aktuell = this->pruefe_doppel(res);
		res[i] = aktuell;
	}
	return res;
}

int CLotto::eine_ziehung(vector<int> tippzettel) {
	int richtig=0;
	vector<int> simu;
	simu.resize(6);
	simu= this->ziehung();
	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) {
			if(tippzettel[i]==simu[j])
					richtig++;
		}
	}
	return richtig;
}

int CLotto::zwei_ziehungen(vector<int> tippzettel) {
	int gleich = 0;
	vector<int> ziehung1 = this->ziehung();
	vector<int> ziehung2 = this->ziehung();
	for (size_t i = 0; i < 6; i++) {
		for (size_t j = 0; j < 6; j++) {
			if (tippzettel[i] == ziehung2[j])
				gleich++;
		}

	}
	return gleich;
}

double CLotto::MC_eineZiehung(vector<int> tippzettel, int N) {
	int nk = 0; 
	for (int i = 0; i < N; i++) {
		int x = this->eine_ziehung(tippzettel);
		if (x == 3) {
			nk++; 
		}
	}
	double p; 
	p = (double)nk / (double)N;
	return p; 
}

double CLotto::MC_zweiZiehungen(vector<int> tippzettel, int N) {
	int nk = 0;
	for (int i = 0; i < N; i++) {
		int x = this->zwei_ziehungen(tippzettel);
		if (x == 3) {
			nk++;
		}
	}
	double p;
	p = (double)nk / (double)N;
	return p;
}