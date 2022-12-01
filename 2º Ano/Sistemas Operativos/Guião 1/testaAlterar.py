#!/usr/bin/python

import sys
import os

try:
    os.system("./pessoas -u {} {}".format(str(sys.argv[1]), str(sys.argv[2])))
except KeyboardInterrupt:
    sys.exit(0)
except Exception as error:
    print("Failed: " + error)
