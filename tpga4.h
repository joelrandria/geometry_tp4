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

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 680

// Accès aux options de la ligne de commandes
extern char *optarg;
extern int opterr;

// Variables globales communes initialisées au démarrage de l'application
extern int _point_count;
extern vertex* _points;

// Variables globales initialisées spécifiquement par les différents exercices
extern int_list* _convex_hull;

// Gestionnaires d'évènements
void on_idle_event();

// Fonctions d'affichage
void draw();
void draw_points(const vertex* points, const unsigned int point_count);
void draw_hull(const vertex* points, const int_list* hull_points);


#endif
