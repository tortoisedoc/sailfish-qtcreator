/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef QMLPROFILEREVENTVIEW_H
#define QMLPROFILEREVENTVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <qmldebug/qmlprofilereventtypes.h>
#include "qmlprofilermodelmanager.h"
#include "qmlprofilereventsmodelproxy.h"
#include "qmlprofilertreeview.h"

#include <analyzerbase/ianalyzertool.h>

#include "qmlprofilerviewmanager.h"

namespace QmlProfiler {
namespace Internal {

class QmlProfilerEventsMainView;
class QmlProfilerEventChildrenView;
class QmlProfilerEventRelativesView;

enum ItemRole {
    EventHashStrRole = Qt::UserRole+1,
    FilenameRole = Qt::UserRole+2,
    LineRole = Qt::UserRole+3,
    ColumnRole = Qt::UserRole+4,
    EventIdRole = Qt::UserRole+5
};

class QmlProfilerEventsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QmlProfilerEventsWidget(QWidget *parent,
                                     QmlProfilerTool *profilerTool,
                                     QmlProfilerViewManager *container,
                                     QmlProfilerModelManager *profilerModelManager );
    ~QmlProfilerEventsWidget();

    void clear();

    void getStatisticsInRange(qint64 rangeStart, qint64 rangeEnd);
    QModelIndex selectedItem() const;
    bool mouseOnTable(const QPoint &position) const;
    void copyTableToClipboard() const;
    void copyRowToClipboard() const;

    bool hasGlobalStats() const;
    void setShowExtendedStatistics(bool show);
    bool showExtendedStatistics() const;

    void setShowJavaScript(bool show);
    bool showJavaScript() const;

    void setShowQml(bool show);
    bool showQml() const;

signals:
    void gotoSourceLocation(const QString &fileName, int lineNumber, int columnNumber);
    void eventSelectedByHash(const QString &eventHash);
    void resized();

public slots:
    void updateSelectedEvent(const QString &eventHash) const;
    void selectBySourceLocation(const QString &filename, int line, int column);

private slots:
    void profilerDataModelStateChanged();

protected:
    void contextMenuEvent(QContextMenuEvent *ev);
    virtual void resizeEvent(QResizeEvent *event);

private:
    class QmlProfilerEventsWidgetPrivate;
    QmlProfilerEventsWidgetPrivate *d;
};

class QmlProfilerEventsMainView : public QmlProfilerTreeView
{
    Q_OBJECT
public:
    explicit QmlProfilerEventsMainView(QWidget *parent,
                                       QmlProfilerEventsModelProxy *modelProxy);
    ~QmlProfilerEventsMainView();

    void setFieldViewable(Fields field, bool show);
    void setShowAnonymousEvents( bool showThem );

    QModelIndex selectedItem() const;
    void copyTableToClipboard() const;
    void copyRowToClipboard() const;

    static QString nameForType(int typeNumber);

    void getStatisticsInRange(qint64 rangeStart, qint64 rangeEnd);
    QString selectedEventHash() const;

    void setShowExtendedStatistics(bool);
    bool showExtendedStatistics() const;


signals:
    void gotoSourceLocation(const QString &fileName, int lineNumber, int columnNumber);
    void eventSelected(const QString &eventHash);

public slots:
    void clear();
    void jumpToItem(const QModelIndex &index);
    void selectEvent(const QString &eventHash);
    void selectEventByLocation(const QString &filename, int line, int column);
    void buildModel();

private slots:
    void profilerDataModelStateChanged();

private:
    void setHeaderLabels();
    void parseModelProxy();

private:
    class QmlProfilerEventsMainViewPrivate;
    QmlProfilerEventsMainViewPrivate *d;

};

class QmlProfilerEventRelativesView : public QmlProfilerTreeView
{
    Q_OBJECT
public:
    explicit QmlProfilerEventRelativesView(QmlProfilerModelManager *modelManager,
                                           QmlProfilerEventRelativesModelProxy *modelProxy,
                                           QWidget *parent );
    ~QmlProfilerEventRelativesView();

signals:
    void eventClicked(const QString &eventHash);

public slots:
    void displayEvent(const QString &eventHash);
    void jumpToItem(const QModelIndex &);
    void clear();

private:
    void rebuildTree(QmlProfilerEventParentsModelProxy::QmlEventRelativesMap eventMap);
    void updateHeader();
    QStandardItemModel *treeModel();

    class QmlProfilerEventParentsViewPrivate;
    QmlProfilerEventParentsViewPrivate *d;
};

} // namespace Internal
} // namespace QmlProfiler

#endif // QMLPROFILEREVENTVIEW_H
