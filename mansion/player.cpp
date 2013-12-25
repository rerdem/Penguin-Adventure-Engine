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
}

void Player::removeItems(QString tempItem)
{
    for (int i=0; i<items.size(); i++)
    {
        if (items[i]==tempItem) items.remove(i);
    }
}

void Player::removeStats(QString tempStat)
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
