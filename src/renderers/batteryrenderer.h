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


#ifndef BATTERYRENDERER_H
#define BATTERYRENDERER_H

#include "../renderer.h"

#include <qmsystem2/qmbattery.h>


/*
 * %batIcon  battery state icon (use resource system)
 * %batCapacity bat capacity mAh/%
 * %batVoltage bat voltage
 * %batCurrent bat current (cc) dafuq
 * %batTime (dis)charge time rimaining (idle,talk,active)
 * %batman lol
 */

class BatteryRenderer : public Renderer
{

public:
    virtual QImage icon();
    virtual QString info();
    virtual QString author();
    virtual int getMaxSize (QString prefix);
    virtual QString brief (QString prefix);
    virtual QImage* render (QString prefix);
    virtual void init();
private:
    void batIcon();
    void batCapacity(QString suffix);
    void batPercent(QString suffix);
    void batPower(QString suffix);
    void batTime(QString type,QString format);
    void batman();
    MeeGo::QmBattery *battery;
    int lh;
    QImage *out;
};

#endif // BATTERYRENDERER_H
