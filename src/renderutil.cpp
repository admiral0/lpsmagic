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


#include "renderutil.h"
#include <QFile>
#include <QPainter>
#include <QColormap>
#include <QRegExp>
#include "renderermanager.h"
#include <QDir>
#include <QFile>

#define SYS_DIR "/opt/lpsmagic/icons/"
#define USER_DIR "/home/user/MyDocs/lpsmagic"

bool RenderUtil::drawIcon (QString path, QImage* image, QPoint point, QSize size)
{
    QFile f(path);
    if(!f.exists()){
        return false;
    }
    QImage icon(path);
    return drawIcon(icon,image,point,size);
}

bool RenderUtil::drawIcon (QImage icon, QImage* image, QPoint point, QSize size)
{
    QPainter painter(image);
    QSize iconSize=icon.size();
    if(size!=QSize() && size!=iconSize){
        icon=icon.scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
    painter.drawImage(point,icon);
}

int RenderUtil::lineHeight()
{
    
    return contentLineHeight()+(2*RendererManager::verticalSpacing());
}

int RenderUtil::contentLineHeight()
{
    QFont font=RendererManager::defaultFont();
    QFontMetrics fm(font);
    return fm.height();
}

int RenderUtil::expectedTextWidth (QString text)
{
    QFontMetrics fm(RendererManager::defaultFont());
    return fm.boundingRect(text).width();
    
}

QStringList RenderUtil::parseToken (QString token)
{
    QRegExp tokenRegex;
    tokenRegex.setPatternSyntax(QRegExp::RegExp2);
    tokenRegex.setMinimal(true);
    tokenRegex.setPattern("%(\\[.*\\])?([A-Za-z]*)(\\{.*\\})");
    int found=tokenRegex.indexIn(token);
    if(found==-1)
        return QStringList();
    QString args=tokenRegex.cap(3);
    QStringList raw=args.split("}{");
    raw.first().remove('{');
    raw.last().remove('}');
    raw.insert(0,tokenRegex.cap(2));
    return raw;
}

int RenderUtil::baseline()
{
    QFontMetrics fm(RendererManager::defaultFont());
    return fm.ascent();
}
QString RenderUtil::resource(QString name)
{
    QDir sys(SYS_DIR);
    QDir usr(USER_DIR);
    QFile fusr(usr.filePath(name));
    if(fusr.exists()){
      return fusr.fileName();
    }
    fusr.setFileName(sys.filePath(name));
    if(fusr.exists()){
      return fusr.fileName();
    }
    return "";
}

QImage RenderUtil::systemIcon(QString name)
{
  return QImage(QString(SYS_DIR)+name);
}

void RenderUtil::fillImage(QImage* img, const QColor color)
{
  QColormap cmap=QColormap::instance(0);
  img->fill(cmap.pixel(color));
}
