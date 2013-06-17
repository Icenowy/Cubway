--Settings

--metro.system("lxterminal")
--metro.load("http://127.0.0.1/Subway/MT.php?distro_pic=debian.png");
runtab={}
runtab["webb"]="chromium"
runtab["term"]="lxterminal"
function luarun(str)
	print(str)
	metro.system(runtab[str])
end
