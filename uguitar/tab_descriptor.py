__author__ = 'vince'

class TabDescriptor(object):

    TAB_PRO_START='http://plus.'

    def __init__(self, artist, title, uri, rating, ratingCounter, type):
        super(TabDescriptor, self).__init__()
        self._artist = artist
        self._title = title
        self._uri = uri
        self._rating = rating
        self._ratingCounter = ratingCounter
        self._type = type
        self._isPlus = False
        if self._uri.startswith(TabDescriptor.TAB_PRO_START):
            self._isPlus = True