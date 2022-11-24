#include "MWebEngineView.h"

MWebEngineView::MWebEngineView(QWidget *parent)
    :QWebEngineView(parent)
{
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    QWebEngineProfile* webProfile = page() -> profile();
    connect(webProfile, &QWebEngineProfile::downloadRequested, this, &MWebEngineView::onWebDownload);

    //TODO: 链接hover时改变m_url的值
    connect(this->page(), &QWebEnginePage::linkHovered, this, [this](const QString &url){
        m_url.setUrl(url);
    });
    connect(this->page(), &QWebEnginePage::urlChanged, this, [this](const QUrl &url){
        m_url = url;
        //qDebug()<<"urlChanged: "<<m_url;
    });
}

MWebEngineView::~MWebEngineView()
{

}

QWebEngineView *MWebEngineView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);
    if(!m_url.isEmpty())
    {
        this->load(m_url);  //加载新的url
    }
    return nullptr;
}

void MWebEngineView::onWebDownload(QWebEngineDownloadItem *item)
{
    connect(item, SIGNAL(finished()), this, SLOT(onDownloadFinished()));
    connect(item, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));

    QString path = item->path();
    //qDebug() << "item->path(): " << item->path();
    item -> setPath(path);
    item -> accept();
}

void MWebEngineView::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit signBytesReceived(bytesReceived);
}

void MWebEngineView::onDownloadFinished()
{
    emit signDownloadFinished();
}
