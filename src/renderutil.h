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


#ifndef RENDERUTIL_H
#define RENDERUTIL_H

#include <QString>
#include <QImage>
#include <QColor>
#include <QFile>


/**
 * @class RenderUtil
 * @brief Utility class for drawing
 * This class contains functions useful for drawing various parts for info widgets
 */
class RenderUtil
{
public:
    /**
     * @brief Draws single icon on the image
     * If point nor size are not specified image is drawn in point (0,0) with its 
     * 100% size
     * @arg path Image to be drawn. Any format supported by Qt's QImage will do
     * @arg image Pointer to the image
     * @return False if drawing failed
     */
    static bool drawIcon(QString path,QImage *image,QPoint point=QPoint(),QSize size=QSize());
    /**
     * @brief Draws single icon on the image
     * If point nor size are not specified image is drawn in point (0,0) with its 
     * 100% size
     * @arg icon Image to be drawn
     * @arg image Pointer to the image
     * @return False if drawing failed
     */
    static bool drawIcon(QImage icon,QImage *image,QPoint point=QPoint(),QSize size=QSize());
    /**
     * \brief Line height calculated from font metrics
     */
    static int lineHeight();
    /**
     * \brief Content should not exceed this height
     */
    static int contentLineHeight();
    /**
     * \brief Approximate width in pixels to display text
     */
    static int expectedTextWidth(QString text);
    /**
     * \brief Parse a token and return a list of params
     * \details This method is for the lazy ones (all of you)
     * \return An array of params. First param is prefix.
     */
    static QStringList parseToken(QString token);
    /**
     * \brief Gets y offset for the baseline of default font
     * \return pixel size of ascent part of the font
     */
    static int baseline();
    /**
     * \brief Gets absolute path of a resource
     * \details There are 2 paths in the program, installation path and user data path<br>
     * The first one is usually in /opt/lpsmagic/icons<br>
     * The second is /home/user/MyDocs/lpsmagic<br>
     * This function searches and finds resource trying to load from user dir first
     * \return the file or empty string
     */
    static QString resource(QString name);
    ///A shortcut for builtin modules icon() method
    static QImage systemIcon(QString name);
    ///Fill img with color, default is transparent
    static void fillImage(QImage *img, const QColor color=QColor(0,0,0,0));
};

#endif // RENDERUTIL_H
