#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include "widgetcontainerprivate.h"

namespace utils {

class WidgetContainer : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetContainer(QWidget *parent = nullptr);
    ~WidgetContainer();

    const QVector<QWidget *> &getWidgets();

    template<typename T>
    void setWidgetType(const QString &widget_name)
    {
        d_ptr.get()->reg<T>(widget_name);
    }

    void setMinimum(int count);

    void setMaximum(int count);

    void fill(int count);

    void addWidget();

    void setSpinBoxTitle(const QString &sbox_title);

    void setTabTitle(const QString &tab_title);

    int size();

signals:
    void dataChanged();

    void widgetsCountChanged();

private slots:
    void slotDataChanged();

protected:
    std::unique_ptr<WidgetContainerPrivate> d_ptr;
};

}

#endif // WIDGETCONTAINER_H


