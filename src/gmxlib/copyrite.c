/*
 *       @(#) copyrgt.c 1.12 9/30/97
 *
 *       This source code is part of
 *
 *        G   R   O   M   A   C   S
 *
 * GROningen MAchine for Chemical Simulations
 *
 *            VERSION 2.0b
 * 
 * Copyright (c) 1990-1997,
 * BIOSON Research Institute, Dept. of Biophysical Chemistry,
 * University of Groningen, The Netherlands
 *
 * Please refer to:
 * GROMACS: A message-passing parallel molecular dynamics implementation
 * H.J.C. Berendsen, D. van der Spoel and R. van Drunen
 * Comp. Phys. Comm. 91, 43-56 (1995)
 *
 * Also check out our WWW page:
 * http://rugmd0.chem.rug.nl/~gmx
 * or e-mail to:
 * gromacs@chem.rug.nl
 *
 * And Hey:
 * Great Red Oystrich Makes All Chemists Sane
 */

#include <string.h>
#include <ctype.h>
#include "sysstuff.h"
#include "smalloc.h"
#include "string2.h"
#include "macros.h"
#include "time.h"
#include "random.h"
#include "copyrite.h"
#include "strdb.h"
#include "futil.h"

static void pr_two(FILE *out,int c,int i)
{
  if (i < 10)
    fprintf(out,"%c0%1d",c,i);
  else
    fprintf(out,"%c%2d",c,i);
}

void pr_difftime(FILE *out,double dt)
{
  int    ndays,nhours,nmins,nsecs;
  bool   bPrint,bPrinted;

  ndays = dt/(24*3600);
  dt    = dt-24*3600*ndays;
  nhours= dt/3600;
  dt    = dt-3600*nhours;
  nmins = dt/60;
  dt    = dt-nmins*60;
  nsecs = dt;
  bPrint= (ndays > 0);
  bPrinted=bPrint;
  if (bPrint) 
    fprintf(out,"%d",ndays);
  bPrint=bPrint || (nhours > 0);
  if (bPrint) {
    if (bPrinted)
      pr_two(out,'d',nhours);
    else 
      fprintf(out,"%d",nhours);
  }
  bPrinted=bPrinted || bPrint;
  bPrint=bPrint || (nmins > 0);
  if (bPrint) {
    if (bPrinted)
      pr_two(out,'h',nmins);
    else 
      fprintf(out,"%d",nmins);
  }
  bPrinted=bPrinted || bPrint;
  if (bPrinted)
    pr_two(out,':',nsecs);
  else
    fprintf(out,"%ds",nsecs);
  fprintf(out,"\n");
}

bool be_cool(void)
{
  static int cool=-1;
  
  if (cool == -1) {
    if ((getenv("IAMCOOL")) == NULL) 
      cool=0;
    else
      cool=1;
  }
  return cool;
}

void space(FILE *out, int n)
{
  fprintf(out,"%*s",n,"");
}

void f(char *a){int i;for(i=0;i<(int)strlen(a);i++)a[i]=~a[i]; }

static void sp_print(FILE *out,char *s)
{
  int slen;
  
  slen=strlen(s);
  space(out,(80-slen)/2);
  fprintf(out,"%s\n",s);
}

static void ster_print(FILE *out,char *s)
{
  int  slen;
  char buf[128];
  
  sprintf(buf,":-)  %s  (-:",s);
  slen=strlen(buf);
  space(out,(80-slen)/2);
  fprintf(out,"%s\n",buf);
}

/* char *GromacsVersion() */
/* { */
/*   return ver; */
/* } */

static int nran=0;

static char *pukeit(char *db,char *defstring)
{
  static char hulp[STRLEN];
  FILE *fp;
  char **help,*c;
  int  i,nhlp;
  int  seed;
  
  if (!be_cool())
    return defstring;
  else if ((fp = low_libopen(db,FALSE)) != NULL) {
    nhlp=fget_lines(fp,&help);
    fclose(fp);
    seed=time(NULL);
    nran=nhlp*rando(&seed);
    if (strlen(help[nran]) >= STRLEN)
      help[nran][STRLEN-1] = '\0';
    strcpy(hulp,help[nran]);
    f(hulp);
    for(i=0; (i<nhlp); i++)
      sfree(help[i]);
    sfree(help);
  
    return hulp;
  }
  else
    return defstring;
}

char *bromacs(void)
{
  return pukeit("bromacs.dat",
                "Groningen Machine for Chemical Simulation");
}

char *cool_quote(void)
{
  static char buf[1024];
  char *s,*ptr;
  
  /* protect audience from explicit lyrics */
  s = pukeit("gurgle.dat","Thanx for Using GROMACS - Have a Nice Day");

  if (be_cool() && ((ptr=strchr(s,'_')) != NULL)) {
    *ptr='\0';
    ptr++;
    sprintf(buf,"\"%s\" %s",s,ptr);
  }
  else {
    strcpy(buf,s);
  }
    
  return buf;
}

void CopyRight(FILE *out,char *szProgram)
{
#define NCR asize(CopyrightText)
  char buf[256];
  char *ptr;
  
  int i;
  
  ster_print(out,"G  R  O  M  A  C  S");
  fprintf(out,"\n");

  ptr=bromacs();
  sp_print(out,ptr); 
  fprintf(out,"\n");
  
  ster_print(out,GromacsVersion());
  fprintf(out,"\n");

  for(i=0; (i<NCR); i++) 
    sp_print(out,CopyrightText[i]);

  sprintf(buf,"%s",szProgram);
#ifdef DOUBLE
  strcat(buf," (double precision)");
#endif
  ster_print(out,buf);
  fprintf(out,"\n");
}

void thanx(FILE *fp)
{
  char *cq,*c;

  /* protect the audience from suggestive discussions */
  cq=cool_quote();
  
  if (be_cool()) {
    snew(c,strlen(cq)+20);
    sprintf(c,"gcq#%d: %s\n",nran,cq);
    fprintf(fp,"\n%s\n",c);
    sfree(c);
  }
  else
    fprintf(fp,"\n%s\n",cq);
}

char *wrap_lines(char *buf,int line_width)
{
  char *b2;
  int i,i0,lspace;

  snew(b2,strlen(buf)+1);
  i0 = 0;
  do {
    i=i0;
    for( ; (i<i0+line_width) && (buf[i]); i++) {
      b2[i] = buf[i];
      if (buf[i] == ' ')
        lspace = i;
    }
    if (buf[i]) {
      b2[lspace] = '\n';
      i0 = lspace+1;
    }
  } while (buf[i]);
  b2[i] = '\0';
  
  return b2;
}

void please_cite(FILE *fp,char *key)
{
  static char *citedb[] = {
   "Berendsen95a",
   "H. J. C. Berendsen, D. van der Spoel and R. van Drunen",
   "GROMACS: A message-passing parallel molecular dynamics implementation",
   "Comp. Phys. Comm.",
   "95 1995 43 56",
   "Berendsen84a",
   "H. J. C. Berendsen, J. P. M. Postma, A. DiNola and J. R. Haak",
   "Molecular dynamics with coupling to an external bath",
   "J. Chem. Phys.",
   "81 1984 3684 3690",
   "Ryckaert77a",
   "J. P. Ryckaert and G. Ciccotti and H. J. C. Berendsen",
   "Numerical Integration of the Cartesian Equations of Motion of a "
   "System with Constraints; Molecular Dynamics of n-Alkanes",
   "J. Comp. Phys.",
   "23 1977 327 341",
   "Miyamoto92a",
   "S. Miyamoto and P. A. Kollman",
   "SETTLE: An Analytical Version of the SHAKE and RATTLE Algorithms "
   "for Rigid Water Models",
   "J. Comp. Chem.",
   "13 1992 952 962",
   "Barth95a",
   "E. Barth and K. Kuczera and B. Leimkuhler and R. D. Skeel",
   "Algorithms for Constrained Molecular Dynamics",
   "J. Comp. Chem.",
   "16 1995 1192 1209",
   "Torda89a",
   "A. E. Torda and R. M. Scheek and W. F. van Gunsteren",
   "Time-dependent distance restraints in molecular dynamics simulations",
   "Chem. Phys. Lett.",
   "157 1989 289 294",
   "Tironi95a",
   "I. G. Tironi and R. Sperb and P. E. Smith and W. F. van Gunsteren",
   "Generalized reaction field method for molecular dynamics simulations",
   "J. Chem. Phys",
   "102 1995 5451 5459",
   "Hess97a",
   "B. Hess and H. Bekker and H. J. C. Berendsen and J. G. E. M. Fraaije",
   "LINCS: A Linear Constraint Solver for molecular simulations",
   "J. Comp. Chem.",
   "18 1997 1463 1472" 
  };
#define NSTR asize(citedb)
  
  int  j,index,year,vol,p1,p2;
  char *ptr[3];
#define LINE_WIDTH 79
  
  index = search_str(NSTR,citedb,key);
  
  fprintf(fp,"\n++++++++ PLEASE CITE THE FOLLOWING REFERENCE ++++++++\n");
  if ((index != -1) && (index+4 < NSTR)) {
    if (sscanf(citedb[index+4],"%d%d%d%d",&vol,&year,&p1,&p2) != 4) {
      vol=year=p1=p2=0;
    }
    /* Insert newlines */
    for(j=1; (j<=3); j++) 
      ptr[j-1] = wrap_lines(citedb[index+j],LINE_WIDTH);
    fprintf(fp,"%s\n%s\n%s %d (%d) pp. %d-%d\n",
            ptr[0],ptr[1],ptr[2],
            vol,year,p1,p2);
    for(j=0; (j<3); j++)
      sfree(ptr[j]);
  }
  else {
    fprintf(fp,"Entry %s not found in citation database\n",key);
  }
  fprintf(fp,"-------- -------- --- Thank You --- -------- --------\n\n");
  fflush(fp);
}
