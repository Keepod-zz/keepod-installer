# -*- coding: utf-8 -*-

from autopilot.testcase import AutopilotTestCase
from os.path import abspath, dirname, join

class installerTestBase(AutopilotTestCase):
    """ base test for installer which launches keepod-installer """
    
    def launch_installer(self):
        """ launch installer
        """
        relative_path = dirname(__file__)+"/../../../../bin/keepod-installer"
        installer = abspath(relative_path)
        return self.launch_test_application(installer, app_type='qt')
        
    
