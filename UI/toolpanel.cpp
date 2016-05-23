#include<UI/toolpanel.h>

Panel::Panel(QWidget* parent, SpectrographDevice& device, 
    ResourceManager& manager) : QFrame(parent),
    m_device(device), m_manager(manager)
{
    
}

Panel::~Panel()
{
    
}

void Panel::closeEvent(QCloseEvent *event)
{
    emit closed();
}
