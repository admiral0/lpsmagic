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


#ifndef LPSDBUS_H
#define LPSDBUS_H

#include <QProcess>
extern "C" {
    #include <unistd.h>
#include <math.h>
}
#include <QFile>
#include <QString>

class LpsDbus : public QObject
{
  Q_OBJECT
public:
    LpsDbus();
    virtual ~LpsDbus();
public slots:
    QString Ping();
    void RestartSysuid();
    void UpdateCss();
private:
    QProcess child;
};

#endif // LPSDBUS_H
