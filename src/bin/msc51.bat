cl /I..\include\ /c bconf.c >> ..\msc.out
cl /I..\include\ /c cconf.c >> ..\msc.out
cl /I..\include\ /c nnconf.c >> ..\msc.out
cl /I..\include\ /c tunepc.c >> ..\msc.out
del cspice.obj
cl /I..\include\ /c /DSIMULATOR /DSPICE2 /DBATCH main.c >> ..\msc.out
rename main.obj cspice.obj
link @cspice.lnk
del bspice.obj
cl /I..\include\ /c /DSIMULATOR /DBATCH main.c >> ..\msc.out
rename main.obj bspice.obj
link @bspice.lnk
del nutmeg.obj
cl /I..\include\ /c main.c >> ..\msc.out
rename main.obj nutmeg.obj
link @nutmeg.lnk
cl /I..\include\ /c sconvert.c >> ..\msc.out
link @sconvert.lnk
cl /I..\include\ /c proc2mod.c >> ..\msc.out
link @proc2mod.lnk
cl /I..\include\ /c help.c >> ..\msc.out
link @help.lnk
cl /I..\include\ /c makeidx.c >> ..\msc.out
link @makeidx.lnk
cl /I..\include\ /c multidec.c >> ..\msc.out
link @multidec.lnk
