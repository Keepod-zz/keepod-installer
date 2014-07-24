#include "cnorimagesdiff.h"
#include "cnorchangedblocks.h"
#include "definitions.h"
#include "unetbootin.h"

#define BLOCK_SIZE         1024

int CNorImagesDiff::s_nCurStep = 0;
int CNorImagesDiff::s_nStepCount = 0;
STChangedFileInfo **CNorImagesDiff::s_aCFInfos = NULL;

CNorImagesDiff::CNorImagesDiff(QObject *parent) :
    QObject(parent)
{
}

// unzip the given file, extract block infos from it.
// Return: extracted count
//         0: error, no extracted blocks
//         n: ...
int CNorImagesDiff::prepareClone ( const char *i_szSrcZip )
{
    if ( i_szSrcZip == NULL ) {
        return 0;
    }

    CNorChangedBlocks::unzip(i_szSrcZip);

    s_aCFInfos = CNorChangedBlocks::extract(&s_nStepCount);
    if ( s_aCFInfos == NULL ) {
        return 0;
    }

    s_nCurStep = 0;
    return s_nStepCount;
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
    if ( i_szDstDev==NULL || s_aCFInfos==NULL ) {
        return -1;
    }

    if ( s_nCurStep == s_nStepCount ) {
        // remove data
        for ( int i=0; i<s_nStepCount; i++ ) {
            free ( s_aCFInfos[i] );
        }

        free ( s_aCFInfos );

        s_nCurStep = 0;
        s_nStepCount = 0;

        // all steps have done.
        return 0;
    }

    STChangedFileInfo *pCurCFInfo = s_aCFInfos[s_nCurStep];

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
        s_nCurStep ++;
    } else {
        return -1;
    }

    return s_nCurStep;
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

