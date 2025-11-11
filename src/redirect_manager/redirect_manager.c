#include "readline/readline.h"
#include "redirect_manager_internal.h"
#include <stdio.h>
#include <stdlib.h>

t_redirect	*redirect_create(t_redirect_type redirect_type, char *file_name)
{
	t_redirect	*r;

	r = malloc(sizeof(t_redirect));
	if (!r)
		return (NULL);
	r->symbol = redirect_type;
	if (file_name)
	{
		r->file = malloc(ft_strlen(file_name) + 1);
		if (!r->file)
		{
			free(r);
			return (NULL);
		}
		ft_strlcpy(r->file, file_name, ft_strlen(file_name) + 1);
	}
	else
		r->file = NULL;
	return (r);
}

void	redirect_destroy(t_redirect *redirect)
{
	free(redirect->file);
	free(redirect);
}
	/*while (1)
	{
		write(0, ">", 1);
		input = get_next_line(0);
		if (!(input)|| (delimiter && ft_strncmp(input, delimiter,
					ft_strlen(input) - 1) == 0))
			break ;
		write(fd, input, ft_strlen(input));
		free(input);
	}*/
static int	heredoc_exec(char *delimiter)
{
	char	*input;
	char	*temp_dir;
	int		fd;

	temp_dir = PATH_HEREDOC_TEMP_FILE;
	if (!delimiter)
		return REDIRECT_NO_HEADERDOC_DELIMITER_ERR;
	fd = open(temp_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return MS_OPEN_ERR;
	while (1)
	{
		input = readline(">");
		if (!input || (delimiter && ft_strncmp(input, delimiter,
					ft_strlen(delimiter)) == 0))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	fd = open(temp_dir, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (MS_OK);
}

/*
 *En esta funcion solo abre los archivos necesarios y redirige la entrada y salida segun convenga,
	pero no las vuelvas
 *a dejar como estaban ni nada,
	eso se hace despues de la ejecucion del comando(en command_exec) no aqui,
	de la misma forma,
 *no hagas unlink ni modifiques el archivo temporal que se crea para el heredoc,
	eso se borra despues de esperar a los posibles
 *procesos hijo(en executer).Echales un vistazo si hace falta.
 *
 *Que devuelva 0 si ha ejecutado el redirect sin errores(no aplica para <<).
 *
 *Que devuelva
	-1 si ha habido algun error a la hora de de abrir el archivo o redirigir etc.
 *
 *Comprueba cada cosa con la bash original(asegurate que no sea fish ni otra vaina) porque hay cosas un poco raras que no te esperarias
 * por ejemplo si hace,
 * 				<< EOF echo
 * 				> hola
 * 				> EOF
 * ,en bash, no devuelve nada, en cambio si lo haces con cat en vez de echo si,
	porque cuando usas << lo que pasa es que se crea

	* como un archivo temporal y se le va metiendo lo que escribes linea a linea hasta que encuenta el delimitador

	* luego se mete por la salida estandard al comando que sea(cat recibe cosas por la salida estandard en cambio echo solo por los argumentos).
 *(O eso creo por lo que he visto por ahi).
 */

 static int file_dup_outfile_redirect(int fd, t_redirect *redirect, t_mini_state *mini_state)
{
	if(redirect->symbol == DOUBLE_RIGHT_REDIRECT)
	{
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		mini_state_set_last_opened_file(mini_state, redirect->file);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDOUT_FILENO);
	}
	else if(redirect->symbol == RIGHT_REDIRECT)
	{
		fd = open(redirect->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		mini_state_set_last_opened_file(mini_state, redirect->file);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDOUT_FILENO);
	}
	return(MS_OK);
}
int	redirect_execute(t_redirect *redirect, t_mini_state *mini_state, int stdin_bakup)
{
	int fd;
	int status_code;

	if (redirect->symbol == DOUBLE_LEFT_REDIRECT)
	{
		dup2(stdin_bakup, 0);
		return heredoc_exec(redirect->file);
	}
	if (redirect->file == NULL)
		return (REDIRECT_MALFORMED_ERR);
	if (redirect->symbol == LEFT_REDIRECT)
	{
		fd = open(redirect->file, O_RDONLY);
		mini_state_set_last_opened_file(mini_state, redirect->file);
		if (fd < 0)
			return (MS_OPEN_ERR);
		dup2(fd, STDIN_FILENO);
	}

	status_code = file_dup_outfile_redirect(fd, redirect, mini_state);
	if(status_code != MS_OK)
		return(status_code);
	close(fd);
	return (MS_OK);
}

