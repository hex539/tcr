#include <X11/Xlib.h>
{ Display* dpy;
  Window root,win;
  XEvent ev; GC gc;
  int screen;

  dpy=XOpenDisplay(NULL);
  screen=DefaultScreen(dpy);
  root=RootWindow(dpy,screen);
  win=
  XCreateSimpleWindow(dpy,root,1,1,512,512,0,BlackPixel(dpy,screen),BlackPixel(dpy,screen));
  XStoreName(dpy,win,"Output");
  gc=
  XCreateGC(dpy,win,0,NULL);
  XSetForeground(dpy,gc,WhitePixel(dpy,screen));
  XSelectInput(dpy,win,ExposureMask|ButtonPressMask);
  XMapWindow(dpy,win);

  bool done=0;
  while (!done){
    XNextEvent(dpy,&ev);
    switch (ev.type){
      case Expose: XDrawArc(dpy,win,gc,20,20,8,8,0,360<<6); break;
      case ButtonPress: done=1; break;
      default: break;
    }
  }

  XUnmapWindow(dpy,win);
  XDestroyWindow(dpy,win); }

-------------------------------------------------------------------------------------
/*
 * Returns the centre of a circle passing through points a,b,c. If a,b,c are colinear
 * it will divide by 0 so check the crossproduct of (ab) with (bc) is nonzero first.
 */
vec2 circumcentre(vec2 a,vec2 b,vec2 c){
  vec2 mid=(a+b)/2, add=(c-b);
  vec2 ab=(b-a).transverse(), ac=(c-a).transverse(); // transverse: (x,y) => (-y,x)
  real t=((c/2-b/2)/(ac))/((ab)/(ac));
  return (a+b)/2+ab*t;
}

-------------------------------------------------------------------------------------

echo `tr -dc A-Za-z0-9 </dev/urandom | head -c 1000000`  #  makes a random |10^6| string

-------------------------------------------------------------------------------------

#!/bin/bash

tests=0; ac=0;
f="`basename $1 .java`"
javac "$f.java" || exit
for tf in tests/$f/*.in                                                          #*/#
  do
    tn=`basename "$tf" .in`
    answer="`cat \"tests/$f/$tn.out\" 2>/dev/null`"
    echo "answer is $answer from tests/$f/$tn.out"
    printf "    %s\n " "$tn"
    printf '%.s-' `eval echo {1..$[ 6 + ${#tn} ]}` && echo
    output="`java $f < "$tf"`"
    printf "%s\n---\n" "$output"
    if [ -n "$answer" ]
      then
        ((++tests))
        echo "$answer"
        [ "$output" == "$answer" ] && ((++ac)) || echo "doesn't match"
      fi
    echo
  done
[ $tests != 0 ] && echo "   ::: $ac/$tests correct :::"
rm *.class
