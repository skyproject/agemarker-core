/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#ifndef ACL_AGEMARKERCORE_H
#define ACL_AGEMARKERCORE_H

#include <QObject>

#include "acl_calculation.h"
#include "acl_data.h"

namespace ACL
{
    class AGEMARKERCORESHARED_EXPORT AgemarkerCore : public QObject
    {
            Q_OBJECT

        public:
            AgemarkerCore(Data::CalculationInput input);
            ~AgemarkerCore();
            void startCalculation();
            void pauseCalculation();
            void resumeCalculation();
            void removeCalculation();

        signals:
            void calculationFinished(ACL::Data::CalculationResult result);

        private slots:
            void collectThreadResult(Data::Types::IpValuesMap result);

        private:
            void calculateAtoms();
            struct CalculationThread
            {
                /* A somewhat-dirty workaround for Qt's multithreading "You're doing it wrong".
                 *
                 * See "http://blog.qt.io/blog/2010/06/17/youre-doing-it-wrong",
                 * "http://stackoverflow.com/questions/19041742/qt-no-matching-function-for-call-to-connect-modifying-qt-fortune-threaded-ser/19045952#19045952"
                 * for more information.
                 */
                QThread *thread;
                ACL::Calculation *calculation;
            };
            std::vector<CalculationThread *> threads;
            Data::Types::IpValuesMap calculatedIp;
            Data::CalculationInput data;
            Data::Structs::CalculationAtomData atoms;
            int runningThreads;
    };
}

#endif // ACL_AGEMARKERCORE_H
