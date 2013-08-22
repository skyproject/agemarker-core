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
            void collectThreadResult(Data::IpValuesMap result);

        private:
            void calculateAtoms();
            ACL::Data::CalculationResult getCalculationResult();
            std::vector<CalculationThread *> threads;
            Data::IpValuesMap calculatedIp;
            Data::CalculationInput data;
            std::vector<double> elementsNewContent;
            std::vector<uint64_t> atomAllEight;
            std::vector<uint64_t> atomAll;
            uint64_t atomAllEightSum = 0;
            uint64_t atomAllSum = 0;
            int runningThreads;
    };
}

#endif // ACL_AGEMARKERCORE_H
