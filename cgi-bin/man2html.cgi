#!/bin/sh
# $Id$

PATH="/usr/local/bin:$PATH"

f=../pkg/doc/"$1.$2"
if [ -r $f ]; then
	echo "Content-Type: text/html"
	echo ""
	nroff -man $f | rman -f html -r 'http://www.CS.Princeton.EDU/cgi-bin/man2html?%s:%s' 2>/dev/null
else
	echo "Content-Type: text/html"
	echo ""
	cat <<END
<HTML><HEAD><TITLE>Manual Page</TITLE></HEAD><BODY>
<H2>No man page for "$1"</H2></BODY></HTML>
END
	exit 1
fi



