/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:01 by lgrigore          #+#    #+#             */
/*   Updated: 2025/10/05 19:01:58 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
#define MS_ERRORS_H

typedef enum e_ms_status
{
	MS_OK = 0,                // Todo correcto

	// --- Errores de sintaxis ---
	MS_ERR_SYNTAX,            // Error de sintaxis (p. ej. token inesperado)
	MS_ERR_UNCLOSED_QUOTE,    // Comilla sin cerrar
	MS_ERR_BAD_SUBSTITUTION,  // Error en expansión de variables

	// --- Errores de ejecución ---
	MS_ERR_CMD_NOT_FOUND,     // Comando no encontrado
	MS_ERR_PERMISSION,        // Permiso denegado
	MS_ERR_IS_DIRECTORY,      // Intento de ejecutar un directorio
	MS_ERR_NUMERIC_ARG,       // Error de argumento numérico (exit, etc.)

	// --- Errores del sistema ---
	MS_ERR_FORK,              // Fallo al hacer fork()
	MS_ERR_PIPE,              // Fallo al crear pipe()
	MS_ERR_DUP2,              // Fallo al duplicar descriptor
	MS_ERR_MALLOC,            // Fallo en malloc()
	MS_ERR_FILE,              // Fallo al abrir/leer/escribir archivo

	// --- Señales y otros ---
	MS_ERR_SIGNAL,            // Señal recibida (SIGINT, SIGQUIT, etc.)
	MS_ERR_UNKNOWN            // Error desconocido

} t_ms_status;

int	ms_handle_status(t_ms_status status, const char *context);

#endif