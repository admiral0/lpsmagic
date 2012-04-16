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


#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include <QImage>

/**
 * @class Renderer
 * @brief Plugins should extend this
 * @details This is a pure virtual class<br>
 * All plugins *must* register themselves with RendererManager in
 * init().
 */
class Renderer : public QObject
{
  Q_OBJECT
public:
    virtual ~Renderer(){};
    /**
     * \brief Initialization
     * \details Usually you initialize your plugin here.
     */
    virtual void init(){};
    /**
     * @brief draw info on self
     * @details Prefixes can accept arguments. Examples:<br>
     * \c \%wIp - No arguments<br>
     * \c \%wIp{arg0} - one argument<br>
     * \c \%wIp{arg0}{arg1} - 2 arguments<br>
     * For receiving these strings plugin should register itself
     * @arg prefix A renderer can handle multiple data for displaying
     */
    virtual QImage* render(QString prefix){return new QImage;};
    /**
     * \brief Get description of prefix info
     * \note Used by GUI to display info about token
     */
    virtual QString brief(QString prefix){return QString();};
    /**
     * \brief Get an estimate of worst case scenario
     * \note Used by the GUI
     */
    virtual int getMaxSize(QString prefix){return 0;};
    /**
     * \brief One line info about author
     * \details This method should return author name and email
     * \note used in the GUI
     */
    virtual QString author(){return QString();};
    /**
     * \brief Plugin description
     */
    virtual QString info(){return QString();};
    /**
     * \brief Icon for the plugin
     * \note If empty default will be used
     */
    virtual QImage icon(){return QImage();};
signals:
    void infoAvailable(QString prefix);
};

#endif // OUTPUT_H
