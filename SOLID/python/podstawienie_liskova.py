'''
    Funkcje które używają wskaźników lub referencji do klas bazowych, muszą być wysokosc stanie używać również obiektów klas dziedziczących po klasach bazowych, bez dokładnej znajomości tych obiektów.
'''
class Prostokat:
    def __init__(self, szerokosc, wysokosc):
        self._wysokosc = wysokosc
        self._szerokosc = szerokosc

    # oblicza pole powierzchni
    @property
    def pole_pow(self):
        return self._szerokosc * self._wysokosc

    def __str__(self):
        return f'Szerokosc: {self.szerokosc}, wysokosc: {self.wysokosc}'

    @property
    def szerokosc(self):
        return self._szerokosc

    @szerokosc.setter
    def szerokosc(self, value):
        self._szerokosc = value

    @property
    def wysokosc(self):
        return self._wysokosc

    @wysokosc.setter
    def wysokosc(self, value):
        self._wysokosc = value

# klassa dziedziczy po klasie prostokąt
class Kwadrat(Prostokat):
    def __init__(self, rozmiar):
        Prostokat.__init__(self, rozmiar, rozmiar)

    @Prostokat.szerokosc.setter
    def szerokosc(self, wartosc):
        _szerokosc = _wysokosc = wartosc

    @Prostokat.wysokosc.setter
    def wysokosc(self, wartosc):
        _szerokosc = _wysokosc = wartosc

'''
    funkcja poniżej będzie działała tylko w przypadku prostokatów,
    więc łamie zasadę podstawienia Liskova
'''
def uzyj(pr):
    szer = pr.szerokosc
    # ustawienie wysokosci na stałą wartość
    pr.wysokosc = 10  # nieprzyjemny efekt uboczny
    oczekiwana = int(szer * 10)
    print(f'Oczekiwane pole powierzchni: {oczekiwana}, otrzymane: {pr.pole_pow}')


rc = Prostokat(2, 3)
uzyj(rc)

sq = Kwadrat(5)
uzyj(sq)
