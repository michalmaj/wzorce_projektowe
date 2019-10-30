'''
    Wiele dedykowanych interfejsów jest lepsze niż jeden ogólny.
'''
from abc import abstractmethod


class Maszyna:
    def drukuj(self, dokument):
        raise NotImplementedError()

    def faksuj(self, dokument):
        raise NotImplementedError()

    def skanuj(self, document):
        raise NotImplementedError()


# jeżeli musi obsługiwać urządzenie wielofunkcyjne
class WieloFunkcyjnaDrukarka(Maszyna):
    def drukuj(self, dokument):
        pass

    def faksuj(self, dokument):
        pass

    def skanuj(self, document):
        pass


class StaregoTypuDrukarka(Maszyna):
    def drukuj(self, dokument):
        # drukuj
        pass

    def faksuj(self, dokument):
        print(f"przefaksowano {dokument}")
        # pass  # nic nie rób

    def skanuj(self, document):
        """Nie obsługuje"""
        raise NotImplementedError('Drukarka nie może skanować!')


class Drukarka:
    @abstractmethod
    def drukuj(self, dokument): pass


class Skaner:
    @abstractmethod
    def skanuj(self, dokument): pass


# to samo dla faksu.

class MojaDrukarka(Drukarka):
    def drukuj(self, dokument):
        print(dokument)


class Fotokopiarka(Drukarka, Skaner):
    def drukuj(self, dokument):
        print(dokument)

    def skanuj(self, dokument):
        pass


class MultiFunkcyjneUrzadzenie(Drukarka, Skaner):  # , Fax, etc
    @abstractmethod
    def drukuj(self, dokument):
        pass

    @abstractmethod
    def skanuj(self, dokument):
        pass


class MultiFunkcyjnaMaszyna(MultiFunkcyjneUrzadzenie):
    def __init__(self, drukarka, skaner):
        self.drukarka = drukarka
        self.skaner = skaner

    def drukuj(self, dokument):
        self.drukarka.drukuj(dokument)

    def skanuj(self, dokument):
        self.skaner.skanuj(dokument)


drukarka = StaregoTypuDrukarka()
drukarka.faksuj(123)  # wyświetli napis
drukarka.skanuj(123)  # błąd!
