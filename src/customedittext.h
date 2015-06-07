/*
 Got line number and highlight current line features from
 http://qt-project.org/doc/qt-4.8/widgets-codeeditor.html
*/

#ifndef CUSTOMEDITTEXT_H
#define CUSTOMEDITTEXT_H

#include <QPlainTextEdit>
#include <QWidget>

class CustomEditText : public QPlainTextEdit {
    Q_OBJECT

public:
    CustomEditText(QWidget* parent);
    QAction* getCutAction();
    QAction* getCopyAction();
    QAction* getPasteAction();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;

    QWidget *lineNumberArea;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CustomEditText *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CustomEditText *codeEditor;
};

#endif // CUSTOMEDITTEXT_H
