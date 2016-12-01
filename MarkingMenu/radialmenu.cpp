#include "radialmenu.h"

#include "markingmenu.h"
#include "QMouseEvent"

#define USER_LENGTH 30 // in px
#define USER_SHOW_LENGTH 120 // in px
#define RADIAL_RANGE 100 // in px
#define SHOW_TIME 500 // in ms
#define STOP_TIME 100 // in ms

RadialMenu::RadialMenu() : QWidget(MarkingMenu::_t) {
    hide(); // The widget is initially hidden
}

RadialMenu::~RadialMenu() {
    for (int i=0; i < struct_vector.size(); i++) {
        delete struct_vector[i].label;
        if (struct_vector[i].handle_delete && struct_vector[i].function)
            delete struct_vector[i].function;
    }
    // Free the marking_menu if necessary
    if (this == MarkingMenu::_t->root_menu)
        MarkingMenu::_t->root_menu = 0;
    if (this == MarkingMenu::_t->active_menu)
        MarkingMenu::_t->active_menu = 0;
}

void RadialMenu::setRootMenu() {
    MarkingMenu::_t->root_menu = this;
}

QLabel* RadialMenu::createLabel(const std::string& string) {
    QLabel* label = new QLabel(this);
    label->setText(QString::fromStdString(string));
    label->setAutoFillBackground(false);
    label->setStyleSheet(QLatin1String("font: 75 10pt \"Calibri\";\n" "font-weight: bold;\n"));
    label->setAlignment(Qt::AlignCenter);
    label->setFrameShape(QFrame::StyledPanel);
    label->setFrameShadow(QFrame::Sunken);

    label->resize(QSize(string.size()*10, 25));
    label->show();

    return label;
}

void RadialMenu::addMenu(const std::string& string, RadialMenu* rw) {
    if (struct_vector.size() >= 8)
        throw std::string("ERREUR : maximul number of entries reached !");

    QLabel* label = createLabel(string);
    radial_struct r = { label, rw, 0, false };
    struct_vector.push_back(r);
}

void RadialMenu::addAction(const std::string& string, std::function<void(void)>* function, bool handle_delete) {
    if (struct_vector.size() >= 8)
        throw std::string("ERREUR : maximul number of entries reached !");

    QLabel* label = createLabel(string);
    radial_struct r = { label, 0, function, handle_delete };
    struct_vector.push_back(r);
}

void RadialMenu::activate(const QPoint& position, bool show) {
    MarkingMenu::_t->active_menu = this;

    center = position;
    my_direction = NOT_RESOLVED;
    current_point = center;
    resolved = false;

    // Arm timers
    timer_show.setSingleShot(true);
    timer_stop.setSingleShot(true);
    // Connect timers to RadialMenu methods
    connect(&timer_show, SIGNAL(timeout()), this, SLOT(showMenu()));
    connect(&timer_stop, SIGNAL(timeout()), this, SLOT(selectionStop()));

    if (!show)
        timer_show.start(SHOW_TIME);
    else
        showMenu();
}

void RadialMenu::deactivate() {
    if (!resolved) {
        // Last chance for a function to be called
        if (my_direction < struct_vector.size())
            if (struct_vector[my_direction].function)
                (*struct_vector[my_direction].function)();

        hide();
        resolved = true;
        // Disable timers
        disconnect(&timer_show, SIGNAL(timeout()), this, SLOT(showMenu()));
        disconnect(&timer_stop, SIGNAL(timeout()), this, SLOT(selectionStop()));
    }
}

void RadialMenu::showMenu() {
    if (!isVisible()) {
        float angle = 90.f;
        QPoint point_orig(center.x() + RADIAL_RANGE, center.y());
        for (int i=0; i < struct_vector.size(); i++) { // Circular positionning of the labels
            struct_vector[i].label->move(point_orig.x() - struct_vector[i].label->size().width()/2,
                                         point_orig.y() - struct_vector[i].label->size().height()/2);
            if (i%4 == 3 && i > 0)
                point_orig = rotationGlobal(point_orig, center, -45);
            point_orig = rotationGlobal(point_orig, center, -angle);
        }

        this->show();
    }
}

RadialMenu::direction RadialMenu::directionFromAngle(float angle, bool deg) {
    if (deg == false)
        angle = angle * 180 / PI;

    if (angle >= -22.5 && angle < 22.5)
        return EAST;
    if (angle >= -67.5 && angle < -22.5)
        return NORTH_EAST;
    if (angle >= -112.5 && angle < -67.5)
        return NORTH;
    if (angle >= -157.5 && angle < -112.5)
        return NORTH_WEST;
    if (angle >= 157.5 || angle < -157.5)
        return WEST;
    if (angle >= 112.5 && angle < 157.5)
        return SOUTH_WEST;
    if (angle >= 67.5 && angle < 112.5)
        return SOUTH;
    if (angle >= 22.5 && angle < 67.5)
        return SOUTH_EAST;

    return NOT_RESOLVED;
}

void RadialMenu::selection() {
    if (!resolved) {
        if (my_direction < struct_vector.size()) { // If a direction match something
            radial_struct& selected = struct_vector[my_direction];
            if (selected.rw)     // MENU
                selected.rw->activate(current_point, isVisible());
            else                 // FUNCTION
                (*selected.function)();
            my_direction = NOT_RESOLVED; // Avoids lambda function call in deactivate()
            deactivate(); // Deactivate radial_menu
        }
        else
            my_direction = NOT_RESOLVED; // This direction is wrong
    }
}

void RadialMenu::selectionStop() {
    current_point = current_mouse; // Get real mouse position (not the one stored before)
    selection();
}

void RadialMenu::mouseMoveEvent(QMouseEvent* qm) {
    if (!resolved) {
        current_mouse = qm->pos();
        QPoint delta = current_mouse - current_point;
        float norme = std::sqrt(std::pow(delta.x(), 2) + std::pow(delta.y(), 2)); // Length dragged
        if ((!isVisible() && norme > USER_LENGTH) ||
             (isVisible() && norme > USER_SHOW_LENGTH) ||
                (my_direction != NOT_RESOLVED && norme > 5)) { // If the drag is enough
            current_point = current_mouse;
            if (!isVisible())
                timer_show.start(SHOW_TIME);
            if (!resolved)
                timer_stop.start(STOP_TIME);

            float angle = atan2(delta.y(), delta.x());
            direction dir = directionFromAngle(angle, false); // Calculate direction

            if (my_direction == NOT_RESOLVED)
                my_direction = dir;
            else if (dir != my_direction)
                selection(); // Check for a sub_menu or a function to call
        }
    }
}

