# -*- coding: utf-8 -*-

import ConfigParser
import os
from os.path import abspath, dirname, join


class TestConfig:
    """ test config 
    """
    def __init__(self):
        self.config = ConfigParser.ConfigParser()
        rpath = dirname(__file__) + '/test.ini'
        self.imgpath = abspath(dirname(__file__) + '/keepod-latest.zip')
        self.cfgFile = abspath(rpath)
        
        if(os.path.isfile(self.cfgFile)):
            self.config.read(self.cfgFile)
        else:
            self.create_sample()
            self.config.read(self.cfgFile)
        return

    def create_sample(self):
        """ create sample ini file """
        self.config.add_section('local')
        self.config.add_section('net')
        self.config.set('local', 'path', self.imgpath)
        self.config.set('net', 'url', 'http://ci.keepod.org/release/')
        self.config.set('net', 'name', 'keepod-latest.zip')
        self.config.set('net', 'md5', 'md5sum.txt')
        ff = open(self.cfgFile, 'w')
        self.config.write(ff)
        ff.flush()
        ff.close()
        return

    def get_img_net_url(self):
        return self.config.get('local', 'path')

    def get_img_name_url(self):
        return self.config.get('net','url')+self.config.get('net','name')

    def get_img_md5_url(self):
        return self.config.get('net','url')+self.config.get('net','md5')

    def get_img_local_file(self):
        return self.config.get('local','path')
