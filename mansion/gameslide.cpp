#include <QString>
//#include <QDir>
//#include <QtCore>
//#include <QtGui>
//#include <QMessageBox>
#include <vector>
//#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameslide.h"

GameSlide::GameSlide()
{
    id=0;
    img="";
    txt="";
    money=0;
    karma=0;
}


void GameSlide::addOptions(int tempGoal, QString tempReq, QString tempName, QString tempTxt)
{
    Option tempOption;
    tempOption.goal=tempGoal;
    tempOption.req=tempReq;
    tempOption.name=tempName;
    tempOption.txt=tempTxt;
    options.append(tempOption);
}
