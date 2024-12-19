#include "CodeDocumentModel.h"
#include <QFile>
#include <QTextStream>

CodeDocumentModel::CodeDocumentModel(QObject *parent)
    : QObject(parent), m_codeDocument("") {};

QString CodeDocumentModel::codeDocument() const { return m_codeDocument; }

void CodeDocumentModel::loadDocumentChunk(const QString &folderPath,
                                          int startLine, int lineCount) {
  QFile file(folderPath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return;
  }

  QTextStream lines(&file);
  QString chunk;
  int lineNumber = 0;
  while (!lines.atEnd()) {
    QString line = lines.readLine();
    if (lineNumber >= startLine && lineNumber < startLine + lineCount) {
      chunk.append(line + "\n");
    }
    if (lineNumber >= startLine + lineCount) {
      break;
    }
    lineNumber++;
  }
  file.close();

  m_codeDocument = chunk;
  emit codeDocumentChanged();
}