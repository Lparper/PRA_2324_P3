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
		
		out << "Tabla Hash: " << std::endl;
		out << "Capacidad: " << th.max << std::endl;
		out << "Número de elementos: " << th.n << std::endl;
		//out << "Factor de carga: " << th.n/th.max << std::endl;
		out << "Elementos: " << std::endl;
		out << "Posición" << "\t" << "Clave" << "\t" << "Valor" << std::endl;
		out << "--------------------------------------------------" << std::endl;
		
		for(int i=0; i<th.max; i++){
			out << i << "\t" << th.table[i] << std::endl;
		}
		
		return out;

		/*out << "List -> [";
			for(int i=0; i<max; i++){
			out << table[i].n.key;
			}
		*/		//Preguntar
	
	}

	V operator[](std::string key){
		//Sobrecarga del operador []. Devuelve el valor correspondiente a key. Si no existe, lanza la excepción std::runtime_error.

		int pos = h(key);
		/*Cálculo de posición hash (pos):
: Se calcula la posición hash de la clave utilizando la función h. La variable pos representa la posición en la tabla de dispersión donde se almacenará el valor asociado a la clave.*/

		TableEntry<V> entry(key, V());

	/*Creación de una entrada (TableEntry<V> entry(key, V());):

Se crea un objeto TableEntry llamado entry utilizando la clave proporcionada y un valor predeterminado para el tipo V. Esto se hace para buscar esta entrada en la lista correspondiente de la tabla de dispersión.*/
		
		int posEntry = table[pos].search(entry);

		if(posEntry == -1){
			throw std::runtime_error("No existe la clave");
		}else{
			return table[pos].get(posEntry).value;
		}

	}
	//Poner las heredadas
	//
	//HEREDADAS:

	void insert(std::string key, V value) override{
		//Inserta el par key->value en el diccionario. Lanza una excepción std::runtime_error si key ya existe en el diccionario.

		int pos = h(key);
		TableEntry<V> entry(key, value);

		if(table[pos].search(entry) == -1){
			table[pos].append(entry);
			n++;
		}else{
			throw std::runtime_error("La clave ya existe");
		}

		/*	table[h(key)].append(TableEntry(key, value));*/	

	//hay que comprobar que no exista ya la key


	}
	
	V search(std::string key) override{
		//Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error.

		int pos = h(key);
		TableEntry<V> entry(key, V());

		int posEntry = table[pos].search(entry);

		if(posEntry == -1){
			throw std::runtime_error("No existe la clave");
		}else{
			return table[pos].get(posEntry).value;
		}

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
