# Unreal Engine 5 - Multiplayer / Open World Template

An evolving template to allow teams the ability to test out multiplayer Pixel Streaming applications and worlds.

The template implements a multiplayer example deployable that can be deployed to Make Live. As Unreal Engine instances are deployed within the same private network (when uploaded using Make Live) game sessions can be seen by each other.

Useful for testing applications and worlds.  Dedicated server(s) would need to be rolled out in order to support mass amounts of players and persistent sessions. Watch this space for how we want to make this easy for people using the Make Live platform.

Template Features Include:

- C++ Unreal Engine project exposing functionallity to Blueprints as much as possible
- [Unreal Engine Pixel Streaming Plugin Enabled](https://docs.unrealengine.com/5.0/en-US/pixel-streaming-in-unreal-engine/)
- [Unreal Engine Gameplay Ability System](https://docs.unrealengine.com/5.0/en-US/gameplay-ability-system-for-unreal-engine/)
- [Unreal Engine 2KM x 2KM Map using World Partition](https://docs.unrealengine.com/5.0/en-US/world-partition-in-unreal-engine/)
- [Unreal Engine Online Subsystem Implementation (NULL by default)](https://docs.unrealengine.com/5.0/en-US/online-subsystem-in-unreal-engine/)

**Folders / Structure:**

* *SourceArt* - Used to store source art before importing into Unreal Engine.
* *Project* - Example Unreal Engine multiplayer project.
* *Project/Content/00_Core/Maps/DefaultGameOpenWorld* - Editable open world Map where players join.

**Deployed Example on Make Live:**

[https://launch.make.live/make-live/open-world](https://launch.make.live/make-live/open-world)