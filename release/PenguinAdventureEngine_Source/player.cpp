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
    return qrand() % ((high + 1) - low) + low;
}
