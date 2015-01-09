/* ===============================================================
    $RCSfile: astring.h,v $
      Author: Piotr Grzybowski <merlin@asua.org.pl>
       $Date: 1999/04/28 16:38:44 $
   $Revision: 1.2 $
      $State: Exp $
       Notes: Biblioteka funkcji jak IString:: dzialajacych na char*

 Copyright ¸ 1999 Asu'a (http://www.asua.org.pl)
================================================================== */
#ifndef _ASTRING_H_
#define _ASTRING_H_

#include <os2.h>

LONG astrixof(char *str,char *source,LONG start_pos,LONG end_pos);                  /*index of*/
char* astrsbstr(char *str,LONG start_pos,LONG end_pos);                  /* sub string */
LONG astrixoao(char *str,char *source,LONG start_pos,LONG end_pos);      /* idex of any of */
char* astrcut(char *str,LONG start_pos,LONG end_pos);                    /* remove */
LONG astrixofwrd(char *str,LONG num_word);                              /* index of word (num_word)*/
LONG astrixofwrd2(char *str,char *word);                              /* index of word (word)*/
LONG astrlnofwrd(char *str,LONG num_word);                              /* length of word */
char* astrwrd(char *str,LONG num_word);                                 /* word */
LONG astrnumwrds(char *str);                                          /* num words */
char* astrwrds(char *str,LONG start_word,LONG end_word);                 /* words */
LONG astrlsixof(char *str,char *source,LONG start_pos,LONG end_pos);    /* last index of */
LONG astrlsixoao(char *str,char *source,LONG start_pos,LONG end_pos);   /* last index of any of */
char* astrcon(char *ch0,char *ch1);                                    /*  */
char* astrins(char *str,LONG poz,char *s);
LONG astrocc(char *str,char *s);                                         /* occurences czy jak tam.. */
LONG astrlen(char s[]);
char *astrrev(char source[],LONG offset,LONG count);                    /* odwraca count znakow z source */
LONG astrcmp(char s1[],LONG offset1,char s2[],LONG offset2);

#endif //_ASTRING_H_