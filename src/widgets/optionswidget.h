#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QtWidgets>
#include "widgets/machineoptions.h"
#include "widgets/mainoptions.h"

#include "options.h"


class OptionsWidget : public QDialog {
    Q_OBJECT

public:
    OptionsWidget(QWidget *parent=0);
    ~OptionsWidget();

private:
    Options *options;

    QVBoxLayout* layout;

    QTabWidget* tabWidget;
    MainOptions *mainWidget;
    MachineOptions* machineWidget;
    QVBoxLayout* unitsLayout;
    QVBoxLayout* compileLayout;
    QVBoxLayout* mainLayout;
    QVBoxLayout* warningsLayout;
    QVBoxLayout* editorLayout;

    QHBoxLayout* buttonsLayout;
    QPushButton* ok;
    QPushButton* cancel;
    QPushButton* apply;

    QTextEdit* xAreaEdit;
    QTextEdit* yAreaEdit;
    QTextEdit* zAreaEdit;
    QTextEdit* fAreaEdit;
    QTextEdit* blankAreaEdit;
public slots:
    void readSettings();
    void writeSettings();
    void closeAndWriteSettings();
    void closeAndReadSettings();

};
#endif // OPTIONSWIDGET_H
