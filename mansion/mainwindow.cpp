#include <QString>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
//#include <vector>
//#include <QFileDialog>


#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    //falls kein Pfad für die Datenbanken gegeben, erstelle database-Ordner
    QDir path;
    QDir().mkdir("gamefiles");
    path = QDir::currentPath() + QDir::separator() +"gamefiles";
    xmlpath=QDir::currentPath() + QDir::separator() + "gamefiles" + QDir::separator() + "adventure.xml";
    //setzt QStrings in UTF-8 für Sonderzeichen
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    /**
    if(!initialize(xmlpath))
    {
        QMessageBox::critical(this, tr("Error!"),
                              tr("XML file not found!"),
                              QMessageBox::Ok);
    }
    else QMessageBox::information(this, "Information", "Init success!");
    **/
}

mainwindow::~mainwindow()
{
    delete ui;
}

/**
bool mainwindow::initialize(QString xmlname)
{
    Q_ASSERT(xmlname.length()>0);

    QFile file(xmlname);
    if (!file.open(QFile::ReadOnly))
        QMessageBox::critical(this, tr("Error!"),
                                    tr("Unable to open XML file!"),
        QMessageBox::Ok);


        //lies txt in QStringList
        QStringList stringList;
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        while (true)
        {
            QString line = textStream.readLine();
            if (line.isNull())
                break;
            else
                stringList.append(line);
        }
        file.close();



        QXmlStreamReader xml(&file);
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
                    if(token == QXmlStreamReader::StartDocument)
                    {
                        continue;
                    }

                    if(token == QXmlStreamReader::StartElement)
                    {
                        if(xml.name() == "data")
                        {
                            continue;
                        }

                        if(xml.name() == "video")
                        {
                            xml.readNext();
                            //qDebug() <<xml.name().toString();
                            while (!xml.atEnd())
                            {
                                if (xml.isStartElement())
                                {
                                    if(xml.name() == "url")
                                    {
                                        curV = xml.readElementText();
                                    }
                                    if(xml.name() == "title")
                                    {
                                        curT = xml.readElementText();
                                    }
                                    if (xml.name() == "user")
                                    {
                                        curU = xml.readElementText();
                                    }
                                    if (xml.name() == "comment")
                                    {
                                        curC = xml.readElementText();
                                        dummyrecord.setValue("title",curT);
                                        dummyrecord.setValue("video",curV);
                                        dummyrecord.setValue("user",curU);
                                        dummyrecord.setValue("comment",curC);
                                        model->insertRecord(-1,dummyrecord);
                                    }
                                }
                                xml.readNext();
                                //qDebug() <<xml.name().toString();
                            }
                        }
                        xml.readNext();
                    }
                    //
                     if(token == QXmlStreamReader::EndDocument)
                     {
                         //qDebug() << "Ende";
                         QMessageBox::information(this, "Information", "Import complete!");
                         break;
                     }
                     //
        }
        file.close();



    }
    else return false;
    return true;
}
**/
