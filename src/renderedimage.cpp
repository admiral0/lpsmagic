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


#include "renderedimage.h"
#include "renderermanager.h"
#include "renderutil.h"

RenderedImage::RenderedImage(QString token)
{
    image=new QImage;
    QRegExp tokenRegex;
    tokenRegex.setPatternSyntax(QRegExp::RegExp2);
    tokenRegex.setMinimal(true);
    tokenRegex.setPattern("%\\[(.*)\\]?([A-Za-z]*)\\{(.*)\\}");
    int found=tokenRegex.indexIn(token);
    if(found==-1){
      valid=false;
      this->token=token;
      return;
    }
    this->token=token;
    this->args=tokenRegex.cap(3).split("}{");
    QString renderargslist=tokenRegex.cap(2);
    this->prefix=tokenRegex.cap(1);
    renderargs=renderargslist.split(',');
    foreach(QString arg, renderargs){
      if(arg=="important"){
	important=true;
      }
      if(arg.contains("size=")){
	QRegExp sizeregex;
	sizeregex.setPatternSyntax(QRegExp::RegExp2);
	sizeregex.setPattern("size=(\\d*)(:(\\d*))?");
	int res=sizeregex.indexIn(arg);
	if(!res==-1){
	  boundingRect.setWidth(sizeregex.cap(1).toInt());
	  if(sizeregex.captureCount()>2){
	      boundingRect.setHeight(sizeregex.cap(3).toInt());
	  }
	}
      }
      if(arg=="center"){
	centered=true;
      }
      if(arg.contains("pos=")){
	QRegExp posregex;
	posregex.setPatternSyntax(QRegExp::RegExp2);
	posregex.setPattern("pos=(\\d*)(:(\\d*))?");
	int res=posregex.indexIn(arg);
	if(!res==-1){
	  boundingRect.setLeft(posregex.cap(1).toInt());
	  if(posregex.captureCount()>2){
	      boundingRect.setHeight(posregex.cap(3).toInt());
	  }
	}
      }
    }
    update();
    valid=true;
    connect(RendererManager::instance(),SIGNAL(outdatedPrefix(QString)),SLOT(invalidatePrefix(QString)));
}

RenderedImage::~RenderedImage()
{
  //LOL? we never unload this....
}

bool RenderedImage::operator==(const RenderedImage& other) const
{
  if(other.token==token){
    return true;
  }
  return false;
}

void RenderedImage::update()
{
  delete image;
  image=RendererManager::instance()->renderPrefix(prefix,args);
}

void RenderedImage::invalidatePrefix(QString prefix)
{
  if(prefix==this->prefix)
    valid=false;
}

QImage* RenderedImage::getImage()
{
  return image;
}


#include "renderedimage.moc"