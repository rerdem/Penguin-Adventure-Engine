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


#include <QApplication>
#include <QString>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <cstdlib> //itoa()
#include "player.h"
#include "inventoryscreen.h"


inventoryScreen::inventoryScreen(QDialog *parent) :
    QDialog(parent)
{
    okButton = new QPushButton("Close");
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));

    nameLabel=new QLabel("Name: ");
    itemLabel=new QLabel("Items: ");
    statLabel=new QLabel("Stats: ");
    moneyLabel=new QLabel("Money: ");
    karmaLabel=new QLabel("Karma: ");
    gameoverLabel=new QLabel("Game Overs: ");

    itemlist = new QTextEdit(this);
    itemlist->setReadOnly(true);
    statlist = new QTextEdit(this);
    statlist->setReadOnly(true);
    moneyAmount = new QLineEdit(this);
    moneyAmount->setReadOnly(true);
    karmaAmount = new QLineEdit(this);
    karmaAmount->setReadOnly(true);
    gameoverAmount = new QLineEdit(this);
    gameoverAmount->setReadOnly(true);

    layout=new QGridLayout(this);
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(itemLabel, 1, 0);
    layout->addWidget(statLabel, 1, 2);
    layout->addWidget(itemlist, 2, 0, 1, 2);
    layout->addWidget(statlist, 2, 2, 1, 2);
    layout->addWidget(moneyLabel, 3, 0);
    layout->addWidget(moneyAmount, 3, 1);
    layout->addWidget(karmaLabel, 4, 0);
    layout->addWidget(karmaAmount, 4, 1);
    layout->addWidget(gameoverLabel, 5, 0);
    layout->addWidget(gameoverAmount, 5, 1);
    layout->addWidget(okButton, 5, 3);
    this->setLayout(layout);
}


void inventoryScreen::showPlayer(Player showPlayer)
{
    itemlist->clear();
    statlist->clear();
    moneyAmount->clear();
    karmaAmount->clear();
    gameoverAmount->clear();

    QVector<QString> tempVector;
    nameLabel->setText("Name: "+showPlayer.getName());
    //fill items
    tempVector=showPlayer.getItems();
    for (int i=0; i<tempVector.size(); i++) itemlist->append(tempVector[i]);
    //fill stats
    tempVector=showPlayer.getStats();
    for (int i=0; i<tempVector.size(); i++) statlist->append(tempVector[i]);
    //fill money, karma, gameovers
    char temp[15];
    itoa(showPlayer.getMoney(), temp, 10);
    moneyAmount->setText(temp);
    itoa(showPlayer.getKarma(), temp, 10);
    karmaAmount->setText(temp);
    itoa(showPlayer.getGameovers(), temp, 10);
    gameoverAmount->setText(temp);
}
