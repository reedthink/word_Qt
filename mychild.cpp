#include "mychild.h"
#include <QtWidgets>

MyChild::MyChild()
{
    setAttribute(Qt::WA_DeleteOnClose);// 子窗口关闭时销毁这个类的对象
    isUntitled = true; // 初始化为没保存在硬盘上

    connect(this, &MyChild::cursorPositionChanged, this, &MyChild::highlightCurrentLine);

    highlightCurrentLine();
    setHighlight();
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
    if (maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
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

bool MyChild::save()
{
    if (isUntitled)
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MyChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), curFile, tr("HTML 文档 (*.htm *.html);;所有文件 (*.*)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MyChild::saveFile(QString fileName)
{
    if (!(fileName.endsWith(".htm", Qt::CaseInsensitive) || fileName.endsWith(".html", Qt::CaseInsensitive)))
    {
        fileName += ".html";
    }
    QTextDocumentWriter writer(fileName);
    bool success = writer.write(this->document());
    if (success)
        setCurrentFile(fileName);
    return success;
}

bool MyChild::maybeSave()
{
    if (!document()->isModified())
        return true;
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Myself Qt Word"), tr("文档 '%1'已被修改，保存吗？").arg(userFriendlyCurrentFile()), QMessageBox::Save | QMessageBox:: Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return save();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void MyChild::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void MyChild::setAlign(int align)
{
    if (align == 1)
        this->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (align == 2)
        this->setAlignment(Qt::AlignHCenter);
    else if (align == 3)
        this->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (align == 4)
        this->setAlignment(Qt::AlignJustify);
}

void MyChild::setStyle(int style)
{
    QTextCursor cursor = this->textCursor();

    if (style != 0)
    {
        QTextListFormat::Style stylename = QTextListFormat::ListDisc;
        switch (style)
        {
            default:
            case 1:
                stylename = QTextListFormat::ListDisc;
                break;
            case 2:
                stylename = QTextListFormat::ListCircle;
                break;
            case 3:
                stylename = QTextListFormat::ListSquare;
                break;
            case 4:
                stylename = QTextListFormat::ListDecimal;
                break;
            case 5:
                stylename = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                stylename = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                stylename = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                stylename = QTextListFormat::ListUpperRoman;
                break;
        }
        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList())
        {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(stylename);

        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else{
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void MyChild::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MyChild::setHighlight()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    highlighter = new Highlighter(this->document());

}
