/* 
 * File:   BackgroundBee.cpp
 * Author: swistak
 * 
 * Created on 3 lipiec 2010, 02:15
 */

#include "common.h"
#include "BackgroundBee.h"

QString d2s2(double d) {
  std::ostringstream strs;
  strs << d;
  return (QString(strs.str().data()));
}

void BackgroundBee::run() {
  double result;
  QString text;
  cout << "2";
  int bagSize = widget->KBagSize->value();

  try {
    result = k1->getBeeValue(bagSize);

    text = d2s2(result);
    widget->resultBee->setText(text);

    result = k1->getAproximatedValue(bagSize);
    text = d2s2(result);
    widget->resultAprox->setText(text);
  } catch (string &e) {
    text = e.data();
    widget->console->appendPlainText(text);
  }
}
