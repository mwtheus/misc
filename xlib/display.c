#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

int main(int argc, char *argv[]) {
  int screen;
  XEvent event;
  Display *display;
  Window window, child_window;

  // Here, we are opening a connection to the server
  display = XOpenDisplay(NULL);

  if (display == NULL) { // If not connected
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  screen = DefaultScreen(display);

  // Parent window
  window = XCreateSimpleWindow(
    display, RootWindow(display, screen), 
    200, 200, 500, 300, // x, y, width, height
    1, BlackPixel(display, screen), WhitePixel(display, screen)
    // border width (pixel), border color, background color
  );

  XSelectInput(display, window, ExposureMask | KeyPressMask); // Input event
  XMapWindow(display, window); // Display (map) window

  // Child Window
  child_window = XCreateSimpleWindow(
    display, window, 
    20, 20, 200, 100,
    1, BlackPixel(display, screen), WhitePixel(display, screen)
  );

  XSelectInput(display, child_window, ExposureMask | KeyPressMask);
  XMapWindow(display, child_window);

  while(1) {
    XNextEvent(display, &event);
    
    if (event.xany.window == child_window) {
      if (event.type == Expose) {
        XDrawLine(
          display, child_window, DefaultGC(display, screen), 
          10, 10, 60, 60
        );
      }
    }
  }
  
  return 0;
}

// $ gcc -o display display.c -lX11
