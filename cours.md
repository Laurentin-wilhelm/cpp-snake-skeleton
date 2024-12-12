
g++ -o snake snake.cpp fonctions.cpp == LENT


# bout par bout


    g++ -c snake.cpp
    g++ -c fonctions.cpp
    g++ -o snake snake.o fonctions.o

## conflit avec les include
attention include plusieurs fois un hpp = 😠

solution:

     #pragma once

en haut du hpp

