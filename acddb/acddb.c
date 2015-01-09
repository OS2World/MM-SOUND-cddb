/* ===============================================================
   Warp CD-Copy
   ============

    $RCSfile: acddb.c,v $
      Author: Bartosz_Tomasik <bart2@asua.org.pl>
       $Date: 1999/10/03 15:00:00 $
   $Revision: 1.0 $
      $State: Exp $
       Notes: Modul obslugi cddb

 Copyright ¸ 1999 Asu'a (http://www.asua.org.pl)
================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>

#include "acddb.h"
#include "..\astring\astring.h"

#define XMCD "xmcd" //znacznik pliku bazy cddb

//----------------------------------------------
// definicje struktur
//

//struktura dla listy laczonej (pojedynczej)
typedef struct _cddb_atom
{
  ATOM atomV;        //wartosc pola
  char cAtomTableIndex; //inex do tablicy uchwytow tablic atomow
  struct _cddb_atom *pNext; //wskaznik na nastepne tego typu pole
} CDDB_ATOM;

//struktura dla listy laczonej atomow (podwojnej)
typedef struct _cddb_multiatom
{
  CDDB_ATOM caAtom;      //zawiera jedna liste laczona atomow
  struct _cddb_multiatom *pNext; //wskaznik na nastepne tego typu pole
} CDDB_MULTIATOM;

//dane dla pojedynczego cd
typedef struct
{
  //pola ogolne - zwiazane z obsluga
  BOOL bIsValid;     //czy struktura ma poprawne dane
  BOOL bQuit;        //uzywane do konczenia watkow CddbQuery
  HMTX hmtxSem; //semafor dostepu do struktury
  int tid;      //id watku pytania

  //pola na dane cddb - kazde zawiera 1 lub wiecej
  CDDB_ATOM caCddbId;     //cddbid
  CDDB_ATOM caArtist;     //artysta
  CDDB_ATOM caTitle;      //tytul cd
  CDDB_ATOM caTTitle;     //tytuly scierzek
  CDDB_ATOM caExtD;       //informacje rozszerzone dla CD
  CDDB_MULTIATOM cmaExtT; //informacje rozszerzone dla scierzek
  CDDB_ATOM caPlayOrder;  //kolejnosc odtwarzania
  CDDB_ATOM caOther;      //inne informacje (zawarte w komentarzu na poczaktu
                          //pliku
} CDDBCDDATA;

//---------------------------------------------
// funkcje wewnetrzne
//

// ssane z dll'a:
LONG _syscall (*CddbSockInit)();
LONG _syscall (*_CddbQueryRemote)(CDDB_QUERY * query,char *bufor, 
                                 ULONG *rozmiar, BOOL *bQuit);

//w tym pliku
LONG _CddbAddMultiAtom(LONG index, ULONG cdNum);
LONG _CddbInvalidateEntry(CDDBCDDATA *dana);
LONG _CddbIsAtom(int Pole, ULONG index, ULONG cdNum);
LONG _CddbLinkDll();
void _CddbFreeDll();
LONG _CddbParse(CDDB_QUERY * query,char *bufor, ULONG rozmiar);
void _CddbSave(CDDB_QUERY *save);
LONG _CddbSaveField(CDDB_QUERY *save, int Pole,ULONG index,
                    char * prestr, char* poststr,FILE *plik,BOOL useCounter);
LONG _CddbSetValue(int Pole,LONG index, ULONG cdNum, PSZ Wartosc);
void _CddbQuery(CDDB_QUERY * query);
LONG _CddbQueryLocal(CDDB_QUERY * query,char *bufor, ULONG *rozmiar);
LONG _CddbQueryValue(int Pole, LONG index, LONG deep, ULONG cdNum,
                     PSZ *Wartosc,ULONG ulBufSize);
LONG _CddbQueryValueCount(int Pole, ULONG *index, ULONG *deep, ULONG cdNum);
LONG _CddbQueryValueLength(int Pole, LONG index, LONG deep, ULONG cdNum,
                           ULONG *rozmiar);


//---------------------------------------------
// zmienne globalne
//
HMODULE acddbtcp=NULLHANDLE; //uchwyt do dll'a od tcp...
ULONG WM_CDDB=0; // kod notyfikacji cddb
BOOL cddbInitialized=FALSE; //czy biblioteka jest zainicjowana
HATOMTBL *hatomtblAtomy;    //tablica uchwytow Tablic Atomow
int iAtomTablesCnt;         //liczba tablic atomow
CDDBCDDATA *cdCdTable;      //tablica danych CDDB dla kazdego napedu CD
ULONG iCdTableCnt;          //liczba napedow Cd - pozycji w cdCdTable
HMTX hmtxAtoms=NULLHANDLE;  //semafor dostepu do tablic atomow
                            //uzywany podczas rozszerzania etc..
HWND hwndCddbWin=NULLHANDLE;//uchwyt okna do ktorego wysylamy WM_CDDB

//-----------------------------------
// funkcje
//

LONG CddbInitialize(ULONG drives, ULONG wm_cddb,HWND hwndCddb)
{
  ULONG rc,i; //kod powrotu i licznik

  if (cddbInitialized)  // Modul juz zostal zainicjowany!
    return ERR_CDDB_ALREADYDONE;

  WM_CDDB = wm_cddb; // zapamietanie kodu notyfikacji
  hwndCddbWin = hwndCddb; //zapamietanie uchwytu okna odbierajacego komunikat

  //tworzymy semafor dostepu do tablic atomow i od razu uzywamy go
  rc = DosCreateMutexSem(NULL,&hmtxAtoms,0,TRUE);
  if (rc!=0) return ERR_CDDB_SEMCREATEFAIL;

  iAtomTablesCnt = 1; //na razie bedziemy mieli jedna tablice atomow
  //alokujemy pamiec pod nia
  hatomtblAtomy = (HATOMTBL *) malloc(sizeof(HATOMTBL));
  //jesli nie udala sie alokacja..
  if (hatomtblAtomy == NULL)
   {
     DosReleaseMutexSem(hmtxAtoms);
     DosCloseMutexSem(hmtxAtoms);
     return ERR_CDDB_MEMALLOCFAILED;
   };
  //tworzymy tablice atomow
  hatomtblAtomy[0] = WinCreateAtomTable(0,0);
  //jesli nie udalo sie
  if (hatomtblAtomy[0] == NULLHANDLE)
   {
     free(hatomtblAtomy);
     DosReleaseMutexSem(hmtxAtoms);
     DosCloseMutexSem(hmtxAtoms);
     return ERR_CDDB_ATBLCREATEFAILED;
   };

  iCdTableCnt = drives; //ile mamy napedow CD w systemie
  //alokujemy pamiec pod tablice danych cddb dla napedow CD
  cdCdTable = (CDDBCDDATA *) malloc (iCdTableCnt * sizeof(CDDBCDDATA));
  //jesli nie udalo sie
  if (cdCdTable == NULL)
   {
     WinDestroyAtomTable(hatomtblAtomy[0]);
     free(hatomtblAtomy);
     DosReleaseMutexSem(hmtxAtoms);
     DosCloseMutexSem(hmtxAtoms);
     return ERR_CDDB_ATBLCREATEFAILED;
   };

  //dla kazdej pozycji w tablicy tworzymy semafor - na razie jest nieuzywany
  for (i=0;i<iCdTableCnt;i++)
  {
    rc=DosCreateMutexSem(NULL,&cdCdTable[i].hmtxSem,0,FALSE);
    //jakby cos nie wyszlo..
    if (rc!=0)
    {
      //usuwamy te ktore juz stworzylismy (--i bo ten aktualny nie jest
      //poprawny)
      for (--i;i>0;i--) DosCloseMutexSem(cdCdTable[i-1].hmtxSem);
      //i zwalniamy reszte zasobow..
      WinDestroyAtomTable(hatomtblAtomy[0]);
      free(hatomtblAtomy);
      free(cdCdTable);
      DosReleaseMutexSem(hmtxAtoms);
      DosCloseMutexSem(hmtxAtoms);
      return ERR_CDDB_SEMCREATEFAIL;
    };
  };

  //zerowanie struktur w tablicy danych cddb dla kazdego cd
  for (i=0;i<iCdTableCnt;i++)
  {
   cdCdTable[i].bIsValid=FALSE;     //czy struktura ma poprawne dane
   cdCdTable[i].bQuit=TRUE;        //uzywane do konczenia watkow CddbQuery
   cdCdTable[i].tid=-1;

   cdCdTable[i].caCddbId.atomV=0;
   cdCdTable[i].caCddbId.pNext=NULL;
   cdCdTable[i].caCddbId.cAtomTableIndex=0;
   cdCdTable[i].caArtist.atomV=0;
   cdCdTable[i].caArtist.pNext=NULL;
   cdCdTable[i].caArtist.cAtomTableIndex=0;
   cdCdTable[i].caTitle.atomV=0;
   cdCdTable[i].caTitle.pNext=NULL;
   cdCdTable[i].caTitle.cAtomTableIndex=0;
   cdCdTable[i].caTTitle.atomV=0;
   cdCdTable[i].caTTitle.pNext=NULL;
   cdCdTable[i].caTTitle.cAtomTableIndex=0;
   cdCdTable[i].caExtD.atomV=0;
   cdCdTable[i].caExtD.pNext=NULL;
   cdCdTable[i].caExtD.cAtomTableIndex=0;
   cdCdTable[i].caPlayOrder.atomV=0;
   cdCdTable[i].caPlayOrder.pNext=NULL;
   cdCdTable[i].caPlayOrder.cAtomTableIndex=0;
   cdCdTable[i].caOther.atomV=0;
   cdCdTable[i].caOther.pNext=NULL;
   cdCdTable[i].caOther.cAtomTableIndex=0;
   cdCdTable[i].cmaExtT.caAtom.atomV=0;
   cdCdTable[i].cmaExtT.caAtom.pNext=NULL;
   cdCdTable[i].cmaExtT.pNext=NULL;
   cdCdTable[i].cmaExtT.caAtom.cAtomTableIndex=0;
  };

  rc=ERR_CDDB_OK;

  rc=_CddbLinkDll();
  DosReleaseMutexSem(hmtxAtoms); //zwalniamy semafor
  cddbInitialized=TRUE;  //zainicjowalismy modul

  if (acddbtcp!=NULLHANDLE) CddbSockInit();

  return rc;
};

LONG CddbCancelAction(ULONG cdNum) //cdNum liczymy od zera!
{
  ULONG rc;
  PID pid=0;
  TID tid=0;
  ULONG ulCount=0;

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;
  rc=DosQueryMutexSem(hmtxAtoms,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;
  //jesli dzieje sie cos wiekszego i semafor jest zablokowany...
  if (ulCount!=0) return ERR_CDDB_MODINUSE;
  if (cdNum>iCdTableCnt) return ERR_CDDB_OUTOFRANGE;
  //czy juz nie dalismy sygnalu by zakonczyc te funkcje?
  if (cdCdTable[cdNum].bQuit==TRUE) return ERR_CDDB_ALREADYDONE;
  rc=DosQueryMutexSem(cdCdTable[cdNum].hmtxSem,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;
  //czy jest w uzyciu?
  if (ulCount!=0) cdCdTable[cdNum].bQuit=TRUE; else
  //lub moze jest dzialajacy thread?
  if (cdCdTable[cdNum].tid!=-1) cdCdTable[cdNum].bQuit=TRUE; else
  //nie ma znaczy sie juz tu raz bylismy :)
   return ERR_CDDB_ALREADYDONE;
  return ERR_CDDB_OK;
};

LONG CddbCreateQuery(CDDB_QUERY query)
{
  ULONG rc;
  PID pid=0;
  TID tid=0;
  ULONG ulCount=0;

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;
  rc=DosQueryMutexSem(hmtxAtoms,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;
  //jesli dzieje sie cos wiekszego i semafor jest zablokowany...
  if (ulCount!=0) return ERR_CDDB_MODINUSE;
  //sprawdzamy czy czasem nie jest juz wlaczone zapytanie lub zapis
  rc=DosQueryMutexSem(cdCdTable[query.lCdNum].hmtxSem,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;
  if ((ulCount!=0)||(cdCdTable[query.lCdNum].tid!=-1))
     return ERR_CDDB_MODINUSE;

  //blokujemy dostep do danych - podnosimy semafor
  rc=DosRequestMutexSem(cdCdTable[query.lCdNum].hmtxSem,0);
  if (rc!=0) return ERR_CDDB_SEMREQFAILED;

  //najpierw usuwamy dane ktore ewentualnie tam byly
  _CddbInvalidateEntry(&cdCdTable[query.lCdNum]);
  cdCdTable[query.lCdNum].bQuit=FALSE; //ustawiamy flage wymuszajaca koniec
                                       //zapytania na falsz
  //startujemy watek zapytania
  cdCdTable[query.lCdNum].tid = _beginthread(_CddbQuery,NULL,8192,&query);
  //jesli nie wyszlo..
  if (cdCdTable[query.lCdNum].tid==-1)
  {
   DosReleaseMutexSem(cdCdTable[query.lCdNum].hmtxSem);
   cdCdTable[query.lCdNum].bQuit=TRUE;
   return ERR_CDDB_THRCREATEFAILED;
  };
  return ERR_CDDB_OK;
};

LONG CddbQueryValue(int Pole, LONG index, LONG deep, ULONG cdNum,
                          PSZ *Wartosc, ULONG ulBufSize)
{
  ULONG rc;
  PID pid=0;
  TID tid=0;
  ULONG ulCount=0;

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;

  //sprawdzamy czy czasem nie jest juz wlaczone zapytanie
  rc=DosQueryMutexSem(cdCdTable[cdNum].hmtxSem,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;

  //blokujemy dostep do danych - podnosimy semafor
  rc=DosRequestMutexSem(cdCdTable[cdNum].hmtxSem,0);
  if (rc!=0) return ERR_CDDB_SEMREQFAILED;

  if ((cdCdTable[cdNum].bIsValid==FALSE)||(cdCdTable[cdNum].bQuit==FALSE))
  {
   DosReleaseMutexSem(cdCdTable[cdNum].hmtxSem);
   return ERR_CDDB_WRONGDATA;
  };

  rc=_CddbQueryValue(Pole,index,deep,cdNum,Wartosc,ulBufSize);
  DosReleaseMutexSem(cdCdTable[cdNum].hmtxSem);
  return rc;
};

LONG CddbQueryValueCount(int Pole, ULONG * index, ULONG * deep, ULONG cdNum)
{
  ULONG rc;
  PID pid=0;
  TID tid=0;
  ULONG ulCount=0;

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;
  //sprawdzamy czy czasem nie jest juz wlaczone zapytanie
  rc=DosQueryMutexSem(cdCdTable[cdNum].hmtxSem,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;

  //blokujemy dostep do danych - podnosimy semafor
  rc=DosRequestMutexSem(cdCdTable[cdNum].hmtxSem,0);
  if (rc!=0) return ERR_CDDB_SEMREQFAILED;

  if ((cdCdTable[cdNum].bIsValid==FALSE)||(cdCdTable[cdNum].bQuit==FALSE))
  {
   DosReleaseMutexSem(cdCdTable[cdNum].hmtxSem);
   return ERR_CDDB_WRONGDATA;
  };

  rc=_CddbQueryValueCount(Pole,index,deep,cdNum);
  DosReleaseMutexSem(cdCdTable[cdNum].hmtxSem);
  return rc;

};

LONG CddbQueryValueLength(int Pole, LONG index, LONG deep, ULONG cdNum,
                          ULONG *rozmiar)
{
  LONG rc;
  PID pid=0;
  TID tid=0;
  ULONG ulCount=0;

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;
  //sprawdzamy czy czasem nie jest juz wlaczone zapytanie
  rc=DosQueryMutexSem(cdCdTable[cdNum].hmtxSem,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;

  //blokujemy dostep do danych - podnosimy semafor
  rc=DosRequestMutexSem(cdCdTable[cdNum].hmtxSem,0);
  if (rc!=0) return ERR_CDDB_SEMREQFAILED;

  if ((cdCdTable[cdNum].bIsValid==FALSE)||(cdCdTable[cdNum].bQuit==FALSE))
  {
   DosReleaseMutexSem(cdCdTable[cdNum].hmtxSem);
   return ERR_CDDB_WRONGDATA;
  };

 rc=_CddbQueryValueLength(Pole,index,deep,cdNum,rozmiar);
 DosReleaseMutexSem(cdCdTable[cdNum].hmtxSem);
 return rc;
};

LONG CddbSave(CDDB_QUERY save)
{
  ULONG rc;
  PID pid=0;
  TID tid=0;
  ULONG ulCount=0;

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;
  rc=DosQueryMutexSem(hmtxAtoms,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;
  //jesli dzieje sie cos wiekszego i semafor jest zablokowany...
  if (ulCount!=0) return ERR_CDDB_MODINUSE;
  //sprawdzamy czy czasem nie jest juz wlaczone zapytanie lub zapis
  rc=DosQueryMutexSem(cdCdTable[save.lCdNum].hmtxSem,&pid,&tid,&ulCount);
  if (rc!=0) return ERR_CDDB_SEMQUERYFAILED;
  if ((ulCount!=0)||(cdCdTable[save.lCdNum].tid!=-1))
     return ERR_CDDB_MODINUSE;

  //blokujemy dostep do danych - podnosimy semafor
  rc=DosRequestMutexSem(cdCdTable[save.lCdNum].hmtxSem,0);
  if (rc!=0) return ERR_CDDB_SEMREQFAILED;

  cdCdTable[save.lCdNum].bQuit=FALSE; //ustawiamy flage wymuszajaca koniec
                                       //zapytania na falsz

  //a tak w ogole czy te dne sa poprawne?
  if (cdCdTable[save.lCdNum].bIsValid!=TRUE)
  {
   DosReleaseMutexSem(cdCdTable[save.lCdNum].hmtxSem);
   cdCdTable[save.lCdNum].bQuit=TRUE;
   return ERR_CDDB_DATANOTVALID;
  };

  //startujemy watek zapytania
  cdCdTable[save.lCdNum].tid = _beginthread(_CddbSave,NULL,8192,&save);
  //jesli nie wyszlo..
  if (cdCdTable[save.lCdNum].tid==-1)
  {
   DosReleaseMutexSem(cdCdTable[save.lCdNum].hmtxSem);
   cdCdTable[save.lCdNum].bQuit=TRUE;
   return ERR_CDDB_THRCREATEFAILED;
  };
  return ERR_CDDB_OK;
}


LONG CddbTerminate(ULONG ulTimeOut)
{
  ULONG rc,i; //kod powrotu i licznik

  if (!cddbInitialized)  // Modul zostal nie zainicjowany!
    return ERR_CDDB_MODNOTINIT;

  //blokujemy dostep do wszystkiego...
  rc=DosRequestMutexSem(hmtxAtoms,ulTimeOut);
  if (rc!=0) return ERR_CDDB_MODINUSE;

  //czy wszystkie watki-zapytan sa zakonczone?
  for (i=iCdTableCnt;i>0;i--)
    if ((cdCdTable[i-1].tid!=-1)||
        (cdCdTable[i-1].bQuit==FALSE)) return ERR_CDDB_MODINUSE;

  //usuwamy semafory i mazemy zawartosc struktur danych
  for (i=iCdTableCnt;i>0;i--)
  {
   DosCloseMutexSem(cdCdTable[i-1].hmtxSem);
   _CddbInvalidateEntry(&cdCdTable[i-1]);
  };
  //usuwamy tablice atomow
  for (i=iAtomTablesCnt;i>0;i--) WinDestroyAtomTable(hatomtblAtomy[i-1]);
  //zwalniamy pamiec po tablicy uchytow do tablic atomow
  free(hatomtblAtomy);
  //zwalniamy pamiec po tablicy danych cddb dla kazdego cd
  free(cdCdTable);

  cddbInitialized=FALSE;  //modul juz nie jest zainicjalizowany
  DosReleaseMutexSem(hmtxAtoms); //zwalniamy semafor
  DosCloseMutexSem(hmtxAtoms);   //i zamykamy go
  _CddbFreeDll();
  return ERR_CDDB_OK;
};

LONG _CddbInvalidateEntry(CDDBCDDATA *dana)
{
 CDDB_ATOM *tmp_atom,*tmp_atom2;
 CDDB_MULTIATOM *tmp_multiatom,*tmp_multiatom2;
 int Pole=1;
 BOOL first=TRUE;//potrzebne do EXTT

 while (Pole<9) //dopoki nie przekroczylismy zakresu
 {
 //najpierw ustawiamy wskaznik na strukture cddb atom - potem juz bedziemy
 //operowac na tym samym typie danych
 switch (Pole)
 {
  case CDDB_VALNAME_CDDBID:
       tmp_atom=&dana->caCddbId; Pole++;
       break;
  case CDDB_VALNAME_ARTIST:
       tmp_atom=&dana->caArtist; Pole++;
       break;
  case CDDB_VALNAME_TITLE:
       tmp_atom=&dana->caTitle; Pole++;
       break;
  case CDDB_VALNAME_TTITLE:
       tmp_atom=&dana->caTTitle; Pole++;
       break;
  case CDDB_VALNAME_EXTD:
       tmp_atom=&dana->caExtD; Pole++;
       break;
  case CDDB_VALNAME_EXTT:
       if (first)
       {
        first=FALSE;
        tmp_multiatom=&dana->cmaExtT;
        tmp_atom=&tmp_multiatom->caAtom;
        tmp_multiatom=tmp_multiatom->pNext;
       } else
        if (tmp_multiatom!=NULL)
        {
         tmp_multiatom=tmp_multiatom->pNext;
         tmp_atom=&tmp_multiatom->caAtom;
        } else Pole++;
       break;
  case CDDB_VALNAME_PLAYORDER:
       tmp_atom=&dana->caPlayOrder; Pole++;
       break;
  case CDDB_VALNAME_OTHER:
       tmp_atom=&dana->caOther; Pole++;
       break;
  default:
   return ERR_CDDB_WRONGFIELD;
 };
  if (tmp_atom!=NULL)
  {
   tmp_atom->atomV=0;
   tmp_atom->cAtomTableIndex=0;
   tmp_atom=tmp_atom->pNext;
  };
  while (tmp_atom!=NULL) //jesli jest co zwolnic
  {
   tmp_atom2=tmp_atom->pNext;//zapamietujemy nastepne pole
   free(tmp_atom); //zwalniamy to
   tmp_atom=tmp_atom2; //i odtwarzamy nastepne
  };//END while (tmp_atom!=NULL)
 };//END while (pole<9)

 tmp_multiatom=dana->cmaExtT.pNext;
 while (tmp_multiatom!=NULL)
 {
  tmp_multiatom2=tmp_multiatom->pNext;
  free(tmp_multiatom);
  tmp_multiatom=tmp_multiatom2;
 };

 dana->bIsValid=FALSE;     //czy struktura ma poprawne dane
 dana->bQuit=TRUE;        //uzywane do konczenia watkow CddbQuery
 dana->tid=-1;

 return ERR_CDDB_OK;
};

LONG _CddbAddMultiAtom(LONG index, ULONG cdNum)
{
 LONG rc;
 CDDB_MULTIATOM *tmp_multiatom;

       tmp_multiatom=&cdCdTable[cdNum].cmaExtT;
       //index okresja dla ktorej scierzki podajemy informacje rozszerzone
        for (rc=1;rc<index;rc++)
        {
         //czy jest ta inna?
         if (tmp_multiatom->pNext==NULL)
         {
          //nie ma musimy dodac..
          tmp_multiatom->pNext = (CDDB_MULTIATOM *) malloc (sizeof(CDDB_MULTIATOM));
          //sprawdzamy czy pamiec sie zaalokowala
          if (tmp_multiatom->pNext==NULL)
             return ERR_CDDB_MEMALLOCFAILED;
          //przechodzimy do nowej struktury
          tmp_multiatom=tmp_multiatom->pNext;
          //i zerujemy ja
          tmp_multiatom->pNext=NULL;
          tmp_multiatom->caAtom.atomV=0;
          tmp_multiatom->caAtom.pNext=NULL;
         } else //jest wiec po prostu przejdzmy tam
           tmp_multiatom=tmp_multiatom->pNext;
        };//END for (rc=1;rc<=index;rc++)
 return ERR_CDDB_OK;
};

LONG _CddbIsAtom(int Pole, ULONG index, ULONG cdNum)
{
 ULONG rc;
 CDDB_ATOM *tmp_atom;
 CDDB_MULTIATOM *tmp_multiatom;

 switch (Pole)
 {
  case CDDB_VALNAME_CDDBID:
       tmp_atom=&cdCdTable[cdNum].caCddbId;
       break;
  case CDDB_VALNAME_ARTIST:
       tmp_atom=&cdCdTable[cdNum].caArtist;
       break;
  case CDDB_VALNAME_TITLE:
       tmp_atom=&cdCdTable[cdNum].caTitle;
       break;
  case CDDB_VALNAME_TTITLE:
       tmp_atom=&cdCdTable[cdNum].caTTitle;
       break;
  case CDDB_VALNAME_EXTD:
       tmp_atom=&cdCdTable[cdNum].caExtD;
       break;
  case CDDB_VALNAME_EXTT:
       tmp_multiatom=&cdCdTable[cdNum].cmaExtT;
       //index okresja dla ktorej scierzki pobieramy dane
        for (rc=1;rc<index;rc++)
         if (tmp_multiatom->pNext==NULL)
         {
           return ERR_CDDB_INDEXOUTOFRANGE;
         } else tmp_multiatom=tmp_multiatom->pNext;
       tmp_atom=&tmp_multiatom->caAtom;
       break;
  case CDDB_VALNAME_PLAYORDER:
       tmp_atom=&cdCdTable[cdNum].caPlayOrder;
       break;
  case CDDB_VALNAME_OTHER:
       tmp_atom=&cdCdTable[cdNum].caOther;
       break;
  default:
   return ERR_CDDB_WRONGFIELD;
 };

  //czy jest tam atom?
  if (tmp_atom->atomV==0)
    return ERR_CDDB_NOATOM;

  return ERR_CDDB_OK;
};

LONG _CddbParse(CDDB_QUERY *query, char *bufor, ULONG rozmiar)
{
 char *buf;//bufor na jedna linie
 char *sprbuf;//bufor do sprintf
 ULONG wsk=0;//wskaznik gdzie znajdujemy sie w buforze (tym duzym)
 ULONG i;
 LONG rc,buflen;
 ULONG tmp=0,tracks=0;
 int faza=CDDB_VALNAME_OTHER;//ktora faza parsingu


 //alokujemy pamiec pod linie
 buf = (char *) malloc(80);
 //udalo sie?
 if (buf==NULL) return ERR_CDDB_MEMALLOCFAILED;
 //alokujemy pamiec pod sprintf
 sprbuf = (char *) malloc(9);
 if (sprbuf==NULL) return ERR_CDDB_MEMALLOCFAILED;

 //dopoki nie wyczerpalismy rozmiaru..
 while (wsk<=rozmiar)
 {
  //najpierw musimy pobrac jedna linie do bufora
  i=0;
  while (i==0) //dopoki jestesmy na pocatku lini - probojemy ja wypelnic
  {
   //czyli dopoki nie ma konca lini ladujemy wszytsko jak leci do buf
   while ((wsk<=rozmiar)&&(bufor[wsk]!='\n')) //bylo !=
   {
    //ale musimy spradzac czy nie wychodzimy poza buf
    if (i<=80) buf[i++]=bufor[wsk++];
   };
   wsk++;//przeskakujemy koniec lini
   if (i>80) i=0; //jesli linia byla za dluga.. sorry olewamy ja..
   buf[i]='\0';
  };
  if (cdCdTable[query->lCdNum].bQuit==TRUE)
  {
   free(buf);
   free(sprbuf);
   return ERR_CDDB_ABORTED;
  };
  //koniec pobierania jednej lini
  while (strlen(buf)>0)
  {
   //najpierw sobie zapamietamy ewentualna pozycje =
   if ((rc=astrixof(buf,"=",0,strlen(buf)))<0) rc=0;
   buflen=strlen(buf); //dlugosc nam sie przyda ;)
   //a teraz w zaleznosci od tego w ktorej fazie jestesmy
   switch (faza)
   {
    //plan jest taki, w zaleznosci od fazy, ustalamy zakres z ktorego string
    //z bufora bedzie dodawany do opisu cddb, rc-poczatek zakresu buflen-koniec
    case CDDB_VALNAME_OTHER: //komentarze
         //czy to kometarz?
         if (buf[0]=='#')
           if (astrnumwrds(buf)>=2) rc=2; else
            {
             buf[0]='\0';
             buflen=0;
            }
          else
          {
           faza=CDDB_VALNAME_CDDBID; //nie - czyli nastepne pole
           buflen=0;
          };
          break;
    case CDDB_VALNAME_CDDBID: //cddbid
         //czy to cddbid?
         if (strcmpi("DISCID",astrsbstr(buf,0,rc))==0) rc++;
          else
         {
          faza=CDDB_VALNAME_ARTIST; //nie znacy sie juz DTITLE
           buflen=0;
         };
         break;
    case CDDB_VALNAME_ARTIST: //artyste
         //czy to tytul artysta?
         if (strcmpi("DTITLE",astrsbstr(buf,0,rc))==0)
         {
           rc++;
           buflen=astrixof(buf,"/",0,buflen);
         } else
         {
          tmp=0;//tmp bedzie nam sluzyc za wskaznik scierzki
          faza=CDDB_VALNAME_TTITLE;
          buflen=0;
         }; break;
    case CDDB_VALNAME_TITLE: //tytul
         //czy to tytul artysta?
         if (strcmpi("DTITLE",astrsbstr(buf,0,rc))==0)
         {
           rc=astrixof(buf,"/",0,buflen)+1;
         } else
         {
          tmp=0;//tmp bedzie nam sluzyc za wskaznik scierzki
          faza=CDDB_VALNAME_TTITLE;
          buflen=0;
         }; break;
    case CDDB_VALNAME_TTITLE://tytul scierzki
         //tworzymy wzorzec do porownania np "TTITLE0"
         sprintf(sprbuf,"%s%d","TTITLE",tmp++);
         //sprawdzamy czy to jest TTITLE
         if (strcmpi(sprbuf,astrsbstr(buf,0,rc))==0)
         {
          tracks=tmp;
          rc++;
         } else
         {
          faza=CDDB_VALNAME_EXTD;
          buflen=0;
         };
         break;
    case CDDB_VALNAME_EXTD: //info rozszerzone
         //czy to extd?
         if (strcmpi("EXTD",astrsbstr(buf,0,rc))==0) rc++;
          else //nie znacy sie juz EXTT
         {
          tmp=0;
          faza=CDDB_VALNAME_EXTT;
          buflen=0;
         };
         break;
    case CDDB_VALNAME_EXTT: //informacje rozszrzone dla scierzek
         if (tmp<tracks)
         {
          //tworzymy wzorzec do porownania np "TTITLE0"
          sprintf(sprbuf,"%s%d","EXTT",tmp);
          //sprawdzamy czy to jest EXTT
          if (strcmpi(sprbuf,astrsbstr(buf,0,rc))==0)
           rc++; else
           {
            tmp++;
            buflen=0;
           };
         } else
         {
          faza=CDDB_VALNAME_PLAYORDER;
          buflen=0;
         };
         break;
    case CDDB_VALNAME_PLAYORDER://kolejnosc odtwarzania
         //czy to playorder?
         if (strcmpi("PLAYORDER",astrsbstr(buf,0,rc))==0) rc++;
         else
         {
          faza=9;//to juz tylko . zostala ;)
           buflen=0;
         };
         break;
    case 9:
        if ((buflen==1) && (buf[0]=='.'))
        {
         buf[0]='\0';
         buflen=0; //zeby nie probowalo dodac tej lini
         faza=10;//poza zakresem.. ale to i tak juz nie powinno miec znaczenia
        };
        break;
    default:
     free(buf);
     free(sprbuf);
     return ERR_CDDB_WRONGDATA;
   };
    if (buflen!=0) //jesli jest jakis sensowny koncowy zakres
       {
       if (buf[rc]!=13) //czy czasem nie dodajemy samego konca lini..?
          {
             //dodajemy..
             rc=_CddbSetValue(faza,tmp+1,query->lCdNum,
                                astrsbstr(buf,rc,buflen));
             //udalo sie?
             if (rc!=0)
                {
                free(buf);
                free(sprbuf);
                return rc;
                } else
            //jesli to byl artysta to ta sama linie musimy przekazac do title
            if (faza!=CDDB_VALNAME_ARTIST) buf[0]='\0'; else
                faza=CDDB_VALNAME_TITLE;
         } else
     {
          if (faza==CDDB_VALNAME_EXTT)//jesli to pole to EXTT, to musimy dodac 
                                      //pusty multiatom...
          {
             rc=_CddbAddMultiAtom(tmp+1,query->lCdNum);
             //udalo sie?
             if (rc!=0)
                {
                free(buf);
                free(sprbuf);
                return rc;
                };
          };
     buf[0]='\0';
     };//END if if (buf[rc]!=13)

    };// END if (buflen!=0);
  };//END while (strlen(buf)>0)
 };
  free(buf);
  free(sprbuf);
  return ERR_CDDB_OK;
};

void _CddbSave(CDDB_QUERY *save)
{
 LONG rc=0;    //return code
 FILE *plik;   //wskaznik na strumien
 int faza;     //ktora faza zapisu
 ULONG index=0,deep,licznik; //uzywane do pytan o ilosc danych

 //otwieramy plik
 if ((plik = fopen(astrcon(save->pszPath,astrwrd(save->pszCddbStr,3)),
                   "wb"))==NULL) //otwieramy plik
  {
    //nie udalo sie
    rc=ERR_CDDB_FILEOPENFAILED; //i zwracamy blad
  };

  faza=CDDB_VALNAME_OTHER;//ktora faza parsingu

  //dopoki nie ma zadnych bledow, ani nie wyszlismy poza zakres...
  while ((rc==0)&&(faza!=10))
  {
     switch (faza)
     {
       case CDDB_VALNAME_OTHER:
         rc=_CddbSaveField(save,faza,0,"# ","\n",plik,FALSE);
         faza=CDDB_VALNAME_CDDBID;
         break;
       case CDDB_VALNAME_CDDBID:
          rc=_CddbSaveField(save,faza,0,"DISCID=","\n",plik,FALSE);
         faza=CDDB_VALNAME_ARTIST;
         break;
       case CDDB_VALNAME_ARTIST:
          rc=_CddbSaveField(save,faza,0,"DTITLE="," \\",plik,FALSE);
         faza=CDDB_VALNAME_TITLE;
         break;
       case CDDB_VALNAME_TITLE:
          rc=_CddbSaveField(save,faza,0,"","\n",plik,FALSE);
         faza=CDDB_VALNAME_TTITLE;
         break;
       case CDDB_VALNAME_TTITLE:
          rc=_CddbSaveField(save,faza,0,"TTITLE=","\n",plik,TRUE);
         faza=CDDB_VALNAME_EXTD;
         break;
       case CDDB_VALNAME_EXTD:
          rc=_CddbSaveField(save,faza,0,"EXTD=","\n",plik,FALSE);
         faza=CDDB_VALNAME_EXTT;
         break;
       case CDDB_VALNAME_EXTT:
          index=0;
          rc=_CddbQueryValueCount(faza,&index,&deep,save->lCdNum);
          for (licznik=1;licznik<=index;licznik++)//=0 (!)
           if (rc!=0) break; else
             rc=_CddbSaveField(save,faza,licznik,"EXTT=","\n",plik,TRUE);
         faza=CDDB_VALNAME_PLAYORDER;
         break;
       case CDDB_VALNAME_PLAYORDER:
          rc=_CddbSaveField(save,faza,0,"PLAYORDER=","\n",plik,FALSE);
         faza=10;
         break;
       default:
        rc=ERR_CDDB_WRONGDATA;
     }
  };  // while ((rc==0)&&(faza!=10))

  if (rc==0)
  {
    rc=fwrite(".\n",1,2,plik);
    if (rc<2) rc=ERR_CDDB_WRITEFAILED;
    //zamykamy plik
    fclose(plik);
   };

  //thhread konczy juz prace...
  cdCdTable[save->lCdNum].bQuit=TRUE;

  //zwalniamy semafor
  DosReleaseMutexSem(cdCdTable[save->lCdNum].hmtxSem);
  //jesli mamy gdzie i co wyslac - informujemy o zakonczeniu pytania
  if ((hwndCddbWin!=NULLHANDLE)&&(WM_CDDB!=0))
  //wysylamy informacje o zakonczeniu query, drugi parametr -> return code
  WinPostMsg(hwndCddbWin,WM_CDDB,MPFROM2SHORT(CDDB_WM_SAVE,rc),MPFROMLONG(save->lCdNum));
  _endthread();
};

LONG _CddbSaveField(CDDB_QUERY *save, int Pole,ULONG index,
                    char * prestr, char* poststr, FILE *plik,BOOL useCounter)
{
 ULONG deep,licznik,rozmiar,rc;
 char *buf,*bufwrt; //bufory na dane...
 char test[3]; //bufor dla itoa...

 //sprawdzamy czy jest jaksi atom dla tego pola
 rc=_CddbIsAtom(Pole,index,save->lCdNum);

 switch (rc)
 {
   case ERR_CDDB_OK: //jest atom, musimy zapisac dane
     //najpierw pytamy o ilosc danych..
     rc=_CddbQueryValueCount(Pole,&index,&deep,save->lCdNum);

     //w zaleznosci od tego ile ich jest bedziemy zapisywac...
     for (licznik=0;licznik<deep;licznik++)
     {
      //jaki rozmiar ma nasza dana?
      rc=_CddbQueryValueLength(Pole,index,licznik+1,save->lCdNum,&rozmiar);
      if (rc!=0) break; //jesli cos nawalilo to wyny...
      //malloc buf'a
      buf = (char *) malloc(rozmiar+1);
      //udalo sie?
      if (buf==NULL) { rc=ERR_CDDB_MEMALLOCFAILED; break;};
      //pobieramy wratosc
      rc=_CddbQueryValue(Pole,index,licznik+1,save->lCdNum,&buf,rozmiar);
      if (rc!=0) break; //jesli cos nawalilo to wyny...
       if (Pole==CDDB_VALNAME_EXTT)
           bufwrt=astrcon(astrcon(astrcon(astrcon(astrsbstr(prestr,0,
                  strlen(prestr)-1),itoa(index-1,test,10)) ,"="),buf),poststr);
        else
         if (useCounter==TRUE)
           bufwrt=astrcon(astrcon(astrcon(astrcon(astrsbstr(prestr,0,
                  strlen(prestr)-1),itoa(licznik,test,10)) ,"="),buf),poststr);
       else
      //laczymy z odpowiednim przedrostkiem..
      bufwrt=astrcon(astrcon(prestr,buf),poststr);
      free(buf);//to juz nie potrzebne
      //zapis
      rc=fwrite(bufwrt,1,strlen(bufwrt),plik);
      if (rc<strlen(bufwrt)) { rc=ERR_CDDB_WRITEFAILED; break;}
      else rc=0;
      free(bufwrt);
     }; //for (licznik=0;licznik<deep;licznik++)
     break;
   case ERR_CDDB_NOATOM: //nie ma atomu, zapisujemy tylko nazwe pola
       buf=""; //to by mozna zrobic inaczej, po prostu wyciac uzywanie buf'a...
       if (Pole==CDDB_VALNAME_EXTT)
           bufwrt=astrcon(astrcon(astrcon(astrcon(astrsbstr(prestr,0,
                  strlen(prestr)-1),itoa(index-1,test,10)) ,"="),buf),poststr);
        else
         if (useCounter==TRUE)
           bufwrt=astrcon(astrcon(astrcon(astrcon(astrsbstr(prestr,0,
                  strlen(prestr)-1),itoa(licznik,test,10)) ,"="),buf),poststr);
        else
      //laczymy z odpowiednim przedrostkiem..
       bufwrt=astrcon(astrcon(prestr,buf),poststr);
      //zapis
      rc=fwrite(bufwrt,1,strlen(bufwrt),plik);
      if (rc<strlen(bufwrt)) { rc=ERR_CDDB_WRITEFAILED; break;}
      else rc=ERR_CDDB_OK;
      free(bufwrt);
     break;
 };
  return rc;
};

LONG _CddbSetValue(int Pole,LONG index, ULONG cdNum, PSZ Wartosc)
{
 LONG rc;
 ATOM tmp=0; //tymzasowy atom
 CDDB_ATOM *tmp_atom; //wskazniki na struktury cddb atom
 CDDB_MULTIATOM *tmp_multiatom;
 HATOMTBL nowaTab; //miejsce na uchwyt pod ewentualna nowa tablice atomow

 //najpierw ustawiamy wskaznik na strukture cddb atom - potem juz bedziemy
 //operowac na tym samym typie danych
 switch (Pole)
 {
  case CDDB_VALNAME_CDDBID:
       tmp_atom=&cdCdTable[cdNum].caCddbId;
       break;
  case CDDB_VALNAME_ARTIST:
       tmp_atom=&cdCdTable[cdNum].caArtist;
       break;
  case CDDB_VALNAME_TITLE:
       tmp_atom=&cdCdTable[cdNum].caTitle;
       break;
  case CDDB_VALNAME_TTITLE:
       tmp_atom=&cdCdTable[cdNum].caTTitle;
       break;
  case CDDB_VALNAME_EXTD:
       tmp_atom=&cdCdTable[cdNum].caExtD;
       break;
  case CDDB_VALNAME_EXTT:
       tmp_multiatom=&cdCdTable[cdNum].cmaExtT;
       //index okresja dla ktorej scierzki podajemy informacje rozszerzone
        for (rc=1;rc<index;rc++)
        {
         //czy jest ta inna?
         if (tmp_multiatom->pNext==NULL)
         {
          //nie ma musimy dodac..
          tmp_multiatom->pNext = (CDDB_MULTIATOM *) malloc (sizeof(CDDB_MULTIATOM));
          //sprawdzamy czy pamiec sie zaalokowala
          if (tmp_multiatom->pNext==NULL)
             return ERR_CDDB_MEMALLOCFAILED;
          //przechodzimy do nowej struktury
          tmp_multiatom=tmp_multiatom->pNext;
          //i zerujemy ja
          tmp_multiatom->pNext=NULL;
          tmp_multiatom->caAtom.atomV=0;
          tmp_multiatom->caAtom.pNext=NULL;
         } else //jest wiec po prostu przejdzmy tam
           tmp_multiatom=tmp_multiatom->pNext;
        };//END for (rc=1;rc<=index;rc++)
       tmp_atom=&tmp_multiatom->caAtom;
       break;
  case CDDB_VALNAME_PLAYORDER:
       tmp_atom=&cdCdTable[cdNum].caPlayOrder;
       break;
  case CDDB_VALNAME_OTHER:
       tmp_atom=&cdCdTable[cdNum].caOther;
       break;
  default:
   return ERR_CDDB_WRONGFIELD;
 };

 //dopoki nasz tymczasowy atom jest zerowy...
 while (tmp==0)
 {
   if (cdCdTable[cdNum].bQuit==TRUE) return ERR_CDDB_ABORTED;
  //sprawdzamy czy atom na obecnym poziomie listy jest pusty
  if (tmp_atom->atomV==0)
  {
    //jest pusty - wypelniamy go
    //probojmy go dodac do ktorejs z tablic
    for (rc=0;rc<iAtomTablesCnt;rc++)
      if ((tmp=WinAddAtom(hatomtblAtomy[rc],Wartosc))!=0)
      {
       tmp_atom->atomV=tmp; //zapamietujemy go
       tmp_atom->cAtomTableIndex=rc; //i index do tablicy atomow..
       break; // i wyskakujem z tej petli
      };
    if (tmp==0) //nadal nie dodany?
    {
     //wiec probojemy go dodac do nowej tablicy..
     nowaTab=WinCreateAtomTable(0,0);
     //czy udalo sie stworzyc nowa tablice?
     if (nowaTab==NULLHANDLE) return ERR_CDDB_ATBLCREATEFAILED;
     //znow probojemy dodac
     if ((tmp=WinAddAtom(nowaTab,Wartosc))==0)
     { //znow nie wyszlo - wiec nie wyjdzie w ogole
       WinDestroyAtomTable(nowaTab);
       return ERR_CDDB_ATOMADDFAILED;
     } else //udalo sie :)
     {
       //musimy zablokowac dostep do tablicy atomow
       rc=DosRequestMutexSem(hmtxAtoms,500);
       if (rc!=0)
       { //nie udalo sie..
         WinDeleteAtom(nowaTab,tmp);
         WinDestroyAtomTable(nowaTab);
         return ERR_CDDB_SEMREQFAILED;
       };
       //zmieniamy rozmiar tablicy na uchwyty tablic atomow
       hatomtblAtomy=(HATOMTBL *) realloc (hatomtblAtomy,++iAtomTablesCnt);
       //czy sie udalo?
       if (hatomtblAtomy==NULL)
       {
        DosReleaseMutexSem(hmtxAtoms);
        WinDeleteAtom(nowaTab,tmp);
        WinDestroyAtomTable(nowaTab);
        return ERR_CDDB_MEMALLOCFAILED;
       };
       //dopisujemy uchwyt nowo utworzonej tablicy atomow
       hatomtblAtomy[iAtomTablesCnt-1]=nowaTab;
       //zapamietujemy atom
       tmp_atom->atomV=tmp;
       //i w ktorej tablicy jest
       tmp_atom->cAtomTableIndex=iAtomTablesCnt-1;
     };//END if ((tmp=WinAddAtom(nowTab,Wartosc))==0)
    };//END if (tmp==0) //nadal nie dodany?
  } else //nie jest, musimy przejsc poziom nizej
    //czy jest jakis poziom nizej?
    if (tmp_atom->pNext==NULL)
    {
      //nie ma, musimy go stworzyc
      //najpierw alokujemy pamiec pod niego
      tmp_atom->pNext = (CDDB_ATOM *)malloc(sizeof(CDDB_ATOM));
      //jesli sie nie udalo no to sorry...
      if (tmp_atom->pNext==NULL) return ERR_CDDB_MEMALLOCFAILED;
      //przechodzimy do niego
      tmp_atom=tmp_atom->pNext;
      //i ustawiamy poczatkowe wartosci
      tmp_atom->pNext=NULL;
      tmp_atom->atomV=0;
      tmp_atom->cAtomTableIndex=0;
    } else //jest - przechodzimy
      tmp_atom=tmp_atom->pNext;
 }; //end of while (tmp==0)

 return ERR_CDDB_OK;
};

void _CddbQuery(CDDB_QUERY * query)
{
  ULONG rc=0;
  char *bufor; //bufor na dane
  ULONG size=15*80; //poczatkowy rozmiar bufora

  ////
  cdCdTable[query->lCdNum].bQuit=FALSE;
 /////

  bufor = (char *) malloc (size); //alokujemy pamiec
  if (bufor==NULL) rc=ERR_CDDB_MEMALLOCFAILED;
  if (rc==0) //jesli wszystko poszlo ok...
  {
    switch (query->bScope)
    {
     case CDDB_SCOPE_REMOTE:
       if (acddbtcp!=NULLHANDLE)
        rc=_CddbQueryRemote(query,bufor,&size,&cdCdTable[query->lCdNum].bQuit);
       else rc=ERR_CDDB_DLLLOADFAILED;
       break;
     case CDDB_SCOPE_LOCAL:
       rc = _CddbQueryLocal(query,bufor,&size); break;
     case CDDB_SCOPE_ALL:
       rc =  _CddbQueryLocal(query,bufor,&size);
       if (rc!=0) 
        {
          if (acddbtcp!=NULLHANDLE) rc=_CddbQueryRemote(query,bufor,&size,
                    &cdCdTable[query->lCdNum].bQuit); else
              rc=ERR_CDDB_DLLLOADFAILED;
        };
       break;
     default:
       rc=ERR_CDDB_INVALIDSCOPE;
    };
  };
  if (rc==ERR_CDDB_OK) rc=_CddbParse(query,bufor,size); else
      if (rc!=ERR_CDDB_ABORTED) rc=ERR_CDDB_CDNOTFOUND;

  if (rc!=0) _CddbInvalidateEntry(&cdCdTable[query->lCdNum]); else
   {
   cdCdTable[query->lCdNum].bIsValid=TRUE;
   cdCdTable[query->lCdNum].bQuit=TRUE;
   };
  //zwalniamy semafor
  DosReleaseMutexSem(cdCdTable[query->lCdNum].hmtxSem);
  //jesli mamy gdzie i co wyslac - informujemy o zakonczeniu pytania
  if ((hwndCddbWin!=NULLHANDLE)&&(WM_CDDB!=0))
  //wysylamy informacje o zakonczeniu query, drugi parametr -> return code
  WinPostMsg(hwndCddbWin,WM_CDDB,MPFROM2SHORT(CDDB_WM_SAVE,rc),MPFROMLONG(query->lCdNum));
  _endthread(); 
};

LONG _CddbQueryLocal(CDDB_QUERY * query,char *bufor, ULONG *rozmiar)
{
 int ile; //ile zsotalo odczytane z pliku (zwraca fread)
 int wsk;
 ULONG i; //akutalna pozycja w buforze
 char *buf; //bufor na jedna linie
 FILE *plik; //wskaznik na strumien

 buf = (char *) malloc (80); //alokujemy pamiec pod bufor do odczytu
 //jesli sie nie udalo...
 if (buf==NULL) return ERR_CDDB_MEMALLOCFAILED;

 if ((plik = fopen(astrcon(query->pszPath,astrwrd(query->pszCddbStr,3)),
                   "rb"))==NULL) //otwieramy plik
  {
    //nie udalo sie
    free(buf);  //zawalniamy zaalokowana przez nas pamiec
    return ERR_CDDB_FILEOPENFAILED; //i zwracamy blad
  };

  ile=fread(buf, 1, 80, plik);
  if (ferror(plik)) //sprawdzamy czy byl moze blad odczytu..?
   {
    free(buf);
    fclose(plik);
    return ERR_CDDB_FILEREADERR;
   } else
  if feof(plik) //a moze koniec pliku?
   {
    free(buf);
    fclose(plik);
    return ERR_CDDB_WRONGDATA;
   };
   //jako ze wczytalismy pierwsza linie - sprawdzamy czy jest to plik bazy cddb
   if ( (buf[0]!='#') || (strcmpi(XMCD,astrwrd(buf,2))!=0))
   {
    free(buf);
    fclose(plik);
    return ERR_CDDB_WRONGDATA;
   };
   for (i=0;i<ile;i++) bufor[i]=buf[i]; //przepisujemy zawarosc do bufora...

   do
   {
     //musimy sprawdic czy czasem nie powinnismy wyjsc z threada?
     if (cdCdTable[query->lCdNum].bQuit==TRUE)
     {
        free(buf);
        fclose(plik);
        return ERR_CDDB_ABORTED;
     };
     //odczytujemy po 80 bajtow
     ile=fread(buf, 1, 80, plik);
     //jesli odczytalismy mniej niz powinnismy
     if (ile<80)
      {
       if (ferror(plik)) //sprawdzamy czy byl moze blad odczytu..?
       {
        free(buf);
        fclose(plik);
        return ERR_CDDB_FILEREADERR;
       };
     }; //end of if (ile==0)
     //sprawdzamy czy nam sie to zmiesci w buforze..
     if (i+ile>*rozmiar)
      {
       *rozmiar+=80; //zwiekszamy o bufor na jedna linie
       bufor = (char *) realloc(bufor, *rozmiar);//i realloc
       if (bufor==NULL)
          {
           free(buf);
           fclose(plik);
           return ERR_CDDB_MEMALLOCFAILED;
          };
      };
     //przepisujemy do bufora
     for (wsk=0;wsk<ile;wsk++) bufor[i++]=buf[wsk];
   } while (ile!=0);

  *rozmiar=i; //zwracamy ile jest danych w tablicy

  fclose(plik); //zamykamy plik
  free(buf); //zwalniamy pamiec

 return ERR_CDDB_OK;
};

LONG _CddbQueryValue(int Pole, LONG index, LONG deep, ULONG cdNum,
                          PSZ *Wartosc, ULONG ulBufSize)
{
 ULONG rc;
 CDDB_ATOM *tmp_atom;
 CDDB_MULTIATOM *tmp_multiatom;

 switch (Pole)
 {
  case CDDB_VALNAME_CDDBID:
       tmp_atom=&cdCdTable[cdNum].caCddbId;
       break;
  case CDDB_VALNAME_ARTIST:
       tmp_atom=&cdCdTable[cdNum].caArtist;
       break;
  case CDDB_VALNAME_TITLE:
       tmp_atom=&cdCdTable[cdNum].caTitle;
       break;
  case CDDB_VALNAME_TTITLE:
       tmp_atom=&cdCdTable[cdNum].caTTitle;
       break;
  case CDDB_VALNAME_EXTD:
       tmp_atom=&cdCdTable[cdNum].caExtD;
       break;
  case CDDB_VALNAME_EXTT:
       tmp_multiatom=&cdCdTable[cdNum].cmaExtT;
       //index okresja dla ktorej scierzki pobieramy dane
        for (rc=1;rc<index;rc++)
         if (tmp_multiatom->pNext==NULL)
         {
           return ERR_CDDB_INDEXOUTOFRANGE;
         } else tmp_multiatom=tmp_multiatom->pNext;
       tmp_atom=&tmp_multiatom->caAtom;
       break;
  case CDDB_VALNAME_PLAYORDER:
       tmp_atom=&cdCdTable[cdNum].caPlayOrder;
       break;
  case CDDB_VALNAME_OTHER:
       tmp_atom=&cdCdTable[cdNum].caOther;
       break;
  default:
   return ERR_CDDB_WRONGFIELD;
 };

 //teraz osiagamy zadana glebokosc
 for (rc=1;rc<deep;rc++)
   if (tmp_atom->pNext==NULL)
   {
    return ERR_CDDB_DEEPOUTOFRANGE;
   } else tmp_atom=tmp_atom->pNext;
  //czy jest sie w ogole o co pytac?
  if (tmp_atom->atomV==0)
  {
   return ERR_CDDB_NOATOM;
  };
  //i juz mozemy sie spokojnie zapytac
  rc=WinQueryAtomName(hatomtblAtomy[tmp_atom->cAtomTableIndex],
                              tmp_atom->atomV,*Wartosc,ulBufSize);
  if (rc==0) return ERR_CDDB_ATOMQUERYFAILED;

  return ERR_CDDB_OK;
};

LONG _CddbQueryValueCount(int Pole, ULONG * index, ULONG * deep, ULONG cdNum)
{
 ULONG rc;
 CDDB_ATOM *tmp_atom;
 CDDB_MULTIATOM *tmp_multiatom;

 *deep=1; //na razie glebokosc jest rowna 1

 switch (Pole)
 {
  case CDDB_VALNAME_CDDBID:
       tmp_atom=&cdCdTable[cdNum].caCddbId;
       break;
  case CDDB_VALNAME_ARTIST:
       tmp_atom=&cdCdTable[cdNum].caArtist;
       break;
  case CDDB_VALNAME_TITLE:
       tmp_atom=&cdCdTable[cdNum].caTitle;
       break;
  case CDDB_VALNAME_TTITLE:
       tmp_atom=&cdCdTable[cdNum].caTTitle;
       break;
  case CDDB_VALNAME_EXTD:
       tmp_atom=&cdCdTable[cdNum].caExtD;
       break;
  case CDDB_VALNAME_PLAYORDER:
       tmp_atom=&cdCdTable[cdNum].caPlayOrder;
       break;
  case CDDB_VALNAME_OTHER:
       tmp_atom=&cdCdTable[cdNum].caOther;
       break;
  case CDDB_VALNAME_EXTT:
       tmp_multiatom=&cdCdTable[cdNum].cmaExtT;
       //jesli jest podany niezerowy index, to wchodzimy w strukture dla
       //odpowiedniej scierzki
       if (*index!=0)
       {
       //index okresja dla ktorej scierzki pobieramy dane
        for (rc=1;rc<*index;rc++)
         if (tmp_multiatom->pNext==NULL)
                return ERR_CDDB_INDEXOUTOFRANGE;
          else tmp_multiatom=tmp_multiatom->pNext;
         tmp_atom=&tmp_multiatom->caAtom;
       } else //index jest zerowy - pytamy sie o ilosc scierzek z informacja
       {      //rozszerzona
        *index=1;
        while (tmp_multiatom->pNext!=NULL)
        {
         tmp_multiatom=tmp_multiatom->pNext; //zaglebiamy sie
         *index+=1; //i zwiekszamy licznik glebokosci
        };
        *deep=0;
        return ERR_CDDB_OK;
       }; //END if (*index!=0)
       break;
  default:
   return ERR_CDDB_WRONGFIELD;
 };
 //dopoki jest w co sie zaglebiac
 while (tmp_atom->pNext!=NULL)
 {
  tmp_atom=tmp_atom->pNext; //zaglebiamy sie
  *deep+=1; //i zwiekszamy licznik glebokosci
 };
 return ERR_CDDB_OK;
};

LONG _CddbQueryValueLength(int Pole, LONG index, LONG deep, ULONG cdNum,
                          ULONG *rozmiar)
{
 LONG rc;
 CDDB_ATOM *tmp_atom;
 CDDB_MULTIATOM *tmp_multiatom;

 switch (Pole)
 {
  case CDDB_VALNAME_CDDBID:
       tmp_atom=&cdCdTable[cdNum].caCddbId;
       break;
  case CDDB_VALNAME_ARTIST:
       tmp_atom=&cdCdTable[cdNum].caArtist;
       break;
  case CDDB_VALNAME_TITLE:
       tmp_atom=&cdCdTable[cdNum].caTitle;
       break;
  case CDDB_VALNAME_TTITLE:
       tmp_atom=&cdCdTable[cdNum].caTTitle;
       break;
       case CDDB_VALNAME_EXTD:
       tmp_atom=&cdCdTable[cdNum].caExtD;
       break;
  case CDDB_VALNAME_EXTT:
       tmp_multiatom=&cdCdTable[cdNum].cmaExtT;
       //index okresja dla ktorej scierzki pobieramy dane
        for (rc=1;rc<index;rc++)
         if (tmp_multiatom->pNext==NULL)
         {
          return ERR_CDDB_INDEXOUTOFRANGE;
         } else tmp_multiatom=tmp_multiatom->pNext;
       tmp_atom=&tmp_multiatom->caAtom;
       break;
  case CDDB_VALNAME_PLAYORDER:
       tmp_atom=&cdCdTable[cdNum].caPlayOrder;
       break;
  case CDDB_VALNAME_OTHER:
       tmp_atom=&cdCdTable[cdNum].caOther;
       break;
  default:
   return ERR_CDDB_WRONGFIELD;
 };

 //teraz osiagamy zadana glebokosc
 for (rc=1;rc<deep;rc++)
   if (tmp_atom->pNext==NULL)
        return ERR_CDDB_DEEPOUTOFRANGE;
    else
     tmp_atom=tmp_atom->pNext;
  //czy jest sie w ogole o co pytac?
  if (tmp_atom->atomV==0)
       return ERR_CDDB_NOATOM;
  //i juz mozemy sie spokojnie zapytac
  *rozmiar=WinQueryAtomLength(hatomtblAtomy[tmp_atom->cAtomTableIndex],
                              tmp_atom->atomV);
  if (*rozmiar==0)
     return ERR_CDDB_ATOMQUERYFAILED;
 return ERR_CDDB_OK;
};


LONG _CddbLinkDll()
{
 LONG rc;
 //ladujemy dll'a odpowiedzialego za siec
 rc=DosLoadModule(NULL,0L,"acddbtcp",&acddbtcp);
 if (rc!=0)
  {
   acddbtcp=NULLHANDLE;
   return ERR_CDDB_DLLLOADFAILED;
  };
 //pobieramy funkcje...
 rc = DosQueryProcAddr(acddbtcp,0L,"CDDBSOCKINIT",&CddbSockInit);
 if (rc!=0)
  {
   _CddbFreeDll();
   return ERR_CDDB_QUERYPROCFAILED;
  };
  rc = DosQueryProcAddr(acddbtcp,0L,"_CDDBQUERYREMOTE",&_CddbQueryRemote);
 if (rc!=0)
  {
   _CddbFreeDll();
   return ERR_CDDB_QUERYPROCFAILED;
  };
 return ERR_CDDB_OK;
};

void _CddbFreeDll()
{
  if (acddbtcp!=NULLHANDLE) DosFreeModule(acddbtcp);
  acddbtcp=NULLHANDLE;
};
