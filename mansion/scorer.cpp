#include <QString>
#include <QDir>
//#include <QtCore>
//#include <QtGui>
#include <QMessageBox>
#include <vector>
//#include <QFileDialog>

#include "player.h"
#include "gameslide.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



#include "scorer.h"

Scorer::Scorer()
{
    money=0;
    karma=0;
    gameovers=0;
    statuscheck status=misc;

    QFile file;
    QString fileName;
    fileName = QDir::currentPath() + QDir::separator() + "gamefiles" + QDir::separator() + "score.txt";

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //QMessageBox::information(mainwindow, "Error", "Scorer-Error");
        }

        QTextStream in(&file);
        QString tempString;
        QStringList splitter;

        while ((in.status() == QTextStream::Ok) && (!in.atEnd()))
        {
            //read Name
            tempString=in.readLine();
            if (in.status() == QTextStream::ReadPastEnd) break;
            if (QString::compare(tempString, "")==0)
            {
                tempString=in.readLine();
                if (in.status() == QTextStream::ReadPastEnd) break;
            }
            if (QString::compare(tempString, "/items")==0)
            {
                status=items;
                tempString=in.readLine();
                if (in.status() == QTextStream::ReadPastEnd) break;
            }
            if (QString::compare(tempString, "/stats")==0)
            {
                status=stats;
                tempString=in.readLine();
                if (in.status() == QTextStream::ReadPastEnd) break;
            }
            if (status==misc)
            {
                splitter=tempString.split(":");
                qDebug() << "Parse Misc Name " << splitter[0] << endl;
                qDebug() << "Parse Misc Value " << splitter[1].toInt() << endl;
                if (QString::compare(splitter[0], "money", Qt::CaseInsensitive)) money=splitter[1].toInt();
                if (QString::compare(splitter[0], "karma", Qt::CaseInsensitive)) karma=splitter[1].toInt();
                if (QString::compare(splitter[0], "gameovers", Qt::CaseInsensitive)) gameovers=splitter[1].toInt();
            }
            else {
                splitter=tempString.split(":");
                ItemStat tempItemStat;
                if (status==items) tempItemStat.item=true;
                else tempItemStat.item=false;
                tempItemStat.name=splitter[0];
                tempItemStat.value=splitter[1].toInt();
                itemstats.append(tempItemStat);
                qDebug() << "Parse imtestat Name " << splitter[0] << endl;
                qDebug() << "Parse itemstat Value " << splitter[1] << endl;
            }
        }
        file.close();
    }
}

int Scorer::scorePlayer(Player toScore)
{
    int finalScore=0;
    int tempNumber=0;
    qDebug() << "Score Beginning " << finalScore << " " << tempNumber << endl;
    //add money
    tempNumber=toScore.getMoney();
    finalScore=finalScore+(money*tempNumber);
    qDebug() << "Score Money " << finalScore << " " << tempNumber << endl;
    //add karma
    tempNumber=toScore.getKarma();
    finalScore=finalScore+(karma*tempNumber);
    qDebug() << "Score Karma " << finalScore << " " << tempNumber << endl;
    //add gameovers
    tempNumber=toScore.getGameovers();
    finalScore=finalScore+(money*tempNumber);
    qDebug() << "Score Gameovers " << finalScore << " " << tempNumber << endl;
    //add items
    QVector<QString> tempVector=toScore.getItems();
    for (int i=0; i<tempVector.size(); i++)
    {
        for (int j=0; j<itemstats.size(); j++)
        {
            if ((itemstats[j].item) && (QString::compare(tempVector[i], itemstats[j].name, Qt::CaseInsensitive)==0)) finalScore+=itemstats[j].value;
        }
    }
    qDebug() << "Score Items " << finalScore << endl;
    //add stats
    tempVector.clear();
    tempVector=toScore.getStats();
    for (int i=0; i<tempVector.size(); i++)
    {
        for (int j=0; j<itemstats.size(); j++)
        {
            if ((!itemstats[j].item) && (QString::compare(tempVector[i], itemstats[j].name, Qt::CaseInsensitive)==0)) finalScore+=itemstats[j].value;
        }
    }
    qDebug() << "Score Stats " << finalScore << endl;

    return finalScore;
}

