#include "knaspackProblem.h"
#include "element.h"

KnaspackProblem::KnaspackProblem(int A_countOfElements, double maxWeight, double maxPrice) : countOfElements(A_countOfElements) {

  elem = new Element[countOfElements];
  for (int i = 0; i < countOfElements; i++) {
    elem[i].setWeight(((double) rand()) / ((double) RAND_MAX) * maxWeight);
    elem[i].setPrice(((double) rand()) / ((double) RAND_MAX) * maxPrice);
    if (elem[i].getWeight() == 0) i--; //by powtorzyc losowanie
  }
}

Element KnaspackProblem::getElementAt(int index) {
  if ((index < 0) & (index >= countOfElements)) {
    throw string("ERROR: Nieprawidlowe odowlanie sie do indeksu elementu");
  }
  return elem[index];
}

int KnaspackProblem::getCountOfElements() {
  return countOfElements;
}

//sortowanie po cenie jednostkowej

void KnaspackProblem::sortByUnitPrice() {

  Element tempE;
  double maxUnitPrice = 0.;
  int IndexOfMax;

  for (int i = 0; i < countOfElements; i++) {
    maxUnitPrice = 0.;
    for (int j = i; j < countOfElements; j++) {
      if (elem[j].getWeight() == 0) {
        throw string("ERROR: Zerowa masa elementu, a nie mozna dzielic przez zero. Uruchom program jeszcze raz.");
      }
      if ((elem[j].getPrice() / elem[j].getWeight()) > maxUnitPrice) {
        maxUnitPrice = (elem[j].getPrice() / elem[j].getWeight());
        IndexOfMax = j;
      }
    }
    tempE = elem[i];
    elem[i] = elem[IndexOfMax];
    elem[IndexOfMax] = tempE;
  }
}
//posortowanie elementow po cenie

void KnaspackProblem::sortByPrice() {

  Element tempE;
  double maxPrice = 0.;
  int IndexOfMax;
  for (int i = 0; i < countOfElements; i++) {
    maxPrice = 0.;
    for (int j = i; j < countOfElements; j++) {
      if (elem[j].getPrice() > maxPrice) {
        maxPrice = elem[j].getPrice();
        IndexOfMax = j;
      }
    }
    tempE = elem[i];
    elem[i] = elem[IndexOfMax];
    elem[IndexOfMax] = tempE;
  }

}
//znalezienie rozwiazania metoda zachlanna sortowanie po cenie jednostkowej.

double KnaspackProblem::getBetterBruteForceValue(double BagSize) {

  double currWeight = 0.;
  double myPrice = 0.;
  //int index = 0;
  sortByUnitPrice();
  for (int i = 0; i < countOfElements; i++) {
    if ((elem[i].getWeight() + currWeight) <= BagSize) { //jezeli element sie zmiesci to go dokladamy:))
      currWeight += elem[i].getWeight();
      myPrice += elem[i].getPrice();
      //cout << "Dodaje=" << elem[i].toString()<<". ";
    }
  }
  return myPrice;
}

//rozwiazanie metoda zachlanna. Sortowanie po cenie jednostkowej

double KnaspackProblem::getBruteForceValue(double BagSize) {

  double currWeight = 0.;
  double myPrice = 0.;
  //int index = 0;
  sortByPrice();
  for (int i = 0; i < countOfElements; i++) {
    if ((elem[i].getWeight() + currWeight) <= BagSize) { //jezeli element sie zmiesci to go dokladamy:))
      currWeight += elem[i].getWeight();
      myPrice += elem[i].getPrice();
    }
  }
  return myPrice;
}

//funkcja ma tworzyc stringa, ale na razie wypisuje na konsole.

string KnaspackProblem::toString() {
  std::ostringstream result;
  result << "W znajduja sie (waga, cena)" << endl;
  for (int i = 0; i < countOfElements; i++) {
    result << "{" << elem[i].getWeight() << ", " << elem[i].getPrice() << "}" << endl;
  }
  return (result.str());
}
//d-or

KnaspackProblem::~KnaspackProblem() {
  delete[] elem;
}


//end file knaspackProblem.cpp

