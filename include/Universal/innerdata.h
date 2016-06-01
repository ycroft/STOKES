#ifndef INNERDATA_H
#define INNERDATA_H

#include<vector>
#include<Universal/complex.h>
#include<iostream>

class InnerData
{
private:
	/** 坐标轴x
	  */
    std::vector<Complex> x;
    /** 坐标轴y
  	  */
	std::vector<Complex> y;
public:
    /** 默认构造函数
	  */
	InnerData();
	/** 根据输入向量x，y构造坐标系
	  */
    InnerData(std::vector<Complex> x, std::vector<Complex> y);
	/** 根据输入向量x, y修改坐标系
	  */
    void SetContent(std::vector<Complex>& lx, std::vector<Complex>& ly);
    void peek(int i); // [!]
	/** 返回坐标轴x
	  */
    std::vector<Complex> getX();
	/** 返回坐标轴y
	  */
    std::vector<Complex> getY();
	/** 原址返回坐标轴x
	  */
    std::vector<Complex>& GetControlX();
	/** 原址返回坐标轴y
	  */
    std::vector<Complex>& GetControlY();
	/** 返回最大x坐标
	  */
    Complex GetXMax(){ return x[x.size()-1]; }
	/** 返回最小x坐标
	  */
    Complex GetXMin(){ return x[0]; }
	/** 判空，空返回真
	  */
    bool empty(){ return x.size()==0; }
	/** 返回坐标数量
	  */
	int length(){  	return x.size();}
};

#endif // INNERDATA_H
