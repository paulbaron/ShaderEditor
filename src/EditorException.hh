#ifndef EDITOREXCEPTION_H
#define EDITOREXCEPTION_H

#include <exception>

#include <QString>

class EditorException : public std::exception
{
public:
    EditorException(QString title, QString details);
    ~EditorException() throw() { }

    virtual char const *what() const throw();

    void displayErrorMessage() const;

private:
    QString const _title;
    QString const _details;
};

#endif // EDITOREXCEPTION_H
