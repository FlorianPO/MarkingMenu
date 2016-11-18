#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MarkingMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    MarkingMenu* marking_menu;
};

#endif // MAINWINDOW_H
