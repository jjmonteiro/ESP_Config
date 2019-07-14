
function jsonRX(json_data){

	var obj = JSON.parse(json_data);


	switch (obj.type){
		case 0:
		  document.getElementById("text2").value = obj.value;
		break;
		case 1:
		  document.getElementById("text3").value = obj.value;
		break;
		case 2:
		  document.getElementById("text4").value = obj.value;
		break;
		case 3:
		  updateTable("table1", obj.value);

		break;
		default:
	}
}


function jsonTX(json_data){
	var obj = json_data; // = JSON.stringify(json_data);
	output("request: " + obj);
	ws.send(obj);
}


