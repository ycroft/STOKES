#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include<DataCollection/spectrograph.h>
#include<Universal/innerdata.h>
#include<DataProcessing/processor.h>
#include<boost/thread.hpp>
#include<string>

#include<qwt_series_data.h>

#include<QtCore/QPointF>
#include<QtCore/QString>
#include<QtCore/QObject>
#include<QtCore/QVector>

#define RUNNING 1
#define WAITING 0
#define STOPPED -1
#define WORK_MILI_CLOCK 50
#define SLEEP_MILI_CLOCK 100

static const char* FNAME_MRLS = "mrls.out";
static const char* FNAME_URLS = "urls.out";
static const char* FNAME_MLS = "mls.out";
static const char* FNAME_RLS_AF = "rls_af.out";
static const char* FNAME_RLS_AF_CH_0 = "rls_af_ch_0.out";
static const char* FNAME_RLS_AF_CH_1 = "rls_af_ch_1.out";
static const char* FNAME_RLS_AF_CH_2 = "rls_af_ch_2.out";
static const char* FNAME_RLS_AF_CH_3 = "rls_af_ch_3.out";
static const char* FNAME_RLS_CH_0 = "rls_ch_0.out";
static const char* FNAME_RLS_CH_1 = "rls_ch_1.out";
static const char* FNAME_RLS_CH_2 = "rls_ch_2.out";
static const char* FNAME_RLS_CH_3 = "rls_ch_3.out";
static const char* FNAME_MF_0 = "mf_0.out";
static const char* FNAME_MF_1 = "mf_1.out";
static const char* FNAME_MF_2 = "mf_2.out";
static const char* FNAME_MF_3 = "mf_3.out";

static const char* FNAME_MLS_AF = "mls_af.out";
static const char* FNAME_MLS_AF_CH_0 = "mls_af_ch_0.out";
static const char* FNAME_MLS_AF_CH_1 = "mls_af_ch_1.out";
static const char* FNAME_MLS_AF_CH_2 = "mls_af_ch_2.out";
static const char* FNAME_MLS_AF_CH_3 = "mls_af_ch_3.out";
static const char* FNAME_MLS_CH_0 = "mls_ch_0.out";
static const char* FNAME_MLS_CH_1 = "mls_ch_1.out";
static const char* FNAME_MLS_CH_2 = "mls_ch_2.out";
static const char* FNAME_MLS_CH_3 = "mls_ch_3.out";

static const char* FNAME_SV_0 = "stokes_vector_0.out";
static const char* FNAME_SV_1 = "stokes_vector_1.out";
static const char* FNAME_SV_2 = "stokes_vector_2.out";
static const char* FNAME_SV_3 = "stokes_vector_3.out";

static const char* FNAME_DOP = "dop.out";

static const char* FILE_START_FLAG = "SOF\n";
static const char* FILE_END_FLAG = "EOF";
static const char* FILE_DATA_SPLIT = "\t";

typedef struct config
{
    int _read_stream_type;  // [!]
    bool _enable_write;
    bool _enable_calc_MF;
} Configuration;

typedef struct states
{
    int _fetch_state;
    int _calc_MF_state;
    int _calc_SV_state;
    int _calc_AD_state;
    int _write_state;
} States;

class ResourceManager
{
public:
    enum DataName{
        MRLS,URLS,MLS,RLS_AF,RLS_AF_CH_0,RLS_AF_CH_1,RLS_AF_CH_2,
        RLS_AF_CH_3,RLS_CH_0,RLS_CH_1,RLS_CH_2,RLS_CH_3,MF_0,MF_1,
        MF_2,MF_3,MLS_AF,MLS_AF_CH_0,MLS_AF_CH_1,MLS_AF_CH_2,
        MLS_AF_CH_3,MLS_CH_0,MLS_CH_1,MLS_CH_2,MLS_CH_3,MF_PHI_1,
        MF_PHI_2,SV_0,SV_1,SV_2,SV_3,DOP,DATA_NUM
    };
    ResourceManager(SpectrographDevice& device);
    virtual ~ResourceManager();
    void Start();
    void Stop();
    void Restart();
    void WriteToFile();
    States GetStates(){ return m_states; }
    int GetInstructor(){ return m_instructor; }
    void SetReadStreamType(int type){
        m_config._read_stream_type = type;
        boost::this_thread::sleep(boost::posix_time::millisec(SLEEP_MILI_CLOCK));
    }
    void GetPointSeriesData(QwtPointSeriesData* seriesData, DataName name, double* range=NULL);
    void EnableWrite(bool);
    void EnableCalcMF(bool);
    QString GetStreamName(DataName);
private:
    States m_states;
    bool m_runnable;
    unsigned int m_instructor;
    Configuration m_config;
    QString m_stream_names[DATA_NUM];
    void __Thread_WriteData();
    void __Thread_FetchData();
    void __Thread_Calc_MF();
    void __Thread_Calc_SV();
    void __Thread_Calc_Additional();
    void __WriteData(InnerData& data, std::string fname);
    SpectrographDevice &m_device;
    
    std::vector<int> m_peak_positions;
    InnerData m_modulated_RLS;
    InnerData m_untreated_RLS;
    InnerData m_measured_LS;
    InnerData m_RLS_autocorrelation_function;
    std::vector<double> m_RLS_AF_feature;
    InnerData m_RLS_AF_ch0;
    InnerData m_RLS_AF_ch1;
    InnerData m_RLS_AF_ch2;
    InnerData m_RLS_AF_ch3;
    InnerData m_RLS_ch0;
    InnerData m_RLS_ch1;
    InnerData m_RLS_ch2;
    InnerData m_RLS_ch3;
    InnerData m_modulation_factor_0;
    InnerData m_modulation_factor_1;
    InnerData m_modulation_factor_2;
    InnerData m_modulation_factor_3;
    
    InnerData m_MLS_autocorrelation_function;
    std::vector<double> m_MLS_AF_feature;
    InnerData m_MLS_AF_ch0;
    InnerData m_MLS_AF_ch1;
    InnerData m_MLS_AF_ch2;
    InnerData m_MLS_AF_ch3;
    InnerData m_MLS_ch0;
    InnerData m_MLS_ch1;
    InnerData m_MLS_ch2;
    InnerData m_MLS_ch3;
    
    InnerData m_modification_factor_phi1;
    InnerData m_modification_factor_phi2;
    
    InnerData m_stokes_vector_0;
    InnerData m_stokes_vector_1;
    InnerData m_stokes_vector_2;
    InnerData m_stokes_vector_3;
    
    InnerData m_DOP;
};

#endif // OBJMANAGER_H
