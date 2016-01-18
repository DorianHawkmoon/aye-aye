# aye-aye
##A text adventure game

Un simple personaje que quiere pasar sus vacaciones en la casa del campo y se lo encuentra lleno de alimañas. El objetivo es acabar con ellas. Pierdes si mueres.

##Extra features:
Además de poder moverse entre lugares y coger y dejar objetos (tal cual o dentro de otros objetos), se dispone de las siguientes caracteristicas:
- Sistema de combate por turnos con uno o varios enemigos, pudiendo atacar, escapar (no siempre es posible) o equiparse y comer para modificar stats y vida
- Los enemigos muertos dejan un saco que puede tener objetos que llevaran encima (actualmente solo lo tiene el ferret en el juego por si no quieres andar buscando)
- stats del personaje, vida/ataque/defensa
- armas y armaduras que se pueden equipar y desequipar, modificando los stats
- comida y pociones que se pueden comer para recuperar vida, incluso durante combate
- distintos tipos de puertas, las que se pueden abrir y cerrar sin más, o con uno o varios objetos necesarios
- puertas/ventanas u otras cosas que pueden coordinar sus acciones (ejemplo, una puerta, cuando lo abres en un lado, por el otro lado se abre también. Otro ejemplo, una trampilla, abres por un lado, pero el otro no y puede necesitar objetos diferentes para ello (one way path))
- algunos items son contenedores, pudiendo contener otros items y abrirse y cerrarse, otros no
- algunos items se pueden coger, otros no
- inventario del jugador y de las criaturas que atacan

##Comandos:
- look [room|inventory]
- go south|west|east|north|up|down
- see [_item] [[in] inventory] es decir, see letter, see letter in inventory ó see letter inventory. Da algo más de información que look, pero ambos son muy similares. Dato, para leer la carta, usar see
- open _item|_nameExit|_direction
- take _item
- drop _item [into|in] [_item] drop letter into mailbox ó drop letter mailbox
- close _item|_nameExit|_direction
- equip _item
- unequip _item
- stats
- eat _item

durante la batalla, los comandos disponibles son:
- escape
- attack _nameEnemy
- eat _nameItem
- look
- equip _nameItem
- unequip _nameItem

##Walkthrougth:
```
Errata: durante el juego es posible que sea necesario comer algo (eat _item), no se ha especificado cuando es necesario, pero se tienen los objetos
//Empiezas en un claro del bosque con tu buzón
-open boxmail (opcional)
-see letter (opcional)
-take knife
-equip knife
-go south
-attack vole

//ahora estamos frente a la casa
-open box
-take key
-open door
-go south

//ahora estamos en la cocina, cogemos alimentos
-take can
-take cupcake
-take bread
-go west

//nos atacan y estaremos en la habitación, donde cogeremos carne, un arma y una armadura/defensa
-attack ferret
-open remains-ferret
-take meat
-open wardrobe
-take hoe
-take overalls
-equip hoe
-equip overalls
-go east

//de nuevo en la cocina, nos vamos a un lado de la casa
-go north
-go west
-attack snake

//estamos en un jardin con una trampilla, abrimos y bajamos
-open trapdoor
-go down
-attack rat
-attack rat
-attack giantspider (repetir)

-take ladder
-open up
-go up

//nos vamos al otro lado de la casa
-go east
-go east
-attack vole
-attack vole

You win

Para perder sería pelear sin equiparse nada y sin comer nada
```
