#ifndef SCORER_H
#define SCORER_H

#include <QString>
#include "player.h"

struct ItemStat {
    bool item;
    QString name;
    int value;
};


class Scorer
{
    public:
        Scorer();
        int scorePlayer(Player toScore);

    private:
        QVector<ItemStat> itemstats;
        int money;
        int karma;
        int gameovers;
        enum statuscheck {misc, items, stats};
};

#endif // SCORER_H
