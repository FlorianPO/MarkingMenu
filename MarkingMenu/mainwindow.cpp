#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>

#include "markingmenu.h"

MainWindow::MainWindow(const QSize& size) : QMainWindow(0) {
    this->resize(size);

    QVBoxLayout* layout = new QVBoxLayout();
    QWidget* central = new QWidget(this);
    central->setLayout(layout);

    marking_menu = new MarkingMenu();
    layout->addWidget(marking_menu);

    setCentralWidget(central);
}

MainWindow::~MainWindow() {
    delete marking_menu;
}
