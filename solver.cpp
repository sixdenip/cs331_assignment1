#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <string>

typedef std::pair<std::tuple<int, int, bool>, std::tuple<int, int, bool>> Node_State; //LEFT AND RIGHT SHORES IN THAT ORDER
typedef std::tuple<int, int, bool> Shore; //CHICKENS, WOLVES AND BOAT IN THAT ORDER
typedef struct Node Node;

//game state is a pair of tuples, where each tuple is the number of chickens, wolves and if the boat is on that shore or not. a pair: 1 tuple for each shore.

struct Node{
    Node* parent;
    std::vector<Node*> children;
    Node_State state; 
};

std::vector<int> read_file(std::string file){
    std::vector<int> values;
    std::ifstream infile(file.c_str());
    int a, b, c;
    char d,e;
    while (infile >> a >> d >> b >> e >> c && d == e && e == ',')
    {
        values.push_back(a);
        values.push_back(b);
        values.push_back(c);
    }
    return values;
}

Node* create_Node(Node* origin, Node_State* state){

    Node* node = new Node{origin, std::vector<Node*>(), *state};
    return node;
}

void insert_node(Node* origin, Node* child){
    (origin->children).push_back(child);
}

int get_num_chickens(Shore shore){
    return std::get<0>(shore);
}

int get_num_wolves(Shore shore){
    return std::get<1>(shore);
}

std::string toString(Node_State* state){
    return std::to_string(std::get<0>(state->first)) + std::to_string(std::get<1>(state->first)) + std::to_string(std::get<2>(state->first)) 
    + std::to_string(std::get<0>(state->second)) + std::to_string(std::get<1>(state->second)) + std::to_string(std::get<2>(state->second));
}

bool is_valid(Node_State* state){

    Shore leftShore = state->first;
    Shore rightShore = state->second;
    if(get_num_chickens(leftShore) < 0 || get_num_chickens(rightShore) < 0 || get_num_wolves(leftShore) < 0 || get_num_wolves(rightShore) < 0)
        return false;
    else if((get_num_chickens(leftShore) < get_num_wolves(leftShore) && (get_num_chickens(leftShore) != 0)) || 
    (get_num_chickens(rightShore) < get_num_wolves(rightShore) && (get_num_chickens(rightShore) != 0)))
        return false;
    else
        return true;
}

bool already_visited(Node_State* state, std::unordered_set<std::string>* visited){
    if(visited->find(toString(state)) == visited->end())
        return false;
    else
        return true;
}

bool has_boat(Shore shore){
    return std::get<2>(shore);
}

void print_state(Node_State* state){
    std::cout << "Left bank: " << std::get<0>(state->first) << " " << std::get<1>(state->first) << " " << std::get<2>(state->first) << "\n"; 
    std::cout << "Right bank: " << std::get<0>(state->second) << " " << std::get<1>(state->second) << " " << std::get<2>(state->second) << "\n"; 
}

//moves n chickens. returns the new state.
Node_State move_chickens(Node_State* state, int n){

    if(std::get<2>(state->first) == 1){
        std::get<2>(state->first) = 0;
        std::get<2>(state->second) = 1;
        std::get<0>(state->first) -= n;
        std::get<0>(state->second) += n;
    }
    else{
        std::get<2>(state->first) = 1;
        std::get<2>(state->second) = 0;
        std::get<0>(state->second) -= n;
        std::get<0>(state->first) += n;
    }

    return *state;
}

//moves n wolves. returns the new state.
Node_State move_wolves(Node_State* state, int n){

    if(std::get<2>(state->first) == 1){
        std::get<2>(state->first) = 0;
        std::get<2>(state->second) = 1;
        std::get<1>(state->first) -= n;
        std::get<1>(state->second) += n;
    }
    else{
        std::get<2>(state->first) = 1;
        std::get<2>(state->second) = 0;
        std::get<1>(state->second) -= n;
        std::get<1>(state->first) += n;
    }

    return *state;
}
//moves 1 chicken and 1 wolf
Node_State move_chicken_and_wolf(Node_State* state){

    if(std::get<2>(state->first) == 1){
        std::get<2>(state->first) = 0;
        std::get<2>(state->second) = 1;

        std::get<0>(state->first) -= 1;
        std::get<0>(state->second) += 1;

        std::get<1>(state->first) -= 1;
        std::get<1>(state->second) += 1;
    }
    else{
        std::get<2>(state->first) = 1;
        std::get<2>(state->second) = 0;

        std::get<0>(state->second) -= 1;
        std::get<0>(state->first) += 1;

        std::get<1>(state->second) -= 1;
        std::get<1>(state->first) += 1;
    }

    return *state;
}


/*
THIS IS THE MAIN FUNCTION THAT EXPANDS ANY GIVEN NODE. AT MOST IT WILL ADD
5 CHILDREN TO THE CURRENT NODE (Node* node). There is an isValid method
that checks if a move is valid before adding it to the vector of children 
for the current parent node.
*/
//takes a node and gives it children that are valid (at most 5 children). children are NODES.Nodes contain a parent, children, and state.
void expand_node(Node* node, std::unordered_set<std::string>* visited){
    Node_State currentState = node->state;
    std::vector<Node*> children();
    Shore currentShore; //tuple of int, int and bool (typedef'd)
    //add the state as a string to the unordered set
    visited->insert(toString(&currentState));
    /*std::unordered_set<std::string>::iterator itr;

    for (itr = visited->begin(); itr != visited->end(); itr++)
        std::cout << (*itr) << std::endl;*/
    //determine where the boat is
    if(std::get<2>(currentState.first) == 1)
        currentShore = currentState.first;
    else
        currentShore = currentState.second;
    
    //start generating possible states and checking for validity before inserting.

    //take 1 chicken
    Node_State state1 = move_chickens(&currentState, 1);
    if(is_valid(&state1) && !already_visited(&state1, visited))
        node->children.push_back(create_Node(node, &state1));

    currentState = node->state; //reset state to current
    //take 2 chickens
    Node_State state2 = move_chickens(&currentState, 2);
    if(is_valid(&state2) && !already_visited(&state2, visited))
        node->children.push_back(create_Node(node, &state2));

    currentState = node->state;
    //take 1 wolf and 1 chicken
    Node_State state3 = move_chicken_and_wolf(&currentState);
    if(is_valid(&state3) && !already_visited(&state3, visited))
        node->children.push_back(create_Node(node, &state3));
    
    currentState = node->state;
    //take 1 wolf
    Node_State state4 = move_wolves(&currentState, 1);
    if(is_valid(&state4) && !already_visited(&state4, visited))
        node->children.push_back(create_Node(node, &state4));
    
    currentState = node->state;
    //take 2 wolves
    Node_State state5 = move_wolves(&currentState, 2);
    if(is_valid(&state5) && !already_visited(&state5, visited))
        node->children.push_back(create_Node(node, &state5));
    
    currentState = node->state;
    }

bool is_win_state(Node_State* state){
    //if there's nothing left on the right shore, then win
    if(get_num_wolves(state->second) == 0 && get_num_chickens(state->second) == 0)
        return true;
    else
        return false; 
}

//recursively print out the win path (starting from winning node and printing the parents of each of parent recursively)
void print_win_path(Node* node){
    if(node->parent != nullptr){
        print_win_path(node->parent);
    }
    print_state(&(node->state));
}
//TODO: implement this lol
void bfs(Node* root){
    std::unordered_set<std::string> visited; //initialize hash table
    std::queue<Node*> queue; //initialize queue
    if(is_win_state(&(root->state))){
        std::cout << "win\n";
        return;
    }
    
    expand_node(root, &visited);
    for(int i = 0; i < root->children.size(); i++){
        queue.push(root->children.at(i));
    }

    while(queue.size() != 0){
        print_state(&(queue.front()->state));

        if(is_win_state(&(queue.front()->state))){
            std::cout << "win\n";
            std::cout << "WIN PATH:\n";
            Node* winNode = queue.front();
            /*while(winNode != nullptr){
                std::cout << "-------------\n";
                print_state(&(winNode->state));
                winNode = winNode->parent;
            }*/
            print_win_path(winNode);
            return;
        }
        expand_node(queue.front(), &visited);
        for(int i = 0; i < queue.front()->children.size(); i++){
            queue.push(queue.front()->children.at(i));
        }
        queue.pop();
    }
    std::cout << "lose\n";

}
/*
    for(int i = 0; i < root->children.size(); i++){
    print_state(&(root->children.at(i)->state));
    }
    
    Node* newRoot = root->children.at(0);
    expand_node(newRoot, &visited);

    std::cout << "new root states:\n";
    for(int i = 0; i < newRoot->children.size(); i++){
        print_state(&(newRoot->children.at(i)->state));
    }
*/


int main(int argc, char* argv[]) {

    if (argc < 5) {
        std::cout << "Usage : < initial state file > < goal state file > < mode > < output file > " << std::endl;
        return 0;
    }
    std::vector<int> values = read_file(argv[1]);
    /*for(int i = 0; i < values.size(); i++){
        cout << values.at(i) << "\n";
    }*/
    Shore left_bank = std::make_tuple(values.at(0), values.at(1), !!values.at(2));
    Shore right_bank = std::make_tuple(values.at(3), values.at(4), !!values.at(5));
    
    Node_State initial_state; 
    initial_state.first = left_bank;
    initial_state.second = right_bank;

    //std::unordered_set<std::string> visited;

    Node* root = new Node{nullptr, std::vector<Node*>(), initial_state};
    //expand_node(root, &visited);
    bfs(root);


    //for different modes
    std::string mode = argv[3];
    if(mode.compare("bfs") == 0){
        //do BFS
    }else if(mode.compare("dfs") == 0){
        //do DFS
    }else if(mode.compare("iddfs") == 0){
        //do IDDFS
    }else if(mode.compare("astar") == 0){
        //DO ASTAR
    }
}
