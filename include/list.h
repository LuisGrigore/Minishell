/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:41 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/28 16:16:42 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_node
{
	void			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_gen_list
{
	t_node			*head;
	size_t			size;
}					t_gen_list;

t_gen_list			*init_list(void);
void				push_end(t_gen_list *list, void *value);
void				destroy_gen_list(t_gen_list *list,
						void(value_destroyer)(void *));
/**
 * @brief Recorre todos los elementos de la lista y aplica una función a cada valor.
 *
 * Esta función itera sobre cada nodo de la lista enlazada genérica y ejecuta
 * la función proporcionada (`func`) con el puntero `value` de cada nodo.
 * 
 * @param list Puntero a la lista genérica a recorrer.
 * @param func Función que recibe un `void *` (el valor del nodo) y no retorna nada.
 *
 * @note La función `func` no debe modificar la estructura interna de la lista
 *       (por ejemplo, no liberar nodos), ya que esto podría corromper la iteración.
 *
 * @warning Si `list` o `func` son NULL, no se hace nada.
 */
void	traverse(t_gen_list *list, void (*func)(void *));


/**
 * @brief Busca el primer elemento de la lista que cumpla una condición.
 *
 * Recorre secuencialmente la lista y aplica la función `predicate` a cada valor.
 * Cuando `predicate` devuelve distinto de 0 (true), la búsqueda se detiene y
 * se retorna el puntero `value` del nodo actual.
 *
 * @param list Puntero a la lista genérica donde se realizará la búsqueda.
 * @param predicate Función que recibe un `void *` y devuelve un `int`
 *                  (0 para falso, distinto de 0 para verdadero).
 *
 * @return 
 * - El puntero `void *` al valor del primer nodo que cumpla la condición.
 * - NULL si no se encuentra ningún valor o si los parámetros son inválidos.
 *
 * @note Esta función retorna el `value` almacenado en el nodo, **no** el puntero al nodo.
 */
void	*find_in_list(t_gen_list *list, int (*predicate)(void *));


#endif
