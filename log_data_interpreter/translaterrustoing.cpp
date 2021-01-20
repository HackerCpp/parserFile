#include "translaterrustoing.h"
#include <QDebug>

QHash<QString,QString> TranslaterRusToIng::f_dictionary;

TranslaterRusToIng::TranslaterRusToIng(){
    f_dictionary.reserve(200);
    f_dictionary.insert("А","A");f_dictionary.insert("а","a");
    f_dictionary.insert("Б","B");f_dictionary.insert("б","b");
    f_dictionary.insert("В","V");f_dictionary.insert("в","v");
    f_dictionary.insert("Г","G");f_dictionary.insert("г","g");
    f_dictionary.insert("Д","D");f_dictionary.insert("д","d");
    f_dictionary.insert("Е","E");f_dictionary.insert("е","e");
    f_dictionary.insert("Ё","YO");f_dictionary.insert("ё","yo");
    f_dictionary.insert("Ж","J");f_dictionary.insert("ж","j");
    f_dictionary.insert("З","Z");f_dictionary.insert("з","z");
    f_dictionary.insert("И","I");f_dictionary.insert("и","i");
    f_dictionary.insert("Й","I");f_dictionary.insert("й","i");
    f_dictionary.insert("К","K");f_dictionary.insert("к","k");
    f_dictionary.insert("Л","L");f_dictionary.insert("л","l");
    f_dictionary.insert("М","M");f_dictionary.insert("м","m");
    f_dictionary.insert("Н","N");f_dictionary.insert("н","n");
    f_dictionary.insert("О","O");f_dictionary.insert("о","o");
    f_dictionary.insert("П","P");f_dictionary.insert("п","p");
    f_dictionary.insert("Р","R");f_dictionary.insert("р","r");
    f_dictionary.insert("С","S");f_dictionary.insert("с","s");
    f_dictionary.insert("Т","T");f_dictionary.insert("т","t");
    f_dictionary.insert("У","U");f_dictionary.insert("у","u");
    f_dictionary.insert("Ф","F");f_dictionary.insert("ф","f");
    f_dictionary.insert("Х","H");f_dictionary.insert("х","h");
    f_dictionary.insert("Ц","C");f_dictionary.insert("ц","c");
    f_dictionary.insert("Ч","Ch");f_dictionary.insert("ч","ch");
    f_dictionary.insert("Ш","Sh");f_dictionary.insert("ш","sh");
    f_dictionary.insert("Щ","Sh");f_dictionary.insert("щ","sh");
    f_dictionary.insert("Ъ","");f_dictionary.insert("ъ","");
    f_dictionary.insert("Ь","");f_dictionary.insert("ь","");
    f_dictionary.insert("Ы","bl");f_dictionary.insert("ы","bl");
    f_dictionary.insert("Э","A");f_dictionary.insert("э","a");
    f_dictionary.insert("Ю","YU");f_dictionary.insert("ю","yu");
    f_dictionary.insert("Я","YA");f_dictionary.insert("я","ya");
    f_dictionary.insert("(","(");f_dictionary.insert(")",")");
    f_dictionary.insert(".",".");f_dictionary.insert(",",",");
    f_dictionary.insert(" ","_");f_dictionary.insert("  ","_");
}


QString TranslaterRusToIng::translate(QString string){
    QString f_str;
    f_str.reserve(string.size());
    foreach(auto value,string){
        f_str.append(f_dictionary.value(value,value));
    }
    return f_str;
}
