# Hyper Abilities
- Sonic combines his *Hyper Flash* ability from S3&K with his *Drop Dash* maneuver to form the
**Hyper Drop Flash**.  Press jump mid-air to take off in the direction held, destroying every badnik
on screen while instantly charging up a Drop Dash, you can also do a normal Drop Dash by holding jump
mid-air without any directional input.
- Tails reuinites with his **Super Flickies**, still as deadly as ever, rabidly attacking any badnik or boss
Tails could without requiring his attendence.
- Knuckles **Gliding Shock Wave Attack** comes back with with a vengeance!  Now not only retaining
his speed from a jump but increasing it, as well as breaking every badnik AND item box nearby when
colliding with a wall, can be bypassed by gliding without directional input.
- Mighty gets the brand-new **Jackhammer Earthquake Attack** which lets him reach never before seen
speeds and altitudes using his *Hammer Drop* ability in conjunction with the environment, cleaning up
badniks in the process.
- Ray's aerobatics are enhanced with his **Jet Glide** which, on pulling up while flying, releases a
super-powered implosion that sucks in rings and blows badniks away while making him as light as
a feather for a small period of time (or until you let go).

# Settings
- `hyperFlashDropDash` - Boolean that instantly activates Drop Dash when using Sonic's Hyper Flash (Default: true).

- `hyperFlashForwarding` - Boolean that activates forward-facing Hyper Flash instead of a Drop Dash while pressing jump mid-air with no directional input (Default: false).

- `GSWburst` -- Boolean that gives Hyper Knuckles' glide the ability to retain momentum while thrusting the player forward (Default: true).

- `GSWitemBoxes` -- Boolean that makes the Gliding Shock Wave Attack destroy item boxes along with badniks (Default: true).

- `JEAJank` -- Boolean that enables old, janky Jackhammer Earthquake Attack physics as seen in alpha builds (fun for speedrunners!) (Default: false).

- `superTailsOnly` -- Makes Tails follow S3&K logic for his transformations (Default: false).
>- cannot turn Super with Chaos Emeralds
>- Hyper Tails renamed to Super Tails
- `hyperStyle` - Enum that controls how hyper forms look (Default: 0)
>- 0 - non-Sonic characters use super palette that pulsates white
>- 1 - non-Sonic characters reuse super palette cycling and don't have hyper sparkles
>- 2 - non-Sonic characters use Hyper Sonic's 6-color pulsating palette

- `screenFlashFactor` - Floating-point range that controls intensity of screen flashing (Default: 1.0).
>- 0.0 - no flashing
>- 0.5 - half-intensity flashing
>- 1.0 - full-intensity flashing

- `twoHeavensMode` - Boolean that activates "Two Heavens mode", a gameplay style similar to [Characters Go Super Then Hyper](https://sonic3air.boards.net/thread/205/new-update-characters-super-hyper)
(Default: false).
>- Go into Super form by default even with all Super Emeralds
>- Press transform + up while Super to go Hyper
>- Hyper forms consume rings 1.5x as fast (does not apply in Egg Reverie)

- `enableHyperMusic` - Boolean that enables "new" music which only plays in Hyper Form (Default: true).

- `hyperMusicLoopPoint` - Integer that controls where the Hyper form music loops from, (use this if you replace the file with something else) measured in samples. (Default: 423801)

# Game.xml vs GameConfig.bin
By default, HyperMania uses `GameConfig.bin` to load global sounds and objects, this works when it's the
only mod of it's kind enabled BUT when loaded with other mods that have their own `GameConfig.bin` one
might cancel out the other. In case of this scenario you might want to try replacing this mod's `GameConfig.bin`
with the included `Game.xml`, please be warned though that this method can cause platform-specific bugs related
to level ordering (i.e. going to Encore Angel Island when starting a new Mania Mode game).