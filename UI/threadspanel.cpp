#include<UI/threadspanel.h>

ThreadsPanel::ThreadsPanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager)
    : Panel(parent, device, manager)
{
    // this->setWindowTitle(tr("Threads"));
    m_main_layout = new QGridLayout(this);
    this->setLayout(m_main_layout);
    // this->setGeometry(POS_X_THREADS, POS_Y_THREADS, WIDTH_LEFT_PANEL, HEIGHT_THREADS);
    
    QLabel* name_write = new QLabel(tr("Write to file:"));
    QLabel* name_calc_MF = new QLabel(tr("Calulate MF:"));
    QLabel* name_switcher = new QLabel(tr("Input Stream:"));
    
    QButtonGroup* group_write = new QButtonGroup(m_main_layout);
    QButtonGroup* group_calc_MF = new QButtonGroup(m_main_layout);
    QButtonGroup* group_switcher = new QButtonGroup(m_main_layout);
    
    radio_write_enable = new QRadioButton(tr("Enable"),this);
    radio_write_disable = new QRadioButton(tr("Disable"),this);
    radio_calc_MF_enable = new QRadioButton(tr("Enable"),this);
    radio_calc_MF_disable = new QRadioButton(tr("Disable"),this);
    radio_switcher_MLS = new QRadioButton(tr("MLS"),this);
    radio_switcher_MRLS = new QRadioButton(tr("MRLS"),this);
    radio_switcher_URLS = new QRadioButton(tr("URLS"),this);
    
    button_start = new QPushButton(tr("Start"),this);
    button_stop = new QPushButton(tr("Stop all"),this);
    
    group_write->addButton(radio_write_enable);
    group_write->addButton(radio_write_disable);
    group_calc_MF->addButton(radio_calc_MF_enable);
    group_calc_MF->addButton(radio_calc_MF_disable);
    group_switcher->addButton(radio_switcher_MLS);
    group_switcher->addButton(radio_switcher_MRLS);
    group_switcher->addButton(radio_switcher_URLS);
    
    name_write->setAlignment(Qt::AlignRight);
    name_calc_MF->setAlignment(Qt::AlignRight);
    name_switcher->setAlignment(Qt::AlignRight);
    
    m_main_layout->addWidget(name_write,0,0,1,1);
    m_main_layout->addWidget(name_calc_MF,1,0,1,1);
    m_main_layout->addWidget(name_switcher,2,0,1,1);
    m_main_layout->addWidget(radio_write_enable,0,1,1,1);
    m_main_layout->addWidget(radio_write_disable,0,2,1,1);
    m_main_layout->addWidget(radio_calc_MF_enable,1,1,1,1);
    m_main_layout->addWidget(radio_calc_MF_disable,1,2,1,1);
    m_main_layout->addWidget(radio_switcher_MRLS,2,1,1,1);
    m_main_layout->addWidget(radio_switcher_URLS,2,2,1,1);
    m_main_layout->addWidget(radio_switcher_MLS,3,1,1,1);
    m_main_layout->addWidget(button_start,4,1,1,1);
    m_main_layout->addWidget(button_stop,4,2,1,1);
    
    radio_write_enable->setChecked(true);
    radio_calc_MF_enable->setChecked(true);
    radio_switcher_MLS->setChecked(true);
    
    connect(radio_write_enable,SIGNAL(toggled(bool)),this,SLOT(__Toggle_Write(bool)));
    connect(radio_calc_MF_enable,SIGNAL(toggled(bool)),this,SLOT(__Toggle_MF(bool)));
    connect(radio_switcher_MLS,SIGNAL(toggled(bool)),this,SLOT(__Select_MLS(bool)));
    connect(radio_switcher_MRLS,SIGNAL(toggled(bool)),this,SLOT(__Select_MRLS(bool)));
    connect(radio_switcher_URLS,SIGNAL(toggled(bool)),this,SLOT(__Select_URLS(bool)));
    connect(button_start,SIGNAL(clicked()),this,SLOT(__StartAll()));
    connect(button_stop,SIGNAL(clicked()),this,SLOT(__StopAll()));
}

ThreadsPanel::~ThreadsPanel()
{
    
}

void ThreadsPanel::__Toggle_Write(bool checked)
{
    m_manager.EnableWrite(checked);
}

void ThreadsPanel::__Toggle_MF(bool checked)
{
    m_manager.EnableCalcMF(checked);
}

void ThreadsPanel::__Select_MLS(bool checked)
{
    m_manager.SetReadStreamType(STREAM_MLS);
}

void ThreadsPanel::__Select_MRLS(bool checked)
{
    m_manager.SetReadStreamType(STREAM_MRLS);
}

void ThreadsPanel::__Select_URLS(bool checked)
{
    m_manager.SetReadStreamType(STREAM_URLS);
}

void ThreadsPanel::__StartAll()
{
    m_manager.Start();
}

void ThreadsPanel::__StopAll()
{
    m_manager.Stop();
}
