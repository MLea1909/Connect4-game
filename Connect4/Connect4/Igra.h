#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include <random>


class Igra {
public:
	Igra();
	~Igra() {}
    Prozor* dohvatiProzor() { return &p; } //vraca pokazivac
    void iVSi();
    void iVSr();


private:
    void ispisi();
    void crtajPlocu();
    int ubaciZeton(int, int);
    int provjeriPobjednika();
    int MinMax(int, int, int, bool);
    bool blokirajPotez(int, int);
    bool punS(int);
    Prozor p;
    int ploca[6][7];
    int igrac;
    int z = 21;
    int c = 21;
    
    int sAI, alfa, beta;
};

Igra::Igra() : p("Connect 4", sf::Vector2u(640, 480)) {
    for (auto i = 0; i < 6; i++) {
        for (auto j = 0; j < 7; j++) {
            ploca[i][j] = 0;
        }
    }
    

    igrac = 1;
    sAI = -1;
    alfa = std::numeric_limits<int>::min();
    beta = std::numeric_limits<int>::max();
    p.nedrzi();
}

void Igra::iVSr() { 
    crtajPlocu();
    bool tipkaPritisnuta[7] = { false }; 
    while (z > 0 && !provjeriPobjednika()) {
        if (igrac == 1) {
            for (int s = 0; s < 7; s++) {
                if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + s))) {
                    if (!tipkaPritisnuta[s]) {
                        tipkaPritisnuta[s] = true;

                        int stupac = s;
                        if (stupac != -1) {
                            if (ubaciZeton(igrac, stupac) == 10) {
                                std::cout << "Tu ne stane žeton, pokušajte drugi stupac." << std::endl;
                                continue; 
                            }
                            igrac = 2;
                        }
                        crtajPlocu();
                    }
                }
                else
                    tipkaPritisnuta[s] = false;
            }
        }
        else if (igrac == 2) {
            MinMax(0, alfa, beta, true);
            if (sAI != -1) {
                ubaciZeton(2, sAI);
                igrac = 1;
                crtajPlocu();
            }
            sAI = -1;
        }

    }

    int pobjednik = provjeriPobjednika();
    if (pobjednik != 0) {
        std::cout << "Pobijedio je igrac " << pobjednik << std::endl;
    }
    else if (z == 0) {
        std::cout << "Igrac 1 je potrosio sve zetone, nema pobjednika " << std::endl;
    }
    
    p.gotovaIgra();
}

void Igra::iVSi() {
    crtajPlocu();
    bool tipkaPritisnuta[7] = { false }; 
    while (z > 0 && c > 0 && !provjeriPobjednika()) {
        for (int s = 0; s < 7; s++) {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + s))) {
                if (!tipkaPritisnuta[s]) {
                    tipkaPritisnuta[s] = true;

                    int stupac = s;
                    if (stupac != -1) {
                        if (ubaciZeton(igrac, stupac) == 10) {
                            std::cout << "Tu ne stane žeton, pokušajte drugi stupac." << std::endl;
                            continue; 
                        }
                        igrac = (igrac == 1) ? 2 : 1; 
                    }
                    crtajPlocu();
                }
            }
            else 
                tipkaPritisnuta[s] = false;
        }
    }
    
    int pobjednik = provjeriPobjednika();
    if (pobjednik != 0) {
        std::cout << "Pobijedio je igrac broj " << pobjednik << std::endl;
    }
    else if (z == 0) {
        std::cout << "Igrac 1 je potrosio sve zetone, nema pobjednika " << std::endl;
    }
    else if (c == 0) {
        std::cout << "Igrac 2 je potrosio sve zetone, nema pobjednika " << std::endl;
    }

    p.gotovaIgra();
}


int Igra::ubaciZeton(int i, int s) {
    int a;
    for (a = 5; a >= 0; a--) {
        if (ploca[a][s] == 0) {
            ploca[a][s] = i;

            if (i == 1)
                z--;

            else if (i == 2)
                c--;

            return a;
        }
    }
    return 10;
}

int Igra::provjeriPobjednika() {
    for (auto i = 0; i < 6; i++) {
        for (auto a = 0; a < 4; a++) { 
            if (ploca[i][a] != 0 && ploca[i][a] == ploca[i][a + 1] && ploca[i][a + 1] == ploca[i][a + 2] && ploca[i][a + 2] == ploca[i][a + 3])
                return ploca[i][a];
        }
    }

    for (auto j = 0; j < 7; j++) {
        for (auto a = 0; a < 3; a++) {
            if (ploca[a][j] != 0 && ploca[a][j] == ploca[a + 1][j] && ploca[a + 1][j] == ploca[a + 2][j] && ploca[a + 2][j] == ploca[a + 3][j]) 
                return ploca[a][j];
  
        }
    }
   
    for (auto b = 0; b < 4; b++) { 
        for (auto c = 0; c < 3 ; c++) {
            if (ploca[b][c] != 0 && ploca[b][c] == ploca[b + 1][c + 1] && ploca[b + 1][c + 1] == ploca[b + 2][c + 2] && ploca[b + 2][c + 2] == ploca[b + 3][c + 3]) 
                return ploca[b][c];      
        }
    }

    for (auto b = 3; b < 7; b++) { 
        for (auto c = 0; c < 3; c++) {
            if (ploca[b][c] != 0 && ploca[b][c] == ploca[b - 1][c + 1] && ploca[b - 1][c + 1] == ploca[b - 2][c + 2] && ploca[b - 2][c + 2] == ploca[b - 3][c + 3]) 
                return ploca[b][c];
        }
    }

    return 0;
}

void Igra::ispisi() {
    for (auto i = 0; i < 6; i++) {
        for (auto j = 0; j < 7; j++) {
            std::cout << ploca[i][j];
        }
        std::cout << std::endl;
    }
}

void Igra::crtajPlocu(){
    float visina = p.dohvatiVelicinu().y / 6.f;
    float sirina = p.dohvatiVelicinu().x / 7.f;

    p.ocisti();

    for (auto i = 0; i < 7; i++) {
        for (auto j = 0; j < 6; j++) {

            sf::RectangleShape pravokutnik(sf::Vector2f(sirina, visina));
            pravokutnik.setPosition(i * sirina, j * visina);
            pravokutnik.setFillColor(sf::Color::Blue);
            p.crtaj(pravokutnik);

            sf::CircleShape krug(35.f);
            
            sf::Texture tekstura;
            sf::Sprite sprite;
            
            if (ploca[j][i] == 1) {
                tekstura.loadFromFile("zvijezda.png");
                sprite.setTexture(tekstura);
                sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
                sprite.setPosition(i * sirina + sirina / 2.f, j * visina + visina / 2.f);
                p.crtaj(sprite);
            }
                
            else if (ploca[j][i] == 2) {
                tekstura.loadFromFile("srce.png");
                sprite.setTexture(tekstura);
                sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
                sprite.setPosition(i * sirina + sirina / 2.f, j * visina + visina / 2.f);
                p.crtaj(sprite);
            }
            else {
                krug.setFillColor(sf::Color::White);
                krug.setPosition(i * sirina + sirina / 2.f, j * visina + visina / 2.f);
                krug.setOrigin(krug.getRadius(), krug.getRadius());
                p.crtaj(krug);
            }
            
            
            
        }
    }
    p.prikazi();
}

bool Igra::blokirajPotez(int i, int s) {
    int tempPloca[6][7];
    for (int a = 0; a < 6; a++) {
        for (int b = 0; b < 7; b++) {
            tempPloca[a][b] = ploca[a][b];
        }
    }

    int red = -1;
    for (int a = 5; a >= 0; a--) {
        if (tempPloca[a][s] == 0) {
            tempPloca[a][s] = i;
            red = a;
            break;
        }
    }

    if (provjeriPobjednika() == i) {
        return true;  
    }

    return false; 
}

int Igra::MinMax(int dubina,int alfa, int beta, bool maxI){
    if (provjeriPobjednika() == 1)
        return -1;
    else if (provjeriPobjednika() == 2)
        return 1;
    if (z == 0 || c == 0)
        return 0;

    if (maxI && dubina < 8) {
        int najbRez = std::numeric_limits<int>::min();

        for (int s = 0; s < 7; s++) {
            if (!punS(s)) {
                int a = ubaciZeton(2, s);
                int rez = MinMax(dubina + 1, alfa, beta, false);
                
                ploca[a][s] = 0;
                c++;

                bool blokiraj = blokirajPotez(1, s);

                if (rez > najbRez  || (rez == najbRez && blokiraj)) {
                    najbRez = rez;
                    sAI = s;
                }
 
                alfa = std::max(alfa, najbRez);

                if (beta <= alfa) {
                    break;
                }
            }
        }

        return najbRez;
    }
    else if (dubina < 8) {
        int najbRez = std::numeric_limits<int>::max();

        for (int s = 0; s < 7; s++) {
            if (!punS(s)) {
                int a = ubaciZeton(1, s);
                int rez = MinMax(dubina + 1, alfa, beta, true);

                ploca[a][s] = 0;
                z++;

                najbRez = std::min(najbRez, rez);
                beta = std::min(beta, najbRez);

                if (beta <= alfa) {
                    break;
                }
            }
        }

        return najbRez;
    }
}

bool Igra::punS(int s){
    for (auto a = 5; a >= 0; a--) {
        if (ploca[a][s] == 0)
            return false;
    }   
    return true;
}
