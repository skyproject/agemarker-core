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

#include <atomic>
#include <vector>
#include <map>

#include "acl_mtrandom.h"
#include "acl_float.h"

namespace ACL
{
    namespace Data
    {
        enum class Logarithm
        {
            Natural,
            Decimal
        };
        enum class ElementsContentUnits
        {
            MassPercent,
            NumberOfAtoms
        };
        namespace Types
        {
            /* A uint64_t wrapper of std::atomic type used for multithreaded
             * Ip calculation */
            struct AGEMARKERCORESHARED_EXPORT AtomicUInt64
            {
                std::atomic<uint64_t> atomic;

                AtomicUInt64() : atomic(uint64_t())
                {
                }
                AtomicUInt64(AtomicUInt64 const &other) : atomic(other.atomic.load())
                {
                }
                explicit AtomicUInt64(uint64_t const &v) : atomic(v)
                {
                }
                explicit AtomicUInt64(std::atomic<uint64_t> const &a) : atomic(a.load())
                {
                }

                AtomicUInt64 &operator= (AtomicUInt64 const &other)
                {
                    atomic.store(other.atomic.load());
                    return *this;
                }

                AtomicUInt64 operator++ ()
                {
                    this->atomic++;
                    return *this;
                }

                template <typename T_i>
                AtomicUInt64 operator= (T_i const &other)
                {
                    this->atomic = other;
                    return *this;
                }

                bool operator< (AtomicUInt64 const &other)
                {
                    if (atomic < other.atomic)
                    {
                        return true;
                    }
                    return false;
                }

                bool operator> (AtomicUInt64 const &other)
                {
                    if (atomic > other.atomic)
                    {
                        return true;
                    }
                    return false;
                }

                template <typename T_i>
                bool operator< (T_i const &other)
                {
                    if (atomic < other)
                    {
                        return true;
                    }
                    return false;
                }

                template <typename T_i>
                bool operator> (T_i const &other)
                {
                    if (atomic > other)
                    {
                        return true;
                    }
                    return false;
                }
            };
            /* A statistical value type consisting of two
             * values - sample and population. */
            template <typename T>
            struct AGEMARKERCORESHARED_EXPORT StatisticalValue
            {
                T sample = 0;
                T population = 0;

                StatisticalValue()
                {
                }

                StatisticalValue(T sampleValue, T populationValue)
                {
                    this->sample = sampleValue;
                    this->population = populationValue;
                }

                inline StatisticalValue operator=(StatisticalValue sv)
                {
                    this->sample = sv.sample;
                    this->population = sv.population;
                    return *this;
                }

                inline StatisticalValue operator+=(StatisticalValue sv)
                {
                    this->sample += sv.sample;
                    this->population += sv.population;
                    return *this;
                }

                template <typename T2>
                inline StatisticalValue operator/(T2 value)
                {
                    this->sample = this->sample / value;
                    this->population = this->population / value;
                    return *this;
                }
            };
            /* typedefs */
            typedef StatisticalValue<uint64_t> StatisticalUInt64;
            typedef StatisticalValue<Float> StatisticalFloat;
            typedef std::map<Float, uint64_t> IpValuesMap;
        }
        /* Data structs used _internally_ in Agemarker Core Library. */
        namespace Structs
        {
            struct CalculationAtomData
            {
                std::vector<Float> elementsNewContent;
                std::vector<uint64_t> allEight;
                std::vector<uint64_t> all;
                uint64_t allEightSum = 0;
                uint64_t allSum = 0;
            };
            struct CalculationThreadInput
            {
                std::vector<Float> elementsWeight;
                std::vector<uint64_t> atomAllEight;
                Logarithm logarithm;
                uint64_t atomAllEightSum;
                uint64_t startIteration;
                uint64_t endIteration;
                int decimalPrecision;
            };
            struct CalculationThreadShared
            {
                MTRandom *random;
                /* 'atomsUsed' represents an array with the
                 * numbers of already choosen atomic weights
                 * of a single chemical element.
                 */
                std::vector<Types::AtomicUInt64> *atomsUsed;
                /* 'runningThreads' represents the number of active
                 * calculation threads. When single thread's destructor
                 * is called, it decrements this number by 1. In case
                 * the value is equal to 0, all shared pointers are
                 * deallocated.
                 */
                int *runningThreads; /* <- TODO: Use smart pointers instead. */
            };
        }
        struct CalculationInput
        {
            std::vector<Float> oxidesContent;
            std::vector<Float> elementsContent;
            std::vector<Float> elementsWeight;
            int decimalPrecision;
            uint64_t multiplier;
            int intervalsNumber;
            Logarithm log;
            ElementsContentUnits elementsContentUnits;
            int threadsNumber;
        };
        struct CalculationResultOptions {
            bool includeApproximateFrequencies;
            int approximateFrequencyPrecision;
            bool includeApproximateValues;
        };
        struct CalculationResult
        {
            CalculationInput calculationInput;
            std::vector<uint64_t> atoms;
            std::vector<Float> ip;
            std::vector<Float> ipSqrt;
            std::vector<uint64_t> ipFrequency;
            std::vector<uint64_t> ipTheoreticalFrequency;
            uint64_t atomsSum;
            Types::StatisticalFloat ipAverage;
            Types::StatisticalFloat ipSqrtAverage;
            Types::StatisticalFloat ipVariance;
            Types::StatisticalFloat ipSqrtVariance;
            Types::StatisticalFloat ipStandardDeviation;
            Types::StatisticalFloat ipSqrtStandardDeviation;
            Types::StatisticalFloat ipSkewnessOfDataset;
            Types::StatisticalFloat ipSqrtSkewnessOfDataset;
            Types::StatisticalFloat ipExcessKurtosisOfDataset;
            Types::StatisticalFloat ipSqrtExcessKurtosisOfDataset;
            Float ipMeanSquareError;
            Float ipSqrtMeanSquareError;
            Float ipRange;
            Float ipSqrtRange;
            Float ipIntervalLength;
            Float ipSqrtIntervalLength;
            std::vector<Float> ipIntervalMinimum;
            std::vector<Float> ipSqrtIntervalMinimum;
            std::vector<Float> ipIntervalMaximum;
            std::vector<Float> ipSqrtIntervalMaximum;
            std::vector<Float> ipIntervalCenter;
            std::vector<Float> ipSqrtIntervalCenter;
            std::vector<Types::StatisticalUInt64> ipIntervalCount;
            std::vector<Types::StatisticalUInt64> ipSqrtIntervalCount;
        };
    }
}

#endif // ACL_DATA_H
