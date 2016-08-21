/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include <QMetaType>
#include <QThread>

#include "acl_calculation.h"
#include "acl_agemarkercore.h"
#include "acl_results.h"
#include "acl_atoms.h"
#include "acl_math.h"

using namespace ACL;

AgemarkerCore::AgemarkerCore(Data::CalculationInput input,
                             Data::CalculationResultOptions options)
{
    qRegisterMetaType<Data::Types::IpValuesMap>("Data::Types::IpValuesMap");
    qRegisterMetaType<Data::Types::StatisticalUInt64>("Data::Types::StatisticalUInt64");
    qRegisterMetaType<Data::Types::StatisticalFloat>("Data::Types::StatisticalFloat");
    this->data = input;
    this->resultOptions = options;
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
    threadsShared.atomsUsed = new std::vector<Data::Types::AtomicUInt64>;
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        threadsShared.atomsUsed->push_back(Data::Types::AtomicUInt64(0));
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

        /* A somewhat-dirty workaround for Qt's multithreading "You're doing it wrong".
         *
         * See "http://blog.qt.io/blog/2010/06/17/youre-doing-it-wrong",
         * "http://stackoverflow.com/questions/19041742/qt-no-matching-function-for-call-to-connect-modifying-qt-fortune-threaded-ser/19045952#19045952"
         * for more information.
         */
        Calculation *c = new Calculation(threadInput, threadsShared);
        connect(c, SIGNAL(threadCalculationFinished(Data::Types::IpValuesMap)),
                this, SLOT(collectThreadResult(Data::Types::IpValuesMap)));
        QThread *t = new QThread(this);
        connect(t, &QThread::started, c, &Calculation::run);

        /* Memory clean-up */
        connect(c, SIGNAL(threadCalculationFinished(Data::Types::IpValuesMap)), t, SLOT(quit()));
        connect(c, SIGNAL(threadCalculationFinished(Data::Types::IpValuesMap)), c, SLOT(deleteLater()));
        connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

        CalculationThread *ct = new CalculationThread;
        ct->calculation = c;
        ct->thread = t;
        this->threads.push_back(ct);

        c->moveToThread(t);
        t->start();
    }
}

void AgemarkerCore::pauseCalculation()
{
    for (uint x = 0; x < this->threads.size(); ++x)
    {
        this->threads[x]->calculation->pauseThread();
    }
}

void AgemarkerCore::resumeCalculation()
{
    for (uint x = 0; x < this->threads.size(); ++x)
    {
        this->threads[x]->calculation->resumeThread();
    }
}

void AgemarkerCore::removeCalculation()
{
    for (uint x = 0; x < this->threads.size(); ++x)
    {
        this->threads[x]->calculation->removeThread();
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
            this->calculatedIp.insert(std::pair<Float, uint64_t> (iter->first, iter->second));
        }
    }
    this->runningThreads--;
    if (this->runningThreads == 0)
    {
        for (int x = 0; x < this->threads.size(); ++x)
        {
            delete this->threads[x];
        }
        Results r(this->data, this->resultOptions, this->atoms, this->calculatedIp);
        emit calculationFinished(r.getCalculationResults());
    }
}
