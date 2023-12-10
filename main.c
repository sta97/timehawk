// references
// https://www.geeksforgeeks.org/socket-programming-cc/

#include <sys/socket.h>
#include <stdio.h>

#define PORT 8080
#define MAX_CLIENTS 64

typedef struct {
    int socket;
    int age;
} client_t;

typedef struct {
    client_t *clients;
    int serverSocket;
} state_t;

void createState()
{
    state_t *state = malloc(sizeof(state_t));
    state->serverSocket = -1;
    state->clients = malloc(sizeof(client_t)*MAX_CLIENTS);
    
    for(int i = 0; i < MAX_CLIENTS; ++i)
        state->clients.socket = -1;
    
    return state;
}

void setupServer(state_t *state)
{
    // get server socket
    state->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(state->serverSocket < 0)
    {
        printf("error making socket\n");
        return 0;
    }
    
    int opt = 1;
    
    // allow address and port reuse for quick server restart
    if(setsockopt(state->serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        printf("setting address and port reuse failed\n");
        return 0;
    }
    
    // make non blocking since we're single threaded
    if(fcntl(state->serverSocket, F_SETFL, O_NONBLOCK) < 0)
    {
        printf("setting non blocking failed\n");
        return 0;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // bind the server socket
    if(bind(state->serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        printf("binding port failed\n");
        return 0;
    }
    
    // begin listening
    if(listen(state->serverSocket, NUM_CLIENTS) < 0)
    {
        printf("port listening failed\n");
        return 0;
    }
}

void mainLoop(state_t *state)
{
    char freePort = -1; // next free client
    
    // read and reply to every client
    for(int i = 0; i < NUM_CLIENTS; ++i)
    {
        // track next free client
        if(clients[i] < 0)
        {
            freePort = i;
            continue;
        }
        
        // read
        
        // reply
    }
    
    // process new connections
    int c = accept(s, (struct sockaddr*)&address, &addrlen);
    // on new connection, add to list
    if(c >= 0)
    {
        // if no free port, kick off oldest
        if(freePort < 0)
        {
            
        }
        
        clients[freePort] = c;
    }
    // close ports if socket failure
    if(c < 0 && !(errno == EAGAIN || errno == EWOULDBLOCK))
    {
        
    }
}

void shutdown(state_t *state)
{
    // close sockets
    for(int i = 0; i < MAX_CLIENTS; ++i)
        close(state->clients[i].socket);
    
    close(state->serverSocket);
    
    // free memory
    free(state->clients);
    free(state);
}

int main()
{
    state_t *state = createState();
    
    setupServer(state);
    
    if(state->serverSocket < 0)
        printf("setup failure. shutting down.\n");
    else
    {
        printf("starting server loop\n");
        
        while(mainLoop(state))
            //sleep 20ms
    }
    
    shutdown(state);
    
    return 0;
}
