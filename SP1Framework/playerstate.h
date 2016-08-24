#include "game.h"
#include <vector>

extern vector<int> fireX;
extern vector<int> fireY;
extern vector<int> spikeX;
extern vector<int> spikeY;
extern vector<int> poisonX;
extern vector<int> poisonY;

extern double  g_dElapsedTime;
extern double  g_dDeltaTime;
extern bool    g_abKeyPressed[K_COUNT];
extern bool	setTimeTrap;
extern int		timer;
extern int		lives;
extern bool	getAntiPoisonPill;
extern bool	fireset;

extern SGameChar g_sChar;
extern EPLAYERSTATES g_ePlayerState;

void PlayerState();
void PlayerFire();
void PlayerSpike();
