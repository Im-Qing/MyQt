#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "MOpenGL/MGLScene.h"
#include "MOpenGL/MGLWidget.h"

#include "MModelTest.h"

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
    void slot_test1(bool);
    void slot_test2(bool);
private:
    Ui::MMainWindow *ui;
    QTimer* m_pTimer;

    MGLScene* m_pGLScene = nullptr;
    MGLWidget* m_pGLWidget = nullptr;
    MModelTest* m_pGLModel = nullptr;
};
#endif // MMAINWINDOW_H
