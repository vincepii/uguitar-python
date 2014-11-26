__author__ = 'vince'

import pycurl
import sys
import unittest

from uguitar.ug_request import UgRequest

class UrlTests(unittest.TestCase):

    def testTitleSearch(self):
        req = UgRequest()
        req.titleSearch("metallica one")
        print req.getUrl()
        assert(req.getUrl() == 'http://www.ultimate-guitar.com/search.php?search_type=title&value=metallica+one')

if __name__ == '__main__':
    unittest.main()