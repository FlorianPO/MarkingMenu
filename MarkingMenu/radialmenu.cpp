#include "radialmenu.h"

RadialMenu::RadialMenu(QWidget *parent) : QWidget(parent) {
    hide();
}


void RadialMenu::setLabelList(const std::vector<std::string>& string_vector) {

}

void RadialMenu::addLabel(std::string string) {
    if (label_vector.size() >= 8)
        throw std::string("ERREUR : maximul number of labels reached !");

    QLabel* label = new QLabel(this);
    label->setText(QString::fromStdString(string));
    label->setAutoFillBackground(false);
    label->setStyleSheet(QLatin1String("font: 75 10pt \"Calibri\";\n" "font-weight: bold;\n"));
    label->setAlignment(Qt::AlignCenter);
    label->setFrameShape(QFrame::StyledPanel);
    label->setFrameShadow(QFrame::Sunken);

    label->resize(QSize(string.size()*10, 25));
    label->show();

    label_vector.push_back(label);
}

void RadialMenu::showMenu(const QPoint& position) {
    center = position;

    float angle = 0;
    switch (label_vector.size()) {
        case 1: break;
        case 2: angle = 180.f; break;
        default:
            angle = 90.f;
    }

    QPoint point_orig(center.x() + distance, center.y());
    for (int i=0; i < label_vector.size(); i++) {
        label_vector[i]->move(point_orig.x() - label_vector[i]->size().width()/2,
                              point_orig.y() - label_vector[i]->size().height()/2);
        if (i%4 == 3 && i > 0)
            point_orig = rotationGlobal(point_orig, center, -45);
        point_orig = rotationGlobal(point_orig, center, -angle);
    }

    this->show();
}
