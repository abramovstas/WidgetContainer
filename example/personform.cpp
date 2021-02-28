#include "personform.h"
#include "ui_personform.h"

PersonForm::PersonForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonForm)
{
    ui->setupUi(this);
}

PersonForm::~PersonForm()
{
    delete ui;
}

Person PersonForm::data()
{
    m_person.setFirstName(ui->lineEdit->text());
    m_person.setLastName(ui->lineEdit_2->text());
    m_person.setAge(ui->spinBox->value());
    return m_person;
}

void PersonForm::setData(const Person &data)
{
    ui->lineEdit->setText(data.getFirstName());
    ui->lineEdit_2->setText(data.getLastName());
    ui->spinBox->setValue(data.getAge());
    return ;
}
