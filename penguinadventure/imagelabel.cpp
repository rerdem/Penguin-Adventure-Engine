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


#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) :
    QWidget(parent)
{
    label = new QLabel(this);
    label->setScaledContents(true);
    label->setFixedSize(0,0);
}

void ImageLabel::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    resizeImage();
}

const QPixmap* ImageLabel::pixmap() const {
    return label->pixmap();
}

void ImageLabel::setPixmap (const QPixmap &pixmap){
    label->setPixmap(pixmap);
    resizeImage();
}

void ImageLabel::resizeImage() {
    QSize pixSize = label->pixmap()->size();
    pixSize.scale(size(), Qt::KeepAspectRatio);
    label->setFixedSize(pixSize);
}
