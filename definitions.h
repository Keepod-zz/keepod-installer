#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#endif // DEFINITIONS_H

// XXX
//#define OLD_VERSION

//#define LATEST_VERSION_URL          "http://repos.keepod.org/installer-latest/keepod.iso"

//#define LATEST_VERSION_URL_BASE     "http://li515-234.members.linode.com/release/"
#define LATEST_VERSION_URL_BASE     "ftp://122.143.5.142/pub/keepod/"
#define LATEST_VERSION_URL_NAME          "keepod-latest.zip"
#define LATEST_VERSION_MD5_NAME          "md5sum.txt"

#define LATEST_VERSION_URL          LATEST_VERSION_URL_BASE LATEST_VERSION_URL_NAME
#define LATEST_VERSION_MD5          LATEST_VERSION_URL_BASE LATEST_VERSION_MD5_NAME


#define TEMPDIR                     "/opt/keepodin"

#define DEFINE_STRING(a,len);       \
    char a[len] = {0};              \
    memset ( a, 0, len );

#ifdef OLD_VERSION

#define PRG_INIT                    0
#define PRG_ISO_PREPARED            20
#define PRG_DRIVE_PREPARED          30
#define PRG_ISO_EXTRACTED           60
#define PRG_BOOTLOADER_INSTALLED    90
#define PRG_FINISHED                100

#else

#define PRG_INIT                    0
// downloaded
#define PRG_ISO_PREPARED            40
// md5 check success
#define PRG_DRIVE_PREPARED          50
// zip extracted
#define PRG_ISO_EXTRACTED           60
#define PRG_BOOTLOADER_INSTALLED    60
// writed
#define PRG_FINISHED                100

#endif






#ifdef Q_OS_WIN32
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <shellapi.h>
#endif

#ifdef Q_OS_MACX
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#endif

#ifdef  Q_OS_LINUX
#include <sys/vfs.h>
#endif

#ifdef AUTOSUPERGRUBDISK
#define KEEPOD_INSTALLER_TITLE "Auto Super Grub Disk"
#define NOEXTERN
//#define NOISO
#define HDDINSTALL
#endif

#ifdef EEEPCLOS
#define KEEPOD_INSTALLER_TITLE "UNetbootin-EeePCLinuxOS"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef EEEUBUNTU
#define KEEPOD_INSTALLER_TITLE "UNetbootin-Ubuntu Eee"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef ELIVE
#define KEEPOD_INSTALLER_TITLE "Elive USB Installer"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef GNEWSENSE
#define KEEPOD_INSTALLER_TITLE "FUSBi"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef KIWILINUX
#define KEEPOD_INSTALLER_TITLE "Kiwi pe USB"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef NIMBLEX
#define KEEPOD_INSTALLER_TITLE "NimbleX Installer"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef SLITAZ
#define KEEPOD_INSTALLER_TITLE "SliTaz Installer"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#endif

#ifdef XPUD
#define KEEPOD_INSTALLER_TITLE "xPUD USB Installer"
#define NOMANUAL
#define NOFLOPPY
//#define USBINSTALL
#define NOEXTRACTKERNEL
#define NOEXTRACTINITRD
#define NODEFAULTBOOT
#define NODEFAULTKERNEL
#define NOINITRD
#endif

#ifndef KEEPOD_INSTALLER_TITLE
#define KEEPOD_INSTALLER_TITLE "Keepod Installer"
#define STDUNETBOOTIN
#define USBINSTALL
#endif
