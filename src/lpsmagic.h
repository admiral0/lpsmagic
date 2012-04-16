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


#ifndef LPSMAGIC_H
#define LPSMAGIC_H

#include <QApplication>
#include <QTimer>
#include <QSettings>
#include <qmsystem2/qmheartbeat.h>
#include <qmsystem2/qmdisplaystate.h>
#include <gconf/gconf.h>
#include <gconf/gconf-client.h>
#include "lpsdbusinterface.h"

class LpsMagic : public QApplication
{
    Q_OBJECT
public:
    LpsMagic (int& argc, char** argv);
    virtual ~LpsMagic();
    QSettings* getSettings();
    bool oneshot;
public slots:
    void render();
    void renderFile();
    void suspendRendering();
    void continueRendering();
    void displayStateChanged(MeeGo::QmDisplayState::DisplayState state);
private:
    MeeGo::QmHeartbeat ticker;
    MeeGo::QmDisplayState displaystate;
    bool odd;
    bool tickless;
    QPair<QString,QString> lolbuffer;
    QSettings *settings;
    GConfClient *gclient;
    OrgAdmiral0LpsmagicInterface *dbus;
};

#endif // LPSMAGIC_H
