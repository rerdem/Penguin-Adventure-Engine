#ifndef GAMESLIDE_H
#define GAMESLIDE_H

#include <QString>
//#include <QtGui>

struct Option {
    int goal;
    QString req;
    QString name;
    QString txt;
};

class GameSlide
{
    public:
        GameSlide();
        void setId(int tempId) {id=tempId;}
        int getId() {return id;}

        void setImg(QString tempImg) {img=tempImg;}
        QString getImg() {return img;}

        void setTxt(QString tempTxt) {txt=tempTxt;}
        QString getTxt() {return txt;}

        void addItems(QString tempItem) {items.append(tempItem);}
        QVector<QString>& getItems() {return items;}

        void addStats(QString tempStat) {stats.append(tempStat);}
        QVector<QString>& getStats() {return stats;}

        void setMoney(int tempMoney) {money=tempMoney;}
        int getMoney() {return money;}

        void setKarma(int tempKarma) {karma=tempKarma;}
        int getKarma() {return karma;}

        void setGameover(bool tempGameover) {gameover=tempGameover;}
        int getGameover() {return gameover;}

        void addOptions(int tempGoal, QString tempReq, QString tempName, QString tempTxt);
        QVector<Option>& getOptions() {return options;}


    private:
        int id;
        QString img;
        QString txt;
        QVector<QString> items;
        QVector<QString> stats;
        int money;
        int karma;
        bool gameover;
        QVector<Option> options;

};


#endif // GAMESLIDE_H
