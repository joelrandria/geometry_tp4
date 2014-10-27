#ifndef __TPGA4_H__
#define __TPGA4_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include <string.h>

#include "tpga4_ex1.h"
#include "tpga4_ex2.h"


#include "vertex.h"
#include "int_list.h"


#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768

// Accès aux options de la ligne de commandes
extern char *optarg;
extern int opterr;

// Variables globales communes initialisées au démarrage de l'application
extern int _point_count;	//nombre de points défini en paramêtre avec l'option "-n"
extern vertex* _points;		//tableau de points de taille _point_count. les points sont définis aléatoirement.

// Variables globales initialisées spécifiquement par les différents exercices
extern int_list* _convex_hull;

extern vertex* _convex_ordonnes;	//reconstruire _convex_hull à partir d'une liste chainée ordonnée est en O(n log(n))	log(n) étant la recherche de _points[i] == vertex de la chaine. 
									//Autant donnée le premier vertex de la chaine (ou donnée un "int id" à chaque vertex égal au "i" de point[i]).

// Gestionnaires d'évènements
void on_idle_event();

// Fonctions d'affichage
void draw();
void draw_points(const vertex* points, const unsigned int point_count);
void draw_hull(const vertex* points, const int_list* hull_points);
void draw_graham(const vertex* debList);


#endif
