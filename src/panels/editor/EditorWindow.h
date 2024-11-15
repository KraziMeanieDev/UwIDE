#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include "EditorWidget.h"
#include <QMainWindow>


class EditorWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit EditorWindow(QWidget *parent = nullptr);

  void newFile();
  bool openFile(const QString &fileName);
  bool saveFile(const QString &fileName);

signals:
  void fileError(const QString &error);

private:
  EditorWidget *editorWidget;
  QString currentFilePath;
};

#endif // EDITORWINDOW_H
