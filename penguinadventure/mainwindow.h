/**
    Copyright 2014 Rona Erdem

    This file is part of the Penguin Adventure Engine.

    The Penguin Adventure Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Penguin Adventure Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the Penguin Adventure Engine.  If not, see <http://www.gnu.org/licenses/>.

**/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <iostream>
using namespace std;
#include <fstream>
#include <QtWidgets>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gameslide.h"
#include "player.h"
#include "scorer.h"
#include "inventoryscreen.h"
#include "imagelabel.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();
    
private:
    QVector<GameSlide*> slides;
    Player *currentplayer;
    Scorer *referee;

    QWidget *centralWidget;
    QGridLayout *mainBox;
    QTextEdit *slideTextEdit;
    ImageLabel *slideImageLabel;
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
