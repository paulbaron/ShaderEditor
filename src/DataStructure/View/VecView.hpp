#ifndef VECVIEW
#define VECVIEW

#include "BaseVecView.hh"
#include "ui_BaseVecView.h"

#include <QLabel>

#include <QDoubleSpinBox>

#include <assert.h>

#include <cfloat>

template<class GlmVec>
class VecView : public BaseVecView
{
public:
    VecView(AbstractData *data, QWidget *parent = 0) :
        BaseVecView(data, parent)
    {
        QString component[] =
        {
            "x", "y", "z", "w"
        };

        for (int i = 0; i < GlmVec().length(); ++i)
        {
            ui->horizontalLayout->addWidget(new QLabel(component[i]));
            _spinBoxes.push_back(new QDoubleSpinBox);
            _spinBoxes.back()->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
            _spinBoxes.back()->setMinimum(-FLT_MAX);
            ui->horizontalLayout->addWidget(_spinBoxes.back());
        }
    }

    ~VecView()
    {
    }

    GlmVec getValue()
    {
        GlmVec ret;

        for (int i = 0; i < ret.length(); ++i)
        {
            ret[i] = static_cast<float>(_spinBoxes[i]->value());
        }
        return (ret);
    }

    void setUi(GlmVec vec)
    {
        for (int i = 0; i < vec.length(); ++i)
        {
            _spinBoxes[i]->setValue(vec[i]);
        }
    }

private:
    QVector<QDoubleSpinBox*> _spinBoxes;
};

#endif // VECVIEW

