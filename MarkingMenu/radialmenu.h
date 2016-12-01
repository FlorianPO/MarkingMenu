#ifndef RADIALMENU_H
#define RADIALMENU_H

#include <QWidget>
#include <QLabel>
#include <functional>
#include <QTimer>

/*
 * This class reprensents a circular menu
 * which can contain up to 8 elements that can
 * be either a RadialMenu or a lambda
 * function.
 *
 * The elements are positioned prior to RIGHT, UP,
 * LEFT and DOWN.
 *
 * To use the widget, use RightClick. Maintaining it
 * for 0.5s will show the widget. When the widget is hidden,
 * mouse movements can be performed with very short moves.
 *
 * Only one RadialMenu is showed at the screen, otherwise
 * it would be hard to properly see them (overlapping).
 * Thus, there is no line displayed beetween the RadialMenus.
 *
 * This could lead to some optimizations, where only one
 * graphic widget is actually created.
 */
class RadialMenu : public QWidget
{
    Q_OBJECT
public:
    RadialMenu();
    ~RadialMenu();

    // Add a sub_menu <rw> named <string>
    void addMenu(const std::string& string, RadialMenu* rw);
    // Add a lambda_function <function> named <string> (<handle_delete> == false if you want to free the lambda manualy)
    void addAction(const std::string& string, std::function<void(void)>* function, bool handle_delete=true);
    // Set the radial menu as top of the tree
    void setRootMenu();

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
        NOT_RESOLVED
    };

    // Contains either a RadialMenu, or a lambda function
    struct radial_struct {
        QLabel* label;
        RadialMenu* rw;
        std::function<void(void)>* function;
        bool handle_delete;
    };

    friend class MarkingMenu;
    void activate(const QPoint& position, bool show=false); // Activate the widget
    void deactivate(); // Deactivate the widget
    void selection(); // Resolve according to the direction dragged
    void mouseMoveEvent(QMouseEvent* qm) override; // Called by the MarkingMenu (Qt issue)

    QLabel* createLabel(const std::string& string); // Create a named label to be displayed
    direction directionFromAngle(float angle, bool deg=true);

    private slots:
        void showMenu(); // Show the menu
        void selectionStop(); // Variant of selection(), called when drags end

private:
    QPoint center;  // Center of the circular widget
    QPoint current_point; // Current position considered
    QPoint current_mouse; // Current mouse position
    direction my_direction; // Direction considered
    QTimer timer_show; // A timer to show the widget
    QTimer timer_stop; // A timer to detect end of mouse drags
    bool resolved;

    std::vector<radial_struct> struct_vector; // Sub_menus or lambda functions
};

#define PI 3.14159265358979323846
// Rotate a point around another
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
