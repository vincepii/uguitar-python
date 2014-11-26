__author__ = 'vince'

import unittest

from uguitar.http_curl import HttpCurl
from uguitar.ug_request import UgRequest
from uguitar.ug_parser import UgParser

class ContentTest(unittest.TestCase):

    def testGetTitleSearchResults(self):
        req = UgRequest()
        req.titleSearch("metallica one")
        url = req.getUrl()
        curl = HttpCurl(url)
        response = curl.send()
        parser = UgParser(response)
        parser.extractTabs()

if __name__ == '__main__':
    unittest.main()