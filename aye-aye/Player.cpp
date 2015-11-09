#include "Player.h"
#include "Room.h"


Player::Player(Room* room): actualRoom(room) {

}


Player::~Player() {
}

const std::string & Player::action(const std::vector<std::string>& arguments) {
	// TODO: insertar una instrucción return aquí
	return *(new std::string("hola"));
}

const std::string & Player::actualState() const{
	return actualRoom->getDescription();
}

