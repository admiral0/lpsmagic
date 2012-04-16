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


#ifndef DATERENDERER_H
#define DATERENDERER_H

#include "../renderer.h"

//define ICON "/opt/lpsmagic/icons/calendar.png"
#define ICON "/home/admiral0/projects/lpsmagic/icons/calendar.png"


class DateRenderer : public Renderer
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
    QString localeFormat();
    int lineheight;
};

#endif // DATERENDERER_H
