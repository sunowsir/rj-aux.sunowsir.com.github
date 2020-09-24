#!/bin/bash
#
#	* File     : rj-aux.sh
#	* Author   : sunowsir
#	* Mail     : sunowsir@163.com
#	* Github   : github.com/sunowsir
#	* Creation : Sun 28 Jun 2020 10:10:06 PM CST

appname="$(basename "$0" | sed s,\.sh,,)"  
dirname="$(dirname "$0")"  
tmp="${dirname#?}"  

if [ "${dirname%$tmp}" != "/" ]; then  
	dirname="$PWD"/"$dirname"  
fi  

LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:$dirname"  
export LD_LIBRARY_PATH  

echo "$dirname"/"$appname"

"$dirname"/"$appname" "$@"
