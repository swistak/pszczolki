/*
 * File:   window.cpp
 * Author: swistak
 *
 * Created on 28 czerwiec 2010, 16:20
 */

#include "window.h"
#include "common.h"
#include "knaspackProblem.h"
#include "beesAlgorithm.h"

window::window() {
  widget.setupUi(this);
  connect(widget.startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
}

window::~window() { }

QString d2s(double d) {
  std::ostringstream strs;
  strs << d;
  return (QString(strs.str().data()));
}

void window::startClicked() {
  int bagSize = widget.KBagSize->value();
  int maxWeight = widget.KMaxWeight->value();
  int maxPrice = widget.KMaxPrice->value();
  int numberOfItems = widget.KNumberOfItems->value();

  KnaspackProblem k1(numberOfItems, maxWeight, maxPrice);

  double result;
  Element element;
    QString text;

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

  try {
    result = KnaspackProblemSolutinUsingBeeAlgorithm(bagSize,
                                            k1,
                                            widget.BSkauts->value(),
                                            widget.BWorkers->value(),
                                            widget.BIterations->value()
                                            );

    text = d2s(result);
    widget.resultBee->setText(text);
    
    result = k1.getAproximatedValue(bagSize);
    text = d2s(result);
    widget.resultAprox->setText(text);
  } catch (string &e) {
    text = e.data();
    widget.console->appendPlainText(text);
  }
}

void window::stopClicked() { }
