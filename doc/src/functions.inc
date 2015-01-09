.* modul CDDB
.* Rozdziaà 4 "Funkcje"
.*
:h1 res=004.Funkcje modulu CDDB
:p.Zestw funkcji umoæliwia znalezienie CD w bazie na sieci i/lub na dysku oraz
p¢´niejszy dost©p do odczytanych danych.


.* Funkcja "CddbCancelAction"
.*
:h2 x=left width=25% scroll=none clear name=CddbCancelAction.CddbCancelAction
:link dependent group=40 reftype=hd auto refid=CddbCancelAction_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=CddbCancelAction_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbCancelAction_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbCancelAction_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbCancelAction_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbCancelAction_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbCancelAction_S.Skàadnia - CddbCancelAction
:cgraphic.
/******************************************/
/* Anulowanie pytania o CD lub zapisu.    */
/******************************************/

#include "accdb.h"

ULONG   ulCDNum;    // Logiczny numer nap©du

LONG CddbCancelAction(ULONG ulCdNum);
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbCancelAction_P.Parametry - CddbCancelAction
:dl tsize=3 break=all.
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap©du.
:p. Nap©dy numerowane s• od 1.
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbCancelAction_E.Bà©dy - CddbCancelAction
Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ALREADYDONE
:dd.Flaga zako‰czenia pytania jest juæ ustawiona.
:dt.ERR_CDDB_OUTOFRANGE
:dd.Podany numer nap©du znajduje si© poza zakresem.
:dt.ERR_CDDB_MODINUSE
:dd.Moduà wykonuje inn• funkcj© uniemoæliwiaj•c• wykonanie zadania.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjowany.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr¢ba sprawdzenia semafora nie powiodàa si©.
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbCancelAction_N.Opis - CddbCancelAction
:p.Funkcja ustawia flag© informuj•c• w•tek pytaj•cy/zapisuj•cy o koniecznoòci
zako‰czenia pracy. O zako‰czeniu pracy w•tku, moduà zawiadomi wysyàaj•c
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
:link dependent group=40 reftype=hd refid=CddbCreateQuery_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbCreateQuery_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbCreateQuery_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbCreateQuery_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbCreateQuery_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbCreateQuery_S.Skàadnia - CddbCreateQuery
:cgraphic.
/******************************************/
/* Pytanie o CD.                          */
/******************************************/

#include "accdb.h"

CDDB_QUERY   query;    //struktura opisuj•ca zapytanie i/lub zapis

LONG CddbCreateQuery(CDDB_QUERY query);
:ecgraphic.

.* PARAMETRY
:h2 x=60% width=40% hide name=CddbCreateQuery_P.Parametry - CddbCreateQuery
:dl tsize=3 break=all.
:dt.:hp2.query:ehp2. (:link reftype=hd vpcx=100% refid=CDDB_QUERY.CDDB_QUERY:elink.) - parametr.
:dd. Struktura opisuj•ca zapytanie, uæuwana takæe przy zapisie.
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbCreateQuery_E.Bà©dy - CddbCreateQuery
Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_MODINUSE
:dd.Moduà wykonuje inn• funkcj© uniemoæliwiaj•c• wykonanie zadania.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjowany.
:dt.ERR_CDDB_SEMREQFAILED
:dd.Pr¢ba zablokowania semafora nie powiodàa si©.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr¢ba sprawdzenia semafora nie powiodàa si©.
:dt.ERR_CDDB_THRCREATEFAILED
:dd.Pr¢ba utworzenia w•tku pytaj•cego nie powiodàa si©..
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbCreateQuery_N.Opis - CddbCreateQuery
:p.Funkcja rozpoczyna w•tek pytaj•cy o CD, dane wejòciowe zapytania przekazywane s• jako parametr.
O zako‰czeniu pracy w•tku, moduà zawiadomi wysyàaj•c komunikat
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
:link dependent group=40 reftype=hd refid=CddbInitialize_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbInitialize_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbInitialize_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbInitialize_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbInitialize_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbInitialize_S.Skàadnia - CddbInitialize
:cgraphic.
/******************************************/
/* Inicjacja moduàu interfejsu cddb.      */
/******************************************/

#include "acddb.h"

ULONG drives; //liczba nap©d¢w CD w systemie
ULONG wm_cddb;//kod notyfikacji
HWND hwndCddb;//uchwyt okna do kt¢rego b©dzie wysyàana notyfikacja

LONG CddbInitialize(ULONG drives, ULONG wm_cddb, HWND hwndCddb);
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbInitialize_P.Parametry - CddbInitialize
:dl tsize=3 break=all.
:dt.:hp2.drives:ehp2. (ULONG) - - parametr.
:dd. Liczba nap©d¢w w systemie.
:p. Uæytkownik moæe podaÜ inn• niæ rzeczywista liczb© nap©d¢w w systemie
(uæywane do tworzenia miejsca w pami©ci pod dane cddb),
pami©taj•c jednak aby podczas p¢´niejszej pracy z moduàem wszystkie wartoòci
numeru nap©du CD, mieòciày si© w podej przez niego granicy.
:dt.:hp2.wm_cddb:ehp2. (ULONG) - - parametr.
:dd. Kod komunikatu WM_CDDB.
:p. Uæytkownik moæe podaÜ odpowiadaj•cy mu kod komunikatu WM_CDDB.
:dt.:hp2.hwndCddb:ehp2. (ULONG) - - parametr.
:dd. Uchwyt okna do kt¢rego b©dzie wysyàany komunikat WM_CDDB.
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbInitialize_E.Bà©dy - CddbInitialize
:p.Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ALREADYDONE
:dd.Moduà juæ zostaà zainicjalizowany.
:dt.ERR_CDDB_ATBLCREATEFAILED
:dd.Tworzenie tablicy atom¢w nie powiodào si©.
:dt.ERR_CDDB_DLLLOADFAILED
:dd.Nie udaào si© zaàadowaÜ biblioteki dll odpowiedzialnej za cz©òÜ sieciow• 
moduàu
:dt.ERR_CDDB_MEMALLOCFAILED
:dd.Alokacja pami©ci nie powiodàa si©.
:dt.ERR_CDDB_QUERYPROCFAILED
:dd.Pobranie funkcji z biblioteki dll, nie powiodào si©.
:dt.ERR_CDDB_SEMCREATEFAILED
:dd.Tworzenie semafora nie powiodào si©.
:dt.ERR_CDDB_SOCKINITFAILED
:dd.Inicjalizacja wsp¢àpracy z siecia nie powiodàa si©.
:dt.ERR_CDDB_TCPFAILED
:dd.Wczytanie acddbtcp.dll nie powiodào si©.
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbInitialize_N.Opis - CddbInitialize
:p.Funkcja inicjuje moduà interfejsu cddb. Naleæy jej uæyÜ przd wywoàaniem
jakiejkolwiek innej funkcji moduàu.
:p.Funkcja alokuje pami©Ü pod dane cddb dla drives nap©d¢w, zapami©tuje kod
komunikatu CDDB oraz uchwyt okna odbiorcy oraz pr¢buje wczytaÜ bibliotek©,
odpowiedzialn• za cz©òÜ sieciow• poszukiwa‰. W razie bà©du inicjalizacji funcja
usuwa 'òmieci' po sobie. 
:warning.Nie wczytanie obsàugi tcp nie przerywa inicjalizacji moduàu.


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
:link dependent group=40 reftype=hd refid=CddbQueryValue_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbQueryValue_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbQueryValue_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbQueryValue_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbQueryValue_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbQueryValue_S.Skàadnia - CddbQueryValue
:cgraphic.
/******************************************/
/* Pytanie o wartoòci danych.             */
/******************************************/

#include "accdb.h"

int Pole; //stala z rodziny CDDB_VALNAME_ okreslajaca pole
LONG index; //index òcierzki jesli pytamy o dane rozszerzone dla òcierzek
LONG deep;  //"gà©bokoòc" danej
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
:dd. okreòla o kt¢re pole si© pytamy (staàe z rodziny CDDB_VALNAME) (!)
:dt.:hp2.index:ehp2. (LONG) - parametr
:dd. uæywane tylko w przypadku pyta‰ o informacj© rozszerzon• dla 
òcierzki (CDDB_VALNAME_EXTT), oznacza kt¢rej òcierzki ma dotyczyÜ pytanie. 
W przypadku gdy Pole!=CDDB_VALNAME_EXTT wartoòÜ index jest ignorowana.
:p. numery òcierzek zaczynaj• si© od 1
:dt.:hp2.deep:ehp2. (LONG) - parametr
:dd. oznacza gà©bokoòÜ danego pola (np jeòli Pole=CDDB_VALNAME_TITLE to deep
oznacza do tytuàu kt¢rej òcierzki sie odwoàujemy)
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap©du.
:p. Nap©dy numerowane s• od 1.
:dt.:hp2.Wartosc:ehp2. (PSZ) - zwracane
:dd. bufor do kt¢rego zostanie zapisany zwracany tekst
:dt.:hp2.ulBufSize:ehp2. (LONG) - parametr
:dd. rozmiar bufora na odczytan• wartoòÜ
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbQueryValue_E.Bà©dy - CddbQueryValue
Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ATOMQUERYFAILED
:dd.Pobranie wartoòci nie powiodào si©.
:dt.ERR_CDDB_DEEPOUTOFRANGE
:dd.Podana gà©bokoòÜ jest poza zakresem.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany index jest poza zakresem.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjowany.
:dt.ERR_CDDB_NOATOM
:dd.Dla podanej gà©bokoòci nie ma przypisanej æadnej wartoòci.
:dt.ERR_CDDB_SEMREQAILED
:dd.Pr¢ba zablokowania semafora nie powiodàa si©
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr¢ba sprawdzenia semafora nie powiodàa si©.
:dt.ERR_CDDB_WRONGDATA
:dd.Dane Cddb dla danego nap©du nie s• poprawne.
:dt.ERR_CDDB_WRONGFIELD
:dd.Uæytkownik podaà bà©dn• staà• okreòlaj•c• pole
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbQueryValue_N.Opis - CddbQueryValue
:p.Funkcja zwraca tekst (w buforze Wartosc) dla danego pola o podanym indeksie
 i gà©bokoòci przyporzadkowan• dla danego nap©du CD (okreòlone przez ulCdNum).


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
:link dependent group=40 reftype=hd refid=CddbQueryValueCount_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbQueryValueCount_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbQueryValueCount_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbQueryValueCount_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbQueryValueCount_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbQueryValueCount_S.Skàadnia - CddbQueryValueCount
:cgraphic.
/******************************************/
/* Pytanie o iloòÜ danych.                */
/******************************************/

#include "accdb.h"

int Pole; //stala z rodziny CDDB_VALNAME_ okreslajaca pole
LONG index; //index òcierzki jesli pytamy o dane rozszerzone dla òcierzek
LONG deep;  //"gà©bokoòc" danej
ULONG cdNum; //logiczny numer napedu

LONG CddbQueryValueCount(int Pole, ULONG * index, ULONG * deep, ULONG cdNum)
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbQueryValueCount_P.Parametry - CddbQueryValueCount
:dl tsize=3 break=all.
:dt.:hp2.Pole:ehp2. (int) - parametr
:dd. okreòla o kt¢re pole si© pytamy (staàe z rodziny CDDB_VALNAME) (!)
:dt.:hp2.index:ehp2. (LONG) - parametr/zwracane
:dd. uæywane tylko w przypadku pyta‰ o informacj© rozszerzon• dla 
òcierzki (CDDB_VALNAME_EXTT): jeòli ustawione na 0 - pytamy si© o iloòÜ p¢l
z informacj• rozszerzon• dla òcierzek - po zako‰czeniu wartoòÜ ta zwracana jest
w index; jeòli ustawione na konkretn• wartoòÜ, wtedy deep zwr¢ci gà©bokoòÜ
dla informacji rozszerzonej dla scierzki o numerze index.
W przypadku gdy Pole!=CDDB_VALNAME_EXTT wartoòÜ index jest ignorowana.
:p. numery òcierzek zaczynaj• si© od 1
:dt.:hp2.deep:ehp2. (LONG) - zwracane
:dd. zwraca gà©bokoòÜ danego pola. Jeòli Pole=CDDB_VALNAME_EXTT i index=0, deep
nic nie zwraca (zwracane jest wtedy tylko index).
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap©du.
:p. Nap©dy numerowane s• od 1.
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbQueryValueCount_E.Bà©dy - CddbQueryValueCount
Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany index jest poza zakresem.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjowany.
:dt.ERR_CDDB_SEMREQAILED
:dd.Pr¢ba zablokowania semafora nie powiodàa si©
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr¢ba sprawdzenia semafora nie powiodàa si©.
:dt.ERR_CDDB_WRONGDATA
:dd.Dane Cddb dla danego nap©du nie s• poprawne.
:dt.ERR_CDDB_WRONGFIELD
:dd.Uæytkownik podaà bà©dn• staà• okreòlaj•c• pole
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbQueryValueCount_N.Opis - CddbQueryValueCount
:p.Funkcja zwraca iloòÜ danych (gà©bokoÜ) dla danego pola (ewentualnie o 
podanym indeksie) lub iloòÜ p¢l z informacj• rozszerzon• dla òcierzek.

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
:link dependent group=40 reftype=hd refid=CddbQueryValueLength_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbQueryValueLength_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbQueryValueLength_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbQueryValueLength_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbQueryValueLength_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbQueryValueLength_S.Skàadnia - CddbQueryValueLength
:cgraphic.
/******************************************/
/* Pytanie o rozmiar danej.               */
/******************************************/

#include "accdb.h"

int Pole; //stala z rodziny CDDB_VALNAME_ okreslajaca pole
LONG index; //index òcierzki jesli pytamy o dane rozszerzone dla òcierzek
LONG deep;  //"gà©bokoòc" danej
ULONG cdNum; //logiczny numer napedu
ULONG *ulBufSize; //rozmiar bufora

LONG CddbQueryValueLength(int Pole, LONG index, LONG deep, ULONG cdNum,
                          ULONG *rozmiar)
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbQueryValueLength_P.Parametry - CddbQueryValueLength
:dl tsize=3 break=all.
:dt.:hp2.Pole:ehp2. (int) - parametr
:dd. okreòla o kt¢re pole si© pytamy (staàe z rodziny CDDB_VALNAME) (!)
:dt.:hp2.index:ehp2. (LONG) - parametr
:dd. uæywane tylko w przypadku pyta‰ o informacj© rozszerzon• dla 
òcierzki (CDDB_VALNAME_EXTT), oznacza kt¢rej òcierzki ma dotyczyÜ pytanie. 
W przypadku gdy Pole!=CDDB_VALNAME_EXTT wartoòÜ index jest ignorowana.
:p. numery òcierzek zaczynaj• si© od 1
:dt.:hp2.deep:ehp2. (LONG) - parametr
:dd. oznacza gà©bokoòÜ danego pola (np jeòli Pole=CDDB_VALNAME_TITLE to deep
oznacza do tytuàu kt¢rej òcierzki sie odwoàujemy)
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap©du.
:p. Nap©dy numerowane s• od 1.
:dt.:hp2.ulBufSize:ehp2. (LONG) - zwracane
:dd. rozmiar bufora jaki trzeba przeznaczyÜ na odczyt danej z tego pola.
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbQueryValueLength_E.Bà©dy - CddbQueryValueLength
Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_ATOMQUERYFAILED
:dd.Pobranie wartoòci nie powiodào si©.
:dt.ERR_CDDB_DEEPOUTOFRANGE
:dd.Podana gà©bokoòÜ jest poza zakresem.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany index jest poza zakresem.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjowany.
:dt.ERR_CDDB_NOATOM
:dd.Dla podanej gà©bokoòci nie ma przypisanej æadnej wartoòci.
:dt.ERR_CDDB_SEMREQAILED
:dd.Pr¢ba zablokowania semafora nie powiodàa si©
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr¢ba sprawdzenia semafora nie powiodàa si©.
:dt.ERR_CDDB_WRONGDATA
:dd.Dane Cddb dla danego nap©du nie s• poprawne.
:dt.ERR_CDDB_WRONGFIELD
:dd.Uæytkownik podaà bà©dn• staà• okreòlaj•c• pole
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbQueryValueLength_N.Opis - CddbQueryValueLength
:p.Funkcja zwraca rozmiar danej dla danego pola o podanym indeksie
 i gà©bokoòci przyporzadkowan• dla danego nap©du CD (okreòlone przez ulCdNum).

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
:link dependent group=40 reftype=hd refid=CddbSave_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbSave_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbSave_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbSave_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbSave_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbSave_S.Skàadnia - CddbSave
:cgraphic.
/******************************************/
/* Zapis danych do lokalnej bazy          */
/******************************************/

#include "accdb.h"

CDDB_QUERY   query;    //struktura opisuj•ca zapytanie i/lub zapis

LONG CddbSave(CDDB_QUERY query);
:ecgraphic.

.* PARAMETRY
:h2 x=60% width=40% hide name=CddbSave_P.Parametry - CddbSave
:dl tsize=3 break=all.
:dt.:hp2.query:ehp2. (:link reftype=hd vpcx=100% refid=CDDB_QUERY.CDDB_QUERY:elink.) - parametr.
:dd. Struktura opisuj•ca zapytanie, uæuwana takæe przy zapisie.
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbSave_E.Bà©dy - CddbSave
Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_DATANOTVALID
:dd.Dane dla danego nap©du nie s• poprawne (albo ich w og¢le nie ma).
:dt.ERR_CDDB_MODINUSE
:dd.Moduà wykonuje inn• funkcj© uniemoæliwiaj•c• wykonanie zadania.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjowany.
:dt.ERR_CDDB_SEMREQFAILED
:dd.Pr¢ba zablokowania semafora nie powiodàa si©.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Pr¢ba sprawdzenia semafora nie powiodàa si©.
:dt.ERR_CDDB_THRCREATEFAILED
:dd.Pr¢ba utworzenia w•tku pytaj•cego nie powiodàa si©..
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbSave_N.Opis - CddbSave
:p.Funkcja rozpoczyna w•tek zapisuj•cy dane CD do lokalnej bazy, òcierzka do 
bazy jest pobierana ze struktury 
:link reftype=hd vpcx=100% refid=CDDB_QUERY.CDDB_QUERY:elink. (wskazane jest 
uæycie tej samej sktrukt¢ry co podczasz tworzenia zapytania). O zako‰czeniu 
pracy w•tku, moduà zawiadomi wysyàaj•c komunikat 
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
:link dependent group=40 reftype=hd refid=CddbTerminate_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=CddbTerminate_P.Parametry:elink.
.br
:link dependent group=42 reftype=hd refid=CddbTerminate_E.Bà©dy:elink.
.br
:link dependent group=43 reftype=hd refid=CddbTerminate_N.Opis:elink.
.br
:link dependent group=44 reftype=hd refid=CddbTerminate_R.Funkcje dodatkowe:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=CddbTerminate_S.Skàadnia - CddbTerminate
:cgraphic.
/******************************************/
/* Zwolnienie zasob¢w moduàu Cddb         */
/******************************************/

#include "acddb.h"
ULONG ulTimeOut;//czas oczekiwania na ewentualne zako‰czenie dziaàania innych funckji moduàu

LONG CddbTerminate(ULONG ulTimeOut);
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=CddbTerminate_P.Parametry - CddbTerminate
:dl tsize=3 break=all.
:dt.:hp2.ulTimeOut:ehp2. (ULONG) - - parametr.
:dd. Czas ewentualnego oczekiwania na zako‰czenie pozostaàych funkcji moduàu.
:p.Jeòli podczas wywoàania funckji istniej• jakieò w•tki pytaj•ce funkcja czeka
ulTimeOut milisekund na ich zako‰czenie, jeòli po upàywie tego czasu w•tki
nadal pracuj• - zwracany jest bà•d ERR_CDDB_MODINUSE;
:edl.


.* Bù®DY
:h2 x=60% width=40% hide name=CddbTerminate_E.Bà©dy - CddbTerminate
:p.Moæliwe rezultaty wykonania funkcji&colon.
:dl tsize=3 break=all.
:dt.ERR_CDDB_OK
:dd.Poprawne wykonanie funkcji.
:dt.ERR_CDDB_MODINUSE
:dd.Pomimo upàyni©cia czasu oczekiwania moduà nadal jest w uæyciu.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduà nie zostaà zainicjalizowany.
:edl.


.* OPIS
:h2 x=60% width=40% hide name=CddbTerminate_N.Opis - CddbTerminate
:p.Funkcja zwalnia zasoby moduàu Cddb, takie jak: pami©Ü, uchwyty nap©d¢w itp.
Jeòli podczas wywoàania funckji istniej• jakieò w•tki pytaj•ce funkcja czeka
ulTimeOut milisekund na ich zako‰czenie, jeòli po upàywie tego czasu w•tki
nadal pracuj• - zwracany jest bà•d ERR_CDDB_MODINUSE;


.* FUNKCJE DODATKOWE
:h2 x=60% width=40% hide name=CddbTerminate_R.Funkcje dodatkowe - CddbTerminate
:p.:hp2.Funkcje dodatkowe&colon.:ehp2.
:ul compact.
:li.:link reftype=hd refid=CddbCancelAction.CddbCancelAction:elink.
:li.:link reftype=hd refid=CddbInitialize.CddbInitialize:elink.
:eul.
