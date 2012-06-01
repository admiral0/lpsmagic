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


#include "iconrenderer.h"
#include "../renderutil.h"
#include <QStringList>
#include <QPainter>


void IconRenderer::init()
{
  //NOP Builtin module
}

QImage* IconRenderer::render(QString prefix)
{
    int lh=RenderUtil::lineHeight();
    QImage *img=new QImage(lh,lh,QImage::Format_ARGB32);
    RenderUtil::fillImage(img);
    QString name=RenderUtil::parseToken(prefix).at(1);
    QString path=RenderUtil::resource(name);
    QPainter p(img);
    QImage pimg(path);
    int ox=0;
    int oy=0;
    if(pimg.size().height()>img->size().height()||pimg.size().width()>img->size().width()){
      pimg=pimg.scaled(img->width()-2,img->height()-2);
      ox=oy=1;
    }else{
      ox=(img->size().width()-pimg.size().width())/2;
      oy=(img->size().height()-pimg.size().height())/2;
    }
    p.drawImage(ox,oy,pimg);
    return img;
}

QString IconRenderer::brief(QString prefix)
{
   QString msg("This icon registers prefix %icon and is used like in the following example:</br><pre>%icon{file.png}</pre><br>This will search lpsmagic and user directories.<br>");
   msg.append("If an icon is bigger it will be scaled. If it's too little it will be centered vertically and horizontally.");
   return msg;
}

int IconRenderer::getMaxSize(QString prefix)
{
    return RenderUtil::lineHeight();
}

QString IconRenderer::author()
{
    return QString("Radu Andries <admiral0@chakra-project.org>");
}

QString IconRenderer::info()
{
    return QString("A basic plugin that displays icons from resources.");
}

QImage IconRenderer::icon()
{
    return RenderUtil::systemIcon("gear.png");
}

IconRenderer::IconRenderer()
{
  //NOP
}

IconRenderer::~IconRenderer()
{
  //NOP
}


#include "iconrenderer.moc"