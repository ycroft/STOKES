#include<UI/analysepanel.h>

AnalysePanel::AnalysePanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager)
    : Panel(parent, device, manager)
{
    // this->setWindowTitle(tr("Analyse"));
    m_main_layout = new QGridLayout(this);
    this->setLayout(m_main_layout);
    // this->setGeometry(POS_X_ANALYSE,POS_Y_ANALYSE,WIDTH_ANALYSE, HEIGHT_ANALYSE);
    
    QLabel* title = new QLabel(tr("Features of the datagrams painted:"),this);
    QTextEdit* text_area = new QTextEdit(this);
    m_main_layout->addWidget(title,0,0,1,3);
    m_main_layout->addWidget(text_area,1,0,1,3);
}

AnalysePanel::~AnalysePanel()
{
    
}
