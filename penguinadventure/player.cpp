#include <QString>
#include <QVector>

#include <QGlobal.h>
#include <QTime>

#include "mainwindow.h"
#include "player.h"


Player::Player()
{
    // Create seed for the random
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    name="Player01";
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
    items.clear();
}


void Player::clearStats()
{
    for (int i=0; i<stats.size(); i++)
    {
        stats.remove(i);
    }
    stats.clear();
}


void Player::removeItem(QString tempItem)
{
    for (int i=0; i<items.size(); i++)
    {
        if (QString::compare(items[i], tempItem, Qt::CaseInsensitive)==0) items.remove(i);
    }
}

void Player::removeRandomItem()
{
    if (!items.isEmpty())
        items.remove(randomInt(0, (items.size()-1)));
}


void Player::removeStat(QString tempStat)
{
    for (int i=0; i<stats.size(); i++)
    {
        if (QString::compare(stats[i], tempStat, Qt::CaseInsensitive)==0) stats.remove(i);
    }
}

void Player::removeRandomStat()
{
    if (!stats.isEmpty())
        stats.remove(randomInt(0, (stats.size()-1)));
}


bool Player::hasItem(QString searchItem)
{
    for (int i=0; i<items.size(); i++)
    {
        if (QString::compare(items[i], searchItem, Qt::CaseInsensitive)==0) return true;
    }
    return false;
}


bool Player::isStatus(QString searchStatus)
{
    for (int i=0; i<stats.size(); i++)
    {
        if (QString::compare(stats[i], searchStatus, Qt::CaseInsensitive)==0) return true;
    }
    return false;
}


bool Player::meetsReq(QString req, QString reqName)
{
    if (req=="") return true;
    if (QString::compare(req.at(0), "+")==0)
    {
        if (QString::compare(req.mid(1), "item", Qt::CaseInsensitive)==0) for (int i=0; i<items.size(); i++) return hasItem(reqName);
        if (QString::compare(req.mid(1), "status", Qt::CaseInsensitive)==0) for (int i=0; i<stats.size(); i++) return isStatus(reqName);
    }
    if (QString::compare(req.at(0), "-")==0)
    {
        if (QString::compare(req.mid(1), "item", Qt::CaseInsensitive)==0) for (int i=0; i<items.size(); i++) return !hasItem(reqName);
        if (QString::compare(req.mid(1), "status", Qt::CaseInsensitive)==0) for (int i=0; i<stats.size(); i++) return !isStatus(reqName);
    }
    return false;
}

int Player::randomInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}
