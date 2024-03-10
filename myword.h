#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>

class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = nullptr);
    ~MyWord();
};
#endif // MYWORD_H
