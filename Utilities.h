/*
*   Created by N.Richard
*   Date de création : 17 novembre 2013
*	Date de version : 25 janvier 2014
*   Version 1.5
*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <sstream>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
 
/*****************************************
	Paramètre inutilisés (passer -Wall)
*****************************************/

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

/****************************************
	    Moteur de nombres aléatoires
****************************************/

void initRandomEngine ();
float getRand(float inter_a, float inter_b);


/*****************************
		Transtypage
*****************************/

template<typename T>
bool from_string( const std::string & Str, T & Dest );

template<typename T>
bool to_string( const T & Orig, const std::string & Str);

template<typename T>
T& from_string( const std::string & Str);

template<typename T>
const std::string to_string( const T & Orig);

/*****************************
	Gestion des benchmarks
*****************************/

#define t_start struct timeval tv1, tv2; gettimeofday(&tv1, NULL)
#define t_end gettimeofday(&tv2, NULL)
#define t_value ((tv2.tv_sec-tv1.tv_sec)*1e6 + tv2.tv_usec-tv1.tv_usec)
#define t_show printf ("\nTemps de calcul : %g ms\n", t_value/1e3)


/***********************************
	Manipulation de fichiers
***********************************/

bool isReadable (const std::string& filePath);

#endif //UTILITIES_H
