input boxes;
beginfig(1);



%Struct so_list
  boxjoin(a.sw=b.nw;a.se=b.ne);

  boxit.next(btex so\_list *so\_list etex);

  boxit.lm_info(btex ln\_info *lm\_info etex );
  boxit.so_original_name(btex char so\_original\_name[]  etex );

  boxit.so_name(btex char so\_name[] etex );
  boxit.so_dot1(btex \vdots etex);
  boxit.so_dot2(btex \vdots etex);


% Struct lm_info
  boxjoin(a.sw = b.nw; a.se = b.ne)
  boxit.lm(btex gdb\_byte *lm  etex);
  boxit.l_addr(btex CORE\_ADDR l\_addr etex);


%
  boxjoin(a.sw=b.nw;a.se=b.ne);
  boxit.mem1(btex memory,length=linux\_map\_size etex);
  
w:=.6u;
next.dx=w;
lm.dx=w;
mem1.dx=w;

lm.nw = next.ne + (4u, 0);
mem1.nw = lm.ne + (4u, 0);



drawboxed(next, lm_info, so_original_name, so_name, so_dot1, so_dot2)
drawboxed(lm, l_addr);
drawboxed(mem1);

drawarrow (lm_info.e - (.8u,0)){right}...{right}lm.nw;
drawarrow (lm.e - (.8u,0)){right}...{right}mem1.w;

label.urt(btex so\_list etex , next.nw+(0,4bp));
label.urt(btex lm\_info etex , lm.nw+(0,4bp));

endfig;

end;