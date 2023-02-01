#include <QHeaderView>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_firstMenu(nullptr),
      m_secondMenu(nullptr),
      m_subMenu(nullptr),
      m_exitAction(nullptr),
      m_firstAction(nullptr),
      m_secondAction(nullptr),
      m_thirdAction(nullptr),
      m_bttnStylePanel(nullptr),
      m_bttnTable(nullptr),
      m_bttnTextPanel(nullptr),
      m_bttnClearTextFields(nullptr),
      m_bttnAddTextField(nullptr),
      m_bttnAddLineTable(nullptr),
      m_bttnDeleteLineTable(nullptr),
      m_tableWidget(nullptr),
      m_mainGridLay(nullptr),
      m_gridLayTextFields(nullptr),
      m_horLayForMainButtons(nullptr),
      m_horLayForTableButtons(nullptr),
      m_verLayForTableAndButtons(nullptr),
      m_styleDockWidget(nullptr),
      m_visibleTable(true),
      m_visibleStyleDockWidget(true)
{
    ui->setupUi(this);

    createMenuAndActions();
    createButtons();

    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("Id")<<tr("Parameter")<<tr("Value"));
    m_tableWidget->setColumnWidth(0, 50);
    m_tableWidget->setColumnWidth(2, 150);

    m_tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);


    m_mainGridLay = new QGridLayout;

    m_horLayForMainButtons = new QHBoxLayout;
    m_horLayForMainButtons->addWidget(m_bttnStylePanel);
    m_horLayForMainButtons->addWidget(m_bttnTable);
    m_horLayForMainButtons->addWidget(m_bttnTextPanel);
    m_horLayForMainButtons->addWidget(m_bttnClearTextFields);
    m_horLayForMainButtons->addWidget(m_bttnAddTextField);

    m_horLayForTableButtons = new QHBoxLayout;
    m_horLayForTableButtons->addWidget(m_bttnAddLineTable);
    m_horLayForTableButtons->addWidget(m_bttnDeleteLineTable);

    m_verLayForTableAndButtons = new QVBoxLayout;
    m_verLayForTableAndButtons->addWidget(m_tableWidget);
    m_verLayForTableAndButtons->addLayout(m_horLayForTableButtons);

    m_mainGridLay->addLayout(m_horLayForMainButtons, 0, 0);
    m_mainGridLay->addLayout(m_verLayForTableAndButtons, 1,0);

    m_styleDockWidget = new QDockWidget(tr("Style"), this);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_styleDockWidget);

    ui->centralwidget->setLayout(m_mainGridLay);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_horLayForMainButtons;
    delete m_horLayForTableButtons;
    delete m_verLayForTableAndButtons;
    delete m_mainGridLay;
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

void MainWindow::createButtons()
{
    m_bttnStylePanel = new QPushButton(this);
    m_bttnStylePanel->setText(tr("Hide style panel"));
    connect(m_bttnStylePanel, &QPushButton::clicked, this, &MainWindow::bttnStylePanelClicked);

    m_bttnTable = new QPushButton(this);
    m_bttnTable->setText(tr("Hide table"));
    connect(m_bttnTable, &QPushButton::clicked, this, &MainWindow::bttnTableClicked);

    m_bttnTextPanel = new QPushButton(this);
    m_bttnTextPanel->setText(tr("Hide text panel"));

    m_bttnClearTextFields = new QPushButton(this);
    m_bttnClearTextFields->setText(tr("Clear text tables"));

    m_bttnAddTextField = new QPushButton(this);
    m_bttnAddTextField->setText(tr("Add text tables"));

    m_bttnAddLineTable = new QPushButton(this);
    m_bttnAddLineTable->setText(tr("Add line"));

    m_bttnDeleteLineTable = new QPushButton(this);
    m_bttnDeleteLineTable->setText(tr("Delete line"));
}

void MainWindow::actionTriggered(bool checked)
{
    Q_UNUSED(checked);
    QAction *senderAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(senderAction);
    ui->statusbar->showMessage(senderAction->text());
}

void MainWindow::bttnStylePanelClicked()
{
    m_visibleStyleDockWidget = !m_visibleStyleDockWidget;
    m_styleDockWidget->setVisible(m_visibleStyleDockWidget);
}

void MainWindow::bttnTableClicked()
{
    m_visibleTable = !m_visibleTable;
    m_tableWidget->setVisible(m_visibleTable);
    m_bttnAddLineTable->setVisible(m_visibleTable);
    m_bttnDeleteLineTable->setVisible(m_visibleTable);
}

