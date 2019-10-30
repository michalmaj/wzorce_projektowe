// Wiele dedykowanych interfejsów jest lepsze niż jeden ogólny.
#include <vector>

struct Dokument;

// Poszczególne interfejsy odpowiadają za poszczególe rzeczy
struct IFDrukarka
{
	virtual void drukuj(Dokument& dok) = 0;
};

struct IFSkaner
{
	virtual void skanuj(Dokument& dok) = 0;
};

struct Drukarka : IFDrukarka
{
	void drukuj(Dokument& dok) override;
};

struct Skaner : IFSkaner
{
	void skanuj(Dokument& dok) override;
};

struct IFUrzadzenie : IFDrukarka, IFSkaner
{
};

struct Urzadzenie : IFUrzadzenie
{
	IFDrukarka& drukarka;
	IFSkaner& skaner;

	Urzadzenie(IFDrukarka& drukarka, IFSkaner& skaner)
		: drukarka{ drukarka },
		skaner{ skaner }
	{
	}

	void drukuj(Dokument& dok) override {
		drukarka.drukuj(dok);
	}
	void skanuj(Dokument& dok) override;
};

// IFDrukarka --> Drukarka
// wszyskto --> Urzadzenie