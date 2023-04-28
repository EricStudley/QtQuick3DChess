#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ChessModel.h"
#include "ChessController.h"
#include "ChessEnums.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ChessModel* chessModel = new ChessModel(&app);
    ChessController *chessController = new ChessController(chessModel, &app);

    qmlRegisterUncreatableType<ChessEnums>("Chess", 1, 0, "PieceType", "Error: PieceType is an uncreatable enum type.");
    qmlRegisterUncreatableType<ChessEnums>("Chess", 1, 0, "ChessPage", "Error: ChessPage is an uncreatable enum type.");

    engine.rootContext()->setContextProperty("chessModel", chessModel);
    engine.rootContext()->setContextProperty("chessController", chessController);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
