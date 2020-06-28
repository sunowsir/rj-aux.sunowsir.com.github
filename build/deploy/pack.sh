#!/bin/bash
#
#	* File     : pack.sh
#	* Author   : sunowsir
#	* Mail     : sunowsir@163.com
#	* Github   : github.com/sunowsir
#	* Creation : Thu 25 Jun 2020 06:10:16 PM CST



exe="rj-aux" #你需要发布的程序名称
des="$(pwd)" #创建文件夹的位置
deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')  
cp $deplist $des
