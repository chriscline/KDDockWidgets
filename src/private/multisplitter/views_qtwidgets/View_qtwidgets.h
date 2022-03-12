/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../View.h"
#include "../Controller.h"
#include "../../Utils_p.h"

#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QWidget>

#include <memory>

namespace KDDockWidgets::Views {

template<typename Base>
class DOCKS_EXPORT View_qtwidgets : public Base, public View
{
public:
    using View::close;
    using View::height;
    using View::rect;
    using View::width;

    explicit View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent = nullptr, Qt::WindowFlags windowFlags = {});

    ~View_qtwidgets() override = default;

    void free_impl() override
    {
        // QObject::deleteLater();
        delete this;
    }

    QSize sizeHint() const override
    {
        return Base::sizeHint();
    }

    QSize minSize() const override
    {
        return widgetMinSize(this);
    }

    QSize maxSizeHint() const override
    {
        return widgetMaxSize(this);
    }

    QRect geometry() const override
    {
        return Base::geometry();
    }

    QRect normalGeometry() const override
    {
        return Base::normalGeometry();
    }

    void setGeometry(QRect geo) override
    {
        Base::setGeometry(geo);
    }

    void setMaximumSize(QSize sz) override
    {
        Base::setMaximumSize(sz);
    }

    bool isVisible() const override
    {
        return Base::isVisible();
    }

    void setVisible(bool is) override
    {
        Base::setVisible(is);
    }

    void move(int x, int y) override
    {
        Base::move(x, y);
    }

    void move(QPoint pt) override
    {
        Base::move(pt);
    }

    void setSize(int width, int height) override
    {
        Base::resize(width, height);
    }

    void setWidth(int width) override
    {
        setSize(width, QWidget::height());
    }

    void setHeight(int height) override
    {
        setSize(QWidget::width(), height);
    }

    void setFixedWidth(int w) override
    {
        QWidget::setFixedWidth(w);
    }

    void setFixedHeight(int h) override
    {
        QWidget::setFixedHeight(h);
    }

    void show() override
    {
        Base::show();
    }

    void hide() override
    {
        Base::hide();
    }

    void update() override
    {
        Base::update();
    }

    void setParent(View *parent) override
    {
        if (!parent) {
            Base::setParent(nullptr);
            return;
        }

        if (auto qwidget = qobject_cast<QWidget *>(parent->asQObject())) {
            Base::setParent(qwidget);
        } else {
            qWarning() << Q_FUNC_INFO << "parent is not a widget, you have a bug" << parent->asQObject();
            Q_ASSERT(false);
        }
    }

    void raiseAndActivate() override
    {
        Base::window()->raise();
        if (!isWayland())
            Base::window()->activateWindow();
    }

    void activateWindow() override
    {
        Base::activateWindow();
    }

    void raise() override
    {
        Base::window()->raise();
    }

    bool isTopLevel() const override
    {
        return QWidget::isTopLevel();
    }

    QPoint mapToGlobal(QPoint localPt) const override
    {
        return Base::mapToGlobal(localPt);
    }

    QPoint mapFromGlobal(QPoint globalPt) const override
    {
        return Base::mapFromGlobal(globalPt);
    }

    void setSizePolicy(QSizePolicy policy) override
    {
        Base::setSizePolicy(policy);
    }

    void closeWindow() override
    {
        if (QWidget *window = QWidget::window())
            window->close();
    }

    QRect windowGeometry() const override
    {
        if (QWidget *window = QWidget::window())
            return window->geometry();

        return {};
    }

    virtual QSize parentSize() const override
    {
        if (auto p = QWidget::parentWidget())
            return p->size();
        return {};
    }

    bool close() override
    {
        return QWidget::close();
    }

    void setFlag(Qt::WindowType flag, bool on = true) override
    {
        QWidget::setWindowFlag(flag, on);
    }

    Qt::WindowFlags flags() const override
    {
        return QWidget::windowFlags();
    }

    void setWindowTitle(const QString &title) override
    {
        QWidget::setWindowTitle(title);
    }

    void setWindowIcon(const QIcon &icon) override
    {
        QWidget::setWindowIcon(icon);
    }

    bool isActiveWindow() const override
    {
        return QWidget::isActiveWindow();
    }

    void showNormal() override
    {
        return QWidget::showNormal();
    }

    void showMinimized() override
    {
        return QWidget::showMinimized();
    }

    void showMaximized() override
    {
        return QWidget::showMaximized();
    }

    bool isMinimized() const override
    {
        return QWidget::isMinimized();
    }

    bool isMaximized() const override
    {
        return QWidget::isMaximized();
    }

    QWindow *windowHandle() const override
    {
        return QWidget::windowHandle();
    }

protected:
    bool event(QEvent *e) override
    {
        if (e->type() == QEvent::LayoutRequest)
            onLayoutRequest();

        return Base::event(e);
    }

    void resizeEvent(QResizeEvent *ev) override
    {
        if (!onResize(ev->size()))
            Base::resizeEvent(ev);
    }

private:
    Q_DISABLE_COPY(View_qtwidgets)
};

}