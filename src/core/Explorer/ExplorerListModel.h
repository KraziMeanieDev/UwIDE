#pragma once
#include <QAbstractItemModel>
#include <QDir>
#include <QFileInfo>
#include <QVector>
#include <qnamespace.h>
#include <qobject.h>

struct ExplorerListItem
{
    QString name;
    QString path;
    bool isDirectory;
    QVector<ExplorerListItem> children;
    ExplorerListItem *parent;

    ExplorerListItem(const QString &name, const QString &path, bool isDirectory, ExplorerListItem *parentItem = nullptr)
        : name(name), path(path), isDirectory(isDirectory), parent(parentItem) {};
};

class ExplorerListModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

  public:
    enum Roles
    {
        NameRole = Qt::UserRole + 1,
        PathRole,
        IsDirectoryRole
    };

    QHash<int, QByteArray> roleNames() const override
    {
        return {{NameRole, "name"}, {PathRole, "path"}, {IsDirectoryRole, "isDirectory"}};
    }

    ExplorerListModel(const QString &rootPath, QObject *parent = nullptr);
    ~ExplorerListModel() override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void browseFolder(const QString &path);
    QString rootPath() const
    {
        return m_rootPath;
    }
    void setRootPath(const QString &path);

  signals:
    void rootPathChanged();

  private:
    ExplorerListItem m_rootItem;
    QString m_rootPath;

    void populate(ExplorerListItem *parentItem, const QString &path);
    ExplorerListItem *getItem(const QModelIndex &index) const;
};