#include "SystemCapabilityCalculation.h"

#ifdef Q_OS_WIN32
#include <windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")

// 时间转换
static __int64 file_time_2_utc(const FILETIME* ftime)
{
    LARGE_INTEGER li;

    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

// 获得CPU的核数
static int get_processor_number()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return (int)info.dwNumberOfProcessors;
}
// 获取进程CPU占用
double get_cpu_usage(int pid)
{
    //cpu数量
    static int processor_count_ = -1;
    //上一次的时间
    static __int64 last_time_ = 0;
    static __int64 last_system_time_ = 0;

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;
    __int64 system_time;
    __int64 time;
    __int64 system_time_delta;
    __int64 time_delta;

    double cpu = -1;

    if (processor_count_ == -1)
    {
        processor_count_ = get_processor_number();
    }

    //qDebug() << "processor_count_: " << processor_count_;

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }
    system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_;
    time = file_time_2_utc(&now);

    if ((last_system_time_ == 0) || (last_time_ == 0))
    {
        last_system_time_ = system_time;
        last_time_ = time;
        return -1;
    }

    system_time_delta = system_time - last_system_time_;
    time_delta = time - last_time_;

    if (time_delta == 0)
        return -1;

    cpu = ((system_time_delta * 100 + time_delta / 2) * 1.0 / time_delta);
    last_system_time_ = system_time;
    last_time_ = time;
    return cpu;
}

SIZE_T CalcWorkSetPrivate(HANDLE hProcess, SIZE_T pageSize)
{
    BOOL bRet = TRUE;
    PSAPI_WORKING_SET_INFORMATION workSetInfo;
    PBYTE pByte = NULL;
    PSAPI_WORKING_SET_BLOCK* pWorkSetBlock = workSetInfo.WorkingSetInfo;
    memset(&workSetInfo, 0, sizeof(workSetInfo));
    // 要求操作进程的权限：PROCESS_QUERY_INFORMATION and PROCESS_VM_READ
    // 第一次调用获取实际缓冲区大小
    bRet = ::QueryWorkingSet(hProcess, &workSetInfo, sizeof(workSetInfo));
    if (!bRet) // 调用失败
    {
        if (GetLastError() == ERROR_BAD_LENGTH) // 需要重新分配缓冲区
        {
            DWORD realSize = sizeof(workSetInfo.NumberOfEntries)
                + workSetInfo.NumberOfEntries * sizeof(PSAPI_WORKING_SET_BLOCK);
            try
            {
                pByte = new BYTE[realSize];
                memset(pByte, 0, realSize);
                pWorkSetBlock = (PSAPI_WORKING_SET_BLOCK*)(pByte + sizeof(workSetInfo.NumberOfEntries));
                // 重新获取
                if (!::QueryWorkingSet(hProcess, pByte, realSize))
                {
                    delete[] pByte; // 清理内存
                    return 0;
                }
            }
            catch (char* e) // 分配内存失败
            {
                // e->Delete();
                return 0;
            }

        }
        else // 其它错误，认为获取失败
            return 0;
    }
    SIZE_T workSetPrivate = 0;
    for (ULONG_PTR i = 0; i < workSetInfo.NumberOfEntries; ++i)
    {
        if (!pWorkSetBlock[i].Shared) // 如果不是共享页
            workSetPrivate += pageSize;
    }
    if (pByte)
        delete[] pByte;
    return workSetPrivate;
}
#endif

SystemCapabilityCalculation::SystemCapabilityCalculation(QObject *parent)
    : QObject(parent)
{
    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &SystemCapabilityCalculation::handleTimeout);
    m_pTimer->start(1000);
}

SystemCapabilityCalculation::~SystemCapabilityCalculation()
{
    
}

void SystemCapabilityCalculation::calCpuUsage()
{
#ifdef Q_OS_MACOS
    QProcess process;
    QStringList options;
    options << "-c"<< "ps aux | grep 'BossHi ' | grep -v grep | awk '{print $2,$3,$4,$5,$6}'";
    process.start("/bin/bash", options);
    process.waitForReadyRead();
    QString result = process.readAllStandardOutput();
    qDebug()<<"ps aux result: "<<result;
    QStringList strList = result.split(" ");
    if(strList.length()>3)
    {
        m_cpuUsage = strList[1].toDouble();
        m_memUsage = strList[2].toDouble();
    }
#else
    //获取进程id
    int pid = GetCurrentProcessId();
    //qDebug() << "pid: " << pid;
    double usgae = get_cpu_usage(pid);
    m_cpuUsage = usgae;
    //static double count = 0.0;
    //static int num = 0;
    //qDebug() << usgae;
    //num++;
    //count += usgae;
    //qDebug() << count / num;
    //m_cpuUsage = usgae + count / num;
#endif
}

void SystemCapabilityCalculation::calMemUsage(bool isPrintMessage)
{
#ifdef Q_OS_WIN32
    //获取进程id
    int pid = GetCurrentProcessId();
    if (isPrintMessage)
    {
        qDebug() << "pid: " << pid;
    }
    //根据pid获取进程内存
    long long processMem = 0;     //进程内存，单位M
    PERFORMANCE_INFORMATION performanceInfo;
    memset(&performanceInfo, 0, sizeof(performanceInfo));
    if (!::GetPerformanceInfo(&performanceInfo, sizeof(performanceInfo)))
        return;
    SIZE_T m_stPageSize = performanceInfo.PageSize; // 获取页面大小, 单位:byte
    SIZE_T d = CalcWorkSetPrivate(OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, pid), m_stPageSize);
    processMem = d / 1024 / 1024;
    if (processMem > 0)
    {
        m_processMem = processMem;
    }
    if (isPrintMessage)
    {
        qDebug() << "m_processMem: " << m_processMem;
    }
    //获取系统总内存
    long long memCount = 16103;     //单位M，默认16G
    QString path = "wmic";
    QStringList commands;
    //commands.append("-Command");
    commands << "ComputerSystem" << "get" << "TotalPhysicalMemory";
    QProcess p;
    p.start(path, commands);
    p.waitForFinished();
    p.waitForReadyRead();
    QString result = p.readAllStandardOutput();
    if (isPrintMessage)
    {
        qDebug() << "wmic ComputerSystem get TotalPhysicalMemory result: " << result;
    }
    QStringList strList = result.split("\r\r\n");
    if (strList.length() > 2)
    {
        memCount = strList[1].simplified().toLongLong()/1024/1024;
        if (isPrintMessage)
        {
            qDebug() << "memCount: " << memCount;
        }
    }
    //计算使用率
    m_memUsage = m_processMem * 1.0 / memCount * 100;
#endif
}

void SystemCapabilityCalculation::winInfoCmd()
{
    //    //QString path = "C:/Windows/system32/WindowsPowerShell/v1.0/powershell.exe";
    //    QString path = "powershell.exe";
    //    QStringList commands;
    //    //commands.append("-Command");
    //    commands.append("get-process");
    //    QProcess *p = new QProcess();
    //    p->start(path, commands);
    //    p->waitForReadyRead();
    //    QString result = p->readAllStandardOutput();
    //    qDebug()<<"result: "<<result;

        //wmic path Win32_PerfFormattedData_PerfProc_Process get Name,PercentProcessorTime | findstr /i /c:_Total

    //    QString path = "wmic";
    //    QStringList commands;
    //    //commands.append("-Command");
    //    commands<<"path"<<"Win32_PerfFormattedData_PerfProc_Process"<<"get"<<"Name,"<<"PercentProcessorTime";//<<"|"<<"findstr"<<"/c:_Total";
    //    //commands<<"wmic path Win32_PerfFormattedData_PerfProc_Process get Name, PercentProcessorTime | findstr /i /c:_Total";
    //    QProcess *p = new QProcess();
    //    p->start(path, commands);
    //    // p->waitForFinished();
    //    p->waitForReadyRead();
    //    QString result = p->readAllStandardOutput();
    //    QStringList strlist = result.split("\r\r\n");
    //    int appCpu = 0;
    //    int countCpu = 0;
    //    for(auto c:strlist)
    //    {
    //        if(c.contains("BossHiMeetingApp"))
    //        {
    //            //qDebug()<<"result: "<<c;
    //            QStringList strlist = c.split(QRegExp("\\s+"));
    //            if(strlist.length()>=2)
    //                appCpu = strlist[1].toInt();
    //        }
    //        if(c.contains("_Total"))
    //        {
    //            //qDebug()<<"result: "<<c;
    //            QStringList strlist = c.split(QRegExp("\\s+"));
    //            if(strlist.length()>=2)
    //            {
    //                countCpu = strlist[1].toInt();
    //                //qDebug()<<countCpu;
    //            }

    //        }
    //    }
    //    qDebug()<<appCpu*1.0/countCpu*100;

    //    numint<<get_cpu_usage(17288);
    //    if(numint.length()>10)
    //    {
    //        numint.pop_front();
    //    }
    //    double sum = 0.0;
    //    for(auto c:numint)
    //    {
    //        sum+=c;
    //    }
    //    qDebug()<<sum/numint.length();


    //    //QString path = "C:/Windows/system32/WindowsPowerShell/v1.0/powershell.exe";
    //    QString path = "powershell.exe";
    //    QStringList commands;
    //    //commands.append("-Command");
    //    commands.append("get-process -Name *");
    //    //commands.append("tasklist -v");
    //    QProcess *p = new QProcess();
    //    p->start(path, commands);
    //    p->waitForFinished();
    //    QString result = p->readAllStandardOutput();
    //    qDebug()<<"result: "<<result;

    //    QString path = "wmic";
    //    QStringList commands;
    //    //commands.append("-Command");
    //    commands<<"path"<<"Win32_PerfFormattedData_PerfProc_Process"<<"get"<<"Name,"<<"PercentProcessorTime";//<<"|"<<"findstr"<<"/c:_Total";
    //    //commands<<"wmic path Win32_PerfFormattedData_PerfProc_Process get Name, PercentProcessorTime | findstr /i /c:_Total";
    //    QProcess *p = new QProcess();
    //    p->start(path, commands);
    //    // p->waitForFinished();
    //    p->waitForReadyRead();
    //    QString result = p->readAllStandardOutput();
    //    QStringList strlist = result.split("\r\r\n");
    //    int appCpu = 0;
    //    int countCpu = 0;
    //    for(auto c:strlist)
    //    {
    //        if(c.contains("BossHiMeetingApp"))
    //        {
    //            qDebug()<<"result: "<<c;
    //            QStringList strlist = c.split(QRegExp("\\s+"));
    //            if(strlist.length()>=2)
    //                appCpu = strlist[2].toInt();
    //        }
    //        if(c.contains("_Total"))
    //        {
    //            qDebug()<<"result: "<<c;
    //            QStringList strlist = c.split(QRegExp("\\s+"));
    //            if(strlist.length()>=2)
    //            {
    //                countCpu = strlist[2].toInt();
    //                //qDebug()<<countCpu;
    //            }
    //        }
    //    }
    //    numint<<appCpu*1.0/countCpu;
    //    if(numint.length()>20)
    //    {

    //    }
    //    for(int i = numint.length() - 1;i>=0;i++)
    //    qDebug()<<appCpu*1.0/countCpu;

    //    QString path = "wmic";
    //    QStringList commands;
    //    //commands.append("-Command");
    //    commands<<"ComputerSystem"<<"get"<<"TotalPhysicalMemory";
    //    QProcess *p = new QProcess();
    //    p->start(path, commands);
    //     p->waitForFinished();
    //    p->waitForReadyRead();
    //    QString result = p->readAllStandardOutput();
    //    qDebug()<<"result: "<<result;
    //    QStringList strList = result.split("\r\r\n");
    //    if(strList.length()>2)
    //    {
    //        qDebug()<<"total: "<<strList[1].simplified().toLongLong();
    //    }
    //    qDebug()<<strList;

        //qDebug()<<GetCurrentProcessId();
}

void SystemCapabilityCalculation::handleTimeout()
{
    m_timeCountS++;
#ifdef Q_OS_WIN32
    calCpuUsage();
    calMemUsage();
#endif
    if(m_timeCountS % (10 * 60) == 0)     //10分钟上报一次cpu和内存使用率
    {
        calCpuUsage();
        calMemUsage(true);
        qDebug()<<"m_cpuUsage: "<<m_cpuUsage;
        qDebug()<<"m_memUsage: "<<m_memUsage;
        if (m_cpuUsage <= 0)
        {
            m_cpuUsage = 1;
        }
    }
}

