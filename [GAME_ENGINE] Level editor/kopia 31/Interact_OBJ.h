#pragma once

// Obiekty statyczne, które s¹ roz³o¿one na mapie i obiekty "¿ywe" mog¹ podejmowaæ z nimi interakcje, które uruchamiaj¹ okreœlone skrypty.
// Podstawowe skrypty bêd¹ zawarte w g³ównym projekcie - w tym projekcie ma zostaæ wygenerowany plik, za pomoc¹ którego,
// bedzie mo¿na odró¿nic czy obiekt jest statyczny czy dynamiczny i odpowiednio przypisaæ je w danym levelu.
class Interact_OBJ
{
public:
	Interact_OBJ();
	~Interact_OBJ();
};