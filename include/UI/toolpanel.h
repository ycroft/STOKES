#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include<DataCollection/objmanager.h>
#include<DataCollection/spectrograph.h>
#include<QtGui/QWidget>
#include<QtGui/QDialog>
#include<QtGui/QGridLayout>
#include<QtGui/QLabel>
#include<QtGui/QVBoxLayout>
#include<QtGui/QFrame>
#include<QtGui/QListWidget>
#include<QtGui/QTextEdit>
#include<QtGui/QListWidgetItem>
#include<QtGui/QRadioButton>
#include<QtGui/QPushButton>
#include<QtGui/QButtonGroup>
#include<QtGui/QCloseEvent>
#include<QtCore/QObject>
#include<QtCore/QString>

#define WIDTH_LEFT_PANEL 300

#define POS_X_INFO 0
#define POS_Y_INFO 0
#define HEIGHT_INFO 300

#define POS_X_GRAPHICS 0
#define POS_Y_GRAPHICS 300
#define HEIGHT_GRAPHICS 300

#define POS_X_THREADS 0
#define POS_Y_THREADS 720
#define HEIGHT_THREADS 180

#define POS_X_ANALYSE 300
#define POS_Y_ANALYSE 720
#define WIDTH_ANALYSE 1300
#define HEIGHT_ANALYSE 180

class Panel : public QFrame
{
    Q_OBJECT
public:
    enum PanelName
    {
        INFO,GRAPHICS,THREADS,ANALYSE,PANELNAME_NUM
    };
    Panel(QWidget* parent, SpectrographDevice& device, ResourceManager& manager);
    virtual ~Panel() = 0;
protected:
    SpectrographDevice& m_device;
    ResourceManager& m_manager;
    void closeEvent(QCloseEvent *event); 
signals:
    void closed();
};

#endif // TOOLPANEL_H