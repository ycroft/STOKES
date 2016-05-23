#include<UI/widget.h>

void Plot::init()
{
    initCanvas();
    initCurves();
    initTools();
}

void Plot::initCanvas()
{
    setGeometry(100,100,800,600);
    setTitle(tr("Title"));
    setCanvasBackground(QBrush(QColor("white")));
    setCanvasLineWidth(1); //  画布边缘宽度
    // enableAxis(0,false);
    /*
    * axisId:
    *     y_leff:   0
    *     y_right:  1
    *     x_buttom: 2
    *     x_top:    4
    */
    setAxisTitle(2, tr("wave number"));
    setAxisTitle(0, tr("DOP"));
    
    setAxisMaxMajor(0, 10); // 主刻度的个数
    setAxisMaxMinor(0, 10); // 辅助刻度的分裂数目
    
    insertLegend(new QwtLegend(),QwtPlot::RightLegend);
}

void Plot::initCurves()
{
    QwtPointSeriesData* data = new QwtPointSeriesData();
    
    m_manager.GetPointSeriesData(data, ResourceManager::MF_0);
    
    QwtPlotCurve* curve = new QwtPlotCurve(tr("measured data"));
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setLegendAttribute(QwtPlotCurve::LegendNoAttribute);
    curve->setPen(QPen(Qt::red));
    curve->attach(this);
    curve->setData(data);
}

void Plot::initTools()
{
    QwtPlotZoomer* zoomer = new QwtPlotZoomer(QwtPlot::xBottom,QwtPlot::yLeft,this->canvas());
    // QwtPlotPicker* picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
    //     QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,this->canvas());
    zoomer->setTrackerMode(QwtPicker::AlwaysOn);
}
