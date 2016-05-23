#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#define MAIN_POS_X 0
#define MAIN_POS_Y 0
#define MAIN_WIDTH 1600
#define MAIN_HEIGHT 900

static const char* HOME_PATH = "/home/ycroft/tmp/twd/valid";
static const char* ICON_WORKPLACE = "/home/ycroft/Pictures/stokes/set_workplace.gif";
static const char* ICON_INFO = "/home/ycroft/Pictures/stokes/info.gif";
static const char* ICON_GRAPHICS = "/home/ycroft/Pictures/stokes/graphics.gif";
static const char* ICON_ANALYSE = "/home/ycroft/Pictures/stokes/analyse.gif";
static const char* ICON_THREADS = "/home/ycroft/Pictures/stokes/threads.gif";

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QAction* m_action_file_workplace;
    QAction* m_action_windows_threads;
    QAction* m_action_windows_graphics;
    QAction* m_action_windows_info;
    QAction* m_action_windows_analyse;
    Plot* m_plot;
    InfoPanel* m_info_panel;
    GraphicsPanel* m_graphics_panel;
    ThreadsPanel* m_threads_panel;
    AnalysePanel* m_analyse_panel;
    
    SpectrographDevice* m_device;
    ResourceManager* m_manager;
    
    MainWindow();
    virtual ~MainWindow();
private:
    void __SetupUI();
private slots:
    void __ChangeWorkplace();
    void __ToggleAction_INFO();
    void __CloseAction_INFO();
    void __ToggleAction_GRAPHICS();
    void __CloseAction_GRAPHICS();
    void __ToggleAction_THREADS();
    void __CloseAction_THREADS();
    void __ToggleAction_ANALYSE();
    void __CloseAction_ANALYSE();
};

#endif // MAINWINDOW_H