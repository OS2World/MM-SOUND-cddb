.* Moduˆ CDDB
.* Rozdziaˆ 2 "Typy danych"
.*   grupa 30  - okna opisuj¥ce znaczenie p¢l struktur
.*
:h1 res=002.Struktury danych
:p. Struktury danych u¾ywane w programie przez funkcje
:link reftype=hd refid=CddbCreateQuery.CddbCreateQuery:elink. i
:link reftype=hd refid=CddbSave.CddbSave:elink..

.* struktura CDDB_QUERY
.*
:h2 name=CDDB_QUERY.CDDB_QUERY
:p.
:hp2.CDDB_QUERY:ehp2. Struktura przekazywana jako parametr do funckji
CddbCreateQuery,
zawiera niezb©dne elementy zapytania o CD.
:cgraphic.
typedef struct
{ 
 PSZ   :link group=30 dependent reftype=hd refid=cddb_str.pszCddbStr:elink.; //ciag znakow dla komendy Query (zawiera cddb id)
 PSZ   :link group=30 dependent reftype=hd refid=psz_path.pszPath:elink.;    //sciezka do lokalnej bazy danych
 PSZ   :link group=30 dependent reftype=hd refid=psz_server.pszServer:elink.;  //nazwa servera cddb
 LONG  :link group=30 dependent reftype=hd refid=l_port.lPort:elink.;    //port servera cddb
 ULONG :link group=30 dependent reftype=hd refid=l_cdnum.lCdNum:elink.;   //numer CD ktorego dotyczy zapytanie
 BYTE  :link group=30 dependent reftype=hd refid=b_scope.bScope:elink.;   //zakres pytania - patrz stale :link group=30 dependent reftype=hd refid=CDDB_SCOPE.CDDB_SCOPE_*:elink.
} CDDB_QUERY;
:ecgraphic.

:h2 name=cddb_str hide.pszCddbStr
:dl tsize=3 break=all.
:dt.:hp2.pszCddbStr (PSZ):ehp2.
:dd.Wska«nik do ci¥gu ASCIIZ - zawieraj¥cego kompletn¥ komend© "cddb query"
:edl.

:h2 name=psz_path hide.pszPath
:dl tsize=3 break=all.
:dt.:hp2.pszPath (PSZ):ehp2.
:dd.Wska«nik do ci¥gu ASCIIZ - zawieraj¥cego scierzk© dost©pu do lokalnej bazy cddb.
:edl.

:h2 name=psz_server hide.pszServer
:dl tsize=3 break=all.
:dt.:hp2.pszServer (PSZ):ehp2.
:dd.Wska«nik do ci¥gu ASCIIZ - zawieraj¥cego nazw© serwera cddb.
:edl.

:h2 name=l_port hide.lPort
:dl tsize=3 break=all.
:dt.:hp2.lPort (LONG):ehp2.
:dd.Czterobajtowa liczba bez znaku - port z jakim si© l¥czymy na serwerze.
:edl.

:h2 name=l_cdnum hide.lCdNum
:dl tsize=3 break=all.
:dt.:hp2.lCdNum (LONG):ehp2.
:dd.Czterobajtowa liczba bez znaku - kt¢rego nap©du CD w systemie dotyczy zapytanie.
:edl.

:h2 name=b_scope hide.bScope
:dl tsize=3 break=all.
:dt.:hp2.bScope (BYTE):ehp2.
:dd.Jedno bajtowa liczba - okre˜la :link reftype=hd refid=CDDB_SCOPE.zakres:elink. pytania.
:edl.