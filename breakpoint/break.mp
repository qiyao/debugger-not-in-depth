input boxes;
verbatimtex
%&latex
  \documentclass{article}
  \usepackage{xcolor}
  \begin{document}
  etex

% Original
beginfig(1);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  inst.b etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);
endfig;
% Set breakpoint
beginfig(2);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  int 3 etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);

%  label.urt(btex pc etex , instb1.sw - (20bp,0));
endfig;

% Hit breakpoint
beginfig(3);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  int 3 etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);

  label.urt(btex pc etex , instc1.sw - (20bp,0));
endfig;

% Decrease PC
beginfig(4);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  int 3 etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);

  label.urt(btex pc etex , instb1.sw - (20bp,0));
endfig;

% Decrease pc
beginfig(5);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  inst.b etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);

  label.urt(btex pc etex , instb1.sw - (20bp,0));
endfig;

% Single step
beginfig(6);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  inst.b etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);

  label.urt(btex pc etex , instc1.sw - (20bp,0));
endfig;

% Displaced stepping: copy.
beginfig(7);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex  inst.a etex);
  boxit.instb1(btex  int 3 etex);
  boxit.instc1(btex  inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.pad1(btex inst.b1 etex);
  boxit.pad2(btex inst.b2 etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1, pad1, pad2);

  label.urt(btex pc etex , pad1.sw - (20bp,0));
  label.urt(btex scratch pad etex , pad1.se + (2bp,0));
endfig;

% Single step
beginfig(8);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex inst.a etex);
  boxit.instb1(btex int 3 etex);
  boxit.instc1(btex inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1);

  label.urt(btex pc etex , instc1.sw - (20bp,0));
endfig;


beginfig(9);
  boxjoin(a.sw=b.nw; a.se=b.ne);
  boxit.boxa1(btex  etex);
  boxit.dota1(btex \vdots etex);
  boxit.insta1(btex inst.a etex);
  boxit.instb1(btex  {\color{red}inst.b} etex);
  boxit.instc1(btex inst.c etex);
  boxit.dotb1(btex \vdots etex);
  boxit.pad1(btex {\color{blue}inst.b1} etex);
  boxit.pad2(btex {\color{blue}inst.b2} etex);
  boxit.boxb1(btex  etex);

  boxa1.dx = 15bp;
  drawboxed(boxa1, dota1, insta1, instb1, instc1, dotb1, boxb1, pad1, pad2);

  label.urt(btex scratch pad etex , pad1.se + (2bp,0));
endfig;

end