#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h> 

using namespace std;

class FrontEnd
{
	char *nombreFichero;
    FILE* entrada;
    int n1;
    int traza;
    string SPila;
    
    public:    
    
          FrontEnd(const char *unNombreFichero, int una_traza=0);
          ~FrontEnd();
          // primera parte lexico
          string siguienteToken(void);
          void  devuelveToken(string token);
          int lineaActual(void){return n1; }
          int existeTraza(void){if(traza)return 1; else return 0;}
          void errores(int codigo);
          
          // Segunda parte sintaxis
          void programa (void);
          void enteros(void);
          void opera_numerica(void);
          void mas_opera_numerica(void);
          void carracteres(void);
          void opera_carracter(void); 
          void variables(void);
          void Imprimir(void);
          void Leer(void);
          void Super_if(void);
          void Super_else(void);
          void While(void);
};

FrontEnd::~FrontEnd()
{
     fclose(entrada);
}

FrontEnd::FrontEnd(const char *unNombreFichero, int una_traza)
{
     entrada=fopen(unNombreFichero, "rt");
     if((entrada==NULL))
     {
          cout<<"No se puede abrir el archivo"<<endl;
          system("sleep 2");
          exit(-2);
     }
     cout<<"Exito al abir el archivo"<<endl;
     if(una_traza) traza=1;
     else traza = 0;
     n1=1;
     SPila = "";
     if(existeTraza())
         cout<<"INICIO DE ANALISIS LEXICO"<<endl;
     programa();
}

string FrontEnd::siguienteToken(void)
{
	 char car;
     string palabra = "";
     string palabra_aux;
     if(SPila ==  ""){
     do{
     while((car=(char)fgetc(entrada))!=EOF )
     {
          if(car==' '){ break;}
          if(car=='\t'){ break;}
          if(car=='\n' ){ ++n1; break;}
          if(car=='\''){ 
			  if(palabra == "")
			  palabra = "\'";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == ';'){
			  if(palabra == "")
			  palabra =";";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == '('){
			  if(palabra == "")
			  palabra ="(";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == ')'){
			  if(palabra == "")
			  palabra =")";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == '+'){
			  if(palabra == "")
			  palabra ="+";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == '-'){
			  if(palabra == "")
			  palabra ="-";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == '*'){
			  if(palabra == "")
			  palabra ="*";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == '/'){
			  if(palabra == "")
			  palabra ="/";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == '<'){
				if(palabra ==""){
				if((car=(char)fgetc(entrada))!=EOF and car == '='){
					palabra = "<="; break;
					}
				else 
					fseek(entrada,-1,SEEK_CUR);
			  palabra = "<";
			  break;}
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
	     if(car == '>'){
				if(palabra ==""){
				if((car=(char)fgetc(entrada))!=EOF and car == '='){
					palabra = ">="; break;
					}
				else 
					fseek(entrada,-1,SEEK_CUR);
			  palabra = ">";
			  break;}
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		 if(car == '='){
				if(palabra ==""){
				if((car=(char)fgetc(entrada))!=EOF and car == '='){
					palabra = "=="; break;
					}
				else 
					fseek(entrada,-1,SEEK_CUR);
			  palabra = "=";
			  break;}
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}		
		if(car == '!'){
				if(palabra ==""){
				if((car=(char)fgetc(entrada))!=EOF and car == '='){
					palabra = "!="; break;
					}
				else 
					fseek(entrada,-1,SEEK_CUR);
			  palabra = "!";
			  break;}
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}			  	  		  		  	  	  	   	    	  
          palabra_aux = car;
          palabra = palabra + palabra_aux;
          if(palabra =="\\\\"){
			  cout<<"Comentario de 1 linea"<<endl;
			  palabra = "";
			  while((car=(char)fgetc(entrada))!=EOF){
				  if(car=='\n' ){ ++n1; break;}
				  }
			  }
		  if(palabra == "\\*"){
			  cout<<"Comentario de multiples lineas"<<endl;
			  palabra = "";
			  while(palabra != "*\\" and car != EOF){
				palabra ="";
				while((car=(char)fgetc(entrada))!=EOF){
					if(car==' ' ){ break;}
					if(car=='\t'){ break;}
					if(car=='\n' ){ ++n1; break;}
					palabra_aux = car;
					palabra = palabra + palabra_aux;
					}
				}
			  if(car == EOF){
				errores(9);  
				  }
			  palabra ="";	
			  }	  
    }
    if( car == EOF){
		palabra = "FinalD";
		}
	}while(palabra == "");
	}
	else{
	palabra = SPila;
	SPila = "";
	}	 
    if(
    palabra == "principal" ||
    //palabras reservadas
    palabra == "entero" ||
    palabra == "letra" ||
    palabra == "escribir" ||
    palabra == "leer" ||
    palabra == "si" ||
    palabra == "sino" ||
    palabra == "para" ||
    palabra == "mientras" ||
    palabra == "hacer" ||
    palabra == "mientras" ||
    palabra == "hacer" ||
    palabra == "devolver" ||
    palabra == "vacio" ||
    //separadores
    palabra == "{" ||
    palabra == "}" ||
    palabra == "(" ||
    palabra == ")" ||
    palabra == ";" ||
    //operadores
    palabra == "+" ||
    palabra == "-" ||
    palabra == "/" ||
    palabra == "*" ||
    //asignacion
    palabra == "=" ||
    //operadores de comparacion
    palabra == "==" ||
    palabra == "!=" ||
    palabra == "<" ||
    palabra == "<=" ||
    palabra == ">" ||
    palabra == ">=" ||
    palabra == "!" ||
    //especiales
    palabra == "\'" ||
    palabra == "FinalD" 
     
    ) {
		cout<<"token "<<palabra<<endl;
		return palabra;
		system("sleep 1");
		}
    else {
		int l = palabra.length(); 
		string es = "Nada";
		for(int i = 0; i < l;i++){
			if( (char)palabra[i] >= '0' and (char)palabra[i] <= '9'){
			if(es == "Nada")
			es = "Numero";
			}
			if((char)palabra[i] >= 'A' and (char)palabra[i] <= 'z' ){
			if(es == "Nada")
			es = "Variable";
			else if(es == "Numero" and es != "_")
			es = "QuienSabe";
			}
		}
		palabra = es;	
        system("sleep 1");
        cout<<"token "<<palabra<<endl;
        return palabra;
       }
	return palabra;
}

void FrontEnd::devuelveToken(string token){
	SPila = token;
	cout<<"Mete a la pila: "<<SPila<<endl;
	}

void FrontEnd::errores(int codigo){
cout<<"LINEA "<<lineaActual();
cout<<" ERROR SINTACTICO "<<codigo;
switch (codigo)
{
	case 1 :cout<<" :Falta un main "<<endl;break;
	case 2 :cout<<" :Falta un { inicial "<<endl;break;
	case 3 :cout<<" :Falta de ; "<<endl;break;
	case 4 :cout<<" :Nombre de variable invalido"<<endl;break;
	case 5 :cout<<" :Error con los parentesis"<<endl;break;
	case 6 :cout<<" :falta un valor de la operacion"<<endl;break;
	case 7 :cout<<" :Error falta \' "<<endl;break;
	case 8 :cout<<" :Error falta = "<<endl;break;
	case 9 :cout<<" :Error Falta *\\"<<endl;break;
	case 11:cout<<" :Error en los parentensis"<<endl;break;
	case 13:cout<<" :Error Desconocido"<<endl;break;
	case 14:cout<<" :Error Falta } "<<endl;break;
	}
	exit(-1);
}

//Segunda parte

void FrontEnd::programa (void){
	string token = siguienteToken();
	if(token == "principal"){
		cout<<"inicio del programa correcto"<<endl;
		token = siguienteToken();
		if(token == "{"){
			cout<<"abre corchete"<<endl;
			while((token=siguienteToken()) != "}" and token != "FinalD"){
				if(token == "entero"){
					cout<<"Creacion de un entero"<<endl;
					enteros();
					}
				if(token == "letra"){
					cout<<"Creacion de un char"<<endl;
					carracteres();
					}
				if(token == "Variable"){
					cout<<"modificaion de una variable"<<endl;
					variables();
					}
				if(token == "escribir"){
					cout<<"Setencia escribir"<<endl;
					Imprimir();
					}
				if(token == "leer"){
					cout<<"Sentencia"<<endl;
					Leer();
					}
				if(token == "si"){
					cout<<"Sentencia"<<endl;
					Super_if();
					}
				if(token == "mientras"){
					cout<<"Sentencia"<<endl;
					While();
					}			
				}
			if(token == "FinalD"){
				errores(14);
				}
			token=siguienteToken();
			if(token != "FinalD"){
				errores(13);
				}		
			}
		else
			errores(2);
		}
	else
		errores(1);
	}

void FrontEnd::enteros(void){
	string token = siguienteToken();
	if(token == "Variable"){
		string token = siguienteToken();
		if(token == ";"){
		cout<<"Termino exito de la sentencia"<<endl;
		return;
		}
		else if(token == "="){
			opera_numerica(); 
			token = siguienteToken();
			if( token == ";"){
			cout<<"Termino exito de la sentencia"<<endl;
			return;
			}
			else
			errores(3);
		}
		else
		errores(3);
	}
	else
	errores(4);
	}

void FrontEnd::opera_numerica(void){
	string token = siguienteToken();
	
	if( token == "("){
		mas_opera_numerica();
		token = siguienteToken();
		if(token != ")"){
		errores(5);	
			}
		}
	else if( token == "Variable" or token == "Numero" )	{
		token = siguienteToken();
		if( token == "+" or token == "-" or token == "/" or token == "*"){
		mas_opera_numerica();
		token = siguienteToken();
		}
		else{
			devuelveToken(token);
			}
	}
	if( token  == ";"){
		devuelveToken(token);
		cout<<"Termino exito de la sentencia"<<endl;	
		}	
	
	}

void FrontEnd::mas_opera_numerica(void){
	string token = siguienteToken();
	if( token == "("){
		mas_opera_numerica();
		token = siguienteToken();
		if(token != ")"){
		errores(5);	
			}
		else {
		token = siguienteToken();	
		if (token == "+" or token == "-" or token == "/" or token == "*")
		mas_opera_numerica();
		else 
		devuelveToken(token);
			}
		}	
	else if( token == "Variable" or token == "Numero" )	{
		token = siguienteToken();
		if( token == "+" or token == "-" or token == "/" or token == "*"){
		mas_opera_numerica();}
		else{
			devuelveToken(token);
			}
	}
	else 
	errores(6);
	}
	
void FrontEnd::carracteres(void){
	string token = siguienteToken();
	if(token == "Variable"){
		string token = siguienteToken();
		if(token == ";"){
		cout<<"Termino exito de la sentencia"<<endl;
		return;
		}
		else if(token == "="){
			cout<<"Asignando valor"<<endl;
			opera_carracter(); 
			token = siguienteToken();
			if(token != ";")
			errores(3);
			return;
			devuelveToken(token);
		}
		else
		errores(3);
	}
	else
	errores(4);
	
	}
void FrontEnd::opera_carracter(void){
	string token = siguienteToken();
	bool op = true;
	if(token == "\'"){
		do{
			token = siguienteToken();
			if(token == "\'")
			op = false;
			if(token == "FinalD")
			errores(7); 
			}while(op);
		//token = siguienteToken();
		//devuelveToken(token);
		cout<<"exito al crear char "<<token<<endl;

		return;
		}
	else if( token == "Variable"){
		token = siguienteToken();
		if(token == ";"){
			cout<<"exito al crear letra"<<endl;
			devuelveToken(token);
			return;}
		else
		errores(3);	
		}
	else
	errores(7);
	} 		
	
void FrontEnd::variables(void){
	string token = siguienteToken();
	cout<<"Analizando la asignacion"<<endl;
	if( token == "="){
		token = siguienteToken();
		if(token == "\'"){
		devuelveToken(token);	
		opera_carracter();
		}
		else{ 
		devuelveToken(token);		
		mas_opera_numerica();
		token = siguienteToken();
		if(token != ";"){
			errores(3);
		}
		else{
		cout<<"Exito con la asignacion"<<endl;	
			}
		}
	}	
	else
	errores(8);
	
	}

void FrontEnd::Imprimir(void){
	string token = siguienteToken();
	if(token == "("){
		token = siguienteToken();
		if(token == "Variable" or token == "Numero" or token == "("){
		devuelveToken(token);
		mas_opera_numerica();
		}
		else if(token == "\'"){
		devuelveToken(token);	
		opera_carracter();	
		}	
		else
		errores(13);	
		token = siguienteToken();
		if(token  == ")"){
			token = siguienteToken();
			if(token == ";"){
				cout<<"impresion correcta"<<endl;
				return;
				}
			else{
				errores(3);
				}
			}
		else{
			errores(11);
			}	
		}
	else{
		errores(11);
		}	
	
	}
	
void FrontEnd::Leer(void){
	string token = siguienteToken();
	if(token == "("){
		token = siguienteToken();
		if(token == "Variable"){
			token = siguienteToken();
		if(token  == ")"){
			token = siguienteToken();
			if(token == ";"){
				cout<<"lectura correcta"<<endl;
				return;
				}
			else{
				errores(3);
				}
			}
			else{
				errores(11);
			}	
		}
		else
		errores(13);		
		}
	else{
		errores(11);
		}	
	
	}	


void FrontEnd::Super_if(void){
	string token = siguienteToken();
	if(token == "("){
		token = siguienteToken();
		if(token == "Variable" or token == "Numero" or token == "("){
		devuelveToken(token);
		mas_opera_numerica();
		}
		else if(token == "\'"){
		devuelveToken(token);	
		opera_carracter();	
		}
		else
		errores(13);	
		token = siguienteToken();
		if( token == "==" || token == "!=" || token == "<" || token == "<=" || token == ">" || token == ">=" ){
			token = siguienteToken();
			if(token == "Variable" or token == "Numero" or token == "("){
			devuelveToken(token);
			mas_opera_numerica();
			}
			else if(token == "\'"){
			devuelveToken(token);	
			opera_carracter();	
			}
			else
			errores(13);	
			}
		else
		errores(13);
		token = siguienteToken();
		if(token == ")"){
			cout<<"Sentencia si correcta"<<endl;
			bool Terminar = false;
			token = siguienteToken();
				if(token == "{"){
					Terminar = true;
					}
				do{
					if(token == "entero"){
						cout<<"Creacion de un entero"<<endl;
						enteros();
					}
					if(token == "letra"){
						cout<<"Creacion de una letra"<<endl;
						carracteres();
					}
					if(token == "Variable"){
						cout<<"modificaion de una variable"<<endl;
						variables();
					}
					if(token == "escribir"){
						cout<<"Setencia escribir"<<endl;
						Imprimir();
					}
					if(token == "leer"){
					cout<<"Sentencia"<<endl;
					Leer();
					}
					if(token == "si"){
						cout<<"Sentencia"<<endl;
						Super_if();
					}
					if(token == "mientras"){
					cout<<"Sentencia"<<endl;
					While();
					}			
					}while(Terminar & ((token=siguienteToken()) != "}" and token != "FinalD"));	
			if(token == "FinalD"){
				errores(14);
				}
			token=siguienteToken();
			if(token == "sino"){
				token=siguienteToken();
					if(token == "si"){
					Super_if();
					return;
					}
				devuelveToken(token);
				Super_else();					
				}		
			return;
			}
		else
		errores(5);	
			
		}
	else
	errores(11);
	}

void FrontEnd::Super_else(){
	bool Terminar = false;
	string token = siguienteToken();
				if(token == "{"){
					Terminar = true;
					devuelveToken(token);
					token = siguienteToken();
					}
				do{
					if(token == "entero"){
						cout<<"Creacion de un entero"<<endl;
						enteros();
					}
					if(token == "letra"){
						cout<<"Creacion de una letra"<<endl;
						carracteres();
					}
					if(token == "Variable"){
						cout<<"modificaion de una variable"<<endl;
						variables();
					}
					if(token == "escribir"){
						cout<<"Setencia escribir"<<endl;
						Imprimir();
					}
					if(token == "leer"){
					cout<<"Sentencia"<<endl;
					Leer();
					}
					if(token == "si"){
						cout<<"Sentencia"<<endl;
						Super_if();
					}
					if(token == "mientras"){
					cout<<"Sentencia"<<endl;
					While();
					}			
					}while(Terminar && ((token=siguienteToken()) != "}" and token != "FinalD"));	
			if(token == "FinalD"){
				errores(14);
				}			
	}

void FrontEnd::While(void){
	string token = siguienteToken();
	if(token == "("){
		token = siguienteToken();
		if(token == "Variable" or token == "Numero" or token == "("){
		devuelveToken(token);
		mas_opera_numerica();
		}
		else if(token == "\'"){
		devuelveToken(token);	
		opera_carracter();	
		}
		else
		errores(13);	
		token = siguienteToken();
		if( token == "==" || token == "!=" || token == "<" || token == "<=" || token == ">" || token == ">=" ){
			token = siguienteToken();
			if(token == "Variable" or token == "Numero" or token == "("){
			devuelveToken(token);
			mas_opera_numerica();
			}
			else if(token == "\'"){
			devuelveToken(token);	
			opera_carracter();	
			}
			else
			errores(13);	
			}
		else
		errores(13);
		token = siguienteToken();
		if(token == ")"){
			cout<<"Sentencia mientras correcta"<<endl;
			bool Terminar = false;
			token = siguienteToken();
				if(token == "{"){
					Terminar = true;
					}
				do{
					if(token == "entero"){
						cout<<"Creacion de un entero"<<endl;
						enteros();
					}
					if(token == "letra"){
						cout<<"Creacion de una letra"<<endl;
						carracteres();
					}
					if(token == "Variable"){
						cout<<"modificaion de una variable"<<endl;
						variables();
					}
					if(token == "escribir"){
						cout<<"Setencia escribir"<<endl;
						Imprimir();
					}
					if(token == "leer"){
					cout<<"Sentencia"<<endl;
					Leer();
					}
					if(token == "si"){
						cout<<"Sentencia"<<endl;
						Super_if();
					}			
					}while(Terminar & ((token=siguienteToken()) != "}" and token != "FinalD"));	
			if(token == "FinalD"){
				errores(14);
				}					
			return;
			}
		else
		errores(5);	
			
		}
	else
	errores(11);
	}
	
	
int main()
{
   FrontEnd pollo("lila.txt",1);
   cout<<"Exito en la compilacion"<<endl;  
   return 0;
}
