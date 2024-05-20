#pragma once
#include <SFML/Graphics.hpp>

class Prozor {
public:
	Prozor();
	Prozor(const std::string&, const sf::Vector2u&);
	~Prozor();

	void nedrzi();
	void prebaciNaCijeli();
	void ocisti();
	void prikazi();
	void crtaj(sf::Drawable&);
	bool jelGotov() { return gotov; }
	void gotovaIgra() { gotov = true;  }
	bool jelCijeli() { return cijeliZaslon; }
	sf::Vector2u dohvatiVelicinu() { return velicina; }

private:
	void Postavi(const std::string&, const sf::Vector2u&);
	void Stvori();
	void Unisti();

	sf::RenderWindow prozor;
	sf::Vector2u velicina;
	std::string naslov;
	bool gotov;
	bool cijeliZaslon;

};

void Prozor::nedrzi() {
	prozor.setKeyRepeatEnabled(false);
}

void Prozor::crtaj(sf::Drawable& d) {
	prozor.draw(d);
}

void Prozor::prebaciNaCijeli() {
	cijeliZaslon = !cijeliZaslon;
	Unisti();
	Stvori();
}

void Prozor::Postavi(const std::string& n, const sf::Vector2u& v) {
	naslov = n;
	velicina = v;
	cijeliZaslon = false;
	gotov = false;
	Stvori();

}

Prozor::Prozor() {
	Postavi("Prozor", sf::Vector2u(640, 480));
}

Prozor::Prozor(const std::string& n, const sf::Vector2u& v) {
	Postavi(n, v);
}

Prozor::~Prozor() {
	Unisti();
}

void Prozor::Stvori() {
	auto stil = (cijeliZaslon ? sf::Style::Fullscreen : sf::Style::Default);
	prozor.create(sf::VideoMode(velicina.x, velicina.y, 32), naslov, stil);
	prozor.setFramerateLimit(300);

}

void Prozor::Unisti() {
	prozor.close();
}

void Prozor::ocisti() {
	prozor.clear(sf::Color(200, 200, 200, 225));
}

void Prozor::prikazi() {
	prozor.display();
}