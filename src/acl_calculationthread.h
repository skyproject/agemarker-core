/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker-core library licensed
 * under the GNU Lesser General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef ACL_CALCULATIONTHREAD_H
#define ACL_CALCULATIONTHREAD_H

#include <QWaitCondition>
#include <QObject>
#include <QThread>
#include <QMutex>

#include "acl_data.h"

namespace ACL
{
    class CalculationThread : public QThread
    {
        Q_OBJECT

        public:
            CalculationThread ( Data::CalculationThreadInput input );
            void pauseThread();
            void resumeThread();
            void removeThread();

        signals:
            void threadCalculationFinished ( Data::IpValuesMap calculatedIpValues );

        private:
            void run();
            Data::CalculationThreadInput threadInput;
            QMutex syncMutex;
            QWaitCondition pauseCond;
            bool pause = false;
            bool cancel = false;
    };
}

#endif // ACL_CALCULATIONTHREAD_H
