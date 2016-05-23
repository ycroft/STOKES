#ifndef INNERDATA_H
#define INNERDATA_H

#include<vector>
#include<Universal/complex.h>
#include<iostream>

class InnerData
{
private:
    std::vector<Complex> x;
    std::vector<Complex> y;
public:
    InnerData();
    InnerData(std::vector<Complex> x, std::vector<Complex> y);
    void SetContent(std::vector<Complex>& lx, std::vector<Complex>& ly);
    void peek(int i); // [!]
    std::vector<Complex> getX();
    std::vector<Complex> getY();
    std::vector<Complex>& GetControlX();
    std::vector<Complex>& GetControlY();
    Complex GetXMax(){ return x[x.size()-1]; }
    Complex GetXMin(){ return x[0]; }
    bool empty(){ return x.size()==0; }
    int length();
};

#endif // INNERDATA_H
