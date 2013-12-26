#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QVector>
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
                //qDebug() << "Parse Misc Name " << splitter[0] << endl;
                //qDebug() << "Parse Misc Value " << splitter[1].toInt() << endl;
                if (QString::compare(splitter[0], "money", Qt::CaseInsensitive)==0) money=splitter[1].toInt();
                if (QString::compare(splitter[0], "karma", Qt::CaseInsensitive)==0) karma=splitter[1].toInt();
                if (QString::compare(splitter[0], "gameovers", Qt::CaseInsensitive)==0) gameovers=splitter[1].toInt();
                //qDebug() << "Parse MiscSave money karma over" << endl;
                //qDebug() << "Parse MiscSave " << money << " " << karma << " " << gameovers << endl;
            }
            else {
                splitter=tempString.split(":");
                ItemStat tempItemStat;
                if (status==items) tempItemStat.item=true;
                else tempItemStat.item=false;
                tempItemStat.name=splitter[0];
                tempItemStat.value=splitter[1].toInt();
                itemstats.append(tempItemStat);
                //qDebug() << "Parse itemstat Name " << splitter[0] << endl;
                //qDebug() << "Parse item " << tempItemStat.item << endl;
                //qDebug() << "Parse itemstat Value " << splitter[1] << endl;
            }
        }
        file.close();
    }
}


int Scorer::scorePlayer(Player toScore)
{
    int finalScore=0;
    int tempNumber=0;

    //add money
    tempNumber=toScore.getMoney();
    finalScore=finalScore+(money*tempNumber);

    //add karma
    tempNumber=toScore.getKarma();
    finalScore=finalScore+(karma*tempNumber);

    //add gameovers
    tempNumber=toScore.getGameovers();
    finalScore=finalScore+(gameovers*tempNumber);

    //add items
    QVector<QString> tempVector=toScore.getItems();
    for (int i=0; i<tempVector.size(); i++)
    {
        for (int j=0; j<itemstats.size(); j++)
        {
            if ((itemstats[j].item) && (QString::compare(tempVector[i], itemstats[j].name, Qt::CaseInsensitive)==0))
            {
                finalScore+=itemstats[j].value;
                break;
            }
        }
    }

    //add stats
    tempVector.clear();
    tempVector=toScore.getStats();
    for (int i=0; i<tempVector.size(); i++)
    {
        for (int j=0; j<itemstats.size(); j++)
        {
            if (!itemstats[j].item)
                if (QString::compare(tempVector[i], itemstats[j].name, Qt::CaseInsensitive)==0)
                {
                    finalScore+=itemstats[j].value;
                    break;
                }
        }
    }

    return finalScore;
}

