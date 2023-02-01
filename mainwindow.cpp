#include <QTableWidget>
#include <QDockWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createMenuAndActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenuAndActions()
{
    m_firstMenu = new QMenu(tr("First menu"), this);
    m_exitAction = new QAction(m_firstMenu);
    connect(m_exitAction, &QAction::triggered, this, &MainWindow::close);
    m_exitAction->setText(tr("Exit"));
    m_exitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    m_firstMenu->addAction(m_exitAction);

    m_secondMenu = new QMenu(tr("Second menu"), this);
    m_firstAction = new QAction(m_secondMenu);
    m_firstAction->setText(tr("Action 1"));
    connect(m_firstAction, &QAction::triggered, this, &MainWindow::actionTriggered);

    m_subMenu = new QMenu(tr("Sub menu"), m_secondMenu);
    m_secondAction = new QAction(m_subMenu);
    m_secondAction->setText(tr("Action 2"));
    connect(m_secondAction, &QAction::triggered, this, &MainWindow::actionTriggered);
    m_thirdAction = new QAction(m_subMenu);
    m_thirdAction->setText(tr("Action 3"));
    connect(m_thirdAction, &QAction::triggered, this, &MainWindow::actionTriggered);
    m_subMenu->addAction(m_secondAction);
    m_subMenu->addAction(m_thirdAction);
    m_secondMenu->addAction(m_firstAction);
    m_secondMenu->addMenu(m_subMenu);

    ui->menubar->addMenu(m_firstMenu);
    ui->menubar->addMenu(m_secondMenu);
}

void MainWindow::actionTriggered(bool checked)
{
    Q_UNUSED(checked);
    QAction *senderAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(senderAction);
    ui->statusbar->showMessage(senderAction->text());
}

