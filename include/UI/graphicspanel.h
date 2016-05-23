#ifndef GRAPHICSPANEL_H
#define GRAPHICSPANEL_H

#include<UI/toolpanel.h>

class GraphicsPanel : public Panel
{
    Q_OBJECT
public:
    public:
    GraphicsPanel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager);
    virtual ~GraphicsPanel();
private:
    QGridLayout* m_main_layout;
    QLabel* label_title;
    QListWidget* list_names;
    int m_stream_list[ResourceManager::DATA_NUM];
private slots:
    void __ChoosePreset();
    void __AddToList(ResourceManager::DataName);
    void __ClearList();
    void __RemoveCurve();
signals:
    void AddCurve(ResourceManager::DataName);
    void DelCurve(ResourceManager::DataName);
    void ClearCurves();
};

class PresetChooser : public QDialog
{
    Q_OBJECT
public:
    PresetChooser(QWidget* parent);
private:
    QGridLayout* main_layout;
    QListWidget* list_names;
    QLabel* title;
    QPushButton* button_add;
    QPushButton* button_cancel;
    QListWidgetItem* item_modulated_RLS;
    QListWidgetItem* item_untreated_RLS;
    QListWidgetItem* item_measured_LS;
    QListWidgetItem* item_RLS_autocorrelation_function;
    QListWidgetItem* item_RLS_AF_ch0;
    QListWidgetItem* item_RLS_AF_ch1;
    QListWidgetItem* item_RLS_AF_ch2;
    QListWidgetItem* item_RLS_AF_ch3;
    QListWidgetItem* item_RLS_ch0;
    QListWidgetItem* item_RLS_ch1;
    QListWidgetItem* item_RLS_ch2;
    QListWidgetItem* item_RLS_ch3;
    QListWidgetItem* item_modulation_factor_0;
    QListWidgetItem* item_modulation_factor_1;
    QListWidgetItem* item_modulation_factor_2;
    QListWidgetItem* item_modulation_factor_3;
    QListWidgetItem* item_MLS_autocorrelation_function;
    QListWidgetItem* item_MLS_AF_ch0;
    QListWidgetItem* item_MLS_AF_ch1;
    QListWidgetItem* item_MLS_AF_ch2;
    QListWidgetItem* item_MLS_AF_ch3;
    QListWidgetItem* item_MLS_ch0;
    QListWidgetItem* item_MLS_ch1;
    QListWidgetItem* item_MLS_ch2;
    QListWidgetItem* item_MLS_ch3;
    QListWidgetItem* item_modification_factor_phi1;
    QListWidgetItem* item_modification_factor_phi2;
    QListWidgetItem* item_stokes_vector_0;
    QListWidgetItem* item_stokes_vector_1;
    QListWidgetItem* item_stokes_vector_2;
    QListWidgetItem* item_stokes_vector_3;
    QListWidgetItem* item_DOP;
private slots:
    void __SelectCurve();
signals:
    void SendCurve(ResourceManager::DataName);
};

#endif // GRAPHICSPANEL_H