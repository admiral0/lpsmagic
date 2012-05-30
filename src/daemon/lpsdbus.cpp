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


#include "lpsdbus.h"
#include <QSettings>
#include <QIODevice>
#include <QString>
#include <QFile>
#include <QRegExp>
#include <QString>
#include <iostream>


LpsDbus::LpsDbus(): QObject()
{
    QRegExp monster("LockScreen\\s+MImageWidgetStyle#LockScreenLowPowerModeOperatorLogo\\s*\\{.*\\s*maximum-size\\s*:\\s*(.+)mm\\s+(.+)mm\\s*;");
    monster.setMinimal(true);
    monster.setPatternSyntax(QRegExp::RegExp2);
    QSettings settings("/home/user/.lpsmagic");
    QFile css("/usr/share/themes/base/meegotouch/libsysuid-screenlock-nokia/style/libsysuid-screenlock-nokia.css");
    css.open(QIODevice::ReadOnly);
    if(!css.exists())
      return;
    //I'm sorry guys
    QString in=css.readAll();
    css.close();
    int pos=monster.indexIn(in);
    if(pos==-1){
      std::cout << "Error: QRegExp2 didn't match. Something is really wrong....";
    }else{
      int h=settings.value("LowPowerScreen/ImageHeight",100).toInt();
      int w=settings.value("LowPowerScreen/ImageWidth",450).toInt();
      h=int(floor(h/10.0));
      w=int(floor(w/10.0));
      if(! (w==monster.cap(1).toInt() || h==monster.cap(1).toInt())){
	UpdateCss();
	RestartSysuid();
      }
    };
}

QString LpsDbus::Ping()
{
  return QString("pong");
}


void LpsDbus::RestartSysuid()
{

    QProcess::execute("/sbin/initctl",QStringList()<<"restart"<<"xsession/sysuid");
}

void LpsDbus::UpdateCss()
{
    QRegExp monster("(LockScreen\\s+MImageWidgetStyle#LockScreenLowPowerModeOperatorLogo\\s*\\{.*\\s*maximum-size\\s*:\\s*).+mm\\s+.+mm(\\s*;)");
    monster.setMinimal(true);
    monster.setPatternSyntax(QRegExp::RegExp2);
    QSettings settings("/home/user/.lpsmagic");
    QFile css("/usr/share/themes/base/meegotouch/libsysuid-screenlock-nokia/style/libsysuid-screenlock-nokia.css");
    css.open(QIODevice::ReadOnly);
    if(!css.exists())
      return;
    //I'm sorry guys
    QString in=css.readAll();
    css.close();
    css.open(QIODevice::WriteOnly);
    
    int h=settings.value("LowPowerScreen/ImageHeight",100).toInt();
    int w=settings.value("LowPowerScreen/ImageWidth",450).toInt();
    h=int(floor(h/10.0));
    w=int(floor(w/10.0));
    //I'm even more sorry
    QString out("\\1%1mm %2mm\\2");
    out=out.arg(w).arg(h);
    css.write(in.replace(monster,out).toAscii());
    css.close();
}
LpsDbus::~LpsDbus()
{
    child.terminate();
}

#include "lpsdbus.moc"
