#include <iostream>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include "Igra.h"

using namespace std;


int main() {

    Igra i;

    cout << "za igru protiv racunala unesi R, a za igru protiv igraca do sebe izaberi I" << endl;
    char odabir;
    cin >> odabir;

    if (odabir == 'R') {
        cout << "unesi broj stupca u kojeg zelis ubaciti zeton" << endl;
        while (!i.dohvatiProzor()->jelGotov())
            i.iVSr();
    }
        
    else if (odabir == 'I') {
        cout << "unesi broj stupca u kojeg zelis ubaciti zeton" << endl;
        while (!i.dohvatiProzor()->jelGotov())
            i.iVSi();
    }
        
    else
        cout << "nije bio dobar odabir, pokreni igru ponovo" << endl; //napravi ponovo unošenje odabira


    return 0;
}