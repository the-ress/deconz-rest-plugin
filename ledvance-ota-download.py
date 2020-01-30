#!/usr/bin/env python
"""
Snipped to download current IKEA ZLL OTA files into ~/otau
compatible with python 3.
"""

import os
import json
import time
try:
	from urllib.request import urlopen, urlretrieve
except ImportError:
	from urllib2 import urlopen
	from urllib import urlretrieve


f = urlopen("https://api.update.ledvance.com/v1/zigbee/products")
data = f.read()

products = json.loads(data)

otapath = '%s/otau' % os.path.expanduser('~')

if not os.path.exists(otapath):
	os.makedirs(otapath)

for product in products['products']:
	id = product['id']
	url = 'https://api.update.ledvance.com/v1/zigbee/firmwares/download/%s/%s/latest'
	url = url % (id['company'], id['product'])

	fname = 'ledvance-%s-%s.ota' % (id['company'], id['product'])
	path = '%s/%s' % (otapath, fname)

	if not os.path.isfile(path):
		urlretrieve(url, path)
		print(path)
		time.sleep(3) # API is limited to 30 calls per minute
	else:
	    print('%s already exists' % fname)
