#ifndef RADIALMENU_H
#define RADIALMENU_H

#include <QWidget>
#include <QLabel>

class RadialMenu : public QWidget
{
    Q_OBJECT
public:
    explicit RadialMenu(QWidget *parent = 0);

    void setLabelList(const std::vector<std::string>& string_vector);
    void addLabel(std::string string);

    // Sets the menu's center position and displays it
    void showMenu(const QPoint& position);

signals:

public slots:

private:
    std::vector<QLabel*> label_vector;
    QPoint center;

    // Distance between center and a label
    const int distance = 100;
};

#define PI 3.14159265358979323846
inline QPoint rotationGlobal(const QPoint& toRot, const QPoint& center, double angle, bool deg=true) {
    if (deg == true)
        angle = angle / 180 * PI;

    double x = toRot.x();
    double y = toRot.y();
    double x_temp;

    x -= center.x();
    y -= center.y();
    x_temp = x;
    x = x*std::cos(angle) - y*std::sin(angle);
    y = y*std::cos(angle) + x_temp*std::sin(angle);
    x += center.x();
    y += center.y();

    return QPoint(x, y);
}

#endif // RADIALMENU_H
