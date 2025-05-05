Aqui dejo el link del word en el explico todo he intentado hacerlo de la forma más clara posible.
https://docs.google.com/document/d/1I0pvSOrzhctGTn65-AILedXgI0sV-HCZpOQX4UQTGng/edit?usp=sharing
Estas son las estructuras que tengo pensadas para comencera ya estan declaradas en el .h

esta seria para los comandos básicos de bin que vendrian a estar en el directorio PATH.Los comentarios los tengo únicamente aqui el .h esta limpio de estos. 
typedef struct s_bcmd
{
  #El doble array es necesario para su ejecucción con la funcion exceve en la cual es necesario taambien el path relativo donde se encuentra el comando.
    char **cmd;
    char *path;

}   t_bcmd;
En esta seria para los bin built-ins.Es un prototipo ya que no estoy seguro de que sería necesario para cada función  pero es para tener algo.
typedef struct s_incmd
{
    char *chs;
    char **cmd;
} t_incmd ;
Esta seria para el apartado de redirecciónes  encontrando un puntero donde almancenar las posibilidades y dos int siendo para el caso de la redirrección de entrada o el de salida o ambos.
typedef struct s_re
{
    int input;
    int output;
    char *redirect;

} t_re;

#Esta seria en concepto una lista enlazada donde partir para cada comando
typedef struct s_comand
{
#Bin por comandos de bin
    t_bcmd *bin;
#Ins por los built-INS
    t_incmd *ins;
#Red por redirections
    t_re    *red;
    struct s_comand *next;
} 
Aun así faltarian  a mi parecer 2 estructuras más la primera para el historial  y otra donde encapsular las otras 2 tu que opinas?.
