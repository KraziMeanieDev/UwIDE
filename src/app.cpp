#include "app.h"
#include <QAction>
#include <QFile>
#include <QFileDevice>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("UwIDE");
  setFixedSize(1280, 700);

  createMenuBar();
}

void AppWindow::createMenuBar() {
  // Create the text editor area
  editor = new QTextEdit(this);
  setCentralWidget(editor);

  // Create the "file" Menu
  QMenuBar *menuBar = new QMenuBar(this);
  QMenu *fileMenu = menuBar->addMenu(tr("File"));

  // Create actions for the "File" Menu
  QAction *newFileAction = new QAction(tr("New"), this);
  QAction *openFileAction = new QAction(tr("Open"), this);
  QAction *saveFileAction = new QAction(tr("Save"), this);

  // Add actions to "File" Menu
  fileMenu->addAction(newFileAction);
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);

  // Set Menu bar
  setMenuBar(menuBar);

  // Connect actions to respective slots
  connect(newFileAction, &QAction::triggered, this, &AppWindow::newFile);
  connect(openFileAction, &QAction::triggered, this, &AppWindow::openFile);
  connect(saveFileAction, &QAction::triggered, this, &AppWindow::saveFile);
}

// Define Slots for Files
void AppWindow::newFile() {
  if (!editor->toPlainText().isEmpty()) {
    QMessageBox::warning(this, "New File",
                         "Do you want to save the current file?");
  } else {
    editor->clear();
  }
}

void AppWindow::openFile() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open File", "", "Text Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly) | QIODevice::Text) {
      QTextStream in(&file);
      QString content = in.readAll();
      editor->setPlainText(content);
      file.close();
    } else {
      QMessageBox::warning(this, "Error", "Could not open file!");
    }
  }
}

void AppWindow::saveFile() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save File", "", "Text Files (*.txt);;All Files (*)");
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly) | QIODevice::Text) {
      QTextStream out(&file);
      out << editor->toPlainText();
      file.close();
    } else {
      QMessageBox::warning(this, "Error", "Could not save this file!");
    }
  }
}