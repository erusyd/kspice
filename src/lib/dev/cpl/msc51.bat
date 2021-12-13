cl /I..\..\..\include /c cpl.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cpldel.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cpldest.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cplload.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cplmdel.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cplmpar.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cplparam.c >> ..\..\..\msc.out
cl /I..\..\..\include /c cplsetup.c >> ..\..\..\msc.out
lib ..\..\dev3.lib @response.lib
