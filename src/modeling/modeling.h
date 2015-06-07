#ifndef MODELING_H
#define MODELING_H

#include "widgets/plotwidget.h"
#include "parser/parsertypes.h"
#include "track.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class ModelingWidget : public QWidget {

Q_OBJECT

public:
    ModelingWidget();
    void plotLine(lines_t* line);

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *controlsLayout;
    QPushButton *okButton;
    QLineEdit *projectionWidget;
    QPushButton *replotButton;
    PlotWidget *plotWidget;
    Track *track;
    lines_t* line;

public slots:
    void changeProjection();

};

#endif // MODELING_H
