/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include <QMetaType>

#include "acl_calculationthread.h"
#include "acl_agemarkercore.h"
#include "acl_results.h"
#include "acl_atoms.h"
#include "acl_math.h"

using namespace ACL;

AgemarkerCore::AgemarkerCore(Data::CalculationInput input)
{
    qRegisterMetaType<Data::Types::IpValuesMap>("Data::Types::IpValuesMap");
    qRegisterMetaType<Data::Types::StatisticalUInt64>("Data::Types::StatisticalUInt64");
    qRegisterMetaType<Data::Types::StatisticalFloat128>("Data::Types::StatisticalFloat128");
    this->data = input;
    this->runningThreads = input.threadsNumber;
}

AgemarkerCore::~AgemarkerCore()
{

}

void AgemarkerCore::startCalculation()
{
    Atoms a(this->data, this->atoms);
    this->atoms = a.getAtomData();

    Data::Structs::CalculationThreadShared threadsShared;
    threadsShared.random = new MTRandom();
    threadsShared.runningThreads = new int();
    *threadsShared.runningThreads = this->runningThreads;
    threadsShared.atomsUsed = new Data::Types::AtomicUInt64[ELEMENTS_COUNT];
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        threadsShared.atomsUsed[x] = 0;
    }

    Data::Structs::CalculationThreadInput threadInput;
    threadInput.logarithm = this->data.log;
    threadInput.atomAllEight = this->atoms.allEight;
    threadInput.atomAllEightSum = this->atoms.allEightSum;
    threadInput.elementsWeight = this->data.elementsWeight;
    threadInput.decimalPrecision = this->data.decimalPrecision;

    uint64_t threadIterations = round(this->atoms.allSum / this->runningThreads);

    for (int x = 0; x < this->runningThreads; ++x)
    {
        uint64_t start = (threadIterations * x);
        uint64_t end = 0;
        if ((x + 1) == this->runningThreads)
        {
            end = this->atoms.allSum;
        }
        else
        {
            end = (threadIterations * (x + 1));
        }
        threadInput.startIteration = start;
        threadInput.endIteration = end;
        CalculationThread *thread = new CalculationThread(threadInput, threadsShared);
        connect(thread, SIGNAL(threadCalculationFinished(Data::Types::IpValuesMap)),
                this, SLOT(collectThreadResult(Data::Types::IpValuesMap)));
        thread->start();
        this->threads.push_back(thread);
    }
}

void AgemarkerCore::pauseCalculation()
{
    for (uint x = 0; x < this->threads.size(); ++x)
    {
        this->threads[x]->pauseThread();
    }
}

void AgemarkerCore::resumeCalculation()
{
    for (uint x = 0; x < this->threads.size(); ++x)
    {
        this->threads[x]->resumeThread();
    }
}

void AgemarkerCore::removeCalculation()
{
    for (uint x = 0; x < this->threads.size(); ++x)
    {
        connect(this->threads[x], SIGNAL(finished()),
                this->threads[x], SLOT(deleteLater()));
        this->threads[x]->removeThread();
    }
    this->deleteLater();
}

void AgemarkerCore::collectThreadResult(Data::Types::IpValuesMap result)
{
    for (Data::Types::IpValuesMap::const_iterator iter = result.begin(); iter != result.end(); ++iter)
    {
        Data::Types::IpValuesMap::iterator it = this->calculatedIp.find(iter->first);
        if (it != this->calculatedIp.end())
        {
            it->second += iter->second;
        }
        else
        {
            this->calculatedIp.insert(std::pair<float128, uint64_t> (iter->first, iter->second));
        }
    }
    this->runningThreads--;
    if (this->runningThreads == 0)
    {
        for (int x = 0; x < this->threads.size(); ++x)
        {
            delete this->threads[x];
        }
        Results r(this->data, this->atoms, this->calculatedIp);
        emit calculationFinished(r.getCalculationResults());
    }
}
