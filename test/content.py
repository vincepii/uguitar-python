__author__ = 'vince'

import unittest

from uguitar.http_curl import HttpCurl
from uguitar.ug_request import UgRequest
from uguitar.ug_parser import UgParser
import uguitar.ug_simplesearch

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

    def testSimpleSearch(self):
        tabs = uguitar.ug_simplesearch.search("metallica one")
        for tab in tabs:
            print tab._uri
            print tab._artist
            print tab._title
            print tab._rating
            print tab._ratingCounter
            print tab._type, '\n'


if __name__ == '__main__':
    unittest.main()