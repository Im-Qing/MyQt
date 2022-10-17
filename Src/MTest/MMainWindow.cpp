#include "MMainWindow.h"
#include "ui_MMainWindow.h"

#include <QDebug>

MMainWindow::MMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MMainWindow)
{
    ui->setupUi(this);
    resize(1000, 600);

    m_pMGLWidget = new MGLWidget(this);
    ui->gridLayout->addWidget(m_pMGLWidget);

    m_pTimer = new QTimer(this);
    //m_pTimer->start(50);
    connect(m_pTimer, &QTimer::timeout,this,&MMainWindow::slot_timeout);

    connect(ui->actiontest1, &QAction::triggered, this, &MMainWindow::slot_test1);
    connect(ui->actiontest2, &QAction::triggered, this, &MMainWindow::slot_test2);
}

MMainWindow::~MMainWindow()
{
    delete ui;
}

void MMainWindow::slot_timeout()
{

}

void MMainWindow::slot_test1(bool)
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
}

void MMainWindow::slot_test2(bool)
{
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

