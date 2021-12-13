cl /I..\..\..\include /c txl.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txldel.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txldest.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txlload.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txlmdel.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txlmpar.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txlparam.c >> ..\..\..\msc.out
cl /I..\..\..\include /c txlsetup.c >> ..\..\..\msc.out
lib ..\..\dev3.lib @response.lib
