// MainWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

class AppWindow : public QMainWindow {
  Q_OBJECT

public:
  AppWindow(QWidget *parent = nullptr);

private slots:
  void newFile();
  void openFile();
  void saveFile();

private:
  QTextEdit *editor;
  void createMenuBar();
};

#endif // APPWINDOW_H
