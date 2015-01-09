/* ===============================================================
    $RCSfile: astring.c,v $
      Author: Piotr Grzybowski <merlin@asua.org.pl>
       $Date: 1999/04/28 16:38:44 $
   $Revision: 1.2 $
      $State: Exp $
       Notes: Biblioteka funkcji jak IString:: dzialajacych na char*

 Copyright ¸ 1999 Asu'a (http://www.asua.org.pl)
================================================================== */

#include <stdlib.h>
#include "astring.h"

LONG astrixof(char *str,char *source,LONG start_pos,LONG end_pos)
{
 LONG zwr=-1,i;
 if (start_pos>end_pos) return -1;
 if (end_pos>astrlen(str)) return -1;
 if ((end_pos-start_pos)<astrlen(source)) return -1; 
 for(i=start_pos;i<end_pos;i++) {
  if (i+astrlen(source)<=end_pos) if (astrcmp(astrsbstr(str,i,i+astrlen(source)),0,source,0)==0) return i;
 }
 return zwr;
};

char* astrsbstr(char *str,LONG start_pos,LONG end_pos)
{
 char *zwr; LONG i;
 if (start_pos>end_pos||start_pos==end_pos) return "";
 zwr=(char *)calloc(end_pos-start_pos+1,1);
 for (i=start_pos;i<end_pos;i++)
  *(zwr+i-start_pos)=*(str+i);
 *(zwr+end_pos-start_pos+1)='\0';
 return zwr;
};

LONG astrixoao(char *str,char *source,LONG start_pos,LONG end_pos)
{
 LONG i,j,zwr=-1;
 if (start_pos>end_pos) return -1;
 if (end_pos>astrlen(str)) return -1;
 for(i=0;i<astrlen(source);i++)
  for(j=start_pos;j<end_pos;j++){
   if (*(source+i)==*(str+j)) { return j; };
  }
 return zwr;
};

char* astrcut(char *str,LONG start_pos,LONG end_pos)
{
 char *zwr; LONG i;
 if (end_pos==0) end_pos=astrlen(str);
 if (start_pos>end_pos||end_pos>astrlen(str)) return "";
 zwr=(char *)calloc(astrlen(str)-(end_pos-start_pos)+1,1);
 for(i=0;i<start_pos;i++) *(zwr+i)=*(str+i);
 for(i=0;i<(astrlen(str)-end_pos);i++) *(zwr+start_pos+i)=*(str+end_pos+i);
 *(zwr+astrlen(str)-(end_pos-start_pos)+1)='\0';
 return zwr;
};

LONG astrixofwrd2(char *str,char *word)
{
 LONG i,zwr=-1;
 for(i=0;i<=astrnumwrds(str);i++){
  if (astrcmp(astrwrd(str,i),0,word,0)==0) { zwr=astrixofwrd(str,i); break; }
 }
 return zwr;
};

LONG astrixofwrd(char *str,LONG num_word)
{
 LONG i,i_str=-1,zwr=0,spacja=0,poz0=-1;
 do {
  i_str++;
 } while(*(str+i_str)==' ');
 for(i=i_str;i<astrlen(str);i++){
  if (*(str+i)==' '){ spacja++; }
  if (*(str+i)!=' '&&spacja) { zwr++; spacja=0; }
  if (zwr==num_word-1){ poz0=i; break; }
 }
 return (poz0);
};

LONG astrlnofwrd(char *str,LONG num_word)
{
 LONG i=astrixofwrd(str,num_word),i1=0;
 i1=i;
 do {
  i1++;
 } while (*(str+i1)!=' '&&*(str+i1)!='\0');
 return (i1-i);
};

char* astrwrd(char *str,LONG num_word)
{
 if (num_word>astrnumwrds(str)) return "";
 return astrsbstr(str,astrixofwrd(str,num_word),astrixofwrd(str,num_word)+astrlnofwrd(str,num_word));
};

LONG astrnumwrds(char *str)
{
 LONG zwr=0,i,spacja=0;
 if (*(str+0)==' ') zwr=-1;
 for(i=0;i<astrlen(str);i++){
  if (*(str+i)==' '||*(str+i)==9){ spacja++; }
  if ((*(str+i)!=' '||*(str+i)!=9)&&spacja) { zwr++; spacja=0; }
 }
 if (astrlen(str)==0) zwr=-1;
 return zwr+1;
};

char* astrwrds(char *str,LONG start_word,LONG end_word)
{
 char *zwr; LONG i;
 if (start_word>end_word) return "";
 if (end_word>astrnumwrds(str)) return "";
 zwr=astrwrd(str,start_word);
 for(i=start_word;i<end_word;i++){
  zwr=astrcon(astrcon(zwr," "),astrwrd(str,i+1));
 }
 return zwr;
};

LONG astrlsixof(char *str,char *source,LONG start_pos,LONG end_pos)
{
 char *strr="",*s=""; LONG start_pos_rez;
 strr=astrcon(strr,str);
 s=astrcon(s,source);
 if (astrixof(str,source,0,astrlen(str))==-1) return -1;
 start_pos_rez=start_pos; start_pos=astrlen(str)-end_pos-1;
 end_pos=astrlen(str)-start_pos_rez;
 return (astrlen(strr)-astrlen(s)-astrixof(astrrev(strr,-1,-1),astrrev(s,-1,-1),start_pos,end_pos));
};

LONG astrlsixoao(char *str,char *source,LONG start_pos,LONG end_pos)
{
 char *s=astrrev(astrsbstr(str,start_pos,end_pos),-1,-1),*source_rev=astrrev(source,-1,-1); LONG i,j;
 if (s==NULL) return -1;
 for(i=0;i<astrlen(source_rev);i++)
  for(j=0;j<astrlen(s);j++){
   if (*(source+i)==*(s+j)) { return j; };
  }
 return -1;
};

char *astrcon(char *ch0,char *ch1)
{
 char *zwr;
 LONG i;
 if (ch0==NULL&&ch1==NULL) return "";
 if (ch0==NULL) return ch1;
 if (ch1==NULL) return ch0;
 zwr=(char *)calloc(astrlen(ch0)+astrlen(ch1)+1,1);
 for(i=0;i<astrlen(ch0);i++) {
  *(zwr+i)=*(ch0+i);
 }
 for(i=astrlen(ch0);i<=astrlen(ch0)+astrlen(ch1);i++) {
  *(zwr+i)=*(ch1+i-astrlen(ch0));
 }
 *(zwr+astrlen(ch0)+astrlen(ch1)+1)='\0';
 return zwr;
};

char* astrins(char *str,LONG poz,char *s)
{
 char *zwr=calloc(astrlen(str)+astrlen(s)+1,sizeof(char));
 zwr=astrcon(astrcon(astrsbstr(str,0,poz),s),astrsbstr(str,poz,astrlen(str)));
 return zwr;
};

LONG astrocc(char *str,char *s)
{
 LONG zwr=0,i,flaga=0;
 for(i=0;i<astrlen(str);i++) if (flaga>0) flaga--; else {
  if (astrcmp(astrsbstr(str,i,i+astrlen(s)),0,s,0)==0) { zwr++; flaga=astrlen(s)-1; }
 }
 return zwr;
};

LONG astrlen(char s[])
{
 LONG i=0;
 if (s==NULL) return 0;
 if (s[0]=='\0') return 0;
 do {
  i++;
 } while(*(s+i)!='\0');
 return i;
};

char *astrrev(char source[],LONG offset,LONG count)
{
 char *probka,*probkaout;
 LONG i=0;
 if (offset<0) offset=0;
 if (count<0) count=astrlen(source);
 if (count==0) return source;
 if (offset+count>astrlen(source)) count=astrlen(source)-offset;
 probka=astrsbstr(source,offset,offset+count);
 source=astrcut(source,offset,offset+count);
 probkaout=(char *)calloc(count+1,1);
 for (i=0;i<=count;i++) 
  *(probkaout+i)=*(probka+astrlen(probka)-i-1);
 return astrins(source,offset,probkaout);
};

LONG astrcmp(char s1[],LONG offset1,char s2[],LONG offset2)
{
 LONG i,imax=astrlen(s2);
 if (astrlen(s1)>astrlen(s2)) imax=astrlen(s1);
 for (i=0;i<imax;i++)
  if (i+offset1>astrlen(s1)||i+offset2>astrlen(s2)) return -1; else
  if (s1[i+offset1]!=s2[i+offset2]) return -1;
 return 0;
};
