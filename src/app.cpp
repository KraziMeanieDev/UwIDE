#include "app.h"
#include <QMessageBox>
#include <iostream>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("UwIDE");
  setFixedSize(1280, 700);

  button = new QPushButton("Welcome!!!", this);
  button->setGeometry(150, 130, 100, 40);
  connect(button, &QPushButton::clicked, this, &AppWindow::onButtonClicked);
}

void AppWindow::onButtonClicked() {
  std::cout << "Button was clicked" << std::endl;
  QMessageBox::information(this, "Hello", "Button was Clicked");
}