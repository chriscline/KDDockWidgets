/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Widget_qwidget.h"
#include "Item_p.h"

#include <QDebug>

using namespace Layouting;

Widget_qwidget::~Widget_qwidget()
{
}

QSize Widget_qwidget::minSize() const
{
    return widgetMinSize(asWidget());
}

QSize Widget_qwidget::maxSize() const
{
    return asWidget()->maximumSize();
}

QRect Widget_qwidget::geometry() const
{
    return asWidget()->geometry();
}

void Widget_qwidget::setParent(Widget *parent)
{
    if (!parent) {
        m_thisWidget->setParent(nullptr);
        return;
    }

    if (auto qwidget = qobject_cast<QWidget*>(parent->asQObject())) {
        m_thisWidget->setParent(qwidget);
    } else {
        qWarning() << Q_FUNC_INFO << "parent is not a widget, you have a bug" << parent->asQObject();
        Q_ASSERT(false);
    }
}

QDebug &Widget_qwidget::dumpDebug(QDebug &d) const
{
    d << " Dump Start: Host=" << m_thisWidget << rect()
      << "; dpr=" << m_thisWidget->devicePixelRatio() << ")";

    return d;
}

bool Widget_qwidget::isVisible() const
{
    return m_thisWidget->isVisible();
}

std::unique_ptr<Widget> Widget_qwidget::parentWidget() const
{
    if (auto pw = m_thisWidget->parentWidget()) {
        return std::unique_ptr<Widget>(new Widget_qwidget(pw));
    }

    return {};
}

QSize Widget_qwidget::widgetMinSize(const QWidget *w)
{
    const int minW = w->minimumWidth() > 0 ? w->minimumWidth()
                                           : w->minimumSizeHint().width();

    const int minH = w->minimumHeight() > 0 ? w->minimumHeight()
                                            : w->minimumSizeHint().height();

    return QSize(minW, minH).expandedTo(Item::hardcodedMinimumSize);
}
