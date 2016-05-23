#ifndef PLOT_H
#define PLOT_H

#include<DataCollection/objmanager.h>

#include<qwt_plot.h>
#include<qwt_legend.h>
#include<qwt_plot_curve.h>
#include<qwt_plot_picker.h>
#include<qwt_plot_zoomer.h>

#include<QtCore/QObject>
#include<QtCore/QObject>
#include<QtCore/QString>

#include<QtGui/QPen>
#include<QtGui/QBrush>
#include<QtGui/QColor>
#include<QtGui/QWidget>
#include<QtGui/QFrame>
#include<QtGui/QApplication>

#define RENEW_MILI_CLOCK 20

class PlotAttribute
{
public:
    PlotAttribute()
    {
        title = QString("Datagrams");
        xAxisName = QString(" ");
        yAxisName = QString(" ");
        background = QBrush(QColor("white"));
    }
    QString title;
    QString xAxisName;
    QString yAxisName;
    QBrush background;
};

class CurveAttribute
{
public:
    CurveAttribute()
    {
        name = QString("no name");
        pen = QPen(Qt::black);
    }
    CurveAttribute(QString n, QPen p)
    {
        name = n;
        pen = p;
    }
    QString name;
    QPen pen;
};

class Plot : public QwtPlot
{
    Q_OBJECT
public:
    Plot(QWidget* parent, ResourceManager& manager, 
        PlotAttribute attr=PlotAttribute()) : QwtPlot(parent),
        m_resourceManager(manager)
    {
        __Initialize(attr);
    }
    virtual ~Plot();
    void RenewEnable(bool flag = true);
    void AddCurve(ResourceManager::DataName dname, CurveAttribute attr=CurveAttribute());
    void DelCurve(ResourceManager::DataName dname);
    void ClearCurves();
private:
    bool m_renewEnable;
    ResourceManager& m_resourceManager;
    std::vector<bool> m_renewList;
    std::vector<QwtPlotCurve*> m_curves;
    std::vector<QwtPointSeriesData*> m_seriesData;
    QwtLegend* m_mainLegend;
    QwtPlotZoomer* m_zoomer;

    void __Initialize(PlotAttribute& attr);
    void __Thread_Renew();
signals:
    void DataRenewed();
};

#endif // PLOT_H