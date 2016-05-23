#ifndef APPLICATION_H
#define APPLICATION_H

#include<UI/plot.h>
#include<UI/infopanel.h>
#include<UI/graphicspanel.h>
#include<UI/threadspanel.h>
#include<UI/analysepanel.h>

#include<QtCore/QList>
#include<QtCore/QDebug>
#include<QtGui/QAction>
#include<QtGui/QMenuBar>
#include<QtGui/QToolBar>
#include<QtGui/QMainWindow>
#include<QtGui/QFileDialog>
#include<QtGui/QDesktopWidget>

static const char* HOME_PATH = "/home/ycroft/tmp/twd/valid";
static const char* ICON_WORKPLACE = "/home/ycroft/Pictures/stokes/set_workplace.gif";
static const char* ICON_VISUAL_MACHINE = "/home/ycroft/Pictures/stokes/vm.gif";
static const char* ICON_REAL_MACHINE = "/home/ycroft/Pictures/stokes/rm.gif";
static const char* ICON_REPORT = "/home/ycroft/Pictures/stokes/report.gif";
static const char* ICON_EDIT = "/home/ycroft/Pictures/stokes/edit.gif";
static const char* ICON_REPAINT = "/home/ycroft/Pictures/stokes/repaint.gif";
static const char* ICON_STATIC = "/home/ycroft/Pictures/stokes/static.gif";

class Application : public QMainWindow
{
    Q_OBJECT
public:
    Application();
    virtual ~Application();
private:
    SpectrographDevice* m_device;
    ResourceManager* m_manager;
    Plot* m_plot;
    InfoPanel* m_info_panel;
    GraphicsPanel* m_graphics_panel;
    ThreadsPanel* m_threads_panel;
    AnalysePanel* m_analyse_panel;
    bool m_curves[ResourceManager::DATA_NUM];
    
    void __SetupUI();
private slots:
    void __AddCurve(ResourceManager::DataName);
    void __DelCurve(ResourceManager::DataName);
    void __ClearCurves();
    void __ChangeWorkplace();
};

#endif // APPLICATION_H