/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
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
                MTRandom *random;
                /* 'atomsUsed' points to the array of 118
                 * values; each of them represents the number
                 * of already chosen atomic weights for a
                 * single chemical element.
                 */
                AtomicUInt64 *atomsUsed;
                /* 'runningThreads' represents the number of active
                 * calculation threads. When single thread's destructor
                 * is called, it decrements this number by 1. In case
                 * it is equal to 0, all shared pointers are deallocated.
                 */
                int *runningThreads;
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
