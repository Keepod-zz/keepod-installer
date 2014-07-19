#ifndef INSTALLTASKINFO_H
#define INSTALLTASKINFO_H

#include <QObject>

#include "cusbdiskinfo.h"

class InstallTaskInfo : public QObject
{
    Q_OBJECT
public:
    explicit InstallTaskInfo(QObject *parent = 0);

    CUsbDiskInfo     *disk;
    int             diskIdOnUI;
    QString         isoPath;
    
signals:
    
public slots:
    
};

#endif // INSTALLTASK_H
