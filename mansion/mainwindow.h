#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>
#include <iostream>
using namespace std;
#include <fstream>
#include <QtGui>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
    Player *currentplayer;

    QWidget *centralWidget;
    QGridLayout *mainBox;
    QTextEdit *slideTextEdit;
    QLabel *slideImageLabel;
    QPushButton *inventoryButton;
    QPushButton *but01, *but02, *but03, *but04, *but05,
                *but06, *but07, *but08, *but09, *but10;
    int opt01, opt02, opt03, opt04, opt05,
        opt06, opt07, opt08, opt09, opt10;

    
private:
    Ui::mainwindow *ui;
    QSignalMapper *signalMapper;
    void initialize();
    void game();

private slots:
    void changeSlide(const int goalID);
    void save();
    void load();
    //void on_actionSave_triggered();
    //void on_actionLoad_triggered();
    //void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
