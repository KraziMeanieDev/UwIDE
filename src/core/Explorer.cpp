#include "Explorer.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QUrl>

Explorer::Explorer(QObject *parent) : QObject(parent) {};

QStringList Explorer::folderContents() const { return m_folderContents; };

void Explorer::browseFolder(const QString &folderPath) {
  QUrl url(folderPath);
  QString localPath = url.toLocalFile();
  qDebug() << "Browsing folder: " << folderPath;
  QDir directory(localPath);
  if (directory.exists()) {
    m_folderContents.clear();
    for (const QFileInfo &entry : directory.entryInfoList(
             QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
      m_folderContents.append(entry.fileName());
    }
  }
  emit folderContentsChanged();
}