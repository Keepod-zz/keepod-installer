#ifndef CUSBDISKINFO_H
#define CUSBDISKINFO_H

#include <QObject>

class CUsbDiskInfo : public QObject
{
    Q_OBJECT
public:
    explicit CUsbDiskInfo(QObject *parent = 0);

public:
    QString  m_szDevName; // devname
    QString  m_szLabel; // label
    quint64  m_llSizeKb; // sizekb
    QString  m_szFileSystem; // filesystem
    QString  m_szModel; // model
    QString  m_szUuid; // uuid

    QString  m_szMountPoint; // mountpoint

    // actions
    bool umount ();
    bool keepodFormat ();
    bool writeGrub ();
    QString mount ();

    // query infos
    QString getShowableName ();
    QString getDevNodeName ();
    QString getSizeString ();
    QString getMoreInfoString ();
    void setInfoByDevname ( QString devname );
    void setLabel ( QString label );
    void setUuid ( QString uuid );

    QString getLabelFromDevname ();
    quint64 getSizeKbFromDevname ();
    QString getModelFromDevname ();
    QString getFstypeFromDevname ();
    QString getUuidFromDevname ();
    QString getParentDevname();

    QString getBlkidValue ( QString key );
    QString getNewMountPoint ();
    
signals:
    
public slots:
    
};

#endif // CUSBDISKINFO_H
