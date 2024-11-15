#include "EditorWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

EditorWindow::EditorWindow(QWidget *parent) {
  editorWidget = new EditorWidget(this); // Initialize the new EditorWidget
  setCentralWidget(
      editorWidget); // Set it as the central widget for EditorWindow
}

void EditorWindow::newFile() {
  if (!editorWidget->isEmpty()) {
    // Show a prompt asking to save the current file before creating a new one
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Unsaved Changes", "Do you want to save the current file?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
      saveFile(currentFilePath); // Save the file before creating a new one
    } else if (reply == QMessageBox::Cancel) {
      return;
    }
  }

  editorWidget->clearEditor(); // Clear the editor for a new file
  currentFilePath.clear();     // Reset the current file path
}
bool EditorWindow::openFile(const QString &fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Could not open file!");
    return false;
  }

  QTextStream in(&file);
  editorWidget->setText(
      in.readAll()); // Set text using EditorWidget's setText method
  file.close();
  currentFilePath = fileName;
  return true;
}

bool EditorWindow::saveFile(const QString &fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Could not save this file!");
    return false;
  }

  QTextStream out(&file);
  out << editorWidget
             ->getText(); // Get text using EditorWidget's getText method
  file.close();
  currentFilePath = fileName;
  return true;
}
