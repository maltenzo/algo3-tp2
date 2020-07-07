from bs4 import BeautifulSoup
import urllib.request

parser = 'html.parser'  # or 'lxml' (preferred) or 'html5lib', if installed
base_url = "http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/"
resp = urllib.request.urlopen(str(base_url+"index.html"))
soup = BeautifulSoup(resp, parser, from_encoding=resp.info().get_param('charset'))

for link in soup.find_all('a', href=True):
	dir = link['href']
	if((".tsp" in dir) or (".opt.tour" in dir)):
		if(dir!='.tsp\"'):
			print(dir)
			path = base_url + str(dir)
			dest = "./download_data/"+ str(dir)
			print(path)
			print(dest)
			urllib.request.urlretrieve(path, dest)