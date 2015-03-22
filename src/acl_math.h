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
            static Float ip(std::vector<Float> input,
                            Data::Logarithm log);
    };
}

#endif // ACL_MATH_H
