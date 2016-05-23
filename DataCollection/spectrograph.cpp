#include<DataCollection/spectrograph.h>

using namespace std;

SpectrographDevice::SpectrographDevice()
{
    // TODO:
}

SpectrographDevice::~SpectrographDevice()
{
    // TODO:
}

VisualMachine::VisualMachine(string dir):SpectrographDevice()
{
    device_type_id = 1;
    m_work_directory = dir;
    if(m_work_directory.at(m_work_directory.length()-1) != SYS_SEPERATOR)
    {
        m_work_directory += SYS_SEPERATOR;
    }
    m_state = OFF;
}

VisualMachine::~VisualMachine()
{
    if(m_state == ON)
    {
        Shutdown();
    }
}

bool VisualMachine::Boot()
{
    if(m_state == ON)
    {
        return FAIL;
    }
    string mrls = m_work_directory + FNAME_INPUT_MRLS;
    string urls = m_work_directory + FNAME_INPUT_URLS;
    string mls = m_work_directory + FNAME_INPUT_MLS;
    m_modulated_RLS.open(mrls.c_str());
    m_untreated_RLS.open(urls.c_str());
    m_measured_LS.open(mls.c_str());
    if(!m_modulated_RLS.is_open()||!m_untreated_RLS.is_open()||!m_measured_LS.is_open())
    {
        m_modulated_RLS.close();
        m_untreated_RLS.close();
        m_measured_LS.close();
        return FAIL;
    }
    m_state = ON;
    return SUCCESS;
}

bool VisualMachine::Shutdown()
{
    if(m_state == OFF)
    {
        return FAIL;
    }
    m_modulated_RLS.close();
    m_untreated_RLS.close();
    m_measured_LS.close();
    m_state = OFF;
    
    return SUCCESS;
}

bool VisualMachine::Reboot()
{
    if(m_state == OFF)
    {
        return FAIL;
    }
    Shutdown();
    Boot();
    return SUCCESS;
}

bool VisualMachine::ReadDatagram(InnerData& innerData,int type)
{
    if(m_state == OFF)
    {
        return FAIL;
    }
    stringstream buffer;
    ifstream* ift;
    switch(type)
    {
    case STREAM_MRLS:
        ift = &m_modulated_RLS; 
        break;
    case STREAM_URLS:
        ift = &m_untreated_RLS;
        break;
    case STREAM_MLS:
        ift = &m_measured_LS;
        break;
    default:
        return FAIL;
    }
    buffer << ift->rdbuf();
    
    vector<double> xaxis,yaxis;
    __ReadBuffer(buffer, xaxis, yaxis);
    math::reciprocal(xaxis,yaxis);
    
    double start = xaxis[0];
    double end = xaxis[xaxis.size()-1];
    double step = (end-start)/(SPLINE_POINT_NUM-1);
    double sx[SPLINE_POINT_NUM];
    double sy[SPLINE_POINT_NUM];
    for(int i=0;i<SPLINE_POINT_NUM;i++)
    {
        sx[i] = start + i*step;
    }
    math::spline(sy,&xaxis[0],&yaxis[0],sx,xaxis.size(),SPLINE_POINT_NUM);
    vector<Complex> cx,cy;
    for(int i = 0; i < SPLINE_POINT_NUM; ++ i)
    {
        cx.push_back(Complex(sx[i],0));
        cy.push_back(Complex(sy[i],0));
    }
    innerData.SetContent(cx,cy);
    __RenewBuffer();
    return SUCCESS;
}

void VisualMachine::__ReadBuffer(stringstream& buf, vector<double>&xaxis, vector<double>& yaxis)
{
    char line[LINE_BUF_SIZE];
    double x,y;
    while(buf.peek()>'A' && buf.peek()<'z')
    {
        buf.getline(line,LINE_BUF_SIZE);
    }
    while(buf >> x)
    {
        buf >> y;
        xaxis.push_back(x);
        yaxis.push_back(y);
    }
}

void VisualMachine::__RenewBuffer()
{
    string mrls = m_work_directory + FNAME_INPUT_MRLS;
    string urls = m_work_directory + FNAME_INPUT_URLS;
    string mls = m_work_directory + FNAME_INPUT_MLS;
    m_modulated_RLS.close();
    m_modulated_RLS.open(mrls.c_str());
    m_modulated_RLS.clear();
    
    m_untreated_RLS.close();
    m_untreated_RLS.open(urls.c_str());
    m_untreated_RLS.clear();
    
    m_measured_LS.close();
    m_measured_LS.open(mls.c_str());
    m_measured_LS.clear();
    if(!m_modulated_RLS.is_open()||!m_untreated_RLS.is_open()||!m_measured_LS.is_open())
    {
        Shutdown();
    }
}
