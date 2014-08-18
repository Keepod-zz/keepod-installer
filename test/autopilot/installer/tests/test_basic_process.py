from autopilot.testcase import AutopilotTestCase
from os.path import abspath, dirname, join

import time
import logging

from test_installer import installerTestBase
from inner import *

class MsgProcess():
    def __init__(self, app, test):
        self.app = app
        self.test = test
        self.map_mbox = {
            MSG_NO_USB_DISKS:self.msg_no_usb_disks,
            MSG_NO_SELECTED_DEVICE:self.msg_no_selected_device,
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

    def process_msgbox(self, params):
        # check if we have messagebox
        mlist = self.app.select_many('QMessageBox')
        if(0 != len(mlist)):
            mbox = self.app.select_single('QMessageBox')
            process = self.map_mbox[mbox.text]
            return process(mbox, params)
        else:
            return RUN_AFTER_MSG_PROCESS
    
    def msg_single_ok(self, mbox, params):
        self.test.mouse.move_to_object(mbox)
        time.sleep(1)
        okButton = mbox.select_single('QPushButton', text=u'OK')
        self.test.mouse.move_to_object(okButton)
        self.test.mouse.click()
        return EXIT_AFTER_MSG_PROCESS
    
    def msg_double_yes_no(self, mbox, bSure):
        self.test.mouse.move_to_object(mbox)
        time.sleep(1)
        if(bSure):
            button = mbox.select_single('QPushButton', text=u'&Yes')
            self.test.mouse.move_to_object(button)
            self.test.mouse.click()
        else:
            button = mbox.select_single('QPushButton', text=u'&No')
            self.test.mouse.move_to_object(button)
            self.test.mouse.click()
            
        return EXIT_AFTER_MSG_PROCESS
    
    def msg_no_usb_disks(self, mbox, params):
        self.msg_single_ok(mbox, params)
        return EXIT_AFTER_MSG_PROCESS
    
    def msg_no_selected_device(self, mbox, params):
        self.msg_single_ok(mbox, params)
        return EXIT_AFTER_MSG_PROCESS
    

    def msg_confirm_build(self, mbox, params):
        self.msg_double_yes_no(mbox, params)
        return EXIT_AFTER_MSG_PROCESS
    

class BasicProcessTests(installerTestBase):
    """ basic process for installer """

    def _move_to_check_box_of_device(self, num, tabview):
        rowHeight = 30
        boxXOffset = 10
        boxYOffset = 10
        viewList = tabview.select_many('QHeaderView')
        VHArea = viewList[0].globalRect
        mx = VHArea.x + boxXOffset
        my = VHArea.y + VHArea.height + num*rowHeight +  boxYOffset
        self.mouse.move(mx, my)


    def test_basic_process(self):
        self.log_setup()
        # launch application
        app_root = self.launch_installer()
        msgHandler = MsgProcess(app_root, self)
        # what if we don't have usb stick mounted
        # check if we have msgbox and push it
        if(EXIT_AFTER_MSG_PROCESS == msgHandler.process_msgbox(None)):
            return
        
        ########################################
        # get main win position
        mainWin = app_root.select_single('CUIMain')
        self.mouse.move_to_object(mainWin)
        time.sleep(2)
        
        ########################################
        # check "download and install..." box
        checkBox = app_root.select_single('QCheckBox', objectName='chkDownloadLatest')
        mx, my = (checkBox.globalRect.x + 5), (checkBox.globalRect.y + 5)
        self.mouse.move(mx, my)
        self.mouse.click()
        time.sleep(2)
        
        # choose usb stick, such as /dev/sdb.
        tabView = app_root.select_single('QTableView', objectName='tblDevices')
        self._move_to_check_box_of_device(0, tabView)
        print tabView.get_children()
        self.mouse.click()
        time.sleep(2)

        ########################################
        # press "make it" button
        makeButton = app_root.select_single('QPushButton', objectName='btnStart')
        self.mouse.move_to_object(makeButton)
        self.mouse.click()
        # process msg box poped up after clicking "make it"
        if(EXIT_AFTER_MSG_PROCESS == msgHandler.process_msgbox(True)):
            return
        
        ########################################
        # after making finished and showing popup dialog,
        # press "OK" button and exit installer
        
        # TODO: wait_signal and then move mouse to new popbox

        # process msgbox of "Completed" or some else
        if(EXIT_AFTER_MSG_PROCESS == msgHandler.process_msgbox(True)):
            return
        
        return

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
