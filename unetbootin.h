/*
unetbootin.h from UNetbootin <http://unetbootin.sourceforge.net>
Copyright (C) 2007-2008 Geza Kovacs <geza0kovacs@gmail.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License at <http://www.gnu.org/licenses/> for more details.
*/

#ifndef UNETBOOTIN_H
#define UNETBOOTIN_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QThread>
#include <time.h>
//#include <QtDebug>

#include "ui_unetbootin.h"

#include "definitions.h"
#include "installtaskinfo.h"
#include "cstatusmanager.h"
#include "cnorimagesdiff.h"



class customver : public QObject
{
	Q_OBJECT
};

class uninstaller : public QObject
{
	Q_OBJECT
};

class callexternappT : public QThread
{
public:
	QString execFile;
	QString execParm;
	QString retnValu;
	void run();
};

class callexternappWriteToStdinT : public QThread
{
public:
	QString execFile;
	QString execParm;
	QString writeToStdin;
	QString retnValu;
	void run();
};

class copyfileT : public QThread
{
	Q_OBJECT

public:
	QString source;
	QString destination;
	void run();

signals:
	void datacopied64(qint64 dlbytes, qint64 maxbytes);
	void finished();
};

class ubngetrequestheader : public QHttpRequestHeader
{
public:
	ubngetrequestheader(QString urhost, QString urpath);
};

class randtmpfile : public QFile
{
public:
	randtmpfile(QString rfpath, QString rfextn);
	static QString getrandfilename(QString rfpath, QString rfextn);
};

class nDirListStor : public QObject
{
	Q_OBJECT

public:
	QStringList nDirFileListSL;
	int nMinFileSizeBytes;
	int nMaxFileSizeBytes;
	bool searchsymlinks;

public slots:
	void sAppendSelfUrlInfoList(QUrlInfo curDirUrl);
};

class CUIMain;

class unetbootin : public QThread
{
	Q_OBJECT

public:
    unetbootin(InstallTaskInfo *taskInfo);
	QString trcurrent;
	QString trdone;

    static QString ubntmpf;
	QString nameDistro;
	QString nameVersion;
    static bool skipExtraction;
    static bool isarch64;
    static bool islivecd;
    static bool isnetinstall;
    static bool ishdmedia;
    static bool overwriteall;
    static bool searchsymlinks;
    static bool ignoreoutofspace;
    static bool dontgeneratesyslinuxcfg;
    static bool downloadFailed;
    static bool exitOnCompletion;
    static bool testingDownload;
    static bool issalt;
    static bool redundanttopleveldir;
    QString redundantrootdirname;
	QString saltRootDir;
    static int persistenceSpaceMB;
	QString extraBootOptions;
	QStringList locatedsyslinuxcfgfiles;
	QString targetDrive;
	QString targetPath;
    static QString installType;
	QString targetDev;
	QString rawtargetDev;
	QString devluid;
	QString devlabel;
	QString devuuid;
	QString postinstmsg;
	QString kernelLine, kernelParam, kernelLoc, kernelOpts, initrdLine, initrdLoc, initrdOpts;
	QString slinitrdLine;
    static QString sevzcommand;
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > extraoptionsPL;
	QMap<QString, QString> grub2vars;
    static QFile *logFile;
    static QTextStream *logStream;
    QStringList loggedLinesNotYetWritten;
	#ifdef Q_OS_UNIX
    static QString fdiskcommand;
    static QString sfdiskcommand;
    static QString dfcommand;
    static QString blkidcommand;
    static QString volidcommand;
    static QString syslinuxcommand;
    static QString extlinuxcommand;
    static QString mke2fscommand;
    static QString mlabelcommand;
    static QString e2labelcommand;
    static bool isext2;
	#endif
#ifdef Q_OS_MAC
	QDir resourceDir;
#endif

    InstallTaskInfo  *taskInfo;
    bool m_bStopFlag;

    CNorImagesDiff  norImagesDiff;
    static bool checkGrub1Installed ();

    static bool ubninitialize(/*QList<QPair<QString, QString> > oppairs*/);

	QPair<QPair<QStringList, QList<quint64> >, QStringList> listarchiveconts(QString archivefile);
	bool overwritefileprompt(QString ovwfileloc);
	bool ignoreoutofspaceprompt(QString destindir);
	bool extractfile(QString filepath, QString destinfileL, QString archivefile);
	bool checkifoutofspace(QString destindir);
	QString locatekernel(QString archivefile, QPair<QStringList, QList<quint64> > archivefileconts);
	bool extractkernel(QString archivefile, QString kernoutputfile, QPair<QStringList, QList<quint64> > archivefileconts);
	QString locateinitrd(QString archivefile, QPair<QStringList, QList<quint64> > archivefileconts);
	bool extractinitrd(QString archivefile, QString initoutputfile, QPair<QStringList, QList<quint64> > archivefileconts);
	QString extractcfg(QString archivefile, QStringList archivefileconts);
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > extractcfgL(QString archivefile, QStringList archivefileconts);
	QString getfullarchivepath(QString relativefilepath, QStringList archivefile);
	QString filteroutlist(QString listofdata, QList<QRegExp> listofmatches);
	QString filteroutlist(QStringList listofdata, QList<QRegExp> listofmatches);
	QStringList filteroutlistL(QStringList listofdata, QList<QRegExp> listofmatches);
	void extractiso(QString isofile);
	void extractiso_krd10(QString isofile);
	void copyfilegui(QString src, QString dst);
	QStringList makepathtree(QString dirmkpathw, QStringList pathlist);
	QStringList extractallfiles(QString archivefile, QString dirxfilesto, QPair<QStringList, QList<quint64> > filesizelist, QStringList outputfilelist);
	QString getgrubcfgargs(QString cfgfile);
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > getgrubcfgargsL(QString cfgfile);
	QString getFirstTextBlock(QString fulltext);
	void loadgrub2env(QString cfgfile);
	QString getgrub2cfgargs(QString cfgfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > getgrub2cfgargsL(QString cfgfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QString getcfgkernargs(QString cfgfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > getcfgkernargsL(QString cfgfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QString searchforincludesfile(QString includesfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > searchforincludesfileL(QString includesfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QString searchforgrub2includesfile(QString includesfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
	QPair<QPair<QStringList, QStringList>, QPair<QStringList, QStringList> > searchforgrub2includesfileL(QString includesfile, QString archivefile, QStringList archivefileconts, QStringList visitedincludes);
    static bool downloadfile(QString fileurl, QString targetfile, int minsize=524288, CUIMain *uimain = NULL);
	QString downloadpagecontents(QString pageurl);
	QStringList lstFtpDirFiles(QString ldfDirStringUrl, int ldfMinSize, int ldfMaxSize);
	QStringList lstHttpDirFiles(QString ldfDirStringUrl);
	QStringList lstNetDirFiles(QString ldfDirStringUrl, int ldfMinSize, int ldfMaxSize);
	QPair<QString, int> weightedFilterNetDir(QString ldfDirStringUrl, int ldfMinSize, int ldfMaxSize, QList<QRegExp> ldfFileMatchExp);
	QString fileFilterNetDir(QStringList ldfDirStringUrlList, int ldfMinSize, int ldfMaxSize, QList<QRegExp> ldfFileMatchExp);
	QPair<QString, int> filterBestMatch(QStringList ufStringList, QList<QRegExp> filterExpList);
	void sysreboot();
	static QString callexternapp(QString xexecFile, QString xexecParm);
	static QString callexternappWriteToStdin(QString xexecFile, QString xexecParm, QString xwriteToStdin);
	QString getdevluid(QString voldrive);
    static QString getlabel(QString voldrive);
    static QString getuuid(QString voldrive);
#ifdef Q_OS_MAC
    static QString getlabel(QString voldrive, QString diskutilinfo);
    static QString getuuid(QString voldrive, QString diskutilinfo);
#endif

    static QStringList listcurdrives();
    static QStringList listsanedrives();
    static QStringList listalldrives();

	void replaceTextInFile(QString repfilepath, QRegExp replaceme, QString replacewith);
	QString fixkernelbootoptions(const QString &cfgfileCL);
	void setLabel(QString devname, QString newlabel);
	#ifdef Q_OS_UNIX
    static QString locatecommand(QString commandtolocate, QString reqforinstallmode, QString packagename);
	QString locatedevicenode(QString mountpoint);
	QString locatemountpoint(QString devicenode);
	QString getGrubNotation(QString devicenode);
	QString getGrub2Notation(QString devicenode);
	int letterToNumber(QChar lettertoconvert);
	int getDiskNumber(QString devicenode);
	int getPartitionNumber(QString devicenode);
	#endif
	#ifdef Q_OS_WIN32
	void installsvzip();
	void configsysEdit();
	void bootiniEdit();
	void vistabcdEdit();
	#endif
	void instIndvfl(QString srcfName, QString dstfName);
	QString instTempfl(QString srcfName, QString dstfType);

    void run(void);

	void instDetType();
	#ifdef Q_OS_UNIX
	void writegrub2cfg();
	#endif
	void runinsthdd();
	void runinstusb();
    void logText(const QString &text);
    void finishLogging();
    void writeTextToFile(const QString &text, const QString &filePath);
	void fininstall();
    static void rmFile(const QString &fn);
    static void rmFile(QFile &fn);
	void mvFile(const QString &fn, const QString &outfn);
	void mvFile(QFile &fn, QFile &outfn);
	void showDownloadFailedScreen(const QString &fileurl);

public slots:
    void cpprogressupdate64(qint64 dlbytes, qint64 maxbytes);

signals:
    void progress(int id, int prg);
    void failed(int id, int err );
};

#endif

