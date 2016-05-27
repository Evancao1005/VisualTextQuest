#include "Item.h";


Item::Item(){

}
Item::Item(string name, bool equip, int arg_part, int mType, int m) {
	itemName = name;
	equipable = equip;
	part = arg_part;
	modificationType = mType;
	modification = m;
}
Item::~Item() {

}
string Item::getName() {
	return itemName;
}
bool Item::getEquipable() {
	return equipable;
}
int Item::getPart() {
	return part;
}
int Item::getModificationType(){
	return modificationType;
}
int Item::getModification() {
	return modification;
}