/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include "acl_math.h"

using namespace ACL;
using namespace boost;

float128 Math::ip(std::vector<float128> input, Data::Logarithm log)
{
    float128 rowSum[3];
    float128 columnSum[3];
    float128 rowsTotalSum = 0;
    float128 rowsUncertaintyTotal = 0;
    float128 columnsUncertaintyTotal = 0;
    for (int x = 0; x < 3; ++x)
    {
        columnSum[x] = input[x] + input[(x + 3)] + input[(x + 6)];
        rowSum[x] = input[(x * 3)] + input[(x * 3) + 1] + input[(x * 3) + 2];
        rowsTotalSum += rowSum[x];
    }

    /* Fill 'rowSum' array with uncertainty values for each row */
    if (log == Data::Logarithm::Natural)
    {
        for (int x = 0; x < 3; ++x)
        {
            if (rowSum[x] > 0)
            {
                rowSum[x] = multiprecision::abs((rowSum[x] / rowsTotalSum) * multiprecision::log(rowSum[x] / rowsTotalSum));
                rowsUncertaintyTotal += rowSum[x];
            }
            if (columnSum[x] > 0)
            {
                columnSum[x] = multiprecision::abs((columnSum[x] / rowsTotalSum) * multiprecision::log(columnSum[x] / rowsTotalSum));
                columnsUncertaintyTotal += columnSum[x];
            }
        }
    }
    else
    {
        for (int x = 0; x < 3; ++x)
        {
            if (rowSum[x] > 0)
            {
                rowSum[x] = multiprecision::abs((rowSum[x] / rowsTotalSum) * multiprecision::log10(rowSum[x] / rowsTotalSum));
                rowsUncertaintyTotal += rowSum[x];
            }
            if (columnSum[x] > 0)
            {
                columnSum[x] = multiprecision::abs((columnSum[x] / rowsTotalSum) * multiprecision::log10(columnSum[x] / rowsTotalSum));
                columnsUncertaintyTotal += columnSum[x];
            }
        }
    }
    float128 kab = 0;
    if (log == Data::Logarithm::Natural)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (input[x] > 0)
            {
                kab += multiprecision::abs(input[x] / rowsTotalSum * multiprecision::log(input[x] / rowsTotalSum));
            }
        }
    }
    else
    {
        for (int x = 0; x < 9; ++x)
        {
            if (input[x] > 0)
            {
                kab += multiprecision::abs(input[x] / rowsTotalSum * multiprecision::log10(input[x] / rowsTotalSum));
            }
        }
    }
    return (rowsUncertaintyTotal + columnsUncertaintyTotal - kab);
}

float128 Math::roundFloat128(float128 source, int decimals)
{
    return multiprecision::ceil((source * std::pow(10, decimals)) - 0.49Q) / std::pow(10, decimals);
}
