/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
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
