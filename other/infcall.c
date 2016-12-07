extern int bar (int);

void
foo ()
{
  /* i is avaliable before.  */
  o = bar (i);
}
