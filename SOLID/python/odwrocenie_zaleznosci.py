'''
    1. Wysokopoziomowe moduły nie powinny zależeć od modułów niskopoziomowych,
		zależności między nimi powinny wynikać z abstrakcji.
	2. Abstrakcja nie powinny zależeć od szczegółów.
		Szczegóły powinny zależeć od abstrakcji.
'''

from abc import abstractmethod
from enum import Enum


class Relacja(Enum):
    RODZIC = 0
    DZIECKO = 1
    RODZENSTWO = 2


class Osoba:
    def __init__(self, imie):
        self.imie = imie


class WyszukiwanieRelacji:
    @abstractmethod
    def znajdz_wszystkie_dzieci(self, imie): pass


class Relacje(WyszukiwanieRelacji):  # niski poziom
    relacje = []

    def dodaj_rodzic_i_dziecko(self, rodzic, dziecko):
        self.relacje.append((rodzic, Relacja.RODZIC, dziecko))
        self.relacje.append((dziecko, Relacja.RODZIC, rodzic))

    def znajdz_wszystkie_dzieci(self, imie):
        for r in self.relacje:
            if r[0].imie == imie and r[1] == Relacja.RODZIC:
                yield r[2].imie


class Wyszukaj:
    '''
        bezpośrednia zależność od modułu niskiego poziomu
        nieprawidłowe podejście, ponieważ jest silnie zależne (m.in.: typ składowania)
    '''

    # def __init__(self, relacje):
    #     # wysoki poziom: znajdź wszystkie dzieci Johna
    #     relacja = relacje.relations
    #     for r in relacja:
    #         if r[0].ime == 'Jan' and r[1] == Relacje.RODZIC:
    #             print(f'John ma dzieci o imieniu {r[2].name}.')

    # prawidłowe podejście
    def __init__(self, znajdz):
        for p in znajdz.znajdz_wszystkie_dzieci("Jan"):
            print(f'Jan ma dziecko o imieniu {p}')


rodzic = Osoba('Jan')
dziecko_1 = Osoba('Krzysztof')
dziecko_2 = Osoba('Mateusz')

# moduł niskiego poziomu
relacje = Relacje()
relacje.dodaj_rodzic_i_dziecko(rodzic, dziecko_1)
relacje.dodaj_rodzic_i_dziecko(rodzic, dziecko_2)

Wyszukaj(relacje)