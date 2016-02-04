#include <glib.h>
#include <stdio.h>

int main(G_GNUC_UNUSED int argc, G_GNUC_UNUSED char **argv)
{
  fprintf(stdout, "Hello main in client.\n");

  /* clean-up */
  fprintf(stdout, "done.\n");
  return 0;
}
