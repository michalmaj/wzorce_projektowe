// Zasada otwarte-zamkniete
// Klasy powinny być otwarte na rozszerzenia i zamknięte na modyfikacje.


/*
	Przykład:
	Zbudowanie alikacji, która zawiera pewne produkty,
	które będzie można filtrowć.
*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Produkty mają kolor i rozmiar
enum class Kolor { czerwony, zielony, niebieski };
enum class Rozmiar { maly, sredni, duzy };

// Produkty mają nazwę, kolor i rozmiar
struct Produkt
{
	string nazwa;
	Kolor kolor;
	Rozmiar rozmiar;
};

/*
	Pierwsza próba filtrowania produktu,
	gdzie każdy filtr stosowany jest osobno
*/
struct FiltrProduktu
{
	typedef vector<Produkt*> Przedmioty;

	// Filtrowanie kolorem
	Przedmioty filtr_kolor(Przedmioty przedmioty, const Kolor kolor)
	{
		Przedmioty wynik;
		for (auto& i : przedmioty)
			if (i->kolor == kolor)
				wynik.push_back(i);
		return wynik;
	}

	// Filtrowanie rozmiarem
	Przedmioty filtr_rozmiar(Przedmioty przedmioty, const Rozmiar rozmiary)
	{
		Przedmioty wynik;
		for (auto& i : przedmioty)
			if (i->rozmiar == rozmiary)
				wynik.push_back(i);
		return wynik;
	}

	// Filtrowanie rozmiarem i kolorem
	Przedmioty filtr_rozmiar_kolor(Przedmioty przedmioty, const Rozmiar rozmiar, const Kolor kolor)
	{
		Przedmioty wynik;
		for (auto& i : przedmioty)
			if (i->rozmiar == rozmiar && i->kolor == kolor)
				wynik.push_back(i);
		return wynik;
	}
};

template <typename T> struct KombinacjaSpecyfikacji;

// Interface:
template <typename T> struct Specyfikacja
{
	virtual ~Specyfikacja() = default;
	virtual bool czy_spelnia(T* przedmiot) const = 0;

};

template <typename T> KombinacjaSpecyfikacji<T> operator&&
(const Specyfikacja<T>& pierwszy, const Specyfikacja<T>& drugi)
{
	return { pierwszy, drugi };
}

template <typename T> struct Filtr
{
	virtual vector<T*> filtr(vector<T*> przedmioty, Specyfikacja<T>& specyfikacja) = 0;
};

struct FiltrLepszy : Filtr<Produkt>
{
	vector<Produkt*> filtr(vector<Produkt*> przedmioty, Specyfikacja<Produkt>& specyfikacja) override
	{
		vector<Produkt*> wynik;
		for (auto& p : przedmioty)
			if (specyfikacja.czy_spelnia(p))
				wynik.push_back(p);
		return wynik;
	}
};
// KOLEJNE SPECYFIKACJE:

// Dla koloru
struct SpecyfikacjaKolor : Specyfikacja<Produkt>
{
	Kolor kolor;

	SpecyfikacjaKolor(Kolor kolor) : kolor(kolor) {}

	bool czy_spelnia(Produkt* produkt) const override {
		return produkt->kolor == kolor;
	}
};

// Dla rozmiaru
struct SpecyfikacjaRozmiar : Specyfikacja<Produkt>
{
	Rozmiar rozmiar;

	explicit SpecyfikacjaRozmiar(const Rozmiar rozmiar)
		: rozmiar{ rozmiar }
	{
	}


	bool czy_spelnia(Produkt* produkt) const override {
		return produkt->rozmiar == rozmiar;
	}
};
// Dla kombinacji koloru i rozmiaru
template <typename T> struct KombinacjaSpecyfikacji : Specyfikacja<T>
{
	const Specyfikacja<T>& pierwszy;
	const Specyfikacja<T>& drugi;

	KombinacjaSpecyfikacji(const Specyfikacja<T>& pierwszy, const Specyfikacja<T>& drugi)
		: pierwszy(pierwszy), drugi(drugi) {}

	bool czy_spelnia(T* przedmiot) const override {
		return pierwszy.czy_spelnia(przedmiot) && drugi.czy_spelnia(przedmiot);
	}
};


int main()
{
	// Nadanie produktom nazwy, koloru i rozmiaru
	Produkt jablko{ "Jablko", Kolor::zielony, Rozmiar::maly };
	Produkt drzewo{ "Drzewo", Kolor::zielony, Rozmiar::duzy };
	Produkt dom{ "Dom", Kolor::niebieski, Rozmiar::duzy };

	const vector<Produkt*> wszystkie{ &jablko, &drzewo, &dom };

	// Wyświtlnie wszystkich przedmiotów zielonych
	cout << "Zielone przedmioty:" << endl;
	FiltrLepszy bf;
	SpecyfikacjaKolor zielony(Kolor::zielony);
	auto zielone_przedmioy = bf.filtr(wszystkie, zielony);
	for (auto& x : zielone_przedmioy)
		cout << x->nazwa << " jest zielone\n";

	cout << endl;
	// Wyświtlneie tylko zielonych i dużych przedmiotów
	cout << "Duze i zielone przedmioty:" << endl;
	SpecyfikacjaRozmiar duzy(Rozmiar::duzy);
	KombinacjaSpecyfikacji<Produkt> zielony_i_duzy(zielony, duzy);

	auto spec = zielony && duzy;
	for (auto& x : bf.filtr(wszystkie, spec))
		cout << x->nazwa << " jest zielone i duze\n";


	getchar();
	return 0;
}