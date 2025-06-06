#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <ctype.h>


#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "gererparking1.h"
#include "gereragent.h"


void
on_buttonvalider_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
}


void
on_checkbuttonaffecte_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    
}



void on_buttonajouterp_clicked(GtkButton *button, gpointer user_data) {
 

}




void
on_buttonannulerajoutp_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}




void
on_buttonrecherchem_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_buttonvaliderm_clicked(GtkButton *button, gpointer user_data) {

}



void
on_buttonannulermodif_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}




void
on_radiobuttonlp1_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobuttonlp2_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_buttonafficherlp_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	// Retrieve the TreeView from the Glade file
    GtkTreeView *treeview = lookup_widget(GTK_WIDGET(button), "treeviewlp");
    GtkWidget *buttonsup = lookup_widget(GTK_WIDGET(button), "buttonsupprimerlp");
    GtkWidget *buttonobs = lookup_widget(GTK_WIDGET(button), "buttonobserverlp");
    if (!treeview) {
        g_print("Error: Could not find TreeView 'treeviewlp' in the Glade file.\n");
        return;
    }

    // Initialize the TreeView columns
    initialize_treeview_columns(treeview);

    // Populate the TreeView with data from the file
    if (populate_treeview_from_file(treeview, "parkings.txt") == FALSE) {
        g_print("Error: Failed to populate TreeView from file.\n");
    }

}




void
on_buttonrecherchelp_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "feedbacklp");
	GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entrylp");
	GtkWidget *radiobuttonid = lookup_widget(GTK_WIDGET(button), "radiobuttonlp1");
	GtkWidget *radiobuttonnom = lookup_widget(GTK_WIDGET(button), "radiobuttonlp2");
	GtkTreeView *treeview = lookup_widget(GTK_WIDGET(button), "treeviewlp");
	GtkWidget *buttonsup = lookup_widget(GTK_WIDGET(button), "buttonsupprimerlp");
        GtkWidget *buttonobs = lookup_widget(GTK_WIDGET(button), "buttonobserverlp");

	gboolean is_activeid = gtk_toggle_button_get_active(radiobuttonid);
	gboolean is_activenom = gtk_toggle_button_get_active(radiobuttonnom);
	
	if (is_activeid){
		const gchar *active_text = gtk_entry_get_text(GTK_ENTRY(entry));
		const char *filename = "parkings.txt";
		park p;
		p =recherche(filename, active_text);
		if (strcmp(p.id_p, "-1") != 0) {
			clear_and_display_single_parking(treeview, p);
			gtk_label_set_text(GTK_LABEL(feedback_label), "");
		}else {
	    		// Display error message for invalid ID
	    		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : ID invalide!</span>");
		}
	}
	else if (is_activenom){
		const gchar *active_text = gtk_entry_get_text(GTK_ENTRY(entry));
		const char *filename = "parkings.txt";
		SearchResult result = recherche_nomp(filename, active_text);

    		if (result.count == 0) {
        		// Display error message for invalid ID
	    		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Nom invalide!</span>");
    		} else {
        		clear_and_display_parkings(treeview, result.list, result.count);
			gtk_label_set_text(GTK_LABEL(feedback_label), "");
		}
	}
}


void on_buttonsupprimerlp_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewlp");
    
    if (!GTK_IS_TREE_VIEW(treeview)) {
        g_print("Error: Failed to find GtkTreeView widget.\n");
        return;
    }

    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (!GTK_IS_TREE_SELECTION(selection)) {
        g_print("Error: selection is not a valid GtkTreeSelection.\n");
        return;
    }

    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id_p = NULL;

    const char *filename = "parkings.txt";
    int test = 0;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_tree_model_get(model, &iter, 0, &id_p, -1);

        if (id_p != NULL) {
            test = supprimer(filename, id_p);
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
            g_print("Deleted parking with ID: %s\n", id_p);
        }
    } else {
        g_print("No row selected to delete.\n");
    }

    if (test == 1) {
        GtkWidget *window_show = create_dialogsupprimerparking();
        gtk_widget_show(window_show);
	GtkWidget *feedback_label1 = lookup_widget(window_show, "labelsuplp");
	char buffer[50]; // Adjust size if needed
	snprintf(buffer, sizeof(buffer), "%s",id_p);
	gtk_label_set_text(GTK_LABEL(feedback_label1), buffer);
	g_free(id_p);
    }
}





void
on_buttonobserverlp_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewlp");
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

    GtkTreeModel *model;
    GtkTreeIter iter;

    // Column values to store
    gchar *id_p;
    gchar *nomp;
    gchar *gouv;
    gchar *munic;
    gint nb_p_t;
    gint nb_p_d;
    gfloat tarif;
    gchar *id_agent;
    gchar *nom_agent;
    gchar *prenom_agent;

    // Get the selected row
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        // Retrieve column values from the selected row
        gtk_tree_model_get(model, &iter,
                           0, &id_p,
                           1, &nomp,
                           2, &gouv,
                           3, &munic,
                           4, &nb_p_t,
                           5, &nb_p_d,
                           6, &tarif,
                           7, &id_agent,
                           8, &nom_agent,
                           9, &prenom_agent,
                           -1);

	GtkWidget *window_show = create_dialogobserverparking();
        gtk_widget_show(window_show);

        // Update labels with the retrieved values
        GtkWidget *label_id = lookup_widget(window_show, "label_id");
        GtkWidget *label_nomp = lookup_widget(window_show, "label_nomp");
        GtkWidget *label_gouv = lookup_widget(window_show, "label_gouv");
        GtkWidget *label_munic = lookup_widget(window_show, "label_munic");
        GtkWidget *label_nb_p_t = lookup_widget(window_show, "label_nb_p_t");
        GtkWidget *label_nb_p_d = lookup_widget(window_show, "label_nb_p_d");
        GtkWidget *label_tarif = lookup_widget(window_show, "label_tarif");
        GtkWidget *label_id_agent = lookup_widget(window_show, "label_id_agent");
        //GtkWidget *label_nom_agent = lookup_widget(window_show, "label_nom_agent");
        //GtkWidget *label_prenom_agent = lookup_widget(window_show, "label_prenom_agent");

        // Set label texts
       char buffer[256];

	// Set label_id in bold
	sprintf(buffer, "<b>%s</b>", id_p);
	gtk_label_set_markup(GTK_LABEL(label_id), buffer);

	// Set label_nomp in bold
	sprintf(buffer, "<b>%s</b>", nomp);
	gtk_label_set_markup(GTK_LABEL(label_nomp), buffer);

	// Set label_gouv in bold
	sprintf(buffer, "<b>%s</b>", gouv);
	gtk_label_set_markup(GTK_LABEL(label_gouv), buffer);

	// Set label_munic in bold
	sprintf(buffer, "<b>%s</b>", munic);
	gtk_label_set_markup(GTK_LABEL(label_munic), buffer);

	// Set label_nb_p_t in bold
	sprintf(buffer, "<b>%d</b>", nb_p_t);
	gtk_label_set_markup(GTK_LABEL(label_nb_p_t), buffer);

	// Set label_nb_p_d in bold
	sprintf(buffer, "<b>%d</b>", nb_p_d);
	gtk_label_set_markup(GTK_LABEL(label_nb_p_d), buffer);

	// Set label_tarif in bold
	sprintf(buffer, "<b>%.2f</b>", tarif);
	gtk_label_set_markup(GTK_LABEL(label_tarif), buffer);

	// Set label_id_agent in bold
	sprintf(buffer, "<b>%s</b>", id_agent);
	gtk_label_set_markup(GTK_LABEL(label_id_agent), buffer);

        //gtk_label_set_text(GTK_LABEL(label_nom_agent), nom_agent);
        //gtk_label_set_text(GTK_LABEL(label_prenom_agent), prenom_agent);

        // Free the dynamically allocated strings
        g_free(id_p);
        g_free(nomp);
        g_free(gouv);
        g_free(munic);
        g_free(id_agent);
        g_free(nom_agent);
        g_free(prenom_agent);
    } else {
        // Handle case where no row is selected
        g_print("No row selected.\n");
    }
}




void
on_buttonafficheraa_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	
	// Retrieve the TreeView from the Glade file
    	GtkTreeView *treeview = lookup_widget(GTK_WIDGET(button), "treeviewaa");
	// Initialize the TreeView columns
   	 initialize_treeview_columns1(treeview);
	 const char *filename="agents.txt";
    	// Populate the TreeView with data from the file
   	 if (populate_treeview_with_agents(treeview,filename) == FALSE) {
       		 g_print("Error: Failed to populate TreeView from file.\n");
	}
}


void
on_buttonaffecteraa_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window_show = create_dialogaffecteragent();

    	GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entryaa");
    	GtkWidget *combobox = lookup_widget(GTK_WIDGET(button), "comboboxentryaa");
	GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "feedbackaa");


	const gchar *active_text1 = gtk_entry_get_text(GTK_ENTRY(entry));
    	const gchar *active_text2 = gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox))));
	gtk_label_set_text(GTK_LABEL(feedback_label), "");
	const char *filename1 = "parkings.txt";
	const char *filename2 = "agents.txt";
	int test = affecter_agent(filename1 ,filename2, active_text1, active_text2);
	if (test==2)
		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : ID Agent invalide!</span>");
	if (test==3)
		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : ID Parking invalide!</span>");
	if (test==4)
		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : ID Parking déjà affecté!</span>");
	if (test==1){
		gtk_widget_show(window_show);
		gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox))), "");
           	gtk_entry_set_text(GTK_ENTRY(entry), "");
		gtk_label_set_text(GTK_LABEL(feedback_label), "");
		
	}
}


void
on_buttonactivateaa_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *combobox = lookup_widget(GTK_WIDGET(button), "comboboxentryaa");
	const char *filename = "parkings.txt";
	char **liste = filter_parkings_by_id(filename); // Function that returns list of IDs
	// Clear existing items in the combobox
	gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));

	// Populate the combobox with the filtered list
	for (int i = 0; liste[i] != NULL; i++) {
		    printf("- Adding: %s\n", liste[i]);
		    gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), liste[i]);
	}
}


//8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888


void
on_buttonaddparkingactivate_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *frame = lookup_widget(GTK_WIDGET(button), "frameparking");

 	   // Show the GtkFixed widget
   	 gtk_widget_show(frame);
}


void
on_buttonmodifierlp_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewlp");
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
     if (!GTK_IS_TREE_VIEW(treeview)) {
        g_print("Error: Failed to find GtkTreeView widget.\n");
        return;
    }
    if (!GTK_IS_TREE_SELECTION(selection)) {
        g_print("Error: selection is not a valid GtkTreeSelection.\n");
        return;
    }

    GtkTreeModel *model;
    GtkTreeIter iter;

    // Column values to store
    gchar *id_p;
    gchar *nomp;
    gchar *gouv;
    gchar *munic;
    gint nb_p_t;
    gint nb_p_d;
    gfloat tarif;
    gchar *id_agent;
    gchar *nom_agent;
    gchar *prenom_agent;

   // Get the selected row
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        // Retrieve column values from the selected row
        gtk_tree_model_get(model, &iter,
                           0, &id_p,
                           1, &nomp,
                           2, &gouv,
                           3, &munic,
                           4, &nb_p_t,
                           5, &nb_p_d,
                           6, &tarif,
                           7, &nom_agent,
                           8, &prenom_agent,
                           9, &id_agent,
                           -1);
	GtkWidget *window_show = create_dialogmodify();
	gtk_widget_show(window_show);

        // Update labels with the retrieved values
        GtkWidget *entry1 = lookup_widget(window_show, "idparkingm");
        GtkWidget *entry2 = lookup_widget(window_show, "nompm");
        GtkWidget *label_gouv = lookup_widget(window_show, "labelgouvm");
        GtkWidget *label_munic = lookup_widget(window_show, "labelmunim");
        GtkWidget *spinbutton1 = lookup_widget(window_show, "nbptm");
        GtkWidget *spinbutton2 = lookup_widget(window_show, "nbpdm");
        GtkWidget *entry3 = lookup_widget(window_show, "tarifm");
        GtkWidget *combobox = lookup_widget(window_show, "agentm");
    	GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "feedbackm");
	

	    // Set the info
	    char updated_textid[256]; // Allocate sufficient space
	    snprintf(updated_textid, sizeof(updated_textid), "%s", id_p);
	    gtk_label_set_markup(GTK_LABEL(entry1), g_strdup_printf("<span foreground='black' weight='bold'>%s</span>", updated_textid));

	    char updated_textg[256]; // Allocate sufficient space
	    snprintf(updated_textg, sizeof(updated_textg), "%s", gouv);
	    replace_underscore_with_space(updated_textg);
	    gtk_label_set_markup(GTK_LABEL(label_gouv), g_strdup_printf("<span foreground='black' weight='bold'>%s</span>", updated_textg));

	    char updated_textm[256]; // Allocate sufficient space
	    snprintf(updated_textm, sizeof(updated_textm), "%s", munic);
	    replace_underscore_with_space(updated_textm);
	    gtk_label_set_markup(GTK_LABEL(label_munic), g_strdup_printf("<span foreground='black' weight='bold'>%s</span>", updated_textm));

	    // Set remaining widgets
	    gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox))), id_agent);
	    gtk_entry_set_text(GTK_ENTRY(entry2), nomp);
	    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton1), nb_p_t);
	    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2), nb_p_d);
	    char strtarif[20];
	    float_to_string(tarif, strtarif, sizeof(strtarif));
	    gtk_entry_set_text(GTK_ENTRY(entry3), strtarif);

	    // Clear any feedback message
	    gtk_label_set_text(GTK_LABEL(feedback_label), "");


	    //open agent combobox
		const char *filename = "agents.txt";
		char **liste = filter_agents_by_etat(filename); // Function that returns list of IDs with etat == 0
		add_to_first(&liste, "Pas d'agent");

		if (liste == NULL) {
		    printf("Error: No matching agents found or file read error.\n");
		}

		// Clear existing items in the combobox
		gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));

		// Populate the combobox with the filtered list
		for (int i = 0; liste[i] != NULL; i++) {
		    printf("- Adding: %s\n", liste[i]);
		    gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), liste[i]);
		}

		// Free the dynamically allocated list
		free_municipalite_list(liste);
	}
}


on_cancelbuttonm_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "dialogmodify");
	// close the modify dialog
	gtk_widget_destroy(dialog);
}


on_applybuttonm_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "dialogmodify");

    GtkWidget *window_show = lookup_widget(GTK_WIDGET(button), "dialogmodifparking");
    window_show = create_dialogmodifparking();

    GtkWidget *labelgouv = lookup_widget(GTK_WIDGET(button), "labelgouvm");
    GtkWidget *labelmunic = lookup_widget(GTK_WIDGET(button), "labelmunim");
    GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "feedbackm");
    GtkWidget *entry1 = lookup_widget(GTK_WIDGET(button), "idparkingm");
    GtkWidget *entry2 = lookup_widget(GTK_WIDGET(button), "nompm");
    GtkWidget *entry3 = lookup_widget(GTK_WIDGET(button), "tarifm");
    GtkWidget *spinbutton1 = lookup_widget(GTK_WIDGET(button), "nbptm");
    GtkWidget *spinbutton2 = lookup_widget(GTK_WIDGET(button), "nbpdm");
    GtkWidget *combobox = lookup_widget(GTK_WIDGET(button), "agentm");
   
    const gchar *active_text0 = gtk_label_get_text(GTK_LABEL(entry1));

    const char *filename = "parkings.txt";
    park p = recherche(filename, active_text0);

    const gchar *active_text1 = gtk_entry_get_text(GTK_ENTRY(entry2));
    const gchar *active_text2 = gtk_entry_get_text(GTK_ENTRY(entry3));
    int active_text3 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton1));
    int active_text4 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
    const gchar *active_text5 = gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox))));

    if (active_text1 && strlen(active_text1) > 0 &&
        active_text2 && strlen(active_text2) > 0 &&
        active_text3 > 0 && active_text4 >= 0 &&
        active_text5 && strlen(active_text5) > 0) {

        snprintf(p.nomp, sizeof(p.nomp), "%s", active_text1);
        p.nb_p_t = active_text3;
        p.nb_p_d = active_text4;

        if (is_valid_float(active_text2)) {
            float value = strtof(active_text2, NULL);
            p.tarif = ((int)(value * 100 + 0.5)) / 100.0;
        } else {
            gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Saisi incorrecte!</span>");
            return;
        }

        if (strcmp(active_text5, p.agent.id_agent) != 0) {
            if (strcmp(active_text5, "Pas d'agent") == 0) {
		if (strcmp(p.agent.id_agent, "0") !=0){
			full_agent aa = recherche_agent_all("agents.txt", p.agent.id_agent);
			aa.etat = 0;
		        modifier_agent("agents.txt", p.agent.id_agent, aa);
		}
                snprintf(p.agent.nom, sizeof(p.agent.nom), "0");
                snprintf(p.agent.prenom, sizeof(p.agent.prenom), "0");
                snprintf(p.agent.id_agent, sizeof(p.agent.id_agent), "0");
            } else {
                full_agent a = recherche_agent("agents.txt", active_text5);
                if (strcmp(a.id_agent, "-1") == 0) {
                    gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Agent invalide!</span>");
                    return;
                } else {
                    full_agent aa = recherche_agent_all("agents.txt", p.agent.id_agent);
                    aa.etat = 0;
                    modifier_agent("agents.txt", p.agent.id_agent, aa);

                    snprintf(p.agent.nom, sizeof(p.agent.nom), "%s", a.nom);
                    snprintf(p.agent.prenom, sizeof(p.agent.prenom), "%s", a.prenom);
                    snprintf(p.agent.id_agent, sizeof(p.agent.id_agent), "%s", a.id_agent);
                    a.etat = 1;
                    modifier_agent("agents.txt", active_text5, a);
                }
            }
        }

        if (modifier(filename, active_text0, p)) {

            gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox))), "");
            gtk_entry_set_text(GTK_ENTRY(entry1), "");
            gtk_entry_set_text(GTK_ENTRY(entry2), "");
            gtk_entry_set_text(GTK_ENTRY(entry3), "");
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton1), 1);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2), 1);
            gtk_label_set_text(GTK_LABEL(feedback_label), "");
            gtk_label_set_text(GTK_LABEL(labelmunic), "");
            gtk_label_set_text(GTK_LABEL(labelgouv), "");
	    // close the modify dialog
	    gtk_widget_destroy(dialog);
	    //show success dialog
	    gtk_widget_show(window_show);
	
        } else {
            printf("Error: Parking could not be modified.\n");
        }
    } else {
        gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Saisi incomplète!</span>");
    }

}

void
on_buttonaddparking_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *window_show = lookup_widget(GTK_WIDGET(button), "dialogajoutparking");
    window_show= create_dialogajoutparking ();

    GtkWidget *checkbutton = lookup_widget(GTK_WIDGET(button), "checkbuttonaffectep");
    GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "feedbackap");	
    GtkWidget *entry1 = lookup_widget(GTK_WIDGET(button), "entryap1");
    GtkWidget *combobox1 = lookup_widget(GTK_WIDGET(button), "comboboxentryap");
    GtkWidget *combobox2 = lookup_widget(GTK_WIDGET(button), "comboboxap");
    GtkWidget *spinbutton = lookup_widget(GTK_WIDGET(button), "spinbuttonap");
    GtkWidget *entry2 = lookup_widget(GTK_WIDGET(button), "entryap2");
    GtkWidget *combobox3 = lookup_widget(GTK_WIDGET(button), "comboboxentryap2");

    // Get input text from widgets
    const gchar *active_text0 = gtk_entry_get_text(GTK_ENTRY(entry1));
    const gchar *active_text1 = gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox1))));
    const gchar *active_text2 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox2));
    int active_text3 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton)); // Fixed for GtkSpinButton
    const gchar *active_text4 = gtk_entry_get_text(GTK_ENTRY(entry2));

    g_print("active_text0 selected/entered: %s\n", active_text0);
    g_print("active_text1 selected/entered: %s\n", active_text1);
    g_print("active_text2 selected/entered: %s\n", active_text2);
    g_print("active_text3 selected/entered: %d\n", active_text3);
    g_print("active_text4 selected/entered: %s\n", active_text4);

    // Validate inputs
    if (active_text0 && strlen(active_text0) > 0 &&
        active_text1 && strlen(active_text1) > 0 &&
        active_text2 && strlen(active_text2) > 0 &&
        active_text3 > 0 &&  // Ensure active_text3 is positive
        active_text4 && strlen(active_text4) > 0) {
        
        const char *filename = "parkings.txt";
        park p;

        // Safely copy input values using snprintf
        snprintf(p.nomp, sizeof(p.nomp), "%s", active_text0);
	char *active_text11 =process_string(active_text1);
        snprintf(p.gouv, sizeof(p.gouv), "%s", active_text11);
	char *active_text22 =process_string(active_text2);
        snprintf(p.munic, sizeof(p.munic), "%s", active_text22);
	p.nb_p_t=active_text3;
	p.nb_p_d=active_text3;

        // Check for valid float in active_text4
        if (is_valid_float(active_text4)) {
	    float value = strtof(active_text4, NULL);
            p.tarif = ((int)(value * 100 + 0.5)) / 100.0;

        } else {
            gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Saisi incorrecte!</span>");
            return;
        }

        // Handle checkbutton logic
        gboolean is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton));
        if (is_active) {
            const gchar *active_text5 = gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox3))));
            if (active_text5 && strlen(active_text5) > 0) {
                full_agent a = recherche_agent("agents.txt", active_text5);
                if (strcmp(a.id_agent, "-1") == 0) {
                    gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Agent invalide!</span>");
                    return;
                }

                // Assign agent to parking
                snprintf(p.agent.nom, sizeof(p.agent.nom), "%s", a.nom);
                snprintf(p.agent.prenom, sizeof(p.agent.prenom), "%s", a.prenom);
                snprintf(p.agent.id_agent, sizeof(p.agent.id_agent), "%s", a.id_agent);

                a.etat = 1; // Update agent status
                modifier_agent("agents.txt", active_text5, a);
            } else {
                gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Saisi incomplète!</span>");
                return;
            }
        } else {
            // Default agent information for non-affected state
            snprintf(p.agent.nom, sizeof(p.agent.nom), "0");
            snprintf(p.agent.prenom, sizeof(p.agent.prenom), "0");
            snprintf(p.agent.id_agent, sizeof(p.agent.id_agent), "0");
        }

        // Generate unique parking ID and add parking
        char *unique_id = generate_unique_id(p.nomp, p.gouv, p.munic, filename);
        snprintf(p.id_p, sizeof(p.id_p), "%s", unique_id);
        free(unique_id);  // Free the allocated memory after using it

        int success = ajouter(filename, p);
        if (success) {
            // Show success dialog 

            gtk_widget_show(window_show);
	    GtkWidget *feedback_label1 = lookup_widget(window_show, "labelajoutparkingid");
	    char buffer[50]; // Adjust size if needed
	    snprintf(buffer, sizeof(buffer), "ID:\n %s", p.id_p);
	    gtk_label_set_text(GTK_LABEL(feedback_label1), buffer);


	//clear everything
	gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox1))), "");
	gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox2))));
	gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox3))), "");
	gtk_entry_set_text(GTK_ENTRY(entry1), "");
	gtk_entry_set_text(GTK_ENTRY(entry2), "");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton), 1);
	gtk_label_set_text(GTK_LABEL(feedback_label), "");

        } else {
            printf("Error: Parking could not be added.\n");
        }
    } else {
        gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Saisi incomplète!</span>");
    }
}


void
on_buttoncancelparking_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *frame = lookup_widget(GTK_WIDGET(button), "frameparking");

   	 GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "feedbackap");
   	 GtkWidget *entry1 = lookup_widget(GTK_WIDGET(button), "entryap1");
   	 GtkWidget *combobox1 = lookup_widget(GTK_WIDGET(button), "comboboxentryap");
  	 GtkWidget *combobox2 = lookup_widget(GTK_WIDGET(button), "comboboxap");
   	 GtkWidget *spinbutton = lookup_widget(GTK_WIDGET(button), "spinbuttonap");
  	 GtkWidget *entry2 = lookup_widget(GTK_WIDGET(button), "entryap2");
  	 GtkWidget *combobox3 = lookup_widget(GTK_WIDGET(button), "comboboxentryap2");

	//clear everything
	gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox1))), "");
	gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox2))));
	gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox3))), "");
	gtk_entry_set_text(GTK_ENTRY(entry1), "");
	gtk_entry_set_text(GTK_ENTRY(entry2), "");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton), 1);
	gtk_label_set_text(GTK_LABEL(feedback_label), "");

 	// hide the GtkFixed widget
   	gtk_widget_hide(frame);
}


void
on_buttonvaliderap_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	 // Retrieve parent window or relevant container
    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button));

    // Use lookup_widget to find comboboxes by ID
    GtkWidget *combobox1 = lookup_widget(GTK_WIDGET(button), "comboboxentryap");
    GtkWidget *combobox2 = lookup_widget(GTK_WIDGET(button), "comboboxap");

   // Get the child entry widget from combobox1 (GtkComboBoxEntry)
    GtkWidget *entry_widget = gtk_bin_get_child(GTK_BIN(combobox1));
    const gchar *active_text = gtk_entry_get_text(GTK_ENTRY(entry_widget));

    if (active_text && strlen(active_text) > 0) {
        g_print("Combobox1 selected/entered: %s\n", active_text);

        // Clear combobox2 (GtkComboBox) options
        GtkListStore *list_store = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox2)));
        gtk_list_store_clear(list_store);

        const char *filename = "municipalite.txt";
	char **municipalities = municipalite(filename, active_text);
	 if (municipalities != NULL) {
        printf("Municipalities in %s:\n", active_text);
        for (int i = 0; municipalities[i] != NULL; i++) {
            printf("- %s\n", municipalities[i]);
            gtk_combo_box_append_text(GTK_COMBO_BOX(combobox2), municipalities[i]);
        }

        // Free the allocated memory
        free_municipalite_list(municipalities);
    } else {
        printf("No municipalities found for %s or file could not be opened.\n", active_text);
    }

        // Set combobox2 to the first item if necessary
        gtk_combo_box_set_active(GTK_COMBO_BOX(combobox2), 0);


    } else {
        g_print("No selection or text entered in combobox1.\n");
    }
    /*  Optionally clear the entry field in combobox1
    gtk_entry_set_text(GTK_ENTRY(entry_widget), "");  */

}


void
on_checkbuttonaffectep_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
// Retrieve the combobox by ID
    GtkWidget *combobox = lookup_widget(GTK_WIDGET(togglebutton), "comboboxentryap2");

    if (!GTK_IS_COMBO_BOX(combobox)) {
        printf("Error: Widget 'comboboxentryap2' is not a valid GtkComboBox.\n");
        return;
    }

    // Check the state of the toggle button (active or inactive)
    gboolean is_active = gtk_toggle_button_get_active(togglebutton);

    if (is_active) {
        // Checkbox is ON: activate and populate the combobox
        gtk_widget_set_sensitive(combobox, TRUE); // Enable the combobox

        const char *filename = "agents.txt";
        char **liste = filter_agents_by_etat(filename); // Function that returns list of IDs with etat == 0

        if (liste == NULL) {
            printf("Error: No matching agents found or file read error.\n");
            return;
        }

        // Clear existing items in the combobox
        gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));

        // Populate the combobox with the filtered list
        for (int i = 0; liste[i] != NULL; i++) {
            printf("- Adding: %s\n", liste[i]);
            gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), liste[i]);
        }

        // Free the dynamically allocated list
        free_municipalite_list(liste);
    } else {
        // Checkbox is OFF: deactivate and disable the combobox
        gtk_widget_set_sensitive(combobox, FALSE); // Disable the combobox

        // Clear the combobox
        gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));
    }
}

//888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

void
on_checkbuttonassignedagent_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    // Retrieve the combobox by ID
    GtkWidget *combobox = lookup_widget(GTK_WIDGET(togglebutton), "comboboxentryforIDparking");

    if (!GTK_IS_COMBO_BOX(combobox)) {
        printf("Error: Widget 'comboboxentryap2' is not a valid GtkComboBox.\n");
        return;
    }

    // Check the state of the toggle button (active or inactive)
    gboolean is_active = gtk_toggle_button_get_active(togglebutton);

    if (is_active) {
        // Checkbox is ON: activate and populate the combobox
        gtk_widget_set_sensitive(combobox, TRUE); // Enable the combobox

        const char *filename = "parkings.txt";
        char **liste = filter_parkings_with_no_agent(filename); // Function that returns list of IDs with etat == 0

        if (liste == NULL) {
            printf("Error: No matching agents found or file read error.\n");
            return;
        }

        // Clear existing items in the combobox
        gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));

        // Populate the combobox with the filtered list
        for (int i = 0; liste[i] != NULL; i++) {
            printf("- Adding: %s\n", liste[i]);
            gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), liste[i]);
        }

        // Free the dynamically allocated list
        free_municipalite_list(liste);
    } else {
        // Checkbox is OFF: deactivate and disable the combobox
        gtk_widget_set_sensitive(combobox, FALSE); // Disable the combobox

        // Clear the combobox
        gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));
    }
}


void
on_buttonnewagentsection_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *frame = lookup_widget(GTK_WIDGET(button), "framea");

 	   // Show the GtkFixed widget
   	 gtk_widget_show(frame);
}


void
on_buttonsearchagent_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *feedback_label = lookup_widget(GTK_WIDGET(button), "labelsearchagent");
	GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entrysearchagent");
	GtkWidget *radiobuttonid = lookup_widget(GTK_WIDGET(button), "radiobuttonagent1");
	GtkWidget *radiobuttonnom = lookup_widget(GTK_WIDGET(button), "radiobuttonagent2");
	GtkTreeView *treeview = lookup_widget(GTK_WIDGET(button), "treeviewagent");
	GtkWidget *buttonsup = lookup_widget(GTK_WIDGET(button), "buttonsupprimerlp");
        GtkWidget *buttonobs = lookup_widget(GTK_WIDGET(button), "buttonobserverlp");

	gboolean is_activeid = gtk_toggle_button_get_active(radiobuttonid);
	gboolean is_activenom = gtk_toggle_button_get_active(radiobuttonnom);
	
	if (is_activeid){
		const gchar *active_text = gtk_entry_get_text(GTK_ENTRY(entry));
		const char *filename = "agents.txt";
		full_agent p;
		p =recherche_agent_all(filename, active_text);
		if (strcmp(p.id_agent, "-1") != 0) {
			clear_and_display_single_agent(treeview, p);
			gtk_label_set_text(GTK_LABEL(feedback_label), "");
		}else {
	    		// Display error message for invalid ID
	    		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : ID invalide!</span>");
		}
	}
	else if (is_activenom){
		const gchar *active_text = gtk_entry_get_text(GTK_ENTRY(entry));
		const char *filename = "agents.txt";
		SearchResult2 result = recherche_noma(filename, active_text);

    		if (result.count == 0) {
        		// Display error message for invalid ID
	    		gtk_label_set_markup(GTK_LABEL(feedback_label), "<span foreground='red'>AVERTISSEMENT : Nom invalide!</span>");
    		} else {
        		clear_and_display_agents(treeview, result.list, result.count);
			gtk_label_set_text(GTK_LABEL(feedback_label), "");
		}
	}
}


void
on_buttonafficheagent_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	// Retrieve the TreeView from the Glade file
    GtkTreeView *treeview = lookup_widget(GTK_WIDGET(button), "treeviewagent");
    if (!treeview) {
        g_print("Error: Could not find TreeView 'treeviewlp' in the Glade file.\n");
        return;
    }

    // Initialize the TreeView columns
    initialize_treeview_columns1(treeview);

    const char *filename = "agents.txt";
    // Populate the TreeView with data from the file
    if (populate_treeview_with_allagents(treeview,filename) == FALSE) {
        g_print("Error: Failed to populate TreeView from file.\n");
    }

}


void
on_buttondeleteagent_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewagent");
    if (!GTK_IS_TREE_VIEW(treeview)) {
        g_print("Error: Failed to find GtkTreeView widget.\n");
        return;
    }

    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (!GTK_IS_TREE_SELECTION(selection)) {
        g_print("Error: selection is not a valid GtkTreeSelection.\n");
        return;
    }

    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id_agent = NULL;

    const char *filename = "agents.txt";
    int test = 0;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_tree_model_get(model, &iter, 2, &id_agent, -1);

        if (id_agent != NULL) {
            test = supprimer_agent(filename, id_agent);
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
            g_print("Deleted parking with ID: %s\n", id_agent);
        }
    } else {
        g_print("No row selected to delete.\n");
    }

    if (test == 1) {
        GtkWidget *window_show = create_dialogsupprimerparking();
        gtk_widget_show(window_show);
	GtkWidget *feedback_label1 = lookup_widget(window_show, "labelsuplp");
	char buffer[50]; // Adjust size if needed
	snprintf(buffer, sizeof(buffer), "%s",id_agent);
	gtk_label_set_text(GTK_LABEL(feedback_label1), buffer);
	g_free(id_agent);
    }
}


void
on_buttonobserveagent_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonmodifyagent_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeviewagent");
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
     if (!GTK_IS_TREE_VIEW(treeview)) {
        g_print("Error: Failed to find GtkTreeView widget.\n");
        return;
    }
    if (!GTK_IS_TREE_SELECTION(selection)) {
        g_print("Error: selection is not a valid GtkTreeSelection.\n");
        return;
    }

    GtkTreeModel *model;
    GtkTreeIter iter;

	// Column values to store
	gchar *id_p;
	gchar *nom;
	gchar *prenom;
	gint telephone;
	gchar *email;
	gchar *id_agent;
	gint   etat;
	gchar *evaluation;

	// Get the selected row
	if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
  	  // Retrieve column values from the selected row
  	  gtk_tree_model_get(model, &iter,
                       0, &nom,
                       1, &prenom,
                       2, &id_agent,
                       3, &telephone,
                       4, &email,
                       5, &id_p,
                       6, &etat,
                       7, &evaluation,
                       -1);
	
    GtkWidget *window_show = create_dialogmodifyagent();
    gtk_widget_show(window_show);
   

        // Update labels with the retrieved values
        GtkWidget *entry1 = lookup_widget(window_show, "entrynamemodifyagent");
        GtkWidget *entry2 = lookup_widget(window_show, "entryfirstnamemodifyagent");
        GtkWidget *entry3 = lookup_widget(window_show, "entryphonemodifyagent");
	GtkWidget *entry4 = lookup_widget(window_show, "entryemailmodifyagent");
        GtkWidget *combobox = lookup_widget(window_show, "comboboxentryidpmodifyagent");
	GtkWidget *combobox1 = lookup_widget(window_show, "comboboxevaluationmodifyagent");
    	GtkWidget *feedback_label = lookup_widget(window_show, "labelmodifyagent");
	GtkWidget *labelid = lookup_widget(window_show, "labelidmodifyagent");	

	    // Set the info
	    char updated_textid[256]; // Allocate sufficient space
	    snprintf(updated_textid, sizeof(updated_textid), "%s", id_agent);
	    gtk_label_set_markup(GTK_LABEL(labelid), g_strdup_printf("<span foreground='black' weight='bold'>%s</span>", updated_textid));


	    // Set remaining widgets
	    gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combobox))), id_p);
	    gtk_entry_set_text(GTK_ENTRY(entry1), nom);
	    gtk_entry_set_text(GTK_ENTRY(entry2), prenom);
	    //not pre existing function
	    set_combobox_valueagent(combobox1, evaluation);


	    char buffer[20];  // Buffer to hold the converted string
	    // Convert the integer to a string
	    sprintf(buffer, "%d",telephone);
	    // Set the text in the GtkEntry
	    gtk_entry_set_text(GTK_ENTRY(entry3), buffer);

	    gtk_entry_set_text(GTK_ENTRY(entry4), email);
	    // Clear any feedback message
	    gtk_label_set_text(GTK_LABEL(feedback_label), "");


	    //open agent combobox
		const char *filename = "parkings.txt";
		char **liste = filter_parkings_with_no_agent(filename); // Function that returns list of IDs with etat == 0
		add_to_first(&liste, "No Parking assigned");

		if (liste == NULL) {
		    printf("Error: No matching agents found or file read error.\n");
		}

		// Clear existing items in the combobox
		gtk_list_store_clear(GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox))));

		// Populate the combobox with the filtered list
		for (int i = 0; liste[i] != NULL; i++) {
		    printf("- Adding: %s\n", liste[i]);
		    gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), liste[i]);
		}

		// Free the dynamically allocated list
		free_municipalite_list(liste);
	}
}


void
on_cancelbuttonmodifyagent_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "dialogmodifyagent");
	// close the modify dialog
	gtk_widget_destroy(dialog);
}


void
on_applybuttonmodifyagent_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}

