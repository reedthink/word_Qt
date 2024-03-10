#include "myword.h"
#include <QtWidgets>

MyWord::MyWord(QWidget *parent)
    : QMainWindow(parent)
{

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    move(200, 150);
    resize(800, 500);

    setWindowTitle(tr("Diy Word"));
}

MyWord::~MyWord()
{
}

