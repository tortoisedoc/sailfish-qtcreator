/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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
#ifndef IOSRUNFACTORIES_H
#define IOSRUNFACTORIES_H

#include <projectexplorer/runconfiguration.h>
#include <qt4projectmanager/qmakerunconfigurationfactory.h>
#include <qcompilerdetection.h>

namespace ProjectExplorer {
class RunControl;
class RunConfigWidget;
class Target;
class Node;
} // namespace ProjectExplorer

namespace Ios {
namespace Internal {

class IosRunConfigurationFactory : public Qt4ProjectManager::QmakeRunConfigurationFactory
{
    Q_OBJECT

public:
    explicit IosRunConfigurationFactory(QObject *parent = 0);

    Q_DECL_OVERRIDE QString displayNameForId(const Core::Id id) const;
    Q_DECL_OVERRIDE QList<Core::Id> availableCreationIds(ProjectExplorer::Target *parent) const;

    Q_DECL_OVERRIDE bool canCreate(ProjectExplorer::Target *parent, const Core::Id id) const;
    Q_DECL_OVERRIDE ProjectExplorer::RunConfiguration *create(ProjectExplorer::Target *parent,
                                                              const Core::Id id);

    Q_DECL_OVERRIDE bool canRestore(ProjectExplorer::Target *parent, const QVariantMap &map) const;
    Q_DECL_OVERRIDE ProjectExplorer::RunConfiguration *restore(ProjectExplorer::Target *parent,
                                                               const QVariantMap &map);

    Q_DECL_OVERRIDE bool canClone(ProjectExplorer::Target *parent,
                                  ProjectExplorer::RunConfiguration *source) const;
    Q_DECL_OVERRIDE ProjectExplorer::RunConfiguration *clone(ProjectExplorer::Target *parent,
                                                             ProjectExplorer::RunConfiguration *source);

    Q_DECL_OVERRIDE bool canHandle(ProjectExplorer::Target *t) const;
    Q_DECL_OVERRIDE QList<ProjectExplorer::RunConfiguration *> runConfigurationsForNode(ProjectExplorer::Target *t,
                                                                        ProjectExplorer::Node *n);
private:
    ProjectExplorer::RunConfiguration *doCreate(ProjectExplorer::Target *parent, const Core::Id id);
    ProjectExplorer::RunConfiguration *doRestore(ProjectExplorer::Target *parent,
                                                 const QVariantMap &map);
};

class IosRunControlFactory : public ProjectExplorer::IRunControlFactory
{
    Q_OBJECT

public:
    explicit IosRunControlFactory(QObject *parent = 0);

    QString displayName() const;

    bool canRun(ProjectExplorer::RunConfiguration *runConfiguration,
                ProjectExplorer::RunMode mode) const;
    ProjectExplorer::RunControl *create(ProjectExplorer::RunConfiguration *runConfiguration,
                       ProjectExplorer::RunMode mode,
                       QString *errorMessage);
};

} // namespace Internal
} // namespace Ios

#endif  // IOSRUNFACTORIES_H