// Built with ❤ by Make Live

using UnrealBuildTool;
using System.Collections.Generic;

public class MakeLiveMultiplayerEditorTarget : TargetRules
{
	public MakeLiveMultiplayerEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "MakeLiveMultiplayer" } );
	}
}
