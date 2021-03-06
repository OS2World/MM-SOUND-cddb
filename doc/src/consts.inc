.* Modu� CDDB
.* Rozdzia� 5 "Typy danych"
.*
:h1 res=005.Zdefiniwane sta�e
:p.W module wykorzystuje si� zdefiniowane sta�e, w tym rozdziale znajdziesz ich
opis.
:ul compact.
:li.Sta�e zakresu szukania :link reftype=hd refid=CDDB_SCOPE.CDDB_SCOPE:elink.
:li.Sta�e nazywania p�l :link reftype=hd refid=CDDB_VALNAME.CDDB_VALNAME:elink.
:li.Sta�e zako�czenia pracy w�tk�w :link reftype=hd refid=CDDB_WM.CDDB_WM:elink.
:eul.

.* sta�e CDDB_SCOPE
.*
:h2 name=CDDB_SCOPE.CDDB_SCOPE
:p.
Sta�e z rodziny :hp2.CDDB_SCOPE:ehp2. okre�laj� zakres szukania CD. 
:dl tsize=30 break=none.
:dthd.:hp2.Sta�a:ehp2.
:ddhd.:hp2.Wyja�nienie:ehp2.
:dt.CDDB_SCOPE_ALL
:dd.Szuka w obu bazach - najpierw w lokalnej (:link refid=undeep reftype=fn.wyszukiwanie "p�ytkie":elink.), potem na sieci.
:dt.CDDB_SCOPE_ALL_DEEP
:dd.Szuka w obu bazach - najpierw w lokalnej (:link refid=deep reftype=fn.wyszukiwanie "g��bokie":elink.), potem na sieci.
:dt.CDDB_SCOPE_LOCAL
:dd.Szuka w tylko w bazie lokalnej (:link refid=undeep reftype=fn.wyszukiwanie "p�ytkie":elink.).
:dt.CDDB_SCOPE_LOCAL_DEEP
:dd.Szuka w tylko w bazie lokalnej (:link refid=deep reftype=fn.wyszukiwanie "g��bokie":elink.).
:dt.CDDB_SCOPE_REMOTE
:dd.Szuka w tylko na sieci.
:edl.

:fn id=undeep.
Wyszukiwanie :hp5.p�ytkie:ehp5. polega na odnajdywaniu CD tylko po nazwie
pliku.
:efn.

:fn id=deep.
Wyszukiwanie :hp5.g��bokie:ehp5. wumusza przeszukiwanie p�l CDDBID w
ka�dym z plik�w bazy.
:efn.

.* sta�e CDDB_VALNAME
.*
:h2 name=CDDB_VALNAME.CDDB_VALNAME
:p.
Sta�e z rodziny :hp2.CDDB_VALNAME:ehp2. s�u�� do nazywania p�l, przy
wywo�aniach funkcji: :link reftype=hd refid=CddbQueryValue.CddbQueryValue:elink.,
:link reftype=hd refid=CddbQueryValueCount.CddbQueryValueCount:elink.,
:link reftype=hd refid=CddbQueryValueLength.CddbQueryValueLength:elink.

:dl tsize=33 break=none.
:dthd.:hp2.Sta�a:ehp2.
:ddhd.:hp2.Pole:ehp2.
:dt.CDDB_VALNAME_CDDBID
:dd.Cddb Id
:dt.CDDB_VALNAME_ARIST
:dd.Artysta
:dt.CDDB_VALNAME_TITLE
:dd.Tytu� p�yty
:dt.CDDB_VALNAME_TTITLE
:dd.Nazwa �cierzki
:dt.CDDB_VALNAME_EXTD
:dd.Informacje rozszerzone dla p�yty
:dt.CDDB_VALNAME_EXTT
:dd.Informacje rozszerzone dla �cierzki
:dt.CDDB_VALNAME_PLAYORDER
:dd.Kolejno�� odtwarzania utwor�w
:dt.CDDB_VALNAME_OTHER
:dd.Pozosta�e dane (w tym cz��� komentarzy)
:edl.

.* sta�e CDDB_WM
.*
:h2 name=CDDB_WM.CDDB_WM
:p.
Sta�e z rodziny :hp2.CDDB_WM:ehp2. s� u�ywane podczas zawiadamiania aplikacji
(poprzez komunikat :link reftype=hd refid=WM_CDDB.WM_CDDB:elink.) o zako�czeniu pracy 
jednego z w�tk�w modu�u.

:dl tsize=33 break=none.
:dthd.:hp2.Sta�a:ehp2.
:ddhd.:hp2.Pole:ehp2.
:dt.CDDB_WM_SAVE
:dd.Prac� zako�czy� w�tek zapisuj�cy.
:dt.CDDB_WM_QUERY
:dd.Prac� zako�czy� w�tek pytaj�cy.
:edl.