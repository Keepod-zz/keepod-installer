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

// if neither i_szSrcZip nor i_szDstDev are not null, prepare for writing
// else if i_szSrcZip=NULL and i_szDstDev!=NULL, go to next step.
// or else return -1 (means error).
// when done, return 0.
int CNorImagesDiff::cloneStep ( const char *i_szSrcZip, const char *i_szDstDev )
{
    if ( i_szSrcZip!=NULL && i_szDstDev!=NULL ) {
        CNorChangedBlocks::unzip(i_szSrcZip);

        s_aCFInfos = CNorChangedBlocks::extract(&s_nStepCount);
        if ( s_aCFInfos == NULL ) {
            return 0;
        }

        s_nCurStep = 0;
        return s_nStepCount;
    } else {
        if ( s_aCFInfos == NULL ) {
            return -1;
        }

        if ( i_szSrcZip==NULL && i_szDstDev!=NULL ) {
            DEFINE_STRING(szDDParam, 256);
            DEFINE_STRING(szTmp, 256);

            sprintf ( szTmp, "%s/%s", TEMPDIR, s_aCFInfos[s_nCurStep]->name );
            sprintf ( szDDParam, "if=%s of=%s bs=%d seek=%llu count=%llu",
                      szTmp, i_szDstDev, BLOCK_SIZE,
                      (s_aCFInfos[s_nCurStep]->start)/BLOCK_SIZE,
                      (s_aCFInfos[s_nCurStep]->end-s_aCFInfos[s_nCurStep]->start)/BLOCK_SIZE );

            unetbootin::callexternapp("dd", szDDParam);

            s_nCurStep ++;
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

            return s_nCurStep;
        } else {
            return -1;
        }
    }
}

