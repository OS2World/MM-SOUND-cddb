/* ===============================================================
   Warp CD-Copy <prototyp>
   =======================

    $RCSfile: acddbtcp.h,v $
      Author: Bartosz_Tomasik <bart2@asua.org.pl>
       $Date: 1999/09/28 07:46:39 $
   $Revision: 1.2 $
      $State: Exp $
       Notes: Modul obslugi cddb - czesc "sieciowa" (dll)

 Copyright ¸ 1999 Asu'a (http://www.asua.org.pl)
================================================================== */

#ifndef __ACDDBTCP_H__
#define __ACDDBTCP_H__

#include <os2.h>
#include "../acddb.h"

LONG _syscall CddbSockInit();

LONG _syscall _CddbQueryRemote(CDDB_QUERY * query,char *bufor, ULONG *rozmiar,
                      BOOL *bQuit);
#endif /* _ACDDBTCP_H__ */