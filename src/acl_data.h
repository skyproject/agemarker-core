/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef ACL_DATA_H
#define ACL_DATA_H

/* The number of chemical elements used in Agemarker calculations */
#define ELEMENTS_COUNT          118

/* The number of oxides used in Agemarker calculations */
#define OXIDES_COUNT            53

#include <vector>
#include <map>

#include "acl_mtrandom.h"
#include "acl_atomic.h"

namespace ACL
{
    class AGEMARKERCORESHARED_EXPORT Data
    {
        public:
            enum class Logarithm
            {
                Natural,
                Decimal
            };
            struct CalculationInput
            {
                std::vector<double> oxidesContent;
                std::vector<double> elementsContent;
                std::vector<double> elementsWeight;
                int decimalPrecision;
                uint64_t multiplier;
                int intervalsNumber;
                Data::Logarithm log;
                int threadsNumber;
            };
            struct CalculationThreadInput
            {
                std::vector<double> elementsWeight;
                std::vector<uint64_t> atomAllEight;
                Data::Logarithm logarithm;
                uint64_t atomAllEightSum;
                uint64_t startIteration;
                uint64_t endIteration;
                int decimalPrecision;
            };
            struct CalculationThreadShared
            {
                AtomicUInt64 *atomsUsed;
                MTRandom *random;
            };
            struct CalculationResult
            {
                Data::CalculationInput calculationInput;
                std::vector<uint64_t> atoms;
                std::vector<double> ip;
                std::vector<double> ipSqrt;
                std::vector<uint64_t> ipCount;
                uint64_t atomsSum;
                double ipAverage = 0;
                double ipSqrtAverage = 0;
                double ipVariance = 0;
                double ipSqrtVariance = 0;
                double ipStandardDeviation = 0;
                double ipSqrtStandardDeviation = 0;
                double ipRange = 0;
                double ipSqrtRange = 0;
                double ipIntervalLength = 0;
                double ipSqrtIntervalLength = 0;
                std::vector<double> ipIntervalMinimum;
                std::vector<double> ipSqrtIntervalMinimum;
                std::vector<double> ipIntervalMaximum;
                std::vector<double> ipSqrtIntervalMaximum;
                std::vector<double> ipIntervalCenter;
                std::vector<double> ipSqrtIntervalCenter;
                std::vector<uint64_t> ipIntervalCount;
                std::vector<uint64_t> ipSqrtIntervalCount;
            };
            typedef std::map<double, uint64_t> IpValuesMap;
    };
}

#endif // ACL_DATA_H
