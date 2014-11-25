__author__ = 'vince'

import pycurl

from content_holder import ContentHolder

class Request(object):

    def __init__(self, url):
        super(Request, self).__init__()
        self._url = url
        self._contentHandler = ContentHolder()

    def send(self):
        c = pycurl.Curl()
        c.setopt(c.URL, self._url)
        c.setopt(c.WRITEFUNCTION, self._contentHandler.pushContent)
        c.perform()
        c.close()
        return self._contentHandler.getContent()