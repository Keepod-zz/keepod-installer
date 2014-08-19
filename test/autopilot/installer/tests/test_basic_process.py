# -*- coding: utf-8 -*-

from autopilot.testcase import AutopilotTestCase
from autopilot.matchers import Eventually
from testtools.matchers import Equals

from os.path import abspath, dirname, join
import time
import logging

from test_installer import installerTestBase
from test_config import *
from inner import *

class BasicProcessTests(installerTestBase):
    """ basic process for installer """

    def _test_single_udisk_installing_with_net_img(self):
        """ test routine:
                single udisk installing process with image from network
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
        self.app_do_checkbox_download()
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        
        # process msg box poped up after clicking "make it"   
        exitFlag = self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        
        # wait to complete installing   
        ret = self.app_do_statewin_wait_completed(-1)
        self.assertTrue(ret)

        # our completed info button will kill application
        # this will cause autipilot identify this as a failed test
        self.app_handle_completed_msg()
        return
    
    def test_single_udisk_installing_with_local_img(self):
        """ test routine:
                single udisk installing process with image from local path
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
        self.app_do_load_local_img()
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)
        
         # press "make it" button
        self.app_do_pushbutton_makeit()
        
        # process msg box poped up after clicking "make it"   
        exitFlag = self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()

        # wait to complete installing
        ret = self.app_do_statewin_wait_completed(-1)
        self.assertTrue(ret)

        # our completed info button will kill application
        # this will cause autipilot identify this as a failed test
        self.app_handle_completed_msg()
        return
    
    def test_multi_udisk_installing_with_local_img(self):
        """ test routine:
                multi udisk installing process with iamge from local path
        """
        self.log_setup()
        # launch application
        self.app_setup()
        
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        exitFlag = self.app_handle_no_usb_disks_msg()
        if(RET_SUCCESS == exitFlag):
            return

        self.app_do_checkbox_udisk(0)
        self.app_do_checkbox_udisk(1)
        
        # go to main win position
        self.app_do_move_mouse_2_mainwin()
        self.app_do_load_local_img()
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)
        self.app_do_checkbox_udisk(1)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        
        # process msg box poped up after clicking "make it"   
        exitFlag = self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        
        # wait to complete installing
        ret = self.app_do_statewin_wait_completed(-1)
        self.assertTrue(ret)

        # our completed info button will kill application
        # this will cause autipilot identify this as a failed test
        self.app_handle_completed_msg()
        return

    def test_single_udisk_downloading_cancel_and_continue_with_net_image(self):
        """ test routine:
                after preparation, we begin downloading image from network ,
                then we cancel downloading operation and then continue this process
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
        self.app_do_checkbox_download()
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button and start downloading
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        
        # then we wait for 4.0 percent
        ret = self.app_do_statewin_wait_download(4.0)
        self.assertTrue(ret)

        # cancel the downloading process
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_cancel_msg(True)

        # handle canceled message
        self.app_handle_canceled_msg()
        self.app_do_move_mouse_2_mainwin()

        # continue process and remake it
        self.app_do_pushbutton_makeit()
        # handle confirm message
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        self.app_sleep(2)
        return

    def test_single_udisk_writting_cancel_and_continue_with_local_img(self):
        """ test routine:
            after preparation, we begin writting to udisk ,
            then we cancel the writting operation and then continue this process
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
        self.app_do_move_mouse_2_mainwin()
        self.app_do_load_local_img()
        
        # choose usb stick, such as /dev/sdb.
        self.app_do_checkbox_udisk(0)

        # press "make it" button
        self.app_do_pushbutton_makeit()
        # handle confirm message and begin writting
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        
        # then we wait writting for 5.0 percent
        ret = self.app_do_statewin_wait_writting(6)
        self.assertTrue(ret)
        
        # cancel the writting process
        self.app_do_pushbutton_makeit()
        # handle cancel confirmed message
        self.app_handle_confirm_cancel_msg(True)

        # wait canceld pop-box
        self.app_wait_msg_pop(MSG_CANCELED)
        
        # handle canceled message
        self.app_handle_canceled_msg()
        self.app_do_move_mouse_2_mainwin()
        
        # restart writting process
        self.app_do_pushbutton_makeit()
        self.app_handle_confirm_build_msg(True)
        self.app_do_move_mouse_2_mainwin()
        return

    def test_single_udisk_md5_check(self):
        """ test routine:
                md5 check for udisk files
        """
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
    
    def app_do_checkbox_download(self):
        """ check download box """
        # choose to download from internet over http or ftp
        checkBox = self.app.select_single('QCheckBox', objectName='chkDownloadLatest')
        mx, my = (checkBox.globalRect.x + 5), (checkBox.globalRect.y + 5)
        self.mouse.move(mx, my)
        self.mouse.click()
        self.app_sleep(2)
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

    def _statewin_check_error(self, text):
        """ check error state of state window """
        if(text in self.msgHandler.get_err_states()):
            return True
        else:
            return False

    def app_do_statewin_wait_download(self, percent):
        if(percent > 100.0):
            percent = 100.0
        
        msgLen = len(MSG_DOWNLOADING)
        stateWin = self.app.select_single('QLabel', objectName='lblStatus')
        while(1):
            curr = stateWin.text
            self.log_info('StateWin', curr)
            # in order to prevent failed message from hanging test
            if(self._statewin_check_error(curr)):
                return False
            
            percentCurStr = curr[msgLen:-1]
            if('.' in percentCurStr):
                percentCur = float(percentCurStr)
                if(percentCur >= percent):
                    return True
            time.sleep(2)
        return True

    def app_do_statewin_wait_writting(self, timeout):
        timeout_count = 0
        stateWin = self.app.select_single('QLabel', objectName='lblStatus')
        while(1):
            curr = stateWin.text
            self.log_info('StateWin', curr)
            if(self._statewin_check_error(curr)):
                    return False
                
            if(MSG_WRITING == curr):
                timeout_count = timeout_count + 1

            if(timeout_count > timeout):
                break
        return True
    
    def app_do_statewin_wait_completed(self, timeout):
        timeout_count = 0
        stateWin = self.app.select_single('QLabel', objectName='lblStatus')
       
        while(1):
            curr = stateWin.text
            if(MSG_COMPLETED == curr):
                self.log_info('StateWin', curr)
                break
            else:
                if(-1 != timeout and timeout_count > timeout):
                    break

                # in order to prevent failed message from hanging test
                if(self._statewin_check_error(curr)):
                    return False
                
                self.log_info('StateWin', curr)
                timeout_count = timeout_count + 1
                time.sleep(1)
        return True

    def app_wait_msg_pop(self, msg):
        """ wait for specified msgbox to pop up """
        while(1):
            mbox = self.msgHandler.get_msg_box(msg)
            if(mbox != None):
                break
            time.sleep(1)
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
        return
        
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
