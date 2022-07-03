#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "MOpenGL/MGLWidget.h"

#include "MRotationImg.h"

using namespace NS_MOpenGL;

QT_BEGIN_NAMESPACE
namespace Ui { class MMainWindow; }
QT_END_NAMESPACE

class MMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MMainWindow(QWidget *parent = nullptr);
    ~MMainWindow();
public slots:
    void slot_timeout();
private:
    Ui::MMainWindow *ui;
    MGLWidget* m_pMGLWidget = nullptr;
    QTimer* m_pTimer;
    MRotationImg* m_pRotationImg;
};
#endif // MMAINWINDOW_H
