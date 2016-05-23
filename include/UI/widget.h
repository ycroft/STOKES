#ifndef WIDGET_H
#define WIDGET_H

#include<qwt_plot.h>
#include<qwt_legend.h>
#include<qwt_plot_curve.h>
#include<qwt_plot_picker.h>
#include<qwt_plot_zoomer.h>

#include<QtCore/QObject>
#include<QtCore/QString>

#include<QtGui/QPen>
#include<QtGui/QBrush>
#include<QtGui/QColor>
#include<QtGui/QWidget>
#include<QtGui/QApplication>

#include<DataCollection/objmanager.h>

class Plot : public QwtPlot
{
public:
    Plot(QWidget* parent, ResourceManager& manager) : QwtPlot(parent),
        m_manager(manager)
    {
        init();
    }
private:
    void init();
    void initCanvas();
    void initCurves();
    void initTools();
    ResourceManager& m_manager;
};

#endif  // WIDGET_H