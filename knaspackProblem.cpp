#include "knaspackProblem.h"
#include "element.h"
#include <algorithm>

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

// Return whether first element is greater than the second
bool UnitPriceGreater ( Element elem1, Element elem2 ) {
   return((elem1.getPrice() / elem1.getWeight()) > (elem2.getPrice() / elem2.getWeight()));
}

double KnaspackProblem::getAproximatedValue(double BagSize) {
  double currWeight = 0.;
  double myPrice = 0.;
  //int index = 0;
  std::sort(elem, elem + countOfElements, UnitPriceGreater);

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
  result << "W domie znajduja sie (waga, cena)" << endl;
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

