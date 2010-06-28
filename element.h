/* 
 * File:   element.h
 * Author: swistak
 *
 * Created on 28 czerwiec 2010, 15:58
 */

#ifndef _ELEMENT_H
#define	_ELEMENT_H

#include "common.h"

///Element z plecaka. Mozna bylo to lepiej zrobic bez seterow. ale nie moglem wtedy alokowac tablicy w klasie KnaspackProblem
///To mozna poprawic ale trzeba sie douczyc. Jak alokowac pamiec dla elementow bez domyslnego konstruktora przy uzyciu operatora new.
///Klasa zawiera dwa pola i reperezentuje element ktory mozna zabrac. Posiada informacje o jego wadze oraz cenie calkowitej.
class Element{

private:
	double weight;	///<masa elementu
	double price; ///<cena elementu

	void setWeight(double A_weight); ///<funkcja ustawiajaca wage elementu
	void setPrice(double A_price); ///<funkcja ustawiajaca cene elementu

public:

	Element(double A_weight=0., double A_price=0.);
	double getWeight();
	double getPrice();
	std::string toString();
	friend class KnaspackProblem;
};


#endif	/* _ELEMENT_H */

