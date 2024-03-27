//////////////////
//  SUBNET CLI  //
//  27/03/2024  //
//  VERSION 1   //
//////////////////

#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
 
using namespace std;
 
/**
 * @brief Convertit une adresse IP en binaire.
 * 
 * Cette fonction prend une adresse IP au format string en entrée
 * et retourne son équivalent binaire sous forme de string.
 * 
 * @param ip L'adresse IP à convertir.
 * @return L'adresse IP en binaire.
 */
string ipToBinary(string ip) {
    stringstream ss;
    string output = "";
    int num;
    char dot;
 
    ss << ip;
    while (ss >> num) {
        output += bitset<8>(num).to_string();
        ss >> dot; // Ignorer les points
    }
 
    return output;
}
 
/**
 * @brief Calcule le nombre d'hôtes possibles dans un sous-réseau.
 * 
 * Cette fonction prend la longueur du préfixe de sous-réseau en entrée
 * et retourne le nombre d'hôtes possibles dans ce sous-réseau.
 * 
 * @param prefixLength La longueur du préfixe de sous-réseau.
 * @return Le nombre d'hôtes possibles.
 */
unsigned int calculateHosts(int prefixLength) {
    return (1U << (32 - prefixLength)) - 2;
}
 
/**
 * @brief Obtient la liste des sous-réseaux disponibles.
 * 
 * Cette fonction prend une adresse IP de base et la longueur du préfixe de sous-réseau en entrée.
 * Elle retourne la liste des sous-réseaux disponibles dans le format "adresse de réseau - première adresse - dernière adresse".
 * 
 * @param ip L'adresse IP de base.
 * @param prefixLength La longueur du préfixe de sous-réseau.
 * @return La liste des sous-réseaux disponibles.
 */
vector<string> getSubnets(string ip, int prefixLength) {
    set<string> subnets_set;
    unsigned int numSubnets = 1U << (32 - prefixLength);
    unsigned int subnetSize = 1U << (32 - prefixLength);
    unsigned int subnetMask = (1U << (32 - prefixLength)) - 1U;
 
    for (unsigned int i = 0; i < numSubnets; ++i) {
        unsigned int subnetBase = (bitset<32>(ipToBinary(ip)).to_ulong() & (subnetMask << (32 - prefixLength))) | (i << (32 - prefixLength));
        unsigned int subnetFirst = subnetBase + 1;
        unsigned int subnetLast = subnetBase + subnetSize - 2;
        subnets_set.insert(to_string(subnetBase >> 24) + "." + to_string((subnetBase >> 16) & 255) + "." + to_string((subnetBase >> 8) & 255) + "." + to_string(subnetBase & 255)
                          + " - " + to_string(subnetFirst >> 24) + "." + to_string((subnetFirst >> 16) & 255) + "." + to_string((subnetFirst >> 8) & 255) + "." + to_string(subnetFirst & 255)
                          + " to " + to_string(subnetLast >> 24) + "." + to_string((subnetLast >> 16) & 255) + "." + to_string((subnetLast >> 8) & 255) + "." + to_string(subnetLast & 255));
    }
 
    vector<string> subnets;
    subnets.assign(subnets_set.begin(), subnets_set.end());
 
    // Tri des sous-réseaux disponibles
    sort(subnets.begin(), subnets.end());
    return subnets;
}
 
/**
 * @brief Fonction principale.
 * 
 * Cette fonction gère les arguments de la ligne de commande,
 * effectue les calculs nécessaires et affiche les informations sur le réseau.
 * 
 * @param argc Nombre d'arguments de la ligne de commande.
 * @param argv Tableau d'arguments de la ligne de commande.
 * @return 0 en cas de succès, 1 en cas d'erreur.
 */
int main(int argc, char* argv[]) {
    string ip;
    int prefixLength;
 
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " -ip <adresse IP> -cidr <notation CIDR>" << endl;
        return 1;
    }
 
    // Traitement des arguments de la ligne de commande
    for (int i = 1; i < argc; i += 2) {
        string arg = argv[i];
        if (arg == "-ip") {
            ip = argv[i + 1];
        } else if (arg == "-cidr") {
            prefixLength = atoi(argv[i + 1]);
        } else {
            cout << "Option invalide: " << arg << endl;
            return 1;
        }
    }
 
    // Convertir l'adresse IP en binaire
    string binaryIP = ipToBinary(ip);
 
    // Calculer le nombre d'hôtes
    unsigned int numHosts = calculateHosts(prefixLength);
 
    // Afficher l'adresse IP en binaire
    cout << "Informations sur le réseau :" << endl;
    cout << "--------------------------------" << endl;
    cout << "Adresse IP : " << ip << endl;
    cout << "Adresse IP binaire : " << binaryIP << endl;
 
    // Afficher le masque de sous-réseau en binaire
    string subnetMask = string(prefixLength, '1') + string(32 - prefixLength, '0');
    cout << "Masque de sous-réseau binaire : " << subnetMask << endl;
 
    // Afficher les sous-réseaux disponibles
    vector<string> subnets = getSubnets(ip, prefixLength);
    cout << "\nSous-réseaux disponibles :" << endl;
    cout << "--------------------------------" << endl;
    for (const string& subnet : subnets) {
        cout << subnet << endl;
    }
 
    cout << "\nNombre total d'hôtes disponibles : " << numHosts << endl;
 
    return 0;
}
