""" Generate test pads for padder. """

# usage: python gen.py > pads.txt

import random

pad   = ""
count = 0

# The pad chars MUST match the character set used by padder.
# See the 'characters' variable in 'main.hpp' for more
# information.
chars = "abcdefghijklmnopqrstuvwxyz0123456789-"

print "#", "Pad"
while count < 12:
    for x in xrange(0, 98):
        pad += random.choice(chars)

    count = count+1
    print count, pad
    pad = ""

