#ifndef INFOPANEL_H
#define INFOPANEL_H

#include<UI/toolpanel.h>

#define INFO_RENEW_CLOCK 1000

class InfoPanel : public Panel
{
    Q_OBJECT
public:
    InfoPanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager);
    virtual ~InfoPanel();
private:
    QGridLayout* m_main_layout;
    QLabel* m_title_name;
    QLabel* m_title_status;
    QLabel* m_name_machine_type;
    QLabel* m_name_machine;
    QLabel* m_name_write;
    QLabel* m_name_fetch;
    QLabel* m_name_MF;
    QLabel* m_name_SV;
    QLabel* m_name_ADDI;
    QLabel* m_name_repaint;
    QLabel* m_status_machine_type;
    QLabel* m_status_machine;
    QLabel* m_status_write;
    QLabel* m_status_fetch;
    QLabel* m_status_MF;
    QLabel* m_status_SV;
    QLabel* m_status_ADDI;
    QLabel* m_status_repaint;
    
    QFrame* m_line;

    bool m_runnable;
    void __Renew();
    QString __GetStateName(int s);
};

#endif // INFOPANEL_H
