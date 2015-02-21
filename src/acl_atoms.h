#ifndef ATOMS_H
#define ATOMS_H

#include <QObject>

#include "acl_data.h"
#include "acl_global.h"

namespace ACL
{
    class AGEMARKERCORESHARED_EXPORT Atoms : public QObject
    {
            Q_OBJECT

        public:
            Atoms(Data::CalculationInput inputData,
                  Data::Structs::CalculationAtomData atomData);
            ~Atoms();
            Data::Structs::CalculationAtomData getAtomData();

        private:
            Data::CalculationInput data;
            Data::Structs::CalculationAtomData atoms;
    };
}

#endif // ATOMS_H
