#include<UI/plot.h>

using namespace std;

Plot::~Plot()
{
    int dataNum = ResourceManager::DATA_NUM;
    m_renewEnable = false;
    for(int i = 0; i < dataNum; ++ i)
    {
        m_renewList[i] = false;
    }
    for(int i = 0; i < dataNum; ++ i)
    {
        if(NULL != m_curves[i])
        {
            delete m_curves[i];
            m_curves[i] = NULL;
        }
    }
}

void Plot::AddCurve(ResourceManager::DataName dname, CurveAttribute attr)
{
    if(NULL == m_curves[dname])
    {
        m_renewList[dname] = true;
        m_curves[dname] = new QwtPlotCurve(attr.name);
        m_curves[dname]->setLegendAttribute(QwtPlotCurve::LegendNoAttribute);
        m_curves[dname]->setRenderHint(QwtPlotItem::RenderAntialiased);
        m_curves[dname]->setPen(attr.pen);
        m_curves[dname]->setData(m_seriesData[dname]);
        m_curves[dname]->attach(this);
    }
    else
    {
        m_curves[dname]->attach(this);
    }
}

void Plot::DelCurve(ResourceManager::DataName dname)
{
    if(NULL == m_curves[dname])
    {
        return;
    }
    m_curves[dname]->detach();
}

void Plot::__Initialize(PlotAttribute& attr)
{
    m_renewEnable = true;
    int dataNum = ResourceManager::DATA_NUM;
    m_renewList = vector<bool>(dataNum);
    m_curves = vector<QwtPlotCurve*>(dataNum);
    m_seriesData = vector<QwtPointSeriesData*>(dataNum);
    for(int i = 0; i < dataNum; ++ i)
    {
        m_curves[i] = NULL;
        m_seriesData[i] = new QwtPointSeriesData();
        m_renewList[i] = false;
    }
    
    setTitle(attr.title);
    setCanvasBackground(attr.background);
    setCanvasLineWidth(1);
    setAxisTitle(QwtPlot::xBottom, attr.xAxisName);
    setAxisTitle(QwtPlot::yLeft, attr.yAxisName);
    setAxisMaxMajor(QwtPlot::xBottom, 10);
    setAxisMaxMinor(QwtPlot::xBottom, 10);
    setAxisMaxMajor(QwtPlot::yLeft, 10);
    setAxisMaxMinor(QwtPlot::yLeft, 10);

    m_mainLegend = new QwtLegend();
    insertLegend(m_mainLegend , QwtPlot::RightLegend);
    
    // m_zoomer = new QwtPlotZoomer(QwtPlot::xBottom,QwtPlot::yLeft,this->canvas());
    // m_zoomer->setTrackerMode(QwtPicker::AlwaysOn);
    
    QObject::connect(this,SIGNAL(DataRenewed()),this,SLOT(replot()));
    boost::thread renew_thread(boost::bind(&Plot::__Thread_Renew,this));
}

void Plot::ClearCurves()
{
    for(int i = 0; i < m_curves.size(); ++ i)
    {
        if(NULL != m_curves[i])
        {
            m_curves[i]->detach();
        }
    }
}

void Plot::RenewEnable(bool flag)
{
}

void Plot::__Thread_Renew()
{
    boost::this_thread::sleep(boost::posix_time::millisec(RENEW_MILI_CLOCK));
    int dataNum = ResourceManager::DATA_NUM;
    while(m_renewEnable)
    {
        for(int i = 0; i < dataNum; ++ i)
        {
            if(m_renewList[i])
            {
                m_resourceManager.GetPointSeriesData(m_seriesData[i],
                    (ResourceManager::DataName)i);
            }
        }
        emit DataRenewed();
        boost::this_thread::sleep(boost::posix_time::millisec(RENEW_MILI_CLOCK));
    }
}
