/* 
 * File:   window.h
 * Author: swistak
 *
 * Created on 28 czerwiec 2010, 16:20
 */

#ifndef _WINDOW_H
#define	_WINDOW_H

#include "ui_window.h"

class window : public QMainWindow {
    Q_OBJECT
public:
    window();
    virtual ~window();
public slots:
    void startClicked();
    void stopClicked();
private:
    Ui::window widget;
};

#endif	/* _WINDOW_H */
