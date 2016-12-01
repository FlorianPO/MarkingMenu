#ifndef MARKINGMENU_H
#define MARKINGMENU_H

#include <QWidget>
class RadialMenu;

/*
 * This class dispatches mouse move events to
 * RadialMenus and also deals with pressEvent
 * and releaseEvent.
 *
 * This class was created due to an issue in Qt
 * which prevents RadialMenus from getting mouse
 * move events (because of the strange layout
 * in the MainWindow). If the bug is solved,
 * RadialMenus could easily work on their
 * own by dealing with their own events.
 */
class MarkingMenu : public QWidget
{
    Q_OBJECT
public:
    MarkingMenu();
private:
    friend class RadialMenu;
    void mousePressEvent(QMouseEvent* qm) override;
    void mouseReleaseEvent(QMouseEvent* qm) override;
    void mouseMoveEvent(QMouseEvent* qm) override;

    RadialMenu* root_menu;
    RadialMenu* active_menu = 0;
    static MarkingMenu* _t;
};

#endif // MARKINGMENU_H
