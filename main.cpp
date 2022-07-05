#ifndef IOSTREAM_H
    #define IOSTREAM_H
    #include <iostream>
#endif
#include <fstream>
#include "Spider.h"
#include <DOMProcessor.h>

using namespace std;

int main()
{
    DOMProcessor dom;
    dom.hello();

    /*
    Spider spider;
    spider.setDomain("https://www.soriana.com");
    spider.setPage("/juguetes/?cref=1&cgid=juguetes&view=grid");
    spider.HTTP_Get();

    string text = spider.chunk.memory;


    int contador = 0;
    string patronInicial = "href=\"";
    string patronFinal = "\"";

    size_t szPosicionDeLaComilla = 0;
    size_t szUltimaCoincidencia = text.find(patronInicial);

    while( szUltimaCoincidencia != string::npos )
    {
        szPosicionDeLaComilla = text.find(patronFinal, szUltimaCoincidencia + patronInicial.size());
        if( szPosicionDeLaComilla != string::npos )
        {
            size_t inicioDelAtributo = szUltimaCoincidencia + patronInicial.size();
            size_t f = szPosicionDeLaComilla - inicioDelAtributo;
            cout << text.substr(inicioDelAtributo, f) << endl;
            contador++;
            szUltimaCoincidencia = text.find(patronInicial, szPosicionDeLaComilla + 1);
        }
    }
    cout << "CONTADOR: " << contador << endl;
    */


    /*
    int e;
    for( size_t i = 0; i < p.text.size(); i++)
    {
        e = 0;
        for(size_t j=0; j < patron.size(); j++ )
        {
            if( patron[e] != p.text[i])
            {
                break;
            }
            else
            {
                if( j == patron.size() - 1)
                {
                    contador++;
                }
                i++;
                e++;
            }
        }
    }
    cout << contador << endl;
    */








    /*
    main: main.cpp
        g++ -Wall Spider.cpp main.cpp -l curl -o main

        COPDIO POSTAL 87400
     _____         _
    |_   _|____  _| |_ ___
      | |/ _ \ \/ / __/ _ \
      | |  __/>  <| || (_) |
      |_|\___/_/\_\\__\___/

    */

    //cout << patron << endl;
    //cout << parrafo.countWord(patron);
/*
    string patron = "data-product-sku=\"";
    size_t pos = parrafo.text.find(patron);
    //string sku = parrafo.text.substr(pos, 6);
    cout << "Posicion Inicial: " << pos << endl;
    //cout << "SKU: " << sku << endl;
  */
    /*
    parrafo.text = "A B A C E D D D E F 88 88 1 1 3 4 5";
    map<string, size_t> listaDeConteo = parrafo.countAllWords();
    for(auto it = listaDeConteo.begin(); it != listaDeConteo.end(); it++ )
    {
        cout << it->first << " : " << it->second << endl;
    }
    */

    /*
    parrafo.text = "1 1 1 1 3";
    map<long, size_t> listaDeConteo = parrafo.countAllNumericStrings();
    for(auto it = listaDeConteo.begin(); it != listaDeConteo.end(); it++ )
    {
        cout << it->first << " : " << it->second << endl;
    }
    */

    /*
    parrafo.text = "programacion";
    map<char, size_t> listaDeConteo = parrafo.countAllLetters();
    for(auto it = listaDeConteo.begin(); it != listaDeConteo.end(); it++ )
    {
        cout << it->first << " : " << it->second << endl;
    }
    */

    // Ejemplo: Conteo de palabras
    /*
    map<string, size_t> listaDeConteo = parrafo.countAllWords();
    for(auto it = listaDeConteo.begin(); it != listaDeConteo.end(); it++ )
    {
        cout << it->first << " : " << it->second << endl;
    }
    */
    // Ejemplo de countCharacter()
    /*
    cout << "Caracteres: "  << parrafo.countCharacter(' ') << endl;
    */

    // Ejemplo de countWord()
    /*
    cout << "Palabras: "    << parrafo.countWord("test") << endl;
    */

    // Ejemplo split()
    /*
    list<string> palabras = parrafo.split(' ');
    list<string>::iterator it;
    for( it = palabras.begin(); it != palabras.end(); it++ )
    {
        cout << "Palabra: " << *it << endl;
    }
    */

    /*
     ____        _     _
    / ___| _ __ (_) __| | ___ _ __
    \___ \| '_ \| |/ _` |/ _ \ '__|
     ___) | |_) | | (_| |  __/ |
    |____/| .__/|_|\__,_|\___|_|
          |_|
    */

    /*
    Spider web;
    web.setDomain("https://www.heb.com.mx/");
    web.setPage("electronica/pantallas.html");
    web.HTTP_Get();
    Texto HTML_Pagina;
    Texto HTML_ol;
    Texto HTML_li;
    size_t pos_ini;
    size_t pos_fin;
    HTML_Pagina.text = web.chunk.memory;
    pos_ini = HTML_Pagina.text.find("<ol");
    pos_fin = HTML_Pagina.text.find("</ol>");
    HTML_ol.text = HTML_Pagina.text.substr(pos_ini, (pos_fin-pos_ini)+5 );
    pos_ini = HTML_ol.text.find("<li");
    pos_fin = HTML_ol.text.find("</li>");
    HTML_li.text = HTML_ol.text.substr(pos_ini, (pos_fin-pos_ini)+5 );
    cout << HTML_li.text;
    */

    /*
    Spider web;
    web.setDomain("https://sii2.matamoros.tecnm.mx");
    web.setPage("/frontend/web/index.php");
    web.HTTP_Get();

    web.HTTP_Post("_csrf-frontend=_2k1Jc62hSFV7Jis4aIjPVxHeT6kP0jrf_HRw0vV9i6KUUFonfTMcz-i9vWgxm4EFzZIWtZdIa4GhpjzGKWuAw%3D%3D&LoginForm%5Busername%5D=19260056&LoginForm%5Bpassword%5D=1196&LoginForm%5BrememberMe%5D=0&LoginForm%5BrememberMe%5D=1&login-button=");

    web.setPage("/frontend/web/index.php");
    web.HTTP_Get();

    web.setPage("frontend/web/index.php?r=alu%2Fdefault");
    web.HTTP_Get();
    */
    return 0;
}
