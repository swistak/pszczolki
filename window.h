/* 
 * File:   window.h
 * Author: swistak
 *
 * Created on 28 czerwiec 2010, 16:20
 */

#ifndef _WINDOW_H
#define	_WINDOW_H

#include "ui_window.h"

class BackgroundBee;

class window : public QMainWindow {
    Q_OBJECT

    BackgroundBee * bb;
    bool working;
    bool stoping;
public:
    window();
    virtual ~window();
public slots:
    void startClicked();
    void stopClicked();
    void updateProgress(int currentProgress, int currentPrice);
    void updateResults(double aprox, double bee);
private:
    Ui::window widget;
    void setupGraph();
};

#endif	/* _WINDOW_H */
