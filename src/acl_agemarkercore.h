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

#include "acl_calculationthread.h"
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
            std::vector<CalculationThread *> threads;
            Data::Types::IpValuesMap calculatedIp;
            Data::CalculationInput data;
            Data::Structs::CalculationAtomData atoms;
            int runningThreads;
    };
}

#endif // ACL_AGEMARKERCORE_H
