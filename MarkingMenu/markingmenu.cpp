#include "markingmenu.h"
#include <QMouseEvent>
#include "radialmenu.h"

MarkingMenu::MarkingMenu(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);

    // Test radial_menu
    RadialMenu* m = new RadialMenu(this);
    m->addLabel("label 1");
    m->addLabel("label 2");
    m->addLabel("label 3");

    radial_menus.push_back(m);
}

void MarkingMenu::mouseMoveEvent(QMouseEvent* qm) {
   // qDebug("");
}

void MarkingMenu::mousePressEvent(QMouseEvent* qm) {
    if (qm->button() == Qt::RightButton) {
        if (radial_menus.size() > 0) {
            radial_menus.front()->showMenu(qm->pos());
        }
    }
}

void MarkingMenu::mouseReleaseEvent(QMouseEvent* qm) {
    if (qm->button() == Qt::RightButton) {
        for (int i=0; i < radial_menus.size(); i++) {
            radial_menus[i]->hide();
        }
    }
}
