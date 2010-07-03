/*
 * File:   window.cpp
 * Author: swistak
 *
 * Created on 28 czerwiec 2010, 16:20
 */

#include "knapsackProblem.h"
#include "beesAlgorithm.h"
#include "window.h"
#include "common.h"
#include "BackgroundBee.h"


window::window() {
  widget.setupUi(this);
  connect(widget.startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
}

window::~window() {
  if(bb) {
    delete bb;
  }
}

QString d2s(double d) {
  std::ostringstream strs;
  strs << d;
  return (QString(strs.str().data()));
}

void window::startClicked() {
  int maxWeight = widget.KMaxWeight->value();
  int maxPrice = widget.KMaxPrice->value();
  int numberOfItems = widget.KNumberOfItems->value();

  KnapsackProblemBee k1(numberOfItems, maxWeight, maxPrice);
  k1.SkautBeens = widget.BSkauts->value();
  k1.WorkerBeens = widget.BWorkers->value();
  k1.A_counOfIteration = widget.BIterations->value();

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

  widget.progressBar->setMaximum(widget.BIterations->value());

  
  cout << "1";
  bb -> start();
}

void window::stopClicked() { }
