__author__ = 'vince'

from ug_request import UgRequest
from http_curl import HttpCurl
from ug_parser import UgParser

def search(arg):
    req = UgRequest()
    req.titleSearch(arg)
    url = req.getUrl()
    curl = HttpCurl(url)
    response = curl.send()
    parser = UgParser(response)
    parser.parseTabs()
    return parser.getTabs()