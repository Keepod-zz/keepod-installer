# -*- coding: utf-8 -*-

from autopilot.testcase import AutopilotTestCase
from os.path import abspath, dirname, join

import time
import logging

from test_installer import installerTestBase
from test_config import *
from inner import *

class BasicProcessTests(installerTestBase):
    """ basic process for installer """

    def test_basic_net_downloading_process(self):
        """ basic test process with downloading iso from net """
        self.log_setup()
        # launch application
        self.app_setup()
        
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        exitFlag = self.app_handle_no_usb_disks_msg()
        if(RET_SUCCESS == exitFlag):
            return
        
        # go to main win position
        self.app_do_move_mouse_2_mainwin()
        
        # check "download and install..." box
        self.app_do_checkbox_download(True, None)
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        
        # process msg box poped up after clicking "make it"   
        exitFlag = self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        
        # after making finished and showing popup dialog,
        # press "OK" button and exit installer
        
        # TODO: wait_signal and then move mouse to new popbox

        # process msgbox of "Completed" or some else
        return
    
    def test_basic_local_loading_process(self):
        """ basic test process with loading iso from local path """
        self.log_setup()
        # launch application
        self.app_setup()
        
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        exitFlag = self.app_handle_no_usb_disks_msg()
        if(RET_SUCCESS == exitFlag):
            return
        
        # go to main win position
        self.app_do_move_mouse_2_mainwin()
        self.app_do_load_local_img()
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)
        
         # press "make it" button
        self.app_do_pushbutton_makeit()
        
        # process msg box poped up after clicking "make it"   
        exitFlag = self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()

        self.app_sleep(2)
        # after making finished and showing popup dialog,
        # press "OK" button and exit installer
        
        # TODO: wait_signal and then move mouse to new popbox

        # process msgbox of "Completed" or some else       
        return
    
    def test_choose_all_disks_process(self):
        """ choose all udisks to process test routine"""
        self.log_setup()
        # launch application
        self.app_setup()
        
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        exitFlag = self.app_handle_no_usb_disks_msg()
        if(RET_SUCCESS == exitFlag):
            return
        
        # go to main win position
        self.app_do_move_mouse_2_mainwin()
        
        # check "download and install..." box
        self.app_do_checkbox_download(True, None)
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        
        # process msg box poped up after clicking "make it"   
        exitFlag = self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        
        # after making finished and showing popup dialog,
        # press "OK" button and exit installer
        
        # TODO: wait_signal and then move mouse to new popbox

        # process msgbox of "Completed" or some else
        return

    def test_iso_downloading_cancel_and_continue(self):
        """ after preparation, we begin writting to udisk ,
            then we cancel the operation and the continue this process
        """
        self.log_setup()
        # launch application
        self.app_setup()
        
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        exitFlag = self.app_handle_no_usb_disks_msg()
        if(RET_SUCCESS == exitFlag):
            return
        
        # go to main win position
        self.app_do_move_mouse_2_mainwin()
        
        # check "download and install..." box
        self.app_do_checkbox_download(True, None)
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        # then we will begin downloading
        self.app_sleep(20)

        # cancel the downloading process and then restart writting
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_cancel_msg(True)
        self.app_sleep(2)
        self.app_handle_canceled_msg()
        self.app_do_move_mouse_2_mainwin()
        self.app_sleep(2)
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        self.app_sleep(2)
        return

    def test_udisk_writting_cancel_and_continue(self):
        self.log_setup()
        # launch application
        self.app_setup()
        
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        exitFlag = self.app_handle_no_usb_disks_msg()
        if(RET_SUCCESS == exitFlag):
            return
        
        # go to main win position
        self.app_do_move_mouse_2_mainwin()
        
        # check "download and install..." box
        self.app_do_checkbox_download(True, None)
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        # then we will begin downloading
        self.app_sleep(20)

        # cancel the downloading process and then restart writting
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_cancel_msg(True)
        self.app_sleep(2)
        self.app_handle_canceled_msg()
        self.app_do_move_mouse_2_mainwin()
        self.app_sleep(2)
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        self.app_sleep(2)
        return

    def test_udisk_files_md5_check_valid(self):
        return

    def app_setup(self):
        # launch application
        self.duration = 2
        self.app = self.launch_installer()
        self.msgHandler = MsgHandler(self.app, self, 2)
        self.config = TestConfig()
        return
    
    def app_sleep(self, duration):
        time.sleep(self.duration)
        return
    
    def app_handle_no_usb_disks_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_NO_USB_DISKS)
        mbox_process = self.msgHandler.get_process_routine(MSG_NO_USB_DISKS)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_do_move_mouse_2_mainwin(self):
        mainWin = self.app.select_single('CUIMain')
        self.mouse.move_to_object(mainWin)
        self.app_sleep(2)
        return
    
    def app_do_pushbutton_browser(self):
        browserButton = self.app.select_single('QPushButton', objectName='btnBrowse')
        # move mouse to btnBrowse and click
        self.mouse.move_to_object(browserButton)
        self.app_sleep(1)
        self.mouse.click()
        # move mouse to filedialog and then click cancel
        fileDialog = self.app.select_single('QFileDialog')
        self.mouse.move_to_object(fileDialog)
        self.app_sleep(1)
        cancelButton = fileDialog.select_single('QPushButton', u'Cancel')
        self.mouse.move_to_object(cancelButton)
        self.app_sleep(1)
        self.mouse.click()
        return
    
    def app_do_load_local_img(self):
        imgPath = self.config.get_img_local_file()
        lineEdit = self.app.select_single('QLineEdit', objectName='edtISOPath')
        # move mouse to lineEdit
        self.mouse.move_to_object(lineEdit)
        self.mouse.click()
        self.app_sleep(1)
        self.keyboard.type(imgPath)
        self.app_sleep(1)
        return
    
    def app_do_checkbox_download(self, bCheck, path):
        """ check whether we download iso from net or loading from local path """
        if(bCheck):
            # choose to download from internet over http or ftp
            checkBox = self.app.select_single('QCheckBox', objectName='chkDownloadLatest')
            mx, my = (checkBox.globalRect.x + 5), (checkBox.globalRect.y + 5)
            self.mouse.move(mx, my)
            self.mouse.click()
            self.app_sleep(2)
            return
        else:
            # choose one iso file to load
            return
        
    def _move_to_check_box_of_udisk(self, num, tabview):
        rowHeight = 30
        boxXOffset = 10
        boxYOffset = 10
        viewList = tabview.select_many('QHeaderView')
        VHArea = viewList[0].globalRect
        mx = VHArea.x + boxXOffset
        my = VHArea.y + VHArea.height + num*rowHeight +  boxYOffset
        self.mouse.move(mx, my)
        return
    
    def app_do_checkbox_udisk(self, idx):
        tabView = self.app.select_single('QTableView', objectName='tblDevices')
        self._move_to_check_box_of_udisk(idx, tabView)
        self.mouse.click()
        self.app_sleep(2)
        return

    def app_do_pushbutton_makeit(self):
        makeButton = self.app.select_single('QPushButton', objectName='btnStart')
        self.mouse.move_to_object(makeButton)
        self.app_sleep(2)
        self.mouse.click()
        return
    
    def app_handle_no_selected_device_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_NO_SELECTED_DEVICE)
        mbox_process = self.msgHandler.get_process_routine(MSG_NO_SELECTED_DEVICE)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_no_source_iso_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_NO_SOURCE_ISO)
        mbox_process = self.msgHandler.get_process_routine(MSG_NO_SOURCE_ISO)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_file_not_found_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_FILE_NOT_FOUND)
        mbox_process = self.msgHandler.get_process_routine(MSG_FILE_NOT_FOUND)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_umount_failed_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_UMOUNT_FAILED)
        mbox_process = self.msgHandler.get_process_routine(MSG_UMOUNT_FAILED)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_repartition_failed_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_REPARTITION_FAILED)
        mbox_process = self.msgHandler.get_process_routine(MSG_REPARTITION_FAILED)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_canceled_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_CANCELED)
        mbox_process = self.msgHandler.get_process_routine(MSG_CANCELED)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_completed_msg(self):
        mbox = self.msgHandler.get_msg_box(MSG_COMPLETED)
        mbox_process = self.msgHandler.get_process_routine(MSG_COMPLETED)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, None)
            return RET_SUCCESS
        
    def app_handle_confirm_build_msg(self, bSure):
        mbox = self.msgHandler.get_msg_box(MSG_CONFIRM_BUILD)
        mbox_process = self.msgHandler.get_process_routine(MSG_CONFIRM_BUILD)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, bSure)
            return RET_SUCCESS

    def app_handle_confirm_cancel_msg(self, bSure):
        mbox = self.msgHandler.get_msg_box(MSG_CONFIRM_CANCEL)
        mbox_process = self.msgHandler.get_process_routine(MSG_CONFIRM_CANCEL)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, bSure)
            return RET_SUCCESS

    def app_handle_confirm_exit_msg(self, bSure):
        mbox = self.msgHandler.get_msg_box(MSG_CONFIRM_EXIT)
        mbox_process = self.msgHandler.get_process_routine(MSG_CONFIRM_EXIT)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, bSure)
            return RET_SUCCESS
        
    def app_handle_confirm_exit2_msg(self, bSure):
        mbox = self.msgHandler.get_msg_box(MSG_CONFIRM_EXIT2)
        mbox_process = self.msgHandler.get_process_routine(MSG_CONFIRM_EXIT2)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, bSure)
            return RET_SUCCESS

    def app_handle_install_grub_msg(self, bSure):
        mbox = self.msgHandler.get_msg_box(MSG_INSTALL_GRUB)
        mbox_process = self.msgHandler.get_process_routine(MSG_INSTALL_GRUB)
        if(None == mbox or None == mbox_process):
            return RET_NONE
        else:
            mbox_process(mbox, bSure)
            return RET_SUCCESS
        
    def log_setup(self):
        self.logger = logging.getLogger(__name__)
        
    def log_info(self, head, msg):
        msg = "%s: %s" %(head, msg)
        self.logger.info(msg)
        return
        
    def log_warning(self, head, msg):
        self.logger.warning("%s: %s" %(head, msg))
        return

    def log_error(self, head, msg):
        self.logger.error("%s: %s" %(head, msg))
        return    
