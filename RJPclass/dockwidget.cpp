#include "dockwidget.h"
#include "ui_dockwidget.h"

#include "QHBoxLayout"
#include "QPalette"
#include "rjp_shapes.h"

DockWidget::DockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockWidget)
{
    ui->setupUi(this);

    //QListWidget Initialization
    temWidget = new QWidget();

    myListWidget = new QListWidget();
    QHBoxLayout * hLayout = new QHBoxLayout(this);
    hLayout->addWidget(myListWidget);

    temWidget->setLayout(hLayout);
    this->setWidget(temWidget);

    //set the backcolor of QDockWidget
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(200,200,200));
    setAutoFillBackground(true);
    setPalette(pal);
}

DockWidget::~DockWidget()
{
    delete ui;
}

void DockWidget::updateListView()
{
    myListWidget->setFixedHeight(this->height());

    if(!singletonShapes::get_gData())
        return;

    myListWidget->clear();

    for(int i=0;i<singletonShapes::get_gData()->getLayerSize();i++)
    {
        myListWidget->insertItem(i,singletonShapes::get_gData()->at(i)->get_DatasetPtr().getValue()->myName);
    }
}
