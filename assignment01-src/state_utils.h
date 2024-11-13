typedef enum {
  NEW_GAME,
  DEEP_SLEEPING,
  GAME_START,
  ROUND,
  ROUND_OVER,
  SHOW_SCORE,
  GAME_OVER
} states;

/*
* implements the transition to the state it has as a parameter.
*/
long switch_state(states new_state);

/*
* Checks the result of a round
*/
bool check_round();