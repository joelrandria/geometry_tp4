#ifndef __TPGA2_H__
#define __TPGA2_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

#include "vertex.h"

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 680

// Accès aux options de la ligne de commandes
extern char *optarg;
extern int opterr;

// Variables globales communes
extern int _point_count;
extern vertex* _points;

#endif
