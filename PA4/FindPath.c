/**Mengdi Wei
  *ID: 1538074
  *PA4
  *This file can read the input of a file. Read the and print data in a graph
  * then print the shortest path between two vertex
  */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]) {
   int n = 0;
   int number1;
   int number2;
   int start;
   int end;
   FILE *in, *out;
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   fscanf(in, "%d", &n);
   Graph graph = NULL;
   graph = newGraph(n);
   //read the data from the input
   while (fgetc(in) != EOF) {
      fscanf(in, "%d", &number1);
      fscanf(in, "%d", &number2);
      if (number1 == 0){
      	  if(number2==0)
         break;
      }
      addEdge(graph, number1, number2);
   }
   //print the graph
   printGraph(out, graph);
   fprintf(out, "\n");
   
   while (fgetc(in) != EOF) {
      fscanf(in, "%d", &start);
      fscanf(in, "%d", &end);
      if (start == 0){
      	if (end==0)
         break;
      }
      List list = newList();
      BFS(graph, start);
      getPath(list, graph, end);
      if (getDist(graph, end) != INF){
         fprintf(out, "The distance from %d to %d is %d\n", start,end, length(list) - 1);
         fprintf(out, "A shortest %d-%d path is: ", start, end);
         printList(out, list);
         fprintf(out, "\n\n");
      }
      else{
         fprintf(out, "The distance from %d to %d is infinity\n", start, end);
         fprintf(out, "No %d-%d path exists\n", start, end);
         fprintf(out, "\n");
      }
      freeList(&list);
   }
   //free and close
   freeGraph(&graph);
   
   fclose(in);
   fclose(out);
   
   return(0);
}