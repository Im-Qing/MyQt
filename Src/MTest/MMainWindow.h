#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "MOpenGL/MGLWidget.h"
#include "MOsg/MOsgScene.h"
#include "MOsg/MOsgWidget.h"

using namespace NS_MOpenGL;
using namespace NS_MOsg;

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
    void slot_test1(bool);
    void slot_test2(bool);
private:
    Ui::MMainWindow *ui;
    QTimer* m_pTimer;

    MGLWidget* m_pMGLWidget = nullptr;

    MOsgScene* m_pMOsgScene = nullptr;
    MOsgWidget* m_pMOsgWidget = nullptr;
};
#endif // MMAINWINDOW_H
