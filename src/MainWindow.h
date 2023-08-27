#ifndef MAINWINDOW_H
#define MAINWINDOW_H


// set to 0 to witness the unsatisfying built-in behavior
#define DERIVE_FROM_DOCK_WINDOW 1


#if DERIVE_FROM_DOCK_WINDOW
#include "DockWindow.h"
using MainWindowBase = DockWindow;
#else
#include <QMainWindow>
using MainWindowBase = QMainWindow;
#endif


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public MainWindowBase
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    QDockWidget *addTab();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
