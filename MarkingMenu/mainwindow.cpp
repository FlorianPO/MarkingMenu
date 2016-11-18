#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>

#include "markingmenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->resize(QSize(1000,1000));

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
