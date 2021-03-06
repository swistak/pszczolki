
#ifndef __KNASPACK_P_H__
#define __KNASPACK_P_H__

#include "element.h"

///KnapsackProblem klasa ktora reprezentuje konkretny problem plecakowy. 
/// Konstruktor inicjalizuje problem zadana jako argument iloscia elementow. Podane sa takze jako argumenty
/// konstruktora  maksymalna cena oraz maksymalna waga elementu. Ktory moze sie w nim znalezc.
/// Klasa inicjalizuje elementy wartosciami losowymi o rozkladzie "jednostajnym" na ile pozwala metoda rand.
/// posiada takze metode do obliczenia rozwiazania problemu plecakowego metoda zachlanna:)
/// oraz metode sortujaca elementy. Dzieku uzyciu domysnego operatora= dla klasy Element
/// Zakomentowane sa fragmenty kodu dzialajacego pierwotnie na tablicach. Podejscie obiektowe ma jednak wygodniejsza forme i 
/// zostanie tutaj uzyte. Mam nadzieje ze uchroni przed bledami ktore czesto pojawiaja sie przy uzywaniu tablic.

class KnapsackProblem {
private:
    int countOfElements;
    //double  ** elements;	//waga = elements[x][0], cena = elements[x][1] <- KONWENCJA
    Element * elem;
public:
    //k-or
    KnapsackProblem(int A_countOfElements, double maxWeight, double maxPrice);

    Element getElementAt(int index);
    int getCountOfElements();

    //znalezienie rozwiazania metoda zachlanna sortowanie po cenie jednostkowej.
    double getAproximatedValue(double BagSize);
    
    //funkcja ma tworzyc stringa, ale na razie wypisuje na konsole.
    std::string toString();
    //d-or
    ~KnapsackProblem();
};


#endif // __KNASPACK_P_H__

