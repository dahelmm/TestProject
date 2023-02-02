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
      m_gridLayTable(nullptr),
      m_gridLayTextFields(nullptr),
      m_horLayForMainButtons(nullptr),
      m_horLayForTableButtons(nullptr),
      m_verLayForTableAndButtons(nullptr),
      m_widgetForTextFields(nullptr),
      m_styleDockWidget(nullptr),
      m_counterTextFields(1),
      m_counterLineInTable(0)
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

    m_mainGridLay->addLayout(m_horLayForMainButtons, 0, 0);

    m_gridLayTable = new QGridLayout;

    m_horLayForTableButtons = new QHBoxLayout;
    m_horLayForTableButtons->addWidget(m_bttnAddLineTable);
    m_horLayForTableButtons->addWidget(m_bttnDeleteLineTable);

    m_verLayForTableAndButtons = new QVBoxLayout;
    m_verLayForTableAndButtons->addWidget(m_tableWidget);
    m_verLayForTableAndButtons->addLayout(m_horLayForTableButtons);

    m_gridLayTable->addLayout(m_verLayForTableAndButtons, 0,0);
    m_mainGridLay->addLayout(m_gridLayTable, 1, 0);

    m_widgetForTextFields = new QWidget(this);
    m_gridLayTextFields = new QGridLayout;
    QGroupBox *newGb = createGroupBox();
    m_gridLayTextFields->addWidget(newGb);
    QGroupBox *newGb2 = createGroupBox();
    m_gridLayTextFields->addWidget(newGb2);
    m_widgetForTextFields->setLayout(m_gridLayTextFields);
    m_mainGridLay->addWidget(m_widgetForTextFields, 1, 1);

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
    connect(m_bttnTextPanel, &QPushButton::clicked, this, &MainWindow::bttnTextPanelClicked);

    m_bttnClearTextFields = new QPushButton(this);
    m_bttnClearTextFields->setText(tr("Clear text tables"));

    m_bttnAddTextField = new QPushButton(this);
    connect(m_bttnAddTextField, &QPushButton::clicked,
            [=]{
        QGroupBox *newGb = createGroupBox();
        m_gridLayTextFields->addWidget(newGb);
    });
    m_bttnAddTextField->setText(tr("Add text tables"));

    m_bttnAddLineTable = new QPushButton(this);
    connect(m_bttnAddLineTable, &QPushButton::clicked, this, &MainWindow::bttnAddLineClicked);
    m_bttnAddLineTable->setText(tr("Add line"));

    m_bttnDeleteLineTable = new QPushButton(this);
    connect(m_bttnDeleteLineTable, &QPushButton::clicked, this, &MainWindow::bttnDeleteLineClicked);
    m_bttnDeleteLineTable->setText(tr("Delete line"));
}

QGroupBox * MainWindow::createGroupBox()
{
    QGroupBox *groupBoxTextField = new QGroupBox(this);

    QPlainTextEdit *plainTextEdit = new QPlainTextEdit(groupBoxTextField);
    connect(m_bttnClearTextFields, &QPushButton::clicked, plainTextEdit, &QPlainTextEdit::clear);
    plainTextEdit->setPlainText(tr("Text %1").arg(m_counterTextFields));

    QPushButton *bttnDeleteTextField = new QPushButton(groupBoxTextField);
    connect(bttnDeleteTextField, &QPushButton::clicked, [=]{groupBoxTextField->deleteLater();});
    bttnDeleteTextField->setText(tr("X"));

    QPushButton *bttnOkTextField = new QPushButton(groupBoxTextField);
    connect(bttnOkTextField, &QPushButton::clicked, [=]{ui->statusbar->showMessage(plainTextEdit->toPlainText());});
    bttnOkTextField->setText(tr("OK"));

    QVBoxLayout *vertLayBttnsTextField = new QVBoxLayout;
    connect(groupBoxTextField, &QGroupBox::destroyed, vertLayBttnsTextField, &QVBoxLayout::deleteLater);
    vertLayBttnsTextField->addWidget(bttnDeleteTextField);
    vertLayBttnsTextField->addWidget(bttnOkTextField);

    QHBoxLayout *horLayGroupBox = new QHBoxLayout;
    connect(groupBoxTextField, &QGroupBox::destroyed, horLayGroupBox, &QHBoxLayout::deleteLater);
    horLayGroupBox->addWidget(plainTextEdit);
    horLayGroupBox->addLayout(vertLayBttnsTextField);

    groupBoxTextField->setLayout(horLayGroupBox);
    ++m_counterTextFields;
    return groupBoxTextField;
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
    m_styleDockWidget->setVisible(!m_styleDockWidget->isVisible());
    if(m_styleDockWidget->isVisible())
        m_bttnStylePanel->setText(tr("Hide style panel"));
    else
        m_bttnStylePanel->setText(tr("Show style panel"));
}

void MainWindow::bttnTableClicked()
{
    m_tableWidget->setVisible(!m_tableWidget->isVisible());
    m_bttnAddLineTable->setVisible(!m_bttnAddLineTable->isVisible());
    m_bttnDeleteLineTable->setVisible(!m_bttnDeleteLineTable->isVisible());
    if(m_tableWidget->isVisible())
        m_bttnTable->setText(tr("Hide table"));
    else
        m_bttnTable->setText(tr("Show table"));
}

void MainWindow::bttnTextPanelClicked()
{
    m_widgetForTextFields->setVisible(!m_widgetForTextFields->isVisible());
    if(m_widgetForTextFields->isVisible())
        m_bttnTextPanel->setText(tr("Hide text panel"));
    else
        m_bttnTextPanel->setText(tr("Show text panel"));
}

void MainWindow::bttnAddLineClicked()
{
    m_tableWidget->insertRow(m_counterLineInTable);
    m_tableWidget->setItem(m_counterLineInTable, 0, new QTableWidgetItem(tr("Id_%1").arg(m_counterLineInTable+1)));
    m_tableWidget->setItem(m_counterLineInTable, 1, new QTableWidgetItem(tr("Parameter_%1").arg(m_counterLineInTable+1)));
    m_tableWidget->setItem(m_counterLineInTable, 2, new QTableWidgetItem(tr("Value_%1").arg(m_counterLineInTable+1)));
    ++m_counterLineInTable;

}

void MainWindow::bttnDeleteLineClicked()
{
    m_tableWidget->removeRow(m_counterLineInTable-1);
    m_counterLineInTable--;
}
