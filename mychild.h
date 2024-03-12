#ifndef MYCHILD_H
#define MYCHILD_H

#include <QTextEdit>

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

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void documentWasModified();
private:
    QString strippedName(const QString &fullFileName);
    void setCurrentFile(const QString &fileName);
    bool maybeSave();
    QString curFile;
    bool isUntitled; //是否保存在硬盘上
};

#endif // MYCHILD_H
