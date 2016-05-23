#ifndef ANALYSEPANEL_H
#define ANALYSEPANEL_H

#include<UI/toolpanel.h>

class AnalysePanel : public Panel
{
    Q_OBJECT
public:
    public:
    AnalysePanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager);
    virtual ~AnalysePanel();
private:
    QGridLayout* m_main_layout;
};

#endif // ANALYSEPANEL_H