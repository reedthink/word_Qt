#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>

class QMdiArea;
class QAction;
class QMenu;
class QComboBox;
class QFontComboBox;
class MyChild;
class QMdiSubWindow;
class QSignalMapper;

class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = nullptr);
    ~MyWord();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QMdiArea *mdiArea;
    void createActions();// 创建系统动作
    void createMenus(); //创建菜单
    void createToolBars();
    void createStatusBar();
    void colorChanged(const QColor &c);

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

    QMenu *helpMenu;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;
    QToolBar *comboToolBar;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    void enabledText();
    MyChild *activeMyChild();
    QSignalMapper *windowMapper;

    QMdiSubWindow *findMyChild(const QString &fileName);

private slots:
    void textAlign(QAction *a);
    void about();
    void fileNew();
    MyChild *createMyChild();
    void updateMenus();
    void updateWindowMenu();
    void setActiveSubWindow(QWidget *window);
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void textBold();
    void textItalic();
    void textUnderline();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textColor();
    void textStyle(int styleIndex);
};
#endif // MYWORD_H
