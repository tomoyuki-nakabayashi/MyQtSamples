#ifndef TYPES_INTERFACE_H_
#define TYPES_INTERFACE_H_

#include <QObject>
#include <QtDBus>

namespace playground {
class TypesInterface: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.qtproject.Qt.Autotests.TypesInterface")
 public:
    TypesInterface(QObject *parent)
        : QDBusAbstractAdaptor(parent)
    { }

 public slots:
    bool retrieveBool() {
      return true;
    }
};

}  // namespace playground

#endif  // TYPES_INTERFACE_H_
