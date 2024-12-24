#include "ExplorerListModel.h"
#include <QDebug>
#include <QDir> // Include QDir
#include <QDirIterator>
#include <Qurl>

ExplorerListModel::ExplorerListModel(const QString &rootPath, QObject *parent)
    : QAbstractItemModel(parent), m_rootPath(rootPath),
      m_rootItem("", "", false) // Initialize with default values if rootPath is empty
{
    if (!m_rootPath.isEmpty()) {
        m_rootItem.name = QFileInfo(m_rootPath).fileName();
        m_rootItem.path = QFileInfo(m_rootPath).absoluteFilePath();
        populate(&m_rootItem, m_rootPath);
    }
};

ExplorerListModel::~ExplorerListModel() {};

void ExplorerListModel::browseFolder(const QString &path)
{
    setRootPath(path);
}

QModelIndex ExplorerListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ExplorerListItem *parentItem = getItem(parent);
    if (parentItem && row >= 0 && row < parentItem->children.count()) {
        return createIndex(row, column, &parentItem->children[row]);
    }

    return QModelIndex();
};

QModelIndex ExplorerListModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    ExplorerListItem *childItem = getItem(child);
    if (childItem && childItem->parent != &m_rootItem) {
        if (childItem->parent) {
            for (int row = 0; row < childItem->parent->children.count(); row++) {
                if (&childItem->parent->children[row] == childItem) {
                    return createIndex(row, 0, childItem->parent);
                }
            }
        }
    };

    return QModelIndex();
};

int ExplorerListModel::rowCount(const QModelIndex &parent) const
{
    ExplorerListItem *parentItem = getItem(parent);
    return parentItem ? parentItem->children.count() : 0;
};

int ExplorerListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
};

QVariant ExplorerListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ExplorerListItem *item = getItem(index);

    switch (role) {
    case NameRole:
    case Qt::DisplayRole:
        return item->name;
    case PathRole:
        return item->path;
    case IsDirectoryRole:
        return item->isDirectory;
    default:
        return QVariant();
    }
}

QVariant ExplorerListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0)
            return "Name";
    }
    return QVariant();
};

void ExplorerListModel::populate(ExplorerListItem *parentItem, const QString &path)
{
    qDebug() << "Attempting to populate path:" << path;

    QDir directory(path);
    if (!directory.exists()) {
        qDebug() << "Directory does not exist:" << path;
        return;
    }

    parentItem->children.clear();

    // Set filters for directory listing
    QFileInfoList entries = directory.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::DirsFirst);

    qDebug() << "Found" << entries.count() << "entries in directory";

    for (const QFileInfo &fileInfo : entries) {
        QString name = fileInfo.fileName();
        QString fullPath = fileInfo.absoluteFilePath();
        bool isDir = fileInfo.isDir();

        ExplorerListItem childItem(name, fullPath, isDir, parentItem);
        parentItem->children.append(childItem);

        qDebug() << "Added:" << name << "(Directory:" << isDir << ")";
    }

    qDebug() << "Finished populating. Total items:" << parentItem->children.count();
}

void ExplorerListModel::setRootPath(const QString &path)
{
    // Convert URL to local file path
    QString localPath = QUrl(path).toLocalFile();
    qDebug() << "Converting URL:" << path << "to local path:" << localPath;

    if (m_rootPath != localPath) {
        beginResetModel();
        m_rootPath = localPath;
        m_rootItem.children.clear();

        if (!m_rootPath.isEmpty()) {
            QFileInfo rootInfo(m_rootPath);
            m_rootItem.name = rootInfo.fileName();
            m_rootItem.path = rootInfo.absoluteFilePath();
            m_rootItem.isDirectory = true;
            populate(&m_rootItem, m_rootPath);
        }

        endResetModel();
        emit rootPathChanged();
    }
}

ExplorerListItem *ExplorerListModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<ExplorerListItem *>(index.internalPointer());
    }
    return const_cast<ExplorerListItem *>(&m_rootItem);
}