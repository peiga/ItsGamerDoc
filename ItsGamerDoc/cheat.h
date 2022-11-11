#pragma once

uintptr_t GuardedRegions = 0;

auto GetWorld(uintptr_t uworld_addr) -> uintptr_t
{
	uintptr_t uworld_offset;

	if (uworld_addr > 0x10000000000)
	{
		uworld_offset = uworld_addr - 0x10000000000;
	}
	else {
		uworld_offset = uworld_addr - 0x8000000000;
	}

	return GuardedRegions + uworld_offset;
}

auto GlowThread() -> void
{
	while (true)
	{
		GuardedRegions = Cool.GetGuardedRegions(offsets::FirstPointer);

		auto UworldAddr = Cool.Read<uintptr_t>(GuardedRegions + offsets::FirstPointer);

		auto Uworld = GetWorld(UworldAddr);

		auto GameState = Cool.Read<uintptr_t>(Uworld + offsets::GameState);

		auto PlayerArray = Cool.Read<TArray<uintptr_t>>(GameState + offsets::PlayerArray);

		if (PlayerArray.Length() == 0) continue;

		if (PlayerArray.IsValid())
		{
			for (auto& PlayerStates : PlayerArray.Iteration())
			{
				auto Pawn = Cool.ReadGuardedWrapper<uintptr_t>(PlayerStates + offsets::PawnPrivate);

				auto MeshComponent = Cool.ReadGuardedWrapper<uintptr_t>(Pawn + offsets::MeshComponent);

				auto AttachChildren = Cool.Read<TArray<uintptr_t>>(MeshComponent + offsets::AttachChildren);

				if (AttachChildren.Length() == 0) continue;

				if (AttachChildren.IsValid())
				{
					for (int i = 0; i < AttachChildren.Length(); i++)
					{
						auto Mesh = AttachChildren[i];

						if (!Mesh) continue;

						auto MeshBoneCount = Cool.Read<int>(Mesh + offsets::BoneCount);

						if (MeshBoneCount == 0) continue;

						if (MeshBoneCount > 90 && MeshBoneCount < 200)
						{
							if (Cool.Read<int>(Mesh + offsets::OutlineMode) == 3)
								Cool.Write<int>(Mesh + offsets::OutlineMode, 1);
						}

					}
				}
			}
		}
		Sleep(1000);
	}
}
