#include "MenuController.h"
#include <QDebug>

MenuController::MenuController(QObject *parent)
    : QObject(parent) {};

void MenuController::handleMenuAction(const QString &actionName)
{
    if (actionName == "OpenFolder") {
        emit openFolderRequested("");
    } else {
        qDebug() << "Unknown Menu Action: " << actionName;
    }
}
