/*
    Copyright (C) 2012  Radu Andries <admiral0@tuxfamily.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef RENDEREDIMAGE_H
#define RENDEREDIMAGE_H

#include <QImage>
#include <QStringList>


class RenderedImage : public QObject
{
Q_OBJECT
public:
    RenderedImage(QString token);
    virtual ~RenderedImage();
    virtual bool operator==(const RenderedImage& other) const;
    QImage* getImage();
signals:
    void needsUpdate();
public slots:
    void update();
private slots:
    void invalidatePrefix(QString prefix);
private:
    QString token;
    QString prefix;
    QStringList args;
    QStringList renderargs;
    bool centered;
    //Info in image is still valid? 
    bool valid;
    //Update image ignoring timers if this image becomes outdated
    bool important;
    //Absolute positioning enabled
    bool absolute;
    //Container for position
    QRect boundingRect;
    QImage *image;
    
};

#endif // RENDEREDIMAGE_H
