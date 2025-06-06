#ifndef GERERAGENT_H_INCLUDED
#define GERERAGENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "gererparking1.h"


typedef struct {
    int count;           // Number of matching parkings
    full_agent *list;          // Pointer to an array of park structures
} SearchResult2;



int modifier_agent( char * filename, char ID[], full_agent nouv );
int ajouter_agent(char * filename, full_agent nouv );
int supprimer_agent(const char *filename, char id[] );
full_agent recherche_agent(char * filename, char id[] );
full_agent recherche_agent_all(char * filename, char id[] );

//void free_municipalite_list(char **list);
char **filter_parkings_with_no_agent(const char *filename);
void set_combobox_valueagent(GtkComboBox *combobox, const char *evaluation);

void initialize_treeview_columns1(GtkTreeView *treeview);
gboolean populate_treeview_with_agents(GtkTreeView *treeview, const char *filename);
gboolean populate_treeview_with_allagents(GtkTreeView *treeview, const char *filename);
void clear_and_display_single_agent(GtkTreeView *treeview, full_agent agent);
SearchResult2 recherche_noma(const char *filename, const char *nom);
void clear_and_display_parkings(GtkTreeView *treeview, park *list, int count);
/*gboolean populate_treeview_from_file(GtkTreeView *treeview, const char *filename);


char random_char();

char *generate_unique_id(const char *str1, const char *str2, const char *str3, const char *filename);
void add_to_first(char ***liste, const char *new_element);
char **filter_parkings_by_id(const char *filename);*/


#endif 
