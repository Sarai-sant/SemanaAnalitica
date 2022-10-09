  // Situación problema 1
// Saraí Santiago Lozano A01735331
// Givka Morales López   A01423534

// Importamos las galerías necesarias
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


// creamos una estructura de datos
struct Bitacora {
  string month; // Mes
  int monthnum; // mes en numero
  int day;      // día
  // División del tiempo
  int hora;
  int minuto;
  int segundo;
  string timeStamp;

  string ipOrigin; // ip
  string message;  // mensaje
  long long int x;
  long int md; 
};

// El vector lo pasa a arreglo y el for lo va imprimiendo dependiendo del
// contador
void print(vector<Bitacora> arreglo) {
  for (int i = 0; i < arreglo.size(); i++) {
    cout << arreglo[i].month << " ";
    cout << arreglo[i].day << " ";
    cout << arreglo[i].timeStamp << " ";
    cout << arreglo[i].ipOrigin << " ";
    cout << arreglo[i].message << endl;
  }
}

// Función que va imprimiento el erreglo
void print2(vector<string> arreglo) {
  for (int i = 0; i < arreglo.size(); i++) {
    cout << arreglo[i] << endl;
  }
}

// Vector que almacena la información
vector<Bitacora> data;

// se le asigna un número a cada mes para poder compararlo
void montoInt(map<int, string> &num_month) {
  num_month.insert(pair<int, string>(1, "Jan"));
  num_month.insert(pair<int, string>(2, "Feb"));
  num_month.insert(pair<int, string>(3, "Mar"));
  num_month.insert(pair<int, string>(4, "Apr"));
  num_month.insert(pair<int, string>(5, "May"));
  num_month.insert(pair<int, string>(6, "Jun"));
  num_month.insert(pair<int, string>(7, "Jul"));
  num_month.insert(pair<int, string>(8, "Aug"));
  num_month.insert(pair<int, string>(9, "Sep"));
  num_month.insert(pair<int, string>(10, "Oct"));
  num_month.insert(pair<int, string>(11, "Nov"));
  num_month.insert(pair<int, string>(12, "Dec"));
}

// metodo que salva las palabras divididas por la estructura
void saveDataToVector(vector<string> words) {
  Bitacora temp;
  // Gracias al map tenemos las claves del mes asignadas del montoInt
  map<int, string> num_month;
  montoInt(num_month);
  vector<int> hour1;
  map<int, string>::iterator itr;
  for (int i = 0; i < words.size(); i++) {
    switch (i) {
    case 0:
      temp.month = words[i];
      for (itr = num_month.begin(); itr != num_month.end(); ++itr) {
        if (itr->second == words[i]) {
          temp.monthnum = itr->first;
        }
      }
      break;

    case 1:
      temp.day = stoi(words[i]);
      break;
    case 2: {
      temp.timeStamp = words[i]; // hora
      string text = words[i];

      stringstream input_stringstream(text);
      string hora, minuto, segundo;

      getline(input_stringstream, hora, ':');
      getline(input_stringstream, minuto, ':');
      getline(input_stringstream, segundo, ':');

      temp.hora = stoi(hora);
      temp.minuto = stoi(minuto);
      temp.segundo = stoi(segundo);
      break;
    }

    case 3:
      temp.ipOrigin = words[i]; // ip (192.168.1.1 ejemplo)
      break;
    default:
      temp.message += words[i] + " "; // mensaje final
    }
    // Guarda la fecha exacta y única asignada ya que hace la convección a
    // segundos
    temp.x = (temp.monthnum * 2592000) + temp.day * 86400 + temp.hora * 3600 +
             temp.minuto * 60 + temp.segundo;
  }
  temp.md = temp.monthnum *100 + temp.day;
  data.push_back(temp);
}

// Ordenamiento Quick Sort -> O(n log n)
void Quick(int primero, int ultimo, vector<Bitacora> &x) {
  int i = primero;
  int j = ultimo;
  struct Bitacora central = x[(primero + ultimo) / 2];
  struct Bitacora temp;
  do {
    while (central.x > x[i].x)
      i++;
    while (central.x < x[j].x)
      j--;
    if (i <= j) {
      temp = x[i];
      x[i] = x[j];
      x[j] = temp;
      i++;
      j--;
    }
  } while (i <= j);
  if (primero < j)
    Quick(primero, j, x);
  if (ultimo > i)
    Quick(i, ultimo, x);
}


void splitBySpace(string line, string space_delimiter) {
  size_t pos = 0;
  vector<string> words;
  string word;

  // ciclo que duvide las lineas por espacios
  //Si la posicion es un " " y no es aún el final de la linea...
    stringstream input_stringstream(line);  // Convertir la cadena a un stream
    while (getline(input_stringstream, word, ' '))
    {
        words.push_back(word);
    }

  saveDataToVector(words);
  int n;
}

// INICIO DEL MAIN
int main() {
  string fileName = "bitacora.txt";
  ifstream archivo(fileName.c_str());
  string line;

  int m_start, d_start, m_end, d_end;

  cin >> m_start >> d_start >> m_end >> d_end;
  int md1, md2; 
  
  md1 = m_start*100 + d_start;
  md2 = m_end*100+ d_end; 

  if (!archivo.is_open()) {
    cerr << "Unable to open file" << endl;
    return 1;
  }

  // se llama para que duvida
  while (getline(archivo, line)) {
    splitBySpace(line, " ");
  }

  int n;
  n = data.size();
  vector<Bitacora> data1;
  Quick(0, n - 1, data);
  string filename("sorted.txt");
  fstream file;


  file.open(filename, std::ios_base::app | std::ios_base::in);
  if (file.is_open()) {
    for (int i = 0; i < n; i++) {
      file << data[i].month << " ";
      file << data[i].day << " ";
      file << data[i].timeStamp << " ";
      file << data[i].ipOrigin << " ";
      file << data[i].message << endl;

      // Seccion que imprime en consola la busqueda
      // Es un IF  para dar el rango de la busqueda
      if (data[i].md >= md1  && data[i].md <= md2) {
          cout << data[i].month << " ";
          cout << data[i].day << " ";
          cout << data[i].timeStamp << " ";
          cout << data[i].ipOrigin << " ";
          cout << data[i].message << endl;
      }
    }
  }
}
