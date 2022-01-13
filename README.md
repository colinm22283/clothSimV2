# ClothSim V2
A cloth simulation built on an old version of my game engine

## Commands
| Command | Parameters | Function |
| --- | --- | --- |
| `generatemesh` |  `<x>` `<y>` `<width>` `<height>` `<spacing>` | Generates a mesh of size (`<width>`, `<height>`) at position (`<x>`, `<y>`) with `<spacing>` pixels between the nodes |
| `pin` | `<x>` `<y>` | Pins a node in place at position (`<x>`, `<y>`) |
| `unpin` | `<x>` `<y>` | Unpins a node at position (`<x>`, `<y>`) |
|`set` | `<variable>` `<value>` | sets `<variable>` to `<value>` [Set Variables](#set-vars) |

## Set Variables {#set-vars}
| Variable | Type | Function |
| --- | --- | --- |
| `linelength` | `float` | Sets the desired distance between cloth nodes |
| `decay` | `float` | Sets the rate at which the node velocity decays |
| `gravity` | `float` | Sets the gravity amount |