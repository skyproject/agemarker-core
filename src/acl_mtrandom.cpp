/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include <QString>
#include <time.h>

#include "acl_mtrandom.h"

using namespace ACL;

MTRandom::MTRandom()
{
    mtwister_engine.seed ( ( unsigned ) time ( NULL ) );
}

uint64_t MTRandom::getRandomULongLong ( uint64_t minValue, uint64_t maxValue )
{
    uint64_t number = mtwister_engine();

    if ( minValue != maxValue )
    {
        return ( std::abs ( number % ( maxValue - minValue ) ) + minValue );
    }
    else
    {
        return minValue;
    }
}
