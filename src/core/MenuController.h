#pragma once
#include <QObject>

class MenuController : public QObject {
  Q_OBJECT

public:
  explicit MenuController(QObject *parent = nullptr);
signals:
  void openFolderRequested(const QString &folderPath);
public slots:
  void handleMenuAction(const QString &actionName);
};