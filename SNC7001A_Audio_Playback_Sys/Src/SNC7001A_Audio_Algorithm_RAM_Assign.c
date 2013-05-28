
#include "SNC7001A_Algorithm_Define.h"

__asm
{
    include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/ALGRAM_Define.h"

	//===================== Algorithm Common Usage RAM ===============================
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/ALGCommonRAM.asm"
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/SysCommonRAM.asm"


	//===================== Algorithm Individual Usage RAM ============================
	#ifdef AUDIO32_PLAY
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/Audio32RAM.asm"
	#endif
	//==================================================================================
	#ifdef MELODY_PLAY
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/MelodyRAM.asm"
	#endif
	//==================================================================================
	//==================================================================================
	#ifdef SNX8K_PLAY
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/SNX8KDecRam.asm"
	#endif
	//==================================================================================
	//==================================================================================
	#ifdef IMAADPCM_PLAY
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/IMAADPCMDecRAM.asm"
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/IMAADPCMDecRAM_R.asm"
	#endif
	//==================================================================================
	//==================================================================================
	#ifdef MUSIC96_PLAY
	include "../../SNC7001A_Audio_Algorithm_RAM_Assignment/Music96Ram.asm"
	#endif
	//==================================================================================

	
}
