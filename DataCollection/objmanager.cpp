#include<DataCollection/objmanager.h>

using namespace std;

ResourceManager::ResourceManager(SpectrographDevice& device):m_device(device)
{
    m_runnable = false;
    m_instructor = 0;
    
    m_states._fetch_state = STOPPED;
    m_states._calc_MF_state = STOPPED;
    m_states._calc_SV_state = STOPPED;
    m_states._write_state = STOPPED;
    
    m_config._read_stream_type = STREAM_MLS;
    m_config._enable_write = true;
    m_config._enable_calc_MF = true;
    
    m_stream_names[0] = QObject::tr("modulated_RLS");
    m_stream_names[1] = QObject::tr("untreated_RLS");
    m_stream_names[2] = QObject::tr("measured_LS");
    m_stream_names[3] = QObject::tr("RLS_autocorrelation_function");
    m_stream_names[4] = QObject::tr("RLS_AF_ch0");
    m_stream_names[5] = QObject::tr("RLS_AF_ch1");
    m_stream_names[6] = QObject::tr("RLS_AF_ch2");
    m_stream_names[7] = QObject::tr("RLS_AF_ch3");
    m_stream_names[8] = QObject::tr("RLS_ch0");
    m_stream_names[9] = QObject::tr("RLS_ch1");
    m_stream_names[10] = QObject::tr("RLS_ch2");
    m_stream_names[11] = QObject::tr("RLS_ch3");
    m_stream_names[12] = QObject::tr("modulation_factor_0");
    m_stream_names[13] = QObject::tr("modulation_factor_1");
    m_stream_names[14] = QObject::tr("modulation_factor_2");
    m_stream_names[15] = QObject::tr("modulation_factor_3");
    m_stream_names[16] = QObject::tr("MLS_autocorrelation_function");
    m_stream_names[17] = QObject::tr("MLS_AF_ch0");
    m_stream_names[18] = QObject::tr("MLS_AF_ch1");
    m_stream_names[19] = QObject::tr("MLS_AF_ch2");
    m_stream_names[20] = QObject::tr("MLS_AF_ch3");
    m_stream_names[21] = QObject::tr("MLS_ch0");
    m_stream_names[22] = QObject::tr("MLS_ch1");
    m_stream_names[23] = QObject::tr("MLS_ch2");
    m_stream_names[24] = QObject::tr("MLS_ch3");
    m_stream_names[25] = QObject::tr("modification_factor_phi1");
    m_stream_names[26] = QObject::tr("modification_factor_phi2");
    m_stream_names[27] = QObject::tr("stokes_vector_0");
    m_stream_names[28] = QObject::tr("stokes_vector_1");
    m_stream_names[29] = QObject::tr("stokes_vector_2");
    m_stream_names[30] = QObject::tr("stokes_vector_3");
    m_stream_names[31] = QObject::tr("DOP");
}

ResourceManager::~ResourceManager()
{
    Stop();
    // TODO:
}

void ResourceManager::Start()
{
    if(m_states._fetch_state == STOPPED)
    {
        m_runnable = true;
        boost::thread fetch_thread(boost::bind(&ResourceManager::__Thread_FetchData,this));
        boost::thread calc_MF_thread(boost::bind(&ResourceManager::__Thread_Calc_MF,this));
        boost::thread calc_SV_thread(boost::bind(&ResourceManager::__Thread_Calc_SV,this));
        boost::thread calc_AD_thread(boost::bind(&ResourceManager::__Thread_Calc_Additional,this));
        boost::thread write_thread(boost::bind(&ResourceManager::__Thread_WriteData,this));
        boost::this_thread::sleep(boost::posix_time::millisec(SLEEP_MILI_CLOCK));
    }
}

void ResourceManager::Stop()
{
    // [!] need to wait for stopping...
    m_runnable = false;
    boost::this_thread::sleep(boost::posix_time::millisec(SLEEP_MILI_CLOCK));        
}

void ResourceManager::Restart()
{
    Stop();
    Start();
}

void ResourceManager::WriteToFile()
{
    __WriteData(m_modulated_RLS, FNAME_MRLS);
    __WriteData(m_untreated_RLS, FNAME_URLS);
    __WriteData(m_RLS_autocorrelation_function, FNAME_RLS_AF);
    __WriteData(m_RLS_AF_ch0, FNAME_RLS_AF_CH_0);
    __WriteData(m_RLS_AF_ch1, FNAME_RLS_AF_CH_1);
    __WriteData(m_RLS_AF_ch2, FNAME_RLS_AF_CH_2);
    __WriteData(m_RLS_AF_ch3, FNAME_RLS_AF_CH_3);
    __WriteData(m_RLS_ch0, FNAME_RLS_CH_0);
    __WriteData(m_RLS_ch1, FNAME_RLS_CH_1);
    __WriteData(m_RLS_ch2, FNAME_RLS_CH_2);
    __WriteData(m_RLS_ch3, FNAME_RLS_CH_3);
    __WriteData(m_modulation_factor_0, FNAME_MF_0);
    __WriteData(m_modulation_factor_1, FNAME_MF_1);
    __WriteData(m_modulation_factor_2, FNAME_MF_2);
    __WriteData(m_modulation_factor_3, FNAME_MF_3);
    
    __WriteData(m_measured_LS, FNAME_MLS);
    __WriteData(m_MLS_autocorrelation_function, FNAME_MLS_AF);
    __WriteData(m_MLS_AF_ch0, FNAME_MLS_AF_CH_0);
    __WriteData(m_MLS_AF_ch1, FNAME_MLS_AF_CH_1);
    __WriteData(m_MLS_AF_ch2, FNAME_MLS_AF_CH_2);
    __WriteData(m_MLS_AF_ch3, FNAME_MLS_AF_CH_3);
    __WriteData(m_MLS_ch0, FNAME_MLS_CH_0);
    __WriteData(m_MLS_ch1, FNAME_MLS_CH_1);
    __WriteData(m_MLS_ch2, FNAME_MLS_CH_2);
    __WriteData(m_MLS_ch3, FNAME_MLS_CH_3);
    
    __WriteData(m_stokes_vector_0, FNAME_SV_0);
    __WriteData(m_stokes_vector_1, FNAME_SV_1);
    __WriteData(m_stokes_vector_2, FNAME_SV_2);
    __WriteData(m_stokes_vector_3, FNAME_SV_3);
    
    __WriteData(m_DOP, FNAME_DOP);
}
void ResourceManager::GetPointSeriesData(QwtPointSeriesData* seriesData, DataName name, double* range)
{
    QVector<QPointF> points;
    InnerData* data;
    switch(name)
    {
    case MRLS: data = &m_modulated_RLS; break;
    case URLS: data = &m_untreated_RLS; break;
    case MLS: data = &m_measured_LS; break;
    case RLS_AF: data = &m_RLS_autocorrelation_function; break;
    case RLS_AF_CH_0: data = &m_RLS_AF_ch0; break;
    case RLS_AF_CH_1: data = &m_RLS_AF_ch1; break;
    case RLS_AF_CH_2: data = &m_RLS_AF_ch2; break;
    case RLS_AF_CH_3: data = &m_RLS_AF_ch3; break;
    case RLS_CH_0: data = &m_RLS_ch0; break;
    case RLS_CH_1: data = &m_RLS_ch1; break;
    case RLS_CH_2: data = &m_RLS_ch2; break;
    case RLS_CH_3: data = &m_RLS_ch3; break;
    case MF_0: data = &m_modulation_factor_0; break;
    case MF_1: data = &m_modulation_factor_1; break;
    case MF_2: data = &m_modulation_factor_2; break;
    case MF_3: data = &m_modulation_factor_3; break;
    case MLS_AF: data = &m_MLS_autocorrelation_function; break;
    case MLS_AF_CH_0: data = &m_MLS_AF_ch0; break;
    case MLS_AF_CH_1: data = &m_MLS_AF_ch1; break;
    case MLS_AF_CH_2: data = &m_MLS_AF_ch2; break;
    case MLS_AF_CH_3: data = &m_MLS_AF_ch3; break;
    case MLS_CH_0: data = &m_MLS_ch0; break;
    case MLS_CH_1: data = &m_MLS_ch1; break;
    case MLS_CH_2: data = &m_MLS_ch2; break;
    case MLS_CH_3: data = &m_MLS_ch3; break;
    case MF_PHI_1: data = &m_modification_factor_phi1; break;
    case MF_PHI_2: data = &m_modification_factor_phi2; break;
    case SV_0: data = &m_stokes_vector_0; break;
    case SV_1: data = &m_stokes_vector_1; break;
    case SV_2: data = &m_stokes_vector_2; break;
    case SV_3: data = &m_stokes_vector_3; break;
    case DOP: data = &m_DOP; break;
    default: return; // [!]
    }
    if(data->empty())
    {
        return;
    }
    vector<Complex>& x = data->GetControlX(); 
    vector<Complex>& y = data->GetControlY();
    if(NULL == range)
    {
        for(int i = 0; i < x.size(); ++ i)
        {
            points.append(QPointF(x[i].real(),y[i].real()));
        }
    }
    else
    {
        
    }
    seriesData->setSamples(points);
}

void ResourceManager::EnableWrite(bool flag)
{
    m_config._enable_write = flag;
}

void ResourceManager::EnableCalcMF(bool flag)
{
    m_config._enable_calc_MF = flag;
}

QString ResourceManager::GetStreamName(DataName name)
{
    return m_stream_names[name];
}

void ResourceManager::__Thread_Calc_MF()
{
    while(m_runnable)
    {
        if((!m_config._enable_calc_MF) || m_modulated_RLS.empty() || m_untreated_RLS.empty())
        {
            m_states._calc_MF_state = WAITING;
        }
        else{
            m_states._calc_MF_state = RUNNING;
            proc::CalcAF(m_RLS_autocorrelation_function, m_RLS_AF_feature, m_modulated_RLS);
            proc::RecognizeAF(m_RLS_autocorrelation_function, m_RLS_AF_feature, m_peak_positions);
            proc::SeparateAF(m_RLS_autocorrelation_function, m_peak_positions, m_RLS_AF_ch0, m_RLS_AF_ch1, m_RLS_AF_ch2, m_RLS_AF_ch3);
            proc::RecoverRLS_MF(m_untreated_RLS,m_RLS_AF_ch0,m_RLS_AF_ch1,m_RLS_AF_ch2,m_RLS_AF_ch3,
                m_RLS_ch0,m_RLS_ch1,m_RLS_ch2,m_RLS_ch3,
                m_modulation_factor_0,m_modulation_factor_1,m_modulation_factor_2,m_modulation_factor_3);
        }
        boost::this_thread::sleep(boost::posix_time::millisec(WORK_MILI_CLOCK));
    }
    m_states._calc_MF_state = STOPPED;
}

void ResourceManager::__Thread_Calc_SV()
{
    while(m_runnable)
    {
        if(m_modulation_factor_0.empty() || m_measured_LS.empty() || m_peak_positions.empty())
        {
            m_states._calc_SV_state = WAITING;
        }
        else
        {
            m_states._calc_SV_state = RUNNING;
            proc::CalcAF(m_MLS_autocorrelation_function, m_MLS_AF_feature, m_measured_LS);
            proc::SeparateAF(m_MLS_autocorrelation_function, m_peak_positions, m_MLS_AF_ch0, m_MLS_AF_ch1, m_MLS_AF_ch2, m_MLS_AF_ch3);
            proc::RecoverMLS_SV(m_MLS_AF_ch0,m_MLS_AF_ch1,m_MLS_AF_ch2,m_MLS_AF_ch3,
                m_MLS_ch0,m_MLS_ch1,m_MLS_ch2,m_MLS_ch3,
                m_modulation_factor_0,m_modulation_factor_1,m_modulation_factor_2,m_modulation_factor_3,
                m_stokes_vector_0,m_stokes_vector_1,m_stokes_vector_2,m_stokes_vector_3);
        }
        boost::this_thread::sleep(boost::posix_time::millisec(WORK_MILI_CLOCK));        
    }
    m_states._calc_SV_state = STOPPED;
}

void ResourceManager::__Thread_FetchData()
{
    int type;
    while(m_runnable)
    {
        if(m_device.GetState() == OFF)
        {
            m_states._fetch_state = WAITING;
        }
        else
        {
            type = m_config._read_stream_type;
            ++ m_instructor;
            m_states._fetch_state = RUNNING;
            switch(type)
            {
            case STREAM_MLS:
                m_device.ReadDatagram(m_measured_LS,type);
                break;
            case STREAM_MRLS:
                m_device.ReadDatagram(m_modulated_RLS,type);
                break;
            case STREAM_URLS:
                m_device.ReadDatagram(m_untreated_RLS,type);
                break;
            default:
                break;
            }
        }
        boost::this_thread::sleep(boost::posix_time::millisec(WORK_MILI_CLOCK));
    }
    m_states._fetch_state = STOPPED;
}

void ResourceManager::__Thread_WriteData()
{
    while(m_runnable)
    {
        if(m_config._enable_write)
        {
            m_states._write_state = RUNNING;
            WriteToFile();
        }
        m_states._write_state = WAITING;
        boost::this_thread::sleep(boost::posix_time::millisec(WORK_MILI_CLOCK));
    }
    m_states._write_state = STOPPED;
}

void ResourceManager::__Thread_Calc_Additional()
{
    while(m_runnable)
    {
        if(m_stokes_vector_0.empty())
        {
            m_states._calc_AD_state = WAITING;
        }
        else
        {
            m_states._calc_AD_state = RUNNING;
            proc::CalcDOP(m_DOP,m_stokes_vector_0,m_stokes_vector_1,m_stokes_vector_2,m_stokes_vector_3);
        }
        boost::this_thread::sleep(boost::posix_time::millisec(WORK_MILI_CLOCK));
    }
    m_states._calc_AD_state = STOPPED;
}

void ResourceManager::__WriteData(InnerData& data, string fname)
{
    fname = m_device.GetDeviceInfo().work_directory + fname;
    ofstream out(fname.c_str());
    if(!out.is_open())
    {
        return; // [!]
    }
    vector<Complex>& x = data.GetControlX();
    vector<Complex>& y = data.GetControlY();
    
    out << FILE_START_FLAG;
    for(int i = 0; i < x.size(); ++ i)
    {
        out << x[i].ToString() << FILE_DATA_SPLIT << y[i].ToString() << '\n';        
    }
    out << FILE_END_FLAG << endl;
}
