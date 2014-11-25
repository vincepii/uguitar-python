__author__ = 'vince'

class ContentHolder(object):

    def __init__(self):
        super(ContentHolder, self).__init__()
        self._content = ''

    def pushContent(self, buffer):
        self._content = self._content + buffer

    def getContent(self):
        return self._content