#ifndef CNORCHANGED_BLOCKS_H
#define CNORCHANGED_BLOCKS_H

#include <QObject>
#include <zip.h>

typedef struct {
    quint64  start;
    quint64  end;
    char     name[256];
    char     md5[256];
} STChangedFileInfo;

#define CHANGED_INDEX_FILE      "changed.index"

// Norman's 'ChangedBlocks' class
class CNorChangedBlocks : public QObject
{
    Q_OBJECT

private:
    static int s_nExtractedCount;

public:
    static STChangedFileInfo **s_aCFInfos;
    static int s_nStepCount;


public:
    explicit CNorChangedBlocks(QObject *parent = 0);

    static int prepareClone ( const char *i_szSrcZip );

    static void finalize ( void );

private:
    // extract the given file into the current directory.
    static void unzip ( QString i_szFileName );

    // load infos about changed blocks from 'changed.index'.
    static STChangedFileInfo** extract ( int *o_nItemCount );
    
signals:
    
public slots:
    
};

#endif // CNORCHANGED_BLOCKS_H
