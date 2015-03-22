/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include "acl_math.h"

using namespace ACL;

Float Math::ip(std::vector<Float> input, Data::Logarithm log)
{
    Float rowSum[3];
    Float columnSum[3];
    Float rowsTotalSum = 0;
    Float rowsUncertaintyTotal = 0;
    Float columnsUncertaintyTotal = 0;
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
                rowSum[x] = FMath::abs((rowSum[x] / rowsTotalSum) * FMath::log(rowSum[x] / rowsTotalSum));
                rowsUncertaintyTotal += rowSum[x];
            }
            if (columnSum[x] > 0)
            {
                columnSum[x] = FMath::abs((columnSum[x] / rowsTotalSum) * FMath::log(columnSum[x] / rowsTotalSum));
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
                rowSum[x] = FMath::abs((rowSum[x] / rowsTotalSum) * FMath::log10(rowSum[x] / rowsTotalSum));
                rowsUncertaintyTotal += rowSum[x];
            }
            if (columnSum[x] > 0)
            {
                columnSum[x] = FMath::abs((columnSum[x] / rowsTotalSum) * FMath::log10(columnSum[x] / rowsTotalSum));
                columnsUncertaintyTotal += columnSum[x];
            }
        }
    }
    Float kab = 0;
    if (log == Data::Logarithm::Natural)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (input[x] > 0)
            {
                kab += FMath::abs(input[x] / rowsTotalSum * FMath::log(input[x] / rowsTotalSum));
            }
        }
    }
    else
    {
        for (int x = 0; x < 9; ++x)
        {
            if (input[x] > 0)
            {
                kab += FMath::abs(input[x] / rowsTotalSum * FMath::log10(input[x] / rowsTotalSum));
            }
        }
    }
    return (rowsUncertaintyTotal + columnsUncertaintyTotal - kab);
}
