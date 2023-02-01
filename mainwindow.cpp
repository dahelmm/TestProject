#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * First menu
     */
    QMenu *firstMenu = new QMenu(tr("First menu"), this);
    QAction *exitAction = new QAction(firstMenu);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    exitAction->setText(tr("Exit"));
    exitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    firstMenu->addAction(exitAction);

    /*
     * Second menu
     */
    QMenu *secondMenu = new QMenu(tr("Second menu"), this);
    QAction *firstAction = new QAction(secondMenu);
    firstAction->setText(tr("Action 1"));
    connect(firstAction, &QAction::triggered, this, &MainWindow::actionTriggered);

    /* Sub menu (second menu) */
    QMenu *subMenu = new QMenu(tr("Sub menu"), secondMenu);
    QAction *secondAction = new QAction(subMenu);
    secondAction->setText(tr("Action 2"));
    connect(secondAction, &QAction::triggered, this, &MainWindow::actionTriggered);
    QAction *thirdAction = new QAction(subMenu);
    thirdAction->setText(tr("Action 3"));
    connect(thirdAction, &QAction::triggered, this, &MainWindow::actionTriggered);
    subMenu->addAction(secondAction);
    subMenu->addAction(thirdAction);
    secondMenu->addAction(firstAction);
    secondMenu->addMenu(subMenu);

    ui->menubar->addMenu(firstMenu);
    ui->menubar->addMenu(secondMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionTriggered(bool checked)
{
    Q_UNUSED(checked);
    QAction *senderAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(senderAction);
    ui->statusbar->showMessage(senderAction->text());
}

