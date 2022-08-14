#include "discordintegration.h"
#include "discord.h"
#include <iostream>

discord::Core* core{};

void updatePres(const char* Details, const char* State)
{
	auto result = discord::Core::Create(1006738426286063766, DiscordCreateFlags_Default, &core);
	discord::Activity activity{};
	activity.SetState(Details);
	activity.SetDetails(State);
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
	});
	if (result == discord::Result::Ok)
	{
		std::cout << "presence updated ok!" << std::endl;
	}
	else
	{
		std::cout << "presence NOT updated ok!" << std::endl;
	}
}

void runcbs()
{
	::core->RunCallbacks();
}