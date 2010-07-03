/* 
 * File:   BackgroundBee.cpp
 * Author: swistak
 * 
 * Created on 3 lipiec 2010, 02:15
 */

#include "common.h"
#include "BackgroundBee.h"
#include "beesAlgorithm.h"

QString d2s(double d) {
  std::ostringstream strs;
  strs << d;
  return (QString(strs.str().data()));
}

void BackgroundBee::stopWorking() {
  stop = true;
}

void BackgroundBee::run() {
  stop = false;
  
  int maxWeight = widget.KMaxWeight->value();
  int maxPrice = widget.KMaxPrice->value();
  int numberOfItems = widget.KNumberOfItems->value();

  KnapsackProblemBee k1(numberOfItems, maxWeight, maxPrice);
  k1.SkautBeens = widget.BSkauts->value();
  k1.WorkerBeens = widget.BWorkers->value();
  k1.A_counOfIteration = widget.BIterations->value();
  k1.widget = widget;
  k1.bb = this;

  Element element;

  for (int y = 0; y < k1.getCountOfElements(); y++) {
    if (!widget.problem->item(y, 0)) {
      int lastRow = widget.problem->rowCount();
      widget.problem->insertRow(lastRow);
    }

    element = k1.getElementAt(y);
    QTableWidgetItem *newItem = new QTableWidgetItem(d2s(element.getPrice()));
    widget.problem->setItem(y, 0, newItem);
    newItem = new QTableWidgetItem(d2s(element.getWeight()));
    widget.problem->setItem(y, 1, newItem);
  }

  double aprox, bee;
  QString text;
  int bagSize = widget.KBagSize->value();

  try {
    bee = k1.getBeeValue(bagSize);
    aprox = k1.getAproximatedValue(bagSize);
    
  } catch (string &e) {
    text = e.data();
    widget.console->appendPlainText(text);
  }

  emit finishedWorking(aprox, bee);
}
