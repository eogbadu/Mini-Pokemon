#include "Pokemon.h"

// Default constructor
Pokemon::Pokemon()
{
  m_name   = "Pikachu";
  m_index  = 0;
  m_type   = "Electric";
  m_strong = "Water";
  m_health = MAX_HEALTH;
  
}

// Overloaded constructor
Pokemon::Pokemon(int index, string name, string type, string strong)
{
  m_name   = name;
  m_index  = index;
  m_type   = type;
  m_strong = strong;
  m_health = MAX_HEALTH;
}

// Returns pointer to the next pokemon
Pokemon* Pokemon::GetNext()
{
  return m_next;
}

// Returns name
string Pokemon::GetName()
{
  return m_name;
}

// Returns index
int Pokemon::GetIndex()
{
  return m_index;
}

// Returns type
string Pokemon::GetType()
{
  return m_type;
}

// Returns health
int Pokemon::GetHealth()
{
  return m_health;
}

// Returns type of Pokemon this Pokemon is strong against
string Pokemon::GetStrong()
{
  return m_strong;
}

// Sets health of pokemon
void Pokemon::SetHealth(int health)
{
  m_health = health;
}

// Sets the pointer to the next Pokemon in the list
void Pokemon::SetNext(Pokemon* next)
{
  m_next = next;
}

// Allows us to cout a Pokemon object
ostream &operator<<(ostream &output, Pokemon &P)
{
  // Declare constants
  const int JUSTIFY_SMALL  = 4;
  const int JUSTIFY_MEDIUM = 10;
  const int JUSTIFY_LARGE  = 13;

  // Set output
  output << left
	 << "Index: "   << setw(JUSTIFY_SMALL)  << P.m_index
	 << "Name: "    << setw(JUSTIFY_LARGE)  << P.m_name 
	 << " Type: "   << setw(JUSTIFY_MEDIUM) << P.m_type
	 << "Health: "  << P.m_health  << endl;

  return output;
}
