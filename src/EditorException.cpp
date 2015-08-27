#include "EditorException.hh"

#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

EditorException::EditorException(QString title, QString details) :
    _title(title),
    _details(details)
{
}

char const *EditorException::what() const throw()
{
    return (_title.toStdString().c_str());
}

void EditorException::displayErrorMessage() const
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Render Pass Error");
    msgBox.setText(_title);
    msgBox.setDetailedText(_details);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    msgBox.exec();
}
