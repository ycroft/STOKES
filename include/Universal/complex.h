#ifndef COMPLEX_H
#define COMPLEX_H

#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<string>

class Complex
{
private:
	/** 复数实部 
	  */
    double m_real;
	/** 复数虚部
	  */
    double m_imag;
public:
    /** 构造默认复数0 
	  */
	Complex();
    /** 从字符串“(a+bj)"或"a"中获取a,b, 以a为实部，b为虚部
      * ,构造复数
      */
	Complex(const char* str);
	/** 输入实部real，虚部imag构造复数
      */
    Complex(double real, double imag);
	/** 复数生成字符串，产生格式："(a+/-bj)",纯实数不带括号
	  */
    std::string ToString();
	/** 返回实部
      */
    double real(){ return m_real;}
	/** 返回虚部
      */
    double imag(){ return m_imag;}
	/** 修改实部
	  */
    void real(double real){ m_real = real;}
	/** 修改虚部
	  */ 
    void imag(double imag){ m_imag = imag;}
	/** 复数求模
	  */
    double modulus();
	/** 复数求模平方
      */
    double squareMod();
	/** 复数加法
	  */
    Complex operator+(Complex x);
	/** 复数减法
	  */
    Complex operator-(Complex x);
	/** 复数乘法
      */
    Complex operator*(Complex x);
	/** 复数除法
	  */
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
