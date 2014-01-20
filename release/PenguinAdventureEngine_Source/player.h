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


#ifndef PLAYER_H
#define PLAYER_H

#include <QString>


class Player
{
    public:
        Player();

        void setName(QString tempName) {name=tempName;}
        QString getName() {return name;}

        void addItem(QString tempItem) {items.append(tempItem);}
        void removeItem(QString tempItem);
        void removeRandomItem();
        void clearItems();
        QVector<QString>& getItems() {return items;}

        void addStat(QString tempStat) {stats.append(tempStat);}
        void removeStat(QString tempStat);
        void removeRandomStat();
        void clearStats();
        QVector<QString>& getStats() {return stats;}

        void setMoney(int tempMoney) {money=tempMoney;}
        int getMoney() {return money;}

        void setKarma(int tempKarma) {karma=tempKarma;}
        int getKarma() {return karma;}

        void setGameovers(int tempGameovers) {gameovers=tempGameovers;}
        int getGameovers() {return gameovers;}

        void setLocation(int tempLocation) {location=tempLocation;}
        int getLocation() {return location;}

        void setPrevLocation(int tempLocation) {prevLocation=tempLocation;}
        int getPrevLocation() {return prevLocation;}

        bool hasItem(QString searchItem);
        bool isStatus(QString searchStatus);
        bool meetsReq(QString req, QString reqName);


    private:
        QString name;
        QVector<QString> items;
        QVector<QString> stats;
        int money;
        int karma;
        int gameovers;
        int location;
        int prevLocation;
        int randomInt(int low, int high);
};

#endif // PLAYER_H
