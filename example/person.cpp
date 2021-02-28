#include "person.h"

#include <QDataStream>

Person::Person()
{
    deserialize(QByteArray(sizeof(Person), 0));
}

Person::Person(const Person &other)
{
    *this = other;
}

Person::Person(Person &&other)
{
    *this = other;
}

Person::Person(const QByteArray &data)
{
    deserialize(data);
}

QString Person::getFirstName() const
{
    return firstName;
}

void Person::setFirstName(const QString &value)
{
    firstName = value;
}

QString Person::getLastName() const
{
    return lastName;
}

void Person::setLastName(const QString &value)
{
    lastName = value;
}

int Person::getAge() const
{
    return age;
}

void Person::setAge(int value)
{
    age = value;
}

QByteArray Person::serialize() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << *this;
    return data;
}

void Person::deserialize(const QByteArray &data)
{
    QDataStream stream(data);
    stream >> *this;
}

QDataStream & operator<<(QDataStream &stream, const Person &data)
{
    stream << data.firstName;
    stream << data.lastName;
    stream << data.age;
    return stream;
}

QDataStream & operator>>(QDataStream &stream, Person &data)
{
    stream >> data.firstName;
    stream >> data.lastName;
    stream >> data.age;
    return stream;
}

bool operator==(const Person &left, const Person &right)
{
    return (left.firstName == right.firstName
         && left.lastName == right.lastName
         && left.age == right.age);
}

Person &Person::operator=(const Person &other)
{
    setFirstName(other.getFirstName());
    setLastName(other.getLastName());
    setAge(other.getAge());

    return *this;
}

Person &Person::operator=(Person &&other)
{
    setFirstName(other.getFirstName());
    setLastName(other.getLastName());
    setAge(other.getAge());

    return *this;
}
