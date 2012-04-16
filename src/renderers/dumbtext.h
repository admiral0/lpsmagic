/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Radu Andries <email>

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


#ifndef DUMBTEXT_H
#define DUMBTEXT_H

#include "../renderer.h"


class DumbText : public Renderer
{

public:
    virtual ~DumbText();
    virtual void init();
    virtual QImage* render(QString prefix);
    virtual QString brief(QString prefix);
    virtual int getMaxSize(QString prefix);
    virtual QString author();
    virtual QString info();
    virtual QImage icon();
};

#endif // DUMBTEXT_H
