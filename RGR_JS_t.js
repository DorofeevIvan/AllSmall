
function Primary(){
	for (var i = 1; i<= 100; i++){
		this["C" + i].addEventListener("click", Game);
		this["P" + i].addEventListener("click", SetPlayerShips);
	}
}

var StartGame = false;

var PlayerStep = true;
var ComputerStep = false;


var MassPlayerShips = [];
var MassComputerShips = [];

var SetedPlayer = false;
var SetedComputer = false;

var TestedFieldsComputer = [];
var TestedFieldsPlayer = [];

var ImposibleToStayPlayer = [];
var ImposibleToStayComputer = [];

var NotNeedCheckComputer = [];

var BadNumberCellUp = [2, 3, 4, 5, 6, 7, 8, 9];
var BadNumberCellDown = [92, 93, 94, 95, 96, 97, 98, 99];
var BadNumberCellRight = [20, 30, 40, 50, 60, 70, 80, 90];
var BadNumberCellLeft = [11, 21, 31, 41, 51, 61, 71, 81];


function SetPlayerShips(){
	if(MassPlayerShips.length >= 10){
		//alert(MassPlayerShips);
		SetedPlayer = true;
		return;
	}
	let DeleteBadCells = false;
	let Cell = document.getElementById(this.id);
	Cell=Cell.id;
	//---
	if(ImposibleToStayPlayer.indexOf(Cell) != -1){

		return;
	}
	
	if(MassPlayerShips.indexOf(Cell) != -1){
		return;
	}
	document.getElementById(Cell).style.backgroundColor = "#0000ff";

	MassPlayerShips.push(Cell);
	
	//---
	//up end
	let C = String(Cell);
	let LastSymbol = parseInt(C.slice(1));
	//alert(C);
	//alert(LastSymbol);
	//alert(BadNumberCell.indexOf(las));
	if((BadNumberCellUp.indexOf(LastSymbol) != -1) && !DeleteBadCells){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+9));//----------
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+11));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//down
	if((BadNumberCellDown.indexOf(LastSymbol) != -1) && !DeleteBadCells){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-11));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-9));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//right
	if((BadNumberCellRight.indexOf(LastSymbol) != -1) && !DeleteBadCells){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-11));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+9));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//left
	if((BadNumberCellLeft.indexOf(LastSymbol) != -1) && !DeleteBadCells){//----------
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-9));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+11));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//-------------углы
	//left up
	if(LastSymbol == 1){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+11));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//right up
	if(LastSymbol == 10){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+9));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//right down
	if(LastSymbol == 100){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-11));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//left down
	if(LastSymbol == 91){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-9));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+1));
		DeleteBadCells = true;
		//alert(ImposibleToStayPlayer);
	}
	//simple cell
	if(!DeleteBadCells){
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-11));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-9));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)-1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+1));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+9));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+10));
		ImposibleToStayPlayer.push("P"+(parseInt(LastSymbol)+11));
		DeleteBadCells = true;
	}
	//alert(ImposibleToStayPlayer);
	
	if(MassPlayerShips.length == 10){
		SetedPlayer = true;
	}
}


function SetComputerShips(){
	if(SetedComputer){
		//alert(MassComputerShips);
		return;
	}
	for (let i = 0; i < 10; i++){
		let NewShip = "C"+String(Math.floor(Math.random() * 100) + 1);
		
		if(MassComputerShips.indexOf(NewShip) != -1){
			i--;
			continue;	
		}
		
		if(ImposibleToStayComputer.indexOf(NewShip) != -1){
			i--;
			continue;
		}
		
		let DeleteBadCells = false;
		
		let C = String(NewShip);
		let LastSymbol = parseInt(C.slice(1));
		//alert(C);
		//alert(LastSymbol);
		//alert(BadNumberCell.indexOf(las));
		if((BadNumberCellUp.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+9));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//down
		if((BadNumberCellDown.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-11));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-9));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//right
		if((BadNumberCellRight.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-11));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+9));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//left
		if((BadNumberCellLeft.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-9));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//-------------углы
		//left up
		if(LastSymbol == 1){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//right up
		if(LastSymbol == 10){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+9));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//right down
		if(LastSymbol == 100){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-11));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//left down
		if(LastSymbol == 91){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-9));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+1));
			DeleteBadCells = true;
			//alert(ImposibleToStayComputer);
		}
		//simple cell
		if(!DeleteBadCells){
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-11));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-9));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)-1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+1));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+9));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+10));
			ImposibleToStayComputer.push("C"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
		}
		//alert(ImposibleToStayComputer);
			
			
		
		
		
		

		
		//document.getElementById(NewShip).style.backgroundColor = "red";
		MassComputerShips.push(NewShip);
	}
	SetedComputer = true;
}


function Game(){
	if(!SetedComputer || !SetedPlayer){
		return;
	}
	StartGame = true;
	var C_s = this.id;
	if(PlayerStep){
		ShotPlayer(C_s);

	}
	if(ComputerStep){
		while(ComputerStep){
			ShotComputer();
		}
	}
	if((MassComputerShips.length == 0)||(MassPlayerShips.length == 0)){
		document.getElementById("endgame").style.visibility = "visible";
		$( function() {
			$( "#endgame" ).dialog();
			} );
		SetedComputer = false;
		SetedPlayer = false;
	}
}












function ShotPlayer(Cell){
	
	if(MassComputerShips.indexOf(Cell) == -1){
		//alert("мимо Pl");
		document.getElementById(Cell).style.backgroundColor = "#ffffff";
		TestedFieldsPlayer.push(Cell);
		ComputerStep = true;
		PlayerStep = false;

		return;
	}
	else{
		//alert("попал Pl");
		document.getElementById(Cell).style.backgroundColor = "#ff4d00";
		let Destroyed = MassComputerShips.indexOf(Cell);

		MassComputerShips.splice(Destroyed, 1);
		TestedFieldsPlayer.push(Cell);

		ComputerStep = false;
		PlayerStep = true;
		return;
	}
}

function ShotComputer(){
	
	let Cell = 0;
	do{
		Cell = "P"+String(Math.floor(Math.random() * 100) + 1);
	}
	while ((TestedFieldsComputer.indexOf(Cell) != -1) || (NotNeedCheckComputer.indexOf(Cell) != -1))
	
	
	
	if(MassPlayerShips.indexOf(Cell)==-1){
		//alert("мимо PC");
		document.getElementById(Cell).style.backgroundColor = "#ffffff";
		ComputerStep = false;
		PlayerStep = true;
		TestedFieldsComputer.push(Cell);
		return;
	}
	else{
		//alert("попал PC");
		document.getElementById(Cell).style.backgroundColor = "#ff4d00";
		let Destroyed = MassPlayerShips.indexOf(Cell);
		MassPlayerShips.splice(Destroyed, 1);
		
		let C = String(Cell);
		let LastSymbol = parseInt(C.slice(1));
		
		//alert(C);
		//alert(LastSymbol);
		
		let DeleteBadCells = false;
		
		
		if((BadNumberCellUp.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+9));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//down
		if((BadNumberCellDown.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-11));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-9));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//right
		if((BadNumberCellRight.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-11));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+9));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//left
		if((BadNumberCellLeft.indexOf(LastSymbol) != -1) && !DeleteBadCells){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-9));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//-------------углы
		//left up
		if(LastSymbol == 1){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//right up
		if(LastSymbol == 10){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+9));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//right down
		if(LastSymbol == 100){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-11));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//left down
		if(LastSymbol == 91){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-9));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+1));
			DeleteBadCells = true;
			//alert(NotNeedCheckComputer);
		}
		//simple cell
		if(!DeleteBadCells){
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-11));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-9));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)-1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+1));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+9));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+10));
			NotNeedCheckComputer.push("P"+(parseInt(LastSymbol)+11));
			DeleteBadCells = true;
		}
		//alert(NotNeedCheckComputer);
		
		ComputerStep = true;
		PlayerStep = false;
		TestedFieldsComputer.push(Cell);

		
		return;
	}
}


startgame.addEventListener("click", SetComputerShips);








