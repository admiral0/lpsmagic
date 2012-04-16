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


#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include "renderer.h"
#include <QStringList>

#include "renderedimage.h"

class QSettings;
class QHash<QString,Renderer*>;
/**
 * \class RendererManager
 * \brief Manages all renderers
 * \details All renderers should be registered so the config tokens can be parsed
 * and appropriate plugin can be called.<br>
 * The tokens are in the form of:<br>
 * <br><br>\c \%[renderOptions]prefix{arg1}{arg2}<br><br>
 * Render options can be these separated by "|":<ul>
 * <li>position=x,y  -> Absolute positioning</li>
 * <li>margin=top,right,bottom,left  -> Margins</li>
 * <ul><br><br>
 * Arguments can be arrays (comma separated vars). There cannot be 0 arguments, but %prefix{}
 * is acceptable
 * \note This is a singleton class
 */
class RendererManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Returns the instance for the class
     */
    static RendererManager* instance();
    /**
     * @brief Registers a renderer in the program
     * All renderers should call this
     * @param prefixes The strings that the plugin interprets.
     * @param renderer An instance of the renderer
     * @return False if any prefix is already registered
     */
    static bool registerRenderer(QStringList prefixes, Renderer *renderer);
    /**
     * \brief Registers a renderer in the program
     * \details All renderers should call this in init()
     * \param prefix The string that the plugin interprets.
     * \param renderer An instance of the renderer
     * \return False if any prefix is already registered
     */
    static bool registerRenderer(QString prefix, Renderer *renderer);
    /**
     * @brief The <class>QFont</class> that should be used to paint text
     */
    static QFont defaultFont();
    /**
     * @brief Foreground color in the settings
     */
    static QColor foreground();
    /**
     * @brief Background color
     * @note Transparent background is the best choice
     */
    static QColor background();
    /**
     * @brief Setting for event driven updating
     */
    static bool tickless();
    /**
     * @brief Gets user preference about icon spacing
     * How many pixels should be between icon and content
     */
    static int horizontalSpacing();
    /**
     * @brief Gets horizontal spacing between items
     */
    static int verticalSpacing();
    /**
     * \brief Renders a single prefix.
     * \details Can be called from other renderers for
     * rendering content.
     * \arg prefix Prefix name
     * \arg drawopts Arguments in the form of  {arg1}{arg2} or {} if empty
     * \return rendered image
     */
    QImage* renderPrefix(QString prefix,QString drawOpts);
    /**
     * \brief Renders a single prefix.
     * \details Can be called from other renderers for
     * rendering content.
     * \arg prefix Prefix name
     * \arg drawopts Arguments in the form of  [arg1,arg2] or empty stringlist if empty
     * \return rendered image
     * \note Overloaded method
     */
    QImage* renderPrefix(QString prefix,QStringList drawOpts);
    /**
     * \brief Render the image to be displayed
     * \details The various lines are parsed and printed onto the image
     * all tokens are composited into the image.<br>
     * There are 2 "fake" renderers:<ul>
     * <li>\%newline{}</li>
     * <li>\%spacer{pixels}</li>
     * </ul>
     * \note This function can be used to generate previews.
     */
    QImage render();
    /**
     * \brief Get Cached rendered image
     * \details Gets a token from cache. It may be not updated so you should
     * control if it's still valid
     */
    RenderedImage* getRenderedImage(QString token);
signals:
    void outdatedPrefix(QString prefix);
private:
    Renderer* rendererForToken(QString token);
    Renderer* rendererForPrefix(QString prefix);
    RendererManager();
    static RendererManager* self;
    static QMap<QString,Renderer*> *renderers;
    QMap<QString,RenderedImage*> *images;
    QList<RenderedImage*> *invalid;
    static QSettings *settings;
};

#endif // RENDERERMANAGER_H
