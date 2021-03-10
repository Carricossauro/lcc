#!/usr/bin/python

import sys
import os

try:
    for i in range(1,int(sys.argv[1])+1):
        os.system("./pessoas -i Pessoa{} {}".format(str(i), str(i)))
except KeyboardInterrupt:
    sys.exit(0)
except Exception as error:
    print("Failed: " + error)