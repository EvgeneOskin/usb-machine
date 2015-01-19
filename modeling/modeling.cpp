#include "modeling.h"

ModelingWidget::ModelingWidget() : QWidget(){
    mainLayout = new QHBoxLayout();
    controlsLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *beatyButtonLayout = new QVBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addLayout(beatyButtonLayout);
    buttonLayout->addStretch(1);
    projectionWidget = new QLineEdit(tr("xyz"));
    replotButton = new QPushButton(tr("Установить проекцию"));

    okButton = new QPushButton(tr("OK"));

    beatyButtonLayout->addWidget(replotButton);
    beatyButtonLayout->addWidget(okButton);
    plotWidget = new PlotWidget();

    mainLayout->addWidget(plotWidget, 1);
    mainLayout->addLayout(controlsLayout);

    controlsLayout->addWidget(projectionWidget);
    controlsLayout->addLayout(buttonLayout);
    controlsLayout->addStretch(1);
    setLayout(mainLayout);
    connect(okButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(replotButton, SIGNAL(clicked()), this, SLOT(changeProjection()));

    setWindowTitle(tr("Моделирование трактории движения"));
}

void ModelingWidget::plotLine(lines_t* line) {
    this->line = line;

    changeProjection();
}

void ModelingWidget::changeProjection() {
    track = new Track(line, projectionWidget->text(), *plotWidget);
    track->setMesh(line->size ()*1000, 3);
    track->setDomain(0.0, track->getTotalTimeSeconds (), 0.0, 1.0);
    track->create();

    plotWidget->updateProjection(track->getXName(), track->getYName(), track->getZName());

    plotWidget->updateLine();
}
