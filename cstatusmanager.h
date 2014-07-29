#ifndef CSTATUSMANAGER_H
#define CSTATUSMANAGER_H

#include <QObject>
#include <QLabel>

typedef enum {
    STAT_UNKNOWN = -1,

    STAT_BASE = 0,
    STAT_DOWNLOADING,
    STAT_CHECKING_MD5SUM,
    STAT_EXTRACTING,
    STAT_WRITING,
    STAT_DONE,

    ERR_BASE = 100,
    ERR_DOWNLOAD_FAILED,
    ERR_MD5_MISMATCH,
    ERR_EXTRACT_FAILED,
    ERR_WRITE_FAILED,
    ERR_CANCELED
} ENStatus;

class CStatusManager : public QObject
{
    Q_OBJECT
public:
    explicit CStatusManager(QObject *parent = 0);

private:
    ENStatus m_enStat;

public:
    ENStatus status ( void );
    void setStatus ( ENStatus i_enStat, QLabel *i_lblStatus = NULL, const QString &i_szMsg = "" );

    QString statusString ( void );
    
signals:
    
public slots:
    
};

#endif // CSTATUSMANAGER_H
