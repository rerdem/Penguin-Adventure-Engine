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
        void clearItems();
        QVector<QString>& getItems() {return items;}

        void addStat(QString tempStat) {stats.append(tempStat);}
        void removeStat(QString tempStat);
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
};

#endif // PLAYER_H
