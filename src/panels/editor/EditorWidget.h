#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class EditorWidget : public QWidget {
  Q_OBJECT

public:
  explicit EditorWidget(QWidget *parent = nullptr);

  QString getText() const;
  void setText(const QString &text);
  void clearEditor();
  bool isEmpty() const;

private:
  QPlainTextEdit *editor;
  QVBoxLayout *layout;
};

#endif // EDITORWIDGET_H
