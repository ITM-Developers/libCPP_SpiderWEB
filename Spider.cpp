#include "Spider.h"

/**
 * @brief Construct a new Spider::Spider object
 *
 */
Spider::Spider()
{
    this->stream            = stdout;
    this->HEADERS_ENABLE    = true;
    this->BODY_ENABLE       = true;
    this->sCookieFilename   = "Cookies.txt";
    this->sBrowserUserAgent = "Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0";

    chunk.memory = (char*) malloc(1);   // will be grown as needed by the realloc above
    chunk.size = 0;                     // no data at this point


    if ( (curl = curl_easy_init()) != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION,    CURL_HTTP_VERSION_2_0);

        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,   writeDataOnStream);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, this->stream);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        curl_easy_setopt(curl, CURLOPT_USERAGENT,       this->sBrowserUserAgent.c_str());
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE,      this->sCookieFilename.c_str());       //For Reading
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR,       this->sCookieFilename.c_str());       //For writing
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    }
}

Spider::~Spider()
{
    if( curl != NULL)
        curl_easy_cleanup(curl);
    fclose(stream);
    free(chunk.memory);
}

/**
 * ======================================================================================================================
 * @brief Spider::WriteMemoryCallback
 *
 * @param contents
 * Puntero a char que almacena el contenido respondido por el servidor.
 *
 * @param size
 * Esta variable siempre es 1
 *
 * @param nmemb
 * Es el tamano de bytes que estan en el puntero contents.
 *
 * @param userp
 *
 * @return
 * @see https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
 * @see https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
 */
size_t Spider::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char*) realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

/**
 * ======================================================================================================================
 * @brief Spider::writeDataOnStream
 * @param buffer
 * @param size
 * @param nbytes
 * @param stream
 * @return
 * @see https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
 * @see https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
 */
size_t Spider::writeDataOnStream(void * buffer, size_t size, size_t nbytes, void * stream){
    size_t bytes_written = fwrite( buffer, size, nbytes, (FILE *) stream);
    return bytes_written;
}

/**
 * ======================================================================================================================
 * @brief
 * Esta Funcion solo establece el dominio en el cual va a trabajar la spider, para evitar tener que  estar  indicando
 * el dominio  en  cada  peticion  se  indica una sola vez y se almacena el valor en la clase spider y todas las operaciones
 * posteriores seran en funcion de este dominio a menos que se establesca otro diferente de nuevo con esta funcion.
 *
 * Ejemplo: setDomain("https://www.heb.com.mx/");
 *
 * @param string DomainName
 * Es un string que indica el FQDN "Fully Qualified Domain Name" Nombre de Dominio completo.
 */
void Spider::setDomain(const string DomainName)
{
    this->sDomino = DomainName;
    curl_easy_setopt(curl, CURLOPT_URL, this->sDomino.c_str());
}
string Spider::getDomain()
{
    return this->sDomino;
}

/**
 * ======================================================================================================================
 * @brief
 * Es importante aclarar que el nombre de la pagina debe ser relativo a la ruta del dominio principal, por ejemplo, si se
 * quiere pedir la pagina  "index.php"  del dominio   "www.mydomain.com"  se  llamaria  a  la  funcion  de  la  siguiente
 * manera setPage("index.php");  Ademas es necesario especificar el dominio antes de llamar a esta funcion, el dominio se
 * indica  con la funcion setDomain("www.mydominio.com").
 *
 * @see     setDomain()
 *
 * @param   Page
 * Un string que indica la pagina que se quiere consultar ya sea por el procedimiento POST o GET del protocolo HTTP.
 *
 * @return  No retorna ningun valor
 */
void Spider::setPage(const string Page)
{
    string URI = this->sDomino + Page;
    this->sPagina = URI;
    curl_easy_setopt(curl, CURLOPT_URL, URI.c_str());
}
string Spider::getPage()
{
    return this->sPagina;
}

/**
 * ======================================================================================================================
 * @brief
 * Asigna el "user agent" que es un string con informacion del software (navegador web) del cliente que se  va  a incluir
 * en las cabeceras de todas las peticiones posteriores, algunos servidores no aceptan peticiones  HTTP  si esta cabecera
 * no se ha indicado ya que detecta que el cliente es un bot,  no es  necesario  llamar a  esta  funcion ya que de manera
 * predeterminada se envia el siguiente User Agent:
 *
 * "Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0"
 *
 * @param   value
 * Es un string que sera usado como el UserAgent al momento de mandar las peticiones
 */
void Spider::setBrowserUserAgent(const string value)
{
    this->sBrowserUserAgent = value;
    curl_easy_setopt(curl, CURLOPT_USERAGENT, this->sBrowserUserAgent.c_str());
}
string Spider::getBrowserUserAgent()
{
    return this->sBrowserUserAgent;
}

/**
 * ======================================================================================================================
 * @brief
 * Asigna el nombre del fichero que el programa necesita para almacenar  cookies,  en  caso  de  que  las  respuestas  de
 * las peticiones HTTP asi lo indiquen.
 *
 * @param   value
 * Nombre del Fichero en donde se alamcenan y/o leen las cookies
 */
void Spider::setCookieFile(const string value)
{
    this->sCookieFilename = value;
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, &this->sCookieFilename);      //For Reading
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, &this->sCookieFilename);       //For writing
}
string Spider::getCookieFile()
{
    return this->sCookieFilename;
}

/**
 * ======================================================================================================================
 * @brief
 * Indica las cookies que son permantes y  no cambian en  las peticiones,  Por ejemplo:  las  cookies  de  session. Estas
 * cookies deben estar en formato crudo como se muestra a continuacion: var=valor&var2=valor2. Tambien se pueden  indicar
 * en la funcion HTTP_Post directamente como parametro pero es recomendable usarlo solo  para  otros  datos  como  los de
 * formularios. Si no entiendes esta funcion investiga como es el formato de las cookies en el siguiente enlace:
 *
 * https://curl.haxx.se/docs/http-cookies.html
 *
 * @param   rawCookie
 * Las cookies en formato crudo a enviar en las proximas peticiones.
 */
void Spider::setRawCookies(const string rawCookie)
{
    this->sRawCookies = rawCookie;
    curl_easy_setopt(curl, CURLOPT_COOKIE, this->sRawCookies.c_str());
}
string Spider::getRawCookies()
{
    return this->sRawCookies;
}

/**
 * ======================================================================================================================
 * @brief
 * Indica el stream a donde se van a enviar los datos,  el  constructor  de la clase por default asigna el stream  stdout
 * (salida por pantalla), si deseas que los datos se escriban en un fichero puedes crear una instancia de FILE  y pasarle
 * ese puntero a esta funcion para que escriba la informacion en un archivo de texto plano. No se  debe cerrar el fichero
 * con fclose(), la clase de libcurl lo hace al finalizar la escritura.
 * Por ejemplo:
 *
 * FILE * file;
 * file = fopen("page.txt","w+");
 * setStream( file );
 *
 * o Tambien
 *
 * setStream( fopen("pagina.txt","w") );
 */
/*
void Spider::setStream(FILE* fileStream)
{
    this->stream = fileStream;
    curl_easy_setopt( this->curl, CURLOPT_WRITEDATA, this->stream );
}
*/

/**
 * ======================================================================================================================
 * @brief
 * Realiza un POST del protocolo HTTP y envia los datos al dominio establecido con la funcion  setDomain()  y a la pagina
 * indica con setPage() los datos que se envian se pasan  como  argumento  y  deben  estar  en  formato  crudo.  Mirar el
 * protocolo post y como se envian los datos.
 *
 * @param   value
 * String con los datos que se van a enviar por POST
 */
void Spider::HTTP_Post(const string &value){
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, value.c_str());
    curlcode = curl_easy_perform(curl);
}

/**
 * ======================================================================================================================
 * @brief
 * Realiza una peticion http get al dominio establecido con la funcion setDomain() y  pide  la  pagina establecida con la
 * funcion setPage() si no se establece ninguna pagina se solicita el index del dominio.
 */
void Spider::HTTP_Get(){
    this->BODY_ENABLE = true;
    //Indicamos que se incluya el BODY en la Peticion HTTP
    this->curlcode = curl_easy_setopt( this->curl, CURLOPT_NOBODY, 0L );
    //Ejecutamos la Peticion
    this->curlcode = curl_easy_perform( this->curl );
}

/**
 * ======================================================================================================================
 * @brief
 * Este metodo podriamos verlo de manera analogica a un switch, es decir, cuando  llamas  a  la funcion se desactivan los
 * headers ( No se guardan en el buffer ) y cuando la vuelves a  llamar  se activan nuevamente, se agrego este metodo por
 * que en algunas ocasiones es muy util ver  los  headers que se estan mandando en una peticion y/o ver los header de las
 * respuestas a tus peticiones, sin embargo en algunas otras ocasiones no los necesitamos.
 */
void Spider::HTTP_Head()
{
    BODY_ENABLE = false;              this->curlcode = curl_easy_setopt( this->curl, CURLOPT_NOBODY, 1L);
    HEADERS_ENABLE = true;            this->curlcode = curl_easy_setopt( this->curl, CURLOPT_HEADER, 1L);
    curlcode = curl_easy_perform( this->curl );
}
