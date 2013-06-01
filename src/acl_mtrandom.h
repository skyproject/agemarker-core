/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef ACL_MTRANDOM_H
#define ACL_MTRANDOM_H

#include <random>

namespace ACL
{
    class MTRandom
    {
        public:
            MTRandom();
            uint64_t getRandomULongLong ( uint64_t minValue, uint64_t maxValue );

        private:
            std::mt19937_64 mtwister_engine;
    };
}

#endif // ACL_MTRANDOM_H
