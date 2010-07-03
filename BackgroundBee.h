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
public:
    BackgroundBee(Ui::window* ui_widget, KnapsackProblemBee* kp): widget(ui_widget),k1(kp) {};
protected:
    void run();
private:
    Ui::window* widget;
    KnapsackProblemBee* k1;
};

#endif	/* _BACKGROUNDBEE_H */

