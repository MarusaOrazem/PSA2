 /*Naloga 1: Varnost pri delu
 Maru�a Ora�em, 27151090
 matematika, 2. letnik*/



#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <ctime>
#include <cmath>

using namespace std;

struct Node {

    Node *left,*right;
    int levo, desno, stevilo,sredina;
    Node(int levo_novi, int desno_novi) : left(nullptr), right(nullptr),sredina(-1){
        stevilo = 0;
        levo = levo_novi;
        desno = desno_novi;
        sredina = (levo+desno)/2;
        // -1 zato da se tam ustavii, da vemo da je to list, �isto spodaj. butasto napisano
        if (levo == -1) {return;}
        else if (desno == -1) {return;}
        else if (desno - levo == 1) {
                left= new Node(levo,-1);
                right=new Node(-1,desno);
        }
        else {
            left = new Node(levo, sredina);
            right = new Node(sredina, desno);
        }
    }
//damo interval v drevo, pri�tejo 1 kjer se ujema
    void zacni(int a,int b) {

        if (levo == -1 || desno == -1) {
            stevilo++;

        }

        //�e je enako intervalu
        else if (a == levo && b == desno) {
            stevilo++;
        }
        //�e je na levem podintervalu od intervala
        else if(a >= levo && b <= sredina ) {
            left-> zacni(a,b);
        }
        //�e je v desnem podintervalu
        else if(a > sredina && b <= desno) {
            right->zacni(a,b);
        }
        //�e je interval nekje na sredini, malo levo malo desno
        else {
            //razbijemo interval na sredini od vozli��a, saj se tko delijo potem otroci
            left->zacni(a,sredina);
            right->zacni(sredina,b);
        }
    }

//enako kot kon�aj samo da od�teje 1
    void koncaj(int a,int b) {


        if (levo == -1 || desno == -1) {
            stevilo--;

        }

        //�e je enako intervalu
        else if (a == levo && b == desno) {
            stevilo--;
        }
        //�e je na levem podintervalu od intervala
        else if(a >= levo && b <= sredina ) {
            left-> koncaj(a,b);
        }
        //�e je v desnem podintervalu
        else if(a > sredina && b <= desno) {
            right->koncaj(a,b);
        }
        //�e je interval nekje na sredini, malo levo malo desno
        else {
            //razbijemo interval na sredini od vozli��a, saj se tko delijo potem otroci
            left->koncaj(a,sredina);
            right->koncaj(sredina,b);
        }
    }

    //in�pekcija gre od korena do lista kjer je x, spotoma se�teva delavce
    int inspekcija(int x) {
        //x je lahko ali levo ali desno od sredine, pogledamo kje in i��emo naprej x, spotoma se�tevamo delavce
        //�e smo �e pri�li do konca
        if (levo == -1 || desno == -1) {
            return stevilo;
        }
        /*else if (levo == desno == x) {
            return stevilo;
        }*/
        //x je levo
        else if (x <= sredina) {
            return stevilo + left->inspekcija(x);
        }
        //x je desno
        else if (x > sredina) {
            return stevilo + right->inspekcija(x);
        }


    }

};





int main() {
int D,P; //D �tevilo delavcev, P �tevilo in�ekcijskih pregledov
cin >> D >> P;


deque<vector<int>>dogodki;
vector<int> dogodek;
vector<int> krajisca;
int najvecji=0;
int najmanjsi =1000000000;
//shranimo si vse dogodke
for (int i = 0; i < D; i++) {
	int cas_zac, cas_konec, odsek_zac, odsek_konec;
	cin >> cas_zac >> cas_konec >> odsek_zac >> odsek_konec;
	if (odsek_zac < najmanjsi) {najmanjsi = odsek_zac;}
	if (odsek_konec >najvecji) {najvecji = odsek_konec;}
	dogodek.push_back(cas_zac);
	dogodek.push_back(0);
	dogodek.push_back(odsek_zac);
	dogodek.push_back(odsek_konec);
	dogodki.push_back(dogodek);
	dogodek.clear();
	dogodek.push_back(cas_konec);
	dogodek.push_back(2);
	dogodek.push_back(odsek_zac);
	dogodek.push_back(odsek_konec);
	dogodki.push_back(dogodek);
	dogodek.clear();
	krajisca.push_back(odsek_zac);
	krajisca.push_back(odsek_konec);
}
//shranimo si in�ekcije
for (int i = 0; i < P; i++) {
    int insp_cas, insp_odsek;
    cin >> insp_cas >> insp_odsek;
    dogodek.push_back(insp_cas);
    dogodek.push_back(1);
    dogodek.push_back(i);
    dogodek.push_back(insp_odsek);
    dogodki.push_back(dogodek);
    dogodek.clear();
    krajisca.push_back(insp_odsek);
}

//uredimo po �asu
sort(dogodki.begin(), dogodki.end());

//shranimo si krajisca da vemo kje se kej dogaja, ostalih �tevilk ne rabimo,
//sortiramo, odstranimo ponavljanja
sort(krajisca.begin(), krajisca.end());
krajisca.erase( unique( krajisca.begin(), krajisca.end() ), krajisca.end() );
//cout<<"dolzina "<<krajisca.size()<<endl;

//pogledamo koliko je najbli�ja potenca 2-ke da bomo vedeli koliko rabimo za drevo
int st_elementov = pow(2,ceil(log2(krajisca.size())));
//cout<<"stelementov " << st_elementov <<endl;

int rezultat;
//zgradimo polno dvoji�ko drevo
Node* root = new Node(0,st_elementov);


//po vrsti dodajamo in bri�emo delavce, naredimo in�ekcijo
//potrebno je poiskat nove indekse v seznamu kraji��, ker delamo na manj�em drevesu
for (int i = 0; i< dogodki.size(); i++) {
    if (dogodki[i][1] == 0) {
        int indeks1 = (lower_bound (krajisca.begin(), krajisca.end(), dogodki[i][2]))-krajisca.begin();
    //cout<<"inseks1"<<"  "<<dogodki[i][2]<<"  "<<indeks1<<endl;
        int indeks2 = (lower_bound (krajisca.begin(), krajisca.end(), dogodki[i][3]))-krajisca.begin();
        root->zacni(indeks1, indeks2);
    }
    if (dogodki[i][1] == 2) {
        int indeks1 = (lower_bound (krajisca.begin(), krajisca.end(), dogodki[i][2]))-krajisca.begin();
        int indeks2 = (lower_bound (krajisca.begin(), krajisca.end(), dogodki[i][3]))-krajisca.begin();
        root->koncaj(indeks1, indeks2);
    }
    if (dogodki[i][1] == 1) {
        int indeks = (lower_bound (krajisca.begin(), krajisca.end(), dogodki[i][3]))-krajisca.begin();
        rezultat = root->inspekcija(indeks);
        cout << rezultat << endl;
    }
}



    return 0;
}
