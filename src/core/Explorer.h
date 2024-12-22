#pragma once
#include <QDebug>
#include <QObject>
#include <QVariantList>

class Explorer : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList folderContents READ folderContents NOTIFY
            folderContentsChanged);

public:
    explicit Explorer(QObject *parent = nullptr);
    QVariantList folderContents() const;
public slots:
    void browseFolder(const QString &folderPath);
    void updateFolderContents(const QString &folderPath);
signals:
    void folderContentsChanged();

private:
    QVariantList m_folderContents;
};