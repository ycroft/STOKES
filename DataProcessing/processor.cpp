#include<DataProcessing/processor.h>

using namespace std;

void proc::CalcAF(InnerData& AF, vector<double>& AF_f, InnerData& data)
{
    // clock_t start = clock();
    int N = data.length();
    double scale = 1/(data.GetXMax().real() - data.GetXMin().real());
    vector<Complex> AF_y = data.getY();
    vector<Complex> AF_x;
    AF_f = vector<double>();
    math::fft(&AF_y[0], AF_y.size());
    for(int i = 0; i < N; ++ i)
    {
        AF_x.push_back(Complex(i*scale,0));
    }
    for(int i = 0; i < N; ++ i)
    {
        AF_f.push_back(AF_y[i].modulus());
    }
    // clock_t end = clock();
    AF.SetContent(AF_x, AF_y);
    // cout << "Time used: " << (double)(end-start)/CLOCKS_PER_SEC*1000 << " ms" << endl;
}

void __PushState(char* sl, char st);
void proc::RecognizeAF(InnerData& AF, vector<double>& feature,vector<int>& positions)
{
    if(AF.length() != feature.size())
    {
        return; // [!]
    }
    vector<Complex> x = AF.GetControlX();
    map<double, int> peaks;
    // vector<double> peaks;
    char state_list[3] = {'X','X','A'};
    char tmp_st;
    int mount = 1;
    double lAB, lBC, tmp_sum=0;
    double peakx=0, peaky=0;
    int peaki = 0;
    double min = feature[0];
    int count_points = feature.size();
    for(int i = 0; i < count_points; ++ i)
    {
        tmp_sum += feature[i];
        if(feature[i] < min)
        {
            min = feature[i];
        }
    }
    lBC = tmp_sum/count_points;
    lAB = 2 * lBC - min;
    
    for(int i = 0; i < feature.size()/2; ++ i)
    {
        if(feature[i] < lBC)
        {
            tmp_st = 'C';
        }
        else if(feature[i] < lAB)
        {
            tmp_st = 'B';
        }
        else{
            tmp_st = 'A';
        }
        if(state_list[2] != tmp_st)
        {
            __PushState(state_list, tmp_st);
        }
        if(feature[i] > peaky)
        {
            peaky = feature[i];
            peakx = x[i].real();
            peaki = i;
        }
        
        if(state_list[0] == 'A' && state_list[1] == 'B' && state_list[2] == 'C' && mount == 1)
        {
            peaks.insert(pair<double,int>(peaky,peaki));
            mount = 0;
        }
        else if(state_list[1] == 'A' && state_list[2] == 'C' && mount == 1)
        {
            peaks.insert(pair<double,int>(peaky,peaki));
            mount = 0;
        }
        else if(state_list[0] == 'C' && state_list[1] == 'B' && state_list[2] == 'A' && mount == 0)
        {
            peakx = x[i].real();
            peaky = feature[i];
            peaki = i;
            mount = 1;
        }
        else if(state_list[1] == 'C' && state_list[2] == 'A' && mount == 0)
        {
            peakx = x[i].real();
            peaky = feature[i];
            peaki = i;
            mount = 1;
        }
    }
    
    map<double, int>::reverse_iterator rit;
    if(peaks.size() < 4)
    {
        return; // [!]
    }
    positions = vector<int>();
    rit =  peaks.rbegin();
    for(int i = 0; i < 4; ++ i)
    {
        positions.push_back((*rit).second);
        ++ rit;
    }
    sort(positions.begin(),positions.end());
}

void __Hanning(vector<Complex>& f, int start_point, int end_point);
void proc::SeparateAF(InnerData& AF, vector<int>& positions,InnerData& ch0, InnerData& ch1, InnerData& ch2, InnerData& ch3)
{
    if(positions.size() != 4)
    {
        return; // [!]
    }
    if(abs(positions[0] - 0) > 0.000001)
    {
        return; // [!]
    }
    vector<Complex>& shared_x = AF.GetControlX();
    vector<Complex> y_ch0 = AF.getY();
    vector<Complex> y_ch1 = AF.getY();
    vector<Complex> y_ch2 = AF.getY();
    vector<Complex> y_ch3 = AF.getY();
    int l0,r0;
    int l1,r1;
    int l2,r2;
    int l3,r3;
    r0 = (positions[1] - positions[0]) / 2;
    l0 = -r0;
    
    if((positions[2] - positions[1]) < (positions[1] - positions[0]))
    {
        r1 = positions[1] + (positions[2] - positions[1])/2;
        l1 = positions[1] - (positions[2] - positions[1])/2;
    }
    else
    {
        r1 = positions[1] + (positions[1] - positions[0])/2;
        l1 = positions[1] - (positions[1] - positions[0])/2;
    }
    if((positions[3] - positions[2]) < (positions[2] - positions[1]))
    {
        r2 = positions[2] + (positions[3] - positions[2])/2;
        l2 = positions[2] - (positions[2] - positions[1])/2;
    }
    else
    {
        r2 = positions[2] + (positions[3] - positions[2])/2;
        l2 = positions[2] - (positions[2] - positions[1])/2;
    }

    r3 = positions[3] + (positions[3] -positions[2])/2;    
    l3 = positions[3] - (positions[3] -positions[2])/2;
    
    __Hanning(y_ch0,l0,r0);
    __Hanning(y_ch1,l1,r1);
    __Hanning(y_ch2,l2,r2);
    __Hanning(y_ch3,l3,r3);
    
    ch0.SetContent(shared_x, y_ch0);
    ch1.SetContent(shared_x, y_ch1);
    ch2.SetContent(shared_x, y_ch2);
    ch3.SetContent(shared_x, y_ch3);
}

void proc::RecoverRLS_MF(InnerData& URLS, InnerData& AF_ch0, InnerData& AF_ch1, InnerData& AF_ch2, InnerData& AF_ch3,
    InnerData& RLS_ch0, InnerData& RLS_ch1, InnerData& RLS_ch2, InnerData& RLS_ch3,
    InnerData& MF_0, InnerData& MF_1, InnerData& MF_2, InnerData& MF_3)
{
    int size = AF_ch0.length();
    vector<Complex>& URLS_x = URLS.GetControlX();
    vector<Complex>& URLS_y = URLS.GetControlY();
    
    vector<Complex> ch0_y = AF_ch0.getY();
    vector<Complex> ch1_y = AF_ch1.getY();
    vector<Complex> ch2_y = AF_ch2.getY();
    vector<Complex> ch3_y = AF_ch3.getY();
    
    math::ifft(&ch0_y[0], size);
    math::ifft(&ch1_y[0], size);
    math::ifft(&ch2_y[0], size);
    math::ifft(&ch3_y[0], size);
    
    RLS_ch0.SetContent(URLS_x, ch0_y);
    RLS_ch1.SetContent(URLS_x, ch1_y);
    RLS_ch2.SetContent(URLS_x, ch2_y);
    RLS_ch3.SetContent(URLS_x, ch3_y);
    
    vector<Complex> MF_0_y,MF_1_y,MF_2_y,MF_3_y;
    for(int i = 0; i < size; ++ i)
    {
        MF_0_y.push_back(ch0_y[i] / URLS_y[i]);
        MF_1_y.push_back(ch1_y[i]*Complex(SQR_2,0) / URLS_y[i]);
        MF_2_y.push_back(ch2_y[i]*Complex(SQR_2,0) / URLS_y[i]);
        MF_3_y.push_back((ch3_y[i]*Complex(SQR_2,0) * Complex(-1,0)) / URLS_y[i]);
    }
    
    MF_0.SetContent(URLS_x, MF_0_y);
    MF_1.SetContent(URLS_x, MF_1_y);
    MF_2.SetContent(URLS_x, MF_2_y);
    MF_3.SetContent(URLS_x, MF_3_y);
}

void proc::RecoverMLS_SV(InnerData& AF_ch0, InnerData& AF_ch1, InnerData& AF_ch2, InnerData& AF_ch3,
    InnerData& MLS_ch0, InnerData& MLS_ch1, InnerData& MLS_ch2, InnerData& MLS_ch3,
    InnerData& MF_0, InnerData& MF_1, InnerData& MF_2, InnerData& MF_3,
    InnerData& SV_0, InnerData& SV_1, InnerData& SV_2, InnerData& SV_3)
{
    int size = AF_ch0.length();
    vector<Complex>& shared_x = MF_0.GetControlX();
    
    vector<Complex> ch0_y = AF_ch0.getY();
    vector<Complex> ch1_y = AF_ch1.getY();
    vector<Complex> ch2_y = AF_ch2.getY();
    vector<Complex> ch3_y = AF_ch3.getY();
    
    vector<Complex>& MF_0_y = MF_0.GetControlY();
    vector<Complex>& MF_1_y = MF_1.GetControlY();
    vector<Complex>& MF_2_y = MF_2.GetControlY();
    vector<Complex>& MF_3_y = MF_3.GetControlY();
    
    math::ifft(&ch0_y[0], size);
    math::ifft(&ch1_y[0], size);
    math::ifft(&ch2_y[0], size);
    math::ifft(&ch3_y[0], size);
    
    MLS_ch0.SetContent(shared_x, ch0_y);
    MLS_ch1.SetContent(shared_x, ch1_y);
    MLS_ch2.SetContent(shared_x, ch2_y);
    MLS_ch3.SetContent(shared_x, ch3_y);
    
    vector<Complex> sv_0_y, sv_1_y, sv_2_y, sv_3_y, sv_23_y;
    for(int i = 0; i < size; ++ i)
    {
        sv_0_y.push_back(ch0_y[i] / MF_0_y[i]);
        sv_23_y.push_back(ch3_y[i] / MF_3_y[i]);
        sv_1_y.push_back(ch2_y[i] / MF_2_y[i]);
        sv_2_y.push_back(Complex(sv_23_y[i].real(),0));
        sv_3_y.push_back(Complex(sv_23_y[i].imag(),0));
    }
    
    SV_0.SetContent(shared_x, sv_0_y);
    SV_1.SetContent(shared_x, sv_1_y);
    SV_2.SetContent(shared_x, sv_2_y);
    SV_3.SetContent(shared_x, sv_3_y);
}

void proc::CalcDOP(InnerData& DOP, InnerData& SV_0, InnerData& SV_1, InnerData& SV_2, InnerData& SV_3)
{
    int size = SV_0.length();
    if(SV_1.length() != size||SV_2.length() != size||SV_3.length() != size)
    {
        return; // [!]
    }
    
    vector<Complex> DOP_y;
    vector<Complex>& shared_x = SV_0.GetControlX();
    
    vector<Complex>& SV_0_y = SV_0.GetControlY(); 
    vector<Complex>& SV_1_y = SV_1.GetControlY(); 
    vector<Complex>& SV_2_y = SV_2.GetControlY(); 
    vector<Complex>& SV_3_y = SV_3.GetControlY(); 
    
    for(int i = 0; i < size; ++ i)
    {
        DOP_y.push_back(Complex(sqrt(SV_1_y[i].squareMod()+SV_2_y[i].squareMod()+SV_3_y[i].squareMod()),0) / SV_0_y[i]);
    }
    DOP.SetContent(shared_x, DOP_y);
}

void __Hanning(vector<Complex>& f, int start_point, int end_point)
{
    int num = end_point - start_point;
    if(start_point >= 0)
    {
        for(int i = 0; i < start_point; ++ i)
        {
            f[i].real(0);
            f[i].imag(0);
        }
        for(int i = end_point; i < f.size(); ++ i)
        {
            f[i].real(0);
            f[i].imag(0);
        }
        int k = 0;
        for(int i = start_point; i < end_point; ++ i)
        {
            f[i] = f[i] * Complex(0.54 - 0.46*cos((2*M_PI*k)/(num-1)),0);
            ++ k;
        } 
    }
    else
    {
        for(int i = end_point; i < f.size() + start_point; ++ i)
        {
            f[i].real(0);
            f[i].imag(0);
        }
        int index = f.size() + start_point;
        int k = 0;
        for(int i = 0; i < num; ++ i)
        {
            if(index == f.size())
            {
                index = 0;
            }
            f[index] = f[index] * Complex(0.54 - 0.46*cos((2*M_PI*k)/(num-1)),0);
            ++ k;
            ++ index;
        }
    }
}

void __PushState(char* sl, char st)
{
    sl[0] = sl[1];
    sl[1] = sl[2];
    sl[2] = st;
}
