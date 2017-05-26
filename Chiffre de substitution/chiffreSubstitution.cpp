#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <map>
using namespace std;

// Foncteur qui effectue un chiffrement par decalage
class ChiffrementSubst{

public:

  // Constructeur prenant le nom fichier contenant les substitutions a utiliser
  ChiffrementSubst(const string& nomFichier)
  {
	  m_codeBook.clear();
	  ifstream fichier;
	  fichier.open(nomFichier.c_str());

	  // Verifie si le chemin du fichier est bien correct
	  if(!fichier.is_open())
	  {
		 fichier.close();
		 cout << "Le fichier est introuvable" << endl;
	  }
	  else
	  {
		 istream_iterator<string> it(fichier);
		 istream_iterator<string> end; //Le signal de fin
		 char key, value;

		 // Parcours le fichier
		 while (it != end)
		 {
			 // Le premier element correspond à la cle
			 key = *(it->c_str());
			 // Verifie si une valeur est associee a la cle
			 if (++it != end)
				 value = *(it->c_str());
			 else
			 {
				 //Cas ou le fichier n'est paq complet
				 cout << "Livre de code incomplet" << endl;
				 m_codeBook.clear();
				 return;
			 }
			 //Ajoute l'element dans le livre de code
			 m_codeBook[key] = value;
			 ++it;
		 }
	  }


  }
  
  // L'operateur() qui effectue le chiffrement
  char operator()(char lettre)
  {
	  // On cherche le caractere dans le livre de code
	  map<char, char>::const_iterator it = m_codeBook.find(lettre);

	  // Si l'element est present, on retourne la valeur associee
	  if (it != m_codeBook.end())
		  return it->second;
	  else
		  return lettre;
  }

private :

  //Livre de code
  map<char, char> m_codeBook;
};


int main()
{

  // Le message a crypter
  string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!");

  // Demande de la cle a l'utilisateur
  cout << "Quel fichier contenant la cle voulez-vous utiliser ? ";
  string nomFichier;
  cin >> nomFichier;

  // Creation du foncteur
  ChiffrementSubst foncteur(nomFichier);

  // Chaine de caracteres pour le message crypter
  string texte_crypte;

  // Un iterateur permettant l'insertion a la fin
  back_insert_iterator<string> it(texte_crypte);

  // On applique le foncteur sur le vector pour crypter le message en utilisant 'transform'
  transform(texte.begin(), texte.end(), it, foncteur);

  // On copie le message dans cout en utilisant l'algorithme 'copy'
  copy(texte_crypte.begin(), texte_crypte.end(), ostream_iterator<char>(cout, ","));
  cout << endl;

  return 0;
}

