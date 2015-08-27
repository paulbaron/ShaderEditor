#ifndef GLSLHIGHLIGHTER_H
#define GLSLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>

class GLSLHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    GLSLHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    void setTypesFormat();
    void setKeyWordsFormat();
    void setBuiltInFormat();
    void setInputFormat();
    void setOutputFormat();
    void setFunctionFormat();
    void setCommentsFormat();

    QTextCharFormat typesFormat;
    QTextCharFormat keyWordsFormat;
    QTextCharFormat builtInFormat;
    QTextCharFormat inputFormat;
    QTextCharFormat outputFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
};

#endif // GLSLHIGHLIGHTER_H
