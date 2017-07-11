//code based on https://www.wikiwand.com/en/Maze_generation_algorithm
#include "maze.h"

int init(Node **nodes,int width, int height ){
    int i, j;
    Node *n;

    //Allocate memory for maze
    *nodes = calloc( width * height, sizeof( Node ) );

    if ( *nodes == NULL ){
        return 1;
    }
    //Setup crucial nodes
    for ( i = 0; i < width; i++ ){
        for ( j = 0; j < height; j++ ){
            n = *nodes + i + j * width;
            if ( i * j % 2 ){
                n->x = i;
                n->y = j;
                n->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
                n->c = ' ';
            }else{
                n->c = '#'; //Add walls between nodes
            }
        }
    }
    return 0;
}

Node *link( Node *n,Node * nodes, int width, int height ){

    //Connects node to random neighbor (if possible) and returns
    //address of next node that should be visited
    int x, y;
    char dir;
    Node *dest;

    //Nothing can be done if null pointer is given - return
    if ( n == NULL ) {
            return NULL;
    }
    //While there are directions still unexplored
    while ( n->dirs ){
        //Randomly pick one direction
        dir = ( 1 << ( rand( ) % 4 ) );
        //If it has already been explored - try again
        if ( ~n->dirs & dir ){
                continue;
        }
        //Mark direction as explored
        n->dirs &= ~dir;
        //Depending on chosen direction
        switch ( dir ){
            //Check if it's possible to go right
            case 1:
                if ( n->x + 2 < width ){
                    x = n->x + 2;
                    y = n->y;
                }
                else continue;
            break;
            //Check if it's possible to go down
            case 2:
                if ( n->y + 2 < height ){
                    x = n->x;
                    y = n->y + 2;
                }
                else continue;
            break;
            //Check if it's possible to go left
            case 4:
                if ( n->x - 2 >= 0 ){
                    x = n->x - 2;
                    y = n->y;
                }
                else continue;
            break;
            //Check if it's possible to go up
            case 8:
                if ( n->y - 2 >= 0 ){
                    x = n->x;
                    y = n->y - 2;
                }
                else continue;
            break;
        }
        //Get destination node into pointer (makes things a tiny bit faster)
        dest = nodes + x + y * width;
        //Make sure that destination node is not a wall
        if ( dest->c == ' ' ){
            //If destination is a linked node already - abort
            if ( dest->parent != NULL ){
                    continue;
            }
            //Otherwise, adopt node
            dest->parent = n;
            //Remove wall between nodes
            nodes[n->x + ( x - n->x ) / 2 + ( n->y + ( y - n->y ) / 2 ) * width].c = ' ';
            //Return address of the child node
            return dest;
        }
    }
    //If nothing more can be done here - return parent's address
    return n->parent;
}

void drawMaze(Node * nodes, int width, int height ){
    int i, j;
    //Outputs maze to terminal - nothing special
    for ( i = 0; i < height; i++ ){
        for ( j = 0; j < width; j++ ){
            printf( "%c", nodes[j + i * width].c );
        }
        printf( "\n" );
    }
}

Node * createMaze( int width, int height ){
    int i, badarg;
    long seed;
    Node *start, *last;
    //Allow only odd dimensions
    if ( !( width % 2 ) || !( height % 2 ) ){
        fprintf( stderr, "dimensions must be odd!\n");
        return NULL;
    }
    //Do not allow negative dimensions
    if ( width <= 0 || height <= 0 ){
        fprintf( stderr, "dimensions must be greater than 0!\n");
        return NULL;
    }
    //Seed random generator
    srand( time( NULL ) );
    Node *nodes; //Nodes array
    //Initialize maze
    if ( init(&nodes, width, height ) ){
        fprintf( stderr, "out of memory!\n");
        return NULL;
    }
    //Setup start node
    start = nodes + 1 + width;
    start->parent = start;
    last = start;
    //Connect nodes until start node is reached and can't be left
    while ( ( last = link( last ,nodes, width, height) ) != start );
    //draw(nodes, width, height );
    return nodes;
}
