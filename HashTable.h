#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <string>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"
using namespace std;

template <typename V>
class HashTable: public Dict<V> {

private:
	int n; //numeros de elementos de la tabla hash
	int max; //numero máximo
	ListLinked<TableEntry<V>>* table;

	int h(std::string key){
		//Función hash que devuelve la posición (cubeta) en la tabla hash de key.  Se calculará como el resto de la divisón entre la suma de los valores ASCII numéricos de los caracteres de la clave y el tamaño de la tabla hash
		//El método at(i) de std::string permite obtener el carácter situado en la posición i de un string, y la función int(c) permite obtener el valor ASCII numérico del carácter c.

		int sum = 0;

		for(int i=0; i<key.length(); i++){
			sum += int(key.at(i));
		}
		
		return sum % max;
	}

public:

	HashTable(int size){

	n = 0;
	max = size;
	table = new ListLinked<TableEntry<V>>[size];
				     
	}

	~HashTable(){
		 for( int i=0; i<max;i++)//recorre toda la tabla 
			 table[i].~ListLinked();//y en cada indice de la tabla elimina listas
		delete[] table;}//como se ha creado con new se destruye asi y como es de arrays tiene los corchetes

	int capacity(){
	
		return max;
	}

	friend ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		 out<<"HashTable[Entries: "<<th.n << ",Capacity:" <<th.max << "]\n" << "\n"; 
		 for(int i=0; i < th.max;i++){//recorremos tabla
			 out << "Cubeta : " <<i<< "\n";
			  out << th.table[i]<<std::endl;
		 }



		return out;

	}

	V operator[](std::string key){
		//Sobrecarga del operador []. Devuelve el valor correspondiente a key. Si no existe, lanza la excepción std::runtime_error.
 			 int pos = table[h(key)].search(key);
		if(pos < 0)// no existe posicion
			throw std::runtime_error("clave no  encontrada");
		
		V aux = table[h(key)].get(pos).value;//devuelve valor correspondiente a jkey
		return aux;

		 }
	//Poner las heredadas
	//
	//HEREDADAS:

	void insert(std::string key, V value) override{
		//Inserta el par key->value en el diccionario. Lanza una excepción std::runtime_error si key ya existe en el diccionario.

		int pos = table[h(key)].search(key);//llamamos pos a h(key)

                if(pos >= 0)
                        throw std::runtime_error("Ya introducido");

		TableEntry<V> aux(key, value);//tabla auxiliar para meter valor y key 
		table[h(key)].prepend(aux);
		n++;//aumenta tamaño cubetas ocupadas
				 //comprobar q no exista ya la key
	}

		/*	table[h(key)].append(TableEntry(key, value));*/	

	//hay que comprobar que no exista ya la key

	
	V search(std::string key) override{
		//Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error.

         int hash = h(key);
		int pos = table[hash].search(key);

                if(pos < 0)
                        throw std::runtime_error("No encontrado");

                V aux = table[hash].get(pos).value;
                return aux;
	}  
	
	 V remove(string key) override {
           	int pos = table[h(key)].search(key);//guardamosposicion

                if(pos > max || pos < 0)//fuera del rango 
                        throw std::runtime_error("No encontrado");

		V aux = table[h(key)].remove(pos).value;//llamamos a lss funciones de list
		n--;//dismuniumos cubetas
		return aux;
	}


    
	
	int entries() override{
		//Devuelve el número de elementos que tiene el Diccionario.

		return n;
	}
                              
};

#endif
