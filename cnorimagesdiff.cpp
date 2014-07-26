#include "cnorimagesdiff.h"
#include "cnorchangedblocks.h"
#include "definitions.h"
#include "unetbootin.h"

#define BLOCK_SIZE         1024

CNorImagesDiff::CNorImagesDiff(QObject *parent) :
    QObject(parent)
{
    m_nCurStep = 0;
    m_nStepCount = CNorChangedBlocks::s_nStepCount;
    m_aCFInfos = CNorChangedBlocks::s_aCFInfos;
}



int CNorImagesDiff::cloneStep ( const char *i_szDstDev )
{
    int nTryCount = 0;
    while ( nTryCount < MAX_TRY_COUNT ) {
        int nRet = __cloneStep(i_szDstDev);
        if ( nRet >= 0 ) {
            return nRet;
        }

        nTryCount ++;
    }

    return -1;
}

// Return:
//     0: all done
//     n: the current step
//    -1: error
int CNorImagesDiff::__cloneStep ( const char *i_szDstDev )
{
    // check parameters
    if ( i_szDstDev==NULL || m_aCFInfos==NULL ) {
        return -1;
    }

    if ( m_nCurStep == m_nStepCount ) {
        m_nCurStep = 0;
        m_nStepCount = 0;

        // all steps have done.
        return 0;
    }

    STChangedFileInfo *pCurCFInfo = m_aCFInfos[m_nCurStep];

    // call dd
    DEFINE_STRING(szDDParam, 256);
    DEFINE_STRING(szTmp, 256);

    sprintf ( szTmp, "%s/%s", TEMPDIR, pCurCFInfo->name );
    sprintf ( szDDParam, "if=%s of=%s bs=%d seek=%llu count=%llu status=noxfer conv=fdatasync",
              szTmp, i_szDstDev, BLOCK_SIZE,
              (pCurCFInfo->start)/BLOCK_SIZE,
              (pCurCFInfo->end-pCurCFInfo->start)/BLOCK_SIZE );

    unetbootin::callexternapp("dd", szDDParam);

    // call dcfldd
    DEFINE_STRING(szDcflddParam, 256);

    sprintf ( szDcflddParam, "if=%s of=/dev/null bs=%d skip=%llu count=%llu hash=md5",
              i_szDstDev, BLOCK_SIZE,
              (pCurCFInfo->start)/BLOCK_SIZE,
              (pCurCFInfo->end-pCurCFInfo->start)/BLOCK_SIZE );

    QString szCmdRes = unetbootin::callexternapp("dcfldd", szDcflddParam);
    if ( szCmdRes.contains(pCurCFInfo->md5) ) {
        m_nCurStep ++;
    } else {
        return -1;
    }

    return m_nCurStep;
}


/*
void CNorImagesDiff::clone ( const char *i_szSrcZip, const char *i_szDstDev )
{
    STChangedFileInfo **aCFInfos = NULL;
    DEFINE_STRING(szDDParam, 256);
    int nItemCount;

    CNorChangedBlocks::unzip(i_szSrcZip);

    aCFInfos = CNorChangedBlocks::extract(&nItemCount);
    if ( aCFInfos == NULL ) {
        return;
    }

    DEFINE_STRING(szTmp, 256);
    for ( int i=0; i<nItemCount; i++ ) {
        sprintf ( szTmp, "%s/%s", TEMPDIR, aCFInfos[i]->name );
        sprintf ( szDDParam, "if=%s of=%s bs=%d seek=%llu count=%llu",
                  szTmp, i_szDstDev, BLOCK_SIZE,
                  (aCFInfos[i]->start)/BLOCK_SIZE, (aCFInfos[i]->end)/BLOCK_SIZE );

        unetbootin::callexternapp("dd", szDDParam);
    }
}
*/

