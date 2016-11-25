#ifndef RADIALMENU_H
#define RADIALMENU_H

#include <QWidget>
#include <QLabel>
#include <functional>
#include <QTimer>

class RadialMenu : public QWidget
{
    Q_OBJECT
public:
    explicit RadialMenu(QWidget *parent = 0);

    void addMenu(const std::string& string, RadialMenu* rw);
    void addAction(const std::string& string, std::function<void(void)>* function);
    void activate(const QPoint& position);

    void mouseMoveEvent(QMouseEvent* qm) override;
    void hideEvent(QHideEvent* event) override;

private:
    enum direction {
        EAST = 0,
        NORTH_EAST = 4,
        NORTH = 1,
        NORTH_WEST = 5,
        WEST = 2,
        SOUTH_WEST = 6,
        SOUTH = 3,
        SOUTH_EAST = 7,
        ERROR
    };

    direction directionFromAngle(float angle, bool deg=true);

    QLabel* createLabel(const std::string& string);

    struct radial_struct {
        QLabel* label;
        RadialMenu* rw;
        std::function<void(void)>* function;
    };

    const int distance = 100;
    QPoint center;
    QPoint current_point;
    direction my_direction;
    QTimer timer_show;
    QTimer timer_stop;
    bool stopped;

    std::vector<radial_struct> struct_vector;

private slots:
    void showMenu();
    void selection();
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
