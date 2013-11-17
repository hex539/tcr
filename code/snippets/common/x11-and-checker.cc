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
  XStoreName(dpy,win,"Output");gc=
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

vec2 circumcentre(vec2 a,vec2 b,vec2 c){
  vec2 mid=(a+b)/2, add=(c-b);
  vec2 ab=(b-a).transverse(), ac=(c-a).transverse(); // (x,y) => (-y,x)
  real t=((c/2-b/2)/(ac))/((ab)/(ac));
  return (a+b)/2+ab*t;
}

-------------------------------------------------------------------------------------

echo `tr -dc A-Za-z0-9 </dev/urandom | head -c 1000000` ## make random |10^6| string

-------------------------------------------------------------------------------------

#!/bin/bash

tests=0; right=0; long=0;
g++ -std=c++11 -Os -o $1 $1.cc || exit
for tf in tests/$1/*.in                                                          #*/#
  do
    tn=`basename "$tf" .in`
    answer="`cat 'tests/$1/$tn.out' 2>/dev/null`"
    printf "    %s\n " "$tn"
    printf '%.s-' `eval echo {1..$[ 6 + ${#tn} ]}` && echo
    {
      rl=$(date +%s%N)
      output="`./$1 < "$tf"`"
      rl=$(printf %2.3fs `bc <<< "scale=3; ($(date +%s%N) - $rl) / (10^9)"`)
      [[ $rl > $long ]] && long=$rl
    }
    printf "`tput bold`%s`tput sgr0`\n---\n" "$output"
    if [ -n "$answer" ]
      then
        ((++tests))
        echo "$answer"
        [ "$output" == "$answer" ] && ((++right)) \
          || (echo -e 'bold\nsetaf 4' | tput -S && echo "doesn't match`tput sgr0`")
      fi
    echo
  done
[ $tests != 0 ] && echo -n "`tput bold`$right/$tests correct`tput sgr0` "
echo "(worst time = $long)"
rm -f $1
exit 0
