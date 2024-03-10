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

void MyWord::createActions()
{
    QString rsrcPath = "images";
    newAct = new QAction(QIcon(rsrcPath + "/filenew.png"), tr("新建(&N)"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setToolTip("新建");
    newAct->setStatusTip(tr("创建一个新文档"));
    //connect(newAct, SIGNAL(triggered()), this, SLOT(fileNew()));

    openAct = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("打开(&O)..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setToolTip("打开");
    openAct->setStatusTip(tr("打开已存在的文档"));
//    connect(openAct, SIGNAL(triggered()), this, SLOT(fileOpen()));

    saveAct = new QAction(QIcon(rsrcPath + "/filesave.png"), tr("保存(&s)"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setToolTip("保存");
    saveAct->setStatusTip(tr("将当前文档存盘"));
//    connect(saveAct, SIGNAL(triggered()), this, SLOT(fileSave()));

    saveAsAct = new QAction(tr("另存为(&A)..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("以一个新名字保存文档"));
//    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    printAct = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("打印(&P)..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印文档"));
//    connect(printAct, SIGNAL(triggered()), this, SLOT(filePrint()));

    printPreviewAct = new QAction(tr("打印预览..."), this);
    printPreviewAct->setStatusTip(tr("预览打印效果"));
//    connect(printPreviewAct, SIGNAL(triggered()), this, SLOT(filePrintPreview()));

    exitAct = new QAction(tr("退出(&X)"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("退出应用程序"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(closeAllWindows()));

    //编辑菜单
    undoAct = new QAction(QIcon(rsrcPath + "/editundo.png"), tr("撤销(&U)"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setToolTip("撤销");
    undoAct->setStatusTip(tr("撤销当前操作"));

    redoAct = new QAction(QIcon(rsrcPath + "/editredo.png"), tr("重做(&R)"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setToolTip("重做");
    redoAct->setStatusTip(tr("重复之前操作"));

    cutAct = new QAction(QIcon(rsrcPath + "/editcut.png"), tr("剪切(&T)"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("从文档中裁剪所选内容，并将其放入剪贴板"));
//    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(QIcon(rsrcPath + "/editcopy.png"), tr("复制(&C)"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("复制所选内容到剪贴板"));
    //    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(QIcon(rsrcPath + "/editpaste.png"), tr("粘贴(&P)"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("将剪贴板的内容粘贴到文档"));
    //    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

}

void MyWord::createMenus()
{
    //文件主菜单
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addAction(printPreviewAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    //编辑主菜单
    editMenu = menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
}
