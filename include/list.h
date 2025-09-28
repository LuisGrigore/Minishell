/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:18:41 by dmaestro          #+#    #+#             */
/*   Updated: 2025/09/28 17:37:35 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_node
{
	void			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_gen_list
{
	t_node			*head;
	t_node			*tail;
	size_t			size;
}					t_gen_list;

typedef struct s_iter
{
	t_node			*current;
}					t_iter;

/**
 * @brief Inicializa una lista vacía.
 *
 * @return Puntero a la lista creada o NULL si falla la asignación.
 */
t_gen_list			*init_list(void);

/**
 * @brief Inserta un valor al final de la lista (O(1)).
 *
 * @param list Lista donde insertar el valor.
 * @param value Puntero al valor a insertar.
 */
void				push_end(t_gen_list *list, void *value);

/**
 * @brief Inserta un valor al principio de la lista (O(1)).
 *
 * @param list Lista donde insertar el valor.
 * @param value Puntero al valor a insertar.
 */
void				push_front(t_gen_list *list, void *value);

/**
 * @brief Elimina el primer nodo de la lista y devuelve su valor.
 *
 * @param list Lista de la que eliminar el primer nodo.
 * @return Valor almacenado en el primer nodo o NULL si la lista está vacía.
 */
void				*pop_front(t_gen_list *list);

/**
 * @brief Destruye toda la lista y sus nodos.
 *
 * @param list Lista a destruir.
 * @param value_destroyer Función que libera cada valor almacenado,
	puede ser NULL.
 */
void				destroy_gen_list(t_gen_list *list,
						void(value_destroyer)(void *));

/**

	* @brief Recorre todos los elementos de la lista y aplica una función a cada valor.
 *
 * @param list Lista a recorrer.
 * @param func Función a aplicar a cada valor.
 */
void				traverse(t_gen_list *list, void (*func)(void *));

/**
 * @brief Elimina nodos de la lista que cumplan una condición.
 *
 * @param list Lista a modificar.
 * @param predicate Función que devuelve true si el nodo debe eliminarse.
 * @param value_destroyer Función para liberar el valor de cada nodo eliminado.
 */
void				remove_if(t_gen_list *list, bool (*predicate)(void *),
						void (*value_destroyer)(void *));

/**
 * @brief Busca el primer elemento que cumpla una condición.
 *
 * @param list Lista donde buscar.
 * @param predicate Función que devuelve true si el valor cumple la condición.
 * @return Valor del primer nodo que cumpla la condición,
	o NULL si no se encuentra.
 */
void				*find_in_list(t_gen_list *list, bool (*predicate)(void *));

/**
 * @brief Inicializa un iterador al inicio de la lista.
 *
 * @param list Lista a iterar.
 * @return Iterador apuntando al primer nodo.
 */
t_iter				iter_start(t_gen_list *list);

/**
 * @brief Devuelve el siguiente valor de la lista usando el iterador y avanza.
 *
 * @param it Iterador de la lista.
 * @return Valor del nodo actual y avanza, o NULL si se llega al final.
 */
void				*iter_next(t_iter *it);

#endif
