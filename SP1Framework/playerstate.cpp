#include "playerstate.h"


void PlayerState(){
	//fire deducts life, if lives == 0 spawn back at map start. Requires timing 
	//Spikes deducts life and spawn back to map starting spawn.
	//poison reverse controls.
	//fireX.push_back(26);
	//fireY.push_back(3);
	//poisonX.push_back(24);
	//poisonY.push_back(26);
	//spikeX.push_back(13);
	//spikeY.push_back(11);

	//Checking player's coordinate with fire's coordinate
	for (unsigned int i = 0; i < fireX.size(); i++){
		if ((g_sChar.m_cLocation.X == fireX[i]) && (g_sChar.m_cLocation.Y == fireY[i])){
			if (fireset == true){
				lives--;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 4;
				if (lives == 0){
					//g_ePlayerState = P_DEAD;
				}

			}

		}
	}




	//Checking player's coordinate with spike's coordinate
	for (int i = 0; i < spikeX.size(); i++){
		for (int u = 0; u < spikeY.size(); u++){
			if ((g_sChar.m_cLocation.X == spikeX[i]) && (g_sChar.m_cLocation.Y == spikeY[u])){
				lives--;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;  //Value == to spawn location at X
				g_sChar.m_cLocation.Y = 4;  //Value == to spawn location at Y
				if (lives == 0){
					g_ePlayerState = P_DEAD;
				}
				break;
			}
		}
	}

	//Checking player's coordinate and poison's coordinate
	for (unsigned int i = 0; i < poisonX.size(); i++){
		for (int u = 0; u < poisonY.size(); u++){
			if ((g_sChar.m_cLocation.X == poisonX[i]) && (g_sChar.m_cLocation.Y == poisonY[u])){
				g_ePlayerState = P_POISONED;
				break;
			}
		}
	}
}

void PlayerFire()
{
	fireX.push_back(26);
	fireX.push_back(26);
	fireX.push_back(26);
	fireX.push_back(26);
	fireX.push_back(26);
	fireY.push_back(3);
	fireY.push_back(4);
	fireY.push_back(5);
	fireY.push_back(6);
	fireY.push_back(7);


	fireX.push_back(9);
	fireX.push_back(10);
	fireX.push_back(11);
	fireX.push_back(12);
	fireX.push_back(13);
	fireX.push_back(14);
	fireX.push_back(15);
	fireX.push_back(16);
	fireX.push_back(17);
	fireX.push_back(18);
	fireX.push_back(19);
	fireX.push_back(20);
	fireX.push_back(21);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);

	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireY.push_back(10);
	fireY.push_back(11);
	fireY.push_back(12);
	fireY.push_back(13);
	fireY.push_back(14);
	fireY.push_back(15);

	//Checking player's coordinate with fire's coordinate
	for (unsigned int i = 0; i < fireX.size(); i++){
		if ((g_sChar.m_cLocation.X == fireX[i]) && (g_sChar.m_cLocation.Y == fireY[i]))
			fireset = true;
		{
			if (fireset == true){
				lives--;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 4;
				if (lives == 0){
					//g_ePlayerState = P_DEAD;
				}

				fireset = false;

			}

		}
	}
}

void PlayerSpike()
{

	spikeX.push_back(13);
	spikeY.push_back(11);


	//Checking player's coordinate with spike's coordinate
	for (int i = 0; i < spikeX.size(); i++){
		for (int u = 0; u < spikeY.size(); u++){
			if ((g_sChar.m_cLocation.X == spikeX[i]) && (g_sChar.m_cLocation.Y == spikeY[u])){
				lives--;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;  //Value == to spawn location at X
				g_sChar.m_cLocation.Y = 4;  //Value == to spawn location at Y
				if (lives == 0){
					g_ePlayerState = P_DEAD;
				}
				break;
			}
		}
	}

}
