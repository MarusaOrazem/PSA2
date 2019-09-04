 /*Naloga 1: Prepogosto
 Maruša Oražem, 27151090
 matematika, 2. letnik*/




#include <iostream>
#include <vector>


using namespace std;
/*int stevila[70000005];
int stevec[10000001];*/
int main() {
    int N;
    int K;
    long long S1;
    long long S2;
    long long X;
    long long Y;
    int M;
    int A;
    int B;

    cin >> N;
    cin >> K;
    cin >> S1;
    cin >> S2;
    cin >> X;
    cin >> Y;
    cin >> M;
    cin >> A;
    cin >> B;
    vector<int> stevila(N,0);
    vector<int> stevec(M,0);

    stevila[0] = S1;
    stevila[1] = S2;

    //naredi seznam števil
    int novo;
    long long a;
    long long b;
    for (int i = 2; i < N; ++i){
        a = stevila[i-2] * X;
        b = stevila[i-1] * Y;
        novo = int((a+b) % M);

        stevila[i] = novo;
    }
    /*for (int a = 0; a<N;++a){
        cout  << stevila[a] << " ";
    } cout << endl;*/

    //prešteje ponovitve od zadaj, ko jih je preveè, namesto št napiše -1

    int trenutno;
    for (int j = N-1; j>=0; --j) {
        trenutno = stevila[j];
        stevec[trenutno]++;
        if (stevec[trenutno] > K) {
            stevila[j] = -1;
        }

    }
    /*for (int a = 0; a<N;++a){
        cout  << stevec[a] << " ";
    } cout << endl;
    for (int b = 0; b<N; ++b){
        cout  << stevila[b] << " ";
    }cout << endl;*/
    //izpiše števila razn èe je -1

    int j = 0;
    for (int i = 0; i<N;++i){
        if (stevila[i] == -1) {
            continue;
        }
        if ( j>= A-1 && j < B) {
            cout << stevila[i] << " ";
        }
        if (j> B){
            break;
        }
        ++j;
    }cout << endl;












}
