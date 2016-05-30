#ifndef SPECTROGRAPH_H
#define SPECTROGRAPH_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream> // [!]****
#include<Universal/innerdata.h>
#include<Universal/math.h>


#define SUCCESS true
#define FAIL false

#define STREAM_MLS 0
#define STREAM_MRLS 1
#define STREAM_URLS 2
#define SPLINE_POINT_NUM 2048

static const char SYS_SEPERATOR = '/';
static const unsigned int LINE_BUF_SIZE = 256;

static const char* FNAME_INPUT_MRLS = "mrls.in";
static const char* FNAME_INPUT_URLS = "urls.in";
static const char* FNAME_INPUT_MLS = "mls.in";

#define ON 1
#define OFF 0

/**
 * ###设备信息
 * 是所有设备种类的设备信息集合<br>
 * 包括实机和虚机的全部信息，不包括仪器状态。
 */
typedef struct deviceinfo
{
    std::string work_directory;
} DeviceInfo;

/**
 * ###光谱仪类型
 * 所有类型的光谱仪的抽象父类，拥有所有光谱仪的公共属性和功
 * 能，光谱仪类型的所有子类都存在状态变量用于记录光谱仪的当
 * 前状态，如运行、休眠、等。<br>
 * 设计该类型的初衷是让程序既支持以文件方式输入也支持直接从
 * 光谱仪获取数据。为了使架构统一，对输入方式用“设备”的概念
 * 进行封装，其中来自文件的原始输入为“虚拟机”，来自光谱仪的
 * 输入为“实机”。
 */
class SpectrographDevice
{
public:
    SpectrographDevice();
    virtual ~SpectrographDevice();
    /**
     * ###启动函数
     * 检查当前设备状态，如果为正常关机状态则启动机器
     * @see VisualMachine::Boot
     */
    virtual bool Boot() = 0;
    /**
     * ###关机函数
     * 检查当前设备状态，如果为正常运行状态则关闭机器
     * @see VisualMachine::Shutdown
     */
    virtual bool Shutdown() = 0;
    /**
     * ###重启函数
     * 检查当前设备状态并重新启动，解决当前设备遇到的问题
     * @see VisualMachine::Reboot
     */
    virtual bool Reboot() = 0;
    /**
     * ###得到当前设备状态
     * 目前光谱仪状态只有两种：<br>
     * + 开启状态-ON
     * + 关闭状态-OFF
     */
    virtual int GetState() = 0;
    virtual DeviceInfo GetDeviceInfo() = 0;
    virtual bool ReadDatagram(InnerData& innerData,int type = STREAM_MLS) = 0;
    int device_type_id;
};

class VisualMachine:public SpectrographDevice
{
public:
    VisualMachine(std::string dir);
    ~VisualMachine();
    bool Boot();
    bool Shutdown();
    bool Reboot();
    bool ReadDatagram(InnerData& innerData,int type = STREAM_MLS);
    int GetState(){ return m_state; }
    DeviceInfo GetDeviceInfo(){
        DeviceInfo dinfo;
        dinfo.work_directory = m_work_directory;
        return dinfo;
    }
private:
    int m_state;
    std::string m_work_directory;
    std::ifstream m_modulated_RLS;
    std::ifstream m_untreated_RLS;
    std::ifstream m_measured_LS;
    void __RenewBuffer();
    void __ReadBuffer(std::stringstream& buf, std::vector<double>& xaxis, std::vector<double>& yaxis);
};

#endif //SPECTROGRAPH_H
