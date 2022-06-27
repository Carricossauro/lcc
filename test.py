import re

exp = '[ ]*(?i:pepino)[ ]*' 

print (bool(re.search(exp+'$','pepinos'.strip())))