#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H
#include "Enemy.h"

// Singleton and factory patterns
class EnemyFactory {
private:
	EnemyFactory();
	static EnemyFactory* instance;
public:
	static EnemyFactory* getInstance();
	Enemy* makeEnemy();
};

#endif