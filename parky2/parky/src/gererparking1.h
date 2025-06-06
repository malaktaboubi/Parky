#ifndef GERERPARKING1_H_INCLUDED
#define GERERPARKING1_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>


typedef struct agent 
{
	char nom[10];
	char prenom[10];
	char id_agent[10];
} agent;

typedef struct full_agent {
    char nom[50];
    char prenom[50];
    char id_agent [10];
    int telephone;
    char email[50];
    char id_p[10];
    int etat;
    char evaluation[20];
} full_agent;

typedef struct park
{
	char id_p[50];
	char nomp[20];
	char gouv[50];
	char munic[50];
	int nb_p_t;
	int nb_p_d;
	float tarif;
	agent agent;
}park;


typedef struct munic
{
	char gouv[50];
	char mun[50];
	
}munic;


typedef struct {
    int count;           // Number of matching parkings
    park *list;          // Pointer to an array of park structures
} SearchResult;



int modifier_agent( char * filename, char ID[], full_agent nouv );
int ajouter(char * filename, park nouv );
int modifier( char *filename,char id[], park nouv );
int supprimer(const char *filename, char id[] );
park recherche(char *filename, char id[]);
full_agent recherche_agent(char * filename, char id[] );
full_agent recherche_agent_all(char * filename, char id[] );
int affecter_agent(char* filename1 , char* filename2, char idagentpouraffecter[], char idp[]);

char **municipalite(const char *filename, const char *gouv);
void free_municipalite_list(char **list);
char **filter_agents_by_etat(const char *filename);

char *process_string(const char *str);
void replace_underscore_with_space(char *str);
void float_to_string(float value, char *buffer, size_t buffer_size);
int is_valid_float(const char *str);
int is_id_unique(const char *id, const char *filename);

SearchResult recherche_nomp(const char *filename, const char *nom);
void clear_and_display_parkings(GtkTreeView *treeview, park *list, int count);
void initialize_treeview_columns(GtkTreeView *treeview);
gboolean populate_treeview_from_file(GtkTreeView *treeview, const char *filename);
void clear_and_display_single_parking(GtkTreeView *treeview, park p);

char random_char();

char *generate_unique_id(const char *str1, const char *str2, const char *str3, const char *filename);
void add_to_first(char ***liste, const char *new_element);
char **filter_parkings_by_id(const char *filename);
#endif 
