#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <string>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

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
	max = 0;
	table = new ListLinked<TableEntry<V>>[size];
				     
	}

	~HashTable(){
		delete[] table;
	}

	int capacity(){
	
		return max;
	}

	friend std::ostream&operator<<(std::ostream &out, const HashTable<V> &th){
		 out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
            out << "==============" << endl << endl;
            for(int i = 0; i < th.max; i++){
                out << "== Cubeta " << i << " =="<< endl << endl;
                out << "List => ";
                for(int j = 0; j < th.table[i].size(); j++){
                    out <<	"[" << th.table[i][j].key << ":" << th.table[i][j].value << "] ";
                } 
                out << endl << endl;
            }  
            out << "==============" << endl << endl;
			return out;
	    }

	V operator[](std::string key){
		//Sobrecarga del operador []. Devuelve el valor correspondiente a key. Si no existe, lanza la excepción std::runtime_error.
 			V kValue = search(key);
            return kValue;
        }
	//Poner las heredadas
	//
	//HEREDADAS:

	void insert(std::string key, V value) override{
		//Inserta el par key->value en el diccionario. Lanza una excepción std::runtime_error si key ya existe en el diccionario.

		int pos = h(key); 
            for(int i = 0; i < table[pos].size(); i++) {
                if(table[pos][i].key == key) throw runtime_error("Key alredy exists!");
            } 
            TableEntry newEntry(key, value);
            table[pos].append(newEntry); 
        }

		/*	table[h(key)].append(TableEntry(key, value));*/	

	//hay que comprobar que no exista ya la key

	
	V search(std::string key) override{
		//Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error.

		int pos = h(key);
            V kValue = -1;
            for(int i = 0; i < table[pos].size(); i++){
                if(table[pos][i].key == key){
                    kValue = table[pos][i].value;
                    break; 
                } 
            } 
            if(kValue == -1)throw runtime_error("Key not found!");
            return kValue;
    }   
	
	 V remove(string key) override {
            int i;
            int pos = h(key);
            for(i = 0; i < table[pos].size(); i++) {
                if(table[pos][i].key == key) break;
            }
            if(i == (table[pos].size())) throw runtime_error("Key not found!");
            V returnValue = (table[pos].remove(i)).value; 

            return returnValue; 
        }

    
	
	int entries() override{
		//Devuelve el número de elementos que tiene el Diccionario.

		return n;
	}
                              
};

#endif
