#pragma once
#include <QDebug>
#include <QObject>
#include <QStringList>

class Explorer : public QObject {
  Q_OBJECT
  Q_PROPERTY(QStringList folderContents READ folderContents NOTIFY
                 folderContentsChanged);

public:
  explicit Explorer(QObject *parent = nullptr);
  QStringList folderContents() const;
public slots:
  void browseFolder(const QString &folderPath);
signals:
  void folderContentsChanged();

private:
  QStringList m_folderContents;
  void updateFolderContents(const QString &folderPath);
};