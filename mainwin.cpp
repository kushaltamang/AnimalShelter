#include "mainwin.h"
#include "dog.h"
#include "cat.h"
#include "rabbit.h"
#include "client.h"
#include <regex>
#include <sstream>
#include <fstream>

Mainwin::Mainwin() : shelter{new Shelter{"Mavs Animal Shelter"}} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);
    set_title(APP_TITLE);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //      F I L E --> O P E N
    Gtk::MenuItem *fileitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    fileitem_open->signal_activate().connect([this] {this->on_open_click();});
    filemenu->append(*fileitem_open);

    // F I L E --> S A V E
    Gtk::MenuItem *fileitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    fileitem_save->signal_activate().connect([this] {this->on_save_click();});
    filemenu->append(*fileitem_save);

    //      F I L E --> S A V E  A S
    Gtk::MenuItem *fileitem_saveas = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    fileitem_saveas->signal_activate().connect([this] {this->on_saveas_click();});
    filemenu->append(*fileitem_saveas);

    //      F I L E --> N E W
    Gtk::MenuItem *fileitem_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    fileitem_new->signal_activate().connect([this] {this->on_new_click();});
    filemenu->append(*fileitem_new);

    // F I L E -> P R O P E R T I E S
    Gtk::MenuItem *fileitem_properties = Gtk::manage(new Gtk::MenuItem("_Properties", true));
    fileitem_properties->signal_activate().connect([this] {this->on_properties_click();});
    filemenu->append(*fileitem_properties);


    //         F I L E --> Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

    //     C L I E N T
    // Create a Client menu and add to the menu bar
    Gtk::MenuItem *menuitem_client = Gtk::manage(new Gtk::MenuItem("_Client", true));
    menubar->append(*menuitem_client);
    Gtk::Menu *clientmenu = Gtk::manage(new Gtk::Menu());
    menuitem_client->set_submenu(*clientmenu);

    //  C L I E N T -> N E W
    Gtk::MenuItem *new_client = Gtk::manage(new Gtk::MenuItem("_New", true));
    new_client->signal_activate().connect([this] {this->on_new_client_click();});
    clientmenu->append(*new_client);

    // C L I E N T -> L I S T
    Gtk::MenuItem *menuitem_listclient = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listclient->signal_activate().connect([this] {this->on_list_clients_click();});
    clientmenu->append(*menuitem_listclient);

    //     A N I M A L
    // Create an Animal menu and add to the menu bar
    Gtk::MenuItem *menuitem_animal = Gtk::manage(new Gtk::MenuItem("_Animal", true));
    menubar->append(*menuitem_animal);
    Gtk::Menu *animalmenu = Gtk::manage(new Gtk::Menu());
    menuitem_animal->set_submenu(*animalmenu);

    //           N E W
    // Append New to the Animal menu
    Gtk::MenuItem *menuitem_newanimal = Gtk::manage(new Gtk::MenuItem("_New", true));
    //menuitem_newanimal->signal_activate().connect([this] {this->on_new_animal_click();});
    animalmenu->append(*menuitem_newanimal);
    Gtk::Menu *newmenu = Gtk::manage(new Gtk::Menu());
    menuitem_newanimal->set_submenu(*newmenu);


    //  N E W -> D O G
    Gtk::MenuItem *menuitem_newdog = Gtk::manage(new Gtk::MenuItem("_Dog", true));
    menuitem_newdog->signal_activate().connect([this] {this->on_new_animal_click();});
    newmenu->append(*menuitem_newdog);

    // N E W -> C A T  
    Gtk::MenuItem *menuitem_newcat = Gtk::manage(new Gtk::MenuItem("_Cat", true));
    menuitem_newcat->signal_activate().connect([this] {this->on_new_cat_click();});
    newmenu->append(*menuitem_newcat);

    // N E W -> R A B B I T
    Gtk::MenuItem *menuitem_newrabbit = Gtk::manage(new Gtk::MenuItem("_Rabbit", true));
    menuitem_newrabbit->signal_activate().connect([this] {this->on_new_rabbit_click();});
    newmenu->append(*menuitem_newrabbit);
    
    /*Gtk::ComboBox* combobox = Gtk::manage(new Gtk::ComboBox{true});
    newmenu->set_submenu(*combobox);
    combobox->append("Dog");
    combobox->append("Cat");
    combobox->append("Rabbit");
    comboboxtext->set_active(1);
    comboboxtext->signal_changed().connect([this] {this->on_new_animal_click();});*/

    //           L I S T
    // Append List to the Animal menu
    Gtk::MenuItem *menuitem_listanimal = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listanimal->signal_activate().connect([this] {this->on_list_animals_click();});
    animalmenu->append(*menuitem_listanimal);

    // A D O P T
    Gtk::MenuItem *menuitem_adopt = Gtk::manage(new Gtk::MenuItem("_Adopt", true));
    menubar->append(*menuitem_adopt);
    Gtk::Menu *adoptmenu = Gtk::manage(new Gtk::Menu());
    menuitem_adopt->set_submenu(*adoptmenu);

    // A D O P T -> N E W  A N I M A L
    Gtk::MenuItem *menuitem_adoptanimal = Gtk::manage(new Gtk::MenuItem("_Animal", true));
    menuitem_adoptanimal->signal_activate().connect([this]{this->on_adopt_animal_click();});
    adoptmenu->append(*menuitem_adoptanimal);

    // A D O P T -> L I S T
    Gtk::MenuItem *menuitem_listadoptedanimal = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listadoptedanimal->signal_activate().connect([this]{this->on_list_adopted_click();});
    adoptmenu->append(*menuitem_listadoptedanimal);

    // H E L P
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    // H E L P -> A B O U T
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this]{this->on_about_click();});
    helpmenu->append(*menuitem_about);



    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    toolbar->override_background_color(Gdk::RGBA{"gray"});
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);

    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the remaining data
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->pack_start(*data, Gtk::PACK_EXPAND_WIDGET, 0);

    // ///////////////////////////////////
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    msg->override_background_color(Gdk::RGBA{"gray"});
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_new_animal_click() {

    Gtk::Dialog dialog{"Dog Information", *this};

    Gtk::Grid grid;

    //Animal* p ;
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    //printf("%s", p->family());
        Gtk::Label l_breed{"Breed"};
    Gtk::ComboBoxText c_breed;
    for(auto b : dog_breeds) c_breed.append(to_string(b));
    c_breed.set_active(0);
    grid.attach(l_breed, 0, 1, 1, 1);
    grid.attach(c_breed, 1, 1, 2, 1);
    Gtk::Label l_gender{"Gender"};
    Gtk::ComboBoxText c_gender;
    c_gender.append("Female");
    c_gender.append("Male");
    c_gender.set_active(0);
    grid.attach(l_gender, 0, 2, 1, 1);
    grid.attach(c_gender, 1, 2, 2, 1);

    Gtk::Label l_age{"Age"};
    Gtk::SpinButton s_age;
    s_age.set_range(0,99);
    s_age.set_increments(1,5);
    s_age.set_value(5);
    grid.attach(l_age, 0, 3, 1, 1);
    grid.attach(s_age, 1, 3, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Add Dog", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if(e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        Animal* animal = new Dog{dog_breeds[c_breed.get_active_row_number()], 
                                 e_name.get_text(),
                                 (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                                 static_cast<int>(s_age.get_value())};
        shelter->add_animal(*animal);
        std::ostringstream oss;
        oss << "Added " << *animal;
        status(oss.str());
        break;
    }
}

void Mainwin::on_new_cat_click(){
    Gtk::Dialog dialog{"Cat Information", *this};
    Gtk::Grid grid;
    //Animal* p ;
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);
        Gtk::Label l_breed{"Breed"};
    Gtk::ComboBoxText c_breed;
   for(auto b : cat_breeds) c_breed.append(to_string(b));
    c_breed.set_active(0);
    grid.attach(l_breed, 0, 1, 1, 1);
    grid.attach(c_breed, 1, 1, 2, 1);
    Gtk::Label l_gender{"Gender"};
    Gtk::ComboBoxText c_gender;
    c_gender.append("Female");
    c_gender.append("Male");
    c_gender.set_active(0);
    grid.attach(l_gender, 0, 2, 1, 1);
    grid.attach(c_gender, 1, 2, 2, 1);

    Gtk::Label l_age{"Age"};
    Gtk::SpinButton s_age;
    s_age.set_range(0,99);
    s_age.set_increments(1,5);
    s_age.set_value(5);
    grid.attach(l_age, 0, 3, 1, 1);
    grid.attach(s_age, 1, 3, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Add Cat", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if(e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        Animal* animal = new Cat{cat_breeds[c_breed.get_active_row_number()], 
                                 e_name.get_text(),
                                 (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                                 static_cast<int>(s_age.get_value())};
        shelter->add_animal(*animal);
        std::ostringstream oss;
        oss << "Added " << *animal;
        status(oss.str());
        break;
    }
}

void Mainwin::on_new_rabbit_click(){
    Gtk::Dialog dialog{"Rabbit Information", *this};
    Gtk::Grid grid;
    //Animal* p ;
    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);
    Gtk::Label l_breed{"Breed"};
    Gtk::ComboBoxText c_breed;
   for(auto b : rabbit_breeds) c_breed.append(to_string(b));
    c_breed.set_active(0);
    grid.attach(l_breed, 0, 1, 1, 1);
    grid.attach(c_breed, 1, 1, 2, 1);
    Gtk::Label l_gender{"Gender"};
    Gtk::ComboBoxText c_gender;
    c_gender.append("Female");
    c_gender.append("Male");
    c_gender.set_active(0);
    grid.attach(l_gender, 0, 2, 1, 1);
    grid.attach(c_gender, 1, 2, 2, 1);

    Gtk::Label l_age{"Age"};
    Gtk::SpinButton s_age;
    s_age.set_range(0,99);
    s_age.set_increments(1,5);
    s_age.set_value(5);
    grid.attach(l_age, 0, 3, 1, 1);
    grid.attach(s_age, 1, 3, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Add Rabbit", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if(e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        Animal* animal = new Rabbit{rabbit_breeds[c_breed.get_active_row_number()], 
                                 e_name.get_text(),
                                 (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                                 static_cast<int>(s_age.get_value())};
        shelter->add_animal(*animal);
        std::ostringstream oss;
        oss << "Added " << *animal;
        status(oss.str());
        break;
    }
}

void Mainwin::on_new_client_click()
{
    Gtk::Dialog *dlg = new Gtk::Dialog("Create a Client", *this);

    // Client Name
    Gtk::HBox hbox;
    Gtk::Label client_name{"Name: "};
    hbox.pack_start(client_name,Gtk::PACK_SHRINK);
    Gtk::Entry name_entry;
    name_entry.set_max_length(20);
    hbox.pack_start(name_entry,Gtk::PACK_SHRINK);
    dlg->get_vbox()->pack_start(hbox,Gtk::PACK_SHRINK);


    // Client Phone Number
    Gtk::HBox pbox;
    Gtk::Label client_num{"Phone: "};
    pbox.pack_start(client_num, Gtk::PACK_SHRINK);
    Gtk::Entry num_entry;
    num_entry.set_max_length(50);
    num_entry.set_text("XXX-XXX-XXXX");
    pbox.pack_start(num_entry, Gtk::PACK_SHRINK);
    dlg->get_vbox()->pack_start(pbox, Gtk::PACK_SHRINK);

    // Client email
    Gtk::HBox ebox;
    Gtk::Label client_email{"Email: "};
    ebox.pack_start(client_email,Gtk::PACK_SHRINK);
    Gtk::Entry email_entry;
    email_entry.set_max_length(40);
    ebox.pack_start(email_entry,Gtk::PACK_SHRINK);
    dlg->get_vbox()->pack_start(ebox,Gtk::PACK_SHRINK);

    //add OK and Cancel button
    dlg->add_button("OK",1);
    dlg->add_button("Cancel",0);

    //show the dialog box
    dlg->show_all();

    // I M P L E M E N T A T I O N
    int result;
    std::string name, phone, email;

    std::regex re_phone{"[(]?(\\d{3,3}[-)])?\\d{3,3}-\\d{4,4}"};
    bool fail = true;  
    while (fail) {
        fail = false;  
        result = dlg->run();

        if (result != 1) 
            {
                delete dlg;
                return;
            }
            // Name
        name = name_entry.get_text();
        if (name.size() == 0) {
            name_entry.set_text("### Invalid ###");
            fail = true;
        }
            // Phone
        phone = num_entry.get_text();
        if(!std::regex_match(phone,re_phone)) 
        {
            num_entry.set_text("XXX-XXX-XXXX");
            status("Invalid Number. Use given format to enter phone number (eg: 214-300-2343)");
            fail = true;
        }  
            //Email
        email = email_entry.get_text();
        if (email.size() == 0) 
        {
            email_entry.set_text("### Invalid ###");
            fail = true;
        }    
    }

    Client* client = new Client{name, phone, email};
    shelter->add_client(*client);
    std::ostringstream oss;
    oss << "Added " << *client;
    status(oss.str()); 
    delete dlg;
}

void Mainwin::on_list_animals_click() {
    std::ostringstream oss;
    for(int i=0; i<shelter->num_animals(); ++i)
        oss << shelter->animal(i) << '\n'; 
    data->set_text(oss.str());
    status("");
}      // List all animals

void Mainwin::on_list_clients_click()
{
    std::ostringstream oss;
    for(int i=0; i<shelter->num_clients(); ++i)
        oss << shelter->client(i) << '\n'; 
    data->set_text(oss.str());
    status("");
}
void Mainwin::on_adopt_animal_click()
{
    Gtk::Dialog *dialog = new Gtk::Dialog("Adopt an animal", *this);
    // Available Animals list
    Gtk::HBox hbox;
    Gtk::Label l_animal{"Available: "};
    hbox.pack_start(l_animal,Gtk::PACK_SHRINK);
    Gtk::ComboBoxText available_box;
    for(int i=0; i < shelter->num_animals(); i++)
    {
        available_box.append(shelter->animal(i).name());
    }
    hbox.pack_start(available_box);
    dialog->get_vbox()->pack_start(hbox,Gtk::PACK_SHRINK);
    
    // Clients list
    Gtk::HBox pbox;
    Gtk::Label l_clients{"Clients: "};
    pbox.pack_start(l_clients, Gtk::PACK_SHRINK);
    Gtk::ComboBoxText clients_box;
    for(int i=0; i < shelter->num_clients(); i++)
    {
        clients_box.append(shelter->client(i).name());
    }
    pbox.pack_start(clients_box);
    dialog->get_vbox()->pack_start(pbox, Gtk::PACK_SHRINK);
    

    dialog->add_button("Adopt", 1);
    dialog->add_button("Cancel", 0);

    dialog->show_all();
    int result;
    result = dialog->run();
    if (result == 0) 
    {
        delete dialog;
        return;  
    }
    if(shelter->num_clients() <= 0)
    {
        std::ostringstream oss;
        oss << "No client selected"; 
        status(oss.str());
    }
    else if(shelter->num_animals() <= 0)
    {
        std::ostringstream oss;
        oss << "No animal available";
        status(oss.str());
    }
    else
    {
        shelter->adopt(shelter->client(clients_box.get_active_row_number()),shelter->animal(available_box.get_active_row_number()));
    }
    delete dialog;

}

void Mainwin::on_list_adopted_click()
{
    Gtk::Dialog *dialog = new Gtk::Dialog("List adopted animal", *this);
    // Clients list
    Gtk::HBox pbox;
    Gtk::Label l_clients{"Clients: "};
    pbox.pack_start(l_clients, Gtk::PACK_SHRINK);
    Gtk::ComboBoxText clients_box;
    for(int i=0; i < shelter->num_clients(); i++)
    {
        clients_box.append(shelter->client(i).name());
    }
    pbox.pack_start(clients_box);
    dialog->get_vbox()->pack_start(pbox, Gtk::PACK_SHRINK);
    
    dialog->add_button("Show", 1);
    dialog->add_button("Cancel", 0);
    dialog->show_all();
    int result;
    
    result = dialog->run();
    if (result != 1) 
    {
        delete dialog;
        return;  
    }
    if(shelter->num_clients() <= 0)
    {
        std::ostringstream oss;
        oss << "No client available"; 
        status(oss.str());
    }
    else
    {
        std::ostringstream oss;
        for(int i=0; i<shelter->client(clients_box.get_active_row_number()).num_adopted(); ++i)
            oss << shelter->client(clients_box.get_active_row_number()).animal(i) << '\n'; 
        data->set_text(oss.str());
        status("");
    }
    
    delete dialog;


}

void Mainwin::on_open_click()
{
    Gtk::Dialog *dlg = new Gtk::Dialog("MASS", *this);
    Gtk::HBox pbox;
    Gtk::Label l_clients{"Do you want to save the current changes?"};
    pbox.pack_start(l_clients, Gtk::PACK_SHRINK);
    dlg->get_vbox()->pack_start(pbox, Gtk::PACK_SHRINK);
    dlg->add_button("Save", 1);
    dlg->add_button("Cancel", 0);
    dlg->show_all();
    int res;
    res = dlg->run();
    if (res == 1) 
    {
        on_save_click();
        delete dlg;
    }
    if (res ==0)
    {
        delete dlg;
    }
    Gtk::FileChooserDialog dialog("Please choose a file to open",Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    auto filter_massfile = Gtk::FileFilter::create();
    filter_massfile->set_name("MASS files");
    filter_massfile->add_pattern("*.mass");
    dialog.add_filter(filter_massfile);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.mass");

    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);
    int result = dialog.run();

    if (result == 1) {
        try{
            delete shelter;
            std::ifstream ifs{dialog.get_filename()};
            shelter = new Shelter{ifs};
            msg->set_text("File has been loaded successfully");
            }
            catch (std::exception e){
                Gtk::MessageDialog{*this, "Unable to load the file"}.run();
            }    
        }        
}

void Mainwin::on_save_click()
{
	try {
        std::ofstream ofs{"untitled.mass"};
        ofs << VERSION << '\n';
        shelter->save(ofs);
    } catch (std::exception& e) {
        std::ostringstream oss;
        oss << "Unable to save file: untitled.mass\n" << e.what();
        Gtk::MessageDialog{*this, oss.str(), false, Gtk::MESSAGE_ERROR}.run();
    }
}

void Mainwin::on_saveas_click()
{
    Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_massfile = Gtk::FileFilter::create();
    filter_massfile->set_name("MASS files");
    filter_massfile->add_pattern("*.mass");
    dialog.add_filter(filter_massfile);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.mass");

    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);
    int result = dialog.run();

    if (result == 1) {
        try{
            std::ofstream ofs{dialog.get_filename()};
            shelter->save(ofs);
            msg->set_text("File has been saved successfully");
        } catch(std::exception e){
            Gtk::MessageDialog{*this, "Unable to save the file"}.run();
        }
    }
}

void Mainwin::on_new_click()
{
    Gtk::Dialog *dlg = new Gtk::Dialog("MASS", *this);
    Gtk::HBox pbox;
    Gtk::Label l_clients{"Do you want to save the current changes?"};
    pbox.pack_start(l_clients, Gtk::PACK_SHRINK);
    dlg->get_vbox()->pack_start(pbox, Gtk::PACK_SHRINK);
    dlg->add_button("Yes", 1);
    dlg->add_button("No", 0);
    dlg->show_all();
    int res;
    res = dlg->run();
    if (res == 1) 
    {
        on_save_click();
        delete dlg;
    }
    if (res ==0)
    {
        delete dlg;
    }
    shelter = new Shelter("MASS");
}

void Mainwin::on_about_click()
{
    Gtk::AboutDialog dialog{};
    dialog.set_transient_for(*this);
    dialog.set_program_name("Mav’s Animal Shelter Software (MASS)");
    auto logo = Gdk::Pixbuf::create_from_file("petshop.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 1.0.0");
    dialog.set_copyright("Copyright 2019");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"Mohit Tamang"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {
        "MASS Logo is licensed under Smashicons https://www.flaticon.com/free-icon/pet-shop_1615232", 
};
    dialog.set_artists(artists);
    dialog.run();   
}

void Mainwin::on_properties_click()
{
	Gtk::Dialog *dlg = new Gtk::Dialog("Properties", *this);
    Gtk::HBox pbox;
    std::ostringstream oss;
    oss << "Name of shelter: "<<shelter->name() << '\n' << "Number of clients: " << shelter->num_clients() << '\n'
	<<"Number of available animals: "<< shelter->num_animals() << '\n' << "Number of adopted animals: " << shelter->client(0).num_adopted();
    Gtk::Label l_clients{oss.str()};
    pbox.pack_start(l_clients, Gtk::PACK_SHRINK);
    dlg->get_vbox()->pack_start(pbox, Gtk::PACK_SHRINK);
    dlg->show_all();
    dlg->run();
    delete dlg;
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::status(std::string s) {
    msg->set_text(s);
}
