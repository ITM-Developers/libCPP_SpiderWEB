#ifndef SPIDER_H
#define SPIDER_H

#ifndef CSTRING_H
    #define CSTRING_H
    #include <cstring>
#endif

#ifndef IOSTREAM_H
    #define IOSTREAM_H
    #include <iostream>
#endif

#ifndef STRING_H
    #define STRING_H
    #include <string>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

using namespace std;

struct MemoryStruct {
  char *memory;
  size_t size;
};

class Spider
{
private:
    CURLcode curlcode;              //Codigos de Respuesta se Usa para manejar Errores
    CURL* curl;                     //Curl Handler instancia de la clase curl para hacer las peticiones HTTP
    FILE* stream;                   //Stream a donde se envian los datos (Archivos, Consola, etc) por omision es STDOUT

    //Variables de Configuracion
    string sDomino;                 // Indica el Dominio (URL base) del sitio WEB
    string sPagina;                 // Indica la Pagina en la cual se va a hacer la Peticion HTTP
    string sBrowserUserAgent;       // User Agent a usar por omision. Tiene el de mozilla firefox para evitar ser detectado como un bot
    string sCookieFilename;         // Nombre del Archivo que almacena las cookies para lectura y escritura
    string sRawCookies;             // Cookies en formato crudo alamacenadas en memoria las demas estan el fichero $this->sCookieFilename

    bool HEADERS_ENABLE;            // Valor logico que indica si los headers deben mostrarse en las Peticiones HTTP
    bool BODY_ENABLE;               // Valor Logico que indica si el body de las peticiones HTTP deben mostarse
public:
    struct MemoryStruct chunk;
    Spider();
    ~Spider();

    void setDomain(const string DomainName);                   string getDomain();
    void setPage(const string Page);                           string getPage();
    void setBrowserUserAgent(const string BrowserAgent);       string getBrowserUserAgent();
    void setCookieFile(const string CookieFile);               string getCookieFile();
    void setRawCookies(const string RawCookies);               string getRawCookies();
    //void setStream(FILE *value);                             FILE* getStream();

    //Peticiones HTTP Disponibles
    void HTTP_Post(const string &DataToPost);   // Realiza Peticion HTTP POST
    void HTTP_Get();                            // Realiza la Peticion HTTP GET
    void HTTP_Head();                           // Solo envia Headers
private:
    static size_t writeDataOnStream(void * buffer, size_t size, size_t nbytes, void * stream);
    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif // SPIDER_H
