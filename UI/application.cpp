#include<UI/application.h>

Application::Application():QMainWindow()
{
    for(int i = 0; i < ResourceManager::DATA_NUM; ++ i)
    {
        m_curves[i] = false;
    }
    
    m_device = new VisualMachine(HOME_PATH);
    m_manager = new ResourceManager(*m_device);
    
    m_device->Boot();
    m_manager->Start();
    m_manager->SetReadStreamType(STREAM_MRLS);
    m_manager->SetReadStreamType(STREAM_URLS);
    m_manager->SetReadStreamType(STREAM_MLS);
    __SetupUI();
}

Application::~Application()
{
    // delete m_plot;
    delete m_manager;
    delete m_device;
}

void Application::__SetupUI()
{
    QMenu* menubar_device = menuBar()->addMenu(tr("&Device"));
    QMenu* menubar_plot = menuBar()->addMenu(tr("&Plot"));
    QToolBar* toolbar_device = addToolBar(tr("&Device"));
    QToolBar* toolbar_plot = addToolBar(tr("&Plot"));
    
    QAction* m_action_file_workplace = new QAction(QIcon(ICON_WORKPLACE),tr("&Change workplace..."),this);
    QAction* m_action_file_report = new QAction(QIcon(ICON_REPORT),tr("&Generate Report..."),this);
    QAction* m_action_type_VM = new QAction(QIcon(ICON_VISUAL_MACHINE),tr("&Toggle visual machine..."),this);
    QAction* m_action_type_RM = new QAction(QIcon(ICON_REAL_MACHINE),tr("&Toggle real machine..."),this);
    QAction* m_action_plot_repaint = new QAction(QIcon(ICON_REPAINT),tr("&Dynamic mode"),this);
    QAction* m_action_plot_static = new QAction(QIcon(ICON_STATIC),tr("&Static mode"),this);
    QAction* m_action_plot_edit = new QAction(QIcon(ICON_EDIT),tr("&Edit plot"),this);
    m_action_type_RM->setCheckable(true);
    m_action_type_VM->setCheckable(true);
    m_action_plot_repaint->setCheckable(true);
    m_action_plot_static->setCheckable(true);
    
    m_action_plot_repaint->setChecked(true);
    m_action_type_VM->setChecked(true);
    
    QActionGroup* m_device_type = new QActionGroup(this);
    m_device_type->addAction(m_action_type_RM);
    m_device_type->addAction(m_action_type_VM);
    QActionGroup* m_plot_mode = new QActionGroup(this);
    m_plot_mode->addAction(m_action_plot_repaint);
    m_plot_mode->addAction(m_action_plot_static);
    
    menubar_device->addAction(m_action_file_workplace);
    menubar_device->addAction(m_action_file_report);
    menubar_device->addSeparator();
    menubar_device->addAction(m_action_type_RM);
    menubar_device->addAction(m_action_type_VM);
    toolbar_device->addAction(m_action_file_workplace);
    toolbar_device->addAction(m_action_file_report);
    toolbar_device->addSeparator();
    toolbar_device->addAction(m_action_type_RM);
    toolbar_device->addAction(m_action_type_VM);
    
    menubar_plot->addAction(m_action_plot_repaint);
    menubar_plot->addAction(m_action_plot_static);
    menubar_plot->addSeparator();
    menubar_plot->addAction(m_action_plot_edit);
    
    toolbar_plot->addAction(m_action_plot_repaint);
    toolbar_plot->addAction(m_action_plot_static);
    toolbar_plot->addSeparator();
    toolbar_plot->addAction(m_action_plot_edit);
    
    QGridLayout* main_layout = new QGridLayout();
    QWidget* main_widget = new QWidget(this); 
    this->setCentralWidget(main_widget);
    main_widget->setLayout(main_layout);
    
    m_plot = new Plot(main_widget,*m_manager);
    m_info_panel = new InfoPanel(main_widget,*m_device,*m_manager);
    m_graphics_panel = new GraphicsPanel(main_widget,*m_device,*m_manager);
    m_threads_panel = new ThreadsPanel(main_widget,*m_device,*m_manager);
    m_analyse_panel = new AnalysePanel(main_widget,*m_device,*m_manager);
    
    m_info_panel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_graphics_panel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_threads_panel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_analyse_panel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_plot->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    
    m_info_panel->setLineWidth(2);
    m_graphics_panel->setLineWidth(2);
    m_threads_panel->setLineWidth(2);
    m_analyse_panel->setLineWidth(2);
    m_plot->setLineWidth(2);
    
    main_layout->addWidget(m_info_panel,0,0,1,1);
    main_layout->addWidget(m_threads_panel,1,0,1,1);
    main_layout->addWidget(m_graphics_panel,2,0,1,1);
    main_layout->addWidget(m_analyse_panel,3,0,1,1);
    main_layout->addWidget(m_plot,0,1,4,5);
    
    connect(m_graphics_panel,SIGNAL(AddCurve(ResourceManager::DataName)),this,SLOT(__AddCurve(ResourceManager::DataName)));
    connect(m_graphics_panel,SIGNAL(DelCurve(ResourceManager::DataName)),this,SLOT(__DelCurve(ResourceManager::DataName)));
    connect(m_graphics_panel,SIGNAL(ClearCurves()),this, SLOT(__ClearCurves()));
    connect(m_action_file_workplace,SIGNAL(triggered()),this,SLOT(__ChangeWorkplace()));
    
    this->setGeometry(0,0,1600,900);
    this->show();
}

void Application::__AddCurve(ResourceManager::DataName dname)
{
    CurveAttribute attr;
    attr.name = m_manager->GetStreamName(dname);
    m_plot->AddCurve(dname, attr);
}

void Application::__DelCurve(ResourceManager::DataName dname)
{
    m_plot->DelCurve(dname);
}

void Application::__ClearCurves()
{
    m_plot->ClearCurves();
}

void Application::__ChangeWorkplace()
{
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Directory"), HOME_PATH, QFileDialog::ShowDirsOnly|
        QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        m_manager->Stop();
        m_device->Shutdown();
        delete m_device;
        m_device = new VisualMachine(dir.toStdString());
        m_device->Boot();
        m_manager->Start();
    }
}
