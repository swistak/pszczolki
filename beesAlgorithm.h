/**
================================================================================
 Plik: 
--------------------------------------------------------------------------------
 Autorzy:       Sebastian Kupny
 Projekt:       Wykorzystanie algorytmu pszczelego do rozwiazania problemu plecakowego
 Kompilator:    g++ : gcc version 4.4.1 (Ubuntu 4.4.1-4ubuntu9)
 Doc:           doxygen 1.4
--------------------------------------------------------------------------------
 Zawiera:       Algorytm programu
--------------------------------------------------------------------------------
 Komentarze:
================================================================================
Tresc dla programu doxygen
@file name: KnaspackProblem_beesAlgorithm.cpp
@date: 2010-05-05, 2010-05-13
@autor: Sebastian Kupny skupny@gmail.com

-------------------------------------------------------
Kolego:
Na samym dole jest main.
W main jest wywolana funkcja test
w test wykonywane sa wszystkie obliczenia.

Ciebie interesuje jedynie funkcja o oryginalnej nazwie: KnaspackProblemSolutinUsingBeeAlgorithm, opisana jest ponizej:
-------------------------------------------------------

Description:
functions:
double KnaspackProblemSolutinUsingBeeAlgorithm(double BagSize, KnaspackProblem &e,int SkautBeens, int WorkerBeens, int A_counOfIteration){
Funkcja ta kompleksowo rozwiazuje problem plecakowy uzywajac algorytmu pszczelego

paraterers:
        gdzie poszczegolne parametry to:
        -BagSize - rozmiar plecaka. Maksymalny rozmiar plecaka ograniczajacy wage elementow.
        -KnaspackProblem e - struktura danych przechowujaca informacje o liczbie elementow do wyboru oraz te elementy. Mozesz o niej poczytac (ale kod i komentarze) niestety dokumentacja w tworzeniu. Na jej rzecz mozna wywolac funkcje, ktora znajdzie zachlanne rozwiazanie problemu. Do zaadaptowania jest algorytm dynamiczny
        -SkautBeens - liczba skautow, ze wzgledu na ich odmienna funkcje podaje sie jako parametr.
        -WorkerBeens - liczba robotnic.
        -A_counOfIteration - liczba iteracji w jakich znajdowane bedzie optymalne rozwiazanie.

returns:
        Funkcja zwraca maksymalna osiagnieta wartosc a dla niej zapamietana w kodzie jest kombinacja wybranych elementow.
        Mozna ja odczytac, ale nalezy zrobic to z poziomu tej funkcji KnaspackProblemSolutinUsingBeeAlgorithm.
Usage:
        W zaleznosci od danych wejsciowych mozna badac otrzymane z funkcji wyniki. Do ustalania parametrow problemu plecakowego nalezy uzyc
        klasy KnaspackProblem

Compile:
                >g++ beesAlgorithm.cpp  -o beesAlgorithm.x


TODO: 
Zrobic dokumentacje z prawdziwego zdarzenia.
Mozna zrobic: podzielic ladnie plik na naglowki, pliki biblioteczne, napisac Makefilea i wiele innych przyjemnych rzeczy:))
 */

#ifndef __BEE_ALG_H__
#define __BEE_ALG_H__

#include "common.h"
#include "knaspackProblem.h"



///Tworzy tablice z permutacja liczb od 0 do size: [0;size] i zwraca wskaznik do niej.
int * getIndexRand(int size);


///funkcja do sprawdzania poprawnosci programu. Przyjmuje jako parametry problem plecakowy,
///wskaznik do tablicy z wybranymi indeksami oraz liczbe wybranych indeksow/elementow.
///zwraca mase wybranych elementow. Nie porownuje jej z masa dozwolona.
double sprawdzenieElementow(KnaspackProblem &e, int *bestPosition, int bestPositionIndex);

///funkcja oblicza dla danej tablicy o zadanym rozmiarze wartosc przchowywana w plecaku.
///jako parametr nalezy przekazac problem, tablice z indeksami wybranych elementow oraz rozmiar tablicy z indeksami.
double calculateSkautValue(KnaspackProblem &e, int * indTab, double A_BagSize, int &LastIndex, double &TotalWeight);


///funkcja oblicza cene oraz ciezar elementow wybranych. Ich indeksy sa w tablicy indTab, liczba wybranych to A_limit.
/// Ponadto zwraca parametry: A_possible jezeli rozmiar plecaka (A_BagSize) zostal przekroczony.
double calculateValue(KnaspackProblem &e, int * indTab, int A_limit, double A_BagSize, double &TotalWeight, bool &A_possible);

enum beeMission {
    CHANGE, SUB
};

class BeeStatus {
public:

    BeeStatus() {
        success = false;
        whatTheyDid = CHANGE;
        Price = 0.;
        Weight = 0.;
        indexLimit = 0;
        swapIndex1 = 0;
        swapIndex2 = 0;
        addedIndex = 0;
        removedIndex = 0;
        //int status=0;
    }
    bool success;
    enum beeMission whatTheyDid;
    double Price;
    double Weight;

    int indexLimit;

    int swapIndex1;
    int swapIndex2;

    int addedIndex;
    int removedIndex;

    int status;
};



BeeStatus beeFly(KnaspackProblem &e, int * indTab, double A_BagSize, int LimitIndex, beeMission whatToDo);

bool tableIsOK(int * tab, int size);

double KnaspackProblemSolutinUsingBeeAlgorithm(double BagSize, KnaspackProblem &e, int SkautBeens, int WorkerBeens, int A_counOfIteration);


#endif //__BEE_ALG_H__
