#include "core/Explorer.h"
#include "core/MenuController.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  MenuController menuController;
  Explorer explorer;

  QObject::connect(&menuController, &MenuController::openFolderRequested,
                   &explorer, &Explorer::browseFolder);

  QQmlApplicationEngine engine;

  engine.rootContext()->setContextProperty("menuController", &menuController);
  engine.rootContext()->setContextProperty("explorer", &explorer);

  using namespace Qt::StringLiterals;
  const QUrl url(u"qrc:/src/main.qml"_s);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}