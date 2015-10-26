#ifndef ELEMENT_H
#define ELEMENT_H

#define I(n, g) ((n) * (dd->G) + (g))

int index(SEXP obj, const char *str){
  int i = -1;
  SEXP names = getAttrib(obj, R_NamesSymbol);
  for (i = 0; i < length(obj); ++i)
    if(strcmp(CHAR(STRING_ELT(names, i)), str) == 0)
      break;
  return i;
}

SEXP le(SEXP obj, const char *str){
  return VECTOR_ELT(obj, index(obj, str));
}

int *li(SEXP obj, const char *str){
  return INTEGER(le(obj, str));
}

double *lr(SEXP obj, const char *str){
  return REAL(le(obj, str));
}

int vi(SEXP obj, const char *str){
  return INTEGER(obj)[index(obj, str)];
}

double vr(SEXP obj, const char *str){
  return REAL(obj)[index(obj, str)];
}

#endif // ELEMENT_H
