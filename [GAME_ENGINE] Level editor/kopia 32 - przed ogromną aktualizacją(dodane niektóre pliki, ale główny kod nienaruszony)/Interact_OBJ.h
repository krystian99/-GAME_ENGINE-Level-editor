#pragma once

// Obiekty statyczne, kt�re s� roz�o�one na mapie i obiekty "�ywe" mog� podejmowa� z nimi interakcje, kt�re uruchamiaj� okre�lone skrypty.
// Podstawowe skrypty b�d� zawarte w g��wnym projekcie - w tym projekcie ma zosta� wygenerowany plik, za pomoc� kt�rego,
// bedzie mo�na odr�nic czy obiekt jest statyczny czy dynamiczny i odpowiednio przypisa� je w danym levelu.
class Interact_OBJ
{
public:
	Interact_OBJ();
	~Interact_OBJ();
};