#include "partie.hpp"
#include "melangeur.hpp"
#include <fstream>

#include <iostream>
#include <cstdlib>
#include <sstream>

std::ostream& operator<<(std::ostream& out, Amenagement amenagement) {
    switch (amenagement) {
        case Amenagement::VIDE:
            out << "VIDE";
            break;
        case Amenagement::ARBRE:
            out << "ARBRE";
            break;
        case Amenagement::PRODUCTEUR_AVOCAT:
            out << "PRODUCTEUR_AVOCAT";
            break;
        default:
            out << "UNKNOWN";
            break;
    }
    return out;
}

// Function to check if an arc exists between two tiles
bool arcExists(const Plateau& plateau, const Position& pos1, const Position& pos2) {
    // Check if both tiles exist in the grid
    if (plateau.tuiles.count(pos1) > 0 && plateau.tuiles.count(pos2) > 0) {
        // Both tiles exist, so an arc exists between them
        return true;
    } else {
        // At least one of the tiles doesn't exist, so no arc exists
        return false;
    }
}

int main() {

  //n'hésitez pas à ajouter vos propres tests

  //test de la fonction voisine
  std::cout << "=== positions voisines de {0,3} ===" << std::endl ;

  std::cout << "attendu : {-1,3}" << std::endl ;
  std::cout << voisine({0,3}, 0) << std::endl ;
  std::cout << "attendu : {0,4}" << std::endl ;
  std::cout << voisine({0,3}, 1) << std::endl ;
  std::cout << "attendu : {1,3}" << std::endl ;
  std::cout << voisine({0,3}, 2) << std::endl ;
  std::cout << "attendu : {0,2}" << std::endl ;
  std::cout << voisine({0,3}, 3) << std::endl ;

  //création d'un plateau
  Plateau p ;
  //spécification de la dimension du plateau
  p.ajouter({0,0}, {9,9}) ;

  //placement d'un arbre
  //le dernier paramètre est le numéro du joueur (inutile pour un arbre)
  p.amenager({1,1}, Amenagement::ARBRE, 0) ;

  //placement d'un producteur
  p.amenager({3,7}, Amenagement::PRODUCTEUR_AVOCAT, 0) ;

  //placement d'une boutique
  p.amenager({8,2}, Amenagement::BOUTIQUE_ECHALOTE, 1) ;

  //dessin du plateau dans la console
  std::cout << p << std::endl ;

  // Open the output file
  std::ofstream outFile("output.txt");

  // Redirect std::cout to the file
  std::streambuf* coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(outFile.rdbuf());

  // Iterate through a few well-chosen boxes
  for (const auto& tile : p.tuiles) { // Iterate over tuiles directly which is a map
      Position boxPosition = tile.first;
      std::cout << "=== Neighboring positions of " << boxPosition << " ===" << std::endl;
      // Get neighboring positions of the current box
      for (int i = 0; i < 4; ++i) {
          Position neighbor = voisine(boxPosition, i);
          std::cout << "Neighbor: " << neighbor << std::endl;
          // Check if the neighbor corresponds to a box
          auto neighborTile = p.tuiles.find(neighbor);
          if (neighborTile != p.tuiles.end()) {
              std::cout << "Corresponding tile exists." << std::endl;
              // Display layout of the neighbor tile if it exists
              std::cout << "Layout: " << neighborTile->second.amenagement << std::endl;
              // Check if the arc between the box and its neighbor exists in the graph
              if (arcExists(p, boxPosition, neighbor)) {
                  std::cout << "An arc exists between the box and its neighbor." << std::endl;
              } else {
                  std::cout << "No arc exists between the box and its neighbor." << std::endl;
              }
          } else {
              std::cout << "No corresponding tile exists." << std::endl;
          }
      }
  }
  // Reset std::cout to its original output
  std::cout.rdbuf(coutbuf);
  //dessin du plateau dans une image
  //il est également possible d'écrire un fichier png
  //pour que ça fonctionne, il faut avoir librsvg-2.0
#ifndef NO_GRAPHICS
  p.dessiner("plateau.svg", 100) ;
#endif
  
  return 0 ;
}
