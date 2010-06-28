/* 
 * File:   Element.cpp
 * Author: swistak
 * 
 * Created on 28 czerwiec 2010, 16:04
 */

#include "element.h"

void Element::setWeight(double A_weight) {
  weight = A_weight;
}

void Element::setPrice(double A_price) {
  price = A_price;
}

Element::Element(double A_weight, double A_price) {
  weight = A_weight;
  price = A_price;
}

double Element::getWeight() {
  return weight;
}

double Element::getPrice() {
  return price;
}

string Element::toString() {
  std::ostringstream strs;
  strs << "{" << weight << ", " << price << ", " << price/weight <<"}";
  
  return strs.str();
}