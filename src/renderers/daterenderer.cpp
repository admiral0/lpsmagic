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


#include "daterenderer.h"
#include "../renderutil.h"
#include "../renderermanager.h"
#include <QImage>
#include <QPainter>
#include <QDate>
#include <QDebug>
#include <QColormap>
#include <QLocale>

QImage DateRenderer::icon()
{
    return RenderUtil::systemIcon("calendar.png");
}

QString DateRenderer::info()
{
    return QString("Displays system local date in format specified");
}

QString DateRenderer::author()
{
    return QString("Radu Andries <admiral0@chakra-project.org>");
}

int DateRenderer::getMaxSize (QString prefix)
{
    return RenderUtil::expectedTextWidth("ddd/mm/yyyy");
}

QString DateRenderer::brief (QString prefix)
{
    return QString("If argument is empty local format is used");
}

QImage* DateRenderer::render (QString prefix)
{
    init();
    QDate date=QDate::currentDate();
    QString text;
    QStringList argv=RenderUtil::parseToken(prefix);
    QString arg;
    if(argv.size()<2){
        arg=localeFormat();
    }else{
      arg=argv.at(1);
      if(arg.isEmpty())
        arg=localeFormat();
    }
    QColormap cmap=QColormap::instance(0);
    uint pix;
    
    text=date.toString(arg);
    QImage *i=new QImage(RenderUtil::expectedTextWidth(text),lineheight,QImage::Format_ARGB32);
    pix=cmap.pixel(RendererManager::background());
    i->fill(pix);
    QPainter p(i);
    p.setBrush(Qt::NoBrush);
    p.setPen(RendererManager::foreground());
    p.setFont(RendererManager::defaultFont());
    p.drawText(0,RenderUtil::baseline(),text);
    qDebug()<<"DATE"<<text;
    return i;
}

void DateRenderer::init()
{
    lineheight=RenderUtil::contentLineHeight();
    
}

QString DateRenderer::localeFormat()
{
  QLocale locale;
  qDebug()<<"LOCALE DATE"<<locale.dateFormat(QLocale::ShortFormat);;
  return locale.dateFormat(QLocale::ShortFormat);
}

