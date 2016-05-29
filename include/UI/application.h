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

/* 设置默认工作目录，将来会移至配置文件 */
static const char* HOME_PATH = "/home/ycroft/tmp/twd/valid";
/*
 * 以下为图标文件，临时使用了本机绝对路径
 * 待修改！
 */
static const char* ICON_WORKPLACE = "/home/ycroft/Pictures/stokes/set_workplace.gif";
static const char* ICON_VISUAL_MACHINE = "/home/ycroft/Pictures/stokes/vm.gif";
static const char* ICON_REAL_MACHINE = "/home/ycroft/Pictures/stokes/rm.gif";
static const char* ICON_REPORT = "/home/ycroft/Pictures/stokes/report.gif";
static const char* ICON_EDIT = "/home/ycroft/Pictures/stokes/edit.gif";
static const char* ICON_REPAINT = "/home/ycroft/Pictures/stokes/repaint.gif";
static const char* ICON_STATIC = "/home/ycroft/Pictures/stokes/static.gif";

/**
 * 主窗口
 * 整个软件的主界面、程序执行入口
 */
class Application : public QMainWindow
{
    Q_OBJECT
public:
    Application();
    virtual ~Application();
private:
    SpectrographDevice* m_device;           /** 声明光谱设备（实机或虚机） */
    ResourceManager* m_manager;             /** 资源管理器：负责维护计算流程 */
    Plot* m_plot;                           /** 绘图面板，用于绘制函数图像 */
    InfoPanel* m_info_panel;                /** 信息面板，用于显示各个线程的状态 */
    GraphicsPanel* m_graphics_panel;        /** 函数图像面板，用于显示正在绘制的函数图像列表 */
    ThreadsPanel* m_threads_panel;          /** 线程控制面板，用于控制各个线程的开闭以及输入流 */
    AnalysePanel* m_analyse_panel;          /** 分析信息面板，用于显示各种分析结果 */
    bool m_curves[ResourceManager::DATA_NUM]；
    
    void __SetupUI();
private slots:
    void __AddCurve(ResourceManager::DataName);
    void __DelCurve(ResourceManager::DataName);
    void __ClearCurves();
    void __ChangeWorkplace();
};

#endif // APPLICATION_H
