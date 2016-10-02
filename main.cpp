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

    examen(string n){
        nombreE = n;
        sig = NULL;
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
    int id, puntaje;
    string pregunta, resCorrecta;
    struct breve *sig;
    struct breve *ant;

    breve(string n, int i, int p, string preg, string resC){
        nombreB = n;
        id = i;
        puntaje = p;
        pregunta = preg;
        resCorrecta = resC;
        sig = NULL;
        ant = NULL;

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
    struct breve * b;
    struct examen_breve * sig;
    struct examen_breve * eb;

    examen_breve(){
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
void menuModificar();
void menuBorrar();

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

void insertarBreve(string n, int i, int p, string preg, string resC){
    struct breve * buscar = buscarBreve(n);

    struct breve * nn = new breve(n, i, p, preg, resC);
    nn->sig = primeroB;
    primeroB = nn;
}

void insertarExamen_breve(string nombreB, string nombreE){

    struct breve * tempB = buscarBreve(nombreB);
    struct examen * tempE = buscarExamen(nombreE);

    if((tempE != NULL)&&(tempB != NULL)){
        struct examen_breve *nn = new examen_breve();
        nn->b = tempB;
        nn->sig = tempE->eb;
        tempE->eb = nn;
    }
}

void insertarExamen(string nombreE){
    struct examen * buscar = buscarExamen(nombreE);
    struct examen * nn = new examen(nombreE);

    string opcion;

    if(buscar != NULL)
    {
        cout<< "\nEste examen ya existe!...\n";
        return;
    }
    nn->sig = primeroE;
    primeroE = nn;

}

///-------------------------------FIN METODOS DE INSERTAR---------------------------------------///

///---------------------------------INICIO METODOS DE IMPRIMIR----------------------------------///
void imprimeExamen(){
    struct examen * temp = primeroE;

    while(temp != NULL){
        cout<<temp->nombreE<<endl;
        temp = temp->sig;
    }
}

void imprimeBreve(struct breve * primeroB){

    if(primeroB == NULL)
        return;

    imprimeBreve(primeroB->sig);
    cout<<primeroB->nombreB<<endl;
    cout<<endl;
    cout<<"Id pregunta: "<<primeroB->id<<endl;
    cout<<"Valor: "<<primeroB->puntaje<<" puntos"<<endl;
    cout<<"Pregunta: "<<primeroB->pregunta<<endl;
    cout<<endl;
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

                cout<<"Id: "<<tempImprime->b->id<<endl;
                cout<<"Puntos: "<<tempImprime->b->puntaje<< endl;
                cout<<"Pregunta: "<<tempImprime->b->pregunta<<endl;
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

///--------------------------------------------METODOS DE MODIFICAR------------------------------------///


void modificarPregunta(){

}

void modificarExamen(){

}
///------------------------------------FIN METODOS DE MODIFICAR---------------------------------///


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
    cout<<"\t\t\tAgregar preguntas a  examenes"<<endl;
    cout<<endl;
    string nombre,opcion,n,preg,resC;
    int i,p;
    cout<<"Digite que desea agregar:"<<endl;
    cout<<"\n1.Unica";
    cout<<"\n2.Breve";
    cout<<"\n3.Volver atras";
    cout<<"\nDigite la opcion que desea: ";
    cin>>opcion;
    if(opcion == "1"){
        system("cls");
    }
    else if(opcion == "2"){
        system("cls");
        cout<<"Nombre de la seccion: ";
        cin>>n;
        cout<<"Id pregunta: ";
        cin>>i;
        cout<<"Puntaje pregunta: ";
        cin>>p;
        cout<<"Pregunta: ";
        cin>>preg;
        cout<<"Respuesta correcta de la pregunta: ";
        cin>>resC;
        insertarBreve(n,i,p,preg,resC);
        cout<<"Nombre del examen al que desea agregar la pregunta: ";
        cin>>nombre;
        insertarExamen_breve(n,nombre);
        system("cls");
        cout<<"Datos insertados con exito!!";
        menuMante();
    }
    else if(opcion == "3"){
        system("cls");
        menuMante();
    }
    else{
        system("cls");
        cout<<"Opcion incorrecta.";
        menuCrear();
    }
}
void menuMante(){
    cout<<"\t\tMenu mantenimiento de datos";
    cout<<"\n\n1.Creacion de preguntas";
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
        menuBorrar();

    }
    else if(opcion == "3"){
        system("cls");
         menuModificar();
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

void menuModificar(){
    cout<<"\t\t\tMenu Modificar";
    cout<<"\n1.Modificar preguntas";
    cout<<"\n2.Modificar examen";
    cout<<"\n3.Volver atras";
    cout<<"\n\nDigite el numero de la opcion que desea: ";
    string opcion;
    cin>>opcion;
    if(opcion =="1"){
        system("cls");
        modificarPregunta();

    }
    else if(opcion == "2"){
        system("cls");
        modificarExamen;

    }
    else if(opcion == "3"){
        system("cls");
        menuMante();
    }
    else{
        system("cls");
        cout<<"Opcion equivocada, intente de nuevo"<<endl;
        menuModificar();
    }

}

void menuBorrar(){
    cout<<"\t\t\tMenu Borrar";
    cout<<"\n1.Borrar preguntas";
    cout<<"\n2.Borrar examen";
    cout<<"\n3.Borrar Secciones";
    cout<<"\n4.Volver atras";
    cout<<"\n\nDigite el numero de la opcion que desea: ";
    string opcion;
    cin>>opcion;
    if(opcion =="1"){
        system("cls");

    }
    else if(opcion == "2"){
        system("cls");


    }
    else if(opcion == "3"){
        system("cls");
    }
    else if(opcion == "4"){
        system("cls");
        menuMante();
    }
    else{
        system("cls");
        cout<<"Opcion equivocada, intente de nuevo"<<endl;
        menuModificar();
    }
}
void menuPrincipal(){
    cout<<"\t\tCreacion de examenes";
    cout<<"\n1.Mantenimiento de Datos";
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
   insertarExamen("E1");
   insertarExamen("E2");
   insertarExamen("E3");


   ///-----------------------RESPUESTA BREVE-----------------///
   insertarBreve("Breve1",1,22,"yo soy","yo");
   insertarBreve("Breve1",2,23,"yo es","yo");
   insertarBreve("Breve1",3,24,"yo fui","yo");

    ///-------------------------EXAMEN CON RESPUESTA BREVE---------------------///
    insertarExamen_breve("Breve1","E1");
    insertarExamen_breve("Breve1","E1");
    insertarExamen_breve("Breve1","E1");

}



///-------------------------------------------FIN MENU-----------------------------------------------------///
int main()
{
    loadData();

    imprimeExamen_Breve("E1");
    //menuPrincipal();

}
