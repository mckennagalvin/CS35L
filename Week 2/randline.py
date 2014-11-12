#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filenames):
        self.lines = []
        for i in range(len(filenames)):
            f = open(filenames[i], 'r')
            self.lines += f.readlines()
            f.close()
            if len(self.lines) > 0:
                lastline = self.lines[len(self.lines)-1]
                lastchar = lastline[len(lastline)-1]
                if lastchar != '\n':
                    self.lines[len(self.lines)-1] += '\n'

    def chooseline(self, w):
        choice = random.choice(self.lines)
        if w:
            self.lines.remove(choice)
        return choice

    def unique(self):
        self.lines = list(set(self.lines))

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1,
                      help="output NUMLINES lines (default 1)")
    parser.add_option("-u", "--unique",
                      action="store_true", dest="unique", default=False,
                      help="only look at unique lines (default false)")
    parser.add_option("-w", "--without-replacement",
                      action="store_true", dest="without", default=False,
                      help="output lines without replacement (default false)")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) < 1:
        parser.error("wrong number of operands")

    try:
        generator = randline(args)
    except IOError as xxx_todo_changeme:
        (errno, strerror) = xxx_todo_changeme.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

    if options.unique:
        generator.unique()

    if options.unique or options.without:
        if len(generator.lines) < numlines:
            parser.error("not enough lines")

    try:
        for index in range(numlines):
            sys.stdout.write(generator.chooseline(options.without))
    except IOError as xxx_todo_changeme2:
        (errno, strerror) = xxx_todo_changeme2.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
        
if __name__ == "__main__":
    main()
