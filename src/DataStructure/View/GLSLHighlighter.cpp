#include "GLSLHighlighter.hh"

GLSLHighlighter::GLSLHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    setFunctionFormat();
    setTypesFormat();
    setKeyWordsFormat();
    setBuiltInFormat();
    setCommentsFormat();
}

void GLSLHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        startIndex = commentStartExpression.indexIn(text);
    }

    while (startIndex >= 0)
    {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}

void GLSLHighlighter::setTypesFormat()
{
    HighlightingRule rule;

    typesFormat.setForeground(Qt::darkBlue);
    typesFormat.setFontWeight(QFont::Bold);
    QStringList typesPattern;
    typesPattern << "\\bbool\\b" << "\\bint\\b" << "\\buint\\b"
                    << "\\bfloat\\b" << "\\bdouble\\b"
                    << "\\bbvec2\\b" << "\\bbvec3\\b" << "\\bbvec4\\b"
                    << "\\bivec2\\b" << "\\bivec3\\b" << "\\bivec4\\b"
                    << "\\buvec2\\b" << "\\buvec3\\b" << "\\buvec4\\b"
                    << "\\bvec2\\b" << "\\bvec3\\b" << "\\bvec4\\b"
                    << "\\bdvec2\\b" << "\\bdvec3\\b" << "\\bdvec4\\b"
                    << "\\bmat2\\b" << "\\bmat3\\b" << "\\bmat4\\b"
                    << "\\bmat2x2\\b" << "\\bmat2x3\\b" << "\\bmat2x4\\b"
                    << "\\bmat3x2\\b" << "\\bmat3x3\\b" << "\\bmat3x4\\b"
                    << "\\bmat4x2\\b" << "\\bmat4x3\\b" << "\\bmat4x4\\b"
                    << "\\bvoid\\b";
    foreach (const QString &pattern, typesPattern)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = typesFormat;
        highlightingRules.append(rule);
    }
}

void GLSLHighlighter::setKeyWordsFormat()
{
    HighlightingRule rule;

    keyWordsFormat.setForeground(Qt::darkYellow);
    keyWordsFormat.setFontWeight(QFont::Bold);
    QStringList keywordsPattern;
    keywordsPattern << "\\bin\\b" << "\\bout\\b"  << "\\binout\\b" << "\\bconst\\b"
                  << "\\bfor\\b" << "\\bwhile\\b" << "\\bswitch\\b" << "\\bcase\\b"
                  << "\\bbreak\\b" << "\\breturn\\b" << "\\bcontinue\\b" << "\\bdiscard\\b";
    foreach (const QString &pattern, keywordsPattern)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keyWordsFormat;
        highlightingRules.append(rule);
    }
}

void GLSLHighlighter::setBuiltInFormat()
{
    HighlightingRule rule;

    keyWordsFormat.setForeground(Qt::darkRed);
    keyWordsFormat.setFontWeight(QFont::Bold);
    QStringList builtInPattern;
    builtInPattern << "\\bgl_VertexID\\b" << "\\bgl_InstanceID\\b"  << "\\bgl_Position\\b"
                   << "\\bgl_FragCoord\\b" << "\\bgl_FrontFacing\\b" << "\\bgl_FragDepth\\b";
    foreach (const QString &pattern, builtInPattern)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keyWordsFormat;
        highlightingRules.append(rule);
    }
}

void GLSLHighlighter::setInputFormat()
{

}

void GLSLHighlighter::setOutputFormat()
{

}

void GLSLHighlighter::setFunctionFormat()
{
    HighlightingRule rule;

    numberFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[0-9]+(\\.[0-9]+[f]?)?");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    functionFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
}

void GLSLHighlighter::setCommentsFormat()
{
    HighlightingRule rule;

    singleLineCommentFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkMagenta);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

