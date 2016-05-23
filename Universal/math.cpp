#include<Universal/math.h>

using namespace std;

void math::chase(double* x, const double* a, const double* b, const double* c,
        const double* f, const int size)
{
    double* p = (double*) malloc(size * sizeof(double));
    double* q = (double*) malloc(size * sizeof(double));
    double* y = (double*) malloc(size * sizeof(double));
    p[0] = b[0];
    q[0] = c[0] / p[0];
    y[0] = f[0] / p[0];
    p[1] = b[1] - a[1] * q[0];
    for (int i = 1; i < size - 1; i++)
    {
        q[i] = c[i] / p[i];
        p[i + 1] = b[i + 1] - a[i + 1] * q[i];
        y[i] = (f[i] - a[i] * y[i - 1]) / p[i];
    }
    y[size - 1] = (f[size - 1] - a[size - 1] * y[size - 2]) / p[size - 1];
    x[size - 1] = y[size - 1];
    for (int i = size - 2; i > -1; i--)
    {
        x[i] = y[i] - q[i] * x[i + 1];
    }

    free(p);
    free(q);
    free(y);
}

void math::spline(double* sy, const double* x, const double* y, const double* sx,
        int length, int lsy)
{
    double* numda = (double*) malloc(length * sizeof(double));
    double* miu = (double*) malloc(length * sizeof(double));
    double* g = (double*) malloc(length * sizeof(double));
    double* c = (double*) malloc((length - 2) * sizeof(double));
    double* m = (double*) malloc((length - 2) * sizeof(double));
    double m_0 = 0;
    double m_n = (y[length - 1] - y[length - 2])
            / (x[length - 1] - x[length - 2]);
    double h;
    double h_;
    for (int i = 0; i < length - 2; i++)
    {
        c[i] = 2.0;
    }
    for (int i = 1; i < length - 1; i++)
    {
        h = x[i + 1] - x[i];
        h_ = x[i] - x[i - 1];
        numda[i] = h / h_;
        miu[i] = 1 - numda[i];
        g[i] = (numda[i] * (y[i] - y[i - 1]) / h_
                + miu[i] * (y[i + 1] - y[i]) / h) * 3;
    }
    g[1] = g[1] - numda[1] * m_0;
    g[length - 2] = g[length - 2] - miu[length - 2] * m_n;
    double* g_ = g + 1;
    double* numda_ = numda + 2;
    double* miu_ = miu + 1;
    chase(m, numda_, c, miu_, g_, length - 2);
    int j = 0;
    double* mx = (double*) malloc((length) * sizeof(double));
    for (int i = 1; i < length - 1; i++)
    {
        mx[i] = m[i - 1];
    }
    mx[0] = m_0;
    mx[length - 1] = m_n;
    for (int i = 0; i < lsy; i++)
    {
        if (j == length)
        {
            break;
        }
        if (sx[i] >= x[j + 1])
        {
            ++j;
        }
        h = x[j + 1] - x[j];
        sy[i] = y[j] * PHI_0((sx[i] - x[j]) / h)
                + y[j + 1] * PHI_0((x[j + 1] - sx[i]) / h)
                + mx[j] * h * PHI_1((sx[i] - x[j]) / h)
                - mx[j + 1] * h * PHI_1((x[j + 1] - sx[i]) / h);
    }

    free(numda);
    free(miu);
    free(g);
    free(c);
    free(m);
    free(mx);
}

void math::fft(Complex* f, int N)  
{  
    Complex t,wn;//中间变量  
    int i,j,k,m,n,l,r,M;  
    int la,lb,lc;  
    /*----计算分解的级数M=log2(N)----*/  
    for(i=N,M=1;(i=i/2)!=1;M++);   
    /*----按照倒位序重新排列原信号----*/  
    for(i=1,j=N/2;i<=N-2;i++)  
    {  
        if(i<j)  
        {  
            t=f[j];  
            f[j]=f[i];  
            f[i]=t;  
        }  
        k=N/2;  
        while(k<=j)  
        {  
            j=j-k;  
            k=k/2;  
        }  
        j=j+k;  
    }  
/*----FFT算法----*/  
    for(m=1;m<=M;m++)  
    {  
        la=pow(2,m); //la=2^m代表第m级每个分组所含节点数       
        lb=la/2;    //lb代表第m级每个分组所含碟形单元数  
                     //同时它也表示每个碟形单元上下节点之间的距离  
        /*----碟形运算----*/  
        for(l=1;l<=lb;l++)  
        {  
            r=(l-1)*pow(2,M-m);     
            for(n=l-1;n<N-1;n=n+la) //遍历每个分组，分组总数为N/la  
            {  
                lc=n+lb;  //n,lc分别代表一个碟形单元的上、下节点编号       
                WNP(N,r,wn);//wn=Wnr  
                // c_mul(f[lc],wn,&t);//t = f[lc] * wn复数运算
                t = f[lc] * wn;
                // c_sub(f[n],t,&(f[lc]));//f[lc] = f[n] - f[lc] * Wnr
                f[lc] = f[n] - t;  
                // c_plus(f[n],t,&(f[n]));//f[n] = f[n] + f[lc] * Wnr
                f[n] = f[n] + t;  
            }  
        }  
    }  
}

void conjugate_complex(int n,Complex in[], Complex out[])  
{  
    int i = 0;  
    for(i=0;i<n;i++)  
    {  
        out[i].imag(-in[i].imag());  
        out[i].real(in[i].real());  
    }   
}

void math::ifft(Complex* f, int N)  
{  
    int i=0;
    conjugate_complex(N,f,f);  
    math::fft(f,N);  
    conjugate_complex(N,f,f);  
    for(i=0;i<N;i++)  
    {  
        f[i].imag(f[i].imag()/N);  
        f[i].real(f[i].real()/N);
    }
} 

void math::reciprocal(vector<double>& x, vector<double>& y)
{
    int i = 0;
    int j = x.size() - 1;
    double t;
    while (i < j)
    {
        t = x.at(i);
        x.at(i) = x.at(j);
        x.at(j) = t;
        t = y.at(i);
        y.at(i) = y.at(j);
        y.at(j) = t;

        x.at(i) = 1 *GLOBAL_SCALE/ x.at(i);
        x.at(j) = 1 *GLOBAL_SCALE/ x.at(j);
        ++i;
        --j;
    }
}