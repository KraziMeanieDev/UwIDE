#include "AppWindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("UwIDE");
  setFixedSize(1280, 700);

  editorWindow = new EditorWindow(this);
  setCentralWidget(editorWindow);

  createMenuBar();
}

void AppWindow::createMenuBar() {
  QMenuBar *menuBar = new QMenuBar(this);
  QMenu *fileMenu = menuBar->addMenu(tr("File"));

  QAction *newFileAction = new QAction(tr("New"), this);
  QAction *openFileAction = new QAction(tr("Open"), this);
  QAction *saveFileAction = new QAction(tr("Save"), this);

  fileMenu->addAction(newFileAction);
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);

  setMenuBar(menuBar);

  connect(newFileAction, &QAction::triggered, this, &AppWindow::newFile);
  connect(openFileAction, &QAction::triggered, this, &AppWindow::openFile);
  connect(saveFileAction, &QAction::triggered, this, &AppWindow::saveFile);
}

void AppWindow::newFile() { editorWindow->newFile(); }

void AppWindow::openFile() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open File", "", "Text Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    editorWindow->openFile(fileName);
  }
}

void AppWindow::saveFile() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save File", "", "Text Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    editorWindow->saveFile(fileName);
  }
}

void AppWindow::handleFileError(const QString &error) {
  QMessageBox::warning(this, "File Error", error);
}
