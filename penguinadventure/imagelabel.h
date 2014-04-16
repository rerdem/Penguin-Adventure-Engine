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


#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QWidget>
#include <QtWidgets>
#include <QtGui>

class ImageLabel : public QWidget
{
    Q_OBJECT

    public:
        explicit ImageLabel(QWidget *parent = 0);
        const QPixmap* pixmap() const;

    public slots:
        void setPixmap(const QPixmap&);

    protected:
        void resizeEvent(QResizeEvent *);

    private slots:
        void resizeImage();

    private:
        QLabel *label;
};


#endif // IMAGELABEL_H
