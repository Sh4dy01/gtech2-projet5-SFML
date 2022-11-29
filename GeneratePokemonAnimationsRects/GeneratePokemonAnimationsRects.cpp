#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

const int coordsX[3] = {1,0,2};
const int coordsY[2] = {0,1};

const std::map<std::string, int> pokemons = { 
    {"BULBASAUR", 19},
    {"CHARMANDER", 18},
    {"SQUIRTLE", 16},
    {"RATTATA", 19},
    {"PIKACHU", 18},
    {"SANDSHREW", 18},
    {"MIAOUSS", 23},
    {"ABRA", 19},
    {"MAGIKARP", 21},
    {"ARCEUS", 40},
};

using namespace std;


int main() {
    ofstream f("PokemonAnimationsRegistry.h");

    f << "#pragma once " << endl;
    f << "#include \"SFML/Graphics/Rect.hpp\"" << endl << endl;

    std::for_each(pokemons.begin(), pokemons.end(), [&](const auto& pokemon) {
        std::string pixels = std::to_string(pokemon.second);

        f << "#define " << pokemon.first + "_ANIMATIONS \\" << endl;
        f << "{ \\" << endl;

        for (int numberOfAnim = 0; numberOfAnim < 3; numberOfAnim++)
        {
            f << "  { \\" << endl;

            for (int numberOfFrames = 0; numberOfFrames < 2; numberOfFrames++)
            {
                f << "      sf::IntRect(" + std::to_string(coordsX[numberOfAnim] * pokemon.second) + ", " + std::to_string(coordsY[numberOfFrames] * pokemon.second) + ", " + pixels + ", " + pixels + ")";
                if (numberOfFrames < 1) f << ",";
                f << "\\" << endl;
            }

            f << "  }";
            if (numberOfAnim < 2) f << ",";
            f << "\\" << endl;
        }

        f << "}" << endl << endl;

    });

    f.close();

    return 0;
}

