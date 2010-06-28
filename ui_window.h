/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created: Mon Jun 28 23:49:37 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_window
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *KBagSize;
    QLabel *label_8;
    QSpinBox *KNumberOfItems;
    QLabel *label_2;
    QSpinBox *KMaxWeight;
    QLabel *label_3;
    QSpinBox *KMaxPrice;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QSpinBox *BSkauts;
    QLabel *label_5;
    QSpinBox *BWorkers;
    QLabel *label_6;
    QSpinBox *BIterations;
    QSpacerItem *verticalSpacer_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_7;
    QLineEdit *resultAprox;
    QLabel *label_9;
    QLineEdit *resultBee;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QTableWidget *problem;
    QProgressBar *progressBar;
    QPlainTextEdit *console;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuStart;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *window)
    {
        if (window->objectName().isEmpty())
            window->setObjectName(QString::fromUtf8("window"));
        window->resize(938, 599);
        centralwidget = new QWidget(window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        formLayout = new QFormLayout(widget_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        KBagSize = new QSpinBox(widget_2);
        KBagSize->setObjectName(QString::fromUtf8("KBagSize"));
        KBagSize->setMaximum(9999);
        KBagSize->setValue(100);

        formLayout->setWidget(0, QFormLayout::FieldRole, KBagSize);

        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_8);

        KNumberOfItems = new QSpinBox(widget_2);
        KNumberOfItems->setObjectName(QString::fromUtf8("KNumberOfItems"));
        KNumberOfItems->setMaximum(9999);
        KNumberOfItems->setValue(200);

        formLayout->setWidget(1, QFormLayout::FieldRole, KNumberOfItems);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        KMaxWeight = new QSpinBox(widget_2);
        KMaxWeight->setObjectName(QString::fromUtf8("KMaxWeight"));
        KMaxWeight->setMaximum(9999);
        KMaxWeight->setSingleStep(0);
        KMaxWeight->setValue(100);

        formLayout->setWidget(2, QFormLayout::FieldRole, KMaxWeight);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        KMaxPrice = new QSpinBox(widget_2);
        KMaxPrice->setObjectName(QString::fromUtf8("KMaxPrice"));
        KMaxPrice->setMaximum(9999);
        KMaxPrice->setValue(50);

        formLayout->setWidget(3, QFormLayout::FieldRole, KMaxPrice);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::LabelRole, verticalSpacer);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        BSkauts = new QSpinBox(widget_2);
        BSkauts->setObjectName(QString::fromUtf8("BSkauts"));
        BSkauts->setMaximum(9999);
        BSkauts->setValue(100);

        formLayout->setWidget(5, QFormLayout::FieldRole, BSkauts);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_5);

        BWorkers = new QSpinBox(widget_2);
        BWorkers->setObjectName(QString::fromUtf8("BWorkers"));
        BWorkers->setMaximum(9999);
        BWorkers->setValue(100);

        formLayout->setWidget(6, QFormLayout::FieldRole, BWorkers);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_6);

        BIterations = new QSpinBox(widget_2);
        BIterations->setObjectName(QString::fromUtf8("BIterations"));
        BIterations->setMaximum(9999);
        BIterations->setSingleStep(10);
        BIterations->setValue(10);

        formLayout->setWidget(7, QFormLayout::FieldRole, BIterations);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(8, QFormLayout::LabelRole, verticalSpacer_2);

        startButton = new QPushButton(widget_2);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        formLayout->setWidget(9, QFormLayout::LabelRole, startButton);

        stopButton = new QPushButton(widget_2);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        formLayout->setWidget(9, QFormLayout::FieldRole, stopButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(11, QFormLayout::LabelRole, verticalSpacer_3);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_7);

        resultAprox = new QLineEdit(widget_2);
        resultAprox->setObjectName(QString::fromUtf8("resultAprox"));

        formLayout->setWidget(12, QFormLayout::FieldRole, resultAprox);

        label_9 = new QLabel(widget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_9);

        resultBee = new QLineEdit(widget_2);
        resultBee->setObjectName(QString::fromUtf8("resultBee"));

        formLayout->setWidget(13, QFormLayout::FieldRole, resultBee);


        horizontalLayout->addWidget(widget_2);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        problem = new QTableWidget(widget_3);
        if (problem->columnCount() < 2)
            problem->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        problem->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        problem->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        problem->setObjectName(QString::fromUtf8("problem"));

        verticalLayout->addWidget(problem);

        progressBar = new QProgressBar(widget_3);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(100);
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        console = new QPlainTextEdit(widget_3);
        console->setObjectName(QString::fromUtf8("console"));

        verticalLayout->addWidget(console);


        horizontalLayout->addWidget(widget_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout_2->addWidget(graphicsView);


        horizontalLayout->addWidget(widget);

        window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(window);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 938, 21));
        menuStart = new QMenu(menubar);
        menuStart->setObjectName(QString::fromUtf8("menuStart"));
        window->setMenuBar(menubar);
        statusbar = new QStatusBar(window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        window->setStatusBar(statusbar);
        QWidget::setTabOrder(KBagSize, KMaxWeight);
        QWidget::setTabOrder(KMaxWeight, KMaxPrice);
        QWidget::setTabOrder(KMaxPrice, BSkauts);
        QWidget::setTabOrder(BSkauts, BWorkers);
        QWidget::setTabOrder(BWorkers, BIterations);
        QWidget::setTabOrder(BIterations, startButton);
        QWidget::setTabOrder(startButton, stopButton);

        menubar->addAction(menuStart->menuAction());

        retranslateUi(window);

        QMetaObject::connectSlotsByName(window);
    } // setupUi

    void retranslateUi(QMainWindow *window)
    {
        window->setWindowTitle(QApplication::translate("window", "window", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("window", "Rozmiat plecaka", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("window", "Ilo\305\233\304\207 przedmiot\303\263w", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("window", "Maksymalna waga jednego elementu", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("window", "Maksymalna cena jednego elementu", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("window", "Liczba skaut\303\263w:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("window", "Liczba robotnic:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("window", "Ilo\305\233\304\207 iteracji:", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("window", "Start", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("window", "Stop", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("window", "Wynik algorytmu aproksymacyjnego", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("window", "Wynika algorytmu pszczelego", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = problem->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("window", "Cena", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = problem->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("window", "Waga", 0, QApplication::UnicodeUTF8));
        menuStart->setTitle(QApplication::translate("window", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class window: public Ui_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
