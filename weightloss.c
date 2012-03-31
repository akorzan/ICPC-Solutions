#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define STRING_LENGTH 31

struct team {
  char* name;
  int totalIni;
  int totalFin;
  float percentLost;
};

struct team* findTeam(char* teamName, struct team** teams, int numberOfTeams) {
  struct team* foundTeam;
  int i;
  
  for (i = 0; i < numberOfTeams; i++) {
    if(strcmp(teams[i]->name, teamName) == 0) {
      return teams[i];
    }
  }
  return NULL;
}

struct team* findWinner(struct team** teams, int numberOfTeams) {
  int i;
  struct team* winner = teams[0];

  for (i = 1; i < numberOfTeams; i++) {
    if(winner->percentLost < teams[i]->percentLost) {
      winner = teams[i];
    } else if (teams[i]->percentLost == winner->percentLost) {
      if (strcmp(teams[i]->name, winner->name) > 0) {
	winner = teams[i];
      }
    }
  }
  
  return winner;
}

int main() {
  // This array will hold pointers to each team.
  struct team** teams;
  struct team* foundTeam;
  
  // Temporary Variables for holding input
  double ini;
  double fin;
  char* teamName = (char*) malloc(sizeof(char) * STRING_LENGTH);

  // String for storing the useless Name of the Person
  char* crap = (char*) malloc(sizeof(char) * STRING_LENGTH);
  
  // A variable for keeping track how teams there are.
  int numberOfTeams;
  
  int input = -1;
  int i;

  while (input != 0) {
    numberOfTeams = 0;
    scanf("%d\n", &input);
    
    // Input = N
    if (input != 0) {
      teams = (struct team**) malloc(sizeof(struct team*) * input);
      
      // Two players for each team. 2N
      for (i = 0; i < 2 * input; i++) {
	// Store input into temporary variables.
	scanf("%s %s %lf %lf\n", crap, teamName, &ini, &fin);
	
	foundTeam = findTeam(teamName, teams, numberOfTeams);
	if (foundTeam == NULL) {
	  // Allocate a team and store its pointer in teams.
	  teams[numberOfTeams] = (struct team*) malloc(sizeof(struct team));
	  // Allocate a team name and sotre its pointer in the new struct.
	  teams[numberOfTeams]->name = (char*) malloc(sizeof(char) * STRING_LENGTH);
	  
	  strcpy(teams[numberOfTeams]->name, teamName);
	  teams[numberOfTeams]->totalIni = (int) (ini * 10.0);
	  teams[numberOfTeams]->totalFin = (int) (fin * 10.0);
	  teams[numberOfTeams]->percentLost =  ((double) ini - (double) fin) / (double) ini;

	  numberOfTeams++;
	} else {
	  foundTeam->totalIni += (int) (ini * 10.0);
	  foundTeam->totalFin += (int) (fin * 10.0);
	  foundTeam->percentLost =  ((double) foundTeam->totalIni - (double) foundTeam->totalFin) / (double) foundTeam->totalIni;
	}
      }
      /*
      // Print Loop
      for (i = 0; i < numberOfTeams; i++) {
      printf("%s - Inital: %d  Final: %d  Percent: %lf\n", teams[i]->name, teams[i]->totalIni, teams[i]->totalFin, teams[i]->percentLost);
      } 
      */
      
      foundTeam = findWinner(teams, numberOfTeams);
      printf("%s %2.1lf%%\n", foundTeam->name, (foundTeam->percentLost * 100));
      
      for(i = 0; i < numberOfTeams - 1; i++) {
	free(teams[i]->name);
	free(teams[i]);
      }
      free(teams);
    }
  }
    
  return 0;
}
