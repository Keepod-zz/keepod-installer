#include "cnorimagesdiff.h"
#include "cnorchangedblocks.h"
#include "definitions.h"
#include "unetbootin.h"

#define BLOCK_SIZE         1024

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
