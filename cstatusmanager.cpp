#include "cstatusmanager.h"
#include "messages.h"

CStatusManager::CStatusManager(QObject *parent) :
    QObject(parent)
{
    m_enStat = STAT_UNKNOWN;
}

ENStatus CStatusManager::status ( void )
{
    return m_enStat;
}

void CStatusManager::setStatus ( ENStatus i_enStat, QLabel *i_lblStatus, const QString &i_szMsg )
{
    m_enStat = i_enStat;

    // if the label widget is given,
    if ( i_lblStatus ) {
        // display the status text on the label.
        QString szErrMsg;

        if ( i_szMsg.isEmpty() ) {
            szErrMsg = statusString();
        } else {
            szErrMsg = i_szMsg;
        }
        i_lblStatus->setText(szErrMsg);

        // adjust the color according to the status.
        QPalette palTextColor;

        switch ( i_enStat ) {
        case ERR_DOWNLOAD_FAILED:
        case ERR_MD5_MISMATCH:
        case ERR_EXTRACT_FAILED:
        case ERR_WRITE_FAILED:
        case ERR_CANCELED:
            palTextColor.setColor(QPalette::WindowText, Qt::red);
            break;

        case STAT_DOWNLOADING:
        case STAT_CHECKING_MD5SUM:
        case STAT_EXTRACTING:
        case STAT_WRITING:
            palTextColor.setColor(QPalette::WindowText, Qt::darkGray);
            break;

        case STAT_DONE:
            palTextColor.setColor(QPalette::WindowText, Qt::green);
            break;

        default:
            palTextColor.setColor(QPalette::WindowText, Qt::transparent);
            break;
        }
        i_lblStatus->setPalette(palTextColor);
    }
}

QString CStatusManager::statusString ( void )
{
    QString szRet;

    switch ( m_enStat ) {
    case STAT_DOWNLOADING:
        szRet = MSG_DOWNLOADING;
        break;

    case STAT_CHECKING_MD5SUM:
        szRet = MSG_CHECKING_MD5SUM;
        break;

    case STAT_EXTRACTING:
        szRet = MSG_PREPARING_INSTALL;
        break;

    case STAT_WRITING:
        szRet = MSG_WRITING;
        break;

    case STAT_DONE:
        szRet = MSG_COMPLETED;
        break;

    case ERR_DOWNLOAD_FAILED:
        szRet = MSG_DOWNLOAD_FAILED;
        break;

    case ERR_MD5_MISMATCH:
        szRet = MSG_MD5_MISMATCH;
        break;

    case ERR_EXTRACT_FAILED:
        szRet = MSG_PREPARE_ERROR;
        break;

    case ERR_WRITE_FAILED:
        szRet = MSG_WRITE_FAILED;
        break;

    case ERR_CANCELED:
        szRet = MSG_CANCELED;
        break;

    case STAT_BASE:
    case ERR_BASE:
    default:
        szRet = "";
        break;
    }

    return szRet;
}
