#include "Explorer.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QUrl>

Explorer::Explorer(QObject *parent) : QObject(parent) {};

QVariantList Explorer::folderContents() const { return m_folderContents; };

void Explorer::browseFolder(const QString &folderPath) {
  updateFolderContents(folderPath);
  // QUrl url(folderPath);
  // QString localPath = url.toLocalFile();
  // qDebug() << "Browsing folder: " << folderPath;
  // QDir directory(localPath);
  // if (directory.exists()) {
  //   m_folderContents.clear();
  //   for (const QFileInfo &entry : directory.entryInfoList(
  //            QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
  //     m_folderContents.append(entry.fileName());
  //   }
  // }
  // emit folderContentsChanged();
}

void Explorer::updateFolderContents(const QString &folderPath) {
  QUrl url(folderPath);
  QString localPath = url.toLocalFile();
  QDir directory(localPath);

  if (!directory.exists()) {
    qWarning() << "Invalid folder path: " << folderPath;
    return;
  }

  QFileInfoList files =
      directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

  m_folderContents.clear();
  for (const QFileInfo &fileInfo : files) {
    QVariantMap folderMap;
    folderMap["name"] = fileInfo.fileName();
    folderMap["path"] = fileInfo.absoluteFilePath();

    m_folderContents.append(folderMap);
  }

  // qDebug() << "Folder contents updated:";
  // for (const QVariant &item : m_folderContents) {
  //   qDebug() << item.toMap()["name"].toString();
  // }

  emit folderContentsChanged();
}