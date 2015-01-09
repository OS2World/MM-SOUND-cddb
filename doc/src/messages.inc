.* modul CDDB
.* Rozdziaà 3 "Komunikaty"
.*
:h1 res=003.Komunikaty CDDB
:p.Moduà CDDB, korzysta tylko z jednego komunikatu:
:link reftype=hd refid=WM_CDDB.WM_CDDB:elink., jego opis znajduje si© w tym
rozdziale.


.* msg "WM_CDDB"
.*
:h2 x=left width=25% scroll=none clear name=WM_CDDB.WM_CDDB
:link dependent group=40 reftype=hd auto refid=WM_CDDB_S.
:p.Wybierz temat&colon.
:p.
:link dependent group=40 reftype=hd refid=WM_CDDB_S.Skàadnia:elink.
.br
:link dependent group=41 reftype=hd refid=WM_CDDB_P.Parametry:elink.
.br
:link dependent group=43 reftype=hd refid=WM_CDDB_N.Opis:elink.


.* SKùADNIA
:h2 x=25% width=75% hide name=WM_CDDB_S.Skàadnia - WM_CDDB
:p.
Ten komunikat informuje o zako‰czeniu pracy jednego z w•tk¢w moduàu.
:cgraphic.
param1
     SHORT sThreadType; //informuje jaki typ w•tku zostaà zako‰czony..
     SHORT sReturnCode; //kod powrotu...
param2
     ULONG ulCdNum;      //dla kt¢rego CD byà ten w•tek
:ecgraphic.


.* PARAMETRY
:h2 x=60% width=40% hide name=WM_CDDB_P.Parametry - WM_CDDB
:dl tsize=3 break=all.
:dt.:hp2.sThreadType:ehp2. (SHORT) - parametr.
:dd. Staàa z rodziny :link reftype=hd refid=CDDB_WM.CDDB_WM:elink.
 informuje, jakiego typu byà to w•tek.
:p. Nap©dy numerowane s• od 1.
:dt.:hp2.sReturnCode:ehp2. (SHORT) - parametr.
:dd. Kod powrotu/bà©du zako‰czenia w•tku.
:p. Nap©dy numerowane s• od 1.
:dt.:hp2.ulCdNum:ehp2. (ULONG) - parametr.
:dd. Logiczny numer nap©du dla kt¢rego byà wywoàany w•tek.
:p. Nap©dy numerowane s• od 1.
:edl.

.* OPIS
:h2 x=60% width=40% hide name=WM_CDDB_N.Opis - WM_CDDB
:p.Komunikat, jest wysyàany przez moduà do aplikacji w momencie kiedy jeden z
w•tk¢w pytaj•cych lub zapisuj•cych ko‰czy prac©. Ty w•tku, kod powrotu oraz
numer CD dla kt¢rego byl on wywoàany przekazywane s• w parametrach.