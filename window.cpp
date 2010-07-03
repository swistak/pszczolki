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
#include "qwt-qt4/qwt_plot.h"

QString d2s(double d);

window::window() {
  widget.setupUi(this);
  connect(widget.startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
  connect(widget.stopButton, SIGNAL(clicked()), this, SLOT(stopClicked()));
  setupGraph();
  working = false;
  stoping = false;
}

window::~window() {
  if (bb) {
    delete bb;
  }
}

void window::startClicked() {
  if (working) return;
  working = true;

  widget.progressBar->setMaximum(widget.BIterations->value());

  widget.startButton->setEnabled(false);
  widget.stopButton->setEnabled(true);

  bb = new BackgroundBee(widget);
  QObject::connect(bb, SIGNAL(finishedIteration(int, int)), this, SLOT(updateProgress(int, int)));
  QObject::connect(bb, SIGNAL(finishedWorking(double, double)), this, SLOT(updateResults(double, double)));

  widget.qwtPlot->removeData();

  bb -> start();
}

void window::stopClicked() {
  if (!working) return;
  stoping = true; working = false;
  bb -> stopWorking();
}

void window::setupGraph() {
  widget.qwtPlot->setTitle(QString::fromUtf8("Efektywność algorytmu pszczelego"));

  // Show the axes
  widget.qwtPlot->setAxisTitle(widget.qwtPlot->xBottom, "Iteracje");
  widget.qwtPlot->setAxisTitle(widget.qwtPlot->yLeft, QString::fromUtf8("Wartość plecaka"));

  widget.qwtPlot->maxX = 100;
  widget.qwtPlot->maxY = 100;
  widget.qwtPlot->resizeIfNeeded(200, 200);

  // Show the plots
  widget.qwtPlot->replot();
}

void window::updateProgress(int currentProgress, int currentPrice) {
  widget.progressBar->setValue(currentProgress + 1);

  widget.qwtPlot->appendData(currentProgress, currentPrice);
}

void window::updateResults(double aprox, double bee) {
  working = false;
  
  widget.resultAprox->setText(d2s(aprox));
  widget.resultBee->setText(d2s(bee));
  widget.startButton->setEnabled(true);
  widget.stopButton->setEnabled(false);
}