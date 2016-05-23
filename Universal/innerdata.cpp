#include<Universal/innerdata.h>

using namespace std;

InnerData::InnerData()
{
}

InnerData::InnerData(vector<Complex> x, vector<Complex> y)
{
    this->x = x;
    this->y = y;
}

void InnerData::SetContent(vector<Complex>& lx, vector<Complex>& ly)
{
    if(lx.size() != ly.size())
    {
        return; // [!] error;
    }
    if(x.size() == lx.size())
    {
        for(int i = 0; i < lx.size(); i ++)
        {
            x[i] = lx[i];
            y[i] = ly[i];
        }
        return;
    }
    if(x.size() == 0)
    {
        for(int i = 0; i < lx.size(); i ++)
        {
            x.push_back(lx[i]);
            y.push_back(ly[i]);
        }
        return;
    }
    // [!] return error;
    return;
}

void InnerData::peek(int i) // [!]
{
    cout << x[i].real() << endl;
}

vector<Complex> InnerData::getX()
{
    return x;
}

vector<Complex> InnerData::getY()
{
    return y;
}

vector<Complex>& InnerData::GetControlX()
{
    return x;
}

vector<Complex>& InnerData::GetControlY()
{
    return y;
}

int InnerData::length()
{
    return x.size();
}