 #include <gtk/gtk.h>
 #include <gtkQR.h>

 void set_isMicro(GtkToggleButton *,gpointer);
 void set_UTF8(GtkToggleButton *,gpointer);
 void change_background(GtkColorButton *,gpointer);
 void change_foreground(GtkColorButton *,gpointer);
 void set_text(GtkButton *,gpointer);
 void save_image(GtkButton *,gpointer);
 const char *to_mode(GtkQREciMode);


  typedef struct  {

  GtkWidget *QR;
  GtkWidget *window;
  GtkWidget *Text;

  GtkComboBoxText *correction;

  GtkLabel *version;
  GtkLabel *encode;
  GtkLabel *mask;
  GtkLabel *nothing;


  GtkComboBoxText *combo;

 } My_Container;


 // Define help functions
 const char *to_version(int);
 const char *to_mask(int);
 const char *to_code(GtkQRData);
 void setInformation (My_Container *);





 int main(int argc, char **argv)
 {
  My_Container container;

  GtkWidget *window;
  GtkWidget *paned;
  GtkWidget *_qr;
  GtkWidget *GtkBox986;
  GtkWidget *GtkLabel997;
  GtkWidget *scrolltext;
  GtkWidget *viewporttext;
  GtkWidget *input_text;
  GtkWidget *GtkBox902;
  GtkWidget *GtkLabel019;
  GtkWidget *comboerror;
  GtkWidget *GtkBox213;
  GtkWidget *lbl2;
  GtkWidget *label_version;
  GtkWidget *GtkLabel354;
  GtkWidget *lbl_encode;
  GtkWidget *GtkLabel592;
  GtkWidget *lbl_mask;
  GtkWidget *GtkBox424;
  GtkWidget *lbl1;
  GtkWidget *lblNothing;
  GtkWidget *cmbecis;
  GtkWidget *isMicro;
  GtkWidget *GtkCheckButton301;
  GtkWidget *GtkBox488;
  GtkWidget *GtkBox337;
  GtkWidget *GtkLabel789;
  GtkWidget *GtkColorButton523;
  GdkRGBA gdkrgba;
  GtkWidget *GtkBox418;
  GtkWidget *GtkLabel229;
  GtkWidget *GtkColorButton963;
  GtkWidget *GtkBox685;
  GtkWidget *GtkButton257;
  GtkWidget *GtkButton634;

  gtk_init(&argc, &argv);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  paned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
  _qr = gtk_qr_new();
  GtkBox986 = gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
  GtkLabel997 = gtk_label_new ("Text");
  scrolltext = gtk_scrolled_window_new (NULL,NULL);
  viewporttext = gtk_viewport_new (NULL,NULL);
  input_text = gtk_text_view_new ();
  GtkBox902 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  GtkLabel019 = gtk_label_new ("Error");
  comboerror = gtk_combo_box_text_new();
  GtkBox213 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  lbl2 = gtk_label_new ("Version:");
  label_version = gtk_label_new (NULL);
  GtkLabel354 = gtk_label_new ("encode :");
  lbl_encode = gtk_label_new (NULL);
  GtkLabel592 = gtk_label_new ("Mask :");
  lbl_mask = gtk_label_new (NULL);
  GtkBox424 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  lbl1 = gtk_label_new ("Eci Mode:");
  lblNothing = gtk_label_new ("Nothing");
  cmbecis = gtk_combo_box_text_new();
  isMicro = gtk_check_button_new_with_label ("Is Micro");
  GtkCheckButton301 = gtk_check_button_new_with_label ("Enable UTF 8");
  GtkBox488 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  GtkBox337 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  GtkLabel789 = gtk_label_new ("Background color :");
  gdkrgba.red = 1.000000;gdkrgba.green = 1.000000;gdkrgba.blue = 1.000000;gdkrgba.alpha = 1.0;
  GtkColorButton523 = gtk_color_button_new_with_rgba(&gdkrgba);
  GtkBox418 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  GtkLabel229 = gtk_label_new ("Foreground color :");
  gdkrgba.red = 0.000000;gdkrgba.green = 0.000000;gdkrgba.blue = 0.000000;gdkrgba.alpha = 1.0;
  GtkColorButton963 = gtk_color_button_new_with_rgba(&gdkrgba);
  GtkBox685 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);
  GtkButton257 = gtk_button_new_with_label ("Set Text");
  GtkButton634 = gtk_button_new_with_label ("Save Image");


  // Setting container
  container.QR=_qr;
  container.window=window;
  container.Text = input_text;
  container.correction = GTK_COMBO_BOX_TEXT(comboerror);

  container.version = GTK_LABEL(label_version);
  container.encode = GTK_LABEL(lbl_encode);
  container.mask = GTK_LABEL(lbl_mask);
  container.nothing= GTK_LABEL(lblNothing);

  container.combo=GTK_COMBO_BOX_TEXT(cmbecis);


  gtk_window_set_default_size (GTK_WINDOW (window),800,600);
  gtk_widget_set_can_focus (window,FALSE);
  gtk_window_set_title (GTK_WINDOW (window),"Example 2");
  gtk_window_set_resizable (GTK_WINDOW (window),FALSE);
  gtk_window_set_position (GTK_WINDOW (window),GTK_WIN_POS_CENTER);
  gtk_widget_set_visible (paned,TRUE);
  gtk_widget_set_can_focus (paned,TRUE);
  gtk_paned_set_position (GTK_PANED (paned),300);
  gtk_paned_set_wide_handle (GTK_PANED (paned),TRUE);
  gtk_widget_set_visible (_qr,TRUE);
  gtk_widget_set_can_focus (_qr,FALSE);
  gtk_widget_set_visible (GtkBox986,TRUE);
  gtk_widget_set_can_focus (GtkBox986,FALSE);
  gtk_widget_set_hexpand (GtkBox986,TRUE);
  gtk_widget_set_visible (GtkLabel997,TRUE);
  gtk_widget_set_can_focus (GtkLabel997,FALSE);
  gtk_widget_set_halign (GtkLabel997,GTK_ALIGN_START);
  gtk_widget_set_margin_start (GtkLabel997,5);
  gtk_widget_set_margin_top (GtkLabel997,5);
  gtk_widget_set_margin_bottom (GtkLabel997,5);
  gtk_widget_set_size_request (scrolltext,-1,200);
  gtk_widget_set_visible (scrolltext,TRUE);
  gtk_widget_set_can_focus (scrolltext,TRUE);
  gtk_widget_set_margin_start (scrolltext,5);
  gtk_widget_set_margin_end (scrolltext,5);
  gtk_widget_set_margin_top (scrolltext,5);
  gtk_widget_set_margin_bottom (scrolltext,5);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolltext),GTK_SHADOW_IN);
  gtk_widget_set_visible (viewporttext,TRUE);
  gtk_widget_set_can_focus (viewporttext,FALSE);
  gtk_widget_set_visible (input_text,TRUE);
  gtk_widget_set_can_focus (input_text,TRUE);
  gtk_widget_set_margin_top (input_text,5);
  gtk_widget_set_margin_bottom (input_text,5);
  gtk_widget_set_visible (GtkBox902,TRUE);
  gtk_widget_set_can_focus (GtkBox902,FALSE);
  gtk_widget_set_visible (GtkLabel019,TRUE);
  gtk_widget_set_can_focus (GtkLabel019,FALSE);
  gtk_widget_set_halign (GtkLabel019,GTK_ALIGN_START);
  gtk_widget_set_margin_start (GtkLabel019,5);
  gtk_widget_set_margin_end (GtkLabel019,5);
  gtk_widget_set_margin_top (GtkLabel019,5);
  gtk_widget_set_margin_bottom (GtkLabel019,5);
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (comboerror),"4","Nothing");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (comboerror),"1","L");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (comboerror),"2","M");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (comboerror),"3","Q");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (comboerror),"4","H");
  gtk_widget_set_size_request (comboerror,100,-1);
  gtk_widget_set_visible (comboerror,TRUE);
  gtk_widget_set_can_focus (comboerror,FALSE);
  gtk_widget_set_halign (comboerror,GTK_ALIGN_START);
  gtk_widget_set_margin_top (comboerror,5);
  gtk_widget_set_margin_bottom (comboerror,5);
  gtk_combo_box_set_active (GTK_COMBO_BOX (comboerror),1);
  gtk_widget_set_visible (GtkBox213,TRUE);
  gtk_widget_set_can_focus (GtkBox213,FALSE);
  gtk_widget_set_visible (lbl2,TRUE);
  gtk_widget_set_can_focus (lbl2,FALSE);
  gtk_widget_set_margin_start (lbl2,5);
  gtk_widget_set_margin_end (lbl2,5);
  gtk_widget_set_margin_top (lbl2,5);
  gtk_widget_set_margin_bottom (lbl2,5);
  gtk_widget_set_can_focus (label_version,FALSE);
  gtk_widget_set_visible (GtkLabel354,TRUE);
  gtk_widget_set_can_focus (GtkLabel354,FALSE);
  gtk_widget_set_margin_start (GtkLabel354,5);
  gtk_widget_set_margin_end (GtkLabel354,5);
  gtk_widget_set_margin_top (GtkLabel354,5);
  gtk_widget_set_margin_bottom (GtkLabel354,5);
  gtk_widget_set_can_focus (lbl_encode,FALSE);
  gtk_widget_set_margin_start (lbl_encode,5);
  gtk_widget_set_margin_end (lbl_encode,5);
  gtk_widget_set_margin_top (lbl_encode,5);
  gtk_widget_set_margin_bottom (lbl_encode,5);
  gtk_widget_set_visible (GtkLabel592,TRUE);
  gtk_widget_set_can_focus (GtkLabel592,FALSE);
  gtk_widget_set_margin_start (GtkLabel592,5);
  gtk_widget_set_margin_end (GtkLabel592,5);
  gtk_widget_set_margin_top (GtkLabel592,5);
  gtk_widget_set_margin_bottom (GtkLabel592,5);
  gtk_widget_set_can_focus (lbl_mask,FALSE);
  gtk_widget_set_margin_start (lbl_mask,5);
  gtk_widget_set_margin_end (lbl_mask,5);
  gtk_widget_set_margin_top (lbl_mask,5);
  gtk_widget_set_margin_bottom (lbl_mask,5);
  gtk_widget_set_visible (GtkBox424,TRUE);
  gtk_widget_set_can_focus (GtkBox424,FALSE);
  gtk_widget_set_visible (lbl1,TRUE);
  gtk_widget_set_can_focus (lbl1,FALSE);
  gtk_widget_set_halign (lbl1,GTK_ALIGN_START);
  gtk_widget_set_margin_start (lbl1,5);
  gtk_widget_set_margin_end (lbl1,10);
  gtk_widget_set_margin_top (lbl1,5);
  gtk_widget_set_margin_bottom (lbl1,5);
  gtk_widget_set_can_focus (lblNothing,FALSE);
  gtk_widget_set_halign (lblNothing,GTK_ALIGN_START);
  gtk_widget_set_margin_top (lblNothing,5);
  gtk_widget_set_margin_bottom (lblNothing,5);
  gtk_widget_set_can_focus (cmbecis,FALSE);
  gtk_widget_set_margin_top (cmbecis,5);
  gtk_widget_set_margin_bottom (cmbecis,5);
  gtk_widget_set_visible (isMicro,TRUE);
  gtk_widget_set_can_focus (isMicro,TRUE);
  gtk_widget_set_receives_default (isMicro,FALSE);
  gtk_widget_set_margin_start (isMicro,5);
  gtk_widget_set_margin_top (isMicro,5);
  gtk_widget_set_margin_bottom (isMicro,5);
  g_object_set (G_OBJECT (isMicro),"draw-indicator",TRUE,NULL);
  gtk_widget_set_visible (GtkCheckButton301,TRUE);
  gtk_widget_set_can_focus (GtkCheckButton301,TRUE);
  gtk_widget_set_receives_default (GtkCheckButton301,FALSE);
  gtk_widget_set_margin_start (GtkCheckButton301,5);
  gtk_widget_set_margin_top (GtkCheckButton301,5);
  gtk_widget_set_margin_bottom (GtkCheckButton301,5);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (GtkCheckButton301),TRUE);
  g_object_set (G_OBJECT (GtkCheckButton301),"draw-indicator",TRUE,NULL);
  gtk_widget_set_visible (GtkBox488,TRUE);
  gtk_widget_set_can_focus (GtkBox488,FALSE);
  gtk_widget_set_visible (GtkBox337,TRUE);
  gtk_widget_set_can_focus (GtkBox337,FALSE);
  gtk_widget_set_visible (GtkLabel789,TRUE);
  gtk_widget_set_can_focus (GtkLabel789,FALSE);
  gtk_widget_set_margin_start (GtkLabel789,5);
  gtk_widget_set_margin_end (GtkLabel789,5);
  gtk_widget_set_margin_top (GtkLabel789,5);
  gtk_widget_set_margin_bottom (GtkLabel789,5);
  gtk_widget_set_visible (GtkColorButton523,TRUE);
  gtk_widget_set_can_focus (GtkColorButton523,TRUE);
  gtk_widget_set_receives_default (GtkColorButton523,TRUE);
  gtk_widget_set_margin_top (GtkColorButton523,5);
  gtk_widget_set_margin_bottom (GtkColorButton523,5);
  g_object_set (G_OBJECT (GtkColorButton523),"show-editor",TRUE,NULL);
  gtk_widget_set_visible (GtkBox418,TRUE);
  gtk_widget_set_can_focus (GtkBox418,FALSE);
  gtk_widget_set_visible (GtkLabel229,TRUE);
  gtk_widget_set_can_focus (GtkLabel229,FALSE);
  gtk_widget_set_margin_start (GtkLabel229,5);
  gtk_widget_set_margin_end (GtkLabel229,5);
  gtk_widget_set_margin_top (GtkLabel229,5);
  gtk_widget_set_margin_bottom (GtkLabel229,5);
  gtk_widget_set_visible (GtkColorButton963,TRUE);
  gtk_widget_set_can_focus (GtkColorButton963,TRUE);
  gtk_widget_set_receives_default (GtkColorButton963,TRUE);
  gtk_widget_set_margin_top (GtkColorButton963,5);
  gtk_widget_set_margin_bottom (GtkColorButton963,5);
  g_object_set (G_OBJECT (GtkColorButton963),"show-editor",TRUE,NULL);
  gtk_widget_set_visible (GtkBox685,TRUE);
  gtk_widget_set_can_focus (GtkBox685,FALSE);
  gtk_widget_set_halign (GtkBox685,GTK_ALIGN_END);
  gtk_widget_set_margin_end (GtkBox685,10);
  gtk_widget_set_margin_top (GtkBox685,10);
  gtk_widget_set_margin_bottom (GtkBox685,10);
  gtk_widget_set_visible (GtkButton257,TRUE);
  gtk_widget_set_can_focus (GtkButton257,TRUE);
  gtk_widget_set_receives_default (GtkButton257,TRUE);
  gtk_widget_set_margin_end (GtkButton257,10);
  gtk_widget_set_visible (GtkButton634,TRUE);
  gtk_widget_set_can_focus (GtkButton634,TRUE);
  gtk_widget_set_receives_default (GtkButton634,TRUE);

  g_signal_connect (isMicro,"toggled", G_CALLBACK (set_isMicro),&container);
  g_signal_connect (GtkCheckButton301,"toggled", G_CALLBACK (set_UTF8),&container);
  g_signal_connect (GtkColorButton523,"color-set", G_CALLBACK (change_background),&container);
  g_signal_connect (GtkColorButton963,"color-set", G_CALLBACK (change_foreground),&container);
  g_signal_connect (GtkButton257,"clicked", G_CALLBACK (set_text),&container);
  g_signal_connect (GtkButton634,"clicked", G_CALLBACK (save_image),&container);
  g_signal_connect (G_OBJECT (window), "destroy",gtk_main_quit, NULL);

  gtk_container_add (GTK_CONTAINER (window),paned);
  gtk_paned_pack1 (GTK_PANED (paned),_qr,FALSE,TRUE);
  gtk_paned_pack2 (GTK_PANED (paned),GtkBox986,TRUE,TRUE);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkLabel997,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),scrolltext,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkBox902,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkBox213,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkBox424,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),isMicro,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkCheckButton301,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkBox488,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkBox418,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox986),GtkBox685,FALSE,TRUE,0);
  gtk_container_add (GTK_CONTAINER (scrolltext),viewporttext);
  gtk_container_add (GTK_CONTAINER (viewporttext),input_text);
  gtk_box_pack_start (GTK_BOX (GtkBox902),GtkLabel019,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox902),comboerror,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox213),lbl2,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox213),label_version,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox213),GtkLabel354,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox213),lbl_encode,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox213),GtkLabel592,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox213),lbl_mask,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox424),lbl1,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox424),lblNothing,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox424),cmbecis,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox488),GtkBox337,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox337),GtkLabel789,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox337),GtkColorButton523,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox418),GtkLabel229,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox418),GtkColorButton963,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox685),GtkButton257,FALSE,TRUE,0);
  gtk_box_pack_start (GTK_BOX (GtkBox685),GtkButton634,FALSE,TRUE,0);

  gtk_widget_show_all(window);
  gtk_main();
  return 0;
 }

 void set_isMicro(GtkToggleButton *togglebutton,gpointer user_data)
 {
    My_Container *container= (My_Container *) user_data;

    if(gtk_toggle_button_get_active(togglebutton))
                    gtk_qr_set_micro(GTK_QR(container->QR),TRUE);
    else
                    gtk_qr_set_micro(GTK_QR(container->QR),FALSE);

    //force regenerate
    gtk_qr_regenerate(GTK_QR(container->QR));

    // set some information off QR
    setInformation (container);
 }

 void set_UTF8(GtkToggleButton *togglebutton,gpointer user_data)
 {
    My_Container *container= (My_Container *) user_data;

    if(gtk_toggle_button_get_active(togglebutton))
                    gtk_qr_set_UFT8(GTK_QR(container->QR),TRUE);
    else
                    gtk_qr_set_UFT8(GTK_QR(container->QR),FALSE);

    //force regenerate
    gtk_qr_regenerate(GTK_QR(container->QR));

    // set some information off QR
    setInformation (container);
 }

 void change_background(GtkColorButton *widget,gpointer user_data)
 {
    GdkRGBA color;
    My_Container *container= (My_Container *) user_data;

    gtk_color_chooser_get_rgba ( GTK_COLOR_CHOOSER(widget), &color);
    gtk_qr_set_background_color(GTK_QR(container->QR),&color);
 }

 void change_foreground(GtkColorButton *widget,gpointer user_data)
 {
    GdkRGBA color;
    My_Container *container= (My_Container *) user_data;

    gtk_color_chooser_get_rgba ( GTK_COLOR_CHOOSER(widget), &color);
    gtk_qr_set_foreground_color(GTK_QR(container->QR),&color);
 }

 void set_text(GtkButton *button,gpointer user_data)
 {
   int value;
   GtkTextIter start, end;
   GtkTextBuffer *buffer;
   gchar *text;
   My_Container *container= (My_Container *) user_data;

   buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(container->Text));
   gtk_text_buffer_get_bounds (buffer, &start, &end);
   text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

    value = gtk_combo_box_get_active(GTK_COMBO_BOX(container->correction));
    switch(value)
    {
        case 0:
            gtk_qr_set_text_and_correction(GTK_QR(container->QR),text,GTKQR_ERROR_CORRECTION_LEVEL_NOTHING);
        break;
        case 1:
           gtk_qr_set_text_and_correction(GTK_QR(container->QR),text,GTKQR_ERROR_CORRECTION_LEVEL_LOW);
        break;
        case 2:
           gtk_qr_set_text_and_correction(GTK_QR(container->QR),text,GTKQR_ERROR_CORRECTION_LEVEL_MEDIUM);
        break;
        case 3:
           gtk_qr_set_text_and_correction(GTK_QR(container->QR),text,GTKQR_ERROR_CORRECTION_LEVEL_QUALITY);
        break;
        case 4:
           gtk_qr_set_text_and_correction(GTK_QR(container->QR),text,GTKQR_ERROR_CORRECTION_LEVEL_HIGH);
        break;

    }
    g_free (text);
    setInformation (container);

 }

 void setInformation (My_Container *container)
 {
    int value;

    value = gtk_qr_get_version(GTK_QR(container->QR));
    gtk_label_set_text(container->version,to_version(value));
    value = gtk_qr_get_mask(GTK_QR(container->QR));
    gtk_label_set_text(container->mask,to_mask(value));
    gtk_label_set_text(container->encode,to_code(gtk_qr_get_mode(GTK_QR(container->QR))));

    value = gtk_qr_get_number_character_encoding(GTK_QR(container->QR));
    if (value > 0)
    {
        gtk_widget_set_visible ( GTK_WIDGET(container->nothing), FALSE);
        gtk_widget_set_visible ( GTK_WIDGET(container->combo), TRUE);
        gtk_combo_box_text_remove_all (  GTK_COMBO_BOX_TEXT(container->combo) );

        for (int i = 0;i < value ; i ++)
            gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (container->combo),NULL,to_mode(gtk_qr_get_character_encoding(GTK_QR(container->QR),i)));

        gtk_combo_box_set_active (GTK_COMBO_BOX (container->combo),0);
    }
    else
    {
        gtk_widget_set_visible ( GTK_WIDGET(container->nothing), TRUE);
        gtk_widget_set_visible ( GTK_WIDGET(container->combo), FALSE);


    }
 }


 void save_image(GtkButton *button,gpointer user_data)
 {
    GtkFileFilter *filter;
    GtkWidget *filechooser;
    gchar *value;
    My_Container *container= (My_Container *) user_data;


    filechooser = gtk_file_chooser_dialog_new ("Save Image as ...",GTK_WINDOW(container->window),GTK_FILE_CHOOSER_ACTION_SAVE,"_Save",GTK_RESPONSE_ACCEPT,"_Cancel",GTK_RESPONSE_REJECT,NULL);
    filter = gtk_file_filter_new ();
    gtk_file_filter_set_name (filter,"Image files");
    gtk_file_filter_add_pattern (filter, "*.jpg");
    gtk_file_filter_add_pattern (filter, "*.jpeg");
    gtk_file_filter_add_pattern (filter, "*.png");
    gtk_file_filter_add_pattern (filter, "*.bmp");
    gtk_file_filter_add_pattern (filter, "*.ico");

    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(filechooser),filter);

    if(gtk_dialog_run (GTK_DIALOG (filechooser))==GTK_RESPONSE_ACCEPT)
    {
        value=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(filechooser));
        gtk_qr_save_image(GTK_QR(container->QR),(const char *)value,90,200);

        g_free(value);
    }


    gtk_widget_destroy(filechooser);
 }


 const char *to_version(int version)
 {

     if(version==1)
             return "QR_1";
     else if(version==2)
             return "QR_2";
     else if(version==3)
             return "QR_3";
     else if(version==4)
             return "QR_4";
     else if(version==5)
             return "QR_5";
     else if(version==6)
             return "QR_6";
     else if(version==7)
             return "QR_7";
     else if(version==8)
             return "QR_8";
     else if(version==9)
             return "QR_9";
     else if(version==10)
             return "QR_10";
     else if(version==11)
             return "QR_11";
     else if(version==12)
             return "QR_12";
     else if(version==13)
             return "QR_13";
     else if(version==14)
             return "QR_14";
     else if(version==15)
             return "QR_15";
     else if(version==16)
             return "QR_16";
     else if(version==17)
             return "QR_17";
     else if(version==18)
             return "QR_18";
     else if(version==19)
             return "QR_19";
     else if(version==20)
             return "QR_20";
     else if(version==21)
             return "QR_21";
     else if(version==22)
             return "QR_22";
     else if(version==23)
             return "QR_23";
     else if(version==24)
             return "QR_24";
     else if(version==25)
             return "QR_25";
     else if(version==26)
             return "QR_26";
     else if(version==27)
             return "QR_27";
     else if(version==28)
             return "QR_28";
     else if(version==29)
             return "QR_29";
     else if(version==30)
             return "QR_30";
     else if(version==31)
             return "QR_31";
     else if(version==32)
             return "QR_32";
     else if(version==33)
             return "QR_33";
     else if(version==34)
             return "QR_34";
     else if(version==35)
             return "QR_35";
     else if(version==36)
             return "QR_36";
     else if(version==37)
             return "QR_37";
     else if(version==38)
             return "QR_38";
     else if(version==39)
             return "QR_39";
     else if(version==40)
             return "QR_40";
     else if(version==0)
             return "NULL";
     else if(version==GTKQR_VERSION_NUMBER_M1)
             return "M1";
     else if(version==GTKQR_VERSION_NUMBER_M2)
             return "M2";
     else if(version==GTKQR_VERSION_NUMBER_M3)
             return "M3";
     else if(version==GTKQR_VERSION_NUMBER_M4)
             return "M4";


     return "";

 }

const char *to_mask(int mask)
{
    switch(mask)
    {
    case 0:
        return "0";
        break;
    case 1:
        return "1";
        break;
    case 2:
        return "2";
        break;
    case 3:
        return "3";
        break;
    case 4:
        return "4";
        break;
    case 5:
        return "5";
        break;
    case 6:
        return "6";
        break;
    case 7:
        return "7";
        break;

    }


    return "";
}

const char *to_code(GtkQRData code)
{
    switch(code)
    {
        case GTKQR_DATA_NUMERIC:
              return "numeric";
        break;
        case GTKQR_DATA_ALPHANUMERIC:
              return "alpha";
        break;
        case GTKQR_DATA_BYTE:
              return "byte";
        break;
        case GTKQR_DATA_KANJI:
              return "kanji";
        break;
        default:

        break;
    }

    return "";
}

const char *to_mode(GtkQREciMode mode)
{
    switch(mode)
    {
        case GTKQR_ECI_MODE_ISO_8859_1:
              return "ISO 8859 1";
        break;
        case GTKQR_ECI_MODE_ISO_8859_2:
              return "ISO 8859 2";
        break;
        case GTKQR_ECI_MODE_ISO_8859_3:
              return "ISO 8859 3";
        break;
        case GTKQR_ECI_MODE_ISO_8859_4:
              return "ISO 8859 4";
        break;
        case GTKQR_ECI_MODE_ISO_8859_5:
              return "ISO 8859 5";
        break;
        case GTKQR_ECI_MODE_ISO_8859_6:
              return "ISO 8859 6";
        break;
        case GTKQR_ECI_MODE_ISO_8859_7:
              return "ISO 8859 7";
        break;
        case GTKQR_ECI_MODE_ISO_8859_8:
              return "ISO 8859 8";
        break;
        case GTKQR_ECI_MODE_ISO_8859_9:
              return "ISO 8859 9";
        break;
        case GTKQR_ECI_MODE_ISO_8859_10:
              return "ISO 8859 10";
        break;
        case GTKQR_ECI_MODE_ISO_8859_11:
              return "ISO 8859 11";
        break;
        case GTKQR_ECI_MODE_ISO_8859_13:
              return "ISO 8859 13";
        break;
        case GTKQR_ECI_MODE_ISO_8859_14:
              return "ISO 8859 14";
        break;
        case GTKQR_ECI_MODE_ISO_8859_15:
              return "ISO 8859 15";
        break;
        case GTKQR_ECI_MODE_ISO_8859_16:
              return "ISO 8859 16";
        break;
        case Shift_JIS:
              return "Shift JIS";
        break;
        case UTF_8:
              return "UTF 8";
        break;

        default:

        break;
    }

    return "";
}


