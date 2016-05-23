#include<UI/mainwindow.h>

MainWindow::MainWindow():QMainWindow()
{
    m_action_file_workplace = new QAction(QIcon(ICON_WORKPLACE),tr("&Change workplace..."),this);
    m_action_windows_info = new QAction(QIcon(ICON_INFO),tr("&Informations..."),this);
    m_action_windows_graphics = new QAction(QIcon(ICON_GRAPHICS),tr("&Add graphics..."),this);
    m_action_windows_analyse = new QAction(QIcon(ICON_ANALYSE),tr("&Analyse..."),this);
    m_action_windows_threads = new QAction(QIcon(ICON_THREADS),tr("&Threads..."),this);
    
    m_device = new VisualMachine(HOME_PATH);
    m_manager = new ResourceManager(*m_device);
    m_plot = new Plot(NULL,*m_manager);
    
    m_device->Boot();
    m_manager->Start();
    m_manager->SetReadStreamType(STREAM_MRLS);
    m_manager->SetReadStreamType(STREAM_URLS);
    m_manager->SetReadStreamType(STREAM_MLS);
    __SetupUI();
}

MainWindow::~MainWindow()
{
    // delete m_plot;
    delete m_manager;
    delete m_device;
    
    delete m_action_windows_threads;
    delete m_action_windows_analyse;
    delete m_action_windows_graphics;
    delete m_action_windows_info;
    delete m_action_file_workplace;
}

void MainWindow::__SetupUI()
{
    QMenu* menubar_file = menuBar()->addMenu(tr("&File"));
    QMenu* menubar_window = menuBar()->addMenu(tr("&Window"));
    QToolBar* toolbar_file = addToolBar(tr("&File"));
    QToolBar* toolbar_window = addToolBar(tr("&Window"));
    
    m_action_windows_analyse->setCheckable(true);
    m_action_windows_info->setCheckable(true);
    m_action_windows_graphics->setCheckable(true);
    m_action_windows_threads->setCheckable(true);
    
    m_action_windows_analyse->setChecked(true);
    m_action_windows_info->setChecked(true);
    m_action_windows_graphics->setChecked(true);
    m_action_windows_threads->setChecked(true);
    
    QList<QKeySequence> ctrl_w,ctrl_i,ctrl_g,ctrl_a,ctrl_f;
    ctrl_w.append(QKeySequence(tr("Ctrl+w")));
    ctrl_i.append(QKeySequence(tr("Ctrl+i")));
    ctrl_g.append(QKeySequence(tr("Ctrl+g")));
    ctrl_a.append(QKeySequence(tr("Ctrl+a")));
    ctrl_f.append(QKeySequence(tr("Ctrl+f")));
    
    m_action_file_workplace->setShortcuts(ctrl_w);
    m_action_windows_info->setShortcuts(ctrl_i);
    m_action_windows_graphics->setShortcuts(ctrl_g);
    m_action_windows_analyse->setShortcuts(ctrl_a);
    m_action_windows_threads->setShortcuts(ctrl_a);
    
    menubar_file->addAction(m_action_file_workplace);
    menubar_window->addAction(m_action_windows_info);
    menubar_window->addAction(m_action_windows_graphics);
    menubar_window->addAction(m_action_windows_analyse);
    menubar_window->addAction(m_action_windows_threads);
    
    toolbar_file->addAction(m_action_file_workplace);
    toolbar_window->addAction(m_action_windows_info);
    toolbar_window->addAction(m_action_windows_graphics);
    toolbar_window->addAction(m_action_windows_analyse);
    toolbar_window->addAction(m_action_windows_threads);
    
    this->setCentralWidget(m_plot);
    this->setGeometry(MAIN_POS_X,MAIN_POS_Y,MAIN_WIDTH,MAIN_HEIGHT);
    
    CurveAttribute attr1(QString("SV_1"),QPen(Qt::red));
    CurveAttribute attr2(QString("SV_2"),QPen(Qt::black));
    CurveAttribute attr3(QString("SV_3"),QPen(Qt::blue));
    m_plot->AddCurve(ResourceManager::SV_1,attr1);
    m_plot->AddCurve(ResourceManager::SV_2,attr2);
    m_plot->AddCurve(ResourceManager::SV_3,attr3);
    
    m_info_panel = new InfoPanel(this,*m_device,*m_manager);
    m_graphics_panel = new GraphicsPanel(this,*m_device,*m_manager);
    m_threads_panel = new ThreadsPanel(this,*m_device,*m_manager);
    m_analyse_panel = new AnalysePanel(this,*m_device,*m_manager);
    m_info_panel->show();
    m_graphics_panel->show();
    m_threads_panel->show();
    m_analyse_panel->show();
    
    connect(m_action_file_workplace,SIGNAL(triggered()),this,SLOT(__ChangeWorkplace()));
    connect(m_info_panel,SIGNAL(closed()),this,SLOT(__CloseAction_INFO()));
    connect(m_graphics_panel,SIGNAL(closed()),this,SLOT(__CloseAction_GRAPHICS()));
    connect(m_threads_panel,SIGNAL(closed()),this,SLOT(__CloseAction_THREADS()));
    connect(m_analyse_panel,SIGNAL(closed()),this,SLOT(__CloseAction_ANALYSE()));
    
    connect(m_action_windows_info,SIGNAL(triggered()),this,SLOT(__ToggleAction_INFO()));
    connect(m_action_windows_graphics,SIGNAL(triggered()),this,SLOT(__ToggleAction_GRAPHICS()));
    connect(m_action_windows_threads,SIGNAL(triggered()),this,SLOT(__ToggleAction_THREADS()));
    connect(m_action_windows_analyse,SIGNAL(triggered()),this,SLOT(__ToggleAction_ANALYSE()));
}

void MainWindow::__ChangeWorkplace()
{
    QString dir = QFileDialog::getExistingDirectory(this, 
        tr("Open Directory"),HOME_PATH,QFileDialog::ShowDirsOnly |
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

void MainWindow::__CloseAction_INFO()
{
    m_info_panel = NULL;
    m_action_windows_info->setChecked(false);
    return;
}
void MainWindow::__CloseAction_GRAPHICS()
{
    m_graphics_panel = NULL;
    m_action_windows_graphics->setChecked(false);
    return;
}
void MainWindow::__CloseAction_THREADS()
{
    m_threads_panel = NULL;
    m_action_windows_threads->setChecked(false);
    return;
}
void MainWindow::__CloseAction_ANALYSE()
{
    m_analyse_panel = NULL;
    m_action_windows_analyse->setChecked(false);
    return;
}

void MainWindow::__ToggleAction_INFO()
{
    if(m_action_windows_info->isChecked())
    {
        if(NULL != m_info_panel)
        {
            return;
        }
        m_info_panel = new InfoPanel(this, *m_device, *m_manager);
        connect(m_info_panel,SIGNAL(closed()),this,SLOT(__CloseAction_INFO()));
        m_info_panel->show();
    }
    else
    {
        if(NULL == m_info_panel)
        {
            return;
        }
        m_info_panel->close();
        m_info_panel = NULL;
    }
}
void MainWindow::__ToggleAction_GRAPHICS()
{
    if(m_action_windows_graphics->isChecked())
    {
        if(NULL != m_graphics_panel)
        {
            return;
        }
        m_graphics_panel = new GraphicsPanel(this, *m_device, *m_manager);
        connect(m_graphics_panel,SIGNAL(closed()),this,SLOT(__CloseAction_GRAPHICS()));
        m_graphics_panel->show();
    }
    else
    {
        if(NULL == m_graphics_panel)
        {
            return;
        }
        m_graphics_panel->close();
        m_graphics_panel = NULL;
    }
}
void MainWindow::__ToggleAction_THREADS()
{
    if(m_action_windows_threads->isChecked())
    {
        if(NULL != m_threads_panel)
        {
            return;
        }
        m_threads_panel = new ThreadsPanel(this, *m_device, *m_manager);
        connect(m_threads_panel,SIGNAL(closed()),this,SLOT(__CloseAction_THREADS()));
        m_threads_panel->show();
    }
    else
    {
        if(NULL == m_threads_panel)
        {
            return;
        }
        m_threads_panel->close();
        m_threads_panel = NULL;
    }
}
void MainWindow::__ToggleAction_ANALYSE()
{
    if(m_action_windows_analyse->isChecked())
    {
        if(NULL != m_analyse_panel)
        {
            return;
        }
        m_analyse_panel = new AnalysePanel(this, *m_device, *m_manager);
        connect(m_analyse_panel,SIGNAL(closed()),this,SLOT(__CloseAction_ANALYSE()));
        m_analyse_panel->show();
    }
    else
    {
        if(NULL == m_analyse_panel)
        {
            return;
        }
        m_analyse_panel->close();
        m_analyse_panel = NULL;
    }
}