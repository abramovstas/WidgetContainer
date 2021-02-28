#ifndef PERSONFORM_H
#define PERSONFORM_H

#include <QWidget>
#include <memory>

#include <person.h>

class Person;

namespace Ui {
class PersonForm;
}

class PersonForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonForm(QWidget *parent = 0);
    ~PersonForm();

    Person data();
    void setData(const Person& data);

private:
    Ui::PersonForm *ui;
    Person m_person;
};

#endif // PERSONFORM_H
