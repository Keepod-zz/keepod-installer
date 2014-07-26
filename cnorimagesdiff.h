#ifndef CNORIMAGESDIFF_H
#define CNORIMAGESDIFF_H

#include <QObject>
#include "cnorchangedblocks.h"

#define MAX_TRY_COUNT           3

class CNorImagesDiff : public QObject
{
    Q_OBJECT
public:
    explicit CNorImagesDiff(QObject *parent = 0);

    //static void clone ( const char *i_szSrcZip, const char *i_szDstDev );

    int cloneStep ( const char *i_szDstDev );

private:
    int __cloneStep ( const char *i_szDstDev );

private:
    int m_nCurStep;
    STChangedFileInfo **m_aCFInfos;
    int m_nStepCount;
    
signals:
    
public slots:
    
};

#endif // CNORIMAGESDIFF_H
