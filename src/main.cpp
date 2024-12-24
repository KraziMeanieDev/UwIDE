#include "core/CodeEditor/CodeDocumentModel.h"
#include "core/Explorer/ExplorerListModel.h"
#include "core/MenuController.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MenuController menuController;
    CodeDocumentModel codeDocumentModel;
    ExplorerListModel explorerModel("");

    QObject::connect(&menuController, &MenuController::openFolderRequested, &explorerModel,
                     &ExplorerListModel::browseFolder);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("menuController", &menuController);
    engine.rootContext()->setContextProperty("codeDocumentModel", &codeDocumentModel);
    engine.rootContext()->setContextProperty("explorerModel", &explorerModel);

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