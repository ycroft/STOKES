#include<Universal/complex.h>

Complex::Complex()
{
    m_real = 0;
    m_imag = 0;
}

Complex::Complex(const char* str)
{
    if (*str == '(')
    {
        char real[128];
        char imag[128];
        char* p = real;
        int i = 1;
        while (str[i] != 'j')
        {
            if (str[i] == '+' || str[i] == '-')
            {
                *p = '\0';
                p = imag;
            }
            *p = str[i];
            ++p;
            ++i;
        }
        this->m_real = atof(real);
        this->m_imag = atof(imag);
    }
    else
    {
        m_real = atof(str);
        m_imag = 0;
    }
}

Complex::Complex(double real, double imag)
{
    m_real = real;
    m_imag = imag;
}

double Complex::modulus()
{
    return sqrt(m_real * m_real + m_imag * m_imag);
}

double Complex::squareMod()
{
    return m_real * m_real + m_imag * m_imag;
}

std::string Complex::ToString()
{
    char buf[128] = {'\0'};
    if(m_imag == 0)
    {
        sprintf(buf,"%f",m_real);
    }
    else if(m_imag > 0)
    {
        sprintf(buf,"(%f+%fj)",m_real,m_imag);
    }
    else
    {
        sprintf(buf,"(%f%fj)",m_real,m_imag);
    }
    return std::string(buf);
}