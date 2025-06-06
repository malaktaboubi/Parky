#include "gereragent.h"
#include "gererparking1.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <ctype.h>


int modifier_agent( char * filename, char ID[], full_agent nouv )
{
    int tr=0;
    full_agent a;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %d %s %s %d %s\n", a.nom, a.prenom ,a.id_agent, &(a.telephone), a.email, a.id_p, &(a.etat), a.evaluation)!=EOF)
        {
            if(strcmp(a.id_agent, ID) == 0)
            {
                fprintf(f2,"%s %s %s %d %s %s %d %s\n", nouv.nom, nouv.prenom, nouv.id_agent, nouv.telephone, nouv.email, nouv.id_p, nouv.etat, nouv.evaluation);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %s %d %s %s %d %s\n", a.nom, a.prenom ,a.id_agent, a.telephone, a.email, a.id_p, a.etat, a.evaluation);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}



int ajouter_agent(char * filename, full_agent nouv )
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %d %s %s %d %s\n", nouv.nom, nouv.prenom, nouv.id_agent, nouv.telephone, nouv.email, nouv.id_p, nouv.etat, nouv.evaluation);
        fclose(f);
        return 1;
    }
    else return 0;
}







int supprimer_agent(const char * filename, char id[] )
{
    int tr=0;
    full_agent a;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {while(fscanf(f,"%s %s %s %d %s %s %d %s\n", a.nom, a.prenom ,a.id_agent, &(a.telephone), a.email, a.id_p, &(a.etat), a.evaluation)!=EOF) 
    {
        if(strcmp(a.id_agent, id) == 0)
                tr=1;
            else
                fprintf(f2,"%s %s %s %d %s %s %d %s\n", a.nom, a.prenom ,a.id_agent, a.telephone, a.email, a.id_p, a.etat, a.evaluation);
    }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}





full_agent recherche_agent(char * filename, char id[] )
{
    full_agent a;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while((tr==0) && (fscanf(f,"%s %s %s %d %s %s %d %s\n", a.nom, a.prenom ,a.id_agent, &(a.telephone), a.email, a.id_p, &(a.etat), a.evaluation)!=EOF))
        {
            if((strcmp(a.id_agent, id) == 0) && (a.etat==0))
                tr=1;
        }
            fclose(f);
    }

    if (tr == 0) 
        strcpy(a.id_agent, "-1"); // Use a string "-1" to indicate not found not 
    return a;
}



full_agent recherche_agent_all(char * filename, char id[] )
{
    full_agent a;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while((tr==0) && (fscanf(f,"%s %s %s %d %s %s %d %s\n", a.nom, a.prenom ,a.id_agent, &(a.telephone), a.email, a.id_p, &(a.etat), a.evaluation)!=EOF))
        {
            if((strcmp(a.id_agent, id) == 0))
                tr=1;
        }
            fclose(f);
    }

    if (tr == 0) 
        strcpy(a.id_agent, "-1"); // Use a string "-1" to indicate not found not 
    return a;
}



//8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888



// Helper function to free the dynamically allocated list
/*void free_municipalite_list(char **list) {
    if (list == NULL) return;
    for (int i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}*/


char **filter_parkings_with_no_agent(const char *filename) {
    char **list = NULL;  // Dynamic array of strings
    char line[256];
    int count = 0;       // Number of matched parkings

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    while (fgets(line, sizeof(line), f)) {
        park parking;

        // Parse the line into a `park` structure
        if (sscanf(line, "%s %s %s %s %d %d %f %s %s %s",
                   parking.id_p,
                   parking.nomp,
                   parking.gouv,
                   parking.munic,
                   &parking.nb_p_t,
                   &parking.nb_p_d,
                   &parking.tarif,
                   parking.agent.id_agent,
                   parking.agent.nom,
                   parking.agent.prenom) == 10) {
            // Check if `id_agent` is "0" (indicating no agent assigned)
            if (strcmp(parking.agent.id_agent, "0") == 0) {
                // Add the parking ID to the list
                list = realloc(list, (count + 2) * sizeof(char *)); // +1 for new item, +1 for NULL
                if (list == NULL) {
                    printf("Memory allocation failed!\n");
                    fclose(f);
                    return NULL;
                }
                list[count] = strdup(parking.id_p);  // Duplicate the parking ID
                count++;
            }
        }
    }
    fclose(f);

    // Add NULL to mark the end of the list
    if (list != NULL) {
        list[count] = NULL;
    }

    return list;
}




void set_combobox_valueagent(GtkComboBox *combobox, const char *evaluation) {
    GtkTreeModel *model = gtk_combo_box_get_model(combobox);
    GtkTreeIter iter;
    gboolean valid;
    int index = 0;

    // Iterate through the combobox items to find the matching text
    valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        gchar *item_text;
        gtk_tree_model_get(model, &iter, 0, &item_text, -1);

        if (g_strcmp0(item_text, evaluation) == 0) {
            gtk_combo_box_set_active(combobox, index);  // Set the active item
            g_free(item_text);
            return;
        }

        g_free(item_text);
        valid = gtk_tree_model_iter_next(model, &iter);
        index++;
    }

    g_print("Warning: Evaluation '%s' not found in combobox.\n", evaluation);
}



SearchResult2 recherche_noma(const char *filename, const char *nom) {
    FILE *f = fopen(filename, "r");
    SearchResult2 result;
    result.count = 0;     // Initialize count to 0
    result.list = NULL;   // Initialize list to NULL

    if (f != NULL) {
        full_agent temp;
        int size = 10; // Initial capacity for the list
        result.list = malloc(size * sizeof(full_agent)); // Allocate initial memory

        if (result.list == NULL) { // Check for allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            fclose(f);
            return result;
        }

        // Scan each line of the file
        while (fscanf(f,"%s %s %s %d %s %s %d %s\n", temp.nom, temp.prenom ,temp.id_agent, &(temp.telephone), temp.email, temp.id_p, &(temp.etat), temp.evaluation) != EOF) {
            if ((strcmp(temp.nom, nom) == 0) || (strcmp(temp.prenom, nom) == 0)) { // Compare names
                if (result.count >= size) {
                    size *= 2;
                    park *temp_list = realloc(result.list, size * sizeof(full_agent));
                    if (temp_list == NULL) { // Check for reallocation failure
                        fprintf(stderr, "Memory reallocation failed\n");
                        free(result.list);
                        fclose(f);
                        result.count = 0;
                        result.list = NULL;
                        return result;
                    }
                    result.list = temp_list;
                }
                // Add the current parking entry to the list
                result.list[result.count++] = temp;
            }
        }
        fclose(f);
    } else {
        fprintf(stderr, "Could not open file: %s\n", filename);
    }

    return result;
}




/*88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888*/





void initialize_treeview_columns1(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    if (gtk_tree_view_get_columns(treeview) == NULL) { // Check for no existing columns
        // First column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Last Name", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Second column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Third column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Fourth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Number", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Fifth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Sixth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking ID", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Seventh column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Status", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(treeview, column);
	
	// eigth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Evaluation", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(treeview, column);
    }
}





gboolean populate_treeview_with_agents(GtkTreeView *treeview, const char *filename) {
    GtkListStore *store;
    GtkTreeIter iter;
    char line[256];
    char nom[50], prenom[50], id_agent[10], email[50], id_p[10], evaluation[20];
    int telephone, etat;

    // Create a GtkListStore model with appropriate columns
    store = gtk_list_store_new(8, 
                               G_TYPE_STRING, // nom
                               G_TYPE_STRING, // prenom
                               G_TYPE_STRING, // id_agent
                               G_TYPE_INT,    // telephone
                               G_TYPE_STRING, // email
                               G_TYPE_STRING, // id_p
                               G_TYPE_INT,    // etat
                               G_TYPE_STRING  // evaluation
                              );

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Error: Could not open file %s\n", filename);
        return FALSE;
    }

    // Read each line of the file
    while (fgets(line, sizeof(line), file)) {
        // Parse the line into variables
        if (sscanf(line, "%49s %49s %9s %d %49s %9s %d %19s",
                   nom, prenom, id_agent, &telephone, email, id_p, &etat, evaluation) == 8) {
            // Add rows where etat == 0
            if (etat == 0) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, 
                                   0, nom, 
                                   1, prenom, 
                                   2, id_agent, 
                                   3, telephone, 
                                   4, email, 
                                   5, id_p, 
                                   6, etat, 
                                   7, evaluation, 
                                   -1);
            }
        } else {
            g_print("Error: Failed to parse line: %s\n", line);
        }
    }

    // Close the file
    fclose(file);

    // Attach the GtkListStore model to the GtkTreeView
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));

    // Release the model reference to avoid memory leaks
    g_object_unref(store);

    return TRUE;
}




gboolean populate_treeview_with_allagents(GtkTreeView *treeview, const char *filename) {
    GtkListStore *store;
    GtkTreeIter iter;
    char line[256];
    char nom[50], prenom[50], id_agent[10], email[50], id_p[10], evaluation[20];
    int telephone, etat;

    // Create a GtkListStore model with appropriate columns
    store = gtk_list_store_new(8, 
                               G_TYPE_STRING, // nom
                               G_TYPE_STRING, // prenom
                               G_TYPE_STRING, // id_agent
                               G_TYPE_INT,    // telephone
                               G_TYPE_STRING, // email
                               G_TYPE_STRING, // id_p
                               G_TYPE_INT,    // etat
                               G_TYPE_STRING  // evaluation
                              );

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Error: Could not open file %s\n", filename);
        return FALSE;
    }

    // Read each line of the file
    while (fgets(line, sizeof(line), file)) {
        // Ensure no trailing newline
        line[strcspn(line, "\n")] = 0;

        // Reset buffers
        nom[0] = prenom[0] = id_agent[0] = email[0] = id_p[0] = evaluation[0] = '\0';

        // Debug: Print raw line
        g_print("Reading line: %s\n", line);

        // Parse the line into variables
        int parsed = sscanf(line, "%49s %49s %9s %d %49s %9s %d %19s",
                            nom, prenom, id_agent, &telephone, email, id_p, &etat, evaluation);

        // Debug: Print extracted values
        g_print("Parsed: %d -> Nom: %s | Prenom: %s | ID Agent: %s | Phone: %d | Email: %s | ID P: %s | Etat: %d | Evaluation: %s\n",
                parsed, nom, prenom, id_agent, telephone, email, id_p, etat, evaluation);

        // Ensure exactly 8 fields were parsed before inserting
        if (parsed == 8) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 
                               0, nom, 
                               1, prenom, 
                               2, id_agent, 
                               3, telephone, 
                               4, email, 
                               5, id_p, 
                               6, etat, 
                               7, evaluation, 
                               -1);
        } else {
            g_print("Warning: Incorrect line format -> %s\n", line);
        }
    }

    // Close the file
    fclose(file);

    // Attach the GtkListStore model to the GtkTreeView
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));

    // Release the model reference to avoid memory leaks
    g_object_unref(store);

    return TRUE;
}



void clear_and_display_single_agent(GtkTreeView *treeview, full_agent agent) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Create a new ListStore model with 8 columns matching full_agent structure
    store = gtk_list_store_new(8, 
                               G_TYPE_STRING, // Nom
                               G_TYPE_STRING, // Prenom
                               G_TYPE_STRING, // ID Agent
                               G_TYPE_INT,    // Telephone
                               G_TYPE_STRING, // Email
                               G_TYPE_STRING, // ID Parking
                               G_TYPE_INT,    // Etat
                               G_TYPE_STRING  // Evaluation
                              );

    // Append a single row to the ListStore
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, agent.nom,
                       1, agent.prenom,
                       2, agent.id_agent,
                       3, agent.telephone,
                       4, agent.email,
                       5, agent.id_p,
                       6, agent.etat,
                       7, agent.evaluation,
                       -1);

    // Attach the new model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Release the store reference to avoid memory leaks
    g_object_unref(store);
}


void clear_and_display_agents(GtkTreeView *treeview, full_agent *list, int count) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Define the model with 8 columns matching full_agent structure
    store = gtk_list_store_new(8, 
                               G_TYPE_STRING, // Nom
                               G_TYPE_STRING, // Prenom
                               G_TYPE_STRING, // ID Agent
                               G_TYPE_INT,    // Telephone
                               G_TYPE_STRING, // Email
                               G_TYPE_STRING, // ID Parking
                               G_TYPE_INT,    // Etat
                               G_TYPE_STRING  // Evaluation
                              );

    // Add rows for each agent in the list
    for (int i = 0; i < count; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, list[i].nom,
                           1, list[i].prenom,
                           2, list[i].id_agent,
                           3, list[i].telephone,
                           4, list[i].email,
                           5, list[i].id_p,
                           6, list[i].etat,
                           7, list[i].evaluation,
                           -1);
    }

    // Attach the new model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Release the store reference to avoid memory leaks
    g_object_unref(store);
}

