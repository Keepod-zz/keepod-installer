#include "cnorchangedblocks.h"
#include "definitions.h"
#include "unetbootin.h"


#include "zip.h"

int CNorChangedBlocks::s_nExtractedCount = 0;
STChangedFileInfo **CNorChangedBlocks::s_aCFInfos = NULL;
int CNorChangedBlocks::s_nStepCount = 0;

CNorChangedBlocks::CNorChangedBlocks(QObject *parent) :
    QObject(parent)
{
}

void CNorChangedBlocks::unzip ( QString i_szFileName )
{

#ifdef Q_OS_MAC

#else

    // get file handle of the zip file.
    zip *pZipArchive = zip_open(i_szFileName.toUtf8(), 0, NULL);

    if ( pZipArchive == NULL ) {
        return;
    }

    // make the temporary directory.
    DEFINE_STRING(szCmdParam, 256);

    sprintf ( szCmdParam, "-p %s", TEMPDIR );
    unetbootin::callexternapp("mkdir", szCmdParam);

    // extract files from the zip file.
    int r;
    int nFilesTotal = zip_get_num_files(pZipArchive);
    s_nExtractedCount = nFilesTotal;

    DEFINE_STRING(pBuf, 8192);

    for ( int i=0; i<nFilesTotal; i++ ) {
        zip_file *pFileInZip = zip_fopen_index(pZipArchive, i, 0);

        if ( pFileInZip == NULL ) {
            // if not possible to read file from the archive, skip it.
            continue;
        }

        DEFINE_STRING(szFileName, 256);
        sprintf ( szFileName, "%s/%s", TEMPDIR, zip_get_name(pZipArchive, i, 0) );

        FILE *fp = fopen(szFileName, "w");

        while ( (r = zip_fread(pFileInZip, pBuf, sizeof(pBuf))) > 0 ) {
            // store into a new file.
            fwrite (pBuf, 1, r, fp);
        }

        fclose (fp);

        zip_fclose(pFileInZip);
    }

    zip_close(pZipArchive);

#endif
}

STChangedFileInfo** CNorChangedBlocks::extract ( int *o_nItemCount )
{
    // build the path of 'changed.index' file.
    DEFINE_STRING(szChangedIndexFile, 256);

    STChangedFileInfo **aCFInfos = NULL;

    sprintf ( szChangedIndexFile, "%s/%s", TEMPDIR, CHANGED_INDEX_FILE);

    if ( s_nExtractedCount <= 0 ) {
        return NULL;
    }

    // read infos about changed-xxx files
    FILE *fp = fopen(szChangedIndexFile, "r");
    if ( fp == NULL ) {
        return NULL;
    }

    *o_nItemCount = s_nExtractedCount-1; // except for 'changed.index'
    s_nExtractedCount = 0;
    aCFInfos = (STChangedFileInfo**) malloc (sizeof(STChangedFileInfo*) * (*o_nItemCount));

    int nItemCount = 0;
    DEFINE_STRING(pBuf, 1024);

    while ( fgets(pBuf, 1024, fp) != NULL ) {
        int nCommaCount = 0;
        // process the csv string: ',' -> ' '    '\n' -> '\0'
        for ( int i=0; pBuf[i]; i++ ) {
            if ( i >= 1024 ) {
                break;
            }

            if ( pBuf[i] == ',' ) {
                pBuf[i] = ' ';
                nCommaCount ++;
            }

            if ( (pBuf[i]=='\r') || (pBuf[i]=='\n') ) {
                pBuf[i] = '\0';
            }
        }

        // if the comma count is not 3, the string is not correct certainly, skip it.
        if ( nCommaCount != 3 ) {
            continue;
        }

        STChangedFileInfo *stNewCFInfo = (STChangedFileInfo*) malloc (sizeof(STChangedFileInfo));
        sscanf ( pBuf, "%llu %llu %s %s", &(stNewCFInfo->start),
                 &(stNewCFInfo->end), stNewCFInfo->name,
                 stNewCFInfo->md5);
        aCFInfos[nItemCount] = stNewCFInfo;

        nItemCount ++;
    }

    fclose ( fp );

    // if the count of extracted files and the count of items read are not the same,
    // free all of data.
    if ( nItemCount != *o_nItemCount ) {
        for ( int i=0; i<nItemCount; i++ ) {
            free ( aCFInfos[i] );
        }

        free ( aCFInfos );

        *o_nItemCount = 0;

        return NULL;
    }

    return aCFInfos;
}

// unzip the given file, extract block infos from it.
// Return: extracted count
//         0: error, no extracted blocks
//         n: ...
int CNorChangedBlocks::prepareClone ( const char *i_szSrcZip )
{
    if ( i_szSrcZip == NULL ) {
        return 0;
    }

    unzip(i_szSrcZip);

    s_aCFInfos = extract(&s_nStepCount);
    if ( s_aCFInfos == NULL ) {
        return 0;
    }

    return s_nStepCount;
}

void CNorChangedBlocks::finalize( void )
{
    if ( s_nStepCount > 0 ) {
        // remove data
        for ( int i=0; i<s_nStepCount; i++ ) {
            free ( s_aCFInfos[i] );
        }

        free ( s_aCFInfos );

        s_aCFInfos = NULL;
        s_nStepCount = 0;
        s_nExtractedCount = 0;
    }
}
