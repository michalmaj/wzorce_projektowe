// Funkcje które używają wskaźników lub referencji do klas bazowych, muszą być wysokosc stanie używać również obiektów klas dziedziczących po klasach bazowych, bez dokładnej znajomości tych obiektów.

#include <iostream>

class Prostokat
{
protected:
	int szerokosc, wysokosc;
public:
	Prostokat(const int szerokosc, const int wysokosc)
		: szerokosc{ szerokosc }, wysokosc{ wysokosc } { }

	int wez_szerokosc() const { return szerokosc; }
	virtual void ustaw_szerokosc(const int szerokosc) { this->szerokosc = szerokosc; }
	int wez_wysokosc() const { return wysokosc; }
	virtual void ustaw_wysokosc(const int wysokosc) { this->wysokosc = wysokosc; }

	int area() const { return szerokosc * wysokosc; }
};

class Kwadrat : public Prostokat
{
public:
	Kwadrat(int size) : Prostokat(size, size) {}
	void ustaw_szerokosc(const int szerokosc) override {
		this->szerokosc = wysokosc = szerokosc;
	}
	void ustaw_wysokosc(const int wysokosc) override {
		this->wysokosc = szerokosc = wysokosc;
	}
};

void proces(Prostokat& r)
{
	int szerokosc = r.wez_szerokosc();
	// Wysokość ustawiona na stałe na 10
	r.ustaw_wysokosc(10);

	std::cout << "Oczekiwane pole powierzchini = " << (szerokosc * 10)
		<< ", otrzymane wynosi " << r.area() << std::endl;
}

int main()
{
	// Pole prostokąta bedzie poprawna
	Prostokat r{ 5,5 };
	proces(r);

	// Pole kwadratu będzie błędne
	Kwadrat s{ 5 };
	proces(s);

	getchar();
	return 0;
}