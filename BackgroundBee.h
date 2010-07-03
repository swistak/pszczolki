/* 
 * File:   BackgroundBee.h
 * Author: swistak
 *
 * Created on 3 lipiec 2010, 02:15
 */

#ifndef _BACKGROUNDBEE_H
#define	_BACKGROUNDBEE_H

#include "common.h"

class KnapsackProblemBee;

class BackgroundBee : public QThread {
    Q_OBJECT

    bool stop;
public:
    BackgroundBee(Ui::window ui_widget): widget(ui_widget) {};
    bool nextIteration(int currentIteration, int currentPrice) {
      emit finishedIteration(currentIteration, currentPrice);
      return(stop);
    }
signals:
    void finishedIteration(int currentIteration, int currentPrice);
    void finishedWorking(double aprox, double bee);
public slots:
    void stopWorking();
protected:
    void run();
private:
    Ui::window widget;
};

#endif	/* _BACKGROUNDBEE_H */

