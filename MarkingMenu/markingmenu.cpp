#include "markingmenu.h"
#include <QMouseEvent>
#include "radialmenu.h"

MarkingMenu* MarkingMenu::_t;

MarkingMenu::MarkingMenu() : QWidget(0) {
    _t = this; // Enables static access to the marking menu
}

void MarkingMenu::mouseMoveEvent(QMouseEvent* qm) {
    if (active_menu)
        active_menu->mouseMoveEvent(qm);
}

void MarkingMenu::mousePressEvent(QMouseEvent* qm) {
    if (qm->button() == Qt::RightButton && root_menu)
        root_menu->activate(qm->pos());
}

void MarkingMenu::mouseReleaseEvent(QMouseEvent* qm) {
    if (qm->button() == Qt::RightButton) {
        if (active_menu)
           active_menu->deactivate();
        active_menu = 0;
    }
}
