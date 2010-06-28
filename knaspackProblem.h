
#ifndef __KNASPACK_P_H__
#define __KNASPACK_P_H__

#include "element.h"

///KnaspackProblem klasa ktora reprezentuje konkretny problem plecakowy. 
/// Konstruktor inicjalizuje problem zadana jako argument iloscia elementow. Podane sa takze jako argumenty
/// konstruktora  maksymalna cena oraz maksymalna waga elementu. Ktory moze sie w nim znalezc.
/// Klasa inicjalizuje elementy wartosciami losowymi o rozkladzie "jednostajnym" na ile pozwala metoda rand.
/// posiada takze metode do obliczenia rozwiazania problemu plecakowego metoda zachlanna:)
/// oraz metode sortujaca elementy. Dzieku uzyciu domysnego operatora= dla klasy Element
/// Zakomentowane sa fragmenty kodu dzialajacego pierwotnie na tablicach. Podejscie obiektowe ma jednak wygodniejsza forme i 
/// zostanie tutaj uzyte. Mam nadzieje ze uchroni przed bledami ktore czesto pojawiaja sie przy uzywaniu tablic.
class KnaspackProblem{

	private:
		int countOfElements;
		//double  ** elements;	//waga = elements[x][0], cena = elements[x][1] <- KONWENCJA
		Element * elem;	
	public:
		//k-or
		KnaspackProblem(int A_countOfElements, double maxWeight, double maxPrice);

	Element getElementAt(int index);
	int getCountOfElements();

	//sortowanie po cenie jednostkowej
	void sortByUnitPrice();
	//posortowanie elementow po cenie
	void sortByPrice();
	//znalezienie rozwiazania metoda zachlanna sortowanie po cenie jednostkowej.
	double getBetterBruteForceValue(double BagSize);
	//rozwiazanie metoda zachlanna. Sortowanie po cenie jednostkowej
	double getBruteForceValue(double BagSize);
	
	//znalezienie rozwiazania najprostrze.
	//do usuniecia, nawet za glupia na glupia
	double getDumpBruteForceValue(double BagSize);
	double dynamicSolution(double ** elementy, double rozmiarPlecaka);

	//funkcja ma tworzyc stringa, ale na razie wypisuje na konsole.
	string toString();
	//d-or
	~KnaspackProblem();
};


#endif // __KNASPACK_P_H__

