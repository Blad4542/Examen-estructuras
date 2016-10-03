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

    struct breve *sig;
    struct breve *ant;

    breve(string n){
        nombreB = n;
        sig = NULL;
        ant = NULL;
    }
}*primeroB;

struct unica{
    string nombreU;
    struct alternativa * opcion;
    struct unica *sig;

    unica(string n){
        nombreU = n;
        sig = NULL;
    }
}*primeroU;

struct examen_unica{
    int num, puntaje;
    string pregunta,resCorrecta;
    struct unica * u;
    struct examen_unica * sig;

    examen_unica(int nu, int p, string pre, string rC){
        num = nu;
        puntaje = p;
        pregunta = pre;
        resCorrecta = rC;
        sig = NULL;
        u = NULL;

    }
};

struct examen_breve{
    int id, puntaje;
    string pregunta, resCorrecta;
    struct breve * b;
    struct examen_breve * sig;
    struct examen_breve * eb;

    examen_breve(int i, int p, string preg, string resC){
        id = i;
        puntaje = p;
        pregunta = preg;
        resCorrecta = resC;
        sig = NULL;
        b = NULL;

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

struct unica * buscarUnica(string nombre){

    struct unica * temp = primeroU;
    if(temp == NULL)
        return NULL;

    while(temp != NULL){
        if(temp->nombreU.compare(nombre)== 0)
            return temp;
        temp = temp->sig;
    }
    return NULL;
};

///---------------------------------FIN METODOS DE BUSQUEDA---------------------------------///



///---------------------METODOS DE INSERTAR------------------------------------///


void insertarUnica(string n){
    struct unica * nn = new unica(n);
    nn->sig = primeroU;
    primeroU = nn;
}

void insertarBreve(string n){
    struct breve * buscar = buscarBreve(n);

    struct breve * nn = new breve(n);
    nn->sig = primeroB;
    primeroB = nn;
}


void insertarExamen_breve(string nombreB, string nombreE, int i, int p, string preg, string resC){

    struct breve * tempB = buscarBreve(nombreB);
    struct examen * tempE = buscarExamen(nombreE);

    if((tempE != NULL)&&(tempB != NULL)){
        struct examen_breve *nn = new examen_breve(i,p, preg, resC);
        nn->b = tempB;
        nn->sig = tempE->eb;
        tempE->eb = nn;
    }
}

void insertarExamen_unica(string nombreU,string nombreE, int nu, int p, string pre, string rC ){
    struct unica * tempU = buscarUnica(nombreU);
    struct examen * tempE = buscarExamen(nombreE);

    if((tempE != NULL)&&(tempU != NULL)){
        struct examen_unica *nn = new examen_unica(nu,p, pre, rC);
        nn->u = tempU;
        nn->sig = tempE->eu;
        tempE->eu = nn;
    }
}

void insertarUnica_alternativa(string nombreU, string opcion){
    struct unica * tempU = buscarUnica(nombreU);
    if(tempU !=NULL){
            struct alternativa * nn = new alternativa(opcion);
            nn->sig = tempU->opcion;
            tempU->opcion = nn;
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
    cout<<"Nombre de la seccion"<<primeroB->nombreB<<endl;
    cout<<endl;

}

void imprimeExamen_Breve(string nombreE){
    string opcion;
    int cont = 0;
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
                cout<<endl;
                cout<<"Id: "<<tempImprime->id<<endl;
                cout<<"Puntos: "<<tempImprime->puntaje<< endl;
                cout<<"Pregunta: "<<tempImprime->pregunta<<endl;

                cout<<"Escriba la respuesta de la pregunta: ";
                cin>>opcion;
                if(tempImprime->resCorrecta == opcion){
                    cout<<"Respuesta Correcta"<<endl;
                    cont = cont + tempImprime->puntaje;
                    cout<<"Puntos obtenidos: "<<cont<<endl;
                }
                else{
                   cout<<"Respuesta incorrecta, la respuesta es: "<<tempImprime->resCorrecta<<endl;
                   cout<<"Puntos obtenidos: "<<cont<<endl;
                }
                tempImprime = tempImprime-> sig;
        }
        tempImprime = temp->eb;
        cout<<"Total de puntos obtenidos: "<<cont<<endl;
    }
}

void imprimeExamen_unica(string nombreE){
    string opcion;
    int cont = 0;
    struct examen * temp = buscarExamen(nombreE);

    if (temp == NULL)
    {
        cout<<"\nEste examen no existe o la lista esta vacia..!!"<<endl;
        return;
    }
    cout<<"Secciones del examen: "<< temp->nombreE <<"."<< endl;

    if (temp->eb == NULL){
        cout<<"\nEste examen no tiene una seleccion unica creada..."<<endl;
    }
    else
    {
        struct examen_unica * tempImprime = temp->eu;
        cout<<"Seccion: "<<tempImprime->u->nombreU<<endl;

        while(tempImprime != NULL){
                cout<<endl;
                cout<<"Id: "<<tempImprime->num<<endl;
                cout<<"Puntos: "<<tempImprime->puntaje<< endl;
                cout<<"Pregunta: "<<tempImprime->pregunta<<endl;
                cout<<"Opciones:"<<endl;
                cout<<"Digite la respuesta de la pregunta: ";
                cin>>opcion;
                if(tempImprime->resCorrecta == opcion){
                    cout<<"Respuesta Correcta"<<endl;
                    cont = cont + tempImprime->puntaje;
                    cout<<"Puntos obtenidos: "<<cont<<endl;
                }
                else{
                   cout<<"Respuesta incorrecta, la respuesta es: "<<tempImprime->resCorrecta<<endl;
                   cout<<"Puntos obtenidos: "<<cont<<endl;
                }
                tempImprime = tempImprime-> sig;
        }
        tempImprime = temp->eu;
        cout<<"Total de puntos obtenidos: "<<cont<<endl;
    }
}

void imprimeUnica_alternativa(){

}

void imprimeUnica(){
    struct unica * temp = primeroU;
    while(temp!=NULL){
        cout<<temp->nombreU<<endl;
        temp = temp->sig;
    }
}
///------------------------------------------FIN METODOS DE IMPRIMIR------------------------------------///

///--------------------------------------------METODOS DE MODIFICAR------------------------------------///


void modificarPregunta(){

}

void modificarExamen(string n){

    struct examen * temp = buscarExamen(n);

    if(temp == NULL){
        cout << "No se encontro un examen con ese nombre" << endl;
        return;
    }

    string nombre;
    cout << "Nuevo nombre: ";
    cin >> nombre;
    struct examen *temp2 = buscarExamen(nombre);

    while(temp2 != NULL){
        cout << "Ese nombre ya se encuentra ocupado" << endl << endl;
        cout << "Nuevo nombre: ";
        cin >> nombre;
        temp2 = buscarExamen(nombre);
    }
    temp->nombreE = nombre;

}
///------------------------------------FIN METODOS DE MODIFICAR---------------------------------///

///------------------------------------------INICIO METODOS DE BORRAR----------------------------------///


///--------------------------------------------FIN METODOS DE BORRAR----------------------------------///
///------------------------------------------INICIO MENU-------------------------------------------------///

void menuSolu(){
    cout<<"\t\tSolucion de examenes"<<endl;
    imprimeExamen();
    cout<<"\n1.Volver atras.";
    cout<<"\n\nEscriba el nombre del examen que desea responder: ";
    string  opcion, nombreE;
    cin>> nombreE;
    imprimeExamen_Breve(nombreE);
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
        insertarBreve(n);
        cout<<"Id pregunta: ";
        cin>>i;
        cout<<"Puntaje pregunta: ";
        cin>>p;
        cout<<"Pregunta: ";
        cin>>preg;
        cout<<"Respuesta correcta de la pregunta: ";
        cin>>resC;
        cout<<"Nombre del examen al que desea agregar la pregunta: ";
        cin>>nombre;
        insertarExamen_breve(n,nombre,i,p,preg,resC);
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
    string opcion,nombre;
    cin>>opcion;
    if(opcion =="1"){
        system("cls");
        modificarPregunta();

    }
    else if(opcion == "2"){
        system("cls");
        cout<<"Escriba el nombre del examen que desea modificar: ";
        cin>>nombre;
        modificarExamen(nombre);
        cout<<"Dato modificado con exito!!!";


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
   insertarBreve("Breve1");
   insertarBreve("Breve1");
   insertarBreve("Breve1");

    insertarBreve("Breve2");
    insertarBreve("Breve2");
    insertarBreve("Breve2");


   ///-----------------------SELECCION UNICA--------------------------///

   insertarUnica("Unica1");

    ///-------------------------EXAMEN CON RESPUESTA BREVE---------------------///
    insertarExamen_breve("Breve1","E1",1,3,"El mejor equipo de costa rica es","Saprissa (no, no es la liga profe xD)");
    insertarExamen_breve("Breve1","E1",2,3,"Campeon nacional actual","Herediano");
    insertarExamen_breve("Breve1","E1",3,4,"Mejor universidad de CR","TEC");

    insertarExamen_breve("Breve2","E2",1,3,"Hola soy","yo");
    insertarExamen_breve("Breve2","E2",2,3,"Apellido del profe Rogelio","Gonzales");
    insertarExamen_breve("Breve2","E2",3,4,"Profe de poo","Lorena");

    ///------------------------EXAMEN CON SELECCION UNICA---------------------------///
    insertarExamen_unica("Unica1","E1",1,1,"Cual es la capital de CR?","San Jose");

    insertarUnica_alternativa("Unica1","A)Pene");
}


///-------------------------------------------FIN MENU-----------------------------------------------------///
int main()
{
    loadData();
    //imprimeExamen_unica("E1");
    //imprimeExamen_Breve("E1");
    menuPrincipal();

}
