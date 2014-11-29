__author__ = 'vince'

from BeautifulSoup import BeautifulSoup
import re

from tab_descriptor import TabDescriptor

class UgParser(object):

    def __init__(self, htmlResponse):
        '''
        :param htmlResponse: the response to a search query
        '''
        super(UgParser, self).__init__()
        self._ugHtml = htmlResponse
        # List of tabs as TabDescriptors
        self._tabs = []

    def parseTabs(self):
        '''
        Parses the HTML returned from ug and extracts tab information.
        Appends into the list of TabDescriptors.
        '''
        parsedHtml = BeautifulSoup(self._ugHtml)
        tabsHtmlTable = parsedHtml.find('table', attrs={'class':'tresults'})
        tabsHtmlRows = tabsHtmlTable.findAll('tr')
        for row in tabsHtmlRows:
            tabdesc = self._parseTabHtmlRow(row)
            if tabdesc is None:
                continue
            self._tabs.append(tabdesc)

    def getTabs(self):
        '''
        Returns a list of TabDescriptor objects
        '''
        return self._tabs

    def _parseTabHtmlRow(self, row):
        '''
        Given an Html row describing a tab in ug, returns a tab descriptor
        '''
        # Link to the tab is <a> of class 'song'
        # Rating is in the <span> of class 'rating' (may be not available)
        # Counter is the content of <b class="ratdig">19</b>
        # Tab type is like <td><strong>chords</strong></td>
        tabUri = self._getTabUriFromHtmlRow(row)
        if tabUri is None:
            # not all rows are tabs (e.g., header row)
            return None
        tabRating = self._getTabRatingFromHtmlRow(row)
        tabRatingCounter = self._getTabRatingCounterFromHtmlRow(row)
        tabType = self._getTabTypeFromHtmlRow(row)
        desc = TabDescriptor(tabUri, tabRating, tabRatingCounter, tabType)
        return desc

    def _getTabUriFromHtmlRow(self, row):
        linkToTab = row.find('a', attrs={'class':'song'})
        if linkToTab is None:
            # not all rows are song
            return None
        return linkToTab.get('href')

    def _getTabRatingFromHtmlRow(self, row):
        ratingSpan = row.find('span', attrs={'class':'rating'})
        if ratingSpan is None:
            return None
        return re.search('class=\"r_([0-9])\"', str(ratingSpan)).group(1)

    def _getTabRatingCounterFromHtmlRow(self, row):
        counterElement = row.find('b', attrs={'class':'ratdig'})
        if counterElement is None:
            return None
        return counterElement.contents

    def _getTabTypeFromHtmlRow(self, row):
        return re.search('<td><strong>(.*)</strong></td>', str(row)).group(1)