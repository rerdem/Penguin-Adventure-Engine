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
    fileMenu->addAction(tr("&Save"), this, SLOT(save()));
    fileMenu->addAction(tr("&Load"), this, SLOT(load()));
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


    signalMapper = new QSignalMapper(this);

    but01=new QPushButton("01");
    but02=new QPushButton("02");
    but03=new QPushButton("03");
    but04=new QPushButton("04");
    but05=new QPushButton("05");
    but06=new QPushButton("06");
    but07=new QPushButton("07");
    but08=new QPushButton("08");
    but09=new QPushButton("09");
    but10=new QPushButton("10");
    opt01=0;
    opt02=0;
    opt03=0;
    opt04=0;
    opt05=0;
    opt06=0;
    opt07=0;
    opt08=0;
    opt09=0;
    opt10=0;
    connect(but01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but08, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but09, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(but10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(but01, opt01);
    signalMapper->setMapping(but02, opt02);
    signalMapper->setMapping(but03, opt03);
    signalMapper->setMapping(but04, opt04);
    signalMapper->setMapping(but05, opt05);
    signalMapper->setMapping(but06, opt06);
    signalMapper->setMapping(but07, opt07);
    signalMapper->setMapping(but08, opt08);
    signalMapper->setMapping(but09, opt09);
    signalMapper->setMapping(but10, opt10);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(changeSlide(int)));




    slideTextEdit = new QTextEdit(this);
    slideTextEdit->setReadOnly(true);
    slideTextEdit->append("01");
    slideTextEdit->append("02");


    //QImage slideImage;
    //slideImage.load("image.jpg");
    slideImageLabel = new QLabel(this);
    //slideImageLabel->setPixmap(QPixmap::fromImage(slideImage));

    mainBox = new QGridLayout(centralWidget);
    mainBox->addWidget(slideImageLabel, 0, 0, 1, 5);
    mainBox->addWidget(inventoryButton, 1, 0, 1, 5);
    mainBox->addWidget(slideTextEdit, 2, 0, 1, 5);
    mainBox->addWidget(but01, 3, 0);
    mainBox->addWidget(but02, 3, 1);
    mainBox->addWidget(but03, 3, 2);
    mainBox->addWidget(but04, 3, 3);
    mainBox->addWidget(but05, 3, 4);
    mainBox->addWidget(but06, 4, 0);
    mainBox->addWidget(but07, 4, 1);
    mainBox->addWidget(but08, 4, 2);
    mainBox->addWidget(but09, 4, 3);
    mainBox->addWidget(but10, 4, 4);

    but01->hide();
    but02->hide();
    but03->hide();
    but04->hide();
    but05->hide();
    but06->hide();
    but07->hide();
    but08->hide();
    but09->hide();
    but10->hide();

    game();
}

mainwindow::~mainwindow()
{
    delete ui;
}


void mainwindow::load()
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this, tr("Load..."), ".", tr("Savegame (*.sav)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("File Error"),
                           tr("The following file cannot be opened: ") + fileName, QMessageBox::Ok);
        }

        QTextStream in(&file);
        QString tempString;
        QStringList tempStringList;



        if (in.status() == QTextStream::Ok)
        {
            //read Name
            tempString=in.readLine();
            if (QString::compare(tempString, "")==0) QMessageBox::warning(this, tr("File Error"), tr("This file is incompatible!"), QMessageBox::Ok);
            else currentplayer->setName(tempString);
            //read Inventory
            tempString=in.readLine();
            tempStringList=tempString.split("@");
            for (int i=0; i<tempStringList.length(); i++) currentplayer->addItem(tempStringList[i]);
            //read Stats
            tempString=in.readLine();
            tempStringList=tempString.split("@");
            for (int i=0; i<tempStringList.length(); i++) currentplayer->addStat(tempStringList[i]);
            //read money
            tempString=in.readLine();
            if (QString::compare(tempString, "")==0) QMessageBox::warning(this, tr("File Error"), tr("This file is incompatible!"), QMessageBox::Ok);
            else currentplayer->setMoney(tempString.toInt());
            //read karma
            tempString=in.readLine();
            if (QString::compare(tempString, "")==0) QMessageBox::warning(this, tr("File Error"), tr("This file is incompatible!"), QMessageBox::Ok);
            else currentplayer->setKarma(tempString.toInt());
            //read gameovers
            tempString=in.readLine();
            if (QString::compare(tempString, "")==0) QMessageBox::warning(this, tr("File Error"), tr("This file is incompatible!"), QMessageBox::Ok);
            else currentplayer->setGameovers(tempString.toInt());
            //read location
            tempString=in.readLine();
            if (QString::compare(tempString, "")==0) QMessageBox::warning(this, tr("File Error"), tr("This file is incompatible!"), QMessageBox::Ok);
            else currentplayer->setLocation(tempString.toInt());
            //read prevLocation
            tempString=in.readLine();
            if (QString::compare(tempString, "")==0) QMessageBox::warning(this, tr("File Error"), tr("This file is incompatible!"), QMessageBox::Ok);
            else currentplayer->setPrevLocation(tempString.toInt());
            tempString=in.readLine();
        }
        file.close();
        game();
    }
}


void mainwindow::save()
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this, tr("Save as..."), ".", tr("Savegame (*.sav)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("File Error"),
                           tr("The following file cannot be used: ") + fileName, QMessageBox::Ok);
        }

        QTextStream out(&file);

        out  << currentplayer->getName() << endl;
        QVector<QString> itemsOut=currentplayer->getItems();
        for (int i=0; i<itemsOut.size(); i++) out  << itemsOut[i] << "@";
        out  << endl;
        QVector<QString> statsOut=currentplayer->getStats();
        for (int i=0; i<statsOut.size(); i++) out  << statsOut[i] << "@";
        out  << endl;
        out  << currentplayer->getMoney() << endl;
        out  << currentplayer->getKarma() << endl;
        out  << currentplayer->getGameovers() << endl;
        out  << currentplayer->getLocation() << endl;
        out  << currentplayer->getPrevLocation() << endl;
        file.close();
    }
}


void mainwindow::changeSlide( const int goalID)
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
                        if (!currentplayer->hasItem(tempItems[j].mid(1))) currentplayer->addItem(tempItems[j].mid(1));
                    }
                    else currentplayer->removeItem(tempItems[j].mid(1));
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
                        if (!currentplayer->isStatus(tempStats[j].mid(1))) currentplayer->addStat(tempStats[j].mid(1));
                    }
                    else currentplayer->removeStat(tempStats[j].mid(1));
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
                //if there are optionButtons visible, hide them
                if (but01->isVisible())
                {
                    but01->hide();
                    but02->hide();
                    but03->hide();
                    but04->hide();
                    but05->hide();
                    but06->hide();
                    but07->hide();
                    but08->hide();
                    but09->hide();
                    but10->hide();
                }

                QVector<Option> tempOptions=slides[i]->getOptions();
                int optionCounter=0;
                for (int j=0; j<tempOptions.size(); j++)
                {
                    //enforcing maximum of 10 Options
                    if (optionCounter==10) break;
                    //qDebug() << tempOptions[j].req << tempOptions[j].name << currentplayer->meetsReq(tempOptions[j].req, tempOptions[j].name);
                    if (currentplayer->meetsReq(tempOptions[j].req, tempOptions[j].name))
                    {
                        //QMessageBox::critical(this, tr("Error!"), tr("Options found!"), QMessageBox::Ok);
                        switch(optionCounter)
                        {
                        case 0:
                            but01->setText(tempOptions[j].txt);
                            opt01=tempOptions[j].goal;
                            signalMapper->removeMappings(but01);
                            signalMapper->setMapping(but01, opt01);
                            but01->show();
                            break;
                        case 1:
                            but02->setText(tempOptions[j].txt);
                            opt02=tempOptions[j].goal;
                            signalMapper->removeMappings(but02);
                            signalMapper->setMapping(but02, opt02);
                            but02->show();
                            break;
                        case 2:
                            but03->setText(tempOptions[j].txt);
                            opt03=tempOptions[j].goal;
                            signalMapper->removeMappings(but03);
                            signalMapper->setMapping(but03, opt03);
                            but03->show();
                            break;
                        case 3:
                            but04->setText(tempOptions[j].txt);
                            opt04=tempOptions[j].goal;
                            signalMapper->removeMappings(but04);
                            signalMapper->setMapping(but04, opt04);
                            but04->show();
                            break;
                        case 4:
                            but05->setText(tempOptions[j].txt);
                            opt05=tempOptions[j].goal;
                            signalMapper->removeMappings(but05);
                            signalMapper->setMapping(but05, opt05);
                            but05->show();
                            break;
                        case 5:
                            but06->setText(tempOptions[j].txt);
                            opt06=tempOptions[j].goal;
                            signalMapper->removeMappings(but06);
                            signalMapper->setMapping(but06, opt06);
                            but06->show();
                            break;
                        case 6:
                            but07->setText(tempOptions[j].txt);
                            opt07=tempOptions[j].goal;
                            signalMapper->removeMappings(but07);
                            signalMapper->setMapping(but07, opt07);
                            but07->show();
                            break;
                        case 7:
                            but08->setText(tempOptions[j].txt);
                            opt08=tempOptions[j].goal;
                            signalMapper->removeMappings(but08);
                            signalMapper->setMapping(but08, opt08);
                            but08->show();
                            break;
                        case 8:
                            but09->setText(tempOptions[j].txt);
                            opt09=tempOptions[j].goal;
                            signalMapper->removeMappings(but09);
                            signalMapper->setMapping(but09, opt09);
                            but09->show();
                            break;
                        case 9:
                            but10->setText(tempOptions[j].txt);
                            opt10=tempOptions[j].goal;
                            signalMapper->removeMappings(but10);
                            signalMapper->setMapping(but10, opt10);
                            but10->show();
                            break;
                        }
                        optionCounter++;
                    }
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
    QString req, name, textReplacer;
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
                            textReplacer=xml.readElementText();
                            //add HTML tags
                            textReplacer.replace("*br*", "<br>");
                            textReplacer.replace("*b*", "<b>");
                            textReplacer.replace("*/b*", "</b>");
                            textReplacer.replace("*i*", "<i>");
                            textReplacer.replace("*/i*", "</i>");
                            textReplacer.replace("*u*", "<u>");
                            textReplacer.replace("*/u*", "</u>");
                            slide->setTxt(textReplacer);
                            //slide->setTxt(xml.readElementText());
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


