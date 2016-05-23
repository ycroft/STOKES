#include<UI/infopanel.h>

InfoPanel::InfoPanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager) :
    Panel(parent, device, manager)
{
    // this->setWindowTitle(tr("Info"));
    m_main_layout = new QGridLayout();
    this->setLayout(m_main_layout);
    // this->setGeometry(POS_X_INFO,POS_Y_INFO,WIDTH_LEFT_PANEL,HEIGHT_INFO);
    
    m_title_name = new QLabel(QString("Name"), this);
    m_title_status = new QLabel(QString("Status"), this);
    m_name_machine_type = new QLabel(tr("machine type:"),this);
    m_name_machine = new QLabel(tr("machine status:"),this);
    m_name_write = new QLabel(tr("write to file:"),this);
    m_name_fetch = new QLabel(tr("fetch from device:"),this);
    m_name_MF = new QLabel(tr("calculate MF"),this);
    m_name_SV = new QLabel(tr("calculate SV"),this);
    m_name_ADDI = new QLabel(tr("additional calc:"),this);
    m_name_repaint = new QLabel(tr("always repaint:"),this);
    m_status_machine_type = new QLabel(tr("unavailable"),this);
    m_status_machine = new QLabel(tr("unavailable"),this);
    m_status_write = new QLabel(tr("unavailable"),this);
    m_status_fetch = new QLabel(tr("unavailable"),this);
    m_status_MF = new QLabel(tr("unavailable"),this);
    m_status_SV = new QLabel(tr("unavailable"),this);
    m_status_ADDI = new QLabel(tr("unavailable"),this);
    m_status_repaint = new QLabel(tr("unavailable"),this);
   
    m_line = new QFrame(this);
    
    m_line->setFrameShape(QFrame::HLine);
    m_line->setFrameShadow(QFrame::Sunken);

    m_title_name->setAlignment(Qt::AlignRight);
    m_title_status->setAlignment(Qt::AlignHCenter);
    m_name_machine_type->setAlignment(Qt::AlignRight);
    m_name_machine->setAlignment(Qt::AlignRight);
    m_name_write->setAlignment(Qt::AlignRight);
    m_name_fetch->setAlignment(Qt::AlignRight);
    m_name_MF->setAlignment(Qt::AlignRight);
    m_name_SV->setAlignment(Qt::AlignRight);
    m_name_ADDI->setAlignment(Qt::AlignRight);
    m_name_repaint->setAlignment(Qt::AlignRight);
    m_status_machine_type->setAlignment(Qt::AlignHCenter);
    m_status_machine->setAlignment(Qt::AlignHCenter);
    m_status_write->setAlignment(Qt::AlignHCenter);
    m_status_fetch->setAlignment(Qt::AlignHCenter);
    m_status_MF->setAlignment(Qt::AlignHCenter);
    m_status_SV->setAlignment(Qt::AlignHCenter);
    m_status_ADDI->setAlignment(Qt::AlignHCenter);
    m_status_repaint->setAlignment(Qt::AlignHCenter);
    
    m_main_layout->addWidget(m_title_name,0,0,1,1);
    m_main_layout->addWidget(m_title_status,0,1,1,2);
    m_main_layout->addWidget(m_name_machine_type,2,0,1,1);
    m_main_layout->addWidget(m_name_machine,3,0,1,1);
    m_main_layout->addWidget(m_name_write,4,0,1,1);
    m_main_layout->addWidget(m_name_fetch,5,0,1,1);
    m_main_layout->addWidget(m_name_MF,6,0,1,1);
    m_main_layout->addWidget(m_name_SV,7,0,1,1);
    m_main_layout->addWidget(m_name_ADDI,8,0,1,1);
    m_main_layout->addWidget(m_name_repaint,9,0,1,1);
    
    m_main_layout->addWidget(m_status_machine_type,2,1,1,2);
    m_main_layout->addWidget(m_status_machine,3,1,1,2);
    m_main_layout->addWidget(m_status_write,4,1,1,2);
    m_main_layout->addWidget(m_status_fetch,5,1,1,2);
    m_main_layout->addWidget(m_status_MF,6,1,1,2);
    m_main_layout->addWidget(m_status_SV,7,1,1,2);
    m_main_layout->addWidget(m_status_ADDI,8,1,1,2);
    m_main_layout->addWidget(m_status_repaint,9,1,1,2);
    
    m_main_layout->addWidget(m_line,1,0,1,3);
    
    // m_status_ADDI->setText(tr("A"));
    //     boost::this_thread::sleep(boost::posix_time::millisec(INFO_RENEW_CLOCK));
    // m_status_ADDI->setText(tr("B"));
    //     boost::this_thread::sleep(boost::posix_time::millisec(INFO_RENEW_CLOCK));
    // m_status_ADDI->setText(tr("C"));
    
    
    m_runnable = true;
    boost::thread renew_thread(boost::bind(&InfoPanel::__Renew,this));
}

InfoPanel::~InfoPanel()
{
    
}

void InfoPanel::__Renew()
{
    while(m_runnable)
    {
        boost::this_thread::interruption_point();
        
        States st = m_manager.GetStates();
        m_status_ADDI->setText(__GetStateName(st._calc_AD_state));
        m_status_fetch->setText(__GetStateName(st._fetch_state));
        if(m_device.GetState() == ON)
            m_status_machine->setText(tr("Power On"));
        else
            m_status_machine->setText(tr("Power Off"));
        if(m_device.device_type_id == 0)
            m_status_machine_type->setText(tr("Spectrograph device"));
        else
            m_status_machine_type->setText(tr("Visual machine"));
        m_status_MF->setText(__GetStateName(st._calc_MF_state));
        m_status_SV->setText(__GetStateName(st._calc_SV_state));
        m_status_write->setText(__GetStateName(st._write_state));
        
        boost::this_thread::sleep(boost::posix_time::millisec(INFO_RENEW_CLOCK));
    }
}

QString InfoPanel::__GetStateName(int s)
{
    switch(s)
    {
    case RUNNING:
        return tr("Running");
    case WAITING:
        return tr("Waiting");
    case STOPPED:
        return tr("STOPPED");
    default:
        return tr("");
    }
}
