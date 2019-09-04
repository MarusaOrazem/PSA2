//Naloga 4: Enaki nizi
//Maruša Oražem, 27151090
//Matematika, drugi letnik

#include <iostream>
#include <string>

using namespace std;

//ideja najdena na spletni strani https://www.geeksforgeeks.org/check-whether-two-strings-are-equivalent-or-not-according-to-given-condition/?fbclid=IwAR295LOcELUpCEAI0ZvOsry1M4qyfJgiRjA9S5xBEFO0Y5m4lJKarGgEfsA
//ubistvu je identièno, samo da mi razbijamo nize na 3 dele, namesto samo na 2
//zelo lahka naloga, èe le znaš malo pogooglat :)

//funkcija vrne besedo, ki jo dobimo èe damo besedo na 3 dele in "uredimo po abecedi vsak del"

string urejeno(string x) {
    //ko in èe pridemo do dolžine 1
    if (x.size() == 1) {
        return x;
    }
    else {
      //damo na 3 dele

      int tretjina = x.size() / 3;
      string prvi = urejeno(x.substr(0,tretjina));
      string drugi = urejeno(x.substr(tretjina,tretjina));
      string tretji = urejeno(x.substr(2*tretjina,tretjina));
        //vrnemo najbolj urejeno iz teh treh delov

      return min(min(min(prvi + drugi + tretji, prvi + tretji + drugi), min(drugi + prvi + tretji, drugi + tretji + prvi)),min(tretji + prvi + drugi, tretji + drugi + prvi));
        }
}

int main() {
  int T;
  cin >> T;

    int i = 0;
  while (i < T) {
    string z,y;
    cin >> z >> y;

    int resitev = (urejeno(z) == urejeno(y));

    if (resitev) {
        cout << "enaka" << endl;
    }
    else {
        cout << "razlicna" << endl;
    }
    i++;
  }
  return 0;
}

