/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985      Hong June Park, Thomas L. Quarles
**********/

#ifdef __STDC__
extern int BSIM1acLoad(GENmodel *,CKTcircuit*);
extern int BSIM1ask(CKTcircuit *,GENinstance*,int,IFvalue*,IFvalue*);
extern int BSIM1convTest(GENmodel *,CKTcircuit*);
extern int BSIM1delete(GENmodel*,IFuid,GENinstance**);
extern void BSIM1destroy(GENmodel**);
extern int BSIM1getic(GENmodel*,CKTcircuit*);
extern int BSIM1load(GENmodel*,CKTcircuit*);
extern int BSIM1mAsk(CKTcircuit*,GENmodel *,int, IFvalue*);
extern int BSIM1mDelete(GENmodel**,IFuid,GENmodel*);
extern int BSIM1mParam(int,IFvalue*,GENmodel*);
extern void BSIM1mosCap(CKTcircuit*, double, double, double, double,
        double, double, double, double, double, double, double,
        double, double, double, double, double, double, double*,
        double*, double*, double*, double*, double*, double*, double*,
        double*, double*, double*, double*, double*, double*, double*, 
        double*);
extern int BSIM1param(int,IFvalue*,GENinstance*,IFvalue*);
extern int BSIM1pzLoad(GENmodel*,CKTcircuit*,SPcomplex*);
extern int BSIM1setup(SMPmatrix*,GENmodel*,CKTcircuit*,int*);
extern int BSIM1temp(GENmodel*,CKTcircuit*);
extern int BSIM1trunc(GENmodel*,CKTcircuit*,double*);
extern int BSIM1disto(int,GENmodel*,CKTcircuit*);
#else /* stdc */
extern int BSIM1acLoad();
extern int BSIM1ask();
extern int BSIM1convTest();
extern int BSIM1delete();
extern void BSIM1destroy();
extern int BSIM1getic();
extern int BSIM1load();
extern int BSIM1mAsk();
extern int BSIM1mDelete();
extern int BSIM1mParam();
extern void BSIM1mosCap();
extern int BSIM1param();
extern int BSIM1pzLoad();
extern int BSIM1setup();
extern int BSIM1temp();
extern int BSIM1trunc();
extern int BSIM1disto();
#endif /* stdc */

