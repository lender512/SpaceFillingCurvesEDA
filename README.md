# SpaceFillingCurvesEDA

Instrucciones:
    Usar 1, 2 y 3 para seleccinar el tipo de curva
    Usar + o - para modificar el factor de escalado (zoom)

Como correrlo:
    g++ -c main.cpp
    g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
    ./sfml-app

    O resumido:
    g++ -std=c++17 -g -c main.cpp &&  g++ -g main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system && ./sfml-app
 
Leyenda:
   Si se presiona el 1, entonces se muestra el GRAY filling curve.
   Si se presiona el 2, entonces se muestra el DOUBLE_GRAY filling curve.
   Si se presiona el 3, entonces se muestra el Z_ORDER filling curve.
   
   
Algoritmos:
  Intercalado: La función intercalado usada para añadir un cero entre cada bit, para posteriormente sumar dos intercalados (con un defase) y tener el Z-order.
    1.Se parte de un tamaño de particion 16bits (maximo) y el tamaño de partición se reduce a la mitad por iteración
      1.1. Cada particion se parte a la mitad con (STEP/2) bits X entre ambos
      1.2. Se vuelven 0s los bits X que estan en el medio de las nuevas particiones
      
  Z-order:
    1. Se obtiene el intercalado de X
    2. Se obtiene el intercalado de Y y se desplaza hacia la izquierda
    3. Se suman (or)
  
  Gray-order:
    1. Se obtiene el Z-order
    2. Se aplica gray code (XOR entre el valor y el valor desplazado a la derecha)

  Double Gray-order:
    1. Se aplica gray code a cada coordenada
    2. Se obtiene el Z-order
    3. Se aplica gray code (XOR entre el valor y el valor desplazado a la derecha)

      
    
 
 
 
 
