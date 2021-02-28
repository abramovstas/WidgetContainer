#ifndef WIDGETCONTAINERPRIVATE_H
#define WIDGETCONTAINERPRIVATE_H

#include <QWidget>
#include <QPointer>
#include "widgetfactory.h"

class QLabel;
class QSpinBox;
class QTabWidget;

namespace utils {

class WidgetContainer;

class WidgetContainerPrivate : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetContainerPrivate(QWidget *parent = nullptr);
    ~WidgetContainerPrivate();

    const QVector<QWidget *> &getWidgets();

    template <typename T>
    void reg( const QString &key )
    {
        this->key = key;
        w_factory.reg<T>(key.toStdString());
    }

    void setSpinBoxTitle(const QString &sbox_title);

    void setTabTitle(const QString &tab_title) { m_tab_title = tab_title; }

    void fill(int count);

    void addWidget();

    void setMinimum(int count) { mMinimum = count; }

    void setMaximum(int count) { mMaximum = count; }

    int size() { return widget_vec.size(); }

signals:
    void widgetsCountChanged();

private slots:
    void on_sbox_count_valueChanged(int arg1);

private:
    QPointer<QSpinBox> sbox_count;
    QString m_spinbox_lb_title;
    QPointer<QLabel> m_spinbox_lb;
    QPointer<QTabWidget> tab_widget;
    QString m_tab_title;

    using WidgetsFactory = factory<std::string, QWidget, QWidget *>;
    using WidgetPtr = WidgetsFactory::base_ptr;

    WidgetsFactory w_factory;
    QVector<WidgetPtr> ptr_vec;
    QVector<QWidget *> widget_vec;
    void addFormular(int formular_index);
    void delFormular();

    QString key;

    int mMinimum;
    int mMaximum;

    QPointer<WidgetContainer> q_ptr;
    friend class WidgetContainer;

    bool metodExists(QObject *obj, const char *slot_sign);
};

}

#endif // WIDGETCONTAINERPRIVATE_H
