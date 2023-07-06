#include "tvectorcom.h"

TVectorCom::TVectorCom() {
   tamano = 0;
   c = NULL;
}
TVectorCom::TVectorCom(int tam) {
   if(tam <= 0) {
      tamano = 0;
      c = NULL;
   }
   else {
      c = new TComplejo [tam];
      tamano = tam;
   }
}
TVectorCom::TVectorCom(const TVectorCom &tv) {
   if(tv.tamano == 0) {
      tamano = 0;
      c = NULL;
   }
   else {
      tamano = tv.tamano;
      c = new TComplejo[tv.tamano];
      for(int i = 0;i < tamano; i++) {
         c[i] = tv.c[i];
      }
   }
}
TVectorCom::~TVectorCom() {
   if(c != NULL) {
      delete [] c;
      c = NULL;
      tamano = 0;
   }
}
TVectorCom &TVectorCom::operator=(const TVectorCom &tv) {
   if(this != &tv) {
      this->~TVectorCom();
      if(tv.c != NULL) {
         tamano = tv.tamano;
         c = new TComplejo [tamano];
         for(int i = 0;i < tamano; i++) {
         c[i] = tv.c[i];
         }
      }
   }
   return *this;
}
bool TVectorCom::operator==(const TVectorCom &tv) const{
   bool iguales = false;

   if(tamano == tv.tamano) {
      for(int i = 0;i < tamano;i++) {
         if(c[i] == tv.c[i]) {
            iguales = true;
         }
      }
   }
   return iguales;
}
bool TVectorCom::operator!=(const TVectorCom &tv) const{
   return !(*this == tv);
}
TComplejo &TVectorCom::operator[](int pos) {
   if(pos >= 1 && pos <= tamano) {
      return c[pos - 1];
   }
   else {
      return error;
   }
}
TComplejo TVectorCom::operator[](int pos) const {
   if(pos >= 1 && pos <= tamano) {
      return c[pos - 1];
   }
   else {
      return error;
   }
}
int TVectorCom::Tamano() const{
   return tamano;
}
int TVectorCom::Ocupadas() const{
   int ocupadas = 0;
   TComplejo tc;
   // for(int i = 0;i < tamano;i++) {
   //    tc = c[i];
   //    if(!(tc == TComplejo())) {
   //       ocupadas++;
   //    }
   // }
   for(int i = 0;i < tamano;i++) {
      if(c[i] != TComplejo()) {
         ocupadas++;
      }
   }
   return ocupadas;
}
bool TVectorCom::ExisteCom(const TComplejo &tc) const{
   bool existe = false;
   for(int i = 0; i < tamano; i++){
		if(c[i] == tc){
			existe = true;
		}
	}
	return existe;
}
void TVectorCom::MostrarComplejos(double re) const{
   cout << "[";
   for(int i = 0; i < tamano; i++){
		if(c[i].Re() >= re) {
         cout << c[i];
         if(i != tamano - 1) {
            cout << ", ";
         }
      }
	}
   cout << "]";
}
bool TVectorCom::Redimensionar(int tam) {
   bool redimension = false;
   TComplejo *tc;

   if(tam > 0 && tam != tamano && tam > tamano) {
      tc = new TComplejo [tam];
      for(int i = 0;i < tam && i < tamano;i++) {
         tc[i] = c[i];
      }
      if(c != NULL) {
         delete[] c;
      }
      c = tc;
      tamano = tam;
      redimension = true;
   }
   return redimension;
}

ostream &operator<<(ostream &os,const TVectorCom &tv) {
   os << "[";
   if(tv.c && tv.tamano > 0) {
      for(int i = 0;i < tv.tamano;i++) {
         os << "(" << i + 1 << ") " << tv.c[i];
         if(i < tv.tamano - 1) {
            os << ", ";
         }
      }
   }
   os << "]";
   return os;
}