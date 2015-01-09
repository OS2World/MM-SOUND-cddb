/* ===============================================================
   Warp CD-Copy
   =======================

    $RCSfile: acddbtcp.c,v $
      Author: Bartosz_Tomasik <bart2@asua.org.pl>
       $Date: 1999/09/28 07:46:39 $
   $Revision: 1.0 $
      $State: Exp $
       Notes: Modul obslugi cddb - czesc "sieciowa" (dll)

 Copyright ¸ 1999 Asu'a (http://www.asua.org.pl)
================================================================== */

/* Special calling convention for LibMain() for compatibility
   when -3r, -4r, -5r or -6r compiler option is used
   (register calling convention).
*/
#pragma aux LibMain "*"    \
            parm caller [] \
            value no8087   \
            modify [eax ecx edx];

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "acddbtcp.h"
#include "..\..\astring\astring.h"


//inicjalizujemy sockety do uzycia
LONG _syscall CddbSockInit()
{
  if (sock_init()) return ERR_CDDB_OK;
  return ERR_CDDB_SOCKINITFAILED;
}


//dwie pomocnicze funckje - odbierajaca i wysylajaca dane
int writeln(char *buf,int sock)
{
   int rc;
   rc=send(sock,buf,strlen(buf),0);
   return rc;
};

int readln(char *buf,LONG bufSize, int sock)
{
   int rc;
   rc=recv(sock,buf,bufSize,0);
   return rc;
};

//funkcja douwalniania pamieci od 2 stringow i zamykania podanego socketa
//zmniejsza objetosc kodu i programu - jesli nic nie bedzie sie sypac
//to i tak bedzie zadko wywolywana
void freeBufsAndSock(int cddbSock, char *buf1, char *buf2)
{
     soclose(cddbSock);
     free(buf1);
     free(buf2);
};

//inicjalizacja dll'a
 unsigned LibMain(unsigned hmod, unsigned term)
  {
    if(term)
    { // DLL termination
    }
    else
    { // DLL initialization
    }
    // Succesfull completion (no errors)
    return(1);
  }

//funkcja odpowiedzialna za 'pytanie' servera
LONG _syscall _CddbQueryRemote(CDDB_QUERY * query,char *bufor, ULONG *rozmiar,
                      BOOL *bQuit)
{
   int cddbSock; //nasz socket u¾ywany do poˆ¥czenia
   int rc,faza; //returncode i w kt¢rej fazie poˆ¥czenia jeste˜my
   int rc2;//przydatne w case 3, gdzie potrzebujemy (choc na chwile)
           //jeszcze jedna zmienna do trzymania rozmiaru tego co przyszlo z sieci
   BOOL wyjscie=FALSE;//wyj˜cie z p©tli odbieraj¥co-wysyˆaj¥cej
   struct sockaddr_in local; //struktura adresowa
   struct hostent *phostInfo;//info na temat serwera..
   char *recvBuf,*tmpbuf; //bufory odbieraj¥cy i pomocniczy
   LONG i=0,wsk; //wskazniki dla bufora danych
   char *hostname;//bufor na nasz adres

   //alokujemy pami©† pod odbi¢r danych
   recvBuf=(char *) malloc(2048);
   //czy si© udaˆo?
   if (recvBuf==NULL) return ERR_CDDB_MEMALLOCFAILED;

   //alokujemy pami©† pod nazw© naszego hosta
   hostname=(char *) malloc(257); //na wszelki wypadek +1 ;)
   //czy si© udaˆo?
   if (hostname==NULL)
   {
    free(recvBuf);
    return ERR_CDDB_MEMALLOCFAILED;
   };

   //nie wiem czemu ale tu te¾ musi by† rodzina adres¢w ustawiana
   //dawniej tak nie robiˆem i dziaˆaˆo...
   local.sin_family=AF_INET;

   //ustalenie rodziny adres¢w
   cddbSock=socket(AF_INET, SOCK_STREAM,0);
   if (cddbSock<0) return ERR_CDDB_SETSOCKFAILED;

  if (*bQuit==TRUE)
  {
     freeBufsAndSock(cddbSock,recvBuf,hostname);
     return ERR_CDDB_ABORTED;
  };

   //czy jest podany jaki˜ nasz host?
   if (strlen(query->Hostname)==0)
   {
     gethostname(hostname,256);
   }  else hostname=query->Hostname;

   //sprawdzamy czy adres jest podany w formacie numerkowym
   if ((local.sin_addr.s_addr=inet_addr(query->pszServer))==INADDR_NONE)
      {
      //nie jest wi©c pobieramy adres z serwera DNS
       phostInfo=gethostbyname(query->pszServer);
       //jesli sie nie udalo zwracamy 0
       if (phostInfo==NULL)
       {
         freeBufsAndSock(cddbSock,recvBuf,hostname);
         return ERR_CDDB_DNSFAILED;
       };
       //jesli sie udalo zapisujemy adres
       local.sin_addr.s_addr=*((unsigned long*)phostInfo->h_addr);
      };

  if (*bQuit==TRUE)
  {
     freeBufsAndSock(cddbSock,recvBuf,hostname);
     return ERR_CDDB_ABORTED;
  };

  //ustalamy port
  local.sin_port = htons(query->lPort);
  //ˆ¥czymy si© z serwerem
  if ((rc=connect(cddbSock,(struct sockaddr*) &local,sizeof(local)))==-1)
     {
      freeBufsAndSock(cddbSock,recvBuf,hostname);
      return ERR_CDDB_CONNECTFAILED;
     };

 //pocz¥tek konwersacji
 faza=0;

 while (wyjscie==FALSE)
 {
  //tmpbuf="";
  memset(recvBuf,0,2048);//zerujemy bufor wej˜ciowy ¾eby nie zostawaˆy jakie˜ ˜mieci..

  //odbieramy dane z serwera
  rc=readln(recvBuf,2048,cddbSock);
  //czy si© udaˆo?
  if (rc<0)
  {
     freeBufsAndSock(cddbSock,recvBuf,hostname);
     return ERR_CDDB_RECVFAILED;
  };
  //sprawdzamy czy przypadkiem nie powinnismy wczesniej zakonczyc pracy
  if (*bQuit==TRUE)
  {
     freeBufsAndSock(cddbSock,recvBuf,hostname);
     return ERR_CDDB_ABORTED;
  };
  //w zale¾no˜ci od tego w kt¢rej fazie konwersacji jeste˜my..
  switch (faza)
  {
     case 0:
        //sam pocz¥tek serwer nas wita:
        // XXX hostname CDDBP server version ready at date
        //gdzie XXX to 200(read write access) lub 201(tylko read)
        tmpbuf=astrwrd(recvBuf,1);
        rc=atoi(tmpbuf);
        if ((rc!=200)&&(rc!=201))
        {
         freeBufsAndSock(cddbSock,recvBuf,hostname);
         return ERR_CDDB_WRONGDATA;
        } else
        {
           //ok, baner byˆ musimy sie teraz my przedstawi†
           //cddb hello User host.com.pl Client ver

           //alokujemy pami©† pod tmpbuf... (to byl ten bug!)
           tmpbuf=(char *) malloc(300);
           //czy si© udaˆo?
           if (tmpbuf==NULL)
           {
             freeBufsAndSock(cddbSock,recvBuf,hostname);
             return ERR_CDDB_MEMALLOCFAILED;
            };
           sprintf(tmpbuf,"%s %s %s %s %s\n\0","cddb hello",query->Username,hostname,query->Clientame,query->Version);
           faza++;
        }; break;
     case 1:
        //po przedstawieniu si©, powinien nam odpowiedzie†
        tmpbuf=astrwrd(recvBuf,1);
        rc=atoi(tmpbuf);
        if (rc!=200)
        {
           freeBufsAndSock(cddbSock,recvBuf,hostname);
           free(tmpbuf);
           return ERR_CDDB_WRONGDATA;
        } else
        {
           free(tmpbuf);
           //odpowiedziaˆ teraz pytamy si© o nasz CD
           tmpbuf=astrcon(query->pszCddbStr,"\n");
           faza++;
        }; break;
     case 2:
        //po pytaniu, powienien powiedzie†, ¾e jest lub ¾eby˜my zje¾dzali..
        tmpbuf=astrwrd(recvBuf,1);
        rc=atoi(tmpbuf);
        switch (rc)
        {
           case 200:
              free(tmpbuf);
              //jest!! no to odczytujemy..
              tmpbuf= astrcon("cddb read ",
              astrcon(astrsbstr(recvBuf,4,13+astrlnofwrd(recvBuf,2)),"\n"));
              faza++;
              break;
           case 211:
              //jest lista trzeba wybrac
              //na razie nie obslugujemy :>
           default:
              freeBufsAndSock(cddbSock,recvBuf,hostname);
              free(recvBuf);
              return ERR_CDDB_CDNOTFOUND;
        }; break;
     case 3:
        //tu leci 'nagˆ¢wek' danych
        rc2=rc;//zapamietanie rozmiaru danych z sieci...
        tmpbuf=astrwrd(recvBuf,1);
        rc=atoi(tmpbuf);
        if (rc!=210)
        {
           freeBufsAndSock(cddbSock,recvBuf,hostname);
           free(tmpbuf);
           return ERR_CDDB_WRONGDATA;
        } else
        {
          //okazalo sie, ze oprocz informacji ze dane sa i beda, pojawiaja sie
          //od razu same dane... tak wiec tutaj zapis do bufora z pominieciem
          //pierwszej lini

             //opuszczamy pierwsza linie
             for (wsk=0;recvBuf[wsk]!='\n';wsk++);
             wsk++; //przeskakujemy jeszcze ten koniec lini..

             //sprawdzamy czy nam sie to zmiesci w buforze..
             if (i+(rc2-wsk)>*rozmiar)
             {
                *rozmiar+=(rc2-wsk); //zwiekszamy o bufor tyle ile odczytalismy
                bufor = (char *) realloc(bufor, *rozmiar);//i realloc
                if (bufor==NULL)
                {
                   freeBufsAndSock(cddbSock,recvBuf,hostname);
                   return ERR_CDDB_MEMALLOCFAILED;
                 };
              };

              //przepisujemy do bufora
              //(tu jest swiadomie uzyte i=0!)
              for (i=0;wsk<rc2;wsk++) bufor[i++]=recvBuf[wsk];
              *rozmiar=i; //zwracamy ile jest danych w tablicy

           tmpbuf="";
           faza++;
        }; break;
     case 4:
        //tu sa teraz dane.. dopoki nie ma '.' wszystko pakujemy do bufora..
        if (recvBuf[0]=='.')
        {
         //jest kropka znaczy sie koniec danych, mozemy sie rozlaczyc
         tmpbuf="quit";
         faza++;
         wyjscie=TRUE;

         //ale zanim juz pojdziemy sobie, musimy te kropke dodac do bufora
         //(uzywana pozniej przez funkcje parse!)

         //sprawdzamy czy nam sie to zmiesci w buforze..
           if (i+2>*rozmiar)
           {
              *rozmiar+=1; //zwiekszamy o bufor tyle ile odczytalismy
              bufor = (char *) realloc(bufor, *rozmiar);//i realloc
              if (bufor==NULL)
              {
                 freeBufsAndSock(cddbSock,recvBuf,hostname);
                 return ERR_CDDB_MEMALLOCFAILED;
               };
            };
            bufor[i++]='.';

        } else
        {  //zapis do bufora
           //sprawdzamy czy nam sie to zmiesci w buforze..
           if (i+rc>*rozmiar)
           {
              *rozmiar+=rc; //zwiekszamy o bufor tyle ile odczytalismy
              bufor = (char *) realloc(bufor, *rozmiar);//i realloc
              if (bufor==NULL)
              {
                 freeBufsAndSock(cddbSock,recvBuf,hostname);
                 return ERR_CDDB_MEMALLOCFAILED;
               };
            };
            //przepisujemy do bufora
            for (wsk=0;wsk<rc;wsk++) bufor[i++]=recvBuf[wsk];
            *rozmiar=i; //zwracamy ile jest danych w tablicy
        }; break;
     default:
        //je˜li jeste˜my tu.. to co˜ sie nie«le pokieˆbasiˆo..
        freeBufsAndSock(cddbSock,recvBuf,hostname);
        return ERR_CDDB_WRONGDATA;
  };
  //jesli jest co, to wysyˆamy to do serwera
  if (strlen(tmpbuf)>0)
  {
     rc=writeln(tmpbuf,cddbSock);
     if (rc<0) //czy udaˆo si© wysˆa†?
     {
        freeBufsAndSock(cddbSock,recvBuf,hostname);
        free(tmpbuf);
        return ERR_CDDB_SENDFAILED;
     };
  };//if (strlen(tmpbuf)>0)
  free(tmpbuf);
 };//while (wyjscie==FALSE)

   //koniec funkcji..
   freeBufsAndSock(cddbSock,recvBuf,hostname);
   return ERR_CDDB_OK;
}
