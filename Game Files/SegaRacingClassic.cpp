/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include "SegaRacingClassic.h"

void SegaRacingClassic::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	UINT8 ff = helpers->ReadByte(0x834C19, /* isRelativeOffset */ false);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);

	if (FFBMode == 0)
	{	
		if ((ff > 0xD7) & (ff < 0xE0))
		{
			//Clutch
			double percentForce = (224 - ff) / 8.0;
			double percentLength = 100;
			triggers->Friction(percentForce);
		}
		else if ((ff > 0xBF) & (ff < 0xC8))
		{
			//Centering
			double percentForce = (200 - ff ) / 8.0;
			double percentLength = 100;
			triggers->Spring(pow(percentForce, 0.1));
		}
		else if ((ff > 0xB7) & (ff < 0xC0))
		{
			//Uncentering
			double percentForce = (192 - ff) / 8.0;
			double percentLength = 100;
			triggers->Sine(70, 80, percentForce);
		}
		else if ((ff > 0xA7) & (ff < 0xB0))
		{
			//Roll Left
			double percentForce = (176 - ff) / 8.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ff > 0x97) & (ff < 0xA0))
		{
			//Roll Right
			double percentForce = (160 - ff) / 8.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	else
	{		
		if ((ff > 0xD7) & (ff < 0xE0))
		{
			//Clutch
			double percentForce = (224 - ff) / 8.0;
			double percentLength = 100;
			triggers->Friction(pow(percentForce, 0.5));
		}
		else if ((ff > 0xBF) & (ff < 0xC8))
		{
			//Centering
			double percentForce = (200 - ff) / 8.0;
			double percentLength = 100;
			triggers->Spring(pow(percentForce, 0.1));
		}
		else if ((ff > 0xB7) & (ff < 0xC0))
		{
			//Uncentering
			double percentForce = (192 - ff) / 8.0;
			double percentLength = 100;
			triggers->Sine(70, 80, pow(percentForce, 0.5));
		}
		else if ((ff > 0xA7) & (ff < 0xB0))
		{
			//Roll Left
			double percentForce = (176 - ff) / 8.0;
			double percentLength = 100;
			triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((ff > 0x97) & (ff < 0xA0))
		{
			//Roll Right
			double percentForce = (160 - ff) / 8.0;
			double percentLength = 100;
			triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
	}
}