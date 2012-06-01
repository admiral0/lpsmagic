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


#include "lpsmagic.h"
#include "renderermanager.h"
#include <QDir>
#include <QDebug>
#include <iostream>
#include <glib-object.h>
#include "qxtlogger.h"
#include "qxtbasicstdloggerengine.h"

#define CONFIG_FILE "/home/user/.lpsmagic"
#define USER_CONFIG_FILE "/home/user/MyDocs/lpsmagic.conf"
using namespace std;
LpsMagic::LpsMagic (int& argc, char** argv) : QApplication (argc, argv)
{
    qxtLog->info("Logging started");
    dbus=new OrgAdmiral0LpsmagicInterface("org.admiral0.lpsmagic","/",QDBusConnection::systemBus());
    oneshot=false;
    
    if(!QFile(CONFIG_FILE).exists()){
      qxtLog->info("Creating config file ",CONFIG_FILE);
      QFile::copy("/opt/lpsmagic/lpsmagicconf.example",CONFIG_FILE);
      dbus->UpdateCss();
      dbus->RestartSysuid();
    }else if(QFile(USER_CONFIG_FILE).exists()){
      qxtLog->info("Moving config file from ",USER_CONFIG_FILE," to ",CONFIG_FILE);
      QFile::copy(USER_CONFIG_FILE,CONFIG_FILE);
      QFile::remove(USER_CONFIG_FILE);
      dbus->UpdateCss();
      dbus->RestartSysuid();
    }
    settings=new QSettings(CONFIG_FILE,QSettings::IniFormat);
    ticker.open(MeeGo::QmHeartbeat::SignalNeeded);
    connect(&ticker,SIGNAL(wakeUp(QTime)),this,SLOT(render()));
    connect(&displaystate,SIGNAL(displayStateChanged(MeeGo::QmDisplayState::DisplayState)),SLOT(displayStateChanged(MeeGo::QmDisplayState::DisplayState)));
    if(arguments().contains("-demo")){
	qxtLog->info("It's a oneshot call.");
        renderFile();
        oneshot=true;
    }else if(arguments().contains("--help") || arguments().contains("-h")){
      cout<<"Lpsmagic - Low power screen manager\n";
      cout<<"\tUsage: lpsmagic [-h|--help] [-demo [configstring]]\n";
      cout<<"\t\t-h/--help: Displays this message\n";
      cout<<"\t\t-demo : Generate out.png in the current directory";
      cout<<"\t\tconfigstring: Sets new configstring\n";
    }else{
        odd=false;
        lolbuffer=qMakePair<QString,QString>("/tmp/lpsmagic.png","/tmp/lpsmagic1.png");
        //ticker.wait(0,15,MeeGo::QmHeartbeat::DoNotWaitHeartbeat);
        g_type_init();
        gclient=gconf_client_get_default();
        render();
    }
    
}

LpsMagic::~LpsMagic()
{
    settings->sync();
    settings->deleteLater();
}
void LpsMagic::render()
{
    //backbuffertrick
    odd=!odd;
    QImage img= RendererManager::instance()->render();
    
    if(odd){
        img.save(lolbuffer.first);
        img.save(lolbuffer.second);
        GError *e=new GError;
        gconf_client_set_string(gclient,"/desktop/meego/screen_lock/low_power_mode/operator_logo",lolbuffer.second.toStdString().c_str(),&e);
        delete e;
    }else{
        img.save(lolbuffer.second);
        img.save(lolbuffer.first);
        GError *e=new GError;
        gconf_client_set_string(gclient,"/desktop/meego/screen_lock/low_power_mode/operator_logo",lolbuffer.first.toStdString().c_str(),&e);
        delete e;
    }
    int mint=settings->value("minWaitTime",20).toInt();
    int maxt=settings->value("maxWaitTime",60).toInt();
    int delta=settings->value("heartbeatDelta",5).toInt();
    if(settings->value("Tickless",false).toBool()){
      if(mint>0){
	ticker.wait(mint-delta,mint+delta,MeeGo::QmHeartbeat::DoNotWaitHeartbeat);
      }else{
	
      }
    }else{
    ticker.wait(maxt-delta,maxt+delta,MeeGo::QmHeartbeat::DoNotWaitHeartbeat);
    }
}

void LpsMagic::renderFile()
{
    if(QApplication::instance()->arguments().size()>2){
      settings->setValue("formatString",QApplication::instance()->arguments().at(2));
      settings->sync();
    }
    QImage img= RendererManager::instance()->render();
    qxtLog->info("Image is null? ",img.isNull());
    img.save("demo.png","PNG");
}

QSettings* LpsMagic::getSettings()
{
    return settings;
}

void LpsMagic::continueRendering()
{
  connect(&ticker,SIGNAL(wakeUp(QTime)),this,SLOT(render()));
  render();
}

void LpsMagic::suspendRendering()
{
  ticker.disconnect();
}

void LpsMagic::displayStateChanged(MeeGo::QmDisplayState::DisplayState state)
{
  if(state==MeeGo::QmDisplayState::Off){
    //that will stop the heartbeat and register a new one
    suspendRendering();
    continueRendering();
  }else if(state==MeeGo::QmDisplayState::On){
    suspendRendering();
  }
}


#include "lpsmagic.moc"