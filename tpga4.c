#include "tpga4.h"
#include "tpga4_ex1.h"

#include <string.h>

// Exercice sélectionné
int _opt_selex = 0;

// Options exercice 1
char* _optex1_filename = 0;

void winInit()
{
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void usage()
{
  printf("Usage: ./tpga4 {-1 -ofilename }\r\n");
}

int main(int argc, char **argv)
{
  int c;

  opterr = 0;
  while ((c = getopt(argc, argv, "1o:")) != EOF)
  {
    switch (c)
    {
    case '1': _opt_selex = 1; break;

    case 'o': _optex1_filename = optarg; break;

    default: usage(); break;
    }
  }

  if (!_opt_selex)
  {
    usage();
    return EXIT_SUCCESS;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(5,5);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("TP Géométrie Algorithmique #2");

  winInit();

  if (_opt_selex == 1)
  {
    if (_optex1_filename == 0)
      usage();
    else
      tpga4_ex1();
  }

  return EXIT_SUCCESS;
}
