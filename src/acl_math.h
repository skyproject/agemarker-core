/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#ifndef ACL_MATH_H
#define ACL_MATH_H

#include "acl_data.h"

namespace ACL
{
    class AGEMARKERCORESHARED_EXPORT Math
    {
        public:
            static float128 ip(std::vector<float128> input,
                             Data::Logarithm log);
            static float128 roundFloat128(float128 source, int decimals);
    };
}

#endif // ACL_MATH_H
