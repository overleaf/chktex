#!/bin/sh
#
# autogen.sh glue
#
# Requires: automake, autoconf
set -e

echo "Update aclocal"
aclocal -I m4

echo "Update autoheader"
autoheader2.50

echo "Update automake"
set +e
automake --foreign --add-missing 2>/dev/null
set -e

echo "Update autoconf"
autoconf2.50

echo timestamp > stamp-h.in
exit 0
