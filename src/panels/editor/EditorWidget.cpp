#include "EditorWidget.h"

EditorWidget::EditorWidget(QWidget *parent) : QWidget(parent) {
  editor = new QTextEdit(this);

  // Create a layout and add the QTextEdit widget to it
  layout = new QVBoxLayout(this);
  layout->addWidget(editor);

  setLayout(layout); // Set the layout for the widget

  editor->setFocus();

  qDebug() << "EditorWidget has been created";
}

QString EditorWidget::getText() const { return editor->toPlainText(); }

void EditorWidget::setText(const QString &text) { editor->setPlainText(text); }

void EditorWidget::clearEditor() { editor->clear(); }

bool EditorWidget::isEmpty() const { return editor->toPlainText().isEmpty(); }
