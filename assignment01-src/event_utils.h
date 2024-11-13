typedef enum {
  B1_PRESSED,
  B2_PRESSED,
  B3_PRESSED,
  B4_PRESSED,
  NONE
} events;

typedef struct queue_node {
  struct queue_node* next;
  events elem;
} queue_node;

/*
* Initialises the event queue.
*/
void queue_init();

/*
* Adds an event to the queue
*/
void add_event(events event);

/*
* Returns an event from the queue
*/
events get_event();

/*
* Clears the event queue.
*/
void clear_queue();