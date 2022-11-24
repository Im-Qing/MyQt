#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H
#include <QObject>
#include <QWidget>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineDownloadItem>
#include <QNetworkProxyFactory>

class MWebEngineView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit MWebEngineView(QWidget* parent = nullptr);
    ~MWebEngineView();
     virtual QWebEngineView* createWindow(QWebEnginePage::WebWindowType type) override;
signals:
    void signBytesReceived(qint64 bytesReceived);
    void signDownloadFinished();
public slots:
    void onWebDownload(QWebEngineDownloadItem* item);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished();
private:
    QUrl m_url;
};

#endif // WEBENGINEVIEW_H
