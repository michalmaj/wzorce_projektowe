'''
    Klasa powinna mieć tylko jedną odpowiedzialność (nigdy nie powinien istnieć więcej niż jeden powód do modyfikacji klasy).
'''

class Dziennik:
    def __init__(self):
        self.wpisy = []
        self.licz = 0

    # dodawanie wpisów
    def dodaj(self, tekst):
        self.wpisy.append(f"{self.licz}: {tekst}")
        self.licz += 1

    # usuwanie wpisów
    def usun(self, pos):
        del self.wpisy[pos]

    def __str__(self):
        return "\n".join(self.wpisy)

    # złamanie pojedynczej odpowiedzialności!!!
    '''
        Poniższe 3 funkcje łamią zasady pojedynczej odpowiedzialności.
        Powinny zostać usuniete! Przykładem może być zapis do pliku,
        w tym momencie jest jako oddzielna klasa, żeby zachować zasadę:
        pojedynczej odpowiedzialności
    '''
    def zapisz(self, nazwa_pliku):
        plik = open(nazwa_pliku, "w")
        plik.write(str(self))
        plik.close()

    def wczytaj(self, nazwa_pliku):
         pass

    def wczytaj_ze_strony(self, uri):
        pass


class ZapisDoPliku:
    def zapisz_do_pliku(self, dziennik, nazwa_pliku):
        nazwa = open(nazwa_pliku, "w")
        nazwa.write(str(dziennik))
        nazwa.close()


j = Dziennik()
# dodawanie wpsiów do dziennika
j.dodaj("Grałem w gre.")
j.dodaj("Programowałem.")
print(f"Wpisy w dzienniku:\n{j}\n")

p = ZapisDoPliku()
# zapisywanie dziennika do pliku dziennik.txt
plik = r'dziennik.txt'
p.zapisz_do_pliku(j, plik)

# weryfikacja!
with open(plik) as fh:
    print(fh.read())
