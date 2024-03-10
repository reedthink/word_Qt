#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>

class QMdiArea;

class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = nullptr);
    ~MyWord();

private:
    QMdiArea *mdiArea;
};
#endif // MYWORD_H
