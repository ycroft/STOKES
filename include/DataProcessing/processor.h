#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<Universal/math.h>
#include<Universal/innerdata.h>
#include<algorithm>
#include<ctime> // [!]
#include<map>

#define SQR_2 1.414213562

namespace proc
{
void CalcAF(InnerData& AF, std::vector<double>& AF_f, InnerData& data);
void RecognizeAF(InnerData& AF, std::vector<double>& feature, std::vector<int>& positions);
void SeparateAF(InnerData& AF, std::vector<int>& positions,
    InnerData& ch0, InnerData& ch1, InnerData& ch2, InnerData& ch3);
void RecoverRLS_MF(InnerData& URLS, InnerData& AF_ch0, InnerData& AF_ch1, InnerData& AF_ch2, InnerData& AF_ch3,
    InnerData& RLS_ch0, InnerData& RLS_ch1, InnerData& RLS_ch2, InnerData& RLS_ch3,
    InnerData& MF_0, InnerData& MF_1, InnerData& MF_2, InnerData& MF_3);
void RecoverMLS_SV(InnerData& AF_ch0, InnerData& AF_ch1, InnerData& AF_ch2, InnerData& AF_ch3,
    InnerData& MLS_ch0, InnerData& MLS_ch1, InnerData& MLS_ch2, InnerData& MLS_ch3,
    InnerData& MF_0, InnerData& MF_1, InnerData& MF_2, InnerData& MF_3,
    InnerData& SV_0, InnerData& SV_1, InnerData& SV_2, InnerData& SV_3);
void CalcDOP(InnerData& DOP, InnerData& SV_0, InnerData& SV_1, InnerData& SV_2, InnerData& SV_3);
}

#endif // PROCESSOR_H