/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Min-Chie Jeng, Hong June Park, Thomas L. Quarles
**********/

#ifdef __STDC__
extern int BSIM2acLoad(GENmodel *,CKTcircuit*);
extern int BSIM2ask(CKTcircuit *,GENinstance*,int,IFvalue*,IFvalue*);
extern int BSIM2convTest(GENmodel *,CKTcircuit*);
extern int BSIM2delete(GENmodel*,IFuid,GENinstance**);
extern void BSIM2destroy(GENmodel**);
extern int BSIM2getic(GENmodel*,CKTcircuit*);
extern int BSIM2load(GENmodel*,CKTcircuit*);
extern int BSIM2mAsk(CKTcircuit*,GENmodel *,int, IFvalue*);
extern int BSIM2mDelete(GENmodel**,IFuid,GENmodel*);
extern int BSIM2mParam(int,IFvalue*,GENmodel*);
extern void BSIM2mosCap(CKTcircuit*, double, double, double, double,
        double, double, double, double, double, double, double,
        double, double, double, double, double, double, double*,
        double*, double*, double*, double*, double*, double*, double*,
        double*, double*, double*, double*, double*, double*, double*, 
        double*);
extern int BSIM2param(int,IFvalue*,GENinstance*,IFvalue*);
extern int BSIM2pzLoad(GENmodel*,CKTcircuit*,SPcomplex*);
extern int BSIM2setup(SMPmatrix*,GENmodel*,CKTcircuit*,int*);
extern int BSIM2temp(GENmodel*,CKTcircuit*);
extern int BSIM2trunc(GENmodel*,CKTcircuit*,double*);
#else /* stdc */
extern int BSIM2acLoad();
extern int BSIM2delete();
extern void BSIM2destroy();
extern int BSIM2getic();
extern int BSIM2load();
extern int BSIM2mDelete();
extern int BSIM2ask();
extern int BSIM2mAsk();
extern int BSIM2convTest();
extern int BSIM2temp();
extern int BSIM2mParam();
extern void BSIM2mosCap();
extern int BSIM2param();
extern int BSIM2pzLoad();
extern int BSIM2setup();
extern int BSIM2trunc();

#endif /* stdc */
