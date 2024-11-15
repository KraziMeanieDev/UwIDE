#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "panels/editor/EditorWindow.h"
#include <QMainWindow>


class AppWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit AppWindow(QWidget *parent = nullptr);

private slots:
  void newFile();
  void openFile();
  void saveFile();
  void handleFileError(const QString &error);

private:
  void createMenuBar();
  EditorWindow *editorWindow;
};

#endif // APPWINDOW_H
