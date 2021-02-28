#include "widgetcontainerprivate.h"

#include <QtWidgets>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QTabWidget>
#include <QPushButton>

#include "widgetcontainer.h"

using namespace utils;

WidgetContainerPrivate::WidgetContainerPrivate(QWidget *parent)
    : QWidget(parent),
      sbox_count(new QSpinBox()),
      m_spinbox_lb_title(QString::fromUtf8("Количество виджетов")),
      m_tab_title(QString::fromUtf8("Пустой виджет")),
      key("empty_qwidget"),
      mMinimum(0),
      mMaximum(99)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QSpacerItem *horizontal_spacer = new QSpacerItem (40, 20,
                                                     QSizePolicy::Expanding,
                                                     QSizePolicy::Minimum);
    QHBoxLayout *hb_layout = new QHBoxLayout();
    m_spinbox_lb = new QLabel(m_spinbox_lb_title, this);
    hb_layout->addWidget(m_spinbox_lb);
    hb_layout->addSpacerItem(horizontal_spacer);

    sbox_count->setFocusPolicy(Qt::NoFocus);
    connect(sbox_count, SIGNAL(valueChanged(int)), this, SLOT(on_sbox_count_valueChanged(int)));
    hb_layout->addWidget(sbox_count);

    QScrollArea *scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);
    QHBoxLayout *hb_2_layout = new QHBoxLayout();
    tab_widget = new QTabWidget(scroll_area);
    hb_2_layout->addWidget(tab_widget);
    scroll_area->setLayout(hb_2_layout);

    mainLayout->addLayout(hb_layout);
    mainLayout->addWidget(scroll_area);

    w_factory.reg<QWidget>(key.toStdString());
}

WidgetContainerPrivate::~WidgetContainerPrivate()
{
    ptr_vec.clear();
    widget_vec.clear();
}

void WidgetContainerPrivate::on_sbox_count_valueChanged(int arg1)
{
    if (arg1 > mMaximum)
    {
        sbox_count->setValue(mMaximum);
        return ;
    }
    else if (arg1 < mMinimum)
    {
        sbox_count->setValue(mMinimum);
        return ;
    }

    if (ptr_vec.size() == arg1)
        return ;

    if (ptr_vec.size() < arg1)
    {
        addFormular(arg1);
    }
    else
    {
        delFormular();
    }

    emit widgetsCountChanged();
}

void WidgetContainerPrivate::addFormular(int formular_index)
{
    if (formular_index > 0)
    {
        WidgetPtr widget_ptr = w_factory.create(key.toStdString(), this);
        ptr_vec.append(widget_ptr);
        tab_widget->addTab(widget_ptr.get(),
                           m_tab_title+QString(" ")+QString::number(formular_index));

        if (widget_ptr.get()->metaObject()->indexOfSignal(QMetaObject::normalizedSignature("dataChanged()")) != -1)
            connect(widget_ptr.get(), SIGNAL(dataChanged()), q_ptr, SIGNAL(dataChanged()));
    }
    return ;
}

void WidgetContainerPrivate::delFormular()
{
    if (!ptr_vec.empty())
        ptr_vec.removeLast();
}

const QVector<QWidget *> &WidgetContainerPrivate::getWidgets()
{
    widget_vec.clear();
    foreach (WidgetPtr var, ptr_vec)
    {
        QWidget *w = var.get();
        widget_vec.append(w);
    }
    return widget_vec;
}

void WidgetContainerPrivate::setSpinBoxTitle(const QString &sbox_title)
{
    if (m_spinbox_lb)
        m_spinbox_lb->setText(sbox_title);
}

void WidgetContainerPrivate::fill(int count)
{
    for (int var = 1; var <= count; ++var)
        sbox_count->setValue(var);
}

void WidgetContainerPrivate::addWidget()
{
    sbox_count->setValue(sbox_count->value() + 1);
}
