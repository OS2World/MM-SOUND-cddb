.* Moduˆ CDDB
.* Rozdziaˆ 5 "Typy danych"
.*
:h1 res=005.Zdefiniwane staˆe
:p.W module wykorzystuje si© zdefiniowane staˆe, w tym rozdziale znajdziesz ich
opis.
:ul compact.
:li.Staˆe zakresu szukania :link reftype=hd refid=CDDB_SCOPE.CDDB_SCOPE:elink.
:li.Staˆe nazywania p¢l :link reftype=hd refid=CDDB_VALNAME.CDDB_VALNAME:elink.
:li.Staˆe zakoäczenia pracy w¥tk¢w :link reftype=hd refid=CDDB_WM.CDDB_WM:elink.
:eul.

.* staˆe CDDB_SCOPE
.*
:h2 name=CDDB_SCOPE.CDDB_SCOPE
:p.
Staˆe z rodziny :hp2.CDDB_SCOPE:ehp2. okre˜laj¥ zakres szukania CD. 
:dl tsize=30 break=none.
:dthd.:hp2.Staˆa:ehp2.
:ddhd.:hp2.Wyja˜nienie:ehp2.
:dt.CDDB_SCOPE_ALL
:dd.Szuka w obu bazach - najpierw w lokalnej (:link refid=undeep reftype=fn.wyszukiwanie "pˆytkie":elink.), potem na sieci.
:dt.CDDB_SCOPE_ALL_DEEP
:dd.Szuka w obu bazach - najpierw w lokalnej (:link refid=deep reftype=fn.wyszukiwanie "gˆ©bokie":elink.), potem na sieci.
:dt.CDDB_SCOPE_LOCAL
:dd.Szuka w tylko w bazie lokalnej (:link refid=undeep reftype=fn.wyszukiwanie "pˆytkie":elink.).
:dt.CDDB_SCOPE_LOCAL_DEEP
:dd.Szuka w tylko w bazie lokalnej (:link refid=deep reftype=fn.wyszukiwanie "gˆ©bokie":elink.).
:dt.CDDB_SCOPE_REMOTE
:dd.Szuka w tylko na sieci.
:edl.

:fn id=undeep.
Wyszukiwanie :hp5.pˆytkie:ehp5. polega na odnajdywaniu CD tylko po nazwie
pliku.
:efn.

:fn id=deep.
Wyszukiwanie :hp5.gˆ©bokie:ehp5. wumusza przeszukiwanie p¢l CDDBID w
ka¾dym z plik¢w bazy.
:efn.

.* staˆe CDDB_VALNAME
.*
:h2 name=CDDB_VALNAME.CDDB_VALNAME
:p.
Staˆe z rodziny :hp2.CDDB_VALNAME:ehp2. sˆu¾¥ do nazywania p¢l, przy
wywoˆaniach funkcji: :link reftype=hd refid=CddbQueryValue.CddbQueryValue:elink.,
:link reftype=hd refid=CddbQueryValueCount.CddbQueryValueCount:elink.,
:link reftype=hd refid=CddbQueryValueLength.CddbQueryValueLength:elink.

:dl tsize=33 break=none.
:dthd.:hp2.Staˆa:ehp2.
:ddhd.:hp2.Pole:ehp2.
:dt.CDDB_VALNAME_CDDBID
:dd.Cddb Id
:dt.CDDB_VALNAME_ARIST
:dd.Artysta
:dt.CDDB_VALNAME_TITLE
:dd.Tytuˆ pˆyty
:dt.CDDB_VALNAME_TTITLE
:dd.Nazwa ˜cierzki
:dt.CDDB_VALNAME_EXTD
:dd.Informacje rozszerzone dla pˆyty
:dt.CDDB_VALNAME_EXTT
:dd.Informacje rozszerzone dla ˜cierzki
:dt.CDDB_VALNAME_PLAYORDER
:dd.Kolejno˜† odtwarzania utwor¢w
:dt.CDDB_VALNAME_OTHER
:dd.Pozostaˆe dane (w tym cz©˜† komentarzy)
:edl.

.* staˆe CDDB_WM
.*
:h2 name=CDDB_WM.CDDB_WM
:p.
Staˆe z rodziny :hp2.CDDB_WM:ehp2. s¥ u¾ywane podczas zawiadamiania aplikacji
(poprzez komunikat :link reftype=hd refid=WM_CDDB.WM_CDDB:elink.) o zakoäczeniu pracy 
jednego z w¥tk¢w moduˆu.

:dl tsize=33 break=none.
:dthd.:hp2.Staˆa:ehp2.
:ddhd.:hp2.Pole:ehp2.
:dt.CDDB_WM_SAVE
:dd.Prac© zakoäczyˆ w¥tek zapisuj¥cy.
:dt.CDDB_WM_QUERY
:dd.Prac© zakoäczyˆ w¥tek pytaj¥cy.
:edl.