// #include <pthread.h>
// took this out because, even though I might use multiple threads in the future, compiling with it is just cumbersome.
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

Display *dis;
int screen;
Window win;
GC gc;

XEvent event;
KeySym key;
char text[255];

void init_x() {
        dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);

        unsigned long HEX(char v[8]) { // Even though both HEX and RGB don't get used HERE specifically and 
				       // we can't call this in any other functions, we can still include it, just in case
        int r, g, b;
	r = 16*(v[1] - 48 - (((v[1] - 48)>>4)*7)) + v[2] - 48 - (((v[2] - 48)>>4)*7);
	g = 16*(v[3] - 48 - (((v[3] - 48)>>4)*7)) + v[4] - 48 - (((v[4] - 48)>>4)*7);
	b = 16*(v[5] - 48 - (((v[5] - 48)>>4)*7)) + v[6] - 48 - (((v[6] - 48)>>4)*7);
	return b + (g<<8) + (r<<16);
	}

        unsigned long RGB(int r, int g, int b) {
	return b + (g<<8) + (r<<16);
	}

	int depth;
	unsigned int class;
	Visual *visual;
	unsigned long valuemask;
        XSetWindowAttributes *attributes;

//    	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, 500, 500, 5, RGB(255,255,255), HEX("#000000"));
// who creates a "simple window"? Just read some of the documentation. Or copy what I have...
        win=XCreateWindow(dis,DefaultRootWindow(dis), 0, 0, 500, 500, 5, CopyFromParent, CopyFromParent, CopyFromParent, 0, attributes);
	XSetStandardProperties(dis,win,"Conway\'s Game of Life","cgol",None,NULL,0,NULL);

	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

        gc=XCreateGC(dis, win, 0,0);

        XSetBackground(dis,gc,RGB(0,0,0));
	XSetForeground(dis,gc,HEX("#000000"));

	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void close_x() { // This doesn't get used. Not yet anyhow. If you're readin this you can delete it..
        XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);
};

void redraw() { // don't know Why exactly I'm calling a function FOR a single function, but hell let's include it.
XClearWindow(dis, win);
}

/* void *Eve(void *vargp) { // ignore. If you feel like deleting, that's fine

        unsigned long HEX(char v[8]) { // supplies long integer string from set hex value; This can also be accomplished by passing RGB()
        int r, g, b;
        r = 16*(v[1] - 48 - (((v[1] - 48)>>4)*7)) + v[2] - 48 - (((v[2] - 48)>>4)*7);
        g = 16*(v[3] - 48 - (((v[3] - 48)>>4)*7)) + v[4] - 48 - (((v[4] - 48)>>4)*7);
        b = 16*(v[5] - 48 - (((v[5] - 48)>>4)*7)) + v[6] - 48 - (((v[6] - 48)>>4)*7);
        return b + (g<<8) + (r<<16);
        };

	while(1) {
		XSetForeground(dis,gc,HEX("#00FFFF"));
		XFillRectangle(dis,win,gc,0,0,10,10);
		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
		printf("Event");
		};
		if (event.type==KeyPress&&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
                        if (text[0]=='q') {
				close_x();
			};
			if (text[0]=='c') {
				XClearWindow(dis,win);
			};
		};
		if (event.type==ButtonPress) {
                   int x, y;
                    x = event.xbutton.x; 
                    y = event.xbutton.y;
		    XSetForeground(dis,gc,HEX("#00FFFF"));
                    XFillRectangle(dis,win,gc,x,y,10,10);
		 };
   	 
	};

}; */

void gull() {

        unsigned long HEX(char v[8]) { // supplies long integer string from set hex value; This can also be accomplished by passing RGB()
        int r, g, b;
        r = 16*(v[1] - 48 - (((v[1] - 48)>>4)*7)) + v[2] - 48 - (((v[2] - 48)>>4)*7);
        g = 16*(v[3] - 48 - (((v[3] - 48)>>4)*7)) + v[4] - 48 - (((v[4] - 48)>>4)*7);
        b = 16*(v[5] - 48 - (((v[5] - 48)>>4)*7)) + v[6] - 48 - (((v[6] - 48)>>4)*7);
        return b + (g<<8) + (r<<16);
        }

        unsigned long RGB(int r, int g, int b) { // supplies long integer string from an RGB value - i.e. RGB(255,255,255) for white;
        return b + (g<<8) + (r<<16);
        };

        char stdinchar[2]; // see if stdin conatins data, and if so to write data to variable
        if (feof (stdin)==1) {
        fgets(stdinchar, 2, stdin);
        }

        bool b[721][1001]; // "main" grid
        bool c[721][1001]; // temp
        long int i, j, k;
	
	for (k = 0; k < stdinchar[0]; k++) { // randomize grid based on stfin value
	rand();
	}
	
        for (i = 0; i < 721; i++) { // write first grid with random data -- This can easily be replaced with a design of your choice; 
                                    // keep in mind i corresponds to y value not x: This may be confusing due just to the way arrays are constructed
                                    // alternatively, you may swap the i and j values to remap the grid to make it more manageable / easier to comprehend
                                    // just make sure if you do swap these values; you do so for all for loops/grid management.
                for (j = 0; j < 1001; j++) {
                b[i][j] = rand() % 2;
                };
                j = 0;
        };
	
	while(1) {
                 redraw(); // This isn't really necessary; Just something I was toying with...

                 long int i, j, med;
                 for (i = 0; i < 721; i++) {
                        for (j = 0; j < 1001; j++) {
                        med = abs((b[i][j-1] + b[i-1][j-1] + b[i-1][j] + b[i-1][j+1] + b[i][j+1] + b[i+1][j+1] + b[i+1][j] + b[i+1][j-1] - 3) - (2*b[i][j]) + ((b[i][j-1] + b[i-1][j-1] + b[i-1][j] + b[i-1][j+1] + b[i][j+1] + b[i+1][j+1] + b[i+1][j] + b[i+1][j-1])*b[i][j]));

			// if your new to cgol, you're probably wondering what the fuck the above statement is. Calm yourself; it's nothing too complex. 
			// Just a mathematical statement that circumvents some if logic you would otherwise be forced to use for taking into account the 
			// past cell's state and the number of surrounding cells.

                        c[i][j] = !((med + 4 + (b[i][j] * 2)) / (5 + (b[i][j] * 4)));    // build new grid + some leftover math I didn't feel like incorperating in the previous statement
											 // for brevity's sake
                                if (b[i][j]) {                                           // read old grid
                                XSetForeground(dis,gc,HEX("#FFFFFF"));
                                XFillRectangle(dis,win,gc,j,i,1,1); // set some pixels on the window!!
                                } else {
                                XSetForeground(dis,gc,HEX("#000000"));
                                XFillRectangle(dis,win,gc,j,i,1,1); // set more pixels on the window!!
                                }
                        };
                        j = 0;
                 };
                 for (i = 0; i < 721; i++) { // write main grid with temp grid data, destroying the old main grid in the process
                        for (j = 0; j < 1001; j++) {
                        b[i][j] = c[i][j];
                        };
                        j = 0;
                 };

	}; // do it all over again!

}

int main() {

init_x(); // create the window
// pthread_t eve;
// pthread_create(&eve, NULL, Eve, NULL);
// printf("Afterburn");
gull(); // D o  Y o u  W a n t  T o  P l a y  A  G a m e . . . ?
// pthread_join(eve, NULL);
// ignore all the posix thread messiness. I was trying to handle XEvents in a new thread...
};
