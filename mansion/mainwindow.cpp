#include <QString>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <vector>
//#include <QFileDialog>

#include "gameslide.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    /**
    testEdit = new QTextEdit(this);
    //testEdit->setStyleSheet("QTextEdit { height:50px; width:200px; margin-top: 50px; }");
    testEdit->append("01");
    //testEdit->show();
    testEdit->append("02");

    QImage myImage;
    myImage.load("image.jpg");
    testLabel = new QLabel(this);
    testLabel->setPixmap(QPixmap::fromImage(myImage));
    //testLabel.show();
    **/

    centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );

    but01=new QPushButton("01");
    but02=new QPushButton("02");

    slideTextEdit = new QTextEdit(this);
    slideTextEdit->setReadOnly(true);
    slideTextEdit->append("01");
    slideTextEdit->append("02");

    QImage myImage;
    myImage.load("image.jpg");
    slideImageLabel = new QLabel(this);
    slideImageLabel->setPixmap(QPixmap::fromImage(myImage));

    mainBox = new QVBoxLayout(centralWidget);
    mainBox->addWidget(slideImageLabel);
    mainBox->addWidget(but01);
    mainBox->addWidget(slideTextEdit);
    mainBox->addWidget(but02);
    //setLayout(mainBox);


    /**
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(testLabel, 0, 1);
    gridLayout->addWidget(testEdit, 1, 1);
    setLayout(gridLayout);
    **/

    //ui->setupUi(this);

    //falls kein Pfad für die Datenbanken gegeben, erstelle database-Ordner
    QDir path;
    QDir().mkdir("gamefiles");
    path = QDir::currentPath() + QDir::separator() +"gamefiles";
    xmlpath=QDir::currentPath() + QDir::separator() + "gamefiles" + QDir::separator() + "adventure.xml";
    imgpath=QDir::currentPath() + QDir::separator() + "gamefiles" + QDir::separator() + + "images" + QDir::separator();
    //setzt QStrings in UTF-8 für Sonderzeichen
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    initialize();
}

mainwindow::~mainwindow()
{
    delete ui;
}


//textEditBody->setText(tmpMailContent->mailBody.replace("\\linebreak", "\n\r"));



void mainwindow::initialize()
{
    Q_ASSERT(xmlpath.length()>0);

    QFile file(xmlpath);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error!"),
                                    tr("Unable to open XML file!"),
        QMessageBox::Ok);
        return;
    }

    GameSlide *slide;
    int goal;
    QString req, name;
    QXmlStreamAttributes attributes;

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "game") {
                continue;
            }
            if(xml.name() == "slide") {
                //qDebug() << xml.name().toString();
                slide=new GameSlide();
                attributes = xml.attributes();
                if(attributes.hasAttribute("id")) {
                    slide->setId(attributes.value("id").toString().toInt());
                    //qDebug() << attributes.value("id").toString();
                }
                xml.readNext();
                //while (!xml.atEnd()) {
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "slide")) {
                    //qDebug() <<xml.name().toString();
                    if (xml.isStartElement()) {
                        if(xml.name() == "img") {
                            //QMessageBox::information(this, "Info", xml.readElementText());
                            slide->setImg(xml.readElementText());
                            //qDebug() << xml.name().toString();
                            //qDebug() << xml.readElementText();
                        }
                        if(xml.name() == "txt") {
                            slide->setTxt(xml.readElementText());
                            //qDebug() << xml.name().toString();
                            //qDebug() << xml.readElementText();
                        }
                        if (xml.name() == "items") {
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "items")) {
                                if (xml.isStartElement()) {
                                    if(xml.name() == "item") {
                                        slide->addItems(xml.readElementText());
                                        //qDebug() << xml.name().toString();
                                        //qDebug() << xml.readElementText();
                                    }
                                }
                                xml.readNext();
                            }
                        }
                        if (xml.name() == "stats") {
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "stats")) {
                                if (xml.isStartElement()) {
                                    if(xml.name() == "stat") {
                                        slide->addStats(xml.readElementText());
                                        //qDebug() << xml.name().toString();
                                        //qDebug() << xml.readElementText();
                                    }
                                }
                                xml.readNext();
                            }
                        }
                        if(xml.name() == "money") {
                            slide->setMoney(xml.readElementText().toInt());
                            //qDebug() << xml.name().toString();
                            //qDebug() << xml.readElementText();
                        }
                        if(xml.name() == "karma") {
                            //qDebug() << xml.name().toString();
                            //qDebug() << xml.readElementText();
                            slide->setKarma(xml.readElementText().toInt());
                        }
                        if (xml.name() == "options") {
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "options")) {
                                if (xml.isStartElement()) {
                                    if(xml.name() == "option") {
                                        attributes = xml.attributes();
                                        if(attributes.hasAttribute("slide")) {
                                            goal=attributes.value("slide").toString().toInt();
                                        }
                                        if(attributes.hasAttribute("req")) {
                                            if(attributes.hasAttribute("name")) {
                                                req=attributes.value("req").toString();
                                                name=attributes.value("name").toString();
                                            }
                                            else QMessageBox::critical(this, tr("Error!"),
                                                                       tr("Option with req missing name found."),
                                                                        QMessageBox::Ok);
                                        }
                                        else
                                        {
                                            req="";
                                            name="";
                                        }
                                        //qDebug() << xml.name().toString();
                                        //qDebug() << attributes.value("slide").toString();
                                        //qDebug() << attributes.value("req").toString();
                                        //qDebug() << xml.readElementText();
                                    }
                                    slide->addOptions(goal, req, name, xml.readElementText());
                                }
                                xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                    //qDebug() <<xml.name().toString();
                }
                slides.append(slide);
                xml.readNext();
            }
        }
        /**
        if(token == QXmlStreamReader::EndDocument) {
            //qDebug() << "Ende";
            QMessageBox::information(this, "Information", "Import complete!");
            break;
        }
        **/
    }

    /* Error handling. */
    if(xml.hasError()) {
        QMessageBox::critical(this,
                              "QXSRExample::parseXML",
                              xml.errorString(),
                              QMessageBox::Ok);
    }
    /* Removes any device() or data from the reader
     * and resets its internal state to the initial state. */
    xml.clear();
    file.close();
}

