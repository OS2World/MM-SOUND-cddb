.*
:userdoc.
:docprof toc=1234.
:title.CDDB - Modu� obs�ugi cddb.

.* Rozdzia� 1 - "Modu� obs�ugi kompaktu"
.*
:h1 res=001.Wst�p
:p.Modu� obs�ugi CDDB zawiera wygodny interfejs do komunikacji z baz� CD,
zar�wno lokaln� jak i sieciow�. G�owne zadania modu�u to:
:ul compact.
:li.Wyszukiwanie danych o CD i ich przechowywanie.
:li.Zapis/usuwanie danych do/z lokalnej bazy.
:li.Dost�p do przechowywanych danych.
:li.Ukrycie przed programnist� obs�ugi sieci (tcp/ip) oraz wielow�tkowo�ci.
:eul.

:warning.
Modu� do pracy wymaga obecno�ci Presentation Managera.
:ewarning.

.* Rozdzia� 2 "Typy danych"
.im cddbdata.inc

.* Rozdzia� 3 "Komunikaty"
.im messages.inc

.* Rozdzia� 4 "Funkcje modu�u"
.im functions.inc

.* Rozdzia� 5 "Sta�e"
.*
.im consts.inc

.* Rozdzia� 6 "Kody b��d�w"
.*
:h1 clear res=006.Kody b��d�w
:p.Zestawienie kod�w b��d�w.
:dl tsize=34 break=none.
:dthd.:hp2.Kod b��du:ehp2.
:ddhd.:hp2.Wyja�nienie:ehp2.
:dt.ERR_CDDB_OK
:dd.Brak b��du.
:dt.ERR_CDDB_ABORTED
:dd.Akcja przerwana przez u�ytkownika.
:dt.ERR_CDDB_ALREADYDONE
:dd.Funckja wykona�a zadanie przy poprednim wywo�aniu.
:dt.ERR_CDDB_ATBLCREATEFAILED
:dd.B��d podczas tworzenia tablicy atom�w.
:dt.ERR_CDDB_ATOMADDFAILED
:dd.B��d podczas dodawania atomu.
:dt.ERR_CDDB_ATOMQUERYFAILED
:dd.B��d podczas pytania o atom.
:dt.ERR_CDDB_CDNOTFOUND
:dd.Nie znaleziono CD w bazie.
:dt.ERR_CDDB_CONNECTFAILED
:dd.B��d podczas ��czenia do serwera.
:dt.ERR_CDDB_DATANOTVALID
:dd.Dane s� b��dne/nie wa�ne (nie ma ich).
:dt.ERR_CDDB_DEEPOUTOFRANGE
:dd.Podana g��boko�� jest poza zakresem.
:dt.ERR_CDDB_DLLLOADFAILED
:dd.Bibklioteka Dll odpowiedzialna za cz��� sieciow� nie zosta�a za�adowana 
i/lub pr�bowano wywo�a� jedna z jej funkcji
:dt.ERR_CDDB_DNSFAILED
:dd.B��d podczas pobierania adresu serwera.
:dt.ERR_CDDB_FILEOPENFAILED
:dd.B��d podczas otwierania pliku.
:dt.ERR_CDDB_FILEREADERR
:dd.B��d podczas odczytu pliku.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany indeks jest poza zakresem.
:dt.ERR_CDDB_INVALIDSCOPE
:dd.B��dny zakres szukania.
:dt.ERR_CDDB_MEMALLOCFAILED
:dd.B��d podczas alokacji pami�ci.
:dt.ERR_CDDB_MODINUSE
:dd.Modu� jest u�ywany, funkcja nie mo�e zosta� wykonana.
:dt.ERR_CDDB_MODNOTINIT
:dd.Modu� nie zosta� zainicjalizowany.
:dt.ERR_CDDB_NOATOM
:dd.Brak atomu.
:dt.ERR_CDDB_OUTOFRANGE
:dd.Pr�ba odczytu danej poza zakresem.
:dt.ERR_CDDB_QUERYPROCFAILED
:dd.B��d podczas pobrania funkcji z dll'a
:dt.ERR_CDDB_RECVFAILED
:dd.B��d podczas odbioru danych z serwera (tcp).
:dt.ERR_CDDB_SEMCREATEFAIL
:dd.B��d podczas tworzenia semafora.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.B��d podczs sprawdzania semafora.
:dt.ERR_CDDB_SEMREQFAILED
:dd.B��d podczas podnoszenia semafora.
:dt.ERR_CDDB_SENDFAILED
:dd.B��d podczas wysy�ania danych do serwera (tcp).
:dt.ERR_CDDB_SETSOCKFAILED
:dd.B��d podczas ustawiania typu interfejsu (tcp).
:dt.ERR_CDDB_THRCREATEFAILED
:dd.B��d podczas tworzenia w�tku.
:dt.ERR_CDDB_WRITEFAILED
:dd.B��d podczas zapisu do pliku.
:dt.ERR_CDDB_WRONGDATA
:dd.B��dne dane.
:dt.ERR_CDDB_WRONGFIELD
:dd.B��dny numer pola.
:edl.

.* Rozdzia� 7 "Do zrobienia"
.*
:h1 clear res=007.Do zrobienia
:p. Rzeczy do dodania..
:ol compact.
:li.Wyszukiwanie "g��bokie" - podejrzewam, �e do Asu'a Commander'a powstanie
modu� obs�uguj�cy wyszukiwanie (Alt+F7 z FC/2), mo�na go wtedy wykorzysta� tak�e
w tym module.
:li.Je�li oka�e si� to potrzebne, funkcje umo�liwiaj�ce u�ytkownikowi tworzenie
wpis�w w bazie.
:li.Je�li oka�e si� to konieczne, obs�ug� komunikatu "211 Found inexact 
matches&comma. list follows &lpar.until terminating marker&rpar." umo�liwiaj�c 
u�ytkownikowi wyb�r z listy.
:li.Mo�e obs�ug� http..?
:eol.

:euserdoc.