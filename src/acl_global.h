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


/* To compile the library with extended precision floats,
 * uncomment the following line.
 * Note: don't forget to rebuild the "agemarker" project.
 */
#define USING_FLOAT128

/* To compile the library with standard ("double") precision
 * floats, uncomment the following line.
 * Note: don't forget to rebuild the "agemarker" project.
 */
//#define USING_DOUBLE

/* See "acl_float.h" for the main implementation
 * (functions / "Float" definitions).
 */


#endif // ACL_AGEMARKERCORE_GLOBAL_H
