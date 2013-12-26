#include <QString>
//#include <QDir>
//#include <QtCore>
//#include <QtGui>
//#include <QMessageBox>
#include <vector>
//#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"

Player::Player()
{
    name="Testplayer";
    money=0;
    karma=0;
    gameovers=0;
    location=0;
    prevLocation=0;
}

void Player::clearItems()
{
    for (int i=0; i<items.size(); i++)
    {
        items.remove(i);
    }
}

void Player::clearStats()
{
    for (int i=0; i<stats.size(); i++)
    {
        stats.remove(i);
    }
}


void Player::removeItem(QString tempItem)
{
    for (int i=0; i<items.size(); i++)
    {
        if (items[i]==tempItem) items.remove(i);
    }
}

void Player::removeStat(QString tempStat)
{
    for (int i=0; i<stats.size(); i++)
    {
        if (stats[i]==tempStat) stats.remove(i);
    }
}

bool Player::hasItem(QString searchItem)
{
    for (int i=0; i<items.size(); i++)
    {
        if (items[i]==searchItem) return true;
    }
    return false;
}

bool Player::isStatus(QString searchStatus)
{
    for (int i=0; i<stats.size(); i++)
    {
        if (stats[i]==searchStatus) return true;
    }
    return false;
}

bool Player::meetsReq(QString req, QString reqName)
{
    if (req=="") return true;
    if (QString::compare(req.at(0), "+")==0)
    {
        if (QString::compare(req.mid(1), "item")==0) for (int i=0; i<items.size(); i++) return hasItem(reqName);
        if (QString::compare(req.mid(1), "status")==0) for (int i=0; i<stats.size(); i++) return isStatus(reqName);
    }
    if (QString::compare(req.at(0), "-")==0)
    {
        if (QString::compare(req.mid(1), "item")==0) for (int i=0; i<items.size(); i++) return !hasItem(reqName);
        if (QString::compare(req.mid(1), "status")==0) for (int i=0; i<stats.size(); i++) return !isStatus(reqName);
    }
    return false;
}
