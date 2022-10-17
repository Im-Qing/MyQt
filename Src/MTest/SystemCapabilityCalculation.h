#ifndef SYSTEMCAPABILITYCALCULATION_H
#define SYSTEMCAPABILITYCALCULATION_H

#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QDebug>

class SystemCapabilityCalculation : public QObject
{
    Q_OBJECT
public:
    SystemCapabilityCalculation(QObject *parent = nullptr);
    ~SystemCapabilityCalculation();
private:
    //计算cpu使用率
    void calCpuUsage();
    //计算内存使用率
    void calMemUsage(bool isPrintMessage = false);
    //win系统下查看信息命令
    void winInfoCmd();
public slots:
    void handleTimeout();
private:
    QTimer *m_pTimer;
    qint64 m_timeCountS{0};    //定时器计数和，单位s

    long long m_processMem = 50;    //  默认50M
    double m_cpuUsage;
    double m_memUsage;
};

#endif // SYSTEMCAPABILITYCALCULATION_H
