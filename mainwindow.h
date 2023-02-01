#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    private slots:
        void actionTriggered(bool checked);

    private:
        Ui::MainWindow *ui;
        QMenu *m_firstMenu;
        QMenu *m_secondMenu;
        QMenu *m_subMenu;

        QAction *m_exitAction;
        QAction *m_firstAction;
        QAction *m_secondAction;
        QAction *m_thirdAction;

};
#endif // MAINWINDOW_H
