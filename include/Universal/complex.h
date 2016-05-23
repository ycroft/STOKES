#ifndef COMPLEX_H
#define COMPLEX_H

#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<string>

class Complex
{
private:
    double m_real;
    double m_imag;
public:
    Complex();
    Complex(const char* str);
    Complex(double real, double imag);
    std::string ToString();
    double real(){ return m_real;}
    double imag(){ return m_imag;}
    void real(double real){ m_real = real;}
    void imag(double imag){ m_imag = imag;}
    double modulus();
    double squareMod();
    Complex operator+(Complex x);
    Complex operator-(Complex x);
    Complex operator*(Complex x);
    Complex operator/(Complex x);
};

inline Complex Complex::operator+(Complex x)
{
    return Complex(m_real + x.real(), m_imag + x.imag());
}

inline Complex Complex::operator-(Complex x)
{
    return Complex(m_real - x.real(), m_imag - x.imag());
}

inline Complex Complex::operator*(Complex x)
{
    return Complex(m_real * x.real() - m_imag * x.imag(), m_real * x.imag() + m_imag * x.real());
}

inline Complex Complex::operator/(Complex x)
{
    double base = x.real() * x.real() + x.imag() * x.imag();
    return Complex((m_real * x.real() + m_imag * x.imag()) / base,
            (m_imag * x.real() - m_real * x.imag()) / base);
}

#endif // COMPLEX_H
