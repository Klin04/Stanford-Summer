//This program is made by Kaijun Lin.
//It is the main part of the trailblazer program.
//It consists of several different algorithms that contribute to the result.

#include "trailblazer.h"
#include "pqueue.h"
#include "queue.h"
using namespace std;

void depthFirstSearchHelper(BasicGraph &graph, Vertex *start, Vertex *end, Vector<Vertex *> &path);

//Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end);
//This function takes in a graph, a starting vertex and an end vertex.
//It is utilizing DFS to find out the way between the two points.
//It will return a vector that stores the path it has passed.
//DFS:Explore as deep as possible in one direction;
//if one way is not successful, that try another.
//It will stop as soon as it finds a path.
Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end){
    graph.resetData();//delete any flag set in the previous function calls
    Vector<Vertex*> path;
    depthFirstSearchHelper(graph, start, end, path);//helper function
    if(path.size() != 0 && path[path.size() - 1] != end){//case that there is no path(everywhere gray)
        path.remove(path.size() - 1);//remove the start one to let the vector be empty
        start->setColor(GRAY);//start becomes gray
    }
    return path;
}

//Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end);
//This function implements the BFS algorithm.
//It takes in a graph by reference, as well as a vertex to start and a vertex to end.
//BFS:go through every direction of the current level, then go to the next level.
//It will returns a vector that contains the path made up with all vertices passed.
Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();//delete any flag set in the previous function calls
    Vector<Vertex*> path;
    if(start == end){//case 1
        path.add(start);//mark
        start->visited = true;
        start->setColor(GREEN);
        return path;
    }
    Queue<Vertex*> toVisit;//case 2
    toVisit.enqueue(start);
    while(!toVisit.isEmpty()){
        Vertex* curr = toVisit.dequeue();
        curr->visited = true;
        curr->setColor(GREEN);
        for(Vertex* neighbor : graph.getNeighbors(curr)){//go through every neighbor
            if(neighbor == end){//end the function as soon as we find a path(no need to explore anymore)
                neighbor->visited = true;//mark
                neighbor->setColor(GREEN);
                neighbor->previous = curr;
                break;
            }
            else{
                if(neighbor->visited == false && neighbor->getColor() != YELLOW){//no need to explore neighbor already in the queue
                    toVisit.enqueue(neighbor);//mark
                    neighbor->setColor(YELLOW);
                    neighbor->previous = curr;
                }
            }
        }
        if(end->previous != NULL){//find the end, end the while loop
            break;
        }
    }
    if(end->previous != NULL){//trace the previous pointer and find out the whole path
        Vertex* temp = end;
        while(temp != NULL){
            path.insert(0,temp);
            temp = temp->previous;
        }
    }
    return path;
}

//Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end);
//This function takes in a graph by reference and two vertices "start" and "end".
//It returns a vector that contains the path consisting of vertices.
//It implements the dijkstras algorithm.
//Dijkstras:explore every direction and find the least cost one, the go to the next level
//(according to current cost, find out the least cost way.)
Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();//delete any flag set in the previous function calls
    Vector<Vertex*> path;
    if(start == end){//case 1
        path.add(start);
        start->visited = true;//mark
        start->setColor(GREEN);
        return path;
    }
    PriorityQueue<Vertex*> visit;//case 2
    visit.enqueue(start, start->cost);
    while(!visit.isEmpty()){
        Vertex* curr = visit.dequeue();//mark
        curr->visited = true;
        curr->setColor(GREEN);
        if(curr == end){//end the while loop if we find the end
            break;      //not the same as the BFS since we cannot guarantee
        }               //that the earliest found path is the cheapest one so we must go through every neighbor
        for(Vertex* neighbor : graph.getNeighbors(curr)){
            if(neighbor->visited == false){
                if(neighbor->cost == 0){//not visited and not enqueued
                    neighbor->cost = curr->cost + graph.getEdge(curr, neighbor)->cost;//cost
                    visit.enqueue(neighbor, neighbor->cost);//enqueue
                    neighbor->setColor(YELLOW);//mark
                    neighbor->previous = curr;
                }
                else{//already in the priority queue
                    if(neighbor->cost > curr->cost + graph.getEdge(curr, neighbor)->cost){//compare cost
                        neighbor->cost = curr->cost + graph.getEdge(curr, neighbor)->cost;//assign new cost
                        visit.changePriority(neighbor, neighbor->cost);//change priority
                        neighbor->previous = curr;
                    }
                }
            }
        }
    }
    if(end->previous != NULL){//find the path, then add the path to the vector through tracing previous pointer
        Vertex* trace = end;
        while(trace != NULL){
            path.insert(0, trace);//the end vertex comes out first
            trace = trace->previous;
        }
    }
    return path;
}

//Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end);
//This function implements the A* algorithm.
//It receives a graph by reference and two vertices as start and end.
//It returns the vertex that contains the path.
//A*:go through every direction and find the least cost one, then go to the next level
//(according to current cost and future heuristic approximation, find out the least cost way)
Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();//delete any flag set in the previous function calls
    Vector<Vertex*> path;
    if(start == end){//case 1
        path.add(start);//add
        start->visited = true;//mark
        start->setColor(GREEN);
        return path;
    }
    PriorityQueue<Vertex*> toVisit;//case 2
    toVisit.enqueue(start, heuristicFunction(start, end));
    while(!toVisit.isEmpty()){
        Vertex* curr = toVisit.dequeue();
        curr->setColor(GREEN);//mark
        curr->visited = true;
        if(curr == end){//find the path(not the same as BFS)
            break;      //reason the same as dijkstras
        }
        for(Vertex* neighbor : graph.getNeighbors(curr)){//go through every neighbor
            if(neighbor->visited == false){
                if(neighbor->cost == 0){//not visited and not enqueued
                    neighbor->cost = curr->cost + graph.getEdge(curr, neighbor)->cost;//cost of the vertex
                    neighbor->setColor(YELLOW);//mark
                    toVisit.enqueue(neighbor, neighbor->cost + heuristicFunction(neighbor, end));//priority is the cost of the whole path
                    neighbor->previous = curr;
                    //different values(the one acting as priority and the cost field of a vertex)
                }
                else{
                    if(neighbor->cost > curr->cost + graph.getEdge(curr, neighbor)->cost){//compare cost
                        neighbor->cost = curr->cost + graph.getEdge(curr, neighbor)->cost;//assign
                        toVisit.changePriority(neighbor, neighbor->cost + heuristicFunction(neighbor, end));//enqueue
                        neighbor->previous = curr;
                    }
                }
            }
        }
    }
    if(end->visited == true){//find the path, trace the previous pointer to add the path into the vector
        Vertex* trace = end;
        while(trace != NULL){
            path.insert(0, trace);//the end vertex comes out first
            trace = trace->previous;
        }
    }
    return path;
}

//Set<Edge*> kruskal(BasicGraph& graph);
//This function randomly generates maps and mazes.
//It is utilizing the kruskal's algorithm, which will produce the least cost map/maze.
//It takes in a graph and returns a set that contains the edges added.
Set<Edge*> kruskal(BasicGraph& graph) {
    graph.resetData();//delete any flag set in the previous function calls
    Set<Edge*> mst;
    Map<Vertex*, Set<Vertex*>* > clusters;//clusters that store the vertices that
    PriorityQueue<Edge*> pqueue;
    for(Edge* edge : graph.getEdgeSet()){//enqueue every edge in the maze
        pqueue.enqueue(edge,edge->cost);
    }
    for(Vertex* each : graph.getVertexSet()){//put every vertex into its own clusters
        clusters[each] = new Set<Vertex*>();
        clusters[each]->add(each);
    }
    while(!pqueue.isEmpty()){
        Edge* now = pqueue.dequeue();//dequeue
        if(!((*clusters[now->start]).contains(now->finish))){
            //clusters[now->start]->addAll(*clusters[now->finish]);
            for(Vertex* each : *clusters[now->finish]){//loop over each element in finish set
                if(clusters[each] != clusters[now->start]){
                    clusters[now->start]->add(each);//add the elements to the start set one by one
                    if(each != now->finish){//cannot modify "finish" in the enhanced for loop
                        clusters[each] = clusters[now->start];
                    }
                }
            }
        Set<Vertex*>* temp = clusters[now->finish];//a pointer for deleting the set
        clusters[now->finish] = clusters[now->start];//modify "finish"
        delete temp;//release allocated memory
        mst.add(now);
        }
    }
    if(clusters[clusters.keys().get(0)]->size() != graph.getVertexSet().size()){
        cout << "no path" << endl;
        mst.clear();//at the end, all keys should go to the same set that contains all vertices
    }               //if not, there should be somewhere not connected, so we return an empty set
    int size = clusters.keys().size();
    Set<Vertex*>* temp = clusters[clusters.keys().get(size - 1)];//only need to delete once
    for(int i = 0;i < size;i++){
        clusters[clusters.keys().get(i)] = NULL;//Set every pointer to NULL
    }
    delete temp;//delete the only left set to release memory
    return mst;
}

//void depthFirstSearchHelper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path);
//This function takes in a graph by reference, a start vertex, an end vertex and a vector storing path.
//It does not return any value.
//It modifies the vector.
void depthFirstSearchHelper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path){
    if(start == end){//base case
        path.add(start);
        start->visited = true;//mark
        start->setColor(GREEN);
        return;
    }
    else{//recursive case
        path.add(start);//choose
        start->visited = true;//mark
        start->setColor(GREEN);
        for(Vertex* neighbor : graph.getNeighbors(start)){
            if(neighbor->visited == false){//do not go to the same vertex!
                depthFirstSearchHelper(graph, neighbor, end, path);//explore
                if(path[path.size() - 1] == end){//exam
                    return;
                }
                else{//unchoose
                    path[path.size() - 1]->setColor(GRAY);//backtracking
                    path.remove(path.size() - 1);
                }
            }
        }
    }
}
