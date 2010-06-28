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


#include "beesAlgorithm.h"

///getIndexRand funkcja tworzy tablice z permutacja liczb od 0 do size: [0;size] i zwraca wskaznik do niej.

int * getIndexRand(int size) {

  int temp = 0;
  ;
  int toChange1 = 0, toChange2 = 0;
  int * wsk = new int[size];
  for (int i = 0; i < size; i++) {
    wsk[i] = i;
  }
  for (int i = 0; i < 10 * size; i++) {
    toChange1 = i % size;
    toChange2 = rand() % size;
    //cout << toChange1 <<" "<< toChange2 << endl;
    temp = wsk[toChange2];
    wsk[toChange2] = wsk[toChange1];
    wsk[toChange1] = temp;
    //cout << wsk[toChange1] <<" "<< wsk[toChange2] << endl;
  }
  return wsk;
}


///funkcja do sprawdzania poprawnosci programu. Przyjmuje jako parametry problem plecakowy,
///wskaznik do tablicy z wybranymi indeksami oraz liczbe wybranych indeksow/elementow.
///zwraca mase wybranych elementow. Nie porownuje jej z masa dozwolona.

double sprawdzenieElementow(KnaspackProblem &e, int *bestPosition, int bestPositionIndex) {
  double tempW = 0.;
  double tempP = 0.;
  double sumW = 0.;
  double sumP = 0.;
  for (int i = 0; i < bestPositionIndex; i++) {
    tempW = e.getElementAt(bestPosition[i]).getWeight();
    tempP = e.getElementAt(bestPosition[i]).getPrice();
    //cout << tempW << " " << tempP << endl;//", e=" << e.getElementAt(bestPosition[i]).toString << endl;
    sumW += tempW;
    sumP += tempP;
  }
  //cout << "SPRAWDZENIE: W=" << sumW << ", PRICE=" << sumP << endl;
  return sumW;
}

///funkcja oblicza dla danej tablicy o zadanym rozmiarze wartosc przchowywana w plecaku.
///jako parametr nalezy przekazac problem, tablice z indeksami wybranych elementow oraz rozmiar tablicy z indeksami.

double calculateSkautValue(KnaspackProblem &e, int * indTab, double A_BagSize, int &LastIndex, double &TotalWeight) {

  double currWeight = 0.;
  double myPrice = 0.;
  //cout << "bag size: " << A_BagSize<<endl;

  int index = 0;

  //	e.toString();
  while (index < e.getCountOfElements() && ((currWeight + e.getElementAt(indTab[index]).getWeight()) <= A_BagSize)) {
    currWeight += e.getElementAt(indTab[index]).getWeight();
    myPrice += e.getElementAt(indTab[index]).getPrice();
    //cout <<"\t\tIteracja:"<<index<<" ("<<indTab[index] <<") +Elem:="<<e.getElementAt(indTab[index]).toString() <<endl;
    //cout<< " "<<indTab[index] << ": "<< e.getElementAt(indTab[index]).getWeight()<<" " << e.getElementAt(indTab[index]).getPrice() <<endl;
    index++;
  }
  LastIndex = index;
  TotalWeight = currWeight;
  return myPrice;
};


///funkcja oblicza cene oraz ciezar elementow wybranych. Ich indeksy sa w tablicy indTab, liczba wybranych to A_limit.
/// Ponadto zwraca parametry: A_possible jezeli rozmiar plecaka (A_BagSize) zostal przekroczony.

double calculateValue(KnaspackProblem &e, int * indTab, int A_limit, double A_BagSize, double &TotalWeight, bool &A_possible) {

  double currWeight = 0.;
  double myPrice = 0.;
  A_possible = false;
  //	e.toString();
  for (int i = 0; i < A_limit; i++) {
    currWeight += e.getElementAt(indTab[i]).getWeight();
    myPrice += e.getElementAt(indTab[i]).getPrice();
  }

  if (DEBUG) {
    cout << "#W calculateValue:==";
    sprawdzenieElementow(e, indTab, A_limit);
  }
  if (currWeight <= A_BagSize) {

    A_possible = true;
    TotalWeight = currWeight;
    return myPrice;
  } else {

    A_possible = false;
    TotalWeight = 0.;
    return 0.;
  }

};

BeeStatus beeFly(KnaspackProblem &e, int * indTab, double A_BagSize, int LimitIndex, beeMission whatToDo) {

  //bool success  = false;
  double tempWeight = 0;
  //double tempPrice = 0.;
  bool zmiesciSie = false;

  double temp;
  BeeStatus bb;
  //cout <<"Debug BF.1"<<endl;

  if (LimitIndex < 2) {
    bb.Price = 0.;
    bb.Weight = 0.;
    bb.status = 4;
    bb.success = false;
    return bb;
  }
  int eCountOfElements = e.getCountOfElements();
  int * tab = new int[eCountOfElements];

  for (int i = 0; i < eCountOfElements; i++) {
    tab[i] = indTab[i];
  }
  //e.toString();
  bb.whatTheyDid = whatToDo;
  //cout <<"Debug BF.2"<<endl;
  switch (whatToDo) {

    case CHANGE:
      //dla kazdej pszczoly losujemy nowe elementy do wymiany.
      //cout <<"Debug BF.CH.1"<<endl;
      bb.indexLimit = LimitIndex;
      bb.status = 1;
      //cout <<"Debug BF.CH.1.1"<<endl;
      //cout <<"limitIndex "<< LimitIndex <<endl;
      bb.swapIndex1 = rand() % LimitIndex; //zeby zamieniac element, ktory jest w zbiorze wybranych juz:))
      //cout <<"Debug BF.CH.1.2"<<endl;
      bb.swapIndex2 = rand() % (eCountOfElements - LimitIndex) + LimitIndex;
      //cout <<"Debug BF.CH.1.3"<<endl;
      //robimy swapa:
      //cout <<"Debug BF.CH.1.4"<<endl;
      temp = tab[bb.swapIndex1];
      tab[bb.swapIndex1] = tab[bb.swapIndex2];
      tab[bb.swapIndex2] = temp;
      //cout <<"Debug BF.CH.1.5"<<endl;
      /////////
      //cout <<"Debug BF.CH.1.6"<<endl;
      bb.Price = calculateValue(e, tab, LimitIndex, A_BagSize, tempWeight, zmiesciSie);
      //cout <<"Debug BF.CH.1.7"<<endl;
      bb.success = zmiesciSie;
      bb.Weight = tempWeight;
      //cout <<"Debug BF.CH.2"<<endl;
      //jesli sie nie zmiesci to lipa:
      if (!bb.success) {
        //cout <<"Debug BF.CH.3"<<endl;
        bb.status = 0;
        bb.Price = 0.;
        //cout <<"Debug BF.CH.4"<<endl;
      } else {
        //sprobuj dodac:
        //cout <<"Debug BF.CH.5"<<endl;
        bb.addedIndex = rand() % (eCountOfElements - LimitIndex) + LimitIndex; //losujemy z reszty
        //cout <<"Debug BF.CH.6"<<endl;
        if ((tempWeight + e.getElementAt(tab[bb.addedIndex]).getWeight()) <= A_BagSize) {
          //cout <<"Debug BF.CH.7"<<endl;
          bb.Price += e.getElementAt(tab[bb.addedIndex]).getPrice();
          bb.Weight += e.getElementAt(tab[bb.addedIndex]).getWeight();
          bb.status = 2;
          bb.indexLimit = LimitIndex + 1; //limit zwiekszamy o jeden //ale to chyba nie ma sensu
          //cout <<"Debug BF.CH.8"<<endl;
        }
      }
      //cout <<"Debug BF.CH.9"<<endl;
      break;
    case SUB:
      //cout <<"Debug SUB.3"<<endl;

      //cout <<"Debug SUB.4"<<endl;
      //wywalamy element z listy
      bb.indexLimit = LimitIndex - 1;
      bb.status = 4;

      bb.removedIndex = rand() % LimitIndex; //losujemy element do wywalenia.
      temp = tab[bb.removedIndex];
      //przestawiamy wszystkie elementy //TODO: SPRAWDZIC KOD TEJ PETLI, CZY DOBRZE PRZESTAWIA I WSTAWIA ELEMENT
      for (int i = bb.removedIndex; i < LimitIndex; i++) {
        tab[i] = tab[i + 1];
      }
      //cout <<"Debug SUB.5"<<endl;
      tab[LimitIndex] = temp;

      //robimy zamiane!!!
      //dla kazdej pszczoly losujemy nowe elementy do wymiany.

      bb.swapIndex1 = (rand() % bb.indexLimit); //zeby zamieniac element, ktory jest w zbiorze wybranych juz:))

      bb.swapIndex2 = rand() % (eCountOfElements - bb.indexLimit) + bb.indexLimit;
      //cout <<"Debug SUB.6"<<endl;
      //robimy swapa:
      temp = tab[bb.swapIndex1];
      tab[bb.swapIndex1] = tab[bb.swapIndex2];
      tab[bb.swapIndex2] = temp;
      /////////
      //cout <<"Debug SUB.7"<<endl;
      bb.Price = calculateValue(e, tab, bb.indexLimit, A_BagSize, tempWeight, zmiesciSie);

      bb.Weight = tempWeight;
      bb.success = zmiesciSie;
      //jesli sie nie zmiesci to lipa:
      if (bb.success) {
        bb.status = 3;
      } else {
        bb.Price = 0.;
        bb.status = 4;
      }
      //cout <<"Debug SUB.8"<<endl;
      break;
    default:
      break;
  }
  //cout <<"Debug BF.3"<<endl;
  if (DEBUG && bb.success) {
    cout << "**************" << endl;
    cout << "IN FUNC BeeFly: , W=" << bb.Weight << ", P=" << bb.Price << ", status=" << bb.status << ", Index= " << bb.indexLimit;
    cout << ", (LimitIndex=" << LimitIndex << " )" << endl;
    sprawdzenieElementow(e, tab, bb.indexLimit);
    cout << "**************" << endl;
  }
  //cout <<"Debug BF.4"<<endl;
  delete[] tab;
  return bb;
}

bool tableIsOK(int * tab, int size) {

  bool ok = true;
  //inicjalizacja:
  bool * v = new bool[size];

  for (int i = 0; i < size; i++) {
    v[i] = false;
  }
  //sprawdzenie czy sa wszystkie liczby
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (tab[j] == i) {
        v[i] = true;
        break;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    if (v[i] == false) {
      ok = false;
    }
  }
  delete[] v;
  return ok;
}

double KnaspackProblemSolutinUsingBeeAlgorithm(double BagSize, KnaspackProblem &e, int SkautBeens, int WorkerBeens, int A_counOfIteration) {

  int iteration = 0; //iterator numer iteracji
  int countOfIteration = A_counOfIteration; //liczba zadanych iteracji
  int COUNT_SKAUT = SkautBeens; //liczba skautow
  int COUNT_WORKER = WorkerBeens; //liczba pracownic

  int eCountOfElements = e.getCountOfElements(); //liczba elementow w problemie plecakowym
  if (eCountOfElements == 0) throw string("ERROR: nie ma elementow do wyboru");
  double bestPrice = 0.; //wynik osiagniety przez algorytm
  double bestWeight = 0.;
  int * bestPosition = new int[eCountOfElements];
  int bestPositionIndex = 0; //liczba elementow
  //cout <<"Debug A.1"<<endl;
  //skauci:
  int * localSkautPosition; // wskaznik dla lokalnej pozycji skautow
  int localSkautIndex = 0; //liczba elementow wybranych
  double localSkautWeight = 0.; //tymczasowa masa plec

  double bestSkautPrice; //najlepsza wartosc osiagnieta przez skauta
  double bestSkautWeight = 0.;
  int bestSkautIndex = 0; //indeks liczby elementow w tablicy, znaleziony przez najelpszego skauta?? Czy moze miec zero?? co sie zdarza!? zobacz sprawdzenie!

  //pracownice:
  //	double * workerPrice = new double[COUNT_WORKER];	//tablica z wartosciami osiagnietymi przez pszczoly
  //BeeStatus * bs = new BeeStatus[COUNT_WORKER];		//tablica ze statusami pszczol
  int bestWorkerBee = 0; //indeks najlepszej pszczoly

  char selectedBee = 'S'; //Skaut

  //tempy:
  double tempPrice = 0.;
  double temp;
  enum beeMission tempOrder = CHANGE;
  if (DEBUG)cout << "ALGORYTM PSZCZELI" << endl;

  for (iteration = 0; iteration < countOfIteration; iteration++) {
    //	if(0 == iteration ){
    //	 cout << iteration << "% \r" << endl;
    //	}

    //zerowanie zmiennych:
    bestSkautPrice = bestPrice;
    bestSkautIndex = bestPositionIndex;
    //wysylamy skautow: - losujemy nowe elementy i zapamietujemy pozycje tego ktory znajdzie najlepszy wynik
    //sprawdzamy ile z tych rzeczy wejdzie do plecaka i zapamietujemy indeks ostatniego elementu oraz wartosc plecaka
    //mozemy od razu z wylosowanych wybierac najlepsze, albo nie koniecznie - w granicy i tak powinnismy dostac optimum

    for (int i = 0; i < COUNT_SKAUT; i++) { //po liczbie skautow


      localSkautPosition = getIndexRand(eCountOfElements); //NOWY TEREN

      tempPrice = calculateSkautValue(e, localSkautPosition, BagSize, localSkautIndex, localSkautWeight);

      if (tempPrice > bestSkautPrice) {
        if (INV)cout << "SKAUT " << i << " ZNALAZŁ COŚ LEPSZEGO (W=" << localSkautWeight << " PRICE=" << tempPrice << ")," << endl;
        //if(sprawdzenieElementow(e,localSkautPosition,localSkautIndex) !=localSkautWeight){
        //	throw string("Error 1: Niezgodna wartosc wagi");
        //}
        for (int j = 0; j < eCountOfElements; j++) { //kopiujemy cala tablice
          bestPosition[j] = localSkautPosition[j];
        }
        bestPrice = bestSkautPrice = tempPrice;
        bestPositionIndex = bestSkautIndex = localSkautIndex;
        bestWeight = bestSkautWeight = localSkautWeight;
        //cout << i <<" skaut znalazl cos lepszego!:)"<<endl;
        //cout << "bestSkautIndex =" << bestSkautIndex << endl;
        //cout << "bestSkautPrice ="  << bestSkautPrice << endl;
      }

    }

    delete[] localSkautPosition;

    //skauci skonczyli swoja prace
    //informacja przechowywana jest w: bestPosition, bestSkautPrice, bestSkautIndex.
    //wysylamy robotnice. Zamieniaja dwa elementy indeksami ze zbioru kt
    BeeStatus * bs = new BeeStatus[COUNT_WORKER];


    for (int i = 0; i < COUNT_WORKER; i++) {
      //BeeStatus beeFly(KnaspackProblem &e, int * indTab, double A_BagSize, int LimitIndex,beeDest whatToDo){
      if (rand() % 2 == 1) tempOrder = CHANGE;
      else tempOrder = SUB;
      //e.toString();
      bs[i] = beeFly(e, bestPosition, BagSize, bestSkautIndex, tempOrder);

    }


    //szukamy najlepszej pszczoly:
    tempPrice = bestPrice;
    for (int i = 0; i < COUNT_WORKER; i++) {
      if (bs[i].Price > tempPrice) {
        //cout << "Najlepsza robotnica: "<< i<< ", workerPrice[i]= "<<workerPrice[i] << ", wczesniejsza=" << tempPrice<<endl;
        tempPrice = bs[i].Price;
        bestWorkerBee = i;
      }
    }

    //jezeli najlepsza pszczola ma lepszy wynik od skauta to wybieramy te pozycje za wyjsciowa.
    //zazwyczaj tak bedzie ale trzeba sprawdzic bo to jest sekret sukcesu algorytmu:

    if (bs[bestWorkerBee].Price > bestPrice) {
      if (INV) {

        cout << "PSZCZOŁA " << bestWorkerBee << " ZNALAZŁA COŚ LEPSZEGO (";
        cout << bs[bestWorkerBee].whatTheyDid << ", " << bs[bestWorkerBee].Price << "), W=" << cout << bs[bestWorkerBee].Weight << endl;
      }

      if (!bs[bestWorkerBee].success) {
        throw string("ERROR 3: NAJLEPSZY BEZ SUKCESU! - anomalia");
        //rzuc wyjatkiem
      }
      switch (bs[bestWorkerBee].whatTheyDid) {
        case CHANGE:
          selectedBee = 'C'; //Changed
          //robimy swapa:
          temp = bestPosition[bs[bestWorkerBee].swapIndex1];
          bestPosition[bs[bestWorkerBee].swapIndex1] = bestPosition[bs[bestWorkerBee].swapIndex2];
          bestPosition[bs[bestWorkerBee].swapIndex2] = temp;
          //jesli sie nie zmiesci to lipa:
          if (bs[bestWorkerBee].status == 2) {
            temp = bestPosition[bs[bestWorkerBee].addedIndex];
            bestPosition[bs[bestWorkerBee].addedIndex] = bestPosition[bs[bestWorkerBee].indexLimit - 1];
            bestPosition[bs[bestWorkerBee].indexLimit - 1] = temp;
          }
          break;
        case SUB:
          selectedBee = 'R'; //Removed
          temp = bestPosition[bs[bestWorkerBee].removedIndex];
          //przestawiamy wszystkie elementy //TODO: SPRAWDZIC KOD TEJ PETLI, CZY DOBRZE PRZESTAWIA I WSTAWIA ELEMENT
          for (int i = bs[bestWorkerBee].removedIndex; i < bs[bestWorkerBee].indexLimit; i++) {
            bestPosition[i] = bestPosition[i + 1];
          }
          bestPosition[bs[bestWorkerBee].indexLimit] = temp;

          //jezeli nie bylo swapa to jest znow absurd
          if (!bs[bestWorkerBee].status == 3) {
            throw string("ABSURD!");
          }
          if (bs[bestWorkerBee].status == 3) {
            temp = bestPosition[bs[bestWorkerBee].swapIndex1];
            bestPosition[bs[bestWorkerBee].swapIndex1] = bestPosition[bs[bestWorkerBee].swapIndex2];
            bestPosition[bs[bestWorkerBee].swapIndex2] = temp;
          }
          break;
        default:
          break;
      }
      if (!tableIsOK(bestPosition, eCountOfElements)) throw string("BŁĄD TABLICY- zła permutacja");
      bestPrice = bs[bestWorkerBee].Price;
      bestPositionIndex = bs[bestWorkerBee].indexLimit;
      bestWeight = bs[bestWorkerBee].Weight;

      //if(sprawdzenieElementow(e, bestPosition,bs[bestWorkerBee].indexLimit)!=bestWeight){throw string("ERROR 5: Niezgodna wartosc wagi");};
    }
    //cout <<"Debug A.10"<<endl;
    //cout << "Dzialanie algorytmu pszczelego: bestPrice="<<bestPrice <<" bPI:" << bestPositionIndex << " tW:"<< tempWeight << endl;
    //zapamietanie zmiennej dla najwyzszej wartosci wartosci plecaka.
    cout << selectedBee;
    delete[] bs;
  }
  //cout << A_counOfIteration << "\tskauci="<<  SkautBeens<< "\tpracownice="<< WorkerBeens;
  //cout << "\tPRICE=" << bestPrice << "\tWeight="<< bestWeight<<"\tL.Elemntow=" << bestPositionIndex<<endl;

  /*
  if(sprawdzenieElementow(e,bestPosition, bestPositionIndex) !=bestWeight){
          throw string("Error 2: Niezgodna wartosc wagi: ");
  }
   */
  delete[] bestPosition;
  return bestPrice;
}



