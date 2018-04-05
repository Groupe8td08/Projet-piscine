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

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
int Graph::updatex(int fonction)
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
        }
        else if(fonction==1)
        {
            fonction=0;
            std::cout<<"Q_connexe"<<std::endl;
            m_interface->m_connexe.set_bg_color(GRIS);
        }

    }
    if(m_interface->m_k_connexe.clicked())
    {

        if(fonction==0)
        {
            fonction=2;
            std::cout<<"k_connexe"<<std::endl;
            m_interface->m_k_connexe.set_bg_color(BLANCROSE);
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

    for(auto elem : m_edges)
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

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    //init from et to avec vert1 et 2

    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;
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
            total += coef/10;
        R = m_vertices[elem.first].m_coef_r;
        populas = m_vertices[elem.first].m_value;
        populas+= R*populas*(1-(populas/capacit))-total;
        m_vertices[elem.first].m_value = capacit;

        if(m_vertices[elem.first].m_value < 0)
            m_vertices[elem.first].m_value = 0;

        liste.erase(liste.begin(),liste.end());
    }
}

