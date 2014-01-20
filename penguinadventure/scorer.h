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
