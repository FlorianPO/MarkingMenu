#include "mainwindow.h"
#include <QApplication>
#include "radialmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(QSize(1350, 900));
    w.show();

    // RadialMenu creation
    RadialMenu* m1 = new RadialMenu();
    RadialMenu* m2_1 = new RadialMenu();
    RadialMenu* m2_2 = new RadialMenu();
    RadialMenu* m2_3 = new RadialMenu();
    RadialMenu* m2_4 = new RadialMenu();
    m1->addMenu("Print", m2_1);
    m1->addMenu("Maze", m2_2);
    m1->addMenu("Challenge", m2_3);
    m1->addMenu("Greetings", m2_4);

    m2_1->addAction("Hello", new std::function<void(void)>([](){qDebug("hello");}));
    m2_1->addAction("World", new std::function<void(void)>([](){qDebug("world");}));
    m2_1->addAction("C++", new std::function<void(void)>([](){qDebug("BEAST MODE ACTIVATED");}));
    m2_1->addAction("Java", new std::function<void(void)>([](){qDebug("*wind*");}));
    m2_1->addAction("5", new std::function<void(void)>([](){qDebug("55555");}));
    m2_1->addAction("6", new std::function<void(void)>([](){qDebug("666666");}));
    m2_1->addAction("7", new std::function<void(void)>([](){qDebug("7777777");}));
    m2_1->addAction("8", new std::function<void(void)>([](){qDebug("88888888");}));

    RadialMenu* m2_21 = new RadialMenu();
    m2_2->addMenu("?", m1);
    m2_2->addMenu("?", m1);
    m2_2->addMenu("?", m2_21);
    m2_2->addMenu("?", m1);
    RadialMenu* m2_22 = new RadialMenu();
    m2_21->addMenu("?", m1);
    m2_21->addMenu("?", m1);
    m2_21->addMenu("?", m1);
    m2_21->addMenu("?", m2_22);

    m2_22->addAction("?", new std::function<void(void)>([](){qDebug("You just wasted 1 min of your life");}));
    m2_22->addMenu("?", m1);
    m2_22->addMenu("?", m1);
    m2_22->addMenu("?", m1);

    RadialMenu* m2_31 = new RadialMenu();
    m2_3->addMenu(" ", m1);
    m2_3->addMenu("THE", m2_31);
    m2_3->addMenu(" ", m1);
    m2_3->addMenu(" ", m1);
    RadialMenu* m2_32 = new RadialMenu();
    m2_31->addMenu(" ", m1);
    m2_31->addMenu(" ", m1);
    m2_31->addMenu("GOAL", m2_32);
    m2_31->addMenu(" ", m1);
    RadialMenu* m2_33 = new RadialMenu();
    m2_32->addMenu(" ", m1);
    m2_32->addMenu(" ", m1);
    m2_32->addMenu("IS", m2_33);
    m2_32->addMenu(" ", m1);
    RadialMenu* m2_34 = new RadialMenu();
    m2_33->addMenu("TO", m2_34);
    m2_33->addMenu(" ", m1);
    m2_33->addMenu(" ", m1);
    m2_33->addMenu(" ", m1);
    RadialMenu* m2_35 = new RadialMenu();
    m2_34->addMenu(" ", m1);
    m2_34->addMenu(" ", m1);
    m2_34->addMenu(" ", m1);
    m2_34->addMenu("REACH", m2_35);
    RadialMenu* m2_36 = new RadialMenu();
    m2_35->addMenu("ME", m2_36);
    m2_35->addMenu(" ", m1);
    m2_35->addMenu(" ", m1);
    m2_35->addMenu(" ", m1);
    RadialMenu* m2_37 = new RadialMenu();
    m2_36->addMenu(" ", m1);
    m2_36->addMenu(" ", m1);
    m2_36->addMenu("WHILE", m2_37);
    m2_36->addMenu(" ", m1);

    m2_37->addAction("HIDDEN", new std::function<void(void)>([](){qDebug(":)");}));
    m2_37->addMenu(" ", m1);
    m2_37->addMenu(" ", m1);
    m2_37->addMenu(" ", m1);

    m2_4->addMenu("NICE", m1);
    m2_4->addMenu("HAVE", m1);
    m2_4->addMenu("A", m1);
    m2_4->addMenu("DAY", m1);

    m1->setRootMenu(); // Set as top of the tree

    return a.exec();
}
