#include "optionswidget.h"

OptionsWidget::OptionsWidget(QWidget *parent) : QDialog(parent){

    options = new Options();

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));
    apply = new QPushButton(tr("Apply"));
    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(ok);
    buttonsLayout->addSpacing(0);
    buttonsLayout->addWidget(apply);
    buttonsLayout->addSpacing(0);
    buttonsLayout->addWidget(cancel);
    buttonsLayout->addSpacing(0);
    connect(apply, SIGNAL(clicked()),this,SLOT(writeSettings()));
    connect(ok, SIGNAL(clicked()),this,SLOT(closeAndWriteSettings()));
    connect(cancel, SIGNAL(clicked()),this,SLOT(closeAndReadSettings()));

    machineWidget = new MachineOptions(this);
    mainWidget= new MainOptions(this);
    tabWidget = new QTabWidget(this);

    //tabWidget->addTab(editorLayout, tr("Редактор"));
    tabWidget->addTab(machineWidget, tr("Станок"));
    tabWidget->addTab(mainWidget, tr("Основное"));
    //tabWidget->addTab(compileLayout, tr("Компиляция"));
    //tabWidget->addTab(warningsLayout, tr("Аварийные"));
    layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->addLayout(buttonsLayout);
    setLayout(layout);
    readSettings();

    setWindowTitle(tr("Настройки"));
}

OptionsWidget::~OptionsWidget() {
    delete options;
}

void OptionsWidget::readSettings() {
    mainWidget->setDimension(options->getDimension ());
    machineWidget->setXArea(options->getXArea ());
    machineWidget->setYArea(options->getYArea ());
    machineWidget->setZArea(options->getZArea ());
    machineWidget->setFArea(options->getFArea ());
    machineWidget->setBlankArea(options->getBlankArea ());
}

void OptionsWidget::closeAndWriteSettings() {
    writeSettings();
    hide();
}

void OptionsWidget::closeAndReadSettings() {
    readSettings();
    hide();
}

void OptionsWidget::writeSettings() {
    options->setDimension (mainWidget->getDimension());
    options->setXArea(machineWidget->getXArea());
    options->setYArea (machineWidget->getYArea());
    options->setZArea (machineWidget->getZArea());
    options->setFArea (machineWidget->getFArea());
    options->setBlankArea (machineWidget->getBlankArea());
}
