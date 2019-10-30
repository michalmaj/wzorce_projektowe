#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;
/*
	1. Wysokopoziomowe moduły nie powinny zależeć od modułów niskopoziomowych,
		zależności między nimi powinny wynikać z abstrakcji.

	2. Abstrakcja nie powinny zależeć od szczegółów.
		Szczegóły powinny zależeć od abstrakcji.
*/


// budowanie relacji w rodzinie
enum class Relacja
{
	rodzic,
	dziecko,
	rodzenstwo
};

struct Osoba
{
	string imie;
};

struct PrzegladanieRelacji
{
	virtual vector<Osoba> znajdz_wszystkie_dzieci(const string& imie) = 0;
};

// dodawanie relacji
struct Relacje : PrzegladanieRelacji // niższy poziom
{
	vector<tuple<Osoba, Relacja, Osoba>> relacja;

	void dodaj_rodzica_i_dziecko(const Osoba& rodzic, const Osoba& dziecko)
	{
		relacja.push_back({ rodzic, Relacja::rodzic, dziecko });
		relacja.push_back({ dziecko, Relacja::dziecko, rodzic });
	}

	vector<Osoba> znajdz_wszystkie_dzieci(const string& imie) override
	{
		vector<Osoba> result;
		for (auto&& [pierwsze, rel, drugie] : relacja)
		{
			if (pierwsze.imie == imie && rel == Relacja::rodzic)
			{
				result.push_back(drugie);
			}
		}
		return result;
	}
};

// Sprawdza relacje w rodzinie
struct Analiza // wyższy poziom
{
	Analiza(PrzegladanieRelacji& przeglad)
	{
		// przeszukuje dzieci dla osoby o imieniu Jan
		for (auto& dziecko : przeglad.znajdz_wszystkie_dzieci("Jan"))
		{
			cout << "Jan ma dziecko o imieiu " << dziecko.imie << "!" << endl;
		}
	}

};

int main()
{
	Osoba rodzic{ "Jan" };
	Osoba dziecko1{ "Krzysztof" };
	Osoba dziecko2{ "Mateusz" };

	Relacje relacje;
	relacje.dodaj_rodzica_i_dziecko(rodzic, dziecko1);
	relacje.dodaj_rodzica_i_dziecko(rodzic, dziecko2);

	Analiza _(relacje);

	return 0;
}