#ifndef CUIMAIN_H
#define CUIMAIN_H

#include "unetbootin.h"
#include "cusbdiskinfo.h"

#define TABLE_COLUMN_CHECK          0
#define TABLE_COLUMN_LABEL          1
#define TABLE_COLUMN_PROGRESS       2
#define TABLE_COLUMN_MOREINFO       3


class CUIMain : public QWidget, private Ui::unetbootinui
{
    Q_OBJECT

public:
    CUIMain(QWidget *parent = 0);

    unetbootin  **m_aInstallTasks;
    int  m_nRunningTaskCount;

    QString m_szAppNlang;
    QString m_szAppDir;
    QString m_szAppLoc;

    // XXX
    QList<CUsbDiskInfo*> m_aUsbDiskInfos;
    bool m_bDownloadLatest;
    QString m_szIsoPath;
    bool m_bStopFlag;

    void customizeUI();
    void refreshDiskTable ();
    void getUsbDrivesList();
    QList<int> getSelectedIds ();
    bool runInstallTasks();
    void setMode ( bool bActive = true );
    void cancelTasks();

    void closeEvent (QCloseEvent *);

    QString displayfisize(quint64 fisize);

public slots:
    void on_btnBrowse_clicked();
    void dlprogressupdate(int dlbytes, int maxbytes);
    void dlprogressupdate64(qint64 dlbytes, qint64 maxbytes);

    void on_tblDevices_clicked(const QModelIndex &index);
    void on_chkDownloadLatest_stateChanged(int arg1);
    void onThreadFinished();
    void onThreadTerminated();
    void onProgressUpdate(int itemId, int prg);

    void on_btnStart_clicked();

};

#endif // CUIMAIN_H
