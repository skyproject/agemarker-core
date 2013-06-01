/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "acl_calculationthread.h"
#include "acl_mtrandom.h"
#include "acl_math.h"

using namespace ACL;

CalculationThread::CalculationThread ( Data::CalculationThreadInput input )
{
    this->threadInput = input;
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
    MTRandom *rnd = new MTRandom();
    std::vector<double> input;
    uint64_t count[118];
    int x = 0;
    for ( x = 0; x < 118; x++ )
    {
        count[x] = 0;
    }
    uint64_t r, rr;
    Data::IpValuesMap ipMap;
    for ( uint64_t l = this->threadInput.startIteration;
          l < this->threadInput.endIteration; l++ )
    {
        if ( this->cancel == true )
        {
            break;
        }
        this->syncMutex.lock();
        if ( this->pause == true )
        {
            this->pauseCond.wait ( &this->syncMutex );
        }
        this->syncMutex.unlock();
        input.clear();
        for ( x = 0; x < 9; x++ )
        {
            input.push_back ( 0 );
        }
        for ( int y = 0; y < 8; y++ )
        {
            while ( input[y] == 0 )
            {
                r = rnd->getRandomULongLong ( 1, this->threadInput.atomAllEightSum );
                rr = 0;
                for ( int z = 0; z < 118; z++ )
                {
                    if ( this->threadInput.atomAllEight[z] != 0 )
                    {
                        rr += this->threadInput.atomAllEight[z];
                        if ( r <= rr && count[z] < this->threadInput.atomAllEight[z] )
                        {
                            input[y] = this->threadInput.elementsWeight[z];
                            count[z]++;
                            break;
                        }
                    }
                }
            }
            input[8] += input[y];
        }
        double ip = Math::roundDouble ( Math::ip ( input, this->threadInput.logarithm ), this->threadInput.decimalPrecision );
        std::map<double, uint64_t>::iterator it = ipMap.find ( ip );
        if ( it != ipMap.end() )
        {
            it->second += 1;
        }
        else
        {
            ipMap.insert ( std::pair<double, uint64_t> ( ip, 1 ) );
        }
    }
    emit threadCalculationFinished ( ipMap );
}
