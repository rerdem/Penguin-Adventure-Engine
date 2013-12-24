#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>
#include <iostream>
using namespace std;
#include <fstream>
#include <QtGui>
//#include <QLineEdit>
#include "gameslide.h"
#include "player.h"

namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

    QString xmlpath;
    QString imgpath;
    QVector<GameSlide*> slides;
    Player currentplayer;
    QTextEdit *testEdit;
    QLabel testLabel;
    
private:
    Ui::mainwindow *ui;
    void initialize();

private slots:
    //void on_actionSave_triggered();
    //void on_actionLoad_triggered();
    //void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
