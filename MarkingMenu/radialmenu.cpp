#include "radialmenu.h"

#include "markingmenu.h"
#include "QMouseEvent"

RadialMenu::RadialMenu(QWidget *parent) : QWidget(parent) {
    hide();
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
    radial_struct r = { label, rw, 0 };
    struct_vector.push_back(r);
}

void RadialMenu::addAction(const std::string& string, std::function<void(void)>* function) {
    if (struct_vector.size() >= 8)
        throw std::string("ERREUR : maximul number of entries reached !");

    QLabel* label = createLabel(string);
    radial_struct r = { label, 0, function };
    struct_vector.push_back(r);
}

void RadialMenu::hideEvent(QHideEvent* event) {
    disconnect(&timer_show, SIGNAL(timeout()), this, SLOT(showMenu()));
    //disconnect(&timer_stop, &QTimer::timeout, [this](){});
    for (int i=0; i < struct_vector.size(); i++)
        if (struct_vector[i].rw != 0)
            struct_vector[i].rw->hide();
    QWidget::hideEvent(event);
}

void RadialMenu::activate(const QPoint& position) {
    center = position;
    my_direction = ERROR;
    current_point = center;
    stopped = false;

    connect(&timer_show, SIGNAL(timeout()), this, SLOT(showMenu()));
    timer_show.start(500);
    connect(&timer_show, SIGNAL(timeout()), this, SLOT(showMenu()));
    timer_show.start(500);
}

void RadialMenu::showMenu() {
    float angle = 90.f;
    QPoint point_orig(center.x() + distance, center.y());
    for (int i=0; i < struct_vector.size(); i++) {
        struct_vector[i].label->move(point_orig.x() - struct_vector[i].label->size().width()/2,
                                     point_orig.y() - struct_vector[i].label->size().height()/2);
        if (i%4 == 3 && i > 0)
            point_orig = rotationGlobal(point_orig, center, -45);
        point_orig = rotationGlobal(point_orig, center, -angle);
    }

    this->show();
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

    return ERROR;
}

void RadialMenu::selection() {
    if (my_direction < struct_vector.size()) {
        radial_struct& selected = struct_vector[my_direction];
        if (selected.rw) { // MENU
            selected.rw->activate(qm->pos());
        }
        else { // Function
            (*selected.function)();
        }
    }
    else
        my_direction = ERROR;
}

void RadialMenu::mouseMoveEvent(QMouseEvent* qm) {
    QPoint delta = qm->pos() - current_point;
    if (delta.manhattanLength() > 30) {
        timer_show.start(500);

        float angle = atan2(delta.y(), delta.x());
        direction dir = directionFromAngle(angle, false);

        if (my_direction == ERROR) {
            my_direction = dir;
        }
        else if (dir != my_direction || stopped){
           selection();
        }

        current_point = qm->pos();
        timer_stop.start(250);
    }
}

