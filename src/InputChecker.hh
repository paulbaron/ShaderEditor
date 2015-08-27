#ifndef INPUTCHECKER_H
#define INPUTCHECKER_H

#include <QMap>
#include <QList>

#include "DataStructure/SInstance.hh"
#include "DataStructure/AbstractData.hh"

class InputChecker
{
public:
    InputChecker();

    void checkInput(SContainerInstance const *root, QString &attributesCode, QString &uniformCode);
    void getAllInputs(SContainerInstance const *root, QString &attributeCode, QString &uniformCode);
    void checkInputsTree(SContainerInstance const *root);

private:
    QMap<QString, AbstractData::EDataTypes> _uniformNames;
    QMap<QString, int> _texturesBinding;
    QList<QString> _uniformFilled;
    QList<QString> _attributeNames;
    int _currentTextureBinding;
};

#endif // INPUTCHECKER_H
