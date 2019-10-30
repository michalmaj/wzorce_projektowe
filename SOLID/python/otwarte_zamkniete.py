'''
    Zasada otwarte-zamkniete
    Klasy powinny być otwarte na rozszerzenia i zamknięte na modyfikacje.
'''

from enum import Enum


class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3


class Size(Enum):
    SMALL = 1
    MEDIUM = 2
    LARGE = 3


class Product:
    def __init__(self, name, color, size):
        self.name = name
        self.color = color
        self.size = size


class ProductFilter:
    def filter_by_color(self, products, color):
        for p in products:
            if p.color == color: yield p

    def filter_by_size(self, products, size):
        for p in products:
            if p.size == size: yield p

    def filter_by_size_and_color(self, products, size, color):
        for p in products:
            if p.color == color and p.size == size:
                yield p


# podstawowa klasa dla specyfikacji
class Specification:
    # metoda sprawdzająca czy przedmiot spełnia kryteria
    def is_satisfied(self, item):
        pass

    def __and__(self, other):
        return AndSpecification(self, other)

# klasa filtrujaca specyfikacje
class Filter:
    def filter(self, items, spec):
        pass


class ColorSpecification(Specification):
    def __init__(self, color):
        self.color = color

    def is_satisfied(self, item):
        return item.color == self.color


class SizeSpecification(Specification):
    def __init__(self, size):
        self.size = size

    def is_satisfied(self, item):
        return item.size == self.size


class AndSpecification(Specification):
    def __init__(self, spec1, spec2):
        self.spec2 = spec2
        self.spec1 = spec1

    def is_satisfied(self, item):
        return self.spec1.is_satisfied(item) and \
               self.spec2.is_satisfied(item)


class BetterFilter(Filter):
    def filter(self, items, spec):
        for item in items:
            if spec.is_satisfied(item):
                yield item


jablko = Product('Jabłko', Color.GREEN, Size.SMALL)
drzewo = Product('Drzewo', Color.GREEN, Size.LARGE)
dom = Product('Dom', Color.BLUE, Size.LARGE)

products = [jablko, drzewo, dom]

pf = ProductFilter()
print('Zielone produkty (stare):')
for p in pf.filter_by_color(products, Color.GREEN):
    print(f' - {p.name} jest zielone')

# ^ PRZED
print('\n')
# v PO
bf = BetterFilter()

print('Zielone produkty (nowe):')
green = ColorSpecification(Color.GREEN)
for p in bf.filter(products, green):
    print(f' - {p.name} jest zielone')

print('Duże produkty:')
large = SizeSpecification(Size.LARGE)
for p in bf.filter(products, large):
    print(f' - {p.name} jest duże')

print('Duże niebieskie produkty:')

large_blue = large and ColorSpecification(Color.BLUE)
for p in bf.filter(products, large_blue):
    print(f' - {p.name} jest duży i niebieski')