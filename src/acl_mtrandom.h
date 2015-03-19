/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
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
            std::mt19937_64 mtwister_engine;
            uint64_t getRandomULongLong(uint64_t minValue, uint64_t maxValue);
    };
}

#endif // ACL_MTRANDOM_H
