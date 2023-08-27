#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDockWidget>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : MainWindowBase(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(nullptr);
    setDockOptions(AnimatedDocks | AllowNestedDocks | AllowTabbedDocks);

    connect(ui->actionExit, &QAction::triggered,
        this, &MainWindow::close);
    connect(ui->actionAddTab, &QAction::triggered,
        this, &MainWindow::addTab);

#if DERIVE_FROM_DOCK_WINDOW
    ui->menubar->setStyleSheet("QMenuBar { border: none }");
    connect(this, &DockWindow::dockCloseRequested, 
        [](QDockWidget *dock) { dock->close(); });
    connect(this, &DockWindow::openNewDock, 
        this, &MainWindow::addTab);
#endif

    auto first = addTab();
    addTab();
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, addTab());

    first->raise();
    first->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QDockWidget* MainWindow::addTab()
{
    static auto sNextUntitledId = 1;

    auto dock = new QDockWidget(this);
    auto editor = new QPlainTextEdit();
    dock->setWindowTitle("Untitled " + QString::number(sNextUntitledId++));
    dock->toggleViewAction()->setVisible(false);
    dock->setWidget(editor);

    if (auto focused = qApp->focusWidget())
        if (auto focusedDock = qobject_cast<QDockWidget*>(focused->parentWidget())) {
            tabifyDockWidget(focusedDock, dock);
            return dock;
        }

    for (auto child : children())
        if (auto someDock = qobject_cast<QDockWidget*>(child))
            if (someDock != dock) {
                tabifyDockWidget(someDock, dock);
                return dock;
            }

    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dock);
    return dock;
}
