# -*- coding: utf-8 -*-

from autopilot.testcase import AutopilotTestCase
from os.path import abspath, dirname, join

import hashlib
import logging 

from inner import *
from config import *

class MD5CheckItem:
    """ item for md5 check """
    def __init__(self, path, value):
        self.value, self.path = value, path
        return

class Udisk(AutopilotTestCase):
    """ udisk test for installer which launches keepod-installer """
    config = TestConfig()
    md5_items = []
    
    def test_single_udisk_md5_check(self):
        """ test routine:
            md5 check for single udisk which is
            the first valid udisk we found from system
        """
        self.log_setup()
        # prepare tests
        self._prepare_test()
        # get valid udisks
        udisks = self._search_valid_udisks()

        # md5 check for the first valid udisk
        self._md5_udisk_check(udisks[0]) 
        return

    def test_multi_udisks_md5_check(self):
        """ test routine:
            md5 check for single udisk which is
            the multi valid udisks we found from system
        """
        self.log_setup()
        # prepare tests
        self._prepare_test()
        # get valid udisks
        udisks = self._search_valid_udisks()

        # udisk check for all udisks
        for udisk in udisks:
            self._md5_udisk_check(udisk)
        return

    def _search_valid_udisks(self):
        udisks = []
        # get mounts info
        fmounts = open('/proc/mounts')
        fmounts.seek(0,0)
        flines = fmounts.readlines()
        fmounts.close()

        # get valid udisks' mount paths
        for line in flines: 
            if 'KEEPOD' in line:
                spices = line.split()
                for spice in spices:
                    if 'KEEPOD' in spice:
                        udisks.append(spice)
                        
        # if no udisks found, report error msg           
        if(0 == len(udisks)):
            self.log_error('', 'Not find any valid udisks!!')
            self.assertTrue(False)
            
        return udisks

    def _prepare_test(self):
        """ prepare md5 test """
        
        # get md5sum file
        md5_file = open(self.config.get_img_local_md5())
        md5_file.seek(0,0)
        md5_maps = md5_file.readlines()
        md5_file.close()

        # parse md5sum file and get the targets we need
        for md5_map in md5_maps:
            value, path = md5_map.split()
            offset = path.find('android')
            if(-1 != offset):
                self.md5_items.append(MD5CheckItem(path[offset:], value))
        return
                

    def _md5_file_check(self, file_path, value):
        """ md5 check for single file according to its value and path """
        ff = file(file_path, 'rb')
        ff.seek(0,0)
        mh = hashlib.md5()
        mh.update(ff.read())
        ff.close()
        md5_value = mh.hexdigest()
        if(value == md5_value or value == md5_value.upper()):
            msg = file_path + ' md5 check success.'
            self.log_info('', msg)
            return
        else:
            msg = file_path + ' md5 value should be ' + item.value + ', but we got ' + md5_value
            self.log_error('', msg)
            self.assertTrue(False)
            return
        
        

    def _md5_udisk_check(self, udisk_path):
        """ md5 check for udisk, return according to checking of the specified files """
        for item in self.md5_items:
            item_path = udisk_path + '/' + item.path
            self._md5_file_check(item_path, item.value)
        return
    
    def log_setup(self):
        self.logger = logging.getLogger(__name__)
        return
        
    def log_info(self, head, msg):
        msg = "%s: %s" %(head, msg)
        print '\n##### INFO: ', msg, '\n'
        self.logger.info(msg)
        return
        
    def log_warning(self, head, msg):
        msg = "%s: %s" %(head, msg)
        print '\n##### WARNING: ', msg, '\n'
        self.logger.warning(msg)
        return

    def log_error(self, head, msg):
        msg = "%s: %s" %(head, msg)
        print '\n##### ERROR: ', msg, '\n'
        self.logger.error(msg)
        return   
