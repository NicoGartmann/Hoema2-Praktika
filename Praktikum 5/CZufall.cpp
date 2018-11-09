#include  "CZufall.h"
using namespace std;

CZufall::CZufall() {

}

int CZufall::wert(int a, int b) {
  int val;
  val= a + rand() % (b-a+1);
  return val;
}

void CZufall::initialisiere(int n) {
  srand(n);
}

vector<int> CZufall::test(int a, int b, int N) {
  vector<int> werte;
  werte.resize(N);
  for(int i=0; i<N; i++)
    werte[i]=this->wert(a,b);

  vector<int> a_bis_b;
  a_bis_b.resize(b-a+1);
  for(int i=0; i<b-a+1; i++) {
    int x=a+i;
    a_bis_b[i]=x;
  }

  vector<int> result;
  result.resize(b-a+1);
  for(int i=0; i<b-a+1; i++) {
    for(int j=0; j<N; j++) {
      if(a_bis_b[i]==werte[j])
        result[i]=result[i]+1;
    }
  }
  return result;
}

vector<int> CZufall::test_falsch(int a, int b, int N) { 
  vector<int> werte;
  werte.resize(N);
  for(int i=0; i<N; i++) {
	this->initialisiere(NULL);
    werte[i]=this->wert(a,b);
  }

  vector<int> a_bis_b;
  a_bis_b.resize(b-a+1);
  for(int i=0; i<b-a+1; i++) {
	
    int x=a+i;
    a_bis_b[i]=x;
  }

  vector<int> result;
  result.resize(b-a+1);
  for(int i=0; i<b-a+1; i++) {
    for(int j=0; j<N; j++) {
      if(a_bis_b[i]==werte[j])
        result[i]=result[i]+1;
    }
  }
  return result;
}