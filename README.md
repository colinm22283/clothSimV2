## ClothSim V2

A cloth simulation built on an old version of my game engine

# Commands

`generatemesh x y width height spacing`
    generates a mesh of size (`width`, `height`) at position (`x`, `y`) with `spacing` pixels between the nodes

`pin x y`
    pins a node in place at position (`x`, `y`)

`unpin x y`
    unpins a node at position (`x`, `y`)

`set variable value`
    sets a `variable` to a `value`
    | Variable | linelength | decay | gravity |
    | --- | --- | --- | --- |
    | Type | float | float | float |
    | --- | --- | --- | --- |
    | Function | Changes the desired distance between cloth nodes | Changes the rate at which the nodes speed decays | Changes how hard the nodes are pulled downward |
