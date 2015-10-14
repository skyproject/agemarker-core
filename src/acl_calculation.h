/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#ifndef ACL_CALCULATION_H
#define ACL_CALCULATION_H

#include <QWaitCondition>
#include <QMutex>

#include "acl_data.h"

namespace ACL
{
    class Calculation : public QObject
    {
            Q_OBJECT

        public:
            Calculation(Data::Structs::CalculationThreadInput input,
                        Data::Structs::CalculationThreadShared shared);
            ~Calculation();
            void pauseThread();
            void resumeThread();
            void removeThread();

        public slots:
            void run();

        signals:
            void threadCalculationFinished(Data::Types::IpValuesMap calculatedIpValues);

        private:
            Data::Structs::CalculationThreadInput threadInput;
            Data::Structs::CalculationThreadShared threadData;
            QMutex syncMutex;
            QWaitCondition pauseCond;
            bool pause = false;
            bool cancel = false;
    };
}

#endif // ACL_CALCULATION_H
