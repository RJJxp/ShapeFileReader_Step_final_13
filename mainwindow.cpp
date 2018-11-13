#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rjp_shapes.h"
#include "rjp_shapes_command.hpp"
#include "QFileDialog"
// map
#include "mapview.h"
#include "mapwindow.h"
#include "mapbuilder.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create gobal data and set observer
    shapesObCommand * sobc =
            new shapesObCommandTemplate<MainWindow>
            (this,& MainWindow::updateWhenShapesChange);
    singletonShapes::get_gData()->setObCommand(sobc);


    // set the centralWidget
    myShpView = new shpView(this);
    this->setCentralWidget(myShpView);

    // set the leftBar
    myLeftbar = new DockWidget(this);
    myLeftbar->setMaximumWidth(200);
    //leftbar->setFixedHeight(this->height());
    //don not set fixed
    this->addDockWidget(Qt::LeftDockWidgetArea, myLeftbar, Qt::Vertical);

    // set the button
    connect(ui->actionOpen,SIGNAL(triggered(bool)),
            this,SLOT(openSHPfile()));
    connect(ui->actionMap_01,SIGNAL(triggered(bool)),
            this,SLOT(createMap01()));
    connect(ui->actionMap_02,SIGNAL(triggered(bool)),
            this,SLOT(createMap02()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMap01() // mapWithoutGridLine
{
    mapWindow * myMapWindow = new mapWindow(this);
    myMapWindow->show();

    mapDirector * myMapDirector = new mapDirector(new mapWithoutGridLineBuilder());
    map * myMap = myMapDirector->constructMap(singletonShapes::get_gData());

    myMapWindow->setMapVieW_Map(myMap);

    delete myMapDirector;

}

void MainWindow::createMap02() // mapWithAllElements
{
    mapWindow * myMapWindow = new mapWindow(this);
    myMapWindow->show();

    mapDirector * myMapDirector = new mapDirector(new mapWithAllElementsBuilder());
    map * myMap = myMapDirector->constructMap(singletonShapes::get_gData());

    myMapWindow->setMapVieW_Map(myMap);

    delete myMapDirector;
}

void MainWindow::updateWhenShapesChange()
{
    this->update();
    this->myLeftbar->updateListView();
    this->myShpView->update();
}

void MainWindow::openSHPfile()
{
    QFileDialog dialog(this,tr("Open File"),"",tr("*.shp"));
    dialog.setFileMode(QFileDialog::ExistingFiles);//可以同时打开多个文件
    QStringList temPL;
    if(dialog.exec())
        temPL = dialog.selectedFiles();
    else
        return;
    singletonShapes::get_gData()->addShapes(temPL);
    singletonShapes::get_gData()->notify();
}
