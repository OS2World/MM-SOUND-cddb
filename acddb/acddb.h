/* ===============================================================
   Warp CD-Copy <prototyp>
   =======================

    $RCSfile: acddb.h,v $
      Author: Bartosz_Tomasik <bart2@asua.org.pl>
       $Date: 1999/10/02 14:00:05 $
   $Revision: 1.1 $
      $State: Exp $
       Notes: Modul obslugi cddb

 Copyright ¸ 1999 Asu'a (http://www.asua.org.pl)
================================================================== */
#ifndef __ACDDB_H__
#define __ACDDB_H__

#define INCL_WINATOM
#define INCL_DOSMODULEMGR
#define INCL_DOSSEMAPHORES
#include <os2.h>

//stale okreslajace zakres pytania
#define CDDB_SCOPE_REMOTE  0 //szukamy tylko w bazie na sieci
#define CDDB_SCOPE_LOCAL   1 //szukamy tylko w lokalnej bazie
#define CDDB_SCOPE_ALL     2 //szukamy w obu bazach (najpierw lokalnie)
#define CDDB_SCOPE_LOCAL_DEEP   11 //szukamy tylko w lokalnej bazie
                                   //ale "gleboko" - patrz dokumentacja
#define CDDB_SCOPE_ALL_DEEP     12 //szukamy w obu bazach (najpierw lokalnie
                                   // - "gleboko")


//stale zakonczenia watkow - wysylane w pierwszym parametrze WM_CDDB
#define CDDB_WM_QUERY 1
#define CDDB_WM_SAVE 2

//stale uzywane do nazywania pol
#define CDDB_VALNAME_CDDBID     1
#define CDDB_VALNAME_ARTIST     2
#define CDDB_VALNAME_TITLE      3
#define CDDB_VALNAME_TTITLE     4
#define CDDB_VALNAME_EXTD       5
#define CDDB_VALNAME_EXTT       6
#define CDDB_VALNAME_PLAYORDER  7
#define CDDB_VALNAME_OTHER      8

//Bledy
#define ERR_CDDB_OK               0 //wszystko jest ok
#define ERR_CDDB_ABORTED          1 //akcja przerwana przez uzytwkonika
#define ERR_CDDB_ALREADYDONE      2 //funkcja wykonala zadanie przy poprzednim
                                    // wywolaniu
#define ERR_CDDB_ATBLCREATEFAILED 3 //tworzenie tablicy atomow nie powiodlo sie
#define ERR_CDDB_ATOMADDFAILED    4 //atom nie dodany
#define ERR_CDDB_ATOMQUERYFAILED  5 //pytanie o atom nie udalo sie
#define ERR_CDDB_CDNOTFOUND       6 //nie znaleziono cd w bazie
#define ERR_CDDB_CONNECTFAILED    7 //polaczenie nie powiodlo sie..
#define ERR_CDDB_DATANOTVALID     8 //dane sa bledne/nie wazne
#define ERR_CDDB_DEEPOUTOFRANGE   9 //glebokosc poza zakresem
#define ERR_CDDB_DLLLOADFAILED   10 //nie zaladowalismy dll'a...
#define ERR_CDDB_DNSFAILED       11 //nie dalo sie zamienic nazwy na ip..
#define ERR_CDDB_FILEOPENFAILED  12 //nie udalo sie otworzyc pliku
#define ERR_CDDB_FILEREADERR     13 //blad odczytu pliku
#define ERR_CDDB_INDEXOUTOFRANGE 14 //index poza zakrsem
#define ERR_CDDB_INVALIDSCOPE    15 //bledny zakres szukania
#define ERR_CDDB_MEMALLOCFAILED  16 //nie mozna zaalokowac pamieci
#define ERR_CDDB_MODINUSE        17 //modul w uzyciu!
#define ERR_CDDB_MODNOTINIT      18 //modul nie jest zainicjalizowany
#define ERR_CDDB_NOATOM          19 //nie ma atomu
#define ERR_CDDB_OUTOFRANGE      20 //funkcja probowala sie odwolac do danej 
                                    // poza zakresem
#define ERR_CDDB_QUERYPROCFAILED 21 //pobranie funkjci z dlla sie wykrzaczylo..
#define ERR_CDDB_RECVFAILED      22 //odbior nie powiodl sie..
#define ERR_CDDB_SEMCREATEFAIL   23 //tworzenie semafora nie powiodlo sie
#define ERR_CDDB_SEMQUERYFAILED  24 //pytanie o semafor nie powiodlo sie
#define ERR_CDDB_SEMREQFAILED    25 //podniesienie semafora nie powiodlo sie
#define ERR_CDDB_SENDFAILED      26 //wyslanie nie powiodlo sie
#define ERR_CDDB_SETSOCKFAILED   27 //ustawienie typu interfejsu nie wyszlo
#define ERR_CDDB_SOCKINITFAILED  28 //inicjalizacja socketu... nie wyszla
#define ERR_CDDB_THRCREATEFAILED 29 //nie udalo sie stworzyc nowego watku!
#define ERR_CDDB_WRITEFAILED     30 //blad zapisu do pliku
#define ERR_CDDB_WRONGDATA       31 //bledne dane
#define ERR_CDDB_WRONGFIELD      32 //bledny numer pola

//struktura opisujaca zapytanie o CD
typedef struct
{
 PSZ pszCddbStr; //ciag znakow dla komendy Query (zawiera cddb id)
 PSZ pszPath;    //sciezka do lokalnej bazy danych
 PSZ pszServer;  //nazwa servera cddb
 LONG lPort;    //port servera cddb
 ULONG lCdNum;   //numer CD ktorego dotyczy zapytanie
 BYTE bScope;   //zakres pytania - patrz stale CDDB_SCOPE_*
 PSZ Username;
 PSZ Hostname;
 PSZ Clientame;
 PSZ Version;
} CDDB_QUERY;


LONG CddbInitialize(ULONG drives, ULONG wm_cddb, HWND hwndCddb);
LONG CddbCancelAction(ULONG cdNum);
LONG CddbCreateQuery(CDDB_QUERY query);
LONG CddbQueryValue(int Pole, LONG index, LONG deep, ULONG cdNum,
                          PSZ *Wartosc,ULONG ulBufSize);
LONG CddbQueryValueCount(int Pole, ULONG *index, ULONG *deep, ULONG cdNum);
LONG CddbQueryValueLength(int Pole, LONG index, LONG deep, ULONG cdNum,
                          ULONG *rozmiar);
LONG CddbSave(CDDB_QUERY save);
LONG CddbTerminate(ULONG ulTimeOut);

#endif /* __ACDDB_H__ */
