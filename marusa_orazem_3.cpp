// Naloga 3: Izštevanka
// Maruša Oražem, 27151090
// matematika, 2. letnik



#include <iostream>
#include <climits>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct AVL {
    int vozlisce;
    int visina;
    bool zbrisan;
    int otroci;
    AVL *levo, *desno;
};

//�tart, novo drevo
AVL* novAVL(int x) {
    AVL* drevo = new AVL;
    drevo->vozlisce = x;
    drevo->levo = nullptr;
    drevo->desno = nullptr;
    drevo->visina = 1;
	drevo->zbrisan = false;
	drevo->otroci = 1; //zaradi lažjega računanja šteje tudi sebe
    return drevo;
}

int visina(AVL* root) {
    if (root == nullptr) {return 0;}
    else {return root->visina;}
}

int otroci(AVL* root) {
    if (root == nullptr) {return 0;}
    else {return root->otroci;}
}
// pomo� : https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
AVL* desna_rotacija(AVL* root) {
    //levi otrok
    AVL* x = root->levo;
    //od levega otroka, desni otrok
    AVL* z = x->desno;

    //zdej jih obrnemo
    x->desno = root;
    root->levo = z;

    //ker smo jih zamenjal je treba spremenit vi�ine, ker prej niso ble ok, obviously
    root->visina = max(visina(root->levo), visina(root->desno)) +1;

    if (root->zbrisan == true) {
        root->otroci = otroci(root->levo) + otroci(root->desno);
    }
    if (root->zbrisan == false) {
        root->otroci = otroci(root->levo) + otroci(root->desno) + 1;
    }

    x->visina = max(visina(x->levo),visina(x->desno)) +1;

    if (x->zbrisan == true) {
        x->otroci = otroci(x->levo) + otroci(x->desno);
    }
    if (x->zbrisan == false) {
        x->otroci = otroci(x->levo) + otroci(x->desno) + 1;
    }
    return x;
}
//isto k desna, sam kontra
AVL* leva_rotacija(AVL* root) {
    AVL* y = root->desno;
    AVL* x = y->levo;

    y->levo = root;
    root->desno = x;

    root->visina = max(visina(root->levo), visina(root->desno)) +1;

    if (root->zbrisan == true) {
        root->otroci = otroci(root->levo) + otroci(root->desno);
    }
    if (root->zbrisan == false) {
        root->otroci = otroci(root->levo) + otroci(root->desno) + 1;
    }


    y->visina = max(visina(y->levo), visina(y->desno)) +1;

    if (y->zbrisan == true) {
        y->otroci = otroci(y->levo) + otroci(y->desno);
    }
    if (y->zbrisan == false) {
        y->otroci = otroci(y->levo) + otroci(y->desno) + 1;
    }

    return y;
}

AVL* dvojna_leva_rotacija(AVL* root) {
    root->desno = desna_rotacija(root->desno);
    if (root->zbrisan == true) {
        root->otroci = otroci(root->levo) + otroci(root->desno);
    }
    if (root->zbrisan == false) {
        root->otroci = otroci(root->levo) + otroci(root->desno) + 1;
    }

    return leva_rotacija(root);
}
AVL* dvojna_desna_rotacija(AVL* root) {
    root->levo = leva_rotacija(root->levo);
    if (root->zbrisan == true) {
        root->otroci = otroci(root->levo) + otroci(root->desno);
    }
    if (root->zbrisan == false) {
        root->otroci = otroci(root->levo) + otroci(root->desno) + 1;
    }

    return desna_rotacija(root);
}

AVL* vstavi(AVL* root, int x) {
    if (root == nullptr) {
        return novAVL(x);
    }
    else if (root->vozlisce == x && root->zbrisan == true) {
        root->zbrisan == false;
    }
    else if (root->vozlisce > x) {
        root->otroci +=1;
        root->levo = vstavi(root->levo, x);

    }
    else if (root->vozlisce < x) {
        root->otroci +=1;
        root->desno = vstavi(root->desno,x);

    }
    //za x == root->vozli��e nerabimo, da se ne podvaja, kar vrnemo drevo
    else {return root;}
    //zdej je pa treba zadevo uravnovesit, ful bedno, ne da se mi.
    //to do, jutr

    //treba obnovit vi�ino

    //sedaj je treba preveriti �e je drevo neuravnote�eno
    //treba nrdit rotacije
    //obstajajo 4je razli�ni scenariji
    //treba napisat if stauke, bruh

    int ravnotezje;
    if (root == nullptr) {ravnotezje =  0;}
    else {ravnotezje = visina(root->levo) - visina(root->desno);}

    //leva leva prva slikca
    if (ravnotezje > 1 && x < root->levo->vozlisce) {
        return desna_rotacija(root);
    }

    //desna desna
    if (ravnotezje < -1 && x > root->desno->vozlisce) {
        return leva_rotacija(root);
    }

    //leva desna
    if (ravnotezje > 1 && x > root->levo->vozlisce) {
        return dvojna_desna_rotacija(root);
    }

    //desna leva
    if (ravnotezje < -1 && x < root->desno->vozlisce) {
        return dvojna_leva_rotacija(root);
    }

    root->visina = 1+ max(visina(root->levo), visina(root->desno));
    if (root->zbrisan == true) {
        root->otroci = otroci(root->levo) + otroci(root->desno);
    }
    if (root->zbrisan == false) {
        root->otroci = otroci(root->levo) + otroci(root->desno) + 1;
    }

    return root;

}

//pomo� na :https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
//https://gist.github.com/Harish-R/097688ac7f48bcbadfa5



 int zbrisi(AVL* root, int x) {
	 if (root == nullptr) {
		 return 0;
	 }
	 else if( x < root->vozlisce) {
        int a = zbrisi(root->levo,x);
        if (a == 1) {
		 root->otroci -=1;
        }
        else {
        }
	 }
	 else if (x > root->vozlisce) {
	     int b = zbrisi(root->desno,x);
        if (b == 1) {
		 root->otroci -=1;
        }
        else {
        }
	 }
	 else if (x == root->vozlisce) {
        if (root->zbrisan == true) {
        return 0;}
        else {
        root->zbrisan = true;
		 root->otroci -=1;
        return 1;
        }
	 }
 }



//manjka �e iskanje k-tega elementa
//jutr


int k_ti (AVL* root, int k) {
    //int otroci;
    //cout << "otroci: " << stevilo_otrok(root->levo) << endl;
    if (root->zbrisan == false) {
        if (otroci(root->levo) == k - 1) {
            return root->vozlisce;
        }
        else if (otroci(root->levo) > k-1 && root->levo != nullptr) {
            return k_ti(root->levo,k);
        }
        else  {
            if (root->levo == nullptr) {
                return k_ti(root->desno, k -1);
            }
            else {
               return k_ti(root->desno, k - otroci(root->levo) -1);
            }

        }
    }
    else if (root->zbrisan == true) {
        if (otroci(root->levo) > k-1 && root->levo != nullptr) {
            return k_ti(root->levo, k);
        }
        else  {
            if (root->levo == nullptr) {
                return k_ti(root->desno, k);
            }
            else {
               return k_ti(root->desno, k - otroci(root->levo));
            }

        }

    }

    }





const int mod = 1000000001;
int main() {
AVL* root = nullptr;
int koraki;
char znak;
int visina;
int prejsnji = 0;

scanf(" %d",&koraki);

for (int i = 0; i<koraki; i++) {
    scanf(" %c %d",&znak,&visina);
    visina = (visina + prejsnji) % mod;
    //cout << "znak " << znak <<" "<< "visina " << visina << endl;
    if (znak == '+') {
        root=vstavi(root,visina);
        //cout << "drevo:  "<< otroci(root)<<endl;
    }
    else {
        prejsnji = k_ti(root,visina);
        zbrisi(root,prejsnji);
        //cout << "drevo:  "<<endl;
        cout << prejsnji << endl;
    }
}


return 0;}
