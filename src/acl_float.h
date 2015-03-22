/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#ifndef ACL_FLOAT
#define ACL_FLOAT

#include <boost/multiprecision/float128.hpp>

/* Float <-> QString conversion */
#include <QLocale>
#include <QString>
#include <sstream>
#include <string>

#include "acl_global.h"

/* Look up "acl_global.h" for USING_DOUBLE and
 * USING_FLOAT128 definitions (read the Qt Project
 * file) for more information.
*/

#ifdef USING_DOUBLE
#define Float double
#endif
#ifdef USING_FLOAT128
#define Float boost::multiprecision::float128
#endif

namespace ACL
{
    using namespace boost::multiprecision;
    class AGEMARKERCORESHARED_EXPORT FMath
    {
        public:
#ifdef USING_DOUBLE
            static double round(double v)
            {
                return std::round(v);
            }
            static double round(double v, int precision)
            {
                return std::ceil((v * std::pow(10, precision)) - 0.49)
                        / std::pow(10, precision);
            }
            static double sqrt(double v)
            {
                 return std::sqrt(v);
            }
            static double abs(double v)
            {
                return std::abs(v);
            }
            static double log(double v)
            {
                return std::log(v);
            }
            static double log10(double v)
            {
                return std::log10(v);
            }
            template <typename T>
            static double pow(double v, T raise)
            {
                return std::pow(v, raise);
            }
            static double fromStr(QString source)
            {
                return QLocale::system().toDouble(source);
            }
            static QString toStr(double v, int precision)
            {
                std::ostringstream s;
                s << std::setprecision(precision) << v;
                return QString::fromStdString(s.str());
            }
            static QString toStr(double v)
            {
                /* 12 is the maximum safe precision the
                 * "double" type is able to handle. */
                return toStr(v, 12);
            }
#endif
#ifdef USING_FLOAT128
            static float128 round(float128 v)
            {
                return boost::multiprecision::round(v);
            }
            static float128 round(float128 v, int precision)
            {
                return boost::multiprecision::ceil((v * std::pow(10, precision)) - 0.49Q)
                        / std::pow(10, precision);
            }
            static float128 sqrt(float128 v)
            {
                 return boost::multiprecision::sqrt(v);
            }
            static float128 abs(float128 v)
            {
                return boost::multiprecision::abs(v);
            }
            static float128 log(float128 v)
            {
                return boost::multiprecision::log(v);
            }
            static float128 log10(float128 v)
            {
                return boost::multiprecision::log10(v);
            }
            template <typename T>
            static float128 pow(float128 v, T raise)
            {
                return boost::multiprecision::pow(v, raise);
            }
            static float128 fromStr(QString source)
            {
                return boost::numeric_cast<float128>(source.toStdString());
            }
            static QString toStr(float128 v, int precision)
            {
                std::ostringstream s;
                s << std::setprecision(precision) << v;
                return QString::fromStdString(s.str());
            }
            static QString toStr(float128 v)
            {
                /* 34 is the maximum precision "float128"
                 * can handle, but we take extra precaution
                 * and settle on 30 decimal places.
                 */
                return toStr(v, 30);
            }
#endif
    };
}

#endif // ACL_FLOAT

