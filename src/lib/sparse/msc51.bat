del ..\sparse.lib
cl /I..\..\include /c spalloc.c >> ..\..\msc.out
cl /I..\..\include /c spbuild.c >> ..\..\msc.out
cl /I..\..\include /c spcompat.c >> ..\..\msc.out
cl /I..\..\include /c spfactor.c >> ..\..\msc.out
cl /I..\..\include /c spfort.c >> ..\..\msc.out
cl /I..\..\include /c spoutput.c >> ..\..\msc.out
cl /I..\..\include /c spsmp.c >> ..\..\msc.out
cl /I..\..\include /c spsolve.c >> ..\..\msc.out
cl /I..\..\include /c sputils.c >> ..\..\msc.out
lib ..\sparse.lib @response.lib
