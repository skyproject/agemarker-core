/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "acl_math.h"

using namespace ACL;

double Math::ip ( std::vector<double> input, Data::Logarithm log )
{
    double rowSum[3];
    double columnSum[3];
    double rowsTotalSum = 0;
    double rowsUncertaintyTotal = 0;
    double columnsUncertaintyTotal = 0;
    for ( int x = 0; x < 3; ++x )
    {
        columnSum[x] = input[x] + input[ ( x + 3 )] + input[ ( x + 6 )];
        rowSum[x] = input[ ( x * 3 )] + input[ ( x * 3 ) + 1] + input[ ( x * 3 ) + 2];
        rowsTotalSum += rowSum[x];
    }
    /* Fill 'rowSum' array with uncertainty values for each row */
    if ( log == Data::Logarithm::Natural )
    {
        for ( int x = 0; x < 3; ++x )
        {
            if ( rowSum[x] > 0 )
            {
                rowSum[x] = std::abs ( ( rowSum[x] / rowsTotalSum ) * std::log ( rowSum[x] / rowsTotalSum ) );
                rowsUncertaintyTotal += rowSum[x];
            }
            if ( columnSum[x] > 0 )
            {
                columnSum[x] = std::abs ( ( columnSum[x] / rowsTotalSum ) * std::log ( columnSum[x] / rowsTotalSum ) );
                columnsUncertaintyTotal += columnSum[x];
            }
        }
    }
    else
    {
        for ( int x = 0; x < 3; ++x )
        {
            if ( rowSum[x] > 0 )
            {
                rowSum[x] = std::abs ( ( rowSum[x] / rowsTotalSum ) * std::log10 ( rowSum[x] / rowsTotalSum ) );
                rowsUncertaintyTotal += rowSum[x];
            }
            if ( columnSum[x] > 0 )
            {
                columnSum[x] = std::abs ( ( columnSum[x] / rowsTotalSum ) * std::log10 ( columnSum[x] / rowsTotalSum ) );
                columnsUncertaintyTotal += columnSum[x];
            }
        }
    }
    double kab = 0;
    if ( log == Data::Logarithm::Natural )
    {
        for ( int x = 0; x < 9; ++x )
        {
            if ( input[x] > 0 )
            {
                kab += std::abs ( input[x] / rowsTotalSum * std::log ( input[x] / rowsTotalSum ) );
            }
        }
    }
    else
    {
        for ( int x = 0; x < 9; ++x )
        {
            if ( input[x] > 0 )
            {
                kab += std::abs ( input[x] / rowsTotalSum * std::log10 ( input[x] / rowsTotalSum ) );
            }
        }
    }
    return ( rowsUncertaintyTotal + columnsUncertaintyTotal - kab );
}

double Math::roundDouble ( double source, int decimals )
{
    return std::ceil ( ( source * std::pow ( 10, decimals ) ) - 0.49L ) / std::pow ( 10, decimals );
}
