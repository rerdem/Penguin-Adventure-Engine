#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
//#include <QtGui>

class Player
{
    public:
        Player();

        void setName(QString tempName) {name=tempName;}
        QString getName() {return name;}

        void addItems(QString tempItem) {items.append(tempItem);}
        void removeItems(QString tempItem);
        QVector<QString>& getItems() {return items;}

        void addStats(QString tempStat) {stats.append(tempStat);}
        void removeStats(QString tempStat);
        QVector<QString>& getStats() {return stats;}

        void setMoney(int tempMoney) {money=tempMoney;}
        int getMoney() {return money;}

        void setKarma(int tempKarma) {karma=tempKarma;}
        int getKarma() {return karma;}

        void setGameovers(int tempGameovers) {gameovers=tempGameovers;}
        int getGameovers() {return gameovers;}

        void setLocation(int tempLocation) {location=tempLocation;}
        int getLocation() {return location;}

        bool hasItem(QString searchItem);
        bool isStatus(QString searchStatus);


    private:
        QString name;
        QVector<QString> items;
        QVector<QString> stats;
        int money;
        int karma;
        int gameovers;
        int location;
};

#endif // PLAYER_H
