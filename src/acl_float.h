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

#include <QString>
#include <sstream>
#include <string>

#include "acl_global.h"

namespace ACL
{
    using namespace boost::multiprecision;
    /* For certain types of calculations, extended precision (provided
     * by "float128") is required. In the majority of cases, however,
     * the precision of "double" is quite enough.
     * Since the quadruple-precision format noticeably slows down
     * computations (sometimes up to 4 times - we measured :) ),
     * there should be a "hybrid" data type that would allow to use
     * either "float128" or "double" depending on the input data.
     */
    class AGEMARKERCORESHARED_EXPORT Float
    {
        /* A quick Google search didn't yield any pre-made
         * solutions, so we have to invent something resembling
         * a wheel here.
         * Pointers make memory-management a headache, but they
         * seem like an "obvious" solution for type switching.
         * It is not quite clean, but it works nonetheless.
         *
         * Okay, scratch that. The current code is an abomination
         * and needs to be fixed asap. The pointers are used only
         * as not to store two scoped variables (both "double"
         * and "float128") in memory at the same time.
         * Is all this mess really worth those few bytes?
         */
        public:
            Float()
            {
                /* The default data type is double */
                this->valueD = new double;
            }
            Float(float128 f128)
            {
                this->valueF128 = new float128;
                *this->valueF128 = f128;
            }
            Float(double d)
            {
                this->valueD = new double;
                *this->valueD = d;
            }
            Float(QString string, int precision)
            {
                setPrecision(precision);
                if (isDouble() == true)
                {
                    *this->valueD = string.toDouble();
                }
                else
                {
                    *this->valueF128 = boost::numeric_cast<float128>(string.toStdString());
                }
            }
            ~Float()
            {
                if (valueD != nullptr)
                {
                    delete valueD;
                    valueD = nullptr;
                }
                if (valueF128 != nullptr)
                {
                    delete [] valueF128;
                    valueF128 = nullptr;
                }
            }
            bool isDouble() const
            {
                if (valueD != nullptr)
                {
                    return true;
                }
                return false;
            }
            float128 getF128() const
            {
                return *valueF128;
            }
            double getDouble() const
            {
                return *valueD;
            }
            void setPrecision(int precision)
            {
                /* According to some testing, 12 is the maximum
                 * number of decimal places "double" handles without
                 * losing precision. */
                if (precision > 12)
                {
                    valueF128 = new float128;
                    if (valueD != nullptr)
                    {
                        delete valueD;
                        valueD = nullptr;
                    }
                }
                else
                {
                    this->valueD = new double;
                    if (valueF128 != nullptr)
                    {
                        delete valueF128;
                        valueF128 = nullptr;
                    }
                }
            }
            QString toString(int precision)
            {
                std::ostringstream s;
                if (isDouble() == true)
                {
                    s << std::setprecision(precision) << getDouble();
                }
                else
                {
                    s << std::setprecision(precision) << getF128();
                }
                return QString::fromStdString(s.str());

                /* QLocale::system().toString(); ? */
            }
            QString toString()
            {
                /* 30 is the default precision for Agemarker
                 * (maximum limitation of "float128" type is
                 * 34 decimal places, but we take extra precaution)
                 */
                return toString(30);
            }
            inline Float operator += (Float v)
            {
                if (isDouble() == true)
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueD += *v.valueD;
                    }
                    else
                    {
                        *this->valueD += boost::numeric_cast<double>(*v.valueF128);
                    }
                }
                else
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueF128 += *v.valueD;
                    }
                    else
                    {
                        *this->valueF128 += *v.valueF128;
                    }
                }
                return *this;
            }
            inline Float operator + (Float v)
            {
                if (isDouble() == true)
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueD += *v.valueD;
                    }
                    else
                    {
                        *this->valueD += boost::numeric_cast<double>(*v.valueF128);
                    }
                }
                else
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueF128 += *v.valueD;
                    }
                    else
                    {
                        *this->valueF128 += *v.valueF128;
                    }
                }
                return *this;
            }
            inline Float operator - (Float v)
            {
                if (isDouble() == true)
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueD -= *v.valueD;
                    }
                    else
                    {
                        *this->valueD -= boost::numeric_cast<double>(*v.valueF128);
                    }
                }
                else
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueF128 -= *v.valueD;
                    }
                    else
                    {
                        *this->valueF128 -= *v.valueF128;
                    }
                }
                return *this;
            }
            inline Float operator * (Float v)
            {
                if (isDouble() == true)
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueD *= *v.valueD;
                    }
                    else
                    {
                        *this->valueD *= boost::numeric_cast<double>(*v.valueF128);
                    }
                }
                else
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueF128 *= *v.valueD;
                    }
                    else
                    {
                        *this->valueF128 *= *v.valueF128;
                    }
                }
                return *this;
            }
            inline Float operator / (Float v)
            {
                if (isDouble() == true)
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueD /= *v.valueD;
                    }
                    else
                    {
                        *this->valueD /= boost::numeric_cast<double>(*v.valueF128);
                    }
                }
                else
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueF128 /= *v.valueD;
                    }
                    else
                    {
                        *this->valueF128 /= *v.valueF128;
                    }
                }
                return *this;
            }
            inline Float operator = (Float v)
            {
                if (isDouble() == true)
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueD = *v.valueD;
                    }
                    else
                    {
                        *this->valueD = boost::numeric_cast<double>(*v.valueF128);
                    }
                }
                else
                {
                    if (v.isDouble() == true)
                    {
                        *this->valueF128 = *v.valueD;
                    }
                    else
                    {
                        *this->valueF128 = *v.valueF128;
                    }
                }
                return *this;
            }
            inline Float operator = (float128 v)
            {
                if (isDouble() == true)
                {
                    *this->valueD = boost::numeric_cast<double>(v);
                }
                else
                {
                    *this->valueF128 = v;
                }
                return *this;
            }
            inline Float operator = (double v)
            {
                if (isDouble() == true)
                {
                    *this->valueD = v;
                }
                else
                {
                    *this->valueF128 = v;
                }
                return *this;
            }
            inline bool operator < (const Float& other) const
            {
                if (isDouble() == true)
                {
                    if (other.isDouble() == true)
                    {
                        return getDouble() < other.getDouble();
                    }
                    return getDouble() < other.getF128();
                }
                else
                {
                    if (other.isDouble() == true)
                    {
                        return getF128() < other.getDouble();
                    }
                    return getF128() < other.getF128();
                }
            }
            inline bool operator > (const Float& other) const
            {
                if (isDouble() == true)
                {
                    if (other.isDouble() == true)
                    {
                        return getDouble() > other.getDouble();
                    }
                    return getDouble() > other.getF128();
                }
                else
                {
                    if (other.isDouble() == true)
                    {
                        return getF128() > other.getDouble();
                    }
                    return getF128() > other.getF128();
                }
            }
            inline bool operator <= (const Float& other) const
            {
                if (isDouble() == true)
                {
                    if (other.isDouble() == true)
                    {
                        return getDouble() <= other.getDouble();
                    }
                    return getDouble() <= other.getF128();
                }
                else
                {
                    if (other.isDouble() == true)
                    {
                        return getF128() <= other.getDouble();
                    }
                    return getF128() <= other.getF128();
                }
            }
            inline bool operator >= (const Float& other) const
            {
                if (isDouble() == true)
                {
                    if (other.isDouble() == true)
                    {
                        return getDouble() >= other.getDouble();
                    }
                    return getDouble() >= other.getF128();
                }
                else
                {
                    if (other.isDouble() == true)
                    {
                        return getF128() >= other.getDouble();
                    }
                    return getF128() >= other.getF128();
                }
            }
            template <typename T>
            inline bool operator == (const T& other)
            {
                if (isDouble() == true)
                {
                    return getDouble() == other;
                }
                return getF128() == other;
            }
            template <typename T>
            inline bool operator != (const T& other)
            {
                return !(*this == other);
            }

        private:
            float128 *valueF128 = nullptr;
            double *valueD = nullptr;
    };

    /* Due to the way Float is implemented at the moment,
     * it is impossible to use most of the standard math functions
     * (pow, sqrt, log, abs, etc.) directly, without checking
     * the type of variable used.
     * Therefore, we use a dedicated class.
     */
     class AGEMARKERCORESHARED_EXPORT FMath
     {
         public:
             static Float round(Float v)
             {
                if (v.isDouble() == true)
                {
                    return Float(std::round(v.getDouble()));
                }
                return Float(boost::multiprecision::round(v.getF128()));
             }
             static Float round(Float v, int precision)
             {
                if (v.isDouble() == true)
                {
                    return Float(std::ceil((v.getDouble() * std::pow(10, precision)) - 0.49) / std::pow(10, precision));
                }
                return Float(boost::multiprecision::ceil((v.getF128() * std::pow(10, precision)) - 0.49Q) / std::pow(10, precision));
             }
             template <typename T>
             static Float pow(Float v, T raise)
             {
                 if (v.isDouble() == true)
                 {
                     return Float(std::pow(v.getDouble(), raise));
                 }
                 return Float(boost::multiprecision::pow(v.getF128(), raise));
             }
             static Float sqrt(Float v)
             {
                 if (v.isDouble() == true)
                 {
                     return Float(std::sqrt(v.getDouble()));
                 }
                 return Float(boost::multiprecision::sqrt(v.getF128()));
             }
             static Float abs(Float v)
             {
                 if (v.isDouble() == true)
                 {
                     return Float(std::abs(v.getDouble()));
                 }
                 return Float(boost::multiprecision::abs(v.getF128()));
             }
             static Float log(Float v)
             {
                 if (v.isDouble() == true)
                 {
                     return Float(std::log(v.getDouble()));
                 }
                 return Float(boost::multiprecision::log(v.getF128()));
             }
             static Float log10(Float v)
             {
                 if (v.isDouble() == true)
                 {
                     return Float(std::log10(v.getDouble()));
                 }
                 return Float(boost::multiprecision::log10(v.getF128()));
             }
             template <typename T>
             static T boost_numeric_cast(Float v)
             {
                 if (v.isDouble() == true)
                 {
                     return boost::numeric_cast<T>(v.getDouble());
                 }
                 return boost::numeric_cast<T>(v.getF128());
             }
     };
}

#endif // ACL_FLOAT

