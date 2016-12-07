struct link_map_list
{
  unsigned int r_version;
  unsigned int r_map;
}lml;

struct link_map
{
  /* Base address shared object is loaded at.  */
  unsigned int l_addr;
  unsigned int l_name;
  /* Dynamic section of the shared object.  */
  unsigned int l_ld;
  unsigned int l_next;
  unsigned int l_prev;
}lm;

/*  Check _r_debug in ld-2.4.so  */
long r__debug = 0x4b56a4;
