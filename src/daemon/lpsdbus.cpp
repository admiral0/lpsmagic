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


LpsDbus::LpsDbus(): QObject()
{
  child.start("aegis-exec",QStringList()<<"-u"<<"user"<<"/usr/bin/lpsmagic");
}

void LpsDbus::RestartLpsMagic()
{
  child.terminate();
  child.waitForFinished(2000);
  if(child.state()==QProcess::Running){
    child.kill();
  }
  child.start("aegis-exec",QStringList()<<"-u"<<"user"<<"/usr/bin/lpsmagic");
}
void LpsDbus::RestartSysuid()
{

    QProcess::execute("/sbin/initctl",QStringList()<<"restart"<<"xsession/sysuid");
}

void LpsDbus::UpdateCss()
{
    QSettings settings("/home/user/.lpsmagic");
    QFile css("/opt/lpsmagic/magiccss");
    css.open(QIODevice::ReadOnly);
    QFile out("/usr/share/themes/base/meegotouch/libsysuid-screenlock-nokia/style/libsysuid-screenlock-nokia.css");
    out.open(QIODevice::WriteOnly);
    if(!css.exists())
      return;
    //I'm sorry guys
    QString in=css.readAll();
    css.close();
    int h=settings.value("LowPowerScreen/ImageHeight",100).toInt();
    int w=settings.value("LowPowerScreen/ImageWidth",450).toInt();
    h=int(floor(h/10.0));
    w=int(floor(w/10.0));
    in.replace("%IMAGEHEIGHT%",QString("%1").arg(h));
    in.replace("%IMAGEWIDTH%",QString("%1").arg(w));
    //TODO:Other settings? Like position
    out.write(in.toStdString().c_str());
    out.close();
}
LpsDbus::~LpsDbus()
{
    child.terminate();
}

#include "lpsdbus.moc"
