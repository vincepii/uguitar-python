__author__ = 'vince'

class TabDescriptor(object):

    def __init__(self, uri, rating, ratingCounter, type):
        super(TabDescriptor, self).__init__()
        self._uri = uri
        self._rating = rating
        self._ratingCounter = ratingCounter
        self._type = type
        self._isPlus = False
        if self._uri.startswith('http://plus.'):
            self._isPlus = True