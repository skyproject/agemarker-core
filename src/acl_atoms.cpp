/*
 * Copyright (c) 2013 Mikhail Labushev.
 *
 * This file is a part of agemarker-core
 * library distributed under the MIT License.
 * For full terms see LICENSE file.
 */

#include "acl_atoms.h"

using namespace ACL;

Atoms::Atoms(Data::CalculationInput inputData,
             Data::Structs::CalculationAtomData atomData)
{
    this->data = inputData;
    this->atoms = atomData;
}

Atoms::~Atoms()
{

}

Data::Structs::CalculationAtomData Atoms::getAtomData()
{
    Float oxidesWeightSum[OXIDES_COUNT];
    oxidesWeightSum[0] = ((this->data.elementsWeight[13] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[1] = ((this->data.elementsWeight[21] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[2] = ((this->data.elementsWeight[12] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[3] = ((this->data.elementsWeight[25] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[4] = ((this->data.elementsWeight[25] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[5] = ((this->data.elementsWeight[24] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[6] = ((this->data.elementsWeight[11] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[7] = ((this->data.elementsWeight[18] * 2) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[8] = ((this->data.elementsWeight[19] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[9] = ((this->data.elementsWeight[10] * 2) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[10] = ((this->data.elementsWeight[0] * 2) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[11] = ((this->data.elementsWeight[14] * 4) + (this->data.elementsWeight[7] * 6));
    oxidesWeightSum[12] = ((this->data.elementsWeight[14] * 2) + (this->data.elementsWeight[7] * 5));
    oxidesWeightSum[13] = ((this->data.elementsWeight[5] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[14] = ((this->data.elementsWeight[4] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[15] = ((this->data.elementsWeight[15] * 1) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[16] = ((this->data.elementsWeight[22] * 2) + (this->data.elementsWeight[7] * 5));
    oxidesWeightSum[17] = ((this->data.elementsWeight[23] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[18] = ((this->data.elementsWeight[27] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[19] = ((this->data.elementsWeight[32] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[20] = ((this->data.elementsWeight[38] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[21] = ((this->data.elementsWeight[55] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[22] = ((this->data.elementsWeight[56] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[23] = ((this->data.elementsWeight[57] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[24] = ((this->data.elementsWeight[58] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[25] = ((this->data.elementsWeight[59] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[26] = ((this->data.elementsWeight[61] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[27] = ((this->data.elementsWeight[62] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[28] = ((this->data.elementsWeight[63] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[29] = ((this->data.elementsWeight[64] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[30] = ((this->data.elementsWeight[65] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[31] = ((this->data.elementsWeight[66] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[32] = ((this->data.elementsWeight[67] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[33] = ((this->data.elementsWeight[68] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[34] = ((this->data.elementsWeight[69] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[35] = ((this->data.elementsWeight[72] * 2) + (this->data.elementsWeight[7] * 5));
    oxidesWeightSum[36] = ((this->data.elementsWeight[73] * 1) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[37] = ((this->data.elementsWeight[39] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[38] = ((this->data.elementsWeight[2] * 2) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[39] = ((this->data.elementsWeight[37] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[40] = ((this->data.elementsWeight[81] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[41] = ((this->data.elementsWeight[29] * 1) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[42] = ((this->data.elementsWeight[89] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[43] = ((this->data.elementsWeight[91] * 3) + (this->data.elementsWeight[7] * 8));
    oxidesWeightSum[44] = ((this->data.elementsWeight[24] * 3) + (this->data.elementsWeight[7] * 4));
    oxidesWeightSum[45] = ((this->data.elementsWeight[24] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[46] = ((this->data.elementsWeight[50] * 2) + (this->data.elementsWeight[7] * 3));
    oxidesWeightSum[47] = ((this->data.elementsWeight[49] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[48] = ((this->data.elementsWeight[71] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[49] = ((this->data.elementsWeight[28] * 2) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[50] = ((this->data.elementsWeight[43] * 1) + (this->data.elementsWeight[7] * 2));
    oxidesWeightSum[51] = ((this->data.elementsWeight[54] * 2) + (this->data.elementsWeight[7] * 1));
    oxidesWeightSum[52] = ((this->data.elementsWeight[36] * 2) + (this->data.elementsWeight[7] * 1));
    Float oxidesPureElement[OXIDES_COUNT];
    oxidesPureElement[0] = ((this->data.elementsWeight[13] * 1) * (this->data.oxidesContent[0]) / (oxidesWeightSum[0]));
    oxidesPureElement[1] = ((this->data.elementsWeight[21] * 1) * (this->data.oxidesContent[1]) / (oxidesWeightSum[1]));
    oxidesPureElement[2] = ((this->data.elementsWeight[12] * 2) * (this->data.oxidesContent[2]) / (oxidesWeightSum[2]));
    oxidesPureElement[3] = ((this->data.elementsWeight[25] * 2) * (this->data.oxidesContent[3]) / (oxidesWeightSum[3]));
    oxidesPureElement[4] = ((this->data.elementsWeight[25] * 1) * (this->data.oxidesContent[4]) / (oxidesWeightSum[4]));
    oxidesPureElement[5] = ((this->data.elementsWeight[24] * 1) * (this->data.oxidesContent[5]) / (oxidesWeightSum[5]));
    oxidesPureElement[6] = ((this->data.elementsWeight[11] * 1) * (this->data.oxidesContent[6]) / (oxidesWeightSum[6]));
    oxidesPureElement[7] = ((this->data.elementsWeight[18] * 2) * (this->data.oxidesContent[7]) / (oxidesWeightSum[7]));
    oxidesPureElement[8] = ((this->data.elementsWeight[19] * 1) * (this->data.oxidesContent[8]) / (oxidesWeightSum[8]));
    oxidesPureElement[9] = ((this->data.elementsWeight[10] * 2) * (this->data.oxidesContent[9]) / (oxidesWeightSum[9]));
    oxidesPureElement[10] = ((this->data.elementsWeight[0] * 2) * (this->data.oxidesContent[10]) / (oxidesWeightSum[10]));
    oxidesPureElement[11] = ((this->data.elementsWeight[14] * 4) * (this->data.oxidesContent[11]) / (oxidesWeightSum[11]));
    oxidesPureElement[12] = ((this->data.elementsWeight[14] * 2) * (this->data.oxidesContent[12]) / (oxidesWeightSum[12]));
    oxidesPureElement[13] = ((this->data.elementsWeight[5] * 1) * (this->data.oxidesContent[13]) / (oxidesWeightSum[13]));
    oxidesPureElement[14] = ((this->data.elementsWeight[4] * 2) * (this->data.oxidesContent[14]) / (oxidesWeightSum[14]));
    oxidesPureElement[15] = ((this->data.elementsWeight[15] * 1) * (this->data.oxidesContent[15]) / (oxidesWeightSum[15]));
    oxidesPureElement[16] = ((this->data.elementsWeight[22] * 2) * (this->data.oxidesContent[16]) / (oxidesWeightSum[16]));
    oxidesPureElement[17] = ((this->data.elementsWeight[23] * 2) * (this->data.oxidesContent[17]) / (oxidesWeightSum[17]));
    oxidesPureElement[18] = ((this->data.elementsWeight[27] * 1) * (this->data.oxidesContent[18]) / (oxidesWeightSum[18]));
    oxidesPureElement[19] = ((this->data.elementsWeight[32] * 2) * (this->data.oxidesContent[19]) / (oxidesWeightSum[19]));
    oxidesPureElement[20] = ((this->data.elementsWeight[38] * 2) * (this->data.oxidesContent[20]) / (oxidesWeightSum[20]));
    oxidesPureElement[21] = ((this->data.elementsWeight[55] * 1) * (this->data.oxidesContent[21]) / (oxidesWeightSum[21]));
    oxidesPureElement[22] = ((this->data.elementsWeight[56] * 2) * (this->data.oxidesContent[22]) / (oxidesWeightSum[22]));
    oxidesPureElement[23] = ((this->data.elementsWeight[57] * 1) * (this->data.oxidesContent[23]) / (oxidesWeightSum[23]));
    oxidesPureElement[24] = ((this->data.elementsWeight[58] * 2) * (this->data.oxidesContent[24]) / (oxidesWeightSum[24]));
    oxidesPureElement[25] = ((this->data.elementsWeight[59] * 2) * (this->data.oxidesContent[25]) / (oxidesWeightSum[25]));
    oxidesPureElement[26] = ((this->data.elementsWeight[61] * 2) * (this->data.oxidesContent[26]) / (oxidesWeightSum[26]));
    oxidesPureElement[27] = ((this->data.elementsWeight[62] * 2) * (this->data.oxidesContent[27]) / (oxidesWeightSum[27]));
    oxidesPureElement[28] = ((this->data.elementsWeight[63] * 2) * (this->data.oxidesContent[28]) / (oxidesWeightSum[28]));
    oxidesPureElement[29] = ((this->data.elementsWeight[64] * 2) * (this->data.oxidesContent[29]) / (oxidesWeightSum[29]));
    oxidesPureElement[30] = ((this->data.elementsWeight[65] * 2) * (this->data.oxidesContent[30]) / (oxidesWeightSum[30]));
    oxidesPureElement[31] = ((this->data.elementsWeight[66] * 2) * (this->data.oxidesContent[31]) / (oxidesWeightSum[31]));
    oxidesPureElement[32] = ((this->data.elementsWeight[67] * 2) * (this->data.oxidesContent[32]) / (oxidesWeightSum[32]));
    oxidesPureElement[33] = ((this->data.elementsWeight[68] * 2) * (this->data.oxidesContent[33]) / (oxidesWeightSum[33]));
    oxidesPureElement[34] = ((this->data.elementsWeight[69] * 2) * (this->data.oxidesContent[34]) / (oxidesWeightSum[34]));
    oxidesPureElement[35] = ((this->data.elementsWeight[72] * 2) * (this->data.oxidesContent[35]) / (oxidesWeightSum[35]));
    oxidesPureElement[36] = ((this->data.elementsWeight[73] * 1) * (this->data.oxidesContent[36]) / (oxidesWeightSum[36]));
    oxidesPureElement[37] = ((this->data.elementsWeight[39] * 1) * (this->data.oxidesContent[37]) / (oxidesWeightSum[37]));
    oxidesPureElement[38] = ((this->data.elementsWeight[2] * 2) * (this->data.oxidesContent[38]) / (oxidesWeightSum[38]));
    oxidesPureElement[39] = ((this->data.elementsWeight[37] * 1) * (this->data.oxidesContent[39]) / (oxidesWeightSum[39]));
    oxidesPureElement[40] = ((this->data.elementsWeight[81] * 1) * (this->data.oxidesContent[40]) / (oxidesWeightSum[40]));
    oxidesPureElement[41] = ((this->data.elementsWeight[29] * 1) * (this->data.oxidesContent[41]) / (oxidesWeightSum[41]));
    oxidesPureElement[42] = ((this->data.elementsWeight[89] * 1) * (this->data.oxidesContent[42]) / (oxidesWeightSum[42]));
    oxidesPureElement[43] = ((this->data.elementsWeight[91] * 3) * (this->data.oxidesContent[43]) / (oxidesWeightSum[43]));
    oxidesPureElement[44] = ((this->data.elementsWeight[24] * 3) * (this->data.oxidesContent[44]) / (oxidesWeightSum[44]));
    oxidesPureElement[45] = ((this->data.elementsWeight[24] * 2) * (this->data.oxidesContent[45]) / (oxidesWeightSum[45]));
    oxidesPureElement[46] = ((this->data.elementsWeight[50] * 2) * (this->data.oxidesContent[46]) / (oxidesWeightSum[46]));
    oxidesPureElement[47] = ((this->data.elementsWeight[49] * 1) * (this->data.oxidesContent[47]) / (oxidesWeightSum[47]));
    oxidesPureElement[48] = ((this->data.elementsWeight[71] * 1) * (this->data.oxidesContent[48]) / (oxidesWeightSum[48]));
    oxidesPureElement[49] = ((this->data.elementsWeight[28] * 2) * (this->data.oxidesContent[49]) / (oxidesWeightSum[49]));
    oxidesPureElement[50] = ((this->data.elementsWeight[43] * 1) * (this->data.oxidesContent[50]) / (oxidesWeightSum[50]));
    oxidesPureElement[51] = ((this->data.elementsWeight[54] * 2) * (this->data.oxidesContent[51]) / (oxidesWeightSum[51]));
    oxidesPureElement[52] = ((this->data.elementsWeight[36] * 2) * (this->data.oxidesContent[52]) / (oxidesWeightSum[52]));
    this->atoms.elementsNewContent = this->data.elementsContent;
    this->atoms.elementsNewContent[13] += oxidesPureElement[0];
    this->atoms.elementsNewContent[21] += oxidesPureElement[1];
    this->atoms.elementsNewContent[12] += oxidesPureElement[2];
    this->atoms.elementsNewContent[25] += oxidesPureElement[3];
    this->atoms.elementsNewContent[25] += oxidesPureElement[4];
    this->atoms.elementsNewContent[24] += oxidesPureElement[5];
    this->atoms.elementsNewContent[11] += oxidesPureElement[6];
    this->atoms.elementsNewContent[18] += oxidesPureElement[7];
    this->atoms.elementsNewContent[19] += oxidesPureElement[8];
    this->atoms.elementsNewContent[10] += oxidesPureElement[9];
    this->atoms.elementsNewContent[0] += oxidesPureElement[10];
    this->atoms.elementsNewContent[14] += oxidesPureElement[11];
    this->atoms.elementsNewContent[14] += oxidesPureElement[12];
    this->atoms.elementsNewContent[5] += oxidesPureElement[13];
    this->atoms.elementsNewContent[4] += oxidesPureElement[14];
    this->atoms.elementsNewContent[15] += oxidesPureElement[15];
    this->atoms.elementsNewContent[22] += oxidesPureElement[16];
    this->atoms.elementsNewContent[23] += oxidesPureElement[17];
    this->atoms.elementsNewContent[27] += oxidesPureElement[18];
    this->atoms.elementsNewContent[32] += oxidesPureElement[19];
    this->atoms.elementsNewContent[38] += oxidesPureElement[20];
    this->atoms.elementsNewContent[55] += oxidesPureElement[21];
    this->atoms.elementsNewContent[56] += oxidesPureElement[22];
    this->atoms.elementsNewContent[58] += oxidesPureElement[24];
    this->atoms.elementsNewContent[59] += oxidesPureElement[25];
    this->atoms.elementsNewContent[61] += oxidesPureElement[26];
    this->atoms.elementsNewContent[62] += oxidesPureElement[27];
    this->atoms.elementsNewContent[63] += oxidesPureElement[28];
    this->atoms.elementsNewContent[64] += oxidesPureElement[29];
    this->atoms.elementsNewContent[65] += oxidesPureElement[30];
    this->atoms.elementsNewContent[66] += oxidesPureElement[31];
    this->atoms.elementsNewContent[67] += oxidesPureElement[32];
    this->atoms.elementsNewContent[68] += oxidesPureElement[33];
    this->atoms.elementsNewContent[69] += oxidesPureElement[34];
    this->atoms.elementsNewContent[72] += oxidesPureElement[35];
    this->atoms.elementsNewContent[73] += oxidesPureElement[36];
    this->atoms.elementsNewContent[39] += oxidesPureElement[37];
    this->atoms.elementsNewContent[2] += oxidesPureElement[38];
    this->atoms.elementsNewContent[37] += oxidesPureElement[39];
    this->atoms.elementsNewContent[81] += oxidesPureElement[40];
    this->atoms.elementsNewContent[29] += oxidesPureElement[41];
    this->atoms.elementsNewContent[89] += oxidesPureElement[42];
    this->atoms.elementsNewContent[91] += oxidesPureElement[43];
    this->atoms.elementsNewContent[24] += oxidesPureElement[44];
    this->atoms.elementsNewContent[24] += oxidesPureElement[45];
    this->atoms.elementsNewContent[50] += oxidesPureElement[46];
    this->atoms.elementsNewContent[49] += oxidesPureElement[47];
    this->atoms.elementsNewContent[71] += oxidesPureElement[48];
    this->atoms.elementsNewContent[28] += oxidesPureElement[49];
    this->atoms.elementsNewContent[43] += oxidesPureElement[50];
    this->atoms.elementsNewContent[54] += oxidesPureElement[51];
    this->atoms.elementsNewContent[36] += oxidesPureElement[52];
    for (int x = 0; x < OXIDES_COUNT; ++x)
    {
        Float oxideOxygen = ((this->data.oxidesContent[x]) - (oxidesPureElement[x]));
        this->atoms.elementsNewContent[7] += oxideOxygen;
    }
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        Float nor;
        if (this->data.elementsContentUnits == Data::ElementsContentUnits::MassPercent)
        {
            nor = (this->atoms.elementsNewContent[x] / this->data.elementsWeight[x]);
        }
        else
        {
            nor = this->atoms.elementsNewContent[x];
        }

        Float atom = FMath::round(nor * this->data.multiplier);
        this->atoms.all.push_back(FMath::boost_numeric_cast<uint64_t>(atom));

        this->atoms.allSum += atoms.all[x];
        this->atoms.allEight.push_back(atoms.all[x] * 8);
        this->atoms.allEightSum += this->atoms.allEight[x];
    }

    return this->atoms;
}
