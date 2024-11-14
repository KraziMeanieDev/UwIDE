// MainWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class AppWindow : public QMainWindow {
  Q_OBJECT

public:
  AppWindow(QWidget *parent = nullptr);

private slots:
  void onButtonClicked(); // Slot for button click

private:
  QPushButton *button; // Button member
};

#endif // APPWINDOW_H
