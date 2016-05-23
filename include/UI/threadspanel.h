#ifndef THREADSPANEL_H
#define THREADSPANEL_H

#include<UI/toolpanel.h>

class ThreadsPanel : public Panel
{
    Q_OBJECT
public:
    public:
    ThreadsPanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager);
    virtual ~ThreadsPanel();
private:
    QGridLayout* m_main_layout;
    QRadioButton* radio_write_enable;
    QRadioButton* radio_write_disable;
    QRadioButton* radio_calc_MF_enable;
    QRadioButton* radio_calc_MF_disable;
    QRadioButton* radio_switcher_MLS;
    QRadioButton* radio_switcher_MRLS;
    QRadioButton* radio_switcher_URLS;
    QPushButton* button_start;
    QPushButton* button_stop;
public slots:
    void __Toggle_Write(bool);
    void __Toggle_MF(bool);
    void __Select_MLS(bool);
    void __Select_MRLS(bool);
    void __Select_URLS(bool);
    void __StartAll();
    void __StopAll();
};

#endif // THREADSPANEL_H