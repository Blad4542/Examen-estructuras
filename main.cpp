#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;
///-------------------------------------INICIO ESTRUCTURAS--------------------------------------/////////
struct examen{
    string nombreE;
    int puntos;

    struct examen * sig;
    struct examen_breve * eb;
    struct examen_unica * eu;

    examen(string n,int p){
        nombreE = n;
        sig = NULL;
        puntos = p;
        eb = NULL;
        eu = NULL;
    }

}*primeroE;

struct alternativa{
    struct alternativa * sig;
    string opcion;

    alternativa(string op){
        sig = NULL;
        opcion = op;
    }
};

struct breve{
    string nombreB;
    struct breve *sig;
    breve(string n){
        nombreB = n;
        sig = NULL;

    }
}*primeroB;

struct unica{
    int num, puntaje;
    string pregunta,resCorrecta;
    struct alternativa * opcion;
    struct unica *sig;

    unica(int n, int p, string pre, string rC){
        num = n;
        puntaje = p;
        pregunta = pre;

        resCorrecta = rC;
        sig = NULL;
    }
}*primeroU;

struct examen_breve{
    int id, puntaje;
    string pregunta, resCorrecta;
    struct breve * b;
    struct examen_breve * sig;

    examen_breve(int id, int puntaje, string pregunta, string resCorrecta){
        id = id;
        puntaje = puntaje;
        pregunta = pregunta;
        resCorrecta = resCorrecta;
        sig = NULL;
        b = NULL;

    }
};


struct examen_unica{
    struct unica * u;
    struct examen_unica * sig;

    examen_unica(){

        sig = NULL;
        u = NULL;

    }
};
///---------------------FIN ESTRUCTURAS------------------------------------///


///---------------------------DECLARACION DE METODOS-------------------------------///
void menuPrincipal();
void menuMante();
void menuSolu();
void menuCrear();

///------------------------FIN DECLARACION DE METODOS---------------------------------///


///-------------------------------METODOS DE BUSQUEDA-------------------------------------///

struct examen *buscarExamen(string n){

    struct examen *temp = primeroE;

    if(temp == NULL)
        return NULL;

    while(temp != NULL){
        if(temp->nombreE.compare(n) == 0)
            return temp;
        temp = temp->sig;
    }
    return NULL;
}

struct breve * buscarBreve(string nombre){

    struct breve * temp = primeroB;
    if(temp == NULL)
        return NULL;

    while(temp != NULL){
        if(temp->nombreB.compare(nombre)== 0)
            return temp;
        temp = temp->sig;
    }
    return NULL;
};

///---------------------------------FIN METODOS DE BUSQUEDA---------------------------------///



///---------------------METODOS DE INSERTAR------------------------------------///



void insertarUnica(int num, int puntaje, string pregunta, string resCorrecta){
    struct unica * nn = new unica(num,puntaje,pregunta,resCorrecta);
    nn->sig = primeroU;
    primeroU = nn;
}

void insertarBreve(string nombre){
    struct breve * buscar = buscarBreve(nombre);

    struct breve * nn = new breve(nombre);
    nn->sig = primeroB;
    primeroB = nn;
}

void insertarExamen_breve(int id, int puntaje, string pregunta, string resCorrecta,
string nombreS, string nombreE){

    struct breve * tempB = buscarBreve(nombreS);
    struct examen * tempE = buscarExamen(nombreE);

    if((tempE != NULL)&&(tempB != NULL)){
        struct examen_breve *nn = new examen_breve(id, puntaje, pregunta,resCorrecta);
        nn->b = tempB;
        nn->sig = tempE->eb;
        tempE->eb = nn;
    }
}

void insertarExamen(string nombre, int puntos){
    struct examen * buscar = buscarExamen(nombre);
    struct examen * nn = new examen(nombre,puntos);

    string opcion;

    if(buscar != NULL)
    {
        cout<< "\nEste examen ya existe!...\n";
        return;
    }
    nn->sig = primeroE;
    primeroE = nn;
    /*cout<<"Digite que desea agregar:";
    cout<<"\n1.Unica";
    cout<<"\n2.Breve";
    cin>>opcion;
    if(opcion == "2"){
        system("cls");
        insertarBreve(1,2,"quien soy yo","yo");
        nn->rep = primeroB;
    }*/

}

///-------------------------------FIN METODOS DE INSERTAR---------------------------------------///

///---------------------------------INICIO METODOS DE IMPRIMIR----------------------------------///
void imprimeExamen(){
    struct examen * temp = primeroE;

    while(temp != NULL){
        cout<<temp->nombreE<<", "<<temp->puntos<<endl;
        temp = temp->sig;
    }
}

void imprimeBreve(struct breve * temp = primeroB){
    if(temp == NULL)
        return;

    imprimeBreve(temp->sig);
    cout<<"Nombre de la Seccion: "<<temp->nombreB<<endl;
}

void imprimeExamen_Breve(string nombreE){
    struct examen * temp = buscarExamen(nombreE);

    if (temp == NULL)
    {
        cout<<"\nEste examen no existe o la lista esta vacia..!!"<<endl;
        return;
    }
    cout<<"Secciones del examen: "<< temp->nombreE <<"."<< endl;


    if (temp->eb == NULL){
        cout<<"\nEste examen no tiene una respuesta breve creada..."<<endl;
    }
    else
    {
        struct examen_breve * tempImprime = temp->eb;
        cout<<"Seccion: "<<tempImprime->b->nombreB<<endl;

        while(tempImprime != NULL){
                cout<<"Id: "<<tempImprime->id<<endl;
                cout<<"Puntos: "<<tempImprime->puntaje<< endl;
                cout<<"Pregunta: "<<tempImprime->pregunta<<endl;

                tempImprime = tempImprime-> sig;
            }
            tempImprime = temp->eb;
    }

}

void imprimeUnica(){
    struct unica * temp = primeroU;
    while(temp!=NULL){
        cout<<temp->num<<", "<<temp->puntaje<<", "<<temp->pregunta<<", "<<temp->opcion<<", "<<temp->resCorrecta<<endl;
        temp = temp->sig;
    }
}
///------------------------------------------FIN METODOS DE IMPRIMIR------------------------------------///


///------------------------------------------INICIO MENU-------------------------------------------------///

void menuSolu(){
    cout<<"\t\tSolucion de examenes";
    imprimeExamen();
    cout<<"\n1.Volver atras.";
    cout<<"\n\nDigite el numero del examen que desea responder: ";
    string  opcion;
    cin>> opcion;
    if(opcion =="1"){
        system("cls");
    }
    else if(opcion == "2"){
        system("cls");

    }
    else if(opcion == "3"){
        system("cls");
        return;
    }
    else{
        system("cls");
        cout<<"Opcion no valida, intente de nuevo\n";
        menuPrincipal();
    }
}

void menuCrear(){
    string nombre;
    int puntos;
    cout<<"\t\tCreacion de examenes";
    insertarExamen(nombre, puntos);
}
void menuMante(){
    cout<<"\t\tMenu mantenimiento de datos";
    cout<<"\n\n1.Crear examen";
    cout<<"\n2.Borrar";
    cout<<"\n3.Modificar";
    cout<<"\n4.Volver atras";
    cout<<"\n\nDigite el numero de la opcion que desea: ";
    string  opcion;
    cin>> opcion;
    if(opcion =="1"){
        system("cls");
        menuCrear();

    }
    else if(opcion == "2"){
        system("cls");

    }
    else if(opcion == "3"){
        system("cls");

    }
    else if(opcion == "4"){
        system("cls");
        menuPrincipal();
    }
    else{
        system("cls");
        cout<<"Opcion no valida, intente de nuevo\n";
        menuMante();
    }
}
void menuPrincipal(){
    cout<<"\t\tCreacion de examenes";
    cout<<"\n\n1.Mantenimiento de Datos";
    cout<<"\n2.Solucionar examen";
    cout<<"\n3.Salir";
    cout<<"\n\nDigite el numero de la opcion que desea: ";
    string  opcion;
    cin>> opcion;
    if(opcion =="1"){
        system("cls");
        menuMante();

    }
    else if(opcion == "2"){
        system("cls");
        menuSolu();

    }
    else if(opcion == "3"){
        system("cls");
        return;
    }
    else{
        system("cls");
        cout<<"Opcion no valida, intente de nuevo\n";
        menuPrincipal();
    }
}

void loadData(){

    ///-------------------EXAMENES---------------------------///
   insertarExamen("E1",56);
   insertarExamen("E2",56);
   insertarExamen("E3",56);


   ///-----------------------RESPUESTA BREVE-----------------///
   insertarBreve("Breve1");
   insertarBreve("Breve1");
   insertarBreve("Breve1");

    ///-------------------------EXAMEN CON RESPUESTA BREVE---------------------///
    insertarExamen_breve(1,23,"yo soy","yo","Breve1","E1");
    insertarExamen_breve(2,23,"yo soy","yo","Breve1","E1");
    insertarExamen_breve(3,23,"yo soy","yo","Breve1","E1");

}



///-------------------------------------------FIN MENU-----------------------------------------------------///
int main()
{
    loadData();
    //menuPrincipal();

    imprimeExamen_Breve("E1");
}
