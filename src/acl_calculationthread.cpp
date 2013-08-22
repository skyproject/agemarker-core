/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include "acl_calculationthread.h"
#include "acl_math.h"

using namespace ACL;

CalculationThread::CalculationThread(Data::CalculationThreadInput input,
                                     Data::CalculationThreadShared shared)
{
    this->threadInput = input;
    this->threadData = shared;
}

CalculationThread::~CalculationThread()
{
    *this->threadData.runningThreads = *this->threadData.runningThreads - 1;
    if (*this->threadData.runningThreads == 0)
    {
        delete this->threadData.random;
        delete[] this->threadData.atomsUsed;
        delete this->threadData.runningThreads;
    }
}

void CalculationThread::pauseThread()
{
    this->syncMutex.lock();
    this->pause = true;
    this->syncMutex.unlock();
}

void CalculationThread::resumeThread()
{
    this->syncMutex.lock();
    this->pause = false;
    this->syncMutex.unlock();
    this->pauseCond.wakeAll();
}

void CalculationThread::removeThread()
{
    this->cancel = true;
    this->pauseCond.wakeAll();
}

void CalculationThread::run()
{
    std::vector<double> input = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint64_t atomicWeightSelector, atomicWeightIterator;
    Data::IpValuesMap ipMap;
    for (uint64_t l = this->threadInput.startIteration;
         l < this->threadInput.endIteration; ++l)
    {
        if (this->cancel == true)
        {
            break;
        }
        this->syncMutex.lock();
        if (this->pause == true)
        {
            this->pauseCond.wait(&this->syncMutex);
        }
        this->syncMutex.unlock();
        std::fill(input.begin(), input.end(), 0);
        /* The loop below randomly places 8 atomic weights
         * from 'atomAllEight' to 'input' vector and fills
         * the 9th value of this vector with the total sum
         * of atomic weights in it.
         */
        for (int input_it = 0; input_it < 8; ++input_it)
        {
            while (input[input_it] == 0)
            {
                atomicWeightSelector = this->threadData.random->getRandomULongLong(1, this->threadInput.atomAllEightSum);
                atomicWeightIterator = 0;
                for (int elements_it = 0; elements_it < ELEMENTS_COUNT; ++elements_it)
                {
                    if (this->threadInput.atomAllEight[elements_it] != 0)
                    {
                        atomicWeightIterator += this->threadInput.atomAllEight[elements_it];
                        if (atomicWeightSelector <= atomicWeightIterator
                            && this->threadData.atomsUsed[elements_it] <
                            this->threadInput.atomAllEight[elements_it])
                        {
                            input[input_it] = this->threadInput.elementsWeight[elements_it];
                            ++this->threadData.atomsUsed[elements_it];
                            break;
                        }
                    }
                }
            }
            input[8] += input[input_it];
        }
        double ip = Math::roundDouble(Math::ip(input, this->threadInput.logarithm), this->threadInput.decimalPrecision);
        std::map<double, uint64_t>::iterator it = ipMap.find(ip);
        if (it != ipMap.end())
        {
            it->second += 1;
        }
        else
        {
            ipMap.insert(std::pair<double, uint64_t>(ip, 1));
        }
    }
    emit threadCalculationFinished(ipMap);
}
