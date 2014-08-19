# -*- coding: utf-8 -*-

import time

# return of msg process
RET_SUCCESS         = 0
RET_NONE            = 1
RET_ERROR           = 2
RET_FAILED          = -1

# msg of installer

MSG_DOWNLOADING                 = u"Downloading the latest version now"
MSG_CHECKING_MD5SUM             = u"Checking the md5sum of the image"
MSG_PREPARING_INSTALL           = u"Preparing install"
MSG_WRITING                     = u"Writing downloaded contents to the disk"

MSG_NO_USB_DISKS                = u"There are no usb disks to process."
MSG_NO_SELECTED_DEVICE          = u"Please select one or more devices."
MSG_NO_SOURCE_ISO               = u"Please input/select the path to the Keepod iso file."
MSG_FILE_NOT_FOUND              = u"The specified iso file does not exist"
MSG_DOWNLOAD_FAILED             = u"Failed to download"
MSG_MD5_MISMATCH                = u"The downloaded file is corrupt. Please try again."
MSG_PREPARE_ERROR               = u"An error occurs while preparing install."
MSG_WRITE_FAILED                = u"An error occurs while writing into the disk."

MSG_UMOUNT_FAILED               = u"Failed to unmount partitions on "
MSG_REPARTITION_FAILED          = u"Failed to repartition"

MSG_CANCELED                    = u"Installing Keepod was canceled by the user."
MSG_COMPLETED                   = u"Installing Keepod was successfully completed."

MSG_CONFIRM_BUILD               = u"Are you sure want to install Keepod on the selected devices? Any data on the devices will be deleted."
MSG_CONFIRM_CANCEL              = u"Canceling the running job will lead to the unexpectable result. Are you sure want to cancel the running job?"
MSG_CONFIRM_EXIT                = u"Are you sure want to exit this application?"
MSG_CONFIRM_EXIT2               = u"Are you sure want to cancel the running job and exit this application?"
MSG_INSTALL_GRUB                = u"Keepod Installer requires grub-0.97 to be installed. Are you sure want to install grub-0.97?"
MSG_GRUB_WAIT                   = u"Installing grub will take a few minutes. Please wait..."

QT_MESSAGE_BOX = 'QMessageBox'
QT_PUSH_BUTTON = 'QPushButton'

class MsgHandler():
    def __init__(self, app, test, duration):
        self.duration = duration
        self.app = app
        self.test = test
        self.msgMap = {
            MSG_NO_USB_DISKS:self.msg_single_ok,
            MSG_NO_SELECTED_DEVICE:self.msg_single_ok,
            MSG_NO_SOURCE_ISO:self.msg_single_ok,
            MSG_FILE_NOT_FOUND:self.msg_single_ok,
            MSG_UMOUNT_FAILED:self.msg_single_ok,
            MSG_REPARTITION_FAILED:self.msg_single_ok,
            MSG_CANCELED:self.msg_single_ok,
            MSG_COMPLETED:self.msg_single_ok,
            
            MSG_CONFIRM_BUILD:self.msg_double_yes_no,
            MSG_CONFIRM_CANCEL:self.msg_double_yes_no,
            MSG_CONFIRM_EXIT:self.msg_double_yes_no,
            MSG_CONFIRM_EXIT2:self.msg_double_yes_no,
            MSG_INSTALL_GRUB:self.msg_double_yes_no,
        }
        return
    
    def get_msg_box(self, msg):
        """ check whether we have this msg pop dialog """
        mlist = self.app.select_many(QT_MESSAGE_BOX)
        if(0 == len(mlist)):
            return None
        else:
            for mbox in mlist:
                if mbox.text == msg:
                    return mbox
            return None
                

    def get_process_routine(self, msg):
        """ get msg handling routine according to its msg text """
        # check if we have messagebox
        if(msg in self.msgMap.keys()):
            return self.msgMap[msg]
        else:
            return None

    def msg_single_ok(self, mbox, params):
        """ msg handling routine for one single button """
        self.test.mouse.move_to_object(mbox)
        time.sleep(self.duration)
        okButton = mbox.select_single(QT_PUSH_BUTTON, text=u'OK')
        self.test.mouse.move_to_object(okButton)
        time.sleep(self.duration)
        self.test.mouse.click()
        return
    
    def msg_double_yes_no(self, mbox, bSure):
        """ msg handling routine for double buttons including yes or no """
        self.test.mouse.move_to_object(mbox)
        time.sleep(self.duration)
        if(bSure):
            button = mbox.select_single(QT_PUSH_BUTTON, text=u'&Yes')
            self.test.mouse.move_to_object(button)
            time.sleep(self.duration)
            self.test.mouse.click()
        else:
            button = mbox.select_single(QT_PUSH_BUTTON, text=u'&No')
            self.test.mouse.move_to_object(button)
            time.sleep(self.duration)
            self.test.mouse.click()
            
        return
