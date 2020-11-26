/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_UTILS_P_H
#define KD_UTILS_P_H

#include "Config.h"

#include <QScreen>
#include <QWidget>
#include <QWindow>

#ifdef KDDOCKWIDGETS_QTQUICK
# include <QQuickItem>
# include <QQuickWindow>
#else
# include <QApplication>
#endif

#ifdef QT_X11EXTRAS_LIB
# include <QtX11Extras/QX11Info>
#endif

QT_BEGIN_NAMESPACE
class QWidget;
class QWindow;
QT_END_NAMESPACE

namespace KDDockWidgets {

inline bool isWayland()
{
    return qApp->platformName() == QLatin1String("wayland");
}

inline bool isLeftButtonPressed()
{
    return qApp->mouseButtons() & Qt::LeftButton;
}

inline bool usesNativeTitleBar()
{
    return Config::self().flags() & Config::Flag_NativeTitleBar;
}

inline bool usesClientTitleBar()
{
    if (isWayland()) {
        // Wayland has both client and native title bars, due to limitations.
        return true;
    }

    // All other platforms have either the OS native title bar or a Qt title bar (aka client title bar).
    return !usesNativeTitleBar();
}

inline bool usesAeroSnapWithCustomDecos()
{
    return Config::self().flags() & Config::Flag_AeroSnapWithClientDecos;
}

inline bool usesNativeDraggingAndResizing()
{
    // a native title bar implies native resizing and dragging
    // Windows Aero-Snap also implies native dragging, and implies no native-title bar
    Q_ASSERT(!(usesNativeTitleBar() && usesAeroSnapWithCustomDecos()));
    return usesNativeTitleBar() || usesAeroSnapWithCustomDecos();
}

inline void activateWindow(QWindow *window)
{
    window->requestActivate();
}

inline bool windowManagerHasTranslucency()
{
#ifdef QT_X11EXTRAS_LIB
    if (qApp->platformName() == QLatin1String("xcb"))
        return QX11Info::isCompositingManagerRunning();
#endif

    // macOS and Windows are fine
    return true;
}

inline QSize screenSizeForWindow(const QWindow *window)
{
    if (window) {
        if (QScreen *screen = window->screen()) {
            return screen->size();
        }
    }

    return {};
}

inline int screenNumberForWindow(const QWindow *window)
{
    if (window) {
        if (QScreen *screen = window->screen()) {
            return qApp->screens().indexOf(screen);
        }
    }

    return -1;
}

inline bool isWindow(const QWidget *w)
{
    return w && w->isWindow();
}

inline bool isWindow(const QWindow *w)
{
    return w != nullptr;
}

inline int startDragDistance()
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    return QApplication::startDragDistance();
#else
    return 4;
#endif
}

#ifdef KDDOCKWIDGETS_QTWIDGETS
inline int screenNumberForWidget(const QWidget *widget)
{
    return screenNumberForWindow(widget->window()->windowHandle());
}

inline QSize screenSizeForWidget(const QWidget *widget)
{
    return screenSizeForWindow(widget->window()->windowHandle());
}

inline QPoint mapToGlobal(QWidget *w, QPoint p)
{
    return w->mapToGlobal(p);
}

inline void activateWindow(QWidget *widget)
{
    widget->activateWindow();
}

#else

inline int screenNumberForWidget(const QQuickItem *w)
{
    return screenNumberForWindow(w->window());
}

inline QSize screenSizeForWidget(const QQuickItem *w)
{
    return screenSizeForWindow(w->window());
}

inline QPoint mapToGlobal(QQuickItem *item, QPoint p)
{
    return item->mapToGlobal(p).toPoint();
}

#endif

};

#endif
