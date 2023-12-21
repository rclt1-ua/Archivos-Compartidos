Para Compilar ______________________________________

      Es necesario tener instaladas la librería X11 y la librería OpenGL.
      - Para instalar la librería X11: sudo apt install libx11-dev
      - Para instalar la librería OpenGL: sudo apt install freeglut3-dev

gcc ./tigr/tigr.c ATM.c -o atm -I./tigr -lGLU -lGL -lX11 -lm
