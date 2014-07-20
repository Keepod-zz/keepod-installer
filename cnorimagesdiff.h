#ifndef CNORIMAGESDIFF_H
#define CNORIMAGESDIFF_H

#include <QObject>
#include "cnorchangedblocks.h"

class CNorImagesDiff : public QObject
{
    Q_OBJECT
public:
    explicit CNorImagesDiff(QObject *parent = 0);

    static void clone ( const char *i_szSrcZip, const char *i_szDstDev );

    static int cloneStep ( const char *i_szSrcZip, const char *i_szDstDev );

private:
    static int s_nCurStep;
    static STChangedFileInfo **s_aCFInfos;
    static int s_nStepCount;
    
signals:
    
public slots:
    
};

#endif // CNORIMAGESDIFF_H
