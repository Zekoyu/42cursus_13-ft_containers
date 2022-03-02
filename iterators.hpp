/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 02-03-2022 10:35 by                                             */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	
	/*
		Iterator tags are used to determine of which type is a given operator.

		They are mostly used for optimization purposes, for instance if we have
		different implementations of a function depending on the iterator type, instead
		of checking for the type at runtype (if is_random_access_iterator(it))
		we can check it at compile time using iterator_traits<it>::iterator_category
	*/

	/* Defines an input iterator (Reads forward) */
	struct input_iterator_tag { };

	/* Defines an output iterator (Writes forward) */
	struct output_iterator_tag { };

	/* Defines a forward iterator (Reads/Writes forward) */	
	struct forward_iterator_tag : public input_iterator_tag { };

	/* Define a bidirectional iterator (Reads/Writes forward/backward) */
	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	/* Define a random access iterator (Read/Writes anywhere (random access like an array)) */
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

}