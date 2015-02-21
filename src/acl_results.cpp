#include "acl_results.h"
#include "acl_math.h"

using namespace ACL;

Results::Results(Data::CalculationInput inputData, Data::Structs::CalculationAtomData atomData,
                 Data::Types::IpValuesMap ipValues)
{
    this->data = inputData;
    this->atoms = atomData;
    this->numberOfIpValues = ipValues.size();
    this->calculatedIp = ipValues;
}

Results::~Results()
{

}

Data::CalculationResult Results::getCalculationResults()
{
    Data::CalculationResult r;

    r.calculationInput = this->data;

    r.atoms = this->atoms.allEight;
    r.atomsSum = this->atoms.allEightSum;

    for (Data::Types::IpValuesMap::const_iterator iter = this->calculatedIp.begin();
         iter != this->calculatedIp.end(); ++iter)
    {
        r.ip.push_back(iter->first);
        r.ipSqrt.push_back(Math::roundDouble(std::sqrt(iter->first), this->data.decimalPrecision));
        r.ipFrequency.push_back(iter->second);
    }

    r.ipTheoreticalFrequency = calculateTheoreticalIpValues(r.ipFrequency);

    if (this->numberOfIpValues > 0)
    {
        try
        {
            r = calculateStatistics(r);
            r = calculateIntervals(r);
        }
        catch (...)
        {
        }
    }
    else
    {
        for (int x = 0; x < this->data.intervalsNumber; ++x)
        {
            r.ipIntervalMinimum.push_back(0);
            r.ipIntervalMaximum.push_back(0);
            r.ipIntervalCenter.push_back(0);
            r.ipSqrtIntervalMinimum.push_back(0);
            r.ipSqrtIntervalMaximum.push_back(0);
            r.ipSqrtIntervalCenter.push_back(0);
            r.ipIntervalCount.push_back(Data::Types::StatisticalUInt64(0, 0));
            r.ipSqrtIntervalCount.push_back(Data::Types::StatisticalUInt64(0, 0));
        }
    }

    return r;
}

std::vector<uint64_t> Results::calculateTheoreticalIpValues(std::vector<uint64_t> ipFrequency)
{
    std::vector<uint64_t>::const_iterator minCount = std::min_element(std::begin(ipFrequency),
                                                                      std::end(ipFrequency));

    std::vector<uint64_t> out;
    for (std::vector<uint64_t>::const_iterator iter = ipFrequency.begin();
         iter != ipFrequency.end(); ++iter)
    {
        out.push_back(std::round((double)*iter / (double)*minCount));
    }

    return out;
}

Data::CalculationResult Results::calculateStatistics(ACL::Data::CalculationResult r)
{
    uint64_t atomAllSumPopulation = std::accumulate(r.ipTheoreticalFrequency.begin(),
                                                    r.ipTheoreticalFrequency.end(), 0);

    Data::Types::StatisticalDouble ipSum;
    Data::Types::StatisticalDouble ipSqrtSum;

    for (int x = 0; x < this->numberOfIpValues; ++x)
    {
        ipSum.sample += (r.ip[x] * r.ipFrequency[x]);
        ipSum.population += (r.ip[x] * r.ipTheoreticalFrequency[x]);
        ipSqrtSum.sample += (r.ipSqrt[x] * r.ipFrequency[x]);
        ipSqrtSum.population += (r.ipSqrt[x] * r.ipTheoreticalFrequency[x]);
    }

    r.ipAverage.sample = (ipSum.sample / this->atoms.allSum);
    r.ipAverage.population = (ipSum.population / atomAllSumPopulation);

    r.ipSqrtAverage.sample = (ipSqrtSum.sample / this->atoms.allSum);
    r.ipSqrtAverage.population = (ipSqrtSum.population / atomAllSumPopulation);

    for (int x = 0; x < this->numberOfIpValues; ++x)
    {
        r.ipSqrtVariance.sample += (std::pow((r.ipSqrt[x] - r.ipSqrtAverage.sample), 2) * r.ipFrequency[x]);
        r.ipSqrtVariance.population += (std::pow((r.ipSqrt[x] - r.ipSqrtAverage.population), 2) * r.ipTheoreticalFrequency[x]);

        r.ipVariance.sample += (std::pow((r.ip[x] - r.ipAverage.sample), 2) * r.ipFrequency[x]);
        r.ipVariance.population += (std::pow((r.ip[x] - r.ipAverage.population), 2) * r.ipTheoreticalFrequency[x]);

        r.ipSqrtSkewnessOfDataset.sample += (std::pow((r.ipSqrt[x] - r.ipSqrtAverage.sample), 3) * r.ipFrequency[x]);
        r.ipSqrtSkewnessOfDataset.population += (std::pow((r.ipSqrt[x] - r.ipSqrtAverage.population), 3) * r.ipTheoreticalFrequency[x]);

        r.ipSkewnessOfDataset.sample += (std::pow((r.ip[x] - r.ipAverage.sample), 3) * r.ipFrequency[x]);
        r.ipSkewnessOfDataset.population += (std::pow((r.ip[x] - r.ipAverage.population), 3) * r.ipTheoreticalFrequency[x]);

        r.ipSqrtExcessKurtosisOfDataset.sample += (std::pow((r.ipSqrt[x] - r.ipSqrtAverage.sample), 4) * r.ipFrequency[x]);
        r.ipSqrtExcessKurtosisOfDataset.population += (std::pow((r.ipSqrt[x] - r.ipSqrtAverage.population), 4) * r.ipTheoreticalFrequency[x]);

        r.ipExcessKurtosisOfDataset.sample += (std::pow((r.ip[x] - r.ipAverage.sample), 4) * r.ipFrequency[x]);
        r.ipExcessKurtosisOfDataset.population += (std::pow((r.ip[x] - r.ipAverage.population), 4) * r.ipTheoreticalFrequency[x]);
    }

    r.ipSqrtVariance.sample = (r.ipSqrtVariance.sample / (this->atoms.allSum - 1));
    r.ipSqrtVariance.population = (r.ipSqrtVariance.population / (atomAllSumPopulation - 1));

    r.ipVariance.sample = (r.ipVariance.sample / (this->atoms.allSum - 1));
    r.ipVariance.population = (r.ipVariance.population / (atomAllSumPopulation - 1));

    r.ipSqrtStandardDeviation.sample = std::sqrt(r.ipSqrtVariance.sample);
    r.ipSqrtStandardDeviation.population = std::sqrt(r.ipSqrtVariance.population);

    r.ipStandardDeviation.sample = std::sqrt(r.ipVariance.sample);
    r.ipStandardDeviation.population = std::sqrt(r.ipVariance.population);

    r = calculateSkewnessOfDataset(r);
    r = calculateExcessKurtosis(r);

    /* Mean square error */

    r.ipSqrtMeanSquareError = (r.ipSqrtVariance.sample / this->atoms.allSum);
    r.ipMeanSquareError = (r.ipVariance.sample / this->atoms.allSum);

    return r;
}

Data::CalculationResult Results::calculateIntervals(ACL::Data::CalculationResult r)
{
    r.ipRange = (r.ip[(this->numberOfIpValues - 1)] - r.ip[0]);
    r.ipIntervalLength = (r.ipRange / this->data.intervalsNumber);
    r.ipSqrtRange = (std::sqrt(r.ip[(this->numberOfIpValues - 1)]) - std::sqrt(r.ip[0]));
    r.ipSqrtIntervalLength = (r.ipSqrtRange / this->data.intervalsNumber);

    for (int x = 0; x < this->data.intervalsNumber; ++x)
    {
        r.ipIntervalMinimum.push_back(r.ip[0] + (r.ipIntervalLength * x));
        r.ipSqrtIntervalMinimum.push_back(std::sqrt(r.ip[0]) + (r.ipSqrtIntervalLength * x));

        if (x < (this->data.intervalsNumber - 1))
        {
            r.ipIntervalMaximum.push_back(r.ip[0] + (r.ipIntervalLength * (x + 1)));
            r.ipSqrtIntervalMaximum.push_back(r.ipSqrt[0] + (r.ipSqrtIntervalLength * (x + 1)));
        }
        else
        {
            r.ipIntervalMaximum.push_back(r.ip[(this->numberOfIpValues - 1)]);
            r.ipSqrtIntervalMaximum.push_back(r.ipSqrt[(this->numberOfIpValues - 1)]);
        }

        r.ipIntervalCenter.push_back((r.ipIntervalMinimum[x] + r.ipIntervalMaximum[x]) / 2);
        r.ipSqrtIntervalCenter.push_back((r.ipSqrtIntervalMinimum[x] + r.ipSqrtIntervalMaximum[x]) / 2);

        r.ipIntervalCount.push_back(Data::Types::StatisticalUInt64(0, 0));
        r.ipSqrtIntervalCount.push_back(Data::Types::StatisticalUInt64(0, 0));
    }
    for (int x = 0; x < this->numberOfIpValues; ++x)
    {
        for (int y = 0; y < this->data.intervalsNumber; ++y)
        {
            if (r.ip[x] <= r.ipIntervalMaximum[y])
            {
                r.ipIntervalCount[y].sample += r.ipFrequency[x];
                r.ipIntervalCount[y].population += r.ipTheoreticalFrequency[x];
                break;
            }
        }
        for (int y = 0; y < this->data.intervalsNumber; ++y)
        {
            if (r.ipSqrt[x] <= r.ipSqrtIntervalMaximum[y])
            {
                r.ipSqrtIntervalCount[y].sample += r.ipFrequency[x];
                r.ipSqrtIntervalCount[y].population += r.ipTheoreticalFrequency[x];
                break;
            }
        }
    }

    return r;
}

Data::CalculationResult Results::calculateSkewnessOfDataset(Data::CalculationResult r)
{
    uint64_t atomAllSumPopulation = std::accumulate(r.ipTheoreticalFrequency.begin(),
                                                    r.ipTheoreticalFrequency.end(), 0);

    r.ipSqrtSkewnessOfDataset.sample = (r.ipSqrtSkewnessOfDataset.sample / (std::pow(r.ipSqrtStandardDeviation.sample, 3)));
    r.ipSqrtSkewnessOfDataset.population = (r.ipSqrtSkewnessOfDataset.population / (std::pow(r.ipSqrtStandardDeviation.population, 3)));

    r.ipSkewnessOfDataset.sample = (r.ipSkewnessOfDataset.sample / (std::pow(r.ipStandardDeviation.sample, 3)));
    r.ipSkewnessOfDataset.population = (r.ipSkewnessOfDataset.population / (std::pow(r.ipStandardDeviation.population, 3)));

    double denom = ((this->atoms.allSum - 1) * (this->atoms.allSum - 2));
    double fraction = (this->atoms.allSum / denom);

    double denomPopulation = ((atomAllSumPopulation - 1) * (atomAllSumPopulation - 2));
    double fractionPopulation = (atomAllSumPopulation / denomPopulation);

    r.ipSqrtSkewnessOfDataset.sample = (r.ipSqrtSkewnessOfDataset.sample * fraction);
    r.ipSqrtSkewnessOfDataset.population = (r.ipSqrtSkewnessOfDataset.population * fractionPopulation);

    r.ipSkewnessOfDataset.sample = (r.ipSkewnessOfDataset.sample * fraction);
    r.ipSkewnessOfDataset.population = (r.ipSkewnessOfDataset.population * fractionPopulation);

    return r;
}

Data::CalculationResult Results::calculateExcessKurtosis(Data::CalculationResult r)
{
    uint64_t atomAllSumPopulation = std::accumulate(r.ipTheoreticalFrequency.begin(),
                                                    r.ipTheoreticalFrequency.end(), 0);

    r.ipSqrtExcessKurtosisOfDataset.sample = (r.ipSqrtExcessKurtosisOfDataset.sample / (std::pow(r.ipSqrtStandardDeviation.sample, 4)));
    r.ipSqrtExcessKurtosisOfDataset.population = (r.ipSqrtExcessKurtosisOfDataset.population / (std::pow(r.ipSqrtStandardDeviation.population, 4)));\

    r.ipExcessKurtosisOfDataset.sample = (r.ipExcessKurtosisOfDataset.sample / (std::pow(r.ipStandardDeviation.sample, 4)));
    r.ipExcessKurtosisOfDataset.population = (r.ipExcessKurtosisOfDataset.population / (std::pow(r.ipStandardDeviation.population, 4)));

    double x0 = (this->atoms.allSum + 1);
    double x1 = (this->atoms.allSum - 1);
    double x2 = (this->atoms.allSum - 2);
    double x3 = (this->atoms.allSum - 3);

    double num = (this->atoms.allSum * x0);
    double denom = (x1 * x2 * x3);
    double fraction = (num / denom);

    x0 = (atomAllSumPopulation + 1);
    x1 = (atomAllSumPopulation - 1);
    x2 = (atomAllSumPopulation - 2);
    x3 = (atomAllSumPopulation - 3);

    double numPopulation = (atomAllSumPopulation * x0);
    double denomPopulation = (x1 * x2 * x3);
    double fractionPopulation = (numPopulation / denomPopulation);

    r.ipSqrtExcessKurtosisOfDataset.sample = (r.ipSqrtExcessKurtosisOfDataset.sample * fraction);
    r.ipSqrtExcessKurtosisOfDataset.population = (r.ipSqrtExcessKurtosisOfDataset.population * fractionPopulation);

    r.ipExcessKurtosisOfDataset.sample = (r.ipExcessKurtosisOfDataset.sample * fraction);
    r.ipExcessKurtosisOfDataset.population = (r.ipExcessKurtosisOfDataset.population * fractionPopulation);

    num = (3 * (std::pow((this->atoms.allSum - 1), 2)));
    denom = ((this->atoms.allSum - 2) * (this->atoms.allSum - 3));
    fraction = (num / denom);

    numPopulation = (3 * (std::pow((atomAllSumPopulation - 1), 2)));
    denomPopulation = ((atomAllSumPopulation - 2) * (atomAllSumPopulation - 3));
    fractionPopulation = (numPopulation / denomPopulation);

    r.ipSqrtExcessKurtosisOfDataset.sample = (r.ipSqrtExcessKurtosisOfDataset.sample - fraction);
    r.ipSqrtExcessKurtosisOfDataset.population = (r.ipSqrtExcessKurtosisOfDataset.population - fractionPopulation);

    r.ipExcessKurtosisOfDataset.sample = (r.ipExcessKurtosisOfDataset.sample - fraction);
    r.ipExcessKurtosisOfDataset.population = (r.ipExcessKurtosisOfDataset.population - fractionPopulation);

    return r;
}
