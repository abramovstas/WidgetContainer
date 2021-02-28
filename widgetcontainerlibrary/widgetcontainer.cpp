#include "widgetcontainer.h"

#include <QVBoxLayout>

using namespace utils;

WidgetContainer::WidgetContainer(QWidget *parent)
    : d_ptr(new WidgetContainerPrivate(parent))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(d_ptr.get());
    mainLayout->setContentsMargins(0, 0, 0, 0);

    d_ptr.get()->q_ptr = this;

    connect(d_ptr.get(), SIGNAL(widgetsCountChanged()), this, SIGNAL(widgetsCountChanged()));
}

WidgetContainer::~WidgetContainer() {}

const QVector<QWidget *> &WidgetContainer::getWidgets()
{
    return d_ptr.get()->getWidgets();
}

void WidgetContainer::setMinimum(int count)
{
    d_ptr.get()->setMinimum(count);
}

void WidgetContainer::setMaximum(int count)
{
    d_ptr.get()->setMaximum(count);
}

void WidgetContainer::fill(int count)
{
    d_ptr.get()->fill(count);
}

void WidgetContainer::addWidget()
{
    d_ptr.get()->addWidget();
}

void WidgetContainer::setSpinBoxTitle(const QString &sbox_title)
{
    d_ptr.get()->setSpinBoxTitle(sbox_title);
}

void WidgetContainer::setTabTitle(const QString &tab_title)
{
    d_ptr.get()->setTabTitle(tab_title);
}

int WidgetContainer::size()
{
    return getWidgets().size();
}

void WidgetContainer::slotDataChanged()
{
    ;//qDebug() << "122334354";
}
