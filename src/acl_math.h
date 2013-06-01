/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
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
            static double ip ( std::vector<double> input, Data::Logarithm log );
            static double roundDouble ( double source, int decimals );
    };
}

#endif // ACL_MATH_H
