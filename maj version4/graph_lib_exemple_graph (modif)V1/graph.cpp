#include "graph.h"

using namespace std;
/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}

void Vertex::set_marqued(bool ver)
{
    marqued=ver;
}
void Vertex::set_k_marqued(bool k_mar)
{
    k_marque=k_mar;
}
bool Vertex::get_marqued()
{
    return marqued;
}
/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);
//   m_interface->m_top_box.set_posx(m_x);
    // m_interface->m_top_box.set_posx(m_y);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
    // m_x= m_interface->m_top_box.get_posx();
    //m_y= m_interface->m_top_box.get_posy();

}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    //ajouter bouton quitter
    m_tool_box.add_child(m_quitter);
    m_quitter.set_dim(73,25);
    m_quitter.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_quitter.set_bg_color(GRIS);
    //texte
    m_quitter.add_child(m_quitter_label);
    m_quitter_label.set_message("Quitter");

    //ajouter bouton sauver
    m_tool_box.add_child(m_sauver);
    m_sauver.set_dim(73,25);
    m_sauver.set_pos(1,33);
    m_sauver.set_bg_color(GRIS);
    //texte
    m_sauver.add_child(m_sauver_label);
    m_sauver_label.set_message("Sauver");

    //ajouter bouton connexe
    m_tool_box.add_child(m_connexe);
    m_connexe.set_dim(73,25);
    m_connexe.set_pos(1,66);
    m_connexe.set_bg_color(GRIS);

    //texte
    m_connexe.add_child(m_connexe_label);
    m_connexe_label.set_message("Connexe");

    //ajouter bouton k connexe
    m_tool_box.add_child(m_k_connexe);
    m_k_connexe.set_dim(73,25);
    m_k_connexe.set_pos(1,99);
    m_k_connexe.set_bg_color(GRIS);
    //texte
    m_k_connexe.add_child(m_k_connexe_label);
    m_k_connexe_label.set_message("K-connexe");

    //ajouter bouton k sommet connexe
    m_tool_box.add_child(m_k_sommet_connexe);
    m_k_sommet_connexe.set_dim(73,25);
    m_k_sommet_connexe.set_pos(1,132);
    m_k_sommet_connexe.set_bg_color(GRIS);

    m_k_sommet_connexe.add_child(m_k_sommet_connexe_label);
    m_k_sommet_connexe_label.set_message("K-som-con");

    //ajouter bouton k sommet connexe
    m_tool_box.add_child(m_temps_reel);
    m_temps_reel.set_dim(73,25);
    m_temps_reel.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    m_temps_reel.set_bg_color(VERT);

    m_temps_reel.add_child(m_temps_reel_label);
    m_temps_reel_label.set_message("Evolution");
}

void GraphInterface::sommet_box1()
{
    m_tool_box.add_child(m_sommet0);
    m_sommet0.set_dim(73,25);
    m_sommet0.set_pos(1,166);
    m_sommet0.set_bg_color(GRIS);

    m_sommet0.add_child(m_sommet_label0);
    m_sommet_label0.set_message("Sommet 0");
///----------------------------------------------
    m_tool_box.add_child(m_sommet1);
    m_sommet1.set_dim(73,25);
    m_sommet1.set_pos(1,196);
    m_sommet1.set_bg_color(GRIS);

    m_sommet1.add_child(m_sommet_label1);
    m_sommet_label1.set_message("Sommet 1");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet2);
    m_sommet2.set_dim(73,25);
    m_sommet2.set_pos(1,226);
    m_sommet2.set_bg_color(GRIS);

    m_sommet2.add_child(m_sommet_label2);
    m_sommet_label2.set_message("Sommet 2");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet3);
    m_sommet3.set_dim(73,25);
    m_sommet3.set_pos(1,256);
    m_sommet3.set_bg_color(GRIS);

    m_sommet3.add_child(m_sommet_label3);
    m_sommet_label3.set_message("Sommet 3");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet4);
    m_sommet4.set_dim(73,25);
    m_sommet4.set_pos(1,286);
    m_sommet4.set_bg_color(GRIS);

    m_sommet4.add_child(m_sommet_label4);
    m_sommet_label4.set_message("Sommet 4");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet5);
    m_sommet5.set_dim(73,25);
    m_sommet5.set_pos(1,316);
    m_sommet5.set_bg_color(GRIS);

    m_sommet5.add_child(m_sommet_label5);
    m_sommet_label5.set_message("Sommet 5");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet6);
    m_sommet6.set_dim(73,25);
    m_sommet6.set_pos(1,346);
    m_sommet6.set_bg_color(GRIS);

    m_sommet6.add_child(m_sommet_label6);
    m_sommet_label6.set_message("Sommet 6");

}

void GraphInterface::sommet_box2()
{
    ///-------------------------------------------------
    m_tool_box.add_child(m_sommet7);
    m_sommet7.set_dim(73,25);
    m_sommet7.set_pos(1,376);
    m_sommet7.set_bg_color(GRIS);

    m_sommet7.add_child(m_sommet_label7);
    m_sommet_label7.set_message("Sommet 7");

    ///-------------------------------------------------
    m_tool_box.add_child(m_sommet8);
    m_sommet8.set_dim(73,25);
    m_sommet8.set_pos(1,406);
    m_sommet8.set_bg_color(GRIS);

    m_sommet8.add_child(m_sommet_label8);
    m_sommet_label8.set_message("Sommet 8");
}

void GraphInterface::sommet_box3()
{
///-------------------------------------------------
    m_tool_box.add_child(m_sommet9);
    m_sommet9.set_dim(73,25);
    m_sommet9.set_pos(1,436);
    m_sommet9.set_bg_color(GRIS);

    m_sommet9.add_child(m_sommet_label9);
    m_sommet_label9.set_message("Sommet 9");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet10);
    m_sommet10.set_dim(73,25);
    m_sommet10.set_pos(1,466);
    m_sommet10.set_bg_color(GRIS);

    m_sommet10.add_child(m_sommet_label10);
    m_sommet_label10.set_message("Sommet 10");
///-------------------------------------------------
    m_tool_box.add_child(m_sommet11);
    m_sommet11.set_dim(73,25);
    m_sommet11.set_pos(1,496);
    m_sommet11.set_bg_color(GRIS);

    m_sommet11.add_child(m_sommet_label11);
    m_sommet_label11.set_message("Sommet 11");
}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
int Graph::updatex(int fonction, int *a,int *b,int *c,int *d,int *e,int *f,int *g,int *h,int *i,int *j,int *k,int *l, int choix)
{
    update();
    //cout<< m_vertices[0].m_interface->m_top_box.get_posx()<<" "<<m_vertices[0].m_interface->m_top_box.get_posy()<<endl;
    if(m_interface->m_connexe.clicked())
    {

        if(fonction==0)
        {
            fonction=1;
            std::cout<<"connexe"<<std::endl;
            m_interface->m_connexe.set_bg_color(BLANCROSE);
            if(choix==1)
                connexe();
            if(choix==2)
                connexe();
            if(choix==3)
                connexe();
        }
        else if(fonction==1)
        {
            fonction=0;
            std::cout<<"Q_connexe"<<std::endl;
            m_interface->m_connexe.set_bg_color(GRIS);
            if(choix==1)
                deconnexe();
            if(choix==2)
                deconnexe();
            if(choix==3)
                deconnexe();
        }

    }
    if(m_interface->m_k_connexe.clicked())
    {

        if(fonction==0)
        {
            fonction=2;
            std::cout<<"k_connexe"<<std::endl;
            m_interface->m_k_connexe.set_bg_color(BLANCROSE);
            if(choix==1)
                k_connexe();

            if(choix==2)
                k_connexe();

            if(choix==3)
                k_connexe();
        }
        else if(fonction==2)
        {
            fonction=0;
            std::cout<<"Q_k_connexe"<<std::endl;
            m_interface->m_k_connexe.set_bg_color(GRIS);
        }

    }
    if(m_interface->m_k_sommet_connexe.clicked())
    {
        if(fonction==0)
        {
            fonction=3;
            std::cout<<"k_sommet_connexe"<<std::endl;
            m_interface->m_k_sommet_connexe.set_bg_color(BLANCROSE);
        }
        else if(fonction==3)
        {
            fonction=0;
            std::cout<<"Q_k_sommet_connexe"<<std::endl;
            m_interface->m_k_sommet_connexe.set_bg_color(GRIS);
        }
    }
    if(m_interface->m_temps_reel.clicked())
    {

        if(fonction==0)
        {
            fonction=4;
            std::cout<<"temps reel"<<std::endl;
            m_interface->m_temps_reel.set_bg_color(ROUGE);
        }
        else if(fonction==4)
        {
            fonction=0;
            std::cout<<"Q_temps reel"<<std::endl;
            m_interface->m_temps_reel.set_bg_color(VERT);
        }
    }
    if(choix>0 && choix<4)
    {
        if(m_interface->m_sommet0.clicked())
        {
            if(*a==0)
            {
                m_interface->m_sommet0.set_bg_color(BLANCJAUNE);
                modi_sommet(0,0);
                *a=2;
            }
            if(*a==1)
            {
                m_interface->m_sommet0.set_bg_color(GRIS);
                modi_sommet(0,1);
                *a=0;
            }
            if(*a==2)
            {
                *a=1;
            }


        }
        if(m_interface->m_sommet1.clicked())
        {
            if(*b==0)
            {
                m_interface->m_sommet1.set_bg_color(BLANCJAUNE);
                modi_sommet(1,0);
                *b=2;
            }
            if(*b==1)
            {
                m_interface->m_sommet1.set_bg_color(GRIS);
                modi_sommet(1,1);
                *b=0;
            }
            if(*b==2)
            {
                *b=1;
            }
        }
        if(m_interface->m_sommet2.clicked())
        {
            if(*c==0)
            {
                m_interface->m_sommet2.set_bg_color(BLANCJAUNE);
                modi_sommet(2,0);
                *c=2;
            }
            if(*c==1)
            {
                m_interface->m_sommet2.set_bg_color(GRIS);
                modi_sommet(2,1);
                *c=0;
            }
            if(*c==2)
            {
                *c=1;
            }
        }
        if(m_interface->m_sommet3.clicked())
        {
            if(*d==0)
            {
                m_interface->m_sommet3.set_bg_color(BLANCJAUNE);
                modi_sommet(3,0);
                *d=2;
            }
            if(*d==1)
            {
                m_interface->m_sommet3.set_bg_color(GRIS);
                modi_sommet(3,1);
                *d=0;
            }
            if(*d==2)
            {
                *d=1;
            }
        }
        if(m_interface->m_sommet4.clicked())
        {
            if(*e==0)
            {
                m_interface->m_sommet4.set_bg_color(BLANCJAUNE);
                modi_sommet(4,0);
                *e=2;
            }
            if(*e==1)
            {
                m_interface->m_sommet4.set_bg_color(GRIS);
                modi_sommet(4,1);
                *e=0;
            }
            if(*e==2)
            {
                *e=1;
            }
        }
        if(m_interface->m_sommet5.clicked())
        {
            if(*f==0)
            {
                m_interface->m_sommet5.set_bg_color(BLANCJAUNE);
                modi_sommet(5,0);
                *f=2;
            }
            if(*f==1)
            {
                m_interface->m_sommet5.set_bg_color(GRIS);
                modi_sommet(5,1);
                *f=0;
            }
            if(*f==2)
            {
                *f=1;
            }
        }
        if(m_interface->m_sommet6.clicked())
        {
            if(*g==0)
            {
                m_interface->m_sommet6.set_bg_color(BLANCJAUNE);
                modi_sommet(6,0);
                *g=2;
            }
            if(*g==1)
            {
                m_interface->m_sommet6.set_bg_color(GRIS);
                modi_sommet(6,1);
                *g=0;
            }
            if(*g==2)
            {
                *g=1;
            }
        }
    }
    if(choix>1 && choix<4)
    {
        if(m_interface->m_sommet7.clicked())
        {
            if(*h==0)
            {
                m_interface->m_sommet7.set_bg_color(BLANCJAUNE);
                modi_sommet(7,0);
                *h=2;
            }
            if(*h==1)
            {
                m_interface->m_sommet7.set_bg_color(GRIS);
                modi_sommet(7,1);
                *h=0;
            }
            if(*h==2)
            {
                *h=1;
            }
        }
        if(m_interface->m_sommet8.clicked())
        {
            if(*i==0)
            {
                m_interface->m_sommet8.set_bg_color(BLANCJAUNE);
                modi_sommet(8,0);
                *i=2;
            }
            if(*i==1)
            {
                m_interface->m_sommet8.set_bg_color(GRIS);
                modi_sommet(8,1);
                *i=0;
            }
            if(*i==2)
            {
                *i=1;
            }
        }
    }
    if(choix==3)
    {
        if(m_interface->m_sommet9.clicked())
        {
            if(*j==0)
            {
                m_interface->m_sommet9.set_bg_color(BLANCJAUNE);
                modi_sommet(9,0);
                *j=2;
            }
            if(*j==1)
            {
                m_interface->m_sommet9.set_bg_color(GRIS);
                modi_sommet(9,1);
                *j=0;
            }
            if(*j==2)
            {
                *j=1;
            }
        }
        if(m_interface->m_sommet10.clicked())
        {
            if(*k==0)
            {
                m_interface->m_sommet10.set_bg_color(BLANCJAUNE);
                modi_sommet(10,0);
                *k=2;
            }
            if(*k==1)
            {
                m_interface->m_sommet10.set_bg_color(GRIS);
                modi_sommet(10,1);
                *k=0;
            }
            if(*k==2)
            {
                *k=1;
            }
        }
        if(m_interface->m_sommet11.clicked())
        {
            if(*l==0)
            {
                m_interface->m_sommet11.set_bg_color(BLANCJAUNE);
                modi_sommet(11,0);
                *l=2;
            }
            if(*l==1)
            {
                m_interface->m_sommet11.set_bg_color(GRIS);
                modi_sommet(11,1);
                *l=0;
            }
            if(*l==2)
            {
                *l=1;
            }
        }
    }
    return fonction;

}
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    for(auto &elem : m_edges)
    {
        elem.second.m_interface->m_top_edge.set_epaisseur(elem.second.m_weight);
    }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);



}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }
    m_edges[idx].m_idx=idx;

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    //init from et to avec vert1 et 2

    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;

    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}

/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example(std::string fichier)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);
    load(fichier);

    //Creer boutton
    if(fichier=="graphe1.txt")
    {
        m_interface->sommet_box1();
    }
    if(fichier=="graphe2.txt")
    {
        m_interface->sommet_box1();
        m_interface->sommet_box2();
    }
    if(fichier=="graphe3.txt")
    {
        m_interface->sommet_box1();
        m_interface->sommet_box2();
        m_interface->sommet_box3();
    }

}

int** Graph::init(int** m_matrice)
{
    m_matrice= new int* [m_ordre];
    for(int i=0; i<m_ordre; i++)
    {
        m_matrice[i]= new int [m_ordre];
    }


    return m_matrice;
}

void Graph::load(string nom_fichier)
{
    int* temp1=nullptr;
    int**matrice;
    int x, y, cpt=0;
    double poid_s;
    string nom_image;
    ifstream fichier(nom_fichier, ios::in);
    if(fichier)
    {
        fichier>>m_ordre>>m_degre;
        temp1=new int [m_ordre];
        for(int i=0; i<m_ordre; i++)
        {
            fichier>>temp1[i]>>poid_s>>x>>y>>nom_image;
            add_interfaced_vertex(temp1[i],poid_s,x,y,nom_image);
        }
        matrice=init(matrice);
        for(int i=0; i<m_ordre; i++)
        {
            for(int j=0; j<m_ordre; j++)
            {
                fichier>>matrice[i][j];
                if(matrice[i][j]!=0)
                {
                    add_interfaced_edge(cpt,temp1[i],temp1[j],matrice[i][j]);
                    cpt++;
                }
            }
        }
        fichier.close();
    }
}

void Graph::save(string nom_fichier)
{
    int**matrice=nullptr;
    int g=0;
    matrice=init(matrice);
    for(int i=0; i<m_ordre; i++)
    {
        for(int j=0; j<m_ordre; j++)
        {
            matrice[i][j]=0;
        }
    }

    ofstream fichier(nom_fichier,ios::out | ios::trunc);
    if(fichier)
    {
        fichier<<m_ordre<<" "<<m_degre<<"\n";
        for(int i=0; i<m_ordre; i++)
        {
            fichier<<i<<" "<<m_vertices[i].m_value<<" "<<m_vertices[i].m_interface->m_top_box.get_posx()<<" "<<m_vertices[i].m_interface->m_top_box.get_posy()
                   <<" "<<m_vertices[i].m_interface->m_img.get_pic_name();
            fichier<<"\n";
        }
        while(g<m_degre)
        {
            if(m_edges[g].m_weight==0)
            {
                m_edges[g].m_weight++;
            }
            matrice[m_edges[g].m_from][m_edges[g].m_to]=m_edges[g].m_weight;
            g++;
        }
        for(int i=0; i<m_ordre; i++)
        {
            for(int j=0; j<m_ordre; j++)
            {
                fichier<<matrice[i][j]<<" ";
            }
            fichier<<"\n";
        }
        fichier.close();
    }

}

void Graph::test_remove_edge(int eidx, int a)
{
    /// r�f�rence vers le Edge � en
    Edge &remed=m_edges.at(eidx);


    /// Il reste encore � virer l'arc supprim� de la liste des entrants et sortants des 2 sommets to et fro
    /// References sur les listes de edges des sommets from et to
    /* std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
     std::vector<int> &veto = m_vertices[remed.m_to].m_in;
     vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
     veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );*/

    if(a==1)
    {
        std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
        vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    }
    if(a==2)
    {
        std::vector<int> &veto = m_vertices[remed.m_to].m_in;
        veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );
    }

    /// Le Edge ne n�cessite pas non plus de delete car on n'a pas fait de new (s�mantique par vale
    /// Il suffit donc de supprimer l'entr�e de la map pour supprimer � la fois l'Edge et le EdgeInterf
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    //m_edges.erase( eidx );

}

void Graph::modi_sommet(int i, int aff)
{
    int maxi=0;
    bool ad;
    for(auto elem:m_edges)
    {
        if(elem.first>maxi)
        {
            maxi=elem.first;
        }
    }
    if(aff==0)
    {
        //cout<<m_edges.size()<<endl;
        for(unsigned int j=0; j<=maxi; j++)
        {
            ad=false;
            for(auto elem: m_edges)
            {
                if(elem.first==j)
                {
                    ad=true;
                }
            }
            if(ad)
            {
                if(i==m_edges[j].m_to)
                {
                    m_arete[j]=m_edges.at(j);
                    m_interface->m_main_box.remove_child(m_edges[j].m_interface->m_top_edge);
                    test_remove_edge(j,2);
                    m_edges.erase(j);
                    // m_degre--;
                }
                else if(i==m_edges[j].m_from)
                {
                    m_arete[j]=m_edges.at(j);
                    m_interface->m_main_box.remove_child(m_edges[j].m_interface->m_top_edge);
                    test_remove_edge(j,1);
                    m_edges.erase(j);
                    //m_degre--;
                }
            }


        }
        cout<<m_edges.size()<<endl;
        m_interface->m_main_box.remove_child(m_vertices[i].m_interface->m_top_box);
        m_sommet[i]=m_vertices.at(i);
        m_vertices.erase(i);
        m_ordre--;
    }

    if(aff==1)
    {


        m_vertices[i] = m_sommet[i];
        m_interface->m_main_box.add_child(m_vertices[i].m_interface->m_top_box);
//        add
        m_ordre++;

    }
}

void Graph::temps_reel()
{
    ///K capacité de portage
    double capacit;
    std::vector<double> liste;
    double total;
    double coef;
    double populas;
    double R;

    for(auto elem: m_vertices)
    {
        capacit=0;
        total=0;
        for(auto arete: m_edges)
        {
            if(m_edges[arete.first].m_to==elem.first && m_vertices[arete.second.m_from].m_value > 0)
            {
                coef = 1+(m_edges[arete.first].m_weight)/1000;
                populas = m_vertices[arete.second.m_from].m_value;
                capacit+=coef*populas;
            }
            else if(m_edges[arete.first].m_from==elem.first && m_vertices[arete.second.m_to].m_value > 0)
            {
                coef = 1+(m_edges[arete.first].m_weight)/1000;
                populas = m_vertices[arete.second.m_to].m_value;
                liste.push_back(coef*populas);
            }

        }
        for(auto coef : liste)
            total += coef/100;
        R = m_vertices[elem.first].m_coef_r;
        populas = m_vertices[elem.first].m_value;
        populas+= R*populas*(1-(populas/capacit))-total;
        m_vertices[elem.first].m_value = capacit;

        if(m_vertices[elem.first].m_value < 0)
            m_vertices[elem.first].m_value = 0;

        liste.erase(liste.begin(),liste.end());
        cout<<"populas= "<<populas<<endl;
        cout<<"capaciter="<<capacit<<endl;
    }
}

void Graph::connexe()
{

    for(auto elem : m_vertices)
    {
        //cout<<elem.first<<endl;
        int i=0;
        int j=0;
        for(auto arete : m_edges)
        {
            if(arete.second.m_from==elem.first)
            {
                i++;
                //cout<<"du sommet "<<arete.second.m_from<<" aux "<<arete.second.m_to<<endl;
                //cout<<m_vertices[arete.second.m_to].get_marqued()<<endl;
            }
            if(arete.second.m_from==elem.first && m_vertices[arete.second.m_to].get_marqued())
            {
                i=i-1;
            }
            if(arete.second.m_to==elem.first)
            {
                j++;
            }
        }

        //cout<<"i="<<i<<endl;
        if(i==0 || j<1)
        {
            m_vertices[elem.first].set_marqued(true);
            //cout<<elem.first<<m_vertices[elem.first].get_marqued()<<"true"<<endl;
        }
    }

    for(auto elem : m_vertices)
    {
        for(auto arete : m_edges)
        {

            if(arete.second.m_from==elem.first && !m_vertices[arete.second.m_to].get_marqued() && !m_vertices[arete.second.m_from].get_marqued() )
            {
                //cout<<"du sommet "<<arete.second.m_from<<" aux "<<arete.second.m_to<<endl;
                m_pile.push_back(arete.second.m_to);
                //cout<<"push"<<arete.second.m_to<<endl;
                m_edges[arete.first].m_interface->m_top_edge.set_m_color(ROUGE);
            }
        }
    }
}

void Graph::deconnexe()
{
    for(auto elem : m_vertices)
    {
        m_vertices[elem.first].set_marqued(false);
        for(auto arete : m_edges)
        {
            m_edges[arete.first].m_interface->m_top_edge.set_m_color(GRISSOMBRE);
        }
    }
}

void Graph::k_connexe()
{

    for(auto elem:m_vertices)
    {
        int k=0;
        for(auto arete: m_edges)
        {
            if(arete.second.m_from==elem.first || arete.second.m_to==elem.first)
            {
                k++;
            }
        }
        m_vertices[elem.first].degre=k;
    }
    int x=0;
    int v=0;
    for(auto elem:m_vertices)
    {
        ///comparaison
        ///iterator parcours de map si le premier egale au k
        if(v==0 || v>elem.second.degre || v==elem.second.degre)
        {
            x=elem.first;
            v=elem.second.degre;
        }
    }
    cout<<"L' element deconnecte est "<<x<<endl;
    for(auto elem : m_edges)
    {
        if(elem.second.m_from==x)
        {
            m_vertices[elem.second.m_to].set_k_marqued(true);
        }
        if(elem.second.m_to==x)
        {
            m_vertices[elem.second.m_from].set_k_marqued(true);
        }
    }
    for(auto elem: m_vertices)
    {
        if(elem.second.k_marque)
        {
            cout<<"tuer sommet "<<elem.first<<endl;
        }
    }
    cout<<"Ce graphe est un "<<v<<"-plet"<<endl;
}


