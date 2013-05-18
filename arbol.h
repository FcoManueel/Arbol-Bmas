// Valores del arbol B+
static int maximo_hijos_por_nodo;
static int maximo_llaves_por_nodo;
static int minimo_llaves_por_nodo;
static float llenado_minimo;

// Estructuras empleadas
struct Registro;
struct Informacion;
// Clases empleadas
class Nodo;
class Arbol;

#pragma pack(1)
struct Registro
{
    int llave;
};
#pragma pack()

struct Informacion
{
    bool  encontrado;
    Nodo* donde;
    int   indice;
    Informacion();
};

class Nodo
{
public:
    int* llaves_;           // alloc
    int  cuantas_llaves_;   // 0
    bool es_hoja_;          // true

    Nodo* padre_;           // NULL
    Nodo* siguiente_;       // NULL
    Nodo* anterior_;        // NULL

    union
    {
        Registro** datos_;  // alloc
        Nodo**     hijos_;
    };

public:
    Nodo();
    ~Nodo();
    bool esta_lleno();
    void pintar();
    void pintar_dir();
    void pintar_all();
    
    friend class Arbol;
};

class Arbol
{
    Nodo* raiz_;
    Nodo* principio_;
    Nodo* final_;

public: 
    Arbol();
    //~Arbol();

    void insert_nonfull(Nodo*,int,int);
    void split_child(Nodo*,int);
    
    Informacion buscar(int llave);
    bool agregar(int llave);
    bool borrar(int llave);

    friend class Nodo;
};
