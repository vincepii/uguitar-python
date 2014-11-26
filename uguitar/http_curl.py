__author__ = 'vince'

import pycurl

from content_holder import ContentHolder

class HttpCurl(object):
    '''
    Class to send curl requests and get output
    '''

    def __init__(self, url):
        '''

        :param url: a simple string
        '''
        super(HttpCurl, self).__init__()
        self._url = url
        self._contentHandler = ContentHolder()

    def send(self):
        '''
        Sends the request and returns the content of the response
        '''
        c = pycurl.Curl()
        c.setopt(c.URL, self._url)
        c.setopt(c.WRITEFUNCTION, self._contentHandler.pushContent)
        c.perform()
        c.close()
        return self._contentHandler.getContent()