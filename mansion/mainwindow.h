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
#include "gameslide.h"
#include "player.h"
#include "scorer.h"
#include "inventoryscreen.h"


namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();
    
private:
    Ui::mainwindow *ui;

    QVector<GameSlide*> slides;
    Player *currentplayer;
    Scorer *referee;

    QWidget *centralWidget;
    QGridLayout *mainBox;
    QTextEdit *slideTextEdit;
    QLabel *slideImageLabel;
    QPushButton *inventoryButton;
    QPushButton *but01, *but02, *but03, *but04, *but05,
                *but06, *but07, *but08, *but09, *but10;
    int opt01, opt02, opt03, opt04, opt05,
        opt06, opt07, opt08, opt09, opt10;

    QString xmlpath;
    QString imgpath;
    QSignalMapper *signalMapper;

    void createInterface();
    void initialize();
    void game();

private slots:
    void changeSlide(const int goalID);
    void save();
    void load();
    void about();
    void reset();
    void showInventory();
};

#endif // MAINWINDOW_H
