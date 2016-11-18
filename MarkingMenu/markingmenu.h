#ifndef MARKINGMENU_H
#define MARKINGMENU_H

#include <QWidget>
class RadialMenu;

class MarkingMenu : public QWidget
{
    Q_OBJECT
public:
    MarkingMenu(QWidget *parent=0);

private:
    void mousePressEvent(QMouseEvent* qm) override;
    void mouseReleaseEvent(QMouseEvent* qm) override;
    void mouseMoveEvent(QMouseEvent* qm) override;

    std::vector<RadialMenu*> radial_menus;
};

#endif // MARKINGMENU_H
