#ifndef _UTIL_H_ // Sirve para evitar la doble inclusión de archivos, es decir, evita que un archivo se incluya dos veces
#define _UTIL_H_ // Define la constante _UTIL_H_ para evitar la doble inclusión de archivos

const int KMAXNAME = 20;

enum Exception {
  EXCEPTION_INFL_NOT_FOUND,
  EXCEPTION_WRONG_COMMISSION,
  EXCEPTION_UNKNOWN_SN,
  EXCEPTION_FILE
};



enum Error{
  ERR_DUPLICATED,
  ERR_NOT_FOUND,
  ERR_WRONG_SOCIALNETWORK,
  ERR_WRONG_COMMISSION,
  ERR_UNKNOWN_SN,
  ERR_FILE
};



class Util{
  public:
    // prints an error message
    static void error(Error e);

    // prints exception type (debug)
    static void debug(Exception e);
    
};

#endif
