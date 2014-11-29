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
        parser.parseTabs()
        # The first page of this request should return 53 results.
        # If they clean up tabs and remove some, this will fail!
        assert(len(parser.getTabs()) is 53)

if __name__ == '__main__':
    unittest.main()