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

bool MyChild::loadFile(const QString &fileName)
{
    if (!fileName.isEmpty())
    {
        if (!QFile::exists(fileName))
            return false;
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly))
            return false;

        QByteArray data = file.readAll();
        QTextCodec *codec = Qt::codecForHtml(data);
        QString str = codec->toUnicode(data);
        if (Qt::mightBeRichText(str))
        {
            this->setHtml(str);
        }
        else{
            str = QString::fromLocal8Bit(data);
            this->setPlainText(str);
        }
        setCurrentFile(fileName);
        connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
        return true;
    }
}

void MyChild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}
