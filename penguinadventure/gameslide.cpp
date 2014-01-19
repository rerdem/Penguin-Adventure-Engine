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
#include "mainwindow.h"
#include "gameslide.h"


GameSlide::GameSlide()
{
    id=0;
    img="";
    txt="";
    money=0;
    karma=0;
    gameover=false;
}


void GameSlide::addOptions(int tempGoal, QString tempReq, QString tempName, QString tempTxt)
{
    Option tempOption;
    tempOption.goal=tempGoal;
    tempOption.req=tempReq;
    tempOption.name=tempName;
    tempOption.txt=tempTxt;
    options.append(tempOption);
}
