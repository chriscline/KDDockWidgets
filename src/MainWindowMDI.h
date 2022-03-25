/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief MainWindow sub-class which uses MDI as a layout
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_MAINWINDOW_MDI_H
#define KD_MAINWINDOW_MDI_H

#ifdef KDDOCKWIDGETS_QTWIDGETS
#include "views_qtwidgets/MainWindow_qtwidgets.h"
#else
#include "private/quick/MainWindowQuick_p.h"
#endif

namespace KDDockWidgets {


/// @brief MainWindow sub-class which uses MDI as a layout
class DOCKS_EXPORT MainWindowMDI : public Views::MainWindow_qtwidgets
{
    Q_OBJECT
public:
    ///@brief Constructor. See base class documentation
    explicit MainWindowMDI(const QString &uniqueName, QWidget *parent = nullptr,
                           Qt::WindowFlags flags = Qt::WindowFlags());

    ///@brief Destructor
    ~MainWindowMDI() override;

    ///@brief Docks @p dockWidget
    /// The widget will be placed at the specified position
    void addDockWidget(Controllers::DockWidgetBase *dockWidget,
                       QPoint localPos, InitialOption addingOption = {});

    ///@brief Convenience overload
    void addDockWidget(Controllers::DockWidgetBase *dockWidget,
                       QPointF localPos, InitialOption addingOption = {});
};

}

#endif
