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


#ifndef ICONRENDERER_H
#define ICONRENDERER_H

#include "../renderer.h"


class IconRenderer : public Renderer
{
Q_OBJECT
public:
    virtual ~IconRenderer();
    virtual void init();
    virtual QImage* render(QString prefix);
    virtual QString brief(QString prefix);
    virtual int getMaxSize(QString prefix);
    virtual QString author();
    virtual QString info();
    virtual QImage icon();
    IconRenderer();
};

#endif // ICONRENDERER_H
