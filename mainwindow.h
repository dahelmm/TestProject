#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        void createMenuAndActions();
        void createButtons();

    private slots:
        void actionTriggered(bool checked);
        void bttnStylePanelClicked();
        void bttnTableClicked();

    private:
        Ui::MainWindow *ui;
        QMenu *m_firstMenu;
        QMenu *m_secondMenu;
        QMenu *m_subMenu;

        QAction *m_exitAction;
        QAction *m_firstAction;
        QAction *m_secondAction;
        QAction *m_thirdAction;

        QPushButton *m_bttnStylePanel;
        QPushButton *m_bttnTable;
        QPushButton *m_bttnTextPanel;
        QPushButton *m_bttnClearTextFields;
        QPushButton *m_bttnAddTextField;
        QPushButton *m_bttnAddLineTable;
        QPushButton *m_bttnDeleteLineTable;

        QTableWidget *m_tableWidget;
        QGridLayout *m_mainGridLay;
        QGridLayout *m_gridLayTextFields;
        QHBoxLayout *m_horLayForMainButtons;
        QHBoxLayout *m_horLayForTableButtons;
        QVBoxLayout *m_verLayForTableAndButtons;

        QDockWidget *m_styleDockWidget;

        bool m_visibleTable;
        bool m_visibleStyleDockWidget;

};
#endif // MAINWINDOW_H
