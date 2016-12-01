#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MarkingMenu;

/*
 * This class represents the main window.
 * It also contains the MarkingMenu widget
 * which will dispatch events to RadialMenus
 *
 * Glitches can occur and hide the RadialMenus
 * (especially the top left side). Layout in a
 * mainwindow is buggy !
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QSize& size);
    ~MainWindow();

private:
    MarkingMenu* marking_menu;
};

#endif // MAINWINDOW_H
