#!/bin/sh
#
# autogen.sh glue
#
# Requires: automake, autoconf
set -e

echo "Update aclocal"
aclocal -I m4

echo "Update autoheader"
autoheader

#echo "Update Automake"
#automake --verbose --foreign --add-missing

echo "Update autoconf"
autoconf

exit 0
