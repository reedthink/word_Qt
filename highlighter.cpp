#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                         << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                         << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                         << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                         << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                         << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                         << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                         << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                         << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                         << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";

    foreach(const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    //class
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    //single
    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("//[^\n]");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    //multi
    multiLineCommentFormat.setForeground(Qt::red);

    //quotation
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //func
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    //comment
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");

}

void Highlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightingRule &rule, highlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while(matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);

        }
    }
    setCurrentBlockState(0); //不知道这行代码的作用

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while(startIndex>=0)
    {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else{
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex+commentLength);
    }
}
