#pragma once
#include <QObject>
#include <QString>

class CodeDocumentModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString codeDocument READ codeDocument NOTIFY codeDocumentChanged)

public:
    explicit CodeDocumentModel(QObject *parent = nullptr);

    QString codeDocument() const;

    Q_INVOKABLE void loadDocumentChunk(const QString &folderPath, int startLine,
        int lineCount);
signals:
    void codeDocumentChanged();

private:
    QString m_codeDocument;
};