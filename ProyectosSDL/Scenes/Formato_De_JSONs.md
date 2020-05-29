Formato de los archivos de cargado/guardado�

[] denota array
{}denota objeto

pj.json

	{
	"mainPj": {
    	"Texture": 0, // numero de la textura segun el ImageID
    	"h": 145.0, // alto del mainpj

    	// Array con los objetos del inventario del personaje 
    	// (de tenerlos) antes de iniciar el acto
    	"itemList": [
    		{"x":368, "y":122, "w":64, "h":64, "descripcion":"Esta es mi descripcion", "tag":"Este es mi tag", "Texture":0}, // datos de cada objeto
    		{...},
    		{...}
    		],

    	"w": 40.0, // ancho del mainpj
    	"x": 835.0, // posicion inicial x
    	"y": 460.0 // posicion inicial y
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneX.json // X = numero de la escena

	{
		"Texture":0; //textura del fondo
        
        "AlenaActiva": true/false //si quieres que alena este activada o no. Si no pones nada se mantiene activa.

		// Array con los datos de los objetos "cogibles" por el jugador existentes en la escena
    	"ItemInventario":[
        	{"descripcion":"Esta es mi descripcion","tag":"Este es mi tag","Texture":0},
        	{"descripcion":"key","tag":"key","Texture":15},
        	{"descripcion":"adafsfdf","tag":"ffftag","Texture":14},
		{"descripcion":"adafsfdf","tag":"ffftag","Texture":14, "permanente": true}, //permanente es una variable que indica si lo vas a poder usar indefinidamente
		//o no. Poner "permanente": false es igual que no poner nada. Poner "permanente": true significa que lo puedes usar todas las veces que quieras
            {...},
            {...}

    	],

    	// Array con los datos de los objetos "abribles" con llaves existentes en la escena
    	"GODoors":[
			{"x":200,"y":500,"w":200,"h":300,"Texture":9,"tag":"key","scneNum":1, *("UnlockId"): 1},
            {...},
            {...}
    	],

    	// Array con los datos de los objetos colisionables existentes en la escena
    	"CollisionableObject":[
    		{"x":0, "y": 0, "w": 0, "h": 0, "Texture": 0},
            {...},
            {...}
    	],

    	// Array con los datos de los objetos que conectan una escena con otra y permiten paso entre escenas
    	"GOTransiciones":[
			{"x":200,"y":500,"w":200,"h":300,"Texture":9,"tag":"key","scneNum":1},
            {...},
            {...}
    	]
		
		//Array con los objetos que cambian de estado (puzzles por ahora)
		 "GOState": [
                { "x": 705, "y": 265, "w": 30, "h": 30, "Texture": 32, "rotation": -45,"numText": 43 ,"numberPuzzle": 0,"type": 0,  }, //Match3
		{"x": 705, "y": 265, "w": 30, "h": 30, "Texture": 32, "rotation": -45,"type": 1, "numCas": 3, "dificultad": 1, *("UnlockId": 1)}, //LightsOut
        { "x": 387, "y": 365, "w": 30, "h": 30, "Texture": 32, "rotation": -45, "password": "kaka","type": 2, "UnlockId": 1 }, //password
		{...}
		]
		
	}

//*SI EN AMBOS OBJETOS "UNLOCKID" ES EL MISMO, AL RESOLVER EL PUZZLE ABRE LA PUERTA, COFRE O LO QUE TOQUE. SI NO LO PONEIS NO PASA NADA, SE ABRIRIA CON LLAVE NORMAL. SI LO PONEIS,
//LA TAG QUE ABRE EL OBJETO EN SI PUEDE SER UN STRING RANDOM QUE SE OS OCURRA