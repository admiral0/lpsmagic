/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Radu Andries <email>

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


#include "dumbtext.h"
#include "../renderutil.h"
#include "../renderermanager.h"
#include <QPainter>

DumbText::~DumbText()
{
  //NOP
};

void DumbText::init()
{
  //NOP
}

QImage* DumbText::render(QString prefix)
{
    
  QString text=RenderUtil::parseToken(prefix).at(1);
  int iw=RenderUtil::expectedTextWidth(text);
  QImage *out=new QImage(iw,RenderUtil::contentLineHeight(),QImage::Format_ARGB32);
  RenderUtil::fillImage(out);
  QPainter p(out);
  p.setFont(RendererManager::defaultFont());
  p.setPen(RendererManager::foreground());
  p.setBrush(RendererManager::foreground());
  p.drawText(0,RenderUtil::baseline(),text);
  p.end();
  return out;
}

QString DumbText::brief(QString prefix)
{
    return QString("Just print text!");
}

int DumbText::getMaxSize(QString prefix)
{
    return 0;
}

QString DumbText::author()
{
    return QString("Radu Andries <admiral0@chakra-project.org>");
}

QString DumbText::info()
{
    return brief("");
}

QImage DumbText::icon()
{
    return Renderer::icon();
}

