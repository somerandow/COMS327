//
// Created by wojoinc on 2/5/17.
//

#include <stdlib.h>
#include "dijkstra.h"
//TODO test this

int main(int argc, char *argv[]){
    dungeon_t *dungeon = generateDungeon();
    graph_t *graph = create_graph_dungeon(dungeon,&dungeon->wunits[50][50]);
    dijkstra(graph);
}


void dijkstra(graph_t *graph){
    // array with same size as dungeon, to keep track of which
    // cells have been considered visited
    //begin with source

    //setup source vertex.
    graph->source->visited=TRUE;
    //create heap
    heap_t *heap = heap_init((size_t)graph->size);

    //add source to heap
    add_with_priority(heap, graph->source, graph->source->weight);
    graph->source->queued = TRUE;

    vertex_t *cursor;
    while(heap->size!=0){
        cursor = remove_min(heap);
        cursor->visited = TRUE;
        update_adjacent(heap,cursor);
    }
}

graph_t *create_graph_dungeon(dungeon_t *dungeon, w_unit_t *source){
    graph_t *graph = malloc(sizeof(graph_t));
    graph->dungeon = dungeon;
    graph->size = d_HEIGHT*d_WIDTH;
    graph->verticies = (vertex_t *)malloc(sizeof(vertex_t) * d_HEIGHT * d_WIDTH);


    for (int i = 0; i < d_HEIGHT; ++i) {
        for (int j = 0; j < d_WIDTH; ++j) {

            graph->verticies[i*d_WIDTH +j] = (vertex_t){0,FALSE,FALSE,&dungeon->wunits[i][j],NULL,NULL};

            /*assign neighbors to be the 8 units surrounding the vertex.
             * each one is a pointer the neighbors location in
             * graph.verticies, and subsequently, its memory address.
             *
             * NOTE: skip this if the unit is a dungeon border, as neighbors
             * would be out of the range of the array. We also do not care about the borders
             * for the purposes of dijkstra's
             */
            if(dungeon->wunits[i][j].type==IMPASS)break;//check that unit is not a dungeon border

            graph->verticies[i*d_WIDTH +j].neighbors = (vertex_t **)calloc(sizeof(vertex_t),8);

            graph->verticies[i*d_WIDTH +j].neighbors[0] = &graph->verticies[(i-1)*d_WIDTH +j-1];
            graph->verticies[i*d_WIDTH +j].neighbors[1] = &graph->verticies[(i-1)*d_WIDTH +j];
            graph->verticies[i*d_WIDTH +j].neighbors[2] = &graph->verticies[(i-1)*d_WIDTH +j+1];
            graph->verticies[i*d_WIDTH +j].neighbors[3] = &graph->verticies[(i)*d_WIDTH +j-1];
            graph->verticies[i*d_WIDTH +j].neighbors[4] = &graph->verticies[(i)*d_WIDTH +j+1];
            graph->verticies[i*d_WIDTH +j].neighbors[5] = &graph->verticies[(i+1)*d_WIDTH +j-1];
            graph->verticies[i*d_WIDTH +j].neighbors[6] = &graph->verticies[(i+1)*d_WIDTH +j];
            graph->verticies[i*d_WIDTH +j].neighbors[7] = &graph->verticies[(i+1)*d_WIDTH +j+1];
        }
    }
    graph->source = &graph->verticies[source->y * d_WIDTH + source->x];
    return graph;
}

int w_unit_weight(int weight, w_unit_t *w_unit){

    if(w_unit->hardness==0) return weight + WEIGHT_1;
    else if(w_unit->hardness>0 && w_unit->hardness<85) return weight + WEIGHT_2;
    else if(w_unit->hardness>=85 && w_unit->hardness<171) return weight + WEIGHT_3;
    else if(w_unit->hardness>=171 && w_unit->hardness<255) return weight + WEIGHT_4;
    else return -1;
}

void update_adjacent(heap_t *heap, vertex_t *source){

/*
 * Update each neighbor of the source vertex, if the new weight is less than the current
 * weight, add it to the heap. Assumes heap initially contains only source.
 */
    int temp;
    for (int i = 0; i < 8; ++i) {
        temp = w_unit_weight(source->weight, source->neighbors[i]->w_unit);
        if(temp<source->neighbors[i]->weight && !source->neighbors[i]->visited) {
            if(!source->neighbors[i]->queued) {
                source->neighbors[i]->weight = temp;
                source->neighbors[i]->prev = source;
                source->neighbors[i]->queued = TRUE;
                add_with_priority(heap, source->neighbors[i], source->neighbors[i]->weight);
            }
            else{
                //TODO add code for changing the priority after fixing heap issues.
            }
        }
    }

}