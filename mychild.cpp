#include "mychild.h"
#include <QtWidgets>

MyChild::MyChild()
{
    setAttribute(Qt::WA_DeleteOnClose);// 子窗口关闭时销毁这个类的对象
    isUntitled = true; // 初始化为没保存在硬盘上
}

void MyChild::newFile()
{
    static int sequenceNumber = 1;

    isUntitled = true;

    curFile = tr("文档 %1").arg(sequenceNumber++);

    setWindowTitle(curFile + "[*]" + tr(" - Diy Word"));

    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

}

void MyChild::documentWasModified()
{
    setWindowModified(document()->isModified());
}

QString MyChild::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}

//从路径中提取文件名
QString MyChild::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MyChild::closeEvent(QCloseEvent *event)
{
    //暂时不处理关闭时候的保存逻辑
    event->accept();
}
