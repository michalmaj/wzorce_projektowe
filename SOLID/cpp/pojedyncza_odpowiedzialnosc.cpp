/* 
	Klasa powinna mieć tylko jedną odpowiedzialność (nigdy nie powinien istnieć więcej niż jeden powód do modyfikacji klasy).
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
using namespace std;

// Dziennik do przechowywania mysli
struct Dziennik
{
	// tytuł dziennika
	string tytul;
	// ilość wpisów jako wektor
	vector<string> entries;

	explicit Dziennik(const string& title)
		: tytul{ title }
	{
	}

	void dodaj(const string& entry);

	void zapisz(const string& filename);
};

// dodawanie kolejnych wpisów
void Dziennik::dodaj(const string& entry)
{
	static int licz = 1;
	entries.push_back(boost::lexical_cast<string>(licz++)
		+ ": " + entry);
}

void Dziennik::zapisz(const string& filename)
{
	ofstream ofs(filename);
	for (auto& s : entries)
		ofs << s << endl;
}

struct Zapisywanie
{
	// zapisywanie dziennika
	static void zapisz(const Dziennik& j, const string& filename)
	{
		ofstream ofs(filename);
		for (auto& s : j.entries)
			ofs << s << endl;
	}
};

void main()
{
	Dziennik journal{ "Drogi dzienniczku" };
	// dodawanie wpisów do dziennika
	journal.dodaj("Grałem w gry");
	journal.dodaj("Programowałem w C++");

	Zapisywanie pm;
	/* 
		dziennik zostanie zapisany w pliku dziennik.txt w tym samym katalogu,
		w którym znajduje się plik pojedyncza_odpowiedzialnosc.cpp
	*/
	pm.zapisz(journal, "dziennik.txt");
}