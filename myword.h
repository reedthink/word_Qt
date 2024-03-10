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
};
#endif // MYWORD_H