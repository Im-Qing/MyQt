﻿#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "MOpenGL/MGLWidget.h"

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
    MGLWidget* m_pMGLWidget = nullptr;
    QTimer* m_pTimer;
};
#endif // MMAINWINDOW_H
