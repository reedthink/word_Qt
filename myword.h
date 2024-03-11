#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>

class QMdiArea;
class QAction;
class QMenu;

class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = nullptr);
    ~MyWord();

private:
    QMdiArea *mdiArea;
    void createActions();// 创建系统动作
    void createMenus(); //创建菜单

    QMenu *fileMenu;

    QAction *newAct;// 新建
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *printPreviewAct;
    QAction *exitAct;

    QMenu *editMenu;
    QAction *undoAct, *redoAct, *cutAct, *copyAct, *pasteAct;

    QMenu *formatMenu;
    QMenu *fontMenu;
    QMenu *alignMenu;
    QAction *boldAct;
    QAction *italicAct;
    QAction *underlineAct;
    QAction *leftAlignAct;
    QAction *centerAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *colorAct;

    QMenu *windowMenu;
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;


private slots:
    void textAlign(QAction *a);
};
#endif // MYWORD_H
