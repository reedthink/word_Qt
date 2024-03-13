#ifndef MYCHILD_H
#define MYCHILD_H

#include <QTextEdit>
#include <QPrinter>
#include "highlighter.h"

class MyChild : public QTextEdit
{
    Q_OBJECT
public:
    MyChild();
    void newFile();
    QString userFriendlyCurrentFile(); // 提取文件名
    QString currentFile()
    {
        return curFile;
    }
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(QString fileName);
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void setAlign(int align);
    void setStyle(int style);

    void setHighlight();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void documentWasModified();
    void highlightCurrentLine();
private:
    QString strippedName(const QString &fullFileName);
    void setCurrentFile(const QString &fileName);
    bool maybeSave();
    QString curFile;
    bool isUntitled; //是否保存在硬盘上
    Highlighter *highlighter; // 高亮
};

#endif // MYCHILD_H
