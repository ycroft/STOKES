#include<UI/graphicspanel.h>

static const char* ICON_DEL = "/home/ycroft/Pictures/stokes/del.gif";

using namespace std;

GraphicsPanel::GraphicsPanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager)
    : Panel(parent, device, manager)
{
    m_main_layout = new QGridLayout(this);
    this->setLayout(m_main_layout);
    for(int i = 0; i < ResourceManager::DATA_NUM; ++ i)
    {
        m_stream_list[i] = -1;
    }
    
    label_title = new QLabel(tr("Datagrams on canvas:"),this);
    list_names = new QListWidget(this);
    
    QPushButton* button_preset = new QPushButton(tr("Preset"),this); 
    QPushButton* button_add = new QPushButton(tr("Add"),this);
    QPushButton* button_clear = new QPushButton(tr("Clear all"), this);
    QPushButton* button_del = new QPushButton(QIcon(ICON_DEL),QString(""));
    
    m_main_layout->addWidget(label_title,0,0,1,2);
    m_main_layout->addWidget(button_del,0,2,1,1,Qt::AlignRight);
    m_main_layout->addWidget(list_names,1,0,1,3);
    m_main_layout->addWidget(button_preset,2,0,1,1);
    m_main_layout->addWidget(button_add,2,1,1,1);
    m_main_layout->addWidget(button_clear,2,2,1,1);
    
    connect(button_preset,SIGNAL(clicked()),this,SLOT(__ChoosePreset()));
    connect(button_clear,SIGNAL(clicked()),this,SLOT(__ClearList()));
    connect(button_clear,SIGNAL(clicked()),this,SIGNAL(ClearCurves()));
    connect(button_del,SIGNAL(clicked()),this,SLOT(__RemoveCurve()));
}

void GraphicsPanel::__RemoveCurve()
{
    int dataId = -1;
    int row = list_names->currentRow();
    for(int i = 0; i < ResourceManager::DATA_NUM; ++ i)
    {
        if(m_stream_list[i] == row){
            dataId = i;
            break;
        }
    }
    if(dataId == -1)
    {
        return;
    }
    list_names->removeItemWidget(list_names->item(row));
    delete list_names->item(row);
    emit DelCurve((ResourceManager::DataName)dataId);
}

void GraphicsPanel::__ChoosePreset()
{
    PresetChooser* chooser = new PresetChooser(this);
    chooser->show();
    connect(chooser,SIGNAL(SendCurve(ResourceManager::DataName)),this,SIGNAL(AddCurve(ResourceManager::DataName)));
    connect(chooser,SIGNAL(SendCurve(ResourceManager::DataName)),this,SLOT(__AddToList(ResourceManager::DataName)));
}

void GraphicsPanel::__AddToList(ResourceManager::DataName name)
{
    if(-1 == m_stream_list[name])
    {
        list_names->addItem(new QListWidgetItem(m_manager.GetStreamName(name)));
        m_stream_list[name] = list_names->count() - 1;
    }
}

void GraphicsPanel::__ClearList()
{
    int l = list_names->count();
    for(int i = 0; i < l; ++ i)
    {
        list_names->removeItemWidget(list_names->item(0));
        delete list_names->item(0);
    }
    for(int i = 0; i < ResourceManager::DATA_NUM; ++ i)
    {
        m_stream_list[i] = -1;
    }
}

GraphicsPanel::~GraphicsPanel()
{
    
}

PresetChooser::PresetChooser(QWidget* parent) : QDialog(parent)
{
    main_layout = new QGridLayout(this);
    list_names = new QListWidget(this);
    title = new QLabel(tr("Preset Datagrams:"));
    button_add = new QPushButton(tr("Add"), this);
    button_cancel = new QPushButton(tr("Cancel"), this);
    
    item_modulated_RLS = new QListWidgetItem(tr("modulated_RLS"),list_names);
    item_untreated_RLS = new QListWidgetItem(tr("untreated_RLS"),list_names);
    item_measured_LS = new QListWidgetItem(tr("measured_LS"),list_names);
    item_RLS_autocorrelation_function = new QListWidgetItem(tr("RLS_autocorrelation_function"),list_names);
    item_RLS_AF_ch0 = new QListWidgetItem(tr("RLS_AF_ch0"),list_names);
    item_RLS_AF_ch1 = new QListWidgetItem(tr("RLS_AF_ch1"),list_names);
    item_RLS_AF_ch2 = new QListWidgetItem(tr("RLS_AF_ch2"),list_names);
    item_RLS_AF_ch3 = new QListWidgetItem(tr("RLS_AF_ch3"),list_names);
    item_RLS_ch0 = new QListWidgetItem(tr("RLS_ch0"),list_names);
    item_RLS_ch1 = new QListWidgetItem(tr("RLS_ch1"),list_names);
    item_RLS_ch2 = new QListWidgetItem(tr("RLS_ch2"),list_names);
    item_RLS_ch3 = new QListWidgetItem(tr("RLS_ch3"),list_names);
    item_modulation_factor_0 = new QListWidgetItem(tr("modulation_factor_0"),list_names);
    item_modulation_factor_1 = new QListWidgetItem(tr("modulation_factor_1"),list_names);
    item_modulation_factor_2 = new QListWidgetItem(tr("modulation_factor_2"),list_names);
    item_modulation_factor_3 = new QListWidgetItem(tr("modulation_factor_3"),list_names);
    item_MLS_autocorrelation_function = new QListWidgetItem(tr("MLS_autocorrelation_function"),list_names);
    item_MLS_AF_ch0 = new QListWidgetItem(tr("MLS_AF_ch0"),list_names);
    item_MLS_AF_ch1 = new QListWidgetItem(tr("MLS_AF_ch1"),list_names);
    item_MLS_AF_ch2 = new QListWidgetItem(tr("MLS_AF_ch2"),list_names);
    item_MLS_AF_ch3 = new QListWidgetItem(tr("MLS_AF_ch3"),list_names);
    item_MLS_ch0 = new QListWidgetItem(tr("MLS_ch0"),list_names);
    item_MLS_ch1 = new QListWidgetItem(tr("MLS_ch1"),list_names);
    item_MLS_ch2 = new QListWidgetItem(tr("MLS_ch2"),list_names);
    item_MLS_ch3 = new QListWidgetItem(tr("MLS_ch3"),list_names);
    item_modification_factor_phi1 = new QListWidgetItem(tr("modification_factor_phi1"),list_names);
    item_modification_factor_phi2 = new QListWidgetItem(tr("modification_factor_phi2"),list_names);
    item_stokes_vector_0 = new QListWidgetItem(tr("stokes_vector_0"),list_names);
    item_stokes_vector_1 = new QListWidgetItem(tr("stokes_vector_1"),list_names);
    item_stokes_vector_2 = new QListWidgetItem(tr("stokes_vector_2"),list_names);
    item_stokes_vector_3 = new QListWidgetItem(tr("stokes_vector_3"),list_names);
    item_DOP = new QListWidgetItem(tr("DOP"),list_names);
    
    main_layout->addWidget(title,0,0,1,3);
    main_layout->addWidget(list_names,1,0,1,3);
    main_layout->addWidget(button_add,2,1,1,1);
    main_layout->addWidget(button_cancel,2,2,1,1);
    
    connect(button_cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(button_add,SIGNAL(clicked()),this,SLOT(__SelectCurve()));
}

void PresetChooser::__SelectCurve()
{
    emit SendCurve((ResourceManager::DataName)list_names->currentRow());
    this->close();
}
