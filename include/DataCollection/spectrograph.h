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

typedef struct deviceinfo
{
    std::string work_directory;
} DeviceInfo;

class SpectrographDevice
{
public:
    SpectrographDevice();
    virtual ~SpectrographDevice();
    virtual bool Boot() = 0;
    virtual bool Shutdown() = 0;
    virtual bool Reboot() = 0;
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