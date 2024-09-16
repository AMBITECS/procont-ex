#pragma once

#include <QString>
#include <QObject>
#include <QWidget>

class XmlParser;
class QListView;
class QStringListModel;
class QDir;
class Pou;

class FilesManager : public QWidget
{
public:
    FilesManager(QWidget *parent = nullptr);
    ~FilesManager();
    QStringListModel * getFilesViewModel();
    void setListToModel(QStringList list);
    void saveStFile(const QString filename, const QString data = "");
    QString openStFile(const QString & filename);
    void importXml(const QString & fileName);
    void exportXml(QString & filename);
    QString getVarsData(const QModelIndex & index);
    QString getBodyData(const QModelIndex & index);
    void delteStFolder();

private:
    Pou converFileToPou(const QString & filename);

private:
    XmlParser * _parser;
    QListView * _filesView;
    QStringListModel * _filesViewModel;
    //QModelIndex current_index;
    //bool is_start = true;
    QDir *  _stFilesDir;
    QString _stFilesDirName;
};

