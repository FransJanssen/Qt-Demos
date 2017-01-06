#pragma once
#include <QObject>

namespace Ps{
class TestClass : public QObject
{
    Q_OBJECT
public:
    explicit TestClass(QObject *parent=0);

private:
    explicit TestClass(const TestClass& rhs) = delete;
    TestClass& operator= (const TestClass& rhs) = delete;
};
}


