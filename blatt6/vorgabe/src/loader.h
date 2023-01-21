/*
 * \file loader.h
 *
 */
#ifndef LOADER_H
#define LOADER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

/*
 * \brief Struct for an operation that can be loaded dynamically
 *
 * A dynamic library that provides a loadable operation has to define
 * a structure of type `struct opfn` and has to export the symbol,
 * making it loadable by a using application.
 */
struct opfn{
	int (*op)(int, int);		/* <- Function pointer to actual operation */
};

/*
 * \brief Struct for an dynamically loaded operation
 */
struct dynop{
	int (*op)(int, int);		/* <- Function pointer to operation */
	void *libhandle;		/* <- Pointer to loaded library */
};

/*
 * \brief Reduces provided values using function `op`
 *
 * \param dest		Points to allocated memory for an integer where the
 *			result will be written
 * \param values	Pointer to an integer array with values to reduce
 * \param count		Number of elements in integer array `values`
 * \param op		Function to use for reduce. Any function that has
 *			a return type of `int` and takes to `int` arguments
 *			is valid.
 * \return		0 on success, -1 on error in which case `errno`
 *			is set to indicate the cause
 */
int reduce(int *dest, const int *input, size_t input_len, int op(int, int));

/*
 * \brief Loads a dynamic operation with name `filename`
 *
 * \param dest		Pointer to struct of type `dynop` to load to
 * \param filename	Name of dynamic operation to load
 * \return		0 on success, -1 on error in which case `errno`
 *			is set to indicate the cause
 */
int load_op(struct dynop *dest, const char *filename);

/*
 * \brief Unsets a `dynop` structure
 *
 * If argument is invalid, `unload_op` does nothing.
 *
 * \param		Pointer to struct of type `dynop` to unset
 */
void unload_op(struct dynop *);

#endif
