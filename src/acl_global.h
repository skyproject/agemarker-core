/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef ACL_AGEMARKERCORE_GLOBAL_H
#define ACL_AGEMARKERCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AGEMARKERCORE_LIBRARY)
#  define AGEMARKERCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define AGEMARKERCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ACL_AGEMARKERCORE_GLOBAL_H
