#include "gererparking1.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <ctype.h>


/*int modifier_agent( char * filename, char ID[], full_agent nouv )
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

*/

int ajouter(char * filename, park p )
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %s %d %d %f %s %s %s\n", p.id_p, p.nomp, p.gouv, p.munic, p.nb_p_t, p.nb_p_d, p.tarif,p.agent.nom, p.agent.prenom, p.agent.id_agent);
        fclose(f);
        return 1;
    }
    else return 0;
}




int modifier(char *filename, char id[], park nouv) 
{
    int tr = 0;
    park p;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    
    if (f != NULL && f2 != NULL) 
    {
        while (fscanf(f, "%s %s %s %s %d %d %f %s %s %s\n", 
                      p.id_p, p.nomp, p.gouv, p.munic, 
                      &(p.nb_p_t), &(p.nb_p_d), &(p.tarif), 
                      p.agent.nom, p.agent.prenom, p.agent.id_agent) != EOF) 
        {
            if (strcmp(p.id_p, id) == 0)
            {
                fprintf(f2, "%s %s %s %s %d %d %.2f %s %s %s\n", 
                        nouv.id_p, nouv.nomp, nouv.gouv, nouv.munic, 
                        nouv.nb_p_t, nouv.nb_p_d, nouv.tarif, 
                        nouv.agent.nom, nouv.agent.prenom, nouv.agent.id_agent);
                tr = 1; 
            } 
            else 
            {
                fprintf(f2, "%s %s %s %s %d %d %.2f %s %s %s\n", 
                        p.id_p, p.nomp, p.gouv, p.munic, 
                        p.nb_p_t, p.nb_p_d, p.tarif, 
                        p.agent.nom, p.agent.prenom, p.agent.id_agent);
            }
        }
        fclose(f);
        fclose(f2);

        // Replace the old file with the new one
        remove(filename);
        rename("nouv.txt", filename);
    } 
    else 
    {
        // Handle file opening errors
        if (f != NULL) fclose(f);
        if (f2 != NULL) fclose(f2);
        return -1; // Error code for file opening failure
    }
    return tr;
}



int supprimer(const char * filename, char id[] )
{
    int tr=0;
    park p;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {while(fscanf(f,"%s %s %s %s %d %d %f %s %s %s\n",p.id_p, p.nomp, p.gouv, p.munic, &(p.nb_p_t), &(p.nb_p_d), &(p.tarif), p.agent.nom, p.agent.prenom, p.agent.id_agent)!=EOF) 
    {
        if(strcmp(p.id_p, id) == 0)
                tr=1;
            else
                fprintf(f2,"%s %s %s %s %d %d %f %s %s %s\n", p.id_p, p.nomp, p.gouv, p.munic, p.nb_p_t, p.nb_p_d, p.tarif,p.agent.nom, p.agent.prenom, p.agent.id_agent);
    }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}




park recherche(char * filename, char id[] )
{
    park p;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while((tr==0) && (fscanf(f,"%s %s %s %s %d %d %f %s %s %s\n", p.id_p, p.nomp, p.gouv, p.munic, &(p.nb_p_t), &(p.nb_p_d), &(p.tarif), p.agent.nom, p.agent.prenom, p.agent.id_agent)!=EOF))
        {
            if(strcmp(p.id_p, id) == 0)
                tr=1;
        }
            fclose(f);
    }

    if (tr == 0) 
        strcpy(p.id_p, "-1"); // Use a string "-1" to indicate not found not 
    return p;
}



/*full_agent recherche_agent(char * filename, char id[] )
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
*/




int affecter_agent(char* fichier, char* fichier1, char idagentpouraffecter[], char idp[]) {
    FILE *f1 = fopen("agents.txt", "r");
    FILE *f = fopen(fichier, "r");

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return 0;
    }
    if (f1 == NULL) {
        printf("Erreur d'ouverture du fichier agent.\n");
        fclose(f);
        return 0;
    }

    park pnew = {0};
    park p = {0};
    full_agent a = {0};
    int modif = 0;

    // Debug: Print the agent ID being searched
    printf("Searching for agent with ID: %s\n", idagentpouraffecter);

    // Check if the agent exists and is available (etat == 0)
    while (fscanf(f1, "%49s %49s %9s %d %49s %9s %d %19s\n", 
                  a.nom, a.prenom, a.id_agent, &(a.telephone), 
                  a.email, a.id_p, &(a.etat), a.evaluation) == 8) {
        // Debug: Log the agent being read
        printf("Read agent: %s %s %s %d %s %s %d %s\n",
               a.nom, a.prenom, a.id_agent, a.telephone,
               a.email, a.id_p, a.etat, a.evaluation);

        // Check if this is the correct agent
        if ((strcmp(idagentpouraffecter, a.id_agent) == 0) && (a.etat == 0)) {
            printf("Found available agent: %s\n", a.id_agent);
            break;
        }
    }

    // If no matching agent is found
    if (strcmp(idagentpouraffecter, a.id_agent) != 0 || a.etat != 0) {
        printf("Agent non existant ou déjà affecté.\n");
        modif = 2; // Agent not found or already assigned
        fclose(f);
        fclose(f1);
        return modif;
    }

    // Debug: Print the park ID being searched
    printf("Searching for park with ID: %s\n", idp);

    // Iterate through parks to find the park to assign the agent to
    while (fscanf(f, "%49s %19s %49s %49s %d %d %f %9s %9s %9s\n", 
                  p.id_p, p.nomp, p.gouv, p.munic, 
                  &p.nb_p_t, &p.nb_p_d, &p.tarif, 
                  p.agent.nom, p.agent.prenom, p.agent.id_agent) == 10) {
        // Debug: Log the park being read
        printf("Read park: %s %s %s %s %d %d %.2f %s %s %s\n",
               p.id_p, p.nomp, p.gouv, p.munic,
               p.nb_p_t, p.nb_p_d, p.tarif,
               p.agent.nom, p.agent.prenom, p.agent.id_agent);

        if (strcmp(p.id_p, idp) == 0) {
            // Check if the park already has an assigned agent
            if (strcmp(p.agent.nom, "0") != 0 || strcmp(p.agent.prenom, "0") != 0 || strcmp(p.agent.id_agent, "0") != 0) {
                printf("Park already has an assigned agent.\n");
                modif = 4; // Park already has an agent
                break;
            }

            // Assign the agent to the park
            pnew = p;
            strncpy(pnew.agent.nom, a.nom, sizeof(pnew.agent.nom) - 1);
            strncpy(pnew.agent.prenom, a.prenom, sizeof(pnew.agent.prenom) - 1);
            strncpy(pnew.agent.id_agent, a.id_agent, sizeof(pnew.agent.id_agent) - 1);

            // Update the park and agent
            int x = modifier(fichier, pnew.id_p, pnew);
            if (x == 1) {
                a.etat = 1; // Mark the agent as assigned
                strncpy(a.id_p, pnew.id_p, sizeof(a.id_p) - 1); // Link the agent to the park
                int y = modifier_agent("agents.txt", a.id_agent, a);

                if (y == 1) {
                    modif = 1; // Successfully assigned
                }
            }
            break;
        } else {
            modif = 3; // Park not found
        }
    }

    if (modif == 0) {
        printf("Echec d'affectation.\n");
    }

    fclose(f);
    fclose(f1);

    return modif;
}





/*88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888*/


char **municipalite(const char *filename, const char *gouv) {
    char **list = NULL;  // Dynamic array of strings
    char line[256], gouv_in_file[100], mun[100];
    int count = 0;       // Number of matched municipalities

    // Process the input governorate: convert to lowercase and replace spaces
    char *gouv_processed = process_string(gouv);

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: Could not open file %s\n", filename);
        free(gouv_processed);
        return NULL;
    }

    while (fgets(line, sizeof(line), f)) {
        // Parse the line, splitting into "gouv" and "mun"
        if (sscanf(line, "%s %[^\n]", gouv_in_file, mun) == 2) {
            // Process gouv_in_file for comparison
            char *gouv_in_file_processed = process_string(gouv_in_file);

            if (strcmp(gouv_processed, gouv_in_file_processed) == 0) {
                // Match found, add the municipality (mun) to the list
                list = realloc(list, (count + 2) * sizeof(char *)); // +1 for new item, +1 for NULL
                list[count] = strdup(mun);  // Duplicate the string
                count++;
            }

            free(gouv_in_file_processed);
        }
    }
    fclose(f);

    free(gouv_processed);

    // Add NULL to mark the end of the list
    if (list != NULL) {
        list[count] = NULL;
    }

    return list;
}


// Helper function to free the dynamically allocated list
void free_municipalite_list(char **list) {
    if (list == NULL) return;
    for (int i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}


char **filter_agents_by_etat(const char *filename) {
    char **list = NULL;  // Dynamic array of strings
    char line[256];
    int count = 0;       // Number of matched agents

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    while (fgets(line, sizeof(line), f)) {
        full_agent agent;
        // Parse the line into an `agent` structure
        if (sscanf(line, "%s %s %s %d %s %s %d %s", 
                   agent.nom, 
                   agent.prenom, 
                   agent.id_agent, 
                   &agent.telephone, 
                   agent.email, 
                   agent.id_p, 
                   &agent.etat, 
                   agent.evaluation) == 8) {
            // Check if `etat` is 0
            if (agent.etat == 0) {
                // Add the agent ID to the list
                list = realloc(list, (count + 2) * sizeof(char *)); // +1 for new item, +1 for NULL
                if (list == NULL) {
                    printf("Memory allocation failed!\n");
                    fclose(f);
                    return NULL;
                }
                list[count] = strdup(agent.id_agent);  // Duplicate the string
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



/*88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888*/




// Convert a string to lowercase and replace spaces with underscores
char *process_string(const char *str) {
    char *processed = strdup(str); // Duplicate the input string
    for (char *p = processed; *p; p++) {
        if (*p == ' ') {
            *p = '_'; // Replace spaces with underscores
        } else {
            *p = tolower(*p); // Convert to lowercase
        }
    }
    return processed;
}


void replace_underscore_with_space(char *str) {
    if (str == NULL) {
        return; // Handle null pointer
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '_') {
            str[i] = ' ';
        }
    }
}




int is_valid_float(const char *str) {
    char *endptr;
    
    // Attempt to convert the string to float
    float number = strtof(str, &endptr);
    
    // Check if no characters were converted
    if (str == endptr) {
        return 0; // Invalid: No conversion performed
    }
    
    // Check if the remaining characters are only whitespace
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return 0; // Invalid: Non-whitespace characters remain
        }
        endptr++;
    }

    // If we reached here, the string is a valid float
    return 1;
}




int is_id_unique(const char *id, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1; // Assume ID is unique if file doesn't exist
    }

    park p;
    while(fscanf(file,"%s %s %s %s %d %d %f %s %s %s\n",p.id_p, p.nomp, p.gouv, p.munic, &(p.nb_p_t), &(p.nb_p_d), &(p.tarif), p.agent.nom, p.agent.prenom, p.agent.id_agent)!=EOF) {
        if (strcmp(p.id_p, id) == 0) {
            fclose(file);
            return 0; // ID is not unique
        }
    }

    fclose(file);
    return 1; // ID is unique
}


void float_to_string(float value, char *buffer, size_t buffer_size) {
    // Convert the float to a string with 2 decimal places
    snprintf(buffer, buffer_size, "%.2f", value);
}




// Function to generate a random character (uppercase letters and digits)
char random_char() {
    int type = rand() % 2; // 0: digit, 1: uppercase letter
    if (type == 0) {
        return '0' + rand() % 10; // Digit
    } else {
        return 'A' + rand() % 26; // Uppercase letter
    }
}


// Function to generate a unique ID and return it
char *generate_unique_id(const char *str1, const char *str2, const char *str3, const char *filename) {
    char id[256];
    int is_unique = 0;

    while (!is_unique) {
        // Initialize the ID
        id[0] = '\0';

        // Take the first two characters from str1
        if (str1 && strlen(str1) > 0) {
            id[0] = isdigit(str1[0]) ? str1[0] : toupper(str1[0]);
            id[1] = (strlen(str1) > 1) ? (isdigit(str1[1]) ? str1[1] : toupper(str1[1])) : 'X'; // 'X' as fallback
        } else {
            id[0] = id[1] = 'X'; // Fallback if str1 is empty
        }
        id[2] = '\0';

        // Take the first character from str2
        if (str2 && strlen(str2) > 0) {
            char c = isdigit(str2[0]) ? str2[0] : toupper(str2[0]);
            strncat(id, &c, 1);
        } else {
            strncat(id, "X", 1); // Fallback if str2 is empty
        }

        // Take the first character from str3
        if (str3 && strlen(str3) > 0) {
            char c = isdigit(str3[0]) ? str3[0] : toupper(str3[0]);
            strncat(id, &c, 1);
        } else {
            strncat(id, "X", 1); // Fallback if str3 is empty
        }

        // Append 5 random characters to the ID
        for (int i = 0; i < 5; i++) {
            char random = random_char();
            strncat(id, &random, 1);
        }

        id[strlen(id)] = '\0'; // Null-terminate the string

        // Check if the generated ID is unique
        if (is_id_unique(id, filename)) {
            is_unique = 1;
        }
    }

    // Dynamically allocate memory for the unique ID and return it
    char *unique_id = malloc(strlen(id) + 1);
    if (unique_id == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(unique_id, id);
    return unique_id;
}



void add_to_first(char ***liste, const char *new_element) {
    // Determine the size of the existing array
    int size = 0;
    if (*liste != NULL) {
        while ((*liste)[size] != NULL) {
            size++;
        }
    }

    // Reallocate memory for the new array with an extra element
    *liste = realloc(*liste, (size + 2) * sizeof(char *));
    if (*liste == NULL) {
        perror("Realloc failed");
        exit(EXIT_FAILURE);
    }

    // Shift all existing elements one position down
    for (int i = size; i > 0; i--) {
        (*liste)[i] = (*liste)[i - 1];
    }

    // Add the new element to the first position
    (*liste)[0] = strdup(new_element);
    if ((*liste)[0] == NULL) {
        perror("Strdup failed");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the list
    (*liste)[size + 1] = NULL;
}



/*8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888*/





void initialize_treeview_columns(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    if (gtk_tree_view_get_columns(treeview) == NULL) { // Check for no existing columns
        // First column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Second column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking Name", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Third column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Gouvernorate", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Fourth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Municipality", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Fifth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Total Places", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Sixth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Available Places", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Seventh column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Rate", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Eighth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Agent Last Name", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Ninth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Agent Name", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(treeview, column);

        // Tenth column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Agent ID", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(treeview, column);
    }
}






gboolean populate_treeview_from_file(GtkTreeView *treeview, const char *filename) {
    GtkListStore *store;
    GtkTreeIter iter;
    char line[256];
    char col1[100], col2[100], col3[100], col4[100], col8[100], col9[100], col10[100];
    float col7;
    int col5, col6;

    store = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_INT, G_TYPE_INT, G_TYPE_FLOAT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Error: Could not open file %s\n", filename);
        return FALSE;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %s %s %s %d %d %f %s %s %s", col1, col2, col3, col4, &col5, &col6, &col7, col8, col9, col10) == 10) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, col1, 1, col2, 2, col3, 3, col4, 4, col5, 5, col6, 
                               6, col7, 7, col8, 8, col9, 9, col10, -1);
        }
    }
    fclose(file);

    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    return TRUE;
}




SearchResult recherche_nomp(const char *filename, const char *nom) {
    FILE *f = fopen(filename, "r");
    SearchResult result;
    result.count = 0;     // Initialize count to 0
    result.list = NULL;   // Initialize list to NULL

    if (f != NULL) {
        park temp;
        int size = 10; // Initial capacity for the list
        result.list = malloc(size * sizeof(park)); // Allocate initial memory

        if (result.list == NULL) { // Check for allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            fclose(f);
            return result;
        }

        // Scan each line of the file
        while (fscanf(f, "%s %s %s %s %d %d %f %s %s %s\n", 
                      temp.id_p, temp.nomp, temp.gouv, temp.munic, 
                      &temp.nb_p_t, &temp.nb_p_d, &temp.tarif, 
                      temp.agent.id_agent, temp.agent.nom, temp.agent.prenom) != EOF) {
            if (strcmp(temp.nomp, nom) == 0) { // Compare names
                if (result.count >= size) {
                    size *= 2;
                    park *temp_list = realloc(result.list, size * sizeof(park));
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


void clear_and_display_single_parking(GtkTreeView *treeview, park p) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Create a new ListStore model with 10 columns matching your Parking structure
    store = gtk_list_store_new(10, 
                               G_TYPE_STRING, // ID
                               G_TYPE_STRING, // Nom de Parking
                               G_TYPE_STRING, // Gouvernorat
                               G_TYPE_STRING, // Municipalité
                               G_TYPE_INT,    // Nombre des places totale
                               G_TYPE_INT,    // Nombre des places disponibles
                               G_TYPE_FLOAT,  // Tarif
                               G_TYPE_STRING, // Agent ID
                               G_TYPE_STRING, // Agent Nom
                               G_TYPE_STRING  // Agent Prénom
                              );

    // Append a single row to the ListStore
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, p.id_p,
                       1, p.nomp,
                       2, p.gouv,
                       3, p.munic,
                       4, p.nb_p_t,
                       5, p.nb_p_d,
                       6, p.tarif,
                       7, p.agent.id_agent,
                       8, p.agent.nom,
                       9, p.agent.prenom,
                       -1);

    // Attach the new model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Release the store reference to avoid memory leaks
    g_object_unref(store);
}




void clear_and_display_parkings(GtkTreeView *treeview, park *list, int count) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Define the model with 10 columns matching your Parking structure
    store = gtk_list_store_new(10, 
                               G_TYPE_STRING, // ID
                               G_TYPE_STRING, // Nom de Parking
                               G_TYPE_STRING, // Gouvernorat
                               G_TYPE_STRING, // Municipalité
                               G_TYPE_INT,    // Nombre des places totale
                               G_TYPE_INT,    // Nombre des places disponibles
                               G_TYPE_FLOAT,  // Tarif
                               G_TYPE_STRING, // Agent ID
                               G_TYPE_STRING, // Agent Nom
                               G_TYPE_STRING  // Agent Prénom
                              );

    // Add rows for each parking entry in the list
    for (int i = 0; i < count; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, list[i].id_p,
                           1, list[i].nomp,
                           2, list[i].gouv,
                           3, list[i].munic,
                           4, list[i].nb_p_t,
                           5, list[i].nb_p_d,
                           6, list[i].tarif,
                           7, list[i].agent.id_agent,
                           8, list[i].agent.nom,
                           9, list[i].agent.prenom,
                           -1);
    }

    // Attach the new model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Release the store reference to avoid memory leaks
    g_object_unref(store);
}


char **filter_parkings_by_id(const char *filename) {
    char **list = NULL;  // Dynamic array to store parking IDs
    char line[256];
    int count = 0;       // Number of parking IDs

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Read each line of the file
    while (fgets(line, sizeof(line), f)) {
        park parking;  // To store parsed parking information

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
            // Add the parking ID to the list
            list = realloc(list, (count + 2) * sizeof(char *)); // +1 for new item, +1 for NULL
            if (list == NULL) {
                printf("Memory allocation failed!\n");
                fclose(f);
                return NULL;
            }
            list[count] = strdup(parking.id_p);  // Duplicate the parking ID string
            count++;
        }
    }
    fclose(f);

    // Add NULL to mark the end of the list
    if (list != NULL) {
        list[count] = NULL;
    }

    return list;
}


