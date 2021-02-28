#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "personform.h"

using namespace utils;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_container->setWidgetType<PersonForm>("PersonForm");
    ui->widget_container->setSpinBoxTitle(QString::fromUtf8("Tab count"));
    ui->widget_container->setTabTitle(QString::fromUtf8("Person "));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_load_clicked()
{
    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }

    QJsonDocument loadDoc(QJsonDocument::fromJson(loadFile.readAll()));
    QJsonArray addressBook = loadDoc.array();
    for (int personIndex = 0; personIndex < addressBook.size(); ++personIndex) {
        QJsonObject jsonPerson = addressBook[personIndex].toObject();
        Person person;
        if (jsonPerson.contains("first_name") && jsonPerson["first_name"].isString())
            person.setFirstName( jsonPerson["first_name"].toString() );
        if (jsonPerson.contains("last_name") && jsonPerson["last_name"].isString())
            person.setLastName( jsonPerson["last_name"].toString() );
        if (jsonPerson.contains("age"))
            person.setAge( jsonPerson["age"].toInt() );

        ui->widget_container->addWidget();
        PersonForm* personForm = static_cast<PersonForm*> (ui->widget_container->getWidgets().last());
        personForm->setData(person);
    }

    return ;
}

void MainWindow::on_btn_save_clicked()
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }

    if (ui->widget_container->size() > 0)
    {
        QJsonArray addressBook;
        foreach (QWidget *widget, ui->widget_container->getWidgets())
        {
            Person person = static_cast<PersonForm*> (widget)->data();
            QJsonObject jsonPerson;
            jsonPerson["first_name"] = person.getFirstName();
            jsonPerson["last_name"] = person.getLastName();
            jsonPerson["age"] = person.getAge();
            addressBook.append(jsonPerson);
        }
        QJsonDocument saveDoc(addressBook);
        saveFile.write(saveDoc.toJson());
    }
}
