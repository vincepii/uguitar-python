uguitar-python
==============

python bindings for ultimate-guitar

Example
-------
```python
import uguitar.ug_simplesearch
    
tabs = uguitar.ug_simplesearch.search("metallica one")
for tab in tabs:
    print tab._uri
    print tab._rating
    print tab._ratingCounter
    print tab._type
```
Requirements
------------

 * python-pycurl
 * urlparse
 * python-beautifulsoup
