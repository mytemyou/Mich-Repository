#include <iostream>  // Operaciones basicas de E/S
#include <fstream>   // Operaciones de E/S con ficheros de texto
#include <string>

using namespace std;

bool parse_mac_dst(string linea) { 

// Esta función analiza con condicionales si dirección mac de destino es introducida correctamente.
	
	// Con este if comprobamos que dirección mac de destino tiene la estructura correcta, con sus
	// guiones y valores acostumbrados, se pueden modificar si necesario.
	if (linea[0]=='2' && (linea[1]=='C'||'E') && linea[2]=='-' && linea[5]=='-' && linea[8]=='-' 
	&& linea[11]=='-' && linea[14]=='-' && (linea[3]=='5'||'2' ) && (linea[4]=='4'||'2' ) 
	&& linea[6]=='9' && (linea[7]=='1'||'2' ) && linea[9]=='8' && linea[10]=='8' && (linea[12]=='A'||'C' )
	&& (linea[13]=='2'||'9' )&& (linea[16]=='E'||'B' )&& (linea[17]=='3'||'7'))
		
		return 1;
	else return 0;
}

bool filtro_mac_lista( string texto, string linea ) {

// Función que comprueba si la nueva linea leída estaba ya introducida para evitar duplicidad.
 	
	if(texto.find( linea.substr(18,17))>10000 ) // El comando substr() selecciona la cadena deseada.
		return 1 ;
	else return 0 ;
}

void imprimir_mac_lista(string linea){

// Función que muestra en pantalla una nueva dirección mac de destino cuando es detectada con las 
// funciones anteriores.

		cout << linea << endl ;	
}

void read_packet_file() {

// Función que lee el fichero y contiene todo el proceso para realizar la tarea :
	
	string texto, linea ;
	
	ifstream fichero ; // ifstream indica que es un fichero solamente de lectura.
	fichero.open ("sample_packets.txt") ; // open() abre el fichero.
	
	if ( fichero.is_open() ) { // Condicional if. Abrimos el fichero siguiendo el proceso correcto.

      // Comenzamos a leer el fichero por la primera linea :
	  getline (fichero, linea) ; // getline() lee la linea del fichero donde se encuentre el cursor.
      if(parse_mac_dst(linea.substr(18,17)) && filtro_mac_lista(texto,linea)){ // if : Condicional.
	  texto = texto + linea.substr(18,17) + "\n"; // texto : lo usamos para comprobar no duplicidades.
	  imprimir_mac_lista(linea.substr(18,17));
	  }
      
	  // Continuamos leyendo el resto del fichero :
	  while ( !fichero.eof() ) { // while : bucle, mientras no sea el final del fichero (eof()).
      		      	
         getline (fichero, linea) ;
		 if(parse_mac_dst(linea.substr(18,17)	) && filtro_mac_lista(texto,linea)){
         texto = texto + linea.substr(18,17) + "\n";
	     imprimir_mac_lista(linea.substr(18,17));
	     }
	
   	  }
	fichero.close(); // close() : cerramos el fichero como aconseja el procedimiento en estos casos.
	}
   else cout << "Fichero no encontrado o falta de permisos "; // Si problemas con la lectura del fichero.
}

int main () {
	
	read_packet_file(); // llamo a la función que lee el fichero y realiza la tarea. 
	
return 0 ; 
}  
