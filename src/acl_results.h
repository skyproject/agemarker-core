/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#ifndef RESULTS_H
#define RESULTS_H

#include <QObject>

#include "acl_data.h"

namespace ACL
{
    class AGEMARKERCORESHARED_EXPORT Results : public QObject
    {
            Q_OBJECT

        public:
            Results(Data::CalculationInput inputData, Data::CalculationResultOptions resultOptions,
                    Data::Structs::CalculationAtomData atomData, Data::Types::IpValuesMap ipValues);
            ~Results();
            Data::CalculationResult getCalculationResults();

        private:
            Data::CalculationResult calculateStatistics(Data::CalculationResult r);
            Data::CalculationResult calculateIntervals(Data::CalculationResult r);
            Data::CalculationResult calculateSkewnessOfDataset(Data::CalculationResult r);
            Data::CalculationResult calculateExcessKurtosis(Data::CalculationResult r);
            std::vector<Float> calculateApproximateIpFrequency(std::vector<uint64_t> ipFrequency);
            Data::CalculationInput data;
            Data::CalculationResultOptions options;
            Data::Structs::CalculationAtomData atoms;
            Data::Types::IpValuesMap calculatedIp;
            int numberOfIpValues;
    };
}

#endif // RESULTS_H
