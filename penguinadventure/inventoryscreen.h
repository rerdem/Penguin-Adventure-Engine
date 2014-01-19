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


#ifndef INVENTORYSCREEN_H
#define INVENTORYSCREEN_H

#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include "player.h"


class inventoryScreen : public QDialog
{
    Q_OBJECT

    public:
        explicit inventoryScreen(QDialog *parent = 0);
        void showPlayer(Player showPlayer);

    private:
        QPushButton *okButton;
        QLabel *nameLabel, *itemLabel, *statLabel, *moneyLabel, *karmaLabel, *gameoverLabel;
        QLineEdit *moneyAmount, *karmaAmount, *gameoverAmount;
        QTextEdit *itemlist, *statlist;
        QGridLayout *layout;
};

#endif // INVENTORYSCREEN_H
