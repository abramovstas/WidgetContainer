#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person
{
public:
    Person();
    Person(const Person & other);
    Person(Person && other);
    Person(const QByteArray & data);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    int getAge() const;
    void setAge(int value);

    QByteArray serialize() const;
    void deserialize(const QByteArray &data);

    friend QDataStream & operator<<(QDataStream &stream, const Person &data);
    friend QDataStream & operator>>(QDataStream &stream, Person &data);

    friend bool operator==(const Person & left, const Person & right);

    Person & operator=(const Person & other);
    Person & operator=(Person && other);

private:
    QString firstName = "";
    QString lastName = "";
    int age = 0;
};

#endif // PERSON_H
