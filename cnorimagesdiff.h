#ifndef CNORIMAGESDIFF_H
#define CNORIMAGESDIFF_H

#include <QObject>

class CNorImagesDiff : public QObject
{
    Q_OBJECT
public:
    explicit CNorImagesDiff(QObject *parent = 0);

    static void clone ( const char *i_szSrcZip, const char *i_szDstDev );
    
signals:
    
public slots:
    
};

#endif // CNORIMAGESDIFF_H
