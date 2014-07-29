#ifndef MESSAGES_H
#define MESSAGES_H

#define MSG_DOWNLOADING                 "Downloading the latest version now"
#define MSG_DOWNLOADING_USER            "Downloading %1"
#define MSG_CHECKING_MD5SUM             "Checking the md5sum of the image"
#define MSG_PREPARING_INSTALL           "Preparing install"
#define MSG_WRITING                     "Writing downloaded contents to the disk"

#define MSG_NO_USB_DISKS                "There are no usb disks to process."
#define MSG_NO_SELECTED_DEVICE          "Please select one or more devices."
#define MSG_NO_SOURCE_ISO               "Please input/select the path to the Keepod iso file."
#define MSG_FILE_NOT_FOUND              "The specified iso file does not exist"
#define MSG_DOWNLOAD_FAILED             "Failed to download"
#define MSG_MD5_MISMATCH                "The downloaded file is corrupt. Please try again."
#define MSG_PREPARE_ERROR               "An error occurs while preparing install."
#define MSG_WRITE_FAILED                "An error occurs while writing into the disk."

// @deprecated@
#define MSG_UMOUNT_FAILED               "Failed to unmount partitions on "
#define MSG_REPARTITION_FAILED          "Failed to repartition"

#define MSG_CANCELED                    "Installing Keepod was canceled by the user."
#define MSG_COMPLETED                   "Installing Keepod was successfully completed."

#define MSG_CONFIRM_BUILD               "Are you sure want to install Keepod on the selected devices? Any data on the devices will be deleted."
#define MSG_CONFIRM_CANCEL              "Canceling the running job will lead to the unexpectable result. Are you sure want to cancel the running job?"
#define MSG_CONFIRM_EXIT                "Are you sure want to exit this application?"
#define MSG_CONFIRM_EXIT2               "Are you sure want to cancel the running job and exit this application?"
#define MSG_INSTALL_GRUB                "Keepod Installer requires grub-0.97 to be installed. Are you sure want to install grub-0.97?"
#define MSG_GRUB_WAIT                   "Installing grub will take a few minutes. Please wait..."


#define SHOW_MESSAGE(title,msg);               \
    QMessageBox msgb; \
    msgb.setIcon(QMessageBox::Information); \
    msgb.setWindowTitle(title); \
    msgb.setText(msg); \
    msgb.setStandardButtons(QMessageBox::Ok); \
    msgb.exec();

#endif // MESSAGES_H
