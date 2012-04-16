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


#include "renderermanager.h"
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QFont>
#include <QColor>
#include <QPainter>
#include <QBrush>
#include <QRegExp>
#include <QDebug>
#include "lpsmagic.h"
#include "renderer.h"
#include "renderutil.h"
#include <QPluginLoader>
#include "rendererinterface.h"


//All renderers init
#include "renderers/dumbtext.h"
#include "renderers/daterenderer.h"
#include "renderers/batteryrenderer.h"
#include "renderers/iconrenderer.h"

//Some static stuff to make programming easier
RendererManager* RendererManager::self(0);
QMap<QString,Renderer*>* RendererManager::renderers(0);
QSettings* RendererManager::settings(0);

RendererManager* RendererManager::instance()
{
    if(!self){
        self=new RendererManager();
    }
    return self;
}
bool RendererManager::registerRenderer (QStringList prefixes, Renderer* renderer)
{
    QStringList keys= renderers->keys();
    foreach(QString prefix,prefixes){
        if(keys.contains(prefix)){
            return false;
        }
    }
    foreach(QString prefix,prefixes){
        renderers->insert(prefix,renderer);
    }
    return true;
}
bool RendererManager::registerRenderer (QString prefix, Renderer* renderer)
{
    if(renderers->keys().contains(prefix)){
        return false;
    }
    renderers->insert(prefix,renderer);
    //We don't want multiple outdatedPrefix signals triggered at once
    if(!renderers->values().contains(renderer))
      connect(renderer,SIGNAL(infoAvailable(QString)),RendererManager::instance(),SIGNAL(outdatedPrefix(QString)));
    return true;
}

RendererManager::RendererManager() : QObject()
{
    renderers=new QMap< QString, Renderer* >;
    settings=qobject_cast<LpsMagic*>(QCoreApplication::instance())->getSettings();
    images=new QMap<QString,RenderedImage*>;
    invalid=new QList<RenderedImage*>;
    
    //initialize static renderers
    Renderer *dateRenderer=new DateRenderer();
    dateRenderer->init();
    Renderer *batRenderer=new BatteryRenderer();
    batRenderer->init();
    Renderer *iconRenderer=new IconRenderer();
    iconRenderer->init();
    Renderer *dumbtext=new DumbText();
    dumbtext->init();
    //register static renderers
    registerRenderer("date",dateRenderer);
    registerRenderer("batman",batRenderer);
    registerRenderer("batIcon",batRenderer);
    registerRenderer("batCapacity",batRenderer);
    registerRenderer("batPower",batRenderer);
    registerRenderer("batPercent",batRenderer);
    registerRenderer("batTime",batRenderer);
    registerRenderer("icon",iconRenderer);
    registerRenderer("dumbtext",dumbtext);
    
    QDir libraries("/opt/lpsmagic/renderers");
    if(!libraries.exists())
      return;
    foreach(QString libpath,libraries.entryList(QStringList()<<"*.so")){
      QPluginLoader ldr(libpath);
      if(ldr.load()){
        QObject *obj=ldr.instance();
        RendererInterface *iface=qobject_cast< RendererInterface* >(obj);
        iface->init();
      }
    }
}

QColor RendererManager::background()
{
    //transparent black as default
    return settings->value("DefaultBackground",QColor(0,0,0,0)).value<QColor>();
}

QFont RendererManager::defaultFont()
{
    return settings->value("DefaultFont",QFont("DejaVu Sans",24,0)).value<QFont>();
}

QColor RendererManager::foreground()
{
    //white as default
    return settings->value("DefaultForeground",QColor(255,255,255,255)).value<QColor>();
}

int RendererManager::horizontalSpacing()
{
    return settings->value("HorizontalSpacing",2).toInt();
}

bool RendererManager::tickless()
{
    return settings->value("Tickless",true).toBool();
}

int RendererManager::verticalSpacing()
{
    return settings->value("VerticalSpacing",1).toInt();
}

QImage RendererManager::render()
{
    //I love regexs
    QRegExp tokenRegex;
    tokenRegex.setPatternSyntax(QRegExp::RegExp2);
    tokenRegex.setMinimal(true);
    tokenRegex.setPattern("(%(\\[.*\\])?([A-Za-z]*)(\\{.*\\}))");
    
    QString formatString=settings->value("formatString"," %batIcon{} %batPercent{} %icon{calendar.png} %date{} %newline{} %batCurrent{}").toString();
    settings->sync();
    qDebug()<<"STATUS"<<settings->status();
    //Initialize variables
    int x=0; //current drawing pointer
    int y=0; //
    int h=settings->value("LowPowerScreen/ImageHeight",100).toInt();//Image details
    int w=settings->value("LowPowerScreen/ImageWidth",450).toInt();
    int lh=RenderUtil::lineHeight();
    QImage out(w,h,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&out);
    
    //draw background and prepare for foreground painting
    painter.fillRect(0,0,w,h,background());
    painter.setBrush(QBrush(background()));
    painter.setPen(QPen(foreground()));
    qDebug()<<formatString;
    int pos=0;
    while((pos = tokenRegex.indexIn(formatString,pos)) != -1){
	QString token=tokenRegex.cap(1);
        QString prefix=tokenRegex.cap(3);
        QString renderOpts=tokenRegex.cap(2);
        QString drawOpts=tokenRegex.cap(4);
        qDebug()<<"Rendering token %"<<renderOpts<<prefix<<drawOpts;
        if(prefix=="newline"){
            x=0;
            y+=lh;
        }else if(prefix=="spacing"){
            drawOpts.remove('{');
            drawOpts.remove('}');
            int spacing=drawOpts.toInt();
            x+=spacing;
        }else{
	    QImage *tout;
	    RenderedImage *img;
	    if(images->contains(token)){
	      img=images->value(token);
	      img->update();
	      tout=img->getImage();
	    }else{
	      img=new RenderedImage(token);
	      images->insert(token,img);
	      img->update();
	      tout=img->getImage();
	    }
            if(!tout){
                pos+=tokenRegex.matchedLength();
                continue;
            }
                
            
            painter.drawImage(QPoint(x,y),*tout);
            x+=tout->width()+horizontalSpacing();
        }
        pos+=tokenRegex.matchedLength();
    }
    return out;
}

Renderer* RendererManager::rendererForToken (QString token)
{
    QRegExp tokenRegex;
    tokenRegex.setPatternSyntax(QRegExp::RegExp2);
    tokenRegex.setMinimal(true);
    tokenRegex.setPattern("%(\\[.*?\\])?([A-Za-z]*)(\\{.*\\})");
    int pos;
    if(tokenRegex.indexIn(token) != -1){
        QString prefix=tokenRegex.cap(2);
        return rendererForPrefix(prefix);
    }
    return 0;
}

QImage* RendererManager::renderPrefix(QString prefix,QString drawOpts)
{
  Renderer* renderer=rendererForPrefix(prefix);
  if(!renderer)
    return NULL;
  return renderer->render(QString("%").append(prefix).append(drawOpts));
}

QImage* RendererManager::renderPrefix(QString prefix,QStringList drawOpts)
{
  Renderer* renderer=rendererForPrefix(prefix);
  if(!renderer)
    return NULL;
  QString sargs=drawOpts.join("}{");
  sargs=QString("{")+sargs+"}";
  return renderer->render(QString("%").append(prefix).append(sargs));
}

Renderer* RendererManager::rendererForPrefix (QString prefix)
{
    return renderers->value(prefix,0);
}
RenderedImage* RendererManager::getRenderedImage(QString token)
{
  if(images->contains(token))
    return images->value(token);
  return NULL;
}

#include "renderermanager.moc"