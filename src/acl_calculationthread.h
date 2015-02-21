/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#ifndef ACL_CALCULATIONTHREAD_H
#define ACL_CALCULATIONTHREAD_H

#include <QWaitCondition>
#include <QThread>
#include <QMutex>

#include "acl_data.h"

namespace ACL
{
    class CalculationThread : public QThread
    {
            Q_OBJECT

        public:
            CalculationThread(Data::Structs::CalculationThreadInput input,
                              Data::Structs::CalculationThreadShared shared);
            ~CalculationThread();
            void pauseThread();
            void resumeThread();
            void removeThread();

        signals:
            void threadCalculationFinished(Data::Types::IpValuesMap calculatedIpValues);

        private:
            void run();
            Data::Structs::CalculationThreadInput threadInput;
            Data::Structs::CalculationThreadShared threadData;
            QMutex syncMutex;
            QWaitCondition pauseCond;
            bool pause = false;
            bool cancel = false;
    };
}

#endif // ACL_CALCULATIONTHREAD_H
