#!/bin/sh
#
# autogen.sh glue
#
# Requires: automake, autoconf
set -e

# Refresh GNU autotools toolchain.
echo "Refresh GNU autotools toolchain"
for i in config.guess config.sub missing install-sh mkinstalldirs ; do
	test -r /usr/share/automake/${i} && {
		rm -f ${i}
		cp /usr/share/automake/${i} .
	}
	chmod 755 ${i}
done

echo "Update aclocal"
aclocal -I m4

echo "Update autoheader"
autoheader

#echo "Update Automake"
#automake --verbose --foreign --add-missing

echo "Update autoconf"
autoconf

exit 0
