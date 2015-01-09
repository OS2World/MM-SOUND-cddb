.*
:userdoc.
:docprof toc=1234.
:title.CDDB - Moduˆ obsˆugi cddb.

.* Rozdziaˆ 1 - "Moduˆ obsˆugi kompaktu"
.*
:h1 res=001.Wst©p
:p.Moduˆ obsˆugi CDDB zawiera wygodny interfejs do komunikacji z baz¥ CD,
zar¢wno lokaln¥ jak i sieciow¥. Gˆowne zadania moduˆu to:
:ul compact.
:li.Wyszukiwanie danych o CD i ich przechowywanie.
:li.Zapis/usuwanie danych do/z lokalnej bazy.
:li.Dost©p do przechowywanych danych.
:li.Ukrycie przed programnist¥ obsˆugi sieci (tcp/ip) oraz wielow¥tkowo˜ci.
:eul.

:warning.
Moduˆ do pracy wymaga obecno˜ci Presentation Managera.
:ewarning.

.* Rozdziaˆ 2 "Typy danych"
.im cddbdata.inc

.* Rozdziaˆ 3 "Komunikaty"
.im messages.inc

.* Rozdziaˆ 4 "Funkcje moduˆu"
.im functions.inc

.* Rozdziaˆ 5 "Staˆe"
.*
.im consts.inc

.* Rozdziaˆ 6 "Kody bˆ©d¢w"
.*
:h1 clear res=006.Kody bˆ©d¢w
:p.Zestawienie kod¢w bˆ©d¢w.
:dl tsize=34 break=none.
:dthd.:hp2.Kod bˆ©du:ehp2.
:ddhd.:hp2.Wyja˜nienie:ehp2.
:dt.ERR_CDDB_OK
:dd.Brak bˆ©du.
:dt.ERR_CDDB_ABORTED
:dd.Akcja przerwana przez u¾ytkownika.
:dt.ERR_CDDB_ALREADYDONE
:dd.Funckja wykonaˆa zadanie przy poprednim wywoˆaniu.
:dt.ERR_CDDB_ATBLCREATEFAILED
:dd.Bˆ¥d podczas tworzenia tablicy atom¢w.
:dt.ERR_CDDB_ATOMADDFAILED
:dd.Bˆ¥d podczas dodawania atomu.
:dt.ERR_CDDB_ATOMQUERYFAILED
:dd.Bˆ¥d podczas pytania o atom.
:dt.ERR_CDDB_CDNOTFOUND
:dd.Nie znaleziono CD w bazie.
:dt.ERR_CDDB_CONNECTFAILED
:dd.Bˆ¥d podczas ˆ¥czenia do serwera.
:dt.ERR_CDDB_DATANOTVALID
:dd.Dane s¥ bˆ©dne/nie wa¾ne (nie ma ich).
:dt.ERR_CDDB_DEEPOUTOFRANGE
:dd.Podana gˆ©boko˜† jest poza zakresem.
:dt.ERR_CDDB_DLLLOADFAILED
:dd.Bibklioteka Dll odpowiedzialna za cz©˜† sieciow¥ nie zostaˆa zaˆadowana 
i/lub pr¢bowano wywoˆa† jedna z jej funkcji
:dt.ERR_CDDB_DNSFAILED
:dd.Bˆ¥d podczas pobierania adresu serwera.
:dt.ERR_CDDB_FILEOPENFAILED
:dd.Bˆ¥d podczas otwierania pliku.
:dt.ERR_CDDB_FILEREADERR
:dd.Bˆ¥d podczas odczytu pliku.
:dt.ERR_CDDB_INDEXOUTOFRANGE
:dd.Podany indeks jest poza zakresem.
:dt.ERR_CDDB_INVALIDSCOPE
:dd.Bˆ©dny zakres szukania.
:dt.ERR_CDDB_MEMALLOCFAILED
:dd.Bˆ¥d podczas alokacji pami©ci.
:dt.ERR_CDDB_MODINUSE
:dd.Moduˆ jest u¾ywany, funkcja nie mo¾e zosta† wykonana.
:dt.ERR_CDDB_MODNOTINIT
:dd.Moduˆ nie zostaˆ zainicjalizowany.
:dt.ERR_CDDB_NOATOM
:dd.Brak atomu.
:dt.ERR_CDDB_OUTOFRANGE
:dd.Pr¢ba odczytu danej poza zakresem.
:dt.ERR_CDDB_QUERYPROCFAILED
:dd.Bˆ¥d podczas pobrania funkcji z dll'a
:dt.ERR_CDDB_RECVFAILED
:dd.Bˆ¥d podczas odbioru danych z serwera (tcp).
:dt.ERR_CDDB_SEMCREATEFAIL
:dd.Bˆ¥d podczas tworzenia semafora.
:dt.ERR_CDDB_SEMQUERYFAILED
:dd.Bˆ¥d podczs sprawdzania semafora.
:dt.ERR_CDDB_SEMREQFAILED
:dd.Bˆ¥d podczas podnoszenia semafora.
:dt.ERR_CDDB_SENDFAILED
:dd.Bˆ¥d podczas wysyˆania danych do serwera (tcp).
:dt.ERR_CDDB_SETSOCKFAILED
:dd.Bˆ¥d podczas ustawiania typu interfejsu (tcp).
:dt.ERR_CDDB_THRCREATEFAILED
:dd.Bˆ¥d podczas tworzenia w¥tku.
:dt.ERR_CDDB_WRITEFAILED
:dd.Bˆ¥d podczas zapisu do pliku.
:dt.ERR_CDDB_WRONGDATA
:dd.Bˆ©dne dane.
:dt.ERR_CDDB_WRONGFIELD
:dd.Bˆ©dny numer pola.
:edl.

.* Rozdziaˆ 7 "Do zrobienia"
.*
:h1 clear res=007.Do zrobienia
:p. Rzeczy do dodania..
:ol compact.
:li.Wyszukiwanie "gˆ©bokie" - podejrzewam, ¾e do Asu'a Commander'a powstanie
moduˆ obsˆuguj¥cy wyszukiwanie (Alt+F7 z FC/2), mo¾na go wtedy wykorzysta† tak¾e
w tym module.
:li.Je˜li oka¾e si© to potrzebne, funkcje umo¾liwiaj¥ce u¾ytkownikowi tworzenie
wpis¢w w bazie.
:li.Je˜li oka¾e si© to konieczne, obsˆug© komunikatu "211 Found inexact 
matches&comma. list follows &lpar.until terminating marker&rpar." umo¾liwiaj¥c 
u¾ytkownikowi wyb¢r z listy.
:li.Mo¾e obsˆug© http..?
:eol.

:euserdoc.