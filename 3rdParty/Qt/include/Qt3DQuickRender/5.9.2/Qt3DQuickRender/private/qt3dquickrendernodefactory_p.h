/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd and/or its subsidiary(-ies).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QUICKRENDERERNODEFACTORY_H
#define QUICKRENDERERNODEFACTORY_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qhash.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <Qt3DCore/private/qabstractnodefactory_p.h>

QT_BEGIN_NAMESPACE

class QQmlType;

namespace Qt3DRender {

class QuickRenderNodeFactory : public Qt3DCore::QAbstractNodeFactory
{
public:
    Qt3DCore::QNode *createNode(const char *type) Q_DECL_OVERRIDE;

    void registerType(const char *className, const char *quickName, int major, int minor);

    static QuickRenderNodeFactory *instance();

private:
    struct Type {
        Type() : t(nullptr), resolved(false) { }
        Type(const char *quickName, int major, int minor)
            : quickName(quickName), version(major, minor), t(nullptr), resolved(false) { }
        QByteArray quickName;
        QPair<int, int> version;
        QQmlType t;
        bool resolved;
    };
    QHash<QByteArray, Type> m_types;
};

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QUICKRENDERERNODEFACTORY_H
