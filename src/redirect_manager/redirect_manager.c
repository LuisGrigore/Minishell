#include"redirect_manager_internal.h"
#include "readline/readline.h"
#include <stdio.h>
#include <stdlib.h>

t_redirect *redirect_create(t_redirect_type redirect_type, char *file_name)
{
    t_redirect *r = malloc(sizeof(t_redirect));
    if (!r) return NULL;
    r->redirect_simbol = redirect_type;
    if (file_name) {
        r->file = malloc(ft_strlen(file_name) + 1);
        if (!r->file) { free(r); return NULL; }
        ft_strlcpy(r->file, file_name, ft_strlen(file_name) + 1);
    } else {
        r->file = NULL;
    }
    return r;
}

void redirect_destroy(t_redirect *redirect)
{
	free(redirect->file);
	free(redirect);
}

static void heredoc_exec(char *delimiter)
{
    char *input;
    char *temp_dir;
    int fd;

    // Calculamos tamaño necesario para el path: TEMPDIR + "/minishel_temp" + '\0'
	//getenv("TEMPDIR")
    temp_dir = PATH_HEREDOC_TEMP_FILE;
    if (!temp_dir)
        return;


    // Abrimos el archivo en modo escritura
    fd = open(temp_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return;

    //signals_init_heredoc();

    while (1)
    {
        input = readline(">");
        if (!input || (delimiter && ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0))
            break;

        write(fd, input, ft_strlen(input));
        write(fd, "\n", 1);
        free(input);
    }

    //signals_init_interactive();
    close(fd);

    // Reabrimos el archivo en modo lectura y redirigimos stdin
    fd = open(temp_dir, O_RDONLY);
    if (fd >= 0)
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}


/*
*En esta funcion solo abre los archivos necesarios y redirige la entrada y salida segun convenga, pero no las vuelvas
*a dejar como estaban ni nada, eso se hace despues de la ejecucion del comando(en command_exec) no aqui, de la misma forma,
*no hagas unlink ni modifiques el archivo temporal que se crea para el heredoc, eso se borra despues de esperar a los posibles
*procesos hijo(en executer).Echales un vistazo si hace falta.
*
*Que devuelva 0 si ha ejecutado el redirect sin errores(no aplica para <<).
*
*Que devuelva -1 si ha habido algun error a la hora de de abrir el archivo o redirigir etc.
*
*Comprueba cada cosa con la bash original(asegurate que no sea fish ni otra vaina) porque hay cosas un poco raras que no te esperarias
* por ejemplo si hace,
* 				<< EOF echo
* 				> hola
* 				> EOF
* ,en bash, no devuelve nada, en cambio si lo haces con cat en vez de echo si, porque cuando usas << lo que pasa es que se crea
* como un archivo temporal y se le va metiendo lo que escribes linea a linea hasta que encuenta el delimitador
* luego se mete por la salida estandard al comando que sea(cat recibe cosas por la salida estandard en cambio echo solo por los argumentos).
*(O eso creo por lo que he visto por ahi).
*/
int redirect_execute(t_redirect *redirect)
{
	if(redirect->redirect_simbol == DOUBLE_LEFT_REDIRECT)
	    heredoc_exec(redirect->file);
	//Modificar a partir de aqui(a menos de que encuentres algun error o lo que sea).
	else 
	    file_dup(redirect);
	return (0);
}
