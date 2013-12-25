/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 25. Dec 19:12:44 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QAction *actionQuit;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionAbout;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QString::fromUtf8("mainwindow"));
        mainwindow->resize(400, 300);
        actionQuit = new QAction(mainwindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSave = new QAction(mainwindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionLoad = new QAction(mainwindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionAbout = new QAction(mainwindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(mainwindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainwindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        mainwindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(mainwindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainwindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionAbout);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionQuit);

        retranslateUi(mainwindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), mainwindow, SLOT(close()));

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QApplication::translate("mainwindow", "mainwindow", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("mainwindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("mainwindow", "Save", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("mainwindow", "Load", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("mainwindow", "About", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("mainwindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
