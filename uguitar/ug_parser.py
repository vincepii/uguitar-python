__author__ = 'vince'

from BeautifulSoup import BeautifulSoup

class UgParser(object):

    def __init__(self, htmlResponse):
        '''
        :param htmlResponse: the response to a search query
        '''
        super(UgParser, self).__init__()
        self._ugHtml = htmlResponse

    def extractTabs(self):
        parsedHtml = BeautifulSoup(self._ugHtml)
        print parsedHtml.body.find('table', attrs={'class':'tresults'})