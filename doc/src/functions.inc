.* modul CDDB
.* Rozdzia� 4 "Funkcje"
.*
:h1 res=004.Funkcje modulu CDDB
:p.Zestw funkcji umo�liwia znalezienie CD w bazie na sieci i/lub na dysku oraz
p��niejszy dost�p do odczytanych danych.


.* Funkcja "CddbCancelAction"
.*
:h2 x=left width=25% scroll=none clear name=CddbCancelAction.CddbCancelAction
:link dependent group=40 reftype=hd auto refid=CddbCancelAction_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbCancelAction_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbCancelAction_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbCancelAction_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbCancelAction_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbCancelAction_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbCancelAction_S.Sk�adnia - CddbCancelAction
:cgraphic.
/******************************************/
/* Anulowanie pytania o CD lub zapisu.    */
/******************************************/

#include "accdb.h"

ULONG   ulCDNum;    // Logiczny numer nap�du

LONG CddbCancelAction(ULONG ulCdNum);
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbCancelAction_P.Parametry - CddbCancelAction
:dl tsize=3 break=all.
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap�du.
:p. Nap�dy numerowane s� od 1.
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbCancelAction_E.B��dy - CddbCancelAction
Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ALREADYDONE
:dd.Flaga zako�czenia pytania jest ju� ustawiona.
:dt.ERR_CDDB_OUTOFRANGE
:dd.Podany numer nap�du znajduje si� poza zakresem.
:dt.ERR_CDDB_MODINUSE
:dd.Modu� wykonuje inn� funkcj� uniemo�liwiaj�c� wykonanie zadania.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjowany.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr�ba sprawdzenia semafora nie powiod�a si�.
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbCancelAction_N.Opis - CddbCancelAction
:p.Funkcja ustawia flag� informuj�c� w�tek pytaj�cy/zapisuj�cy o konieczno�ci
zako�czenia pracy. O zako�czeniu pracy w�tku, modu� zawiadomi wysy�aj�c
komunikat :link reftype=hd refid=WM_CDDB.WM_CDDB:elink..

.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbCancelAction_R.Funkcje dodatkowe - CddbCancelAction
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbCreateQuery.CddbCreateQuery:elink.
:li.:link reftype=hd refid=CddbInitialize.CddbInitialize:elink.
:eul.

.* Funkcja "CddbCreateQuery"
.*
:h2 x=left width=25% scroll=none clear name=CddbCreateQuery.CddbCreateQuery
:link dependent group=40 reftype=hd auto refid=CddbCreateQuery_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbCreateQuery_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbCreateQuery_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbCreateQuery_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbCreateQuery_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbCreateQuery_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbCreateQuery_S.Sk�adnia - CddbCreateQuery
:cgraphic.
/******************************************/
/* Pytanie o CD.                          */
/******************************************/

#include "accdb.h"

CDDB_QUERY   query;    //struktura opisuj�ca zapytanie i/lub zapis

LONG CddbCreateQuery(CDDB_QUERY query);
:ecgraphic.

.* PARAMETRY
:h2 x=60% width=40% hide name=CddbCreateQuery_P.Parametry - CddbCreateQuery
:dl tsize=3 break=all.
:dt.:hp2.query:ehp2. (:link reftype=hd vpcx=100% refid=CDDB_QUERY.CDDB_QUERY:elink.) - parametr.
:dd. Struktura opisuj�ca zapytanie, u�uwana tak�e przy zapisie.
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbCreateQuery_E.B��dy - CddbCreateQuery
Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_MODINUSE
:dd.Modu� wykonuje inn� funkcj� uniemo�liwiaj�c� wykonanie zadania.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjowany.
:dt.ERR_CDDB_SEMREQFAILED
:dd.Pr�ba zablokowania semafora nie powiod�a si�.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr�ba sprawdzenia semafora nie powiod�a si�.
:dt.ERR_CDDB_THRCREATEFAILED
:dd.Pr�ba utworzenia w�tku pytaj�cego nie powiod�a si�..
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbCreateQuery_N.Opis - CddbCreateQuery
:p.Funkcja rozpoczyna w�tek pytaj�cy o CD, dane wej�ciowe zapytania przekazywane s� jako parametr.
O zako�czeniu pracy w�tku, modu� zawiadomi wysy�aj�c komunikat
:link reftype=hd refid=WM_CDDB.WM_CDDB:elink.

.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbCreateQuery_R.Funkcje dodatkowe - CddbCreateQuery
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbCancelAction.CddbCancelAction:elink.
:eul.


.* Funkcja "CddbInitialize"
.*
:h2 x=left width=25% scroll=none clear name=CddbInitialize.CddbInitialize
:link dependent group=40 reftype=hd auto refid=CddbInitialize_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbInitialize_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbInitialize_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbInitialize_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbInitialize_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbInitialize_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbInitialize_S.Sk�adnia - CddbInitialize
:cgraphic.
/******************************************/
/* Inicjacja modu�u interfejsu cddb.      */
/******************************************/

#include "acddb.h"

ULONG drives; //liczba nap�d�w CD w systemie
ULONG wm_cddb;//kod notyfikacji
HWND hwndCddb;//uchwyt okna do kt�rego b�dzie wysy�ana notyfikacja

LONG CddbInitialize(ULONG drives, ULONG wm_cddb, HWND hwndCddb);
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbInitialize_P.Parametry - CddbInitialize
:dl tsize=3 break=all.
:dt.:hp2.drives:ehp2. (ULONG) - - parametr.
:dd. Liczba nap�d�w w systemie.
:p. U�ytkownik mo�e poda� inn� ni� rzeczywista liczb� nap�d�w w systemie
(u�ywane do tworzenia miejsca w pami�ci pod dane cddb),
pami�taj�c jednak aby podczas p��niejszej pracy z modu�em wszystkie warto�ci
numeru nap�du CD, mie�ci�y si� w podej przez niego granicy.
:dt.:hp2.wm_cddb:ehp2. (ULONG) - - parametr.
:dd. Kod komunikatu WM_CDDB.
:p. U�ytkownik mo�e poda� odpowiadaj�cy mu kod komunikatu WM_CDDB.
:dt.:hp2.hwndCddb:ehp2. (ULONG) - - parametr.
:dd. Uchwyt okna do kt�rego b�dzie wysy�any komunikat WM_CDDB.
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbInitialize_E.B��dy - CddbInitialize
:p.Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ALREADYDONE
:dd.Modu� ju� zosta� zainicjalizowany.
:dt.ERR_CDDB_ATBLCREATEFAILED
:dd.Tworzenie tablicy atom�w nie powiod�o si�.
:dt.ERR_CDDB_DLLLOADFAILED
:dd.Nie uda�o si� za�adowa� biblioteki dll odpowiedzialnej za cz��� sieciow� 
modu�u
:dt.ERR_CDDB_MEMALLOCFAILED
:dd.Alokacja pami�ci nie powiod�a si�.
:dt.ERR_CDDB_QUERYPROCFAILED
:dd.Pobranie funkcji z biblioteki dll, nie powiod�o si�.
:dt.ERR_CDDB_SEMCREATEFAILED
:dd.Tworzenie semafora nie powiod�o si�.
:dt.ERR_CDDB_SOCKINITFAILED
:dd.Inicjalizacja wsp��pracy z siecia nie powiod�a si�.
:dt.ERR_CDDB_TCPFAILED
:dd.Wczytanie acddbtcp.dll nie powiod�o si�.
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbInitialize_N.Opis - CddbInitialize
:p.Funkcja inicjuje modu� interfejsu cddb. Nale�y jej u�y� przd wywo�aniem
jakiejkolwiek innej funkcji modu�u.
:p.Funkcja alokuje pami�� pod dane cddb dla drives nap�d�w, zapami�tuje kod
komunikatu CDDB oraz uchwyt okna odbiorcy oraz pr�buje wczyta� bibliotek�,
odpowiedzialn� za cz��� sieciow� poszukiwa�. W razie b��du inicjalizacji funcja
usuwa '�mieci' po sobie. 
:warning.Nie wczytanie obs�ugi tcp nie przerywa inicjalizacji modu�u.


.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbInitialize_R.Funkcje dodatkowe - CddbInitialize
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbTerminate.CddbTerminate:elink.
:eul.



.* Funkcja  CddbQueryValue
.*
:h2 x=left width=25% scroll=none clear name=CddbQueryValue.CddbQueryValue
:link dependent group=40 reftype=hd auto refid=CddbQueryValue_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbQueryValue_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbQueryValue_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbQueryValue_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbQueryValue_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbQueryValue_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbQueryValue_S.Sk�adnia - CddbQueryValue
:cgraphic.
/******************************************/
/* Pytanie o warto�ci danych.             */
/******************************************/

#include "accdb.h"

int Pole; //stala z rodziny CDDB_VALNAME_ okreslajaca pole
LONG index; //index �cierzki jesli pytamy o dane rozszerzone dla �cierzek
LONG deep;  //"g��boko�c" danej
ULONG cdNum; //logiczny numer napedu
PSZ Wartosc; //bufor na dane
ULONG ulBufSize; //rozmiar bufora

LONG CddbQueryValue(int Pole, LONG index, LONG deep, ULONG cdNum,
                    PSZ *Wartosc, ULONG ulBufSize)
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbQueryValue_P.Parametry - CddbQueryValue
:dl tsize=3 break=all.
:dt.:hp2.Pole:ehp2. (int) - parametr
:dd. okre�la o kt�re pole si� pytamy (sta�e z rodziny CDDB_VALNAME) (!)
:dt.:hp2.index:ehp2. (LONG) - parametr
:dd. u�ywane tylko w przypadku pyta� o informacj� rozszerzon� dla 
�cierzki (CDDB_VALNAME_EXTT), oznacza kt�rej �cierzki ma dotyczy� pytanie. 
W przypadku gdy Pole!=CDDB_VALNAME_EXTT warto�� index jest ignorowana.
:p. numery �cierzek zaczynaj� si� od 1
:dt.:hp2.deep:ehp2. (LONG) - parametr
:dd. oznacza g��boko�� danego pola (np je�li Pole=CDDB_VALNAME_TITLE to deep
oznacza do tytu�u kt�rej �cierzki sie odwo�ujemy)
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap�du.
:p. Nap�dy numerowane s� od 1.
:dt.:hp2.Wartosc:ehp2. (PSZ) - zwracane
:dd. bufor do kt�rego zostanie zapisany zwracany tekst
:dt.:hp2.ulBufSize:ehp2. (LONG) - parametr
:dd. rozmiar bufora na odczytan� warto��
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbQueryValue_E.B��dy - CddbQueryValue
Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ATOMQUERYFAILED
:dd.Pobranie warto�ci nie powiod�o si�.
:dt.ERR_CDDB_DEEPOUTOFRANGE
:dd.Podana g��boko�� jest poza zakresem.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany index jest poza zakresem.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjowany.
:dt.ERR_CDDB_NOATOM
:dd.Dla podanej g��boko�ci nie ma przypisanej �adnej warto�ci.
:dt.ERR_CDDB_SEMREQAILED
:dd.Pr�ba zablokowania semafora nie powiod�a si�
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr�ba sprawdzenia semafora nie powiod�a si�.
:dt.ERR_CDDB_WRONGDATA
:dd.Dane Cddb dla danego nap�du nie s� poprawne.
:dt.ERR_CDDB_WRONGFIELD
:dd.U�ytkownik poda� b��dn� sta�� okre�laj�c� pole
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbQueryValue_N.Opis - CddbQueryValue
:p.Funkcja zwraca tekst (w buforze Wartosc) dla danego pola o podanym indeksie
 i g��boko�ci przyporzadkowan� dla danego nap�du CD (okre�lone przez ulCdNum).


.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbQueryValue_R.Funkcje dodatkowe - CddbQueryValue
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbQueryValueCount.CddbQueryValueCount:elink.
:li.:link reftype=hd refid=CddbQueryValueLength.CddbQueryValueLength:elink.
:eul.

.* Funkcja "CddbQueryValueCount"
.*
:h2 x=left width=25% scroll=none clear name=CddbQueryValueCount.CddbQueryValueCount
:link dependent group=40 reftype=hd auto refid=CddbQueryValueCount_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbQueryValueCount_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbQueryValueCount_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbQueryValueCount_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbQueryValueCount_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbQueryValueCount_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbQueryValueCount_S.Sk�adnia - CddbQueryValueCount
:cgraphic.
/******************************************/
/* Pytanie o ilo�� danych.                */
/******************************************/

#include "accdb.h"

int Pole; //stala z rodziny CDDB_VALNAME_ okreslajaca pole
LONG index; //index �cierzki jesli pytamy o dane rozszerzone dla �cierzek
LONG deep;  //"g��boko�c" danej
ULONG cdNum; //logiczny numer napedu

LONG CddbQueryValueCount(int Pole, ULONG * index, ULONG * deep, ULONG cdNum)
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbQueryValueCount_P.Parametry - CddbQueryValueCount
:dl tsize=3 break=all.
:dt.:hp2.Pole:ehp2. (int) - parametr
:dd. okre�la o kt�re pole si� pytamy (sta�e z rodziny CDDB_VALNAME) (!)
:dt.:hp2.index:ehp2. (LONG) - parametr/zwracane
:dd. u�ywane tylko w przypadku pyta� o informacj� rozszerzon� dla 
�cierzki (CDDB_VALNAME_EXTT): je�li ustawione na 0 - pytamy si� o ilo�� p�l
z informacj� rozszerzon� dla �cierzek - po zako�czeniu warto�� ta zwracana jest
w index; je�li ustawione na konkretn� warto��, wtedy deep zwr�ci g��boko��
dla informacji rozszerzonej dla scierzki o numerze index.
W przypadku gdy Pole!=CDDB_VALNAME_EXTT warto�� index jest ignorowana.
:p. numery �cierzek zaczynaj� si� od 1
:dt.:hp2.deep:ehp2. (LONG) - zwracane
:dd. zwraca g��boko�� danego pola. Je�li Pole=CDDB_VALNAME_EXTT i index=0, deep
nic nie zwraca (zwracane jest wtedy tylko index).
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap�du.
:p. Nap�dy numerowane s� od 1.
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbQueryValueCount_E.B��dy - CddbQueryValueCount
Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany index jest poza zakresem.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjowany.
:dt.ERR_CDDB_SEMREQAILED
:dd.Pr�ba zablokowania semafora nie powiod�a si�
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr�ba sprawdzenia semafora nie powiod�a si�.
:dt.ERR_CDDB_WRONGDATA
:dd.Dane Cddb dla danego nap�du nie s� poprawne.
:dt.ERR_CDDB_WRONGFIELD
:dd.U�ytkownik poda� b��dn� sta�� okre�laj�c� pole
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbQueryValueCount_N.Opis - CddbQueryValueCount
:p.Funkcja zwraca ilo�� danych (g��boko�) dla danego pola (ewentualnie o 
podanym indeksie) lub ilo�� p�l z informacj� rozszerzon� dla �cierzek.

.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbQueryValueCount_R.Funkcje dodatkowe - CddbQueryValueCount
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbQueryValue.CddbQueryValue:elink.
:li.:link reftype=hd refid=CddbQueryValueLength.CddbQueryValueLength:elink.
:eul.

.* Funkcja "CddbQueryValueLength"
.*
:h2 x=left width=25% scroll=none clear name=CddbQueryValueLength.CddbQueryValueLength
:link dependent group=40 reftype=hd auto refid=CddbQueryValueLength_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbQueryValueLength_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbQueryValueLength_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbQueryValueLength_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbQueryValueLength_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbQueryValueLength_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbQueryValueLength_S.Sk�adnia - CddbQueryValueLength
:cgraphic.
/******************************************/
/* Pytanie o rozmiar danej.               */
/******************************************/

#include "accdb.h"

int Pole; //stala z rodziny CDDB_VALNAME_ okreslajaca pole
LONG index; //index �cierzki jesli pytamy o dane rozszerzone dla �cierzek
LONG deep;  //"g��boko�c" danej
ULONG cdNum; //logiczny numer napedu
ULONG *ulBufSize; //rozmiar bufora

LONG CddbQueryValueLength(int Pole, LONG index, LONG deep, ULONG cdNum,
                          ULONG *rozmiar)
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbQueryValueLength_P.Parametry - CddbQueryValueLength
:dl tsize=3 break=all.
:dt.:hp2.Pole:ehp2. (int) - parametr
:dd. okre�la o kt�re pole si� pytamy (sta�e z rodziny CDDB_VALNAME) (!)
:dt.:hp2.index:ehp2. (LONG) - parametr
:dd. u�ywane tylko w przypadku pyta� o informacj� rozszerzon� dla 
�cierzki (CDDB_VALNAME_EXTT), oznacza kt�rej �cierzki ma dotyczy� pytanie. 
W przypadku gdy Pole!=CDDB_VALNAME_EXTT warto�� index jest ignorowana.
:p. numery �cierzek zaczynaj� si� od 1
:dt.:hp2.deep:ehp2. (LONG) - parametr
:dd. oznacza g��boko�� danego pola (np je�li Pole=CDDB_VALNAME_TITLE to deep
oznacza do tytu�u kt�rej �cierzki sie odwo�ujemy)
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap�du.
:p. Nap�dy numerowane s� od 1.
:dt.:hp2.ulBufSize:ehp2. (LONG) - zwracane
:dd. rozmiar bufora jaki trzeba przeznaczy� na odczyt danej z tego pola.
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbQueryValueLength_E.B��dy - CddbQueryValueLength
Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ATOMQUERYFAILED
:dd.Pobranie warto�ci nie powiod�o si�.
:dt.ERR_CDDB_DEEPOUTOFRANGE
:dd.Podana g��boko�� jest poza zakresem.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany index jest poza zakresem.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjowany.
:dt.ERR_CDDB_NOATOM
:dd.Dla podanej g��boko�ci nie ma przypisanej �adnej warto�ci.
:dt.ERR_CDDB_SEMREQAILED
:dd.Pr�ba zablokowania semafora nie powiod�a si�
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr�ba sprawdzenia semafora nie powiod�a si�.
:dt.ERR_CDDB_WRONGDATA
:dd.Dane Cddb dla danego nap�du nie s� poprawne.
:dt.ERR_CDDB_WRONGFIELD
:dd.U�ytkownik poda� b��dn� sta�� okre�laj�c� pole
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbQueryValueLength_N.Opis - CddbQueryValueLength
:p.Funkcja zwraca rozmiar danej dla danego pola o podanym indeksie
 i g��boko�ci przyporzadkowan� dla danego nap�du CD (okre�lone przez ulCdNum).

.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbQueryValueLength_R.Funkcje dodatkowe - CddbQueryValueLength
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbQueryValue.CddbQueryValue:elink.
:li.:link reftype=hd refid=CddbQueryValueCount.CddbQueryValueCount:elink.
:eul.

.* Funkcja "CddbSave"
.*
:h2 x=left width=25% scroll=none clear name=CddbSave.CddbSave
:link dependent group=40 reftype=hd auto refid=CddbSave_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbSave_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbSave_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbSave_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbSave_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbSave_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbSave_S.Sk�adnia - CddbSave
:cgraphic.
/******************************************/
/* Zapis danych do lokalnej bazy          */
/******************************************/

#include "accdb.h"

CDDB_QUERY   query;    //struktura opisuj�ca zapytanie i/lub zapis

LONG CddbSave(CDDB_QUERY query);
:ecgraphic.

.* PARAMETRY
:h2 x=60% width=40% hide name=CddbSave_P.Parametry - CddbSave
:dl tsize=3 break=all.
:dt.:hp2.query:ehp2. (:link reftype=hd vpcx=100% refid=CDDB_QUERY.CDDB_QUERY:elink.) - parametr.
:dd. Struktura opisuj�ca zapytanie, u�uwana tak�e przy zapisie.
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbSave_E.B��dy - CddbSave
Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_DATANOTVALID
:dd.Dane dla danego nap�du nie s� poprawne (albo ich w og�le nie ma).
:dt.ERR_CDDB_MODINUSE
:dd.Modu� wykonuje inn� funkcj� uniemo�liwiaj�c� wykonanie zadania.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjowany.
:dt.ERR_CDDB_SEMREQFAILED
:dd.Pr�ba zablokowania semafora nie powiod�a si�.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr�ba sprawdzenia semafora nie powiod�a si�.
:dt.ERR_CDDB_THRCREATEFAILED
:dd.Pr�ba utworzenia w�tku pytaj�cego nie powiod�a si�..
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbSave_N.Opis - CddbSave
:p.Funkcja rozpoczyna w�tek zapisuj�cy dane CD do lokalnej bazy, �cierzka do 
bazy jest pobierana ze struktury 
:link reftype=hd vpcx=100% refid=CDDB_QUERY.CDDB_QUERY:elink. (wskazane jest 
u�ycie tej samej sktrukt�ry co podczasz tworzenia zapytania). O zako�czeniu 
pracy w�tku, modu� zawiadomi wysy�aj�c komunikat 
:link reftype=hd refid=WM_CDDB.WM_CDDB:elink.

.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbSave_R.Funkcje dodatkowe - CddbSave
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbCancelAction.CddbCancelAction:elink.
:eul.


.* Funkcja "CduTerminate"
.*
:h2 x=left width=25% scroll=none clear name=CddbTerminate.CddbTerminate
:link dependent group=40 reftype=hd auto refid=CddbTerminate_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbTerminate_S.Sk�adnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbTerminate_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbTerminate_E.B��dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbTerminate_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbTerminate_R.Funkcje dodatkowe:elink.


.* SK�ADNIA
:h2 x=25% width=75% hide name=CddbTerminate_S.Sk�adnia - CddbTerminate
:cgraphic.
/******************************************/
/* Zwolnienie zasob�w modu�u Cddb         */
/******************************************/

#include "acddb.h"
ULONG ulTimeOut;//czas oczekiwania na ewentualne zako�czenie dzia�ania innych funckji modu�u

LONG CddbTerminate(ULONG ulTimeOut);
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbTerminate_P.Parametry - CddbTerminate
:dl tsize=3 break=all.
:dt.:hp2.ulTimeOut:ehp2. (ULONG) - - parametr.
:dd. Czas ewentualnego oczekiwania na zako�czenie pozosta�ych funkcji modu�u.
:p.Je�li podczas wywo�ania funckji istniej� jakie� w�tki pytaj�ce funkcja czeka
ulTimeOut milisekund na ich zako�czenie, je�li po up�ywie tego czasu w�tki
nadal pracuj� - zwracany jest b��d ERR_CDDB_MODINUSE;
:edl.


.* B��DY
:h2 x=60% width=40% hide name=CddbTerminate_E.B��dy - CddbTerminate
:p.Mo�liwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_MODINUSE
:dd.Pomimo up�yni�cia czasu oczekiwania modu� nadal jest w u�yciu.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjalizowany.
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbTerminate_N.Opis - CddbTerminate
:p.Funkcja zwalnia zasoby modu�u Cddb, takie jak: pami��, uchwyty nap�d�w itp.
Je�li podczas wywo�ania funckji istniej� jakie� w�tki pytaj�ce funkcja czeka
ulTimeOut milisekund na ich zako�czenie, je�li po up�ywie tego czasu w�tki
nadal pracuj� - zwracany jest b��d ERR_CDDB_MODINUSE;


.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbTerminate_R.Funkcje dodatkowe - CddbTerminate
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbCancelAction.CddbCancelAction:elink.
:li.:link reftype=hd refid=CddbInitialize.CddbInitialize:elink.
:eul.
