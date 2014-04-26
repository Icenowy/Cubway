#!/bin/bash
ls "$@" -AQlih --time-style=full-iso|awk 'NR==1 {print "{\x22totalsize\x22:\x22"$2"\x22,\x22""files""\x22:["} NR!=1 {print "{\x22inode\x22:\x22"$1"\x22,\x22pm\x22:\x22"$2"\x22"",\x22links\x22:\x22"$3"\x22,\x22owner\x22:\x22"$4"\x22,\x22grp\x22:\x22"$5"\x22,\x22size\x22:\x22"$6"\x22,\x22""date""\x22:\x22"$7"\x22,\x22time\x22:\x22"$8"\x22,\x22timezone\x22:\x22"$9"\x22,\x22name\x22:";for (i=10;i<=NF;i=i+1)printf $i;printf "\},"} END {printf "]}"}'|sed 's/\\"/\&quot\;/g;s/"->"/","linkto":"/g;s/</\&lt\;/g;s/>/\&gt\;/g;s/ /\&nbsp\;/g;s/,]}/]}/'|sed ':a;N;$!ba;s/\n//g'

#"totalsize" doesn't include folders.
