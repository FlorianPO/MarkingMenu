#include "markingmenu.h"
#include <QMouseEvent>
#include "radialmenu.h"

MarkingMenu::MarkingMenu(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);

    // Test radial_menu
    RadialMenu* m1 = new RadialMenu(this);
    RadialMenu* m2 = new RadialMenu(this);
    m1->addMenu("new_menu", m2);
    m2->addAction("new_action", new std::function<void(void)>([](){qDebug("function_lol");}));

    root_menu = m1;
    active_menu = m1;
}

void MarkingMenu::mouseMoveEvent(QMouseEvent* qm) {
    if (activated)
        active_menu->mouseMoveEvent(qm);
}

void MarkingMenu::mousePressEvent(QMouseEvent* qm) {
    if (qm->button() == Qt::RightButton) {
        activated = true;
        root_menu->activate(qm->pos());
    }
}

void MarkingMenu::mouseReleaseEvent(QMouseEvent* qm) {
    if (qm->button() == Qt::RightButton) {
        active_menu = root_menu;
        root_menu->hide();
        activated = false;
    }
}
