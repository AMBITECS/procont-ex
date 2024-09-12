#include "filesmanager.h"
#include "xmlparser.h"

#include <QFile>
#include <QTextStream>
#include <QStringListModel>
#include <QDir>
#include <QMessageBox>

FilesManager::FilesManager(QWidget *parent)
    : QWidget(parent)
{
    QStringList list;
    _filesViewModel = new QStringListModel(list);
    _parser = new XmlParser();
    _parser->typesFromFile(":/resources/types.txt");
    _stFilesDirName = "st_files";
    _stFilesDir = new QDir();
    _stFilesDir->mkdir(_stFilesDirName);
    _stFilesDir->cd(_stFilesDirName);
}

FilesManager::~FilesManager()
{

}

QStringListModel *FilesManager::getFilesViewModel()
{
    return _filesViewModel;
}

void FilesManager::setListToModel(QStringList list)
{
    _filesViewModel->setStringList(list);
}

void FilesManager::saveStFile(const QString filename, const QString data)
{
    if (filename.isEmpty())
        return;

    QFile file(_stFilesDir->canonicalPath() + "/" + filename + ".st");


    //Open the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << data;

    file.close();
}

QString FilesManager::openStFile(const QString &filename)
{
    if (filename.isEmpty())
        return "";
    else {

        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return "";
        }
        return file.read(file.size());
    }
}

void FilesManager::importXml(const QString & fileName)
{
    _parser->importFromXml(fileName);
    QStringList list = _parser->getFilesNames();

    _filesViewModel->setStringList(list);

    for (auto i = 0; i < list.size(); ++i)
    {
        saveStFile(QString(list.at(i) + "_vars"), _parser->getPouVarsText(i));
        saveStFile(QString(list.at(i) + "_body"), _parser->getPouBodyText(i));
    }
}

void FilesManager::exportXml(QString & fileName)
{
    //Save File

    if (fileName.isEmpty())
        return;

    if (!fileName.contains(".xml"))
    {
        fileName += ".xml";
    }

    auto * pous = _parser->getPous();
    pous->clear();
    for (const auto name : _filesViewModel->stringList())
    {
        pous->append(converFileToPou(QString(_stFilesDirName + "/" + name )));
        //analyzeFile(QString(st_files_dir_name + "/" + name + "_vars.st"));
    }

    _parser->exportToXml(fileName);
}

QString FilesManager::getVarsData(const QModelIndex &index)
{
    return openStFile(_stFilesDir->canonicalPath() + "/" + QString(_filesViewModel->data(index).toString() + "_vars.st"));
}

QString FilesManager::getBodyData(const QModelIndex &index)
{
    return openStFile(_stFilesDir->canonicalPath() + "/" + QString(_filesViewModel->data(index).toString() + "_body.st"));
}

void FilesManager::delteStFolder()
{
    qDebug() << "DELETE";
    _stFilesDir->removeRecursively();
}

Pou FilesManager::converFileToPou(const QString &filename)
{
    QStringList stringList;
    QFile textFile(filename + "_vars.st");
    if (!textFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    //... (open the file for reading, etc.)
    QTextStream textStream(&textFile);
    Pou pou;
    QString pou_name = filename;
    QStringList path = pou_name.split("/");
    if (!path.isEmpty())
    {
        pou.name = path[path.size() - 1].replace("_vars.st", "");
    }

    while (true)
    {
        QString line = textStream.readLine();

        if (line.isNull())
            break;
        else {
            Variable variable;
            line.replace(" ", "");
            line.replace("\t", "");
            QStringList list_values = line.split(":=");

            if (list_values.size() > 1)
            {
                QStringList list_types = list_values.at(0).split(":");
                if (list_types.size() > 1)
                {
                    variable.name = list_types.at(0);
                    variable.type = list_types.at(1);
                    variable.initialValue.simpleValue.value = list_values.at(1);
                    pou.interface.setVariable(variable);
                } else {
                    variable.name = list_values.at(0);
                    variable.type = list_values.at(1);
                    pou.interface.setVariable(variable);
                }
            } else {
                QStringList list_types = list_values.at(0).split(":");
                if (list_types.size() > 1) {
                    variable.name = list_types.at(0);
                    variable.type = list_types.at(1);
                    pou.interface.setVariable(variable);
                }
            }
        }
    }
    textFile.close();

    QFile bodyFile(filename + "_body.st");
    if (!bodyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    //... (open the file for reading, etc.)
    QTextStream bodyStream(&bodyFile);
    QString body;

    while (true)
    {
        QString line = bodyStream.readLine();

        if (line.isNull())
            break;
        else {
            body += line + "\n";
        }
    }
    pou.body.value = body;
    return pou;
}





