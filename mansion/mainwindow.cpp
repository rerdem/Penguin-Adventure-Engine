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
    centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );

    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(tr("&About"), this, SLOT(close()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Save"), this, SLOT(close()));
    fileMenu->addAction(tr("&Load"), this, SLOT(close()));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Quit"), this, SLOT(close()));


    //ui->setupUi(this);

    //if it doesn't exist, create gamefiles folder
    QDir path;
    QDir().mkdir("gamefiles");
    path = QDir::currentPath() + QDir::separator() +"gamefiles";
    xmlpath=QDir::currentPath() + QDir::separator() + "gamefiles" + QDir::separator() + "adventure.xml";
    imgpath=QDir::currentPath() + QDir::separator() + "gamefiles" + QDir::separator() + + "images" + QDir::separator();
    //set QString to UTF-8 encoding for special characters
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    initialize();



    inventoryButton=new QPushButton("Inventory");
    but02=new QPushButton("02");

    slideTextEdit = new QTextEdit(this);
    slideTextEdit->setReadOnly(true);
    slideTextEdit->append("01");
    slideTextEdit->append("02");


    //QImage slideImage;
    //slideImage.load("image.jpg");
    slideImageLabel = new QLabel(this);
    //slideImageLabel->setPixmap(QPixmap::fromImage(slideImage));

    //mainBox = new QVBoxLayout(centralWidget);
    //mainBox->addWidget(slideImageLabel);
    //mainBox->addWidget(inventoryButton);
    //mainBox->addWidget(slideTextEdit);
    //mainBox->addWidget(but02);
    mainBox = new QGridLayout(centralWidget);
    mainBox->addWidget(slideImageLabel, 0, 0, 1, 5);
    mainBox->addWidget(inventoryButton, 1, 0, 1, 5);
    mainBox->addWidget(slideTextEdit, 2, 0, 1, 5);
    //mainBox->addWidget(but02);
    //setLayout(mainBox);



    game();
}

mainwindow::~mainwindow()
{
    delete ui;
}


void mainwindow::changeSlide(int goalID)
{
    if (goalID==-1) QMessageBox::information(this, "Congratulations!", "You win!");
    else
    {
        currentplayer->setPrevLocation(currentplayer->getLocation());
        currentplayer->setLocation(goalID);
        game();
    }
}


void mainwindow::game()
{

    QImage slideImage;
    for (int i=0; i<slides.size(); i++)
    {
        //Slide found
        if (currentplayer->getLocation()==slides[i]->getId())
        {
            //load image
            slideImage.load(imgpath+slides[i]->getImg());
            slideImageLabel->setPixmap(QPixmap::fromImage(slideImage));
            //clear the text area and add text of the new slide
            slideTextEdit->clear();
            slideTextEdit->append(slides[i]->getTxt());
            //compute items change
            if (!slides[i]->getItems().isEmpty())
            {
                QVector<QString> tempItems=slides[i]->getItems();
                for (int j=0; j<tempItems.size(); j++)
                {
                    if (QString::compare(tempItems[j].at(0),"+")==0)
                    {
                        if (!currentplayer->hasItem(tempItems[j].mid(1))) currentplayer->addItems(tempItems[j].mid(1));
                    }
                    else currentplayer->removeItems(tempItems[j].mid(1));
                }
            }
            //compute stats change
            if (!slides[i]->getStats().isEmpty())
            {
                QVector<QString> tempStats=slides[i]->getStats();
                for (int j=0; j<tempStats.size(); j++)
                {
                    if (QString::compare(tempStats[j].at(0),"+")==0)
                    {
                        if (!currentplayer->isStatus(tempStats[j].mid(1))) currentplayer->addStats(tempStats[j].mid(1));
                    }
                    else currentplayer->removeStats(tempStats[j].mid(1));
                }
            }
            //compute money change
            if ((currentplayer->getMoney()+slides[i]->getMoney())<0) currentplayer->setMoney(0);
            else currentplayer->setMoney(currentplayer->getMoney()+slides[i]->getMoney());
            //compute karma change
            currentplayer->setKarma(currentplayer->getKarma()+slides[i]->getKarma());
            //compute gameovers change
            if (slides[i]->getGameover()) currentplayer->setGameovers(currentplayer->getGameovers()+1);
            //list options
            if (!slides[i]->getOptions().isEmpty())
            {
                //if there are optionButtons, delete them
                if (!optionButtons.isEmpty())
                {
                    for (int j=0; j<optionButtons.size(); j++) disconnect(optionButtons[j], SIGNAL(clicked()), this, SLOT(changeSlide(buttonRefs[j])));
                    for (int j=0; j<optionButtons.size(); j++) delete optionButtons[j];
                    optionButtons.clear();
                    buttonRefs.clear();
                }

                QVector<Option> tempOptions=slides[i]->getOptions();
                for (int j=0; j<tempOptions.size(); j++)
                {
                    //enforcing maximum of 10 Options
                    if (optionButtons.size()==10) break;
                    //qDebug() << tempOptions[j].req;
                    if (currentplayer->meetsReq(tempOptions[j].req, tempOptions[j].name))
                    {
                        //QMessageBox::critical(this, tr("Error!"), tr("Options found!"), QMessageBox::Ok);
                        QPushButton *tempButton = new QPushButton(tempOptions[j].txt);
                        optionButtons.append(tempButton);
                        buttonRefs.append(tempOptions[j].goal);
                        //connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
                    }
                }
                for (int j=0; j<optionButtons.size(); j++)
                {
                    QObject::connect(optionButtons[j], SIGNAL(clicked()), this, SLOT(changeSlide(buttonRefs[j])));
                    if (j<=5) mainBox->addWidget(optionButtons[j], j+3, j);
                    if (j>5) mainBox->addWidget(optionButtons[j], j+3, j-5);
                }

            }
            else QMessageBox::critical(this, tr("Error!"),
                                       tr("No options found!"),
                                        QMessageBox::Ok);
            break;
        }
    }



    /**
    QImage slideImage;
    slideImage.load("image2.jpg");
    //slideImageLabel = new QLabel(this);
    slideImageLabel->setPixmap(QPixmap::fromImage(slideImage));
    slideTextEdit->clear();
    slideTextEdit->append("03");


    bool breaker=false;
    //game-Loop
    while (!breaker)
    {

        if (currentplayer->getLocation()==-1) breaker=true;
        breaker=true;
    }
    **/
}


void mainwindow::initialize()
{
    Q_ASSERT(xmlpath.length()>0);

    currentplayer=new Player();

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
                        if(xml.name() == "gameover") {
                            //qDebug() << xml.name().toString();
                            //qDebug() << xml.readElementText();
                            slide->setGameover(true);
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


